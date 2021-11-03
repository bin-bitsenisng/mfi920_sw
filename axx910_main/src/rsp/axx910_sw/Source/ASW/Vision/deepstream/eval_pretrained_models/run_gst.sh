
input_file=$1
output_file=$2
primary_config=$3

gst-launch-1.0 filesrc location=$input_file ! \
    h264parse ! nvv4l2decoder ! \
    m.sink_0 nvstreammux name=m batch-size=1 width=640 height=480 ! \
    nvvideoconvert ! "video/x-raw(memory:NVMM),format=RGBA,framerate=(fraction)30/1" ! \
    queue ! \
    nvinfer \
        config-file-path=yolov4_0_gpu_config_infer_primary.txt ! \
    queue ! \
    nvtracker \
        tracker-width=640 \
        tracker-height=384 \
        ll-lib-file=/opt/nvidia/deepstream/deepstream-5.0/lib/libnvds_nvdcf.so ! \
    nvdsosd ! \
    nvvideoconvert ! "video/x-raw(memory:NVMM),format=I420" ! \
    nvv4l2h264enc ! \
    h264parse ! \
    qtmux ! \
    filesink location=$output_file qos=1



    #x264enc ! \
    #mp4mux ! \
    #filesink location=tmp.mp4
    #'video/x-raw, format=RGBA' ! \