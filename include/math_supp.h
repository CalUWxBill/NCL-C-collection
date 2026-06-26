/* Created by Bill Scheftic */
/*------------------------------------*/
/* Header for Mathematical Functions  */
/*------------------------------------*/
#ifndef  _MTH_SUPP_
#define  _MTH_SUPP_

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#define _USE_MATH_DEFINES
#include <math.h>
/* #include <normsinv.h> */

#if !defined(M_PI)
# define M_E		2.7182818284590452354	/* e */
# define M_LOG2E	1.4426950408889634074	/* log_2 e */
# define M_LOG10E	0.43429448190325182765	/* log_10 e */
# define M_LN2		0.69314718055994530942	/* log_e 2 */
# define M_LN10		2.30258509299404568402	/* log_e 10 */
# define M_PI		3.14159265358979323846	/* pi */
# define M_PI_2		1.57079632679489661923	/* pi/2 */
# define M_PI_4		0.78539816339744830962	/* pi/4 */
# define M_1_PI		0.31830988618379067154	/* 1/pi */
# define M_2_PI		0.63661977236758134308	/* 2/pi */
# define M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
# define M_SQRT2	1.41421356237309504880	/* sqrt(2) */
# define M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */
#endif

#define DOUBLE_EPS 2.22045E-16
#define FLOAT_EPS 1.192e-07
#define EXP_THRESH 700

const double PI_180 = M_PI/180.0;
const double TWO_PI = 2.0*M_PI;

/*------------------------*/
/* Function Declarations  */
/*------------------------*/

/* double expm1_c(double x); */
double exp_c(double x);

int isVal(double, double);		/* compares two doubles within the precision of the number */
/* int isValFlt(float, float); */
int isNear(double, double);		/* compares two doubles within a precision relevant to ascii text (~ 7 sig. figs.) */
/* int isNan(double); */

/* Should rename these since not, and, or are keywords in C++ and maybe even C now */
/* int not(double);        */
/* int and(double,double); */
/* int or(double, double); */
int eq(double, double);
int ne(double, double);
int gt(double, double);
int lt(double, double);
int ge(double, double);
int le(double, double);

int inot(int);
int iand(int,int);
int ior(int, int);
int ieq(int, int);
int ine(int, int);
int igt(int, int);
int ilt(int, int);
int ige(int, int);
int ile(int, int);

int ineg(int);

int imin(int, int);
int imax(int, int);

double neg(double);

double signof(double);
double add(double, double);
double sub(double, double);
double mult(double, double);
double Div(double, double);

double angadd(double, double);
double angsub(double, double);
double angmult(double, double);
double angdiv(double, double);

double devSq(double, double);
double amax2(double, double);
double amin2(double, double);
double amax3(double, double, double);
double amin3(double, double, double);
double dim(double,double);

int myRound(double);
int TriangularNumber(int);
int fact(int);
int factpart(int,int);
int nCk(int, int);

double erfi(double);

/* double normRand(); */
double linInterp(double x,double x1,double x2,double y1,double y2);
double LambertW(const double z);
const int dbgW=0;
/* double em2=0.3678794411714423215955237701614608; */
double em2=0.3645;


double dist  (double, double);
double dist2d(double, double, double, double);
double dist3d(double, double, double);

double where(int, double, double);

double ceq_mean (double, double);
double ceq_var  (double, double, double);
double ceq_std_s(double, double, double);
double ceq_std_welford(double sum0,double sum1,double sum2);
double ceq_std_p(double, double, double);
double ceq_cov  (double, double, double, double);
double ceq_slope     (double, double, double, double, double);
double ceq_orthoslope(double, double, double, double, double, double);
double ceq_corr      (double, double, double, double, double, double);

double eq_ndvi(double, double);


/* hwrs560_transform_wnd_sres.c */
double calcZscore(double x,double meanx,double stdx);
double invZscore(double z,double meanx,double stdx);
double calcX(double u,double meanx,double stdx);
double calcY(double u,double v,double meany,double stdx,double stdy,double rho);



double expm1_c(double x){
	double y;
	if (x > EXP_THRESH){
		double logmax = log(DBL_MAX);
		double a = logmax - EXP_THRESH;
		double x_ = EXP_THRESH + a*log(x-EXP_THRESH)/logmax;
		y = expm1(x_);
	} else {
		y = expm1(x);
	}
	return y;
}

