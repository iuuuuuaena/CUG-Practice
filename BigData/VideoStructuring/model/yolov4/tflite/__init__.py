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
import numpy as np
import cv2
import tflite_runtime.interpreter as tflite

from ..core import utils


class YoloV4:
    def __init__(self, names_path, tflite_path):
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

        self.classes = utils.read_class_names(names_path)

        self.load_tflite(tflite_path)

        self.width = self.height = self.input_shape[1]

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

    def train(self):
        pass

    def load_tflite(self, tflite_path):
        self.interpreter = tflite.Interpreter(model_path=tflite_path)
        self.interpreter.allocate_tensors()
        input_details = self.interpreter.get_input_details()
        self.input_shape = input_details[0]["shape"]
        self.input_index = input_details[0]["index"]
        self.output_details = self.interpreter.get_output_details()

    def predict(self, frame, classes):
        frame_size = frame.shape[:2]

        image_data = utils.image_preprocess(
            np.copy(frame), [self.height, self.width]
        )
        image_data = image_data[np.newaxis, ...].astype(np.float32)

        self.interpreter.set_tensor(self.input_index, image_data)
        self.interpreter.invoke()

        pred_bbox = utils.postprocess_bbbox(
            [
                self.interpreter.get_tensor(self.output_details[i]["index"])
                for i in range(len(self.output_details))
            ],
            self.anchors,
            self.strides,
            self.xyscale,
        )
        bboxes = utils.postprocess_boxes(
            pred_bbox, frame_size, self.width, 0.25
        )
        bboxes = utils.nms(bboxes, 0.213, method="nms")

        return utils.draw_bbox(frame, bboxes, classes)
