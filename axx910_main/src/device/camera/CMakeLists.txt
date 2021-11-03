# 요구 CMake 최소 버전
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
 
# 프로젝트 이름 및 버전
PROJECT("afi910_sw_ai_server")
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
FIND_PACKAGE(yolov5)
PKG_CHECK_MODULES(GLIB REQUIRED glib-2.0)

INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIR})

SET(SRC_FILES
	./camera.cpp
	../../inference/inference.cpp
	../../lane_detection/lane_detection/camera_calibration.cpp
	../../lane_detection/lane_detection/lane_detect.cpp
	../../lane_detection/lane_detection/lane_mapping.cpp
	../../lane_detection/lane_detection/preprocess.cpp
)


# 공통 컴파일러
SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_C_COMPILER "gcc")
 
# 공통 헤더 파일 Include 디렉토리 (-I)
INCLUDE_DIRECTORIES(include 
	../../inference
	../../lane_detection/lane_detection
    /usr/local/cuda-10.2/include
	${GLIB_INCLUDE_DIRS}
)
 
# 공통 컴파일 옵션, 링크 옵션
#ADD_COMPILE_OPTIONS(-g -fpermissive -fopenmp)
ADD_COMPILE_OPTIONS(-w)
#SET ( CMAKE_EXE_LINKER_FLAGS "-static -Wl,--gc-sections" )

# 전처리기
#ADD_DEFINITIONS()

# 공통 링크 라이브러리 (-l)
LINK_LIBRARIES(pthread zmq)
 
# 공통 링크 라이브러리 디렉토리 (-L)
LINK_DIRECTORIES(
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
 
# 빌드 대상 바이너리 추가
#ADD_EXECUTABLE( ${OUTPUT_ELF} ${SRC_FILES} )
#cuda_add_executable(${OUTPUT_ELF} ${SRC_FILES} ${CU_SRC_FILES})
add_executable( ${OUTPUT_ELF} ${SRC_FILES} )
target_link_libraries(${OUTPUT_ELF} ${OpenCV_LIBRARIES} ${GLIB_LDFLAGS} yolov5 nvinfer)
