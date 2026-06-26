#ifndef  _WRAP_GSL_SF_H_
#define  _WRAP_GSL_SF_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <gsl/gsl_sf.h>

gsl_mode_t global_mode = GSL_PREC_DOUBLE;

double wrap_dbl_1d_mode(double (*fct)(double,gsl_mode_t),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    double rv = fct(x,global_mode);
    if (!isfinite(rv)){ rv = *(double *)args->missval; }
    return rv;
}

double wrap_dbl_2d_mode(double (*fct)(double,double,gsl_mode_t),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    double y = args->dblp[1];
    double rv = fct(x,y,global_mode);
    if (!isfinite(rv)){ rv = *(double *)args->missval; }
    return rv;
}

double wrap_dbl_3d_mode(double (*fct)(double,double,double,gsl_mode_t),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    double y = args->dblp[1];
    double z = args->dblp[2];
    double rv = fct(x,y,z,global_mode);
    if (!isfinite(rv)){ rv = *(double *)args->missval; }
    return rv;
}

double wrap_dbl_4d_mode(double (*fct)(double,double,double,double,gsl_mode_t),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    double y = args->dblp[1];
    double z = args->dblp[2];
    double t = args->dblp[3];
    double rv = fct(x,y,z,t,global_mode);
    if (!isfinite(rv)){ rv = *(double *)args->missval; }
    return rv;
}


double wrap_dbl_1i1d(double (*fct)(int,double),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    int xint = args->intp[0];
    double rv = fct(xint,x);
    if (!isfinite(rv)){ rv = *(double *)args->missval; }
    return rv;
}

double wrap_dbl_1i2d(double (*fct)(int,double,double),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    double y = args->dblp[1];
    int xint = args->intp[0];
    double rv = fct(xint,x,y);
    if (!isfinite(rv)){ rv = *(double *)args->missval; }
    return rv;
}

double wrap_dbl_2i1d(double (*fct)(int,int,double),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    int xint = args->intp[0];
    int yint = args->intp[1];
    double rv = fct(xint,yint,x);
    if (!isfinite(rv)){ rv = *(double *)args->missval; }
    return rv;
}

double wrap_dbl_2i2d(double (*fct)(int,int,double,double),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    double y = args->dblp[1];
    int xint = args->intp[0];
    int yint = args->intp[1];
    double rv = fct(xint,yint,x,y);
    if (!isfinite(rv)){ rv = *(double *)args->missval; }
    return rv;
}

double wrap_dbl_2i(double (*fct)(int,int),input_args *args){
    int i;
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    int xint = args->intp[0];
    int yint = args->intp[1];
    double rv = fct(xint,yint);
    if (!isfinite(rv)){ rv = *(double *)args->missval; }
    return rv;
}

double wrap_dbl_1i(double (*fct)(int),input_args *args){
    int i;
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    int xint = args->intp[0];
    double rv = fct(xint);
    if (!isfinite(rv)){ rv = *(double *)args->missval; }
    return rv;
}


double wrap_dbl_1ui(double (*fct)(unsigned int),input_args *args){
    int i;
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    if (args->intp[0] < 0){
        return *(double *)args->missval;
    }
    unsigned int xuint = (unsigned int)args->intp[0];
    double rv = fct(xuint);
    if (!isfinite(rv)){ rv = *(double *)args->missval; }
    return rv;
}

double wrap_dbl_1d1ui(double (*fct)(double,unsigned int),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    for(i=0;i<args->nints;i++){
        if (args->intp[i] < 0){
            return *(double *)args->missval;
        }
    }
    double x           = args->dblp[0];
    unsigned int xuint = (unsigned int)args->intp[0];
    double rv = fct(x,xuint);
    if (!isfinite(rv)){ rv = *(double *)args->missval; }
    return rv;
}

double wrap_dbl_2ui(double (*fct)(unsigned int,unsigned int),input_args *args){
    int i;
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    for(i=0;i<args->nints;i++){
        if (args->intp[i] < 0){
            return *(double *)args->missval;
        }
    }
    unsigned int xuint = (unsigned int)args->intp[0];
    unsigned int yuint = (unsigned int)args->intp[1];
    double rv = fct(xuint,yuint);
    if (!isfinite(rv)){ rv = *(double *)args->missval; }
    return rv;
}


arr wrap_gsl_sf_arr_nmnmx1d(int (*fct)(int,int,double,double *),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    int nmin = args->intp[0];
    int nmax = args->intp[1];
    int n = nmax-nmin+1;
    arr rv = Array(1,DOUBLE,n);
    if (args->dblp_miss){ *(double *)getMiss(&rv) = args->dblp_miss[0]; }
    
    fct(nmin,nmax,x,pntr_of(&rv));
    return rv;
}

arr wrap_gsl_sf_arr_lmx1d(int (*fct)(int,double,double *),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    int lmax = args->intp[0];
    int n = lmax+1;
    arr rv = Array(1,DOUBLE,n);
    if (args->dblp_miss){ *(double *)getMiss(&rv) = args->dblp_miss[0]; }
    
    fct(lmax,x,pntr_of(&rv));
    return rv;
}


/* specfunc/gsl_sf_result.h
 */

/*
struct gsl_sf_result_struct {
  double val;
  double err;
};
typedef struct gsl_sf_result_struct gsl_sf_result;

#define GSL_SF_RESULT_SET(r,v,e) do { (r)->val=(v); (r)->err=(e); } while(0)

struct gsl_sf_result_e10_struct {
  double val;
  double err;
  int    e10;
};
typedef struct gsl_sf_result_e10_struct gsl_sf_result_e10;

int gsl_sf_result_smash_e(const gsl_sf_result_e10 * re, gsl_sf_result * r);
*/

/* specfunc/gsl_sf_airy.h
 */

/* Airy function Ai(x)
 *
 * exceptions: GSL_EUNDRFLW
 */
/* int gsl_sf_airy_Ai_e(const double x, const gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_airy_Ai(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d_mode(gsl_sf_airy_Ai,args);
}

/* Airy function Bi(x)
 *
 * exceptions: GSL_EOVRFLW
 */
/* int gsl_sf_airy_Bi_e(const double x, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_airy_Bi(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d_mode(gsl_sf_airy_Bi,args);
}

/* scaled Ai(x):
 *                     Ai(x)   x < 0
 *   exp(+2/3 x^{3/2}) Ai(x)   x > 0
 */
/* int gsl_sf_airy_Ai_scaled_e(const double x, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_airy_Ai_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d_mode(gsl_sf_airy_Ai_scaled,args);
}

/* scaled Bi(x):
 *                     Bi(x)   x < 0
 *   exp(-2/3 x^{3/2}) Bi(x)   x > 0
 */
/* int gsl_sf_airy_Bi_scaled_e(const double x, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_airy_Bi_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d_mode(gsl_sf_airy_Bi_scaled,args);
}

/* derivative Ai'(x)
 *
 * exceptions: GSL_EUNDRFLW
 */
/* int gsl_sf_airy_Ai_deriv_e(const double x, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_airy_Ai_deriv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d_mode(gsl_sf_airy_Ai_deriv,args);
}

/* derivative Bi'(x)
 *
 * exceptions: GSL_EOVRFLW
 */
/* int gsl_sf_airy_Bi_deriv_e(const double x, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_airy_Bi_deriv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d_mode(gsl_sf_airy_Bi_deriv,args);
}

/* scaled derivative Ai'(x):
 *                     Ai'(x)   x < 0
 *   exp(+2/3 x^{3/2}) Ai'(x)   x > 0
 */
/* int gsl_sf_airy_Ai_deriv_scaled_e(const double x, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_airy_Ai_deriv_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d_mode(gsl_sf_airy_Ai_deriv_scaled,args);
}

/* scaled derivative:
 *                     Bi'(x)   x < 0
 *   exp(-2/3 x^{3/2}) Bi'(x)   x > 0
 */
/* int gsl_sf_airy_Bi_deriv_scaled_e(const double x, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_airy_Bi_deriv_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d_mode(gsl_sf_airy_Bi_deriv_scaled,args);
}

/* Zeros of Ai(x)
 */
/* int gsl_sf_airy_zero_Ai_e(unsigned int s, gsl_sf_result * result); */
double wrap_gsl_sf_airy_zero_Ai(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ui(gsl_sf_airy_zero_Ai,args);
}

/* Zeros of Bi(x)
 */
/* int gsl_sf_airy_zero_Bi_e(unsigned int s, gsl_sf_result * result); */
double wrap_gsl_sf_airy_zero_Bi(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ui(gsl_sf_airy_zero_Bi,args);
}

/* Zeros of Ai'(x)
 */
/* int gsl_sf_airy_zero_Ai_deriv_e(unsigned int s, gsl_sf_result * result); */
double wrap_gsl_sf_airy_zero_Ai_deriv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ui(gsl_sf_airy_zero_Ai_deriv,args);
}

/* Zeros of Bi'(x)
 */
/* int gsl_sf_airy_zero_Bi_deriv_e(unsigned int s, gsl_sf_result * result); */
double wrap_gsl_sf_airy_zero_Bi_deriv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ui(gsl_sf_airy_zero_Bi_deriv,args);
}


/* specfunc/gsl_sf_bessel.h
 */

/* Regular Bessel Function J_0(x)
 */
/* int gsl_sf_bessel_J0_e(const double x,  gsl_sf_result * result); */
double wrap_gsl_sf_bessel_J0(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_J0,args);
}

/* Regular Bessel Function J_1(x)
 *
 * exceptions: GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_J1_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_J1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_J1,args);
}

/* Regular Bessel Function J_n(x)
 *
 * exceptions: GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_Jn_e(int n, double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_Jn(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_bessel_Jn,args);
}

/* Regular Bessel Function J_n(x),  nmin <= n <= nmax
 *
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
arr wrap_gsl_sf_bessel_Jn_array(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_sf_arr_nmnmx1d(gsl_sf_bessel_Jn_array,args);
}

/* Irregular Bessel function Y_0(x)
 *
 * x > 0.0
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_Y0_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_Y0(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_Y0,args);
}

/* Irregular Bessel function Y_1(x)
 *
 * x > 0.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_Y1_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_Y1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_Y1,args);
}

/* Irregular Bessel function Y_n(x)
 *
 * x > 0.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_Yn_e(int n,const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_Yn(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_bessel_Yn,args);
}

/* Irregular Bessel function Y_n(x), nmin <= n <= nmax
 *
 * x > 0.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
arr wrap_gsl_sf_bessel_Yn_array(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_sf_arr_nmnmx1d(gsl_sf_bessel_Yn_array,args);
}

/* Regular modified Bessel function I_0(x)
 *
 * exceptions: GSL_EOVRFLW
 */
/* int gsl_sf_bessel_I0_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_I0(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_I0,args);
}

/* Regular modified Bessel function I_1(x)
 *
 * exceptions: GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_I1_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_I1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_I1,args);
}

/* Regular modified Bessel function I_n(x)
 *
 * exceptions: GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_In_e(const int n, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_In(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_bessel_In,args);
}

/* Regular modified Bessel function  I_n(x) for n=nmin,...,nmax
 *
 * nmin >=0, nmax >= nmin
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
arr wrap_gsl_sf_bessel_In_array(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_sf_arr_nmnmx1d(gsl_sf_bessel_In_array,args);
}

/* Scaled regular modified Bessel function
 *  exp(-|x|) I_0(x)
 */
/* int gsl_sf_bessel_I0_scaled_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_I0_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_I0_scaled,args);
}

/* Scaled regular modified Bessel function
 *  exp(-|x|) I_1(x)
 *
 * exceptions: GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_I1_scaled_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_I1_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_I1_scaled,args);
}

/* Scaled regular modified Bessel function
 *  exp(-|x|) I_n(x)
 *
 * exceptions: GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_In_scaled_e(int n, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_In_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_bessel_In_scaled,args);
}

/* Scaled regular modified Bessel function
 *  exp(-|x|) I_n(x)  for n=nmin,...,nmax
 *
 * nmin >=0, nmax >= nmin
 * exceptions: GSL_EUNDRFLW
 */
