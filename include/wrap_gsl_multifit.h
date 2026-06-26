#ifndef  _WRAP_GSL_MULTIFIT_H_
#define  _WRAP_GSL_MULTIFIT_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_statistics.h>
#include <gsl/gsl_multifit.h>

int areAllEqual(double a,double *b,typ_idx nb){
	typ_idx i;
	for(i=0;i<nb;++i){
		if( a != *b++ ){ return 0; }
	}
	return 1;
}

int areAnyEqual(double a,double *b,typ_idx nb){
	typ_idx i;
	for(i=0;i<nb;++i){
		if( a == *b++ ){ return 1; }
	}
	return 0;
}

int areNoneEqual(double a,double *b,typ_idx nb){
	typ_idx i;
	for(i=0;i<nb;++i){
		if( a == *b++ ){ return 0; }
	}
	return 1;
}

/* For regressions with a constant you must add a vector of 1s to X */
arr multifit_linear_fit(arr *restrict Xin, arr *restrict Y, arr *Pcov,double *chisq,double *TSS,double *MSE,double *r2){
/*    fputs("multifit_linear_fit: 1",stderr); */
    typ_idx n = Xin->len[0]; /* Sample size            */
    typ_idx p = Xin->len[1]; /* Number of predictors   */

/*    fputs(" 2",stderr); */
    gsl_matrix *X = gsl_matrix_alloc (n, p);
    gsl_vector_view y = gsl_vector_view_array(pntr_of(Y), n);

/*    fputs(" 3",stderr); */
    typ_idx i,j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < p; ++j){
            gsl_matrix_set (X, i, j, DBL(Xin,i,j));
            
        }
    }

/*    fputs(" 4",stderr); */
    arr P = Array(1,DOUBLE,p);
    *Pcov = Array(2,DOUBLE,p,p);
/*    fputs(" 5",stderr); */
    gsl_vector_view    c = gsl_vector_view_array(pntr_of(&P), p);
    gsl_matrix_view  cov = gsl_matrix_view_array(pntr_of(Pcov), p, p);
    {
/*    fputs(" 6",stderr); */
        gsl_multifit_linear_workspace * work = gsl_multifit_linear_alloc (n, p);
        gsl_multifit_linear (X, &y.vector, &c.vector, &cov.matrix, chisq, work);
        gsl_multifit_linear_free (work);

/*    fputs(" 7",stderr); */
        *TSS = gsl_stats_tss(pntr_of(Y), 1, n);
        *MSE = *chisq/(n - p); /* MSE for C.I. and P.I. */
        *r2  = 1.0 - *chisq/(*TSS);
    }

/*    fputs(" 8",stderr); */
    gsl_matrix_free (X);
/*    fputs(" 9\n",stderr); */
    return P;
}

arr wrap_gsl_multifit_linear_fit(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 1,/*nrdbls*/ 4,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }

    int i;
    arr rv;

/*    fputs("wrap_gsl_multifit_linear_fit: 1",stderr); */
    arr *X = args->arrays[0]; /* Should have one more dim than Y */
    arr *Y = args->arrays[1];
    if ((X->n - Y->n) != 1){
        fprintf(stderr,"wrap_gsl_multifit_linear_fit: X must have one more dimension than Y\n");
        printArrayInfoWHdr(stderr,X,"%g","X - ");
        printArrayInfoWHdr(stderr,Y,"%g","Y - ");
        exit(EXIT_FAILURE);
    }
/*    fputs(" 2",stderr); */
    typ_idx n = Y->tlen;
    typ_idx p = X->tlen / n;
    double xmiss  = *(double *)getMiss(X);
    double ymiss  = *(double *)getMiss(Y);
    double *pX    = pntr_of(X);
    double *pX2;
    double *pY    = pntr_of(Y);
    double *poutX = malloc(X->tlen*sizeof *poutX);
    double *poutY = malloc(n      *sizeof *poutY);
    double *pXo   = poutX;
    double *pYo   = poutY;
/*    fputs(" 3",stderr); */
    typ_idx nvalid = 0;
    for(typ_idx j=0; j < n; ++j, pY++, pX += p){
        if (*pY != ymiss){
            if (areNoneEqual(xmiss,pX,p)){
                pX2 = pX;
                *pYo++ = *pY;
                for(typ_idx k=0; k < p; ++k){
                    *pXo++ = *pX2++;
                }
                ++nvalid;
            }
        }
    }
