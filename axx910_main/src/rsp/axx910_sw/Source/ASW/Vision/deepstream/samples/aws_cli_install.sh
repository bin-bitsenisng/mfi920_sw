#!/usr/bin/env bash

if ! [ -x "$(command -v curl)" ]; then
    sudo apt-get install curl -y
fi

curl "https://awscli.amazonaws.com/awscli-exe-linux-aarch64.zip" -o "awscliv2.zip"
unzip awscliv2.zip
sudo ./aws/install