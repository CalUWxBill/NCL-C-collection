/* Created by Bill Scheftic */
#ifndef  _GRID_H_
#define  _GRID_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <math_supp.h>
#include <arrayinit2.h>
#include <print_arrays2.h>

typedef struct {            double lt, ln, dy, dx; typ_idx y, x; } grid;
typedef struct { typ_idx n; double  *bcrd,  *dcrd; typ_idx *len; } gridnd;

/*
 *  Nd grid functions
 */
gridnd NullGridNd(){
    gridnd grd;
    grd.n    = 0;
    grd.bcrd = NULL;
    grd.dcrd = NULL;
    grd.len  = NULL;
    return grd;
}

void printGridNd(FILE *fout,gridnd *restrict grd){
	typ_idx j;
    fprintf(fout,"Grid has %lld dims\n", grd->n);
	for (j=0;j<grd->n;++j){
        fprintf(fout,"%lld: %lld %g %g\n", j,grd->len[j],grd->bcrd[j],grd->dcrd[j]);
	}
	return;
}

void freeGridNd(gridnd *m){
	if(m->bcrd){ free(m->bcrd); m->bcrd = NULL; }
	if(m->dcrd){ free(m->dcrd); m->dcrd = NULL; }
	if(m->len ){ free(m->len);  m->len  = NULL; }
    m->n = 0;
	return;
}

void setGridNdFromList(typ_idx ndims,gridnd *grd,double *bcrd,double *dcrd,typ_idx *len){
	typ_idx j;
	grd->n    = ndims;
	grd->bcrd = malloc(ndims*sizeof(double));
	grd->dcrd = malloc(ndims*sizeof(double));
	grd->len  = malloc(ndims*sizeof(typ_idx));

	for (j=0;j<ndims;++j){
		grd->bcrd[j] = bcrd[j];
		grd->dcrd[j] = dcrd[j];
		grd->len[j]  = len[j];
	}

	return;
}

void setGridNd(typ_idx ndims,gridnd *grd,...){
	typ_idx j;
	grd->n    = ndims;
	grd->bcrd = malloc(ndims*sizeof(double));
	grd->dcrd = malloc(ndims*sizeof(double));
	grd->len  = malloc(ndims*sizeof(typ_idx));

	va_list arg_list;
	va_start(arg_list, grd);

	for (j=0;j<ndims;++j){
		grd->bcrd[j] = va_arg(arg_list, double);
	}
	for (j=0;j<ndims;++j){
		grd->dcrd[j] = va_arg(arg_list, double);
	}
	for (j=0;j<ndims;++j){
		grd->len[j]  = va_arg(arg_list, typ_idx);
	}

	va_end(arg_list);

	return;
}

void subGridNd(gridnd *grd,gridnd *restrict m,typ_idx ndims,typ_idx *dims){
	typ_idx j;
    grd->n    = ndims;
	grd->bcrd = malloc(ndims*sizeof(double));
	grd->dcrd = malloc(ndims*sizeof(double));
	grd->len  = malloc(ndims*sizeof(typ_idx));

	for (j=0;j<ndims;++j){
		grd->bcrd[j] = m->bcrd[dims[j]];
		grd->dcrd[j] = m->dcrd[dims[j]];
		grd->len[j]  = m->len[dims[j]];
	}

	return;
}

void calcGridFromCornersNdFromList(typ_idx ndims,gridnd *grd,double *crd1,double *crd2,double *dcrd){
	typ_idx j;
	grd->n    = ndims;
	grd->bcrd = malloc(ndims*sizeof(double));
	grd->dcrd = malloc(ndims*sizeof(double));
	grd->len  = malloc(ndims*sizeof(typ_idx));

	for (j=0;j<ndims;++j){
		grd->dcrd[j] = dcrd[j];
		grd->bcrd[j] = crd1[j] + 0.5*grd->dcrd[j];
		grd->len[j]  = myRound2((crd2[j]-crd1[j])/grd->dcrd[j]);
	}

	return;
}

