#!/bin/bash
# Begin LSF directives
#BSUB -P csc143
#BSUB -J test
#BSUB -o tst.o%J
#BSUB -W 00:30
#BSUB -nnodes 3

export PATH=$PATH:/gpfs/alpine/scratch/pdavis/csc143/ds-summit-ex/install/dspaces/bin:../src

rm -f conf.*

jsrun -n 1 -a 1 -r 1 -c 1 dataspaces_server -s 1 &

while [ ! -f conf.0 ]; do
    sleep 1s
done

jsrun -n 1 -a 1 -r 1 -c 1 put &> put.log &
jsrun -n 1 -a 1 -r 1 -c 1 get &> get.log &

wait
