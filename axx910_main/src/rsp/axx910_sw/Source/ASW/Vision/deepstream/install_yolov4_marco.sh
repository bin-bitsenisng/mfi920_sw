#!/usr/bin/env bash

DS5=$1
DS5=${DS5:=/opt/nvidia/deepstream/deepstream-5.0}

set -e

if [ ! -d yolo_marco ]; then
    git clone https://github.com/marcoslucianops/DeepStream-Yolo.git yolo_marco
fi

sed -i 's/libnvdsinfer_custom_impl_Yolo.so/libnvdsinfer_custom_impl_Yolo4_marco.so/' yolo_marco/native/nvdsinfer_custom_impl_Yolo/Makefile

if [ -d $DS5/sources/yolo ]; then
    rm -rf $DS5/sources/yolo
fi
cp -r yolo_marco/native $DS5/sources/yolo

samples/download_yolov4.sh
cp -r samples/yolo_v4.* $DS5/sources/yolo/
cp -r samples/yolo_v4_tiny.* $DS5/sources/yolo/

pushd $DS5/sources/yolo/
CUDA_VER=10.2 make -C nvdsinfer_custom_impl_Yolo
popd

pushd src/webcamsrc
if [ ! -d nvdsinfer_custom_impl_Yolo4_marco ]; then
    ln -s $DS5/sources/yolo/nvdsinfer_custom_impl_Yolo nvdsinfer_custom_impl_Yolo4_marco
fi
popd

