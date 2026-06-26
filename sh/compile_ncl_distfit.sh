#!/bin/bash

cd $NCL_USER_DIR/so
nhlcc -Wall -c $NCLC_SRC/ncl_distfit.c -lgsl -lgslcblas
ld -shared -zmuldefs -o ncl_distfit.so ncl_distfit.o -G -L$CONDA_PREFIX/lib -lgsl -lgslcblas
rm *.o
