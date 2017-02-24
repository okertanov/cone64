##
## Copyright (C) 2017 Oleg Kertanov <okertanov@gmail.com>
##

all: metrics myip

metrics: metrics.o

myip: myio.o

clean:
	-@rm -f *.o *.a *.so metrics myip

.PHONY: all clean

.SILENT: clean
