"""
MIT License

Copyright (c) 2020 Hyeonki Hong <hhk7734@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
"""

import time
import os
import shutil

import numpy as np
import cv2
import tensorflow as tf

from ..core import dataset
from ..core import utils
from ..core import yolov4


class YoloV4:
    def __init__(self, names_path, weights_path=None):
        self.strides = np.array([8, 16, 32])
        self.anchors = np.array(
            [
                12,
                16,
                19,
                36,
                40,
                28,
                36,
                75,
                76,
                55,
                72,
                146,
                142,
                110,
                192,
                243,
                459,
                401,
            ],
            dtype=np.float32,
        ).reshape(3, 3, 2)
        self.xyscale = np.array([1.2, 1.1, 1.05])
        self.width = self.height = 608

        self.classes = utils.read_class_names(names_path)
        self.num_class = len(self.classes)

        self.make_model()

        if weights_path is not None:
            self.load_weights(weights_path)

    def inference(self, media_path, is_image=True, video_interval_ms=1):
        if is_image:
            frame = cv2.imread(media_path)
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

            image = self.predict(frame, self.classes)

            cv2.namedWindow("result", cv2.WINDOW_AUTOSIZE)
            result = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
            cv2.imshow("result", result)
            cv2.waitKey(0)
        else:
            vid = cv2.VideoCapture(media_path)
            while True:
                return_value, frame = vid.read()
                if return_value:
                    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                else:
                    raise ValueError("No image! Try with another video format")

                prev_time = time.time()
                image = self.predict(frame, self.classes)
                curr_time = time.time()
                exec_time = curr_time - prev_time

                result = np.asarray(image)
                info = "time: %.2f ms" % (1000 * exec_time)
                print(info)
                cv2.namedWindow("result", cv2.WINDOW_AUTOSIZE)
                result = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
                cv2.imshow("result", result)
                if cv2.waitKey(video_interval_ms) & 0xFF == ord("q"):
                    break

    def train(
            self,
            train_annote_path,
            test_annote_path,
            pre_trained_weights=None,
            trained_weights_path="./checkpoints",
            log_dir_path="./log",
            iou_loss_threshold=0.5,
    ):

        learning_rate_init = 1e-3
        learning_rate_end = 1e-6

        physical_devices = tf.config.experimental.list_physical_devices("GPU")
        if len(physical_devices) > 0:
            tf.config.experimental.set_memory_growth(physical_devices[0], True)

        trainset = dataset.Dataset(
            annot_path=train_annote_path,
            classes=self.classes,
            anchors=self.anchors,
            input_sizes=self.width,
        )
        testset = dataset.Dataset(
            annot_path=test_annote_path,
            classes=self.classes,
            anchors=self.anchors,
            input_sizes=self.width,
            is_training=False,
        )
        isfreeze = False
        steps_per_epoch = len(trainset)
        first_stage_epochs = 20
        second_stage_epochs = 30
        global_steps = tf.Variable(1, trainable=False, dtype=tf.int64)
        warmup_steps = 2 * steps_per_epoch
        total_steps = (
                              first_stage_epochs + second_stage_epochs
                      ) * steps_per_epoch
        # train_steps = (first_stage_epochs + second_stage_epochs) * steps_per_period

        self.make_model(True)
        if pre_trained_weights is not None:
            self.load_weights(pre_trained_weights)

        optimizer = tf.keras.optimizers.Adam()
        if os.path.exists(log_dir_path):
            shutil.rmtree(log_dir_path)
        writer = tf.summary.create_file_writer(log_dir_path)

        def train_step(image_data, target):
            with tf.GradientTape() as tape:
                pred_result = self.model(image_data, training=True)
                giou_loss = conf_loss = prob_loss = 0

                # optimizing process
                for i in range(3):
                    conv, pred = pred_result[i * 2], pred_result[i * 2 + 1]
                    loss_items = yolov4.compute_loss(
                        pred,
                        conv,
                        target[i][0],
                        target[i][1],
                        strides=self.strides,
                        num_class=self.num_class,
                        iou_loss_threshold=iou_loss_threshold,
                        i=i,
                    )
                    giou_loss += loss_items[0]
                    conf_loss += loss_items[1]
                    prob_loss += loss_items[2]

                total_loss = giou_loss + conf_loss + prob_loss

                gradients = tape.gradient(
                    total_loss, self.model.trainable_variables
                )
                optimizer.apply_gradients(
                    zip(gradients, self.model.trainable_variables)
                )
                tf.print(
                    "=> STEP %4d   lr: %.6f   giou_loss: %4.2f   conf_loss: %4.2f   "
                    "prob_loss: %4.2f   total_loss: %4.2f"
                    % (
                        global_steps,
                        optimizer.lr.numpy(),
                        giou_loss,
                        conf_loss,
                        prob_loss,
                        total_loss,
                    )
                )
                # update learning rate
                global_steps.assign_add(1)
                if global_steps < warmup_steps:
                    lr = global_steps / warmup_steps * learning_rate_init
                else:
                    lr = learning_rate_end + 0.5 * (
                            learning_rate_init - learning_rate_end
                    ) * (
                             (
                                     1
                                     + tf.cos(
                                 (global_steps - warmup_steps)
                                 / (total_steps - warmup_steps)
                                 * np.pi
                             )
                             )
                         )
                optimizer.lr.assign(lr.numpy())

                # writing summary data
                writer.as_default()
                tf.summary.scalar("lr", optimizer.lr, step=global_steps)
                tf.summary.scalar(
                    "loss/total_loss", total_loss, step=global_steps
                )
                tf.summary.scalar(
                    "loss/giou_loss", giou_loss, step=global_steps
                )
                tf.summary.scalar(
                    "loss/conf_loss", conf_loss, step=global_steps
                )
                tf.summary.scalar(
                    "loss/prob_loss", prob_loss, step=global_steps
                )
                writer.flush()

        def test_step(image_data, target):
            with tf.GradientTape() as tape:
                pred_result = self.model(image_data, training=True)
                giou_loss = conf_loss = prob_loss = 0

                # optimizing process
                for i in range(3):
                    conv, pred = pred_result[i * 2], pred_result[i * 2 + 1]
                    loss_items = yolov4.compute_loss(
                        pred,
                        conv,
                        target[i][0],
                        target[i][1],
                        strides=self.strides,
                        num_class=self.num_class,
                        iou_loss_threshold=iou_loss_threshold,
                        i=i,
                    )
                    giou_loss += loss_items[0]
                    conf_loss += loss_items[1]
                    prob_loss += loss_items[2]

                total_loss = giou_loss + conf_loss + prob_loss

                tf.print(
                    "=> TEST STEP %4d   giou_loss: %4.2f   conf_loss: %4.2f   "
                    "prob_loss: %4.2f   total_loss: %4.2f"
                    % (
                        global_steps,
                        giou_loss,
                        conf_loss,
                        prob_loss,
                        total_loss,
                    )
                )

        for epoch in range(first_stage_epochs + second_stage_epochs):
            if epoch < first_stage_epochs:
                if not isfreeze:
                    isfreeze = True
                    for name in ["conv2d_93", "conv2d_101", "conv2d_109"]:
                        freeze = self.model.get_layer(name)
                        utils.freeze_all(freeze)
            elif epoch >= first_stage_epochs:
                if isfreeze:
                    isfreeze = False
                    for name in ["conv2d_93", "conv2d_101", "conv2d_109"]:
                        freeze = self.model.get_layer(name)
                        utils.unfreeze_all(freeze)
            for image_data, target in trainset:
                train_step(image_data, target)
            for image_data, target in testset:
                test_step(image_data, target)
            self.model.save_weights(trained_weights_path)

    def make_model(self, is_training=False):
        tf.keras.backend.clear_session()
        input_layer = tf.keras.layers.Input([self.height, self.width, 3])
        feature_maps = yolov4.YOLOv4(input_layer, self.num_class)

        bbox_tensors = []
        for i, fm in enumerate(feature_maps):
            if is_training:
                bbox_tensor = yolov4.decode_train(
                    fm,
                    self.num_class,
                    self.strides,
                    self.anchors,
                    i,
                    self.xyscale,
                )
                bbox_tensors.append(fm)

            else:
                bbox_tensor = yolov4.decode(fm, self.num_class, i)

            bbox_tensors.append(bbox_tensor)

        self.model = tf.keras.Model(input_layer, bbox_tensors)

    def load_weights(self, weights_path):
        if (
                weights_path.split(".")[len(weights_path.split(".")) - 1]
                == "weights"
        ):
            utils.load_weights(self.model, weights_path)
        else:
            self.model.load_weights(weights_path).expect_partial()

        self.model.summary()

    def predict(self, frame, classes):
        frame_size = frame.shape[:2]

        image_data = utils.image_preprocess(
            np.copy(frame), [self.height, self.width]
        )
        image_data = image_data[np.newaxis, ...].astype(np.float32)

        pred_bbox = self.model.predict(image_data)

        pred_bbox = utils.postprocess_bbbox(
            pred_bbox, self.anchors, self.strides, self.xyscale
        )
        bboxes = utils.postprocess_boxes(
            pred_bbox, frame_size, self.width, 0.25
        )
        bboxes = utils.nms(bboxes, 0.213, method="nms")

        return utils.draw_bbox(frame, bboxes, classes), [i for i in bboxes if int(i[5]) == 0]
