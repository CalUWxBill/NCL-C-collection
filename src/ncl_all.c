/* Created by Bill Scheftic */
#include <stdio.h>
/*
 * The following are the required NCAR Graphics include files.
 * They should be located in ${NCARG_ROOT}/include
 * 
 * This is a single file that gathers the wrappers from the other files.  Easier for debugging compilation.
 * - Many functions are not registered as there seems to be a limit.
 * 
 */

#include <ncl_c_wrap.h>     /* Contains all included headers, Type conversion Macros, and getVarFromNCL function */
#include <udunits2.h>
#include <stats2.h>
#include <arraystats2.h>
#include <print_arrays2.h>
#include <arrayinit2.h>
#include <ncl_stateq.h>
#include <dist_params.h>
#include <wrap_gsl_randist.h>
#include <wrap_gsl_statistics.h>
#include <wrap_gsl_multifit.h>
#include <wrap_hi2lo.h>
#include <wrap_s2s.h>
#include <wrap_math.h>
#include <wrap_sort.h>
#include <wrap_verify.h>

/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_convert ***********
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */


cv_converter *openConverter(char *from,char *to,ut_system **unitSystem_ptr){
/*  fprintf(stderr,"openConverter: 1\n"); */
  ut_set_error_message_handler(ut_ignore);
  *unitSystem_ptr = ut_read_xml("/st3/scheftic/lib/ncarg/udunits/udunits2.xml");

  ut_unit *ut_from = ut_parse(*unitSystem_ptr, from, UT_ASCII);
  if (ut_from == NULL) {
    ut_status parse_err = ut_get_status ();
    fprintf(stderr,"Unable to parse from %s, Err: %d\n", from, parse_err);
    switch (parse_err) {
      case UT_BAD_ARG:
        fprintf(stderr,"system or string is NULL.\n");
    break;
      case UT_SYNTAX:
        fprintf(stderr,"string contained a syntax error.\n");
    break;
      case UT_UNKNOWN:
        fprintf(stderr,"string contained an unknown identifier.\n");
    break;
      case UT_OS:
        fprintf(stderr,"Operating-system failure. See errno for the reason.\n");
    break;
      default:
        fprintf(stderr,"Unknown Error.\n");
    break;
    }
    return NULL;
  }

  ut_unit *ut_to = ut_parse(*unitSystem_ptr, to, UT_ASCII);
  if (ut_to == NULL) {
    ut_status parse_err = ut_get_status ();
    fprintf(stderr,"Unable to parse to %s, Err: %d\n", to, parse_err);
    switch (parse_err) {
      case UT_BAD_ARG:
        fprintf(stderr,"system or string is NULL.\n");
    break;
      case UT_SYNTAX:
        fprintf(stderr,"string contained a syntax error.\n");
    break;
      case UT_UNKNOWN:
        fprintf(stderr,"string contained an unknown identifier.\n");
    break;
      case UT_OS:
        fprintf(stderr,"Operating-system failure. See errno for the reason.\n");
    break;
      default:
        fprintf(stderr,"Unknown Error.\n");
    break;
    }
    return NULL;
  }

  cv_converter *converter = ut_get_converter(ut_from, ut_to);

  return converter;
}

void closeConverter(cv_converter *converter,ut_system **unitSystem_ptr){
/*  fprintf(stderr,"closeConverter: 1\n"); */
  cv_free(converter);
  ut_free_system(*unitSystem_ptr);

  return;
}

NhlErrorTypes ncl_c_convert_W( void ) {
/*  fprintf(stderr,"convert_W: 1\n"); */
  int i;
  NhlErrorTypes retval;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */ 

  arr X = getVarFromNCL(0,3);
  char *from = getStringFromNCL(1,3);
  char *to   = getStringFromNCL(2,3);

/*
 * Call the C function.
 */

  
  ut_system *unitSystem;
  cv_converter *converter = openConverter(from, to, &unitSystem);
  if (converter){
    arr data;
    arr m = ArrayFromList(X.n,DOUBLE,X.len);
    arr Xi = castAr(&X,DOUBLE,0);
    copyMiss(&m,&Xi);
    double *p    = pntr_of(&m);
    double *pX   = pntr_of(&Xi);
    double xmiss = *(double *)getMiss(&Xi);
    for(i=0; i<m.tlen; i++,pX++){
        if (*pX == xmiss){
          *p++ = xmiss;
        } else {
          *p++ = cv_convert_double(converter, *pX);
        }
    }
    freeAr(&Xi);
    data = castAr(&m,X.typ,1);
    
    closeConverter(converter,&unitSystem);
    retval = returnArToNCL(&data);
    
    freeAr(&data);
  } else {
    fprintf(stderr,"convert_W: error; can't be converted from %s to %s\n",from,to);
    retval = NhlFATAL;
  }
  freeArShell(&X);

/*
 * Set up return value.
 */ 

  return retval;
}

/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_distfit ***********
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
/* func(arr, double *, double *) */
NhlErrorTypes ncl_c_Gauss_W( void ) {
    NhlErrorTypes retval = st_eqNarRNarNdblNint(wrap_params_Gauss,1,0,2,0);
    return retval;
}

NhlErrorTypes ncl_c_Gamma_W( void ) {
    NhlErrorTypes retval = st_eqNarRNarNdblNint(wrap_params_Gamma,1,0,2,0);
    return retval;
}

NhlErrorTypes ncl_c_MixedGamma_W( void ) {
    NhlErrorTypes retval = st_eqNarRNarNdblNint(wrap_params_MixedGamma,1,0,3,0);
    return retval;
}

NhlErrorTypes ncl_c_Beta_W( void ) {
    NhlErrorTypes retval = st_eqNarRNarNdblNint(wrap_params_Beta,1,0,2,0);
    return retval;
}

NhlErrorTypes ncl_c_Weibull_W( void ) {
    NhlErrorTypes retval = st_eqNarRNarNdblNint(wrap_params_Weibull,1,0,2,0);
    return retval;
}

NhlErrorTypes ncl_c_cos_fun_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_cos_fun,5,0,0);
  return retval;
}

NhlErrorTypes ncl_c_Cos_W( void ) {
    NhlErrorTypes retval = st_eqNarRNarNdblNint_Maps(wrap_params_Cos,3,0,3,0);
    return retval;
}

NhlErrorTypes ncl_c_Gumbel1_W( void ) {
    NhlErrorTypes retval = st_eqNarRNarNdblNint(wrap_params_Gumbel1,1,0,3,0);
    return retval;
}

NhlErrorTypes ncl_c_Gumbel2_W( void ) {
    NhlErrorTypes retval = st_eqNarRNarNdblNint(wrap_params_Gumbel2,1,0,2,0);
    return retval;
}


/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_gsl_randist *******
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
/* 1 arg */
NhlErrorTypes ncl_c_gsl_ran_ugaussian_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint(wrap_gsl_ran_ugaussian_pdf,1,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_ugaussian_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint(wrap_gsl_cdf_ugaussian_P,1,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_ugaussian_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint(wrap_gsl_cdf_ugaussian_Q,1,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_ugaussian_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint(wrap_gsl_cdf_ugaussian_Pinv,1,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_ugaussian_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint(wrap_gsl_cdf_ugaussian_Qinv,1,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_landau_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint(wrap_gsl_ran_landau_pdf,1,0,0);
  return retval;
}


/* 2 args */
NhlErrorTypes ncl_c_gsl_ran_gaussian_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_gaussian_pdf,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_gaussian_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_gaussian_P,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_gaussian_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_gaussian_Q,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_gaussian_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_gaussian_Pinv,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_gaussian_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_gaussian_Qinv,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_ugaussian_tail_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_ugaussian_tail_pdf,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_exponential_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_exponential_pdf,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_exponential_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_exponential_P,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_exponential_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_exponential_Q,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_exponential_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_exponential_Pinv,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_exponential_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_exponential_Qinv,2,0,0);
  return retval;
}


NhlErrorTypes ncl_c_gsl_ran_laplace_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_laplace_pdf,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_laplace_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_laplace_P,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_laplace_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_laplace_Q,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_laplace_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_laplace_Pinv,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_laplace_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_laplace_Qinv,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_cauchy_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_cauchy_pdf,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_cauchy_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_cauchy_P,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_cauchy_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_cauchy_Q,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_cauchy_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_cauchy_Pinv,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_cauchy_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_cauchy_Qinv,2,0,0);
  return retval;
}


