#!/usr/bin/env bash

set -e
cwd=$(dirname $(readlink -f $0))
cd $cwd

if [ ! -f yolo_v4.weights ] && [ ! -f yolov4.weights ]; then
    wget https://raw.githubusercontent.com/AlexeyAB/darknet/master/cfg/yolov4.cfg
    wget https://github.com/AlexeyAB/darknet/releases/download/darknet_yolo_v3_optimal/yolov4.weights
    mv yolov4.cfg yolo_v4.cfg
    mv yolov4.weights yolo_v4.weights
fi

if [ ! -f yolo_v4_tiny.weights ] && [ ! -f yolov4-tiny.weights ]; then
    wget https://raw.githubusercontent.com/AlexeyAB/darknet/master/cfg/yolov4-tiny.cfg
    wget https://github.com/AlexeyAB/darknet/releases/download/darknet_yolo_v4_pre/yolov4-tiny.weights
    mv yolov4-tiny.cfg yolo_v4_tiny.cfg
    mv yolov4-tiny.weights yolo_v4_tiny.weights
fi
