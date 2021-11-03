#!/usr/bin/env bash

trap ctrl_c INT

function ctrl_c() {
	echo "** Trapped CTRL-C"
	mkdir -p pipeline_graph
	for dotfile in *.dot; do
		dot -Tpng ${dotfile} > ${dotfile}.png
		rm ${dotfile}
	done
}

export GST_DEBUG_DUMP_DOT_DIR=$(pwd) && \
    gst-launch-1.0 -v videotestsrc ! autovideosink
