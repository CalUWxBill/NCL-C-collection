/* Created by Bill Scheftic */
/*-------------------------------------------------*/
/* Header for 1d Statistic Processing of nd arrays */
/*-------------------------------------------------*/
/*
 *  Things to add:
 *  --------------
 *  + + http://www.ncl.ucar.edu/Document/Functions/Built-in/regCoef.shtml for output dimensions
 */
#ifndef  _STATS2_E_
#define  _STATS2_E_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <math_supp.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <arraynd.h>
#include <wrap_stats2.h>
#include <arrayftypes.h>

/*------------------------*/
/* Function Declarations  */
/*------------------------*/

typ_idx *initStatsIdx(typ_idx *c,typ_idx ndims,typ_idx avedim);
typ_idx *initStatsIdxVal(typ_idx *c,typ_idx ndims,typ_idx avedim,typ_idx avedimidx);
arr c_cdiff(arr *restrict IN);
void cdiff_WLoop(arr *restrict OUT, arr *restrict IN, typ_idx avedim, typ_idx dim, typ_idx *c, typ_idx *clens);
arr cdiff_W(arr *restrict IN, typ_idx statdim);
arr d_dx(arr *restrict Xin, arr *restrict IN);
void d_dx_WLoop(arr *restrict OUT, arr *restrict Xin, arr *restrict IN, typ_idx avedim, typ_idx dim, typ_idx *c, typ_idx *clens);
arr d_dx_W(arr *restrict Xin, arr *restrict IN, typ_idx statdim);
arr arStatArg1ar(fctArgsRdbl fct,arr *restrict X,typ_idx avedim);
arr arStatArg2ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,typ_idx avedim);
arr arStatArg3ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,typ_idx avedim);
arr arStatArg4ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,typ_idx avedim);
arr arStatArg5ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,arr *restrict U,typ_idx avedim);
arr arStatArg1ar1s(fctArgsRdbl fct,arr *restrict X,double xdbl,typ_idx avedim);
arr arStatArg2ar1s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,double xdbl,typ_idx avedim);
arr arStatArg2ar2s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,double xdbl,double ydbl,typ_idx avedim);
arr arStatArg2ar3s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,double xdbl,double ydbl,double zdbl,typ_idx avedim);
arr arStatArg3ar2s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,double xdbl,double ydbl,typ_idx avedim);
arr arStatArg3ar3s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,double xdbl,double ydbl,double zdbl,typ_idx avedim);
arr arStatArg4ar2s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,double xdbl,double ydbl,typ_idx avedim);
arr arStatArg1ar1intRet1dbl(fctArgsRdbl fct,arr *restrict X,int xint,typ_idx avedim);
arr arStatArg2ar1intRet1dbl(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,int xint,typ_idx avedim);
arr arStatArg2ar2intRet1dbl(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,int xint,int yint,typ_idx avedim);
arr arStatArg3ar2intRet1dbl(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,int xint,int yint,typ_idx avedim);
arr arStatArg4ar2intRet1dbl(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,int xint,int yint,typ_idx avedim);
arr arStatArg1arRet1Int1Dbl(fctArgsRint fct,arr *restrict X,arr *R1,typ_idx avedim);
arr arStatArg1arRet1Int2Dbl(fctArgsRint fct,arr *restrict X,arr *R1,arr *R2,typ_idx avedim);
arr arStatArg2arRet1Int1Dbl(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *R1,typ_idx avedim);
arr arStatArg2arRet1Int2Dbl(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *R1,arr *R2,typ_idx avedim);
arr arStatArg3arRet1Int1Dbl(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *R1,typ_idx avedim);
arr arStatArg3arRet1Int2Dbl(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *R1,arr *R2,typ_idx avedim);
arr arStatArg1arRet1int(fctArgsRint fct,arr *restrict X,typ_idx avedim);
arr arStatArg2arRet1int(fctArgsRint fct,arr *restrict X,arr *restrict Y,typ_idx avedim);
arr arStatArg3arRet1int(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *restrict Z,typ_idx avedim);
arr arStatArg4arRet1int(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,typ_idx avedim);
arr arStatArg1ar1int(fctArgsRint fct,arr *restrict X,int xint,typ_idx avedim);
arr arStatArg2ar1int(fctArgsRint fct,arr *restrict X,arr *restrict Y,int xint,typ_idx avedim);
arr arStatArg2ar2int(fctArgsRint fct,arr *restrict X,arr *restrict Y,int xint,int yint,typ_idx avedim);
arr arStatArg3ar2int(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *restrict Z,int xint,int yint,typ_idx avedim);
arr arStatArg4ar2int(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,int xint,int yint,typ_idx avedim);
arr arStatArg1ar1sRet1int(fctArgsRint fct,arr *restrict X,double xdbl,typ_idx avedim);
arr arStatArg2ar1sRet1int(fctArgsRint fct,arr *restrict X,arr *restrict Y,double xdbl,typ_idx avedim);
arr arStatArg2ar2sRet1int(fctArgsRint fct,arr *restrict X,arr *restrict Y,double xdbl,double ydbl,typ_idx avedim);
arr arStatArg3ar2sRet1int(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *restrict Z,double xdbl,double ydbl,typ_idx avedim);
arr arStatArg4ar2sRet1int(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,double xdbl,double ydbl,typ_idx avedim);
void arStatArgNarNsBegEndLoop(
    fctArgsRdbl fct,arr *restrict OUT,arr *restrict times,arr *restrict B,arr *restrict E,
    arr **arrays, double *dbl_ptr, int *int_ptr,
    int narrs, int ndbls, int nints,
    typ_idx ndims, typ_idx *map_o2c,typ_idx *map_t2o,typ_idx *map_b2o,typ_idx *map_e2o,typ_idx **map_as2o,
    typ_idx adims_t,typ_idx adims_b,typ_idx adims_e,typ_idx *adims,typ_idx dim,typ_idx *c);
