#include <stdio.h>
/*
 * The following are the required NCAR Graphics include files.
 * They should be located in ${NCARG_ROOT}/include
 */

#include <ncl_c_wrap.h>		/* Contains all included headers, Type conversion Macros, and getVarFromNCL function */
#include <wrap_gsl_statistics.h>
#include <ncl_stateq.h>



NhlErrorTypes ncl_gsl_stats_mean_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_mean,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_variance_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_variance,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_sd_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_sd,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_tss_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_tss,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_absdev_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_absdev,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_skew_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_skew,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_kurtosis_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_kurtosis,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_lag1_autocorrelation_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_lag1_autocorrelation,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_max_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_max,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_min_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_min,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_median_from_sorted_data_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_median_from_sorted_data,1,0,0,0);
  return retval;
}

/* This function will sort the input arrays which we probably don't want */
/*
double wrap_gsl_stats_median(input_args args){
    return wrap_gsl_stats_1ar(gsl_stats_median,args,1);
}
*/

NhlErrorTypes ncl_gsl_stats_gastwirth_from_sorted_data_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_gastwirth_from_sorted_data,1,0,0,0);
  return retval;
}



NhlErrorTypes ncl_gsl_stats_minmax_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNint(wrap_gsl_stats_minmax,1,0,2,0);
  return retval;
}



NhlErrorTypes ncl_gsl_stats_covariance_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_covariance,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_correlation_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_correlation,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_wmean_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_wmean,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_wvariance_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_wvariance,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_wsd_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_wsd,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_wtss_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_wtss,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_wabsdev_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_wabsdev,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_wskew_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_wskew,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_wkurtosis_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_wkurtosis,2,0,0,0);
  return retval;
}



NhlErrorTypes ncl_gsl_stats_mad0_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_mad0,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_mad_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_mad,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_Sn0_from_sorted_data_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_Sn0_from_sorted_data,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_Sn_from_sorted_data_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_Sn_from_sorted_data,1,0,0,0);
  return retval;
}



NhlErrorTypes ncl_gsl_stats_Qn0_from_sorted_data_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_Qn0_from_sorted_data,1,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_Qn_from_sorted_data_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint(wrap_gsl_stats_Qn_from_sorted_data,1,0,0,0);
  return retval;
}



NhlErrorTypes ncl_gsl_stats_quantile_from_sorted_data_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_quantile_from_sorted_data,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_variance_m_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_variance_m,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_sd_m_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_sd_m,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_tss_m_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_tss_m,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_variance_with_fixed_mean_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_variance_with_fixed_mean,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_sd_with_fixed_mean_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_sd_with_fixed_mean,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_absdev_m_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_absdev_m,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_lag1_autocorrelation_m_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_lag1_autocorrelation_m,2,0,0,0);
  return retval;
}



NhlErrorTypes ncl_gsl_stats_trmean_from_sorted_data_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_trmean_from_sorted_data,2,0,0,0);
  return retval;
}



NhlErrorTypes ncl_gsl_stats_skew_m_sd_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_skew_m_sd,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_kurtosis_m_sd_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_kurtosis_m_sd,3,0,0,0);
  return retval;
}



NhlErrorTypes ncl_gsl_stats_wvariance_m_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_wvariance_m,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_wsd_m_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_wsd_m,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_wvariance_with_fixed_mean_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_wvariance_with_fixed_mean,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_wsd_with_fixed_mean_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_wsd_with_fixed_mean,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_wtss_m_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_wtss_m,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_wabsdev_m_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_wabsdev_m,3,0,0,0);
  return retval;
}



NhlErrorTypes ncl_gsl_stats_covariance_m_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_covariance_m,4,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_wskew_m_sd_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_wskew_m_sd,4,0,0,0);
  return retval;
}

NhlErrorTypes ncl_gsl_stats_wkurtosis_m_sd_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_wkurtosis_m_sd,4,0,0,0);
  return retval;
}



NhlErrorTypes ncl_gsl_stats_spearman_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_stats_spearman,2,0,0,0);
  return retval;
}



