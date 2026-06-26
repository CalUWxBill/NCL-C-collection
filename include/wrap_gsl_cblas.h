#ifndef  _WRAP_GSL_CBLAS_H_
#define  _WRAP_GSL_CBLAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <gsl/gsl_cblas.h>

/* blas/gsl_cblas.h
 */

/* This is a copy of the CBLAS standard header.
 * We carry this around so we do not have to
 * break our model for flexible BLAS functionality.
 */

/*
 * ===========================================================================
 * Prototypes for level 1 BLAS functions (complex are recast as routines)
 * ===========================================================================
 */
double wrap_dbl_cblas_2vec(double (*fct)(int, double *, int, double *, int),input_args *args,typ_idx nneeded){
    int i;
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(double *)args->missval;
    } else {
        rv = fct(A[0].tlen, pntr_of(&A[0]), 1, pntr_of(&A[1]), 1);
        if (!isfinite(rv)){ rv = *(double *)args->missval; }
    }
    for (i=0;i<args->narrs;++i){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_cblas_ddot(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_cblas_2vec(cblas_ddot,args,1);
}

/*
 * Functions having prefixes Z and C only
 */
/*
void   cblas_zdotu_sub(const int N, const void *X, const int incX,
                       const void *Y, const int incY, void *dotu);
void   cblas_zdotc_sub(const int N, const void *X, const int incX,
                       const void *Y, const int incY, void *dotc);
*/

/*
 * Functions having prefixes S D SC DZ
 */
double wrap_dbl_cblas_1vec(double (*fct)(int, double *, int),input_args *args,typ_idx nneeded){
    int i;
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(double *)args->missval;
    } else {
        rv = fct(A[0].tlen, pntr_of(&A[0]), 1);
        if (!isfinite(rv)){ rv = *(double *)args->missval; }
    }
    for (i=0;i<args->narrs;++i){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_cblas_dnrm2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_cblas_1vec(cblas_dnrm2,args,1);
}

double wrap_cblas_dasum(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_cblas_1vec(cblas_dasum,args,1);
}


/*
double cblas_dznrm2(const int N, const void *X, const int incX);
double cblas_dzasum(const int N, const void *X, const int incX);
*/

/*
 * Functions having standard 4 prefixes (S D C Z)
 */
typ_idx wrap_cblas_idamax(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    typ_idx rv = *(typ_idx *)args->missval;
    typ_idx nnonmiss = 0;
    arr missidx = getMissingIdxsNArraysList(args->narrs, args->arrays, &nnonmiss);
    typ_idx N = missidx.tlen;

    if (nnonmiss){
        if (nnonmiss == N){
            rv     = (typ_idx)cblas_idamax(N, pntr_of(args->arrays[0]), 1);
        } else {
            typ_idx i;
            arr *A = removeMissingNArraysFromMissArList_alloc(nnonmiss,&missidx,args->narrs,args->arrays);
            rv     = (typ_idx)cblas_idamax(nnonmiss, pntr_of(&A[0]), 1);
            for(i=0;i<rv;++i){
                if (!iIDX(&missidx,i)){
                    rv++;
                }
            }
            for (i=0;i<args->narrs;i++){
                freeAr(&A[i]);
            }
            free(A);
        }
    }

    freeAr(&missidx);
    return rv;
}

/*
CBLAS_INDEX cblas_izamax(const int N, const void   *X, const int incX);
*/

/*
 * ===========================================================================
 * Prototypes for level 1 BLAS routines
 * ===========================================================================
 */

/* 
 * Routines with standard 4 prefixes (s, d, c, z)
 */
/*
void cblas_dswap(const int N, double *X, const int incX, 
                 double *Y, const int incY);
void cblas_dcopy(const int N, const double *X, const int incX, 
                 double *Y, const int incY);
*/
arr wrap_cblas_daxpy(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr **A = args->arrays;
    arr  *X = A[0];
    arr   Y = copyAr(A[1]);
    typ_idx  N = X->tlen;
    typ_idx nnonmiss = 0;
    arr missidx = getMissingIdxsNArraysList(args->narrs, A, &nnonmiss);
    double alpha = args->dblp[0];

    if (nnonmiss){
        if (nnonmiss == N){
            cblas_daxpy(N, alpha, pntr_of(X), 1, pntr_of(&Y), 1);
        } else {
            typ_idx i=0,k=0,ibeg,iend,nprt;
            for (;;){
            /*  fprintf(stderr,"wrap_cblas_daxpy: k=%d\n",k); */
                for(;(i<N) && (iIDX(&missidx,i)==0);++i); ibeg = i;
                if (ibeg >=N) { break; }
                for(;(i<N) && (iIDX(&missidx,i)==1);++i); iend = i;
                nprt = iend-ibeg;
            /*  fprintf(stderr,"wrap_cblas_daxpy: ibeg=%d iend=%d nprt=%d\n",ibeg,iend,nprt); */
                cblas_daxpy(nprt, alpha, address_of_i(X,ibeg), 1, address_of_i(&Y,ibeg), 1);
                ++k;
                if (i >=N) { break; }
            }
        }
    } else {
        fillArWithMiss(&Y);
    }

    freeAr(&missidx);
    return Y;
}


/*
void cblas_zswap(const int N, void *X, const int incX, 
                 void *Y, const int incY);
void cblas_zcopy(const int N, const void *X, const int incX, 
                 void *Y, const int incY);
void cblas_zaxpy(const int N, const void *alpha, const void *X,
                 const int incX, void *Y, const int incY);
*/

/* 
 * Routines with S and D prefix only
 */
/*
void cblas_drotg(double *a, double *b, double *c, double *s);
void cblas_drotmg(double *d1, double *d2, double *b1, const double b2, double *P);
void cblas_drot(const int N, double *X, const int incX,
                double *Y, const int incY, const double c, const double  s);
void cblas_drotm(const int N, double *X, const int incX,
                double *Y, const int incY, const double *P);
*/

/* 
 * Routines with S D C Z CS and ZD prefixes
 */
/*
void cblas_dscal(const int N, const double alpha, double *X, const int incX);
*/
/*
void cblas_zscal(const int N, const void *alpha, void *X, const int incX);
void cblas_zdscal(const int N, const double alpha, void *X, const int incX);
*/

/*
 * ===========================================================================
 * Prototypes for level 2 BLAS
 * ===========================================================================
 */

/* 
 * Routines with standard 4 prefixes (S, D, C, Z)
 */
arr wrap_cblas_dgemv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 2,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    double alpha   = args->dblp[0];
    double beta    = args->dblp[1];
    int    istrans = args->intp[0];
    arr **Ars = args->arrays;
    arr    *A = Ars[0];
    arr    *x = Ars[1];
    arr     y = copyAr(Ars[2]); /* Copy because y is also output vector */
    
    enum CBLAS_TRANSPOSE TransA;
    typ_idx  M = A->len[0];
    typ_idx  N = A->len[1];
    
    if (istrans){
        TransA = CblasTrans;
        if (x->tlen != M){ fprintf(stderr,"wrap_cblas_dgemv: x should have M=%lld elements, it has %lld\n",M,x->tlen); exit(0); }
        if (y.tlen != N){  fprintf(stderr,"wrap_cblas_dgemv: y should have N=%lld elements, it has %lld\n",N,y.tlen);  exit(0); }
    } else {
        TransA = CblasNoTrans;
        if (x->tlen != N){ fprintf(stderr,"wrap_cblas_dgemv: x should have N=%lld elements, it has %lld\n",N,x->tlen); exit(0); }
        if (y.tlen != M){  fprintf(stderr,"wrap_cblas_dgemv: y should have M=%lld elements, it has %lld\n",M,y.tlen);  exit(0); }
    }
    
    typ_idx miss_A = countMiss(A);
    typ_idx miss_x = countMiss(x);
    typ_idx miss_y = countMiss(&y);
    if (miss_A || miss_x || miss_y){
        fillArWithMiss(&y);
    } else {
        cblas_dgemv(CblasRowMajor, TransA, M, N, alpha, pntr_of(A), A->len[1], pntr_of(x), 1, beta, pntr_of(&y), 1);
    }

    return y;
}

