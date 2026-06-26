/* Created by Bill Scheftic */
/*-------------------------------------------*/
/* Header for Element-by-Element Processing  */
/*-------------------------------------------*/
/*
 *  Things to add:
 *  --------------
 *  + change all functions to be like fct2ar that can deal with variably dimensioned input
 */
#ifndef  _MATH2_E_
#define  _MATH2_E_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <math_supp.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <arraynd.h>
#include <arrayftypes.h>

/*------------------------*/
/* Function Declarations  */
/*------------------------*/
void isetToMissIF(arr *restrict m,fctRint fct,int condval);
void setToMissIF(arr *restrict m,fctRint fct,double condval);
typ_idx countIF(arr *restrict X,fctRint fct,double y);
arr fct1ar(fctArgsRdbl fct,arr *restrict X);
arr fct1ar_free(fctArgsRdbl fct,arr *restrict X,int fr0);
arr fct2ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y);
arr fct3ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z);
arr fct4ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict A);
arr fct5ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict A,arr *restrict B);
arr fct6ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict A,arr *restrict B,arr *restrict C);
arr fct7ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict A,arr *restrict B,arr *restrict C,arr *restrict D);
arr fct8ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict A,arr *restrict B,arr *restrict C,arr *restrict D,arr *restrict E);
arr fct9ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict A,arr *restrict B,arr *restrict C,arr *restrict D,arr *restrict E,arr *restrict F);
int OrListVar(int(*fct)(int, int), int n, int x, ...);
arr fct1ar1s(fctArgsRdbl fct,arr *restrict X,double y);
arr fctdi1ar1s(fctArgsRdbl fct,arr *restrict X,int y);
arr fct2ar1s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,double b);
arr fct1ar2s(fctArgsRdbl fct,arr *restrict X,double b,double c);
arr fct1ar3s(fctArgsRdbl fct,arr *restrict X,double b,double c,double d);
arr fct1ar4s(fctArgsRdbl fct,arr *restrict X,double b,double c,double d,double e);
arr fct2ar2s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,double b,double c);
arr fct2ar3s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,double b,double c,double d);
arr fct3ar1s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,double b);
arr fct3ar2s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,double b,double c);
arr fct3ar3s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,double a,double b,double c);
arr fct4ar1s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict A,double b);
arr fct4ar2s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict A,double b,double c);
arr ifct1ar(fctArgsRint fct,arr *restrict X);
arr ifct1ar1s(fctArgsRint fct,arr *restrict X,double y);
arr ifct2ar(fctArgsRint fct,arr *restrict X,arr *restrict Y);
arr fctid2ar(fctRdbl fct,arr *restrict X,arr *restrict Y);
arr fct1s1ar(fctRdbl fct,double x,arr *restrict Y);
arr ifct1s1ar(fctRint fct,double x,arr *restrict Y);
void fct1arRef(fctRdbl fct,arr *restrict m,arr *restrict X);
void fct2arRef(fctRdbl fct,arr *restrict m,arr *restrict X,arr *restrict Y);
void fct1ar1sRef(fctRdbl fct,arr *restrict m,arr *restrict X,double y);
arr fx1d(fctRdbl fct,typ_idx ndims,typ_idx *len,typ_idx xdim,double xbeg,double xend);
	void fx1dLoop(fctRdbl fct,arr *restrict X,double xbeg,double dx,typ_idx xdim, typ_idx dim, typ_idx *c);
arr getCoordArray(double xbeg, double xend, typ_idx nx);
arr wrap_getCoordArray(input_args *args);

/* Unfortunately, I would need to create wrapper functions */
/*
arr fctNArLst(fctRdbl,int,arr **);
 */

/*-----------------------------*/
/* General Operation Functions */
/*-----------------------------*/
void isetToMissIF(arr *restrict m,fctRint fct,int condval){
	typ_idx i;

	switch (m->typ) {
	#define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)	\
    { \
        swcast miss = *(swcast *)getMiss(m); \
        swcast *p   = pntr_of(m); \
		for(i=0;i<m->tlen;i++,p++){								\
			if((*fct)((int)*p,condval)){ *p = miss; }		\
		} \
    }
		ALLTYPECASES
		default:
			fprintf(stderr,"Error in isetToMissIF: undefined type %d!\n",m->typ);
			exit(0);
			break;
	}
	#undef SWITCHCAST
	return;
}

