/* Created by Bill Scheftic */
#include <stdio.h>
/*
 * should rename ncl_misc
 * The following are the required NCAR Graphics include files.
 * They should be located in ${NCARG_ROOT}/include
 */

#include <ncl_c_wrap.h>		/* Contains all included headers, Type conversion Macros, and getVarFromNCL function */
#include <wrap_sort.h>
#include <ncl_stateq.h>


/* arr func(arr) */
NhlErrorTypes ncl_c_qsort_idx_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx(wrap_qsort_idx,1,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_qsort_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx(wrap_qsort,1,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_qsort_idx_rev_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx(wrap_qsort_idx_rev,1,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_qsort_rev_W( void ) {
  NhlErrorTypes retval = st_arr_eqNarRNarNdblNintNidx(wrap_qsort_rev,1,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_countNonMiss2Arrays_W( void ) {
  NhlErrorTypes retval = st_idx_eqNarRNarNdblNintNidx_Maps(wrap_countNonMissNArrays,2,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_countNonMiss3Arrays_W( void ) {
  NhlErrorTypes retval = st_idx_eqNarRNarNdblNintNidx_Maps(wrap_countNonMissNArrays,3,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_countNonMiss4Arrays_W( void ) {
  NhlErrorTypes retval = st_idx_eqNarRNarNdblNintNidx_Maps(wrap_countNonMissNArrays,4,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_countNonMiss_W( void ) {
  NhlErrorTypes retval = st_idx_eqNarRNarNdblNintNidx(wrap_countNonMiss,1,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_countMiss_W( void ) {
  NhlErrorTypes retval = st_idx_eqNarRNarNdblNintNidx(wrap_countMiss,1,0,0,0,0);
  return retval;
}

NhlErrorTypes ncl_c_isAnyMiss_W( void ) {
  NhlErrorTypes retval = st_int_eqNarRNarNdblNint(wrap_isAnyMiss,1,0,0,0);
  return retval;
}


void Init(void){
  void *args;
  int nargs;
  fprintf(stderr,"Init: Initializing ncl_sort functions ...\n");

/* In: 1 arr, 1 int arr Return: 1 arr */
  nargs = 0;
  args = NewArgs(2);

  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */

  NclRegisterFunc(ncl_c_qsort_idx_W,     args,"ncl_c_qsort_idx",    nargs); /* ret: array */
  NclRegisterFunc(ncl_c_qsort_W,         args,"ncl_c_qsort",        nargs); /* ret: array */
  NclRegisterFunc(ncl_c_qsort_idx_rev_W, args,"ncl_c_qsort_idx_rev",nargs); /* ret: array */
  NclRegisterFunc(ncl_c_qsort_rev_W,     args,"ncl_c_qsort_rev",    nargs); /* ret: array */
  NclRegisterFunc(ncl_c_countNonMiss_W,  args,"ncl_c_nnonmiss",     nargs); /* ret: int64 */
  NclRegisterFunc(ncl_c_countMiss_W,     args,"ncl_c_nmiss",        nargs); /* ret: int64 */
  NclRegisterFunc(ncl_c_isAnyMiss_W,     args,"ncl_c_isanymiss",    nargs); /* ret: int   */

/* In: 1 arr, 1 int arr Return: 1 arr */
  nargs = 0;
  args = NewArgs(4);

  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_countNonMiss2Arrays_W,  args,"ncl_c_nvalid_2",     nargs); /* ret: int64 */

/* In: 1 arr, 1 int arr Return: 1 arr */
  nargs = 0;
  args = NewArgs(5);

  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_countNonMiss3Arrays_W,  args,"ncl_c_nvalid_3",     nargs); /* ret: int64 */

/* In: 1 arr, 1 int arr Return: 1 arr */
  nargs = 0;
  args = NewArgs(6);

  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"double", 0,NclANY); nargs++;
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* stat dims */
  SetArgTemplate(args,nargs,"integer",0,NclANY); nargs++; /* maps to all dims */

  NclRegisterFunc(ncl_c_countNonMiss4Arrays_W,  args,"ncl_c_nvalid_4",     nargs); /* ret: int64 */

}

