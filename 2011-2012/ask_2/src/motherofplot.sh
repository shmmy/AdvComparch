#!/bin/bash
for i in *
do
    cd $i
    ./plotall.sh
    cd ../
done

