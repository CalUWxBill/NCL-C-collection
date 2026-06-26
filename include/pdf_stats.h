/* Created by Bill Scheftic */
/*
 *  Statistics and operations on probability density functions
 */
#ifndef  _PDF_STATS_H_
#define  _PDF_STATS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <arraymath2.h>
#include <print_arrays2.h>
#include <sort2.h>
#include <stats2.h>
#include <grid2.h>

double cdf_PercatVal(arr *,double,gridnd *);
double pdf_PercatVal(arr *,double,gridnd *);
double cdf_ValatPerc(arr *,double,gridnd *);
double pdf_ValatPerc(arr *,double,gridnd *);
arr    cdf_ValsatPercs(arr *,arr *,gridnd *);
arr    pdf_ValsatPercs(arr *,arr *,gridnd *);
double pdf_Mode(arr *,gridnd *);
double pdf_Mean(arr *,gridnd *);
double pdf_Var_mn(arr *,double,gridnd *);
double pdf_Var(arr *,gridnd *);

arr findCdfatPercs(arr *,typ_idx);
arr findValsatPercs(arr *,gridnd *,typ_idx);

arr accumCDF(arr *,gridnd *);
void normalizePDF(arr *,gridnd *);
arr findCondMean(arr *,gridnd *,typ_idx);
void findCondMean_Loop(arr *,arr *,gridnd *,
    typ_idx,typ_idx*,typ_idx,
    typ_idx*,typ_idx,typ_idx*,typ_idx*);
arr findCpdf(arr *, gridnd *,typ_idx);
void findCpdf_Loop(arr *,arr *,gridnd *,
    typ_idx,typ_idx*,typ_idx,
    typ_idx*,typ_idx,typ_idx*,typ_idx*);
arr findCdf(arr *, gridnd *,typ_idx);
void findCdf_Loop(arr *,arr *,gridnd *,
    typ_idx,typ_idx*,typ_idx,
    typ_idx*,typ_idx,typ_idx*,typ_idx*);
void findCpdfSlice(arr *,arr*,arr*,gridnd *,double*,typ_idx);


double cdf_PercatVal(arr *restrict cdf,double x,gridnd *restrict grd){
	double perc;
    typ_idx i_L   = grd->len[0] - 1;
    typ_idx i_Lm1 = i_L        - 1;
    double x_0   = calcGridValNd(grd,  0,0);
    double x_L   = calcGridValNd(grd,i_L,0);
    if (x < x_0) {
        double P_0   = iDBL(cdf,0);
        double P_1   = iDBL(cdf,1);
        double x_1   = calcGridValNd(grd,1,0);
        perc = expPercatValTail_Lower(x,P_0,P_1,x_0,x_1);
        fprintf(stderr,"cdf_PercatVal: using expPercatValTail_Lower, perc=%g, P_0=%g, P_1=%g, x_0=%g, x_1=%g, x=%g\n"
            ,perc,P_0,P_1,x_0,x_1,x);
    } else if (x > x_L) {
        double P_Lm1 = iDBL(cdf,i_Lm1);
        double P_L   = iDBL(cdf,i_L);
        double x_Lm1 = calcGridValNd(grd,i_Lm1,0);
        perc = expPercatValTail_Upper(x,P_Lm1,P_L,x_Lm1,x_L);
        fprintf(stderr,"cdf_PercatVal: using expPercatValTail_Upper, perc=%g, P_Lm1=%g, P_L=%g, x_Lm1=%g, x_L=%g, x=%g\n"
            ,perc,P_Lm1,P_L,x_Lm1,x_L,x);
    } else {
        double result_i = calcGridIdxNd_Dbl(x,grd,0);
        typ_idx hi_i    = ceil(result_i);
        typ_idx lo_i    = floor(result_i);
        if (lo_i == hi_i){
            perc = iDBL(cdf,lo_i);
        } else {
            perc = linInterp(result_i,(double)lo_i,(double)hi_i,iDBL(cdf,lo_i),iDBL(cdf,hi_i));
        }
	}
	return perc;
}

double pdf_PercatVal(arr *restrict pdf,double val,gridnd *restrict grd){
    arr cdf     = accumCDF(pdf,grd);
    double perc = cdf_PercatVal(&cdf,val,grd);
    freeAr(&cdf);
    return perc;
}

