#!/bin/bash

cd $NCL_USER_DIR/so
nhlcc -Wall -c $NCLC_SRC/ncl_gsl_randist.c -lgsl -lgslcblas
ld -shared -zmuldefs -o ncl_gsl_randist.so ncl_gsl_randist.o -G -L$CONDA_PREFIX/lib -lgsl -lgslcblas
rm *.o