NhlErrorTypes ncl_c_gsl_ran_rayleigh_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_rayleigh_pdf,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_rayleigh_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_rayleigh_P,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_rayleigh_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_rayleigh_Q,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_rayleigh_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_rayleigh_Pinv,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_rayleigh_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_rayleigh_Qinv,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_chisq_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_chisq_pdf,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_chisq_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_chisq_P,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_chisq_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_chisq_Q,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_chisq_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_chisq_Pinv,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_chisq_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_chisq_Qinv,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_tdist_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_tdist_pdf,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_tdist_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_tdist_P,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_tdist_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_tdist_Q,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_tdist_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_tdist_Pinv,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_tdist_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_tdist_Qinv,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_logistic_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_logistic_pdf,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_logistic_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_logistic_P,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_logistic_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_logistic_Q,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_logistic_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_logistic_Pinv,2,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_logistic_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_logistic_Qinv,2,0,0);
  return retval;
}


/* 3 args */
NhlErrorTypes ncl_c_gsl_ran_gaussian_tail_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_gaussian_tail_pdf,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_exppow_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_exppow_pdf,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_exppow_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_exppow_P,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_exppow_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_exppow_Q,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_rayleigh_tail_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_rayleigh_tail_pdf,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_gamma_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_gamma_pdf,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_gamma_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_gamma_P,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_gamma_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_gamma_Q,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_gamma_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_gamma_Pinv,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_gamma_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_gamma_Qinv,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_flat_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_flat_pdf,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_flat_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_flat_P,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_flat_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_flat_Q,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_flat_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_flat_Pinv,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_flat_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_flat_Qinv,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_lognormal_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_lognormal_pdf,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_lognormal_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_lognormal_P,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_lognormal_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_lognormal_Q,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_lognormal_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_lognormal_Pinv,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_lognormal_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_lognormal_Qinv,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_fdist_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_fdist_pdf,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_fdist_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_fdist_P,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_fdist_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_fdist_Q,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_fdist_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_fdist_Pinv,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_fdist_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_fdist_Qinv,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_beta_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_beta_pdf,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_beta_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_beta_P,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_beta_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_beta_Q,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_beta_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_beta_Pinv,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_beta_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_beta_Qinv,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_pareto_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_pareto_pdf,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_pareto_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_pareto_P,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_pareto_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_pareto_Q,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_pareto_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_pareto_Pinv,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_pareto_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_pareto_Qinv,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_weibull_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_weibull_pdf,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_weibull_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_weibull_P,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_weibull_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_weibull_Q,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_weibull_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_weibull_Pinv,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_weibull_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_weibull_Qinv,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_gumbel1_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_gumbel1_pdf,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_gumbel1_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_gumbel1_P,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_gumbel1_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_gumbel1_Q,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_gumbel1_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_gumbel1_Pinv,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_gumbel1_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_gumbel1_Qinv,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_gsl_ran_gumbel2_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_gumbel2_pdf,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_gumbel2_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_gumbel2_P,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_gumbel2_Q_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_gumbel2_Q,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_gumbel2_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_gumbel2_Pinv,3,0,0);
  return retval;
}
NhlErrorTypes ncl_c_gsl_cdf_gumbel2_Qinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_cdf_gumbel2_Qinv,3,0,0);
  return retval;
}


NhlErrorTypes ncl_c_cdf_mixed_gamma_P_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_cdf_mixed_gamma_P,4,0,0);
  return retval;
}
NhlErrorTypes ncl_c_cdf_mixed_gamma_Pinv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_cdf_mixed_gamma_Pinv,4,0,0);
  return retval;
}

/* 5 args */
NhlErrorTypes ncl_c_gsl_ran_bivariate_gaussian_pdf_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_gsl_ran_bivariate_gaussian_pdf,5,0,0);
  return retval;
}


/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_gsl_statistics ****
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
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


/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_hi2lo *************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
NhlErrorTypes ncl_c_Hi2LoIdxWgt_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_Hi2LoIdxWgt,12,5,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_Hi2LoIdxWgt_Ar_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_Hi2LoIdxWgt_Ar,4,5,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_upScaleIdxWgt_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx_Maps(wrap_upScaleIdxWgt,6,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_upScaleStatsIdxWgt_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_upScaleStatsIdxWgt,6,7,0,0,0);
  return retval;
}


/*
 ***************************
 ***************************
 ***************************
 ***************************
 ***************************
 ***************************
 ***** ncl_gsl_multifit ****
 ***************************
 ***************************
 ***************************
 ***************************
 ***************************
 ***************************
 */
NhlErrorTypes ncl_gsl_multifit_linear_fit_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNint_Maps(wrap_gsl_multifit_linear_fit,2,1,4,0);
  return retval;
}

NhlErrorTypes ncl_gsl_multifit_wlinear_fit_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNint_Maps(wrap_gsl_multifit_wlinear_fit,3,1,4,0);
  return retval;
}

NhlErrorTypes ncl_gsl_multifit_wlinear_fit_add1_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNint_Maps(wrap_gsl_multifit_wlinear_fit_add1,3,1,4,0);
  return retval;
}

NhlErrorTypes ncl_gsl_multifit_linear_predict_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_multifit_linear_predict,3,0,1,0);
  return retval;
}

NhlErrorTypes ncl_gsl_multifit_linear_predict_add1_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_gsl_multifit_linear_predict_add1,3,0,1,0);
  return retval;
}


/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_s2s ***********
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
NhlErrorTypes ncl_c_getPercZscoreFromCDF_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_getPercZscoreFromCDF,5,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_getPercZscoreFromCDF_1_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_getPercZscoreFromCDF_1,5,0,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_getPdfCdf_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_getPdfCdf,5,2,0,0,0);
  return retval;
}


NhlErrorTypes ncl_c_getTertiaryExtremes_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_getTertiaryExtremes,5,0,5,0,0);
  return retval;
}

NhlErrorTypes ncl_c_getTertiaryExtremes_z_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_getTertiaryExtremes_z,1,0,5,0,0);
  return retval;
}


NhlErrorTypes ncl_c_getMultiRegression_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_getMultiRegression,4,4,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_getMultiRegression_min_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_getMultiRegression_min,5,4,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_getMultiRegression_min_Prescribed_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_getMultiRegression_min_Prescribed,6,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_applyMultiRegression_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNintNidx_Maps(wrap_applyMultiRegression,6,0,0,0,0);
  return retval;
}



NhlErrorTypes ncl_c_sortedCDF_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_sortedCDF,1,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_sortedCDF0_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_sortedCDF0,1,2,1,0,0);
  return retval;
}



NhlErrorTypes ncl_c_Start2ValidTime_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx(wrap_Start2ValidTime,1,0,0,0,0);
  return retval;
}


NhlErrorTypes ncl_c_printArray_W( void ) {
  arr     X = getVarFromNCL(0,2);
  char *fmt = getStringFromNCL(1,2);

  printArrayFmtAllWHdr(stdout,&X,fmt,"print_array: ");

  freeArShell(&X);
  return(NhlNOERROR);
}



/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_math **************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
/* 1 variable functions */
NhlErrorTypes ncl_c_signof_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint(wrap_sgn,1,0,0);
  return retval;
}

NhlErrorTypes ncl_c_tanh_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint(wrap_tanh,1,0,0);
  return retval;
}

NhlErrorTypes ncl_c_atanh_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint(wrap_atanh,1,0,0);
  return retval;
}

NhlErrorTypes ncl_c_angbtwpi_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint(wrap_angbtwpi,1,0,0);
  return retval;
}

/* 2 variable functions */
NhlErrorTypes ncl_c_devsq_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_devSq,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_amin2_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_amin2,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_amax2_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_amax2,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_dim_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_dim,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_dist_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_dist,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_ceq_mean_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_ceq_mean,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_ndvi_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_eq_ndvi,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_mult_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_mult,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_div_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_Div,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_angadd_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_angadd,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_angsub_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_angsub,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_angmult_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_angmult,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_angdiv_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_angdiv,2,0,0);
  return retval;
}

