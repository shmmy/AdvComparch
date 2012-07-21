#!/bin/bash

resultfolder03=results03
resultfolder46=results46
resultfolder79=results79


echo team03
cd $resultfolder03
./plot-all *.res
cd ../

echo team46
cd $resultfolder46
./plot-all *.res
cd ../

echo team79
cd $resultfolder03
./plot-all *.res
cd ../
