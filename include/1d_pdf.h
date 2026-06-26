/* Created by Bill Scheftic */
/* Create probability density functions using a kernel density estimators */
#ifndef  _1D_PDF_H_
#define  _1D_PDF_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <math_supp.h>
#include <arrayinit2.h>
#include <matrix_op2.h>
#include <grid2.h>
#include <arraymath2.h>

double applyKernel1d(double p1,double p2,double h){
    double t    = (p2-p1)/h;
    double t_2  = t*t;
    double kval = (1/sqrt(2*M_PI))*exp(-(t_2)/2);
	return kval;
}

void KernelCalcLoop1d(arr *restrict jpdf,double *jcdf_in,double *jcdf_out,arr *restrict array,gridnd *restrict grd,double hs,typ_idx idx,typ_idx cbeg,typ_idx cend){
	typ_idx c;
	double par, pgrd;

    for(c=cbeg;c<cend;++c){
        par  = iDBL(array,idx);
		pgrd = calcGridValNd(grd,c,0);

		if ( isInGrid(&pgrd,grd) ) {
			iDBL(jpdf,c) = applyKernel1d(par,pgrd,hs);
			*jcdf_in += iDBL(jpdf,c);
		} else {
			*jcdf_out += applyKernel1d(par,pgrd,hs);
		}
    }
	return;
}

void JPdfAccumLoop1d(arr *restrict jpdf_sum,arr *restrict jpdf,double factor,typ_idx cbeg,typ_idx cend){
	typ_idx c;
    for(c=cbeg;c<cend;++c){ iDBL(jpdf_sum,c) += iDBL(jpdf,c)*factor; }
	return;
}

void ZeroOutLoop1d(arr *restrict jpdf,typ_idx cbeg,typ_idx cend){
	typ_idx c;
    for(c=cbeg;c<cend;++c){ iDBL(jpdf,c) = 0.0; }
	return;
}

/*-------------------------*/
/*  KernelPdf1d            */
/*-------------------------*/
arr KernelPdf1d(gridnd *restrict grd,arr *restrict array){
	typ_idx j,l;

	for (j=0;j<grd->n;++j){
		fprintf(stderr,"KernelPdf1d: grd[%lld] bcrd=%g, dcrd=%g, len=%lld\n",j,grd->bcrd[j],grd->dcrd[j],grd->len[j]);
	}

	double jcdf_in,jcdf_out,jcdf_tot,factor;

	arr jpdf     = ArrayFromList(grd->n,DOUBLE,grd->len);
	arr jpdf_sum = ArrayFromList(grd->n,DOUBLE,grd->len);

	double hs = 1.5;
    double hs_3 = 3*hs;

	typ_idx cbeg,cend,cbeg_in,cend_in;

	/* For each value of qpf apply kernel and add to pdf */
	typ_idx nmiss = 0;
	double dcrd = grd->dcrd[0];

	for(l=0;l<array->tlen;++l) {
		fprintf(stderr,"KernelPdf1d: l=%lld\n",l);
		if ( isMiss(array,l) ){
			nmiss = nmiss + 1;
		} else {
            cbeg = calcGridIdxNd(iDBL(array,l)-hs_3,grd,0);
            cend = calcGridIdxNd(iDBL(array,l)+hs_3,grd,0);
            if (cbeg <  0)         { cbeg_in = 0;            } else { cbeg_in = cbeg; }
            if (cend >= grd->len[0]){ cend_in = grd->len[0]-1; } else { cend_in = cend; }

			KernelCalcLoop1d(&jpdf,&jcdf_in,&jcdf_out,array,grd,hs,l,cbeg,cend);

			jcdf_tot = jcdf_in+jcdf_out;
			if (jcdf_tot != 0){
				factor = 1.0/jcdf_in;
				JPdfAccumLoop1d(&jpdf_sum,&jpdf,factor,cbeg_in,cend_in);
			}
			ZeroOutLoop1d(&jpdf,cbeg_in,cend_in);
            jcdf_in = 0; jcdf_out = 0;
		}
	}

	fprintf(stderr,"KernelPdf1d: 3 nmiss = %lld\n",nmiss);
	double nnonmiss = (double)(array->tlen-nmiss);

	fct1ar1sRef(Div,&jpdf_sum,&jpdf_sum,nnonmiss);

	double jcdf1 = sumAllAr(&jpdf_sum);
	fprintf(stderr,"KernelPdf1d: jcdf1 = %g\n",jcdf1);
	
	fct1ar1sRef(Div,&jpdf_sum,&jpdf_sum,dcrd*jcdf1);

	jcdf1 = sumAllAr(&jpdf_sum);
	fprintf(stderr,"KernelPdf1d: jcdf1 = %g,jcdf1*dcrd=%g\n",jcdf1,jcdf1*dcrd);

	freeAr(&jpdf);
	return jpdf_sum;
}


