#!/bin/bash

cd $NCL_USER_DIR/so
nhlcc -Wall -c $NCLC_SRC/ncl_s2s.c -lgsl -lgslcblas
ld -shared -zmuldefs -o ncl_s2s.so ncl_s2s.o -G -L$CONDA_PREFIX/lib -lgsl -lgslcblas
rm *.o