/* 3 variable functions */
NhlErrorTypes ncl_c_amax3_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_amax3,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_amin3_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_amin3,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_dist3d_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_dist3d,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_mx_b_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_mx_b,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_ceq_var_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_ceq_var,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_ceq_std_s_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_ceq_std_s,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_ceq_std_p_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_ceq_std_p,3,0,0);
  return retval;
}

NhlErrorTypes ncl_c_mult3_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_mult3,3,0,0);
  return retval;
}

/* 4 variable functions */
NhlErrorTypes ncl_c_dist2d_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_dist2d,4,0,0);
  return retval;
}

NhlErrorTypes ncl_c_ceq_cov_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_ceq_cov,4,0,0);
  return retval;
}

NhlErrorTypes ncl_c_mult4_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_mult4,4,0,0);
  return retval;
}

/* 5 variable functions */
NhlErrorTypes ncl_c_linint_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_linInterp,5,0,0);
  return retval;
}

NhlErrorTypes ncl_c_ceq_slope_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_ceq_slope,5,0,0);
  return retval;
}

NhlErrorTypes ncl_c_mult5_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_mult5,5,0,0);
  return retval;
}

/* 6 variable functions */
NhlErrorTypes ncl_c_ceq_orthoslope_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_ceq_orthoslope,6,0,0);
  return retval;
}

NhlErrorTypes ncl_c_ceq_corr_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_ceq_corr,6,0,0);
  return retval;
}



