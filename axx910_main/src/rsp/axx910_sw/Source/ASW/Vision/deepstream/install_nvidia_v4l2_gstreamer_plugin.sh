#!/usr/bin/env bash
set -e
sudo cp \
    nvidia-l4t-apt-source-for-xavier-nx.list \
    /etc/apt/sources.list.d/nvidia-l4t-apt-source.list

sudo apt update -y
sudo apt install -y --reinstall nvidia-l4t-gstreamer