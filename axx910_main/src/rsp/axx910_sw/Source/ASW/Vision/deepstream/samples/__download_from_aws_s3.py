import os
import sys
import subprocess

try:
    import boto3
except ModuleNotFoundError:
    subprocess.run([sys.executable, "-m", "pip", "install", "boto3"])
    import boto3

blob = sys.argv[1]

s3 = boto3.client('s3')
print('download', 's3://btsml/'+blob)
s3.download_file('btsml', blob, blob.split('/')[-1])