arr arStatArgNarNsBegEnd(
    fctArgsRdbl fct,arr *restrict times,arr *restrict B,arr *restrict E,
    int narrs,int ndbls,int nints,
    arr **arrays,double *dbl_ptr,int *int_ptr,
    typ_idx avedim);
arr arStatArg1arBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,typ_idx avedim);
arr arStatArg2arBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,arr *restrict Y,typ_idx avedim);
arr arStatArg3arBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,arr *restrict Y,arr *restrict Z,typ_idx avedim);
arr arStatArg4arBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,typ_idx avedim);
arr arStatArg1ar1sBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,double xdbl,typ_idx avedim);
arr arStatArg2ar1sBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,arr *restrict Y,double xdbl,typ_idx avedim);
arr arStatArg2ar2sBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,arr *restrict Y,double xdbl,double ydbl,typ_idx avedim);
arr arStatArg3ar2sBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,arr *restrict Y,arr *restrict Z,double xdbl,double ydbl,typ_idx avedim);
arr arStatArg4ar2sBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,double xdbl,double ydbl,typ_idx avedim);

/*-----------*/
/* Functions */
/*-----------*/
typ_idx *initStatsIdx(typ_idx *c,typ_idx ndims,typ_idx avedim){
	if ((avedim < 0) || (ndims <= avedim)){
		fprintf(stderr,"Error in initStatsIdx: Invalid dimension as 3rd argument! ndims=%lld, avedim=%lld\n",ndims,avedim);
		exit(0);
	}
	typ_idx i;
	typ_idx *idx = init0(ndims,TYPIDX);
	for(i=0;i<ndims;i++){
		if (i < avedim){
			idx[i] = c[i];
		} else if (i == avedim) {
			idx[i] = 0;
		} else {
			idx[i] = c[i-1];
		}
	}
	return idx;
}

typ_idx *initStatsIdxVal(typ_idx *c,typ_idx ndims,typ_idx avedim,typ_idx avedimidx){
	if ((avedim < 0) || (ndims <= avedim)){
		fprintf(stderr,"Error in initStatsIdxVal: Invalid dimension as 3rd argument! ndims=%lld, avedim=%lld\n",ndims,avedim);
		exit(0);
	}
	typ_idx i;
	typ_idx *idx = init0(ndims,TYPIDX);
	for(i=0;i<ndims;i++){
		if (i < avedim){
			idx[i] = c[i];
		} else if (i == avedim) {
			idx[i] = avedimidx;
		} else {
			idx[i] = c[i-1];
		}
	}
	return idx;
}



arr c_cdiff(arr *restrict IN){
	typ_idx i;
	arr Y = castAr(IN,DOUBLE,0);
	arr m = ArrayFromList(Y.n,DOUBLE,Y.len);
    copyMiss(&m,&Y);

	i = 0;
	if(isMiss(&Y,i) || isMiss(&Y,i+1)){
        setToMiss(&m,i);
	} else {
		iDBL(&m,i) = iDBL(&Y,i+1)-iDBL(&Y,i);
	}
	for(i=1;i<Y.tlen-1;i++){
		if(isMiss(&Y,i-1) || isMiss(&Y,i+1)){
            setToMiss(&m,i);
		} else {
			iDBL(&m,i) = iDBL(&Y,i+1)-iDBL(&Y,i-1);
		}
	}
	if(isMiss(&Y,i-1) || isMiss(&Y,i)){
        setToMiss(&m,i);
	} else {
		iDBL(&m,i) = iDBL(&Y,i)-iDBL(&Y,i-1);
	}

	freeAr(&Y);
	return m;
}


void cdiff_WLoop(arr *restrict OUT, arr *restrict IN, typ_idx avedim, typ_idx dim, typ_idx *c, typ_idx *clens){
/*	This is a recursive n dimensional loop function	*/
	typ_idx k;
	typ_idx *idx;
	arr IN1d;
	arr OUT1d;

/*	fputs("cdiff_WLoop: 1\n",stderr);	*/
	if (dim == IN->n-1){
	/*	What is computed inside all loops	*/
		idx = initStatsIdx(c,IN->n,avedim);
		IN1d = grab1dAr(IN, avedim, idx);
		/*
		 *	The following is the call to the code for determining seasonal modes!
		 */
		if (!countMiss(&IN1d)){
			OUT1d = c_cdiff( &IN1d );
			for(k=0;k<OUT1d.tlen;k++){
				idx[avedim]   = k;
				cDBL(OUT,idx) = iDBL(&OUT1d,k);
			}
			freeAr(&OUT1d);
		} else {
			for(k=0;k<OUT->len[avedim];k++){
				idx[avedim]   = k;
                setToMissc(OUT,idx);
			}
		}
		free(idx);
		freeAr(&IN1d);
		return;
	} else {
		for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
		/*	Uncomment to print loop counter c
			fputs("cdiff_WLoop: ",stderr);
			for(j=0;j<=dim;j++){
				fprintf(stderr,"c[%lld]=%lld ",j,c[j]);
			}
			fputs("\n",stderr);
		 */
			cdiff_WLoop(OUT,IN,avedim,dim+1,c,clens);
		}
	}

	return;
}


