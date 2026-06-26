/* Created by Bill Scheftic */
#ifndef  _WRAP_GSL_RANDIST_H_
#define  _WRAP_GSL_RANDIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>

/* Mixed Distributions */
double wrap_cdf_mixed_gamma_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    /* return wrap_dbl_3d(gsl_cdf_gamma_P,args); */
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x  = args->dblp[0];
    double p0 = args->dblp[1];
    double a  = args->dblp[2];
    double b  = args->dblp[3];

    if (x > 0){
        double pG = gsl_cdf_gamma_P(x,a,b);
        if (isfinite(pG)){ return p0+(1-p0)*pG; } else { return *(double *)args->missval; }
    } else {
        /*  This will generate a random number as the percentile can be between 0 and p0 exclusive */
        double rnum_0_1 = (double)(1+rand()%8192)/8193.0;
        return rnum_0_1*p0;
    /*  return 0.5*p0;  */
    }
}

double wrap_cdf_mixed_gamma_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    /* return wrap_dbl_3d(gsl_cdf_gamma_P,args); */
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double p  = args->dblp[0];
    double p0 = args->dblp[1];
    double a  = args->dblp[2];
    double b  = args->dblp[3];

    if (p > p0){
        double pG = (p-p0)/(1-p0);
        double x  = gsl_cdf_gamma_Pinv(pG,a,b);
        if (isfinite(x)){ return x; } else { return *(double *)args->missval; }
    } else {
        return 0;
    }
}



/* The Gaussian Distribution */
/*
double gsl_ran_gaussian(const gsl_rng * r, double sigma)
double gsl_ran_gaussian_ziggurat(const gsl_rng * r, double sigma)
double gsl_ran_gaussian_ratio_method(const gsl_rng * r, double sigma)
*/
double wrap_gsl_ran_gaussian_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_ran_gaussian_pdf,args);
}
double wrap_gsl_cdf_gaussian_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_gaussian_P,args);
}
double wrap_gsl_cdf_gaussian_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_gaussian_Q,args);
}
double wrap_gsl_cdf_gaussian_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_gaussian_Pinv,args);
}
double wrap_gsl_cdf_gaussian_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_gaussian_Qinv,args);
}

/* The Unit Gaussian Distribution */
/*
double gsl_ran_ugaussian(const gsl_rng * r)
double gsl_ran_ugaussian_ratio_method(const gsl_rng * r)
*/
double wrap_gsl_ran_ugaussian_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_ran_ugaussian_pdf,args);
}
double wrap_gsl_cdf_ugaussian_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_cdf_ugaussian_P,args);
}
double wrap_gsl_cdf_ugaussian_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_cdf_ugaussian_Q,args);
}
double wrap_gsl_cdf_ugaussian_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_cdf_ugaussian_Pinv,args);
}
double wrap_gsl_cdf_ugaussian_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_cdf_ugaussian_Qinv,args);
}

/* The Gaussian Tail Distribution */
/*
double gsl_ran_gaussian_tail(const gsl_rng * r, double a, double sigma)
*/
double wrap_gsl_ran_gaussian_tail_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_ran_gaussian_tail_pdf,args);
}
/*
double gsl_ran_ugaussian_tail(const gsl_rng * r, double a)
*/
double wrap_gsl_ran_ugaussian_tail_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_ran_ugaussian_tail_pdf,args);
}

/* The Bivariate Gaussian Distribution */
/*
void gsl_ran_bivariate_gaussian(const gsl_rng * r, double sigma_x, double sigma_y, double rho, double * x, double * y)
*/
double wrap_gsl_ran_bivariate_gaussian_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_5d(gsl_ran_bivariate_gaussian_pdf,args);
}

/* The Multivariate Gaussian Distribution */
/*
int gsl_ran_multivariate_gaussian(const gsl_rng * r, const gsl_vector * mu, const gsl_matrix * L, gsl_vector * result)
*/
/*
int gsl_ran_multivariate_gaussian_pdf(const gsl_vector * x, const gsl_vector * mu, const gsl_matrix * L, double * result, gsl_vector * work)
int gsl_ran_multivariate_gaussian_log_pdf(const gsl_vector * x, const gsl_vector * mu, const gsl_matrix * L, double * result, gsl_vector * work)
int gsl_ran_multivariate_gaussian_mean(const gsl_matrix * X, gsl_vector * mu_hat)
int gsl_ran_multivariate_gaussian_vcov(const gsl_matrix * X, gsl_matrix * sigma_hat)
*/

