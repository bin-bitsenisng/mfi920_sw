
APP:= webcamsrc_test
CC:= gcc

BTS_DS_VISION_INCLUDE_DIR?=/usr/local/include/bts_deepstream_vision/
BTS_DS_VISION_LIB_DIR?=/usr/local/lib/
BTS_DS_VISION_BIN_DIR?=/usr/local/bin/bts_deepstream_vision/

LIB_INSTALL_DIR?=/opt/nvidia/deepstream/deepstream-5.0/lib/

SRCS:= $(wildcard *.c)

INCS:=	callback_bus.h \
		callback_probe_sink_nvinfer.h \
		callback_sample_appsink.h \
		caps_webcamsrc.h \
		common.h \
		config_bbox.h \
		context_vision.h \
		context_vision_init.h \
		context_vision_monitor.h \
		context_vision_play.h \
		context_vision_unref.h \
		element_caps_filter.h \
		input_check.h \
		input_parse.h \
		vision.h

PKGS:= gstreamer-1.0 \
		deepstream-5.0-tegra
CXXPKGS:= $(PKGS) opencv4

OBJS:= $(SRCS:.c=.o) cv_copy_meta_to_context.o

CFLAGS:= `pkg-config --cflags $(PKGS)`
CXXFLAGS:= `pkg-config --cflags $(CXXPKGS)`

LIBS:= `pkg-config --libs $(PKGS)` 
CXXLIBS:= `pkg-config --libs $(CXXPKGS)` 

all: $(APP)

cv_copy_meta_to_context.o: cv_copy_meta_to_context.cc $(INCS) Makefile
	g++ -c -fPIC -o cv_copy_meta_to_context.o $(CXXFLAGS) $(CXXLIBS) $<

main.o: main.c $(INCS) cv_copy_meta_to_context.o Makefile
	g++ -c -o $@ $(CXXFLAGS) $(CXXLIBS) $< 

webcamsrc_test: $(OBJS) Makefile
	#$(CC) -o $(APP) $(OBJS) $(LIBS)
	g++ -o $(APP) $(OBJS) $(CXXLIBS)

install: $(APP) cv_copy_meta_to_context.o
	g++ -shared -fPIC -o libbtscvcopymeta2context.so cv_copy_meta_to_context.o $(CXXLIBS)
	mkdir -p $(BTS_DS_VISION_INCLUDE_DIR)/nvdsinfer_custom_impl_Yolo
	cp -rv *.h $(BTS_DS_VISION_INCLUDE_DIR)
	cp -rv *.so $(BTS_DS_VISION_LIB_DIR)
	cp -rv nvdsinfer_custom_impl_Yolo/*.h $(BTS_DS_VISION_INCLUDE_DIR)/nvdsinfer_custom_impl_Yolo
	cp -v nvdsinfer_custom_impl_Yolo/*.so $(BTS_DS_VISION_LIB_DIR)

	mkdir -p $(BTS_DS_VISION_INCLUDE_DIR)/nvdsinfer_custom_impl_Yolo4_marco
	cp -rv nvdsinfer_custom_impl_Yolo4_marco/*.h $(BTS_DS_VISION_INCLUDE_DIR)/nvdsinfer_custom_impl_Yolo4_marco
	cp -v nvdsinfer_custom_impl_Yolo4_marco/*.so $(BTS_DS_VISION_LIB_DIR)

	mkdir -p $(BTS_DS_VISION_BIN_DIR) 
	cp -rv $(APP) $(BTS_DS_VISION_BIN_DIR)


clean:
	rm -rf $(OBJS) $(APP)


