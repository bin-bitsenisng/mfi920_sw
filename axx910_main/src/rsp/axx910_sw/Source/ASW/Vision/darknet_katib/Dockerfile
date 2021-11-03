FROM nvcr.io/nvidia/cuda:10.1-cudnn7-devel-ubuntu18.04

RUN apt-get update
RUN apt-get install -y unzip curl
RUN apt-get install -y python3-pip
RUN pip3 install -U awscli

WORKDIR /
COPY install.sh /
RUN ./install.sh

WORKDIR /
COPY run.sh /

ARG AWS_CONFIG
ARG AWS_CREDENTIALS
RUN mkdir ~/.aws
RUN printf "%s" "${AWS_CONFIG}" >> ~/.aws/config
RUN printf "%s" "${AWS_CREDENTIALS}" >> ~/.aws/credentials

ENTRYPOINT ["./run.sh"]
