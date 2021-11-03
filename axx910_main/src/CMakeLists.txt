# 요구 CMake 최소 버전
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# 프로젝트 이름 및 버전
PROJECT("afi910_sw")
SET(PROJECT_VERSION_MAJOR 1)
SET(PROJECT_VERSION_MINOR 0)

# 빌드 형상(Configuration) 및 Makefile 생성 여부
#SET(CMAKE_BUILD_TYPE builds)
SET(CMAKE_VERBOSE_MAKEFILE false)

# 빌드 대상 바이너리 파일명 및 소스 파일 목록
SET(OUTPUT_ELF
	"${CMAKE_PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
)

set(CMAKE_PREFIX_PATH
    ${CMAKE_PREFIX_PATH}
    /usr/share/cmake-3.10/Modules/)

FIND_PACKAGE(PkgConfig)
FIND_PACKAGE(CUDA REQUIRED)
SET(OpenCV_DIR [OpenCV.cmake PATH])
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(Boost REQUIRED)
FIND_PACKAGE(yolov5)

INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

SET(SRC_FILES
	./main.cpp
	./main_argument.cpp
	./common/bts_log.c
	./common/bts.c
	./common/krs_macro.c
	./daq/reshape.cu
	./daq/dmdriver-src/driver/examples/adar690x_DCCMRAM_bin.cpp
	./daq/dmdriver-src/driver/examples/adar690x_ICCMRAM_bin.cpp
	./daq/dmdriver-src/driver/examples/example_burst_loop.cpp
	./daq/dmdriver-src/driver/examples/example_init.cpp
	./daq/dmdriver-src/driver/examples/example_tasklist.cpp
	./daq/dmdriver-src/driver/examples/example_syscal.cpp
	./daq/dmdriver-src/driver/examples/example_dma_ramp.cpp
	./daq/dmdriver-src/driver/examples/dummy_hal.cpp
	./daq/dmdriver-src/driver/examples/dummy_platform.cpp
	./daq/dmdriver-src/driver/examples/tasklist_util.cpp
	./daq/dmdriver-src/driver/examples/host_dev.cu
	./daq/dmdriver-src/driver/examples/jetsonGPIO.cpp
	./daq/dmdriver-src/driver/examples/bts_afi910.cpp
	./daq/dmdriver-src/driver/examples/bts_afi910_init.cpp
	./daq/dmdriver-src/driver/examples/bts_afi910_burst_loop.cpp
	./daq/dmdriver-src/driver/examples/bts_afi910_rfic_dma.cpp
	./daq/dmdriver-src/driver/examples/../src/pmic_adar690x.cpp
	./daq/dmdriver-src/driver/examples/../src/pmic_driver.cpp
	./daq/dmdriver-src/driver/examples/../src/pmic_rw.cpp
	./device/device_ctrl.cpp
	#./device/camera/camera.cpp
	./device/radar/radar.cpp
	./device/imu/imu.c
	./device/gps/gps.c
	./device/can_drv/can_sig.c
	./filesystem/linux/linux_fs.c
	./filesystem/linux/linux_fs_app.c
	./generated/sys_param_jsontype_dump.c
	./generated/sys_param_jsontype_info.c
	./generated/sys_param_jsontype_load.c
	./inference/inference.cpp
	./lane_detection/lane_detection/lane_detect.cpp
	./lib/bts_queue.c
	./lib/krs_base64.c
	./lib/krs_fifo.c
	./lib/linked_queue.c
	./lib/frozen/frozen.c
	./lib/json/jsmn.c
	./lib/json/jWrite.c
	./lib/json/cJSON.c
	./logging/hdf5_ctrl.cpp
	./net/network.c
	./net/app/app.c
	./net/app/bts_comm/bts_comm_appl.c
	./net/app/bts_comm/bts_comm_applcmd_callback.c
	./net/app/bts_comm/bts_comm_applcmd.c
	./net/app/bts_comm/bts_comm_callback.c
	./net/app/bts_comm/bts_comm_packet.c
	./net/app/bts_comm/bts_comm_service.c
	./net/app/bts_comm/bts_comm_status.c
	./net/app/bts_comm/bts_comm.c
	./net/app/bts_comm/bts_comm_appl/bts_comm_appl_ai_object.c
	./net/app/bts_comm/bts_comm_appl/bts_comm_appl_canlog.c
	./net/app/bts_comm/bts_comm_appl/bts_comm_appl_common.c
	./net/app/bts_comm/bts_comm_appl/bts_comm_appl_dataset.c
	./net/app/bts_comm/bts_comm_appl/bts_comm_appl_fcw.c
	./net/app/bts_comm/bts_comm_appl/bts_comm_appl_flog.c
	./net/app/bts_comm/bts_comm_appl/bts_comm_appl_freespace.c
	./net/app/bts_comm/bts_comm_appl/bts_comm_appl_image.c
	./net/app/bts_comm/bts_comm_appl/bts_comm_appl_its.c
	./net/app/bts_comm/bts_comm_appl/bts_comm_appl_lane_detection.c
	./net/app/bts_comm/bts_comm_appl/bts_comm_appl_object.c
	./net/app/bts_comm/bts_comm_appl/bts_comm_appl_raw.c
	./net/app/bts_comm/bts_comm_appl/bts_comm_appl_rs485.c
	./net/app/bts_comm/bts_comm_appl/bts_comm_appl_status.c
	./net/app/bts_comm/bts_comm_appl/bts_comm_appl_track.c
	./net/app/bts_comm/bts_comm_appl/bts_comm_appl_vf.c
	./net/if/if.c
	./net/if/eth/eth.c
	./net/if/eth/eth_linuxsock.c
	./net/if/can/can.c
	./os/os.c
	./rsp/rsp_main.cpp
	./rsp/axx910_sw/Source/ASW/SignalProcessing/Sp_Main.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/template.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/Application/App_Input.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/Application/App_Main.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/lib/rsp_lib.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/lib/cfarlib/bts_cfarlib.c
	#./rsp/axx910_sw/Source/ASW/SignalProcessing/ObjectDetection/Obj_AngEst.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/ObjectDetection/Obj_AngEst.cu
	./rsp/axx910_sw/Source/ASW/SignalProcessing/ObjectDetection/Obj_CalRV.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/ObjectDetection/Obj_CFAR.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/ObjectDetection/Obj_DBF.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/ObjectDetection/Obj_FreqEst.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/ObjectDetection/Obj_Main.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/ObjectDetection/Obj_Output.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/ObjectDetection/Obj_SelCand.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/ObjectDetection/GhostFilter/Gf_FoVFilter.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/ObjectDetection/GhostFilter/Gf_Main.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/ObjectDetection/GhostFilter/Gf_RefPairFilter.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/PreProcessing/Pre_fft.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/PreProcessing/Pre_Main.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/Tracking/Trk_Association.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/Tracking/Trk_Correction.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/Tracking/Trk_Freespace.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/Tracking/Trk_Input.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/Tracking/Trk_Main.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/Tracking/Trk_Managing.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/Tracking/Trk_Output.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/Tracking/Trk_Prediction.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/Tracking/Trk_Clustering.c
	./rsp/axx910_sw/Source/ASW/SignalProcessing/Tracking/Trk_SensorFusion.c
	./sys/system.c
	./sys/sys_param/sys_param_jsontype_bts24mx.c
	./sys/sys_param/sys_param_jsontype.c
	./sys/sys_param/sys_param.c
	./thread/cam_thread.cpp
	./thread/daq_thread.cpp
	./thread/inf_thread.cpp
	./thread/net_thread.cpp
	./thread/rsp_thread.cpp
	./thread/can_thread.cpp
	./thread/trk_thread.cpp
	./thread/thread_manager.cpp
	./time/timestamp.cpp
)

