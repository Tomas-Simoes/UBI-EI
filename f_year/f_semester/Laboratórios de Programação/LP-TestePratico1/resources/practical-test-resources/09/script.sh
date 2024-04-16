#!/bin/bash

openssl enc -aes-128-ctr -K 112233445566 -in cant-touch-this.enc -iv 0 2> /dev/null
