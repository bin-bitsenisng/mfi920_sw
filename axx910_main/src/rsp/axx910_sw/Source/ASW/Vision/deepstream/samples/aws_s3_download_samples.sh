#!/usr/bin/env bash

cwd=$(dirname $(readlink -f $0))

aws_credentials_base64_decoded="$1"

if [[ ! $aws_credentials_base64_decoded ]]; then
    echo ""
    echo "Usage: $0 DECODED_CREDENTIAL_STRING"
    echo ""
    echo "Ask aws credentials string to heron" 
    echo ""
    exit 1
fi

mkdir -p ~/.aws
echo $aws_credentials_base64_decoded | base64 -d > ~/.aws/credentials

# https://s3.console.aws.amazon.com/s3/upload/btsml?region=ap-northeast-2

if ! [ -x "$(command -v pip3)" ]; then
    sudo apt install -y python3-pip
fi

pushd $cwd

for blob in \
    "yolo_v3_tiny.weights" \
    "yolo_v3_tiny.cfg" \
    "yolo_v3_tiny.labels" \
    "detectnet_v2_resnet18.etlt" \
    "detectnet_v2_labels.txt"; 
do

    if [ ! -f $blob ]; then
        python3 __download_from_aws_s3.py $blob
    else
        echo "$blob already exists. skipped."
    fi

done

popd