double cdf_ValatPerc(arr *restrict cdf,double perc,gridnd *restrict grd){
    typ_idx i_L = grd->len[0] - 1;
    double  P_0 = iDBL(cdf,0);
    double  P_L = iDBL(cdf,i_L);

    double result_i;
	if (perc < P_0){
        double P_1   = iDBL(cdf,1);
        result_i = lnValatPercTail_Lower(perc,P_0,P_1,0.0,1.0);
        fprintf(stderr,"cdf_ValatPerc: using lnValatPercTail_Lower, perc=%g, P_0=%g, P_1=%g, result_i=%g\n",perc,P_0,P_1,result_i);
	} else if (perc > P_L){
        typ_idx i_Lm1 = i_L - 1;
        double  P_Lm1 = iDBL(cdf,i_Lm1);
        result_i = lnValatPercTail_Upper(perc,P_Lm1,P_L,(double)i_Lm1,(double)i_L);
        fprintf(stderr,"cdf_ValatPerc: using lnValatPercTail_Upper, perc=%g, P_Lm1=%g, P_L=%g, result_i=%g\n",perc,P_Lm1,P_L,result_i);
	} else {
        typ_idx i = 0;
        while (perc > iDBL(cdf,i)) { i++; }
		result_i = linInterp(perc,iDBL(cdf,i-1),iDBL(cdf,i),(double)i-1,(double)i);
    }
    
    double val = calcGridValNd_Dbl(grd,result_i,0);
    if (val < 0.0) { val = 0.0; }
	return val;
}

double pdf_ValatPerc(arr *restrict pdf,double perc,gridnd *restrict grd){
    arr cdf    = accumCDF(pdf,grd);
    double val = cdf_ValatPerc(&cdf,perc,grd);
    freeAr(&cdf);
    return val;
}

arr cdf_ValsatPercs(arr *restrict cdf,arr *restrict percs,gridnd *restrict grd){
    typ_idx i_L   = grd->len[0] - 1;
    typ_idx i_Lm1 = i_L - 1;
    double  P_0   = iDBL(cdf,0);
    double  P_1   = iDBL(cdf,1);
    double  P_L   = iDBL(cdf,i_L);
    double  P_Lm1 = iDBL(cdf,i_Lm1);

	typ_idx ip = 0;
	double result_i,val;
    arr vals = Array(1,DOUBLE,percs->tlen);
    
    while ((ip < percs->tlen) && (iDBL(percs,ip) < P_0)) {
        result_i = lnValatPercTail_Lower(iDBL(percs,ip),P_0,P_1,0.0,1.0);
        val      = calcGridValNd_Dbl(grd,result_i,0);
        if (val < 0.0) { iDBL(&vals,ip) = 0.0; } else { iDBL(&vals,ip) = val; }
        ip++;
    }
    if (ip == percs->tlen){ return vals; }

    typ_idx ic = 1;
    while ((ip < percs->tlen) && (iDBL(percs,ip) <= P_L)) {
        while (iDBL(percs,ip) > iDBL(cdf,ic)) { ic++; }
		result_i = linInterp(iDBL(percs,ip),iDBL(cdf,ic-1),iDBL(cdf,ic),(double)ic-1,(double)ic);
        val = calcGridValNd_Dbl(grd,result_i,0);
        if (val < 0.0) { iDBL(&vals,ip) = 0.0; } else { iDBL(&vals,ip) = val; }
        ip++;
    }
    if (ip == percs->tlen){ return vals; }

    while (ip < percs->tlen) {
        result_i = lnValatPercTail_Upper(iDBL(percs,ip),P_Lm1,P_L,(double)i_Lm1,(double)i_L);
        val      = calcGridValNd_Dbl(grd,result_i,0);
        if (val < 0.0) { iDBL(&vals,ip) = 0.0; } else { iDBL(&vals,ip) = val; }
        ip++;
    }
	return vals;
}