void calcGridFromCornersNd(typ_idx ndims,gridnd *grd,...){
	typ_idx j;
	grd->n    = ndims;
	grd->bcrd = malloc(ndims*sizeof(double));
	grd->dcrd = malloc(ndims*sizeof(double));
	grd->len  = malloc(ndims*sizeof(typ_idx));

	double *crd1 =malloc(ndims*sizeof(double));
	double *crd2 =malloc(ndims*sizeof(double));

	va_list arg_list;
	va_start(arg_list, grd);

	for (j=0;j<ndims;++j){
		crd1[j] = va_arg(arg_list, double);
	}
	for (j=0;j<ndims;++j){
		crd2[j] = va_arg(arg_list, double);
	}
	for (j=0;j<ndims;++j){
		grd->dcrd[j]  = va_arg(arg_list, double);
	}

	va_end(arg_list);

	for (j=0;j<ndims;++j){
		grd->bcrd[j] = crd1[j] + 0.5*grd->dcrd[j];
		grd->len[j]  = myRound2((crd2[j]-crd1[j])/grd->dcrd[j]);
	}

	free(crd1);
	free(crd2);
	return;
}

void calcGridFromCornersCntNdFromList(typ_idx ndims,gridnd *grd,double *crd1,double *crd2,typ_idx *len){
	typ_idx j;
	grd->n    = ndims;
	grd->bcrd = malloc(ndims*sizeof(double));
	grd->dcrd = malloc(ndims*sizeof(double));
	grd->len  = malloc(ndims*sizeof(typ_idx));

	for (j=0;j<ndims;++j){
		grd->len[j]  = len[j];
		grd->dcrd[j] = (crd2[j]-crd1[j])/grd->len[j];
		grd->bcrd[j] = crd1[j] + 0.5*grd->dcrd[j];
	}

	return;
}

void calcGridFromCornersCntNd(typ_idx ndims,gridnd *grd,...){
	typ_idx j;
	grd->n    = ndims;
	grd->bcrd = malloc(ndims*sizeof(double));
	grd->dcrd = malloc(ndims*sizeof(double));
	grd->len  = malloc(ndims*sizeof(typ_idx));

	double *crd1 =malloc(ndims*sizeof(double));
	double *crd2 =malloc(ndims*sizeof(double));

	va_list arg_list;
	va_start(arg_list, grd);

	for (j=0;j<ndims;++j){
		crd1[j] = va_arg(arg_list, double);
	}
	for (j=0;j<ndims;++j){
		crd2[j] = va_arg(arg_list, double);
	}
	for (j=0;j<ndims;++j){
		grd->len[j]  = va_arg(arg_list, typ_idx);
	}

	va_end(arg_list);

	for (j=0;j<ndims;++j){
		grd->dcrd[j] = (crd2[j]-crd1[j])/grd->len[j];
		grd->bcrd[j] = crd1[j] + 0.5*grd->dcrd[j];
	}

	free(crd1);
	free(crd2);
	return;
}

typ_idx calcGridIdxNd(double val,gridnd *restrict grd,typ_idx x){
    /*
    fprintf(stderr,"calcGridIdxNd: val=%g, x=%lld\n",val,x);
    printGridNd(stderr,grd);
    fprintf(stderr,"calcGridIdxNd: (val - grd->bcrd[x])=%g\n",(val - grd->bcrd[x]));
    fprintf(stderr,"calcGridIdxNd: (val - grd->bcrd[x])/grd->dcrd[x]=%g\n",(val - grd->bcrd[x])/grd->dcrd[x]);
    fprintf(stderr,"calcGridIdxNd: myRound((val - grd->bcrd[x])/grd->dcrd[x])=%d\n",(int)rint((val - grd->bcrd[x])/grd->dcrd[x]));
     */
	return (typ_idx)myRound2((val - grd->bcrd[x])/grd->dcrd[x]);
}

typ_idx *calcGridIdxNd_c(gridnd *restrict grd,double *vals){
	typ_idx *ridxs = malloc(grd->n*sizeof(typ_idx));
	typ_idx i;
	for(i=0;i<grd->n;++i){
		ridxs[i] = calcGridIdxNd(vals[i],grd,i);
	}
	return ridxs;
}

double calcGridIdxNd_Dbl(double val,gridnd *restrict grd,typ_idx x){
	return (val - grd->bcrd[x])/grd->dcrd[x];
}

double *calcGridIdxNd_Dbl_c(gridnd *restrict grd,double *vals){
	double *ridxs = malloc(grd->n*sizeof(double));
	typ_idx i;
	for(i=0;i<grd->n;++i){
		ridxs[i] = calcGridIdxNd_Dbl(vals[i],grd,i);
	}
	return ridxs;
}

