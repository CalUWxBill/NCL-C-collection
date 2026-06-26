/* Created by Bill Scheftic */
/* Calls GSL nonlinear fitting routines.
   Right now Gamma and Gaussian parameters are estimated
   rather than use the fitting routine to increase speed */
#ifndef  _DIST_PRMS_H_
#define  _DIST_PRMS_H_

#include <stdlib.h>
#include <stdio.h>
#include <wrap_functions.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_multifit_nlinear.h>
#include <gsl/gsl_cdf.h>
#include <sort2.h>
#include <stats2.h>
#include <gsl/gsl_statistics.h>

struct data {
  size_t  n;
  double *t;
  double *y;
};

struct data_cos {
  size_t  n;
  double  T; /* Constant period passed in */
  double *t;
  double *y;
};

void params_Gauss(arr *restrict X, double *Mn, double *sigma);
void params_Beta(arr *restrict X, double *a, double *b);

double wrap_cos_fun(input_args *args);
void wrap_params_Cos(input_args *args);
double cos_fun(double x, double mu, double A, double T, double dT);
int cos_f (const gsl_vector * x, void *data, gsl_vector * f);
int cos_df (const gsl_vector * x, void *data, gsl_matrix * J);
int cos_init (double *x, double *t,  double *y, size_t n);
void callback_cos(const size_t iter, void *params, const gsl_multifit_nlinear_workspace *w);
void params_Cos(arr * X, arr * Y, double T, double *mu, double *A, double *dT);

int gamcdf_f (const gsl_vector * x, void *data, gsl_vector * f);
int gamcdf_init (double *x, double *t, size_t n);
void callback(const size_t iter, void *params, const gsl_multifit_nlinear_workspace *w);
void params_Gamma(arr *restrict X, double *shape, double *scale);

int weibcdf_f (const gsl_vector * x, void *data, gsl_vector * f);
int weibcdf_init (double *x, double *t, size_t n);
void callback_wbl(const size_t iter, void *params, const gsl_multifit_nlinear_workspace *w);
void params_Weibull(arr *restrict X, double *scale, double *pexp);

int gumb1cdf_f (const gsl_vector *, void *, gsl_vector *);
int gumb1cdf_init (double *, double *, size_t);
void callback_gum1(const size_t, void *, const gsl_multifit_nlinear_workspace *);
void params_Gumbel1(arr *, double *, double *, double *);

int gumb2cdf_f (const gsl_vector *, void *, gsl_vector *);
int gumb2cdf_init (double *);
void callback_gum2(const size_t, void *, const gsl_multifit_nlinear_workspace *);
void params_Gumbel2(arr *, double *, double *);

void wrap_params_Gauss(input_args *args){
    return wrap_1ar_r2d(params_Gauss,args,(typ_idx)5);
}

void wrap_params_Gamma(input_args *args){
/*  return wrap_1ar_r2d(params_Gamma,args,(typ_idx)5); */
    return wrap_1ar_r2d(fit_gamma_prms,args,(typ_idx)5);
}

void wrap_params_MixedGamma(input_args *args){
/*  return wrap_1ar_r2d(params_Gamma,args,(typ_idx)5); */
    return wrap_1ar_r3d(fit_mixed_gamma_prms,args,(typ_idx)5);
}

void wrap_params_Beta(input_args *args){
/*  return wrap_1ar_r2d(params_Gamma,args,(typ_idx)5); */
    return wrap_1ar_r2d(params_Beta,args,(typ_idx)5);
}

void wrap_params_Weibull(input_args *args){
    return wrap_1ar_r2d(params_Weibull,args,(typ_idx)5);
}

void wrap_params_Gumbel1(input_args *args){
    return wrap_1ar_r3d(params_Gumbel1,args,(typ_idx)5);
}

void wrap_params_Gumbel2(input_args *args){
    return wrap_1ar_r2d(params_Gumbel2,args,(typ_idx)5);
}

double wrap_cos_fun(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_5d(cos_fun,args);
}

void wrap_params_Cos(input_args *args){
    return wrap_2ar1d_r3d(params_Cos,args,(typ_idx)5);
}


double cos_fun(double x, double mu, double A, double T, double dT){
  double B = TWO_PI/T;
  return mu + A*cos(B*(x-dT));
}

int cos_f (const gsl_vector * x, void *data, gsl_vector * f){
  size_t  n = ((struct data_cos *)data)->n;
  double *t = ((struct data_cos *)data)->t;
  double *y = ((struct data_cos *)data)->y;

  double mu    = gsl_vector_get(x,0);
  double A     = gsl_vector_get(x,1);
  double T     = ((struct data_cos *)data)->T;
  double dT    = gsl_vector_get(x,2);
  double B     = TWO_PI/T;

  size_t i;
  for (i = 0; i < n; ++i){
      double Yi = mu + A*cos(B*(t[i]-dT));
      gsl_vector_set (f, i, Yi - y[i]);
  }

  return GSL_SUCCESS;
}