arr cdiff_W(arr *restrict IN, typ_idx statdim) {
  typ_idx k;

/*
 *  Check input variables.
 *  - IN should be at least 1d
 */

  fputs("cdiff_W: 1\n",stderr);
  if ((IN->n < 1) || (IN->tlen <= 1)){
    fprintf(stderr,"cdiff: IN at least needs to be a one dimensional array!\n");
    exit(0);
  }

/*
 * Call the C function.
 */
  arr data;

  if (IN->n == 1){
    if (!countMiss(IN)){
      data = c_cdiff( IN );
    } else {
      data = Array(1,DOUBLE,IN->tlen);
      copyMiss(&data,IN);
      fillArWithMiss(&data);
    }
  } else {
    typ_idx *clens = init0((IN->n-1),TYPIDX);

    for (k=0;k<IN->n-1;k++){
      if (k < statdim){
        clens[k] = IN->len[k];
      } else if (k > statdim) {
        clens[k-1] = IN->len[k];
      }
    }

    data = ArrayFromList(IN->n,DOUBLE,IN->len);
    typ_idx *c = init0(IN->n-1,TYPIDX);
    cdiff_WLoop(&data,IN,statdim,0,c,clens);
    free(c);
    free(clens);
  }

  return data;
}



arr d_dx(arr *restrict Xin, arr *restrict IN){
	typ_idx i;
	arr X = castAr(Xin,DOUBLE,0);
	arr Y = castAr(IN,DOUBLE,0);
	arr m = ArrayFromList(Y.n,DOUBLE,Y.len);
    copyMiss(&m,&Y);

	i = 0;
	if(isMiss(&X,i) || isMiss(&Y,i) || isMiss(&X,i+1) || isMiss(&Y,i+1)){
        setToMiss(&m,i);
	} else {
		iDBL(&m,i) = (iDBL(&Y,i+1)-iDBL(&Y,i))/(iDBL(&X,i+1)-iDBL(&X,i));
	}
	for(i=1;i<X.tlen-1;i++){
		if(isMiss(&X,i-1) || isMiss(&Y,i-1) || isMiss(&X,i+1) || isMiss(&Y,i+1)){
            setToMiss(&m,i);
		} else {
			iDBL(&m,i) = (iDBL(&Y,i+1)-iDBL(&Y,i-1))/(iDBL(&X,i+1)-iDBL(&X,i-1));
		}
	}
	if(isMiss(&X,i-1) || isMiss(&Y,i-1) || isMiss(&X,i) || isMiss(&Y,i)){
        setToMiss(&m,i);
	} else {
		iDBL(&m,i) = (iDBL(&Y,i)-iDBL(&Y,i-1))/(iDBL(&X,i)-iDBL(&X,i-1));
	}

	freeAr(&X);
	freeAr(&Y);
	return m;
}


void d_dx_WLoop(arr *restrict OUT, arr *restrict Xin, arr *restrict IN, typ_idx avedim, typ_idx dim, typ_idx *c, typ_idx *clens){
/*	This is a recursive n dimensional loop function	*/
	typ_idx k;
	typ_idx *idx;
	arr IN1d;
	arr OUT1d;

/*	fputs("d_dx_WLoop: 1\n",stderr);	*/
	if (dim == IN->n-1){
	/*	What is computed inside all loops	*/
		idx = initStatsIdx(c,IN->n,avedim);
		IN1d = grab1dAr(IN, avedim, idx);
		/*
		 *	The following is the call to the code for determining seasonal modes!
		 */
		if (!countMiss(&IN1d)){
			OUT1d = d_dx( Xin, &IN1d );
			for(k=0;k<OUT1d.tlen;k++){
				idx[avedim]   = k;
				cDBL(OUT,idx) = iDBL(&OUT1d,k);
			}
			freeAr(&OUT1d);
		} else {
			for(k=0;k<OUT->len[avedim];k++){
				idx[avedim]   = k;
                setToMissc(OUT,idx);
			}
		}
		free(idx);
		freeAr(&IN1d);
		return;
	} else {
		for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
		/*	Uncomment to print loop counter c
			fputs("d_dx_WLoop: ",stderr);
			for(j=0;j<=dim;j++){
				fprintf(stderr,"c[%lld]=%lld ",j,c[j]);
			}
			fputs("\n",stderr);
		 */
			d_dx_WLoop(OUT,Xin,IN,avedim,dim+1,c,clens);
		}
	}

	return;
}


