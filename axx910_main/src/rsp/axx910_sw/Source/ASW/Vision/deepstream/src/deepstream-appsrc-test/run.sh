#!/usr/bin/env bash

trap ctrl_c INT

function ctrl_c() {
        echo "** Trapped CTRL-C"
        mkdir -p pipeline_graph
        for dotfile in *.dot; do
                dot -Tpng ${dotfile} > ${dotfile}.png
                rm ${dotfile}
        done
}

#  gst-launch-1.0 uridecodebin uri=<URI of file> ! nvvideoconvert !
#      'video/x-raw, format=<Format of stream (example: I420, NV12, RGBA)>,
#      width=<Width of stream>, height=<height of stream>' ! filesink location=test.raw

width=1280
height=720
fps=30
format=RGBA


export GST_DEBUG_DUMP_DOT_DIR=$(pwd) && \
./deepstream_appsrc_test \
    raw.rgba \
    $width \
    $height \
    $fps \
    $format \
    dstest_appsrc_config.txt
