#!/bin/bash
killbg() {
        for p in "${pids[@]}" ; do
                kill "$p";
        done
}
trap killbg EXIT

help() {
        echo "AI & CAM [OPTIONS]"
        echo "    -h    help."
        echo "    -c    AI confidence threshold (0.0 ~ 1.0. Default is 0.5)"
        echo "    -n    AI nms threshold (0.0 ~ 1.0. Default is 0.4)"
        echo "    -r    camera resolution (4K, QHD, FHD, 720P, VGA. Default is VGA)"
        exit 0
}
while getopts "c:n:r:h" opt
do
    case $opt in
        c) confidence_threshold=$OPTARG
          echo "confidence threshold: $confidence_threshold"
          ;;
        n) nms_threshold=$OPTARG
          echo "nms threshold: $nms_threshold"
          ;;
        r) cam_resolution=$OPTARG
        echo "camera resolution: $cam_resolution"
        ;;
        h) help ;;
        ?) help ;;
    esac
done

if [ -z "$confidence_threshold" ]
then
        confidence_threshold="0.25"
fi
if [ -z "$nms_threshold" ]
then
        nms_threshold="0.6"
fi
if [ -z "$cam_resolution" ]
then
        cam_resolution="720P"
fi

systemctl restart nvargus-daemon
pids=()
cd axx910_main/src/device/camera/build
nohup ./afi910_sw_ai_server-1.0 -c $confidence_threshold -n $nms_threshold -r $cam_resolution &
pids+=($!)
cd ../../../build
./afi910_sw-1.0 -h 0 -d 0 -m rt_mode