/* The Exponential Distribution */
/*
double gsl_ran_exponential(const gsl_rng * r, double mu)
*/
double wrap_gsl_ran_exponential_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_ran_exponential_pdf,args);
}
double wrap_gsl_cdf_exponential_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_exponential_P,args);
}
double wrap_gsl_cdf_exponential_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_exponential_Q,args);
}
double wrap_gsl_cdf_exponential_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_exponential_Pinv,args);
}
double wrap_gsl_cdf_exponential_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_exponential_Qinv,args);
}

/* The Laplace Distribution */
/*
double gsl_ran_laplace(const gsl_rng * r, double a)
*/
double wrap_gsl_ran_laplace_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_ran_laplace_pdf,args);
}
double wrap_gsl_cdf_laplace_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_laplace_P,args);
}
double wrap_gsl_cdf_laplace_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_laplace_Q,args);
}
double wrap_gsl_cdf_laplace_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_laplace_Pinv,args);
}
double wrap_gsl_cdf_laplace_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_laplace_Qinv,args);
}

/* The Exponential Power Distribution */
/*
double gsl_ran_exppow(const gsl_rng * r, double a, double b)
*/
double wrap_gsl_ran_exppow_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_ran_exppow_pdf,args);
}
double wrap_gsl_cdf_exppow_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_exppow_P,args);
}
double wrap_gsl_cdf_exppow_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_exppow_Q,args);
}

/* The Cauchy Distribution */
/*
double gsl_ran_cauchy(const gsl_rng * r, double a)
*/
double wrap_gsl_ran_cauchy_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_ran_cauchy_pdf,args);
}
double wrap_gsl_cdf_cauchy_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_cauchy_P,args);
}
double wrap_gsl_cdf_cauchy_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_cauchy_Q,args);
}
double wrap_gsl_cdf_cauchy_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_cauchy_Pinv,args);
}
double wrap_gsl_cdf_cauchy_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_cauchy_Qinv,args);
}

/* The Rayleigh Distribution */
/*
double gsl_ran_rayleigh(const gsl_rng * r, double sigma)
*/
double wrap_gsl_ran_rayleigh_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_ran_rayleigh_pdf,args);
}
double wrap_gsl_cdf_rayleigh_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_rayleigh_P,args);
}
double wrap_gsl_cdf_rayleigh_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_rayleigh_Q,args);
}
double wrap_gsl_cdf_rayleigh_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_rayleigh_Pinv,args);
}
double wrap_gsl_cdf_rayleigh_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_rayleigh_Qinv,args);
}

/* The Rayleigh Tail Distribution */
/*
double gsl_ran_rayleigh_tail(const gsl_rng * r, double a, double sigma)
*/
double wrap_gsl_ran_rayleigh_tail_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_ran_rayleigh_tail_pdf,args);
}

/* The Landau Distribution */
/*
double gsl_ran_landau(const gsl_rng * r)
*/
double wrap_gsl_ran_landau_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(gsl_ran_landau_pdf,args);
}

/* The Levy alpha-Stable Distributions */
/*
double gsl_ran_levy(const gsl_rng * r, double c, double alpha)
*/

/* The Levy skew alpha-Stable Distribution */
/*
double gsl_ran_levy_skew(const gsl_rng * r, double c, double alpha, double beta)
*/