int cos_df (const gsl_vector * x, void *data, gsl_matrix * J){
  size_t  n = ((struct data_cos *)data)->n;
  double *t = ((struct data_cos *)data)->t;

  double A     = gsl_vector_get(x,1);
  double T     = ((struct data_cos *)data)->T;
  double dT    = gsl_vector_get(x,2);
  double B     = TWO_PI/T;

  size_t i;
  for (i = 0; i < n; ++i){
      double u = B*(t[i]-dT);
      gsl_matrix_set (J, i, 0, 1.0);
      gsl_matrix_set (J, i, 1, cos(u));
      gsl_matrix_set (J, i, 2, A*B*sin(u));
  }

  return GSL_SUCCESS;
}

/* int cos_init (double *x, size_t p, double *t, size_t n){ */
int cos_init (double *x, double *t, double *y, size_t n){
  /* Calculate some stats on t */
  double y_mean = gsl_stats_mean(y, 1, n);
  double y_max  = gsl_stats_max (y, 1, n);
  
  /* Calculate parameters based on moments calculated above */

  x[0] = y_mean;
  x[1] = 0.3*(y_max-y_mean);
  x[2] = 0.0;
  
  /* fprintf(stderr,"cos_init: %g, %g, %g\n",x[0],x[1],x[2]); */
 
  return GSL_SUCCESS;
}

void callback_cos(const size_t iter, void *params,
              const gsl_multifit_nlinear_workspace *w){
  gsl_vector *f = gsl_multifit_nlinear_residual(w);
  gsl_vector *x = gsl_multifit_nlinear_position(w);
  double rcond;

  /* compute reciprocal condition number of J(x) */
  gsl_multifit_nlinear_rcond(&rcond, w);

  fprintf(stdout, "iter %2zu: mu = %.4f, A = %.4f, dT = %.4f cond(J) = %8.4f, |f(x)| = %.4f\n",
          iter,
          gsl_vector_get(x, 0),
          gsl_vector_get(x, 1),
          gsl_vector_get(x, 2),
          1.0 / rcond,
          gsl_blas_dnrm2(f));
}

void params_Cos(arr * X, arr * Y, double T, double *mu, double *A, double *dT){
  const gsl_multifit_nlinear_type *Trust = gsl_multifit_nlinear_trust;
  gsl_multifit_nlinear_workspace *w;
  gsl_multifit_nlinear_fdf fdf;
  gsl_multifit_nlinear_parameters fdf_params =
    gsl_multifit_nlinear_default_parameters();
  fdf_params.trs = gsl_multifit_nlinear_trs_lmaccel;
  const size_t n = (size_t)X->tlen;
  const size_t p = 3;

  gsl_vector *f;
  gsl_matrix *J;
  
  /* printArrayFmtAllWHdr(stderr,X, "%g","params_Cos: X - ");        */
  /* printArrayFmtAllWHdr(stderr,Y, "%g","params_Cos: T=%g Y - ",T); */

  double *t = pntr_of(X);
  double *y = pntr_of(Y);
  struct data_cos d = { n, T, t, y };
  double chisq0;
  int status, info;
  size_t i;

  const double xtol = 1e-8;
  const double gtol = 1e-8;
  const double ftol = 0.0;

  /* define the function to be minimized */
  fdf.f   = cos_f;
  fdf.df  = cos_df;
  /* fdf.df  = NULL; */ /* set to NULL for finite-difference Jacobian */
  fdf.fvv = NULL;     /* not using geodesic acceleration */
  fdf.n = n;
  fdf.p = p;
  fdf.params = &d;

  double *x_init = malloc(p*sizeof *x_init);
  /* cos_init (x_init, p, t, n); */
  cos_init (x_init, t, y, n);
  gsl_vector_view x = gsl_vector_view_array (x_init, p);
  
  /* allocate workspace with default parameters */
  w = gsl_multifit_nlinear_alloc (Trust, &fdf_params, n, p);

  /* initialize solver with starting point and weights */
  gsl_multifit_nlinear_init (&x.vector, &fdf, w);

  /* compute initial cost function */
  f = gsl_multifit_nlinear_residual(w);
  gsl_blas_ddot(f, f, &chisq0);

  /* solve the system with a maximum of 100 iterations */
  status = gsl_multifit_nlinear_driver(100, xtol, gtol, ftol,
                                       NULL, NULL, &info, w);
  if (status == GSL_SUCCESS){
    *mu = gsl_vector_get(w->x, 0);
    *A  = gsl_vector_get(w->x, 1);
    *dT = gsl_vector_get(w->x, 2);
    
    /* compute covariance of best fit parameters */
    /*
    gsl_matrix *covar = gsl_matrix_alloc (p, p);
    J = gsl_multifit_nlinear_jac(w);
    gsl_multifit_nlinear_covar (J, 0.0, covar);
    */
    
    /* compute final cost */
    /*
    double chisq;
    gsl_blas_ddot(f, f, &chisq);
    
    fprintf(stdout, "summary from method '%s/%s'\n",
            gsl_multifit_nlinear_name(w),
            gsl_multifit_nlinear_trs_name(w));
    fprintf(stdout, "number of iterations: %zu\n",
            gsl_multifit_nlinear_niter(w));
    fprintf(stdout, "function evaluations: %zu\n", fdf.nevalf);
    fprintf(stdout, "Jacobian evaluations: %zu\n", fdf.nevaldf);
    fprintf(stdout, "reason for stopping: %s\n",
            (info == 1) ? "small step size" : "small gradient");
    fprintf(stdout, "initial |f(x)| = %f\n", sqrt(chisq0));
    fprintf(stdout, "final   |f(x)| = %f\n", sqrt(chisq));
    */
    
    /*
    {
      double dof = n - p;
      double c = GSL_MAX_DBL(1, sqrt(chisq / dof));
    
      fprintf(stdout, "chisq/dof = %g\n", chisq / dof);
    
      fprintf (stdout, "mu = %.5f err = %.5f\n", *mu, sqrt(gsl_matrix_get(covar,0,0)));
      fprintf (stdout, "A  = %.5f err = %.5f\n", *A,  sqrt(gsl_matrix_get(covar,1,1)));
      fprintf (stdout, "dT = %.5f err = %.5f\n", *dT, sqrt(gsl_matrix_get(covar,2,2)));
    }
    
    gsl_matrix_free (covar);
    */
  } else {
    fprintf (stdout, "status = %s\n", gsl_strerror (status));
  }

  gsl_multifit_nlinear_free (w);
  free(x_init);
  /* fprintf (stderr, "params_Cos: %g %g %g\n", *mu, *A, *dT); */
  return;
}





