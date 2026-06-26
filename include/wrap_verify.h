/* Created by Bill Scheftic */
#ifndef  _WRAP_VERIFY_H_
#define  _WRAP_VERIFY_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <verify.h>

double wrap_skillScore(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
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

double wrap_invertSkillScore(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double ss = args->dblp[0];
    return invertSkillScore(ss);
}

double wrap_ensRPS_One(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1ar1d(ensRPS_One,args,1);
}

double wrap_cdfRPS_one(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }

    double rv;
    arr *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < 4){
        rv = *(double *)args->missval;
    } else {
        double val  = args->dblp[0];
        double bcrd = args->dblp[1];
        double dcrd = args->dblp[2];
        typ_idx n   = args->idxp[0];

        gridnd grd;
        setGridNdFromList(1,&grd,&bcrd,&dcrd,&n);

        rv = cdfRPS_one(&A[0],val,&grd);
        freeGridNd(&grd);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_BiasImp(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3ar(findBiasImp,args,1);
}

double wrap_calcRPS(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }

    double rv;
    arr *ccdf = args->arrays[0];
    arr *A = removeMissingNArraysList_alloc(2, &args->arrays[1]);
    if (A[0].tlen < 4){
        rv = *(double *)args->missval;
    } else {
        double bcrd = args->dblp[0];
        double dcrd = args->dblp[1];
        typ_idx n   = args->idxp[0];

        gridnd grd;
        setGridNdFromList(1,&grd,&bcrd,&dcrd,&n);

        rv = calcRPS(ccdf,&A[0],&A[1],&grd);
        freeGridNd(&grd);
    }

    for (i=0;i<2;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_calcRPSClim(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 1,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }

    double rv;
    arr *cdf_clim = args->arrays[0];
    arr  obs      = removeMissing(args->arrays[1]);
    if (obs.tlen < 4){
        rv = *(double *)args->missval;
    } else {
        double bcrd = args->dblp[0];
        double dcrd = args->dblp[1];
        typ_idx n   = args->idxp[0];

        gridnd grd;
        setGridNdFromList(1,&grd,&bcrd,&dcrd,&n);

        rv = calcRPSClim(cdf_clim,&obs,&grd);
        freeGridNd(&grd);
    }

    freeAr(&obs);
    return rv;
}


void wrap_verify_ensemble_forecast(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 4,/*nrdbls*/ 50,/*nrints*/ 0,/*nridxs*/ 1)){ exit(EXIT_FAILURE); }
    int cntr = 0;
    arr *fcst = args->arrays[cntr]; cntr++;
    arr *obs  = args->arrays[cntr]; cntr++;
    cntr = 0;
    arr    *ENSM       = args->arrpp[cntr]; cntr++;
    arr    *ENSMed     = args->arrpp[cntr]; cntr++;
    arr    *ENS_Spread = args->arrpp[cntr]; cntr++;
    arr    *ENS_AE     = args->arrpp[cntr]; cntr++;
    cntr = 0;
    double *obs_Mean        = args->dblpp[cntr]; cntr++;
    double *obs_Med         = args->dblpp[cntr]; cntr++;
    double *Climo_MAE       = args->dblpp[cntr]; cntr++;
    double *ENSM_MAE        = args->dblpp[cntr]; cntr++;
    double *Climo_MSE       = args->dblpp[cntr]; cntr++;
    double *ENSM_MSE        = args->dblpp[cntr]; cntr++;
    double *ENSM_SS_MAE     = args->dblpp[cntr]; cntr++;
    double *SS_MAE_min      = args->dblpp[cntr]; cntr++;
    double *SS_MAE_Q1       = args->dblpp[cntr]; cntr++;
    double *SS_MAE_med      = args->dblpp[cntr]; cntr++;
    double *SS_MAE_Q3       = args->dblpp[cntr]; cntr++;
    double *SS_MAE_max      = args->dblpp[cntr]; cntr++;
    double *ENSM_SS_MSE     = args->dblpp[cntr]; cntr++;
    double *SS_MSE_min      = args->dblpp[cntr]; cntr++;
    double *SS_MSE_Q1       = args->dblpp[cntr]; cntr++;
    double *SS_MSE_med      = args->dblpp[cntr]; cntr++;
    double *SS_MSE_Q3       = args->dblpp[cntr]; cntr++;
    double *SS_MSE_max      = args->dblpp[cntr]; cntr++;
    double *Climo_MedAE     = args->dblpp[cntr]; cntr++;
    double *ENSM_MedAE      = args->dblpp[cntr]; cntr++;
    double *ENSM_SS_MedAE   = args->dblpp[cntr]; cntr++;
    double *Climo_MedSE     = args->dblpp[cntr]; cntr++;
    double *ENSM_MedSE      = args->dblpp[cntr]; cntr++;
    double *ENSM_SS_MedSE   = args->dblpp[cntr]; cntr++;
    double *ENSMed_MedAE    = args->dblpp[cntr]; cntr++;
    double *ENSMed_SS_MedAE = args->dblpp[cntr]; cntr++;
    double *ENSMed_MedSE    = args->dblpp[cntr]; cntr++;
    double *ENSMed_SS_MedSE = args->dblpp[cntr]; cntr++;
    double *ENSMed_MAE      = args->dblpp[cntr]; cntr++;
    double *ENSMed_MSE      = args->dblpp[cntr]; cntr++;
    double *ENSMed_SS_MAE   = args->dblpp[cntr]; cntr++;
    double *ENSMed_SS_MSE   = args->dblpp[cntr]; cntr++;
    double *Climo_RPS       = args->dblpp[cntr]; cntr++;
    double *fcst_RPS        = args->dblpp[cntr]; cntr++;
    double *fcst_RPSS       = args->dblpp[cntr]; cntr++;
    double *Climo_RPSmed    = args->dblpp[cntr]; cntr++;
    double *fcst_RPSmed     = args->dblpp[cntr]; cntr++;
    double *fcst_RPSSmed    = args->dblpp[cntr]; cntr++;
    double *ENSM_Bias       = args->dblpp[cntr]; cntr++;
    double *ENSM_RelBias    = args->dblpp[cntr]; cntr++;
    double *ENSM_Corr       = args->dblpp[cntr]; cntr++;
    double *ENSM_SpCr       = args->dblpp[cntr]; cntr++;
    double *ENSMed_Bias     = args->dblpp[cntr]; cntr++;
    double *ENSMed_RelBias  = args->dblpp[cntr]; cntr++;
    double *ENSMed_Corr     = args->dblpp[cntr]; cntr++;
    double *var_fcst        = args->dblpp[cntr]; cntr++;
    double *var_obs         = args->dblpp[cntr]; cntr++;
    double *var_ensm        = args->dblpp[cntr]; cntr++;
    double *var_ensmed      = args->dblpp[cntr]; cntr++;
    double *fcst_mean       = args->dblpp[cntr]; cntr++;
    cntr = 0;
    typ_idx *nvalid         = args->idxpp[cntr]; cntr++;
    
    if (isAnyNonMiss(fcst) && isAnyNonMiss(obs)){
        verify_ensemble_forecast(fcst,obs,ENSM,ENSMed,ENS_Spread,ENS_AE,obs_Mean,obs_Med
            ,Climo_MAE,ENSM_MAE,Climo_MSE,ENSM_MSE
            ,ENSM_SS_MAE,SS_MAE_min,SS_MAE_Q1
            ,SS_MAE_med,SS_MAE_Q3,SS_MAE_max
            ,ENSM_SS_MSE,SS_MSE_min,SS_MSE_Q1
            ,SS_MSE_med,SS_MSE_Q3,SS_MSE_max
            ,Climo_MedAE, ENSM_MedAE,ENSM_SS_MedAE
            ,Climo_MedSE, ENSM_MedSE,ENSM_SS_MedSE
            ,ENSMed_MedAE,ENSMed_SS_MedAE,ENSMed_MedSE,ENSMed_SS_MedSE
            ,ENSMed_MAE,ENSMed_MSE,ENSMed_SS_MAE,ENSMed_SS_MSE
            ,Climo_RPS,fcst_RPS,fcst_RPSS
            ,Climo_RPSmed,fcst_RPSmed,fcst_RPSSmed
            ,ENSM_Bias,ENSM_RelBias,ENSM_Corr,ENSM_SpCr
            ,ENSMed_Bias,ENSMed_RelBias,ENSMed_Corr
            ,var_fcst,var_obs,var_ensm,var_ensmed,fcst_mean,nvalid);
    }
    return;
}