/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_sort **************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
/* arr func(arr) */
NhlErrorTypes ncl_c_qsort_idx_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx(wrap_qsort_idx,1,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_qsort_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx(wrap_qsort,1,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_qsort_idx_rev_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx(wrap_qsort_idx_rev,1,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_qsort_rev_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx(wrap_qsort_rev,1,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_countNonMiss2Arrays_W( void ) {
  NhlErrorTypes retval = st_idx_eqNarRNarNdblNintNidx_Maps(wrap_countNonMissNArrays,2,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_countNonMiss3Arrays_W( void ) {
  NhlErrorTypes retval = st_idx_eqNarRNarNdblNintNidx_Maps(wrap_countNonMissNArrays,3,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_countNonMiss4Arrays_W( void ) {
  NhlErrorTypes retval = st_idx_eqNarRNarNdblNintNidx_Maps(wrap_countNonMissNArrays,4,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_countNonMiss_W( void ) {
  NhlErrorTypes retval = st_idx_eqNarRNarNdblNintNidx(wrap_countNonMiss,1,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_countMiss_W( void ) {
  NhlErrorTypes retval = st_idx_eqNarRNarNdblNintNidx(wrap_countMiss,1,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_isAnyMiss_W( void ) {
  NhlErrorTypes retval = st_int_eqNarRNarNdblNint(wrap_isAnyMiss,1,0,0,0);
  return retval;
}


/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_stats *************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
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



/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_verify ************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
NhlErrorTypes ncl_c_skillScore_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_skillScore,2,0,0);
  return retval;
}


NhlErrorTypes ncl_c_invertSkillScore_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint(wrap_invertSkillScore,1,0,0);
  return retval;
}


NhlErrorTypes ncl_c_ensrps1_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_ensRPS_One,2,0,0,0);
  return retval;
}


NhlErrorTypes ncl_c_cdfRPS_one_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNintNidx_Maps(wrap_cdfRPS_one,5,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_calcRPSClim_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNintNidx_Maps(wrap_calcRPSClim,5,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_BiasImp_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_BiasImp,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_calcRPS_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNintNidx_Maps(wrap_calcRPS,6,0,0,0,0);
  return retval;
}


NhlErrorTypes ncl_c_verify_ensemble_forecast_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_verify_ensemble_forecast,2,4,50,0,1);
  return retval;
}

NhlErrorTypes ncl_c_verify_2_ensemble_forecasts_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_verify_2_ensemble_forecasts,3,8,25,0,1);
  return retval;
}

NhlErrorTypes ncl_c_verify_2_deterministic_forecasts_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_verify_2_deterministic_forecasts,3,4,20,0,1);
  return retval;
}



NhlErrorTypes ncl_c_verify_ensemble_forecast_1_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_verify_ensemble_forecast_1,2,0,6,0,0);
  return retval;
}


void Init(void){
/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_convert ***********
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
  void *args;
  int nargs;
  fprintf(stderr,"Init: Initializing ncl_convert functions ...\n");

  ng_size_t dimsizes[NCL_MAX_DIMENSIONS];

/*
 * Register convert function.
 */
  nargs = 0;
  args = NewArgs(3);

  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  dimsizes[0] = 1;
  SetArgTemplate(args,nargs,"string",1,dimsizes);   nargs++;
  SetArgTemplate(args,nargs,"string",1,dimsizes);   nargs++;

  NclRegisterFunc(ncl_c_convert_W,args,"ncl_c_convert",nargs);


/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_distfit ***********
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
  fprintf(stderr,"Init: Initializing ncl_distfit functions ...\n");

/*
 * Register function.
 */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* X       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* OUT_1   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* OUT_2   */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */

  NclRegisterProc(ncl_c_Gauss_W,  args,"ncl_c_gauss",  nargs);
  NclRegisterProc(ncl_c_Gamma_W,  args,"ncl_c_gamma",  nargs);
  NclRegisterProc(ncl_c_Beta_W,   args,"ncl_c_beta",   nargs);
  NclRegisterProc(ncl_c_Weibull_W,args,"ncl_c_weibull",nargs);
  NclRegisterProc(ncl_c_Gumbel2_W,args,"ncl_c_gumbel2",nargs);

/*
 * Register function.
 */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* X       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* OUT_1   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* OUT_2   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* OUT_3   */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */

/*  NclRegisterProc(ncl_c_Gumbel1_W,   args,"ncl_c_gumbel1",    nargs); */
  NclRegisterProc(ncl_c_MixedGamma_W,args,"ncl_c_mixed_gamma",nargs);

/*
 * Register function.
 */
  nargs = 0;
  args = NewArgs(8);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* X       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* Y       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* T       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* OUT_1   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* OUT_2   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* OUT_3   */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_Cos_W,   args,"ncl_c_fit_cos",    nargs);


/*
 * Register 5 variable functions.
 */
  nargs = 0;
  args = NewArgs(6);

  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;

  NclRegisterFunc(ncl_c_cos_fun_W,args,"ncl_c_cos_fun",nargs);



/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_gsl_randist *******
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
  gsl_set_error_handler_off();
  fprintf(stderr,"Init: Initializing ncl_gsl_randist functions ...\n");

/*
 * Register 1 variable functions.
 */
  nargs = 0;
  args = NewArgs(1);

  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;

  NclRegisterFunc(ncl_c_gsl_ran_ugaussian_pdf_W, args,"ncl_c_ugaussian_pdf", nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_ugaussian_P_W,   args,"ncl_c_ugaussian_P",   nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_ugaussian_Pinv_W,args,"ncl_c_ugaussian_Pinv",nargs);
/*  NclRegisterFunc(ncl_c_gsl_cdf_ugaussian_Q_W,   args,"ncl_c_ugaussian_Q",   nargs); */
/*  NclRegisterFunc(ncl_c_gsl_cdf_ugaussian_Qinv_W,args,"ncl_c_ugaussian_Qinv",nargs); */
/*  NclRegisterFunc(ncl_c_gsl_ran_landau_pdf_W,    args,"ncl_c_landau_pdf",    nargs); */

/*
 * Register 2 variable functions.
 */
  nargs = 0;
  args = NewArgs(3);

  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;

  NclRegisterFunc(ncl_c_gsl_cdf_gaussian_P_W,        args,"ncl_c_gaussian_P",        nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gaussian_Pinv_W,     args,"ncl_c_gaussian_Pinv",     nargs);
/*
  NclRegisterFunc(ncl_c_gsl_ran_gaussian_pdf_W,      args,"ncl_c_gaussian_pdf",      nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gaussian_Q_W,        args,"ncl_c_gaussian_Q",        nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gaussian_Qinv_W,     args,"ncl_c_gaussian_Qinv",     nargs);
  NclRegisterFunc(ncl_c_gsl_ran_ugaussian_tail_pdf_W,args,"ncl_c_ugaussian_tail_pdf",nargs);
  NclRegisterFunc(ncl_c_gsl_ran_exponential_pdf_W,   args,"ncl_c_exponential_pdf",   nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_exponential_P_W,     args,"ncl_c_exponential_P",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_exponential_Q_W,     args,"ncl_c_exponential_Q",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_exponential_Pinv_W,  args,"ncl_c_exponential_Pinv",  nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_exponential_Qinv_W,  args,"ncl_c_exponential_Qinv",  nargs);
  NclRegisterFunc(ncl_c_gsl_ran_laplace_pdf_W,       args,"ncl_c_laplace_pdf",       nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_laplace_P_W,         args,"ncl_c_laplace_P",         nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_laplace_Q_W,         args,"ncl_c_laplace_Q",         nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_laplace_Pinv_W,      args,"ncl_c_laplace_Pinv",      nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_laplace_Qinv_W,      args,"ncl_c_laplace_Qinv",      nargs);
  NclRegisterFunc(ncl_c_gsl_ran_cauchy_pdf_W,        args,"ncl_c_cauchy_pdf",        nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_cauchy_P_W,          args,"ncl_c_cauchy_P",          nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_cauchy_Q_W,          args,"ncl_c_cauchy_Q",          nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_cauchy_Pinv_W,       args,"ncl_c_cauchy_Pinv",       nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_cauchy_Qinv_W,       args,"ncl_c_cauchy_Qinv",       nargs);
  NclRegisterFunc(ncl_c_gsl_ran_rayleigh_pdf_W,      args,"ncl_c_rayleigh_pdf",      nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_rayleigh_P_W,        args,"ncl_c_rayleigh_P",        nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_rayleigh_Q_W,        args,"ncl_c_rayleigh_Q",        nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_rayleigh_Pinv_W,     args,"ncl_c_rayleigh_Pinv",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_rayleigh_Qinv_W,     args,"ncl_c_rayleigh_Qinv",     nargs);
  NclRegisterFunc(ncl_c_gsl_ran_chisq_pdf_W,         args,"ncl_c_chisq_pdf",         nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_chisq_P_W,           args,"ncl_c_chisq_P",           nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_chisq_Q_W,           args,"ncl_c_chisq_Q",           nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_chisq_Pinv_W,        args,"ncl_c_chisq_Pinv",        nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_chisq_Qinv_W,        args,"ncl_c_chisq_Qinv",        nargs);
  NclRegisterFunc(ncl_c_gsl_ran_tdist_pdf_W,         args,"ncl_c_tdist_pdf",         nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_tdist_P_W,           args,"ncl_c_tdist_P",           nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_tdist_Q_W,           args,"ncl_c_tdist_Q",           nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_tdist_Pinv_W,        args,"ncl_c_tdist_Pinv",        nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_tdist_Qinv_W,        args,"ncl_c_tdist_Qinv",        nargs);
  NclRegisterFunc(ncl_c_gsl_ran_logistic_pdf_W,      args,"ncl_c_logistic_pdf",      nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_logistic_P_W,        args,"ncl_c_logistic_P",        nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_logistic_Q_W,        args,"ncl_c_logistic_Q",        nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_logistic_Pinv_W,     args,"ncl_c_logistic_Pinv",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_logistic_Qinv_W,     args,"ncl_c_logistic_Qinv",     nargs);
 */
 
/*
 * Register 3 variable functions.
 */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;

  NclRegisterFunc(ncl_c_gsl_cdf_gamma_P_W,          args,"ncl_c_gamma_P",       nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gamma_Pinv_W,       args,"ncl_c_gamma_Pinv",    nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_beta_P_W,           args,"ncl_c_beta_P",        nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_beta_Pinv_W,        args,"ncl_c_beta_Pinv",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_weibull_P_W,        args,"ncl_c_weibull_P",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_weibull_Pinv_W,     args,"ncl_c_weibull_Pinv",  nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gumbel2_P_W,        args,"ncl_c_gumbel2_P",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gumbel2_Pinv_W,     args,"ncl_c_gumbel2_Pinv",  nargs);
/*
  NclRegisterFunc(ncl_c_gsl_ran_gaussian_tail_pdf_W,args,"ncl_c_gaussian_tail_pdf",nargs);
  NclRegisterFunc(ncl_c_gsl_ran_exppow_pdf_W,       args,"ncl_c_exppow_pdf",       nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_exppow_P_W,         args,"ncl_c_exppow_P",         nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_exppow_Q_W,         args,"ncl_c_exppow_Q",         nargs);
  NclRegisterFunc(ncl_c_gsl_ran_rayleigh_tail_pdf_W,args,"ncl_c_rayleigh_tail_pdf",nargs);
  NclRegisterFunc(ncl_c_gsl_ran_gamma_pdf_W,        args,"ncl_c_gamma_pdf",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gamma_Q_W,          args,"ncl_c_gamma_Q",       nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gamma_Qinv_W,       args,"ncl_c_gamma_Qinv",    nargs);
  NclRegisterFunc(ncl_c_gsl_ran_flat_pdf_W,         args,"ncl_c_flat_pdf",      nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_flat_P_W,           args,"ncl_c_flat_P",        nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_flat_Q_W,           args,"ncl_c_flat_Q",        nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_flat_Pinv_W,        args,"ncl_c_flat_Pinv",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_flat_Qinv_W,        args,"ncl_c_flat_Qinv",     nargs);
  NclRegisterFunc(ncl_c_gsl_ran_lognormal_pdf_W,    args,"ncl_c_lognormal_pdf", nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_lognormal_P_W,      args,"ncl_c_lognormal_P",   nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_lognormal_Q_W,      args,"ncl_c_lognormal_Q",   nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_lognormal_Pinv_W,   args,"ncl_c_lognormal_Pinv",nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_lognormal_Qinv_W,   args,"ncl_c_lognormal_Qinv",nargs);
  NclRegisterFunc(ncl_c_gsl_ran_fdist_pdf_W,        args,"ncl_c_fdist_pdf",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_fdist_P_W,          args,"ncl_c_fdist_P",       nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_fdist_Q_W,          args,"ncl_c_fdist_Q",       nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_fdist_Pinv_W,       args,"ncl_c_fdist_Pinv",    nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_fdist_Qinv_W,       args,"ncl_c_fdist_Qinv",    nargs);
  NclRegisterFunc(ncl_c_gsl_ran_beta_pdf_W,         args,"ncl_c_beta_pdf",      nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_beta_Q_W,           args,"ncl_c_beta_Q",        nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_beta_Qinv_W,        args,"ncl_c_beta_Qinv",     nargs);
  NclRegisterFunc(ncl_c_gsl_ran_pareto_pdf_W,       args,"ncl_c_pareto_pdf",    nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_pareto_P_W,         args,"ncl_c_pareto_P",      nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_pareto_Q_W,         args,"ncl_c_pareto_Q",      nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_pareto_Pinv_W,      args,"ncl_c_pareto_Pinv",   nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_pareto_Qinv_W,      args,"ncl_c_pareto_Qinv",   nargs);
  NclRegisterFunc(ncl_c_gsl_ran_weibull_pdf_W,      args,"ncl_c_weibull_pdf",   nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_weibull_Q_W,        args,"ncl_c_weibull_Q",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_weibull_Qinv_W,     args,"ncl_c_weibull_Qinv",  nargs);
  NclRegisterFunc(ncl_c_gsl_ran_gumbel1_pdf_W,      args,"ncl_c_gumbel1_pdf",   nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gumbel1_P_W,        args,"ncl_c_gumbel1_P",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gumbel1_Q_W,        args,"ncl_c_gumbel1_Q",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gumbel1_Pinv_W,     args,"ncl_c_gumbel1_Pinv",  nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gumbel1_Qinv_W,     args,"ncl_c_gumbel1_Qinv",  nargs);
  NclRegisterFunc(ncl_c_gsl_ran_gumbel2_pdf_W,      args,"ncl_c_gumbel2_pdf",   nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gumbel2_Q_W,        args,"ncl_c_gumbel2_Q",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gumbel2_Qinv_W,     args,"ncl_c_gumbel2_Qinv",  nargs);
 */

/*
 * Register 4 variable functions.
 */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;

  NclRegisterFunc(ncl_c_cdf_mixed_gamma_P_W,   args,"ncl_c_mixed_gamma_P",       nargs);
  NclRegisterFunc(ncl_c_cdf_mixed_gamma_Pinv_W,args,"ncl_c_mixed_gamma_Pinv",    nargs);

/*
 * Register 5 variable functions.
 */
  nargs = 0;
  args = NewArgs(6);

  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;
/*
  NclRegisterFunc(ncl_c_gsl_ran_bivariate_gaussian_pdf_W,args,"ncl_c_bivariate_gaussian_pdf",nargs);
 */


/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_gsl_statistics ****
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
  fprintf(stderr,"Init: Initializing ncl_gsl_statistics functions ...\n");

/* In: 1 arr Return: 1 double */
  nargs = 0;
  args = NewArgs(2);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;  /* X       */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
/*
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
 */

/* In: 2 arr Return: 1 double */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double",0,NclANY);     nargs++;  /* X       */
  SetArgTemplate(args,nargs,"double",0,NclANY);     nargs++;  /* Y       */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_gsl_stats_spearman_W,   args,"ncl_gsl_stats_spearman",nargs);
/*
  NclRegisterFunc(ncl_gsl_stats_covariance_W, args,"ncl_gsl_stats_covariance",nargs);
  NclRegisterFunc(ncl_gsl_stats_correlation_W,args,"ncl_gsl_stats_correlation",nargs);
  NclRegisterFunc(ncl_gsl_stats_wmean_W,      args,"ncl_gsl_stats_wmean",nargs);
  NclRegisterFunc(ncl_gsl_stats_wvariance_W,  args,"ncl_gsl_stats_wvariance",nargs);
  NclRegisterFunc(ncl_gsl_stats_wsd_W,        args,"ncl_gsl_stats_wsd",nargs);
  NclRegisterFunc(ncl_gsl_stats_wtss_W,       args,"ncl_gsl_stats_wtss",nargs);
  NclRegisterFunc(ncl_gsl_stats_wabsdev_W,    args,"ncl_gsl_stats_wabsdev",nargs);
  NclRegisterFunc(ncl_gsl_stats_wskew_W,      args,"ncl_gsl_stats_wskew",nargs);
  NclRegisterFunc(ncl_gsl_stats_wkurtosis_W,  args,"ncl_gsl_stats_wkurtosis",nargs);

  NclRegisterFunc(ncl_gsl_stats_quantile_from_sorted_data_W,args,"ncl_gsl_stats_quantile_srtd",nargs);
  NclRegisterFunc(ncl_gsl_stats_variance_m_W,               args,"ncl_gsl_stats_variance_m",nargs);
  NclRegisterFunc(ncl_gsl_stats_sd_m_W,                     args,"ncl_gsl_stats_sd_m",nargs);
  NclRegisterFunc(ncl_gsl_stats_tss_m_W,                    args,"ncl_gsl_stats_tss_m",nargs);
  NclRegisterFunc(ncl_gsl_stats_variance_with_fixed_mean_W, args,"ncl_gsl_stats_variance_with_fixed_mean",nargs);
  NclRegisterFunc(ncl_gsl_stats_sd_with_fixed_mean_W,       args,"ncl_gsl_stats_sd_with_fixed_mean",nargs);
  NclRegisterFunc(ncl_gsl_stats_absdev_m_W,                 args,"ncl_gsl_stats_absdev_m",nargs);
  NclRegisterFunc(ncl_gsl_stats_lag1_autocorrelation_m_W,   args,"ncl_gsl_stats_lag1_autocorrelation_m",nargs);

  NclRegisterFunc(ncl_gsl_stats_trmean_from_sorted_data_W,args,"ncl_gsl_stats_trmean_srtd",nargs);
 */

/* In: 3 arr Return: 1 double */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double",0,NclANY);     nargs++;  /* X       */
  SetArgTemplate(args,nargs,"double",0,NclANY);     nargs++;  /* Y       */
  SetArgTemplate(args,nargs,"double",0,NclANY);     nargs++;  /* Z       */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

/*
  NclRegisterFunc(ncl_gsl_stats_skew_m_sd_W,    args,"ncl_gsl_stats_skew_m_sd",nargs);
  NclRegisterFunc(ncl_gsl_stats_kurtosis_m_sd_W,args,"ncl_gsl_stats_kurtosis_m_sd",nargs);

  NclRegisterFunc(ncl_gsl_stats_wvariance_m_W,              args,"ncl_gsl_stats_wvariance_m",nargs);
  NclRegisterFunc(ncl_gsl_stats_wsd_m_W,                    args,"ncl_gsl_stats_wsd_m",nargs);
  NclRegisterFunc(ncl_gsl_stats_wvariance_with_fixed_mean_W,args,"ncl_gsl_stats_wvariance_with_fixed_mean",nargs);
  NclRegisterFunc(ncl_gsl_stats_wsd_with_fixed_mean_W,      args,"ncl_gsl_stats_wsd_with_fixed_mean",nargs);
  NclRegisterFunc(ncl_gsl_stats_wtss_m_W,                   args,"ncl_gsl_stats_wtss_m",nargs);
  NclRegisterFunc(ncl_gsl_stats_wabsdev_m_W,                args,"ncl_gsl_stats_wabsdev_m",nargs);
 */

/* In: 4 arr Return: 1 double */
  nargs = 0;
  args = NewArgs(6);

  SetArgTemplate(args,nargs,"double",0,NclANY);     nargs++;  /* X       */
  SetArgTemplate(args,nargs,"double",0,NclANY);     nargs++;  /* Y       */
  SetArgTemplate(args,nargs,"double",0,NclANY);     nargs++;  /* Z       */
  SetArgTemplate(args,nargs,"double",0,NclANY);     nargs++;  /* T       */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */
/*
  NclRegisterFunc(ncl_gsl_stats_covariance_m_W,  args,"ncl_gsl_stats_covariance_m",nargs);
  NclRegisterFunc(ncl_gsl_stats_wskew_m_sd_W,    args,"ncl_gsl_stats_wskew_m_sd",nargs);
  NclRegisterFunc(ncl_gsl_stats_wkurtosis_m_sd_W,args,"ncl_gsl_stats_wkurtosis_m_sd",nargs);
 */

/* In: 1 arr Out: 2 doubles */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double",0,NclANY);     nargs++;  /* X       */
  SetArgTemplate(args,nargs,"double",0,NclANY);     nargs++;  /* OUT_1   */
  SetArgTemplate(args,nargs,"double",0,NclANY);     nargs++;  /* OUT_2   */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
/*
  NclRegisterProc(ncl_gsl_stats_minmax_W,args,"ncl_gsl_stats_minmax",nargs);
 */



/*
 ***************************
 ***************************
 ***************************
 ***************************
 ***************************
 ***************************
 ***** ncl_gsl_multifit ****
 ***************************
 ***************************
 ***************************
 ***************************
 ***************************
 ***************************
 */
  fprintf(stderr,"Init: Initializing ncl_gsl_multifit functions ...\n");

/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(9);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcst_ens */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcst_ens */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* modwgts */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* modwgts */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* modwgts */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* modwgts */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* modwgts */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_gsl_multifit_linear_fit_W,args,"ncl_gsl_multifit_linear_fit",nargs);

