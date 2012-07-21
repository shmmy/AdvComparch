#!/bin/bash

files03=team03/*.trace
files46=team46/*.trace
files79=team79/*.trace

resultfolder03=results03
resultfolder46=results46
resultfolder79=results79


echo team03
for i in $files03
do
    echo $i
    ./predict $i >> $i.res
    #mv $i.res $resultfolder03
done

echo team46
for i in $files46
do
    echo $i
    ./predict $i >> $i.res
    #mv $i.res $resultfolder46
done

echo team79
for i in $files79
do
    echo $i
    ./predict $i >> $i.res
    #mv $i.res $resultfolder79
done
