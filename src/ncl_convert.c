/* Created by Bill Scheftic */
#include <stdio.h>
/*
 * The following are the required NCAR Graphics include files.
 * They should be located in ${NCARG_ROOT}/include
 */

#include <ncl_c_wrap.h>		/* Contains all included headers, Type conversion Macros, and getVarFromNCL function */
#include <udunits2.h>
#include <stats2.h>
#include <arraystats2.h>
#include <print_arrays2.h>

cv_converter *openConverter(char *from,char *to,ut_system **unitSystem_ptr){
/*  fprintf(stderr,"openConverter: 1\n"); */
  ut_set_error_message_handler(ut_ignore);
  *unitSystem_ptr = ut_read_xml("/st3/scheftic/lib/ncarg/udunits/udunits2.xml");

  ut_unit *ut_from = ut_parse(*unitSystem_ptr, from, UT_ASCII);
  if (ut_from == NULL) {
    ut_status parse_err = ut_get_status ();
    fprintf(stderr,"Unable to parse from %s, Err: %d\n", from, parse_err);
    switch (parse_err) {
      case UT_BAD_ARG:
        fprintf(stderr,"system or string is NULL.\n");
	break;
      case UT_SYNTAX:
        fprintf(stderr,"string contained a syntax error.\n");
	break;
      case UT_UNKNOWN:
        fprintf(stderr,"string contained an unknown identifier.\n");
	break;
      case UT_OS:
        fprintf(stderr,"Operating-system failure. See errno for the reason.\n");
	break;
      default:
        fprintf(stderr,"Unknown Error.\n");
	break;
    }
    return NULL;
  }

  ut_unit *ut_to = ut_parse(*unitSystem_ptr, to, UT_ASCII);
  if (ut_to == NULL) {
    ut_status parse_err = ut_get_status ();
    fprintf(stderr,"Unable to parse to %s, Err: %d\n", to, parse_err);
    switch (parse_err) {
      case UT_BAD_ARG:
        fprintf(stderr,"system or string is NULL.\n");
	break;
      case UT_SYNTAX:
        fprintf(stderr,"string contained a syntax error.\n");
	break;
      case UT_UNKNOWN:
        fprintf(stderr,"string contained an unknown identifier.\n");
	break;
      case UT_OS:
        fprintf(stderr,"Operating-system failure. See errno for the reason.\n");
	break;
      default:
        fprintf(stderr,"Unknown Error.\n");
	break;
    }
    return NULL;
  }

  cv_converter *converter = ut_get_converter(ut_from, ut_to);

  return converter;
}

void closeConverter(cv_converter *converter,ut_system **unitSystem_ptr){
/*  fprintf(stderr,"closeConverter: 1\n"); */
  cv_free(converter);
  ut_free_system(*unitSystem_ptr);

  return;
}

NhlErrorTypes ncl_c_convert_W( void ) {
/*  fprintf(stderr,"convert_W: 1\n"); */
  int i;
  NhlErrorTypes retval;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */ 

  arr X = getVarFromNCL(0,3);
  char *from = getStringFromNCL(1,3);
  char *to   = getStringFromNCL(2,3);

/*
 * Call the C function.
 */

  
  ut_system *unitSystem;
  cv_converter *converter = openConverter(from, to, &unitSystem);
  if (converter){
    arr data;
    arr m = ArrayFromList(X.n,DOUBLE,X.len);
    arr Xi = castAr(&X,DOUBLE,0);
    copyMiss(&m,&Xi);
    double *p    = pntr_of(&m);
    double *pX   = pntr_of(&Xi);
    double xmiss = *(double *)getMiss(&Xi);
    for(i=0; i<m.tlen; i++,pX++){
    	if (*pX == xmiss){
    	  *p++ = xmiss;
    	} else {
    	  *p++ = cv_convert_double(converter, *pX);
    	}
    }
    freeAr(&Xi);
    data = castAr(&m,X.typ,1);
    
    closeConverter(converter,&unitSystem);
    retval = returnArToNCL(&data);
    
    freeAr(&data);
  } else {
    fprintf(stderr,"convert_W: error; can't be converted from %s to %s\n",from,to);
    retval = NhlFATAL;
  }
  freeArShell(&X);

/*
 * Set up return value.
 */ 

  return retval;
}


void Init(void){
  void *args;
  int nargs;
  fprintf(stderr,"Init: Initializing ncl_convert functions ...\n");

  ng_size_t dimsizes[NCL_MAX_DIMENSIONS];

/*
 * Register convert function.
 */
  nargs = 0;
  args = NewArgs(3);

  SetArgTemplate(args,nargs,NclANY,0,NclANY);	nargs++;
  dimsizes[0] = 1;
  SetArgTemplate(args,nargs,"string",1,dimsizes);	nargs++;
  SetArgTemplate(args,nargs,"string",1,dimsizes);	nargs++;

  NclRegisterFunc(ncl_c_convert_W,args,"ncl_c_convert",nargs);

}