arr wrap_cblas_dgemv_simple(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int    istrans = args->intp[0];
    arr **Ars = args->arrays;
    arr    *A = Ars[0];
    arr    *x = Ars[1];
    
    enum CBLAS_TRANSPOSE TransA;
    typ_idx  M = A->len[0];
    typ_idx  N = A->len[1];
    
    arr y;
    if (istrans){
        TransA = CblasTrans;
        if (x->tlen != M){ fprintf(stderr,"wrap_cblas_dgemv: x should have M=%lld elements, it has %lld\n",M,x->tlen); exit(0); }
        y = Array(1,DOUBLE,N);
    } else {
        TransA = CblasNoTrans;
        if (x->tlen != N){ fprintf(stderr,"wrap_cblas_dgemv: x should have N=%lld elements, it has %lld\n",N,x->tlen); exit(0); }
        y = Array(1,DOUBLE,M);
    }
    copyMiss(&y,A);
    
    typ_idx miss_A = countMiss(A);
    typ_idx miss_x = countMiss(x);
    if (miss_A || miss_x){
        fillArWithMiss(&y);
    } else {
        cblas_dgemv(CblasRowMajor, TransA, M, N, 1.0, pntr_of(A), A->len[1], pntr_of(x), 1, 0.0, pntr_of(&y), 1);
    }

    return y;
}