void params_Gauss(arr *restrict X, double *Mn, double *sigma){
    *Mn    = gsl_stats_mean(pntr_of(X), 1, X->tlen);
    *sigma = gsl_stats_sd_m(pntr_of(X), 1, X->tlen, *Mn);
}

void params_Beta(arr *restrict X, double *a, double *b){
    double m = gsl_stats_mean      (pntr_of(X), 1, X->tlen);
    double v = gsl_stats_variance_m(pntr_of(X), 1, X->tlen, m);
    if (v > 0){
        double num = m*(1-m);
        if (v < num){
            double rat = num/v-1;
            *a =    m *rat;
            *b = (1-m)*rat;
        } else {
            printArrayFmtAllWHdr(stderr,X, "%g","Error: params_Beta: num=%g, m=%g, v=%g X - ",num,m,v);
        }
    } else {
        printArrayFmtAllWHdr(stderr,X, "%g","Error: params_Beta: m=%g, v=%g X - ",m,v);
    }
}



int gamcdf_f (const gsl_vector * x, void *data, gsl_vector * f){
  size_t  n = ((struct data *)data)->n;
  double *t = ((struct data *)data)->t;
  double *y = ((struct data *)data)->y;

  double ln_shape = gsl_vector_get (x, 0);
  double ln_scale = gsl_vector_get (x, 1);

  size_t i;
  for (i = 0; i < n; ++i){
      double Yi = gsl_cdf_gamma_P(t[i], exp(ln_shape), exp(ln_scale));
      gsl_vector_set (f, i, Yi - y[i]);
  }

  return GSL_SUCCESS;
}

/* int gamcdf_init (double *x, size_t p, double *t, size_t n){ */
int gamcdf_init (double *x, double *t, size_t n){
  /* Calculate some stats on t */
  double t_mean     = gsl_stats_mean    (t, 1, n);
  double t_variance = gsl_stats_variance(t, 1, n);
  
  /* Calculate parameters based on moments calculated above */
  double t_scale = t_variance/t_mean;
  double t_shape = (t_mean*t_mean)/t_variance;

  if (t_shape > 0) { x[0] = log(t_shape); } else { x[0] = -5.0; }
  if (t_scale > 0) { x[1] = log(t_scale); } else { x[1] = -5.0; }
 
  return GSL_SUCCESS;
}

