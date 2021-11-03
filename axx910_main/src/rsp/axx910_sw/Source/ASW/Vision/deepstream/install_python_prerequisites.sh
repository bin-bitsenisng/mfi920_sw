#!/usr/bin/env bash

# https://github.com/NVIDIA-AI-IOT/deepstream_python_apps/blob/master/HOWTO.md

sudo apt-get install python-gi-dev
export GST_LIBS="-lgstreamer-1.0 -lgobject-2.0 -lglib-2.0"
export GST_CFLAGS="-pthread -I/usr/include/gstreamer-1.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include"
git clone https://github.com/GStreamer/gst-python.git
cd gst-python
git checkout 1a8f48a
./autogen.sh PYTHON=python3
./configure PYTHON=python3          # sometimes error occurs. retry manually. from ./autogen.sh
make
sudo make install