arr wrap_gsl_sf_bessel_In_scaled_array(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_sf_arr_nmnmx1d(gsl_sf_bessel_In_scaled_array,args);
}

/* Irregular modified Bessel function K_0(x)
 *
 * x > 0.0
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_K0_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_K0(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_K0,args);
}

/* Irregular modified Bessel function K_1(x)
 *
 * x > 0.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_K1_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_K1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_K1,args);
}

/* Irregular modified Bessel function K_n(x)
 *
 * x > 0.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_Kn_e(const int n, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_Kn(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_bessel_Kn,args);
}

/* Irregular modified Bessel function  K_n(x)  for n=nmin,...,nmax
 *
 * x > 0.0, nmin >=0, nmax >= nmin
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
arr wrap_gsl_sf_bessel_Kn_array(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_sf_arr_nmnmx1d(gsl_sf_bessel_Kn_array,args);
}

/* Scaled irregular modified Bessel function
 *  exp(x) K_0(x)
 *
 * x > 0.0
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_bessel_K0_scaled_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_K0_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_K0_scaled,args);
}

/* Scaled irregular modified Bessel function
 *  exp(x) K_1(x)
 *
 * x > 0.0
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_K1_scaled_e(const double x, gsl_sf_result * result); */ 
double wrap_gsl_sf_bessel_K1_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_K1_scaled,args);
}

/* Scaled irregular modified Bessel function
 *  exp(x) K_n(x)
 *
 * x > 0.0
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_Kn_scaled_e(int n, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_Kn_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_bessel_Kn_scaled,args);
}

/* Scaled irregular modified Bessel function  exp(x) K_n(x)  for n=nmin,...,nmax
 *
 * x > 0.0, nmin >=0, nmax >= nmin
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
arr wrap_gsl_sf_bessel_Kn_scaled_array(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_sf_arr_nmnmx1d(gsl_sf_bessel_Kn_scaled_array,args);
}

/* Regular spherical Bessel function j_0(x) = sin(x)/x
 */
/* int gsl_sf_bessel_j0_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_j0(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_j0,args);
}

/* Regular spherical Bessel function j_1(x) = (sin(x)/x - cos(x))/x
 *
 * exceptions: GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_j1_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_j1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_j1,args);
}

/* Regular spherical Bessel function j_2(x) = ((3/x^2 - 1)sin(x) - 3cos(x)/x)/x
 *
 * exceptions: GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_j2_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_j2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_j2,args);
}

/* Regular spherical Bessel function j_l(x)
 *
 * l >= 0, x >= 0.0
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_jl_e(const int l, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_jl(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_bessel_jl,args);
}

/* Regular spherical Bessel function j_l(x) for l=0,1,...,lmax
 *
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
arr wrap_gsl_sf_bessel_jl_array(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_sf_arr_lmx1d(gsl_sf_bessel_jl_array,args);
}

/* Regular spherical Bessel function j_l(x) for l=0,1,...,lmax
 * Uses Steed's method.
 *
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
arr wrap_gsl_sf_bessel_jl_steed_array(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_sf_arr_lmx1d(gsl_sf_bessel_jl_steed_array,args);
}

/* Irregular spherical Bessel function y_0(x)
 */
/* int gsl_sf_bessel_y0_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_y0(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_y0,args);
}

/* Irregular spherical Bessel function y_1(x)
 *
 * exceptions: GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_y1_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_y1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_y1,args);
}

/* Irregular spherical Bessel function y_2(x)
 *
 * exceptions: GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_y2_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_y2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_y2,args);
}

/* Irregular spherical Bessel function y_l(x)
 *
 * exceptions: GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_yl_e(int l, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_yl(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_bessel_yl,args);
}

/* Irregular spherical Bessel function y_l(x) for l=0,1,...,lmax
 *
 * exceptions: GSL_EUNDRFLW
 */
arr wrap_gsl_sf_bessel_yl_array(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_sf_arr_lmx1d(gsl_sf_bessel_yl_array,args);
}

/* Regular scaled modified spherical Bessel function
 *
 * Exp[-|x|] i_0(x)
 */
/* int gsl_sf_bessel_i0_scaled_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_i0_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_i0_scaled,args);
}

/* Regular scaled modified spherical Bessel function
 *
 * Exp[-|x|] i_1(x)
 *
 * exceptions: GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_i1_scaled_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_i1_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_i1_scaled,args);
}

/* Regular scaled modified spherical Bessel function
 *
 * Exp[-|x|] i_2(x)
 *
 * exceptions: GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_i2_scaled_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_i2_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_i2_scaled,args);
}

/* Regular scaled modified spherical Bessel functions
 *
 * Exp[-|x|] i_l(x)
 *
 * i_l(x) = Sqrt[Pi/(2x)] BesselI[l+1/2,x]
 *
 * l >= 0
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_il_scaled_e(const int l, double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_il_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_bessel_il_scaled,args);
}

/* Regular scaled modified spherical Bessel functions
 *
 * Exp[-|x|] i_l(x)
 * for l=0,1,...,lmax
 *
 * exceptions: GSL_EUNDRFLW
 */
arr wrap_gsl_sf_bessel_il_scaled_array(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_sf_arr_lmx1d(gsl_sf_bessel_il_scaled_array,args);
}

/* Irregular scaled modified spherical Bessel function
 * Exp[x] k_0(x)
 *
 * x > 0.0
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_k0_scaled_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_k0_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_k0_scaled,args);
}

/* Irregular modified spherical Bessel function
 * Exp[x] k_1(x)
 *
 * x > 0.0
 * exceptions: GSL_EDOM, GSL_EUNDRFLW, GSL_EOVRFLW
 */
/* int gsl_sf_bessel_k1_scaled_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_k1_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_k1_scaled,args);
}

/* Irregular modified spherical Bessel function
 * Exp[x] k_2(x)
 *
 * x > 0.0
 * exceptions: GSL_EDOM, GSL_EUNDRFLW, GSL_EOVRFLW
 */
/* int gsl_sf_bessel_k2_scaled_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_k2_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_bessel_k2_scaled,args);
}

/* Irregular modified spherical Bessel function
 * Exp[x] k_l[x]
 *
 * k_l(x) = Sqrt[Pi/(2x)] BesselK[l+1/2,x]
 *
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_kl_scaled_e(int l, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_kl_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_bessel_kl_scaled,args);
}

/* Irregular scaled modified spherical Bessel function
 * Exp[x] k_l(x)
 *
 * for l=0,1,...,lmax
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
arr wrap_gsl_sf_bessel_kl_scaled_array(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_sf_arr_lmx1d(gsl_sf_bessel_kl_scaled_array,args);
}

/* Regular cylindrical Bessel function J_nu(x)
 *
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_Jnu_e(const double nu, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_Jnu(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_bessel_Jnu,args);
}

/* Irregular cylindrical Bessel function Y_nu(x)
 */
/* int gsl_sf_bessel_Ynu_e(double nu, double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_Ynu(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_bessel_Ynu,args);
}

/* Regular cylindrical Bessel function J_nu(x)
 * evaluated at a series of x values. The array
 * contains the x values. They are assumed to be
 * strictly ordered and positive. The array is
 * over-written with the values of J_nu(x_i).
 *
 * exceptions: GSL_EDOM, GSL_EINVAL
 */
/* int gsl_sf_bessel_sequence_Jnu_e(double nu, gsl_mode_t mode, size_t size, double * v); */

/* Scaled modified cylindrical Bessel functions
 *
 * Exp[-|x|] BesselI[nu, x]
 * x >= 0, nu >= 0
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_bessel_Inu_scaled_e(double nu, double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_Inu_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_bessel_Inu_scaled,args);
}

/* Modified cylindrical Bessel functions
 *
 * BesselI[nu, x]
 * x >= 0, nu >= 0
 *
 * exceptions: GSL_EDOM, GSL_EOVRFLW
 */
/* int gsl_sf_bessel_Inu_e(double nu, double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_Inu(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_bessel_Inu,args);
}

/* Scaled modified cylindrical Bessel functions
 *
 * Exp[+|x|] BesselK[nu, x]
 * x > 0, nu >= 0
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_bessel_Knu_scaled_e(const double nu, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_Knu_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_bessel_Knu_scaled,args);
}

/* int gsl_sf_bessel_Knu_scaled_e10_e(const double nu, const double x, gsl_sf_result_e10 * result); */

/* Modified cylindrical Bessel functions
 *
 * BesselK[nu, x]
 * x > 0, nu >= 0
 *
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int gsl_sf_bessel_Knu_e(const double nu, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_Knu(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_bessel_Knu,args);
}

/* Logarithm of modified cylindrical Bessel functions.
 *
 * Log[BesselK[nu, x]]
 * x > 0, nu >= 0
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_bessel_lnKnu_e(const double nu, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_lnKnu(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_bessel_lnKnu,args);
}

/* s'th positive zero of the Bessel function J_0(x).
 */
/* int gsl_sf_bessel_zero_J0_e(unsigned int s, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_zero_J0(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ui(gsl_sf_bessel_zero_J0,args);
}

/* s'th positive zero of the Bessel function J_1(x).
 */
/* int gsl_sf_bessel_zero_J1_e(unsigned int s, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_zero_J1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ui(gsl_sf_bessel_zero_J1,args);
}

/* s'th positive zero of the Bessel function J_nu(x).
 */
/* int gsl_sf_bessel_zero_Jnu_e(double nu, unsigned int s, gsl_sf_result * result); */
double wrap_gsl_sf_bessel_zero_Jnu(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d1ui(gsl_sf_bessel_zero_Jnu,args);
}


/* specfunc/gsl_sf_clausen.h
 */

/* Calculate the Clausen integral:
 *   Cl_2(x) := Integrate[-Log[2 Sin[t/2]], {t,0,x}]
 *
 * Relation to dilogarithm:
 *   Cl_2(theta) = Im[ Li_2(e^(i theta)) ]
 */
/* int gsl_sf_clausen_e(double x, gsl_sf_result * result); */
double wrap_gsl_sf_clausen(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_clausen,args);
}


/* specfunc/gsl_sf_coulomb.h
 */

/* Normalized hydrogenic bound states, radial dependence. */

/* R_1 := 2Z sqrt(Z) exp(-Z r)
 */
/* int gsl_sf_hydrogenicR_1_e(const double Z, const double r, gsl_sf_result * result); */
double wrap_gsl_sf_hydrogenicR_1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_hydrogenicR_1,args);
}

/* R_n := norm exp(-Z r/n) (2Z/n)^l Laguerre[n-l-1, 2l+1, 2Z/n r]
 *
 * normalization such that psi(n,l,r) = R_n Y_{lm}
 */
/* int gsl_sf_hydrogenicR_e(const int n, const int l, const double Z, const double r, gsl_sf_result * result); */
double wrap_gsl_sf_hydrogenicR(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2i2d(gsl_sf_hydrogenicR,args);
}

/* Coulomb wave functions F_{lam_F}(eta,x), G_{lam_G}(eta,x)
 * and their derivatives; lam_G := lam_F - k_lam_G
 *
 * lam_F, lam_G > -0.5
 * x > 0.0
 *
 * Conventions of Abramowitz+Stegun.
 *
 * Because there can be a large dynamic range of values,
 * overflows are handled gracefully. If an overflow occurs,
 * GSL_EOVRFLW is signalled and exponent(s) are returned
 * through exp_F, exp_G. These are such that
 *
 *   F_L(eta,x)  =  fc[k_L] * exp(exp_F)
 *   G_L(eta,x)  =  gc[k_L] * exp(exp_G)
 *   F_L'(eta,x) = fcp[k_L] * exp(exp_F)
 *   G_L'(eta,x) = gcp[k_L] * exp(exp_G)
 */