double calcGridValNd(gridnd *restrict grd,typ_idx idx,typ_idx x){
	return grd->bcrd[x] + idx*grd->dcrd[x];
}

double *calcGridValNd_c(gridnd *restrict grd,typ_idx *c){
	double *rvals = malloc(grd->n*sizeof(double));
	typ_idx i;
	for(i=0;i<grd->n;++i){
		rvals[i] = calcGridValNd(grd,c[i],i);
	}
	return rvals;
}

double calcGridValNd_Dbl(gridnd *restrict grd,double idx_dbl,typ_idx x){
	return grd->bcrd[x] + idx_dbl*grd->dcrd[x];
}

double *calcGridValNd_Dbl_c(gridnd *restrict grd,double *c_dbl){
	double *rvals = malloc(grd->n*sizeof(double));
	typ_idx i;
	for(i=0;i<grd->n;++i){
		rvals[i] = calcGridValNd_Dbl(grd,c_dbl[i],i);
	}
	return rvals;
}

arr calcGridArrayNd(gridnd *restrict grd,typ_idx x){	/* Probably, should allow for an Nd grid, not just 1d */
	arr m;
	typ_idx i;
	m = Array(1,DOUBLE,grd->len[x]);
	for(i=0;i<m.tlen;++i){ iDBL(&m,i) = grd->bcrd[x] + i*grd->dcrd[x]; }

	return m;
}

int isInGrid(double *a,gridnd *restrict grd){
	typ_idx i;
	for(i=0;i<grd->n;++i){
		if( (a[i] < grd->bcrd[i]) || (a[i] > calcGridValNd(grd,grd->len[i]-1,i)) ){ return 0; }
	}
	return 1;
}

arr findSliceOnGrid(arr *restrict A,gridnd *restrict grd,double *vals,typ_idx subdim){
    typ_idx *xidx = calcGridIdxNd_c(grd,vals);
    typ_idx *idx  = initNdIdx(xidx,grd->n,1,&subdim);
    arr slice = grab1dAr(A, subdim, idx);
    free(xidx);
    free(idx);
	return slice;
}




/*
 *  Old 2-d only grid functions
 */
void setGrid(grid *grd,double lt,double ln,double dy, double dx,typ_idx y,typ_idx x){
	grd->lt = lt;
	grd->ln = ln;
	grd->dy = dy;
	grd->dx = dx;
	grd->y  = y;
	grd->x  = x;
	return;
}

void calcGridFromCorners(grid *grd,double lt1,double ln1,double lt2,double ln2,double dy,double dx){
	grd->lt = lt1 + 0.5*dy;
	grd->ln = ln1 + 0.5*dx;
	grd->dy = dy;
	grd->dx = dx;
	grd->y = myRound2((lt2-lt1)/dy);
	grd->x = myRound2((ln2-ln1)/dx);
	return;
}

void calcGridFromCornersCnt(grid *grd,double lt1,double ln1,double lt2,double ln2,typ_idx y,typ_idx x){
	grd->y = y;
	grd->x = x;
	grd->dy = (lt2-lt1)/y;
	grd->dx = (ln2-ln1)/x;
	grd->lt = lt1 + 0.5*grd->dy;
	grd->ln = ln1 + 0.5*grd->dx;
	return;
}

typ_idx calcGridIdx(double val, grid *restrict grd,typ_idx x){
	if (x == 1){
		return myRound2((val - grd->ln)/grd->dx);
	} else if (x == 0) {
		return myRound2((val - grd->lt)/grd->dy);
	}

	return 0;
}

arr calcGridArray(grid *restrict grd,typ_idx x){
	arr m;
	typ_idx i;
	if (x == 1){
		m = Array(1,DOUBLE,grd->x);
		for(i=0;i<m.tlen;++i){ iDBL(&m,i) = grd->ln + i*grd->dx; }
	} else if (x == 0) {
		m = Array(1,DOUBLE,grd->y);
		for(i=0;i<m.tlen;++i){ iDBL(&m,i) = grd->lt + i*grd->dy; }
	}

	return m;
}

