#!/usr/bin/env bash

#  gst-launch-1.0 uridecodebin uri=<URI of file> ! nvvideoconvert !
#      'video/x-raw, format=<Format of stream (example: I420, NV12, RGBA)>,
#      width=<Width of stream>, height=<height of stream>' ! filesink location=test.raw

gst-launch-1.0 uridecodebin \
    uri=file:///opt/nvidia/deepstream/deepstream-5.0/samples/streams/sample_720p.mp4 \
    ! nvvideoconvert \
    ! 'video/x-raw, format=RGBA, width=1280, height=720' \
    ! filesink location=raw.rgba 
    # I420, NV12의 경우 build demo에서 화면이 재생되다가 멈추는 버그가 있다.
    #! autovideosink
    #! filesink location=test.i420
