/* Created by Bill Scheftic */
#include <stdio.h>
/*
 * The following are the required NCAR Graphics include files.
 * They should be located in ${NCARG_ROOT}/include
 */

#include <ncl_c_wrap.h>		/* Contains all included headers, Type conversion Macros, and getVarFromNCL function */
#include <wrap_gsl_randist.h>
#include <ncl_stateq.h>


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



void Init(void){
  void *args;
  int nargs;
  fprintf(stderr,"Init: Initializing ncl_gsl_randist functions ...\n");

/*
 * Register 1 variable functions.
 */
  nargs = 0;
  args = NewArgs(1);

  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;

  NclRegisterFunc(ncl_c_gsl_ran_ugaussian_pdf_W, args,"ncl_c_ugaussian_pdf", nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_ugaussian_P_W,   args,"ncl_c_ugaussian_P",   nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_ugaussian_Q_W,   args,"ncl_c_ugaussian_Q",   nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_ugaussian_Pinv_W,args,"ncl_c_ugaussian_Pinv",nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_ugaussian_Qinv_W,args,"ncl_c_ugaussian_Qinv",nargs);
  NclRegisterFunc(ncl_c_gsl_ran_landau_pdf_W,    args,"ncl_c_landau_pdf",    nargs);

/*
 * Register 2 variable functions.
 */
  nargs = 0;
  args = NewArgs(3);

  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;

  NclRegisterFunc(ncl_c_gsl_ran_gaussian_pdf_W,      args,"ncl_c_gaussian_pdf",      nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gaussian_P_W,        args,"ncl_c_gaussian_P",        nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gaussian_Q_W,        args,"ncl_c_gaussian_Q",        nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gaussian_Pinv_W,     args,"ncl_c_gaussian_Pinv",     nargs);
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

/*
 * Register 3 variable functions.
 */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;

  NclRegisterFunc(ncl_c_gsl_ran_gaussian_tail_pdf_W,args,"ncl_c_gaussian_tail_pdf",nargs);
  NclRegisterFunc(ncl_c_gsl_ran_exppow_pdf_W,       args,"ncl_c_exppow_pdf",       nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_exppow_P_W,         args,"ncl_c_exppow_P",         nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_exppow_Q_W,         args,"ncl_c_exppow_Q",         nargs);
  NclRegisterFunc(ncl_c_gsl_ran_rayleigh_tail_pdf_W,args,"ncl_c_rayleigh_tail_pdf",nargs);
  NclRegisterFunc(ncl_c_gsl_ran_gamma_pdf_W,        args,"ncl_c_gamma_pdf",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gamma_P_W,          args,"ncl_c_gamma_P",       nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gamma_Q_W,          args,"ncl_c_gamma_Q",       nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gamma_Pinv_W,       args,"ncl_c_gamma_Pinv",    nargs);
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
  NclRegisterFunc(ncl_c_gsl_cdf_beta_P_W,           args,"ncl_c_beta_P",        nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_beta_Q_W,           args,"ncl_c_beta_Q",        nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_beta_Pinv_W,        args,"ncl_c_beta_Pinv",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_beta_Qinv_W,        args,"ncl_c_beta_Qinv",     nargs);
  NclRegisterFunc(ncl_c_gsl_ran_pareto_pdf_W,       args,"ncl_c_pareto_pdf",    nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_pareto_P_W,         args,"ncl_c_pareto_P",      nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_pareto_Q_W,         args,"ncl_c_pareto_Q",      nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_pareto_Pinv_W,      args,"ncl_c_pareto_Pinv",   nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_pareto_Qinv_W,      args,"ncl_c_pareto_Qinv",   nargs);
  NclRegisterFunc(ncl_c_gsl_ran_weibull_pdf_W,      args,"ncl_c_weibull_pdf",   nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_weibull_P_W,        args,"ncl_c_weibull_P",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_weibull_Q_W,        args,"ncl_c_weibull_Q",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_weibull_Pinv_W,     args,"ncl_c_weibull_Pinv",  nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_weibull_Qinv_W,     args,"ncl_c_weibull_Qinv",  nargs);
  NclRegisterFunc(ncl_c_gsl_ran_gumbel1_pdf_W,      args,"ncl_c_gumbel1_pdf",   nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gumbel1_P_W,        args,"ncl_c_gumbel1_P",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gumbel1_Q_W,        args,"ncl_c_gumbel1_Q",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gumbel1_Pinv_W,     args,"ncl_c_gumbel1_Pinv",  nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gumbel1_Qinv_W,     args,"ncl_c_gumbel1_Qinv",  nargs);
  NclRegisterFunc(ncl_c_gsl_ran_gumbel2_pdf_W,      args,"ncl_c_gumbel2_pdf",   nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gumbel2_P_W,        args,"ncl_c_gumbel2_P",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gumbel2_Q_W,        args,"ncl_c_gumbel2_Q",     nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gumbel2_Pinv_W,     args,"ncl_c_gumbel2_Pinv",  nargs);
  NclRegisterFunc(ncl_c_gsl_cdf_gumbel2_Qinv_W,     args,"ncl_c_gumbel2_Qinv",  nargs);

/*
 * Register 4 variable functions.
 */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;

  NclRegisterFunc(ncl_c_cdf_mixed_gamma_P_W,   args,"ncl_c_mixed_gamma_P",       nargs);
  NclRegisterFunc(ncl_c_cdf_mixed_gamma_Pinv_W,args,"ncl_c_mixed_gamma_Pinv",    nargs);

/*
 * Register 5 variable functions.
 */
  nargs = 0;
  args = NewArgs(6);

  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;

  NclRegisterFunc(ncl_c_gsl_ran_bivariate_gaussian_pdf_W,args,"ncl_c_bivariate_gaussian_pdf",nargs);
}

