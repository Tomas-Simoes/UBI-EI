#!/bin/bash 
# Script File sc1.sh 
# 
bigFile=/tmp/bigFile 
if [ ! -e $bigFile ] ; then 
    # create 16MB file in /tmp with random values 
    dd if=/dev/urandom of=${bigFile} bs=16M count=1 
fi 

size=4096 

while [ $size -gt 1 ]; do 
    tmpFile=$(mktemp) 
   echo $size 
   echo $tmpFile
   ./copy_lowlevel $bigFile $tmpFile $size
   ./copy_highlevel $bigFile $tmpFile $size
   rm $tmpFile 
   let size=size/4 
done