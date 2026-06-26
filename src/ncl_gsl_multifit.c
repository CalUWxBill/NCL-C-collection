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
#include <wrap_gsl_multifit.h>

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


/* func(arr, double *, double *) */
NhlErrorTypes ncl_c_Cos_W( void ) {
    NhlErrorTypes retval = st_eqNarRNarNdblNint_Maps(wrap_params_Cos,3,0,3,0);
    return retval;
}

void Init(void){
  void *args;
  int nargs;
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
  NclRegisterFunc(ncl_gsl_multifit_wlinear_fit_add1_W,args,"ncl_gsl_multifit_wlinear_fit_add1",nargs);

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
  NclRegisterFunc(ncl_gsl_multifit_linear_predict_add1_W, args,"ncl_gsl_multifit_linear_predict_add1",nargs);
}

