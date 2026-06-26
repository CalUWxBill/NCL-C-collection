#!/bin/bash

cd $NCL_USER_DIR/so
nhlcc -Wall -c $NCLC_SRC/ncl_verify.c -lgsl -lgslcblas
ld -shared -zmuldefs -o ncl_verify.so ncl_verify.o -G -L$CONDA_PREFIX/lib -lgsl -lgslcblas
rm *.o