void Init(void){
  void *args;
  int nargs;
  fprintf(stderr,"Init: Initializing ncl_gsl_statistics functions ...\n");

/* In: 1 arr Return: 1 double */
  nargs = 0;
  args = NewArgs(2);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* X       */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */

  NclRegisterFunc(ncl_gsl_stats_mean_W,                      args,"ncl_gsl_stats_mean",nargs);
  NclRegisterFunc(ncl_gsl_stats_variance_W,                  args,"ncl_gsl_stats_variance",nargs);
  NclRegisterFunc(ncl_gsl_stats_sd_W,                        args,"ncl_gsl_stats_sd",nargs);
  NclRegisterFunc(ncl_gsl_stats_tss_W,                       args,"ncl_gsl_stats_tss",nargs);
  NclRegisterFunc(ncl_gsl_stats_absdev_W,                    args,"ncl_gsl_stats_absdev",nargs);
  NclRegisterFunc(ncl_gsl_stats_skew_W,                      args,"ncl_gsl_stats_skew",nargs);
  NclRegisterFunc(ncl_gsl_stats_kurtosis_W,                  args,"ncl_gsl_stats_kurtosis",nargs);
  NclRegisterFunc(ncl_gsl_stats_lag1_autocorrelation_W,      args,"ncl_gsl_stats_lag1_autocorrelation",nargs);
  NclRegisterFunc(ncl_gsl_stats_max_W,                       args,"ncl_gsl_stats_max",nargs);
  NclRegisterFunc(ncl_gsl_stats_min_W,                       args,"ncl_gsl_stats_min",nargs);
  NclRegisterFunc(ncl_gsl_stats_median_from_sorted_data_W,   args,"ncl_gsl_stats_median_srtd",nargs);
  NclRegisterFunc(ncl_gsl_stats_gastwirth_from_sorted_data_W,args,"ncl_gsl_stats_gastwirth_srtd",nargs);
  NclRegisterFunc(ncl_gsl_stats_mad0_W,                      args,"ncl_gsl_stats_mad0",nargs);
  NclRegisterFunc(ncl_gsl_stats_mad_W,                       args,"ncl_gsl_stats_mad",nargs);
  NclRegisterFunc(ncl_gsl_stats_Sn0_from_sorted_data_W,      args,"ncl_gsl_stats_Sn0_srtd",nargs);
  NclRegisterFunc(ncl_gsl_stats_Sn_from_sorted_data_W,       args,"ncl_gsl_stats_Sn_srtd",nargs);
  NclRegisterFunc(ncl_gsl_stats_Qn0_from_sorted_data_W,      args,"ncl_gsl_stats_Qn0_srtd",nargs);
  NclRegisterFunc(ncl_gsl_stats_Qn_from_sorted_data_W,       args,"ncl_gsl_stats_Qn_srtd",nargs);


/* In: 2 arr Return: 1 double */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double",0,NclANY);		nargs++;  /* X       */
  SetArgTemplate(args,nargs,"double",0,NclANY);		nargs++;  /* Y       */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_gsl_stats_covariance_W, args,"ncl_gsl_stats_covariance",nargs);
  NclRegisterFunc(ncl_gsl_stats_correlation_W,args,"ncl_gsl_stats_correlation",nargs);
  NclRegisterFunc(ncl_gsl_stats_wmean_W,      args,"ncl_gsl_stats_wmean",nargs);
  NclRegisterFunc(ncl_gsl_stats_wvariance_W,  args,"ncl_gsl_stats_wvariance",nargs);
  NclRegisterFunc(ncl_gsl_stats_wsd_W,        args,"ncl_gsl_stats_wsd",nargs);
  NclRegisterFunc(ncl_gsl_stats_wtss_W,       args,"ncl_gsl_stats_wtss",nargs);
  NclRegisterFunc(ncl_gsl_stats_wabsdev_W,    args,"ncl_gsl_stats_wabsdev",nargs);
  NclRegisterFunc(ncl_gsl_stats_wskew_W,      args,"ncl_gsl_stats_wskew",nargs);
  NclRegisterFunc(ncl_gsl_stats_wkurtosis_W,  args,"ncl_gsl_stats_wkurtosis",nargs);
  NclRegisterFunc(ncl_gsl_stats_spearman_W,   args,"ncl_gsl_stats_spearman",nargs);

  NclRegisterFunc(ncl_gsl_stats_quantile_from_sorted_data_W,args,"ncl_gsl_stats_quantile_srtd",nargs);
  NclRegisterFunc(ncl_gsl_stats_variance_m_W,               args,"ncl_gsl_stats_variance_m",nargs);
  NclRegisterFunc(ncl_gsl_stats_sd_m_W,                     args,"ncl_gsl_stats_sd_m",nargs);
  NclRegisterFunc(ncl_gsl_stats_tss_m_W,                    args,"ncl_gsl_stats_tss_m",nargs);
  NclRegisterFunc(ncl_gsl_stats_variance_with_fixed_mean_W, args,"ncl_gsl_stats_variance_with_fixed_mean",nargs);
  NclRegisterFunc(ncl_gsl_stats_sd_with_fixed_mean_W,       args,"ncl_gsl_stats_sd_with_fixed_mean",nargs);
  NclRegisterFunc(ncl_gsl_stats_absdev_m_W,                 args,"ncl_gsl_stats_absdev_m",nargs);
  NclRegisterFunc(ncl_gsl_stats_lag1_autocorrelation_m_W,   args,"ncl_gsl_stats_lag1_autocorrelation_m",nargs);

  NclRegisterFunc(ncl_gsl_stats_trmean_from_sorted_data_W,args,"ncl_gsl_stats_trmean_srtd",nargs);


