pushd ~/deepstream-5.0/sources/objectDetector_Yolo
./prebuild.sh
export CUDA_VER=10.2
make -C nvdsinfer_custom_impl_Yolo
deepstream-app -c deepstream_app_config_yoloV3_tiny.txt