/*
int
gsl_sf_coulomb_wave_FG_e(const double eta, const double x,
                            const double lam_F,
                            const int  k_lam_G,
                            gsl_sf_result * F, gsl_sf_result * Fp,
                            gsl_sf_result * G, gsl_sf_result * Gp,
                            double * exp_F, double * exp_G);
                            */


/* F_L(eta,x) as array */
/*
int gsl_sf_coulomb_wave_F_array(
  double lam_min, int kmax,
  double eta, double x,
  double * fc_array,
  double * F_exponent
  );
  */

/* F_L(eta,x), G_L(eta,x) as arrays */
/*
int gsl_sf_coulomb_wave_FG_array(double lam_min, int kmax,
                                double eta, double x,
                                double * fc_array, double * gc_array,
                                double * F_exponent,
                                double * G_exponent
                                );
                                */

/* F_L(eta,x), G_L(eta,x), F'_L(eta,x), G'_L(eta,x) as arrays */
/*
int gsl_sf_coulomb_wave_FGp_array(double lam_min, int kmax,
                                double eta, double x,
                                double * fc_array, double * fcp_array,
                                double * gc_array, double * gcp_array,
                                double * F_exponent,
                                double * G_exponent
                                );
                                */

/* Coulomb wave function divided by the argument,
 * F(eta, x)/x. This is the function which reduces to
 * spherical Bessel functions in the limit eta->0.
 */
/*
int gsl_sf_coulomb_wave_sphF_array(double lam_min, int kmax,
                                        double eta, double x,
                                        double * fc_array,
                                        double * F_exponent
                                        );
                                        */

/* Coulomb wave function normalization constant.
 * [Abramowitz+Stegun 14.1.8, 14.1.9]
 */
/* int gsl_sf_coulomb_CL_e(double L, double eta, gsl_sf_result * result); */
/* int gsl_sf_coulomb_CL_array(double Lmin, int kmax, double eta, double * cl); */


/* specfunc/gsl_sf_coupling.h
 */

/* 3j Symbols:  / ja jb jc \
 *              \ ma mb mc /
 *
 * exceptions: GSL_EDOM, GSL_EOVRFLW
 */
/*
int gsl_sf_coupling_3j_e(int two_ja, int two_jb, int two_jc,
                            int two_ma, int two_mb, int two_mc,
                            gsl_sf_result * result
                            );
                            */
/*
double gsl_sf_coupling_3j(int two_ja, int two_jb, int two_jc,
                          int two_ma, int two_mb, int two_mc
                          );
                          */

/* 6j Symbols:  / ja jb jc \
 *              \ jd je jf /
 *
 * exceptions: GSL_EDOM, GSL_EOVRFLW
 */
/*
int gsl_sf_coupling_6j_e(int two_ja, int two_jb, int two_jc,
                         int two_jd, int two_je, int two_jf,
                         gsl_sf_result * result
                         );
                         */
/*
double gsl_sf_coupling_6j(int two_ja, int two_jb, int two_jc,
                          int two_jd, int two_je, int two_jf
                          );
                          */

/* Racah W coefficients:
 *
 *   W(a b c d; e f) = (-1)^{a+b+c+d} / a b e \
 *                                    \ d c f /
 *
 * exceptions: GSL_EDOM, GSL_EOVRFLW
 */
/*
int gsl_sf_coupling_RacahW_e(int two_ja, int two_jb, int two_jc,
                             int two_jd, int two_je, int two_jf,
                             gsl_sf_result * result
                             );
                             */
/*
double gsl_sf_coupling_RacahW(int two_ja, int two_jb, int two_jc,
                              int two_jd, int two_je, int two_jf
                              );
                              */

/* 9j Symbols:  / ja jb jc \
 *              | jd je jf |
 *              \ jg jh ji /
 *
 * exceptions: GSL_EDOM, GSL_EOVRFLW
 */
/*
int gsl_sf_coupling_9j_e(int two_ja, int two_jb, int two_jc,
                         int two_jd, int two_je, int two_jf,
                         int two_jg, int two_jh, int two_ji,
                         gsl_sf_result * result
                         );
                         */
/*
double gsl_sf_coupling_9j(int two_ja, int two_jb, int two_jc,
                          int two_jd, int two_je, int two_jf,
                          int two_jg, int two_jh, int two_ji
                          );
                          */


/* specfunc/gsl_sf_dawson.h
 */

/* Dawson's integral:
 *
 *   Exp[-x^2] Integral[ Exp[t^2], {t,0,x}]
 *
 * exceptions: GSL_EUNDRFLW;
 */
/* int     gsl_sf_dawson_e(double x, gsl_sf_result * result); */
double wrap_gsl_sf_dawson(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_dawson,args);
}


/* specfunc/gsl_sf_debye.h
 */

/* D_n(x) := n/x^n Integrate[t^n/(e^t - 1), {t,0,x}] */

/* D_1(x)
 *
 * exceptions: GSL_EDOM
 */
/* int     gsl_sf_debye_1_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_debye_1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_debye_1,args);
}

/* D_2(x)
 *
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int     gsl_sf_debye_2_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_debye_2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_debye_2,args);
}

/* D_3(x)
 *
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int     gsl_sf_debye_3_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_debye_3(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_debye_3,args);
}

/* D_4(x)
 *
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int     gsl_sf_debye_4_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_debye_4(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_debye_4,args);
}

/* D_5(x)
 *
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int     gsl_sf_debye_5_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_debye_5(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_debye_5,args);
}

/* D_6(x)
 *
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int     gsl_sf_debye_6_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_debye_6(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_debye_6,args);
}


/* specfunc/gsl_sf_dilog.h
 */

/* Real part of DiLogarithm(x), for real argument.
 * In Lewin's notation, this is Li_2(x).
 *
 *   Li_2(x) = - Re[ Integrate[ Log[1-s] / s, {s, 0, x}] ]
 *
 * The function in the complex plane has a branch point
 * at z = 1; we place the cut in the conventional way,
 * on [1, +infty). This means that the value for real x > 1
 * is a matter of definition; however, this choice does not
 * affect the real part and so is not relevant to the
 * interpretation of this implemented function.
 */
/* int     gsl_sf_dilog_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_dilog(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_dilog,args);
}

/* DiLogarithm(z), for complex argument z = x + i y.
 * Computes the principal branch.
 *
 * Recall that the branch cut is on the real axis with x > 1.
 * The imaginary part of the computed value on the cut is given
 * by -Pi*log(x), which is the limiting value taken approaching
 * from y < 0. This is a conventional choice, though there is no
 * true standardized choice.
 *
 * Note that there is no canonical way to lift the defining
 * contour to the full Riemann surface because of the appearance
 * of a "hidden branch point" at z = 0 on non-principal sheets.
 * Experts will know the simple algebraic prescription for
 * obtaining the sheet they want; non-experts will not want
 * to know anything about it. This is why GSL chooses to compute
 * only on the principal branch.
 */
 /*
int
gsl_sf_complex_dilog_xy_e(
  const double x,
  const double y,
  gsl_sf_result * result_re,
  gsl_sf_result * result_im
  );
  */

/* DiLogarithm(z), for complex argument z = r Exp[i theta].
 * Computes the principal branch, thereby assuming an
 * implicit reduction of theta to the range (-2 pi, 2 pi).
 *
 * If theta is identically zero, the imaginary part is computed
 * as if approaching from y > 0. For other values of theta no
 * special consideration is given, since it is assumed that
 * no other machine representations of multiples of pi will
 * produce y = 0 precisely. This assumption depends on some
 * subtle properties of the machine arithmetic, such as
 * correct rounding and monotonicity of the underlying
 * implementation of sin() and cos().
 *
 * This function is ok, but the interface is confusing since
 * it makes it appear that the branch structure is resolved.
 * Furthermore the handling of values close to the branch
 * cut is subtle. Perhap this interface should be deprecated.
 */
/*
int
gsl_sf_complex_dilog_e(
  const double r,
  const double theta,
  gsl_sf_result * result_re,
  gsl_sf_result * result_im
  );
  */

/* Spence integral; spence(s) := Li_2(1-s)
 *
 * This function has a branch point at 0; we place the
 * cut on (-infty,0). Because of our choice for the value
 * of Li_2(z) on the cut, spence(s) is continuous as
 * s approaches the cut from above. In other words,
 * we define spence(x) = spence(x + i 0+).
 */
/*
int
gsl_sf_complex_spence_xy_e(
  const double x,
  const double y,
  gsl_sf_result * real_sp,
  gsl_sf_result * imag_sp
  );
  */

  
/* specfunc/gsl_sf_elementary.h
 */

/* Multiplication.
 *
 * exceptions: GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int gsl_sf_multiply_e(const double x, const double y, gsl_sf_result * result); */
double wrap_gsl_sf_multiply(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_multiply,args);
}

/* Multiplication of quantities with associated errors.
 */
/* int gsl_sf_multiply_err_e(const double x, const double dx, const double y, const double dy, gsl_sf_result * result); */


/* specfunc/gsl_sf_ellint.h
 */

/* Legendre form of complete elliptic integrals
 *
 * K(k) = Integral[1/Sqrt[1 - k^2 Sin[t]^2], {t, 0, Pi/2}]
 * E(k) = Integral[  Sqrt[1 - k^2 Sin[t]^2], {t, 0, Pi/2}]
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_ellint_Kcomp_e(double k, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_ellint_Kcomp(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d_mode(gsl_sf_ellint_Kcomp,args);
}

/* int gsl_sf_ellint_Ecomp_e(double k, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_ellint_Ecomp(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d_mode(gsl_sf_ellint_Ecomp,args);
}

/* int gsl_sf_ellint_Pcomp_e(double k, double n, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_ellint_Pcomp(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d_mode(gsl_sf_ellint_Pcomp,args);
}

/* int gsl_sf_ellint_Dcomp_e(double k, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_ellint_Dcomp(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d_mode(gsl_sf_ellint_Dcomp,args);
}

/* Legendre form of incomplete elliptic integrals
 *
 * F(phi,k)   = Integral[1/Sqrt[1 - k^2 Sin[t]^2], {t, 0, phi}]
 * E(phi,k)   = Integral[  Sqrt[1 - k^2 Sin[t]^2], {t, 0, phi}]
 * P(phi,k,n) = Integral[(1 + n Sin[t]^2)^(-1)/Sqrt[1 - k^2 Sin[t]^2], {t, 0, phi}]
 * D(phi,k,n) = R_D(1-Sin[phi]^2, 1-k^2 Sin[phi]^2, 1.0)
 *
 * F: [Carlson, Numerische Mathematik 33 (1979) 1, (4.1)]
 * E: [Carlson, ", (4.2)]
 * P: [Carlson, ", (4.3)]
 * D: [Carlson, ", (4.4)]
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_ellint_F_e(double phi, double k, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_ellint_F(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d_mode(gsl_sf_ellint_F,args);
}

/* int gsl_sf_ellint_E_e(double phi, double k, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_ellint_E(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d_mode(gsl_sf_ellint_E,args);
}

/* int gsl_sf_ellint_P_e(double phi, double k, double n, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_ellint_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d_mode(gsl_sf_ellint_P,args);
}

/* int gsl_sf_ellint_D_e(double phi, double k, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_ellint_D(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d_mode(gsl_sf_ellint_D,args);
}

/* Carlson's symmetric basis of functions
 *
 * RC(x,y)   = 1/2 Integral[(t+x)^(-1/2) (t+y)^(-1)], {t,0,Inf}]
 * RD(x,y,z) = 3/2 Integral[(t+x)^(-1/2) (t+y)^(-1/2) (t+z)^(-3/2), {t,0,Inf}]
 * RF(x,y,z) = 1/2 Integral[(t+x)^(-1/2) (t+y)^(-1/2) (t+z)^(-1/2), {t,0,Inf}]
 * RJ(x,y,z,p) = 3/2 Integral[(t+x)^(-1/2) (t+y)^(-1/2) (t+z)^(-1/2) (t+p)^(-1), {t,0,Inf}]
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_ellint_RC_e(double x, double y, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_ellint_RC(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d_mode(gsl_sf_ellint_RC,args);
}

/* int gsl_sf_ellint_RD_e(double x, double y, double z, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_ellint_RD(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d_mode(gsl_sf_ellint_RD,args);
}

/* int gsl_sf_ellint_RF_e(double x, double y, double z, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_ellint_RF(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d_mode(gsl_sf_ellint_RF,args);
}

/* int gsl_sf_ellint_RJ_e(double x, double y, double z, double p, gsl_mode_t mode, gsl_sf_result * result); */
double wrap_gsl_sf_ellint_RJ(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_4d_mode(gsl_sf_ellint_RJ,args);
}


