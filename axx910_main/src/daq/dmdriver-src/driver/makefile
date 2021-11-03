TOP?=.
CONFIG?=Debug

ABIBIN_R5=c:/Xilinx/SDK/2017.3/gnu/armr5/nt/gcc-arm-none-eabi/bin/

MKDIR=mkdir
RMDIR=rm -rf

CC_R5=$(ABIBIN_R5)/armr5-none-eabi-gcc
CFLAGS_R5=\
	-DARMR5 -mcpu=cortex-r5 -mfloat-abi=hard -mfpu=vfpv3-d16 \
	-MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" \
	-Wall
INCPATH=-I$(TOP)/include

AR_R5=$(ABIBIN_R5)/armr5-none-eabi-ar
ARFLAGS_R5=r

#CC=$(CC_R5)
#CFLAGS=$($(CONFIG)_CFLAGS) $(CFLAGS_R5) $(INCPATH)
CFLAGS=$($(CONFIG)_CFLAGS) $(INCPATH)
Debug_CFLAGS=-O0 -g3
Release_CFLAGS=-O2
OBJFLAG=-c -o
EXEFLAG=-o
#AR=$(AR_R5)
#ARFLAGS=$(ARFLAGS_R5)

ARTIFACT = libdriver.a

C_SRC = \
	src/power_up.c \
	src/power_down.c \
	src/dataport_mipi.c \
	src/dataport_lvds.c \
	src/ramp_simple.c \
	src/calc_ramp.c \
	src/basic_op.c \
	src/trigger.c \
	src/periodic.c \
	src/ramp_multi.c \
	src/callfw.c \
	src/rfpll_ramp.c \
	src/pin_mux.c \
	src/set_rfpll_freq.c \
	src/afe.c \
	src/version.c \
	src/init.c \
	src/fini.c \
	src/spicmd.c \
	src/mask_faults.c \
	src/pd_measure.c \
	src/tx_ramp.c \
	src/decode_bpid.c \
	src/temperature.c \
	src/temp_change.c \
	src/readtemps.c \
	src/lvdstestpat.c \
	src/lockconfig.c \
	src/unlockconfig.c \
	src/sleep.c \
	src/spicounter.c \
	src/tasklist.c \
	src/tasklistnb.c \
	src/syscal.c \
	src/pwdn.c \
	src/writerfpllperiod.c \
	src/rfpllperiod.c \
	src/pwrdetcfg.c \
	src/pmic_driver.c \
	src/pmic_adar690x.c \
	src/pmic_rw.c \
	src/legacy/3_0_adcpllfreq.c \
	src/legacy/3_0_calc_ramp.c \
	src/legacy/3_0_dataport_mipi.c \
	src/legacy/3_0_dataport_lvds.c \
	src/legacy/3_0_modify_ramp.c \
	src/legacy/3_0_multiburst.c \
	src/legacy/3_0_power_up.c \
	src/legacy/3_0_ramp_multi.c \
	src/legacy/3_0_ramp_simple.c \
	src/legacy/3_0_set_rfpll_freq.c \
	src/legacy/3_0_trigger.c \
	src/legacy/3_2_dataport_mipi.c \
	src/legacy/3_2_dataport_lvds.c \
	src/legacy/3_3_calc_ramp.c \
	src/legacy/3_3_ramp_multi.c \
	src/legacy/3_3_ramp_simple.c \
	src/legacy/3_3_3_tlpool.c \
	src/vars/active_dms.c \
	src/vars/checkspicounters.c \
	src/vars/checkramcrc.c \
	src/vars/checkromcrc.c \
	src/vars/checkfabriccrc.c \
	src/vars/fault_mask.c \
	src/vars/fwadcphasecal.c \
	src/vars/fwadcpllalign.c \
	src/vars/fwconfig.c \
	src/vars/fwdecifltdiagchk.c \
	src/vars/fwflashadccal.c \
	src/vars/fwhpfcal.c \
	src/vars/fwpwrsupchk.c \
	src/vars/fwtxpwrchk.c \
	src/vars/fwtxloadmonchk.c \
	src/vars/fwfltoverflowdetchk.c \
	src/vars/fwauxdiagchk.c \
	src/vars/fwrxbasebandchk.c \
	src/vars/fwrxbasebandlatentchk.c \
	src/vars/fwlochaincal.c \
	src/vars/fwrxgainnorm.c \
	src/vars/fwpgacal.c \
	src/vars/fwtxpacal.c \
	src/vars/fwtxpaadj.c \
	src/vars/fwrfpllbowcal.c \
	src/vars/poweredblocks.c \
	src/vars/savedtemps.c \
	src/vars/savedrfpll.c \
	src/vars/checkrfpll.c \
	src/vars/checkadcpll.c \
	src/vars/checkspicrc.c \
	src/vars/fwtxisomonchk.c \
	src/vars/fwpwrdetratchk.c \
	src/vars/fwrxchaindiagchk.c \
	src/vars/fwrfpllperiodchk.c \
	src/vars/fwtimecompenchk.c \
	src/vars/wdtchken.c \
	src/vars/entrig.c \
	src/vars/entrigprog.c \
	examples/host_dev.c \
	examples/jetsonGPIO.c \

SRC := $(C_SRC)
OBJ := $(C_SRC:.c=.o)
DEP := $(OBJ:.o=.d)

.PHONY: all clean $(CONFIG)_build
all: $(CONFIG)_build

clean:
	$(RMDIR) $(CONFIG)

$(CONFIG)_build: | $(CONFIG)
	$(MAKE) -C $(CONFIG) -f ../Makefile $(ARTIFACT) TOP=.. CONFIG=$(CONFIG)

$(ARTIFACT): $(OBJ)
	$(AR) $(ARFLAGS) $@ $?

%.o: %.c
	$(CC) $(CFLAGS) $(OBJFLAG) $@ $<

# directory structure recreated for objects in build dir
OBJDIR := $(sort $(dir $(OBJ)))
OBJDIR := $(patsubst %/,%,$(OBJDIR))
$(OBJ): | $(OBJDIR)

# so only look for sources, not directories, in source dir
vpath %.h $(TOP)
vpath %.c $(TOP)

$(CONFIG) $(OBJDIR):
	$(MKDIR) "$@"

ifneq ($(strip $(DEP)),)
-include $(DEP)
endif
