#!/usr/bin/env bash

set -e
./install_prerequisite_packages.sh
./install_librdkafka.sh
./install_nvidia_v4l2_gstreamer_plugin.sh
./install_deepstream_sdk.sh
