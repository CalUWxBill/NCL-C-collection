#ifndef  _WRAP_GSL_STATS_H_
#define  _WRAP_GSL_STATS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <gsl/gsl_statistics.h>

double wrap_gsl_stats_1ar(double (*fct)(const double [], const size_t, const size_t),input_args *args,typ_idx nneeded){
    int i;
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(double *)args->missval;
    } else {
        rv = fct(pntr_of(&A[0]), 1, A[0].tlen);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_gsl_stats_mean(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar(gsl_stats_mean,args,1);
}

double wrap_gsl_stats_variance(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar(gsl_stats_variance,args,1);
}

double wrap_gsl_stats_sd(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar(gsl_stats_sd,args,1);
}

double wrap_gsl_stats_tss(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar(gsl_stats_tss,args,1);
}

double wrap_gsl_stats_absdev(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar(gsl_stats_absdev,args,1);
}

double wrap_gsl_stats_skew(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar(gsl_stats_skew,args,1);
}

double wrap_gsl_stats_kurtosis(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar(gsl_stats_kurtosis,args,1);
}

double wrap_gsl_stats_lag1_autocorrelation(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar(gsl_stats_lag1_autocorrelation,args,1);
}

double wrap_gsl_stats_max(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar(gsl_stats_max,args,1);
}

double wrap_gsl_stats_min(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar(gsl_stats_min,args,1);
}

double wrap_gsl_stats_median_from_sorted_data(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar(gsl_stats_median_from_sorted_data,args,1);
}

double wrap_gsl_stats_median(input_args *args){
    /* This function will sort the input arrays which we probably don't want */
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar(gsl_stats_median,args,1);
}

double wrap_gsl_stats_gastwirth_from_sorted_data(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar(gsl_stats_gastwirth_from_sorted_data,args,1);
}


void wrap_gsl_stats_1ar_r2d(void (*fct)(double *, double *, const double [], const size_t, const size_t),input_args *args,typ_idx nneeded){
    int i;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        fct(pdbl0, pdbl1, pntr_of(&A[0]), 1, A[0].tlen);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_gsl_stats_minmax(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 2,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar_r2d(gsl_stats_minmax,args,1);
}


double wrap_gsl_stats_2ar(double (*fct)(const double [], const size_t, const double [], const size_t, const size_t),input_args *args,typ_idx nneeded){
    int i;
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(double *)args->missval;
    } else {
        rv = fct(pntr_of(&A[0]), 1, pntr_of(&A[1]), 1, A[0].tlen);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_gsl_stats_covariance(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar(gsl_stats_covariance,args,1);
}

double wrap_gsl_stats_correlation(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar(gsl_stats_correlation,args,1);
}

double wrap_gsl_stats_wmean(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar(gsl_stats_wmean,args,1);
}

double wrap_gsl_stats_wvariance(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar(gsl_stats_wvariance,args,1);
}

double wrap_gsl_stats_wsd(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar(gsl_stats_wsd,args,1);
}

double wrap_gsl_stats_wtss(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar(gsl_stats_wtss,args,1);
}

double wrap_gsl_stats_wabsdev(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar(gsl_stats_wabsdev,args,1);
}

double wrap_gsl_stats_wskew(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar(gsl_stats_wskew,args,1);
}

double wrap_gsl_stats_wkurtosis(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar(gsl_stats_wkurtosis,args,1);
}


double wrap_gsl_stats_1ar_work(double (*fct)(const double [], const size_t, const size_t, double []),input_args *args,typ_idx nneeded){
    int i;
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(double *)args->missval;
    } else {
        typ_idx n = A[0].tlen;
        double *work = malloc(n*sizeof(double));
        rv = fct(pntr_of(&A[0]), 1, n, work);
        free(work);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_gsl_stats_mad0(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar_work(gsl_stats_mad0,args,1);
}

double wrap_gsl_stats_mad(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar_work(gsl_stats_mad,args,1);
}

double wrap_gsl_stats_Sn0_from_sorted_data(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar_work(gsl_stats_Sn0_from_sorted_data,args,1);
}

double wrap_gsl_stats_Sn_from_sorted_data(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar_work(gsl_stats_Sn_from_sorted_data,args,1);
}


double wrap_gsl_stats_1ar_Qn(double (*fct)(const double [], const size_t, const size_t, double [], int []),input_args *args,typ_idx nneeded){
    int i;
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(double *)args->missval;
    } else {
        typ_idx n = A[0].tlen;
        double *work  = malloc(3*n*sizeof(double));
        int *work_int = malloc(5*n*sizeof(int));
        rv = fct(pntr_of(&A[0]), 1, n, work, work_int);
        free(work);
        free(work_int);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_gsl_stats_Qn0_from_sorted_data(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar_Qn(gsl_stats_Qn0_from_sorted_data,args,1);
}

double wrap_gsl_stats_Qn_from_sorted_data(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar_Qn(gsl_stats_Qn_from_sorted_data,args,1);
}


double wrap_gsl_stats_1ar1d(double (*fct)(const double [], const size_t, const size_t, double),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(double *)args->missval;
    } else {
        double  dbl0  = args->dblp[0];
        rv = fct(pntr_of(&A[0]), 1, A[0].tlen, dbl0);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_gsl_stats_quantile_from_sorted_data(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar1d(gsl_stats_quantile_from_sorted_data,args,1);
}

double wrap_gsl_stats_variance_m(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar1d(gsl_stats_variance_m,args,1);
}

double wrap_gsl_stats_sd_m(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar1d(gsl_stats_sd_m,args,1);
}

double wrap_gsl_stats_tss_m(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar1d(gsl_stats_tss_m,args,1);
}

double wrap_gsl_stats_variance_with_fixed_mean(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar1d(gsl_stats_variance_with_fixed_mean,args,1);
}

double wrap_gsl_stats_sd_with_fixed_mean(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar1d(gsl_stats_sd_with_fixed_mean,args,1);
}

double wrap_gsl_stats_absdev_m(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar1d(gsl_stats_absdev_m,args,1);
}

double wrap_gsl_stats_lag1_autocorrelation_m(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar1d(gsl_stats_lag1_autocorrelation_m,args,1);
}


double wrap_gsl_stats_1d1ar(double (*fct)(const double, const double [], const size_t, const size_t),input_args *args,typ_idx nneeded){
    /* Still pass in args in same order as 1ar1d, just this passes to gsl function in reverse order */
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(double *)args->missval;
    } else {
        double  dbl0  = args->dblp[0];
        rv = fct(dbl0, pntr_of(&A[0]), 1, A[0].tlen);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_gsl_stats_trmean_from_sorted_data(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1d1ar(gsl_stats_trmean_from_sorted_data,args,1);
}


double wrap_gsl_stats_1ar2d(double (*fct)(const double [], const size_t, const size_t, double, double),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(double *)args->missval;
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        rv = fct(pntr_of(&A[0]), 1, A[0].tlen, dbl0, dbl1);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_gsl_stats_skew_m_sd(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar2d(gsl_stats_skew_m_sd,args,1);
}

double wrap_gsl_stats_kurtosis_m_sd(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_1ar2d(gsl_stats_kurtosis_m_sd,args,1);
}


double wrap_gsl_stats_2ar1d(double (*fct)(const double [], const size_t, const double [], const size_t, const size_t, double),
    input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(double *)args->missval;
    } else {
        double  dbl0  = args->dblp[0];
        rv = fct(pntr_of(&A[0]), 1, pntr_of(&A[1]), 1, A[0].tlen, dbl0);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_gsl_stats_wvariance_m(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar1d(gsl_stats_wvariance_m,args,1);
}

double wrap_gsl_stats_wsd_m(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar1d(gsl_stats_wsd_m,args,1);
}

double wrap_gsl_stats_wvariance_with_fixed_mean(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar1d(gsl_stats_wvariance_with_fixed_mean,args,1);
}

double wrap_gsl_stats_wsd_with_fixed_mean(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar1d(gsl_stats_wsd_with_fixed_mean,args,1);
}

double wrap_gsl_stats_wtss_m(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar1d(gsl_stats_wtss_m,args,1);
}

double wrap_gsl_stats_wabsdev_m(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar1d(gsl_stats_wabsdev_m,args,1);
}


double wrap_gsl_stats_2ar2d(double (*fct)(const double [], const size_t, const double [], const size_t, const size_t, double, double),
    input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(double *)args->missval;
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        rv = fct(pntr_of(&A[0]), 1, pntr_of(&A[1]), 1, A[0].tlen, dbl0, dbl1);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_gsl_stats_covariance_m(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar2d(gsl_stats_covariance_m,args,1);
}

double wrap_gsl_stats_wskew_m_sd(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar2d(gsl_stats_wskew_m_sd,args,1);
}

double wrap_gsl_stats_wkurtosis_m_sd(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar2d(gsl_stats_wkurtosis_m_sd,args,1);
}


double wrap_gsl_stats_2ar_work(double (*fct)(const double [], const size_t, const double [], const size_t, const size_t, double []),
    input_args *args,typ_idx nneeded,int wrkmlt){
    int i;
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(double *)args->missval;
    } else {
        typ_idx n = A[0].tlen;
        double *work = malloc(wrkmlt*n*sizeof(double));
        rv = fct(pntr_of(&A[0]), 1, pntr_of(&A[1]), 1, n, work);
        free(work);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_gsl_stats_spearman(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_stats_2ar_work(gsl_stats_spearman,args,1,2);
}


#endif
