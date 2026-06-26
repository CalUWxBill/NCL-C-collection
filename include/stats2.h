/* Created by Bill Scheftic */
/*
 *  Contains many statistical operations on 1d arrays
 *  - fit_gamma_prms uses the Thom estimator to determine the gamma distribution parameters
 *  - RegrRef_TheilSen computes the Theil-Sen median slope regression used by getTCMultiRegression
 *    - It can also be called in NCL using theil_sen by loading named_stats.ncl
 */
#ifndef  _STATS_H_
#define  _STATS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <sort2.h>
#include <arrayops2.h>
#include <wrap_math.h>
#include <arraymath2.h>
#include <print_arrays2.h>

typedef struct { double a0, a1, r, n; } Linreg;

int misscheck = 1;

const double ttable[79][11] = {
  {1.000, 1.376, 1.963, 3.078, 6.314, 12.71, 31.82, 63.66, 127.3, 318.3, 636.6},
  {0.816, 1.061, 1.386, 1.886, 2.920, 4.303, 6.965, 9.925, 14.09, 22.33, 31.60}, 
  {0.765, 0.978, 1.250, 1.638, 2.353, 3.182, 4.541, 5.841, 7.453, 10.21, 12.92}, 
  {0.741, 0.941, 1.190, 1.533, 2.132, 2.776, 3.747, 4.604, 5.598, 7.173, 8.610}, 
  {0.727, 0.920, 1.156, 1.476, 2.015, 2.571, 3.365, 4.032, 4.773, 5.893, 6.869}, 
  {0.718, 0.906, 1.134, 1.440, 1.943, 2.447, 3.143, 3.707, 4.317, 5.208, 5.959}, 
  {0.711, 0.896, 1.119, 1.415, 1.895, 2.365, 2.998, 3.499, 4.029, 4.785, 5.408}, 
  {0.706, 0.889, 1.108, 1.397, 1.860, 2.306, 2.896, 3.355, 3.833, 4.501, 5.041}, 
  {0.703, 0.883, 1.100, 1.383, 1.833, 2.262, 2.821, 3.250, 3.690, 4.297, 4.781},
  {0.700, 0.879, 1.093, 1.372, 1.812, 2.228, 2.764, 3.169, 3.581, 4.144, 4.587}, 
  {0.697, 0.876, 1.088, 1.363, 1.796, 2.201, 2.718, 3.106, 3.497, 4.025, 4.437}, 
  {0.695, 0.873, 1.083, 1.356, 1.782, 2.179, 2.681, 3.055, 3.428, 3.930, 4.318}, 
  {0.694, 0.870, 1.079, 1.350, 1.771, 2.160, 2.650, 3.012, 3.372, 3.852, 4.221}, 
  {0.692, 0.868, 1.076, 1.345, 1.761, 2.145, 2.624, 2.977, 3.326, 3.787, 4.140}, 
  {0.691, 0.866, 1.074, 1.341, 1.753, 2.131, 2.602, 2.947, 3.286, 3.733, 4.073}, 
  {0.690, 0.865, 1.071, 1.337, 1.746, 2.120, 2.583, 2.921, 3.252, 3.686, 4.015},
  {0.689, 0.863, 1.069, 1.333, 1.740, 2.110, 2.567, 2.898, 3.222, 3.646, 3.965}, 
  {0.688, 0.862, 1.067, 1.330, 1.734, 2.101, 2.552, 2.878, 3.197, 3.610, 3.922}, 
  {0.688, 0.861, 1.066, 1.328, 1.729, 2.093, 2.539, 2.861, 3.174, 3.579, 3.883}, 
  {0.687, 0.860, 1.064, 1.325, 1.725, 2.086, 2.528, 2.845, 3.153, 3.552, 3.850}, 
  {0.686, 0.859, 1.063, 1.323, 1.721, 2.080, 2.518, 2.831, 3.135, 3.527, 3.819}, 
  {0.686, 0.858, 1.061, 1.321, 1.717, 2.074, 2.508, 2.819, 3.119, 3.505, 3.792}, 
  {0.685, 0.858, 1.060, 1.319, 1.714, 2.069, 2.500, 2.807, 3.104, 3.485, 3.767},
  {0.685, 0.857, 1.059, 1.318, 1.711, 2.064, 2.492, 2.797, 3.091, 3.467, 3.745}, 
  {0.684, 0.856, 1.058, 1.316, 1.708, 2.060, 2.485, 2.787, 3.078, 3.450, 3.725}, 
  {0.684, 0.856, 1.058, 1.315, 1.706, 2.056, 2.479, 2.779, 3.067, 3.435, 3.707}, 
  {0.684, 0.855, 1.057, 1.314, 1.703, 2.052, 2.473, 2.771, 3.057, 3.421, 3.690}, 
  {0.683, 0.855, 1.056, 1.313, 1.701, 2.048, 2.467, 2.763, 3.047, 3.408, 3.674}, 
  {0.683, 0.854, 1.055, 1.311, 1.699, 2.045, 2.462, 2.756, 3.038, 3.396, 3.659}, 
  {0.683, 0.854, 1.055, 1.310, 1.697, 2.042, 2.457, 2.750, 3.030, 3.385, 3.646},
  {0.683, 0.854, 1.055, 1.310, 1.697, 2.042, 2.457, 2.750, 3.030, 3.385, 3.646},
  {0.683, 0.854, 1.055, 1.310, 1.697, 2.042, 2.457, 2.750, 3.030, 3.385, 3.646},
  {0.683, 0.854, 1.055, 1.310, 1.697, 2.042, 2.457, 2.750, 3.030, 3.385, 3.646},
  {0.683, 0.854, 1.055, 1.310, 1.697, 2.042, 2.457, 2.750, 3.030, 3.385, 3.646},
  {0.683, 0.854, 1.055, 1.310, 1.697, 2.042, 2.457, 2.750, 3.030, 3.385, 3.646},
  {0.683, 0.854, 1.055, 1.310, 1.697, 2.042, 2.457, 2.750, 3.030, 3.385, 3.646},
  {0.683, 0.854, 1.055, 1.310, 1.697, 2.042, 2.457, 2.750, 3.030, 3.385, 3.646},
  {0.683, 0.854, 1.055, 1.310, 1.697, 2.042, 2.457, 2.750, 3.030, 3.385, 3.646},
  {0.683, 0.854, 1.055, 1.310, 1.697, 2.042, 2.457, 2.750, 3.030, 3.385, 3.646},
  {0.681, 0.851, 1.050, 1.303, 1.684, 2.021, 2.423, 2.704, 2.971, 3.307, 3.551},
  {0.681, 0.851, 1.050, 1.303, 1.684, 2.021, 2.423, 2.704, 2.971, 3.307, 3.551},
  {0.681, 0.851, 1.050, 1.303, 1.684, 2.021, 2.423, 2.704, 2.971, 3.307, 3.551},
  {0.681, 0.851, 1.050, 1.303, 1.684, 2.021, 2.423, 2.704, 2.971, 3.307, 3.551},
  {0.681, 0.851, 1.050, 1.303, 1.684, 2.021, 2.423, 2.704, 2.971, 3.307, 3.551},
  {0.681, 0.851, 1.050, 1.303, 1.684, 2.021, 2.423, 2.704, 2.971, 3.307, 3.551},
  {0.681, 0.851, 1.050, 1.303, 1.684, 2.021, 2.423, 2.704, 2.971, 3.307, 3.551},
  {0.681, 0.851, 1.050, 1.303, 1.684, 2.021, 2.423, 2.704, 2.971, 3.307, 3.551},
  {0.681, 0.851, 1.050, 1.303, 1.684, 2.021, 2.423, 2.704, 2.971, 3.307, 3.551},
  {0.681, 0.851, 1.050, 1.303, 1.684, 2.021, 2.423, 2.704, 2.971, 3.307, 3.551},
  {0.679, 0.849, 1.047, 1.299, 1.676, 2.009, 2.403, 2.678, 2.937, 3.261, 3.496},
  {0.679, 0.849, 1.047, 1.299, 1.676, 2.009, 2.403, 2.678, 2.937, 3.261, 3.496},
  {0.679, 0.849, 1.047, 1.299, 1.676, 2.009, 2.403, 2.678, 2.937, 3.261, 3.496},
  {0.679, 0.849, 1.047, 1.299, 1.676, 2.009, 2.403, 2.678, 2.937, 3.261, 3.496},
  {0.679, 0.849, 1.047, 1.299, 1.676, 2.009, 2.403, 2.678, 2.937, 3.261, 3.496},
  {0.679, 0.849, 1.047, 1.299, 1.676, 2.009, 2.403, 2.678, 2.937, 3.261, 3.496},
  {0.679, 0.849, 1.047, 1.299, 1.676, 2.009, 2.403, 2.678, 2.937, 3.261, 3.496},
  {0.679, 0.849, 1.047, 1.299, 1.676, 2.009, 2.403, 2.678, 2.937, 3.261, 3.496},
  {0.679, 0.849, 1.047, 1.299, 1.676, 2.009, 2.403, 2.678, 2.937, 3.261, 3.496},
  {0.679, 0.849, 1.047, 1.299, 1.676, 2.009, 2.403, 2.678, 2.937, 3.261, 3.496},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460},
  {0.679, 0.848, 1.045, 1.296, 1.671, 2.000, 2.390, 2.660, 2.915, 3.232, 3.460}
};

const double tsig[12] = {
    0.4501, 0.501, 0.601, 0.701, 0.801, 0.901, 0.9501, 0.9801, 0.9901, 0.99501, 0.99801, 0.99901
};

/*------------------------*/
/* Function Declarations  */
/*------------------------*/
double  expPercatValTail_Lower(double,double,double,double,double);
double  lnValatPercTail_Lower(double,double,double,double,double);
double  expPercatValTail_Upper(double,double,double,double,double);
double  expPdfTail_Upper(double,double,double,double,double);
double  lnValatPercTail_Upper(double,double,double,double,double);
double  calcValatPercSorted(arr *, double);
double  calcValatPerc(arr *, double);
arr     calcValsatPercsSorted(arr *, arr *);
arr     calcValsatPercs(arr *, arr *);
double  calcPercatValSorted(arr *, double);
double  calcPercatVal(arr *, double);
arr     calcPercsatValsSorted(arr *, arr *);
arr     calcPercsatVals(arr *, arr *);
arr     calcPercentile(arr *);
double  calcValatPercWeighted(arr *, arr *, double);
double  calcValatPercFromHist(arr *, arr *, double);
arr     conv_cyclic(arr *,arr *);
double  Min(arr *);
double  Max(arr *);
typ_idx MinIdx(arr *);
typ_idx MaxIdx(arr *);
typ_idx ClosestIdx(arr *,double);
double  IdxFromVal(arr *,double);
double  ValFromIdx(arr *,double);
int     intMin(arr *);
int     intMax(arr *);
typ_idx intMaxIdx(arr *);
int     intMode(arr *);
double  Sum(arr *);
double  PiMult(arr *);
double  Zeros(arr *);
arr     rotateAnglesToIdx(arr *,typ_idx);
typ_idx findClosestClockwiseAngle(arr *, typ_idx, double*);
void    find2AnglesWithAllPoints(arr *,typ_idx*, typ_idx*);
double  doyTrend(arr *,arr *);
double  doyTrendR(arr *,arr *);
double  doyLength(arr *);
double  doyMean(arr *);
double  cyclicMean(arr *,arr *,double);
double  cyclicStdDev(arr *,arr *,double);
double  my_Mean(arr *);
double  Median(arr *);
double  wMean(arr *, arr *);
double  devMoment(arr *, int);
double  Moment(arr *, int);
double  devXY(arr *, arr *);
double  XY(arr *, arr *);
arr     StdAnom(arr *);
arr     AbsErr(arr *,arr *);
arr     SqErr(arr *,arr *);
double  calcBias(arr *,arr *);
double  calcRelBias(arr *,arr *);
double  calcMAE(arr *,arr *);
double  calcMedAE(arr *,arr *);
double  calcMSD(arr *,arr *);
double  calcMedSD(arr *,arr *);
double  calcSSD(arr *,arr *);
double  WdevMoment(arr *, arr *, int);
double  WMoment(arr *, arr *, int);
double  VarP(arr *);
double  SkewP(arr *);
double  KurtP(arr *);
double  normVarP(arr *);
double  normSkewP(arr *);
double  normKurtP(arr *);
double  stdDevP(arr *);
double  VarS(arr *);
double  SkewS(arr *);
double  KurtS(arr *);
double  normVarS(arr *);
double  normSkewS(arr *);
double  normKurtS(arr *);
double  stdDevS(arr *);
double  WstdDevS(arr *,arr *);
double  WKurt(arr *,arr *);
double  sampleStat(arr *);
double  shapeParam(arr *);
double  scaleParam(arr *);
void    fit_gamma_prms(arr *,double*,double*);
double  Tval(double,int);
Linreg  Regr(arr *, arr *);
void    RegrRef(arr *, arr *,double*, double*, double*, double*);
void    RegrRef_TheilSen(arr *, arr *,double*, double*, double*, double*);
void    RegrRef_TheilSen_CC_slopes(arr *, arr *,arr*,arr*,arr*);
void    RegrRef_TheilSen_CC_skip(arr *, arr *,arr *,arr *,typ_idx,double*, double*, double*, double*);
void    RegrRef_TheilSen_CC(arr *, arr *,arr *,arr *,double*, double*, double*, double*);
double  lagCorr(arr *);
double  lagCorrN(arr *,int);
double  Corr(arr *, arr *);
double  PCorr(arr *, arr *, arr *);
double  SPCorr(arr *, arr *, arr *);
double  orthoRegr(arr *, arr *);
double  Cov(arr *, arr *);
double  Slope(arr *, arr *);
void    WMomentStats(arr *, arr *, double*, double*, double*, double*, double*);

arr    RunningStatistic       (double (*fct)(arr *),arr *,typ_idx);
arr    RunningStatistic_End   (double (*fct)(arr *),arr *,typ_idx);
arr    RunningStatistic_2_End (double (*fct)(arr *,arr *),arr *,arr *,typ_idx);
arr    RunningStatistic_Extrap(double (*fct)(arr *),arr *,typ_idx);
arr    RunningRegr     (arr *,typ_idx);
arr    RunningMean     (arr *,typ_idx);
arr    RunningMedian   (arr *,typ_idx);
arr    RunningMean_End (arr *,typ_idx);
arr    RunningSlope_End(arr *,arr *,typ_idx len);

arr    RunningWeightedPercentile(arr *,arr *,arr *,double);
arr    RunningWeightedPercentileNoMean(arr *,arr *,double);
arr    RunningWeightedMean(arr *,arr *);

/*-----------------------*/
/* Function Definitions  */
/*-----------------------*/
double expPercatValTail_Lower(double x,double P_0,double P_1,double x_0,double x_1){
    /* fprintf(stderr,"(x,P_0,P_1,x_0,x_1)=(%lf,%lf,%lf,%lf,%lf)\n",x,P_0,P_1,x_0,x_1); */
    double m = (P_1-P_0)/(x_1-x_0);
    double a = m/P_0;
    double P = P_0*exp(a*(x-x_0));
    /* fprintf(stderr,"(m,a,P)=(%lf,%lf,%lf)\n",m,a,P); */
    return P;
}

double lnValatPercTail_Lower(double P,double P_0,double P_1,double x_0,double x_1){
    double m = (P_1-P_0)/(x_1-x_0);
    double a = m/P_0;
    double x = x_0+log(P/P_0)/a;
    return x;
}

double expPercatValTail_Upper(double x,double P_last1,double P_last,double x_last1,double x_last){
    double m = (P_last-P_last1)/(x_last-x_last1);
    double a = m/(1.0-P_last);
    double P = 1.0 - (1.0-P_last)*exp(a*(x_last-x));
    return P;
}

double expPdfTail_Upper(double x,double p_last1,double p_last,double x_last1,double x_last){
    /* p_last should be small here since it is the last value of the pdf */
    double m = (p_last-p_last1)/(x_last-x_last1);
    double a = m/p_last;
    double p = p_last*exp(a*(x-x_last));
    return p;
}

double lnValatPercTail_Upper(double P,double P_last1,double P_last,double x_last1,double x_last){
    double m = (P_last-P_last1)/(x_last-x_last1);
    double a = m/(1.0-P_last);
    double x = x_last-log((1.0-P)/(1.0-P_last))/a;
    return x;
}