double SingleVarNorm(double x,double inv_Var,double bef_exp,double Mu){
	double x_Mu = (x-Mu);
	double D_sq = x_Mu*x_Mu*inv_Var;
	double f_x  = bef_exp*exp(-0.5*D_sq);

	if (!isfinite(f_x)){
		fprintf(stderr,"SingleVarNorm: x = %g, Mu = %g, inv_Var = %g, bef_exp = %g, x_Mu = %g, D_sq = %g, f_x = %g\n"
            ,x,Mu,inv_Var,bef_exp,x_Mu,D_sq,f_x);
		exit(0);
	}
	return f_x;
}

void SingleVarNormLoop(arr *restrict jpdf,double *jcdf_in,double *jcdf_out,double x_ar,gridnd *restrict grd,double inv_Var,double bef_exp
    ,typ_idx cbeg,typ_idx cend){
    /* fprintf(stderr,"SingleVarNormLoop: c from %lld to %lld\n",cbeg,cend); */
	typ_idx c;
	double pdf_tmp, x_grd;

    for(c=cbeg;c<=cend;++c){
		x_grd   = calcGridValNd(grd,c,0);
		pdf_tmp = SingleVarNorm(x_grd,inv_Var,bef_exp,x_ar);

        if ( isInGrid(&x_grd,grd) ) {
            iDBL(jpdf,c) = pdf_tmp;
            *jcdf_in  += iDBL(jpdf,c);
        } else {
            *jcdf_out += pdf_tmp;
        }
    }
	return;
}

/*--------------------------*/
/*  NormKernelPdf1d */
/*--------------------------*/
arr NormKernelPdf1d(gridnd *restrict grd,arr *restrict array){
	typ_idx j,l;

    arr X_srtd = qsortArray(array);
    typ_idx nx = X_srtd.tlen;
	
	for (j=0;j<grd->n;++j){
		fprintf(stderr,"NormKernelPdf1d: grd[%lld] bcrd=%g, dcrd=%g, len=%lld\n",j,grd->bcrd[j],grd->dcrd[j],grd->len[j]);
	}

	double jcdf_in,jcdf_out,factor,h_i;

	arr jpdf     = ArrayFromList(grd->n,DOUBLE,grd->len);
	arr jpdf_sum = ArrayFromList(grd->n,DOUBLE,grd->len);

	typ_idx cbeg,cend,cbeg_in,cend_in;

	/* For each value of qpf apply kernel and add to pdf */
	typ_idx nmiss = 0;

	double dcrd = grd->dcrd[0];
	double Var,inv_Var,bef_exp,x_ar;

	typ_idx n_nearest_pnts = (typ_idx)amin2(nx,9);
    arr Xlocal             = assign1dtoNd(pntr_of(&X_srtd), 1, DOUBLE, n_nearest_pnts);
    double **pXlocal       = (double **)ppntr_of(&Xlocal);
    typ_idx half_pnts      = (typ_idx)floor( ((double)n_nearest_pnts)/2 );
    typ_idx l_min          = 0 - half_pnts;
    typ_idx l_max          = l_min + n_nearest_pnts - 1;
	for(l=0;l<nx;++l) {
        if ((l_min > 0) && (l_max < nx)){
            (*pXlocal)++;
        }
		if ( isMiss(&X_srtd,l) ){
			nmiss = nmiss + 1;
		} else {
            jcdf_in = 0; jcdf_out = 0;
            Var = VarS(&Xlocal);
            h_i = sqrt(Var);
            
            cbeg = calcGridIdxNd(iDBL(&X_srtd,l)-3*h_i,grd,0);
            cend = calcGridIdxNd(iDBL(&X_srtd,l)+3*h_i,grd,0);
            if (cbeg <  0)         { cbeg_in = 0;            } else { cbeg_in = cbeg; }
            if (cend >= grd->len[0]){ cend_in = grd->len[0]-1; } else { cend_in = cend; }

            inv_Var = 1.0/Var;
			bef_exp = (1.0/sqrt(2*M_PI*Var));

			x_ar = iDBL(&X_srtd,l);
			SingleVarNormLoop(&jpdf,&jcdf_in,&jcdf_out,x_ar,grd,inv_Var,bef_exp,cbeg,cend);
			if (jcdf_in != 0){
				factor = 1.0/jcdf_in;
				JPdfAccumLoop1d(&jpdf_sum,&jpdf,factor,cbeg_in,cend_in);
			}

			ZeroOutLoop1d(&jpdf,cbeg_in,cend_in);
		}
        ++l_min;
        ++l_max;
    }
    freeArShell(&Xlocal);

/*
    printArrayAllWHdr(stderr, jpdf_sum,"NormKernelPdf1d: factor=%g, jpdf_sum - ",factor);
*/

/*  fprintf(stderr,"NormKernelPdf1d: 3 nmiss = %lld\n",nmiss);  */
	double nnonmiss = (double)(nx-nmiss);
    double nnonmiss_pct = nnonmiss/nx;
    if (nnonmiss < 1){
        fillArWithMiss(&jpdf_sum);
        fprintf(stderr,"NormKernelPdf1d: Not enough non-missing values (%d), setting jpdf to missing\n",(int)nnonmiss);
    } else {
        fct1ar1sRef(Div,&jpdf_sum,&jpdf_sum,nnonmiss);
    
        double jcdf1 = sumAllAr(&jpdf_sum);
    /*  fprintf(stderr,"NormKernelPdf1d: jcdf1 = %g\n",jcdf1);  */
        
        fct1ar1sRef(Div,&jpdf_sum,&jpdf_sum,dcrd*jcdf1);
    
        jcdf1 = sumAllAr(&jpdf_sum);
        fprintf(stderr,"NormKernelPdf1d: nmiss = %lld, jcdf1 = %g,jcdf1*dcrd=%g\n",nmiss,jcdf1,jcdf1*dcrd);
    }
    
	freeAr(&X_srtd);
	freeAr(&jpdf);
	return jpdf_sum;
}

