#!/bin/bash

cd $NCL_USER_DIR/so
nhlcc -Wall -Wextra -c $NCLC_SRC/ncl_sort.c
ld -shared -zmuldefs -o ncl_sort.so ncl_sort.o -G
rm *.o
