##
## Copyright (C) 2017 Oleg Kertanov <okertanov@gmail.com>
##

all:
	$(MAKE) -C lib
	$(MAKE) -C server
	$(MAKE) -C wwwroot

clean:
	$(MAKE) -C lib clean
	$(MAKE) -C server clean
	$(MAKE) -C wwwroot clean

.PHONY: all clean

.SILENT: clean
