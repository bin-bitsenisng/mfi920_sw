#!/bin/bash

for i in "$@"
do
case $i in
    --learning_rate=*)
    LEARNING_RATE=${i#*=}

    ;;
    --momentum=*)
    MOMENTUM=${i#*=}

    ;;
    --decay=*)
    DECAY=${i#*=}

    ;;
    *)

    ;;
esac
done

aws s3 cp s3://bts-ml-datasets/yolo-bdd100k/darknet.zip /darknet.zip
unzip /darknet.zip -d /

aws s3 cp s3://bts-ml-datasets/yolo-bdd100k/bdd100k_data.zip /darknet/data/bdd100k_data.zip
aws s3 cp s3://bts-ml-datasets/yolo-bdd100k/cfg_wts.zip /darknet/cfg_wts.zip
unzip /darknet/cfg_wts.zip -d /darknet
unzip /darknet/data/bdd100k_data.zip -d /darknet/data
mv /darknet/yolov4-tiny-bdd100k.cfg /darknet/cfg/
mv /darknet/yolov4-tiny.conv.29 /darknet/weights

aws s3 cp s3://bts-ml-datasets/yolo-bdd100k/train.zip /darknet/data/bdd100k/train.zip
aws s3 cp s3://bts-ml-datasets/yolo-bdd100k/val.zip /darknet/data/bdd100k/val.zip
unzip /darknet/data/bdd100k/train.zip -d /darknet/data/bdd100k
unzip /darknet/data/bdd100k/val.zip -d /darknet/data/bdd100k

aws s3 cp s3://bts-ml-datasets/yolo-bdd100k/py_scripts.zip /darknet/py_scripts.zip
unzip /darknet/py_scripts.zip -d /darknet

cd /darknet
make

python3 mod_args.py --learning_rate $LEARNING_RATE --momentum $MOMENTUM --decay $DECAY
python3 run_subp.py
