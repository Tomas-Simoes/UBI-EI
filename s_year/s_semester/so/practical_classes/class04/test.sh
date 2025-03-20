#!/bin/bash 
# Script File sc1.sh 
# 
bigFile=/tmp/bigFile 
if [ ! -e $bigFile ] ; then 
    # create 16MB file in /tmp with random values 
    dd if=/dev/urandom of=${bigFile} bs=8M count=1 
fi 

size=8192
outputFile="results52585.txt"

> $outputFile

while [ $size -gt 1 ]; do 
    echo "" >> $outputFile
    echo $size >> $outputFile
   { time ./main $bigFile $size; } 2>&1 | tr '\n' ' ' >> $outputFile
   echo -n " " >> $outputFile
   let size=size/2
done