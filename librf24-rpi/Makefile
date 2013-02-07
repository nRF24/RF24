all: librf24 examples

librf24:
	$(MAKE) -C librf24 all

examples:
	$(MAKE) -C examples


clean: 
	$(MAKE) -C librf24 clean
	$(MAKE) -C examples clean

install: 
	$(MAKE) -C librf24 install
	$(MAKE) -C examples install

.PHONY:  all install  librf24 examples