arr d_dx_W(arr *restrict Xin, arr *restrict IN, typ_idx statdim) {
  typ_idx k;

/*
 *  Check input variables.
 *  - Xin should be 1d
 *  - IN should be at least 1d
 *  - statdim is the dim of IN that matches the length of Xin.
 */

  fputs("d_dx_W: 1\n",stderr);
  if (Xin->n != 1){
    fprintf(stderr,"d_dx: Xin must be a one dimensional array!\n");
    exit(0);
  }
  if ((IN->n < 1) || (IN->tlen <= 1)){
    fprintf(stderr,"d_dx: IN at least needs to be a one dimensional array!\n");
    exit(0);
  }

/*
 * Call the C function.
 */
  arr data;

  if (IN->n == 1){
    if (!countMiss(IN)){
      data = d_dx( Xin, IN );
    } else {
      data = Array(1,DOUBLE,IN->tlen);
      copyMiss(&data,IN);
      fillArWithMiss(&data);
    }
  } else {
    typ_idx *clens = init0((IN->n-1),TYPIDX);

    for (k=0;k<IN->n-1;k++){
      if (k < statdim){
        clens[k] = IN->len[k];
      } else if (k > statdim) {
        clens[k-1] = IN->len[k];
      }
    }

    data = ArrayFromList(IN->n,DOUBLE,IN->len);
    typ_idx *c = init0(IN->n-1,TYPIDX);
    d_dx_WLoop(&data,Xin,IN,statdim,0,c,clens);
    free(c);
    free(clens);
  }

  return data;
}




arr arStatArg1ar(fctArgsRdbl fct,arr *restrict X,typ_idx avedim){
	int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,0,0,0,0,0,
        arrays,NULL,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	return OUT;
}


arr arStatArg2ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,typ_idx avedim){
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,0,0,0,0,0,
        arrays,NULL,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	return OUT;
}


arr arStatArg3ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,typ_idx avedim){
	int narrs = 3;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,0,0,0,0,0,
        arrays,NULL,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	return OUT;
}


arr arStatArg4ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,typ_idx avedim){
	int narrs = 4;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = T;

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,0,0,0,0,0,
        arrays,NULL,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	return OUT;
}


arr arStatArg5ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,arr *restrict U,typ_idx avedim){
	int narrs = 5;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = T;
	arrays[4] = U;

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,0,0,0,0,0,
        arrays,NULL,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	return OUT;
}


arr arStatArg1ar1s(fctArgsRdbl fct,arr *restrict X,double xdbl,typ_idx avedim){
	int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

	int ndbls = 1;
	double *dbl_ptr = dbls(ndbls, xdbl);

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,
        arrays,dbl_ptr,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}


arr arStatArg2ar1s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,double xdbl,typ_idx avedim){
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	int ndbls = 1;
	double *dbl_ptr = dbls(ndbls, xdbl);

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,
        arrays,dbl_ptr,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}


arr arStatArg2ar2s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,double xdbl,double ydbl,typ_idx avedim){
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	int ndbls = 2;
	double *dbl_ptr = dbls(ndbls, xdbl, ydbl);

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,
        arrays,dbl_ptr,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}


arr arStatArg2ar3s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,double xdbl,double ydbl,double zdbl,typ_idx avedim){
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	int ndbls = 3;
	double *dbl_ptr = dbls(ndbls, xdbl, ydbl, zdbl);

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,
        arrays,dbl_ptr,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}


arr arStatArg3ar2s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,double xdbl,double ydbl,typ_idx avedim){
	int narrs = 3;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

	int ndbls = 2;
	double *dbl_ptr = dbls(ndbls, xdbl, ydbl);

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,
        arrays,dbl_ptr,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}


arr arStatArg3ar3s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,double xdbl,double ydbl,double zdbl,typ_idx avedim){
	int narrs = 3;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

	int ndbls = 3;
	double *dbl_ptr = dbls(ndbls, xdbl, ydbl, zdbl);

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,
        arrays,dbl_ptr,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}


arr arStatArg4ar2s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,double xdbl,double ydbl,typ_idx avedim){
	int narrs = 4;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = T;

	int ndbls = 2;
	double *dbl_ptr = dbls(ndbls, xdbl, ydbl);

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,
        arrays,dbl_ptr,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}


arr arStatArg1ar1intRet1dbl(fctArgsRdbl fct,arr *restrict X,int xint,typ_idx avedim){
	int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

	int nints = 1;
	int *int_ptr = ints(nints, xint);

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,0,nints,0,0,0,
        arrays,NULL,int_ptr,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(int_ptr);
	return OUT;
}


arr arStatArg2ar1intRet1dbl(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,int xint,typ_idx avedim){
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	int nints = 1;
	int *int_ptr = ints(nints, xint);

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,0,nints,0,0,0,
        arrays,NULL,int_ptr,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(int_ptr);
	return OUT;
}


arr arStatArg2ar2intRet1dbl(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,int xint,int yint,typ_idx avedim){
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	int nints = 2;
	int *int_ptr = ints(nints, xint, yint);

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,0,nints,0,0,0,
        arrays,NULL,int_ptr,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(int_ptr);
	return OUT;
}


arr arStatArg3ar2intRet1dbl(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,int xint,int yint,typ_idx avedim){
	int narrs = 3;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

	int nints = 2;
	int *int_ptr = ints(nints, xint, yint);

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,0,nints,0,0,0,
        arrays,NULL,int_ptr,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(int_ptr);
	return OUT;
}