/*    fputs(" 4",stderr); */
    if (nvalid < 2){
        /*
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        */
        rv = *(arr *)args->missval;
        free(poutX);
        free(poutY);
    } else {
/*    fputs(" 5",stderr); */
        arr Xcut = assign1dtoNd(poutX, 2, DOUBLE, nvalid, p);
        arr Ycut = assign1dtoNd(poutY, 1, DOUBLE, nvalid);
/*    fputs(" 6",stderr); */
/*
        if (nvalid < n){
            printArrayFmtAllWHdr(stderr,X,"%g","X - ");
            printArrayFmtAllWHdr(stderr,&Xcut,"%g","Xcut - ");
            printArrayFmtAllWHdr(stderr,Y,"%g","Y - ");
            printArrayFmtAllWHdr(stderr,&Ycut,"%g","Ycut - ");
        }
 */
/*    fputs(" 7",stderr); */
        arr    *Pcov  = args->arrpp[0];
        double *chisq = args->dblpp[0];
        double *TSS   = args->dblpp[1];
        double *MSE   = args->dblpp[2];
        double *r2    = args->dblpp[3];

/*    fputs(" 8",stderr); */
        rv = multifit_linear_fit(&Xcut,&Ycut,Pcov,chisq,TSS,MSE,r2);
/*    fputs(" 9",stderr); */
        freeAr(&Xcut);
        freeAr(&Ycut);
    }
/*    fputs(" 10\n",stderr); */
    return rv;
}


/* For regressions with a constant you must add a vector of 1s to X */
arr multifit_wlinear_fit(arr *restrict Xin, arr *restrict Y, arr *restrict W, arr *Pcov,double *chisq,double *TSS,double *MSE,double *r2){
    typ_idx n = Xin->len[0]; /* Sample size            */
    typ_idx p = Xin->len[1]; /* Number of predictors   */

    gsl_matrix *X = gsl_matrix_alloc (n, p);
    gsl_vector_view w = gsl_vector_view_array(pntr_of(W), n);
    gsl_vector_view y = gsl_vector_view_array(pntr_of(Y), n);
    
    double wsum = 0;

    typ_idx i,j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < p; ++j){
            gsl_matrix_set (X, i, j, DBL(Xin,i,j));
            
        }
        wsum += gsl_vector_get(&w.vector,i);
    }

    arr P = Array(1,DOUBLE,p);
    *Pcov = Array(2,DOUBLE,p,p);
    gsl_vector_view    c = gsl_vector_view_array(pntr_of(&P), p);
    gsl_matrix_view  cov = gsl_matrix_view_array(pntr_of(Pcov), p, p);
    {
        gsl_multifit_linear_workspace * work = gsl_multifit_linear_alloc (n, p);
        gsl_multifit_wlinear (X, &w.vector, &y.vector, &c.vector, &cov.matrix, chisq, work);
        gsl_multifit_linear_free (work);

        *TSS = gsl_stats_wtss(pntr_of(W), 1, pntr_of(Y), 1, n);
        *MSE = *chisq/wsum*n/(n - p);
        *r2  = 1.0 - *chisq/(*TSS);
    }

    gsl_matrix_free (X);
    return P;
}