void wrap_verify_2_ensemble_forecasts(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 8,/*nrdbls*/ 25,/*nrints*/ 0,/*nridxs*/ 1)){ exit(EXIT_FAILURE); }
    int cntr = 0;
    arr *fcst1 = args->arrays[cntr]; cntr++;
    arr *fcst2 = args->arrays[cntr]; cntr++;
    arr *obs   = args->arrays[cntr]; cntr++;
    cntr = 0;
    arr       *ENS1M       = args->arrpp[cntr]; cntr++;
    arr       *ENS1_Spread = args->arrpp[cntr]; cntr++;
    arr       *ENS1_AE     = args->arrpp[cntr]; cntr++;
    arr       *ENS1_Err    = args->arrpp[cntr]; cntr++;
    arr       *ENS2M       = args->arrpp[cntr]; cntr++;
    arr       *ENS2_Spread = args->arrpp[cntr]; cntr++;
    arr       *ENS2_AE     = args->arrpp[cntr]; cntr++;
    arr       *ENS2_Err    = args->arrpp[cntr]; cntr++;
    cntr = 0;
    double *obs_Mean       = args->dblpp[cntr]; cntr++;
    double *var_obs        = args->dblpp[cntr]; cntr++;
    double *ENSM_SS_MAE    = args->dblpp[cntr]; cntr++;
    double *ENSM_SS_MSE    = args->dblpp[cntr]; cntr++;
    double *fcst_RPSS      = args->dblpp[cntr]; cntr++;
    double *ENS1M_MAE      = args->dblpp[cntr]; cntr++;
    double *ENS1M_MSE      = args->dblpp[cntr]; cntr++;
    double *fcst1_RPS_Mean = args->dblpp[cntr]; cntr++;
    double *ENS1M_Bias     = args->dblpp[cntr]; cntr++;
    double *ENS1M_RelBias  = args->dblpp[cntr]; cntr++;
    double *ENS1M_Corr     = args->dblpp[cntr]; cntr++;
    double *ENS1M_SpCr     = args->dblpp[cntr]; cntr++;
    double *var_fcst1      = args->dblpp[cntr]; cntr++;
    double *var_ens1m      = args->dblpp[cntr]; cntr++;
    double *fcst1_mean     = args->dblpp[cntr]; cntr++;
    double *ENS2M_MAE      = args->dblpp[cntr]; cntr++;
    double *ENS2M_MSE      = args->dblpp[cntr]; cntr++;
    double *fcst2_RPS_Mean = args->dblpp[cntr]; cntr++;
    double *ENS2M_Bias     = args->dblpp[cntr]; cntr++;
    double *ENS2M_RelBias  = args->dblpp[cntr]; cntr++;
    double *ENS2M_Corr     = args->dblpp[cntr]; cntr++;
    double *ENS2M_SpCr     = args->dblpp[cntr]; cntr++;
    double *var_fcst2      = args->dblpp[cntr]; cntr++;
    double *var_ens2m      = args->dblpp[cntr]; cntr++;
    double *fcst2_mean     = args->dblpp[cntr]; cntr++;
    cntr = 0;
    typ_idx *nvalid        = args->idxpp[cntr]; cntr++;
    
    if (isAnyNonMiss(fcst1) && isAnyNonMiss(fcst2) && isAnyNonMiss(obs)){
        verify_2_ensemble_forecasts(
            /* input */
             fcst1
            ,fcst2
            ,obs
            /* Output */
            ,ENS1M
            ,ENS1_Spread
            ,ENS1_AE
            ,ENS1_Err
            ,ENS2M
            ,ENS2_Spread
            ,ENS2_AE
            ,ENS2_Err
            ,obs_Mean
            ,var_obs
            ,ENSM_SS_MAE
            ,ENSM_SS_MSE
            ,fcst_RPSS
            ,ENS1M_MAE
            ,ENS1M_MSE
            ,fcst1_RPS_Mean
            ,ENS1M_Bias
            ,ENS1M_RelBias
            ,ENS1M_Corr
            ,ENS1M_SpCr
            ,var_fcst1
            ,var_ens1m
            ,fcst1_mean
            ,ENS2M_MAE
            ,ENS2M_MSE
            ,fcst2_RPS_Mean
            ,ENS2M_Bias
            ,ENS2M_RelBias
            ,ENS2M_Corr
            ,ENS2M_SpCr
            ,var_fcst2
            ,var_ens2m
            ,fcst2_mean
            ,nvalid
            );
    }
    return;
}