/* specfunc/gsl_sf_elljac.h
 */

/* Jacobian elliptic functions sn, dn, cn,
 * by descending Landen transformations
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_elljac_e(double u, double m, double * sn, double * cn, double * dn); */


/* specfunc/gsl_sf_erf.h
 */

/* Complementary Error Function
 * erfc(x) := 2/Sqrt[Pi] Integrate[Exp[-t^2], {t,x,Infinity}]
 */
/* int gsl_sf_erfc_e(double x, gsl_sf_result * result); */
double wrap_gsl_sf_erfc(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_erfc,args);
}

/* Log Complementary Error Function
 */
/* int gsl_sf_log_erfc_e(double x, gsl_sf_result * result); */
double wrap_gsl_sf_log_erfc(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_log_erfc,args);
}

/* Error Function
 * erf(x) := 2/Sqrt[Pi] Integrate[Exp[-t^2], {t,0,x}]
 */
/* int gsl_sf_erf_e(double x, gsl_sf_result * result); */
double wrap_gsl_sf_erf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_erf,args);
}

/* Probability functions:
 * Z(x) :  Abramowitz+Stegun 26.2.1
 * Q(x) :  Abramowitz+Stegun 26.2.3
 */
/* int gsl_sf_erf_Z_e(double x, gsl_sf_result * result); */
/* int gsl_sf_erf_Q_e(double x, gsl_sf_result * result); */
double wrap_gsl_sf_erf_Z(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_erf_Z,args);
}
double wrap_gsl_sf_erf_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_erf_Q,args);
}

/* Hazard function, also known as the inverse Mill's ratio.
 *
 *   H(x) := Z(x)/Q(x)
 *         = Sqrt[2/Pi] Exp[-x^2 / 2] / Erfc[x/Sqrt[2]]
 *
 * exceptions: GSL_EUNDRFLW
 */
/* int gsl_sf_hazard_e(double x, gsl_sf_result * result); */
double wrap_gsl_sf_hazard(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_hazard,args);
}


/* specfunc/gsl_sf_exp.h
 */

/* Provide an exp() function with GSL semantics,
 * i.e. with proper error checking, etc.
 *
 * exceptions: GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int gsl_sf_exp_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_exp(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_exp,args);
}

/* Exp(x)
 *
 * exceptions: GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int gsl_sf_exp_e10_e(const double x, gsl_sf_result_e10 * result); */

/* Exponentiate and multiply by a given factor:  y * Exp(x)
 *
 * exceptions: GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int gsl_sf_exp_mult_e(const double x, const double y, gsl_sf_result * result); */
double wrap_gsl_sf_exp_mult(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_exp_mult,args);
}

/* Exponentiate and multiply by a given factor:  y * Exp(x)
 *
 * exceptions: GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int gsl_sf_exp_mult_e10_e(const double x, const double y, gsl_sf_result_e10 * result); */

/* exp(x)-1
 *
 * exceptions: GSL_EOVRFLW
 */
/* int gsl_sf_expm1_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_expm1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_expm1,args);
}

/* (exp(x)-1)/x = 1 + x/2 + x^2/(2*3) + x^3/(2*3*4) + ...
 *
 * exceptions: GSL_EOVRFLW
 */
/* int gsl_sf_exprel_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_exprel(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_exprel,args);
}

/* 2(exp(x)-1-x)/x^2 = 1 + x/3 + x^2/(3*4) + x^3/(3*4*5) + ...
 *
 * exceptions: GSL_EOVRFLW
 */
/* int gsl_sf_exprel_2_e(double x, gsl_sf_result * result); */
double wrap_gsl_sf_exprel_2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_exprel_2,args);
}

/* Similarly for the N-th generalization of
 * the above. The so-called N-relative exponential
 *
 * exprel_N(x) = N!/x^N (exp(x) - Sum[x^k/k!, {k,0,N-1}])
 *             = 1 + x/(N+1) + x^2/((N+1)(N+2)) + ...
 *             = 1F1(1,1+N,x)
 */
/* int gsl_sf_exprel_n_e(const int n, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_exprel_n(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_exprel_n,args);
}

/* int gsl_sf_exprel_n_CF_e(const double n, const double x, gsl_sf_result * result); */

/* Exponentiate a quantity with an associated error.
 */
/* int gsl_sf_exp_err_e(const double x, const double dx, gsl_sf_result * result); */

/* Exponentiate a quantity with an associated error.
 */
/* int gsl_sf_exp_err_e10_e(const double x, const double dx, gsl_sf_result_e10 * result); */

/* Exponentiate and multiply by a given factor:  y * Exp(x),
 * for quantities with associated errors.
 *
 * exceptions: GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int gsl_sf_exp_mult_err_e(const double x, const double dx, const double y, const double dy, gsl_sf_result * result); */

/* Exponentiate and multiply by a given factor:  y * Exp(x),
 * for quantities with associated errors.
 *
 * exceptions: GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int gsl_sf_exp_mult_err_e10_e(const double x, const double dx, const double y, const double dy, gsl_sf_result_e10 * result); */


/* specfunc/gsl_sf_expint.h
 */

/* E_1(x) := Re[ Integrate[ Exp[-xt]/t, {t,1,Infinity}] ]
 *
 * x != 0.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int     gsl_sf_expint_E1_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_expint_E1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if (args->dblp[0] != 0.0){
        return wrap_dbl_1d(gsl_sf_expint_E1,args);
    } else {
        return *(double *)args->missval;
    }
}

/* E_2(x) := Re[ Integrate[ Exp[-xt]/t^2, {t,1,Infinity}] ]
 *
 * x != 0.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int     gsl_sf_expint_E2_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_expint_E2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if (args->dblp[0] != 0.0){
        return wrap_dbl_1d(gsl_sf_expint_E2,args);
    } else {
        return *(double *)args->missval;
    }
}

/* E_n(x) := Re[ Integrate[ Exp[-xt]/t^n, {t,1,Infinity}] ]
 *
 * x != 0.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int     gsl_sf_expint_En_e(const int n, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_expint_En(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if (args->dblp[0] != 0.0){
        return wrap_dbl_1i1d(gsl_sf_expint_En,args);
    } else {
        return *(double *)args->missval;
    }
}

/* E_1_scaled(x) := exp(x) E_1(x)
 *
 * x != 0.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int     gsl_sf_expint_E1_scaled_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_expint_E1_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if (args->dblp[0] != 0.0){
        return wrap_dbl_1d(gsl_sf_expint_E1_scaled,args);
    } else {
        return *(double *)args->missval;
    }
}

/* E_2_scaled(x) := exp(x) E_2(x)
 *
 * x != 0.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int     gsl_sf_expint_E2_scaled_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_expint_E2_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if (args->dblp[0] != 0.0){
        return wrap_dbl_1d(gsl_sf_expint_E2_scaled,args);
    } else {
        return *(double *)args->missval;
    }
}

/* E_n_scaled(x) := exp(x) E_n(x)
 *
 * x != 0.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int     gsl_sf_expint_En_scaled_e(const int n, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_expint_En_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if (args->dblp[0] != 0.0){
        return wrap_dbl_1i1d(gsl_sf_expint_En_scaled,args);
    } else {
        return *(double *)args->missval;
    }
}

/* Ei(x) := - PV Integrate[ Exp[-t]/t, {t,-x,Infinity}]
 *       :=   PV Integrate[ Exp[t]/t, {t,-Infinity,x}]
 *
 * x != 0.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int     gsl_sf_expint_Ei_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_expint_Ei(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if (args->dblp[0] != 0.0){
        return wrap_dbl_1d(gsl_sf_expint_Ei,args);
    } else {
        return *(double *)args->missval;
    }
}

/* Ei_scaled(x) := exp(-x) Ei(x)
 *
 * x != 0.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int     gsl_sf_expint_Ei_scaled_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_expint_Ei_scaled(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if (args->dblp[0] != 0.0){
        return wrap_dbl_1d(gsl_sf_expint_Ei_scaled,args);
    } else {
        return *(double *)args->missval;
    }
}

/* Shi(x) := Integrate[ Sinh[t]/t, {t,0,x}]
 *
 * exceptions: GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int     gsl_sf_Shi_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_Shi(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_Shi,args);
}

/* Chi(x) := Re[ M_EULER + log(x) + Integrate[(Cosh[t]-1)/t, {t,0,x}] ]
 *
 * x != 0.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int     gsl_sf_Chi_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_Chi(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if (args->dblp[0] != 0.0){
        return wrap_dbl_1d(gsl_sf_Chi,args);
    } else {
        return *(double *)args->missval;
    }
}

/* Ei_3(x) := Integral[ Exp[-t^3], {t,0,x}]
 *
 * x >= 0.0
 * exceptions: GSL_EDOM
 */
/* int     gsl_sf_expint_3_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_expint_3(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if (args->dblp[0] >= 0.0){
        return wrap_dbl_1d(gsl_sf_expint_3,args);
    } else {
        return *(double *)args->missval;
    }
}

/* Si(x) := Integrate[ Sin[t]/t, {t,0,x}]
 */
/* int     gsl_sf_Si_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_Si(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_Si,args);
}

/* Ci(x) := -Integrate[ Cos[t]/t, {t,x,Infinity}]
 *
 * x > 0.0
 * exceptions: GSL_EDOM 
 */
/* int     gsl_sf_Ci_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_Ci(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if (args->dblp[0] > 0.0){
        return wrap_dbl_1d(gsl_sf_Ci,args);
    } else {
        return *(double *)args->missval;
    }
}

/* AtanInt(x) := Integral[ Arctan[t]/t, {t,0,x}]
 *
 */
/* int     gsl_sf_atanint_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_atanint(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_atanint,args);
}


/* specfunc/gsl_sf_fermi_dirac.h
 */

/* Complete Fermi-Dirac Integrals:
 *
 *  F_j(x)   := 1/Gamma[j+1] Integral[ t^j /(Exp[t-x] + 1), {t,0,Infinity}]
 *
 *
 * Incomplete Fermi-Dirac Integrals:
 *
 *  F_j(x,b) := 1/Gamma[j+1] Integral[ t^j /(Exp[t-x] + 1), {t,b,Infinity}]
 */

/* Complete integral F_{-1}(x) = e^x / (1 + e^x)
 *
 * exceptions: GSL_EUNDRFLW
 */
/* int     gsl_sf_fermi_dirac_m1_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_fermi_dirac_m1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_fermi_dirac_m1,args);
}

/* Complete integral F_0(x) = ln(1 + e^x)
 *
 * exceptions: GSL_EUNDRFLW
 */
/* int     gsl_sf_fermi_dirac_0_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_fermi_dirac_0(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_fermi_dirac_0,args);
}

/* Complete integral F_1(x)
 *
 * exceptions: GSL_EUNDRFLW, GSL_EOVRFLW
 */
/* int     gsl_sf_fermi_dirac_1_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_fermi_dirac_1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_fermi_dirac_1,args);
}

/* Complete integral F_2(x)
 *
 * exceptions: GSL_EUNDRFLW, GSL_EOVRFLW
 */
