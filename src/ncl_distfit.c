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
#include <dist_params.h>

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

void Init(void){
  void *args;
  int nargs;
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

  NclRegisterProc(ncl_c_Gumbel1_W,   args,"ncl_c_gumbel1",    nargs);
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

  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++;

  NclRegisterFunc(ncl_c_cos_fun_W,args,"ncl_c_cos_fun",nargs);
}

