#!/bin/bash

export AWS_CONFIG="$(cat ~/.aws/config)"
export AWS_CREDENTIALS="$(cat ~/.aws/credentials)"

docker build . --build-arg AWS_CONFIG --build-arg AWS_CREDENTIALS -t 608157343330.dkr.ecr.ap-northeast-2.amazonaws.com/adam_bddtest:latest

unset AWS_CONFIG
unset AWS_CREDENTIALS