/* int     gsl_sf_fermi_dirac_2_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_fermi_dirac_2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_fermi_dirac_2,args);
}

/* Complete integral F_j(x)
 * for integer j
 *
 * exceptions: GSL_EUNDRFLW, GSL_EOVRFLW
 */
/* int     gsl_sf_fermi_dirac_int_e(const int j, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_fermi_dirac_int(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_fermi_dirac_int,args);
}

/* Complete integral F_{-1/2}(x)
 *
 * exceptions: GSL_EUNDRFLW, GSL_EOVRFLW
 */
/* int     gsl_sf_fermi_dirac_mhalf_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_fermi_dirac_mhalf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_fermi_dirac_mhalf,args);
}

/* Complete integral F_{1/2}(x)
 *
 * exceptions: GSL_EUNDRFLW, GSL_EOVRFLW
 */
/* int     gsl_sf_fermi_dirac_half_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_fermi_dirac_half(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_fermi_dirac_half,args);
}

/* Complete integral F_{3/2}(x)
 *
 * exceptions: GSL_EUNDRFLW, GSL_EOVRFLW
 */
/* int     gsl_sf_fermi_dirac_3half_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_fermi_dirac_3half(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_fermi_dirac_3half,args);
}

/* Incomplete integral F_0(x,b) = ln(1 + e^(b-x)) - (b-x)
 *
 * exceptions: GSL_EUNDRFLW, GSL_EDOM
 */
/* int     gsl_sf_fermi_dirac_inc_0_e(const double x, const double b, gsl_sf_result * result); */
double wrap_gsl_sf_fermi_dirac_inc_0(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_fermi_dirac_inc_0,args);
}


/* specfunc/gsl_sf_gamma.h
 */

/* Log[Gamma(x)], x not a negative integer
 * Uses real Lanczos method.
 * Returns the real part of Log[Gamma[x]] when x < 0,
 * i.e. Log[|Gamma[x]|].
 *
 * exceptions: GSL_EDOM, GSL_EROUND
 */
/* int gsl_sf_lngamma_e(double x, gsl_sf_result * result); */
double wrap_gsl_sf_lngamma(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_lngamma,args);
}

/* Log[Gamma(x)], x not a negative integer
 * Uses real Lanczos method. Determines
 * the sign of Gamma[x] as well as Log[|Gamma[x]|] for x < 0.
 * So Gamma[x] = sgn * Exp[result_lg].
 *
 * exceptions: GSL_EDOM, GSL_EROUND
 */
/* int gsl_sf_lngamma_sgn_e(double x, gsl_sf_result * result_lg, double *sgn); */

/* Gamma(x), x not a negative integer
 * Uses real Lanczos method.
 *
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EROUND
 */
/* int gsl_sf_gamma_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_gamma(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_gamma,args);
}

/* Regulated Gamma Function, x > 0
 * Gamma^*(x) = Gamma(x)/(Sqrt[2Pi] x^(x-1/2) exp(-x))
 *            = (1 + 1/(12x) + ...),  x->Inf
 * A useful suggestion of Temme.
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_gammastar_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_gammastar(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if (args->dblp[0] > 0.0){
        return wrap_dbl_1d(gsl_sf_gammastar,args);
    } else {
        return *(double *)args->missval;
    }
}

/* 1/Gamma(x)
 * Uses real Lanczos method.
 *
 * exceptions: GSL_EUNDRFLW, GSL_EROUND
 */
/* int gsl_sf_gammainv_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_gammainv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_gammainv,args);
}

/* Log[Gamma(z)] for z complex, z not a negative integer
 * Uses complex Lanczos method. Note that the phase part (arg)
 * is not well-determined when |z| is very large, due
 * to inevitable roundoff in restricting to (-Pi,Pi].
 * This will raise the GSL_ELOSS exception when it occurs.
 * The absolute value part (lnr), however, never suffers.
 *
 * Calculates:
 *   lnr = log|Gamma(z)|
 *   arg = arg(Gamma(z))  in (-Pi, Pi]
 *
 * exceptions: GSL_EDOM, GSL_ELOSS
 */
/* int gsl_sf_lngamma_complex_e(double zr, double zi, gsl_sf_result * lnr, gsl_sf_result * arg); */

/* x^n / n!
 *
 * x >= 0.0, n >= 0
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int gsl_sf_taylorcoeff_e(const int n, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_taylorcoeff(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if ((args->dblp[0] >= 0.0) && (args->intp[0] >= 0)){
        return wrap_dbl_1i1d(gsl_sf_taylorcoeff,args);
    } else {
        return *(double *)args->missval;
    }
}

/* n!
 *
 * exceptions: GSL_EDOM, GSL_EOVRFLW
 */
/* int gsl_sf_fact_e(const unsigned int n, gsl_sf_result * result); */
double wrap_gsl_sf_fact(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ui(gsl_sf_fact,args);
}

/* n!! = n(n-2)(n-4) ... 
 *
 * exceptions: GSL_EDOM, GSL_EOVRFLW
 */
/* int gsl_sf_doublefact_e(const unsigned int n, gsl_sf_result * result); */
double wrap_gsl_sf_doublefact(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ui(gsl_sf_doublefact,args);
}

/* log(n!) 
 * Faster than ln(Gamma(n+1)) for n < 170; defers for larger n.
 */
/* int gsl_sf_lnfact_e(const unsigned int n, gsl_sf_result * result); */
double wrap_gsl_sf_lnfact(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ui(gsl_sf_lnfact,args);
}

/* log(n!!) 
 */
/* int gsl_sf_lndoublefact_e(const unsigned int n, gsl_sf_result * result); */
double wrap_gsl_sf_lndoublefact(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ui(gsl_sf_lndoublefact,args);
}

/* log(n choose m)
 *
 * exceptions: GSL_EDOM 
 */
/* int gsl_sf_lnchoose_e(unsigned int n, unsigned int m, gsl_sf_result * result); */
double wrap_gsl_sf_lnchoose(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ui(gsl_sf_lnchoose,args);
}

/* n choose m
 *
 * exceptions: GSL_EDOM, GSL_EOVRFLW
 */
/* int gsl_sf_choose_e(unsigned int n, unsigned int m, gsl_sf_result * result); */
double wrap_gsl_sf_choose(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2ui(gsl_sf_choose,args);
}

/* Logarithm of Pochhammer (Apell) symbol
 *   log( (a)_x )
 *   where (a)_x := Gamma[a + x]/Gamma[a]
 *
 * a > 0, a+x > 0
 *
 * exceptions:  GSL_EDOM
 */
/* int gsl_sf_lnpoch_e(const double a, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_lnpoch(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if ((args->dblp[0] > 0.0) && (args->dblp[0]+args->dblp[1] > 0.0)){
        return wrap_dbl_2d(gsl_sf_lnpoch,args);
    } else {
        return *(double *)args->missval;
    }
}

/* Logarithm of Pochhammer (Apell) symbol, with sign information.
 *   result = log( |(a)_x| )
 *   sgn    = sgn( (a)_x )
 *   where (a)_x := Gamma[a + x]/Gamma[a]
 *
 * a != neg integer, a+x != neg integer
 *
 * exceptions:  GSL_EDOM
 */
/* int gsl_sf_lnpoch_sgn_e(const double a, const double x, gsl_sf_result * result, double * sgn); */

/* Pochhammer (Apell) symbol
 *   (a)_x := Gamma[a + x]/Gamma[x]
 *
 * a != neg integer, a+x != neg integer
 *
 * exceptions:  GSL_EDOM, GSL_EOVRFLW
 */
/* int gsl_sf_poch_e(const double a, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_poch(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_poch,args);
}

/* Relative Pochhammer (Apell) symbol
 *   ((a,x) - 1)/x
 *   where (a,x) = (a)_x := Gamma[a + x]/Gamma[a]
 *
 * exceptions:  GSL_EDOM
 */
/* int gsl_sf_pochrel_e(const double a, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_pochrel(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_pochrel,args);
}

/* Normalized Incomplete Gamma Function
 *
 * Q(a,x) = 1/Gamma(a) Integral[ t^(a-1) e^(-t), {t,x,Infinity} ]
 *
 * a >= 0, x >= 0
 *   Q(a,0) := 1
 *   Q(0,x) := 0, x != 0
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_gamma_inc_Q_e(const double a, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_gamma_inc_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if ((args->dblp[0] >= 0.0) && (args->dblp[1] >= 0.0)){
        return wrap_dbl_2d(gsl_sf_gamma_inc_Q,args);
    } else {
        return *(double *)args->missval;
    }
}

/* Complementary Normalized Incomplete Gamma Function
 *
 * P(a,x) = 1/Gamma(a) Integral[ t^(a-1) e^(-t), {t,0,x} ]
 *
 * a > 0, x >= 0
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_gamma_inc_P_e(const double a, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_gamma_inc_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if ((args->dblp[0] > 0.0) && (args->dblp[1] >= 0.0)){
        return wrap_dbl_2d(gsl_sf_gamma_inc_P,args);
    } else {
        return *(double *)args->missval;
    }
}

/* Non-normalized Incomplete Gamma Function
 *
 * Gamma(a,x) := Integral[ t^(a-1) e^(-t), {t,x,Infinity} ]
 *
 * x >= 0.0
 *   Gamma(a, 0) := Gamma(a)
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_gamma_inc_e(const double a, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_gamma_inc(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if (args->dblp[1] >= 0.0){
        return wrap_dbl_2d(gsl_sf_gamma_inc,args);
    } else {
        return *(double *)args->missval;
    }
}

/* Logarithm of Beta Function
 * Log[B(a,b)]
 *
 * a > 0, b > 0
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_lnbeta_e(const double a, const double b, gsl_sf_result * result); */
double wrap_gsl_sf_lnbeta(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if ((args->dblp[0] > 0.0) && (args->dblp[1] > 0.0)){
        return wrap_dbl_2d(gsl_sf_lnbeta,args);
    } else {
        return *(double *)args->missval;
    }
}

/* int gsl_sf_lnbeta_sgn_e(const double x, const double y, gsl_sf_result * result, double * sgn); */

/* Beta Function
 * B(a,b)
 *
 * a > 0, b > 0
 * exceptions: GSL_EDOM, GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int gsl_sf_beta_e(const double a, const double b, gsl_sf_result * result); */
double wrap_gsl_sf_beta(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if ((args->dblp[0] > 0.0) && (args->dblp[1] > 0.0)){
        return wrap_dbl_2d(gsl_sf_beta,args);
    } else {
        return *(double *)args->missval;
    }
}

/* Normalized Incomplete Beta Function
 * B_x(a,b)/B(a,b)
 *
 * a > 0, b > 0, 0 <= x <= 1
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int gsl_sf_beta_inc_e(const double a, const double b, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_beta_inc(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if ((args->dblp[0] > 0.0) && (args->dblp[1] > 0.0) && (args->dblp[2] >= 0.0) && (args->dblp[2] <= 1.0)){
        return wrap_dbl_3d(gsl_sf_beta_inc,args);
    } else {
        return *(double *)args->missval;
    }
}

/* The maximum x such that gamma(x) is not
 * considered an overflow.
 */
/*
#define GSL_SF_GAMMA_XMAX  171.0

The maximum n such that gsl_sf_fact(n) does not give an overflow.
#define GSL_SF_FACT_NMAX 170

The maximum n such that gsl_sf_doublefact(n) does not give an overflow.
#define GSL_SF_DOUBLEFACT_NMAX 297
*/

/* specfunc/gsl_sf_gegenbauer.h
 */

/* Evaluate Gegenbauer polynomials
 * using explicit representations.
 */
