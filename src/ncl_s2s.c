/* Created by Bill Scheftic */
#include <stdio.h>
/*
 * The following are the required NCAR Graphics include files.
 * They should be located in ${NCARG_ROOT}/include
 */
/*
#define DEBUG_ARRAYND_LOOPS
*/

#include <ncl_c_wrap.h>		/* Contains all included headers, Type conversion Macros, and getVarFromNCL function */
#include <arrayinit2.h>
#include <stats2.h>
#include <arraystats2.h>
#include <print_arrays2.h>
#include <wrap_s2s.h>
#include <ncl_stateq.h>

NhlErrorTypes ncl_c_getPercZscoreFromCDF_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_getPercZscoreFromCDF,5,2,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_getPercZscoreFromCDF_1_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_getPercZscoreFromCDF_1,5,0,2,0,0);
  return retval;
}

NhlErrorTypes ncl_c_getPdfCdf_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_getPdfCdf,5,2,0,0,0);
  return retval;
}


NhlErrorTypes ncl_c_getTertiaryExtremes_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_getTertiaryExtremes,5,0,5,0,0);
  return retval;
}

NhlErrorTypes ncl_c_getTertiaryExtremes_z_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_getTertiaryExtremes_z,1,0,5,0,0);
  return retval;
}



NhlErrorTypes ncl_c_getMultiRegression_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_getMultiRegression,4,4,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_getMultiRegression_min_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_getMultiRegression_min,5,4,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_getMultiRegression_min_Prescribed_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_getMultiRegression_min_Prescribed,6,3,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_applyMultiRegression_W( void ) {
  NhlErrorTypes retval = st_dbl_eqNarRNarNdblNintNidx_Maps(wrap_applyMultiRegression,6,0,0,0,0);
  return retval;
}



NhlErrorTypes ncl_c_sortedCDF_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_sortedCDF,1,2,0,0,0);
  return retval;
}



NhlErrorTypes ncl_c_ensemble_z_weighted_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx_Maps(wrap_ensemble_z_weighted,3,0,0,0,0);
  return retval;
}



NhlErrorTypes ncl_c_getPersistenceNLeads_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx_Maps(wrap_getPersistenceNLeads,2,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_getPersistenceNLeads_Lag_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx_Maps(wrap_getPersistenceNLeads_Lag,3,0,0,0,0);
  return retval;
}


NhlErrorTypes ncl_c_Start2ValidTime_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx(wrap_Start2ValidTime,1,0,0,0,0);
  return retval;
}


NhlErrorTypes ncl_c_printArray_W( void ) {
  arr     X = getVarFromNCL(0,2);
  char *fmt = getStringFromNCL(1,2);

  printArrayFmtAllWHdr(stdout,&X,fmt,"print_array: ");

  freeArShell(&X);
  return(NhlNOERROR);
}


void Init(void){
  void *args;
  int nargs;
  ng_size_t dimsizes[NCL_MAX_DIMENSIONS];

  fprintf(stderr,"Init: Initializing ncl_s2s functions ...\n");


/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(2);

  SetArgTemplate(args,nargs,NclANY,  0,NclANY);   nargs++;
  dimsizes[0] = 1;
  SetArgTemplate(args,nargs,"string",1,dimsizes); nargs++;

  NclRegisterProc(ncl_c_printArray_W, args, "ncl_c_print_array", nargs);
  
/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(2);

  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */

  NclRegisterFunc(ncl_c_Start2ValidTime_W,       args,"ncl_c_start_2_valid", nargs);
  
/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"int64",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_getPersistenceNLeads_W, args,"ncl_c_get_persNld", nargs);
  
/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"int64",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"int64",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_getPersistenceNLeads_Lag_W, args,"ncl_c_get_persNld_Lag", nargs);
  
/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(9);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* Fr     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* Fr_cdf */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* bbndry */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ebndry */
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++; /* n      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret z  */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_getPercZscoreFromCDF_W,  args,"ncl_c_get_P_z_cdf",  nargs);
  NclRegisterProc(ncl_c_getPercZscoreFromCDF_1_W,args,"ncl_c_get_P_z_cdf_1",nargs);
  NclRegisterProc(ncl_c_getPdfCdf_W,             args,"ncl_c_get_pdf_cdf",  nargs);
  
/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(12);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* Fr     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* Fr_cdf */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* bbndry */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ebndry */
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++; /* n      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_vlo */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_lo  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_mid */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_hi  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_vhi */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_getTertiaryExtremes_W,  args,"ncl_c_get_tertiary",  nargs);
  
/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(8);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* Fr     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_vlo */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_lo  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_mid */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_hi  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret P_vhi */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_getTertiaryExtremes_z_W,  args,"ncl_c_get_tertiary_z",  nargs);


/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(10);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcstens_z  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* obs_z      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* TC         */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* rsq_thresh */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ms     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret bs     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret rsqs   */
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++; /* ret idxs   */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_getMultiRegression_W,args,     "ncl_c_get_multi_regr",      nargs);

/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(11);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcstens_z  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* obs_z      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* TC         */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* t_sig      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* rsq_thresh */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ms     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret bs     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret rsqs   */
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++; /* ret idxs   */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_getMultiRegression_min_W,args, "ncl_c_get_multi_regr_min",  nargs);

/*
 * Register verify function.
 */
  nargs = 0;
  args = NewArgs(11);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* fcstens_z  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* obs_z      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* TC         */
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++; /* idxs       */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* t_sig      */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* rsq_thresh */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret ms     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret bs     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret rsqs   */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims        */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_getMultiRegression_min_Prescribed_W,args, "ncl_c_get_multi_regr_min_prscrbd",  nargs);


/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(8);

  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"int64", 0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_applyMultiRegression_W,args,"ncl_c_apply_multi_regr",nargs);


/*
 * Register functions accepting 2 n dimensional double arrays and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);	 nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_sortedCDF_W,               args,"ncl_c_fit_cdf",nargs);
}