void wrap_verify_2_deterministic_forecasts(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 4,/*nrdbls*/ 20,/*nrints*/ 0,/*nridxs*/ 1)){ exit(EXIT_FAILURE); }
    int cntr = 0;
    arr *fcst1 = args->arrays[cntr]; cntr++;
    arr *fcst2 = args->arrays[cntr]; cntr++;
    arr *obs   = args->arrays[cntr]; cntr++;
    cntr = 0;
    arr      *Fcst1_AE     = args->arrpp[cntr]; cntr++;
    arr      *Fcst1_Err    = args->arrpp[cntr]; cntr++;
    arr      *Fcst2_AE     = args->arrpp[cntr]; cntr++;
    arr      *Fcst2_Err    = args->arrpp[cntr]; cntr++;
    cntr = 0;
    double *obs_Mean       = args->dblpp[cntr]; cntr++;
    double *var_obs        = args->dblpp[cntr]; cntr++;
    double *SS_MAE         = args->dblpp[cntr]; cntr++;
    double *SS_MSE         = args->dblpp[cntr]; cntr++;
    double *Fcst1_MAE      = args->dblpp[cntr]; cntr++;
    double *Fcst1_MSE      = args->dblpp[cntr]; cntr++;
    double *Fcst1_Bias     = args->dblpp[cntr]; cntr++;
    double *Fcst1_RelBias  = args->dblpp[cntr]; cntr++;
    double *Fcst1_Corr     = args->dblpp[cntr]; cntr++;
    double *Fcst1_SpCr     = args->dblpp[cntr]; cntr++;
    double *var_fcst1      = args->dblpp[cntr]; cntr++;
    double *fcst1_mean     = args->dblpp[cntr]; cntr++;
    double *Fcst2_MAE      = args->dblpp[cntr]; cntr++;
    double *Fcst2_MSE      = args->dblpp[cntr]; cntr++;
    double *Fcst2_Bias     = args->dblpp[cntr]; cntr++;
    double *Fcst2_RelBias  = args->dblpp[cntr]; cntr++;
    double *Fcst2_Corr     = args->dblpp[cntr]; cntr++;
    double *Fcst2_SpCr     = args->dblpp[cntr]; cntr++;
    double *var_fcst2      = args->dblpp[cntr]; cntr++;
    double *fcst2_mean     = args->dblpp[cntr]; cntr++;
    cntr = 0;
    typ_idx *nvalid        = args->idxpp[cntr]; cntr++;
    
    if (isAnyNonMiss(fcst1) && isAnyNonMiss(fcst2) && isAnyNonMiss(obs)){
        verify_2_deterministic_forecasts(
            /* input */
             fcst1
            ,fcst2
            ,obs
            /* Output */
            ,Fcst1_AE
            ,Fcst1_Err
            ,Fcst2_AE
            ,Fcst2_Err
            ,obs_Mean
            ,var_obs
            ,SS_MAE
            ,SS_MSE
            ,Fcst1_MAE
            ,Fcst1_MSE
            ,Fcst1_Bias
            ,Fcst1_RelBias
            ,Fcst1_Corr
            ,Fcst1_SpCr
            ,var_fcst1
            ,fcst1_mean
            ,Fcst2_MAE
            ,Fcst2_MSE
            ,Fcst2_Bias
            ,Fcst2_RelBias
            ,Fcst2_Corr
            ,Fcst2_SpCr
            ,var_fcst2
            ,fcst2_mean
            ,nvalid
            );
    }
    return;
}


void wrap_verify_ensemble_forecast_1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 6,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    int cntr = 0;
    arr   *fcst_in      = args->arrays[cntr]; cntr++;
    cntr = 0;
    double ob           = args->dblp[cntr];   cntr++;
    cntr = 0;
    double *ENSM        = args->dblpp[cntr];  cntr++;
    double *ENS_Spread  = args->dblpp[cntr];  cntr++;
    double *ENSM_AE     = args->dblpp[cntr];  cntr++;
    double *ENSM_SE     = args->dblpp[cntr];  cntr++;
    double *ENSM_Bias   = args->dblpp[cntr];  cntr++;
    double *fcst_RPS    = args->dblpp[cntr];  cntr++;
    
    arr  fcst = removeMissing(fcst_in);
    if (fcst.tlen > 1){ 
        verify_ensemble_forecast_1(&fcst,ob,ENSM,ENS_Spread,ENSM_AE,ENSM_SE,ENSM_Bias,fcst_RPS);
    }
    return;
}

#endif
