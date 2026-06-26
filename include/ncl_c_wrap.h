/* Created by Bill Scheftic */
#ifndef  _NCL_C_WRAP_H_
#define  _NCL_C_WRAP_H_

#include <stdio.h>
/*
 * The following are the required NCAR Graphics include files.
 * They should be located in ${NCARG_ROOT}/include
 */
#include <ncarg/hlu/hlu.h>
#include <ncarg/hlu/NresDB.h>
#include <ncarg/ncl/defs.h>
#include <ncarg/ncl/NclDataDefs.h>
#include <ncarg/ncl/NclBuiltInSupport.h>
#include <ncarg/ncl/NclBuiltIns.h>
#include <arrayinit2.h>

/* The following macro assumes int and long are the same! */
#define NCLTYPECASES                                        \
case NCL_byte:                                              \
	NCL_SWITCHCAST(byteval,NCL_byte,byt,missbyt,signed char,BYTE,BYT,cBYT,compare_byts,"%10d","%10d") \
	break;                                                  \
case NCL_short:                                             \
	NCL_SWITCHCAST(shortval,NCL_short,shrt,missshrt,short,SHORT,SHT,cSHT,compare_shrts,"%10d","%10d")\
	break;                                                  \
case NCL_int:                                               \
	NCL_SWITCHCAST(intval,NCL_int,intg,missintg,int,INT,INTG,cINTG,compare_ints,"%10d","%10d") \
	break;                                                  \
case NCL_long:                                              \
	NCL_SWITCHCAST(longval,NCL_long,intg,missintg,int,INT,INTG,cINTG,compare_ints,"%10d","%10d") \
	break;                                                  \
case NCL_float:                                             \
	NCL_SWITCHCAST(floatval,NCL_float,flt,missflt,float,FLOAT,FLT,cFLT,compare_flts,"%10g","%10g") \
	break;                                                  \
case NCL_double:                                            \
	NCL_SWITCHCAST(doubleval,NCL_double,dbl,missdbl,double,DOUBLE,DBL,cDBL,compare_dbls,"%10g","%10g") \
	break;                                                  \
case NCL_char:                                              \
	NCL_SWITCHCAST(charval,NCL_char,ubyt,missubyt,unsigned char,UBYTE,UBYT,cUBYT,compare_ubyts,"%10d","%10d") \
	break;                                                  \
case NCL_ushort:                                            \
	NCL_SWITCHCAST(ushortval,NCL_ushort,ushrt,missushrt,unsigned short,USHORT,USHT,cUSHT,compare_ushrts,"%10d","%10d") \
	break;                                                  \
case NCL_uint:                                              \
	NCL_SWITCHCAST(uintval,NCL_uint,uint,missuint,unsigned int,UINT,UINTG,cUINTG,compare_uints,"%10d","%10d") \
	break;                                                  \
case NCL_ulong:                                             \
	NCL_SWITCHCAST(ulongval,NCL_ulong,uint,missuint,unsigned int,UINT,UINTG,cUINTG,compare_uints,"%10d","%10d") \
	break;                                                  \
case NCL_int64:                                             \
	NCL_SWITCHCAST(int64val,NCL_int64,int64,missint64,long long,INT64,LINT,cLINT,compare_int64s,"%10d","%10d") \
	break;                                                  \
case NCL_uint64:                                            \
	NCL_SWITCHCAST(uint64val,NCL_uint64,uint64,missuint64,unsigned long long,UINT64,ULINT,cULINT,compare_uint64s,"%10d","%10d") \
	break;


/* The following macro assumes int and long are the same! */
int typeNCLToAr(ncltyp){
  switch (ncltyp) {
	case NCL_byte:
		return BYTE;
		break;
	case NCL_short:
		return SHORT;
		break;
	case NCL_int:
		return INT;
		break;
	case NCL_long:
		return INT;
		break;
	case NCL_float:
		return FLOAT;
		break;
	case NCL_double:
		return DOUBLE;
		break;
	case NCL_char:
		return UBYTE;
		break;
	case NCL_ushort:
		return USHORT;
		break;
	case NCL_uint:
		return UINT;
		break;
	case NCL_ulong:
		return UINT;
		break;
	case NCL_int64:
		return INT64;
		break;
	case NCL_uint64:
		return UINT64;
		break;
      default:
        fprintf(stderr,"Error in typeNCLToAr: cannot process this type! ncltyp=%d\n",ncltyp);
        exit(0);
        break;
  }
  return -1;
}


/* The following macro casts INT to NCL_int and not NCL_long! */
int typeArToNCL(artyp){
  switch (artyp) {
	case BYTE:
		return NCL_byte;
		break;
	case CHAR:
		return NCL_byte;
		break;
	case SHORT:
		return NCL_short;
		break;
	case INT:
		return NCL_int;
		break;
	case FLOAT:
		return NCL_float;
		break;
	case DOUBLE:
		return NCL_double;
		break;
	case UBYTE:
		return NCL_char;
		break;
	case USHORT:
		return NCL_ushort;
		break;
	case UINT:
		return NCL_uint;
		break;
	case INT64:
		return NCL_int64;
		break;
	case UINT64:
		return NCL_uint64;
		break;
      default:
        fprintf(stderr,"Error in typeArToNCL: cannot process this type! artyp=%d\n",artyp);
        exit(0);
        break;
  }
  return -1;
}


