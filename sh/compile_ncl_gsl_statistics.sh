#!/bin/bash

cd $NCL_USER_DIR/so
nhlcc -Wall -c $NCLC_SRC/ncl_gsl_statistics.c -lgsl -lgslcblas
ld -shared -zmuldefs -o ncl_gsl_statistics.so ncl_gsl_statistics.o -G -L$CONDA_PREFIX/lib -lgsl -lgslcblas
rm *.o