arr arStatArg4ar2intRet1dbl(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,int xint,int yint,typ_idx avedim){
	int narrs = 4;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = T;

	int nints = 2;
	int *int_ptr = ints(nints, xint, yint);

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,0,nints,0,0,0,
        arrays,NULL,int_ptr,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(int_ptr);
	return OUT;
}




arr arStatArg1arRet1Int1Dbl(fctArgsRint fct,arr *restrict X,arr *R1,typ_idx avedim){
	int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

	int nrdbls = 1;
	arr **R = malloc(nrdbls*sizeof(arr *));
	R[0] = R1;

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,0,0,0,nrdbls,0,
        arrays,NULL,NULL,NULL,R,NULL,1,&avedim);
	free(arrays);
	free(R);
	return OUT;
}


arr arStatArg1arRet1Int2Dbl(fctArgsRint fct,arr *restrict X,arr *R1,arr *R2,typ_idx avedim){
	int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

	int nrdbls = 2;
	arr **R = malloc(nrdbls*sizeof(arr *));
	R[0] = R1;
	R[1] = R2;

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,0,0,0,nrdbls,0,
        arrays,NULL,NULL,NULL,R,NULL,1,&avedim);
	free(arrays);
	free(R);
	return OUT;
}


arr arStatArg2arRet1Int1Dbl(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *R1,typ_idx avedim){
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	int nrdbls = 1;
	arr **R = malloc(nrdbls*sizeof(arr *));
	R[0] = R1;

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,0,0,0,nrdbls,0,
        arrays,NULL,NULL,NULL,R,NULL,1,&avedim);
	free(arrays);
	free(R);
	return OUT;
}


arr arStatArg2arRet1Int2Dbl(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *R1,arr *R2,typ_idx avedim){
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	int nrdbls = 2;
	arr **R = malloc(nrdbls*sizeof(arr *));
	R[0] = R1;
	R[1] = R2;

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,0,0,0,nrdbls,0,
        arrays,NULL,NULL,NULL,R,NULL,1,&avedim);
	free(arrays);
	free(R);
	return OUT;
}


arr arStatArg3arRet1Int1Dbl(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *R1,typ_idx avedim){
	int narrs = 3;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

	int nrdbls = 1;
	arr **R = malloc(nrdbls*sizeof(arr *));
	R[0] = R1;

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,0,0,0,nrdbls,0,
        arrays,NULL,NULL,NULL,R,NULL,1,&avedim);
	free(arrays);
	free(R);
	return OUT;
}


arr arStatArg3arRet1Int2Dbl(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *R1,arr *R2,typ_idx avedim){
	int narrs = 3;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

	int nrdbls = 2;
	arr **R = malloc(nrdbls*sizeof(arr *));
	R[0] = R1;
	R[1] = R2;

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,0,0,0,nrdbls,0,
        arrays,NULL,NULL,NULL,R,NULL,1,&avedim);
	free(arrays);
	free(R);
	return OUT;
}


arr arStatArg1arRet1int(fctArgsRint fct,arr *restrict X,typ_idx avedim){
	int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,0,0,0,0,0,
        arrays,NULL,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	return OUT;
}


arr arStatArg2arRet1int(fctArgsRint fct,arr *restrict X,arr *restrict Y,typ_idx avedim){
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,0,0,0,0,0,
        arrays,NULL,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	return OUT;
}


arr arStatArg3arRet1int(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *restrict Z,typ_idx avedim){
	int narrs = 3;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,0,0,0,0,0,
        arrays,NULL,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	return OUT;
}


arr arStatArg4arRet1int(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,typ_idx avedim){
	int narrs = 4;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = T;

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,0,0,0,0,0,
        arrays,NULL,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	return OUT;
}


arr arStatArg1ar1int(fctArgsRint fct,arr *restrict X,int xint,typ_idx avedim){
	int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

	int nints = 1;
	int *int_ptr = ints(nints, xint);

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,0,nints,0,0,0,
        arrays,NULL,int_ptr,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(int_ptr);
	return OUT;
}


arr arStatArg2ar1int(fctArgsRint fct,arr *restrict X,arr *restrict Y,int xint,typ_idx avedim){
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	int nints = 1;
	int *int_ptr = ints(nints, xint);

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,0,nints,0,0,0,
        arrays,NULL,int_ptr,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(int_ptr);
	return OUT;
}


arr arStatArg2ar2int(fctArgsRint fct,arr *restrict X,arr *restrict Y,int xint,int yint,typ_idx avedim){
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	int nints = 2;
	int *int_ptr = ints(nints, xint, yint);

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,0,nints,0,0,0,
        arrays,NULL,int_ptr,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(int_ptr);
	return OUT;
}


arr arStatArg3ar2int(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *restrict Z,int xint,int yint,typ_idx avedim){
	int narrs = 3;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

	int nints = 2;
	int *int_ptr = ints(nints, xint, yint);

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,0,nints,0,0,0,
        arrays,NULL,int_ptr,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(int_ptr);
	return OUT;
}


arr arStatArg4ar2int(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,int xint,int yint,typ_idx avedim){
	int narrs = 4;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = T;

	int nints = 2;
	int *int_ptr = ints(nints, xint, yint);

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,0,nints,0,0,0,
        arrays,NULL,int_ptr,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(int_ptr);
	return OUT;
}


