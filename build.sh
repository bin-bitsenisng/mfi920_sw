#!/bin/bash

SHELL_PATH=`pwd -P`

cd ${SHELL_PATH}/axx910_main/src
if [ ! -d build ] ; then
    mkdir build
fi
cd build
cmake ..
make -j 6

if [ $? -eq 0 ] ; then
  echo ""	
else
  echo -e "\033[31;1m"Build Fail."\033[0m"
  exit
fi

cd ${SHELL_PATH}/axx910_main/src/device/camera
if [ ! -d build ] ; then
    mkdir build
fi
cd build
cmake ..
make -j 6

if [ $? -eq 0 ] ; then
  echo -e "\033[32;1m"Build Success."\033[0m"
else
  echo -e "\033[31;1m"Build Fail."\033[0m"
fi