double earthArea(double lt1, double ln1, double lt2, double ln2) {
	double R = 6378.1;
	double pi = 3.14159265358979323846;
	double rlt1 = (lt1/180)*pi;
	double rlt2 = (lt2/180)*pi;
	return (pi/180)*(R*R)*fabs(sin(rlt1)-sin(rlt2))*fabs(ln1-ln2);
}

arr upScale(arr *restrict inp, grid *restrict in, grid *restrict out) {
	arr m = Array(2,DOUBLE,out->y,out->x);  

	typ_idx i,j,k,l;
	typ_idx linit, kinit, lend, kend;

	double bot, top, left, right;
	double lt1, ln1, lt2, ln2;
	double area, areasum, wgtsum;
	
	for (j=0;j<out->y;++j) {
		bot = out->lt + ((double)j-0.5)*out->dy;
		top = out->lt + ((double)j+0.5)*out->dy;
		linit = myRound2((bot-in->lt)/in->dy);
		lend  = myRound2((top-in->lt)/in->dy);
		for (i=0;i<out->x;++i) {
			areasum = 0.0;
			wgtsum  = 0.0;
			left  = out->ln + ((double)i-0.5)*out->dx;
			right = out->ln + ((double)i+0.5)*out->dx;
			kinit = myRound2((left-in->ln)/in->dx);
			kend  = myRound2((right-in->ln)/in->dx);
			if (linit == -1) { linit = 0; }
			if (kinit == -1) { kinit = 0; }
			if (lend  == in->y) { lend = in->y-1; }
			if (kend  == in->x) { kend = in->x-1; }
			for (l=linit;l<=lend;++l) {
				lt1 = in->lt + ((double)l-0.5)*in->dy;
				lt2 = in->lt + ((double)l+0.5)*in->dy;
				if (bot > lt1) { lt1 = bot; }
				if (top < lt2) { lt2 = top; }
				for (k=kinit;k<kend;++k) {
					ln1 = in->ln + ((double)k-0.5)*in->dx;
					ln2 = in->ln + ((double)k+0.5)*in->dx;
					if (left > ln1) { ln1 = left; }
					if (right < ln2) { ln2 = right; }
					area = earthArea(lt1,ln1,lt2,ln2);
					areasum += area;
					wgtsum += area*DBL(inp,l,k);
				}
			}
			DBL(&m,j,i) = wgtsum/areasum;
		}
	}

	return m;
}


arr upScale1d(arr *restrict A_in, gridnd * grd_in, gridnd * grd_out) {
/*  Need to process missing values in A_in */
/*  printArrayFmtAllWHdr(stderr,A_in,"%g","upScale1d: A_in"); */
    fputs("upScale1d: ",stderr); printGridNd(stderr,grd_in);
    fputs("upScale1d: ",stderr); printGridNd(stderr,grd_out);
	typ_idx i,k;
	typ_idx kbeg, kend;

	double left, right;
	double x1,  x2;
	double width, widthsum, wgtsum;
    typ_idx nx_o = grd_out->len[0];
    typ_idx nx_i = grd_in->len[0];
    double  dx_o = grd_out->dcrd[0];
    double  dx_i = grd_in->dcrd[0];
    double  x_o  = grd_out->bcrd[0];
    double  x_i  = grd_in->bcrd[0];
    double  dx_o_2 = dx_o/2;
	
	arr A_out = Array(1,DOUBLE,nx_o);  

 /* char astr[2048];
    char wstr[2048];
    char *astr_end = NULL;
    char *wstr_end = NULL; */
    left = x_o - dx_o_2;
    kbeg = myRound2((left-x_i)/dx_i);
    for (i=0;i<nx_o;++i) {
    /*  astr[0] = '\0';
        wstr[0] = '\0';
        astr_end = astr;
        wstr_end = wstr; */
        widthsum = 0.0;
        wgtsum   = 0.0;
        right = x_o  + ((double)i+0.5)*dx_o;
        kend  = myRound2((right-x_i)/dx_i);
        if (kend  <  0){
            setToMiss(&A_out,i);
        } else if (kbeg >= nx_i){
            for (;i<nx_o;++i) { setToMiss(&A_out,i); }
            break;
        } else {
            if (kbeg  < 0)   { kbeg = 0; }
            if (kend >= nx_i) { kend = nx_i-1; }
            for (k=kbeg;k<=kend;++k) {
                if (!isMiss(A_in,k)){
                    x1 = x_i + ((double)k-0.5)*dx_i;
                    x2 = x1 + dx_i;
                    if (left  > x1) { x1 = left; }
                    if (right < x2) { x2 = right; }
                    width     = x2-x1;
                    widthsum += width;
                    wgtsum   += width*DBL(A_in,k);
                /*  astr_end += sprintf(astr_end," + %g",width);
                    wstr_end += sprintf(wstr_end," + %g*%g",width,DBL(A_in,k));
                    fprintf(stderr,"upScale1d: k=%lld, x1=%g, x2=%g, A_in=%g\n",k,x1,x2,iDBL(A_in,k)); */
                }
            }
            if (widthsum > 0){
                iDBL(&A_out,i) = wgtsum/widthsum;
            } else {
                setToMiss(&A_out,i);
            }
        /*  fprintf(stderr,"upScale1d: left=%g, right=%g, kbeg=%lld, kend=%lld: (%s)/(%s) = %g/%g = %g\n",left,right,kbeg,kend,wstr,astr,wgtsum,widthsum,iDBL(A_out,i));  */
        }
        left = right;
        kbeg = kend;
    }

	return A_out;
}