void setToMissIF(arr *restrict m,fctRint fct,double condval){
	typ_idx i;

	switch (m->typ) {
	#define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)	\
    { \
        swcast miss = *(swcast *)getMiss(m); \
        swcast *p   = pntr_of(m); \
		for(i=0;i<m->tlen;i++){								\
			if((*fct)((double)*p,condval)){ *p = miss; }		\
		} \
    }
		ALLTYPECASES
		default:
			fprintf(stderr,"Error in setToMissIF: undefined type %d!\n",m->typ);
			exit(0);
			break;
	}
	#undef SWITCHCAST
	return;
}

typ_idx countIF(arr *restrict X,fctRint fct,double y){
	typ_idx i,count = 0;
	arr Xi = castAr(X,DOUBLE,0);

	for(i=0;i<X->tlen;++i){
		if(!isMiss(&Xi,i)){
			if ((*fct)(iDBL(&Xi,i),y)) { count++; }
		}
	}

	freeAr(&Xi);
	return count;
}


/* 
 *  These functions should be cast back to original type.
 */
arr fct1ar(fctArgsRdbl fct,arr *restrict X){
	int narrs = 1;
    
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,0,0,0,0,arrays,NULL,NULL,NULL,NULL);

	free(arrays);
	return OUT;
}

/* 
 *  Testing function that can free input on passed int
 *  - used for cases where an array is passed to this function from another function
 */
arr fct1ar_free(fctArgsRdbl fct,arr *restrict X,int fr0){
	int narrs = 1;
    
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,0,0,0,0,arrays,NULL,NULL,NULL,NULL);

	free(arrays);
	if (fr0){
		freeAr(X);
	}
	return castAr(&OUT,X->typ,1);
}


/* fctdi2ar will use this now, but Y must be int type */
arr fct2ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y){
	int narrs = 2;
    
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,0,0,0,0,arrays,NULL,NULL,NULL,NULL);

	free(arrays);
	return OUT;
}

arr fct3ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z){
	int narrs = 3;

	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,0,0,0,0,arrays,NULL,NULL,NULL,NULL);

	free(arrays);
	return OUT;
}

arr fct4ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict A){
	int narrs = 4;

	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = A;

	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,0,0,0,0,arrays,NULL,NULL,NULL,NULL);

	free(arrays);
	return OUT;
}

arr fct5ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict A,arr *restrict B){
	int narrs = 5;

	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = A;
	arrays[4] = B;

	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,0,0,0,0,arrays,NULL,NULL,NULL,NULL);

	free(arrays);
	return OUT;
}

arr fct6ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict A,arr *restrict B,arr *restrict C){
	int narrs = 6;

	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = A;
	arrays[4] = B;
	arrays[5] = C;

	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,0,0,0,0,arrays,NULL,NULL,NULL,NULL);

	free(arrays);
	return OUT;
}

arr fct7ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict A,arr *restrict B,arr *restrict C,arr *restrict D){
	int narrs = 7;

	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = A;
	arrays[4] = B;
	arrays[5] = C;
	arrays[6] = D;

	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,0,0,0,0,arrays,NULL,NULL,NULL,NULL);

	free(arrays);
	return OUT;
}

arr fct8ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict A,arr *restrict B,arr *restrict C,arr *restrict D,arr *restrict E){
	int narrs = 8;

	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = A;
	arrays[4] = B;
	arrays[5] = C;
	arrays[6] = D;
	arrays[7] = E;

	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,0,0,0,0,arrays,NULL,NULL,NULL,NULL);

	free(arrays);
	return OUT;
}

arr fct9ar(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict A,arr *restrict B,arr *restrict C,arr *restrict D,arr *restrict E,arr *restrict F){
	int narrs = 9;

	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = A;
	arrays[4] = B;
	arrays[5] = C;
	arrays[6] = D;
	arrays[7] = E;
	arrays[8] = F;

	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,0,0,0,0,arrays,NULL,NULL,NULL,NULL);

	free(arrays);
	return OUT;
}


