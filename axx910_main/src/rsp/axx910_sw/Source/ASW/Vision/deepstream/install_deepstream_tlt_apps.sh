#!/usr/bin/env bash
# https://github.com/NVIDIA-AI-IOT/deepstream_tlt_apps

cd $HOME
if [ ! -d deepstream_tlt_apps ]; then
	git clone https://github.com/NVIDIA-AI-IOT/deepstream_tlt_apps.git
fi

cd deepstream_tlt_apps/
if [ ! -d models ]; then
	wget https://nvidia.box.com/shared/static/8k0zpe9gq837wsr0acoy4oh3fdf476gq.zip -O models.zip
	unzip models.zip
	rm models.zip
fi

if [ ! -f deepstream-custom ]; then
	if [ ! -d $HOME/deepstream-5.0 ]; then
		echo "can't find ~/deepstream-5.0. modify this script." && exit
	elif [ ! -d $HOME/TensorRT ]; then 
		echo "can't find ~/TensorRT. build TRT-OSS plugin first." && exit
	fi

	export DS_SRC_PATH="$HOME/deepstream-5.0"
	export CUDA_VER=10.2
	make
fi
set -x