double calcValatPercSorted(arr *restrict Y, double perc) {
    double val;
    double rxp1;
    double pcl, pch, ipperc;
    double n_percs = (double)Y->tlen+1;
    typ_idx i_last = Y->tlen-1;
    int ih,il;

    switch (Y->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pY = pntr_of(Y);\
        if (Y->tlen == 1) {              \
            val = pY[0];          \
        } else {                        \
            rxp1 = 1.0/((double)n_percs);  \
            pcl = rxp1;                 \
            pch = rxp1*Y->tlen;          \
            if ((perc < pch) && (perc > pcl)) { \
                ipperc = perc*n_percs-1; \
                ih = ceil(ipperc);      \
                il = floor(ipperc);     \
                if (ih == il){ \
                    val = (double)pY[il]; \
                } else { \
                    val = linInterp(ipperc,(double)il,(double)ih,(double)pY[il],(double)pY[ih]); \
                } \
            } else if (perc <= pcl) {          \
                double Y_first = (double)pY[0]; \
                double Y_1     = (double)pY[1]; \
                pch = (double)2.0/n_percs; \
                if (Y_first ==Y_1){ \
                    val = Y_first; \
                } else{ \
                    val = lnValatPercTail_Lower(perc,pcl,pch,Y_first,Y_1); \
                } \
            } else if (perc >= pch) {          \
                double Y_last1 = (double)pY[i_last-1]; \
                double Y_last  = (double)pY[i_last]; \
                pcl = (double)i_last/n_percs; \
                if (Y_last1 == Y_last){ \
                    val = Y_last; \
                } else{ \
                    val = lnValatPercTail_Upper(perc,pcl,pch,Y_last1,Y_last); \
                } \
            } \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"calcValatPercSorted: undefined type %d!\n",Y->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return val;
}

double calcValatPerc(arr *restrict X, double perc) {
    arr Y = qsortArray(X);
    double val = calcValatPercSorted(&Y, perc);
    freeAr(&Y);
    return val;
}

arr calcValsatPercsSorted(arr *restrict Y, arr *restrict percs) {
    arr val = Array(1,Y->typ,percs->tlen);
    typ_idx ip;

    switch (Y->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        for(ip=0;ip<percs->tlen;++ip){   \
            swassign(&val,ip) = calcValatPercSorted(Y, iDBL(percs,ip));          \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"calcValsatPercsSorted: undefined type %d!\n",Y->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return val;
}

arr calcValsatPercs(arr *restrict X, arr *restrict percs) {
    arr Y = qsortArray(X);
    arr val = calcValsatPercsSorted(&Y, percs);
    freeAr(&Y);
    return val;
}


double calcPercatValSorted(arr *restrict Y, double val) {
    double perc;
    typ_idx i, ilo, ihi;
    typ_idx i_last = Y->tlen-1;
    double n_percs = (double)Y->tlen+1;
    double ival, pcl, pch;
    
    /* printArrayFmtAllWHdr(stderr,Y,"%7.3f","calcPercatValSorted: val=%g, Y - ",val); */

    switch (Y->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pY = pntr_of(Y);\
        { \
            double Y_first = (double)pY[0]; \
            double Y_1     = (double)pY[1]; \
            double Y_last  = (double)pY[i_last]; \
            double Y_last1 = (double)pY[i_last-1]; \
            if (val <= Y_first) { \
                pcl = (double)1.0/n_percs; \
                pch = (double)2.0/n_percs; \
                if (Y_first ==Y_1){ \
                    perc = 0.5*pcl; \
                } else{ \
                    perc = expPercatValTail_Lower(val,pcl,pch,Y_first,Y_1); \
                } \
            } else if (val > Y_last) { \
                pcl = (double)i_last/n_percs; \
                pch = (double)Y->tlen/n_percs; \
                if (Y_last1 == Y_last){ \
                    perc = 0.5+0.5*pch; \
                } else{ \
                    perc = expPercatValTail_Upper(val,pcl,pch,Y_last1,Y_last); \
                } \
            } else {                            \
                ival = IdxFromVal(Y,val); /* will the "+ 1" cause problems? */ \
                ilo  = (typ_idx)floor(ival); \
                ihi  = (typ_idx)ceil(ival); \
                pcl  = (double)(ilo+1)/n_percs; \
                pch  = (double)(ihi+1)/n_percs; \
                /* fprintf(stderr,"ival=%g,ilo=%lld,ihi=%lld,pcl=%g,pch=%g\n",ival,ilo,ihi,pcl,pch); */ \
                if (pY[ilo] == pY[ihi]) { \
                    perc = 0.5*(pcl+pch); \
                    /* fprintf(stderr,"1 perc=%g\n",perc); */ \
                } else {    \
                    perc = linInterp(val,(double)pY[ilo],(double)pY[ihi],pcl,pch);  \
                    /* fprintf(stderr,"2 perc=%g\n",perc); */ \
                }                   \
            } \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"calcPercatValSorted: undefined type %d!\n",Y->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return perc;
}

double calcPercatVal(arr *restrict X, double val) {
    arr Y = qsortArray(X);
    double perc = calcPercatValSorted(&Y, val);
    freeAr(&Y);
    return perc;
}

arr calcPercsatValsSorted(arr *restrict Y, arr *restrict vals) {
    arr percs = Array(1,DOUBLE,vals->tlen);
    typ_idx iv,i = 1;
    typ_idx i_last = Y->tlen-1;
    double n_percs = (double)Y->tlen+1;
    double val, pcl, pch;
    double Y_first;
    double Y_1    ;
    double Y_last ;
    double Y_last1;

    switch (Y->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pY = pntr_of(Y);\
        Y_first = (double)pY[0]; \
        Y_1     = (double)pY[1]; \
        Y_last  = (double)pY[i_last]; \
        Y_last1 = (double)pY[i_last-1]; \
        for (iv=0;iv<vals->tlen;++iv){ \
            val = swassign(vals,iv); \
            if (val <= Y_first) { \
                pcl = (double)1.0/n_percs; \
                pch = (double)2.0/n_percs; \
                if (Y_first ==Y_1){ \
                    iDBL(&percs,iv) = 0.5*pcl; \
                } else{ \
                    iDBL(&percs,iv) = expPercatValTail_Lower(val,pcl,pch,Y_first,Y_1); \
                } \
            } else if (val > Y_last) { \
                pcl = (double)i_last/n_percs; \
                pch = (double)Y->tlen/n_percs; \
                if (Y_last1 == Y_last){ \
                    iDBL(&percs,iv) = 0.5+0.5*pch; \
                } else{ \
                    iDBL(&percs,iv) = expPercatValTail_Upper(val,pcl,pch,Y_last1,Y_last); \
                } \
            } else {                            \
                for(;i<Y->tlen;++i){          \
                    if ( (val <= pY[i]) && (val > pY[i-1]) ){ \
                        pcl = (double)i/n_percs; \
                        pch = (double)(i+1)/n_percs; \
                        if (pY[i-1] == pY[i]) { \
                            iDBL(&percs,iv) = 0.5*(pcl+pch); \
                        } else {    \
                            iDBL(&percs,iv) = linInterp(val,(double)pY[i-1],(double)pY[i],pcl,pch);  \
                        }                   \
                        break;              \
                    }                       \
                }                           \
            } \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"calcPercsatValsSorted: undefined type %d!\n",Y->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return percs;
}

arr calcPercsatVals(arr *restrict X, arr *restrict vals) {
    arr Y = qsortArray(X);
    arr percs = calcPercsatValsSorted(&Y, vals);
    freeAr(&Y);
    return percs;
}

arr calcPercentile(arr *restrict X) {
    typ_idx i;
    arr XIdx     = qsortArrayIdx(X);
    typ_idx ntot = countNonMiss(X)+1;
    arr P        = ArrayFromList(X->n,DOUBLE,X->len);
    copyMiss(&P,X);
    for (i=0;i<X->tlen;++i){
        if (isMiss(&XIdx,i)) { setToMiss(&P,i); } else {
            iDBL(&P,iIDX(&XIdx,i)) = (double)i/ntot;
        }
    }
    freeAr(&XIdx);
    return P;
}

double calcValatPercWeighted(arr *restrict X, arr *restrict W, double perc) {

    if (X->tlen == 1) {
        return iDBL(X,(typ_idx)0);
    } else {
        double val    = *(double *)getMiss(X);
        double Wsum   = Sum(W);
        double Wsump1 = Wsum + Wsum/(double)W->tlen; /* This is the analog to Y->tlen + 1 in calcValatPercWeighted */
    
        arr idx = Array((typ_idx)1,TYPIDX,X->tlen);
        qsortTable2(X,&idx);

        arr Xs    = Array((typ_idx)1,DOUBLE,X->tlen);
        arr Ws    = Array((typ_idx)1,DOUBLE,W->tlen);
        arr Percs = Array((typ_idx)1,DOUBLE,W->tlen);
        /*
         *  Should pre-sort these arrays, then if there are multiple values of Xs that are the same
         *  , then the corresponding weights should be averaged for that value.
         */
        double Wstot = 0;
        double pcl, pch;
        typ_idx i;
        for(i=0;i<X->tlen;++i){
            iDBL(&Xs,i)    = iDBL(X,iIDX(&idx,i));
            iDBL(&Ws,i)    = iDBL(W,iIDX(&idx,i));
            Wstot        += iDBL(&Ws,i);
            iDBL(&Percs,i) = Wstot/Wsump1;
            if (iDBL(&Percs,i) >= perc){
                if (i == 0) { /* percentile of all values greater than desired percentile */
                    iDBL(&Xs,1)    = iDBL(X,iIDX(&idx,1));
                    iDBL(&Ws,1)    = iDBL(W,iIDX(&idx,1));
                    Wstot        += iDBL(&Ws,1);
                    iDBL(&Percs,1) = Wstot/Wsump1;
                    if (iDBL(&Xs,0) == iDBL(&Xs,1)){
                        val = iDBL(&Xs,0);
                    } else{
                        val = lnValatPercTail_Lower(perc,iDBL(&Percs,0),iDBL(&Percs,1),iDBL(&Xs,0),iDBL(&Xs,1));
                    }
                } else {
                    pcl = iDBL(&Percs,i-1);
                    pch = iDBL(&Percs,i);
                    if (pcl == pch) {
                        val = iDBL(&Xs,i);  /* This may never occur */
                    } else {
                        val = linInterp(perc,pcl,pch,iDBL(&Xs,i-1),iDBL(&Xs,i));
                    }
                }
                break;
            }
        }
    
        if (i == X->tlen){ /* percentile never reached */
            if (iDBL(&Xs,X->tlen-2) == iDBL(&Xs,X->tlen-1)){
                val = iDBL(&Xs,X->tlen-1);
            } else{
                val = lnValatPercTail_Upper(perc,iDBL(&Percs,X->tlen-2),iDBL(&Percs,X->tlen-1),iDBL(&Xs,X->tlen-2),iDBL(&Xs,X->tlen-1));
            }
        }

        freeAr(&idx);
        freeAr(&Xs);
        freeAr(&Ws);
        freeAr(&Percs);
        return val;
    }
}

double calcValatPercFromHist(
      arr *restrict Y       /* Counts in each bin */
    , arr *restrict X       /* Value of each bin  */
    , double perc /* Desired perentile  */
    ) {
    return calcValatPercWeighted(X, Y, perc);
}

arr conv_cyclic(arr *d,arr *e){ 
    int i,j,k;
    int st = floor(e->tlen/2);
    double csum = 0;
    arr d_cyc = cyclicArray(d,st);
    arr m = Array((typ_idx)1,d->typ,d->tlen);

    switch (m.typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pd_cyc = pntr_of(&d_cyc);\
        swcast *pe     = pntr_of(e);\
        swcast *p      = pntr_of(&m);\
        for(i=0;i<m.tlen;++i){                      \
            csum = 0; k = 0; j = i+2*st;                \
            while((j>=0) && (k<e->tlen)){                \
                if ( isMiss(&d_cyc,j) || isMiss(e,k) ) {   \
                    csum = *(swcast *)getMiss(&m);         \
                    break;                  \
                }                           \
                csum += pd_cyc[j]*pe[k];    \
                --j; ++k;                   \
            }                               \
            p[i] = csum;                    \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"conv_cyclic: undefined type!\n");
            exit(0);
            break;
    }
    #undef SWITCHCAST

    freeAr(&d_cyc);
    return m;
}

double Min(arr *restrict P){ 
/*  arr P = castAr(Pin,DOUBLE,0); */
/*  printArrayFmt2AllWHdr(stderr, P, "%g", "P - "); */

    double *p  = address_of_i(P,0);
    double min = *p++;
    for (typ_idx i=1; i < P->tlen; ++i){
        if ( *p < min ) { min = *p++; } else { p++; }
    }

/*  freeAr(&P); */
    return min;
}

double Max(arr *restrict P){ 
/*  arr P = castAr(Pin,DOUBLE,0); */

    double *p  = address_of_i(P,0);
    double max = *p++;
    for (typ_idx i=1; i < P->tlen; ++i){
        if ( *p > max ) { max = *p++; } else { p++; }
    }

/*  freeAr(&P); */
    return max;
}

typ_idx FirstTrue(arr *restrict P){ 
    if (P->n != 1) { fprintf(stderr,"FirstTrue: Must be 1 dimension\n"); exit(0); }
    arr Pi = castAr(P,INT,0);

    typ_idx retidx = -1;
    typ_idx b;

    for(b=0;b<Pi.tlen;++b){
        if (!isMiss(&Pi,b)){
            if (iINTG(&Pi,b)){
                retidx = b;
                break;
            }
        }
    }

    freeAr(&Pi);
    return retidx;
}

typ_idx LastTrue(arr *restrict P){ 
    if (P->n != 1) { fprintf(stderr,"LastTrue: Must be 1 dimension\n"); exit(0); }
    arr Pi = castAr(P,INT,0);

    typ_idx retidx = -1;
    typ_idx b;

    for(b=Pi.tlen-1;b>-1;--b){
        if (!isMiss(&Pi,b)){
            if (iINTG(&Pi,b)){
                retidx = b;
                break;
            }
        }
    }

    freeAr(&Pi);
    return retidx;
}

typ_idx MinIdx(arr *restrict P){ 
    /* if (P->n != 1) { fprintf(stderr,"MinIdx: Must be 1 dimension\n"); exit(0); } */
    arr Pd = castAr(P,DOUBLE,0);

    double min;
    int minset;
    typ_idx minidx = -1;
    typ_idx b;

    min = iDBL(&Pd,(typ_idx)0);
    minset = 0;
    for(b=0;b<Pd.tlen;++b){
        if (!isMiss(&Pd,b)){
            if (!minset){
                min = iDBL(&Pd,b);
                minidx = b;
                minset = 1;
            } else if ( iDBL(&Pd,b) < min ) {
                min = iDBL(&Pd,b);
                minidx = b;
            }
        }
    }

    freeAr(&Pd);
    return minidx;
}

typ_idx MaxIdx(arr *restrict P){ 
    /* if (P->n != 1) { fprintf(stderr,"MaxIdx: Must be 1 dimension\n"); exit(0); } */
    arr Pd = castAr(P,DOUBLE,0);

    double max;
    int maxset;
    typ_idx maxidx = -1;
    typ_idx b;

    max = iDBL(&Pd,(typ_idx)0);
    maxset = 0;
    for(b=0;b<Pd.tlen;++b){
        if (!isMiss(&Pd,b)){
            if (!maxset){
                max = iDBL(&Pd,b);
                maxidx = b;
                maxset = 1;
            } else if ( iDBL(&Pd,b) > max ) {
                max = iDBL(&Pd,b);
                maxidx = b;
            }
        }
    }

    freeAr(&Pd);
    return maxidx;
}

typ_idx ClosestIdx(arr *restrict P,double val){ 
    /* if (P->n != 1) { fprintf(stderr,"ClosestIdx: Must be 1 dimension\n"); exit(0); } */
    arr Pd = castAr(P,DOUBLE,0);
    double Pmin = Min(&Pd);
    double Pmax = Max(&Pd);
    if ( (Pmin == *(double *)getMiss(&Pd)) || (Pmax == *(double *)getMiss(&Pd)) || ((Pmax - Pmin) <= 0) || (val > Pmax) || (val < Pmin) ){
        freeAr(&Pd);
        return -1;
    }

    double min,d2val;
    int minset;
    typ_idx minidx;
    typ_idx b;

    min = fabs(iDBL(&Pd,(typ_idx)0)-val);
    minidx = -1;
    minset = 0;
    for(b=0;b<Pd.tlen;++b){
            d2val = fabs(iDBL(&Pd,b)-val);
            if (!minset){
                min = d2val;
                minidx = b;
                minset = 1;
            } else if ( d2val < min ) {
                min = d2val;
                minidx = b;
            }
    }

    freeAr(&Pd);
    return minidx;
}


double IdxFromVal(arr *restrict P,double val){ /* Attempt at faster search algorithm */
    arr Pd = castAr(P,DOUBLE,0);
    
    typ_idx idxlo = 0;
    typ_idx idxhi = Pd.tlen-1;
    
    double ridx;
    if (val < iDBL(&Pd,idxlo)){
        idxhi = idxlo+1;
        ridx  = linInterp(val,iDBL(&Pd,idxlo),iDBL(&Pd,idxhi),(double)idxlo,(double)idxhi);
        freeAr(&Pd);
        return ridx;
    }
    if (val > iDBL(&Pd,idxhi)){
        idxlo = idxhi-1;
        ridx  = linInterp(val,iDBL(&Pd,idxlo),iDBL(&Pd,idxhi),(double)idxlo,(double)idxhi);
        freeAr(&Pd);
        return ridx;
    }
    
    typ_idx tmpidx;
    while ((idxhi-idxlo) > 3){
        tmpidx = (idxlo+idxhi)/2;
        if (iDBL(&Pd,tmpidx) > val){
            idxhi = tmpidx;
        } else {
            idxlo = tmpidx;
        }
    }

    ++idxlo;
    while (val > iDBL(&Pd,idxlo)){ ++idxlo; }
    idxhi = idxlo;
    --idxlo;
    ridx  = linInterp(val,iDBL(&Pd,idxlo),iDBL(&Pd,idxhi),(double)idxlo,(double)idxhi);
/*  fprintf(stderr,"IdxFromVal: idxlo=%lld, idxhi=%lld, vallo=%g, valhi=%g, ridx=%g, val=%g\n"
        ,idxlo,idxhi,iDBL(&Pd,idxlo),iDBL(&Pd,idxhi),ridx,val);   */
    
    freeAr(&Pd);
    return ridx;
}

double ValFromIdx(arr *restrict P,double idx){ 
    arr Pd = castAr(P,DOUBLE,0);
    
    double rval,idxlo,idxhi;
    if (idx < 0.0){
        idxlo = 0;
        idxhi = 1;
        /* rval = *(double *)getMiss(&Pd); */
        /* freeAr(&Pd);        */
        /* return rval;       */
    } else if (idx > (double)(Pd.tlen-1)){
        idxlo = (double)(Pd.tlen-2);
        idxhi = (double)(Pd.tlen-1);
        /* rval = *(double *)getMiss(&Pd); */
        /* freeAr(&Pd);        */
        /* return rval;       */
    } else {
        idxlo = floor(idx);
        idxhi = ceil(idx);
    }

    if (idxlo == idxhi){
        rval = iDBL(&Pd,(typ_idx)idx);
    } else {
        rval = linInterp(idx,idxlo,idxhi,iDBL(&Pd,(typ_idx)idxlo),iDBL(&Pd,(typ_idx)idxhi));
    }
    freeAr(&Pd);
    return rval;
}

int intMin(arr *restrict Pin){ 
    arr P = castAr(Pin,INT,0);
    
    int min;
    typ_idx b = 0;
    
    min = iINTG(&P,b);
    while ( b < P.tlen){
        if ( iINTG(&P,b) < min ) { min = iINTG(&P,b); }
        b = b + 1;  
    }
    
    freeAr(&P);
    return min;
}

int intMax(arr *restrict Pin){ 
    arr P = castAr(Pin,INT,0);

    int max;
    typ_idx b = 0;

    max = iINTG(&P,b);
    while ( b < P.tlen){
        if ( iINTG(&P,b) > max ) { max = iINTG(&P,b); }
        b = b + 1;  
    }

    freeAr(&P);
    return max;
}

typ_idx intMaxIdx(arr *restrict Pin){ 
    if (Pin->n != 1) { fprintf(stderr,"intMaxIdx: Must be 1 dimension\n"); exit(0); }
    arr P = castAr(Pin,INT,0);

    int max;
    int maxset;
    typ_idx maxidx;
    typ_idx b;

    max = iINTG(&P,(typ_idx)0);
    maxidx = 0;
    maxset = 0;
    for(b=0;b<P.tlen;++b){
        if (!maxset){
            max = iINTG(&P,b);
            maxidx = b;
            maxset = 1;
        } else if ( iINTG(&P,b) > max ) {
            max = iINTG(&P,b);
            maxidx = b;
        }
    }

    freeAr(&P);
    return maxidx;
}

int intMode(arr *restrict Pin){ 
    if (Pin->n != 1) { fprintf(stderr,"intMode: Must be 1 dimension\n"); exit(0); }
    arr P = castAr(Pin,INT,0);

    typ_idx b;
    int min = intMin(&P);
    int max = intMax(&P);
    if ((min == *(int *)getMiss(&P)) || (max == *(int *)getMiss(&P))){
        int retmode = *(int *)getMiss(&P);
        freeAr(&P);
        return retmode;
    }

    arr X = Array((typ_idx)1,INT,(typ_idx)max-min+1);

    int *pX = pntr_of(&X);
    for(b=0;b<P.tlen;++b){
        if (!isMiss(&P,b)){
            pX[iINTG(&P,b)-min]++;
        }
    }

    int maxidx = intMaxIdx(&X);

    freeAr(&P);
    freeAr(&X);
    return maxidx+min;
}

arr intModes(arr *restrict Pin){ 
    arr P = castAr(Pin,INT,0);

    typ_idx b;
    int min = intMin(&P);
    int max = intMax(&P);
    if ((min == *(int *)getMiss(&P)) || (max == *(int *)getMiss(&P))){
        freeAr(&P);
        return NullArray();
    }

    arr X = Array((typ_idx)1,INT,(typ_idx)(max-min+1));
    for(b=0;b<P.tlen;++b){
        if (!isMiss(&P,b)){
            (iINTG(&X,iINTG(&P,b)-min))++;
        }
    }

    arr XIdx = qsortArrayIdxRev(&X);
    for(b=0;b<XIdx.tlen;++b){
        if (!isMiss(&XIdx,b)){
            iIDX(&XIdx,b) += min;
        }
    }
    /* printArrayFmtAllWHdr(stderr,XIdx,"%d","intModes: XIdx  - "); */

    freeAr(&P);
    freeAr(&X);
    return XIdx;
}

arr intModes_Freq(arr *restrict Pin,arr *Freq){ 
    arr P = castAr(Pin,INT,0);

    typ_idx b;
    int min = intMin(&P);
    int max = intMax(&P);
    if ((min == *(int *)getMiss(&P)) || (max == *(int *)getMiss(&P))){
        freeAr(&P);
        return NullArray();
    }

    arr X = Array((typ_idx)1,INT,(typ_idx)(max-min+1));
    for(b=0;b<P.tlen;++b){
        if (!isMiss(&P,b)){
            (iINTG(&X,iINTG(&P,b)-min))++;
        }
    }

    arr XIdx = qsortArrayIdxRev(&X);
    *Freq = sortOnIdx(&X,&XIdx);
    for(b=0;b<XIdx.tlen;++b){
        if (!isMiss(&XIdx,b)){
            iIDX(&XIdx,b) += min;
        }
    }
    /* printArrayFmtAllWHdr(stderr,XIdx,"%d","intModes: XIdx  - "); */

    freeAr(&P);
    freeAr(&X);
    return XIdx;
}

double Sum(arr *restrict Pin){ 
    arr P = castAr(Pin,DOUBLE,0);

    double sum = 0;
    double *p = address_of_i(&P,0);
    for (typ_idx i=0; i < P.tlen; ++i){
        sum += *p++;
    }

    freeAr(&P);
    return sum;
}

double PiMult(arr *restrict Pin){ 
    arr P = castAr(Pin,DOUBLE,0);

    double total = 1;
    double *p = address_of_i(&P,0);
    for (typ_idx i=0; i < P.tlen; ++i){
        total *= *p++;
    }

    freeAr(&P);
    return total;
}

double Zeros(arr *restrict Pin){ 
    arr P = castAr(Pin,DOUBLE,0);

    double zsum = 0;
    typ_idx b = 0;

    while ( b < P.tlen){
        if (iDBL(&P,b) == 0) { ++zsum; }
        b = b + 1;
    }

    zsum = zsum/(double)P.tlen;

    freeAr(&P);
    return zsum;
}

int Logical_All(arr *restrict P){ 
    int *p  = address_of_i(P,0);

    for (typ_idx i=0; i < P->tlen; ++i){
        if (!(*p++)) { return 0; }
    }

	return 1;
}

int Logical_Any(arr *restrict P){ 
    int *p  = address_of_i(P,0);

    for (typ_idx i=0; i < P->tlen; ++i){
        if (*p++) { return 1; }
    }

	return 0;
}


arr rotateAnglesToIdx(arr *restrict Ang,typ_idx curidx){
    typ_idx i;
    double ang = iDBL(Ang,curidx);

    arr AngR = Array((typ_idx)1,DOUBLE,Ang->tlen);

    /* calculate array of angles from current point */
    for(i=0;i<Ang->tlen;++i){
        if (iDBL(Ang,i) >= ang){
            iDBL(&AngR,i) = iDBL(Ang,i) - ang;
        } else {
            iDBL(&AngR,i) = iDBL(Ang,i) + 2*M_PI - ang;
        }
    }

    return AngR;
}

typ_idx findClosestClockwiseAngle(arr *restrict Ang, typ_idx curidx, double *clockAng){
    typ_idx i;
    double ang = iDBL(Ang,curidx);

    arr AngR = Array((typ_idx)1,DOUBLE,Ang->tlen);

    double maxAngR  = -1.0;
    typ_idx maxAngRidx = -1;
    /* calculate array of angles from current point */
    for(i=0;i<Ang->tlen;++i){
        if (iDBL(Ang,i) >= ang){
            iDBL(&AngR,i) = iDBL(Ang,i) - ang;
        } else {
            iDBL(&AngR,i) = iDBL(Ang,i) + 2*M_PI - ang;
        }
        if (i != curidx){
            if (iDBL(&AngR,i) > maxAngR){
                maxAngR = iDBL(&AngR,i);
                maxAngRidx = i;
            }
        }
    }

    *clockAng = 2*M_PI - maxAngR;

    freeAr(&AngR);
    return maxAngRidx;
}

void find2AnglesWithAllPoints(arr *restrict Ang,typ_idx *idx1, typ_idx *idx2){
    typ_idx i;
    arr closestidxs = Array((typ_idx)1,INT,Ang->tlen);;
    arr closestangs = Array((typ_idx)1,DOUBLE,Ang->tlen);;

    for (i=0;i<Ang->tlen;++i){
        iINTG(&closestidxs,i) = findClosestClockwiseAngle(Ang, i, address_of_i(&closestangs,i));
    }

    *idx1 = MaxIdx(&closestangs);
    *idx2 = iINTG(&closestidxs,*idx1);

    freeAr(&closestidxs);
    freeAr(&closestangs);

    return;
}

double doyTrend(arr *restrict P,arr *restrict T){ 
    if (P->tlen != T->tlen) { fprintf(stderr,"doyTrend: Input arrays must have same total length\n"); exit(0); }
    double trend;

    arr V1 = fct1ar1s(wrap_Div,P,365.0);
    arr Vf = fct1ar(wrap_floor,&V1);
    arr V2 = fct2ar(wrap_sub,&V1,&Vf);
    arr V  = fct1ar1s(wrap_mult,&V2,2*M_PI);

    typ_idx idx1, idx2;
    find2AnglesWithAllPoints(&V,&idx1,&idx2);
    arr VR = rotateAnglesToIdx(&V,idx1);

    double varT  = VarS(T);
    double mVR   = Cov(T, &VR)/varT;
    trend = (365.0/(2*M_PI))*mVR;

    freeAr(&V1);
    freeAr(&V2);
    freeAr(&Vf);
    freeAr(&V);
    freeAr(&VR);

    return trend;
}

double doyTrendR(arr *restrict P,arr *restrict T){ 
    if (P->tlen != T->tlen) { fprintf(stderr,"doyTrendR: Input arrays must have same total length\n"); exit(0); }
    double R;

    arr V1 = fct1ar1s(wrap_Div,P,365.0);
    arr Vf = fct1ar(wrap_floor,&V1);
    arr V2 = fct2ar(wrap_sub,&V1,&Vf);
    arr V  = fct1ar1s(wrap_mult,&V2,2*M_PI);

    typ_idx idx1, idx2;
    find2AnglesWithAllPoints(&V,&idx1,&idx2);
    arr VR = rotateAnglesToIdx(&V,idx1);

    R = Regr(T, &VR).r;

    freeAr(&V1);
    freeAr(&V2);
    freeAr(&Vf);
    freeAr(&V);
    freeAr(&VR);

    return R;
}

double doyLength(arr *restrict P){ 
/*  
 *  Need to separate P into winter-summer vector and sprint-fall vector
 *  cos(day 0 or day 365) = 1
 *  cos(day 182.5)        = -1
 *  sin(day 91.25)        = 1
 *  sin(day 273.75)       = -1
 */
    double len;

    arr V1 = fct1ar1s(wrap_Div,P,365.0);
    arr Vf = fct1ar(wrap_floor,&V1);
    arr V2 = fct2ar(wrap_sub,&V1,&Vf);
    arr V  = fct1ar1s(wrap_mult,&V2,2*M_PI);
    arr X  = fct1ar(wrap_cos,&V);
    arr Y  = fct1ar(wrap_sin,&V);

    double Xmean = my_Mean(&X);
    double Ymean = my_Mean(&Y);
    len = sqrt(Xmean*Xmean + Ymean*Ymean);

    freeAr(&V1);
    freeAr(&V2);
    freeAr(&Vf);
    freeAr(&V);
    freeAr(&X);
    freeAr(&Y);

    return len;
}

double doyMean(arr *restrict P){ 
/*  
 *  Need to separate P into winter-summer vector and sprint-fall vector
 *  cos(day 0 or day 365) = 1
 *  cos(day 182.5)        = -1
 *  sin(day 91.25)        = 1
 *  sin(day 273.75)       = -1
 */
    double mean;

    arr V1 = fct1ar1s(wrap_Div,P,365.0);
    arr Vf = fct1ar(wrap_floor,&V1);
    arr V2 = fct2ar(wrap_sub,&V1,&Vf);
    arr V  = fct1ar1s(wrap_mult,&V2,2*M_PI);
    arr X  = fct1ar(wrap_cos,&V);
    arr Y  = fct1ar(wrap_sin,&V);

    double Xmean = my_Mean(&X);
    double Ymean = my_Mean(&Y);
    if ((Xmean == 0) && (Ymean == 0)){
        mean = *(double *)getMiss(P);
    } else {
        mean = atan2(Ymean,Xmean)*365.0/(2*M_PI);
        if (mean < 0){
            mean = 365.0+mean;
        }
    }       

    freeAr(&V1);
    freeAr(&V2);
    freeAr(&Vf);
    freeAr(&V);
    freeAr(&X);
    freeAr(&Y);

    return mean;
}

double cyclicMean(arr *restrict T,arr *restrict data,double Pd){ 
/*  
 *  Need to separate T into winter-summer vector and sprint-fall vector
 *  cos(     Pd) =  1
 *  cos( 0.5*Pd) = -1
 *  sin(0.25*Pd) =  1
 *  sin(0.75*Pd) = -1
 */
    arr V1 = fct1ar1s(wrap_Div,T,Pd);
    arr Vf = fct1ar(wrap_floor,&V1);
    arr V2 = fct2ar(wrap_sub,&V1,&Vf);
    arr V  = fct1ar1s(wrap_mult,&V2,2*M_PI);
    arr X  = fct1ar(wrap_cos,&V);
    arr Y  = fct1ar(wrap_sin,&V);

    double datamin = Min(data);
    
    arr wgts = fct1ar1s(wrap_sub,data,datamin);

    double mean;
    double Xmean = wMean(&X,&wgts);
    double Ymean = wMean(&Y,&wgts);
    if ((Xmean == 0) && (Ymean == 0)){
        mean = *(double *)getMiss(T);
    } else {
        mean = atan2(Ymean,Xmean)*Pd/(2*M_PI);
        if (mean < 0){
            mean = Pd+mean;
        }
    }       

    freeAr(&V1);
    freeAr(&V2);
    freeAr(&Vf);
    freeAr(&V);
    freeAr(&X);
    freeAr(&Y);
    freeAr(&wgts);

    return mean;
}

double cyclicStdDev(arr *restrict T,arr *restrict data,double Pd){ 
/*  
 *  Need to separate T into winter-summer vector and sprint-fall vector
 *  cos(     Pd) =  1
 *  cos( 0.5*Pd) = -1
 *  sin(0.25*Pd) =  1
 *  sin(0.75*Pd) = -1
 */
    arr V1 = fct1ar1s(wrap_Div,T,Pd);
    arr Vf = fct1ar(wrap_floor,&V1);
    arr V2 = fct2ar(wrap_sub,&V1,&Vf);
    arr V  = fct1ar1s(wrap_mult,&V2,2*M_PI);
    arr X  = fct1ar(wrap_cos,&V);
    arr Y  = fct1ar(wrap_sin,&V);

    double datamin = Min(data);
    arr wgts = fct1ar1s(wrap_sub,data,datamin);

    double std_dev;
    double Xstd = WstdDevS(&X,&wgts);
    double Ystd = WstdDevS(&Y,&wgts);
    if ((Xstd == 0.0) && (Ystd == 0.0)){
        std_dev = *(double *)getMiss(T);
    } else {
      std_dev = dist(Xstd,Ystd);
    /*    std_dev = sqrt((Xstd*Xstd)+(Ystd*Ystd));  */
    }
    /*
    if (std_dev == 1.0){
        fprintf(stderr,"cyclicStdDev: std_dev=%g,Xstd=%g,Ystd=%g,datamin=%g,Pd=%g\n",std_dev,Xstd,Ystd,datamin,Pd);
        printArrayWHdr(stderr,T,"T\n");
        printArrayWHdr(stderr,V1,"V1\n");
        printArrayWHdr(stderr,Vf,"Vf\n");
        printArrayWHdr(stderr,V2,"V2\n");
        printArrayWHdr(stderr,V,"V\n");
        printArrayWHdr(stderr,X,"X\n");
        printArrayWHdr(stderr,Y,"Y\n");
        printArrayWHdr(stderr,data,"data\n");
        printArrayWHdr(stderr,wgts,"wgts\n");
        exit(0);
    } else {
        fprintf(stderr,"cyclicStdDev: std_dev=%g,Xstd=%g,Ystd=%g,datamin=%g,Pd=%g\n",std_dev,Xstd,Ystd,datamin,Pd);
    }
    */

    freeAr(&V1);
    freeAr(&V2);
    freeAr(&Vf);
    freeAr(&V);
    freeAr(&X);
    freeAr(&Y);
    freeAr(&wgts);

    return std_dev;
}

double my_Mean(arr *restrict P){ 
    double sum_P = Sum(P);
    return sum_P/(double)P->tlen;
}

double Median(arr *restrict P){ 
    double median = calcValatPerc(P, 0.5);
    return median;
}

double wMean(arr *restrict P, arr *restrict W){ 
    if (P->tlen != W->tlen) { fprintf(stderr,"wMean: Input arrays must have same total length\n"); exit(0); }

    arr PmW = fct2ar(wrap_mult,P,W);
    double SumPmW = Sum(&PmW);
    double SumW   = Sum(W);
    double wmean;
    if (SumW > 0){
        wmean = SumPmW/SumW;
    } else {
        wmean = *(double *)getMiss(P);
    }
    freeAr(&PmW);
    return wmean;
}

double devMoment(arr *restrict P, int moment){ 
    arr X = fct1ar1s(wrap_sub,P,my_Mean(P));
    arr Y = fct1ar1s(wrap_pow,&X,(double)moment);
    double devsum = Sum(&Y);
    freeAr(&X); freeAr(&Y);
    return devsum;
}

double Moment(arr *restrict P, int moment){ 
    arr Y = fct1ar1s(wrap_pow,P,(double)moment);
    double devsum = Sum(&Y);
    freeAr(&Y);
    return devsum;
}

double devXY(arr *restrict PX, arr *restrict PY){ 
    if (PX->tlen != PY->tlen) { fprintf(stderr,"devXY: Input arrays must have same total length\n"); exit(0); }
    arr X  = fct1ar1s(wrap_sub,PX,my_Mean(PX));
    arr Y  = fct1ar1s(wrap_sub,PY,my_Mean(PY));
    arr XY = fct2ar(wrap_mult,&X,&Y);
    double devsum = Sum(&XY);
    freeAr(&X); freeAr(&Y); freeAr(&XY);
    return devsum;
}

double XY(arr *restrict PX, arr *restrict PY){ 
    if (PX->tlen != PY->tlen) { fprintf(stderr,"XY: Input arrays must have same total length\n"); exit(0); }
    arr XY = fct2ar(wrap_mult,PX,PY);
    double devsum = Sum(&XY);
    freeAr(&XY);
    return devsum;
}

arr StdAnom(arr *restrict Pin){ 
    arr P = castAr(Pin,DOUBLE,0);
    arr Pcut = removeMissing(&P);
    
    double Pmean = my_Mean(&Pcut);
    if (Pmean == *(double *)getMiss(&P)){
        fillArWithMiss(&P);
        freeAr(&Pcut);
        return P;
    }

    double Pstd = stdDevS(&Pcut);
    if ((Pstd == *(double *)getMiss(&P)) || (Pstd <= 0)){
        fillArWithMiss(&P);
        freeAr(&Pcut);
        return P;
    }

    arr Res = ArrayFromList(P.n,DOUBLE,P.len);
    copyMiss(&Res,&P);
    typ_idx i;
    for (i=0;i<P.tlen;++i){
        if (isMiss(&P,i)) { setToMiss(&Res,i); } else {
            iDBL(&Res,i) = (iDBL(&P,i)-Pmean)/Pstd;
        }
    }

    freeAr(&P);
    freeAr(&Pcut);
    return Res;
}

arr AbsErr(arr *restrict Xin,arr *restrict Yin){ 
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"AbsErr: Input arrays must have same total length\n"); exit(0); }
    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);
    
    arr AE = ArrayFromList(X.n,DOUBLE,X.len);
    copyMiss(&AE,&X);
    typ_idx i;
    for (i=0;i<X.tlen;++i){
        if (isMiss(&X,i) || isMiss(&Y,i)) { setToMiss(&AE,i); } else {
            iDBL(&AE,i) = fabs(iDBL(&X,i)-iDBL(&Y,i));
        }
    }
    
    freeAr(&X);
    freeAr(&Y);
    return AE;
}

arr SqErr(arr *restrict Xin,arr *restrict Yin){ 
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"SqErr: Input arrays must have same total length\n"); exit(0); }
    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);
    
    arr SE = ArrayFromList(X.n,DOUBLE,X.len);
    copyMiss(&SE,&X);
    typ_idx i;
    for (i=0;i<X.tlen;++i){
        if (isMiss(&X,i) || isMiss(&Y,i)) { setToMiss(&SE,i); } else {
            iDBL(&SE,i) = pow(iDBL(&X,i)-iDBL(&Y,i),2);
        }
    }

    freeAr(&X);
    freeAr(&Y);
    return SE;
}

double calcBias(arr *restrict Xin,arr *restrict Yin){
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"calcBias: Input arrays must have same total length\n"); exit(0); }
    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);

    typ_idx i;
    double Xsum = 0.0;
    double Ysum  = 0.0;
    for(i=0;i<Y.tlen;++i){
        Xsum += iDBL(&X,i);
        Ysum += iDBL(&Y,i);
    }
    double bias = (Xsum - Ysum)/(double)Y.tlen;
    
    freeAr(&X);
    freeAr(&Y);
    return bias;
}

