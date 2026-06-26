/* Created by Bill Scheftic */
#include <stdio.h>
/*
 * The following are the required NCAR Graphics include files.
 * They should be located in ${NCARG_ROOT}/include
 */

#include <ncl_c_wrap.h>		/* Contains all included headers, Type conversion Macros, and getVarFromNCL function */
#include <arrayinit2.h>
#include <stats2.h>
#include <arraystats2.h>
#include <print_arrays2.h>
#include <ncl_stateq.h>

/* dbl func(arr) */
NhlErrorTypes ncl_c_doylen_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_doyLength,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_doymean_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_doyMean,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_pimult_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_PiMult,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_median_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_Median,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_mean_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_Mean,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_min_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_Min,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_max_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_Max,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_varp_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_VarP,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_vars_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_VarS,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_skewp_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_SkewP,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_skews_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_SkewS,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_kurtp_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_KurtP,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_kurts_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_KurtS,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_normvarp_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_normVarP,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_normvars_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_normVarS,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_normskewp_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_normSkewP,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_normskews_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_normSkewS,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_normkurtp_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_normKurtP,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_normkurts_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_normKurtS,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_stddevp_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_stdDevP,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_stddevs_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_stdDevS,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_samplestat_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_sampleStat,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_shapeparam_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_shapeParam,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_scaleparam_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_scaleParam,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_zeros_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_Zeros,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_lagcorr_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_lagCorr,1,0,0,0);
  return retval;
}


NhlErrorTypes ncl_c_StdAnom_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNint(wrap_StdAnom,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_Percentile_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNint(wrap_calcPercentile,1,0,0,0);
  return retval;
}


/* dbl func(arr, arr) */
NhlErrorTypes ncl_c_orthoslope_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_orthoRegr,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_doytrendr_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_doyTrendR,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_doytrend_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_doyTrend,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_wmean_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_wMean,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_wstddev_s_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_WstdDevS,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_wkurt_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_WKurt,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_covar_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_Cov,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_corr_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_Corr,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_r_squared_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_calcRSquared,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_rsq_ols_cv_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_calcRSq_OLSCV,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_devxy_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_devXY,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_xy_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_XY,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_bias_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_calcBias,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_relbias_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_calcRelBias,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_msd_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_calcMSD,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_rmsd_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_calcRMSD,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_mae_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_calcMAE,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_ssd_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_calcSSD,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_dist_multigausswgt_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_dist_multigausswgt,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_dist_gausswgt_ave_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_dist_gausswgt_ave,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_dist_gausswgt_ave_h2_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_dist_gausswgt_ave_h2,3,0,0,0);
  return retval;
}




NhlErrorTypes ncl_c_dist_gausswgt_wave_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_dist_gausswgt_wave,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_dist_gausswgt_wave_h2_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_dist_gausswgt_wave_h2,4,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_dist_gausswgt_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_dist_gausswgt,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_combined_predictor_index_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_combined_predictor_index,4,0,0,0);
  return retval;
}


NhlErrorTypes ncl_c_valatperc_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_calcValatPerc,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_percatval_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_calcPercatVal,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_valatpercsrtd_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_calcValatPercSorted,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_percatvalsrtd_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_calcPercatValSorted,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_valsatpercs_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNint_Maps(wrap_calcValsatPercs,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_percsatvals_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNint_Maps(wrap_calcPercsatVals,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_valsatpercssrtd_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNint_Maps(wrap_calcValsatPercsSorted,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_percsatvalssrtd_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNint_Maps(wrap_calcPercsatValsSorted,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_valfromidx_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_ValFromIdx,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_idxfromval_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_IdxFromVal,2,0,0,0);
  return retval;
}


/* dbl func(arr, arr, arr) */
NhlErrorTypes ncl_c_cyclicMean_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_cyclicMean,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_cyclicStdDev_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_cyclicStdDev,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_calcValatPercFromHist_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_calcValatPercFromHist,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_calcValatPercWeighted_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_calcValatPercWeighted,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_Pcorr_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_PCorr,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_SPcorr_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_SPCorr,3,0,0,0);
  return retval;
}


