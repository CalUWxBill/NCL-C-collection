#ifndef  _WRAP_PDF_STATS_H_
#define  _WRAP_PDF_STATS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <pdf_stats.h>

double wrap_cdf_PercatVal(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }

    double rv;
    arr *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < 4){
        rv = *(double *)args->missval;
    } else {
        double val  = args->dblp[0];
        double bcrd = args->dblp[1];
        double dcrd = args->dblp[2];
        typ_idx n   = args->idxp[0];

        gridnd grd;
        setGridNdFromList(1,&grd,&bcrd,&dcrd,&n);

        rv = cdf_PercatVal(&A[0],val,&grd);
        freeGridNd(&grd);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_pdf_PercatVal(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }

    double rv;
    arr *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < 4){
        rv = *(double *)args->missval;
    } else {
        double val  = args->dblp[0];
        double bcrd = args->dblp[1];
        double dcrd = args->dblp[2];
        typ_idx n   = args->idxp[0];

        gridnd grd;
        setGridNdFromList(1,&grd,&bcrd,&dcrd,&n);

        rv = pdf_PercatVal(&A[0],val,&grd);
        freeGridNd(&grd);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_cdf_ValatPerc(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }

    double rv;
    arr *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < 4){
        rv = *(double *)args->missval;
    } else {
        double perc = args->dblp[0];
        double bcrd = args->dblp[1];
        double dcrd = args->dblp[2];
        typ_idx n   = args->idxp[0];

        gridnd grd;
        setGridNdFromList(1,&grd,&bcrd,&dcrd,&n);

        rv = cdf_ValatPerc(&A[0],perc,&grd);
        freeGridNd(&grd);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_pdf_ValatPerc(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }

    double rv;
    arr *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < 4){
        rv = *(double *)args->missval;
    } else {
        double perc = args->dblp[0];
        double bcrd = args->dblp[1];
        double dcrd = args->dblp[2];
        typ_idx n   = args->idxp[0];

        gridnd grd;
        setGridNdFromList(1,&grd,&bcrd,&dcrd,&n);

        rv = pdf_ValatPerc(&A[0],perc,&grd);
        freeGridNd(&grd);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

arr wrap_cdf_ValsatPercs(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }

    arr rv;
    arr data  = removeMissing(args->arrays[0]);
    arr percs = removeMissing(args->arrays[1]);
    if ((data.tlen < 4) || (percs.tlen < 1)){
        rv = *(arr *)args->missval;
    } else {
        double bcrd = args->dblp[0];
        double dcrd = args->dblp[1];
        typ_idx n   = args->idxp[0];

        gridnd grd;
        setGridNdFromList(1,&grd,&bcrd,&dcrd,&n);

        rv = cdf_ValsatPercs(&data,percs,&grd);
        freeGridNd(&grd);
    }
    freeAr(&data);
    freeAr(&percs);
    return rv;
}

arr wrap_pdf_ValsatPercs(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }

    arr rv;
    arr data  = removeMissing(args->arrays[0]);
    arr percs = removeMissing(args->arrays[1]);
    if ((data.tlen < 4) || (percs.tlen < 1)){
        rv = *(arr *)args->missval;
    } else {
        double bcrd = args->dblp[0];
        double dcrd = args->dblp[1];
        typ_idx n   = args->idxp[0];

        gridnd grd;
        setGridNdFromList(1,&grd,&bcrd,&dcrd,&n);

        rv = pdf_ValsatPercs(&data,percs,&grd);
        freeGridNd(&grd);
    }
    freeAr(&data);
    freeAr(&percs);
    return rv;
}

double wrap_pdf_Mode(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }

    double rv;
    arr *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < 4){
        rv = *(double *)args->missval;
    } else {
        double bcrd = args->dblp[0];
        double dcrd = args->dblp[1];
        typ_idx n   = args->idxp[0];

        gridnd grd;
        setGridNdFromList(1,&grd,&bcrd,&dcrd,&n);

        rv = pdf_Mode(&A[0],&grd);
        freeGridNd(&grd);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_pdf_Mean(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }

    double rv;
    arr *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < 4){
        rv = *(double *)args->missval;
    } else {
        double bcrd = args->dblp[0];
        double dcrd = args->dblp[1];
        typ_idx n   = args->idxp[0];

        gridnd grd;
        setGridNdFromList(1,&grd,&bcrd,&dcrd,&n);

        rv = pdf_Mean(&A[0],&grd);
        freeGridNd(&grd);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_pdf_Var_mn(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }

    double rv;
    arr *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < 4){
        rv = *(double *)args->missval;
    } else {
        double mean = args->dblp[0];
        double bcrd = args->dblp[1];
        double dcrd = args->dblp[2];
        typ_idx n   = args->idxp[0];

        gridnd grd;
        setGridNdFromList(1,&grd,&bcrd,&dcrd,&n);

        rv = pdf_Var_mn(&A[0],mean,&grd);
        freeGridNd(&grd);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_pdf_Var(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }

    double rv;
    arr *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < 4){
        rv = *(double *)args->missval;
    } else {
        double bcrd = args->dblp[0];
        double dcrd = args->dblp[1];
        typ_idx n   = args->idxp[0];

        gridnd grd;
        setGridNdFromList(1,&grd,&bcrd,&dcrd,&n);

        rv = pdf_Var(&A[0],&grd);
        freeGridNd(&grd);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

#endif