arr cdf_ValsatPercs_z(arr *restrict cdf,arr *restrict percs,gridnd *restrict grd){
    typ_idx i_L   = grd->len[0] - 1;
    typ_idx i_Lm1 = i_L - 1;
    double  P_0   = iDBL(cdf,0);
    double  P_1   = iDBL(cdf,1);
    double  P_L   = iDBL(cdf,i_L);
    double  P_Lm1 = iDBL(cdf,i_Lm1);

	typ_idx ip = 0;
	double result_i;
    arr vals = Array(1,DOUBLE,percs->tlen);
    
    while ((ip < percs->tlen) && (iDBL(percs,ip) < P_0)) {
        result_i = lnValatPercTail_Lower(iDBL(percs,ip),P_0,P_1,0.0,1.0);
        iDBL(&vals,ip) = calcGridValNd_Dbl(grd,result_i,0);
        ip++;
    }
    if (ip == percs->tlen){ return vals; }

    typ_idx ic = 1;
    while ((ip < percs->tlen) && (iDBL(percs,ip) <= P_L)) {
        while (iDBL(percs,ip) > iDBL(cdf,ic)) { ic++; }
		result_i = linInterp(iDBL(percs,ip),iDBL(cdf,ic-1),iDBL(cdf,ic),(double)ic-1,(double)ic);
        iDBL(&vals,ip) = calcGridValNd_Dbl(grd,result_i,0);
        ip++;
    }
    if (ip == percs->tlen){ return vals; }

    while (ip < percs->tlen) {
        result_i = lnValatPercTail_Upper(iDBL(percs,ip),P_Lm1,P_L,(double)i_Lm1,(double)i_L);
        iDBL(&vals,ip) = calcGridValNd_Dbl(grd,result_i,0);
        ip++;
    }
	return vals;
}

arr pdf_ValsatPercs(arr *restrict pdf,arr *restrict percs,gridnd *restrict grd){
    arr cdf  = accumCDF(pdf,grd);
    arr vals = cdf_ValsatPercs(&cdf,percs,grd);
    freeAr(&cdf);
    return vals;
}

double pdf_Mode(arr *restrict pdf,gridnd *restrict grdpdf){
	typ_idx i;
	double pdfmax = 0;
	double iest = 0;
	double mode = 0;

	/* find mode */
	for(i=0;i<pdf->tlen;i++){
		if (DBL(pdf,i) > pdfmax) {
			pdfmax = DBL(pdf,i);
			iest = (double)i;
		}
	}
	mode = (iest+0.5)*grdpdf->dcrd[0];

	return mode;
}

double pdf_Mean(arr *restrict pdf,gridnd *restrict grdpdf){
	typ_idx i;
    double dx   = grdpdf->dcrd[0];

    double x,f_x,mean=0;
	for(i=0;i<pdf->tlen;i++){
        x     = calcGridValNd(grdpdf,i,0);
        f_x   = iDBL(pdf,i);
		mean += x*f_x*dx;
	}

	return mean;
}

double pdf_Var_mn(arr *restrict pdf,double mean,gridnd *restrict grdpdf){
	typ_idx i;
    double dx   = grdpdf->dcrd[0];

    double x,f_x,var=0;
	for(i=0;i<pdf->tlen;i++){
        x    = calcGridValNd(grdpdf,i,0);
        f_x  = iDBL(pdf,i);
        var += pow(x-mean,2)*f_x*dx;
	}

	return var;
}

double pdf_Var(arr *restrict pdf,gridnd *restrict grdpdf){
	double mean = pdf_Mean(pdf,grdpdf);
	return pdf_Var_mn(pdf,mean,grdpdf);
}


arr findCdfatPercs(arr *restrict X,typ_idx numpercs) {
	typ_idx i;
    arr percs = Array(1,DOUBLE,numpercs);
    double np1 = (double)numpercs + 1.0;
	for(i=0;i<numpercs;i++){
		iDBL(&percs,i) = (double)(i+1)/np1;
	}
    arr m = calcValsatPercs(X, &percs);
    freeAr(&percs);
	return m;
}

arr findValsatPercs(arr *restrict cdf,gridnd *restrict grd,typ_idx numpercs){
	typ_idx i;
    arr percs    = Array(1,DOUBLE,numpercs);
    double np1 = (double)numpercs + 1.0;
	for(i=0;i<numpercs;i++){
		iDBL(&percs,i) = (double)(i+1)/np1;
	}
    arr m = cdf_ValsatPercs(cdf,&percs,grd);
    freeAr(&percs);
	return m;
}


void halfStepCDF(arr *restrict cdf){
    typ_idx i, nx = cdf->len[0];
	double dP_0 = (iDBL(cdf,1)    - iDBL(cdf,0)   );
	double dP_L = (iDBL(cdf,nx-1) - iDBL(cdf,nx-2));
	double half_step = 0.5*amin3(iDBL(cdf,0),dP_0,dP_L);
    /* double half_step = iDBL(cdf,0)*0.5; */
    for(i=0;i<nx;i++){ iDBL(cdf,i) = iDBL(cdf,i) - half_step; }
	return;
}