void callback(const size_t iter, void *params,
              const gsl_multifit_nlinear_workspace *w){
  gsl_vector *f = gsl_multifit_nlinear_residual(w);
  gsl_vector *x = gsl_multifit_nlinear_position(w);
  double rcond;

  /* compute reciprocal condition number of J(x) */
  gsl_multifit_nlinear_rcond(&rcond, w);

  fprintf(stdout, "iter %2zu: ln_shape = %.4f, ln_scale = %.4f cond(J) = %8.4f, |f(x)| = %.4f\n",
          iter,
          gsl_vector_get(x, 0),
          gsl_vector_get(x, 1),
          1.0 / rcond,
          gsl_blas_dnrm2(f));
}

void params_Gamma(arr *restrict X, double *shape, double *scale){
  const gsl_multifit_nlinear_type *T = gsl_multifit_nlinear_trust;
  gsl_multifit_nlinear_workspace *w;
  gsl_multifit_nlinear_fdf fdf;
  gsl_multifit_nlinear_parameters fdf_params =
    gsl_multifit_nlinear_default_parameters();
  fdf_params.trs = gsl_multifit_nlinear_trs_lmaccel;
  const size_t n = (size_t)X->tlen;
  const size_t p = 2;

  gsl_vector *f;
  arr Xsrtd = copyAr(X);
  double *t = pntr_of(&Xsrtd);
  double *y = malloc(n*sizeof *y);
  struct data d = { n, t, y };
  double chisq0;
  int status, info;
  size_t i;

  const double xtol = 1e-8;
  const double gtol = 1e-8;
  const double ftol = 0.0;

  /* define the function to be minimized */
  fdf.f   = gamcdf_f;
  fdf.df  = NULL;     /* set to NULL for finite-difference Jacobian */
  fdf.fvv = NULL;     /* not using geodesic acceleration */
  fdf.n = n;
  fdf.p = p;
  fdf.params = &d;

  /* this is the data to be fitted */
  for (i = 0; i < n; ++i){
      y[i] = (double)(i+1)/(double)n;
  };

  qsort (t, n, sizeof(double), compare_dbls);
  
  double *x_init = malloc(p*sizeof *x_init);
  /* gamcdf_init (x_init, p, t, n); */
  gamcdf_init (x_init, t, n);
  gsl_vector_view x = gsl_vector_view_array (x_init, p);
  
  /* allocate workspace with default parameters */
  w = gsl_multifit_nlinear_alloc (T, &fdf_params, n, p);

  /* initialize solver with starting point and weights */
  gsl_multifit_nlinear_init (&x.vector, &fdf, w);

  /* compute initial cost function */
  f = gsl_multifit_nlinear_residual(w);
  gsl_blas_ddot(f, f, &chisq0);

  /* solve the system with a maximum of 100 iterations */
  status = gsl_multifit_nlinear_driver(100, xtol, gtol, ftol,
                                       NULL, NULL, &info, w);
  if (status == GSL_SUCCESS){
    *shape = exp(gsl_vector_get(w->x, 0));
    *scale = exp(gsl_vector_get(w->x, 1));
    
    /* compute covariance of best fit parameters */
    /*
    gsl_matrix *covar = gsl_matrix_alloc (p, p);
    gsl_matrix *J = gsl_multifit_nlinear_jac(w);
    gsl_multifit_nlinear_covar (J, 0.0, covar);
    */
    
    /* compute final cost */
    /*
    double chisq;
    gsl_blas_ddot(f, f, &chisq);
    
    fprintf(stdout, "summary from method '%s/%s'\n",
            gsl_multifit_nlinear_name(w),
            gsl_multifit_nlinear_trs_name(w));
    fprintf(stdout, "number of iterations: %zu\n",
            gsl_multifit_nlinear_niter(w));
    fprintf(stdout, "function evaluations: %zu\n", fdf.nevalf);
    fprintf(stdout, "Jacobian evaluations: %zu\n", fdf.nevaldf);
    fprintf(stdout, "reason for stopping: %s\n",
            (info == 1) ? "small step size" : "small gradient");
    fprintf(stdout, "initial |f(x)| = %f\n", sqrt(chisq0));
    fprintf(stdout, "final   |f(x)| = %f\n", sqrt(chisq));
    */
    
    /*
    {
      double dof = n - p;
      double c = GSL_MAX_DBL(1, sqrt(chisq / dof));
    
      fprintf(stdout, "chisq/dof = %g\n", chisq / dof);
    
      fprintf (stdout, "ln_shape = %.5f shape = %.5f err = %.5f\n", gsl_vector_get(w->x, 0), *shape, sqrt(gsl_matrix_get(covar,0,0)));
      fprintf (stdout, "ln_scale = %.5f scale = %.5f err = %.5f\n", gsl_vector_get(w->x, 1), *scale, sqrt(gsl_matrix_get(covar,1,1)));
    }
    
    gsl_matrix_free (covar);
    */
  } else {
    fprintf (stdout, "params_Gamma: status = %s\n", gsl_strerror (status));
  }

  gsl_multifit_nlinear_free (w);
  free(x_init);
  freeAr(&Xsrtd);
  free(y);
  return;
}



