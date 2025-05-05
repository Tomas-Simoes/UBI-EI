#!/bin/bash
# 
# This file can be used to test if your shell implements the execution in background (&) funcionality
# You should make the file executable : chmod 755 1.sh
# Then run 
# soshell > ./1.sh covilha &
# soshell > ./1.sh fundao  &
# Can also be used to test if the shell implements job control.
#
if [ $# -lt 1 ]; then echo "usage ./1.sh <string>"; exit 1; fi
while [ 1 ]; do 
  echo $1
  sleep 2
done