/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(10);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcst_ens */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcst_ens */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcst_ens */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* modwgts */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* modwgts */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* modwgts */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* modwgts */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* modwgts */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_gsl_multifit_wlinear_fit_W,     args,"ncl_gsl_multifit_wlinear_fit",nargs);
/*  NclRegisterFunc(ncl_gsl_multifit_wlinear_fit_add1_W,args,"ncl_gsl_multifit_wlinear_fit_add1",nargs); */

/* In: 2 arr Return: 1 double */
  nargs = 0;
  args = NewArgs(6);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* X       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* Y       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* T       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* OUT_1   */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_gsl_multifit_linear_predict_W,      args,"ncl_gsl_multifit_linear_predict",nargs);
/*  NclRegisterFunc(ncl_gsl_multifit_linear_predict_add1_W, args,"ncl_gsl_multifit_linear_predict_add1",nargs); */



/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_hi2lo *************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
  fprintf(stderr,"Init: Initializing ncl_hi2lo functions ...\n");

/*
 * Register functions accepting 2 n dimensional double arrays, 1 scalar integer and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(19);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret N      */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret jIdxs  */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret iIdxs  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Wgts   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret WgtSum */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims  */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_Hi2LoIdxWgt_W,args,"ncl_c_hi2lo_idxwgt",nargs);

