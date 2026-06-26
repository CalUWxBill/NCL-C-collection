#!/bin/bash

cd $NCL_USER_DIR/so
nhlcc -Wall -c $NCLC_SRC/ncl_math.c
ld -shared -zmuldefs -o ncl_math.so ncl_math.o -G
rm *.o