int weibcdf_f (const gsl_vector * x, void *data, gsl_vector * f){
  size_t  n = ((struct data *)data)->n;
  double *t = ((struct data *)data)->t;
  double *y = ((struct data *)data)->y;

  double ln_scale = gsl_vector_get (x, 0);
  double ln_exp = gsl_vector_get (x, 1);

  size_t i;
  for (i = 0; i < n; ++i){
      double Yi = gsl_cdf_weibull_P(t[i], exp(ln_scale), exp(ln_exp));
      gsl_vector_set (f, i, Yi - y[i]);
  }

  return GSL_SUCCESS;
}

/* int weibcdf_init (double *x, size_t p, double *t, size_t n){ */
int weibcdf_init (double *x, double *t, size_t n){
  /* Calculate some stats on t */
  double t_mean     = gsl_stats_mean    (t, 1, n);
/* double t_variance = gsl_stats_variance(t, 1, n); */
  
  /* Calculate parameters based on moments calculated above */
  double t_scale = t_mean;
/*  double t_pexp  = 1.0; */

  if (t_scale > 0) { x[0] = log(t_scale); } else { x[0] = -5.0; }
  x[1] = 0.0;
 
  return GSL_SUCCESS;
}

void callback_wbl(const size_t iter, void *params,
              const gsl_multifit_nlinear_workspace *w){
  gsl_vector *f = gsl_multifit_nlinear_residual(w);
  gsl_vector *x = gsl_multifit_nlinear_position(w);
  double rcond;

  /* compute reciprocal condition number of J(x) */
  gsl_multifit_nlinear_rcond(&rcond, w);

  fprintf(stdout, "iter %2zu: ln_scale = %.4f, ln_exp = %.4f cond(J) = %8.4f, |f(x)| = %.4f\n",
          iter,
          gsl_vector_get(x, 0),
          gsl_vector_get(x, 1),
          1.0 / rcond,
          gsl_blas_dnrm2(f));
}

void params_Weibull(arr *restrict X, double *scale, double *pexp){
  const gsl_multifit_nlinear_type *T = gsl_multifit_nlinear_trust;
  gsl_multifit_nlinear_workspace *w;
  gsl_multifit_nlinear_fdf fdf;
  gsl_multifit_nlinear_parameters fdf_params =
    gsl_multifit_nlinear_default_parameters();
  fdf_params.trs = gsl_multifit_nlinear_trs_lmaccel;
  const size_t n = (size_t)X->tlen;
  const size_t p = 2;

  gsl_vector *f;
  arr Xsrtd = copyAr(X);
  double *t = pntr_of(&Xsrtd);
  double *y = malloc(n*sizeof *y);
  struct data d = { n, t, y };
  double chisq0;
  int status, info;
  size_t i;

  const double xtol = 1e-8;
  const double gtol = 1e-8;
  const double ftol = 0.0;

  /* define the function to be minimized */
  fdf.f   = weibcdf_f;
  fdf.df  = NULL;     /* set to NULL for finite-difference Jacobian */
  fdf.fvv = NULL;     /* not using geodesic acceleration */
  fdf.n = n;
  fdf.p = p;
  fdf.params = &d;

  /* this is the data to be fitted */
  for (i = 0; i < n; ++i){
      y[i] = (double)(i+1)/(double)n;
  };

  qsort (t, n, sizeof(double), compare_dbls);
  
  double *x_init = malloc(p*sizeof *x_init);
  /* weibcdf_init (x_init, p, t, n); */
  weibcdf_init (x_init, t, n);
  gsl_vector_view x = gsl_vector_view_array (x_init, p);
  
  /* allocate workspace with default parameters */
  w = gsl_multifit_nlinear_alloc (T, &fdf_params, n, p);

  /* initialize solver with starting point and weights */
  gsl_multifit_nlinear_init (&x.vector, &fdf, w);

  /* compute initial cost function */
  f = gsl_multifit_nlinear_residual(w);
  gsl_blas_ddot(f, f, &chisq0);

  /* solve the system with a maximum of 100 iterations */
  status = gsl_multifit_nlinear_driver(100, xtol, gtol, ftol,
                                       NULL, NULL, &info, w);
  if (status == GSL_SUCCESS){
    *scale = exp(gsl_vector_get(w->x, 0));
    *pexp  = exp(gsl_vector_get(w->x, 1));
    
    /* compute covariance of best fit parameters */
    /*
    gsl_matrix *covar = gsl_matrix_alloc (p, p);
    gsl_matrix *J = gsl_multifit_nlinear_jac(w);
    gsl_multifit_nlinear_covar (J, 0.0, covar);
    */
    
    /* compute final cost */
    /*
    double chisq;
    gsl_blas_ddot(f, f, &chisq);
    
    fprintf(stdout, "summary from method '%s/%s'\n",
            gsl_multifit_nlinear_name(w),
            gsl_multifit_nlinear_trs_name(w));
    fprintf(stdout, "number of iterations: %zu\n",
            gsl_multifit_nlinear_niter(w));
    fprintf(stdout, "function evaluations: %zu\n", fdf.nevalf);
    fprintf(stdout, "Jacobian evaluations: %zu\n", fdf.nevaldf);
    fprintf(stdout, "reason for stopping: %s\n",
            (info == 1) ? "small step size" : "small gradient");
    fprintf(stdout, "initial |f(x)| = %f\n", sqrt(chisq0));
    fprintf(stdout, "final   |f(x)| = %f\n", sqrt(chisq));
    
    {
      double dof = n - p;
      double c = GSL_MAX_DBL(1, sqrt(chisq / dof));
    
      fprintf(stdout, "chisq/dof = %g\n", chisq / dof);
    
      fprintf (stdout, "ln_scale = %.5f scale = %.5f err = %.5f\n", gsl_vector_get(w->x, 0), *scale, sqrt(gsl_matrix_get(covar,0,0)));
      fprintf (stdout, "ln_exp   = %.5f pexp  = %.5f err = %.5f\n", gsl_vector_get(w->x, 1), *pexp,  sqrt(gsl_matrix_get(covar,1,1)));
    }
    
    gsl_matrix_free (covar);
    */
  } else {
    fprintf (stdout, "params_Weibull: status = %s\n", gsl_strerror (status));
  }
  
  gsl_multifit_nlinear_free (w);
  free(x_init);
  freeAr(&Xsrtd);
  free(y);
  return;
}



