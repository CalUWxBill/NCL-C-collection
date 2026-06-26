/* Created by Bill Scheftic */
#ifndef  _WRAP_STATS_H_
#define  _WRAP_STATS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <stats2.h>

double wrap_st_dbl_1ar(double (*fct)(arr *),input_args *args,typ_idx nneeded, typ_typ *typ_arrs){
    int i;
    double rv;
    /* Check if types are correct */
    int narrs = args->narrs;
    arr **As = malloc(narrs*sizeof *As);
    int *was_casted = malloc(narrs*sizeof *was_casted);
    for (i=0;i<narrs;i++){
        if (typeOf(args->arrays[i]) != *typ_arrs){
        /*  fprintf(stderr,"casting array argument 1 from %s to %s\n",
                    ARR_TYPE_LBLS[typeOf(args->arrays[i])],
                    ARR_TYPE_LBLS[*typ_arrs]);  */
            As[i]  = malloc(sizeof(arr));
            *As[i] = castAr(args->arrays[i],*typ_arrs,0);
            was_casted[i] = 1;
        } else {
            As[i]  = args->arrays[i];
            was_casted[i] = 0;
        }
        typ_arrs++;
    }
    arr  *A = removeMissingNArraysList_alloc(narrs, As);
    if (A[0].tlen < nneeded){
        rv = *(double *)args->missval;
    } else {
        rv = fct(&A[0]);
        if (!isfinite(rv)){ rv = *(double *)args->missval; }
    }
    for (i=0;i<narrs;i++){
        if (was_casted[i]){
            freeAr(As[i]);
            free(As[i]);
        }
        freeAr(&A[i]);
    }
    free(As);
    free(A);
    free(was_casted);
    return rv;
}

int wrap_st_int_1ar(int (*fct)(arr *),input_args *args,typ_idx nneeded, typ_typ *typ_arrs){
    int i;
    int rv;
    /* Check if types are correct */
    int narrs = args->narrs;
    arr **As = malloc(narrs*sizeof *As);
    int *was_casted = malloc(narrs*sizeof *was_casted);
    for (i=0;i<narrs;i++){
        if (typeOf(args->arrays[i]) != *typ_arrs){
        /*  fprintf(stderr,"casting array argument 1 from %s to %s\n",
                    ARR_TYPE_LBLS[typeOf(args->arrays[i])],
                    ARR_TYPE_LBLS[*typ_arrs]);  */
            As[i]  = malloc(sizeof(arr));
            *As[i] = castAr(args->arrays[i],*typ_arrs,0);
            was_casted[i] = 1;
        } else {
            As[i]  = args->arrays[i];
            was_casted[i] = 0;
        }
        typ_arrs++;
    }
    arr  *A = removeMissingNArraysList_alloc(narrs, As);
    if (A[0].tlen < nneeded){
        rv = *(int *)args->missval;
    } else {
        rv = fct(&A[0]);
    }
    for (i=0;i<narrs;i++){
        if (was_casted[i]){
            freeAr(As[i]);
            free(As[i]);
        }
        freeAr(&A[i]);
    }
    free(As);
    free(A);
    free(was_casted);
    return rv;
}

double wrap_st_dbl_2ar(double (*fct)(arr *,arr *),input_args *args,typ_idx nneeded, typ_typ *typ_arrs){
    int i;
    double rv;
    /* Check if types are correct */
    int narrs = args->narrs;
    arr **As = malloc(narrs*sizeof *As);
    int *was_casted = malloc(narrs*sizeof *was_casted);
    for (i=0;i<narrs;i++){
        if (typeOf(args->arrays[i]) != *typ_arrs){
        /*  fprintf(stderr,"casting array argument 1 from %s to %s\n",
                    ARR_TYPE_LBLS[typeOf(args->arrays[i])],
                    ARR_TYPE_LBLS[*typ_arrs]);  */
            As[i]  = malloc(sizeof(arr));
            *As[i] = castAr(args->arrays[i],*typ_arrs,0);
            was_casted[i] = 1;
        } else {
            As[i]  = args->arrays[i];
            was_casted[i] = 0;
        }
        typ_arrs++;
    }
    arr  *A = removeMissingNArraysList_alloc(narrs, As);
    if (A[0].tlen < nneeded){
        rv = *(double *)args->missval;
    } else {
        rv = fct(&A[0],&A[1]);
        if (!isfinite(rv)){ rv = *(double *)args->missval; }
    }
    for (i=0;i<narrs;i++){
        if (was_casted[i]){
            freeAr(As[i]);
            free(As[i]);
        }
        freeAr(&A[i]);
    }
    free(As);
    free(A);
    free(was_casted);
    return rv;
}

