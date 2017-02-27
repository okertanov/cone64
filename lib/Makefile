##
## Copyright (C) 2017 Oleg Kertanov <okertanov@gmail.com>
##

CXX_FLAGS:=-Wall -Wextra -std=c++1z \
	-Wno-deprecated-declarations \
	-Wno-unused-private-field \
	-D_BSD_SOURCE -D_GNU_SOURCE \
	-O3 -msse4 -ffast-math
LD_FLAGS:=

all: myip metrics uname

metrics: metrics.o
	c++ $(CXX_FLAGS) $(LD_FLAGS) -o $@ $^

myip: myip.o
	c++ $(CXX_FLAGS) $(LD_FLAGS) -o $@ $^

uname: uname.o
	c++ $(CXX_FLAGS) $(LD_FLAGS) -o $@ $^

%.o:%.cpp
	c++ $(CXX_FLAGS) -c -o $@ $^

clean:
	-@rm -f *.o *.a *.so metrics myip uname

.PHONY: all clean

.SILENT: clean