int gumb1cdf_f (const gsl_vector * x, void *data, gsl_vector * f){
  size_t  n = ((struct data *)data)->n;
  double *t = ((struct data *)data)->t;
  double *y = ((struct data *)data)->y;

  double ln_a = gsl_vector_get (x, 0);
  double ln_b = gsl_vector_get (x, 1);
  double u    = gsl_vector_get (x, 2);

  size_t i;
  for (i = 0; i < n; ++i){
      double Yi = gsl_cdf_gumbel1_P(t[i]-u, exp(ln_a), exp(ln_b));
      gsl_vector_set (f, i, Yi - y[i]);
  }

  return GSL_SUCCESS;
}

/* int gumb1cdf_init (double *x, size_t p, double *t, size_t n){ */
int gumb1cdf_init (double *x, double *t, size_t n){
  /* Calculate some stats on t */
  double t_mean     = gsl_stats_mean    (t, 1, n);
  
  /* Calculate parameters based on moments calculated above */

  x[0] = -1.0;
  x[1] = -1.0;
  x[2] = t_mean;
 
  return GSL_SUCCESS;
}

void callback_gum1(const size_t iter, void *params,
              const gsl_multifit_nlinear_workspace *w){
  gsl_vector *f = gsl_multifit_nlinear_residual(w);
  gsl_vector *x = gsl_multifit_nlinear_position(w);
  double rcond;

  /* compute reciprocal condition number of J(x) */
  gsl_multifit_nlinear_rcond(&rcond, w);

  fprintf(stdout, "iter %2zu: ln_a = %.4f, ln_b = %.4f, u = %.4f cond(J) = %8.4f, |f(x)| = %.4f\n",
          iter,
          gsl_vector_get(x, 0),
          gsl_vector_get(x, 1),
          gsl_vector_get(x, 2),
          1.0 / rcond,
          gsl_blas_dnrm2(f));
}

