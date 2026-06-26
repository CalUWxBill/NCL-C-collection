#!/bin/sh

# User specific aliases and functions
function remove_from {
    # Delete path by parts so we can never accidentally remove sub paths
    local ret_path=$1
    ret_path=${ret_path//":$2:"/":"} # delete any instances in the middle
    ret_path=${ret_path/#"$2:"/} # delete any instance at the beginning
    ret_path=${ret_path/%":$2"/} # delete any instance in the at the end
    echo $ret_path
}

unset NCARG_COLORMAPS

if [ "$PATH" = "$NCLC_SH" ] ; then
  unset PATH
else
  export PATH=$(remove_from $PATH "$NCLC_SH")
fi

if [ "$C_INCLUDE_PATH" = "$HOME/ncl-c/include" ] ; then
  unset C_INCLUDE_PATH
else
  export C_INCLUDE_PATH=$(remove_from $C_INCLUDE_PATH "$HOME/ncl-c/include")
fi

conda deactivate