arr accumCDF(arr *restrict pdf,gridnd *restrict grd){
	double tcdf;

    typ_idx i, nx = pdf->len[0];
    double     dx = grd->dcrd[0];
	arr cdf = Array(1,DOUBLE,nx);

    tcdf = iDBL(pdf,0)*dx;
	iDBL(&cdf,0) = tcdf;
	for(i=1;i<nx;i++){
        tcdf += iDBL(pdf,i)*dx;
		iDBL(&cdf,i) = tcdf;
	}

    if (tcdf != 1.0){
        if (tcdf == 0) {
            for(i=0;i<nx;i++){ iDBL(&cdf,i) = 0; }
        } else {
            for(i=0;i<nx;i++){ iDBL(&cdf,i) = iDBL(&cdf,i)/tcdf; }
        }
    }

	return cdf;
}

void normalizeCDF(arr *restrict cdf){
/*  static double tcdf_tolerance = 1e-6; */
	double tcdf;

    typ_idx i, nx = cdf->len[0];

    tcdf = iDBL(cdf,nx-1);

/*  if (fabs(tcdf-1.0) > tcdf_tolerance){ */
    if (tcdf != 1.0){
        if (tcdf == 0) {
            for(i=0;i<nx;i++){ iDBL(cdf,i) = 0; }
        } else {
            for(i=0;i<nx;i++){ iDBL(cdf,i) = iDBL(cdf,i)/tcdf; }
        }
    }
/*  } */

	return;
}

void normalizePDF(arr *restrict pdf,gridnd *restrict grd){
/*  static double tcdf_tolerance = 1e-6; */
	double tcdf = 0.0;

    typ_idx i, nx = pdf->len[0];
    double     dx = grd->dcrd[0];

	for(i=0;i<nx;i++){
        tcdf += iDBL(pdf,i)*dx;
	}

/*  if (fabs(tcdf-1.0) > tcdf_tolerance){ */
    if (tcdf != 1.0){
        if (tcdf == 0) {
            for(i=0;i<nx;i++){ iDBL(pdf,i) = 0; }
        } else {
            for(i=0;i<nx;i++){ iDBL(pdf,i) = iDBL(pdf,i)/tcdf; }
        }
    }
/*  } */

	return;
}


arr findCondMean(arr *restrict jpdf,gridnd *restrict grd,typ_idx subdim){
    gridnd subgrd;
    subGridNd(&subgrd,grd,1,&subdim);
    
    typ_idx *idx       = init0(grd->n,  TYPIDX);
    typ_idx *c         = init0(grd->n-1,TYPIDX);
    typ_idx *map_c2all = init0(grd->n-1,TYPIDX);
    typ_idx *clens = initNdLoopCounterLengthsWMaps2(grd->n,1,&subdim,grd->len,map_c2all);
	arr mean = ArrayFromList(grd->n-1,DOUBLE,clens);
    
    findCondMean_Loop(&mean,jpdf,&subgrd,grd->n,map_c2all,subdim,idx,0,c,clens);

    freeGridNd(&subgrd);
    free(idx);
    free(c);
    free(clens);
    free(map_c2all);
	return mean;
}

void findCondMean_Loop(arr *restrict OUT,arr *restrict IN,gridnd *restrict subgrd,
    typ_idx ndims,typ_idx *map_c2all,typ_idx subdim,
    typ_idx *idx,typ_idx dim,typ_idx *c,typ_idx *clens){

	if (dim == ndims-1){
        arr pdf = grab1dAr(IN, subdim, idx);
        normalizePDF(&pdf,subgrd);
		cDBL(OUT,c) = pdf_Mean(&pdf,subgrd);
        freeAr(&pdf);
	} else {
        typ_idx j;
		for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
		/*	fputs("findCondMean_Loop: ",stderr);
			for(j=0;j<=dim;j++){ fprintf(stderr,"c[%d]=%d ",j,c[j]); }
			fputs("\n",stderr);
		 */
            j = map_c2all[dim];
            if (j >= 0){ idx[j] = c[dim]; }
            findCondMean_Loop(OUT,IN,subgrd,ndims,map_c2all,subdim,idx,dim+1,c,clens);
		}
	}

	return;
}

