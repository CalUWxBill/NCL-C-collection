/* Created by Bill Scheftic */
#include <stdio.h>
/*
 * The following are the required NCAR Graphics include files.
 * They should be located in ${NCARG_ROOT}/include
 */

#include <ncl_c_wrap.h>		/* Contains all included headers, Type conversion Macros, and getVarFromNCL function */
#include <wrap_math.h>
#include <ncl_stateq.h>


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



void Init(void){
  void *args;
  int nargs;
  fprintf(stderr,"Init: Initializing ncl_math functions ...\n");

/*
 * Register 1 variable functions.
 */
  nargs = 0;
  args = NewArgs(1);

  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;

  NclRegisterFunc(ncl_c_signof_W,  args,"ncl_c_signof",  nargs);
  NclRegisterFunc(ncl_c_tanh_W,    args,"ncl_c_tanh",    nargs);
  NclRegisterFunc(ncl_c_atanh_W,   args,"ncl_c_atanh",   nargs);
  NclRegisterFunc(ncl_c_angbtwpi_W,args,"ncl_c_angbtwpi",nargs);

/*
 * Register 2 variable functions.
 */
  nargs = 0;
  args = NewArgs(3);

  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;

  NclRegisterFunc(ncl_c_devsq_W,   args,"ncl_c_devsq",   nargs);
  NclRegisterFunc(ncl_c_amax2_W,   args,"ncl_c_amax2",   nargs);
  NclRegisterFunc(ncl_c_amin2_W,   args,"ncl_c_amin2",   nargs);
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

/*
 * Register 3 variable functions.
 */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY);	nargs++;

  NclRegisterFunc(ncl_c_amax3_W, args,"ncl_c_amax3", nargs);
  NclRegisterFunc(ncl_c_amin3_W, args,"ncl_c_amin3", nargs);
  NclRegisterFunc(ncl_c_dist3d_W,args,"ncl_c_dist3d",nargs);
  NclRegisterFunc(ncl_c_mx_b_W,  args,"ncl_c_mx_b",  nargs);
  NclRegisterFunc(ncl_c_ceq_var_W,   args,"ncl_c_ceq_var",   nargs);
  NclRegisterFunc(ncl_c_ceq_std_s_W, args,"ncl_c_ceq_std_s", nargs);
  NclRegisterFunc(ncl_c_ceq_std_p_W, args,"ncl_c_ceq_std_p", nargs);
  NclRegisterFunc(ncl_c_mult3_W, args,"ncl_c_mult3", nargs);

/*
 * Register 4 variable functions.
 */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY);	nargs++;

  NclRegisterFunc(ncl_c_dist2d_W,args,"ncl_c_dist2d",nargs);
  NclRegisterFunc(ncl_c_ceq_cov_W,   args,"ncl_c_ceq_cov",   nargs);
  NclRegisterFunc(ncl_c_mult4_W, args,"ncl_c_mult4", nargs);

/*
 * Register 5 variable functions.
 */
  nargs = 0;
  args = NewArgs(6);

  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY);	nargs++;

  NclRegisterFunc(ncl_c_linint_W,args,"ncl_c_linint",nargs);
  NclRegisterFunc(ncl_c_ceq_slope_W, args,"ncl_c_ceq_slope", nargs);
  NclRegisterFunc(ncl_c_mult5_W, args,"ncl_c_mult5", nargs);

/*
 * Register 6 variable functions.
 */
  nargs = 0;
  args = NewArgs(7);

  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY);	nargs++;

  NclRegisterFunc(ncl_c_ceq_orthoslope_W,args,"ncl_c_ceq_orthoslope",nargs);
  NclRegisterFunc(ncl_c_ceq_corr_W,      args,"ncl_c_ceq_corr",      nargs);

}

