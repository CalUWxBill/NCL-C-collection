#!/bin/bash

cd $NCL_USER_DIR/so
nhlcc -Wall -c $NCLC_SRC/ncl_convert.c
ld -shared -zmuldefs -o ncl_convert.so ncl_convert.o -G
rm *.o