/*
 * Register functions accepting 2 n dimensional double arrays, 1 scalar integer and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(11);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret N      */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret jIdxs  */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret iIdxs  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Wgts   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret WgtSum */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims  */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_Hi2LoIdxWgt_Ar_W,args,"ncl_c_hi2lo_idxwgt_ar",nargs);

/*
 * Register functions accepting 2 n dimensional double arrays, 1 scalar integer and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(8);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* IN_hi  */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* N      */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* jIdxs  */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* iIdxs  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* Wgts   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* WgtSum */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_upScaleIdxWgt_W,args,"ncl_c_hi2lo_mean",nargs);

/*
 * Register functions accepting 2 n dimensional double arrays, 1 scalar integer and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(15);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* IN_hi  */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* N      */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* jIdxs  */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* iIdxs  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* Wgts   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* thresh */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Mn     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret min    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret max    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret med    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret FrcAbv */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret sigma  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret MnAbv  */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims  */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_upScaleStatsIdxWgt_W,args,"ncl_c_hi2lo_stats",nargs);



/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_s2s ***********
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
  fprintf(stderr,"Init: Initializing ncl_s2s functions ...\n");


/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(2);

  SetArgTemplate(args,nargs,NclANY,  0,NclANY);   nargs++;
  dimsizes[0] = 1;
  SetArgTemplate(args,nargs,"string",1,dimsizes); nargs++;

  NclRegisterProc(ncl_c_printArray_W, args, "ncl_c_print_array", nargs);
  
/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(2);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */

  NclRegisterFunc(ncl_c_Start2ValidTime_W,       args,"ncl_c_start_2_valid", nargs);
  
/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64",0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_getPersistenceNLeads_W, args,"ncl_c_get_persNld", nargs);
  
/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64",0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,"int64",0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_getPersistenceNLeads_Lag_W, args,"ncl_c_get_persNld_Lag", nargs);
  
/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(9);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* Fr     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* Fr_cdf */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* bbndry */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ebndry */
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++; /* n      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret z  */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_getPercZscoreFromCDF_W,  args,"ncl_c_get_P_z_cdf",  nargs);
  NclRegisterProc(ncl_c_getPercZscoreFromCDF_1_W,args,"ncl_c_get_P_z_cdf_1",nargs);
  NclRegisterProc(ncl_c_getPdfCdf_W,             args,"ncl_c_get_pdf_cdf",  nargs);
  
/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(12);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* Fr     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* Fr_cdf */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* bbndry */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ebndry */
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++; /* n      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_vlo */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_lo  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_mid */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_hi  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_vhi */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_getTertiaryExtremes_W,  args,"ncl_c_get_tertiary",  nargs);
  
/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(8);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* Fr     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_vlo */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_lo  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_mid */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_hi  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_vhi */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_getTertiaryExtremes_z_W,  args,"ncl_c_get_tertiary_z",  nargs);


/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(10);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcstens_z  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* obs_z      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* TC         */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* rsq_thresh */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ms     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret bs     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret rsqs   */
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++; /* ret idxs   */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_getMultiRegression_W,args,     "ncl_c_get_multi_regr",      nargs);

/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(11);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcstens_z  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* obs_z      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* TC         */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* t_sig      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* rsq_thresh */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ms     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret bs     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret rsqs   */
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++; /* ret idxs   */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_getMultiRegression_min_W,args, "ncl_c_get_multi_regr_min",  nargs);

/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(11);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcstens_z  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* obs_z      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* TC         */
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++; /* idxs       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* t_sig      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* rsq_thresh */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ms     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret bs     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret rsqs   */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_getMultiRegression_min_Prescribed_W,args, "ncl_c_get_multi_regr_min_prscrbd",  nargs);


/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(8);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_applyMultiRegression_W,args,"ncl_c_apply_multi_regr",nargs);





/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_sortedCDF_W,               args,"ncl_c_fit_cdf",nargs);

/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(6);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_sortedCDF0_W,               args,"ncl_c_fit_cdf0",nargs);


/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_math **************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
  fprintf(stderr,"Init: Initializing ncl_math functions ...\n");

/*
 * Register 1 variable functions.
 */
  nargs = 0;
  args = NewArgs(1);

  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  NclRegisterFunc(ncl_c_tanh_W,    args,"ncl_c_tanh",    nargs);
  NclRegisterFunc(ncl_c_atanh_W,   args,"ncl_c_atanh",   nargs);
/*
  NclRegisterFunc(ncl_c_signof_W,  args,"ncl_c_signof",  nargs);
  NclRegisterFunc(ncl_c_angbtwpi_W,args,"ncl_c_angbtwpi",nargs);
 */
 
/*
 * Register 2 variable functions.
 */
  nargs = 0;
  args = NewArgs(3);

  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;

  NclRegisterFunc(ncl_c_amax2_W,   args,"ncl_c_amax2",   nargs);
  NclRegisterFunc(ncl_c_amin2_W,   args,"ncl_c_amin2",   nargs);
/*
  NclRegisterFunc(ncl_c_devsq_W,   args,"ncl_c_devsq",   nargs);
  NclRegisterFunc(ncl_c_dim_W  ,   args,"ncl_c_dim"  ,   nargs);
  NclRegisterFunc(ncl_c_dist_W ,   args,"ncl_c_dist" ,   nargs);
  NclRegisterFunc(ncl_c_ceq_mean_W,args,"ncl_c_ceq_mean",nargs);
  NclRegisterFunc(ncl_c_ndvi_W,    args,"ncl_c_ndvi",    nargs);
  NclRegisterFunc(ncl_c_mult_W,    args,"ncl_c_mult",    nargs);
  NclRegisterFunc(ncl_c_div_W,     args,"ncl_c_div",     nargs);
  NclRegisterFunc(ncl_c_angadd_W,  args,"ncl_c_angadd",  nargs);
  NclRegisterFunc(ncl_c_angsub_W,  args,"ncl_c_angsub",  nargs);
  NclRegisterFunc(ncl_c_angmult_W, args,"ncl_c_angmult", nargs);
  NclRegisterFunc(ncl_c_angdiv_W,  args,"ncl_c_angdiv",  nargs);
 */
 
/*
 * Register 3 variable functions.
 */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY);    nargs++;

  NclRegisterFunc(ncl_c_mx_b_W,  args,"ncl_c_mx_b",  nargs);
/*
  NclRegisterFunc(ncl_c_amax3_W, args,"ncl_c_amax3", nargs);
  NclRegisterFunc(ncl_c_amin3_W, args,"ncl_c_amin3", nargs);
  NclRegisterFunc(ncl_c_dist3d_W,args,"ncl_c_dist3d",nargs);
  NclRegisterFunc(ncl_c_ceq_var_W,   args,"ncl_c_ceq_var",   nargs);
  NclRegisterFunc(ncl_c_ceq_std_s_W, args,"ncl_c_ceq_std_s", nargs);
  NclRegisterFunc(ncl_c_ceq_std_p_W, args,"ncl_c_ceq_std_p", nargs);
  NclRegisterFunc(ncl_c_mult3_W, args,"ncl_c_mult3", nargs);
 */
 
/*
 * Register 4 variable functions.
 */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY);    nargs++;
/*
  NclRegisterFunc(ncl_c_dist2d_W, args,"ncl_c_dist2d" ,nargs);
  NclRegisterFunc(ncl_c_ceq_cov_W,args,"ncl_c_ceq_cov",nargs);
  NclRegisterFunc(ncl_c_mult4_W,  args,"ncl_c_mult4"  ,nargs);
 */
 
/*
 * Register 5 variable functions.
 */
  nargs = 0;
  args = NewArgs(6);

  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY);    nargs++;
/*
  NclRegisterFunc(ncl_c_linint_W   , args,"ncl_c_linint"   , nargs);
  NclRegisterFunc(ncl_c_ceq_slope_W, args,"ncl_c_ceq_slope", nargs);
  NclRegisterFunc(ncl_c_mult5_W    , args,"ncl_c_mult5"    , nargs);
 */
 
/*
 * Register 6 variable functions.
 */
  nargs = 0;
  args = NewArgs(7);

  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY);    nargs++;