arr arStatArg1ar1sRet1int(fctArgsRint fct,arr *restrict X,double xdbl,typ_idx avedim){
	int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

	int ndbls = 1;
	double *dbl_ptr = dbls(ndbls, xdbl);

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,
        arrays,dbl_ptr,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}


arr arStatArg2ar1sRet1int(fctArgsRint fct,arr *restrict X,arr *restrict Y,double xdbl,typ_idx avedim){
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	int ndbls = 1;
	double *dbl_ptr = dbls(ndbls, xdbl);

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,
        arrays,dbl_ptr,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}


arr arStatArg2ar2sRet1int(fctArgsRint fct,arr *restrict X,arr *restrict Y,double xdbl,double ydbl,typ_idx avedim){
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	int ndbls = 2;
	double *dbl_ptr = dbls(ndbls, xdbl, ydbl);

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,
        arrays,dbl_ptr,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}


arr arStatArg3ar2sRet1int(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *restrict Z,double xdbl,double ydbl,typ_idx avedim){
	int narrs = 3;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

	int ndbls = 2;
	double *dbl_ptr = dbls(ndbls, xdbl, ydbl);

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,
        arrays,dbl_ptr,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}


arr arStatArg4ar2sRet1int(fctArgsRint fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,double xdbl,double ydbl,typ_idx avedim){
	int narrs = 4;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = T;

	int ndbls = 2;
	double *dbl_ptr = dbls(ndbls, xdbl, ydbl);

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,
        arrays,dbl_ptr,NULL,NULL,NULL,NULL,1,&avedim);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}




