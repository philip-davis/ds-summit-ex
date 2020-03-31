DSPACES_ROOT ?= ../install/dspaces
DSPACES_BIN=$(DSPACES_ROOT)/bin
export PATH := $(DSPACES_BIN):$(PATH)
DSPACES_CFLAGS=$(shell PATH=$(PATH) dspaces_config -c)
DSPACES_LDFLAGS=$(shell PATH=$(PATH) dspaces_config -l)
CC=mpicc

all: put get

put: put.o common.o
	$(CC) -g -o put put.o common.o $(DSPACES_LDFLAGS)

get: get.o common.o
	$(CC) -g -o get get.o common.o $(DSPACES_LDFLAGS)

%.o: %.c
	$(CC) -g -c $(DSPACES_CFLAGS) $<

clean:
	rm -f *.o put get