/* The Gamma Distribution */
/*
double gsl_ran_gamma(const gsl_rng * r, double a, double b)
double gsl_ran_gamma_knuth(const gsl_rng * r, double a, double b)
*/
double wrap_gsl_ran_gamma_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_ran_gamma_pdf,args);
}
double wrap_gsl_cdf_gamma_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    /* return wrap_dbl_3d(gsl_cdf_gamma_P,args); */
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    double a = args->dblp[1];
    double b = args->dblp[2];

    if (x > 0){
        /* fprintf(stderr,"wrap_gsl_cdf_gamma_P: x=%g, a=%g, b=%g\n",x,a,b); */
        double rv = gsl_cdf_gamma_P(x,a,b);
        if (isfinite(rv)){ return rv; } else { return *(double *)args->missval; }
    } else {
        fprintf(stderr,"Error: wrap_gsl_cdf_gamma_P: x is out of range: x=%g, a=%g, b=%g\n",x,a,b);
        return *(double *)args->missval;
    }
}
double wrap_gsl_cdf_gamma_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_gamma_Q,args);
}
double wrap_gsl_cdf_gamma_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_gamma_Pinv,args);
}
double wrap_gsl_cdf_gamma_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_gamma_Qinv,args);
}

/* The Flat (Uniform) Distribution */
/*
double gsl_ran_flat(const gsl_rng * r, double a, double b)
*/
double wrap_gsl_ran_flat_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_ran_flat_pdf,args);
}
double wrap_gsl_cdf_flat_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_flat_P,args);
}
double wrap_gsl_cdf_flat_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_flat_Q,args);
}
double wrap_gsl_cdf_flat_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_flat_Pinv,args);
}
double wrap_gsl_cdf_flat_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_flat_Qinv,args);
}

/* The Lognormal Distribution */
/*
double gsl_ran_lognormal(const gsl_rng * r, double zeta, double sigma)
*/
double wrap_gsl_ran_lognormal_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_ran_lognormal_pdf,args);
}
double wrap_gsl_cdf_lognormal_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_lognormal_P,args);
}
double wrap_gsl_cdf_lognormal_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_lognormal_Q,args);
}
double wrap_gsl_cdf_lognormal_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_lognormal_Pinv,args);
}
double wrap_gsl_cdf_lognormal_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_lognormal_Qinv,args);
}

/* The Chi-squared Distribution */
/*
double gsl_ran_chisq(const gsl_rng * r, double nu)
*/
double wrap_gsl_ran_chisq_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_ran_chisq_pdf,args);
}
double wrap_gsl_cdf_chisq_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_chisq_P,args);
}
double wrap_gsl_cdf_chisq_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_chisq_Q,args);
}
double wrap_gsl_cdf_chisq_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_chisq_Pinv,args);
}
double wrap_gsl_cdf_chisq_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_chisq_Qinv,args);
}

/* The F-distribution */
/*
double gsl_ran_fdist(const gsl_rng * r, double nu1, double nu2)
*/
double wrap_gsl_ran_fdist_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_ran_fdist_pdf,args);
}
double wrap_gsl_cdf_fdist_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_fdist_P,args);
}
double wrap_gsl_cdf_fdist_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_fdist_Q,args);
}
double wrap_gsl_cdf_fdist_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_fdist_Pinv,args);
}
double wrap_gsl_cdf_fdist_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_fdist_Qinv,args);
}

/* The t-distribution */
/*
double gsl_ran_tdist(const gsl_rng * r, double nu)
*/
double wrap_gsl_ran_tdist_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_ran_tdist_pdf,args);
}
double wrap_gsl_cdf_tdist_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_tdist_P,args);
}
double wrap_gsl_cdf_tdist_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_tdist_Q,args);
}
double wrap_gsl_cdf_tdist_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_tdist_Pinv,args);
}
double wrap_gsl_cdf_tdist_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_tdist_Qinv,args);
}

/* The Beta Distribution */
/*
double gsl_ran_beta(const gsl_rng * r, double a, double b)
*/
double wrap_gsl_ran_beta_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_ran_beta_pdf,args);
}
double wrap_gsl_cdf_beta_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_beta_P,args);
}
double wrap_gsl_cdf_beta_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_beta_Q,args);
}
double wrap_gsl_cdf_beta_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_beta_Pinv,args);
}
double wrap_gsl_cdf_beta_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_beta_Qinv,args);
}