int OrListVar(int(*fct)(int, int), int n, int x, ...) {
	int i, y;
	va_list arg_list;
	va_start(arg_list, x);
	for (i=0; i<n; i++) {
		y = va_arg(arg_list, int);
		if (fct(x, y)) {
			va_end(arg_list);
			return 1;
		}
	}
	va_end(arg_list);
	return 0;
}



arr fct1ar1s(fctArgsRdbl fct,arr *restrict X,double y){
    int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

    int ndbls = 1;
	double *dbl_ptr = dbls(ndbls, y);
/*  printArrayAllWHdr(stderr,X,"fct1ar1s: dbl_ptr[0]=%g, X - ",dbl_ptr[0]); */
    
	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,ndbls,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL);
/*  printArrayAllWHdr(stderr,OUT,"fct1ar1s: OUT - ");   */

	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr fctdi1ar1s(fctArgsRdbl fct,arr *restrict X,int y){
    int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

    int nints = 1;
	int *int_ptr = ints(nints, y);
    
	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,0,nints,0,0,arrays,NULL,int_ptr,NULL,NULL);

	free(arrays);
	free(int_ptr);
	return OUT;
}

arr fct2ar1s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,double b){
    int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

    int ndbls = 1;
	double *dbl_ptr = dbls(ndbls, b);
    
	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,ndbls,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL);

	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr fct1ar2s(fctArgsRdbl fct,arr *restrict X,double b,double c){
    int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

    int ndbls = 2;
	double *dbl_ptr = dbls(ndbls, b, c);
    
	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,ndbls,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL);

	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr fct1ar3s(fctArgsRdbl fct,arr *restrict X,double b,double c,double d){
    int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

    int ndbls = 3;
	double *dbl_ptr = dbls(ndbls, b, c, d);
    
	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,ndbls,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL);

	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr fct1ar4s(fctArgsRdbl fct,arr *restrict X,double b,double c,double d,double e){
    int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

    int ndbls = 4;
	double *dbl_ptr = dbls(ndbls, b, c, d, e);
    
	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,ndbls,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL);

	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr fct2ar2s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,double b,double c){
    int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

    int ndbls = 2;
	double *dbl_ptr = dbls(ndbls, b, c);
    
	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,ndbls,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL);

	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr fct2ar3s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,double b,double c,double d){
    int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

    int ndbls = 3;
	double *dbl_ptr = dbls(ndbls, b, c, d);
    
	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,ndbls,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL);

	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr fct3ar1s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,double b){
    int narrs = 3;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

    int ndbls = 1;
	double *dbl_ptr = dbls(ndbls, b);
    
	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,ndbls,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL);

	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr fct3ar2s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,double b,double c){
    int narrs = 3;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

    int ndbls = 2;
	double *dbl_ptr = dbls(ndbls, b, c);
    
	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,ndbls,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL);

	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr fct3ar3s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,double a,double b,double c){
    int narrs = 3;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

    int ndbls = 3;
	double *dbl_ptr = dbls(ndbls, a, b, c);
    
	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,ndbls,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL);

	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr fct4ar1s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict A,double b){
    int narrs = 4;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = A;

    int ndbls = 1;
	double *dbl_ptr = dbls(ndbls, b);
    
	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,ndbls,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL);

	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr fct4ar2s(fctArgsRdbl fct,arr *restrict X,arr *restrict Y,arr *restrict Z,arr *restrict A,double b,double c){
    int narrs = 4;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = A;

    int ndbls = 2;
	double *dbl_ptr = dbls(ndbls, b, c);
    
	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,ndbls,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL);

	free(arrays);
	free(dbl_ptr);
	return OUT;
}



/* use this in place of ifcti1ar */
arr ifct1ar(fctArgsRint fct,arr *restrict X){
	int narrs = 1;
    
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

	arr OUT = ndmath_int_NarNsNint_RNDblNInt(fct,narrs,0,0,0,0,arrays,NULL,NULL,NULL,NULL);

	free(arrays);
	return OUT;
}

arr ifct1ar1s(fctArgsRint fct,arr *restrict X,double y){
    int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

    int ndbls = 1;
	double *dbl_ptr = dbls(ndbls, y);
    
	arr OUT = ndmath_int_NarNsNint_RNDblNInt(fct,narrs,ndbls,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL);

	free(arrays);
	free(dbl_ptr);
	return OUT;
}

