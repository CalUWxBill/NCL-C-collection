#!/bin/bash

cd $NCL_USER_DIR/so
nhlcc -Wall -Wextra -c $NCLC_SRC/ncl_all.c -lgsl -lgslcblas
ld -shared -zmuldefs -o ncl_all.so ncl_all.o -G -L$CONDA_PREFIX/lib -lgsl -lgslcblas
rm *.o