double wrap_st_dbl_3ar1d(double (*fct)(arr *,arr *,arr *,double),input_args *args,typ_idx nneeded, typ_typ *typ_arrs){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double rv;
    /* Check if types are correct */
    int narrs = args->narrs;
    arr **As = malloc(narrs*sizeof *As);
    int *was_casted = malloc(narrs*sizeof *was_casted);
    for (i=0;i<narrs;i++){
        if (typeOf(args->arrays[i]) != *typ_arrs){
        /*  fprintf(stderr,"casting array argument 1 from %s to %s\n",
                    ARR_TYPE_LBLS[typeOf(args->arrays[i])],
                    ARR_TYPE_LBLS[*typ_arrs]);  */
            As[i]  = malloc(sizeof(arr));
            *As[i] = castAr(args->arrays[i],*typ_arrs,0);
            was_casted[i] = 1;
        } else {
            As[i]  = args->arrays[i];
            was_casted[i] = 0;
        }
        typ_arrs++;
    }
    arr  *A = removeMissingNArraysList_alloc(narrs, As);
    if (A[0].tlen < nneeded){
        rv = *(double *)args->missval;
    } else {
        double x = args->dblp[0];
        rv = fct(&A[0],&A[1],&A[2],x);
        if (!isfinite(rv)){ rv = *(double *)args->missval; }
    }
    for (i=0;i<narrs;i++){
        if (was_casted[i]){
            freeAr(As[i]);
            free(As[i]);
        }
        freeAr(&A[i]);
    }
    free(As);
    free(A);
    free(was_casted);
    return rv;
}

/* Should do casting and handling of missing values once here rather than a bunch of times within stats2.h */
double wrap_calcValatPerc(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar1d(calcValatPerc,args,1);
}

double wrap_calcPercatVal(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar1d(calcPercatVal,args,1);
}

double wrap_calcValatPercSorted(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar1d(calcValatPercSorted,args,1);
}

double wrap_calcPercatValSorted(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar1d(calcPercatValSorted,args,1);
}

arr wrap_calcValsatPercs(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_2ar(calcValsatPercs,args,1);
}

arr wrap_calcPercsatVals(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_2ar(calcPercsatVals,args,1);
}

arr wrap_calcValsatPercsSorted(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_2ar(calcValsatPercsSorted,args,1);
}

arr wrap_calcPercsatValsSorted(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_2ar(calcPercsatValsSorted,args,1);
}

arr wrap_calcPercentile(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr *P = args->arrays[0];
    return calcPercentile(P);
}

double wrap_calcValatPercWeighted(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar1d(calcValatPercWeighted,args,1);
}

double wrap_calcValatPercFromHist(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar1d(calcValatPercFromHist,args,1);
}

