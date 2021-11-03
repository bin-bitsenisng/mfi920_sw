#!/usr/bin/env bash

if [ ! -f opencv.zip ]; then
    wget -O opencv.zip https://github.com/Itseez/opencv/archive/3.4.5.zip
    unzip -d opencv opencv.zip
fi 
cd opencv/opencv-3.4.5
mkdir -p build
cd build

cmake -D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D WITH_TBB=OFF \
-D WITH_IPP=OFF \
-D WITH_1394=OFF \
-D BUILD_WITH_DEBUG_INFO=OFF \
-D BUILD_DOCS=OFF \
-D INSTALL_C_EXAMPLES=ON \
-D BUILD_EXAMPLES=ON \
-D BUILD_TESTS=OFF \
-D BUILD_PERF_TESTS=OFF \
-D WITH_QT=OFF \
-D WITH_GTK=ON \
-D WITH_OPENGL=OFF \
-D WITH_V4L=ON  \
-D WITH_FFMPEG=ON \
-D WITH_XINE=ON \
-D WITH_GSTREAMER=ON \
../

make -j 6
sudo -H make install