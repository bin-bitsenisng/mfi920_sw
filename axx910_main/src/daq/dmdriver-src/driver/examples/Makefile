TOP?=.

TARGET=example

CFILES= \
	adar690x_DCCMRAM_bin.cpp \
	adar690x_ICCMRAM_bin.cpp \
	example_burst_loop.cpp \
	example_init.cpp \
	example_tasklist.cpp \
	example_syscal.cpp \
	example_dma_ramp.cpp \
	example_main.cpp \
	dummy_hal.cpp \
	dummy_platform.cpp \
	tasklist_util.cpp \
	host_dev.cpp \
	jetsonGPIO.cpp \
	bts_afi910.cpp\
	bts_afi910_init.cpp\
	bts_afi910_burst_loop.cpp\
	bts_afi910_rfic_dma.cpp\
	../src/pmic_adar690x.cpp \
	../src/pmic_driver.cpp \
	../src/pmic_rw.cpp \

OBJS=$(CFILES:.cpp=.o)
DEPS=$(OBJS:.o=.d)
LIB_DIRS=-L../Debug
SLIBS=-ldriver -lm -pthread -lrt
INCPATH=-I../include

all: $(TARGET)

$(TARGET): $(OBJS) Makefile
	$(CXX) $(VERBOSE) $(OBJS) $(OFLAGS) $(INCPATH) $(LIBFLAGS) $(LIB_DIRS) $(SLIBS) -o $@

%.o: %.cpp
	$(CXX) $(VERBOSE) $(CCFLAGS) $(INCPATH) -o $@ -c $<

clean:
	$(RM) *.o *.gdb $(TARGET) $(DEPS)

-include $(DEPS)