FILE(GLOB CU_FILES ./rsp/axx910_sw/Source/ASW/Acceleration/*.cu)

SET(CU_SRC_FILES
	${CU_FILES}
)

# 공통 컴파일러
SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_C_COMPILER "gcc")

# 공통 헤더 파일 Include 디렉토리 (-I)
INCLUDE_DIRECTORIES(include
	.
	./common
	./daq
	./daq/dmdriver-src/driver/examples
	./daq/dmdriver-src/driver/include
	./device
	./device/camera
	./device/radar
	./device/imu
	./device/gps
	./device/can_drv
	./filesystem/linux
	./generated
	./inference
	./lane_detection/lane_detection
	./lib
	./lib/frozen
	./lib/json
	#./lib/simclist
	./logging
	./logging/HDF5_Lib/include
	./logging/mini
	./net
	./net/app
	./net/app/bts_comm
	./net/app/bts_comm/bts_comm_appl
	./net/if
	./net/if/eth
	./net/if/eth/bsdsocket
	./net/if/can
	./os
	./rsp
	./rsp/axx910_sw/Source/ASW/Acceleration
	./rsp/axx910_sw/Source/ASW/Cfg
	./rsp/axx910_sw/Source/ASW/SignalProcessing
	./rsp/axx910_sw/Source/ASW/SignalProcessing/Application
	./rsp/axx910_sw/Source/ASW/SignalProcessing/lib
	./rsp/axx910_sw/Source/ASW/SignalProcessing/lib/cfarlib
	./rsp/axx910_sw/Source/ASW/SignalProcessing/lib/NE10/common
	./rsp/axx910_sw/Source/ASW/SignalProcessing/lib/NE10/dsp
	./rsp/axx910_sw/Source/ASW/SignalProcessing/lib/NE10/inc
	./rsp/axx910_sw/Source/ASW/SignalProcessing/ObjectDetection
	./rsp/axx910_sw/Source/ASW/SignalProcessing/ObjectDetection/GhostFilter
	./rsp/axx910_sw/Source/ASW/SignalProcessing/PreProcessing
	./rsp/axx910_sw/Source/ASW/SignalProcessing/Tracking
	./sys
	./sys/sys_config
	./sys/sys_param
	./sys/sys_param/sys_param_bts24mx
	./thread
	./time
	/usr/local/cuda-10.2/include
	#/usr/local/include/bts_deepstream_vision
)

# 공통 컴파일 옵션, 링크 옵션
ADD_COMPILE_OPTIONS(-g -w -fpermissive -fopenmp)
#SET ( CMAKE_EXE_LINKER_FLAGS "-static -Wl,--gc-sections" )

# 전처리기
ADD_DEFINITIONS(-DCUDA_ACC -DCUDA_ACC_ANGLE_EST -DARM64 -DLINUX -D_CONSOLE -D_LIB -DH5_BUILT_AS_DYNAMIC_LIB -DHAS_BOOST)

# 공통 링크 라이브러리 (-l)
LINK_LIBRARIES(hdf5 z dl pthread NE10 cufft cudart cublas driver m rt zmq)

# 공통 링크 라이브러리 디렉토리 (-L)
LINK_DIRECTORIES(
	./logging/HDF5_Lib/lib
	./rsp/axx910_sw/Source/ASW/SignalProcessing/lib/NE10/lib
	./daq/dmdriver-src/driver/Debug
	/usr/lib/aarch64-linux-gnu/
	/usr/local/cuda-10.2/lib64
)

# "Debug" 형상 한정 컴파일 옵션, 링크 옵션
#SET ( CMAKE_C_FLAGS_DEBUG "-DDEBUG -DC_FLAGS" )
#SET ( CMAKE_EXE_LINKER_FLAGS_DEBUG "-DDEBUG -DLINKER_FLAGS" )

# "Release" 형상 한정 컴파일 옵션, 링크 옵션
#SET ( CMAKE_C_FLAGS_RELEASE "-DRELEASE -DC_FLAGS" )
#SET ( CMAKE_EXE_LINKER_FLAGS_RELEASE "-DRELEASE -DLINKER_FLAGS" )

# 출력 디렉토리
SET ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE} )
SET ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE}/lib )
SET ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE}/lib )

# 빌드 대상 바이너리 추가
#ADD_EXECUTABLE( ${OUTPUT_ELF} ${SRC_FILES} )
cuda_add_executable(${OUTPUT_ELF} ${SRC_FILES} ${CU_SRC_FILES})
target_link_libraries(${OUTPUT_ELF} ${OpenCV_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY} yolov5 nvinfer)