double calcRelBias(arr *restrict Xin,arr *restrict Yin){
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"calcRelBias: Input arrays must have same total length\n"); exit(0); }
    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);

    typ_idx i;
    double Xsum = 0.0;
    double Ysum = 0.0;
    for(i=0;i<Y.tlen;++i){
        Xsum += iDBL(&X,i);
        Ysum += iDBL(&Y,i);
    }
    double bias = (Xsum - Ysum)/fabs(Ysum);
    freeAr(&X);
    freeAr(&Y);
    return bias;
}

double calcMAE(arr *restrict Xin,arr *restrict Yin){
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"calcMAE: Input arrays must have same total length\n"); exit(0); }
    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);

    typ_idx i;
    double abserrsum = 0.0;
    for(i=0;i<Y.tlen;++i){
        abserrsum += fabs(iDBL(&X,i)-iDBL(&Y,i));
    }

    double MAE = abserrsum/(double)Y.tlen;
    
    freeAr(&X);
    freeAr(&Y);
    return MAE;
}

double calcMedAE(arr *restrict Xin,arr *restrict Yin){
    arr AE = AbsErr(Xin,Yin);
    double MedAE = Median(&AE);
    freeAr(&AE);
    return MedAE;
}

double calcMSD(arr *restrict Xin,arr *restrict Yin){
/*  The mean square difference, if X is forecast and Y is observed, then the result is the mean square error    */
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"calcMSD: Input arrays must have same total length\n"); exit(0); }
    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);

    typ_idx i;
    double diff;
    double sqerrsum = 0.0;
    for(i=0;i<Y.tlen;++i){
        diff = iDBL(&X,i)-iDBL(&Y,i);
        sqerrsum += diff*diff;
    }

    double MSD = sqerrsum/(double)Y.tlen;
    freeAr(&X);
    freeAr(&Y);
    return MSD;
}

