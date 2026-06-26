#ifndef  _WRAP_SORT_H_
#define  _WRAP_SORT_H_
/* rename wrap_misc */

#include <stdio.h>
#include <stdlib.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <sort2.h>

arr wrap_qsort_idx(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr *P = args->arrays[0];
    return qsortArrayIdx(P);
}

arr wrap_qsort(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr *array = args->arrays[0];
    arr rv     = Array(1,DOUBLE,array->tlen);
    copyMiss(&rv,array);
    fillArWithMiss(&rv);
    arr A = removeMissing(array);
    
    arr P  = qsortArray(&A);
    copyArVals(&rv,&P);
    
    freeAr(&A);
    freeAr(&P);
    return rv;
}

arr wrap_qsort_idx_rev(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr *P = args->arrays[0];
    return qsortArrayIdxRev(P);
}

arr wrap_qsort_rev(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr *array = args->arrays[0];
    arr rv     = Array(1,DOUBLE,array->tlen);
    copyMiss(&rv,array);
    fillArWithMiss(&rv);
    arr A = removeMissing(array);
    
    arr P  = qsortArrayRev(&A);
    copyArVals(&rv,&P);
    
    freeAr(&A);
    freeAr(&P);
    return rv;
}

typ_idx wrap_countNonMissNArrays(input_args *args){
    /* Variable number of arguments */
    return countNonMissNArraysList(args->narrs,args->arrays);
}

typ_idx wrap_countNonMiss(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return countNonMiss(args->arrays[0]);
}

typ_idx wrap_countMiss(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return countMiss(args->arrays[0]);
}

int wrap_isAnyMiss(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return isAnyMiss(args->arrays[0]);
}

#endif
