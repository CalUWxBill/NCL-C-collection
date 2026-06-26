/* Created by Bill Scheftic */
#ifndef  _WRAP_S2S_H_
#define  _WRAP_S2S_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <s2s.h>

void wrap_getPercZscoreFromCDF(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 2,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    if (args->idxp_miss){
        for(i=0;i<args->nidxs;i++){
            if (args->idxp[i] == args->idxp_miss[i]){
                return;
            }
        }
    }
    gridnd grd;
    arr    *Val    = args->arrays[0];
    arr    *cdf    = args->arrays[1];
    double  bbndry = args->dblp[0];
    double  ebndry = args->dblp[1];
    typ_idx n      = args->idxp[0];
    arr    *P      = args->arrpp[0];
    arr    *z      = args->arrpp[1];
    /*
    printArrayFmtAllWHdr(stderr,Val,"%g","wrap_getPercZscoreFromCDF: Val - ");
    printArrayFmtAllWHdr(stderr,cdf,"%g","wrap_getPercZscoreFromCDF: cdf - ");
    fprintf(stderr,"bbndry=%g, ebndry=%g, n=%lld\n",bbndry,ebndry,n);
    */
    if (isAnyNonMiss(Val) && isAnyNonMiss(cdf)){
        calcGridFromCornersCntNdFromList(1,&grd,&bbndry,&ebndry,&n);
        getPercZscoreFromCDF(Val,cdf,&grd,P,z);
        freeGridNd(&grd);
    }
    return;
}

void wrap_getPercZscoreFromCDF_1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 2,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    if (args->idxp_miss){
        for(i=0;i<args->nidxs;i++){
            if (args->idxp[i] == args->idxp_miss[i]){
                return;
            }
        }
    }
    gridnd grd;
    double  Val    = args->dblp[0];
    arr    *cdf    = args->arrays[0];
    double  bbndry = args->dblp[1];
    double  ebndry = args->dblp[2];
    typ_idx n      = args->idxp[0];
    double *P      = args->dblpp[0];
    double *z      = args->dblpp[1];
    /*
    printArrayFmtAllWHdr(stderr,cdf,"%g","wrap_getPercZscoreFromCDF_1: Val=%g, cdf - ",Val);
    fprintf(stderr,"bbndry=%g, ebndry=%g, n=%lld\n",bbndry,ebndry,n);
    */
    if (isAnyNonMiss(cdf)){
        calcGridFromCornersCntNdFromList(1,&grd,&bbndry,&ebndry,&n);
        getPercZscoreFromCDF_1(Val,cdf,&grd,P,z);
        freeGridNd(&grd);
    }
    return;
}

void wrap_getPdfCdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 2,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    if (args->idxp_miss){
        for(i=0;i<args->nidxs;i++){
            if (args->idxp[i] == args->idxp_miss[i]){
                return;
            }
        }
    }
    gridnd grd;
    arr  *obs     = args->arrays[0];
    double kwidth = args->dblp[0];
    double bbndry = args->dblp[1];
    double ebndry = args->dblp[2];
    typ_idx n     = args->idxp[0];
    arr  *pdf_y   = args->arrpp[0];
    arr  *cdf_y   = args->arrpp[1];
    
    if (isAnyNonMiss(obs)){
        calcGridFromCornersCntNdFromList(1,&grd,&bbndry,&ebndry,&n);

        getPdfCdf(obs,kwidth,&grd,pdf_y,cdf_y);
        freeGridNd(&grd);
    }
    return;
}

void wrap_getTertiaryExtremes(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 5,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    if (args->idxp_miss){
        for(i=0;i<args->nidxs;i++){
            if (args->idxp[i] == args->idxp_miss[i]){
                return;
            }
        }
    }
    gridnd grd;
    arr    *fcstens = args->arrays[0];
    arr    *cdf     = args->arrays[1];
    double  bbndry  = args->dblp[0];
    double  ebndry  = args->dblp[1];
    typ_idx n       = args->idxp[0];
    double *P_vlo   = args->dblpp[0];
    double *P_lo    = args->dblpp[1];
    double *P_mid   = args->dblpp[2];
    double *P_hi    = args->dblpp[3];
    double *P_vhi   = args->dblpp[4];
    /*
    printArrayFmtAllWHdr(stderr,fcstens,"%g","wrap_getTertiaryExtremes: fcstens - ");
    printArrayFmtAllWHdr(stderr,cdf,"%g","wrap_getTertiaryExtremes: cdf - ");
    fprintf(stderr,"bbndry=%g, ebndry=%g, n=%lld\n",bbndry,ebndry,n);
    */
    if (isAnyNonMiss(cdf) && isAnyNonMiss(fcstens)){
    /*  fprintf(stderr,"wrap_getTertiaryExtremes: %lld valid in fcstens\n",countNonMiss(fcstens)); */
        calcGridFromCornersCntNdFromList(1,&grd,&bbndry,&ebndry,&n);
        getTertiaryExtremes(fcstens,cdf,&grd,P_vlo,P_lo,P_mid,P_hi,P_vhi);
        freeGridNd(&grd);
    }
    return;
}

