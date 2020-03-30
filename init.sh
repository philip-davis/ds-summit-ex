#!/bin/bash -e

export PROJID=$1
basedir=$(pwd)
export DSPACES_ROOT=${basedir}/install/dspaces
mkdir -p install/dspaces
wget https://dataspaces.rdi2.rutgers.edu/downloads/dataspaces-latest.tar.gz
tar -xzf dataspaces-latest.tar.gz
cd dataspaces-*
./configure CC=mpicc FC=mpifort --prefix=${DSPACES_ROOT}
make
make install
cd ../src
make
cd ..

envsubst '${DSPACES_ROOT} ${PROJID}' < run/job.tmpl > run/job.sh
