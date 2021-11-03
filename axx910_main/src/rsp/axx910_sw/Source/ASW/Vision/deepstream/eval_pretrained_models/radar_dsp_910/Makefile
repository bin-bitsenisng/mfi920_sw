CXX             = nvcc
CFLAGS			= -O2 
LIB_DIR			= /usr/local/cuda/lib64
INC_DIR			= /usr/local/cuda/include
SRCS            = ./cuda_fft_910.cu

OBJS            = *.o
TARGET          = cuda_fft_910
LIB_DIRS        = -L$(LIB_DIR)
LIB				= -lcufft -lcudart -lcuda -lcublas
INC_DIRS		= -I$(INC_DIR)


all : $(TARGET)
	$(CXX) -o $(TARGET) $(OBJS) $(LIB_DIRS) $(LIB) 
 
$(TARGET) : $(SRCS)
	$(CXX) $(CFLAGS) -c $(SRCS) $(INC_DIRS) 

clean :
		rm -f $(TARGET)
		rm -f *.o