double calcRMSD(arr *restrict Xin,arr *restrict Yin){
    return sqrt(calcMSD(Xin,Yin));
}


double calcMedSD(arr *restrict Xin,arr *restrict Yin){
    arr SE = SqErr(Xin,Yin);
    double MedSE = Median(&SE);
    freeAr(&SE);
    return MedSE;
}

double calcSSD(arr *restrict Xin,arr *restrict Yin){
/*  The Sum square difference, if X is forecast and Y is observed, then the result is the Sum square error    */
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"calcSSD: Input arrays must have same total length\n"); exit(0); }
    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);

    typ_idx i;
    double diff;
    double sqerrsum = 0.0;
    for(i=0;i<Y.tlen;++i){
            diff = iDBL(&X,i)-iDBL(&Y,i);
            sqerrsum += diff*diff;
    }

    double SSD = sqerrsum;
    freeAr(&X);
    freeAr(&Y);
    return SSD;
}

double calcRSquared(arr *restrict Y, arr *restrict Y_fit){
    if (Y->tlen != Y_fit->tlen) {
        fprintf(stderr,"calcRSquared: Input arrays must have same total length; Y->tlen=%lld, Y_fit->tlen=%lld\n",Y->tlen,Y_fit->tlen);
        printArrayFmtAllWHdr(stderr, Y    ,"%g","calcRSquared: Y     - ");
        printArrayFmtAllWHdr(stderr, Y_fit,"%g","calcRSquared: Y_fit - ");
        exit(0);
    }

    double rsq, SS_tot = devMoment(Y,2), SS_res = 0;
    double err_tmp;
    double *pY     = pntr_of(Y);
    double *pY_fit = pntr_of(Y_fit);
    typ_idx i, n=Y->tlen;
    for (i=0;i<n;++i,pY++,pY_fit++){
        err_tmp = *pY - *pY_fit;
        SS_res += err_tmp*err_tmp;
    }

    rsq = 1 - SS_res/SS_tot;
    /* fprintf(stderr,"SS_res=%g, SS_tot=%g, rsq=%g\n",SS_res,SS_tot,rsq); */

    return rsq;
}



double dist_multigausswgt(arr *restrict Xin,arr *restrict Yin){
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"dist_multigausswgt: Input arrays must have same total length\n"); exit(0); }
    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);
    /*
    printArrayFmtAllWHdr(stderr,X, "%g","dist_multigausswgt: X - ");
    printArrayFmtAllWHdr(stderr,Y, "%g","dist_multigausswgt: Y - ");
     */
	double t, t2_sum = 0.0;
    typ_idx ndims = X.tlen;
	typ_idx j;
	for (j=0;j<ndims;j++){
		t       = iDBL(&Y,j)-iDBL(&X,j);
		t2_sum += t*t;
	}
    double num = exp(-0.5*t2_sum);
    double den = exp(-0.5*ndims); /* normalized to distance of standard deviation */

    /* fprintf(stderr,"dist_multigausswgt: ndims=%lld, t2_sum=%g, num=%g, den=%g, ret=%g\n",ndims,t2_sum,num,den,num/den); */
    freeAr(&X);
    freeAr(&Y);
	return num/den;
}


double dist_gausswgt(double X,double Y){
    /* static double A = (1/sqrt(2*M_PI)); */
    static double B  = -0.5;
    static double h2 =  0.25; /* 0.5*0.5 */

    double kval = exp(B*pow(fabs(Y-X),2)/h2);

	return kval;
}

double dist_gausswgt_ave(arr *restrict Xin,arr *restrict Yin){
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"dist_gausswgt_ave: Input arrays must have same total length\n"); exit(0); }
    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);

    /* static double A = (1/sqrt(2*M_PI)); */
    static double B  = -0.5;
    static double h2 =  0.25; /* 0.5*0.5 */

	typ_idx j;
    typ_idx ndims = X.tlen;
	double tsum = 0.0;
	for (j=0;j<ndims;j++){
        tsum += fabs((iDBL(&Y,j)-iDBL(&X,j)));
	}
    tsum = tsum/ndims;
    double t_2  = tsum*tsum;
    double kval = exp(B*t_2/h2);

    freeAr(&X);
    freeAr(&Y);
	return kval;
}


double dist_gausswgt_ave_h2(arr *restrict Xin,arr *restrict Yin, double h2){
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"dist_gausswgt_ave: Input arrays must have same total length\n"); exit(0); }
    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);

    /* static double A = (1/sqrt(2*M_PI)); */
    static double B  = -0.5;

	typ_idx j;
    typ_idx ndims = X.tlen;
	double tsum = 0.0;
	for (j=0;j<ndims;j++){
        tsum += fabs((iDBL(&Y,j)-iDBL(&X,j)));
	}
    tsum = tsum/ndims;
    double t_2  = tsum*tsum;
    double kval = exp(B*t_2/h2);

    freeAr(&X);
    freeAr(&Y);
	return kval;
}


double dist_gausswgt_wave(arr *restrict Xin,arr *restrict Yin, arr *restrict Win){
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"dist_gausswgt_wave: Input arrays must have same total length\n"); exit(0); }
    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);
    arr W = castAr(Win,DOUBLE,0);

    /* static double A = (1/sqrt(2*M_PI)); */
    static double B  = -0.5;
    static double h2 =  0.25; /* 0.5*0.5 */

	typ_idx j;
    typ_idx ndims = X.tlen;
	double tsum = 0.0;
	double wsum = 0.0;
	for (j=0;j<ndims;j++){
        tsum += fabs((iDBL(&Y,j)-iDBL(&X,j)))*iDBL(&W,j);
        wsum += iDBL(&W,j);
	}
    double t_2  = pow(tsum/wsum,2);
    double kval = exp(B*t_2/h2);

    freeAr(&X);
    freeAr(&Y);
    freeAr(&W);
	return kval;
}



double dist_gausswgt_wave_h2(arr *restrict Xin,arr *restrict Yin, arr *restrict Win, double h2){
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"dist_gausswgt_wave: Input arrays must have same total length\n"); exit(0); }
    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);
    arr W = castAr(Win,DOUBLE,0);

    /* static double A = (1/sqrt(2*M_PI)); */
    static double B  = -0.5;

	typ_idx j;
    typ_idx ndims = X.tlen;
	double tsum = 0.0;
	double wsum = 0.0;
	for (j=0;j<ndims;j++){
        tsum += fabs((iDBL(&Y,j)-iDBL(&X,j)))*iDBL(&W,j);
        wsum += iDBL(&W,j);
	}
    double t_2  = pow(tsum/wsum,2);
    double kval = exp(B*t_2/h2);

    freeAr(&X);
    freeAr(&Y);
    freeAr(&W);
	return kval;
}


double WdevMoment(arr *restrict P, arr *restrict W, int moment){ 
    if (P->tlen != W->tlen) { fprintf(stderr,"WdevMoment: Input arrays must have same total length\n"); exit(0); }

    arr X = fct1ar1s(wrap_sub,P,wMean(P,W));
    arr Y = fct1ar1s(wrap_pow,&X,(double)moment);
    arr Z = fct2ar(wrap_mult,&Y,W);
    
    double devsum = Sum(&Z);
    
    freeAr(&X); freeAr(&Y); freeAr(&Z);
    return devsum;
}

double WMoment(arr *restrict P, arr *restrict W, int moment){ 
    if (P->tlen != W->tlen) { fprintf(stderr,"WMoment: Input arrays must have same total length\n"); exit(0); }

    arr Y = fct1ar1s(wrap_pow,P,(double)moment);
    arr Z = fct2ar(wrap_mult,&Y,W);
    
    double devsum = Sum(&Z);
    
    freeAr(&Y); freeAr(&Z);
    return devsum;
}

double VarP(arr *restrict P){ 
    double variance = devMoment(P,2)/(double)P->tlen;
    return variance;
}

double SkewP(arr *restrict P){ 
    double skew = devMoment(P,3)/(double)P->tlen;
    return skew;
}

double KurtP(arr *restrict P){ 
    double kurt = devMoment(P,4)/(double)P->tlen;
    return kurt;
}

double normVarP(arr *restrict P){ 
    double var2 = VarP(P)/pow(stdDevP(P),2);
    return var2;
}

double normSkewP(arr *restrict P){ 
    double skew2 = SkewP(P)/pow(stdDevP(P),3);
    return skew2;
}

double normKurtP(arr *restrict P){ 
    double kurt2 = KurtP(P)/pow(stdDevP(P),4);
    return kurt2;
}

double stdDevP(arr *restrict P){ 
    double sqsum = devMoment(P,2);
    double stddev = sqrt(sqsum/P->tlen);
    return stddev;
}

double VarS(arr *restrict P){ 
    double variance = devMoment(P,2)/(double)(P->tlen-1);
    return variance;
}

double SkewS(arr *restrict P){ 
    double skew = devMoment(P,3)/(double)(P->tlen-1);
    return skew;
}

double KurtS(arr *restrict P){ 
    double kurt = devMoment(P,4)/(double)(P->tlen-1);
    return kurt;
}

double normVarS(arr *restrict P){ 
    double var2 = VarS(P)/pow(stdDevS(P),2);
    return var2;
}

double normSkewS(arr *restrict P){ 
    double skew2 = SkewS(P)/pow(stdDevS(P),3);
    return skew2;
}

double normKurtS(arr *restrict P){ 
    double kurt2 = KurtS(P)/pow(stdDevS(P),4);
    return kurt2;
}

double stdDevS(arr *restrict P){ 
    double sqsum = devMoment(P,2);
    double stddev = sqrt(sqsum/(P->tlen-1));
    return stddev;
}

double WstdDevS(arr *restrict P,arr *restrict W){ 
    if (P->tlen != W->tlen) { fprintf(stderr,"WstdDevS: Input arrays must have same total length\n"); exit(0); }

    double WSum = Sum(W);
    double sqsum,stddev;
    if (WSum > 0.0){
        sqsum = WdevMoment(P,W,2);
        stddev = sqrt(sqsum/WSum);
    } else {
        stddev = stdDevS(P);
    }
    return stddev;
}

double WKurt(arr *restrict P,arr *restrict W){ 
    if (P->tlen != W->tlen) { fprintf(stderr,"WKurt: Input arrays must have same total length\n"); exit(0); }

    double WSum = Sum(W);
    double quartsum,kurt ;
    /* double sqsum,stddev,kurt2; */
    if (WSum > 0.0){
        quartsum = WdevMoment(P,W,4);
        kurt = quartsum/WSum;
    /*  sqsum = WdevMoment(P,W,2);
        stddev = sqrt(sqsum/WSum);
        kurt2 = kurt/pow(stddev,4); */
    } else {
        kurt = KurtS(P);
    /*  kurt2 = normKurtS(P);   */  
    }
    return kurt;
/*  return kurt2 - 3.0; */
}

double sampleStat(arr *restrict P){
    arr s1dP = fct1ar1s(wrap_add,P,0.01);
    arr t1dP = fct1ar(wrap_ln,&s1dP);
    
    double D = log(my_Mean(P)) - (Sum(&t1dP)/P->tlen);
    
    freeAr(&s1dP);
    freeAr(&t1dP);
    return D;
}

double shapeParam(arr *restrict P){ 
    double D = sampleStat(P);
    if (D == *(double *)getMiss(P)){ return D; }
    double alpha = (1 + sqrt(1+4*D/3))/(4*D);
    return alpha;
}

double scaleParam(arr *restrict P){ 
    double meanp  = my_Mean(P);
    if (meanp == *(double *)getMiss(P)){ return meanp; }
    double shapep = shapeParam(P);
    double beta   = meanp/shapep;
    return beta;
}

/* long double used for precision gamma parameter calculations */
long double *cast_arr_long_double(arr *restrict Pin){
    typ_idx len = Pin->tlen;
    long double *m = NULL;
    long double *p = m = malloc(sizeof(long double)*len);
    double *pdbl = pntr_of(Pin);
    
    for(typ_idx i=0;i<len;++i){
        *p++ = *pdbl++;
    }
    return m;
}

long double ld_sum(long double *P,typ_idx len){ 
    long double sum = 0L;
    long double *p = P;
    for (typ_idx i=0; i < len; ++i){
        sum += *p++;
    }

    return sum;
}

long double ld_mean(long double *P,typ_idx len){ 
    return ld_sum(P,len)/(long double)len;
}

long double ld_devmoment(long double *P, typ_idx len, int moment){ 
    long double meanp  = ld_mean(P,len);
    long double moment_ld = (long double)moment;
    long double devsum = 0L;
    long double *p = P;
    for (typ_idx i=0; i < len; ++i, ++p){
        devsum += powl(*p - meanp, moment_ld);
    }
    return devsum;
}

long double ld_vars(long double *P, typ_idx len){ 
    long double variance = ld_devmoment(P,len,2)/(long double)(len-1);
    return variance;
}

