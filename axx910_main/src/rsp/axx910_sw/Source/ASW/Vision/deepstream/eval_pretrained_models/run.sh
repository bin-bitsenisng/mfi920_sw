#!/usr/bin/env bash
set -e

trap cleanup SIGINT SIGTERM ERR EXIT

cleanup() {
  trap - SIGINT SIGTERM ERR EXIT
  # script cleanup here
    echo "cleanup"
    echo "======="
    tegrastats --stop
    pkill -9 -ef cuda_fft
    pkill -9 -ef tegrastats
}


exp_name=$1
if [ -z $exp_name ]; then
    echo "no exp_name!"
    exit 1;
fi

	#../samples/models/MobileNetV2-YOLOv3-Lite-coco.weights \
	#../samples/models/MobileNetV2-YOLOv3-Nano-coco.weights \
	#../samples/models/yolov3-spp.weights \
	#../samples/models/yolov3-tiny-prn.weights \
	#../samples/models/yolov3-tiny.weights \
	#../samples/models/yolov3.weights \
	#../samples/models/yolov4-csp.weights \
	#../samples/models/yolov4-tiny.weights \
	#../samples/models/yolov4x-mish.weights \

	#../samples/models/yolov3-spp.weights \
for weight in \
	../samples/models/yolov4.weights \

	; do 

	#for _precision_tuple in 0,fp32 1,int8, 2,fp16; do IFS=","; set -- ${_precision_tuple}; 
	for _precision_tuple in 0,fp32 2,fp16; do IFS=","; set -- ${_precision_tuple}; 

        network_mode=$1
        network_mode_label=$2


			#klt,/opt/nvidia/deepstream/deepstream-5.0/lib/libnvds_mot_klt.so
        		#iou,/opt/nvidia/deepstream/deepstream-5.0/lib/libnvds_mot_iou.so \
        for _tracker_tuple in \
                        dcf,/opt/nvidia/deepstream/deepstream-5.0/lib/libnvds_nvdcf.so \
                        no_tracker,no_tracker \
                        ; do IFS=","; set -- ${_tracker_tuple};
            
            tracker_name=$1
            tracker_lib=$2

            for _device_tuple in \
                        gpu,0; do IFS=","; set -- ${_device_tuple};
            # for _device_tuple in \
            #             dla,1 \
            #             gpu,0; do IFS=","; set -- ${_device_tuple};

                device_name=$1
                dla_enable=$2

                input_file="data/front_10s.h264" 

                name=${weight##*/}
                name=${name/\.weights/}
                cfg=${weight/weights/cfg}
                weight=${weight}
                if [[ $device_name == "dla" ]]; then
                    engine=../samples/models/${name}_${network_mode}_${device_name}.engine
                else
                    engine=../samples/models/${name}_${network_mode}.engine
                fi

                output_file=result_video/${name}_${network_mode}_${device_name}_${tracker_name}_10s.mp4


                pri_config=${name}_${network_mode}_${device_name}_config_infer_primary.txt
                ds_config=${name}_${network_mode}_${device_name}_${tracker_name}_deepstream_app_config_no_videosink.txt


                sed "s?__WEIGHTS__?$weight?" config_infer_primary_yolo.txt > $pri_config
                sed -i "s?__CFG__?$cfg?" $pri_config
                sed -i "s?__ENGINE__?$engine?" $pri_config
                sed -i "s?__NETWORK_MODE__?$network_mode?" $pri_config
                sed -i "s?__ENABLE_DLA__?$dla_enable?" $pri_config
                sed -i "s?__USE_DLA_CORE__?$dla_enable?" $pri_config


                sed "s?__CONFIG_INFER_PRIMARY__?$pri_config?" deepstream_app_config_no_videosink.txt > $ds_config

                sed -i "s?__INPUT_FILE__?$input_file?" $ds_config
                sed -i "s?__OUTPUT_FILE__?$output_file?" $ds_config
                if [[ $tracker_name == "no_tracker" ]]; then
                    sed -i "s?__TRACKER_ENABLE__?0?" $ds_config
                else
                    sed -i "s?__TRACKER_ENABLE__?1?" $ds_config
                fi
                sed -i "s?__TRACKER_LIB__?$tracker_lib?" $ds_config


                set -x

		#radar_dsp_910/cuda_fft_910 > /dev/null 2>&1 & 
		radar_dsp/cuda_fft > /dev/null 2>&1 & 

                PID_CUDA_FFT=$(echo $!)

                perf=${name}_${network_mode}_${device_name}_${tracker_name}_perf
                gpu_usage=${name}_${network_mode}_${device_name}_${tracker_name}_gpu_usage

                tegrastats --start --logfile $gpu_usage
                deepstream-app -c $ds_config | grep PERF > $perf 
                tegrastats --stop
                kill -9 $PID_CUDA_FFT

                if [ -f model_b1_${device_name}0_${network_mode_label}.engine ]; then
                    mv model_b1_${device_name}0_${network_mode_label}.engine $engine
                fi
                set +x

                python3 gspread_append.py $exp_name $perf $gpu_usage http://192.168.0.217/data/$output_file 

                #break

            done
            #break

        done
        #break

	done
	#break

done
