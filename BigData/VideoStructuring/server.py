import base64
import os
from importlib import import_module
import cv2
from flask import Flask, render_template, Response, jsonify

# from lib.camera_predict import Camera

if os.environ.get('CAMERA'):
    Camera = import_module('camera_' + os.environ['CAMERA']).Camera
else:
    from lib. camera_predict import Camera

import model.yolov4.tf as yolo
from argparse import ArgumentParser

parser = ArgumentParser()
parser.add_argument("-s", "--stream", dest="STREAM", default="http://172.17.0.1:8888/video_feed")
parser.add_argument("-n", "--names", dest="NAMES_PATH", default="E:\code\PycharmProjects\SmartCities\data\darknet\coco.names")
parser.add_argument("-w", "--weights", dest="WEIGHTS_PATH", default="E:\code\PycharmProjects\SmartCities\data\darknet\yolov4.weights")
# parser.add_argument("-n", "--names", dest="NAMES_PATH", default="./data/darknet/coco.names")
# parser.add_argument("-w", "--weights", dest="WEIGHTS_PATH", default="./data/darknet/yolov4.weights")

app = Flask(__name__)


@app.route('/')
def index():
    """Video streaming home page."""
    return render_template('index.html')


def gen(camera):
    """Video streaming generator function."""
    while True:
        frame = camera.get_frame()
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')


@app.route('/video_feed')
def video_feed():
    """Video streaming route. Put this in the src attribute of an img tag."""
    return Response(gen(Camera()),
                    mimetype='multipart/x-mixed-replace; boundary=frame')


@app.route('/box')
def get_box():
    return jsonify([base64.b64encode(cv2.imencode('.jpg', i)[1]).decode('utf-8') for i in Camera().person_list])


def init():
    args = parser.parse_args()
    Camera.video_source = args.STREAM
    Camera.detector = yolo.YoloV4(
        names_path=args.NAMES_PATH,
        weights_path=args.WEIGHTS_PATH,
    )


if __name__ == '__main__':
    init()
    app.run(host='0.0.0.0', port=5000, threaded=True)
