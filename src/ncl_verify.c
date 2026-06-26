/* Created by Bill Scheftic */
#include <stdio.h>
/*
 * The following are the required NCAR Graphics include files.
 * They should be located in ${NCARG_ROOT}/include
 */
/*
#define DEBUG_ARRAYND_ENTRY
#define DEBUG_ARRAYND
#define DEBUG_ARRAYND_LOOPS
*/

#include <ncl_c_wrap.h>		/* Contains all included headers, Type conversion Macros, and getVarFromNCL function */
#include <arrayinit2.h>
#include <stats2.h>
#include <arraystats2.h>
#include <print_arrays2.h>
#include <wrap_verify.h>
#include <ncl_stateq.h>

NhlErrorTypes ncl_c_skillScore_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint_Maps(wrap_skillScore,2,0,0);
  return retval;
}


NhlErrorTypes ncl_c_invertSkillScore_W( void ) {
  NhlErrorTypes retval = mth_dbl_eqNarRNdblNint(wrap_invertSkillScore,1,0,0);
  return retval;
}


NhlErrorTypes ncl_c_ensrps1_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_ensRPS_One,2,0,0,0);
  return retval;
}


NhlErrorTypes ncl_c_cdfRPS_one_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNintNidx_Maps(wrap_cdfRPS_one,5,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_calcRPSClim_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNintNidx_Maps(wrap_calcRPSClim,5,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_BiasImp_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNint_Maps(wrap_BiasImp,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_calcRPS_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNintNidx_Maps(wrap_calcRPS,6,0,0,0,0);
  return retval;
}


NhlErrorTypes ncl_c_verify_ensemble_forecast_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_verify_ensemble_forecast,2,4,50,0,1);
  return retval;
}

NhlErrorTypes ncl_c_verify_2_ensemble_forecasts_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_verify_2_ensemble_forecasts,3,8,25,0,1);
  return retval;
}

NhlErrorTypes ncl_c_verify_2_deterministic_forecasts_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_verify_2_deterministic_forecasts,3,4,20,0,1);
  return retval;
}



NhlErrorTypes ncl_c_verify_ensemble_forecast_1_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_verify_ensemble_forecast_1,2,0,6,0,0);
  return retval;
}


void Init(void){
  void *args;
  int nargs;
  /* ng_size_t dimsizes[NCL_MAX_DIMENSIONS]; */

  fprintf(stderr,"Init: Initializing ncl_verify functions ...\n");
/* In: 1 arr, 1 int arr Return: 1 arr */
  nargs = 0;
  args = NewArgs(1);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;

  NclRegisterFunc(ncl_c_invertSkillScore_W,args,"ncl_c_inv_skill",nargs);

  fprintf(stderr," 0\n");
/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(3);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_skillScore_W,     args,"ncl_c_skill",    nargs);

  fprintf(stderr," 1\n");
/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(7);

  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_cdfRPS_one_W, args,"ncl_c_cdf_rps1",   nargs);
  NclRegisterFunc(ncl_c_calcRPSClim_W,args,"ncl_c_cdf_rpsclim",nargs);

  fprintf(stderr," 2\n");
/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(8);

  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_calcRPS_W,args,"ncl_c_ccdf_rps",nargs);

  fprintf(stderr," 3\n");
/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_ensrps1_W,   args,   "ncl_c_ensrps1",nargs);

  fprintf(stderr," 4\n");
/*
 * Register functions accepting 3 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_BiasImp_W,args,"ncl_c_biasimp",nargs);
  
  fprintf(stderr," 5\n");
/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(10);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcst  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* obs   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM         */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS_Spread   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_AE      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_SE      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_Bias    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst_RPS     */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_verify_ensemble_forecast_1_W,args,"ncl_c_verify_1",nargs);
  
  fprintf(stderr," 6\n");
/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(59);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcst  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* obs   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM            */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed          */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS_Spread      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS_AE          */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret obs_Mean        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret obs_Med         */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Climo_MAE       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_MAE        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Climo_MSE       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_MSE        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_SS_MAE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MAE_min      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MAE_Q1       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MAE_med      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MAE_Q3       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MAE_max      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_SS_MSE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MSE_min      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MSE_Q1       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MSE_med      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MSE_Q3       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MSE_max      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Climo_MedAE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_MedAE      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_SS_MedAE   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Climo_MedSE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_MedSE      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_SS_MedSE   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_MedAE    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_SS_MedAE */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_MedSE    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_SS_MedSE */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_MAE      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_MSE      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_SS_MAE   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_SS_MSE   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Climo_RPS       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst_RPS        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst_RPSS       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Climo_RPSmed    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst_RPSmed     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst_RPSSmed    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_Bias       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_RelBias    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_Corr       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_SpCr       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_Bias     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_RelBias  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSMed_Corr     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_fcst        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_obs         */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_ensm        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_ensmed      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst_mean       */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret nvalid          */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_verify_ensemble_forecast_W,args,"ncl_c_verify",nargs);
  
  fprintf(stderr," 7\n");
/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(39);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcst1  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcst2  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* obs    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1M           */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1_Spread     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1_AE         */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1_Err        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2M           */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2_Spread     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2_AE         */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2_Err        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret obs_Mean        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_obs         */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_SS_MAE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENSM_SS_MSE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst_RPSS       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1M_MAE       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1M_MSE       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst1_RPS_Mean  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1M_Bias      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1M_RelBias   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1M_Corr      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS1M_SpCr      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_fcst1       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_ens1m       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst1_mean      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2M_MAE       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2M_MSE       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst2_RPS_Mean  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2M_Bias      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2M_RelBias   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2M_Corr      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ENS2M_SpCr      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_fcst2       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_ens2m       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst2_mean      */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret nvalid          */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_verify_2_ensemble_forecasts_W,args,"ncl_c_verify_2",nargs);
  
/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(30);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcst1             */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcst2             */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* obs               */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst1_AE      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst1_Err     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst2_AE      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst2_Err     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret obs_Mean      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_obs       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MAE        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret SS_MSE        */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst1_MAE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst1_MSE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst1_Bias    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst1_RelBias */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst1_Corr    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst1_SpCr    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_fcst1     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst1_mean    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst2_MAE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst2_MSE     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst2_Bias    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst2_RelBias */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst2_Corr    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Fcst2_SpCr    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret var_fcst2     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret fcst2_mean    */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret nvalid        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims         */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims  */

  NclRegisterProc(ncl_c_verify_2_deterministic_forecasts_W,args,"ncl_c_verify_det_2",nargs);


  fprintf(stderr,"Finished\n");
}

