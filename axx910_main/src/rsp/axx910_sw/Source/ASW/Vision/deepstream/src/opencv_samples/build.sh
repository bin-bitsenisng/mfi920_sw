#!/usr/bin/env bash
set -x

#g++ -o bin/imshow imshow.cpp $(pkg-config --cflags --libs opencv4)
g++ -o bin/imshow_gst_raw_image imshow_gst_raw_image.cpp  \
    -L/usr/lib/aarch64-linux-gnu/ $(pkg-config --cflags --libs gstreamer-1.0 deepstream-5.0-tegra bts-deepstream-vision opencv4)