void arStatArgNarNsBegEndLoop(
    fctArgsRdbl fct,arr *restrict OUT,arr *restrict times,arr *restrict B,arr *restrict E,
    arr **arrays, double *dbl_ptr, int *int_ptr,
    int narrs, int ndbls, int nints,
    typ_idx ndims, typ_idx *map_o2c,typ_idx *map_t2o,typ_idx *map_b2o,typ_idx *map_e2o,typ_idx **map_as2o,
    typ_idx adims_t,typ_idx adims_b,typ_idx adims_e,typ_idx *adims,typ_idx dim,typ_idx *c){
	typ_idx i,j,k,l;

	if (dim == ndims-1){
        int nar1ds,ndbls2,nints2;
        arr *ar1d;
        double *dblp;
        int *intp;
        typ_idx **idxs = malloc(narrs*sizeof(typ_idx *));
        for (i=0;i<narrs;i++){
            idxs[i] = init0(arrays[i]->n,TYPIDX);
            for(j=0;j<arrays[i]->n;j++){
                if (adims[i] == j){
                    idxs[i][j] = 0;
                } else {
                    idxs[i][j] = c[map_o2c[map_as2o[i][j]]];
                }
            }
        }

        typ_idx *idx_t = init0(times->n,TYPIDX);
        for(j=0;j<times->n;j++){
            if (adims_t == j){
                idx_t[j] = 0;
            } else {
                idx_t[j] = c[map_o2c[map_t2o[j]]];
            }
        }

        typ_idx *idx_b = init0(B->n,TYPIDX);
        for(j=0;j<B->n;j++){
            if (adims_b == j){
                idx_b[j] = 0;
            } else {
                idx_b[j] = c[map_o2c[map_b2o[j]]];
            }
        }

        typ_idx *idx_e = init0(E->n,TYPIDX);
        for(j=0;j<E->n;j++){
            if (adims_e == j){
                idx_e[j] = 0;
            } else {
                idx_e[j] = c[map_o2c[map_e2o[j]]];
            }
        }

		j = 0; k = 0; l = 0;
		ar1d = malloc(narrs*sizeof(arr));
		dblp = malloc((narrs+ndbls)*sizeof(double));
		intp = malloc((narrs+nints)*sizeof(int));
		for(i=0;i<narrs;i++){
			if (adims[i] == -1){
                if (arrays[i]->typ == DOUBLE){
                    dblp[k] = cDBL(arrays[i],idxs[i]);
                    k++;
                } else if (arrays[i]->typ == INT){
                    intp[l] = cINTG(arrays[i],idxs[i]);
                    l++;
                } else {
                    fprintf(stderr,"arStatArgNarNsBegEndLoop: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                    exit(0);
                }
			} else {
				ar1d[j] = grab1dAr(arrays[i], adims[i], idxs[i]);
				j++;
			}
		}
		for(i=0;i<ndbls;i++){
			dblp[k] = dbl_ptr[i];
			k++;
		}
		for(i=0;i<nints;i++){
			intp[l] = int_ptr[i];
			l++;
		}
		nar1ds = j;
		ndbls2 = k;
		nints2 = l;

		arr **ar1d_t = malloc((nar1ds+1)*sizeof(arr *));
		for(i=0;i<nar1ds;i++){
			ar1d_t[i] = &ar1d[i];
		}
        if (adims_t == -1){
            fprintf(stderr,"arStatArgNarNsBegEndLoop: The time array must have a dimension matching avedim!\n");
            exit(0);
        } else {
            ar1d_t[nar1ds]  = malloc(sizeof(arr));
            *ar1d_t[nar1ds] = grab1dAr(times, adims_t, idx_t);
            j++;
        }

        double tbeg, tend;
        if (adims_b == -1){
            if (B->typ == DOUBLE){
                tbeg = cDBL(B,idx_b);
            } else if (B->typ == INT){
                tbeg = (double)cINTG(B,idx_b);
            } else {
                fprintf(stderr,"arStatArgNarNsBegEndLoop: Type must be DOUBLE or INT! Type is %d\n",B->typ);
                exit(0);
            }
        } else {
            fprintf(stderr,"arStatArgNarNsBegEndLoop: The B array must not have a dimension matching avedim!\n");
            exit(0);
        }

        if (adims_e == -1){
            if (E->typ == DOUBLE){
                tend = cDBL(E,idx_e);
            } else if (E->typ == INT){
                tend = (double)cINTG(E,idx_e);
            } else {
                fprintf(stderr,"arStatArgNarNsBegEndLoop: Type must be DOUBLE or INT! Type is %d\n",E->typ);
                exit(0);
            }
        } else {
            fprintf(stderr,"arStatArgNarNsBegEndLoop: The B array must not have a dimension matching avedim!\n");
            exit(0);
        }

		arr *ar1d_filt = FilterBetween1dArraysFromDim(ar1d_t, nar1ds+1, tbeg, tend, nar1ds);
		arr **ar1d_f = malloc((nar1ds+1)*sizeof(arr *));
		for(i=0;i<nar1ds;i++){
			ar1d_f[i] = &ar1d_filt[i];
		}

        input_args args=passInputArgs(nar1ds,ndbls2,nints2,0,0,0,0,0
            ,ar1d_f,dblp,intp,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,getMiss(OUT));

        cDBL(OUT,c) = fct(&args);

		for (j=0;j<narrs;j++){
			free(idxs[j]);
		}
		free(idxs);
		free(idx_t);
		free(idx_b);
		free(idx_e);
		for (j=0;j<=nar1ds;j++){
			freeAr(ar1d_t[j]);
		}
		free(ar1d);
		free(ar1d_t);
		for (j=0;j<=nar1ds;j++){
			freeAr(ar1d_f[j]);
		}
		free(ar1d_filt);
        freeInputArgs(&args);
		return;
	} else {
		for(c[dim]=0;c[dim]<OUT->len[dim];c[dim]++){
		/*	Uncomment to print loop counter c
			fputs("arStatArgNarNsBegEndLoop: ",stderr);
			for(j=0;j<=dim;j++){ fprintf(stderr,"c[%lld]=%lld ",j,c[j]); }
			fputs("\n",stderr);
		 */
		/*	if (dim == 0){ fprintf(stderr,"arStatArgNarNsBegEndLoop: c[0]=%lld\n",c[0]);	}   */
			arStatArgNarNsBegEndLoop(fct,OUT,times,B,E,arrays,dbl_ptr,int_ptr,narrs,ndbls,nints,
                ndims,map_o2c,map_t2o,map_b2o,map_e2o,map_as2o,adims_t,adims_b,adims_e,adims,dim+1,c);
		}
	}

	return;
}


arr arStatArgNarNsBegEnd(
    fctArgsRdbl fct,arr *restrict times,arr *restrict B,arr *restrict E,
    int narrs,int ndbls,int nints,
    arr **arrays,double *dbl_ptr,int *int_ptr,
    typ_idx avedim){
	typ_idx i,j;

	typ_idx ndims;
	typ_idx **map_as2o;
	typ_idx *all_len = mapdims_Nar(narrs,arrays,&ndims,&map_as2o);
    /*
	*/
    fputs("arStatArgNarNsBegEnd: all_len\n",stderr);
	for(i=0;i<ndims;i++){
		fprintf(stderr," %lld",all_len[i]);
	}
	fputs("\n",stderr);
	for(j=0;j<narrs;j++){
        fprintf(stderr,"arStatArgNarNsBegEnd: map_as2o[%lld]",j);
		for(i=0;i<arrays[j]->n;i++){
			fprintf(stderr," %lld",map_as2o[j][i]);
		}
        fputs("\n",stderr);
	}

    typ_idx *map_t2o = mapdims_1ar2Nar(times,ndims,all_len);
    typ_idx *map_b2o = mapdims_1ar2Nar(B,ndims,all_len);
    typ_idx *map_e2o = mapdims_1ar2Nar(E,ndims,all_len);

	int maxn  = 0, maxar = -1;
	for(i=0;i<narrs;i++){
    /*  printArrayInfoWHdr(stderr,arrays[i],"arStatArgNarNsBegEnd: arrays[%lld]\n",i);   */
		if (arrays[i]->n > maxn){
			maxn  = arrays[i]->n;
			maxar = i;
		}
	}

	if ((avedim < -1) || (maxn <= avedim)){
		fprintf(stderr,"Error in arStatArgNarNsBegEnd: Invalid dimension for argument 4! maxn=%d, avedim=%lld\n",maxn,avedim);
		exit(0);
	}

    typ_idx adim_all = map_as2o[maxar][avedim];

    typ_idx *adims = malloc(narrs*sizeof *adims);
	for(i=0;i<narrs;i++){
        adims[i] = -1;
        if (i==maxar){
            adims[i] = avedim;
        } else {
            for (j=0;j<arrays[i]->n;j++){
                if (map_as2o[i][j]==adim_all){
                    adims[i] = j;
                    break;
                }
            }
        }
	}

    typ_idx adims_t,adims_b,adims_e;
    adims_t = -1;
    for (j=0;j<times->n;j++){
        if (map_t2o[j]==adim_all){
            adims_t = j;
            break;
        }
    }

    adims_b = -1;
    for (j=0;j<B->n;j++){
        if (map_b2o[j]==adim_all){
            adims_b = j;
            break;
        }
    }

    adims_e = -1;
    for (j=0;j<E->n;j++){
        if (map_e2o[j]==adim_all){
            adims_e = j;
            break;
        }
    }

	typ_idx *c,*clens;
    typ_idx *map_o2c,*map_c2o;
	arr OUT;
	if (ndims == 0){ OUT = NullArray(); } else {
		clens = init0((ndims-1),TYPIDX);
        map_o2c = init0((ndims),TYPIDX);
        map_c2o = init0((ndims-1),TYPIDX);
		for (i=0;i<ndims;i++){
			if (i < adim_all){
				clens[i] = all_len[i];
                map_c2o[i] = i;
                map_o2c[i] = i;
			} else if (i > adim_all) {
				clens[i-1] = all_len[i];
                map_c2o[i-1] = i;
                map_o2c[i] = i-1;
			} else {
                map_o2c[i] = -1;
            }
		}
		c 	= init0(ndims-1,TYPIDX);
		OUT	= ArrayFromList(ndims-1,DOUBLE,clens);
		copyMiss(&OUT,arrays[maxar]);
        arStatArgNarNsBegEndLoop(fct,&OUT,times,B,E,arrays,dbl_ptr,int_ptr,narrs,ndbls,nints,
            ndims,map_o2c,map_t2o,map_b2o,map_e2o,map_as2o,adims_t,adims_b,adims_e,adims,0,c);
		free(c);
		free(clens);
		free(map_o2c);
		free(map_c2o);
	}

    for(i=0;i<narrs;i++){ free(map_as2o[i]); }
	free(map_as2o);
	free(all_len);
    free(adims);
	return OUT;
}


arr arStatArg1arBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,typ_idx avedim){
	int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

	arr OUT = arStatArgNarNsBegEnd(fct,times,B_arr,E_arr,narrs,0,0,arrays,NULL,NULL,avedim);
	free(arrays);
	return OUT;
}


