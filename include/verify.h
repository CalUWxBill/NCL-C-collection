/* Created by Bill Scheftic */
/*
 *  Functions for verifying ensemble forecasts
 *  - verify_ensemble_forecast calculates a suite of quantities from an
 *    input set of ensemble forecasts and observations.
 *  - verify_ensemble_forecast_1 calculates some basic metrics on one ensemble forecast
 */
#ifndef  _VERIFY_H_
#define  _VERIFY_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <arraymath2.h>
#include <print_arrays2.h>
#include <sort2.h>
#include <stats2.h>
#include <grid2.h>
#include <pdf_stats.h>
#include <gsl/gsl_statistics.h>

typedef struct { arr a, b, c, d; }contingency;

typedef struct { arr msetst, mseadj, biastst, biasadj; }score;

typedef struct { arr p_y, p_y_o1, p_y_o2, p_o1_y; }probs;


double skillScore(double,double);
double findBiasImp(arr *,arr *,arr *);
double cdfRPS_one(arr *,double,gridnd *);
double calcRPS(arr *,arr *,arr *,gridnd *);
double calcRPSClim(arr *,arr *,gridnd *);
arr findFcstProb(arr *,arr *,double,gridnd *);
arr findFcstsatPerc(arr *,arr *,gridnd *,typ_idx);
arr findQpfAdjust(arr *,arr *,double);
void initProb(probs*,typ_idx,typ_idx);
void initContingency(contingency*,typ_idx);
void calcContingDet(arr *,arr *,double,typ_idx,contingency*);
void calcContingPrb(arr *,arr *,double,typ_idx,contingency*);
void findProbabilities(arr *,arr *,arr *,typ_idx,typ_idx,probs*);
void findProbHistCounts(arr *,arr *,arr *,double,arr*,arr*,arr*);


double skillScore(double fcst,double ref){
    return 1.0-fcst/ref;
}

double invertSkillScore(double ss){
    return -ss/(1-ss);
}

double wrap_skillScore2(input_args *args){
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
    if (y == 0){
        return *(double *)args->missval;
    } else {
        return skillScore(x,y);
    }
}

double findBiasImp(arr *restrict fcst,arr *restrict ref,arr *restrict obs){
	double fcstbias = calcBias(fcst,obs);
	double refbias = calcBias(ref,obs);
	double biasimp = skillScore(fabs(fcstbias),fabs(refbias));
	return biasimp; 
}

double ensRPS_One(arr *restrict fcstens,double ob){
    typ_idx i;
    double fcstcur,Fo_y,F_y,rps,rps_sum = 0.0;
    int nens = fcstens->tlen;
    if (nens < 1){
        freeAr(&fcstens);
        return *(double *)getMiss(fcstens);
    }
    arr ens_sorted = qsortArray(fcstens);
    
    double Dy1,Dy2;
    double fcstnxt = DBL(&ens_sorted,(typ_idx)0);
    if (ob < fcstnxt) {
        Dy1 = fcstnxt-ob;
        rps = Dy1;
        rps_sum += rps;
    /*  fprintf(stderr,"ensRPS_One: bef F_y=%g, rps_sum=%g, rps=%g, ob=%g, fcstcur=%g, fcstnxt=%g\n"
            ,F_y,rps_sum,rps,ob,fcstcur,fcstnxt); */
    }
    for (i=0;i<nens-1;i++){
        fcstcur = fcstnxt;
        fcstnxt = DBL(&ens_sorted,i+1);
        F_y = (i+1.0)/(double)nens;
        if (fcstnxt < ob) {
            Fo_y = 0.0;
            Dy1 = fcstnxt-fcstcur;
            rps = (F_y-Fo_y)*(F_y-Fo_y)*Dy1;
        } else if (fcstcur >= ob) {
            Fo_y = 1.0;
            Dy1 = fcstnxt-fcstcur;
            rps = (F_y-Fo_y)*(F_y-Fo_y)*Dy1;
        } else {
            Dy1 = ob-fcstcur;
            Dy2 = fcstnxt-ob;
            rps = F_y*F_y*Dy1 + (F_y-1.0)*(F_y-1.0)*Dy2;
        }
        rps_sum += rps;
    /*  fprintf(stderr,"ensRPS_One: %3d F_y=%g, rps_sum=%g, rps=%g, ob=%g, fcstcur=%g, fcstnxt=%g\n"
            ,i,F_y,rps_sum,rps,ob,fcstcur,fcstnxt); */
    }
    if (fcstnxt < ob) {
        Dy1 = ob-fcstnxt;
        rps = Dy1;
        rps_sum += rps;
    /*  fprintf(stderr,"ensRPS_One: aft F_y=%g, rps_sum=%g, rps=%g, ob=%g, fcstcur=%g, fcstnxt=%g\n"
            ,F_y,rps_sum,rps,ob,fcstcur,fcstnxt); */
    }
    freeAr(&ens_sorted);
    
    return rps_sum;
}

double wrap_ensRPS_One2(input_args *args){
    return wrap_dbl_1ar1d(ensRPS_One,args,1);
}

double cdfRPS_one(arr *restrict cdf,double ob,gridnd *restrict grd){
    typ_idx ii;
    double rps = 0;
    double result_i = (ob-grd->bcrd[0])/(grd->dcrd[0]);
    typ_idx obs_i = myRound2(result_i); /* myRound used in past */
    double Dy1,Dy2,fcst0,F_y,Fo_y;
    if (obs_i < 0) {
        fcst0 = grd->bcrd[0] - 0.5*grd->dcrd[0];
        rps += fcst0-ob;
    } else if (obs_i >= grd->len[0]) {
        fcst0 = grd->bcrd[0] + (grd->len[0]-0.5)*grd->dcrd[0];
        rps += ob-fcst0;
    }
    for (ii=0;ii<grd->len[0];ii++){
        fcst0 = grd->bcrd[0] + grd->dcrd[0]*ii;
        F_y = cdf_PercatVal(cdf,fcst0,grd);
        if (ii >= obs_i) {
            Fo_y = 1.0;
            rps += (F_y-Fo_y)*(F_y-Fo_y)*grd->dcrd[0];
        } else if (ii == obs_i) {
            Dy1 = fabs(ob-(fcst0-grd->dcrd[0]/2));
            Dy2 = fabs((fcst0+grd->dcrd[0]/2)-ob);
            rps += F_y*F_y*Dy1 + (F_y-1.0)*(F_y-1.0)*Dy2;
        } else {
            Fo_y = 0.0;
            rps += (F_y-Fo_y)*(F_y-Fo_y)*grd->dcrd[0];
        }
    }
    return rps;
}