/* The Logistic Distribution */
/*
double gsl_ran_logistic(const gsl_rng * r, double a)
*/
double wrap_gsl_ran_logistic_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_ran_logistic_pdf,args);
}
double wrap_gsl_cdf_logistic_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_logistic_P,args);
}
double wrap_gsl_cdf_logistic_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_logistic_Q,args);
}
double wrap_gsl_cdf_logistic_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_logistic_Pinv,args);
}
double wrap_gsl_cdf_logistic_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(gsl_cdf_logistic_Qinv,args);
}

/* The Pareto Distribution */
/*
double gsl_ran_pareto(const gsl_rng * r, double a, double b)
*/
double wrap_gsl_ran_pareto_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_ran_pareto_pdf,args);
}
double wrap_gsl_cdf_pareto_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_pareto_P,args);
}
double wrap_gsl_cdf_pareto_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_pareto_Q,args);
}
double wrap_gsl_cdf_pareto_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_pareto_Pinv,args);
}
double wrap_gsl_cdf_pareto_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_pareto_Qinv,args);
}

/* Spherical Vector Distributions */
/*
void gsl_ran_dir_2d(const gsl_rng * r, double * x, double * y)
void gsl_ran_dir_2d_trig_method(const gsl_rng * r, double * x, double * y)
void gsl_ran_dir_3d(const gsl_rng * r, double * x, double * y, double * z)
void gsl_ran_dir_nd(const gsl_rng * r, size_t n, double * x)
*/

/* The Weibull Distribution */
/*
double gsl_ran_weibull(const gsl_rng * r, double a, double b)
*/
double wrap_gsl_ran_weibull_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_ran_weibull_pdf,args);
}
double wrap_gsl_cdf_weibull_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_weibull_P,args);
}
double wrap_gsl_cdf_weibull_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_weibull_Q,args);
}
double wrap_gsl_cdf_weibull_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_weibull_Pinv,args);
}
double wrap_gsl_cdf_weibull_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_weibull_Qinv,args);
}

/* The Type-1 Gumbel Distribution */
/*
double gsl_ran_gumbel1(const gsl_rng * r, double a, double b)
*/
double wrap_gsl_ran_gumbel1_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_ran_gumbel1_pdf,args);
}
double wrap_gsl_cdf_gumbel1_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_gumbel1_P,args);
}
double wrap_gsl_cdf_gumbel1_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_gumbel1_Q,args);
}
double wrap_gsl_cdf_gumbel1_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_gumbel1_Pinv,args);
}
double wrap_gsl_cdf_gumbel1_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_gumbel1_Qinv,args);
}

/* The Type-2 Gumbel Distribution */
/*
double gsl_ran_gumbel2(const gsl_rng * r, double a, double b)
*/
double wrap_gsl_ran_gumbel2_pdf(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_ran_gumbel2_pdf,args);
}
double wrap_gsl_cdf_gumbel2_P(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_gumbel2_P,args);
}
double wrap_gsl_cdf_gumbel2_Q(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_gumbel2_Q,args);
}
double wrap_gsl_cdf_gumbel2_Pinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_gumbel2_Pinv,args);
}
double wrap_gsl_cdf_gumbel2_Qinv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(gsl_cdf_gumbel2_Qinv,args);
}

/* The Dirichlet Distribution */
/*
void gsl_ran_dirichlet(const gsl_rng * r, size_t K, const double alpha[], double theta[])
*/
/*
double gsl_ran_dirichlet_pdf(size_t K, const double alpha[], const double theta[])
double gsl_ran_dirichlet_lnpdf(size_t K, const double alpha[], const double theta[])
*/

/* General Discrete Distributions */
/*
gsl_ran_discrete_t * gsl_ran_discrete_preproc(size_t K, const double * P)

size_t gsl_ran_discrete(const gsl_rng * r, const gsl_ran_discrete_t * g)

double gsl_ran_discrete_pdf(size_t k, const gsl_ran_discrete_t * g)

void gsl_ran_discrete_free(gsl_ran_discrete_t * g)
*/

/* The Poisson Distribution */
/*
unsigned int gsl_ran_poisson(const gsl_rng * r, double mu)
*/
/*
double gsl_ran_poisson_pdf(unsigned int k, double mu)
double gsl_cdf_poisson_P(unsigned int k, double mu)
double gsl_cdf_poisson_Q(unsigned int k, double mu)
*/