/* typ_idx func(arr) */
NhlErrorTypes ncl_c_firstidx_W( void ) {
  NhlErrorTypes retval = st_idx_eqNarRNarNdblNintNidx(wrap_FirstTrue,1,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_lastidx_W( void ) {
  NhlErrorTypes retval = st_idx_eqNarRNarNdblNintNidx(wrap_LastTrue,1,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_maxind_n_W( void ) {
  NhlErrorTypes retval = st_idx_eqNarRNarNdblNintNidx(wrap_MaxIdx,1,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_minind_n_W( void ) {
  NhlErrorTypes retval = st_idx_eqNarRNarNdblNintNidx(wrap_MinIdx,1,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_intmode_W( void ) {
  NhlErrorTypes retval = st_int_eqNarRNarNdblNint(wrap_intMode,1,0,0,0);
  return retval;
}


/* typ_idx func(arr,arr) */
NhlErrorTypes ncl_c_closestind_n_W( void ) {
  NhlErrorTypes retval = st_idx_eqNarRNarNdblNintNidx_Maps(wrap_ClosestIdx,2,0,0,0,0);
  return retval;
}


/* dbl func(arr, int) */
NhlErrorTypes ncl_c_devmoment_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_devMoment,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_moment_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_Moment,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_lagcorrn_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_lagCorrN,2,0,0,0);
  return retval;
}


/* dbl func(arr, arr, int) */
NhlErrorTypes ncl_c_wdevmoment_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_WdevMoment,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_wmoment_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_WMoment,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_rsq_ols_cv_n_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNintNidx_Maps(wrap_calcRSq_OLSCV_nout,3,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_rsq_ols_fv_n_W( void ) {
  /* NhlErrorTypes retval = st_dbl_eqNarRNarNdblNintNidx_Maps(wrap_calcRSq_OLSFV_nout,3,0,0,0,0); */
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNintNidx_Maps(wrap_calcRSq_OLSFV_nlast,3,0,0,0,0);
  return retval;
}


/* func(arr, arr, double *, double *, double *, double *) */
NhlErrorTypes ncl_c_RegrRef_W( void ) {
    NhlErrorTypes retval = st_eqNarRNarNdblNint_Maps(wrap_RegrRef,2,0,4,0);
    return retval;
}

NhlErrorTypes ncl_c_RegrRef_TheilSen_W( void ) {
    NhlErrorTypes retval = st_eqNarRNarNdblNint_Maps(wrap_RegrRef_TheilSen,2,0,4,0);
    return retval;
}


NhlErrorTypes ncl_c_RunningMedian_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx_Maps(wrap_RunningMedian,2,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_RunningMean_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx_Maps(wrap_RunningMean,2,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_RunningRegr_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx_Maps(wrap_RunningRegr,2,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_RunningMean_End_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx_Maps(wrap_RunningMean_End,2,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_RunningSlope_End_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx_Maps(wrap_RunningSlope_End,3,0,0,0,0);
  return retval;
}


NhlErrorTypes ncl_c_RunningWeightedMean_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx_Maps(wrap_RunningWeightedMean,2,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_RunningWeightedPercentileNoMean_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx_Maps(wrap_RunningWeightedPercentileNoMean,3,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_RunningWeightedPercentile_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx_Maps(wrap_RunningWeightedPercentile,4,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_RunningWeightedPercentiles_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx_Maps(wrap_RunningWeightedPercentiles,4,0,0,0,0);
  return retval;
}




void Init(void){
  void *args;
  int nargs;
  fprintf(stderr,"Init: Initializing ncl_stats functions ...\n");

/*
 * Register 2 variable functions.
 */
  nargs = 0;
  args = NewArgs(3);

  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;

  NclRegisterFunc(ncl_c_dist_gausswgt_W,  args,"ncl_c_dist_gausswgt",  nargs);
  fprintf(stderr,"Init: ncl_stats 1\n");

/*
 * Register functions accepting 1 n dimensional double array and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(2);

  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */

  NclRegisterFunc(ncl_c_doylen_W,    args,"ncl_c_doylen",    nargs); fprintf(stderr,"Init: ncl_stats ncl_c_doylen    \n");
  NclRegisterFunc(ncl_c_doymean_W,   args,"ncl_c_doymean",   nargs); fprintf(stderr,"Init: ncl_stats ncl_c_doymean   \n");
  NclRegisterFunc(ncl_c_pimult_W,    args,"ncl_c_pimult",    nargs); fprintf(stderr,"Init: ncl_stats ncl_c_pimult    \n");
  NclRegisterFunc(ncl_c_median_W,    args,"ncl_c_median",    nargs); fprintf(stderr,"Init: ncl_stats ncl_c_median    \n");
  NclRegisterFunc(ncl_c_mean_W,      args,"ncl_c_mean",      nargs); fprintf(stderr,"Init: ncl_stats ncl_c_mean      \n");
  NclRegisterFunc(ncl_c_min_W,       args,"ncl_c_min",       nargs); fprintf(stderr,"Init: ncl_stats ncl_c_min       \n");
  NclRegisterFunc(ncl_c_max_W,       args,"ncl_c_max",       nargs); fprintf(stderr,"Init: ncl_stats ncl_c_max       \n");
  NclRegisterFunc(ncl_c_varp_W,      args,"ncl_c_varp",      nargs); fprintf(stderr,"Init: ncl_stats ncl_c_varp      \n");
  NclRegisterFunc(ncl_c_vars_W,      args,"ncl_c_vars",      nargs); fprintf(stderr,"Init: ncl_stats ncl_c_vars      \n");
  NclRegisterFunc(ncl_c_skewp_W,     args,"ncl_c_skewp",     nargs); fprintf(stderr,"Init: ncl_stats ncl_c_skewp     \n");
  NclRegisterFunc(ncl_c_skews_W,     args,"ncl_c_skews",     nargs); fprintf(stderr,"Init: ncl_stats ncl_c_skews     \n");
  NclRegisterFunc(ncl_c_kurtp_W,     args,"ncl_c_kurtp",     nargs); fprintf(stderr,"Init: ncl_stats ncl_c_kurtp     \n");
  NclRegisterFunc(ncl_c_kurts_W,     args,"ncl_c_kurts",     nargs); fprintf(stderr,"Init: ncl_stats ncl_c_kurts     \n");
  NclRegisterFunc(ncl_c_normvarp_W,  args,"ncl_c_normvarp",  nargs); fprintf(stderr,"Init: ncl_stats ncl_c_normvarp  \n");
  NclRegisterFunc(ncl_c_normvars_W,  args,"ncl_c_normvars",  nargs); fprintf(stderr,"Init: ncl_stats ncl_c_normvars  \n");
  NclRegisterFunc(ncl_c_normskewp_W, args,"ncl_c_normskewp", nargs); fprintf(stderr,"Init: ncl_stats ncl_c_normskewp \n");
  NclRegisterFunc(ncl_c_normskews_W, args,"ncl_c_normskews", nargs); fprintf(stderr,"Init: ncl_stats ncl_c_normskews \n");
  NclRegisterFunc(ncl_c_normkurtp_W, args,"ncl_c_normkurtp", nargs); fprintf(stderr,"Init: ncl_stats ncl_c_normkurtp \n");
  NclRegisterFunc(ncl_c_normkurts_W, args,"ncl_c_normkurts", nargs); fprintf(stderr,"Init: ncl_stats ncl_c_normkurts \n");
  NclRegisterFunc(ncl_c_stddevp_W,   args,"ncl_c_stddevp",   nargs); fprintf(stderr,"Init: ncl_stats ncl_c_stddevp   \n");
  NclRegisterFunc(ncl_c_stddevs_W,   args,"ncl_c_stddevs",   nargs); fprintf(stderr,"Init: ncl_stats ncl_c_stddevs   \n");
  NclRegisterFunc(ncl_c_samplestat_W,args,"ncl_c_samplestat",nargs); fprintf(stderr,"Init: ncl_stats ncl_c_samplestat\n");
  NclRegisterFunc(ncl_c_shapeparam_W,args,"ncl_c_shapeparam",nargs); fprintf(stderr,"Init: ncl_stats ncl_c_shapeparam\n");
  NclRegisterFunc(ncl_c_scaleparam_W,args,"ncl_c_scaleparam",nargs); fprintf(stderr,"Init: ncl_stats ncl_c_scaleparam\n");
  NclRegisterFunc(ncl_c_zeros_W,     args,"ncl_c_zeros",     nargs); fprintf(stderr,"Init: ncl_stats ncl_c_zeros     \n");
  NclRegisterFunc(ncl_c_lagcorr_W,   args,"ncl_c_lagcorr",   nargs); fprintf(stderr,"Init: ncl_stats ncl_c_lagcorr   \n");
  NclRegisterFunc(ncl_c_StdAnom_W,   args,"ncl_c_stdanom",   nargs); fprintf(stderr,"Init: ncl_stats ncl_c_stdanom   \n");   /* Returns arr */
  NclRegisterFunc(ncl_c_Percentile_W,args,"ncl_c_percentile",nargs); fprintf(stderr,"Init: ncl_stats ncl_c_percentile\n");   /* Returns arr */
  NclRegisterFunc(ncl_c_maxind_n_W,  args,"ncl_c_maxind_n",  nargs); fprintf(stderr,"Init: ncl_stats ncl_c_maxind_n  \n");   /* Returns int64 */
  NclRegisterFunc(ncl_c_minind_n_W,  args,"ncl_c_minind_n",  nargs); fprintf(stderr,"Init: ncl_stats ncl_c_minind_n  \n");   /* Returns int64 */
  fprintf(stderr,"Init: ncl_stats 2\n");

/*
 * Register functions accepting 1 n dimensional double array and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(2);

  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */

  NclRegisterFunc(ncl_c_firstidx_W, args,"ncl_c_firstidx", nargs);    /* Returns int64 */
  NclRegisterFunc(ncl_c_lastidx_W,  args,"ncl_c_lastidx",  nargs);    /* Returns int64 */
  fprintf(stderr,"Init: ncl_stats 3\n");

/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_orthoslope_W,        args,"ncl_c_orthoslope"        ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_orthoslope        \n");
  NclRegisterFunc(ncl_c_doytrendr_W,         args,"ncl_c_doytrendr"         ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_doytrendr         \n");
  NclRegisterFunc(ncl_c_doytrend_W,          args,"ncl_c_doytrend"          ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_doytrend          \n");
  NclRegisterFunc(ncl_c_wmean_W,             args,"ncl_c_wmean"             ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_wmean             \n");
  NclRegisterFunc(ncl_c_wstddev_s_W,         args,"ncl_c_wstddev_s"         ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_wstddev_s         \n");
  NclRegisterFunc(ncl_c_wkurt_W,             args,"ncl_c_wkurt"             ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_wkurt             \n");
  NclRegisterFunc(ncl_c_covar_W,             args,"ncl_c_covar"             ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_covar             \n");
  NclRegisterFunc(ncl_c_corr_W,              args,"ncl_c_corr"              ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_corr              \n");
  NclRegisterFunc(ncl_c_r_squared_W,         args,"ncl_c_r_squared"         ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_r_squared         \n");
  NclRegisterFunc(ncl_c_rsq_ols_cv_W,        args,"ncl_c_rsq_ols_cv"        ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_rsq_ols_cv        \n");
  NclRegisterFunc(ncl_c_devxy_W,             args,"ncl_c_devxy"             ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_devxy             \n");
  NclRegisterFunc(ncl_c_xy_W,                args,"ncl_c_xy"                ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_xy                \n");
  NclRegisterFunc(ncl_c_bias_W,              args,"ncl_c_bias"              ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_bias              \n");
  NclRegisterFunc(ncl_c_relbias_W,           args,"ncl_c_relbias"           ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_relbias           \n");
  NclRegisterFunc(ncl_c_msd_W,               args,"ncl_c_msd"               ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_msd               \n");
  NclRegisterFunc(ncl_c_rmsd_W,              args,"ncl_c_rmsd"              ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_rmsd              \n");
  NclRegisterFunc(ncl_c_mae_W,               args,"ncl_c_mae"               ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_mae               \n");
  NclRegisterFunc(ncl_c_ssd_W,               args,"ncl_c_ssd"               ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_ssd               \n");
  NclRegisterFunc(ncl_c_dist_multigausswgt_W,args,"ncl_c_dist_multigausswgt",nargs); fprintf(stderr,"Init: ncl_stats ncl_c_dist_multigausswgt\n");
  NclRegisterFunc(ncl_c_dist_gausswgt_ave_W, args,"ncl_c_dist_gausswgt_ave" ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_dist_gausswgt_ave \n");
  NclRegisterFunc(ncl_c_valatperc_W,         args,"ncl_c_valatperc"         ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_valatperc         \n");
  NclRegisterFunc(ncl_c_percatval_W,         args,"ncl_c_percatval"         ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_percatval         \n");
  NclRegisterFunc(ncl_c_valatpercsrtd_W,     args,"ncl_c_valatpercsrtd"     ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_valatpercsrtd     \n");
  NclRegisterFunc(ncl_c_percatvalsrtd_W,     args,"ncl_c_percatvalsrtd"     ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_percatvalsrtd     \n");
  NclRegisterFunc(ncl_c_valsatpercs_W,       args,"ncl_c_valsatpercs"       ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_valsatpercs       \n"); /* Returns arr */
  NclRegisterFunc(ncl_c_percsatvals_W,       args,"ncl_c_percsatvals"       ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_percsatvals       \n"); /* Returns arr */
  NclRegisterFunc(ncl_c_valsatpercssrtd_W,   args,"ncl_c_valsatpercssrtd"   ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_valsatpercssrtd   \n"); /* Returns arr */
  NclRegisterFunc(ncl_c_percsatvalssrtd_W,   args,"ncl_c_percsatvalssrtd"   ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_percsatvalssrtd   \n"); /* Returns arr */
  NclRegisterFunc(ncl_c_valfromidx_W,        args,"ncl_c_valfromidx"        ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_valfromidx        \n");
  NclRegisterFunc(ncl_c_idxfromval_W,        args,"ncl_c_idxfromval"        ,nargs); fprintf(stderr,"Init: ncl_stats ncl_c_idxfromval        \n");

  NclRegisterFunc(ncl_c_closestind_n_W,args,"ncl_c_closestind_n",nargs);		/* Returns int64 */
  fprintf(stderr,"Init: ncl_stats 4\n");
  
/*
 * Register functions accepting 3 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_cyclicMean_W           ,args,"ncl_c_cyclicMean"           ,nargs);
  NclRegisterFunc(ncl_c_cyclicStdDev_W         ,args,"ncl_c_cyclicStdDev"         ,nargs);
  NclRegisterFunc(ncl_c_calcValatPercFromHist_W,args,"ncl_c_calcValatPercFromHist",nargs);
  NclRegisterFunc(ncl_c_calcValatPercWeighted_W,args,"ncl_c_calcValatPercWeighted",nargs);
  NclRegisterFunc(ncl_c_Pcorr_W                ,args,"ncl_c_pcorr"                ,nargs);
  NclRegisterFunc(ncl_c_SPcorr_W               ,args,"ncl_c_spcorr"               ,nargs);
  NclRegisterFunc(ncl_c_dist_gausswgt_wave_W   ,args,"ncl_c_dist_gausswgt_wave"   ,nargs);
  NclRegisterFunc(ncl_c_dist_gausswgt_ave_h2_W ,args,"ncl_c_dist_gausswgt_ave_h2" ,nargs);
  fprintf(stderr,"Init: ncl_stats 5\n");

/*
 * Register functions accepting 3 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(6);

  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_dist_gausswgt_wave_h2_W   ,args,"ncl_c_dist_gausswgt_wave_h2"   ,nargs);
  NclRegisterFunc(ncl_c_combined_predictor_index_W,args,"ncl_c_combined_predictor_index",nargs);
  fprintf(stderr,"Init: ncl_stats 6\n");

/*
 * Register functions accepting 1 n dimensional int array and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(2);

  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */

  NclRegisterFunc(ncl_c_intmode_W,args,"ncl_c_intmode",nargs);		/* Returns integer */
  fprintf(stderr,"Init: ncl_stats 7\n");

/*
 * Register functions accepting 1 n dimensional double array, 1 scalar integer and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_devmoment_W,args,"ncl_c_devmoment",nargs);
  NclRegisterFunc(ncl_c_moment_W   ,args,"ncl_c_moment"   ,nargs);
  NclRegisterFunc(ncl_c_lagcorrn_W ,args,"ncl_c_lagcorrn" ,nargs);
  fprintf(stderr,"Init: ncl_stats 8\n");

/*
 * Register functions accepting 2 n dimensional double arrays, 1 scalar integer and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_wdevmoment_W,  args,"ncl_c_wdevmoment",  nargs);
  NclRegisterFunc(ncl_c_wmoment_W,     args,"ncl_c_wmoment",     nargs);
  fprintf(stderr,"Init: ncl_stats 9\n");
  
/*
 * Register NPIonsetThreshPercGT function.
 */
  nargs = 0;
  args = NewArgs(8);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* X       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* Y       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* OUT_1   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* OUT_2   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* OUT_3   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* OUT_4   */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_RegrRef_W,args         ,"ncl_c_regr_mbrn",nargs);
  NclRegisterProc(ncl_c_RegrRef_TheilSen_W,args,"ncl_c_theil_sen",nargs);
  fprintf(stderr,"Init: ncl_stats 10\n");

/*
 * Register functions accepting 2 n dimensional double arrays, 1 scalar integer and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double" ,0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"int64"  ,0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_RunningMean_W,    args,"ncl_c_runmean"    ,nargs);
  NclRegisterFunc(ncl_c_RunningMedian_W,  args,"ncl_c_runmed"     ,nargs);
  NclRegisterFunc(ncl_c_RunningMean_End_W,args,"ncl_c_runmean_end",nargs);
  NclRegisterFunc(ncl_c_RunningRegr_W,    args,"ncl_c_runregr"    ,nargs);
  fprintf(stderr,"Init: ncl_stats 11\n");

/*
 * Register functions accepting 2 n dimensional double arrays, 1 scalar integer and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double" ,0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double" ,0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"int64"  ,0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_RunningSlope_End_W,args,"ncl_c_runslope_end",nargs);
  NclRegisterFunc(ncl_c_rsq_ols_cv_n_W,    args,"ncl_c_rsq_ols_cv_n",nargs);
  NclRegisterFunc(ncl_c_rsq_ols_fv_n_W,    args,"ncl_c_rsq_ols_fv_n",nargs);
  fprintf(stderr,"Init: ncl_stats 12\n");

/*
 * Register functions accepting 2 n dimensional double arrays, 1 scalar integer and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double" ,0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double" ,0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_RunningWeightedMean_W,args,"ncl_c_runwgtmean",nargs);
  fprintf(stderr,"Init: ncl_stats 13\n");

/*
 * Register functions accepting 2 n dimensional double arrays, 1 scalar integer and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double" ,0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double" ,0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double" ,0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_RunningWeightedPercentileNoMean_W,args,"ncl_c_runwgtperc_nm",nargs);
  fprintf(stderr,"Init: ncl_stats 14\n");

/*
 * Register functions accepting 2 n dimensional double arrays, 1 scalar integer and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(6);

  SetArgTemplate(args,nargs,"double" ,0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double" ,0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double" ,0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double" ,0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_RunningWeightedPercentile_W, args,"ncl_c_runwgtperc" ,nargs);
  NclRegisterFunc(ncl_c_RunningWeightedPercentiles_W,args,"ncl_c_runwgtpercs",nargs);
  fprintf(stderr,"Init: ncl_stats end\n");
}

