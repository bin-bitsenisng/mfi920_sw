#!/usr/bin/env bash
set -e

width=800
height=600
fps=20
format=RGBA
#format=NV12

export GST_DEBUG=1 && \
./imshow_gst_raw_image \
    --nvinfer=config_yolov4_tiny.txt \
    --bbox=config_bbox.txt \
    --format=$format \
    -w $width \
    -h $height \
    --fps=$fps #-v