void fit_gamma_prms(arr *restrict Pin,double *shape,double *scale){
    static long double four_thirds  = 4.0L/3.0L;

    long double *P = cast_arr_long_double(Pin);
    typ_idx len = Pin->tlen;

    long double vars = ld_vars(P,len);
    if (vars > 0L){
        long double meanp     = ld_mean(P,len);
        /* This was causing problem, but do I still need slight offset in some cases? */
        /* long double meanp_001 = 0.001L*meanp; */

        long double *p = P;
        long double *lnP = NULL;
        long double *x = lnP = malloc(sizeof(long double)*len);
        for (typ_idx i=0; i < len; ++i, ++x, ++p){
            /* *x = logl(*p + meanp_001); */
            *x = logl(*p);
        }
        
        long double D = logl(meanp) - (ld_sum(lnP,len)/(long double)len);
        
        free(lnP);

        double miss_shp = *shape;
        double miss_scl = *scale;
        *shape = (double)((1.0 + sqrtl(1.0+four_thirds*D))/(4.0L*D));
        *scale = meanp/(*shape);
        if (!(*shape > 0) || !(*scale > 0)){
            fprintf(stderr,"Error: fit_gamma_prms: shape=%g, scale=%g, mean=%Lg, var=%Lg\n",*shape,*scale,meanp,vars);
            printArrayFmtAllWHdr(stderr,Pin, "%g","fit_gamma_prms: Pin - ");
            *shape = miss_shp;
            *scale = miss_scl;
            /* exit(0); */
        }
    }

    free(P);
    return;
}

void fit_gamma_prms_lt_3(arr *restrict Pin,double *shape,double *scale){
    long double *P = cast_arr_long_double(Pin);
    typ_idx len = Pin->tlen;

    long double meanp = ld_mean(P,len);
    double miss_shp = *shape;
    double miss_scl = *scale;
    *shape = 1.0;
    *scale = meanp/(*shape);
    if (!(*scale > 0)){
        fprintf(stderr,"Error: fit_gamma_prms_lt_3: shape=%g, scale=%g, mean=%Lg\n",*shape,*scale,meanp);
        printArrayFmtAllWHdr(stderr,Pin, "%g","fit_gamma_prms_lt_3: Pin - ");
        *shape = miss_shp;
        *scale = miss_scl;
        /* exit(0); */
    }

    free(P);
    return;
}

arr NonZeros(arr *restrict Pin,double *pct0){ 
    arr P    = castAr(Pin,DOUBLE,0);
    arr P_nz = Array(1,DOUBLE,P.tlen);

    double zsum = 0,inz = 0;
    typ_idx b = 0;

    while ( b < P.tlen){
        if (iDBL(&P,b) == 0) {
            ++zsum;
        } else {
            iDBL(&P_nz,inz) = iDBL(&P,b);
            inz++;
        }
        b = b + 1;
    }

    *pct0 = zsum/(double)P.tlen;

    freeAr(&P);
    P_nz.len[0] = inz; /* Should properly resize */
    P_nz.tlen   = inz; /* Should properly resize */
    return P_nz;
}

void fit_mixed_gamma_prms(arr *restrict P,double *pct0,double *shape,double *scale){
    double miss_pct0 = *pct0;
    arr P_nz = NonZeros(P,pct0);
    typ_idx n_nz = P_nz.tlen;
    if (n_nz > 4){
        fit_gamma_prms(&P_nz,shape,scale);
    } else if (n_nz > 0) {
        fit_gamma_prms_lt_3(&P_nz,shape,scale);
    } else {
        /* Should I do something here? Nothing leaves shape and scale as missing */
        *pct0 = miss_pct0;
    }

    freeAr(&P_nz);
    return;
}

double Tval(double s,int v) /* needs simplified, to be applied to larger tables */ {
    if (v>80){ v = 80; }
    int i;
    for (i=10;i>=0;--i){
        if (s >= tsig[i]){ break; }
    }

    return ttable[v-1][i];
}

Linreg Regr(arr *restrict X, arr *restrict Y){ /* Renamed from Corr to Regr */
    if (X->tlen != Y->tlen) { fprintf(stderr,"Regr: Input arrays must have same total length\n"); exit(0); }
    arr X2,Y2;
    removeMissing2Arrays(&X2,&Y2,X,Y);
    Linreg lin;
    if (X2.tlen < 3){
        lin.a1 = *(double *)getMiss(X);
        lin.a0 = *(double *)getMiss(X);
        lin.r  = *(double *)getMiss(X);
        lin.n  = *(double *)getMiss(X);
        freeAr(&X2);
        freeAr(&Y2);
        return lin;
    }

    double covxy = Cov(&X2,&Y2);
    double varx = VarP(&X2);
    double vary = VarP(&Y2);
    lin.a1 = covxy/varx;
    lin.a0 = my_Mean(&Y2) - lin.a1*my_Mean(&X2);
    lin.r = (covxy/sqrt(varx*vary));
    lin.n = X2.tlen*((1-lin.r)/(1+lin.r));
    freeAr(&X2);
    freeAr(&Y2);
    return lin;
}



void RegrRef(arr *restrict X, arr *restrict Y,double *a1, double *a0, double *r, double *n){
    if (X->tlen != Y->tlen) { fprintf(stderr,"RegrRef: Input arrays must have same total length; X->tlen=%lld, Y->tlen=%lld\n",X->tlen,Y->tlen); exit(0); }

    double covxy = Cov(X,Y);
    double varx = VarP(X); /* X and Y could have different missing values, leading to non-pairwise answer */
    double vary = VarP(Y);
    *a1 = covxy/varx;
    *a0 = my_Mean(Y) - (*a1)*my_Mean(X);
    *r  = (covxy/sqrt(varx*vary));
    *n  = X->tlen*((1-(*r))/(1+(*r)));
    return;
}

double RSq_OLSCV_old(arr *restrict Xin, arr *restrict Yin){
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"RSq_OLSCV: Input arrays must have same total length; Xin->tlen=%lld, Yin->tlen=%lld\n",Xin->tlen,Yin->tlen); exit(0); }

    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);
    
    arr Xcpy = copyAr(&X);
    arr Ycpy = copyAr(&Y);
    arr Yprd = copyAr(&Y);
    fillArWithMiss(&Yprd);
    /* Set the 3 out to missing */
    double m, b, r, n;
    setToMiss(&Xcpy,0);
    setToMiss(&Ycpy,0);

    arr Xtmp,Ytmp;
    typ_idx ical=0;
    for(; ical < 2; ++ical){
        setToMiss(&Xcpy,ical+1);
        setToMiss(&Ycpy,ical+1);
        removeMissing2Arrays(&Xtmp,&Ytmp,&Xcpy,&Ycpy);
        RegrRef(&Xtmp, &Ytmp, &m, &b, &r, &n);
        iDBL(&Yprd,ical) = mx_b(m,iDBL(&X,ical),b);
        freeAr(&Xtmp);
        freeAr(&Ytmp);
    }

    for(; ical < X.tlen-1; ++ical){
        iDBL(&Xcpy,ical-2) = iDBL(&X,ical-2);
        iDBL(&Ycpy,ical-2) = iDBL(&Y,ical-2);
        setToMiss(&Xcpy,ical+1);
        setToMiss(&Ycpy,ical+1);
        removeMissing2Arrays(&Xtmp,&Ytmp,&Xcpy,&Ycpy);
        RegrRef(&Xtmp, &Ytmp, &m, &b, &r, &n);
        iDBL(&Yprd,ical) = mx_b(m,iDBL(&X,ical),b);
        freeAr(&Xtmp);
        freeAr(&Ytmp);
    }

    iDBL(&Xcpy,ical-2) = iDBL(&X,ical-2);
    iDBL(&Ycpy,ical-2) = iDBL(&Y,ical-2);
    removeMissing2Arrays(&Xtmp,&Ytmp,&Xcpy,&Ycpy);
    RegrRef(&Xtmp, &Ytmp, &m, &b, &r, &n);
    iDBL(&Yprd,ical) = mx_b(m,iDBL(&X,ical),b);
    freeAr(&Xtmp);
    freeAr(&Ytmp);
    
    double rsq = calcRSquared(&Y, &Yprd);
    freeAr(&Xcpy);
    freeAr(&Ycpy);
    freeAr(&Yprd);
    freeAr(&X);
    freeAr(&Y);
    return rsq;
}


void SumStatsXY_online_add(double x, double y,
                           double *Xsum, double *Ysum,
                           double *Xsumsq, double *Ysumsq,
                           double *XYsum, double *XYSD,
                           double *XYSSD, double *XYSAD, typ_idx *N){
    double xyd = x-y;
    *Xsum   += x;
    *Ysum   += y;
    *Xsumsq += x*x;
    *Ysumsq += y*y;
    *XYsum  += x*y;
    *XYSD   += xyd;
    *XYSSD  += xyd*xyd;
    *XYSAD  += fabs(xyd);
    (*N)++;
    return;
}

void SumStatsXY_online_sub(double x, double y,
                           double *Xsum, double *Ysum,
                           double *Xsumsq, double *Ysumsq,
                           double *XYsum, double *XYSD,
                           double *XYSSD, double *XYSAD, typ_idx *N){
    double xyd = x-y;
    *Xsum   -= x;
    *Ysum   -= y;
    *Xsumsq -= x*x;
    *Ysumsq -= y*y;
    *XYsum  -= x*y;
    *XYSD   -= xyd;
    *XYSSD  -= xyd*xyd;
    *XYSAD  -= fabs(xyd);
    (*N)--;
    return;
}


/* Try to make online calculation of correlation to speed up process of adding and removing data */
double RSq_OLSCV_naive(arr *restrict Xin, arr *restrict Yin){
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"RSq_OLSCV: Input arrays must have same total length; Xin->tlen=%lld, Yin->tlen=%lld\n",Xin->tlen,Yin->tlen); exit(0); }

    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);

    double  Xsum   = 0;
    double  Ysum   = 0;
    double  Xsumsq = 0;
    double  Ysumsq = 0;
    double  XYsum  = 0;
    double  XYSD   = 0;
    double  XYSSD  = 0;
    double  XYSAD  = 0;
    typ_idx N      = 0;

    /* Initial pass calculates full in-sample regression */
    typ_idx ical=0;
    for(ical=0; ical < X.tlen; ++ical){
        SumStatsXY_online_add(iDBL(&X,ical), iDBL(&Y,ical),
                              &Xsum,   &Ysum,
                              &Xsumsq, &Ysumsq,
                              &XYsum,  &XYSD, 
                              &XYSSD, &XYSAD, &N);
    }
    
    arr Yprd = copyAr(&Y);
    fillArWithMiss(&Yprd);
    /* Set the 3 out to missing */
    double m, b, r, n;
    SumStatsXY_online_sub(iDBL(&X,0), iDBL(&Y,0),
                          &Xsum,   &Ysum,
                          &Xsumsq, &Ysumsq,
                          &XYsum,  &XYSD, 
                          &XYSSD, &XYSAD, &N);

    ical=0;
    for(; ical < 2; ++ical){
        SumStatsXY_online_sub(iDBL(&X,ical+1), iDBL(&Y,ical+1),
                              &Xsum,   &Ysum,
                              &Xsumsq, &Ysumsq,
                              &XYsum,  &XYSD, 
                              &XYSSD, &XYSAD, &N);
        m = ceq_slope(Xsum, Ysum, Xsumsq, XYsum, N);
        b = ceq_mean(Ysum, N) - m*ceq_mean(Xsum, N);

        iDBL(&Yprd,ical) = mx_b(m,iDBL(&X,ical),b);
    }

    for(; ical < X.tlen-1; ++ical){
        SumStatsXY_online_sub(iDBL(&X,ical+1), iDBL(&Y,ical+1),
                              &Xsum,   &Ysum,
                              &Xsumsq, &Ysumsq,
                              &XYsum,  &XYSD, 
                              &XYSSD, &XYSAD, &N);
        SumStatsXY_online_add(iDBL(&X,ical-2), iDBL(&Y,ical-2),
                              &Xsum,   &Ysum,
                              &Xsumsq, &Ysumsq,
                              &XYsum,  &XYSD, 
                              &XYSSD, &XYSAD, &N);
        m = ceq_slope(Xsum, Ysum, Xsumsq, XYsum, N);
        b = ceq_mean(Ysum, N) - m*ceq_mean(Xsum, N);

        iDBL(&Yprd,ical) = mx_b(m,iDBL(&X,ical),b);
    }

    SumStatsXY_online_add(iDBL(&X,ical-2), iDBL(&Y,ical-2),
                          &Xsum,   &Ysum,
                          &Xsumsq, &Ysumsq,
                          &XYsum,  &XYSD, 
                          &XYSSD, &XYSAD, &N);
    m = ceq_slope(Xsum, Ysum, Xsumsq, XYsum, N);
    b = ceq_mean(Ysum, N) - m*ceq_mean(Xsum, N);

    iDBL(&Yprd,ical) = mx_b(m,iDBL(&X,ical),b);

    double rsq = calcRSquared(&Y, &Yprd);
    freeAr(&Yprd);
    freeAr(&X);
    freeAr(&Y);
    return rsq;
}

void Welford_add(double x, double y, double *XMn, double *XM2, double *YMn, double *YM2,double *C, typ_idx *N){
    (*N)++;
    
    double dx = x - (*XMn);
    *XMn += dx / (*N);
    double dx2 = x - (*XMn);
    *XM2 += dx * dx2;
    
    double dy = y - *YMn;
    *YMn += dy / (*N);
    double dy2 = y - *YMn;
    *YM2 += dy * dy2;

    *C   += dx * dy2;
    return;
}

void Welford_sub(double x, double y, double *XMn, double *XM2, double *YMn, double *YM2,double *C, typ_idx *N){
    (*N)--;
    
    double dx = x - (*XMn);
    *XMn -= dx / (*N);
    double dx2 = x - (*XMn);
    *XM2 -= dx * dx2;
    
    double dy = y - *YMn;
    *YMn -= dy / (*N);
    double dy2 = y - *YMn;
    *YM2 -= dy * dy2;

    *C   -= dx * dy2;
    return;
}

double ceq_slope_welford(double XM2, double C){
  double slope;
  if (XM2 != 0){
    slope = C/XM2;
  } else {
    slope = -999.0;
  }

  return slope;
}

/* Try to make online calculation of correlation to speed up process of adding and removing data */
double RSq_OLSCV(arr *restrict Xin, arr *restrict Yin){
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"RSq_OLSCV: Input arrays must have same total length; Xin->tlen=%lld, Yin->tlen=%lld\n",Xin->tlen,Yin->tlen); exit(0); }

    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);

    double  XMn = 0;
    double  XM2 = 0;
    double  YMn = 0;
    double  YM2 = 0;
    double  C   = 0;
    typ_idx N   = 0;

    /* Initial pass calculates full in-sample regression */
    typ_idx ical=0;
    for(ical=0; ical < X.tlen; ++ical){
        Welford_add(iDBL(&X,ical), iDBL(&Y,ical), &XMn, &XM2, &YMn, &YM2, &C, &N);
    }
    
    arr Yprd = copyAr(&Y);
    fillArWithMiss(&Yprd);
    /* Set the 3 out to missing */
    double m, b;
    Welford_sub(iDBL(&X,0), iDBL(&Y,0), &XMn, &XM2, &YMn, &YM2, &C, &N);

    ical=0;
    for(; ical < 2; ++ical){
        Welford_sub(iDBL(&X,ical+1), iDBL(&Y,ical+1), &XMn, &XM2, &YMn, &YM2, &C, &N);

        m = ceq_slope_welford(XM2, C);
        b = YMn - m*XMn;

        iDBL(&Yprd,ical) = mx_b(m,iDBL(&X,ical),b);
    }

    for(; ical < X.tlen-1; ++ical){
        Welford_sub(iDBL(&X,ical+1), iDBL(&Y,ical+1), &XMn, &XM2, &YMn, &YM2, &C, &N);
        Welford_add(iDBL(&X,ical-2), iDBL(&Y,ical-2), &XMn, &XM2, &YMn, &YM2, &C, &N);

        m = ceq_slope_welford(XM2, C);
        b = YMn - m*XMn;

        iDBL(&Yprd,ical) = mx_b(m,iDBL(&X,ical),b);
    }

    Welford_add(iDBL(&X,ical-2), iDBL(&Y,ical-2), &XMn, &XM2, &YMn, &YM2, &C, &N);

    m = ceq_slope_welford(XM2, C);
    b = YMn - m*XMn;

    iDBL(&Yprd,ical) = mx_b(m,iDBL(&X,ical),b);

    double rsq = calcRSquared(&Y, &Yprd);

    freeAr(&Yprd);
    freeAr(&X);
    freeAr(&Y);
    return rsq;
}


/* Try to make online calculation of correlation to speed up process of adding and removing data */
double RSq_OLSCV_nout(arr *restrict Xin, arr *restrict Yin, typ_idx nout){
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"RSq_OLSCV_nout: Input arrays must have same total length; Xin->tlen=%lld, Yin->tlen=%lld\n",Xin->tlen,Yin->tlen); exit(0); }

    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);

    double  XMn = 0;
    double  XM2 = 0;
    double  YMn = 0;
    double  YM2 = 0;
    double  C   = 0;
    typ_idx N   = 0;
    typ_idx n   = X.tlen;

    /* Initial pass calculates full in-sample regression */
    typ_idx i=0;
    for(i=0; i < n; ++i){
        Welford_add(iDBL(&X,i), iDBL(&Y,i), &XMn, &XM2, &YMn, &YM2, &C, &N);
    }
    
    arr Yprd = copyAr(&Y);
    fillArWithMiss(&Yprd);
    /* Set the 3 out to missing */
    double m, b;
    typ_idx n1 = (nout-1)/2;
    typ_idx n2 = n1+1;
    for(i=0;i<n1;++i){
        Welford_sub(iDBL(&X,i), iDBL(&Y,i), &XMn, &XM2, &YMn, &YM2, &C, &N);
    }

    i=0;
    for(; i < n2; ++i){
        Welford_sub(iDBL(&X,i+n1), iDBL(&Y,i+n1), &XMn, &XM2, &YMn, &YM2, &C, &N);

        m = ceq_slope_welford(XM2, C);
        b = YMn - m*XMn;

        iDBL(&Yprd,i) = mx_b(m,iDBL(&X,i),b);
    }

    for(; i < n-n1; ++i){
        Welford_sub(iDBL(&X,i+n1), iDBL(&Y,i+n1), &XMn, &XM2, &YMn, &YM2, &C, &N);
        Welford_add(iDBL(&X,i-n2), iDBL(&Y,i-n2), &XMn, &XM2, &YMn, &YM2, &C, &N);

        m = ceq_slope_welford(XM2, C);
        b = YMn - m*XMn;

        iDBL(&Yprd,i) = mx_b(m,iDBL(&X,i),b);
    }

    for(; i < n; ++i){
        Welford_add(iDBL(&X,i-n2), iDBL(&Y,i-n2), &XMn, &XM2, &YMn, &YM2, &C, &N);
        m = ceq_slope_welford(XM2, C);
        b = YMn - m*XMn;
    
        iDBL(&Yprd,i) = mx_b(m,iDBL(&X,i),b);
    }
    
    double rsq = calcRSquared(&Y, &Yprd);

    freeAr(&Yprd);
    freeAr(&X);
    freeAr(&Y);
    return rsq;
}


