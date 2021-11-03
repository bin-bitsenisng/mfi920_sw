trap ctrl_c INT

function ctrl_c() {
	echo "** Trapped CTRL-C"
	for dotfile in *-ds-app-{null,ready,playing}.dot; do
		dot -Tpng ${dotfile} > ${dotfile}.png
		rm ${dotfile}
	done
}

export ds_local_src=/home/heron/deepstream-5.0/sources && make 
export GST_DEBUG_DUMP_DOT_DIR=$(pwd) && \
	bin/deepstream-app deepstream_app_config_yoloV3_tiny.txt
	#./deepstream-app -c deepstream_app_config_yoloV3_tiny.txt