void wrap_getTertiaryExtremes_z(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 5,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }

    arr    *fcstens = args->arrays[0];
    double *P_vlo   = args->dblpp[0];
    double *P_lo    = args->dblpp[1];
    double *P_mid   = args->dblpp[2];
    double *P_hi    = args->dblpp[3];
    double *P_vhi   = args->dblpp[4];
    /*
    printArrayFmtAllWHdr(stderr,fcstens,"%g","wrap_getTertiaryExtremes_z: fcstens - ");
    */
    if (isAnyNonMiss(fcstens)){
    /*  fprintf(stderr,"wrap_getTertiaryExtremes_z: %lld valid in fcstens\n",countNonMiss(fcstens));  */
        getTertiaryExtremes_z(fcstens,P_vlo,P_lo,P_mid,P_hi,P_vhi);
    }
    return;
}


void wrap_getMultiRegression(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 4,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr   *fcstens_z  = args->arrays[0];
    arr   *obs_z      = args->arrays[1];
    arr   *TC         = args->arrays[2];
    double rsq_thresh = args->dblp[0];
    arr   *ms         = args->arrpp[0];
    arr   *bs         = args->arrpp[1];
    arr   *rsqs       = args->arrpp[2];
    arr   *idxs       = args->arrpp[3];

    if (isAnyNonMiss(fcstens_z) && isAnyNonMiss(obs_z)){
        getMultiRegression(fcstens_z,obs_z,TC,rsq_thresh,ms,bs,rsqs,idxs);
    }
    return;
}

void wrap_getMultiRegression_min(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 4,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr   *fcstens_z  = args->arrays[0];
    arr   *obs_z      = args->arrays[1];
    arr   *TC         = args->arrays[2];
    double t_sig      = args->dblp[0];
    double rsq_thresh = args->dblp[1];
    arr   *ms         = args->arrpp[0];
    arr   *bs         = args->arrpp[1];
    arr   *rsqs       = args->arrpp[2];
    arr   *idxs       = args->arrpp[3];

    if (isAnyNonMiss(fcstens_z) && isAnyNonMiss(obs_z)){
        getMultiRegression_min(fcstens_z,obs_z,TC,t_sig,rsq_thresh,ms,bs,rsqs,idxs);
    }
    return;
}

void wrap_getMultiRegression_min_Prescribed(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 4,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 3,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr   *fcstens_z  = args->arrays[0];
    arr   *obs_z      = args->arrays[1];
    arr   *TC         = args->arrays[2];
    arr   *idxs       = args->arrays[3];
    double t_sig      = args->dblp[0];
    double rsq_thresh = args->dblp[1];
    arr   *ms         = args->arrpp[0];
    arr   *bs         = args->arrpp[1];
    arr   *rsqs       = args->arrpp[2];

    if (isAnyNonMiss(fcstens_z) && isAnyNonMiss(obs_z)){
        getMultiRegression_min_Prescribed(fcstens_z,obs_z,TC,idxs,t_sig,rsq_thresh,ms,bs,rsqs);
    }
    return;
}

double wrap_applyMultiRegression(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 4,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    /*
    if (args->idxp_miss){
        for(i=0;i<args->nidxs;i++){
            if (args->idxp[i] == args->idxp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
     */
    arr    *TC     = args->arrays[0];
    arr    *ms     = args->arrays[1];
    arr    *bs     = args->arrays[2];
    arr    *idxs   = args->arrays[3];
    double  fcst_z = args->dblp[0];
    typ_idx napply = args->idxp[0];
    /* Allow pers_z to be missing */
    if (fcst_z == args->dblp_miss[0]){ return *(double *)args->missval; }

    double rv = applyMultiRegression(TC,ms,bs,idxs,fcst_z,napply);
    return rv;
}


void wrap_sortedCDF(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 2,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr  X      = removeMissing(args->arrays[0]);
    arr *X_srtd = args->arrpp[0];
    arr *X_perc = args->arrpp[1];
    
    if (X.tlen){ sortedCDF(&X,X_srtd,X_perc); }
    freeAr(&X);
    return;
}


void wrap_sortedCDF0(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 2,/*nrdbls*/ 1,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr  X       = removeMissing(args->arrays[0]);
    arr *X_srtd  = args->arrpp[0];
    arr *X_perc  = args->arrpp[1];
    double *pct0 = args->dblpp[0];
    
    if (X.tlen){ sortedCDF0(&X,X_srtd,X_perc,pct0); }
    freeAr(&X);
    return;
}



arr wrap_Start2ValidTime(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr *IN = args->arrays[0];
    arr OUT = *(arr *)args->missval;
    if (isAnyNonMiss(IN)){
        OUT = Start2ValidTime(IN);
    }
    return OUT;
}
    
arr wrap_getPersistenceNLeads(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->idxp_miss){
        for(i=0;i<args->nidxs;i++){
            if (args->idxp[i] == args->idxp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }
    arr    *obs = args->arrays[0];
    typ_idx   n = args->idxp[0];

    arr pers = *(arr *)args->missval;
    if (isAnyNonMiss(obs)){
        pers = getPersistenceNLeads(obs,n);
    }
    return pers;
}

arr wrap_getPersistenceNLeads_Lag(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 2,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->idxp_miss){
        for(i=0;i<args->nidxs;i++){
            if (args->idxp[i] == args->idxp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }
    arr    *obs = args->arrays[0];
    typ_idx   n = args->idxp[0];
    typ_idx lag = args->idxp[1];

    arr pers = *(arr *)args->missval;
    if (isAnyNonMiss(obs)){
        pers = getPersistenceNLeads_Lag(obs,n,lag);
    }
    return pers;
}

#endif