arr wrap_gsl_multifit_wlinear_fit(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 1,/*nrdbls*/ 4,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }

    int i;
    arr rv;
    arr *X = args->arrays[0];
    arr *Y = args->arrays[1];
    arr *W = args->arrays[2];
    if ((X->n - Y->n) != 1){
        fprintf(stderr,"wrap_gsl_multifit_wlinear_fit: X must have one more dimension than Y\n");
        printArrayInfoWHdr(stderr,X,"%g","X - ");
        printArrayInfoWHdr(stderr,Y,"%g","Y - ");
        exit(EXIT_FAILURE);
    }
    typ_idx n = Y->tlen;
    typ_idx p = X->tlen / n;
    double xmiss  = *(double *)getMiss(X);
    double ymiss  = *(double *)getMiss(Y);
    double wmiss  = *(double *)getMiss(W);
    double *pX    = pntr_of(X);
    double *pX2;
    double *pY    = pntr_of(Y);
    double *pW    = pntr_of(W);
    double *poutX = malloc(X->tlen*sizeof *poutX);
    double *poutY = malloc(n      *sizeof *poutY);
    double *poutW = malloc(n      *sizeof *poutW);
    double *pXo   = poutX;
    double *pYo   = poutY;
    double *pWo   = poutW;
    typ_idx nvalid = 0;
    for(typ_idx j=0; j < n; ++j, pY++, pW++, pX += p){
        if ((*pY != ymiss) && (*pW != wmiss)){
            if (areNoneEqual(xmiss,pX,p)){
                pX2 = pX;
                *pYo++ = *pY;
                *pWo++ = *pW;
                for(typ_idx k=0; k < p; ++k){
                    *pXo++ = *pX2++;
                }
                ++nvalid;
            }
        }
    }
    if (nvalid < 2){
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        rv = *(arr *)args->missval;
        free(poutX);
        free(poutY);
        free(poutW);
    } else {
        arr Xcut = assign1dtoNd(poutX, 2, DOUBLE, nvalid, p);
        arr Ycut = assign1dtoNd(poutY, 1, DOUBLE, nvalid);
        arr Wcut = assign1dtoNd(poutW, 1, DOUBLE, nvalid);
        arr    *Pcov  = args->arrpp[0];
        double *chisq = args->dblpp[0];
        double *TSS   = args->dblpp[1];
        double *MSE   = args->dblpp[2];
        double *r2    = args->dblpp[3];

        rv = multifit_wlinear_fit(&Xcut,&Ycut,&Wcut,Pcov,chisq,TSS,MSE,r2);
        freeAr(&Xcut);
        freeAr(&Ycut);
        freeAr(&Wcut);
    }
    return rv;
}

double multifit_linear_predict(arr *restrict Xin, arr *restrict P, arr *restrict Pcov,double *yerr){
    typ_idx p = Xin->tlen;   /* Number of predictors   */

    gsl_vector *X = gsl_vector_alloc (p);

    typ_idx j;
    for (j = 0; j < p; ++j){
        gsl_vector_set (X, j, iDBL(Xin,j));
        
    }

    gsl_vector_view   c = gsl_vector_view_array(pntr_of(P), p);
    gsl_matrix_view cov = gsl_matrix_view_array(pntr_of(Pcov), p, p);

    double y;
    gsl_multifit_linear_est(X, &c.vector, &cov.matrix, &y, yerr);

    gsl_vector_free (X);
    return y;
}

double wrap_gsl_multifit_linear_predict(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 1,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }

    int i;
    double rv;
    arr *X    = args->arrays[0];
    arr *P    = args->arrays[1];
    arr *Pcov = args->arrays[2];
    if (isAnyMiss(X)){ /* We can't handle any missing predictors unless we calculate separate regressions for each possibility */
        rv = *(double *)args->missval;
    } else {
        double *yerr = args->dblpp[0];

        rv = multifit_linear_predict(X,P,Pcov,yerr);
        if (!isfinite(rv)){ rv = *(double *)args->missval; }
    }
    return rv;
}

/* _add1 appends the constant 1 as a predictor for X, the other ones you have to add it before using. */
arr multifit_wlinear_fit_add1(arr *restrict Xin, arr *restrict Y, arr *restrict W, arr *Pcov,double *chisq,double *TSS,double *MSE,double *r2){
    typ_idx n  = Xin->len[0]; /* Sample size            */
    typ_idx np = Xin->len[1]; /* Number of predictors   */
    typ_idx p  = np + 1;      /* Number of coefficients */

    gsl_matrix *X = gsl_matrix_alloc (n, p);
    gsl_vector_view w = gsl_vector_view_array(pntr_of(W), n);
    gsl_vector_view y = gsl_vector_view_array(pntr_of(Y), n);
    
    double wsum = 0;

    typ_idx i,j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < np; ++j){
            gsl_matrix_set (X, i, j, DBL(Xin,i,j));
            
        }
        gsl_matrix_set (X, i, j, 1.0); /* Constant parameter appended to end of array */
        wsum += gsl_vector_get(&w.vector,i);
    }

    arr P = Array(1,DOUBLE,p);
    *Pcov = Array(2,DOUBLE,p,p);
    gsl_vector_view    c = gsl_vector_view_array(pntr_of(&P), p);
    gsl_matrix_view  cov = gsl_matrix_view_array(pntr_of(Pcov), p, p);
    {
        gsl_multifit_linear_workspace * work = gsl_multifit_linear_alloc (n, p);
        gsl_multifit_wlinear (X, &w.vector, &y.vector, &c.vector, &cov.matrix, chisq, work);
        gsl_multifit_linear_free (work);

        *TSS = gsl_stats_wtss(pntr_of(W), 1, pntr_of(Y), 1, n);
        *MSE = *chisq/wsum*n/(n - p);
        *r2  = 1.0 - *chisq/(*TSS);
    }

    gsl_matrix_free (X);
    return P;
}

