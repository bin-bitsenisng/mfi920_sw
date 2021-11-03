APP:= imshow

CC:= g++
SRCS:= $(wildcard *.cpp)

INCS:= $(wildcard *.h)

PKGS:= opencv

OBJS:= $(SRCS:.cpp=.o)

CFLAGS+= `pkg-config --cflags $(PKGS)`

LIBS:= `pkg-config --libs $(PKGS)` 

all: $(APP)

%.o: %.cpp $(INCS) Makefile
	$(CC) -c -o $@ $(CFLAGS) $<

$(APP): $(OBJS) Makefile
	$(CC) -o $(APP) $(OBJS) $(LIBS)

clean:
	rm -rf $(OBJS) $(APP)


