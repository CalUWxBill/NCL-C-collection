#ifndef  _WRAP_1D_PDF_H_
#define  _WRAP_1D_PDF_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <1d_pdf.h>

arr wrap_KernelPdf1d(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }

    arr A = removeMissing(args->arrays[0]);
    arr rv;
    if (A.tlen < (typ_idx)4){
        rv = *(arr *)args->missval;
    } else {
        gridnd grd;
        double bbndry = args->dblp[0];
        double ebndry = args->dblp[1];
        typ_idx lens  = args->idxp[0];
        calcGridFromCornersCntNdFromList(1,&grd,&bbndry,&ebndry,&lens);
        rv = KernelPdf1d(grd,A);
        freeGridNd(&grd);
    }
    freeAr(&A);
    return rv;
}

arr wrap_NormKernelPdf1d(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
/*  printInputArgs(stderr,args);    */
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }

    arr A = removeMissing(args->arrays[0]);
    arr rv;
    if (A.tlen < (typ_idx)4){
        rv = *(arr *)args->missval;
    } else {
        gridnd grd;
        double bbndry = args->dblp[0];
        double ebndry = args->dblp[1];
        typ_idx lens  = args->idxp[0];
        calcGridFromCornersCntNdFromList(1,&grd,&bbndry,&ebndry,&lens);
        rv = NormKernelPdf1d(grd,A);
        freeGridNd(&grd);
    }
    freeAr(&A);
    return rv;
}


arr wrap_NormSmoothKernelPdf1d(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
/*  printInputArgs(stderr,args);    */
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }

    arr A = removeMissing(args->arrays[0]);
    arr rv;
    if (A.tlen < (typ_idx)4){
        rv = *(arr *)args->missval;
    } else {
        gridnd grd;
        double kwidth = args->dblp[0];
        double bbndry = args->dblp[1];
        double ebndry = args->dblp[2];
        typ_idx lens  = args->idxp[0];
        calcGridFromCornersCntNdFromList(1,&grd,&bbndry,&ebndry,&lens);
        rv = NormSmoothKernelPdf1d(grd,A,kwidth);
        freeGridNd(&grd);
    }
    freeAr(&A);
    return rv;
}


arr wrap_NormSmoothKernelPdf1dWgt(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 10,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
/*  printInputArgs(stderr,args);    */
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }

    arr *A = removeMissingNArraysList_alloc(2, args->arrays);
    arr rv;
    if (A[0].tlen < (typ_idx)4){
        rv = *(arr *)args->missval;
    } else {
        gridnd grd;
        double kwidth = args->dblp[0];
        double bbndry = args->dblp[1];
        double ebndry = args->dblp[2];
        typ_idx lens  = args->idxp[0];
        calcGridFromCornersCntNdFromList(1,&grd,&bbndry,&ebndry,&lens);
        arr wgt = A[0];
        rv = NormSmoothKernelPdf1dWgt(wgt,grd,A[1],kwidth);
        freeGridNd(&grd);
    }
    for (i=0;i<2+1;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

#endif