double calcRPS(arr *restrict ccdf,arr *restrict fcst,arr *restrict obs,gridnd *restrict grd){
	typ_idx i;
	double rps,rps_sum = 0;
    double val;
	arr cdf;
	for(i=0;i<fcst->len[0];i++) {
        val = iDBL(fcst,i);
		cdf = findSliceOnGrid(ccdf,grd,&val,0);
        rps_sum += cdfRPS_one(&cdf,DBL(obs,i),grd);
		freeAr(&cdf);
	}
	rps = rps_sum/fcst->len[0];
	return rps;
}

double calcRPSClim(arr *restrict cdf_clim,arr *restrict obs,gridnd *restrict grd){
	typ_idx i;
	double rps,rps_sum = 0;
	for(i=0;i<obs->len[0];i++) {
        rps_sum += cdfRPS_one(cdf_clim,DBL(obs,i),grd);
	}
	rps = rps_sum/obs->len[0];
	return rps;
}


arr findFcstProb(arr *restrict ccdf,arr *restrict fcst,double fcst0,gridnd *restrict grd){
	typ_idx i;
	arr cdf;
    double val;
	arr fcst_prob = Array(1,DOUBLE,fcst->tlen);
	for(i=0;i<fcst->tlen;i++) {
        val = iDBL(fcst,i);
		cdf = findSliceOnGrid(ccdf,grd,&val,0);
		DBL(&fcst_prob,i) = 1-cdf_PercatVal(&cdf,fcst0,grd);
		freeAr(&cdf);
	}
	return fcst_prob;
}

arr findFcstsatPerc(arr *restrict ccdf,arr *restrict fcst,gridnd *restrict grd,typ_idx numpercs){
	typ_idx i;
	arr cdf, tmpvals;
    double val;
    typ_idx *idx = init0(2, TYPIDX);
	arr fcst_cdf = Array(2,DOUBLE,fcst->tlen,numpercs);
	for(i=0;i<fcst->tlen;i++,idx[0]++) {
        val = iDBL(fcst,i);
		cdf = findSliceOnGrid(ccdf,grd,&val,0);
        tmpvals = findValsatPercs(&cdf,grd,numpercs);
        assignPart2(&fcst_cdf,&tmpvals,1,idx);
		freeAr(&cdf);
		freeAr(&tmpvals);
	}
	return fcst_cdf;
}

arr findQpfAdjust(arr *restrict fcst,arr *restrict mean,double dbin){
	typ_idx i;
	arr fcst_adj = Array(1,DOUBLE,fcst->len[0]);
	double fcsti;
	typ_idx fcstint;

	for(i=0;i<fcst->len[0];i++) {
		fcsti = (DBL(fcst,i)/dbin)-0.5;
		if (fcsti < 0) { fcstint = 0;
		} else {
			fcstint = myRound2(fcsti);
		}
		DBL(&fcst_adj,i) = DBL(mean,fcstint);
	}

	return fcst_adj;
}


void initProb(probs *prb,typ_idx y,typ_idx x){
	prb->p_y    = Array(2,DOUBLE,y,x);
	prb->p_y_o1 = Array(2,DOUBLE,y,x);
	prb->p_y_o2 = Array(2,DOUBLE,y,x);
	prb->p_o1_y = Array(2,DOUBLE,y,x);
	return;
}

void initContingency(contingency *cont,typ_idx y){
	cont->a = Array(1,DOUBLE,y);
	cont->b = Array(1,DOUBLE,y);
	cont->c = Array(1,DOUBLE,y);
	cont->d = Array(1,DOUBLE,y);
	return;
}

void calcContingDet(arr *restrict fcsttst,arr *restrict obstst,double fcst0,typ_idx j,contingency *contdet){
	typ_idx i,a=0,b=0,c=0,d=0,n=0;
	for(i=0;i<obstst->len[0];i++){
		if (DBL(obstst,i) > fcst0){
			if (DBL(fcsttst,i) > fcst0){ a++; } else { c++; } 
		} else {
			if (DBL(fcsttst,i) > fcst0){ b++; } else { d++; } 
		}
	}
	n = a + b + c + d;
	DBL(&contdet->a,j) = (double)a/n;
	DBL(&contdet->b,j) = (double)b/n;
	DBL(&contdet->c,j) = (double)c/n;
	DBL(&contdet->d,j) = (double)d/n;

	return;
}

void calcContingPrb(arr *restrict fcst_cpdf,arr *restrict obstst,double fcst0,typ_idx j,contingency *contprb){
	typ_idx i,k,a=0,b=0,c=0,d=0,n=0;
	for(i=0;i<obstst->len[0];i++){
		if (DBL(obstst,i) > fcst0){
			for(k=0;k<fcst_cpdf->len[0];k++){
				if (DBL(fcst_cpdf,k,i) > fcst0){ a++; } else { c++; } 
			}
		} else {
			for(k=0;k<fcst_cpdf->len[0];k++){
				if (DBL(fcst_cpdf,k,i) > fcst0){ b++; } else { d++; } 
			}
		}
	}
	n = a + b + c + d;
	DBL(&contprb->a,j) = (double)a/n;
	DBL(&contprb->b,j) = (double)b/n;
	DBL(&contprb->c,j) = (double)c/n;
	DBL(&contprb->d,j) = (double)d/n;

	return;
}

void findProbabilities(arr *restrict prob_hist,arr *restrict o1_y,arr *restrict o2_y,typ_idx numdays,typ_idx j,probs *prb){
	typ_idx i;
	typ_idx rlblty_res = prob_hist->len[0];
	for(i=0;i<rlblty_res;i++) {
		DBL(&prb->p_y,   j,i) = DBL(prob_hist,i)/numdays;
		DBL(&prb->p_y_o1,j,i) = DBL(o1_y,i)/numdays;
		DBL(&prb->p_y_o2,j,i) = DBL(o2_y,i)/numdays;
		DBL(&prb->p_o1_y,j,i) = DBL(&prb->p_y_o1,j,i)/DBL(&prb->p_y,j,i);
	}
	return;
}

