#############################################################################
#
# Makefile for librf24 examples on Linux
#
# License: GPL (General Public License)
# Author:  gnulnulf <arco@appeltaart.mine.nu>
# Date:    2013/02/07 (version 1.0)
#
# Description:
# ------------
# use make all and make install to install the examples
#

ifeq ($(wildcard ../Makefile.inc), )
	$(error Configuration not found. Run ./configure first)
endif

include ../Makefile.inc

# define all programs
PROGRAMS = gettingstarted gettingstarted_call_response transfer pingpair_dyn
SOURCES = ${PROGRAMS:=.cpp}

all: ${PROGRAMS}

${PROGRAMS}: ${SOURCES}
	${CXX} ${CFLAGS} -I${HEADER_DIR}/.. -I.. -L${LIB_DIR} -lrf24 $@.cpp -o $@

clean:
	rm -rf $(PROGRAMS)

install: all
	mkdir -p $(EXAMPLES_DIR)
	for prog in $(PROGRAMS); do \
	  install -m 0755 $$prog $(EXAMPLES_DIR); \
	done

upload: all
	@echo "[Uploading examples to ${REMOTE}:${REMOTE_EXAMPLES_DIR}]"
	@ssh -q -t -p ${REMOTE_PORT} ${REMOTE} "mkdir -p ${REMOTE_EXAMPLES_DIR}"
	@ssh -q -t -p ${REMOTE_PORT} ${REMOTE} "mkdir -p /tmp/RF24_examples"
	@scp -q -P ${REMOTE_PORT} ${PROGRAMS} ${REMOTE}:/tmp/RF24_examples
	for prog in $(PROGRAMS); do \
		ssh -q -t -p ${REMOTE_PORT} ${REMOTE} "sudo install -m 0755 /tmp/RF24_examples/$${prog} ${REMOTE_EXAMPLES_DIR}"; \
	done
	@ssh -q -t -p ${REMOTE_PORT} ${REMOTE} "rm -rf /tmp/RF24_examples"

.PHONY: install upload