void params_Gumbel1(arr *restrict X, double *a, double *b, double *u){
  const gsl_multifit_nlinear_type *T = gsl_multifit_nlinear_trust;
  gsl_multifit_nlinear_workspace *w;
  gsl_multifit_nlinear_fdf fdf;
  gsl_multifit_nlinear_parameters fdf_params =
    gsl_multifit_nlinear_default_parameters();
  fdf_params.trs = gsl_multifit_nlinear_trs_lmaccel;
  const size_t n = (size_t)X->tlen;
  const size_t p = 3;

  gsl_vector *f;
  arr Xsrtd = copyAr(X);
  double *t = pntr_of(&Xsrtd);
  double *y = malloc(n*sizeof *y);
  struct data d = { n, t, y };
  double chisq0;
  int status, info;
  size_t i;

  const double xtol = 1e-8;
  const double gtol = 1e-8;
  const double ftol = 0.0;

  /* define the function to be minimized */
  fdf.f   = gumb1cdf_f;
  fdf.df  = NULL;     /* set to NULL for finite-difference Jacobian */
  fdf.fvv = NULL;     /* not using geodesic acceleration */
  fdf.n = n;
  fdf.p = p;
  fdf.params = &d;

  /* this is the data to be fitted */
  for (i = 0; i < n; ++i){
      y[i] = (double)(i+1)/(double)n;
  };

  qsort (t, n, sizeof(double), compare_dbls);
  
  double *x_init = malloc(p*sizeof *x_init);
  /* gumb1cdf_init (x_init, p, t, n); */
  gumb1cdf_init (x_init, t, n);
  gsl_vector_view x = gsl_vector_view_array (x_init, p);
  
  /* allocate workspace with default parameters */
  w = gsl_multifit_nlinear_alloc (T, &fdf_params, n, p);

  /* initialize solver with starting point and weights */
  gsl_multifit_nlinear_init (&x.vector, &fdf, w);

  /* compute initial cost function */
  f = gsl_multifit_nlinear_residual(w);
  gsl_blas_ddot(f, f, &chisq0);

  /* solve the system with a maximum of 100 iterations */
  status = gsl_multifit_nlinear_driver(100, xtol, gtol, ftol,
                                       NULL, NULL, &info, w);
  if (status == GSL_SUCCESS){
    *a = exp(gsl_vector_get(w->x, 0));
    *b = exp(gsl_vector_get(w->x, 1));
    *u = gsl_vector_get(w->x, 2);
    
    /* compute covariance of best fit parameters */
    /*
    gsl_matrix *covar = gsl_matrix_alloc (p, p);
    gsl_matrix *J = gsl_multifit_nlinear_jac(w);
    gsl_multifit_nlinear_covar (J, 0.0, covar);
    */
    
    /* compute final cost */
    /*
    double chisq;
    gsl_blas_ddot(f, f, &chisq);
    
    fprintf(stdout, "summary from method '%s/%s'\n",
            gsl_multifit_nlinear_name(w),
            gsl_multifit_nlinear_trs_name(w));
    fprintf(stdout, "number of iterations: %zu\n",
            gsl_multifit_nlinear_niter(w));
    fprintf(stdout, "function evaluations: %zu\n", fdf.nevalf);
    fprintf(stdout, "Jacobian evaluations: %zu\n", fdf.nevaldf);
    fprintf(stdout, "reason for stopping: %s\n",
            (info == 1) ? "small step size" : "small gradient");
    fprintf(stdout, "initial |f(x)| = %f\n", sqrt(chisq0));
    fprintf(stdout, "final   |f(x)| = %f\n", sqrt(chisq));
    */
    
    /*
    {
      double dof = n - p;
      double c = GSL_MAX_DBL(1, sqrt(chisq / dof));
    
      fprintf(stdout, "chisq/dof = %g\n", chisq / dof);
    
      fprintf (stdout, "ln_a = %.5f a = %.5f err = %.5f\n", gsl_vector_get(w->x, 0), *a, sqrt(gsl_matrix_get(covar,0,0)));
      fprintf (stdout, "ln_b = %.5f b = %.5f err = %.5f\n", gsl_vector_get(w->x, 1), *b, sqrt(gsl_matrix_get(covar,1,1)));
      fprintf (stdout, "            u = %.5f err = %.5f\n",                          *u, sqrt(gsl_matrix_get(covar,2,2)));
    }
    
    gsl_matrix_free (covar);
    */
  } else {
    fprintf (stdout, "status = %s\n", gsl_strerror (status));
  }

  gsl_multifit_nlinear_free (w);
  free(x_init);
  freeAr(&Xsrtd);
  free(y);
  return;
}



int gumb2cdf_f (const gsl_vector * x, void *data, gsl_vector * f){
  size_t  n = ((struct data *)data)->n;
  double *t = ((struct data *)data)->t;
  double *y = ((struct data *)data)->y;

  double ln_a = gsl_vector_get (x, 0);
  double ln_b = gsl_vector_get (x, 1);

  size_t i;
  for (i = 0; i < n; ++i){
      double Yi = gsl_cdf_gumbel2_P(t[i], exp(ln_a), exp(ln_b));
      gsl_vector_set (f, i, Yi - y[i]);
  }

  return GSL_SUCCESS;
}

/* int gumb2cdf_init (double *x, size_t p, double *t, size_t n){ */
int gumb2cdf_init (double *x){
  x[0] = -0.5;
  x[1] = -0.5;
 
  return GSL_SUCCESS;
}

void callback_gum2(const size_t iter, void *params,
              const gsl_multifit_nlinear_workspace *w){
  gsl_vector *f = gsl_multifit_nlinear_residual(w);
  gsl_vector *x = gsl_multifit_nlinear_position(w);
  double rcond;

  /* compute reciprocal condition number of J(x) */
  gsl_multifit_nlinear_rcond(&rcond, w);

  fprintf(stdout, "iter %2zu: ln_a = %.4f, ln_b = %.4f cond(J) = %8.4f, |f(x)| = %.4f\n",
          iter,
          gsl_vector_get(x, 0),
          gsl_vector_get(x, 1),
          1.0 / rcond,
          gsl_blas_dnrm2(f));
}

