#!/usr/bin/env bash

# ask to heron
aws_credentials_base64_decoded=$1
# https://s3.console.aws.amazon.com/s3/upload/btsml?region=ap-northeast-2
sdk=deepstream_sdk_v5.0.1_jetson.tbz2

mkdir ~/.aws
echo $aws_credentials_base64_decoded | base64 -d > ~/.aws/credentials

if [ ! -f $sdk ]; then
    sudo apt install -y python3-pip
    python3 -m pip install boto3

    python3 <<END
import boto3

blob="$sdk"

s3 = boto3.client('s3')
print('download', 's3://btsml/'+blob)
s3.download_file('btsml', blob, blob.split('/')[-1])
END
    sudo tar -xvf $sdk -C /
    pushd /opt/nvidia/deepstream/deepstream-5.0
    sudo ./install.sh
    sudo ldconfig
    popd
    cp -r /opt/nvidia/deepstream/deepstream-5.0 .
fi

cat <<END
./run_sample_yolov3.sh on GUI desktop.
END