/* ifctii2ar will use this now, but X & Y must be int type
   also compAr just uses this function as well. */
arr ifct2ar(fctArgsRint fct,arr *restrict X,arr *restrict Y){
	int narrs = 2;
    
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	arr OUT = ndmath_int_NarNsNint_RNDblNInt(fct,narrs,0,0,0,0,arrays,NULL,NULL,NULL,NULL);

	free(arrays);
	return OUT;
}



arr fctid2ar(fctRdbl fct,arr *restrict X,arr *restrict Y){
	if (X->tlen != Y->tlen){
		fprintf(stderr,"Error in fctid2ar: X and Y must have same total number of elements!\n"
			         "\tX->tlen=%lld, Y->tlen=%lld\n",X->tlen,Y->tlen);
		exit(0);
	}
	typ_idx i;
	arr m = ArrayFromList(X->n,DOUBLE,X->len);
	arr Xi = castAr(X,INT,0);
	arr Yi = castAr(Y,DOUBLE,0);
    double miss = *(double *)getMiss(&Yi);
	*(double *)getMiss(&m) = miss;

	for(i=0;i<m.tlen;i++){
		if(isMiss(&Xi,i) || isMiss(&Yi,i)){
			iDBL(&m,i) = miss;
		} else {
			iDBL(&m,i) = (*fct)(iINTG(&Xi,i),iDBL(&Yi,i));
		}
	}

	freeAr(&Xi);
	freeAr(&Yi);
	return castAr(&m,Y->typ,1);
}

arr fct1s1ar(fctArgsRdbl fct,double x,arr *restrict Y){
    int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
    arr X = Scalar2Array(DOUBLE,&x);
    arrays[0] = &X;
	arrays[1] = Y;
    
	arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,0,0,0,0,arrays,NULL,NULL,NULL,NULL);

	freeAr(&X);
	free(arrays);
	return OUT;

/*
	typ_idx i;
	arr m = ArrayFromList(Y->n,DOUBLE,Y->len);
	arr Yi = castAr(Y,DOUBLE,0);
	*(double *)getMiss(m) = *(double *)getMiss(Yi);

	if(isVal(x,*(double *)getMiss(Yi))){
		for(i=0;i<m.tlen;i++){ iDBL(&m,i) = *(double *)getMiss(m); }
	} else {
		for(i=0;i<m.tlen;i++){
			if(isMiss(&Yi,i)){
				iDBL(&m,i) = *(double *)getMiss(m);
			} else {
				iDBL(&m,i) = (*fct)(x,iDBL(&Yi,i));
			}
		}
	}

	freeAr(&Yi);
	return m;
*/ /*	return castAr(&m, Y->typ, 1);	*/
}

arr ifct1s1ar(fctRint fct,double x,arr *restrict Y){
	typ_idx i;
	arr m = ArrayFromList(Y->n,INT,Y->len);
	arr Yi = castAr(Y,DOUBLE,0);
	*(int *)getMiss(&m) = -999;

	if(isVal(x,*(double *)getMiss(&Yi))){
		for(i=0;i<m.tlen;i++){ iINTG(&m,i) = *(int *)getMiss(&m); }
	} else {
		for(i=0;i<m.tlen;i++){
			if(isMiss(&Yi,i)){
				iINTG(&m,i) = *(int *)getMiss(&m);
			} else {
				iINTG(&m,i) = (*fct)(x,iDBL(&Yi,i));
			}
		}
	}

	freeAr(&Yi);
	return m;
}

void fct1arRef(fctRdbl fct,arr *restrict m,arr *restrict X){
	if (X->tlen != m->tlen){
		fprintf(stderr,"Error in fct1arRef: X and m must have same total number of elements!\n"
			         "\tX->tlen=%lld, m->tlen=%lld\n",X->tlen,m->tlen);
		exit(0);
	}
	typ_idx i;

	switch (m->typ) {
	#define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)	\
    { \
        swcast *p  = pntr_of(m); \
        swcast *pX = pntr_of(X); \
		for(i=0;i<m->tlen;i++){ *p++ = (swcast)(*fct)((double)*pX++); } \
    }
		ALLTYPECASES
		default:
			fprintf(stderr,"undefined type %d!\n",m->typ);
			exit(0);
			break;
	}
	#undef SWITCHCAST

	return;
}