/* int gsl_sf_gegenpoly_1_e(double lambda, double x, gsl_sf_result * result); */
/* int gsl_sf_gegenpoly_2_e(double lambda, double x, gsl_sf_result * result); */
/* int gsl_sf_gegenpoly_3_e(double lambda, double x, gsl_sf_result * result); */
double wrap_gsl_sf_gegenpoly_1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_gegenpoly_1,args);
}
double wrap_gsl_sf_gegenpoly_2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_gegenpoly_2,args);
}
double wrap_gsl_sf_gegenpoly_3(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_gegenpoly_3,args);
}

/* Evaluate Gegenbauer polynomials.
 *
 * lambda > -1/2, n >= 0
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_gegenpoly_n_e(int n, double lambda, double x, gsl_sf_result * result); */
double wrap_gsl_sf_gegenpoly_n(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i2d(gsl_sf_gegenpoly_n,args);
}

/* Calculate array of Gegenbauer polynomials
 * for n = (0, 1, 2, ... nmax)
 *
 * lambda > -1/2, nmax >= 0
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_gegenpoly_array(int nmax, double lambda, double x, double * result_array); */


/* gsl_sf_hermite.h
 */

/* int gsl_sf_hermite_prob_e(const int n, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_hermite_prob(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_hermite_prob,args);
}

/* int gsl_sf_hermite_prob_der_e(const int m, const int n, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_hermite_prob_der(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2i1d(gsl_sf_hermite_prob_der,args);
}

/* int gsl_sf_hermite_phys_e(const int n, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_hermite_phys(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_hermite_phys,args);
}

/* int gsl_sf_hermite_phys_der_e(const int m, const int n, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_hermite_phys_der(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2i1d(gsl_sf_hermite_phys_der,args);
}

/* int gsl_sf_hermite_func_e(const int n, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_hermite_func(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_hermite_func,args);
}

/*
int gsl_sf_hermite_prob_array(const int nmax, const double x, double * result_array);
int gsl_sf_hermite_prob_array_der(const int m, const int nmax, const double x, double * result_array);
int gsl_sf_hermite_prob_der_array(const int mmax, const int n, const double x, double * result_array);
*/

/* int gsl_sf_hermite_prob_series_e(const int n, const double x, const double * a, gsl_sf_result * result); */
/* double gsl_sf_hermite_prob_series(const int n, const double x, const double * a); */

/*
int gsl_sf_hermite_phys_array(const int nmax, const double x, double * result_array);
int gsl_sf_hermite_phys_array_der(const int m, const int nmax, const double x, double * result_array);
int gsl_sf_hermite_phys_der_array(const int mmax, const int n, const double x, double * result_array);
*/

/* int gsl_sf_hermite_phys_series_e(const int n, const double x, const double * a, gsl_sf_result * result); */
/* double gsl_sf_hermite_phys_series(const int n, const double x, const double * a); */

/* int gsl_sf_hermite_func_array(const int nmax, const double x, double * result_array); */
/* int gsl_sf_hermite_func_series_e(const int n, const double x, const double * a, gsl_sf_result * result); */
/* double gsl_sf_hermite_func_series(const int n, const double x, const double * a); */

/* int gsl_sf_hermite_func_der_e(const int m, const int n, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_hermite_func_der(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2i1d(gsl_sf_hermite_func_der,args);
}

/* int gsl_sf_hermite_prob_zero_e(const int n, const int s, gsl_sf_result * result); */
double wrap_gsl_sf_hermite_prob_zero(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2i(gsl_sf_hermite_prob_zero,args);
}

/* int gsl_sf_hermite_phys_zero_e(const int n, const int s, gsl_sf_result * result); */
double wrap_gsl_sf_hermite_phys_zero(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2i(gsl_sf_hermite_phys_zero,args);
}

/* int gsl_sf_hermite_func_zero_e(const int n, const int s, gsl_sf_result * result); */
double wrap_gsl_sf_hermite_func_zero(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2i(gsl_sf_hermite_func_zero,args);
}


/* specfunc/gsl_sf_hyperg.h
 */

/* Hypergeometric function related to Bessel functions
 * 0F1[c,x] =
 *            Gamma[c]    x^(1/2(1-c)) I_{c-1}(2 Sqrt[x])
 *            Gamma[c] (-x)^(1/2(1-c)) J_{c-1}(2 Sqrt[-x])
 *
 * exceptions: GSL_EOVRFLW, GSL_EUNDRFLW
 */
/* int gsl_sf_hyperg_0F1_e(double c, double x, gsl_sf_result * result); */
double wrap_gsl_sf_hyperg_0F1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_hyperg_0F1,args);
}

/* Confluent hypergeometric function  for integer parameters.
 * 1F1[m,n,x] = M(m,n,x)
 */
/* int gsl_sf_hyperg_1F1_int_e(const int m, const int n, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_hyperg_1F1_int(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2i1d(gsl_sf_hyperg_1F1_int,args);
}

/* Confluent hypergeometric function.
 * 1F1[a,b,x] = M(a,b,x)
 */
/* int gsl_sf_hyperg_1F1_e(const double a, const double b, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_hyperg_1F1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_sf_hyperg_1F1,args);
}

/* Confluent hypergeometric function for integer parameters.
 * U(m,n,x)
 */
/* int gsl_sf_hyperg_U_int_e(const int m, const int n, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_hyperg_U_int(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2i1d(gsl_sf_hyperg_U_int,args);
}

/* Confluent hypergeometric function for integer parameters.
 * U(m,n,x)
 */
/* int gsl_sf_hyperg_U_int_e10_e(const int m, const int n, const double x, gsl_sf_result_e10 * result); */

/* Confluent hypergeometric function.
 * U(a,b,x)
 */
/* int gsl_sf_hyperg_U_e(const double a, const double b, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_hyperg_U(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_sf_hyperg_U,args);
}

/* Confluent hypergeometric function.
 * U(a,b,x)
 */
/* int gsl_sf_hyperg_U_e10_e(const double a, const double b, const double x, gsl_sf_result_e10 * result); */

/* Gauss hypergeometric function 2F1[a,b,c,x]
 * |x| < 1
 */
/* int gsl_sf_hyperg_2F1_e(double a, double b, const double c, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_hyperg_2F1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_4d(gsl_sf_hyperg_2F1,args);
}

/* Gauss hypergeometric function
 * 2F1[aR + I aI, aR - I aI, c, x]
 * |x| < 1
 */
/* int gsl_sf_hyperg_2F1_conj_e(const double aR, const double aI, const double c, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_hyperg_2F1_conj(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_4d(gsl_sf_hyperg_2F1_conj,args);
}

/* Renormalized Gauss hypergeometric function
 * 2F1[a,b,c,x] / Gamma[c]
 * |x| < 1
 */
/* int gsl_sf_hyperg_2F1_renorm_e(const double a, const double b, const double c, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_hyperg_2F1_renorm(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_4d(gsl_sf_hyperg_2F1_renorm,args);
}

/* Renormalized Gauss hypergeometric function
 * 2F1[aR + I aI, aR - I aI, c, x] / Gamma[c]
 * |x| < 1
 */
/* int gsl_sf_hyperg_2F1_conj_renorm_e(const double aR, const double aI, const double c, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_hyperg_2F1_conj_renorm(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_4d(gsl_sf_hyperg_2F1_conj_renorm,args);
}

/* Mysterious hypergeometric function. The series representation
 * is a divergent hypergeometric series. However, for x < 0 we
 * have 2F0(a,b,x) = (-1/x)^a U(a,1+a-b,-1/x)
 *
 * exceptions: GSL_EDOM
 */
/* int     gsl_sf_hyperg_2F0_e(const double a, const double b, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_hyperg_2F0(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_sf_hyperg_2F0,args);
}


/* specfunc/gsl_sf_laguerre.h
 */

/* L^a_n(x) = (a+1)_n / n! 1F1(-n,a+1,x) */

/* Evaluate generalized Laguerre polynomials
 * using explicit representations.
 */
/* int gsl_sf_laguerre_1_e(const double a, const double x, gsl_sf_result * result); */
/* int gsl_sf_laguerre_2_e(const double a, const double x, gsl_sf_result * result); */
/* int gsl_sf_laguerre_3_e(const double a, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_laguerre_1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_laguerre_1,args);
}
double wrap_gsl_sf_laguerre_2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_laguerre_2,args);
}
double wrap_gsl_sf_laguerre_3(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_laguerre_3,args);
}

/* Evaluate generalized Laguerre polynomials.
 *
 * a > -1.0
 * n >= 0
 * exceptions: GSL_EDOM
 */
/* int     gsl_sf_laguerre_n_e(const int n, const double a, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_laguerre_n(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i2d(gsl_sf_laguerre_n,args);
}


/* specfunc/gsl_sf_lambert.h
 */

/* Lambert's Function W_0(x)
 *
 * W_0(x) is the principal branch of the
 * implicit function defined by W e^W = x.
 *
 * -1/E < x < \infty
 *
 * exceptions: GSL_EMAXITER;
 */
/* int     gsl_sf_lambert_W0_e(double x, gsl_sf_result * result); */
double wrap_gsl_sf_lambert_W0(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_lambert_W0,args);
}

/* Lambert's Function W_{-1}(x)
 *
 * W_{-1}(x) is the second real branch of the
 * implicit function defined by W e^W = x.
 * It agrees with W_0(x) when x >= 0.
 *
 * -1/E < x < \infty
 *
 * exceptions: GSL_MAXITER;
 */
/* int     gsl_sf_lambert_Wm1_e(double x, gsl_sf_result * result); */
double wrap_gsl_sf_lambert_Wm1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_lambert_Wm1,args);
}


/* specfunc/gsl_sf_legendre.h
 */

/* P_l(x)   l >= 0; |x| <= 1
 *
 * exceptions: GSL_EDOM
 */
/* int     gsl_sf_legendre_Pl_e(const int l, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_legendre_Pl(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_legendre_Pl,args);
}

/* P_l(x) for l=0,...,lmax; |x| <= 1
 *
 * exceptions: GSL_EDOM
 */
arr wrap_gsl_sf_legendre_Pl_array(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_sf_arr_lmx1d(gsl_sf_legendre_Pl_array,args);
}


/* P_l(x) and P_l'(x) for l=0,...,lmax; |x| <= 1
 *
 * exceptions: GSL_EDOM
 */
/*
int gsl_sf_legendre_Pl_deriv_array(
  const int lmax, const double x,
  double * result_array,
  double * result_deriv_array
  );
  */

/* P_l(x), l=1,2,3
 */
/* int gsl_sf_legendre_P1_e(double x, gsl_sf_result * result); */
/* int gsl_sf_legendre_P2_e(double x, gsl_sf_result * result); */
/* int gsl_sf_legendre_P3_e(double x, gsl_sf_result * result); */
double wrap_gsl_sf_legendre_P1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_legendre_P1,args);
}
double wrap_gsl_sf_legendre_P2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_legendre_P2,args);
}
double wrap_gsl_sf_legendre_P3(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_legendre_P3,args);
}

/* Q_0(x), x > -1, x != 1
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_legendre_Q0_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_legendre_Q0(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_legendre_Q0,args);
}

/* Q_1(x), x > -1, x != 1
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_legendre_Q1_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_legendre_Q1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_legendre_Q1,args);
}

/* Q_l(x), x > -1, x != 1, l >= 0
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_legendre_Ql_e(const int l, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_legendre_Ql(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_legendre_Ql,args);
}

/* P_l^m(x)  m >= 0; l >= m; |x| <= 1.0
 *
 * Note that this function grows combinatorially with l.
 * Therefore we can easily generate an overflow for l larger
 * than about 150.
 *
 * There is no trouble for small m, but when m and l are both large,
 * then there will be trouble. Rather than allow overflows, these
 * functions refuse to calculate when they can sense that l and m are
 * too big.
 *
 * If you really want to calculate a spherical harmonic, then DO NOT
 * use this. Instead use legendre_sphPlm() below, which  uses a similar
 * recursion, but with the normalized functions.
 *
 * exceptions: GSL_EDOM, GSL_EOVRFLW
 */