void findProbHistCounts(arr *restrict fcst_prob,arr *restrict fcsttst,arr *restrict obstst,double fcst0,arr *prob_hist,arr *o1_y,arr *o2_y){
	typ_idx i,fcst_bin;
	typ_idx rlblty_res = prob_hist->tlen;
	for(i=0;i<fcsttst->len[0];i++) {
		fcst_bin = myRound2(DBL(fcst_prob,i)*(rlblty_res-1));
		(iDBL(prob_hist,fcst_bin))++;
		if (iDBL(obstst,i) > fcst0) { (iDBL(o1_y,fcst_bin))++; } else { (iDBL(o2_y,fcst_bin))++; }
	}
	return;
}


void verify_ensemble_forecast(
    /* input */
     arr *restrict fcst       /* Forecast ensembles fcst[time][ensembles] */
    ,arr *restrict obs        /* Observation obs[time] */
    /* Output */
    ,arr *ENSM                /* Ensemble mean of each forecast */
    ,arr *ENSMed              /* Ensemble median of each forecast */
    ,arr *ENS_Spread          /* Ensemble spread of each forecast */
    ,arr *ENS_AE              /* Absoluter error between ENSM and obs */
    ,double *obs_Mean         /* my_Mean observation (climatology) */
    ,double *obs_Med          /* Median observation */
    ,double *Climo_MAE        /* my_Mean absolute error of climatology */
    ,double *ENSM_MAE         /* my_Mean absolute error of ensemble mean */
    ,double *Climo_MSE        /* my_Mean square error of climatology */
    ,double *ENSM_MSE         /* my_Mean square error of ensemble mean */
    ,double *ENSM_SS_MAE      /* MAE-based skill score of ENSM */
    ,double *SS_MAE_min       /* Minimum MAE-based skill score amongst ensemble members */
    ,double *SS_MAE_Q1        /* 1st quartile MAE-based skill score amongst ensemble members */
    ,double *SS_MAE_med       /* Median MAE-based skill score amongst ensemble members */
    ,double *SS_MAE_Q3        /* 3rd quartile MAE-based skill score amongst ensemble members */
    ,double *SS_MAE_max       /* Maximum MAE-based skill score amongst ensemble members */
    ,double *ENSM_SS_MSE      /* MSE-based skill score of ENSM */
    ,double *SS_MSE_min       /* Minimum MSE-based skill score amongst ensemble members */
    ,double *SS_MSE_Q1        /* 1st quartile MSE-based skill score amongst ensemble members */
    ,double *SS_MSE_med       /* Median MSE-based skill score amongst ensemble members */
    ,double *SS_MSE_Q3        /* 3rd quartile MSE-based skill score amongst ensemble members */
    ,double *SS_MSE_max       /* Maximum MSE-based skill score amongst ensemble members */
    ,double *Climo_MedAE      /* Median absolute error of climatology */
    ,double *ENSM_MedAE       /* Median absolute error of ensemble mean */
    ,double *ENSM_SS_MedAE    /* MedAE-based skill score of ENSM */
    ,double *Climo_MedSE      /* Median square error of climatology */
    ,double *ENSM_MedSE       /* Median square error of ensemble mean */
    ,double *ENSM_SS_MedSE    /* MedSE-based skill score of ENSM */
    ,double *ENSMed_MedAE     /* Median absolute error of ENSMed */
    ,double *ENSMed_SS_MedAE  /* MedAE-based skill score of ENSMed */
    ,double *ENSMed_MedSE     /* Median square error of ENSMed */
    ,double *ENSMed_SS_MedSE  /* MedSE-based skill score of ENSMed */
    ,double *ENSMed_MAE       /* my_Mean absolute error of ENSMed */
    ,double *ENSMed_MSE       /* my_Mean square error of ENSMed */
    ,double *ENSMed_SS_MAE    /* MAE-based skill score of ENSMed */
    ,double *ENSMed_SS_MSE    /* MSE-based skill score of ENSMed */
    ,double *Climo_RPS_Mean   /* Ranked probability score mean of climatology */
    ,double *fcst_RPS_Mean    /* Ranked probability score mean of ensemble forecasts */
    ,double *fcst_RPSS        /* RPS-based skill score (RPSS) of ensemble forecasts */
    ,double *Climo_RPS_Med    /* Ranked probability score median of climatology */
    ,double *fcst_RPS_Med     /* Ranked probability score median of ensemble forecasts */
    ,double *fcst_RPSSmed     /* RPS_med-based skill score of ensemble forecasts */
    ,double *ENSM_Bias        /* Absolute bias of ensemble mean */
    ,double *ENSM_RelBias     /* Relative or percent bias of ensemble mean */
    ,double *ENSM_Corr        /* Correlation of ensemble mean with observations */
    ,double *ENSM_SpCr        /* Spearman rank correlation of ensemble mean with observations */
    ,double *ENSMed_Bias      /* Absolute bias of ensemble median */
    ,double *ENSMed_RelBias   /* Relative or percent bias of ensemble median */
    ,double *ENSMed_Corr      /* Correlation of ensemble median with observations */
    ,double *var_fcst         /* Overall forecast variance */
    ,double *var_obs          /* Overall observed variance */
    ,double *var_ensm         /* variance of ensemble means */
    ,double *var_ensmed       /* variance of ensemble medians */
    ,double *fcst_mean        /* Overall forecast mean */
    ,typ_idx *nvalid          /* Number of valid observation pairs */
    ){
    /* Save missing values passed in */
    double miss_obs_Mean        = *obs_Mean;
    double miss_obs_Med         = *obs_Med;
    double miss_Climo_MAE       = *Climo_MAE;
    double miss_ENSM_MAE        = *ENSM_MAE;
    double miss_Climo_MSE       = *Climo_MSE;
    double miss_ENSM_MSE        = *ENSM_MSE;
    double miss_ENSM_SS_MAE     = *ENSM_SS_MAE;
    double miss_SS_MAE_min      = *SS_MAE_min;
    double miss_SS_MAE_Q1       = *SS_MAE_Q1;
    double miss_SS_MAE_med      = *SS_MAE_med;
    double miss_SS_MAE_Q3       = *SS_MAE_Q3;
    double miss_SS_MAE_max      = *SS_MAE_max;
    double miss_ENSM_SS_MSE     = *ENSM_SS_MSE;
    double miss_SS_MSE_min      = *SS_MSE_min;
    double miss_SS_MSE_Q1       = *SS_MSE_Q1;
    double miss_SS_MSE_med      = *SS_MSE_med;
    double miss_SS_MSE_Q3       = *SS_MSE_Q3;
    double miss_SS_MSE_max      = *SS_MSE_max;
    double miss_Climo_MedAE     = *Climo_MedAE;
    double miss_ENSM_MedAE      = *ENSM_MedAE;
    double miss_ENSM_SS_MedAE   = *ENSM_SS_MedAE;
    double miss_Climo_MedSE     = *Climo_MedSE;
    double miss_ENSM_MedSE      = *ENSM_MedSE;
    double miss_ENSM_SS_MedSE   = *ENSM_SS_MedSE;
    double miss_ENSMed_MedAE    = *ENSMed_MedAE;
    double miss_ENSMed_SS_MedAE = *ENSMed_SS_MedAE;
    double miss_ENSMed_MedSE    = *ENSMed_MedSE;
    double miss_ENSMed_SS_MedSE = *ENSMed_SS_MedSE;
    double miss_ENSMed_MAE      = *ENSMed_MAE;
    double miss_ENSMed_MSE      = *ENSMed_MSE;
    double miss_ENSMed_SS_MAE   = *ENSMed_SS_MAE;
    double miss_ENSMed_SS_MSE   = *ENSMed_SS_MSE;
    double miss_Climo_RPS_Mean  = *Climo_RPS_Mean;
    double miss_fcst_RPS_Mean   = *fcst_RPS_Mean;
    double miss_fcst_RPSS       = *fcst_RPSS;
    double miss_Climo_RPS_Med   = *Climo_RPS_Med;
    double miss_fcst_RPS_Med    = *fcst_RPS_Med;
    double miss_fcst_RPSSmed    = *fcst_RPSSmed;
    double miss_ENSM_Bias       = *ENSM_Bias;
    double miss_ENSM_RelBias    = *ENSM_RelBias;
    double miss_ENSM_Corr       = *ENSM_Corr;
    double miss_ENSM_SpCr       = *ENSM_SpCr;
    double miss_ENSMed_Bias     = *ENSMed_Bias;
    double miss_ENSMed_RelBias  = *ENSMed_RelBias;
    double miss_ENSMed_Corr     = *ENSMed_Corr;
    double miss_var_fcst        = *var_fcst;
    double miss_var_obs         = *var_obs;
    double miss_var_ensm        = *var_ensm;
    double miss_var_ensmed      = *var_ensmed;
    double miss_fcst_mean       = *fcst_mean;
    *ENSM       = arStatArg1ar(wrap_Mean,fcst,1);
    *ENSMed     = arStatArg1ar(wrap_Median,fcst,1);
    *ENS_Spread = arStatArg1ar(wrap_stdDevS,fcst,1);
    *ENS_AE     = fct2ar(wrap_devAbs,ENSM,obs);

    arr obs_nm,ENSM_nm,ENSMed_nm;
    removeMissingNArrays(3,&obs_nm,&ENSM_nm,&ENSMed_nm,obs,ENSM,ENSMed);
    /*
    int printout = 0;
    if ((Zeros(&obs_nm) == 1) || (Zeros(&ENSM_nm) == 1)){
        printArrayFmtAllWHdr(stderr,fcst,       "%5f","fcst - ");
        printArrayFmtAllWHdr(stderr,obs,        "%5f","obs - ");
        printArrayFmtAllWHdr(stderr,&ENSM_nm,    "%5f","ENSM_nm - ");
        printArrayFmtAllWHdr(stderr,&ENSMed_nm,  "%5f","ENSMed_nm - ");
        printArrayFmtAllWHdr(stderr,&obs_nm,     "%5f","obs_nm - ");
        printArrayFmtAllWHdr(stderr,ENSM,      "%5f","ENSM - ");
        printArrayFmtAllWHdr(stderr,ENSMed,    "%5f","ENSMed - ");
        printArrayFmtAllWHdr(stderr,ENS_Spread,"%5f","ENS_Spread - ");
        printArrayFmtAllWHdr(stderr,ENS_AE,    "%5f","ENS_AE - ");
        printout = 1;
    }
    */
    *nvalid = obs_nm.tlen;
    if (*nvalid > 0){
        *obs_Mean = my_Mean(&obs_nm);
        *obs_Med  = Median(&obs_nm);
        arr Climo = Array(1,DOUBLE,*nvalid);
        fillAr(&Climo, obs_Mean);

        *ENSM_Bias    = calcBias(&ENSM_nm,&obs_nm);
        
        *ENSM_RelBias = calcRelBias(&ENSM_nm,&obs_nm);
        if (!isfinite(*ENSM_RelBias)){ *ENSM_RelBias = miss_ENSM_RelBias; }
        
        *ENSM_Corr    = Corr(&ENSM_nm,&obs_nm);
        if (!isfinite(*ENSM_Corr)){ *ENSM_Corr = miss_ENSM_Corr; }
        
        double *work  = malloc(2*(*nvalid)*sizeof(double));
        *ENSM_SpCr    = gsl_stats_spearman(pntr_of(&ENSM_nm), 1, pntr_of(&obs_nm), 1, *nvalid, work);
        free(work);
        if (!isfinite(*ENSM_SpCr)){ *ENSM_SpCr = miss_ENSM_SpCr; }
        
        *ENSMed_Bias    = calcBias(&ENSMed_nm,&obs_nm);
        
        *ENSMed_RelBias = calcRelBias(&ENSMed_nm,&obs_nm);
        if (!isfinite(*ENSMed_RelBias)){ *ENSMed_RelBias = miss_ENSMed_RelBias; }
        
        *ENSMed_Corr    = Corr(&ENSMed_nm,&obs_nm);
        if (!isfinite(*ENSMed_Corr)){ *ENSMed_Corr = miss_ENSMed_Corr; }
        
        arr Fcst_Obs_MAE  = arStatArg2ar(wrap_calcMAE,fcst,obs,0);
        
        *Climo_MAE = calcMAE(&Climo,&obs_nm);
        
        *ENSM_MAE  = calcMAE(&ENSM_nm,&obs_nm);

        if (*Climo_MAE > 0){
            arr    Fcst_SS_MAE_tmp = fct1ar1s(wrap_skillScore2,&Fcst_Obs_MAE,*Climo_MAE);
            
            *ENSM_SS_MAE = skillScore(*ENSM_MAE,*Climo_MAE);
            
            arr Fcst_SS_MAE = removeMissing(&Fcst_SS_MAE_tmp);
            freeAr(&Fcst_SS_MAE_tmp);
            arr Fcst_SS_MAE_srtd = qsortArray(&Fcst_SS_MAE);

            *SS_MAE_min = Min(&Fcst_SS_MAE);
            *SS_MAE_Q1  = calcValatPercSorted(&Fcst_SS_MAE_srtd,0.25);
            *SS_MAE_med = calcValatPercSorted(&Fcst_SS_MAE_srtd,0.50);
            *SS_MAE_Q3  = calcValatPercSorted(&Fcst_SS_MAE_srtd,0.75);
            *SS_MAE_max = Max(&Fcst_SS_MAE);
            
            freeAr(&Fcst_SS_MAE);
            freeAr(&Fcst_SS_MAE_srtd);
        }

        arr Fcst_Obs_MSE  = arStatArg2ar(wrap_calcMSD,fcst,obs,0);
        
        *Climo_MSE = calcMSD(&obs_nm,&Climo);
        *ENSM_MSE  = calcMSD(&ENSM_nm,&obs_nm);

        if (*Climo_MSE > 0){
            arr    Fcst_SS_MSE_tmp = fct1ar1s(wrap_skillScore2,&Fcst_Obs_MSE,*Climo_MSE);
            *ENSM_SS_MSE = skillScore(*ENSM_MSE,*Climo_MSE);
            
            arr Fcst_SS_MSE = removeMissing(&Fcst_SS_MSE_tmp);
            freeAr(&Fcst_SS_MSE_tmp);
            arr Fcst_SS_MSE_srtd = qsortArray(&Fcst_SS_MSE);

            *SS_MSE_min = Min(&Fcst_SS_MSE);
            *SS_MSE_Q1  = calcValatPercSorted(&Fcst_SS_MSE_srtd,0.25);
            *SS_MSE_med = calcValatPercSorted(&Fcst_SS_MSE_srtd,0.50);
            *SS_MSE_Q3  = calcValatPercSorted(&Fcst_SS_MSE_srtd,0.75);
            *SS_MSE_max = Max(&Fcst_SS_MSE);

            freeAr(&Fcst_SS_MSE);
            freeAr(&Fcst_SS_MSE_srtd);
        }
        
        *Climo_MedAE   = calcMedAE(&Climo,&obs_nm);
        *ENSM_MedAE    = calcMedAE(&ENSM_nm,&obs_nm);
        if (*Climo_MedAE > 0){
            *ENSM_SS_MedAE = skillScore(*ENSM_MedAE,*Climo_MedAE);
        }
        
        *Climo_MedSE   = calcMedSD(&Climo,&obs_nm);
        *ENSM_MedSE    = calcMedSD(&ENSM_nm,&obs_nm);
        if (*Climo_MedSE > 0){
            *ENSM_SS_MedSE = skillScore(*ENSM_MedSE,*Climo_MedSE);
        }
        
        *ENSMed_MedAE    = calcMedAE(&ENSMed_nm,&obs_nm);
        if (*Climo_MedAE > 0){
            *ENSMed_SS_MedAE = skillScore(*ENSMed_MedAE,*Climo_MedAE);
        }
        
        *ENSMed_MedSE    = calcMedSD(&ENSMed_nm,&obs_nm);
        if (*Climo_MedSE > 0){
            *ENSMed_SS_MedSE = skillScore(*ENSMed_MedSE,*Climo_MedSE);
        }
        
        *ENSMed_MAE    = calcMAE(&ENSMed_nm,&obs_nm);
        if (*Climo_MAE > 0){
            *ENSMed_SS_MAE = skillScore(*ENSMed_MAE,*Climo_MAE);
        }
        
        *ENSMed_MSE    = calcMSD(&ENSMed_nm,&obs_nm);
        if (*Climo_MSE > 0){
            *ENSMed_SS_MSE = skillScore(*ENSMed_MSE,*Climo_MSE);
        }

        typ_idx *outlen = int64s(2,obs->tlen,obs->tlen);
        typ_idx map = 1;
        arr Climo_Ens = expandArExp(obs,2,outlen,&map);

        arr Climo_RPS    = arStatArg2ar(wrap_ensRPS_One2,&Climo_Ens,obs,1);
        arr Climo_RPS_nm = removeMissing(&Climo_RPS);
        *Climo_RPS_Mean  = my_Mean(&Climo_RPS_nm);
        *Climo_RPS_Med   = Median(&Climo_RPS_nm);

        arr fcst_RPS = arStatArg2ar(wrap_ensRPS_One2,fcst,obs,1);
        arr fcst_RPS_nm = removeMissing(&fcst_RPS);
        *fcst_RPS_Mean = my_Mean(&fcst_RPS_nm);
        *fcst_RPS_Med  = Median(&fcst_RPS_nm);

        if (*Climo_RPS_Mean > 0){
            *fcst_RPSS = skillScore(*fcst_RPS_Mean,*Climo_RPS_Mean);
        }
        if (*Climo_RPS_Med > 0){
            *fcst_RPSSmed = skillScore(*fcst_RPS_Med,*Climo_RPS_Med);
        }
    
        arr fcst_nm = removeMissing(fcst);
        *var_fcst   = VarS(&fcst_nm);
        *var_obs    = VarS(&obs_nm);
        *var_ensm   = VarS(&ENSM_nm);
        *var_ensmed = VarS(&ENSMed_nm);
        *fcst_mean  = my_Mean(&fcst_nm);

        freeAr(&fcst_nm);
        freeAr(&Climo);
        freeAr(&Fcst_Obs_MAE);
        freeAr(&Fcst_Obs_MSE);
        freeAr(&Climo_Ens);
        freeAr(&Climo_RPS);
        freeAr(&Climo_RPS_nm);
        freeAr(&fcst_RPS);
        freeAr(&fcst_RPS_nm);
        free(outlen);
    }
    freeAr(&obs_nm);
    freeAr(&ENSM_nm);
    freeAr(&ENSMed_nm);
    return;
}