double exp_c(double x){
	double y;
	if (x > EXP_THRESH){
		double logmax = log(DBL_MAX);
		double a = logmax - EXP_THRESH;
		double x_ = EXP_THRESH + a*log(x-EXP_THRESH)/logmax;
		y = exp(x_);
	} else {
		y = exp(x);
	}
	return y;
}



int isVal(double x, double y) {

	if ((x <= y + fabs(y*DOUBLE_EPS)) && (x >= y - fabs(y*DOUBLE_EPS))){ return 1; }

	return 0;
}
  
int isValFlt(float x, float y) {

	if ((x <= y + fabs(y*FLOAT_EPS)) && (x >= y - fabs(y*FLOAT_EPS))){ return 1; }

	return 0;
}

int isNear(double x, double y) {

	double percdiff = .0001;		/* 1 ten-thousandth difference, mostly for ascii originated values */

	if ((x <= y + fabs(y*percdiff)) && (x >= y - fabs(y*percdiff))){ return 1; }

	return 0;
}

/*-----------------------------*/
/* Operators as Functions      */
/*-----------------------------*/

/* int not(double x) { return (!x); }            */
/* int and(double x,double y) { return (x&&y); } */
/* int or(double x,double y) { return (x||y); }  */
int eq(double x,double y) { return (x==y); }
int ne(double x,double y) { return (x!=y); }
int gt(double x,double y) { return (x>y);  }
int ge(double x,double y) { return (x>=y); }
int lt(double x,double y) { return (x<y);  }
int le(double x,double y) { return (x<=y); }

int inot(int x) { return (!x); }
int iand(int x,int y) { return (x&&y); }
int ior(int x,int y) { return (x||y); }
int ieq(int x,int y) { return (x==y); }
int ine(int x,int y) { return (x!=y); }
int igt(int x,int y) { return (x>y);  }
int ige(int x,int y) { return (x>=y); }
int ilt(int x,int y) { return (x<y);  }
int ile(int x,int y) { return (x<=y); }

int imin(int a, int b) {
	if (a < b) { return a; } else { return b; }
	return 0;
}

int imax(int a, int b) {
	if (a > b) { return a; } else { return b; }
	return 0;
}

double neg(double x) { return (-x); }

int ineg(int x) { return (-x); }

double signof  (double x){ if (x >= 0) {return 1.0; } else { return -1.0; } }
double add     (double x, double y) { return (x+y); }
double sub     (double x, double y) { return (x-y); }
double mult    (double x, double y) { return (x*y); }
double mult3   (double x, double y, double z) { return (x*y*z); }
double mult4   (double x, double y, double z, double t) { return (x*y*z*t); }
double mult5   (double x, double y, double z, double t, double u) { return (x*y*z*t*u); }
double Div     (double x, double y) { return (x/y); } /* lowercase div is in stdlib.h */
double devSq   (double x, double y) { return (x-y)*(x-y); }
double devAbs  (double x, double y) { return fabs(x-y); }


double angbtwpi(double ang1){
    double ang=ang1;
    if (ang > M_PI){
        ang -= 2*M_PI;
    } else if (ang < -M_PI){
        ang += 2*M_PI;
    }
    return ang;
}

double angadd(double ang1, double ang2) {
    double ang = ang1 + ang2;
    return angbtwpi(ang);
}

double angsub(double ang1, double ang2) {
    double ang = ang1 - ang2;
    return angbtwpi(ang);
}

double angmult(double x, double ang1) {
    double ang = x*ang1;
    ang = fmod(ang,2*M_PI);
    return angbtwpi(ang);
}

double angdiv(double ang1, double y) {
    return (ang1/y);
}

/*	Should be safe to remove redundant conditions in these functions	*/
double amax2(double a, double b) {
/*
	if (a > b) { return a; }
	if (b >= a) { return b; }
	return 0.00;
 */
	if (a > b) { return a; } else { return b; }
}

double amin2(double a, double b) {
/*
	if (a < b) { return a; }
	if (b <= a) { return b; }
	return 0.00;
 */
	if (a < b) { return a; } else { return b; }
}

double amax3(double a, double b, double c) {
/*
	if ((a >= b) && (a >= c)) { return a; }
	if ((b >= a) && (b >= c)) { return b; }
	if ((c >= a) && (c >= b)) { return c; }
	return 0.00;
 */
	if (a >= b){
		if (a >= c){
			return a;
		} else {
			return c;
		}
	} else if (b >= c){
		return b;
	} else {
		return c;
	}
}

