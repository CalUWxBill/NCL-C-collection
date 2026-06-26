#!/bin/bash

cd $NCL_USER_DIR/so
nhlcc -Wall -Wextra -c $NCLC_SRC/ncl_stats.c
ld -shared -zmuldefs -o ncl_stats.so ncl_stats.o -G
rm *.o