/*
  NclRegisterFunc(ncl_c_ceq_orthoslope_W,args,"ncl_c_ceq_orthoslope",nargs);
  NclRegisterFunc(ncl_c_ceq_corr_W,      args,"ncl_c_ceq_corr",      nargs);
 */


/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_sort **************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
  fprintf(stderr,"Init: Initializing ncl_sort functions ...\n");

/* In: 1 arr, 1 int arr Return: 1 arr */
  nargs = 0;
  args = NewArgs(2);

  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */

  NclRegisterFunc(ncl_c_qsort_idx_W,     args,"ncl_c_qsort_idx",    nargs); /* ret: array */
  NclRegisterFunc(ncl_c_qsort_W,         args,"ncl_c_qsort",        nargs); /* ret: array */
  NclRegisterFunc(ncl_c_qsort_idx_rev_W, args,"ncl_c_qsort_idx_rev",nargs); /* ret: array */
  NclRegisterFunc(ncl_c_qsort_rev_W,     args,"ncl_c_qsort_rev",    nargs); /* ret: array */
  NclRegisterFunc(ncl_c_countNonMiss_W,  args,"ncl_c_nnonmiss",     nargs); /* ret: int64 */
/*  NclRegisterFunc(ncl_c_countMiss_W,     args,"ncl_c_nmiss",        nargs); */ /* ret: int64 */
/*  NclRegisterFunc(ncl_c_isAnyMiss_W,     args,"ncl_c_isanymiss",    nargs); */ /* ret: int   */

/* In: 1 arr, 1 int arr Return: 1 arr */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_countNonMiss2Arrays_W,  args,"ncl_c_nvalid_2",     nargs); /* ret: int64 */

/* In: 1 arr, 1 int arr Return: 1 arr */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_countNonMiss3Arrays_W,  args,"ncl_c_nvalid_3",     nargs); /* ret: int64 */

/* In: 1 arr, 1 int arr Return: 1 arr */
  nargs = 0;
  args = NewArgs(6);

  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_countNonMiss4Arrays_W,  args,"ncl_c_nvalid_4",     nargs); /* ret: int64 */



/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_stats *************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
  fprintf(stderr,"Init: Initializing ncl_stats functions ...\n");

/*
 * Register 2 variable functions.
 */
  nargs = 0;
  args = NewArgs(3);

  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);   nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;

  NclRegisterFunc(ncl_c_dist_gausswgt_W,  args,"ncl_c_dist_gausswgt",  nargs);

/*
 * Register functions accepting 1 n dimensional double array and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(2);

  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */

  NclRegisterFunc(ncl_c_median_W,    args,"ncl_c_median",    nargs); 
  NclRegisterFunc(ncl_c_mean_W,      args,"ncl_c_mean",      nargs); 
  NclRegisterFunc(ncl_c_min_W,       args,"ncl_c_min",       nargs); 
  NclRegisterFunc(ncl_c_max_W,       args,"ncl_c_max",       nargs); 
  NclRegisterFunc(ncl_c_lagcorr_W,   args,"ncl_c_lagcorr",   nargs); 
  NclRegisterFunc(ncl_c_maxind_n_W,  args,"ncl_c_maxind_n",  nargs);   /* Returns int64 */
  NclRegisterFunc(ncl_c_minind_n_W,  args,"ncl_c_minind_n",  nargs);   /* Returns int64 */
/*                                                                   
  NclRegisterFunc(ncl_c_doylen_W,    args,"ncl_c_doylen",    nargs); 
  NclRegisterFunc(ncl_c_doymean_W,   args,"ncl_c_doymean",   nargs); 
  NclRegisterFunc(ncl_c_pimult_W,    args,"ncl_c_pimult",    nargs); 
  NclRegisterFunc(ncl_c_varp_W,      args,"ncl_c_varp",      nargs); 
  NclRegisterFunc(ncl_c_vars_W,      args,"ncl_c_vars",      nargs); 
  NclRegisterFunc(ncl_c_skewp_W,     args,"ncl_c_skewp",     nargs); 
  NclRegisterFunc(ncl_c_skews_W,     args,"ncl_c_skews",     nargs); 
  NclRegisterFunc(ncl_c_kurtp_W,     args,"ncl_c_kurtp",     nargs); 
  NclRegisterFunc(ncl_c_kurts_W,     args,"ncl_c_kurts",     nargs); 
  NclRegisterFunc(ncl_c_normvarp_W,  args,"ncl_c_normvarp",  nargs); 
  NclRegisterFunc(ncl_c_normvars_W,  args,"ncl_c_normvars",  nargs); 
  NclRegisterFunc(ncl_c_normskewp_W, args,"ncl_c_normskewp", nargs); 
  NclRegisterFunc(ncl_c_normskews_W, args,"ncl_c_normskews", nargs); 
  NclRegisterFunc(ncl_c_normkurtp_W, args,"ncl_c_normkurtp", nargs); 
  NclRegisterFunc(ncl_c_normkurts_W, args,"ncl_c_normkurts", nargs); 
  NclRegisterFunc(ncl_c_stddevp_W,   args,"ncl_c_stddevp",   nargs); 
  NclRegisterFunc(ncl_c_stddevs_W,   args,"ncl_c_stddevs",   nargs); 
  NclRegisterFunc(ncl_c_samplestat_W,args,"ncl_c_samplestat",nargs); 
  NclRegisterFunc(ncl_c_shapeparam_W,args,"ncl_c_shapeparam",nargs); 
  NclRegisterFunc(ncl_c_scaleparam_W,args,"ncl_c_scaleparam",nargs); 
  NclRegisterFunc(ncl_c_zeros_W,     args,"ncl_c_zeros",     nargs); 
  NclRegisterFunc(ncl_c_StdAnom_W,   args,"ncl_c_stdanom",   nargs);   */ /* Returns arr */
/*  NclRegisterFunc(ncl_c_Percentile_W,args,"ncl_c_percentile",nargs); */ /* Returns arr */

/*
 * Register functions accepting 1 n dimensional double array and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(2);

  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */

  NclRegisterFunc(ncl_c_firstidx_W, args,"ncl_c_firstidx", nargs);    /* Returns int64 */
  NclRegisterFunc(ncl_c_lastidx_W,  args,"ncl_c_lastidx",  nargs);    /* Returns int64 */

/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_wmean_W,             args,"ncl_c_wmean"             ,nargs);
  NclRegisterFunc(ncl_c_corr_W,              args,"ncl_c_corr"              ,nargs);
  NclRegisterFunc(ncl_c_r_squared_W,         args,"ncl_c_r_squared"         ,nargs);
  NclRegisterFunc(ncl_c_rsq_ols_cv_W,        args,"ncl_c_rsq_ols_cv"        ,nargs);
  NclRegisterFunc(ncl_c_msd_W,               args,"ncl_c_msd"               ,nargs);
  NclRegisterFunc(ncl_c_rmsd_W,              args,"ncl_c_rmsd"              ,nargs);
  NclRegisterFunc(ncl_c_mae_W,               args,"ncl_c_mae"               ,nargs);
  NclRegisterFunc(ncl_c_dist_multigausswgt_W,args,"ncl_c_dist_multigausswgt",nargs);
  NclRegisterFunc(ncl_c_dist_gausswgt_ave_W, args,"ncl_c_dist_gausswgt_ave" ,nargs);
  NclRegisterFunc(ncl_c_valatperc_W,         args,"ncl_c_valatperc"         ,nargs);
  NclRegisterFunc(ncl_c_percatval_W,         args,"ncl_c_percatval"         ,nargs);
  NclRegisterFunc(ncl_c_valatpercsrtd_W,     args,"ncl_c_valatpercsrtd"     ,nargs);   
  NclRegisterFunc(ncl_c_percatvalsrtd_W,     args,"ncl_c_percatvalsrtd"     ,nargs);   
  NclRegisterFunc(ncl_c_valfromidx_W,        args,"ncl_c_valfromidx"        ,nargs);   
  NclRegisterFunc(ncl_c_idxfromval_W,        args,"ncl_c_idxfromval"        ,nargs);   