double wrap_Min(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs */ 1,/*ndbls */ 0,/*nints */ 0,/*nidxs */ 0,
                                     /*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)
                      ){ exit(EXIT_FAILURE); }
    static int arr_typs[] = { DOUBLE };
    return wrap_st_dbl_1ar(Min,args,1,arr_typs);
}

double wrap_Max(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs */ 1,/*ndbls */ 0,/*nints */ 0,/*nidxs */ 0,
                                     /*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)
                      ){ exit(EXIT_FAILURE); }
    return wrap_st_dbl_1ar(Max,args,1,(typ_typ []){ DOUBLE });
}

typ_idx wrap_FirstTrue(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_idx_1ar_km(FirstTrue,args);
}

typ_idx wrap_LastTrue(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_idx_1ar_km(LastTrue,args);
}

typ_idx wrap_MinIdx(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_idx_1ar_km(MinIdx,args);
}

typ_idx wrap_MaxIdx(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_idx_1ar_km(MaxIdx,args);
}

typ_idx wrap_ClosestIdx(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_idx_1ar1d(ClosestIdx,args,1);
}

double wrap_IdxFromVal(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar1d(IdxFromVal,args,1);
}

double wrap_ValFromIdx(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar1d(ValFromIdx,args,1);
}

int wrap_intMode(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_int_1ar(intMode,args,1);
}

arr wrap_intModes(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_1ar(intModes,args,1);
}

int wrap_Logical_All(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs */ 1,/*ndbls */ 0,/*nints */ 0,/*nidxs */ 0,
                                     /*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)
                      ){ exit(EXIT_FAILURE); }
    static int arr_typs[] = { INT };
    return wrap_st_int_1ar(Logical_All,args,1,arr_typs);
}

int wrap_Logical_Any(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs */ 1,/*ndbls */ 0,/*nints */ 0,/*nidxs */ 0,
                                     /*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)
                      ){ exit(EXIT_FAILURE); }
    static int arr_typs[] = { INT };
    return wrap_st_int_1ar(Logical_Any,args,1,arr_typs);
}


double wrap_PiMult(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(PiMult,args,1);
}

double wrap_Zeros(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(Zeros,args,1);
}

double wrap_doyTrend(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(doyTrend,args,3);
}

double wrap_doyTrendR(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(doyTrendR,args,3);
}

double wrap_doyLength(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(doyLength,args,2);
}

double wrap_doyMean(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(doyMean,args,1);
}

double wrap_cyclicMean(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar1d(cyclicMean,args,1);
}

double wrap_cyclicStdDev(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar1d(cyclicStdDev,args,1);
}

double wrap_Mean(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(my_Mean,args,1);
}

double wrap_Median(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(Median,args,1);
}

double wrap_wMean(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
/*    return wrap_dbl_2ar(wMean,args,1); */
    return wrap_st_dbl_2ar(wMean,args,1,(typ_typ []){ DOUBLE, DOUBLE });
}

double wrap_devMoment(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar1i(devMoment,args,3);
}

double wrap_Moment(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar1i(Moment,args,1);
}

double wrap_devXY(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(devXY,args,2);
}

double wrap_XY(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(XY,args,1);
}

arr wrap_StdAnom(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr *P = args->arrays[0];
    return StdAnom(P);
}

arr wrap_RunningMedian(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr    *P   = args->arrays[0];
    typ_idx len = args->idxp[0];
    if (countNonMiss(P)<len){
        arr Ret = copyAr(P);
        fillArWithMiss(&Ret);
        return Ret;
    } else if (len < 3) {
        return copyAr(P);
    } else {
        return RunningMedian(P,len);
    }
}

arr wrap_RunningMean(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr    *P   = args->arrays[0];
    typ_idx len = args->idxp[0];
    if (countNonMiss(P)<len){
        arr Ret = copyAr(P);
        fillArWithMiss(&Ret);
        return Ret;
    } else if (len < 3) {
        return copyAr(P);
    } else {
        return RunningMean(P,len);
    }
}

arr wrap_RunningRegr(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr    *P   = args->arrays[0];
    typ_idx len = args->idxp[0];
    if (isAnyNonMiss(P)){
        return RunningRegr(P,len);
    } else {
        return *(arr *)args->missval;
    }
}

arr wrap_RunningMean_End(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr    *P   = args->arrays[0];
    typ_idx len = args->idxp[0];
    if (isAnyNonMiss(P)){
        return RunningMean_End(P,len);
    } else {
        return *(arr *)args->missval;
    }
}

arr wrap_RunningSlope_End(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr    *X   = args->arrays[0];
    arr    *Y   = args->arrays[1];
    typ_idx len = args->idxp[0];
    if (isAnyNonMiss(X)&&isAnyNonMiss(Y)){
        return RunningSlope_End(X,Y,len);
    } else {
        return *(arr *)args->missval;
    }
}



arr wrap_RunningWeightedMean(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr *P = args->arrays[0];
    arr *W = args->arrays[1];
    if (isAnyNonMiss(P)){
        return RunningWeightedMean(P,W);
    } else {
        return *(arr *)args->missval;
    }
}

arr wrap_RunningWeightedPercentileNoMean(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr *P = args->arrays[0];
    arr *W = args->arrays[1];
    double perc = args->dblp[0];
    if (isAnyNonMiss(P)){
        return RunningWeightedPercentileNoMean(P,W,perc);
    } else {
        return *(arr *)args->missval;
    }
}

arr wrap_RunningWeightedPercentile(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr *X    = args->arrays[0];
    arr *Xbar = args->arrays[1];
    arr *W    = args->arrays[2];
    double perc = args->dblp[0];
    if (isAnyNonMiss(X)){
        return RunningWeightedPercentile(X,Xbar,W,perc);
    } else {
        return *(arr *)args->missval;
    }
}