/* Try to make online calculation of correlation to speed up process of adding and removing data */
double RSq_OLSFV_nout(arr *restrict Xin, arr *restrict Yin, typ_idx nstart){
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"RSq_OLSFV_nstart: Input arrays must have same total length; Xin->tlen=%lld, Yin->tlen=%lld\n",Xin->tlen,Yin->tlen); exit(0); }

    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);

    double  XMn = 0;
    double  XM2 = 0;
    double  YMn = 0;
    double  YM2 = 0;
    double  C   = 0;
    typ_idx N   = 0;
    typ_idx n   = X.tlen;

    /* Initial pass calculates full in-sample regression */
    typ_idx i=0;
    for(i=0; i < nstart; ++i){
        Welford_add(iDBL(&X,i), iDBL(&Y,i), &XMn, &XM2, &YMn, &YM2, &C, &N);
    }
    
    arr Yprd = copyAr(&Y);
    fillArWithMiss(&Yprd);
    /* Set the 3 out to missing */
    double m, b;
    for(; i < n; ++i){
        m = ceq_slope_welford(XM2, C);
        b = YMn - m*XMn;
    
        iDBL(&Yprd,i) = mx_b(m,iDBL(&X,i),b);

        Welford_add(iDBL(&X,i), iDBL(&Y,i), &XMn, &XM2, &YMn, &YM2, &C, &N);
    }
    
    arr Ytmp, Yprdtmp;
    removeMissing2Arrays(&Ytmp,&Yprdtmp,&Y,&Yprd);
    double rsq = calcRSquared(&Ytmp,&Yprdtmp);

    freeAr(&Ytmp);
    freeAr(&Yprdtmp);
    freeAr(&Yprd);
    freeAr(&X);
    freeAr(&Y);
    return rsq;
}



/* Try to make online calculation of correlation to speed up process of adding and removing data */
double RSq_OLSFV_nlast(arr *restrict Xin, arr *restrict Yin, typ_idx nlast){
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"RSq_OLSFV_nlast: Input arrays must have same total length; Xin->tlen=%lld, Yin->tlen=%lld\n",Xin->tlen,Yin->tlen); exit(0); }

    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);

    double  XMn    = 0;
    double  XM2    = 0;
    double  YMn    = 0;
    double  YM2    = 0;
    double  C      = 0;
    typ_idx N      = 0;
    typ_idx n      = X.tlen;
    typ_idx nstart = n - nlast;
    if (nstart < 15){
        freeAr(&X);
        freeAr(&Y);
        return NAN;
    }

    /* Initial pass calculates full in-sample regression */
    typ_idx i=0;
    for(i=0; i < nstart; ++i){
        Welford_add(iDBL(&X,i), iDBL(&Y,i), &XMn, &XM2, &YMn, &YM2, &C, &N);
    }
    
    arr Yprd = copyAr(&Y);
    fillArWithMiss(&Yprd);
    /* Set the 3 out to missing */
    double m, b;
    for(; i < n; ++i){
        m = ceq_slope_welford(XM2, C);
        b = YMn - m*XMn;
    
        iDBL(&Yprd,i) = mx_b(m,iDBL(&X,i),b);

        Welford_add(iDBL(&X,i), iDBL(&Y,i), &XMn, &XM2, &YMn, &YM2, &C, &N);
    }
    
    arr Ytmp, Yprdtmp;
    removeMissing2Arrays(&Ytmp,&Yprdtmp,&Y,&Yprd);
    double rsq = calcRSquared(&Ytmp,&Yprdtmp);

    freeAr(&Ytmp);
    freeAr(&Yprdtmp);
    freeAr(&Yprd);
    freeAr(&X);
    freeAr(&Y);
    return rsq;
}


void RegrRef_min(arr *restrict X, arr *restrict Y,double t_sig,double *m, double *b, double *rsq, double *mad){
    if (X->tlen != Y->tlen) { fprintf(stderr,"RegrRef_min: Input arrays must have same total length; X->tlen=%lld, Y->tlen=%lld\n",X->tlen,Y->tlen); exit(0); }

    typ_idx i,n=X->tlen;
    double xi,yi,Sx=0,Sxx=0,Sy=0,Syy=0,Sxy=0;
    for (i=0;i<n;++i){
        xi   = iDBL(X,i);
        yi   = iDBL(Y,i);
        Sx  += xi;
        Sxx += xi*xi;
        Sy  += yi;
        Syy += yi*yi;
        Sxy += xi*yi;
    }
    *m = (n*Sxy - Sx*Sy)/(n*Sxx - Sx*Sx);
    double S_eps_2 = (n*Syy-Sy*Sy-(*m)*(*m)*(n*Sxx-Sx*Sx))/(n*(n-2));
    double S_m_2   = (n*S_eps_2)/(n*Sxx-Sx*Sx);
    double t       = Tval(t_sig,(int)n-2);
    double m_adj   = t*S_m_2;
    /* fprintf(stderr,"RegrRef_min: m_adj=%g, m=%g",m_adj,*m); */
    if (m_adj > fabs(*m)){
        *m = 0;
    } else {
        double m_lo    = (*m) - m_adj;
        double m_hi    = (*m) + m_adj;
        /* fprintf(stderr," m_lo=%g, m_hi=%g",m_lo,m_hi); */
        if (fabs(m_lo) < fabs(m_hi)){ *m = m_lo; } else { *m = m_hi; }
    }
    *b = my_Mean(Y) - (*m)*my_Mean(X);
    /* fprintf(stderr," m=%g\n",*m); */

    double rsq1, mad1 = 0, SS_tot = devMoment(Y,2);
    if (SS_tot > 0){
        double SS_res = 0;
        double err_tmp;
        for (i=0;i<n;++i){
            err_tmp = iDBL(Y,i)-(*m)*iDBL(X,i)-(*b);
            SS_res +=       err_tmp*err_tmp;
            mad1   += fabs( err_tmp );
        }
    
        mad1 /= n;
        rsq1  = 1 - SS_res/SS_tot;
    } else {
        printArrayFmtAllWHdr(stderr,X, "%g","RegrRef_min: X - ");
        printArrayFmtAllWHdr(stderr,Y, "%g","RegrRef_min: Y - ");
        fprintf(stderr,"RegrRef_min: m=%g, b=%g, nelem=%lld, SS_tot=%g\n",*m,*b,n,SS_tot);
        exit(0); /* */
    }

    *mad = mad1;
    *rsq = rsq1;

    return;
}

void RegrRef_TheilSen(arr *restrict X, arr *restrict Y,double *a1, double *a0, double *rsq, double *mad){
    if (X->tlen != Y->tlen) {
        fprintf(stderr,"RegrRef_TheilSen: Input arrays must have same total length; X->tlen=%lld, Y->tlen=%lld\n",X->tlen,Y->tlen);
        printArrayFmtAllWHdr(stderr, X,"%g","RegrRef_TheilSen: X - ");
        printArrayFmtAllWHdr(stderr, Y,"%g","RegrRef_TheilSen: Y - ");
        exit(0);
    }

    typ_idx nelem      = X->tlen;
    typ_idx npairs = nelem*(nelem-1)/2;
    
    arr slopes = Array(1,DOUBLE,npairs);
    typ_idx ip = 0,i,j;
    
    double dx;
    for (j=0;j<nelem-1;++j){
        for (i=j+1;i<nelem;++i){
            dx = (iDBL(X,i)-iDBL(X,j));
            if (fabs(dx) > 0){
                iDBL(&slopes,ip) = (iDBL(Y,i)-iDBL(Y,j))/dx;
                ++ip;
            }
        }
    }
    
    arr ms = assign1dtoNd(pntr_of(&slopes), 1, DOUBLE, ip);
    
    double m = Median(&ms);
    if (!isfinite(m)){
        printArrayFmtAllWHdr(stderr,X,"%g","RegrRef_TheilSen: X - ");
        printArrayFmtAllWHdr(stderr,Y,"%g","RegrRef_TheilSen: Y - ");
        printArrayFmtAllWHdr(stderr,&ms,"%g","RegrRef_TheilSen: m=%g, ms - ",m);
        exit(0);
    }
    
    arr bs = Array(1,DOUBLE,nelem);
    for (i=0;i<nelem;++i){
        iDBL(&bs,i) = iDBL(Y,i)-m*iDBL(X,i);
    }
    
    double b = Median(&bs);
    if (!isfinite(b)){
        printArrayFmtAllWHdr(stderr,X,"%g","RegrRef_TheilSen: X - ");
        printArrayFmtAllWHdr(stderr,Y,"%g","RegrRef_TheilSen: Y - ");
        printArrayFmtAllWHdr(stderr,&ms,"%g","RegrRef_TheilSen: m=%g, ms - ",m);
        printArrayFmtAllWHdr(stderr,&bs,"%g","RegrRef_TheilSen: b=%g, bs - ",b);
        exit(0);
    }
    
    double rsq1, mad1 = 0, SS_tot = devMoment(Y,2);
    if (SS_tot > 0){
        double SS_res = 0;
        double err_tmp;
        for (i=0;i<nelem;++i){
            err_tmp = iDBL(&bs,i)-b;
            SS_res +=       err_tmp*err_tmp;
            mad1   += fabs( err_tmp );
        }
    
        mad1 /= nelem;
        rsq1 = 1 - SS_res/SS_tot;
    } else {
        mad1 = *mad;
        rsq1 = *rsq;
        /* m    = *a1; */
        /* b    = *a0; */
        /*
        printArrayFmtAllWHdr(stderr,X,"%g","RegrRef_TheilSen: X - ");
        printArrayFmtAllWHdr(stderr,Y,"%g","RegrRef_TheilSen: Y - ");
        printArrayFmtAllWHdr(stderr,&ms,"%g","RegrRef_TheilSen: m=%g, ms - ",m);
        printArrayFmtAllWHdr(stderr,&bs,"%g","RegrRef_TheilSen: b=%g, bs - ",b);
        fprintf(stderr,"RegrRef_TheilSen: nelem=%lld,SS_tot=%g\n",nelem,SS_tot);
         */
        /* exit(0); */
    }

    *a1  = m;
    *a0  = b;
    *mad = mad1;
    *rsq = rsq1;
    
    freeArShell(&ms);
    freeAr(&slopes);
    freeAr(&bs);
    return;
}

void RegrRef_TheilSen_CC_slopes(arr *restrict X, arr *restrict Y,arr *slopes,arr *Slopes_Idx,arr *Slopes_RevIdx){
    if (X->tlen != Y->tlen) {
        fprintf(stderr,"RegrRef_TheilSen_CC_slopes: Input arrays must have same total length; X->tlen=%lld, Y->tlen=%lld\n",X->tlen,Y->tlen);
        printArrayFmtAllWHdr(stderr, X,"%g","RegrRef_TheilSen_CC_slopes: X - ");
        printArrayFmtAllWHdr(stderr, Y,"%g","RegrRef_TheilSen_CC_slopes: Y - ");
        exit(0);
    }

    typ_idx nelem  = X->tlen;
    typ_idx npairs = nelem*(nelem-1)/2;
    
    *slopes = Array(1,DOUBLE,npairs);
    typ_idx ip = 0,i,j;
    
    double dx;
    for (j=0;j<nelem-1;++j){
        if (isMiss(X,j) || isMiss(Y,j)){
            for (i=j+1;i<nelem;++i){
                setToMiss(slopes,ip);
                ++ip;
            }
        } else {
            for (i=j+1;i<nelem;++i){
                if (isMiss(X,i) || isMiss(Y,i)){
                    setToMiss(slopes,ip);
                } else {
                    dx = (iDBL(X,i)-iDBL(X,j));
                    if (fabs(dx) > 0){
                        iDBL(slopes,ip) = (iDBL(Y,i)-iDBL(Y,j))/dx;
                    } else {
                        setToMiss(slopes,ip);
                    }
                }
                ++ip;
            }
        }
    }
    
    qsortArrayIdxWRev(slopes,Slopes_Idx,Slopes_RevIdx);

    return;
}

void RegrRef_TheilSen_CC_skip(arr *restrict X, arr *restrict Y,arr *restrict slopes,arr *restrict Slopes_Idx,typ_idx iskip,double *a1, double *a0, double *rsq, double *mad){
    if (X->tlen != Y->tlen) { 
        fprintf(stderr,"RegrRef_TheilSen_CC_skip: Input arrays must have same total length; X->tlen=%lld, Y->tlen=%lld\n",X->tlen,Y->tlen);
        printArrayFmtAllWHdr(stderr, X,"%g","RegrRef_TheilSen_CC_skip: X - ");
        printArrayFmtAllWHdr(stderr, Y,"%g","RegrRef_TheilSen_CC_skip: Y - ");
        exit(0);
    }

    typ_idx n      = X->tlen;
    typ_idx npairs = n*(n-1)/2;
    
    arr slopes2 = Array(1,DOUBLE,npairs);
    typ_idx ip2 = 0,ip,i,j,cidx;
    
    typ_idx jtrm1 = n - 2;
    double  jtrm2 = 4*n*(n-1)-7;
    typ_idx itrm1 = 1 - npairs;
    for (ip=0;ip<npairs;++ip){
        cidx = iIDX(Slopes_Idx,ip);
        j = jtrm1 - floor(sqrt(-8*cidx + jtrm2)/2.0 - 0.5);
        if (j != iskip){
            i = cidx + j + itrm1 + (n-j)*((n-j)-1)/2;
            if (i != iskip){
                if (isMiss(slopes,cidx)){
                    break;
                } else {
                    iDBL(&slopes2,ip2) = iDBL(slopes,cidx) ;
                    ++ip2;
                }
            }
        }
    }
    
    arr ms = assign1dtoNd(pntr_of(&slopes2), 1, DOUBLE, ip2);
    
    double m = calcValatPercSorted(&ms,0.5);
    if (!isfinite(m)){ /* */
        printArrayFmtAllWHdr(stderr, X,"%g","RegrRef_TheilSen_CC_skip: X - ");
        printArrayFmtAllWHdr(stderr, Y,"%g","RegrRef_TheilSen_CC_skip: Y - ");
        printArrayFmtAllWHdr(stderr,&ms,"%g","RegrRef_TheilSen_CC_skip: m=%g, ms - ",m);
        exit(0);
    } /* */
    
    arr X_tmp,Y_tmp;
    removeMissing2Arrays(&X_tmp,&Y_tmp,X,Y);
    if (Y_tmp.tlen == 0){
        freeArShell(&ms);
        freeAr(&slopes2);
        freeAr(&X_tmp);
        freeAr(&Y_tmp);
        return;
    }

    arr bs = Array(1,DOUBLE,Y_tmp.tlen);
    for (i=0;i<Y_tmp.tlen;++i){
        iDBL(&bs,i) = iDBL(&Y_tmp,i)-m*iDBL(&X_tmp,i);
    }
    
    double b = Median(&bs);
    if (!isfinite(b)){
        printArrayFmtAllWHdr(stderr,&X_tmp,"%g","RegrRef_TheilSen_CC_skip: X_tmp - ");
        printArrayFmtAllWHdr(stderr,&Y_tmp,"%g","RegrRef_TheilSen_CC_skip: Y_tmp - ");
        printArrayFmtAllWHdr(stderr,&ms,"%g","RegrRef_TheilSen_CC_skip: m=%g, ms - ",m);
        printArrayFmtAllWHdr(stderr,&bs,"%g","RegrRef_TheilSen_CC_skip: b=%g, bs - ",b);
        exit(0);
    }
    
    double rsq1, mad1 = 0, SS_tot = devMoment(&Y_tmp,2);
    if (SS_tot > 0){
        double SS_res = 0;
        double err_tmp;
        for (i=0;i<Y_tmp.tlen;++i){
        /*  err_tmp = iDBL(&Y_tmp,i)-m*iDBL(&X_tmp,i)-b; */
            err_tmp = iDBL(&bs,i)-b;
            SS_res +=       err_tmp*err_tmp;
            mad1   += fabs( err_tmp );
        }
    
        mad1 /= Y_tmp.tlen;
        rsq1 = 1 - SS_res/SS_tot;
    } else {
        printArrayFmtAllWHdr(stderr,&X_tmp,"%g","RegrRef_TheilSen_CC_skip: X_tmp - ");
        printArrayFmtAllWHdr(stderr,&Y_tmp,"%g","RegrRef_TheilSen_CC_skip: Y_tmp - ");
        printArrayFmtAllWHdr(stderr,&ms,"%g","RegrRef_TheilSen_CC_skip: m=%g, ms - ",m);
        printArrayFmtAllWHdr(stderr,&bs,"%g","RegrRef_TheilSen_CC_skip: b=%g, bs - ",b);
        fprintf(stderr,"RegrRef_TheilSen_CC_skip: n=%lld,SS_tot=%g\n",Y_tmp.tlen,SS_tot);
        exit(0); /* */
    }

    *a1  = m;
    *a0  = b;
    *mad = mad1;
    *rsq = rsq1;
    
    freeArShell(&ms);
    freeAr(&slopes2);
    freeAr(&bs);
    freeAr(&X_tmp);
    freeAr(&Y_tmp);
    return;
}