arr NormSmoothKernelPdf1d(gridnd *restrict grd,arr *restrict array,double kwidth){
    /*
	clock_t tm_start_all,tm_end_all;
    tm_start_all = clock();
    */

    static double PI2_n = 2*M_PI;
	typ_idx l;

    arr X_srtd = qsortArray(array);
    typ_idx nx = X_srtd.tlen;
	/*
    */
	typ_idx j;
    for (j=0;j<grd->n;++j){
		fprintf(stderr,"NormSmoothKernelPdf1d: grd[%lld] bcrd=%g, dcrd=%g, len=%lld\n",j,grd->bcrd[j],grd->dcrd[j],grd->len[j]);
	}
	/* For each value of qpf apply kernel and add to pdf */
	typ_idx nmiss = 0;

	double dcrd = grd->dcrd[0];

    double kVar = kwidth*kwidth;
    double inv_kVar =  1.0/kVar;
    double kbef_exp = (1.0/sqrt(PI2_n*kVar));
    
	double Var,inv_Var,bef_exp,x_ar;
    /* pointers to connect to already calculated parameters */
	double *pVar     = NULL;
    double *pinv_Var = NULL;
    double *pbef_exp = NULL;

	double jcdf_in,jcdf_out,factor,h_i;

	arr jpdf     = ArrayFromList(grd->n,DOUBLE,grd->len);
	arr jpdf_sum = ArrayFromList(grd->n,DOUBLE,grd->len);

	typ_idx cbeg,cend,cbeg_in,cend_in;

	typ_idx n_nearest_pnts = (typ_idx)amin2(nx,9);
    arr Xlocal             = assign1dtoNd(pntr_of(&X_srtd), 1, DOUBLE, n_nearest_pnts);
    double **pXlocal       = (double **)ppntr_of(&Xlocal);
    typ_idx half_pnts      = (typ_idx)floor( ((double)n_nearest_pnts)/2 );
    typ_idx l_min          = 0 - half_pnts;
    typ_idx l_max          = l_min + n_nearest_pnts - 1;
	for(l=0;l<nx;++l) {
	/*  fprintf(stderr,"NormSmoothKernelPdf1d: l=%lld\n",l); */
        if ((l_min > 0) && (l_max < nx)){
            (*pXlocal)++; /* Increments pointer along the array X_srtd */
        }
		if ( isMiss(&X_srtd,l) ){
			nmiss = nmiss + 1;
		} else {
            jcdf_in = 0; jcdf_out = 0;
            Var = VarS(&Xlocal);
            /*
            if (!isfinite(Var)){
                printArrayFmtAllWHdr(stderr,&Xlocal,"%g","NormSmoothKernelPdf1d: Var=%g, Xlocal - ",Var);
                exit(0);
            }
            */
            if (Var > kVar){
                inv_Var  =  1.0/Var;
                bef_exp  = (1.0/sqrt(PI2_n*Var));
                pVar     = &Var;
                pinv_Var = &inv_Var;
                pbef_exp = &bef_exp;
            } else {
                pVar     = &kVar;
                pinv_Var = &inv_kVar;
                pbef_exp = &kbef_exp;
            }
            h_i = sqrt(*pVar);
            /* fprintf(stderr,"NormSmoothKernelPdf1d: X_srtd=%g, h_i=%g\n",iDBL(&X_srtd,l),h_i); */

            cbeg = calcGridIdxNd(iDBL(&X_srtd,l)-3*h_i,grd,0);
            cend = calcGridIdxNd(iDBL(&X_srtd,l)+3*h_i,grd,0);
            if (cbeg <  0)         { cbeg_in = 0;            } else { cbeg_in = cbeg; }
            if (cend >= grd->len[0]){ cend_in = grd->len[0]-1; } else { cend_in = cend; }

			x_ar = iDBL(&X_srtd,l);

			SingleVarNormLoop(&jpdf,&jcdf_in,&jcdf_out,x_ar,grd,*pinv_Var,*pbef_exp,cbeg,cend);
			if (jcdf_in != 0){
				factor = 1.0/jcdf_in;
				JPdfAccumLoop1d(&jpdf_sum,&jpdf,factor,cbeg_in,cend_in);
			}
            /*
            if (isAnyNanInf(&jpdf_sum)){
                printArrayFmtAllWHdr(stderr,&X_srtd,  "%g","NormSmoothKernelPdf1d: kwidth=%g, kVar=%g, X_srtd - ",kwidth,kVar);
                printArrayFmtAllWHdr(stderr,&Xlocal,  "%g","NormSmoothKernelPdf1d: l=%lld, cbeg=%lld, cend=%lld, Var=%g, inv_Var=%g, pbef_exp=%g, x_ar=%g, Xlocal - ",  l,cbeg,cend,*pVar,*pinv_Var,*pbef_exp,x_ar);
                printArrayFmtAllWHdr(stderr,&jpdf,    "%g","NormSmoothKernelPdf1d: l=%lld, cbeg=%lld, cend=%lld, Var=%g, inv_Var=%g, pbef_exp=%g, x_ar=%g, jpdf - ",    l,cbeg,cend,*pVar,*pinv_Var,*pbef_exp,x_ar);
                printArrayFmtAllWHdr(stderr,&jpdf_sum,"%g","NormSmoothKernelPdf1d: l=%lld, cbeg=%lld, cend=%lld, Var=%g, inv_Var=%g, pbef_exp=%g, x_ar=%g, jpdf_sum - ",l,cbeg,cend,*pVar,*pinv_Var,*pbef_exp,x_ar);
                printGridNd(stderr,grd);
                exit(0);
            }
            */
			ZeroOutLoop1d(&jpdf,cbeg_in,cend_in);
		}
        ++l_min;
        ++l_max;
    }
    freeArShell(&Xlocal);

	double nnonmiss = (double)(nx-nmiss);
    double nnonmiss_pct = nnonmiss/nx;
    if (isAnyNanInf(&jpdf_sum)){
        printArrayFmtAllWHdr(stderr,&X_srtd,  "%g","NormSmoothKernelPdf1d: kwidth=%g, kVar=%g, X_srtd - ",kwidth,kVar);
        printArrayFmtAllWHdr(stderr,&Xlocal,  "%g","NormSmoothKernelPdf1d: l=%lld, cbeg=%lld, cend=%lld, Var=%g, inv_Var=%g, pbef_exp=%g, x_ar=%g, Xlocal - ",  l,cbeg,cend,*pVar,*pinv_Var,*pbef_exp,x_ar);
        printArrayFmtAllWHdr(stderr,&jpdf,    "%g","NormSmoothKernelPdf1d: l=%lld, cbeg=%lld, cend=%lld, Var=%g, inv_Var=%g, pbef_exp=%g, x_ar=%g, jpdf - ",    l,cbeg,cend,*pVar,*pinv_Var,*pbef_exp,x_ar);
        printArrayFmtAllWHdr(stderr,&jpdf_sum,"%g","NormSmoothKernelPdf1d: l=%lld, cbeg=%lld, cend=%lld, Var=%g, inv_Var=%g, pbef_exp=%g, x_ar=%g, jpdf_sum - ",l,cbeg,cend,*pVar,*pinv_Var,*pbef_exp,x_ar);
        printGridNd(stderr,grd);
        fillArWithMiss(&jpdf_sum);
    } else {
        if (nnonmiss < 1){
            fillArWithMiss(&jpdf_sum);
            fprintf(stderr,"NormSmoothKernelPdf1d: too many missing values, setting jpdf to missing, nmiss=%lld\n",nmiss);
            printArrayFmtAllWHdr(stderr,&X_srtd,"%g","NormSmoothKernelPdf1d: X_srtd - ");
        } else {
        /*  printArrayFmtAllWHdr(stderr,&jpdf_sum,"%g","NormSmoothKernelPdf1d: jpdf_sum - "); */
            fct1ar1sRef(Div,&jpdf_sum,&jpdf_sum,nnonmiss);
        
            double jcdf1 = sumAllAr(&jpdf_sum);
        /*  fprintf(stderr,"NormSmoothKernelPdf1d: jcdf1 = %g\n",jcdf1);
            printArrayFmtAllWHdr(stderr,&jpdf_sum,"%g","NormSmoothKernelPdf1d: jpdf_sum - ");  */
            
            fct1ar1sRef(Div,&jpdf_sum,&jpdf_sum,dcrd*jcdf1);
        
        /*  jcdf1 = sumAllAr(&jpdf_sum);
            fprintf(stderr,"NormSmoothKernelPdf1d: nmiss = %lld, jcdf1 = %g,jcdf1*dcrd=%g\n",nmiss,jcdf1,jcdf1*dcrd);   */
        }
    }
    
	freeAr(&X_srtd);
	freeAr(&jpdf);
    /*
    tm_end_all = clock();
    double tm_NormSmoothKernelPdf1d = (double) (tm_end_all-tm_start_all) / CLOCKS_PER_SEC;

    fprintf(stderr,"tm_NormSmoothKernelPdf1d =%5.2f\n",tm_NormSmoothKernelPdf1d);
    */
	return jpdf_sum;
}

