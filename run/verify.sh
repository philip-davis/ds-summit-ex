#!/bin/bash

diff <(awk '!/integers/ {print $4, $6, $8}' put.log | sort -n) <(awk '{print $4, $5, $7}' get.log | sort -n) > /dev/null
if [ "$?" == "0" ] ; then
    echo "Results OK"
else
    echo "Error in results!"
fi
