#!/bin/bash -e

basedir=$(pwd)
export DSPACES_INSTALL=${basedir}/install/dspaces
mkdir -p install/dspaces
wget https://dataspaces.rdi2.rutgers.edu/downloads/dataspaces-latest.tar.gz
tar -xzf dataspaces-latest.tar.gz
cd dataspaces-*
./configure CC=mpicc FC=mpifort --prefix=${DSPACES_INSTALL}
make
make install
cd ../src
make