double amin3(double a, double b, double c) {
/*
	if ((a <= b) && (a <= c)) { return a; }
	if ((b <= a) && (b <= c)) { return b; }
	if ((c <= a) && (c <= b)) { return c; }
	return 0.00;
 */
	if (a <= b){
		if (a <= c){
			return a;
		} else {
			return c;
		}
	} else if (b <= c){
		return b;
	} else {
		return c;
	}
}

double dim(double a,double b) {
/*
	if ((a-b) > 0) { return a-b; }
	if ((a-b) <= 0) { return 0; }
	return 0.00;
 */
	if ((a-b) > 0) { return a-b; } else { return 0; }
}

double mx_b(double m,double x,double b) {
    return m*x+b;
}



/*-----------------------------*/
/* Specialized Functions       */
/*-----------------------------*/

int myRound(double x) {
	int result;
	double resdbl;
	if (x >=0) {
		result = (int)(x+0.5);
	} else {
		result = (int)(x-0.5);
	}

	return result;
}

/* Don't remember why I created a duplicate */
int myRound2(double x) {
	int result;
	double resdbl;
	if (x >=0) {
		result = (int)(x+0.5);
	} else {
		result = (int)(x-0.5);
	}

	return result;
}

int TriangularNumber(int n)
{ return n*(n+1)/2;
}

int fact(int n)
{ if ( n == 0 ) { return 1; }
  int r = 1;
  while (n >= 1) { r *= n; n--; }
  return r;
}

int factpart(int n,int p)
{ if ( n == 0 ) { return 1; }
  int r = 1;
  while (n >= p) { r *= n; n--; }
  return r;
}

int nCk(int n, int k){ 
  int i,r = 1;
  for (i=0;i<k;i++){
	r *= (n-i);
	r /= (i+1);
  }

  return r;
}

double erfi(double x){
  /* http://algo.inria.fr/esf/function/ERFI/ERFI.pdf */

  int nIters,i;
  double n_2,n,u_2,u;

    nIters = 20;
    u_2 = 2;
    double y = u_2 * x;
    for(i = 1;i<=nIters;i++){
        n = (double)(i * 2 + 1);
        n_2 = n - 2;
        u = (2 * n_2 * u_2) / (pow(n_2,2) + 3 * n_2 + 2);
        y += u * pow(x,n);
        u_2 = u;
    }
  
  y *= pow(M_PI,-0.5);
  return y;
}

/*
double normRand()
{ int prec = 10000;
  double percent = 0.0;
  while ((percent == 0.00) || (percent == 1.00))
  { percent = ((double)(rand()%prec))/prec;
  }
  double zscore = normsinv((long double)percent);
  return zscore;
}
 */

double linInterp(double x,double x1,double x2,double y1,double y2){
	double m = (y2-y1)/(x2-x1);
	double y = m*(x-x1) + y1;
	
	return y;
}

double LambertW(const double z)
{ int i; 
  const double eps=4.0e-16, em1=0.3678794411714423215955237701614608; 
  double p,e,t,w;
  if (dbgW) fprintf(stderr,"LambertW: z=%g\n",z);
  if (z<-em1 || isinf(z) || isnan(z))
  { fprintf(stderr,"LambertW: bad argument %g, exiting.\n",z); exit(1); 
  }
  if (0.0==z) return 0.0;
  if (z<-em1+1e-4)
  { /* series near -em1 in sqrt(q) */
    double q=z+em1,r=sqrt(q),q2=q*q,q3=q2*q;
    return 
     -1.0
     +2.331643981597124203363536062168*r
     -1.812187885639363490240191647568*q
     +1.936631114492359755363277457668*r*q
     -2.353551201881614516821543561516*q2
     +3.066858901050631912893148922704*r*q2
     -4.175335600258177138854984177460*q3
     +5.858023729874774148815053846119*r*q3
     -8.401032217523977370984161688514*q3*q;  /* error approx 1e-16 */
  }
  /* initial approx for iteration... */
  if (z<1.0)
  { /* series near 0 */
    p=sqrt(2.0*(2.7182818284590452353602874713526625*z+1.0));
    w=-1.0+p*(1.0+p*(-0.333333333333333333333+p*0.152777777777777777777777));
  } else 
    w=log(z); /* asymptotic */
  if (z>3.0) w-=log(w); /* useful? */
  for (i=0; i<10; i++)
  { /* Halley iteration */
    e=exp(w); 
    t=w*e-z;
    p=w+1.0;
    t/=e*p-0.5*(p+1.0)*t/p; 
    w-=t;
    if (fabs(t)<eps*(1.0+fabs(w))) return w; /* rel-abs error */
  }
  /* should never get here */
  fprintf(stderr,"LambertW: No convergence at z=%g, exiting.\n",z); 
  exit(1);
}


