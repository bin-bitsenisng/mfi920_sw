#!/usr/bin/env bash

set -xe

cwd=$(dirname $(readlink -f $0))

dstdir=$cwd/../samples/models/

cd $dstdir

wget https://raw.githubusercontent.com/AlexeyAB/darknet/master/cfg/yolov4x-mish.cfg
wget https://github.com/AlexeyAB/darknet/releases/download/darknet_yolo_v4_pre/yolov4x-mish.weights
wget https://raw.githubusercontent.com/AlexeyAB/darknet/master/cfg/yolov4-csp.cfg
wget https://github.com/AlexeyAB/darknet/releases/download/darknet_yolo_v4_pre/yolov4-csp.weights
wget https://raw.githubusercontent.com/AlexeyAB/darknet/master/cfg/yolov4.cfg
wget https://github.com/AlexeyAB/darknet/releases/download/darknet_yolo_v3_optimal/yolov4.weights
wget https://raw.githubusercontent.com/AlexeyAB/darknet/master/cfg/yolov4-tiny.cfg
wget https://github.com/AlexeyAB/darknet/releases/download/darknet_yolo_v4_pre/yolov4-tiny.weights
wget https://raw.githubusercontent.com/pjreddie/darknet/master/cfg/yolov3-spp.cfg
wget https://pjreddie.com/media/files/yolov3-spp.weights
wget https://raw.githubusercontent.com/pjreddie/darknet/master/cfg/yolov3.cfg
wget https://pjreddie.com/media/files/yolov3.weights
wget https://raw.githubusercontent.com/WongKinYiu/PartialResidualNetworks/master/cfg/yolov3-tiny-prn.cfg
wget https://github.com/WongKinYiu/PartialResidualNetworks/raw/master/model/yolov3-tiny-prn.weights
wget https://raw.githubusercontent.com/pjreddie/darknet/master/cfg/yolov3-tiny.cfg
wget https://pjreddie.com/media/files/yolov3-tiny.weights
wget https://raw.githubusercontent.com/dog-qiuqiu/MobileNet-Yolo/master/MobileNetV2-YOLOv3-Lite/COCO/MobileNetV2-YOLOv3-Lite-coco.cfg
wget https://github.com/dog-qiuqiu/MobileNet-Yolo/raw/master/MobileNetV2-YOLOv3-Lite/COCO/MobileNetV2-YOLOv3-Lite-coco.weights
wget https://raw.githubusercontent.com/dog-qiuqiu/MobileNet-Yolo/master/MobileNetV2-YOLOv3-Nano/COCO/MobileNetV2-YOLOv3-Nano-coco.cfg
wget https://github.com/dog-qiuqiu/MobileNet-Yolo/raw/master/MobileNetV2-YOLOv3-Nano/COCO/MobileNetV2-YOLOv3-Nano-coco.weights
wget https://raw.githubusercontent.com/dog-qiuqiu/Yolo-Fastest/master/Yolo-Fastest/COCO/yolo-fastest.cfg
wget https://github.com/dog-qiuqiu/Yolo-Fastest/raw/master/Yolo-Fastest/COCO/yolo-fastest.weights
wget https://raw.githubusercontent.com/dog-qiuqiu/Yolo-Fastest/master/Yolo-Fastest/COCO/yolo-fastest-xl.cfg
wget https://github.com/dog-qiuqiu/Yolo-Fastest/raw/master/Yolo-Fastest/COCO/yolo-fastest-xl.weights
wget https://raw.githubusercontent.com/pjreddie/darknet/master/cfg/yolov2.cfg
wget https://pjreddie.com/media/files/yolov2.weights
wget https://raw.githubusercontent.com/pjreddie/darknet/master/cfg/yolov2-tiny.cfg
wget https://pjreddie.com/media/files/yolov2-tiny.weights


git clone https://github.com/NVIDIA-AI-IOT/deepstream_tlt_apps
cd deepstream_tlt_apps
wget https://nvidia.box.com/shared/static/8k0zpe9gq837wsr0acoy4oh3fdf476gq.zip -O models.zip
unzip models.zip
rm models.zip
