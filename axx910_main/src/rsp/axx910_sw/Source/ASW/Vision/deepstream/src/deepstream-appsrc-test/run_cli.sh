#!/usr/bin/env bash

gst-launch-1.0 -v \
	filesrc location=/home/heron/deepstream-5.0/samples/streams/sample_720p.h264 \
	! h264parse \
	! nvv4l2decoder \
	! nvvideoconvert \
	! autovideosink

	# not work. for testing
	#! h264parse \
	#! nvv4l2decoder \
	#! nvinfer config-file-path=dstest_appsrc_config.txt \
	#! nvvideoconvert \
	#! nvdsosd \
	#! autovideosink