arr findCpdf(arr *restrict jpdf, gridnd *restrict grd,typ_idx subdim){
	arr cpdf = ArrayFromList(grd->n,DOUBLE,grd->len);
    
    gridnd subgrd;
    subGridNd(&subgrd,grd,1,&subdim);
    
    typ_idx *idx       = init0(grd->n,  TYPIDX);
    typ_idx *c         = init0(grd->n-1,TYPIDX);
    typ_idx *map_c2all = init0(grd->n-1,TYPIDX);
    typ_idx *clens = initNdLoopCounterLengthsWMaps2(grd->n,1,&subdim,grd->len,map_c2all);
    
    findCpdf_Loop(&cpdf,jpdf,&subgrd,grd->n,map_c2all,subdim,idx,0,c,clens);

    freeGridNd(&subgrd);
    free(idx);
    free(c);
    free(clens);
    free(map_c2all);
	return cpdf;
}

void findCpdf_Loop(arr *restrict OUT,arr *restrict IN,gridnd *restrict subgrd,
    typ_idx ndims,typ_idx *map_c2all,typ_idx subdim,
    typ_idx *idx,typ_idx dim,typ_idx *c,typ_idx *clens){

	if (dim == ndims-1){
        arr pdf = grab1dAr(IN, subdim, idx);
        normalizePDF(&pdf,subgrd);
        assignPart2(OUT,&pdf,&subdim,idx);
        freeAr(&pdf);
	} else {
        typ_idx j;
		for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
		/*	fputs("findCpdf_Loop: ",stderr);
			for(j=0;j<=dim;j++){ fprintf(stderr,"c[%d]=%d ",j,c[j]); }
			fputs("\n",stderr);
		 */
            j = map_c2all[dim];
            if (j >= 0){ idx[j] = c[dim]; }
            findCpdf_Loop(OUT,IN,subgrd,ndims,map_c2all,subdim,idx,dim+1,c,clens);
		}
	}

	return;
}

arr findCdf(arr *restrict jpdf, gridnd *restrict grd,typ_idx subdim){
	arr ccdf = ArrayFromList(grd->n,DOUBLE,grd->len);
    
    gridnd subgrd;
    subGridNd(&subgrd,grd,1,&subdim);
    
    typ_idx *idx       = init0(grd->n,  TYPIDX);
    typ_idx *c         = init0(grd->n-1,TYPIDX);
    typ_idx *map_c2all = init0(grd->n-1,TYPIDX);
    typ_idx *clens = initNdLoopCounterLengthsWMaps2(grd->n,1,&subdim,grd->len,map_c2all);
    
    findCdf_Loop(&ccdf,jpdf,&subgrd,grd->n,map_c2all,subdim,idx,0,c,clens);

    freeGridNd(&subgrd);
    free(idx);
    free(c);
    free(clens);
    free(map_c2all);
	return ccdf;
}

void findCdf_Loop(arr *restrict OUT,arr *restrict IN,gridnd *restrict subgrd,
    typ_idx ndims,typ_idx *map_c2all,typ_idx subdim,
    typ_idx *idx,typ_idx dim,typ_idx *c,typ_idx *clens){

	if (dim == ndims-1){
        arr pdf = grab1dAr(IN, subdim, idx);
        arr cdf = accumCDF(&pdf,subgrd);
        assignPart2(OUT,&cdf,&subdim,idx);
        freeAr(&pdf);
        freeAr(&cdf);
	} else {
        typ_idx j;
		for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
		/*	fputs("findCdf_Loop: ",stderr);
			for(j=0;j<=dim;j++){ fprintf(stderr,"c[%d]=%d ",j,c[j]); }
			fputs("\n",stderr);
		 */
            j = map_c2all[dim];
            if (j >= 0){ idx[j] = c[dim]; }
            findCdf_Loop(OUT,IN,subgrd,ndims,map_c2all,subdim,idx,dim+1,c,clens);
		}
	}

	return;
}


void findCpdfSlice(arr *restrict jpdf,arr *pdf,arr *cdf,gridnd *restrict grd,double *vals,typ_idx subdim){
    gridnd subgrd;
    subGridNd(&subgrd,grd,1,&subdim);
    *pdf = findSliceOnGrid(jpdf,grd,vals,subdim);
    normalizePDF(pdf,&subgrd);
    *cdf = accumCDF(pdf,&subgrd);

    freeGridNd(&subgrd);
	return;
}



#endif

