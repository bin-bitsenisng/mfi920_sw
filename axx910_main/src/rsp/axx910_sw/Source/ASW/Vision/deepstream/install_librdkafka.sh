#!/usr/bin/env bash
set -e
if [ ! -d librdkafka ]; then
    git clone https://github.com/edenhill/librdkafka.git 
    pushd librdkafka

    set -x
    git reset --hard 7101c2310341ab3f4675fc565f64f0967e135a6a
    ./configure
    make
    sudo make install
    popd
fi 

sudo mkdir -p /opt/nvidia/deepstream/deepstream-5.0/lib
sudo cp /usr/local/lib/librdkafka* /opt/nvidia/deepstream/deepstream-5.0/lib