/* In: 3 arr Return: 1 double */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double",0,NclANY);		nargs++;  /* X       */
  SetArgTemplate(args,nargs,"double",0,NclANY);		nargs++;  /* Y       */
  SetArgTemplate(args,nargs,"double",0,NclANY);		nargs++;  /* Z       */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_gsl_stats_skew_m_sd_W,    args,"ncl_gsl_stats_skew_m_sd",nargs);
  NclRegisterFunc(ncl_gsl_stats_kurtosis_m_sd_W,args,"ncl_gsl_stats_kurtosis_m_sd",nargs);

  NclRegisterFunc(ncl_gsl_stats_wvariance_m_W,              args,"ncl_gsl_stats_wvariance_m",nargs);
  NclRegisterFunc(ncl_gsl_stats_wsd_m_W,                    args,"ncl_gsl_stats_wsd_m",nargs);
  NclRegisterFunc(ncl_gsl_stats_wvariance_with_fixed_mean_W,args,"ncl_gsl_stats_wvariance_with_fixed_mean",nargs);
  NclRegisterFunc(ncl_gsl_stats_wsd_with_fixed_mean_W,      args,"ncl_gsl_stats_wsd_with_fixed_mean",nargs);
  NclRegisterFunc(ncl_gsl_stats_wtss_m_W,                   args,"ncl_gsl_stats_wtss_m",nargs);
  NclRegisterFunc(ncl_gsl_stats_wabsdev_m_W,                args,"ncl_gsl_stats_wabsdev_m",nargs);


/* In: 4 arr Return: 1 double */
  nargs = 0;
  args = NewArgs(6);

  SetArgTemplate(args,nargs,"double",0,NclANY);		nargs++;  /* X       */
  SetArgTemplate(args,nargs,"double",0,NclANY);		nargs++;  /* Y       */
  SetArgTemplate(args,nargs,"double",0,NclANY);		nargs++;  /* Z       */
  SetArgTemplate(args,nargs,"double",0,NclANY);		nargs++;  /* T       */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_gsl_stats_covariance_m_W,  args,"ncl_gsl_stats_covariance_m",nargs);
  NclRegisterFunc(ncl_gsl_stats_wskew_m_sd_W,    args,"ncl_gsl_stats_wskew_m_sd",nargs);
  NclRegisterFunc(ncl_gsl_stats_wkurtosis_m_sd_W,args,"ncl_gsl_stats_wkurtosis_m_sd",nargs);


/* In: 1 arr Out: 2 doubles */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double",0,NclANY);		nargs++;  /* X       */
  SetArgTemplate(args,nargs,"double",0,NclANY);		nargs++;  /* OUT_1   */
  SetArgTemplate(args,nargs,"double",0,NclANY);		nargs++;  /* OUT_2   */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */

  NclRegisterProc(ncl_gsl_stats_minmax_W,args,"ncl_gsl_stats_minmax",nargs);

}

