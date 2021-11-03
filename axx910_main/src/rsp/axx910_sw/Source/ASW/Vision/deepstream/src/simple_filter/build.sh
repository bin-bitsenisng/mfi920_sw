#!/usr/bin/env bash

gcc \
    simple_filter.c \
    $(pkg-config --cflags --libs gstreamer-1.0) \
    -o simple_filter
