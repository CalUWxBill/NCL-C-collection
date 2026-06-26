/* Created by Bill Scheftic */
#include <stdio.h>
/*
 * The following are the required NCAR Graphics include files.
 * They should be located in ${NCARG_ROOT}/include
 */

#include <ncl_c_wrap.h>		/* Contains all included headers, Type conversion Macros, and getVarFromNCL function */
#include <arrayinit2.h>
#include <print_arrays2.h>
#include <wrap_hi2lo.h>
#include <ncl_stateq.h>

NhlErrorTypes ncl_c_Hi2LoIdxWgt_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_Hi2LoIdxWgt,12,5,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_Hi2LoIdxWgt_Ar_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_Hi2LoIdxWgt_Ar,4,5,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_upScaleIdxWgt_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx_Maps(wrap_upScaleIdxWgt,6,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_upScaleStatsIdxWgt_W( void ) {
  NhlErrorTypes retval = st_eqNarRNarNdblNintNidx_Maps(wrap_upScaleStatsIdxWgt,6,7,0,0,0);
  return retval;
}


void Init(void){
  void *args;
  int nargs;
  fprintf(stderr,"Init: Initializing ncl_hi2lo functions ...\n");

/*
 * Register functions accepting 2 n dimensional double arrays, 1 scalar integer and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(19);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64", 0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret N      */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret jIdxs  */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret iIdxs  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Wgts   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret WgtSum */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims  */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_Hi2LoIdxWgt_W,args,"ncl_c_hi2lo_idxwgt",nargs);

/*
 * Register functions accepting 2 n dimensional double arrays, 1 scalar integer and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(11);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++;
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret N      */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret jIdxs  */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* ret iIdxs  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Wgts   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret WgtSum */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims  */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_Hi2LoIdxWgt_Ar_W,args,"ncl_c_hi2lo_idxwgt_ar",nargs);

/*
 * Register functions accepting 2 n dimensional double arrays, 1 scalar integer and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(8);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* IN_hi  */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* N      */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* jIdxs  */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* iIdxs  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* Wgts   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* WgtSum */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_upScaleIdxWgt_W,args,"ncl_c_hi2lo_mean",nargs);

/*
 * Register functions accepting 2 n dimensional double arrays, 1 scalar integer and 1 statdim integer.
 */
  nargs = 0;
  args = NewArgs(15);

  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* IN_hi  */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* N      */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* jIdxs  */
  SetArgTemplate(args,nargs,"int64" ,0,NclANY);  nargs++; /* iIdxs  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* Wgts   */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* thresh */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret Mn     */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret min    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret max    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret med    */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret FrcAbv */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret sigma  */
  SetArgTemplate(args,nargs,"double",0,NclANY);  nargs++; /* ret MnAbv  */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims  */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterProc(ncl_c_upScaleStatsIdxWgt_W,args,"ncl_c_hi2lo_stats",nargs);

}

