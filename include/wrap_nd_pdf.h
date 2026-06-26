#ifndef  _WRAP_ND_PDF_H_
#define  _WRAP_ND_PDF_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <nd_pdf.h>

arr wrap_KernelPdfNd(input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }

    int ntotvars = args->narrs + args->ndbls + args->nidxs;
    int ndims    = ntotvars - 3;
    if (ndims < 1){
        return *(arr *)args->missval;
    }
    arr **data = malloc(ndims*sizeof(arr *));
    for (i=0;i<ndims;i++){
        data[i] = args->arrays[i];
    }
    arr *A = removeMissingNArraysList_alloc(ndims, data);
    arr rv;
    if (A[0].tlen < (typ_idx)5){
        rv = *(arr *)args->missval;
    } else {
        gridnd grd;
        if (ndims > 1){
            arr bbndry = args->arrays[ndims+0];
            arr ebndry = args->arrays[ndims+1];
            arr lens   = args->arrays[ndims+2];
            calcGridFromCornersCntNdFromList(ndims,&grd,pntr_of(&bbndry),pntr_of(&ebndry),pntr_of(&lens));
        } else {
            double bbndry = args->dblp[0];
            double ebndry = args->dblp[1];
            typ_idx lens  = args->idxp[0];
            calcGridFromCornersCntNdFromList(ndims,&grd,&bbndry,&ebndry,&lens);
        }
        rv = KernelPdfNdList(&grd,A);
        freeGridNd(&grd);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    free(data);
    return rv;
}

arr wrap_MultiVarNormKernelPdfNd(input_args *args){
    int i;
/*  printInputArgs(stderr,args);    */
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }

    int ntotvars = args->narrs + args->ndbls + args->nidxs;
    int ndims    = ntotvars - 3;
    if (ndims < 1){
        return *(arr *)args->missval;
    }
    arr *data = malloc(ndims*sizeof(arr));
    for (i=0;i<ndims;i++){
        data[i] = args->arrays[i];
    }
    arr *A = removeMissingNArraysList_alloc(ndims, data);
    arr rv;
    if (A[0].tlen < (typ_idx)5){
        rv = *(arr *)args->missval;
    } else {
        gridnd grd;
        if (ndims > 1){
            arr bbndry = args->arrays[ndims+0];
            arr ebndry = args->arrays[ndims+1];
            arr lens   = args->arrays[ndims+2];
            calcGridFromCornersCntNdFromList(ndims,&grd,pntr_of(&bbndry),pntr_of(&ebndry),pntr_of(&lens));
        } else {
            double bbndry = args->dblp[0];
            double ebndry = args->dblp[1];
            typ_idx lens  = args->idxp[0];
            calcGridFromCornersCntNdFromList(ndims,&grd,&bbndry,&ebndry,&lens);
        }
        rv = MultiVarNormKernelPdfNdList(&grd,A);
        freeGridNd(&grd);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    free(data);
    return rv;
}


arr wrap_MultiVarNormSmoothKernelPdfNd(input_args *args){
    int i;
/*  printInputArgs(stderr,args);    */
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }

    int ntotvars = args->narrs + args->ndbls + args->nidxs;
    int ndims    = ntotvars - 4;
    if (ndims < 1){
        return *(arr *)args->missval;
    }
    arr *data = malloc(ndims*sizeof(arr));
    for (i=0;i<ndims;i++){
        data[i] = args->arrays[i];
    }
    arr *A = removeMissingNArraysList_alloc(ndims, data);
    arr rv;
    if (A[0].tlen < (typ_idx)5){
        rv = *(arr *)args->missval;
    } else {
        gridnd grd;
        double *kwidth = NULL;
        if (ndims > 1){
            kwidth = pntr_of(args->arrays[ndims+0]);
            arr bbndry = args->arrays[ndims+1];
            arr ebndry = args->arrays[ndims+2];
            arr lens   = args->arrays[ndims+3];
            calcGridFromCornersCntNdFromList(ndims,&grd,pntr_of(&bbndry),pntr_of(&ebndry),pntr_of(&lens));
        } else {
            kwidth = &args->dblp[0];
            double bbndry = args->dblp[1];
            double ebndry = args->dblp[2];
            typ_idx lens  = args->idxp[0];
            calcGridFromCornersCntNdFromList(ndims,&grd,&bbndry,&ebndry,&lens);
        }
        rv = MultiVarNormSmoothKernelPdfNdList(&grd,A,kwidth);
        freeGridNd(&grd);
    }
    for (i=0;i<ndims;i++){
        freeAr(&A[i]);
    }
    free(A);
    free(data);
    return rv;
}


arr wrap_MultiVarNormSmoothKernelPdfNdWgt(input_args *args){
    int i;
/*  printInputArgs(stderr,args);    */
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }

    int ntotvars = args->narrs + args->ndbls + args->nidxs;
    int ndims    = ntotvars - 5;
    if (ndims < 1){
        return *(arr *)args->missval;
    }
    arr *data = malloc(ndims+1*sizeof(arr));
    for (i=0;i<ndims+1;i++){
        data[i] = args->arrays[i];
    }
    arr *A = removeMissingNArraysList_alloc(ndims+1, data);
    arr rv;
    if (A[0].tlen < (typ_idx)4){
        rv = *(arr *)args->missval;
    } else {
        gridnd grd;
        double *kwidth = NULL;
        if (ndims > 1){
            kwidth = pntr_of(args->arrays[ndims+1]);
            arr bbndry = args->arrays[ndims+2];
            arr ebndry = args->arrays[ndims+3];
            arr lens   = args->arrays[ndims+4];
            calcGridFromCornersCntNdFromList(ndims,&grd,pntr_of(&bbndry),pntr_of(&ebndry),pntr_of(&lens));
        } else {
            kwidth = &args->dblp[0];
            double bbndry = args->dblp[1];
            double ebndry = args->dblp[2];
            typ_idx lens  = args->idxp[0];
            calcGridFromCornersCntNdFromList(ndims,&grd,&bbndry,&ebndry,&lens);
        }
        arr wgt = A[0];
        rv = MultiVarNormSmoothKernelPdfNdWgtList(&wgt,&grd,&A[1],kwidth);
        freeGridNd(&grd);
    }
    for (i=0;i<ndims+1;i++){
        freeAr(&A[i]);
    }
    free(A);
    free(data);
    return rv;
}

#endif
