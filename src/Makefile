DSPACES_BIN=$(DSPACES_ROOT)/bin

export PATH := $(DSPACES_BIN):$(PATH)

DSPACES_CFLAGS=$(shell dspaces_config -c)
DSPACES_LDFLAGS=$(shell dspaces_config -l)
CC=mpicc

all: put get

put: put.o
	$(CC) -o put put.o $(DSPACES_LDFLAGS)

get: get.o
	$(CC) -o get get.o $(DSPACES_LDFLAGS)

%.o: %.c
	$(CC) -c $(DSPACES_CFLAGS) $<

clean:
	rm -f *.o put get