arr wrap_RunningWeightedPercentiles(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 4,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr *X     = args->arrays[0];
    arr *Xbar  = args->arrays[1];
    arr *W     = args->arrays[2];
    arr *percs = args->arrays[3];
    if (isAnyNonMiss(X)){
        return RunningWeightedPercentiles(X,Xbar,W,percs);
    } else {
        return *(arr *)args->missval;
    }
}


double wrap_calcBias(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(calcBias,args,1);
}

double wrap_calcRelBias(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(calcRelBias,args,1);
}

double wrap_calcMAE(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(calcMAE,args,1);
}

double wrap_calcMSD(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(calcMSD,args,1);
}

double wrap_calcRMSD(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(calcRMSD,args,1);
}

double wrap_calcSSD(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(calcSSD,args,1);
}

double wrap_dist_multigausswgt(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(dist_multigausswgt,args,1);
}

double wrap_dist_gausswgt(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(dist_gausswgt,args);
}

double wrap_dist_gausswgt_ave(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(dist_gausswgt_ave,args,1);
}

double wrap_dist_gausswgt_ave_h2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar1d(dist_gausswgt_ave_h2,args,1);
}

double wrap_dist_gausswgt_wave(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3ar(dist_gausswgt_wave,args,1);
}

double wrap_dist_gausswgt_wave_h2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3ar1d(dist_gausswgt_wave_h2,args,1);
}

double wrap_WdevMoment(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar1i(WdevMoment,args,3);
}

double wrap_WMoment(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar1i(WMoment,args,1);
}

double wrap_VarP(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(VarP,args,2);
}

double wrap_SkewP(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(SkewP,args,3);
}

double wrap_KurtP(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(KurtP,args,4);
}

double wrap_normVarP(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(normVarP,args,2);
}

double wrap_normSkewP(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(normSkewP,args,3);
}

double wrap_normKurtP(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(normKurtP,args,4);
}

double wrap_stdDevP(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(stdDevP,args,2);
}

double wrap_VarS(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(VarS,args,2);
}

double wrap_SkewS(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(SkewS,args,3);
}

double wrap_KurtS(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(KurtS,args,4);
}

double wrap_normVarS(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(normVarS,args,2);
}

double wrap_normSkewS(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(normSkewS,args,3);
}

double wrap_normKurtS(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(normKurtS,args,4);
}

double wrap_stdDevS(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(stdDevS,args,2);
}

double wrap_WstdDevS(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(WstdDevS,args,2);
}

double wrap_WKurt(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(WKurt,args,4);
}

double wrap_sampleStat(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(sampleStat,args,4);
}

double wrap_shapeParam(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(shapeParam,args,4);
}

double wrap_scaleParam(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(scaleParam,args,4);
}

void wrap_RegrRef(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 4,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_2ar_r4d(RegrRef,args,3);
}

void wrap_RegrRef_TheilSen(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 4,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_2ar_r4d(RegrRef_TheilSen,args,3);
}

double wrap_lagCorr(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar(lagCorr,args,3);
}

double wrap_lagCorrN(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar1i(lagCorrN,args,1);
}

double wrap_Corr(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(Corr,args,3);
}

double wrap_calcRSquared(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(calcRSquared,args,3);
}

double wrap_calcRSq_OLSCV(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(RSq_OLSCV,args,7);
}

double wrap_calcRSq_OLSCV_nout(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar1x(RSq_OLSCV_nout,args,7);
}

double wrap_calcRSq_OLSFV_nout(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar1x(RSq_OLSFV_nout,args,15);
}

double wrap_calcRSq_OLSFV_nlast(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar1x(RSq_OLSFV_nlast,args,15);
}

double wrap_combined_predictor_index(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
/*    return wrap_dbl_2ar(wMean,args,1); */
    return wrap_st_dbl_3ar1d(combined_predictor_index,args,1,(typ_typ []){ DOUBLE, DOUBLE, DOUBLE });
}


double wrap_PCorr(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3ar(PCorr,args,1);
}

double wrap_SPCorr(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3ar(SPCorr,args,1);
}

double wrap_orthoRegr(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(orthoRegr,args,3);
}

double wrap_Cov(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ar(Cov,args,3);
}

#endif