arr getVarFromNCL(int varid,int numvars){
  if ((varid < 0) || (varid >= numvars)){
    fprintf(stderr,"Error in getVarFromNCL: invalid argument number! varid=%d, numvars=%d\n",varid,numvars);
    exit(0);
  }

  int i;
  void *tmp_void;
  ng_size_t var_dimsizes[NCL_MAX_DIMENSIONS];
  int n_dims;

  NclScalar missing;
  int       hasmissing;
  NclBasicDataTypes type;

  tmp_void   = (void *) NclGetArgValue(
    varid,
    numvars,
    &n_dims,
    var_dimsizes,
    &missing,
    &hasmissing,
    &type,
    1
  );

  typ_idx *var_dimsizes_int = NULL;
  if ((n_dims == 1) && (var_dimsizes[0]==1)){
    n_dims = 0;
  } else {
    var_dimsizes_int = malloc(n_dims*sizeof(typ_idx));
    for (i=0;i<n_dims;i++){
      var_dimsizes_int[i] = (typ_idx)var_dimsizes[i];
    }
  }

  arr retvar;
  switch (type) {
    #define NCL_SWITCHCAST(swnclval,swnclmacro,swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)	\
      retvar = assign1dtoNdFromList(tmp_void, n_dims, swmacro, var_dimsizes_int);								\
      if (hasmissing){ retvar.um.swmtyp = missing.swnclval; } else { /* might have to do something here */ }
      NCLTYPECASES
      default:
        fprintf(stderr,"Error in getVarFromNCL: arg %d of %d; cannot process this type! type=%d\n",varid,numvars,type);
        exit(0);
        break;
  }

  free(var_dimsizes_int);
  return(retvar);
}


char *getStringFromNCL(int varid,int numvars){
  if ((varid < 0) || (varid >= numvars)){
    fprintf(stderr,"Error in getStringFromNCL: invalid argument number! varid=%d, numvars=%d\n",varid,numvars);
    exit(0);
  }

  NclQuark *tmp_string;
  char *retvar;

  int i;
  int n_dims;

  NclScalar missing;
  int       hasmissing;
  NclBasicDataTypes type;

  tmp_string   = (void *) NclGetArgValue(
    varid,
    numvars,
    &n_dims,
    NULL,
    &missing,
    &hasmissing,
    &type,
    1
  );

  retvar = NrmQuarkToString(*tmp_string);
  return retvar;
}


NhlErrorTypes returnArToNCL(arr *out){
  int i;
  NhlErrorTypes retval;
  ng_size_t* retlen;
  NclScalar   ret_missing;

  int nout;
  if (out->n == 0){
    nout = 1;
    retlen = malloc(sizeof(ng_size_t));
    *retlen = 1;
  } else {
    nout = out->n;
    retlen = malloc(nout*sizeof(ng_size_t));
    for (i=0;i<out->n;i++){ retlen[i] = (ng_size_t)out->len[i]; }
  }
  switch (typeArToNCL(out->typ)) {
    #define NCL_SWITCHCAST(swnclval,swnclmacro,swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)	\
      ret_missing.swnclval = out->um.swmtyp;								\
      retval = NclReturnValue(pntr_of(out),nout,retlen,&ret_missing,swnclmacro,1);
      NCLTYPECASES
      default:
        fprintf(stderr,"Error in returnArToNCL: cannot process this type! outncltyp=%d\n",typeArToNCL(out->typ));
        exit(0);
        break;
  }

  free(retlen);
  return retval;
}


NhlErrorTypes returnValToNCL(void *out,void *outmiss,int intyp,int outtyp){
  NhlErrorTypes retval;
  ng_size_t *retlen = malloc(sizeof(ng_size_t));
  NclScalar   ret_missing;
  MultiTypeVal rval;
  void *tval1, *tval2;

  *retlen = 1;
  switch (typeArToNCL(outtyp)) {
    #define NCL_SWITCHCAST(swnclval,swnclmacro,swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)	\
      tval1 = translateType(outmiss,intyp,outtyp);	\
      tval2 = translateType(out,intyp,outtyp);		\
      ret_missing.swnclval = *(swcast *)tval1;		\
      rval.swtyp = *(swcast *)tval2;			\
      free(tval1);						\
      free(tval2);						\
      retval = NclReturnValue(&(rval.swtyp),1,retlen,&ret_missing,swnclmacro,1);
      NCLTYPECASES
      default:
        fprintf(stderr,"Error in returnValToNCL: cannot process this type! outncltyp=%d\n",typeArToNCL(outtyp));
        exit(0);
        break;
  }

  free(retlen);
  return retval;
}

#endif