/* int     gsl_sf_legendre_Plm_e(const int l, const int m, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_legendre_Plm(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2i1d(gsl_sf_legendre_Plm,args);
}

/* P_l^m(x)  m >= 0; l >= m; |x| <= 1.0
 * l=|m|,...,lmax
 *
 * exceptions: GSL_EDOM, GSL_EOVRFLW
 */
/*
int gsl_sf_legendre_Plm_array(
  const int lmax, const int m, const double x,
  double * result_array
  );
  */

/* P_l^m(x)  and d(P_l^m(x))/dx;  m >= 0; lmax >= m; |x| <= 1.0
 * l=|m|,...,lmax
 *
 * exceptions: GSL_EDOM, GSL_EOVRFLW
 */
/* 
int gsl_sf_legendre_Plm_deriv_array(
  const int lmax, const int m, const double x,
  double * result_array,
  double * result_deriv_array
  );
  */

/* P_l^m(x), normalized properly for use in spherical harmonics
 * m >= 0; l >= m; |x| <= 1.0
 *
 * There is no overflow problem, as there is for the
 * standard normalization of P_l^m(x).
 *
 * Specifically, it returns:
 *
 *        sqrt((2l+1)/(4pi)) sqrt((l-m)!/(l+m)!) P_l^m(x)
 *
 * exceptions: GSL_EDOM
 */
/* int     gsl_sf_legendre_sphPlm_e(const int l, int m, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_legendre_sphPlm(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2i1d(gsl_sf_legendre_sphPlm,args);
}

/* sphPlm(l,m,x) values
 * m >= 0; l >= m; |x| <= 1.0
 * l=|m|,...,lmax
 *
 * exceptions: GSL_EDOM
 */
/*
int gsl_sf_legendre_sphPlm_array(
  const int lmax, int m, const double x,
  double * result_array
  );
  */

/* sphPlm(l,m,x) and d(sphPlm(l,m,x))/dx values
 * m >= 0; l >= m; |x| <= 1.0
 * l=|m|,...,lmax
 *
 * exceptions: GSL_EDOM
 */
/*
int gsl_sf_legendre_sphPlm_deriv_array(
  const int lmax, const int m, const double x,
  double * result_array,
  double * result_deriv_array
  );
  */

/* size of result_array[] needed for the array versions of Plm
 * (lmax - m + 1)
 */
/* int gsl_sf_legendre_array_size(const int lmax, const int m); */

/* Irregular Spherical Conical Function
 * P^{1/2}_{-1/2 + I lambda}(x)
 *
 * x > -1.0
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_conicalP_half_e(const double lambda, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_conicalP_half(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_conicalP_half,args);
}

/* Regular Spherical Conical Function
 * P^{-1/2}_{-1/2 + I lambda}(x)
 *
 * x > -1.0
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_conicalP_mhalf_e(const double lambda, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_conicalP_mhalf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_conicalP_mhalf,args);
}

/* Conical Function
 * P^{0}_{-1/2 + I lambda}(x)
 *
 * x > -1.0
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_conicalP_0_e(const double lambda, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_conicalP_0(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_conicalP_0,args);
}

/* Conical Function
 * P^{1}_{-1/2 + I lambda}(x)
 *
 * x > -1.0
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_conicalP_1_e(const double lambda, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_conicalP_1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_conicalP_1,args);
}

/* Regular Spherical Conical Function
 * P^{-1/2-l}_{-1/2 + I lambda}(x)
 *
 * x > -1.0, l >= -1
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_conicalP_sph_reg_e(const int l, const double lambda, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_conicalP_sph_reg(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i2d(gsl_sf_conicalP_sph_reg,args);
}

/* Regular Cylindrical Conical Function
 * P^{-m}_{-1/2 + I lambda}(x)
 *
 * x > -1.0, m >= -1
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_conicalP_cyl_reg_e(const int m, const double lambda, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_conicalP_cyl_reg(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i2d(gsl_sf_conicalP_cyl_reg,args);
}

/* The following spherical functions are specializations
 * of Legendre functions which give the regular eigenfunctions
 * of the Laplacian on a 3-dimensional hyperbolic space.
 * Of particular interest is the flat limit, which is
 * Flat-Lim := {lambda->Inf, eta->0, lambda*eta fixed}.
 */
  
/* Zeroth radial eigenfunction of the Laplacian on the
 * 3-dimensional hyperbolic space.
 *
 * legendre_H3d_0(lambda,eta) := sin(lambda*eta)/(lambda*sinh(eta))
 * 
 * Normalization:
 * Flat-Lim legendre_H3d_0(lambda,eta) = j_0(lambda*eta)
 *
 * eta >= 0.0
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_legendre_H3d_0_e(const double lambda, const double eta, gsl_sf_result * result); */
double wrap_gsl_sf_legendre_H3d_0(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_legendre_H3d_0,args);
}

/* First radial eigenfunction of the Laplacian on the
 * 3-dimensional hyperbolic space.
 *
 * legendre_H3d_1(lambda,eta) :=
 *    1/sqrt(lambda^2 + 1) sin(lam eta)/(lam sinh(eta))
 *    (coth(eta) - lambda cot(lambda*eta))
 * 
 * Normalization:
 * Flat-Lim legendre_H3d_1(lambda,eta) = j_1(lambda*eta)
 *
 * eta >= 0.0
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_legendre_H3d_1_e(const double lambda, const double eta, gsl_sf_result * result); */
double wrap_gsl_sf_legendre_H3d_1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_legendre_H3d_1,args);
}

/* l'th radial eigenfunction of the Laplacian on the
 * 3-dimensional hyperbolic space.
 *
 * Normalization:
 * Flat-Lim legendre_H3d_l(l,lambda,eta) = j_l(lambda*eta)
 *
 * eta >= 0.0, l >= 0
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_legendre_H3d_e(const int l, const double lambda, const double eta, gsl_sf_result * result); */
double wrap_gsl_sf_legendre_H3d(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i2d(gsl_sf_legendre_H3d,args);
}

/* Array of H3d(ell),  0 <= ell <= lmax
 */
/* int gsl_sf_legendre_H3d_array(const int lmax, const double lambda, const double eta, double * result_array); */

/* associated legendre P_{lm} routines */

/*
typedef enum
{
  GSL_SF_LEGENDRE_SCHMIDT,
  GSL_SF_LEGENDRE_SPHARM,
  GSL_SF_LEGENDRE_FULL,
  GSL_SF_LEGENDRE_NONE
} gsl_sf_legendre_t;
*/

/*
int gsl_sf_legendre_array(const gsl_sf_legendre_t norm,
                          const size_t lmax, const double x,
                          double result_array[]);
                          */
/*
int gsl_sf_legendre_array_e(const gsl_sf_legendre_t norm,
                            const size_t lmax, const double x,
                            const double csphase,
                            double result_array[]);
                            */
/*
int gsl_sf_legendre_deriv_array(const gsl_sf_legendre_t norm,
                                const size_t lmax, const double x,
                                double result_array[],
                                double result_deriv_array[]);
                                */
/*
int gsl_sf_legendre_deriv_array_e(const gsl_sf_legendre_t norm,
                                  const size_t lmax, const double x,
                                  const double csphase,
                                  double result_array[],
                                  double result_deriv_array[]);
                                  */
/*
int gsl_sf_legendre_deriv_alt_array(const gsl_sf_legendre_t norm,
                                    const size_t lmax, const double x,
                                    double result_array[],
                                    double result_deriv_array[]);
                                    */
/*
int gsl_sf_legendre_deriv_alt_array_e(const gsl_sf_legendre_t norm,
                                      const size_t lmax, const double x,
                                      const double csphase,
                                      double result_array[],
                                      double result_deriv_array[]);
                                      */
/*
int gsl_sf_legendre_deriv2_array(const gsl_sf_legendre_t norm,
                                 const size_t lmax, const double x,
                                 double result_array[],
                                 double result_deriv_array[],
                                 double result_deriv2_array[]);
                                 */
/*
int gsl_sf_legendre_deriv2_array_e(const gsl_sf_legendre_t norm,
                                   const size_t lmax, const double x,
                                   const double csphase,
                                   double result_array[],
                                   double result_deriv_array[],
                                   double result_deriv2_array[]);
                                   */
/*
int gsl_sf_legendre_deriv2_alt_array(const gsl_sf_legendre_t norm,
                                     const size_t lmax, const double x,
                                     double result_array[],
                                     double result_deriv_array[],
                                     double result_deriv2_array[]);
                                     */
/*
int gsl_sf_legendre_deriv2_alt_array_e(const gsl_sf_legendre_t norm,
                                       const size_t lmax, const double x,
                                       const double csphase,
                                       double result_array[],
                                       double result_deriv_array[],
                                       double result_deriv2_array[]);
                                       */
/*
size_t gsl_sf_legendre_array_n(const size_t lmax);
size_t gsl_sf_legendre_array_index(const size_t l, const size_t m);
size_t gsl_sf_legendre_nlm(const size_t lmax);
*/


/* specfunc/gsl_sf_log.h
 */

/* Provide a logarithm function with GSL semantics.
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_log_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_log(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_log,args);
}

/* Log(|x|)
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_log_abs_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_log_abs(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_log_abs,args);
}

/* Complex Logarithm
 *   exp(lnr + I theta) = zr + I zi
 * Returns argument in [-pi,pi].
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_complex_log_e(const double zr, const double zi, gsl_sf_result * lnr, gsl_sf_result * theta); */

/* Log(1 + x)
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_log_1plusx_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_log_1plusx(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_log_1plusx,args);
}

/* Log(1 + x) - x
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_log_1plusx_mx_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_log_1plusx_mx(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_log_1plusx_mx,args);
}


/* specfunc/gsl_sf_mathieu.h
 */

#define GSL_SF_MATHIEU_COEFF 100

/*
typedef struct 
{
  size_t size;
  size_t even_order;
  size_t odd_order;
  int extra_values;
  double qa;
  double qb;
  double *aa;
  double *bb;
  double *dd;
  double *ee;
  double *tt;
  double *e2;
  double *zz;
  gsl_vector *eval;
  gsl_matrix *evec;
  gsl_eigen_symmv_workspace *wmat;
} gsl_sf_mathieu_workspace;
*/

/* Compute an array of characteristic (eigen) values from the recurrence
   matrices for the Mathieu equations. */
/*
int gsl_sf_mathieu_a_array(int order_min, int order_max, double qq, gsl_sf_mathieu_workspace *work, double result_array[]);
int gsl_sf_mathieu_b_array(int order_min, int order_max, double qq,  gsl_sf_mathieu_workspace *work, double result_array[]);
*/

/* Compute the characteristic value for a Mathieu function of order n and
   type ntype. */
/* int gsl_sf_mathieu_a_e(int order, double qq, gsl_sf_result *result); */
double wrap_gsl_sf_mathieu_a(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_mathieu_a,args);
}
/* int gsl_sf_mathieu_b_e(int order, double qq, gsl_sf_result *result); */
double wrap_gsl_sf_mathieu_b(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_mathieu_b,args);
}

/* Compute the Fourier coefficients for a Mathieu function. */
/*
int gsl_sf_mathieu_a_coeff(int order, double qq, double aa, double coeff[]);
int gsl_sf_mathieu_b_coeff(int order, double qq, double aa, double coeff[]);
*/

/* Allocate computational storage space for eigenvalue solution. */
/*
gsl_sf_mathieu_workspace *gsl_sf_mathieu_alloc(const size_t nn,
                                               const double qq);
void gsl_sf_mathieu_free(gsl_sf_mathieu_workspace *workspace);
*/

/* Compute an angular Mathieu function. */
/* int gsl_sf_mathieu_ce_e(int order, double qq, double zz, gsl_sf_result *result); */
double wrap_gsl_sf_mathieu_ce(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i2d(gsl_sf_mathieu_ce,args);
}
/* int gsl_sf_mathieu_se_e(int order, double qq, double zz, gsl_sf_result *result); */
double wrap_gsl_sf_mathieu_se(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i2d(gsl_sf_mathieu_se,args);
}