void RegrRef_TheilSen_CC(arr *restrict X, arr *restrict Y,arr *restrict slopes,arr *restrict Slopes_Idx,double *a1, double *a0, double *rsq, double *mad){
    if (X->tlen != Y->tlen) {
        fprintf(stderr,"RegrRef_TheilSen_CC: Input arrays must have same total length; X->tlen=%lld, Y->tlen=%lld\n",X->tlen,Y->tlen);
        printArrayFmtAllWHdr(stderr, X,"%g","RegrRef_TheilSen_CC: X - ");
        printArrayFmtAllWHdr(stderr, Y,"%g","RegrRef_TheilSen_CC: Y - ");
        exit(0);
    }

    typ_idx n      = X->tlen;
    typ_idx npairs = n*(n-1)/2;
    
    arr slopes2 = Array(1,DOUBLE,npairs);
    typ_idx ip2 = 0,ip,i,cidx;
    
    for (ip=0;ip<npairs;++ip){
        cidx = iIDX(Slopes_Idx,ip);
        if (isMiss(slopes,cidx)){
            break;
        } else {
            iDBL(&slopes2,ip2) = iDBL(slopes,cidx) ;
            ++ip2;
        }
    }
    
    arr ms = assign1dtoNd(pntr_of(&slopes2), 1, DOUBLE, ip2);
    
    double m = calcValatPercSorted(&ms,0.5);
    if (!isfinite(m)){ /* */
        printArrayFmtAllWHdr(stderr,X,"%g","RegrRef_TheilSen_CC: X - ");
        printArrayFmtAllWHdr(stderr,Y,"%g","RegrRef_TheilSen_CC: Y - ");
        printArrayFmtAllWHdr(stderr,&ms,"%g","RegrRef_TheilSen_CC: m=%g, ms - ",m);
        exit(0);
    } /* */
    
    arr X_tmp,Y_tmp;
    removeMissing2Arrays(&X_tmp,&Y_tmp,X,Y);
    if (Y_tmp.tlen == 0){
        freeArShell(&ms);
        freeAr(&slopes2);
        freeAr(&X_tmp);
        freeAr(&Y_tmp);
        return;
    }

    arr bs = Array(1,DOUBLE,Y_tmp.tlen);
    for (i=0;i<Y_tmp.tlen;++i){
        iDBL(&bs,i) = iDBL(&Y_tmp,i)-m*iDBL(&X_tmp,i);
    }
    
    double b = Median(&bs);
    if (!isfinite(b)){
        printArrayFmtAllWHdr(stderr,&X_tmp,"%g","RegrRef_TheilSen_CC: X_tmp - ");
        printArrayFmtAllWHdr(stderr,&Y_tmp,"%g","RegrRef_TheilSen_CC: Y_tmp - ");
        printArrayFmtAllWHdr(stderr,&ms,"%g","RegrRef_TheilSen_CC: m=%g, ms - ",m);
        printArrayFmtAllWHdr(stderr,&bs,"%g","RegrRef_TheilSen_CC: b=%g, bs - ",b);
        exit(0);
    }
    
    double rsq1, mad1 = 0, SS_tot = devMoment(&Y_tmp,2);
    if (SS_tot > 0){
        double SS_res = 0;
        double err_tmp;
        for (i=0;i<Y_tmp.tlen;++i){
        /*  err_tmp = iDBL(&Y_tmp,i)-m*iDBL(&X_tmp,i)-b; */
            err_tmp = iDBL(&bs,i)-b;
            SS_res +=       err_tmp*err_tmp;
            mad1   += fabs( err_tmp );
        }
    
        mad1 /= Y_tmp.tlen;
        rsq1 = 1 - SS_res/SS_tot;
    } else {
        printArrayFmtAllWHdr(stderr,&X_tmp,"%g","RegrRef_TheilSen_CC: X_tmp - ");
        printArrayFmtAllWHdr(stderr,&Y_tmp,"%g","RegrRef_TheilSen_CC: Y_tmp - ");
        printArrayFmtAllWHdr(stderr,&ms,"%g","RegrRef_TheilSen_CC: m=%g, ms - ",m);
        printArrayFmtAllWHdr(stderr,&bs,"%g","RegrRef_TheilSen_CC: b=%g, bs - ",b);
        fprintf(stderr,"RegrRef_TheilSen_CC: n=%lld,SS_tot=%g\n",Y_tmp.tlen,SS_tot);
        exit(0); /* */
    }

    *a1  = m;
    *a0  = b;
    *mad = mad1;
    *rsq = rsq1;
    
    freeArShell(&ms);
    freeAr(&slopes2);
    freeAr(&bs);
    return;
}

double lagCorr(arr * P){ /* Only works for offset of one time-step */
    int i;
    typ_idx tlen = P->tlen-1;
    arr X = Array((typ_idx)1,P->typ,tlen);
    arr Y = Array((typ_idx)1,P->typ,tlen);

    switch (P->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pP = pntr_of( P); \
        swcast *pX = pntr_of(&X); \
        swcast *pY = pntr_of(&Y); \
        for(i=0;i<tlen;++i) { \
            *pY++ = *pP++; \
            *pX++ = *pP; \
        }  \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"lagCorr: undefined type!\n");
            exit(0);
            break;
    }
    #undef SWITCHCAST

    double r = Corr(&X,&Y);
    freeAr(&X); freeAr(&Y);
    return r;
}

double lagCorrN(arr * P,int n){ /* Works for offset of n time-steps */
    int i;
    typ_idx tlen = P->tlen-n;
    arr X = Array((typ_idx)1,P->typ,tlen);
    arr Y = Array((typ_idx)1,P->typ,tlen);

    switch (P->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pP = pntr_of( P); \
        swcast *pX = pntr_of(&X); \
        swcast *pY = pntr_of(&Y); \
        for(i=0;i<tlen;++i) { \
            *pX++ = *(pP+n); \
            *pY++ = *pP++; \
        }  \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"lagCorrN: undefined type!\n");
            exit(0);
            break;
    }
    #undef SWITCHCAST

    double r = Corr(&X,&Y);
    freeAr(&X); freeAr(&Y);
    return r;
}

double Corr(arr * X, arr * Y){
    if (X->tlen != Y->tlen) { fprintf(stderr,"Corr: Input arrays must have same total length\n"); exit(0); }

    double xmiss = *(double *)getMiss(X);
    double covxy = Cov(X,Y);
    if (covxy == xmiss){
        return xmiss;
    }
    double varx  = VarP(X);
    if (varx <= 0){
        return xmiss;
    }
    double vary  = VarP(Y);
    if (vary <= 0){
        return xmiss;
    }
    double r = (covxy/sqrt(varx*vary));
    return r;
}



double PCorr(arr *restrict X, arr *restrict Y, arr *restrict Z){
    double rxy_z;
    double rxy = Corr(X,Y);
    double rxz = Corr(X,Z);
    if ((rxy == *(double *)getMiss(X)) || (rxz == *(double *)getMiss(X))){
        rxy_z  = *(double *)getMiss(X);
        return rxy_z;
    }
    double ryz = Corr(Y,Z);
    rxy_z = (rxy-rxz*ryz)/(sqrt(1-rxz*rxz)*sqrt(1-ryz*ryz));
    return rxy_z;
}

double SPCorr(arr *restrict X, arr *restrict Y, arr *restrict Z){
    double rxy_z;
    double rxy = Corr(X,Y);
    double rxz = Corr(X,Z);
    if ((rxy == *(double *)getMiss(X)) || (rxz == *(double *)getMiss(X))){
        rxy_z  = *(double *)getMiss(X);
        return rxy_z;
    }
    double ryz = Corr(Y,Z);
    rxy_z = (rxy-rxz*ryz)/sqrt(1-ryz*ryz);
    return rxy_z;
}

double orthoRegr(arr *restrict X, arr *restrict Y){
    if (X->tlen != Y->tlen) { fprintf(stderr,"orthoRegr: Input arrays must have same total length\n"); exit(0); }

    double meanx = my_Mean(X);
    double meany = my_Mean(Y);
    arr Xdev   = fct1ar1s(wrap_sub, X,   meanx);
    arr Ydev   = fct1ar1s(wrap_sub, Y,   meany);
    arr Xdevsq = fct1ar1s(wrap_pow, &Xdev,2);
    arr Ydevsq = fct1ar1s(wrap_pow, &Ydev,2);
    arr XdevYdev = fct2ar(wrap_mult,&Xdev,&Ydev);

    double S2xx = my_Mean(&Xdevsq);
    double S2yy = my_Mean(&Ydevsq);
    double Sxy  = my_Mean(&XdevYdev);

    double S2xx_err = 1.0;          /*  Error variances assumed equal for now!  */
    double S2yy_err = 1.0;
    double eta = S2yy_err/S2xx_err;

    double num = (S2yy-eta*S2xx)+sqrt(pow(S2yy-eta*S2xx,2)+4*eta*Sxy*Sxy);
    /* if eta = inf then num = sqrt(pow(S2xx,2)+4*Sxy*Sxy)-S2xx */
    double den = 2*Sxy;

    double slope;
    if (den != 0){
        slope = num/den;
    } else {
        slope = *(double *)getMiss(X);
    }

    static int statdbg = 0;
    if ((slope > 2.0) && (statdbg)) {
        fputs("X\n",stderr);
        printArray(stderr,X);
        fputs("Y\n",stderr);
        printArray(stderr,Y);
        fputs("----\n",stderr);
        fprintf(stderr,"meanx = %g, meany = %g\n",meanx,meany);
        fputs("Xdev\n",stderr);
        printArray(stderr,&Xdev);
        fputs("Ydev\n",stderr);
        printArray(stderr,&Ydev);
        fputs("Xdevsq\n",stderr);
        printArray(stderr,&Xdevsq);
        fputs("Ydevsq\n",stderr);
        printArray(stderr,&Ydevsq);
        fputs("XdevYdev\n",stderr);
        printArray(stderr,&XdevYdev);
        fputs("----\n",stderr);
        fprintf(stderr,"S2xx = %g, S2yy = %g, Sxy = %g\n",S2xx,S2yy,Sxy);
        fprintf(stderr,"slope = %g\n",slope);
        fputs("----\n",stderr);
        fputs("----\n",stderr);
        statdbg = 0;
    }

    freeAr(&Xdev);
    freeAr(&Ydev);
    freeAr(&Xdevsq);
    freeAr(&Ydevsq);
    freeAr(&XdevYdev);
    return slope;
}

double Cov(arr * X, arr * Y){ 
    if (X->tlen != Y->tlen) { fprintf(stderr,"Cov: Input arrays must have same total length\n"); exit(0); }

    arr P = fct2ar(wrap_mult,X,Y);
    double meanp = my_Mean(&P);
    double meanx = my_Mean(X);
    double meany = my_Mean(Y);
    double cov = meanp - meanx*meany;
    freeAr(&P);
    return cov;
}

double Slope(arr * X, arr * Y){
    if (X->tlen != Y->tlen) { fprintf(stderr,"RegrRef: Input arrays must have same total length; X->tlen=%lld, Y->tlen=%lld\n",X->tlen,Y->tlen); exit(0); }

    double covxy = Cov(X,Y);
    double varx  = VarP(X);
    double a1 = covxy/varx;
    return a1;
}

double combined_predictor_index(arr *restrict X,arr *restrict r, arr *restrict p, double p_thresh){
    /* Based on Zhou et al. 2021, doi:10.1175/JCLI-D-20-0824.1 */
    /* How r and p are specified will change the result */
    /* All missing values should be removed */
    /* X, r, and p must be the same total length and of double format */

    typ_idx i, npos=0, nneg=0, n = X->tlen;
    double posX = 0.0;
    double negX = 0.0;
    for(i=0;i<n;++i){
        if (iDBL(p,i) > p_thresh){
            if (iDBL(r,i) > 0){
                posX += iDBL(X,i);
                ++npos;
            } else {
                negX += iDBL(X,i);
                ++nneg;
            }
        }
    }

    if (npos > 0) { posX /= (double)npos; }
    if (nneg > 0) { negX /= (double)nneg; }

    double Idx = posX - negX;

    return Idx;
}

void WMomentStats(arr *restrict X, arr *restrict W, double *WSum, double *wmean, double *stddev, double *skew, double *kurt){ 
    if (X->tlen != W->tlen) { fprintf(stderr,"WMomentStats: Input arrays must have same total length\n"); exit(0); }

    arr PmW = fct2ar(wrap_mult,X,W);
    double SumPmW = Sum(&PmW);
    double wsm    = Sum(W);
    if (WSum){ *WSum = wsm; }
    freeAr(&PmW);
   
    double wmn   = SumPmW/wsm;
    if (wmean){ *wmean = wmn; }
    
    if (stddev || skew || kurt){
        arr Dev   = fct1ar1s(wrap_sub,X,wmn);
        arr Dev2  = fct1ar1s(wrap_pow,&Dev,2.0);
        typ_idx ndev = countIF(&Dev2,gt,0.0);
        if (ndev > 3){
            arr WDev2 = fct2ar(wrap_mult,&Dev2,W);
            double sqsum = Sum(&WDev2);
            double stdtmp = sqrt(sqsum/wsm);
            if (stddev){ *stddev = stdtmp; }
            freeAr(&WDev2);
            
            if (ndev > 9){
                if (skew){
                    arr Dev3  = fct1ar1s(wrap_pow,&Dev,3.0);
                    arr WDev3 = fct2ar(wrap_mult,&Dev3,W);
                    double dev3sum = Sum(&WDev3);
                    double u3      = dev3sum/wsm;
                    *skew = u3/pow(stdtmp,3.0);
                    freeAr(&Dev3);
                    freeAr(&WDev3);
                }

                if (kurt){
                    arr Dev4  = fct1ar1s(wrap_pow,&Dev,4.0);
                    arr WDev4 = fct2ar(wrap_mult,&Dev4,W);
                    double quartsum = Sum(&WDev4);
                    double u4       = quartsum/wsm;
                    *kurt = u4/pow(stdtmp,4.0);
                    freeAr(&Dev4);
                    freeAr(&WDev4);
                }
            }
        }
        freeAr(&Dev);
        freeAr(&Dev2);
    }

    return;
}



arr RunningStatistic(double (*fct)(arr *),arr *restrict X,typ_idx len){
    typ_idx nX = X->tlen;
    typ_idx halflen = (len-1)/2;
    arr Xpct = ArrayFromList(X->n,DOUBLE,X->len);
    copyMiss(&Xpct,X);

    /* Set missing all points at end of array that are missing in original array */
    typ_idx i=0,nmissbeg=0,nmissend=0;
    double  miss  = *(double *)getMiss(&Xpct);
    double *pXpct = address_of_i(&Xpct,nX-1);
    double *pX    = address_of_i(X,    nX-1);
    for(i=nX-1; *pX == miss; --i,pX--){
        *pXpct-- = miss;
        ++nmissend;
    }
    
    /* Set missing all points at beg of array that are missing in original array */
    pXpct = pntr_of(&Xpct);
    pX    = pntr_of(X    );
    for(i=0; *pX == miss; ++i,pX++){
        *pXpct++ = miss;
        ++nmissbeg;
    }
    
    /* Set missing halflen points before first stat computation */
    for(; i < halflen+nmissbeg; ++i){
        *pXpct++ = miss;
    }
    
    /* Step through array and perform statistical operation */
    arr      Xloc  = assign1dtoNd(address_of_i(X ,i-halflen), 1, DOUBLE, len);
    double **pXloc = ppntr_of(&Xloc);
    arr Xtmp;
    for(; i < nX-halflen-nmissend; ++i){
        Xtmp = removeMissing(&Xloc); // This is likely an expensive operation!
        if (Xtmp.tlen > 0) {
            *pXpct++ = fct(&Xtmp);
        } else {
            *pXpct++ = miss;
        }
        freeAr(&Xtmp);
        (*pXloc)++;
    }
    
    for(; i < nX-nmissend; ++i){
        *pXpct++ = miss;
    }

    freeArShell(&Xloc);
    return Xpct;
}

arr RunningStatistic_End(double (*fct)(arr *),arr *restrict X,typ_idx len){
    typ_idx nX = X->tlen;
    arr Xpct = ArrayFromList(X->n,DOUBLE,X->len);
    copyMiss(&Xpct,X);
    
    /* Set missing all points at end of array that are missing in original array */
    typ_idx i=0,nmissbeg=0,nmissend=0;
    double  miss  = *(double *)getMiss(&Xpct);
    double *pXpct = address_of_i(&Xpct,nX-1);
    double *pX    = address_of_i(X,    nX-1);
    for(i=nX-1; *pX == miss; --i,pX--){
        *pXpct-- = miss;
        ++nmissend;
    }
    
    /* Set missing all points at beg of array that are missing in original array */
    pXpct = pntr_of(&Xpct);
    pX    = pntr_of(X    );
    for(i=0; *pX == miss; ++i,pX++){
        *pXpct++ = miss;
        ++nmissbeg;
    }
    
    /* Set missing len-1 points before first stat computation */
    for(; i < len+nmissbeg-1; ++i){
        *pXpct++ = miss;
    }
    
    /* Step through array and perform statistical operation */
    arr      Xloc  = assign1dtoNd(address_of_i(X ,i-len+1), 1, DOUBLE, len);
    double **pXloc = ppntr_of(&Xloc);
    arr Xtmp;
    for(; i < nX-nmissend; ++i){
        Xtmp = removeMissing(&Xloc); // This is likely an expensive operation!
        if (Xtmp.tlen > 0) {
            *pXpct++ = fct(&Xtmp);
        } else {
            *pXpct++ = miss;
        }
        freeAr(&Xtmp);
        (*pXloc)++;
    }

    freeArShell(&Xloc);
    return Xpct;
}

