#!/usr/bin/env bash

set -e

DS5=$1
DS5=${DS5:=/opt/nvidia/deepstream/deepstream-5.0}

sudo cp *.pc /usr/local/lib/pkgconfig
ln -s $DS5/sources/objectDetector_Yolo/nvdsinfer_custom_impl_Yolo
ln -s $DS5/sources/yolo/nvdsinfer_custom_impl_Yolo4_marco
make
sudo make install