double dist(double x, double y){
  double r = sqrt((x*x)+(y*y));
  return r;
}

double dist2d(double x1, double y1,double x2, double y2){
  double x = x1-x2;
  double y = y1-y2;
  double r = sqrt((x*x)+(y*y));
  return r;
}

double dist3d(double x, double y,double z){
  double r = sqrt((x*x)+(y*y)+(z*z));
  return r;
}

double where(int c, double x, double y){
  if (c) { return x; } else { return y; }
  return -999.0;
}


double ceq_mean(double S, double n){
  if (n) { return S/n; }
  return -999.0;
}


double ceq_var(double Xsum, double Xsumsq, double N){
/* I think to get variance need to divide by N again */
  return Xsumsq - (Xsum*Xsum)/N;
}


double ceq_std_s(double Xsum, double Xsumsq, double N){
  return sqrt( (Xsumsq - (Xsum*Xsum)/N) / (N-1) );
}


double ceq_std_welford(double sum0,double sum1,double sum2){
/*
 *	Source:  prod_gamma_PDF_stats.c
 *	Purpose: potentially use welford algorithm
 *	Input:
 *	+	sum0   : []
 *	+	sum1   : []
 *	+	sum2   : []
 *	Output:
 *	+	stddev : []
 *---------------------------------------------------------------------
 */
  	double stddev = (1/sum0)*sqrt(sum0*sum2-sum1*sum1);
	return stddev;
}


double ceq_std_p(double Xsum, double Xsumsq, double N){
  return sqrt( (Xsumsq - (Xsum*Xsum)/N) / N );
}


double ceq_cov(double Xsum, double Ysum, double XYsum, double N){
  return XYsum  - (Xsum*Ysum)/N;
}


double ceq_slope(double Xsum, double Ysum, double Xsumsq, double XYsum, double N){
  double S2xx = ceq_var(Xsum,Xsumsq,N);
  double Sxy  = ceq_cov(Xsum,Ysum,XYsum,N);

  double slope;
  if (S2xx != 0){
    slope = Sxy/S2xx;
  } else {
    slope = -999.0;
  }

  return slope;
}


double ceq_orthoslope(double Xsum, double Ysum, double Xsumsq, double Ysumsq, double XYsum, double N){
  double S2xx = ceq_var(Xsum,Xsumsq,N);
  double S2yy = ceq_var(Ysum,Ysumsq,N);
  double Sxy  = ceq_cov(Xsum,Ysum,XYsum,N);

  double S2xx_err = 1.0;			/*	Error variances assumed equal for now!	*/
  double S2yy_err = 1.0;
  double eta = S2yy_err/S2xx_err;

  double num = (S2yy-eta*S2xx)+sqrt(pow(S2yy-eta*S2xx,2)+4*eta*Sxy*Sxy);
  /* if eta = inf then num = sqrt(pow(S2xx,2)+4*Sxy*Sxy)-S2xx */
  double den = 2*Sxy;

  double slope;
  if (den != 0){
    slope = num/den;
  } else {
    fputs("ceq_orthoslope: denominator equals zero!\n",stderr);
    slope = -999.0;
  }

  return slope;
}


double ceq_corr(double Xsum, double Ysum, double Xsumsq, double Ysumsq, double XYsum, double N){
  double S2xx = ceq_var(Xsum,Xsumsq,N);
  double S2yy = ceq_var(Ysum,Ysumsq,N);
  double Sxy  = ceq_cov(Xsum,Ysum,XYsum,N);

  double corr = Sxy/(sqrt(S2yy)*sqrt(S2xx));

  return corr;
}


double eq_ndvi(double R, double NIR){
  return (NIR-R)/(NIR+R);
}


/* hwrs560_transform_wnd_sres.c */
double calcZscore(double x,double meanx,double stdx){
  	double z = (x-meanx)/stdx;
	return z;
}


double invZscore(double z,double meanx,double stdx){
  	double x = (z*stdx) + meanx;
	return x;
}


double calcX(double u,double meanx,double stdx){
  	double x = meanx + stdx*u;
	return x;
}


double calcY(double u,double v,double meany,double stdx,double stdy,double rho){
  	double y = meany + stdx*rho*u + stdy*sqrt(1 - rho*rho)*v;
	return y;
}


#endif
