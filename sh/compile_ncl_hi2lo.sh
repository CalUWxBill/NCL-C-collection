#!/bin/bash

cd $NCL_USER_DIR/so
nhlcc -Wall -c $NCLC_SRC/ncl_hi2lo.c
ld -shared -zmuldefs -o ncl_hi2lo.so ncl_hi2lo.o -G
rm *.o
