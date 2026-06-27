# Do NOT install in production environments as C code needs to be rigorously checked for security and memory issues!

## This is a collection of NCL functions, many of which call C functions that use a pretty substantial N-dim array library that is in the include directory.

# Install Prerequisites:

#### * Works on a Linux machine.

#### * conda

#### * Prerequisites are now in the ncl-c.yml file

# Compile NCL shared libraries that have C code used by my NCL scripts.
#### Copy ncl-c directory under home directory or another place you put shell scripts.

#### Edit ncl-c.yml according to your paths
    $ conda env create -f ncl-c/ncl-c.yml

#### activate.sh and deactivate.sh may need to be edited:

#### To activate,
    $ . ncl-c/activate.sh

#### To deactivate,
    $ . ncl-c/deactivate.sh

#### Give executable permission for bash shell scripts.
##### - Use whatever permission is appropriate for your system as long as you can execute scripts and scripts called within can be executed.
    $ chmod ug+x ncl-c/sh/*

#### Edit the nhlcc program at $CONDA_PREFIX/bin/nhlcc, by changing the "set cc" line.
    set cc       = "cc"

#### Install the C source files into NCL shared library objects by running the following script.
    $ compile_ncl_all.sh