arr wrap_gsl_multifit_wlinear_fit_add1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 1,/*nrdbls*/ 4,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }

    int i;
    arr rv;
    arr *X = args->arrays[0];
    arr *Y = args->arrays[1];
    arr *W = args->arrays[2];
    if ((X->n - Y->n) != 1){
        fprintf(stderr,"wrap_gsl_multifit_wlinear_fit: X must have one more dimension than Y\n");
        printArrayInfoWHdr(stderr,X,"%g","X - ");
        printArrayInfoWHdr(stderr,Y,"%g","Y - ");
        exit(EXIT_FAILURE);
    }
    typ_idx n = Y->tlen;
    typ_idx p = X->tlen / n;
    double xmiss  = *(double *)getMiss(X);
    double ymiss  = *(double *)getMiss(Y);
    double wmiss  = *(double *)getMiss(W);
    double *pX    = pntr_of(X);
    double *pX2;
    double *pY    = pntr_of(Y);
    double *pW    = pntr_of(W);
    double *poutX = malloc(X->tlen*sizeof *poutX);
    double *poutY = malloc(n      *sizeof *poutY);
    double *poutW = malloc(n      *sizeof *poutW);
    double *pXo   = poutX;
    double *pYo   = poutY;
    double *pWo   = poutW;
    typ_idx nvalid = 0;
    for(typ_idx j=0; j < n; ++j, pY++, pW++, pX += p){
        if ((*pY != ymiss) && (*pW != wmiss)){
            if (areNoneEqual(xmiss,pX,p)){
                pX2 = pX;
                *pYo++ = *pY;
                *pWo++ = *pW;
                for(typ_idx k=0; k < p; ++k){
                    *pXo++ = *pX2++;
                }
                ++nvalid;
            }
        }
    }
    if (nvalid < 2){
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        rv = *(arr *)args->missval;
        free(poutX);
        free(poutY);
        free(poutW);
    } else {
        arr Xcut = assign1dtoNd(poutX, 2, DOUBLE, nvalid, p);
        arr Ycut = assign1dtoNd(poutY, 1, DOUBLE, nvalid);
        arr Wcut = assign1dtoNd(poutW, 1, DOUBLE, nvalid);
        arr    *Pcov  = args->arrpp[0];
        double *chisq = args->dblpp[0];
        double *TSS   = args->dblpp[1];
        double *MSE   = args->dblpp[2];
        double *r2    = args->dblpp[3];

        rv = multifit_wlinear_fit_add1(&Xcut,&Ycut,&Wcut,Pcov,chisq,TSS,MSE,r2);
        freeAr(&Xcut);
        freeAr(&Ycut);
        freeAr(&Wcut);
    }
    return rv;
}

double multifit_linear_predict_add1(arr *restrict Xin, arr *restrict P, arr *restrict Pcov,double *yerr){
    typ_idx np = Xin->tlen;   /* Number of predictors   */
    typ_idx p  = np + 1;      /* Number of coefficients */

    gsl_vector *X = gsl_vector_alloc (p);

    typ_idx j;
    for (j = 0; j < np; ++j){
        gsl_vector_set (X, j, iDBL(Xin,j));
        
    }
    gsl_vector_set (X, j, 1.0); /* Constant parameter appended to end of array */

    gsl_vector_view   c = gsl_vector_view_array(pntr_of(P), p);
    gsl_matrix_view cov = gsl_matrix_view_array(pntr_of(Pcov), p, p);

    double y;
    gsl_multifit_linear_est(X, &c.vector, &cov.matrix, &y, yerr);

    gsl_vector_free (X);
    return y;
}

double wrap_gsl_multifit_linear_predict_add1(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 1,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }

    int i;
    double rv;
    arr *X    = args->arrays[0];
    arr *P    = args->arrays[1];
    arr *Pcov = args->arrays[2];
    if (isAnyMiss(X)){
        rv = *(double *)args->missval;
    } else {
        double *yerr = args->dblpp[0];

        rv = multifit_linear_predict_add1(X,P,Pcov,yerr);
        if (!isfinite(rv)){ rv = *(double *)args->missval; }
    }
    return rv;
}


#endif