void fct2arRef(fctRdbl fct,arr *restrict m,arr *restrict X,arr *restrict Y){
	if ((X->tlen != Y->tlen) || (Y->tlen != m->tlen)){
		fprintf(stderr,"Error in fct2arRef: X, Y and m must have same total number of elements!\n"
			         "\tX->tlen=%lld, Y->tlen=%lld, m->tlen=%lld\n",X->tlen,Y->tlen,m->tlen);
		exit(0);
	}
	typ_idx i;

	switch (m->typ) {
	#define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)	\
    { \
        swcast *p  = pntr_of(m); \
        swcast *pX = pntr_of(X); \
        swcast *pY = pntr_of(Y); \
		for(i=0;i<m->tlen;i++){ *p++ = (swcast)(*fct)((double)*pX++,(double)*pY++); } \
    }
		ALLTYPECASES
		default:
			fprintf(stderr,"undefined type %d!\n",m->typ);
			exit(0);
			break;
	}
	#undef SWITCHCAST

	return;
}

void fct1ar1sRef(fctRdbl fct,arr *restrict m,arr *restrict X,double y){
	if (X->tlen != m->tlen){
		fprintf(stderr,"Error in fct1ar1sRef: X and m must have same total number of elements!\n"
			         "\tX->tlen=%lld, m->tlen=%lld\n",X->tlen,m->tlen);
		exit(0);
	}
	typ_idx i;

	switch (m->typ) {
	#define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)	\
    { \
        swcast *p  = pntr_of(m); \
        swcast *pX = pntr_of(X); \
		for(i=0;i<m->tlen;i++){ *p++ = (swcast)(*fct)((double)*pX++,y); } \
    }
		ALLTYPECASES
		default:
			fprintf(stderr,"undefined type %d!\n",m->typ);
			exit(0);
			break;
	}
	#undef SWITCHCAST

	return;
}



arr fx1d(fctRdbl fct,typ_idx ndims,typ_idx *len,typ_idx xdim,double xbeg,double xend){
	if ((xdim < 0) || (ndims <= xdim)){
		fprintf(stderr,"Error in fx1d: Invalid dimension as 4th argument! ndims=%lld, xdim=%lld\n",ndims,xdim);
		exit(0);
	}

	arr X = ArrayFromList(ndims,DOUBLE,len);

	double dx = (xend - xbeg)/(len[xdim] - 1);
	typ_idx *c = init0(ndims,TYPIDX);
	fx1dLoop(fct,&X,xbeg,dx,xdim,0,c);

	free(c);

	return X;
}

	/*	Used only in fx1d	*/
	void fx1dLoop(fctRdbl fct,arr *restrict X,double xbeg,double dx,typ_idx xdim, typ_idx dim, typ_idx *c){
		if (dim == X->n){
			cDBL(X,c) = fct(xbeg + c[xdim]*dx);
			return;
		} else {
			for(c[dim]=0;c[dim]<X->len[dim];c[dim]++){
				fx1dLoop(fct,X,xbeg,dx,xdim,dim+1,c);
			}
		}

		return;
	}

arr getCoordArrayInt(int xbeg, int xend, int dx){
    typ_idx nx = (xend - xbeg)/dx + 1;
	arr m = Array(1,INT,nx);
    int *pm = pntr_of(&m);
	for(typ_idx i=0;i<nx;i++){ *pm++ = xbeg + i*dx; }

	return m;
}

arr getCoordArray(double xbeg, double xend, typ_idx nx){
	double dx = (xend - xbeg)/(double)(nx - 1);
	arr m = Array(1,DOUBLE,nx);
    double *pm = pntr_of(&m);
	for(typ_idx i=0;i<nx;i++){ *pm++ = xbeg + i*dx; }

	return m;
}

arr wrap_getCoordArray(input_args *args){
    typ_idx i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }
    if (args->idxp_miss){
        for(i=0;i<args->nidxs;i++){
            if (args->idxp[i] == args->idxp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }
    double  dbl0 = args->dblp[0];
    double  dbl1 = args->dblp[1];
    typ_idx idx0 = args->idxp[0];
    arr rv = getCoordArray(dbl0,dbl1,idx0);
    return rv;
}

#endif
