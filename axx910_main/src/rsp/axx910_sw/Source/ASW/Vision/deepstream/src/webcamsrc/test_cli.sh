#!/usr/bin/env bash

# gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,framerate=30/1,width=1280,height=720 ! xvimagesink    # not work
# gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,framerate=10/1,width=1280,height=720 ! xvimagesink    # work
# gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,framerate=30/1                       ! xvimagesink    # work (available, auto-sized)
# gst-launch-1.0 autovideosrc               ! video/x-raw,framerate=30/1                       ! xvimagesink    # work (available, auto-sized)
# gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,framerate=10/1,width=1280,height=720 ! autovideosink  # not work
# gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,framerate=10/1,width=1280,height=720 ! nveglglessink  # not work

# GST_DEBUG=5: too many info
GST_DEBUG=4 && \
gst-launch-1.0 \
    v4l2src device=/dev/video0 ! \
    video/x-raw,framerate=10/1,width=1280,height=720 ! \
    xvimagesink