/*
  NclRegisterFunc(ncl_c_orthoslope_W,        args,"ncl_c_orthoslope"        ,nargs);   
  NclRegisterFunc(ncl_c_doytrendr_W,         args,"ncl_c_doytrendr"         ,nargs);   
  NclRegisterFunc(ncl_c_doytrend_W,          args,"ncl_c_doytrend"          ,nargs);   
  NclRegisterFunc(ncl_c_wstddev_s_W,         args,"ncl_c_wstddev_s"         ,nargs);   
  NclRegisterFunc(ncl_c_wkurt_W,             args,"ncl_c_wkurt"             ,nargs);   
  NclRegisterFunc(ncl_c_covar_W,             args,"ncl_c_covar"             ,nargs);   
  NclRegisterFunc(ncl_c_devxy_W,             args,"ncl_c_devxy"             ,nargs);   
  NclRegisterFunc(ncl_c_xy_W,                args,"ncl_c_xy"                ,nargs);   
  NclRegisterFunc(ncl_c_bias_W,              args,"ncl_c_bias"              ,nargs);   
  NclRegisterFunc(ncl_c_relbias_W,           args,"ncl_c_relbias"           ,nargs);   
  NclRegisterFunc(ncl_c_ssd_W,               args,"ncl_c_ssd"               ,nargs);   
  NclRegisterFunc(ncl_c_valsatpercs_W,       args,"ncl_c_valsatpercs"       ,nargs);   */ /* Returns arr */
/*  NclRegisterFunc(ncl_c_percsatvals_W,       args,"ncl_c_percsatvals"       ,nargs); */ /* Returns arr */
/*  NclRegisterFunc(ncl_c_valsatpercssrtd_W,   args,"ncl_c_valsatpercssrtd"   ,nargs); */ /* Returns arr */
/*  NclRegisterFunc(ncl_c_percsatvalssrtd_W,   args,"ncl_c_percsatvalssrtd"   ,nargs); */ /* Returns arr */

/*  NclRegisterFunc(ncl_c_closestind_n_W,args,"ncl_c_closestind_n",nargs); */ /* Returns int64 */
  
/*
 * Register functions accepting 3 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_dist_gausswgt_wave_W   ,args,"ncl_c_dist_gausswgt_wave"   ,nargs);
  NclRegisterFunc(ncl_c_dist_gausswgt_ave_h2_W ,args,"ncl_c_dist_gausswgt_ave_h2" ,nargs);
/*
  NclRegisterFunc(ncl_c_cyclicMean_W           ,args,"ncl_c_cyclicMean"           ,nargs);
  NclRegisterFunc(ncl_c_cyclicStdDev_W         ,args,"ncl_c_cyclicStdDev"         ,nargs);
  NclRegisterFunc(ncl_c_calcValatPercFromHist_W,args,"ncl_c_calcValatPercFromHist",nargs);
  NclRegisterFunc(ncl_c_calcValatPercWeighted_W,args,"ncl_c_calcValatPercWeighted",nargs);
  NclRegisterFunc(ncl_c_Pcorr_W                ,args,"ncl_c_pcorr"                ,nargs);
  NclRegisterFunc(ncl_c_SPcorr_W               ,args,"ncl_c_spcorr"               ,nargs);
 */

/*
 * Register functions accepting 3 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(6);

  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_dist_gausswgt_wave_h2_W   ,args,"ncl_c_dist_gausswgt_wave_h2"   ,nargs);
  NclRegisterFunc(ncl_c_combined_predictor_index_W,args,"ncl_c_combined_predictor_index",nargs);

/*
 * Register functions accepting 1 n dimensional int array and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(2);

  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */

  NclRegisterFunc(ncl_c_intmode_W,args,"ncl_c_intmode",nargs);      /* Returns integer */

/*
 * Register functions accepting 1 n dimensional double array, 1 scalar integer and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_lagcorrn_W ,args,"ncl_c_lagcorrn" ,nargs);
/*
  NclRegisterFunc(ncl_c_devmoment_W,args,"ncl_c_devmoment",nargs);
  NclRegisterFunc(ncl_c_moment_W   ,args,"ncl_c_moment"   ,nargs);
 */

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
/*
  NclRegisterFunc(ncl_c_wdevmoment_W,  args,"ncl_c_wdevmoment",  nargs);
  NclRegisterFunc(ncl_c_wmoment_W,     args,"ncl_c_wmoment",     nargs);
 */
  
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


/*
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 ***** ncl_verify ************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 *****************************
 */
  fprintf(stderr,"Init: Initializing ncl_verify functions ...\n");
/* In: 1 arr, 1 int arr Return: 1 arr */
  nargs = 0;
  args = NewArgs(1);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;

  NclRegisterFunc(ncl_c_invertSkillScore_W,args,"ncl_c_inv_skill",nargs);

/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(3);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_skillScore_W,     args,"ncl_c_skill",    nargs);

/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(7);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */
/*
  NclRegisterFunc(ncl_c_cdfRPS_one_W, args,"ncl_c_cdf_rps1",   nargs);
  NclRegisterFunc(ncl_c_calcRPSClim_W,args,"ncl_c_cdf_rpsclim",nargs);
 */

/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(8);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */
/*
  NclRegisterFunc(ncl_c_calcRPS_W,args,"ncl_c_ccdf_rps",nargs);
 */

/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */
  NclRegisterFunc(ncl_c_ensrps1_W,   args,   "ncl_c_ensrps1",nargs);
/*
 */

/*
 * Register functions accepting 3 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */
/*
  NclRegisterFunc(ncl_c_BiasImp_W,args,"ncl_c_biasimp",nargs);
 */

/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(10);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcst  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* obs   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM         */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS_Spread   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_AE      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_SE      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_Bias    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst_RPS     */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_verify_ensemble_forecast_1_W,args,"ncl_c_verify_1",nargs);
  
/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(59);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcst  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* obs   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM            */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed          */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS_Spread      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS_AE          */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret obs_Mean        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret obs_Med         */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Climo_MAE       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_MAE        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Climo_MSE       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_MSE        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_SS_MAE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MAE_min      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MAE_Q1       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MAE_med      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MAE_Q3       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MAE_max      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_SS_MSE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MSE_min      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MSE_Q1       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MSE_med      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MSE_Q3       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MSE_max      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Climo_MedAE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_MedAE      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_SS_MedAE   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Climo_MedSE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_MedSE      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_SS_MedSE   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_MedAE    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_SS_MedAE */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_MedSE    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_SS_MedSE */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_MAE      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_MSE      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_SS_MAE   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_SS_MSE   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Climo_RPS       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst_RPS        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst_RPSS       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Climo_RPSmed    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst_RPSmed     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst_RPSSmed    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_Bias       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_RelBias    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_Corr       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_SpCr       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_Bias     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_RelBias  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_Corr     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_fcst        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_obs         */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_ensm        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_ensmed      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst_mean       */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret nvalid          */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_verify_ensemble_forecast_W,args,"ncl_c_verify",nargs);
  
/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(39);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcst1  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcst2  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* obs    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1M           */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1_Spread     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1_AE         */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1_Err        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2M           */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2_Spread     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2_AE         */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2_Err        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret obs_Mean        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_obs         */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_SS_MAE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_SS_MSE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst_RPSS       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1M_MAE       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1M_MSE       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst1_RPS_Mean  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1M_Bias      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1M_RelBias   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1M_Corr      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1M_SpCr      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_fcst1       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_ens1m       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst1_mean      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2M_MAE       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2M_MSE       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst2_RPS_Mean  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2M_Bias      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2M_RelBias   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2M_Corr      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2M_SpCr      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_fcst2       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_ens2m       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst2_mean      */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret nvalid          */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_verify_2_ensemble_forecasts_W,args,"ncl_c_verify_2",nargs);
  
/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(30);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcst1             */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcst2             */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* obs               */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst1_AE      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst1_Err     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst2_AE      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst2_Err     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret obs_Mean      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_obs       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MAE        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MSE        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst1_MAE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst1_MSE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst1_Bias    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst1_RelBias */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst1_Corr    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst1_SpCr    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_fcst1     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst1_mean    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst2_MAE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst2_MSE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst2_Bias    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst2_RelBias */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst2_Corr    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst2_SpCr    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_fcst2     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst2_mean    */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret nvalid        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims         */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims  */

  NclRegisterProc(ncl_c_verify_2_deterministic_forecasts_W,args,"ncl_c_verify_det_2",nargs);


  fprintf(stderr,"Finished loading shared libraries!\n");
}

