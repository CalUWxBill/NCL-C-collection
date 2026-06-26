#!/bin/sh

conda activate ncl-c

if [ -z ${PATH+x} ]; then
  PATH=$NCLC_SH
else
  PATH=$NCLC_SH:$PATH
fi
export PATH

if [ -z ${C_INCLUDE_PATH+x} ]; then
  C_INCLUDE_PATH=$HOME/ncl-c/include
else
  C_INCLUDE_PATH=$HOME/ncl-c/include:$C_INCLUDE_PATH
fi
export C_INCLUDE_PATH

export NCARG_COLORMAPS=$NCL_USER_DIR/colormaps:$NCARG_ROOT/lib/ncarg/colormaps
export NCL_DEF_LIB_DIR=$NCL_USER_DIR/so