/*
void cblas_dgbmv(const enum CBLAS_ORDER order,
                 const enum CBLAS_TRANSPOSE TransA, const int M, const int N,
                 const int KL, const int KU, const double alpha,
                 const double *A, const int lda, const double *X,
                 const int incX, const double beta, double *Y, const int incY);
void cblas_dtrmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const double *A, const int lda, 
                 double *X, const int incX);
void cblas_dtbmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const int K, const double *A, const int lda, 
                 double *X, const int incX);
void cblas_dtpmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const double *Ap, double *X, const int incX);
void cblas_dtrsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const double *A, const int lda, double *X,
                 const int incX);
void cblas_dtbsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const int K, const double *A, const int lda,
                 double *X, const int incX);
void cblas_dtpsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const double *Ap, double *X, const int incX);
*/
                 
/*
void cblas_zgemv(const enum CBLAS_ORDER order,
                 const enum CBLAS_TRANSPOSE TransA, const int M, const int N,
                 const void *alpha, const void *A, const int lda,
                 const void *X, const int incX, const void *beta,
                 void *Y, const int incY);
void cblas_zgbmv(const enum CBLAS_ORDER order,
                 const enum CBLAS_TRANSPOSE TransA, const int M, const int N,
                 const int KL, const int KU, const void *alpha,
                 const void *A, const int lda, const void *X,
                 const int incX, const void *beta, void *Y, const int incY);
void cblas_ztrmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const void *A, const int lda, 
                 void *X, const int incX);
void cblas_ztbmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const int K, const void *A, const int lda, 
                 void *X, const int incX);
void cblas_ztpmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const void *Ap, void *X, const int incX);
void cblas_ztrsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const void *A, const int lda, void *X,
                 const int incX);
void cblas_ztbsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const int K, const void *A, const int lda,
                 void *X, const int incX);
void cblas_ztpsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const void *Ap, void *X, const int incX);
*/

/* 
 * Routines with S and D prefixes only
 */
/*
void cblas_dsymv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const int N, const double alpha, const double *A,
                 const int lda, const double *X, const int incX,
                 const double beta, double *Y, const int incY);
void cblas_dsbmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const int N, const int K, const double alpha, const double *A,
                 const int lda, const double *X, const int incX,
                 const double beta, double *Y, const int incY);
void cblas_dspmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const int N, const double alpha, const double *Ap,
                 const double *X, const int incX,
                 const double beta, double *Y, const int incY);
*/

arr wrap_cblas_dger(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    double alpha   = args->dblp[0];
    arr **Ars = args->arrays;
    arr    *x = Ars[0];
    arr    *y = Ars[1];
    arr     A = copyAr(Ars[2]); /* Copy because A is also output matrix */

    typ_idx  M = A.len[0];
    typ_idx  N = A.len[1];

    if (y->tlen != N){ fprintf(stderr,"wrap_cblas_dger: y should have N=%lld elements, it has %lld\n",N,y->tlen); exit(0); }
    if (x->tlen != M){ fprintf(stderr,"wrap_cblas_dger: x should have M=%lld elements, it has %lld\n",M,x->tlen); exit(0); }

    typ_idx miss_x = countMiss(x);
    typ_idx miss_y = countMiss(y);
    typ_idx miss_A = countMiss(&A);
    if (miss_A || miss_x || miss_y){
        printArrayFmtAllWHdr(stdout,  x, "%4g", "%lld missing, x - ", miss_x);
        printArrayFmtAllWHdr(stdout,  y, "%4g", "%lld missing, y - ", miss_y);
        printArrayFmtAllWHdr(stdout, &A, "%4g", "%lld missing, A - ", miss_A);
        fillArWithMiss(&A);
    } else {
        cblas_dger(CblasRowMajor, M, N, alpha, pntr_of(x), 1, pntr_of(y), 1, pntr_of(&A), A.len[1]);
    }

    return A;
}


