##
## Copyright (C) 2017 Oleg Kertanov <okertanov@gmail.com>
##

all:
	$(MAKE) -C bin
	$(MAKE) -C etc
	$(MAKE) -C server
	$(MAKE) -C wwwroot

clean:
	$(MAKE) -C bin clean
	$(MAKE) -C etc clean
	$(MAKE) -C server clean
	$(MAKE) -C wwwroot clean

.PHONY: all clean

.SILENT: clean
