#!/usr/bin/env bash


set -e
trap ctrl_c INT

function ctrl_c() {
        echo "** Trapped CTRL-C"
        mkdir -p pipeline_graph
        # for dotfile in *.dot; do
        #         dot -Tpng ${dotfile} > ${dotfile}.png
        #         rm ${dotfile}
        # done
}

#  gst-launch-1.0 uridecodebin uri=<URI of file> ! nvvideoconvert !
#      'video/x-raw, format=<Format of stream (example: I420, NV12, RGBA)>,
#      width=<Width of stream>, height=<height of stream>' ! filesink location=test.raw

width=960
height=544
fps=20
format=RGBA

# export GST_DEBUG_DUMP_DOT_DIR=$(pwd) && \
export GST_DEBUG=1 && \
./webcamsrc_test \
    --nvinfer=config_detectnet_v2_tlt.txt \
    --bbox=config_bbox.txt \
    --format=$format \
    -w $width \
    -h $height \
    --fps=$fps -v
