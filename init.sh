#!/bin/bash -e

export PROJID=$1
basedir=$(pwd)
export DSPACES_ROOT=${basedir}/install/dspaces
mkdir -p install/dspaces
if [ ! -f dataspaces-latest.tar.gz ] ; then
    wget https://dataspaces.rdi2.rutgers.edu/downloads/dataspaces-latest.tar.gz
    tar -xzf dataspaces-latest.tar.gz
fi
cd dataspaces-*
./configure CC=mpicc FC=mpifort --prefix=${DSPACES_ROOT}
make
make install
cd ../src
make
cd ..

envsubst '${DSPACES_ROOT} ${PROJID}' < run/job.tmpl > run/job.sh
