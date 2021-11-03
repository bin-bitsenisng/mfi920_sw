#!/usr/bin/env bash

sudo apt update
sudo apt install deepstream-5.0
cp -r /opt/nvidia/deepstream/deepstream-5.0 ~/

cat <<END
./run_sample_yolov3.sh on GUI desktop.
END