void verify_2_ensemble_forecasts(
    /* input */
     arr *restrict fcst1                 /* Forecast ensembles fcst[time][ensembles] */
    ,arr *restrict fcst2                 /* Reference Forecast ensembles fcst[time][ensembles] */
    ,arr *restrict obs                   /* Observation obs[time] */
    /* Output */
    ,arr *ENS1M                /* Ensemble mean of each forecast */
    ,arr *ENS1_Spread          /* Ensemble spread of each forecast */
    ,arr *ENS1_AE              /* Absolute error between ENSM and obs */
    ,arr *ENS1_Err             /* Error error between ENSM and obs */
    ,arr *ENS2M                /* Ensemble mean of each forecast */
    ,arr *ENS2_Spread          /* Ensemble spread of each forecast */
    ,arr *ENS2_AE              /* Absolute error between ENSM and obs */
    ,arr *ENS2_Err             /* Error between ENSM and obs */
    ,double *obs_Mean          /* my_Mean observation (climatology) */
    ,double *var_obs           /* Overall observed variance */
    ,double *ENSM_SS_MAE       /* MAE-based skill score of ENSM */
    ,double *ENSM_SS_MSE       /* MSE-based skill score of ENSM */
    ,double *fcst_RPSS         /* RPS-based skill score (RPSS) of ensemble forecasts */
    ,double *ENS1M_MAE         /* my_Mean absolute error of ensemble mean */
    ,double *ENS1M_MSE         /* my_Mean square error of ensemble mean */
    ,double *fcst1_RPS_Mean    /* Ranked probability score mean of ensemble forecasts */
    ,double *ENS1M_Bias        /* Absolute bias of ensemble mean */
    ,double *ENS1M_RelBias     /* Relative or percent bias of ensemble mean */
    ,double *ENS1M_Corr        /* Correlation of ensemble mean with observations */
    ,double *ENS1M_SpCr        /* Spearman rank correlation of ensemble mean with observations */
    ,double *var_fcst1         /* Overall forecast variance */
    ,double *var_ens1m         /* variance of ensemble means */
    ,double *fcst1_mean        /* Overall forecast mean */
    ,double *ENS2M_MAE         /* my_Mean absolute error of ensemble mean */
    ,double *ENS2M_MSE         /* my_Mean square error of ensemble mean */
    ,double *fcst2_RPS_Mean    /* Ranked probability score mean of ensemble forecasts */
    ,double *ENS2M_Bias        /* Absolute bias of ensemble mean */
    ,double *ENS2M_RelBias     /* Relative or percent bias of ensemble mean */
    ,double *ENS2M_Corr        /* Correlation of ensemble mean with observations */
    ,double *ENS2M_SpCr        /* Spearman rank correlation of ensemble mean with observations */
    ,double *var_fcst2         /* Overall forecast variance */
    ,double *var_ens2m         /* variance of ensemble means */
    ,double *fcst2_mean        /* Overall forecast mean */
    ,typ_idx *nvalid           /* Number of valid observation pairs */
    ){
    /* Save missing values passed in */
    double miss_obs_Mean        = *obs_Mean;
    double miss_var_obs         = *var_obs;
    double miss_ENSM_SS_MAE     = *ENSM_SS_MAE;
    double miss_ENSM_SS_MSE     = *ENSM_SS_MSE;
    double miss_fcst_RPSS       = *fcst_RPSS;
    double miss_ENS1M_MAE       = *ENS1M_MAE;
    double miss_ENS1M_MSE       = *ENS1M_MSE;
    double miss_fcst1_RPS_Mean  = *fcst1_RPS_Mean;
    double miss_ENS1M_Bias      = *ENS1M_Bias;
    double miss_ENS1M_RelBias   = *ENS1M_RelBias;
    double miss_ENS1M_Corr      = *ENS1M_Corr;
    double miss_ENS1M_SpCr      = *ENS1M_SpCr;
    double miss_var_fcst1       = *var_fcst1;
    double miss_var_ens1m       = *var_ens1m;
    double miss_fcst1_mean      = *fcst1_mean;
    double miss_ENS2M_MAE       = *ENS2M_MAE;
    double miss_ENS2M_MSE       = *ENS2M_MSE;
    double miss_fcst2_RPS_Mean  = *fcst2_RPS_Mean;
    double miss_ENS2M_Bias      = *ENS2M_Bias;
    double miss_ENS2M_RelBias   = *ENS2M_RelBias;
    double miss_ENS2M_Corr      = *ENS2M_Corr;
    double miss_ENS2M_SpCr      = *ENS2M_SpCr;
    double miss_var_fcst2       = *var_fcst2;
    double miss_var_ens2m       = *var_ens2m;
    double miss_fcst2_mean      = *fcst2_mean;

    *ENS1M       = arStatArg1ar(wrap_Mean,fcst1,1);
    *ENS1_Spread = arStatArg1ar(wrap_stdDevS,fcst1,1);
    *ENS1_AE     = fct2ar(wrap_devAbs,ENS1M,obs);
    *ENS1_Err    = fct2ar(wrap_sub,ENS1M,obs);

    *ENS2M       = arStatArg1ar(wrap_Mean,fcst2,1);
    *ENS2_Spread = arStatArg1ar(wrap_stdDevS,fcst2,1);
    *ENS2_AE     = fct2ar(wrap_devAbs,ENS2M,obs);
    *ENS2_Err    = fct2ar(wrap_sub,ENS2M,obs);

    arr obs_nm,ENS1M_nm,ENS2M_nm;
    removeMissingNArrays(3,&obs_nm,&ENS1M_nm,&ENS2M_nm,obs,ENS1M,ENS2M);
    
    /*
    int printout = 0;
    if ((Zeros(&obs_nm) == 1) || (Zeros(&ENS1M_nm) == 1) || (Zeros(&ENS2M_nm) == 1)){
        printArrayFmtAllWHdr(stderr,fcst1,      "%5f","fcst1 - ");
        printArrayFmtAllWHdr(stderr,fcst2,      "%5f","fcst2 - ");
        printArrayFmtAllWHdr(stderr,obs,        "%5f","obs - ");
        printArrayFmtAllWHdr(stderr,&ENS1M_nm,  "%5f","ENS1M_nm - ");
        printArrayFmtAllWHdr(stderr,&obs_nm,    "%5f","obs_nm - ");
        printArrayFmtAllWHdr(stderr,ENS1M,      "%5f","ENS1M - ");
        printArrayFmtAllWHdr(stderr,ENS1_Spread,"%5f","ENS1_Spread - ");
        printArrayFmtAllWHdr(stderr,ENS1_AE,    "%5f","ENS1_AE - ");
        printArrayFmtAllWHdr(stderr,ENS2M,      "%5f","ENS2M - ");
        printArrayFmtAllWHdr(stderr,ENS2_Spread,"%5f","ENS2_Spread - ");
        printArrayFmtAllWHdr(stderr,ENS2_AE,    "%5f","ENS2_AE - ");
        printout = 1;
    }
    */
    *nvalid = obs_nm.tlen;
    if (*nvalid > 0){
        *obs_Mean = my_Mean(&obs_nm);

        *ENS1M_Bias    = calcBias(&ENS1M_nm,&obs_nm);
        *ENS2M_Bias    = calcBias(&ENS2M_nm,&obs_nm);
        
        *ENS1M_RelBias = calcRelBias(&ENS1M_nm,&obs_nm);
        if (!isfinite(*ENS1M_RelBias)){ *ENS1M_RelBias = miss_ENS1M_RelBias; }
        *ENS2M_RelBias = calcRelBias(&ENS2M_nm,&obs_nm);
        if (!isfinite(*ENS2M_RelBias)){ *ENS2M_RelBias = miss_ENS2M_RelBias; }
        
        *ENS1M_Corr    = Corr(&ENS1M_nm,&obs_nm);
        if (!isfinite(*ENS1M_Corr)){ *ENS1M_Corr = miss_ENS1M_Corr; }
        *ENS2M_Corr    = Corr(&ENS2M_nm,&obs_nm);
        if (!isfinite(*ENS2M_Corr)){ *ENS2M_Corr = miss_ENS2M_Corr; }
        
        double *work  = malloc(2*(*nvalid)*sizeof(double));
        *ENS1M_SpCr    = gsl_stats_spearman(pntr_of(&ENS1M_nm), 1, pntr_of(&obs_nm), 1, *nvalid, work);
        free(work);
        if (!isfinite(*ENS1M_SpCr)){ *ENS1M_SpCr = miss_ENS1M_SpCr; }

        work = malloc(2*(*nvalid)*sizeof(double));
        *ENS2M_SpCr  = gsl_stats_spearman(pntr_of(&ENS2M_nm), 1, pntr_of(&obs_nm), 1, *nvalid, work);
        free(work);
        if (!isfinite(*ENS2M_SpCr)){ *ENS2M_SpCr = miss_ENS2M_SpCr; }

        *ENS1M_MAE = calcMAE(&ENS1M_nm,&obs_nm);
        *ENS2M_MAE = calcMAE(&ENS2M_nm,&obs_nm);
        if (*ENS2M_MAE > 0){ *ENSM_SS_MAE  = skillScore(*ENS1M_MAE,*ENS2M_MAE); }

        *ENS1M_MSE = calcMSD(&ENS1M_nm,&obs_nm);
        *ENS2M_MSE = calcMSD(&ENS2M_nm,&obs_nm);
        if (*ENS2M_MSE > 0){ *ENSM_SS_MSE  = skillScore(*ENS1M_MSE,*ENS2M_MSE); }

        arr fcst1_RPS = arStatArg2ar(wrap_ensRPS_One2,fcst1,obs,1);
        arr fcst1_RPS_nm = removeMissing(&fcst1_RPS);
        *fcst1_RPS_Mean = my_Mean(&fcst1_RPS_nm);

        arr fcst2_RPS = arStatArg2ar(wrap_ensRPS_One2,fcst2,obs,1);
        arr fcst2_RPS_nm = removeMissing(&fcst2_RPS);
        *fcst2_RPS_Mean = my_Mean(&fcst2_RPS_nm);

        if (*fcst2_RPS_Mean > 0){
            *fcst_RPSS = skillScore(*fcst1_RPS_Mean,*fcst2_RPS_Mean);
        }
    
        *var_obs    = VarS(&obs_nm);
        
        arr fcst1_nm = removeMissing(fcst1);
        *var_fcst1   = VarS(&fcst1_nm);
        *var_ens1m   = VarS(&ENS1M_nm);
        *fcst1_mean  = my_Mean(&fcst1_nm);
        
        arr fcst2_nm = removeMissing(fcst2);
        *var_fcst2   = VarS(&fcst2_nm);
        *var_ens2m   = VarS(&ENS2M_nm);
        *fcst2_mean  = my_Mean(&fcst2_nm);

        freeAr(&fcst1_nm);
        freeAr(&fcst1_RPS);
        freeAr(&fcst1_RPS_nm);
        
        freeAr(&fcst2_nm);
        freeAr(&fcst2_RPS);
        freeAr(&fcst2_RPS_nm);
    }
    freeAr(&obs_nm);
    freeAr(&ENS1M_nm);
    freeAr(&ENS2M_nm);
    return;
}


