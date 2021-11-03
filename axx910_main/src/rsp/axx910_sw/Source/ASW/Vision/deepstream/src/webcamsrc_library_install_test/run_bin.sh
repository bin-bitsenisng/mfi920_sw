#!/usr/bin/env bash
set -e

width=800
height=600
fps=20
format=NV12

export GST_DEBUG=1 && \
webcamsrc_test \
    --nvinfer=config_yolov3_tiny.txt \
    --bbox=config_bbox.txt \
    --format=$format \
    -w $width \
    -h $height \
    --fps=$fps -v