void params_Gumbel2(arr *restrict X, double *a, double *b){
  const gsl_multifit_nlinear_type *T = gsl_multifit_nlinear_trust;
  gsl_multifit_nlinear_workspace *w;
  gsl_multifit_nlinear_fdf fdf;
  gsl_multifit_nlinear_parameters fdf_params =
    gsl_multifit_nlinear_default_parameters();
  fdf_params.trs = gsl_multifit_nlinear_trs_lmaccel;
  const size_t n = (size_t)X->tlen;
  const size_t p = 2;

  gsl_vector *f;
  arr Xsrtd = copyAr(X);
  double *t = pntr_of(&Xsrtd);
  double *y = malloc(n*sizeof *y);
  struct data d = { n, t, y };
  double chisq0;
  int status, info;
  size_t i;

  const double xtol = 1e-8;
  const double gtol = 1e-8;
  const double ftol = 0.0;

  /* define the function to be minimized */
  fdf.f   = gumb2cdf_f;
  fdf.df  = NULL;     /* set to NULL for finite-difference Jacobian */
  fdf.fvv = NULL;     /* not using geodesic acceleration */
  fdf.n = n;
  fdf.p = p;
  fdf.params = &d;

  /* this is the data to be fitted */
  for (i = 0; i < n; ++i){
      y[i] = (double)(i+1)/(double)n;
  };

  qsort (t, n, sizeof(double), compare_dbls);
  
  double *x_init = malloc(p*sizeof *x_init);
  /* gumb2cdf_init (x_init, p, t, n); */
  gumb2cdf_init (x_init);
  gsl_vector_view x = gsl_vector_view_array (x_init, p);
  
  /* allocate workspace with default parameters */
  w = gsl_multifit_nlinear_alloc (T, &fdf_params, n, p);

  /* initialize solver with starting point and weights */
  gsl_multifit_nlinear_init (&x.vector, &fdf, w);

  /* compute initial cost function */
  f = gsl_multifit_nlinear_residual(w);
  gsl_blas_ddot(f, f, &chisq0);

  /* solve the system with a maximum of 100 iterations */
  status = gsl_multifit_nlinear_driver(100, xtol, gtol, ftol,
                                       NULL, NULL, &info, w);
  if (status == GSL_SUCCESS){
    *a = exp(gsl_vector_get(w->x, 0));
    *b = exp(gsl_vector_get(w->x, 1));
    
    /* compute covariance of best fit parameters */
    /*
    gsl_matrix *covar = gsl_matrix_alloc (p, p);
    gsl_matrix *J = gsl_multifit_nlinear_jac(w);
    gsl_multifit_nlinear_covar (J, 0.0, covar);
    */
    
    /* compute final cost */
    /*
    double chisq;
    gsl_blas_ddot(f, f, &chisq);
    
    fprintf(stdout, "summary from method '%s/%s'\n",
            gsl_multifit_nlinear_name(w),
            gsl_multifit_nlinear_trs_name(w));
    fprintf(stdout, "number of iterations: %zu\n",
            gsl_multifit_nlinear_niter(w));
    fprintf(stdout, "function evaluations: %zu\n", fdf.nevalf);
    fprintf(stdout, "Jacobian evaluations: %zu\n", fdf.nevaldf);
    fprintf(stdout, "reason for stopping: %s\n",
            (info == 1) ? "small step size" : "small gradient");
    fprintf(stdout, "initial |f(x)| = %f\n", sqrt(chisq0));
    fprintf(stdout, "final   |f(x)| = %f\n", sqrt(chisq));
    */
    
    /*
    {
      double dof = n - p;
      double c = GSL_MAX_DBL(1, sqrt(chisq / dof));
    
      fprintf(stdout, "chisq/dof = %g\n", chisq / dof);
    
      fprintf (stdout, "ln_a = %.5f a = %.5f err = %.5f\n", gsl_vector_get(w->x, 0), *a, sqrt(gsl_matrix_get(covar,0,0)));
      fprintf (stdout, "ln_b = %.5f b = %.5f err = %.5f\n", gsl_vector_get(w->x, 1), *b, sqrt(gsl_matrix_get(covar,1,1)));
    }
    
    gsl_matrix_free (covar);
    */
  } else {
    fprintf (stdout, "status = %s\n", gsl_strerror (status));
  }

  gsl_multifit_nlinear_free (w);
  free(x_init);
  freeAr(&Xsrtd);
  free(y);
  return;
}



#endif