arr arStatArg2arBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,arr *restrict Y,typ_idx avedim){
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	arr OUT = arStatArgNarNsBegEnd(fct,times,B_arr,E_arr,narrs,0,0,arrays,NULL,NULL,avedim);
	free(arrays);
	return OUT;
}


arr arStatArg3arBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,arr *restrict Y,arr *restrict Z,typ_idx avedim){
	int narrs = 3;

	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

	arr OUT = arStatArgNarNsBegEnd(fct,times,B_arr,E_arr,narrs,0,0,arrays,NULL,NULL,avedim);
	free(arrays);
	return OUT;
}


arr arStatArg4arBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,typ_idx avedim){
	int narrs = 4;

	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = T;

	arr OUT = arStatArgNarNsBegEnd(fct,times,B_arr,E_arr,narrs,0,0,arrays,NULL,NULL,avedim);
	free(arrays);
	return OUT;
}


arr arStatArg1ar1sBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,double xdbl,typ_idx avedim){
	int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

	int ndbls = 1;
	double *dbl_ptr = dbls(ndbls, xdbl);

	arr OUT = arStatArgNarNsBegEnd(fct,times,B_arr,E_arr,narrs,ndbls,0,arrays,dbl_ptr,NULL,avedim);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}


arr arStatArg2ar1sBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,arr *restrict Y,double xdbl,typ_idx avedim){
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	int ndbls = 1;
	double *dbl_ptr = dbls(ndbls, xdbl);

	arr OUT = arStatArgNarNsBegEnd(fct,times,B_arr,E_arr,narrs,ndbls,0,arrays,dbl_ptr,NULL,avedim);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}


arr arStatArg2ar2sBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,arr *restrict Y,double xdbl,double ydbl,typ_idx avedim){
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	int ndbls = 2;
	double *dbl_ptr = dbls(ndbls, xdbl, ydbl);

	arr OUT = arStatArgNarNsBegEnd(fct,times,B_arr,E_arr,narrs,ndbls,0,arrays,dbl_ptr,NULL,avedim);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}


arr arStatArg3ar2sBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,arr *restrict Y,arr *restrict Z,double xdbl,double ydbl,typ_idx avedim){
	int narrs = 3;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

	int ndbls = 2;
	double *dbl_ptr = dbls(ndbls, xdbl, ydbl);

	arr OUT = arStatArgNarNsBegEnd(fct,times,B_arr,E_arr,narrs,ndbls,0,arrays,dbl_ptr,NULL,avedim);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}


arr arStatArg4ar2sBegEnd(fctArgsRdbl fct,arr *restrict times,arr *restrict B_arr,arr *restrict E_arr,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict T,double xdbl,double ydbl,typ_idx avedim){
	int narrs = 4;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = T;

	int ndbls = 2;
	double *dbl_ptr = dbls(ndbls, xdbl, ydbl);

	arr OUT = arStatArgNarNsBegEnd(fct,times,B_arr,E_arr,narrs,ndbls,0,arrays,dbl_ptr,NULL,avedim);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}

#endif