arr wrap_cblas_dger_simple(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr **Ars = args->arrays;
    arr    *x = Ars[0];
    arr    *y = Ars[1];

    typ_idx M = x->tlen;
    typ_idx N = y->tlen;

    arr  A = Array(2,DOUBLE,M,N);
    copyMiss(&A,x);
    
    typ_idx miss_x = countMiss(x);
    typ_idx miss_y = countMiss(y);
    if (miss_x || miss_y){
        fillArWithMiss(&A);
    } else {
        cblas_dger(CblasRowMajor, M, N, 1.0, pntr_of(x), 1, pntr_of(y), 1, pntr_of(&A), A.len[1]);
    }

    return A;
}

/*
void cblas_dsyr(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                const int N, const double alpha, const double *X,
                const int incX, double *A, const int lda);
void cblas_dspr(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                const int N, const double alpha, const double *X,
                const int incX, double *Ap);
void cblas_dsyr2(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                const int N, const double alpha, const double *X,
                const int incX, const double *Y, const int incY, double *A,
                const int lda);
void cblas_dspr2(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                const int N, const double alpha, const double *X,
                const int incX, const double *Y, const int incY, double *A);
*/

/* 
 * Routines with C and Z prefixes only
 */
/*
void cblas_zhemv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const int N, const void *alpha, const void *A,
                 const int lda, const void *X, const int incX,
                 const void *beta, void *Y, const int incY);
void cblas_zhbmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const int N, const int K, const void *alpha, const void *A,
                 const int lda, const void *X, const int incX,
                 const void *beta, void *Y, const int incY);
void cblas_zhpmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const int N, const void *alpha, const void *Ap,
                 const void *X, const int incX,
                 const void *beta, void *Y, const int incY);
void cblas_zgeru(const enum CBLAS_ORDER order, const int M, const int N,
                 const void *alpha, const void *X, const int incX,
                 const void *Y, const int incY, void *A, const int lda);
void cblas_zgerc(const enum CBLAS_ORDER order, const int M, const int N,
                 const void *alpha, const void *X, const int incX,
                 const void *Y, const int incY, void *A, const int lda);
void cblas_zher(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                const int N, const double alpha, const void *X, const int incX,
                void *A, const int lda);
void cblas_zhpr(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                const int N, const double alpha, const void *X,
                const int incX, void *A);
void cblas_zher2(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo, const int N,
                const void *alpha, const void *X, const int incX,
                const void *Y, const int incY, void *A, const int lda);
void cblas_zhpr2(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo, const int N,
                const void *alpha, const void *X, const int incX,
                const void *Y, const int incY, void *Ap);
*/

/*
 * ===========================================================================
 * Prototypes for level 3 BLAS
 * ===========================================================================
 */

/* 
 * Routines with standard 4 prefixes (S, D, C, Z)
 */
arr wrap_cblas_dgemm(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 2,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    double alpha    = args->dblp[0];
    double beta     = args->dblp[1];
    int    istransa = args->intp[0];
    int    istransb = args->intp[1];
    arr **Ars = args->arrays;
    arr    *A = Ars[0];
    arr    *B = Ars[1];
    arr     C = copyAr(Ars[2]); /* Copy because C is also output matrix */
    
    enum CBLAS_TRANSPOSE TransA;
    enum CBLAS_TRANSPOSE TransB;
    typ_idx  M,   K;
    typ_idx  K_B, N;
    
    if (istransa){
        TransA = CblasTrans;
        M = A->len[1];
        K = A->len[0];
    } else {
        TransA = CblasNoTrans;
        M = A->len[0];
        K = A->len[1];
    }
    
    if (istransb){
        TransB = CblasTrans;
        K_B = B->len[1];
        N   = B->len[0];
    } else {
        TransB = CblasNoTrans;
        K_B = B->len[0];
        N   = B->len[1];
    }
    
    if (K != K_B){
        fprintf(stderr,"number of columns of op(A) must be equal to rows of op(B), K=%lld, K_B=%lld\n", K, K_B);
        exit(0);
    }
    
    if ((M != C.len[0]) || (N != C.len[1])){
        fprintf(stderr,"C must have size that is number of rows of op(A) and columns of op(B), M=%lld, N=%lld, M_C=%lld, N_C=%lld\n",
            M, N, C.len[0], C.len[1]);
        exit(0);
    }
    
    typ_idx miss_A = countMiss(A);
    typ_idx miss_B = countMiss(B);
    typ_idx miss_C = countMiss(&C);
    if (miss_A || miss_B || miss_C){
        fillArWithMiss(&C);
    } else {
        cblas_dgemm(CblasRowMajor, TransA, TransB, M, N, K, alpha, pntr_of(A), A->len[1], pntr_of(B), B->len[1], beta, pntr_of(&C), C.len[1]);
    }

    return C;
}

