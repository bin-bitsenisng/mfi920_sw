#!/usr/bin/env bash

set -e

aws_credentials_base64_decoded="$1"
DS5=$2

if [[ ! $aws_credentials_base64_decoded ]]; then
    echo ""
    echo "Usage: $0 DECODED_CREDENTIAL_STRING" 
    echo ""
    echo "Ask aws credentials string to heron" 
    echo ""
    exit 1
fi
 
cd samples
./aws_s3_download_samples.sh $aws_credentials_base64_decoded

cd ../
./install_yolov4_marco.sh $DS5

cd src/webcamsrc
./install.sh $DS5

cd ../src/opencv_samples
./build.sh

echo "Run cd src/opencv_samples && ./run_gst_opencv_imshow.sh"
