#!/usr/bin/env bash
# https://github.com/NVIDIA-AI-IOT/deepstream_tlt_apps/tree/master/TRT-OSS/Jetson/TRT7.1

set -e


if [ ! -f ~/.aws/credentials ]; then
	echo "prepare ~/.aws/credential first. ask to heron" && exit
fi


cmake_ver=$(cmake --version | head -1 | awk '{print $3}' | awk -F. '{print $2}') 
if [ ! $cmake_ver -ge 13 ]; then
	echo "Your cmake version is $cmake_ver."
	echo "Required cmake version is higher or equal than 3.13."
	while true; do
	    read -p "cmake installation takes time. will you proceed? [y/n]"
	    case $yn in
		[Yy]* ) break;;
		[Nn]* ) exit;;
		* ) echo "Please answer y or n.";;
	    esac
	done

	sudo apt-get install libssl-dev -y

	wget https://github.com/Kitware/CMake/releases/download/v3.13.5/cmake-3.13.5.tar.gz
	tar xvf cmake-3.13.5.tar.gz
	cd cmake-3.13.5/
	./configure
	make -j$(nproc)
	sudo make install
	sudo ln -s /usr/local/bin/cmake /usr/bin/cmake
fi


cd ~/

# Download TensorRT OSS sources
if [ ! -d TensorRT ]; then
	git clone https://github.com/nvidia/TensorRT TensorRT -b release/7.1
fi

# Download the TensorRT binary release
cd TensorRT

git submodule update --init --recursive
export TRT_SOURCE=`pwd`
cd $TRT_SOURCE

mkdir -p build && cd build
/usr/local/bin/cmake .. -DGPU_ARCHS="53 62 72" -DTRT_LIB_DIR=/usr/lib/aarch64-linux-gnu/ -DCMAKE_C_COMPILER=/usr/bin/gcc -DTRT_OUT_DIR=`pwd`/out
make nvinfer_plugin -j$(nproc)

if [ ! -f out/libnvinfer_plugin.so.7.1.3 ]; then
	echo "This script is for libnvinfer_plugin.so.7.1.3" && exit
fi

sudo mv /usr/lib/aarch64-linux-gnu/libnvinfer_plugin.so.7.?.? ${HOME}/  ## backup original libnvinfer_plugin
sudo cp out/libnvinfer_plugin.so.7.1.3  /usr/lib/aarch64-linux-gnu/
pushd /usr/lib/aarch64-linux-gnu/
sudo rm -f libnvinfer_plugin.so.7 libnvinfer_plugin.so
sudo ln -s libnvinfer_plugin.so.7.1.3 libnvinfer_plugin.so.7
sudo ln -s libnvinfer_plugin.so.7.1.3 libnvinfer_plugin.so
sudo ldconfig

popd
make -j$(nproc)
sudo make install

