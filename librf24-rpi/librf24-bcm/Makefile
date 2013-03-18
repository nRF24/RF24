all: librf24-bcm examples

librf24-bcm:
	$(MAKE) -C librf24-bcm all

examples:
	$(MAKE) -C examples

clean: 
	$(MAKE) -C librf24-bcm clean
	$(MAKE) -C examples clean

install: 
	$(MAKE) -C librf24-bcm install
	$(MAKE) -C examples install

.PHONY:  all install  librf24-bcm examples