arr NormSmoothKernelPdf1dConstWidth(gridnd *restrict grd,arr *restrict array,double kwidth){
    static double PI2_n = 2*M_PI;
	typ_idx j,l;

	for (j=0;j<grd->n;++j){
		fprintf(stderr,"NormSmoothKernelPdf1dConstWidth: grd[%lld] bcrd=%g, dcrd=%g, len=%lld\n",j,grd->bcrd[j],grd->dcrd[j],grd->len[j]);
	}

	double jcdf_in,jcdf_out,factor;

	arr jpdf     = ArrayFromList(grd->n,DOUBLE,grd->len);
	arr jpdf_sum = ArrayFromList(grd->n,DOUBLE,grd->len);

	typ_idx cbeg,cend,cbeg_in,cend_in;

	/* For each value of qpf apply kernel and add to pdf */
	typ_idx nmiss = 0;

	double dcrd = grd->dcrd[0];

	double x_ar;
	double kVar = kwidth*kwidth;

	double inv_kVar,kbef_exp;
	inv_kVar = 1.0/kVar;
    kbef_exp = (1.0/sqrt(PI2_n*kVar));

    /* pointers to connect to already calculated parameters */
	double *pVar     = &kVar;
    double *pinv_Var = &inv_kVar;
    double *pbef_exp = &kbef_exp;
    double h_i = sqrt(*pVar);
    double h_3 = 3*h_i;

    double *parray = pntr_of(array);
	for(l=0; l<array->tlen; ++l,parray++) {
		if ( isMiss(array,l) ){
			nmiss = nmiss + 1;
		} else {
            cbeg = calcGridIdxNd(*parray-h_3,grd,0);
            cend = calcGridIdxNd(*parray+h_3,grd,0);
            if (cbeg <  0)         { cbeg_in = 0;            } else { cbeg_in = cbeg; }
            if (cend >= grd->len[0]){ cend_in = grd->len[0]-1; } else { cend_in = cend; }

			x_ar = *parray;

			SingleVarNormLoop(&jpdf,&jcdf_in,&jcdf_out,x_ar,grd,*pinv_Var,*pbef_exp,cbeg,cend);

			if (jcdf_in != 0){
				factor = 1.0/jcdf_in;
				JPdfAccumLoop1d(&jpdf_sum,&jpdf,factor,cbeg_in,cend_in);
			}
			ZeroOutLoop1d(&jpdf,cbeg_in,cend_in);
            jcdf_in = 0; jcdf_out = 0;
		}
    }

/*  fprintf(stderr,"NormSmoothKernelPdf1dConstWidth: 3 nmiss = %lld\n",nmiss);  */
	double nnonmiss = (double)(array->tlen-nmiss);
    double nnonmiss_pct = nnonmiss/array->tlen;
    if (nnonmiss < 1){
        fillArWithMiss(&jpdf_sum);
        fprintf(stderr,"NormSmoothKernelPdf1dConstWidth: Not enough non-missing values (%d), setting jpdf to missing\n",(int)nnonmiss);
    } else {
        fct1ar1sRef(Div,&jpdf_sum,&jpdf_sum,nnonmiss);
    
        double jcdf1 = sumAllAr(&jpdf_sum);
    /*  fprintf(stderr,"NormSmoothKernelPdf1dConstWidth: jcdf1 = %g\n",jcdf1);  */
        
        fct1ar1sRef(Div,&jpdf_sum,&jpdf_sum,dcrd*jcdf1);
    
    /*  jcdf1 = sumAllAr(&jpdf_sum);
        fprintf(stderr,"NormSmoothKernelPdf1dConstWidth: nmiss = %lld, jcdf1 = %g,jcdf1*dcrd=%g\n",nmiss,jcdf1,jcdf1*dcrd);   */
    }
    
	freeAr(&jpdf);
	return jpdf_sum;
}