/* The Bernoulli Distribution */
/*
unsigned int gsl_ran_bernoulli(const gsl_rng * r, double p)
*/
/*
double gsl_ran_bernoulli_pdf(unsigned int k, double p)
*/

/* The Binomial Distribution */
/*
unsigned int gsl_ran_binomial(const gsl_rng * r, double p, unsigned int n)
*/
/*
double gsl_ran_binomial_pdf(unsigned int k, double p, unsigned int n)
double gsl_cdf_binomial_P(unsigned int k, double p, unsigned int n)
double gsl_cdf_binomial_Q(unsigned int k, double p, unsigned int n)
*/

/* The Multinomial Distribution */
/*
void gsl_ran_multinomial(const gsl_rng * r, size_t K, unsigned int N, const double p[], unsigned int n[])
*/
/*
double gsl_ran_multinomial_pdf(size_t K, const double p[], const unsigned int n[])
double gsl_ran_multinomial_lnpdf(size_t K, const double p[], const unsigned int n[])
*/

/* The Negative Binomial Distribution */
/*
unsigned int gsl_ran_negative_binomial(const gsl_rng * r, double p, double n)
*/
/*
double gsl_ran_negative_binomial_pdf(unsigned int k, double p, double  n)
double gsl_cdf_negative_binomial_P(unsigned int k, double p, double n)
double gsl_cdf_negative_binomial_Q(unsigned int k, double p, double n)
*/

/* The Pascal Distribution */
/*
unsigned int gsl_ran_pascal(const gsl_rng * r, double p, unsigned int n)
*/
/*
double gsl_ran_pascal_pdf(unsigned int k, double p, unsigned int n)
double gsl_cdf_pascal_P(unsigned int k, double p, unsigned int n)
double gsl_cdf_pascal_Q(unsigned int k, double p, unsigned int n)
*/

/* The Geometric Distribution */
/*
unsigned int gsl_ran_geometric(const gsl_rng * r, double p)
*/
/*
double gsl_ran_geometric_pdf(unsigned int k, double p)
double gsl_cdf_geometric_P(unsigned int k, double p)
double gsl_cdf_geometric_Q(unsigned int k, double p)
*/

/* The Hypergeometric Distribution */
/*
unsigned int gsl_ran_hypergeometric(const gsl_rng * r, unsigned int n1, unsigned int n2, unsigned int t)
*/
/*
double gsl_ran_hypergeometric_pdf(unsigned int k, unsigned int n1, unsigned int n2, unsigned int t)
double gsl_cdf_hypergeometric_P(unsigned int k, unsigned int n1, unsigned int n2, unsigned int t)
double gsl_cdf_hypergeometric_Q(unsigned int k, unsigned int n1, unsigned int n2, unsigned int t)
*/

/* The Logarithmic Distribution */
/*
unsigned int gsl_ran_logarithmic(const gsl_rng * r, double p)
*/
/*
double gsl_ran_logarithmic_pdf(unsigned int k, double p)
*/

/* The Wishart Distribution */
/*
int gsl_ran_wishart(const gsl_rng * r, const double n, const gsl_matrix * L, gsl_matrix * result, gsl_matrix * work)
*/
/*
int gsl_ran_wishart_pdf(const gsl_matrix * X, const gsl_matrix * L_X, const double n, const gsl_matrix * L, double * result, gsl_matrix * work)
int gsl_ran_wishart_log_pdf(const gsl_matrix * X, const gsl_matrix * L_X, const double n, const gsl_matrix * L, double * result, gsl_matrix * work)
*/

/* Shuffling and Sampling */
/*
void gsl_ran_shuffle(const gsl_rng * r, void * base, size_t n, size_t size)
int gsl_ran_choose(const gsl_rng * r, void * dest, size_t k, void * src, size_t n, size_t size)
void gsl_ran_sample(const gsl_rng * r, void * dest, size_t k, void * src, size_t n, size_t size)
*/

#endif