/*
int gsl_sf_mathieu_ce_array(int nmin, int nmax, double qq, double zz,
                            gsl_sf_mathieu_workspace *work,
                            double result_array[]);
int gsl_sf_mathieu_se_array(int nmin, int nmax, double qq, double zz,
                            gsl_sf_mathieu_workspace *work,
                            double result_array[]);
                            */

/* Compute a radial Mathieu function. */
/* int gsl_sf_mathieu_Mc_e(int kind, int order, double qq, double zz,
                      gsl_sf_result *result); */
double wrap_gsl_sf_mathieu_Mc(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2i2d(gsl_sf_mathieu_Mc,args);
}
/* int gsl_sf_mathieu_Ms_e(int kind, int order, double qq, double zz,
                      gsl_sf_result *result); */
double wrap_gsl_sf_mathieu_Ms(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2i2d(gsl_sf_mathieu_Ms,args);
}

/*
int gsl_sf_mathieu_Mc_array(int kind, int nmin, int nmax, double qq,
                            double zz, gsl_sf_mathieu_workspace *work,
                            double result_array[]);
int gsl_sf_mathieu_Ms_array(int kind, int nmin, int nmax, double qq,
                            double zz, gsl_sf_mathieu_workspace *work,
                            double result_array[]);
                            */


/* specfunc/gsl_sf_pow_int.h
 */

/* Calculate x^n.
 * Does not check for overflow/underflow.
 */
/* int gsl_sf_pow_int_e(double x, int n, gsl_sf_result * result); */
double wrap_gsl_sf_pow_int(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d1i(gsl_sf_pow_int,args);
}


/* specfunc/gsl_sf_psi.h
 */

/* Poly-Gamma Functions
 *
 * psi(m,x) := (d/dx)^m psi(0,x) = (d/dx)^{m+1} log(gamma(x))
 */

/* Di-Gamma Function  psi(n) = psi(0,n)
 *
 * n > 0
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_psi_int_e(const int n, gsl_sf_result * result); */
double wrap_gsl_sf_psi_int(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i(gsl_sf_psi_int,args);
}

/* Di-Gamma Function psi(x) = psi(0, x)
 *
 * x != 0.0, -1.0, -2.0, ...
 * exceptions: GSL_EDOM, GSL_ELOSS
 */
/* int gsl_sf_psi_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_psi(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_psi,args);
}

/* Di-Gamma Function Re[psi(1 + I y)]
 */
/* int gsl_sf_psi_1piy_e(const double y, gsl_sf_result * result); */
double wrap_gsl_sf_psi_1piy(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_psi_1piy,args);
}

/* Di-Gamma Function psi(z) for general complex argument z = x + iy
 *
 * exceptions: GSL_EDOM
 */
/*
int gsl_sf_complex_psi_e(
  const double x,
  const double y,
  gsl_sf_result * result_re,
  gsl_sf_result * result_im
  );
  */

/* Tri-Gamma Function psi^(1)(n)
 *
 * n > 0
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_psi_1_int_e(const int n, gsl_sf_result * result); */
double wrap_gsl_sf_psi_1_int(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i(gsl_sf_psi_1_int,args);
}

/* Tri-Gamma Function psi^(1)(x)
 *
 * x != 0.0, -1.0, -2.0, ...
 * exceptions: GSL_EDOM, GSL_ELOSS
 */
/* int gsl_sf_psi_1_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_psi_1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_psi_1,args);
}

/* Poly-Gamma Function psi^(n)(x)
 *
 * n >= 0, x > 0.0
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_psi_n_e(const int n, const double x, gsl_sf_result * result); */
double wrap_gsl_sf_psi_n(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i1d(gsl_sf_psi_n,args);
}


/* specfunc/gsl_sf_sincos_pi.h
 */

/* sin_pi(x) with GSL semantics. This is actually important
 * because we want to control the error estimate, and trying
 * to guess the error for the standard library implementation
 * every time it is used would be a little goofy.
 */
/* int gsl_sf_sin_pi_e(double x, gsl_sf_result * result); */
double wrap_gsl_sf_sin_pi(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_sin_pi,args);
}

/* cos_pi(x) with GSL semantics.
 */
/* int gsl_sf_cos_pi_e(double x, gsl_sf_result * result); */
double wrap_gsl_sf_cos_pi(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_cos_pi,args);
}


/* specfunc/gsl_sf_synchrotron.h
 */

/* First synchrotron function:
 *   synchrotron_1(x) = x Integral[ K_{5/3}(t), {t, x, Infinity}]
 *
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int gsl_sf_synchrotron_1_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_synchrotron_1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_synchrotron_1,args);
}

/* Second synchroton function:
 *   synchrotron_2(x) = x * K_{2/3}(x)
 *
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int gsl_sf_synchrotron_2_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_synchrotron_2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_synchrotron_2,args);
}


/* specfunc/gsl_sf_transport.h
 */

/* Transport function:
 *   J(n,x) := Integral[ t^n e^t /(e^t - 1)^2, {t,0,x}]
 */

/* J(2,x)
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_transport_2_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_transport_2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_transport_2,args);
}

/* J(3,x)
 *
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int gsl_sf_transport_3_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_transport_3(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_transport_3,args);
}

/* J(4,x)
 *
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int gsl_sf_transport_4_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_transport_4(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_transport_4,args);
}

/* J(5,x)
 *
 * exceptions: GSL_EDOM, GSL_EUNDRFLW
 */
/* int gsl_sf_transport_5_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_transport_5(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_transport_5,args);
}


/* specfunc/gsl_sf_trig.h
 */

/* Sin(x) with GSL semantics. This is actually important
 * because we want to control the error estimate, and trying
 * to guess the error for the standard library implementation
 * every time it is used would be a little goofy.
 */
/* int gsl_sf_sin_e(double x, gsl_sf_result * result); */
double wrap_gsl_sf_sin(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_sin,args);
}

/* Cos(x) with GSL semantics.
 */
/* int gsl_sf_cos_e(double x, gsl_sf_result * result); */
double wrap_gsl_sf_cos(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_cos,args);
}

/* Hypot(x,y) with GSL semantics.
 */
/* int gsl_sf_hypot_e(const double x, const double y, gsl_sf_result * result); */
double wrap_gsl_sf_hypot(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_hypot,args);
}

/* Sin(z) for complex z
 *
 * exceptions: GSL_EOVRFLW
 */
/* int gsl_sf_complex_sin_e(const double zr, const double zi, gsl_sf_result * szr, gsl_sf_result * szi); */

/* Cos(z) for complex z
 *
 * exceptions: GSL_EOVRFLW
 */
/* int gsl_sf_complex_cos_e(const double zr, const double zi, gsl_sf_result * czr, gsl_sf_result * czi); */

/* Log(Sin(z)) for complex z
 *
 * exceptions: GSL_EDOM, GSL_ELOSS
 */
/* int gsl_sf_complex_logsin_e(const double zr, const double zi, gsl_sf_result * lszr, gsl_sf_result * lszi); */

/* Sinc(x) = sin(pi x) / (pi x)
 */
/* int gsl_sf_sinc_e(double x, gsl_sf_result * result); */
double wrap_gsl_sf_sinc(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_sinc,args);
}

/* Log(Sinh(x)), x > 0
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_lnsinh_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_lnsinh(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    if (args->dblp[0] > 0.0){
        return wrap_dbl_1d(gsl_sf_lnsinh,args);
    } else {
        return *(double *)args->missval;
    }
}

/* Log(Cosh(x))
 */
/* int gsl_sf_lncosh_e(const double x, gsl_sf_result * result); */
double wrap_gsl_sf_lncosh(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_lncosh,args);
}

/* Convert polar to rectlinear coordinates.
 *
 * exceptions: GSL_ELOSS
 */
/* int gsl_sf_polar_to_rect(const double r, const double theta, gsl_sf_result * x, gsl_sf_result * y); */

/* Convert rectilinear to polar coordinates.
 * return argument in range [-pi, pi]
 *
 * exceptions: GSL_EDOM
 */
/* int gsl_sf_rect_to_polar(const double x, const double y, gsl_sf_result * r, gsl_sf_result * theta); */

/* Sin(x) for quantity with an associated error.
 */
/* int gsl_sf_sin_err_e(const double x, const double dx, gsl_sf_result * result); */

/* Cos(x) for quantity with an associated error.
 */
/* int gsl_sf_cos_err_e(const double x, const double dx, gsl_sf_result * result); */

/* Force an angle to lie in the range (-pi,pi].
 *
 * exceptions: GSL_ELOSS
 */
/* int gsl_sf_angle_restrict_symm_e(double * theta); */
double wrap_gsl_sf_angle_restrict_symm(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_angle_restrict_symm,args);
}

/* Force an angle to lie in the range [0, 2pi)
 *
 * exceptions: GSL_ELOSS
 */
/* int gsl_sf_angle_restrict_pos_e(double * theta); */
double wrap_gsl_sf_angle_restrict_pos(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_angle_restrict_pos,args);
}

/* int gsl_sf_angle_restrict_symm_err_e(const double theta, gsl_sf_result * result); */
/* int gsl_sf_angle_restrict_pos_err_e (const double theta, gsl_sf_result * result); */


/* specfunc/gsl_sf_zeta.h
 */

/* Riemann Zeta Function
 * zeta(n) = Sum[ k^(-n), {k,1,Infinity} ]
 *
 * n=integer, n != 1
 * exceptions: GSL_EDOM, GSL_EOVRFLW
 */
/* int gsl_sf_zeta_int_e(const int n, gsl_sf_result * result); */
double wrap_gsl_sf_zeta_int(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i(gsl_sf_zeta_int,args);
}

/* Riemann Zeta Function
 * zeta(x) = Sum[ k^(-s), {k,1,Infinity} ], s != 1.0
 *
 * s != 1.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW
 */
/* int gsl_sf_zeta_e(const double s, gsl_sf_result * result); */
double wrap_gsl_sf_zeta(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_zeta,args);
}

/* Riemann Zeta Function minus 1
 *   useful for evaluating the fractional part
 *   of Riemann zeta for large argument
 *
 * s != 1.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW
 */
/* int gsl_sf_zetam1_e(const double s, gsl_sf_result * result); */
double wrap_gsl_sf_zetam1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_zetam1,args);
}

/* Riemann Zeta Function minus 1 for integer arg
 *   useful for evaluating the fractional part
 *   of Riemann zeta for large argument
 *
 * s != 1.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW
 */
/* int gsl_sf_zetam1_int_e(const int s, gsl_sf_result * result); */
double wrap_gsl_sf_zetam1_int(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i(gsl_sf_zetam1_int,args);
}

/* Hurwitz Zeta Function
 * zeta(s,q) = Sum[ (k+q)^(-s), {k,0,Infinity} ]
 *
 * s > 1.0, q > 0.0
 * exceptions: GSL_EDOM, GSL_EUNDRFLW, GSL_EOVRFLW
 */
/* int gsl_sf_hzeta_e(const double s, const double q, gsl_sf_result * result); */
double wrap_gsl_sf_hzeta(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_sf_hzeta,args);
}

/* Eta Function
 * eta(n) = (1-2^(1-n)) zeta(n)
 *
 * exceptions: GSL_EUNDRFLW, GSL_EOVRFLW
 */
/* int gsl_sf_eta_int_e(int n, gsl_sf_result * result); */
double wrap_gsl_sf_eta_int(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1i(gsl_sf_eta_int,args);
}

/* Eta Function
 * eta(s) = (1-2^(1-s)) zeta(s)
 *
 * exceptions: GSL_EUNDRFLW, GSL_EOVRFLW
 */
/* int gsl_sf_eta_e(const double s, gsl_sf_result * result); */
double wrap_gsl_sf_eta(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_sf_eta,args);
}

#endif
