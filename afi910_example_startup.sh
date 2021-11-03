#!/bin/bash

jetson_clocks
/opt/bitsensing/load_rfic.sh
/opt/bitsensing/load_arducam.sh
/opt/bitsensing/load_can.sh
/opt/bitsensing/set_spi.sh

if [ ! -d /mnt/ssd ] ; then
 mkdir -p /mnt/ssd
fi
mount /dev/nvme0n1p1 /mnt/ssd