arr NormSmoothKernelPdf1dWgt(arr *restrict wgt,gridnd *restrict grd,arr *restrict array,double kwidth){
    static double PI2_n = 2*M_PI;
	typ_idx l;

    /* Need to sort the weights as well! */
    arr XIdx   = qsortArrayIdx(array);
    arr X_srtd = sortOnIdx(array,&XIdx);
    arr W_srtd = sortOnIdx(wgt  ,&XIdx);
    freeAr(&XIdx);
    /* arr X_srtd = qsortArray(array); */
    typ_idx nx = X_srtd.tlen;

    /*
        printArrayFmtAllWHdr(stderr,wgt   ,"%g","NormSmoothKernelPdf1dWgt: kwidth=%g, wgt - ",kwidth);
        printArrayFmtAllWHdr(stderr,array ,"%g","NormSmoothKernelPdf1dWgt: array - ");
        fputs("NormSmoothKernelPdf1dWgt: grd - ",stderr); printGridNd(stderr,grd);
    */
	double jcdf_in,jcdf_out,factor,h_i;

	arr jpdf     = ArrayFromList(grd->n,DOUBLE,grd->len);
	arr jpdf_sum = ArrayFromList(grd->n,DOUBLE,grd->len);

	typ_idx cbeg,cend,cbeg_in,cend_in;

	/* For each value of qpf apply kernel and add to pdf */
	typ_idx nmiss = 0;

	double dcrd = grd->dcrd[0];

    double kVar = kwidth*kwidth;

	double Var,inv_Var;
	double bef_exp;
    /* pointers to connect to already calculated parameters */
	double *pVar     = NULL;
    double *pinv_Var = NULL;
    double *pbef_exp = NULL;

	double inv_kVar = 1.0/kVar;
    double kbef_exp = 1.0/sqrt(PI2_n*kVar);

	typ_idx n_nearest_pnts = (typ_idx)amin2(nx,9);
    arr Xlocal             = assign1dtoNd(pntr_of(&X_srtd), 1, DOUBLE, n_nearest_pnts);
    double **pXlocal       = (double **)ppntr_of(&Xlocal);
    typ_idx half_pnts      = (typ_idx)floor( ((double)n_nearest_pnts)/2 );
    typ_idx l_min          = 0 - half_pnts;
    typ_idx l_max          = l_min + n_nearest_pnts - 1;
	for(l=0;l<nx;++l) {
        if ((l_min > 0) && (l_max < nx)){
            (*pXlocal)++;
        }
		if ( isMiss(&X_srtd,l) ){
			nmiss = nmiss + 1;
		} else {
            jcdf_in = 0; jcdf_out = 0;
            Var = VarS(&Xlocal);
            if (Var > kVar){
                inv_Var  = 1.0/Var;
                bef_exp  = 1.0/sqrt(PI2_n*Var);
                pVar     = &Var;
                pinv_Var = &inv_Var;
                pbef_exp = &bef_exp;
            } else {
                pVar     = &kVar;
                pinv_Var = &inv_kVar;
                pbef_exp = &kbef_exp;
            }
            h_i = sqrt(*pVar);
            cbeg = calcGridIdxNd(iDBL(&X_srtd,l)-3*h_i,grd,0);
            cend = calcGridIdxNd(iDBL(&X_srtd,l)+3*h_i,grd,0);
            if (cbeg <  0)         { cbeg_in = 0;            } else { cbeg_in = cbeg; }
            if (cend >= grd->len[0]){ cend_in = grd->len[0]-1; } else { cend_in = cend; }

			SingleVarNormLoop(&jpdf,&jcdf_in,&jcdf_out,iDBL(&X_srtd,l),grd,*pinv_Var,*pbef_exp,cbeg,cend);
            /*
            if (isAnyNanInf(&jpdf)){
                printArrayFmtAllWHdr(stderr,&jpdf,"%g","NormSmoothKernelPdf1dWgt: jpdf err: l=%lld, pinv_Var=%g, pbef_exp=%g, cbeg=%lld, cend=%lld, jpdf - "
                    ,l,*pinv_Var,*pbef_exp,cbeg,cend);
                printArrayFmtAllWHdr(stderr,&jpdf_sum,"%g","NormSmoothKernelPdf1dWgt: jpdf_sum - ");
                printArrayFmtAllWHdr(stderr,wgt   ,"%g","NormSmoothKernelPdf1dWgt: kwidth=%g, wgt - ",kwidth);
                printArrayFmtAllWHdr(stderr,array ,"%g","NormSmoothKernelPdf1dWgt: array - ");
                fputs("NormSmoothKernelPdf1dWgt: grd - ",stderr); printGridNd(stderr,grd);
                printArrayFmtAllWHdr(stderr,&X_srtd,  "%g","NormSmoothKernelPdf1dWgt: X_srtd - ");
                printArrayFmtAllWHdr(stderr,&W_srtd,  "%g","NormSmoothKernelPdf1dWgt: W_srtd - ");
                printArrayFmtAllWHdr(stderr,&Xlocal,  "%g","NormSmoothKernelPdf1dWgt: Xlocal - ");
                printGridNd(stderr,grd);
                exit(0);
            }
            */
			if (jcdf_in != 0){
				factor = iDBL(&W_srtd,l)/jcdf_in;
				JPdfAccumLoop1d(&jpdf_sum,&jpdf,factor,cbeg_in,cend_in);
			}
            /*
            if (isAnyNanInf(&jpdf_sum) || (sumAllAr(&jpdf) <= 0) || (cbeg <= 0)){
                printArrayFmtAllWHdr(stderr,&jpdf,"%g","NormSmoothKernelPdf1dWgt: jpdf_sum err: l=%lld, pinv_Var=%g, pbef_exp=%g, cbeg=%lld, cend=%lld, jcdf_in=%g, jcdf_out=%g, factor=%g, jpdf - "
                    ,l,*pinv_Var,*pbef_exp,cbeg,cend,jcdf_in,jcdf_out,factor);
                printArrayFmtAllWHdr(stderr,&jpdf_sum,"%g","NormSmoothKernelPdf1dWgt: jpdf_sum - ");
                printArrayFmtAllWHdr(stderr,wgt   ,"%g","NormSmoothKernelPdf1dWgt: kwidth=%g, wgt - ",kwidth);
                printArrayFmtAllWHdr(stderr,array ,"%g","NormSmoothKernelPdf1dWgt: array - ");
                fputs("NormSmoothKernelPdf1dWgt: grd - ",stderr); printGridNd(stderr,grd);
                printArrayFmtAllWHdr(stderr,&X_srtd,  "%g","NormSmoothKernelPdf1dWgt: X_srtd - ");
                printArrayFmtAllWHdr(stderr,&W_srtd,  "%g","NormSmoothKernelPdf1dWgt: W_srtd - ");
                printArrayFmtAllWHdr(stderr,&Xlocal,  "%g","NormSmoothKernelPdf1dWgt: Xlocal - ");
                printGridNd(stderr,grd);
                if (cbeg > 0){
                    exit(0);
                }
            }
            */
			ZeroOutLoop1d(&jpdf,cbeg_in,cend_in);
		}
        ++l_min;
        ++l_max;
    }
    freeArShell(&Xlocal);

/*  fprintf(stderr,"NormSmoothKernelPdf1dWgt: 3 nmiss = %lld\n",nmiss);  */
	double nnonmiss = (double)(nx-nmiss);
    double nnonmiss_pct = nnonmiss/nx;
    if ((nnonmiss < 1) || (sumAllAr(&jpdf_sum) <= 0)){
        freeAr(&jpdf_sum);
        fprintf(stderr,"NormSmoothKernelPdf1dWgt: Not enough non-missing values (%d, %lf), setting jpdf to missing\n",(int)nnonmiss, nnonmiss_pct);
        printArrayFmtAllWHdr(stderr,wgt   ,"%g","NormSmoothKernelPdf1dWgt: kwidth=%g, wgt - ",kwidth);
        printArrayFmtAllWHdr(stderr,array ,"%g","NormSmoothKernelPdf1dWgt: array - ");
        fputs("NormSmoothKernelPdf1dWgt: grd - ",stderr); printGridNd(stderr,grd);
        printArrayFmtAllWHdr(stderr,&X_srtd,"%g","NormSmoothKernelPdf1dWgt: X_srtd - ");
    } else {
        fct1ar1sRef(Div,&jpdf_sum,&jpdf_sum,nnonmiss);
        /*
        if (isAnyNanInf(&jpdf_sum)){
            printArrayFmtAllWHdr(stderr,&jpdf_sum,"%g","NormSmoothKernelPdf1dWgt: err 1: nnonmiss=%lld jpdf_sum - ",nnonmiss);
            printArrayFmtAllWHdr(stderr,&X_srtd,  "%g","NormSmoothKernelPdf1dWgt: X_srtd - ");
            printArrayFmtAllWHdr(stderr,&W_srtd,  "%g","NormSmoothKernelPdf1dWgt: W_srtd - ");
            printGridNd(stderr,grd);
            exit(0);
        }
        */
    
        double jcdf1 = sumAllAr(&jpdf_sum);
    /*  fprintf(stderr,"NormSmoothKernelPdf1dWgt: jcdf1 = %g\n",jcdf1);  */
        
        fct1ar1sRef(Div,&jpdf_sum,&jpdf_sum,dcrd*jcdf1);
        /*
        if (isAnyNanInf(jpdf_sum)){
            printArrayFmtAllWHdr(stderr,&jpdf_sum,"%g","NormSmoothKernelPdf1dWgt: err 2: nnonmiss=%lld, dcrd=%g, jcdf1=%g jpdf_sum - ",nnonmiss,dcrd,jcdf1);
            printArrayFmtAllWHdr(stderr,&X_srtd,  "%g","NormSmoothKernelPdf1dWgt: X_srtd - ");
            printArrayFmtAllWHdr(stderr,&W_srtd,  "%g","NormSmoothKernelPdf1dWgt: W_srtd - ");
            printGridNd(stderr,grd);
            exit(0);
        }
        */
    
    
    /*  jcdf1 = sumAllAr(&jpdf_sum);
        fprintf(stderr,"NormSmoothKernelPdf1dWgt: nmiss = %lld, jcdf1 = %g,jcdf1*dcrd=%g\n",nmiss,jcdf1,jcdf1*dcrd);   */
    }
    
	freeAr(&X_srtd);
	freeAr(&W_srtd);
	freeAr(&jpdf);
	return jpdf_sum;
}

#endif