arr wrap_cblas_dgemm_simple(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 2,/*ndbls*/ 0,/*nints*/ 2,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int    istransa = args->intp[0];
    int    istransb = args->intp[1];
    arr **Ars = args->arrays;
    arr    *A = Ars[0];
    arr    *B = Ars[1];

    enum CBLAS_TRANSPOSE TransA;
    enum CBLAS_TRANSPOSE TransB;
    typ_idx  M,   K;
    typ_idx  K_B, N;
    
    if (istransa){
        TransA = CblasTrans;
        M = A->len[1];
        K = A->len[0];
    } else {
        TransA = CblasNoTrans;
        M = A->len[0];
        K = A->len[1];
    }
    
    if (istransb){
        TransB = CblasTrans;
        K_B = B->len[1];
        N   = B->len[0];
    } else {
        TransB = CblasNoTrans;
        K_B = B->len[0];
        N   = B->len[1];
    }
    
    if (K != K_B){
        fprintf(stderr,"number of columns of op(A) must be equal to rows of op(B), K=%lld, K_B=%lld\n", K, K_B);
        exit(0);
    }
    
    arr  C = Array(2,DOUBLE,M,N);
    copyMiss(&C,A);
    
    typ_idx miss_A = countMiss(A);
    typ_idx miss_B = countMiss(B);
    if (miss_A || miss_B){
        fillArWithMiss(&C);
    } else {
        cblas_dgemm(CblasRowMajor, TransA, TransB, M, N, K, 1.0, pntr_of(A), A->len[1], pntr_of(B), B->len[1], 0.0, pntr_of(&C), C.len[1]);
    }

    return C;
}

/*
void cblas_dsymm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const int M, const int N,
                 const double alpha, const double *A, const int lda,
                 const double *B, const int ldb, const double beta,
                 double *C, const int ldc);
void cblas_dsyrk(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                 const double alpha, const double *A, const int lda,
                 const double beta, double *C, const int ldc);
void cblas_dsyr2k(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                  const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                  const double alpha, const double *A, const int lda,
                  const double *B, const int ldb, const double beta,
                  double *C, const int ldc);
void cblas_dtrmm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const int M, const int N,
                 const double alpha, const double *A, const int lda,
                 double *B, const int ldb);
void cblas_dtrsm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const int M, const int N,
                 const double alpha, const double *A, const int lda,
                 double *B, const int ldb);
*/

/*
void cblas_zgemm(const enum CBLAS_ORDER Order, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_TRANSPOSE TransB, const int M, const int N,
                 const int K, const void *alpha, const void *A,
                 const int lda, const void *B, const int ldb,
                 const void *beta, void *C, const int ldc);
void cblas_zsymm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const int M, const int N,
                 const void *alpha, const void *A, const int lda,
                 const void *B, const int ldb, const void *beta,
                 void *C, const int ldc);
void cblas_zsyrk(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                 const void *alpha, const void *A, const int lda,
                 const void *beta, void *C, const int ldc);
void cblas_zsyr2k(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                  const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                  const void *alpha, const void *A, const int lda,
                  const void *B, const int ldb, const void *beta,
                  void *C, const int ldc);
void cblas_ztrmm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const int M, const int N,
                 const void *alpha, const void *A, const int lda,
                 void *B, const int ldb);
void cblas_ztrsm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const int M, const int N,
                 const void *alpha, const void *A, const int lda,
                 void *B, const int ldb);
*/

/* 
 * Routines with prefixes C and Z only
 */
/*
void cblas_zhemm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const int M, const int N,
                 const void *alpha, const void *A, const int lda,
                 const void *B, const int ldb, const void *beta,
                 void *C, const int ldc);
void cblas_zherk(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                 const double alpha, const void *A, const int lda,
                 const double beta, void *C, const int ldc);
void cblas_zher2k(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                  const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                  const void *alpha, const void *A, const int lda,
                  const void *B, const int ldb, const double beta,
                  void *C, const int ldc);
*/

#endif