arr downScale1d(arr *restrict A_in, gridnd * grd_in, gridnd * grd_out) {
/*  Need to process missing values in A_in */
/*  printArrayFmtAllWHdr(stderr,A_in,"%g","downScale1d: A_in"); */
    fputs("downScale1d: ",stderr); printGridNd(stderr,grd_in);
    fputs("downScale1d: ",stderr); printGridNd(stderr,grd_out);
    typ_idx nx_o = grd_out->len[0];
    typ_idx nx_i = grd_in->len[0];
    double  dx_o = grd_out->dcrd[0];
    double  dx_i = grd_in->dcrd[0];
    double  x_o  = grd_out->bcrd[0];
    double  x_i  = grd_in->bcrd[0];

	arr A_out = Array(1,DOUBLE,nx_o);
    
	typ_idx i=0,k;
    while (isMiss(A_in,i)){ ++i; }
    double xleft = x_i  + (double)i*dx_i;
    double yleft = iDBL(A_in,i);
    typ_idx kbeg = myRound2((xleft -x_o)/dx_o);
	typ_idx kend = kbeg;
    for (k=0;k<kbeg;++k) {
    /*  fprintf(stderr,"downScale1d: set A_out[%lld] to missing\n",k,iDBL(&A_out,k)); */
        setToMiss(&A_out,k);
    }
	double xright,yright;
	double m,  b,  x;
    for (++i;i<nx_i;++i) {
        if (isMiss(A_in,i)){
            while (isMiss(A_in,i)){ ++i; }
            xleft = x_i  + (double)i*dx_i;
            yleft = iDBL(A_in,i);
            kbeg  = myRound2((xleft -x_o)/dx_o);
            for (;k<kbeg;++k) {
            /*  fprintf(stderr,"downScale1d: set A_out[%lld] to missing\n",k,iDBL(&A_out,k)); */
                setToMiss(&A_out,k);
            }
        } else {
            xright = x_i  + (double)i*dx_i;
            yright = iDBL(A_in,i);
            m = (yright-yleft)/dx_i;
            b = yleft - m*xleft;
            kend = myRound2((xright-x_o)/dx_o);
            if (kend  <  0){
            } else if (kbeg >= nx_o){
                break;
            } else {
                if (kbeg  < 0)   { kbeg = 0; }
                if (kend >= nx_o) { kend = nx_o-1; }
                for (k=kbeg;k<=kend;++k) {
                    x  = x_o + (double)k*dx_o;
                /*  fprintf(stderr,"downScale1d: set A_out[%lld] to missing\n",k,m*x+b); */
                    iDBL(&A_out,k) = m*x+b;
                }
            }
            xleft = xright;
            yleft = yright;
            kbeg = kend;
        }
    }
    for (k=kend+1;k<nx_o;++k) { setToMiss(&A_out,k); }

	return A_out;
}

arr interpGrid1d(arr *restrict A_in, gridnd * grd_in, gridnd * grd_out){
    if (grd_out->dcrd[0] < grd_in->dcrd[0]){
        return downScale1d(A_in,grd_in,grd_out);
    } else {
        return upScale1d  (A_in,grd_in,grd_out);
    }
}

#endif
