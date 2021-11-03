
APP:= webcamsrc_test_built_from_library

SRCS:= $(wildcard *.c)
INCS:= $(wildcard *.h)

PKGS:= gstreamer-1.0 \
		deepstream-5.0-tegra \
		bts-deepstream-vision

OBJS:= $(SRCS:.c=.o)
CFLAGS:= `pkg-config --cflags $(PKGS)`
LIBS:= `pkg-config --libs $(PKGS)`

all: $(APP)

%.o: %.c $(INCS) Makefile
	$(CC) -c -o $@ $(CFLAGS) $<

$(APP): $(OBJS) Makefile
	$(CC) -o $(APP) $(OBJS) $(LIBS)

clean:
	rm -rf $(OBJS) $(APP)