void verify_2_deterministic_forecasts(
    /* input */
     arr *restrict fcst1                 /* Forecast fcst[time] */
    ,arr *restrict fcst2                 /* Reference Forecast fcst[time] */
    ,arr *restrict obs                   /* Observation obs[time] */
    /* Output */
    ,arr *Fcst1_AE              /* Absolute error between ENSM and obs */
    ,arr *Fcst1_Err             /* Error error between ENSM and obs */
    ,arr *Fcst2_AE              /* Absolute error between ENSM and obs */
    ,arr *Fcst2_Err             /* Error between ENSM and obs */
    ,double *obs_Mean          /* my_Mean observation (climatology) */
    ,double *var_obs           /* Overall observed variance */
    ,double *SS_MAE       /* MAE-based skill score of ENSM */
    ,double *SS_MSE       /* MSE-based skill score of ENSM */
    ,double *Fcst1_MAE         /* my_Mean absolute error of ensemble mean */
    ,double *Fcst1_MSE         /* my_Mean square error of ensemble mean */
    ,double *Fcst1_Bias        /* Absolute bias of ensemble mean */
    ,double *Fcst1_RelBias     /* Relative or percent bias of ensemble mean */
    ,double *Fcst1_Corr        /* Correlation of ensemble mean with observations */
    ,double *Fcst1_SpCr        /* Spearman rank correlation of ensemble mean with observations */
    ,double *var_fcst1         /* Overall forecast variance */
    ,double *fcst1_mean        /* Overall forecast mean */
    ,double *Fcst2_MAE         /* my_Mean absolute error of ensemble mean */
    ,double *Fcst2_MSE         /* my_Mean square error of ensemble mean */
    ,double *Fcst2_Bias        /* Absolute bias of ensemble mean */
    ,double *Fcst2_RelBias     /* Relative or percent bias of ensemble mean */
    ,double *Fcst2_Corr        /* Correlation of ensemble mean with observations */
    ,double *Fcst2_SpCr        /* Spearman rank correlation of ensemble mean with observations */
    ,double *var_fcst2         /* Overall forecast variance */
    ,double *fcst2_mean        /* Overall forecast mean */
    ,typ_idx *nvalid           /* Number of valid observation pairs */
    ){
    /* Save missing values passed in */
    double miss_obs_Mean        = *obs_Mean;
    double miss_var_obs         = *var_obs;
    double miss_SS_MAE          = *SS_MAE;
    double miss_SS_MSE          = *SS_MSE;
    double miss_Fcst1_MAE       = *Fcst1_MAE;
    double miss_Fcst1_MSE       = *Fcst1_MSE;
    double miss_Fcst1_Bias      = *Fcst1_Bias;
    double miss_Fcst1_RelBias   = *Fcst1_RelBias;
    double miss_Fcst1_Corr      = *Fcst1_Corr;
    double miss_Fcst1_SpCr      = *Fcst1_SpCr;
    double miss_var_fcst1       = *var_fcst1;
    double miss_fcst1_mean      = *fcst1_mean;
    double miss_Fcst2_MAE       = *Fcst2_MAE;
    double miss_Fcst2_MSE       = *Fcst2_MSE;
    double miss_Fcst2_Bias      = *Fcst2_Bias;
    double miss_Fcst2_RelBias   = *Fcst2_RelBias;
    double miss_Fcst2_Corr      = *Fcst2_Corr;
    double miss_Fcst2_SpCr      = *Fcst2_SpCr;
    double miss_var_fcst2       = *var_fcst2;
    double miss_fcst2_mean      = *fcst2_mean;

    *Fcst1_AE     = fct2ar(wrap_devAbs,fcst1,obs);
    *Fcst1_Err    = fct2ar(wrap_sub,fcst1,obs);

    *Fcst2_AE     = fct2ar(wrap_devAbs,fcst2,obs);
    *Fcst2_Err    = fct2ar(wrap_sub,fcst2,obs);

    arr obs_nm,Fcst1_nm,Fcst2_nm;
    removeMissingNArrays(3,&obs_nm,&Fcst1_nm,&Fcst2_nm,obs,fcst1,fcst2);
    /*
    int printout = 0;
    if ((Zeros(&obs_nm) == 1) || (Zeros(&Fcst1_nm) == 1) || (Zeros(&Fcst2_nm) == 1)){
        printArrayFmtAllWHdr(stderr,fcst1,       "%5f","fcst1 - ");
        printArrayFmtAllWHdr(stderr,obs,        "%5f","obs - ");
        printArrayFmtAllWHdr(stderr,&Fcst1_nm,    "%5f","Fcst1_nm - ");
        printArrayFmtAllWHdr(stderr,&obs_nm,     "%5f","obs_nm - ");
        printArrayFmtAllWHdr(stderr,fcst1,      "%5f","fcst1 - ");
        printArrayFmtAllWHdr(stderr,Fcst1_AE,    "%5f","Fcst1_AE - ");
        printArrayFmtAllWHdr(stderr,fcst2,      "%5f","fcst2 - ");
        printArrayFmtAllWHdr(stderr,Fcst2_AE,    "%5f","Fcst2_AE - ");
        printout = 1;
    }
    */
    *nvalid = obs_nm.tlen;
    if (*nvalid > 0){
        *obs_Mean = my_Mean(&obs_nm);

        *Fcst1_Bias    = calcBias(&Fcst1_nm,&obs_nm);
        *Fcst2_Bias    = calcBias(&Fcst2_nm,&obs_nm);
        
        *Fcst1_RelBias = calcRelBias(&Fcst1_nm,&obs_nm);
        if (!isfinite(*Fcst1_RelBias)){ *Fcst1_RelBias = miss_Fcst1_RelBias; }
        *Fcst2_RelBias = calcRelBias(&Fcst2_nm,&obs_nm);
        if (!isfinite(*Fcst2_RelBias)){ *Fcst2_RelBias = miss_Fcst2_RelBias; }
        
        *Fcst1_Corr    = Corr(&Fcst1_nm,&obs_nm);
        if (!isfinite(*Fcst1_Corr)){ *Fcst1_Corr = miss_Fcst1_Corr; }
        *Fcst2_Corr    = Corr(&Fcst2_nm,&obs_nm);
        if (!isfinite(*Fcst2_Corr)){ *Fcst2_Corr = miss_Fcst2_Corr; }
        
        double *work  = malloc(2*(*nvalid)*sizeof(double));
        *Fcst1_SpCr    = gsl_stats_spearman(pntr_of(&Fcst1_nm), 1, pntr_of(&obs_nm), 1, *nvalid, work);
        free(work);
        if (!isfinite(*Fcst1_SpCr)){ *Fcst1_SpCr = miss_Fcst1_SpCr; }

        work = malloc(2*(*nvalid)*sizeof(double));
        *Fcst2_SpCr  = gsl_stats_spearman(pntr_of(&Fcst2_nm), 1, pntr_of(&obs_nm), 1, *nvalid, work);
        free(work);
        if (!isfinite(*Fcst2_SpCr)){ *Fcst2_SpCr = miss_Fcst2_SpCr; }

        *Fcst1_MAE = calcMAE(&Fcst1_nm,&obs_nm);
        *Fcst2_MAE = calcMAE(&Fcst2_nm,&obs_nm);
        if (*Fcst2_MAE > 0){ *SS_MAE  = skillScore(*Fcst1_MAE,*Fcst2_MAE); }

        *Fcst1_MSE = calcMSD(&Fcst1_nm,&obs_nm);
        *Fcst2_MSE = calcMSD(&Fcst2_nm,&obs_nm);
        if (*Fcst2_MSE > 0){ *SS_MSE  = skillScore(*Fcst1_MSE,*Fcst2_MSE); }
    
        *var_obs    = VarS(&obs_nm);
        
        *var_fcst1   = VarS(&Fcst1_nm);
        *fcst1_mean  = my_Mean(&Fcst1_nm);
        
        *var_fcst2   = VarS(&Fcst1_nm);
        *fcst2_mean  = my_Mean(&Fcst1_nm);
    }
    freeAr(&obs_nm);
    freeAr(&Fcst1_nm);
    freeAr(&Fcst2_nm);
    return;
}



void verify_ensemble_forecast_1(arr *restrict fcst,double ob
    ,double *ENSM     ,double *ENS_Spread
    ,double *ENSM_AE  ,double *ENSM_SE
    ,double *ENSM_Bias,double *fcst_RPS){
    /*    
    printArrayFmtAllWHdr(stderr,fcst,"%5f","verify_ensemble_forecast_1: ob=%g, fcst - ",ob);
    */
    *ENSM       = my_Mean(fcst);
    *ENS_Spread = stdDevS(fcst);

    *ENSM_Bias    = *ENSM - ob;
/*  *ENSM_RelBias = *ENSM_Bias/fabs(ob); */
    *ENSM_AE      = fabs(*ENSM_Bias);
    *ENSM_SE      = pow(*ENSM_Bias,2);
    *fcst_RPS     = ensRPS_One(fcst,ob);
    return;
}

#endif