arr RunningStatistic_2_End(double (*fct)(arr *,arr *),arr *restrict X,arr *restrict Y,typ_idx len){
    typ_idx nX = X->tlen;
    arr Xpct = ArrayFromList(X->n,DOUBLE,X->len);
    copyMiss(&Xpct,X);

    /* Set missing all points at end of array that are missing in original array */
    typ_idx i=0,nmissbeg=0,nmissend=0;
    double  miss  = *(double *)getMiss(&Xpct);
    double  ymiss = *(double *)getMiss(Y);
    double *pXpct = address_of_i(&Xpct,nX-1);
    double *pX    = address_of_i(X,    nX-1);
    double *pY    = address_of_i(Y,    nX-1);
    for(i=nX-1; *pX == miss || *pY == ymiss; --i,pX--,pY--){
        *pXpct-- = miss;
        ++nmissend;
    }
    
    /* Set missing all points at beg of array that are missing in original array */
    pXpct = pntr_of(&Xpct);
    pX    = pntr_of(X    );
    pY    = pntr_of(Y    );
    for(i=0; *pX == miss || *pY == ymiss; ++i,pX++,pY++){
        *pXpct++ = miss;
        ++nmissbeg;
    }
    
    /* Set missing len-1 points before first stat computation */
    for(; i<len+nmissbeg-1; ++i){
        *pXpct++ = miss;
    }
    
    /* Step through array and perform statistical operation */
    arr Xloc = assign1dtoNd(address_of_i(X ,i-len+1), 1, DOUBLE, len);
    arr Yloc = assign1dtoNd(address_of_i(Y ,i-len+1), 1, DOUBLE, len);
    double **pXloc = ppntr_of(&Xloc);
    double **pYloc = ppntr_of(&Yloc);
    arr Xtmp,Ytmp;
    for(; i<nX-nmissend; ++i){
        removeMissing2Arrays(&Xtmp,&Ytmp,&Xloc,&Yloc); // This is likely an expensive operation!
        if (Xtmp.tlen > 0) {
            *pXpct++ = fct(&Xtmp,&Ytmp);
        } else {
            *pXpct++ = miss;
        }
        freeAr(&Xtmp);
        freeAr(&Ytmp);
        /* step through array pointers */
        (*pXloc)++;
        (*pYloc)++;
    }

    /* fputs("RunningStatistic_2_End: 1\n",stderr); */
    /* printArrayAllWHdr(stderr,&Xpct,"Xpct - ");   */
    freeArShell(&Xloc);
    freeArShell(&Yloc);
    return Xpct;
}

arr RunningStatistic_Extrap(double (*fct)(arr *),arr *restrict X,typ_idx len){
    typ_idx halflen = (len-1)/2;
    typ_idx nX    = X->tlen;
    arr Xpct = ArrayFromList(X->n,DOUBLE,X->len);
    copyMiss(&Xpct,X);
    arr Xtmp;

    typ_idx i=0,nmissbeg=0,nmissend=0;
    double miss = *(double *)getMiss(&Xpct);
    double *pXpct = address_of_i(&Xpct,nX-1);
    double *pX    = address_of_i(X,    nX-1);
    for(i=nX-1; *pX == miss; --i,pX--){
        *pXpct-- = miss;
        ++nmissend;
    }
    
    pXpct = pntr_of(&Xpct);
    pX    = pntr_of(X    );
    for(i=0; *pX == miss; ++i,pX++){
        *pXpct++ = miss;
        ++nmissbeg;
    }
    
    for(; i<halflen+nmissbeg; ++i){
        *pXpct++ = miss;
    }
    
    arr Xloc = assign1dtoNd(address_of_i(X ,i-halflen), 1, DOUBLE, len);
    double **pXloc = ppntr_of(&Xloc);
    for(; i<nX-halflen-nmissend; ++i){
        Xtmp = removeMissing(&Xloc); // This is likely an expensive operation!
        if (Xtmp.tlen > 0) {
            *pXpct++ = fct(&Xtmp);
        } else {
            *pXpct++ = miss;
        }
        freeAr(&Xtmp);
        (*pXloc)++;
    }
    freeArShell(&Xloc);
    /*
    for(; i<nX-nmissend; ++i){
        *pXpct++ = miss;
    }
    */
    
    /* Extrapolate beginning */
    typ_idx ibeg_regr = nmissbeg+halflen;
    typ_idx len_regr  = halflen+1;
    typ_idx iend_regr = ibeg_regr+len_regr-1;
    Xloc = assign1dtoNd(address_of_i(&Xpct,ibeg_regr), 1, DOUBLE, len_regr);
    arr Tloc = getCoordArray(ibeg_regr, iend_regr, len_regr);

    double m, b, rsq, mad;
    RegrRef_TheilSen(&Tloc, &Xloc, &m, &b, &rsq, &mad);
    freeArShell(&Xloc);
    freeAr(&Tloc);

    for(i=nmissbeg;i<ibeg_regr;++i){ iDBL(&Xpct,i) = m*i + b; }

    /* Extrapolate end */
    iend_regr = nX-halflen-nmissend-1;
    ibeg_regr = iend_regr-len_regr+1;
    Xloc = assign1dtoNd(address_of_i(&Xpct,ibeg_regr), 1, DOUBLE, len_regr);
    Tloc = getCoordArray(ibeg_regr, iend_regr, len_regr);

    RegrRef_TheilSen(&Tloc, &Xloc, &m, &b, &rsq, &mad);
    freeArShell(&Xloc);
    freeAr(&Tloc);

    for(i=iend_regr+1;i<nX-nmissend;++i){ iDBL(&Xpct,i) = m*i + b; }

    /* fprintf(stderr,"[m,b,rsq,mad]=[%g,%g,%g,%g]\n",m,b,rsq,mad); */
    return Xpct;
}

arr RunningRegr(arr *restrict X,typ_idx len){
    typ_idx nX    = X->tlen;
    arr Xpct = ArrayFromList(X->n,DOUBLE,X->len);
    
    arr T = getCoordArray(0, (double)(nX-1), nX);

    copyMiss(&Xpct,X);
    typ_idx i=0,nmissbeg=0,nmissend=0;
    
    /* Set beginning and end missing points to missing in resulting array */
    double miss   = *(double *)getMiss(&Xpct);
    double *pXpct = address_of_i(&Xpct,nX-1);
    double *pX    = address_of_i(X,    nX-1);
    for(i=nX-1; *pX == miss; --i,pX--){
        *pXpct-- = miss;
        ++nmissend;
    }
    
    pXpct = pntr_of(&Xpct);
    pX    = pntr_of(X    );
    for(i=0; *pX == miss; ++i,pX++){
        *pXpct++ = miss;
        ++nmissbeg;
    }
    
    /* Fill in first len period of data with first regression */
    arr Xloc = assign1dtoNd(address_of_i(X ,i), 1, DOUBLE, len);
    arr Tloc = assign1dtoNd(address_of_i(&T,i), 1, DOUBLE, len);
    arr Xtmp,Ttmp;
    double m, b, rsq, mad;
    removeMissing2Arrays(&Xtmp,&Ttmp,&Xloc,&Tloc);
    if (Xtmp.tlen > 0) {
        m = miss; b = miss; rsq = miss; mad = miss;
        RegrRef_TheilSen(&Ttmp, &Xtmp, &m, &b, &rsq, &mad);
        if (m == miss){
            for(; i<len+nmissbeg; ++i){
                *pXpct++ = miss;
            }
        } else {
            for(; i<len+nmissbeg; ++i){
                *pXpct++ = m*i + b;
            }
        }
    } else {
        for(;i<len+nmissbeg;++i){
            *pXpct++ = miss;
        }
    }
    freeAr(&Xtmp);
    freeAr(&Ttmp);
    
    /* Fill in remaining points with end point of regression to represent end of period index */
    Xloc = assign1dtoNd(address_of_i(X ,i-len+1), 1, DOUBLE, len);
    Tloc = assign1dtoNd(address_of_i(&T,i-len+1), 1, DOUBLE, len);
    double **pXloc = ppntr_of(&Xloc);
    double **pTloc = ppntr_of(&Tloc);
    for(;i<nX-nmissend;++i){
        removeMissing2Arrays(&Xtmp,&Ttmp,&Xloc,&Tloc);
        if (Xtmp.tlen > 0) {
            m = miss; b = miss; rsq = miss; mad = miss;
            RegrRef_TheilSen(&Ttmp, &Xtmp, &m, &b, &rsq, &mad);
            if (m == miss){
                *pXpct++ = miss;
            } else {
                *pXpct++ = m*i + b;
            }
        } else {
            *pXpct++ = miss;
        }
        freeAr(&Xtmp);
        freeAr(&Ttmp);
        (*pXloc)++;
        (*pTloc)++;
    }

    freeArShell(&Xloc);
    freeArShell(&Tloc);
    
    freeArShell(&T);
    return Xpct;
}

arr RunningMean(arr *restrict X,typ_idx len){
    return RunningStatistic(my_Mean,X,len);
}

arr RunningMedian(arr *restrict X,typ_idx len){
    return RunningStatistic_Extrap(Median,X,len);
}

arr RunningMean_End(arr *restrict X,typ_idx len){
    return RunningStatistic_End(my_Mean,X,len);
}

arr RunningSlope_End(arr *restrict X,arr *restrict Y,typ_idx len){
    return RunningStatistic_2_End(Slope,X,Y,len);
}

arr RunningStatistic_Beg(double (*fct)(arr *),arr *restrict X,typ_idx len){
    typ_idx nX = X->tlen;
    arr Xpct = ArrayFromList(X->n,DOUBLE,X->len);
    copyMiss(&Xpct,X);
    
    /* Set missing all points at end of array that are missing in original array */
    typ_idx i=0,nmissbeg=0,nmissend=0;
    double  miss  = *(double *)getMiss(&Xpct);
    double *pXpct = address_of_i(&Xpct,nX-1);
    double *pX    = address_of_i(X,    nX-1);
    for(i=nX-1; *pX == miss; --i,pX--){
        *pXpct-- = miss;
        ++nmissend;
    }
    
    /* Set missing len-1 points after last stat computation */
    for(; i > nX-nmissend-len; --i){
        *pXpct-- = miss;
    }
    
    /* Set missing all points at beg of array that are missing in original array */
    pXpct = pntr_of(&Xpct);
    pX    = pntr_of(X    );
    for(i=0; *pX == miss; ++i,pX++){
        *pXpct++ = miss;
        ++nmissbeg;
    }
    
    /* Step through array and perform statistical operation */
    arr      Xloc  = assign1dtoNd(address_of_i(X ,i-len+1), 1, DOUBLE, len);
    double **pXloc = ppntr_of(&Xloc);
    arr Xtmp;
    for(; i < nX-nmissend; ++i){
        Xtmp = removeMissing(&Xloc); // This is likely an expensive operation!
        if (Xtmp.tlen > 0) {
            *pXpct++ = fct(&Xtmp);
        } else {
            *pXpct++ = miss;
        }
        freeAr(&Xtmp);
        (*pXloc)++;
    }

    freeArShell(&Xloc);
    return Xpct;
}

arr RunningMean_Beg(arr *restrict X,typ_idx len){
    return RunningStatistic_Beg(my_Mean,X,len);
}


arr RunningWeightedPercentile(arr *X,arr *Xbar,arr *W,double perc){
/*  Xbar should be the weighted running mean of X, and W should be the same filter to apply */
    typ_idx nX = X->tlen,nW = W->tlen;
    typ_idx halflen = (nW-1)/2;
    
    arr Xanom = fct2ar(wrap_sub,X,Xbar);
    copyMiss(&Xanom,X);
    
    arr Xpct = ArrayFromList(X->n,DOUBLE,X->len);
    copyMiss(&Xpct,X);
    
    arr Xanomtmp = assign1dtoNd(pntr_of(&Xanom), 1, DOUBLE, nW); /* attach pointer with set_pntr */
    copyMiss(&Xanomtmp,X);
    
    double **pXanomtmp = ppntr_of(&Xanomtmp); /* needed to increment pntr of Xanomtmp */
    double *pXpct      = pntr_of(&Xpct);
    double xmiss       = *(double *)getMiss(&Xpct);
    
    typ_idx i;
    for(i=0; i<halflen; ++i){
        *pXpct++ = xmiss;
    }
    
    double *pXbar = address_of_i(Xbar,i);
    double xbmiss = *(double *)getMiss(Xbar);
    for(; i<nX-halflen; ++i,(*pXanomtmp)++,pXbar++){
        if (*pXbar == xbmiss){
            *pXpct++ = xmiss;
        } else {
            if (isAnyMiss(&Xanomtmp)){
                *pXpct++ = xmiss;
            } else {
                *pXpct++ = calcValatPercWeighted(&Xanomtmp, W, perc) + *pXbar;
            }
        }
    }
    for(; i<nX; ++i){ *pXpct++ = xmiss; }

    freeAr(&Xanom);
    freeArShell(&Xanomtmp);
    return Xpct;
}

arr RunningWeightedPercentiles(arr *X,arr *Xbar,arr *W,arr *perc){
/*  Xbar should be the weighted running mean of X, and W should be the same filter to apply */
    typ_idx nX = X->tlen,nW = W->tlen,nperc = perc->tlen;
    typ_idx halflen = (nW-1)/2;
    
    arr Xanom = fct2ar(wrap_sub,X,Xbar);
    copyMiss(&Xanom,X);
    
    typ_idx  ndim_O = X->n+1;
    typ_idx *olen   = malloc(ndim_O*sizeof *olen);
    for (typ_idx i=0; i < X->n; ++i){
        olen[i] = X->len[i];
    }
    olen[X->n] = nperc;
    arr     Xpct = ArrayFromList(ndim_O,DOUBLE,olen);
    copyMiss(&Xpct,X);
    
    arr Xanomtmp = assign1dtoNd(pntr_of(&Xanom), 1, DOUBLE, nW); /* attach pointer with set_pntr */
    copyMiss(&Xanomtmp,X);
    
    double **pXanomtmp = ppntr_of(&Xanomtmp); /* needed to increment pntr of Xanomtmp */
    double  *pXpct     = pntr_of(&Xpct);
    double   xmiss     = *(double *)getMiss(&Xpct);
    
    typ_idx i;
    for(i=0; i<halflen; ++i){
        for(typ_idx j=0; j<nperc; ++j){
            *pXpct++ = xmiss;
        }
    }
    
    double *pXbar = address_of_i(Xbar,i);
    double xbmiss = *(double *)getMiss(&Xpct);
    double *pperc = NULL;
    for(; i<nX-halflen; ++i,(*pXanomtmp)++,pXbar++){
        if (*pXbar == xbmiss){
            for(typ_idx j=0; j<nperc; ++j){
                *pXpct++ = xmiss;
            }
        } else {
            if (isAnyMiss(&Xanomtmp)){
                for(typ_idx j=0; j<nperc; ++j){
                    *pXpct++ = xmiss;
                }
            } else {
                pperc = pntr_of(perc);
                for(typ_idx j=0; j<nperc; ++j){
                    *pXpct++ = calcValatPercWeighted(&Xanomtmp, W, *pperc++) + *pXbar;
                }
            }
        }
    }
    for(; i<nX; ++i){
        for(typ_idx j=0; j<nperc; ++j){
            *pXpct++ = xmiss;
        }
    }

    free(olen);
    freeAr(&Xanom);
    freeArShell(&Xanomtmp);
    return Xpct;
}

arr RunningWeightedPercentileNoMean(arr *X,arr *W,double perc){
    typ_idx nX = X->tlen,nW = W->tlen;
    typ_idx halflen = (nW-1)/2;

    arr Xpct = ArrayFromList(X->n,DOUBLE,X->len);
    copyMiss(&Xpct,X);
    
    arr Xtmp = assign1dtoNd(pntr_of(X), 1, DOUBLE, nW); /* attach pointer with set_pntr */
    copyMiss(&Xtmp,X);
    
    double **pXtmp = ppntr_of(&Xtmp);
    double *pXpct      = pntr_of(&Xpct);
    double xmiss       = *(double *)getMiss(&Xpct);
    
    typ_idx i;
    for(i=0; i<halflen; ++i){
        *pXpct++ = xmiss;
    }
    
    for(; i<nX-halflen; ++i,(*pXtmp)++){
        if (isAnyMiss(&Xtmp)){
            *pXpct++ = xmiss;
        } else {
            *pXpct++ = calcValatPercWeighted(&Xtmp, W, perc);
        }
    }
    for(; i<nX; ++i){
        *pXpct++ = xmiss;
    }

    freeArShell(&Xtmp);
    return Xpct;
}

arr RunningWeightedMean(arr *X,arr *W){
    /* fputs("RunningWeightedMean: 1\n",stderr); */
    typ_idx nX = X->tlen,nW = W->tlen;
    typ_idx halflen = (nW-1)/2;

    arr Out  = ArrayFromList(X->n,DOUBLE,X->len);
    copyMiss(&Out,X);
    
    double  *pOut  = pntr_of(&Out);
    double   xmiss = *(double *)getMiss(&Out);
    typ_idx i;
    for(i=0; i<halflen; ++i){
        *pOut++ = xmiss;
    }
    
    arr Xtmp = assign1dtoNd(pntr_of(X), 1, DOUBLE, nW); /* attach pointer with set_pntr */
    copyMiss(&Xtmp,X);
    
    double **pXtmp = ppntr_of(&Xtmp);
    
    for(; i<nX-halflen; ++i,(*pXtmp)++){
        if (isAnyMiss(&Xtmp)){
            *pOut++ = xmiss;
        } else {
            *pOut++ = wMean(&Xtmp, W);
        }
    }

    for(; i<nX; ++i){
        *pOut++ = xmiss;
    }

    freeArShell(&Xtmp);
    return Out;
}


#endif
