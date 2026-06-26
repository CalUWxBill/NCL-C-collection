/* Created by Bill Scheftic */
/*
 *  This is the main header file for the bias correction and super-ensemble creation.
 *  - getTCMultiRegression selects the indices and generates the stage 2 regression parameters
 *  - applyTCMultiRegression applies the regression parameters to a forecast ensemble
 *  - superEnsemble_z_weighted is used to create the weighted super ensemble
 *  - getTertiaryExtremes_z generates tercile and extreme 10% probabilities from an ensemble
 */
#ifndef  _S2S_H_
#define  _S2S_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <math_supp.h>
#include <arrayinit2.h>
#include <stats2.h>
#include <arrayops2.h>
#include <arraymath2.h>
#include <arraystats2.h>
#include <dist_params.h>
#include <gsl/gsl_linalg.h>
#include <1d_pdf.h>
#include <pdf_stats.h>

/*------------------------*/
/* Function Declarations  */
/*------------------------*/
void sortedCDF(arr *,arr*,arr*);
void getPercZscoreFromCDF(arr *,arr *,gridnd *,arr*,arr*);
void getPercZscoreFromCDF_1(double,arr *,gridnd *,double*,double*);
void getTertiaryExtremes(arr *,arr *,gridnd *,double*,double*,double*,double*,double*);
void getTertiaryExtremes_z(arr *,double*,double*,double*,double*,double*);
void getPdfCdf(arr *,double,gridnd *,arr*,arr*);
arr Start2ValidTime(arr *);
arr getPersistenceNLeads(arr *,typ_idx);

/*-----------------------*/
/* Function Definitions  */
/*-----------------------*/

/*----------------------------------*/
/* Marginal Distribution Estimation */
/*----------------------------------*/

void sortedCDF(arr *restrict X,arr *X_srtd,arr *X_perc){
    typ_idx n = X->tlen;
    *X_srtd = qsortArray(X);

    double n_dbl = (double)n;
    double P_beg  = 1.0/(n_dbl+1.0);
    double P_end  = n_dbl/(n_dbl+1.0);

    *X_perc = getCoordArray(P_beg, P_end, n);
    return;
}

void sortedCDF0(arr *restrict X,arr *X_srtd,arr *X_perc,double *pct0){
    double miss_pct0 = *pct0;
    arr X_nz = NonZeros(X,pct0);
    typ_idx n_nz = X_nz.tlen;
    if (n_nz > 4){ /* I think X_nz has to be same size as X, fill with missing */
        *X_srtd = qsortArray(&X_nz);
        /*
        arr X_srtd_tmp = qsortArray(X_nz);
        
        *X_srtd = ArrayFromList(X->n,DOUBLE,X->len);
        copyMiss(X_srtd,X);
        fillArWithMiss(X_srtd);

        assignSect1d(X_srtd, 0, n_nz-1, &X_srtd_tmp, 0, n_nz-1);
        */

        double n_dbl = (double)n_nz;
        double P_beg  = 1.0/(n_dbl+1.0);
        double P_end  = n_dbl/(n_dbl+1.0);

        *X_perc = getCoordArray(P_beg, P_end, n_nz);
        /*
        arr X_perc_tmp = getCoordArray(P_beg, P_end, n_nz);
        
        *X_perc        = ArrayFromList(X->n,DOUBLE,X->len);
        copyMiss(X_perc,X);
        fillArWithMiss(X_perc);
        
        assignSect1d(X_perc, 0, n_nz-1, &X_perc_tmp, 0, n_nz-1);
        */
    } else {
        /* Should I do something here? Nothing leaves shape and scale as missing */
        *pct0   = miss_pct0;
        *X_srtd = NullArray();
        *X_perc = NullArray();
    }

    freeAr(&X_nz);

    return;
}



void getMultiRegression(arr *restrict fcstens_z,arr *restrict obs_z_in,arr *restrict TC_in,double rsq_thresh
    ,arr *ms,arr *bs,arr *rsqs,arr *idxs){
    /*
	clock_t tm_start_all,tm_end_all;
    tm_start_all = clock();
    */

    typ_idx i,k,l;
    /*
    printArrayFmtAllWHdr(stderr,fcstens_z,"%g","getMultiRegression: fcstens_z - ");
    printArrayFmtAllWHdr(stderr,obs_z_in, "%g","getMultiRegression: obs_z_in - ");
    printArrayFmtAllWHdr(stderr,TC_in,    "%g","getMultiRegression: TC_in - ");
    */
    
    arr fcst_z = arStatArg1ar(wrap_Mean,fcstens_z,1);
    if ((fcst_z.tlen < 1) || (fcst_z.n != 1) || (fcstens_z->n != 2) || (obs_z_in->n != 1) || (TC_in->n != 2)){
        printArrayFmtAllWHdr(stderr,fcstens_z,"%g","getMultiRegression: fcstens_z - ");
        printArrayFmtAllWHdr(stderr,TC_in,    "%g","getMultiRegression: TC_in     - ");
        printArrayFmtAllWHdr(stderr,&fcst_z,  "%g","getMultiRegression: fcst_z    - ");
        fputs("obs_z_in: \n",stderr);
        print_arr_exit(obs_z_in);
        printArrayFmtAllWHdr(stderr,obs_z_in, "%g","getMultiRegression: obs_z_in  - ");
    }
    
    typ_idx inlen = obs_z_in->tlen;
    typ_idx ntcs  = TC_in->len[0];
    
/*  int pcnt = 0; */
/*  fprintf(stderr,"getMultiRegression: %d",++pcnt);  */
    *ms   = Array(1,DOUBLE,ntcs);
    *bs   = Array(1,DOUBLE,ntcs);
    *rsqs = Array(1,DOUBLE,ntcs);
    *idxs = Array(1,TYPIDX,ntcs);
    fillArWithMiss(ms);
    fillArWithMiss(bs);
    fillArWithMiss(rsqs);
    fillArWithMiss(idxs);

    /* Remove missing values evenly across files. Not dealing with issue if an entire tc is missing for some reason for a given month. */
	typ_idx cnt = 0;
    int valid_fcst, valid_obs, valid_both;
	arr nvalid_TC  = Array(1,TYPIDX,ntcs);
	arr valid_TC   = Array(2,INT,ntcs,inlen);
/*  fprintf(stderr," %d",++pcnt);   */
	for(k=0;k<inlen;++k){
        valid_fcst = !isMiss(&fcst_z,k);
        valid_obs  = !isMiss(obs_z_in,k);
        valid_both = valid_fcst*valid_obs;
        for(i=0;i<ntcs;++i){
            INTG(&valid_TC,i,k)  = (!isMissIdx(TC_in,i,k))*valid_both;
            IDX(&nvalid_TC,i)   += INTG(&valid_TC,i,k);
        }
        cnt += valid_both;
	}
    /*
    printArrayFmtAllWHdr(stderr,nvalid_TC,"%lld","getMultiRegression: nvalid_TC");
    printArrayFmtAllWHdr(stderr,valid_TC,"%d","getMultiRegression: valid_TC");
    */
    
/*    fprintf(stderr," %d",++pcnt); */
    if (cnt == 0){
        freeAr(&nvalid_TC);
        freeAr(&valid_TC);
        freeAr(&fcst_z);
        return;
    }
    
    arr *TC   = malloc(ntcs*sizeof(arr));
/*    fprintf(stderr," %d",++pcnt); */
    for(i=0;i<ntcs;++i){
        TC[i]   = Array(1,DOUBLE,IDX(&nvalid_TC,i));
        copyMiss(&TC[i],  TC_in    );
    }
    cnt = 0;
/*    fprintf(stderr," %d",++pcnt); */
    for(i=0;i<ntcs;++i){
        cnt = 0;
        for(k=0;k<inlen;++k){
            if(INTG(&valid_TC,i,k)){
                iDBL(&TC[i],cnt)  = DBL(TC_in,i,k);
                ++cnt;
            }
        }
    }
/*    fprintf(stderr," %d",++pcnt); */
    
    /*
    for(i=0;i<ntcs;++i){
        printArrayFmtAllWHdr(stderr,TC[i], "%g","getMultiRegression: TC[%lld]  - ",i);
    }
    */

    /* main part of function to compute stepwise regression */
    typ_idx jtop;
    double m_c,b_c,rsq_c,mad_c;
    double m_top,b_top,rsq_top,mad_top;
    arr err_z,err_z_tmp;
    
    /* can use similar to strategy to missarr to filter already used indices */
    /* printArrayFmtAllWHdr(stderr,&fcst_z,"%g","getMultiRegression: fcst_z     - "); */
    /* for(l=0;l<ntcs;++l){ */
    for(l=0;l<2;++l){ /* Only does two iterations for speed, probably should also limit array size! */
        jtop    = -1;
        m_top   =  0;
        b_top   =  0;
        rsq_top =  0;
        mad_top =  987654321; /* Should be set to Max of err? */
        /*
        fprintf(stderr,"l=%lld: jtop = %lld,m_top = %g,b_top = %g,rsq_top = %g,mad_top = %g\n"
            ,l,jtop,m_top,b_top,rsq_top,mad_top);
        */
        
        err_z  = fct2ar(wrap_sub,&fcst_z,obs_z_in);
        /* printArrayFmtAllWHdr(stderr,&err_z,"%g","getMultiRegression: l=%lld: err_z     - ",l); */
        
        for(i=0;i<ntcs;++i){
            if (IDX(&nvalid_TC,i) > 5){
                err_z_tmp = Array(1,DOUBLE,IDX(&nvalid_TC,i));
                copyMiss(&err_z_tmp,&err_z);
                cnt = 0;
                for(k=0;k<inlen;++k){
                    if(INTG(&valid_TC,i,k)){
                        iDBL(&err_z_tmp,cnt) = iDBL(&err_z,k);
                        ++cnt;
                    }
                }
                /*
                printArrayFmtAllWHdr(stderr,&err_z_tmp,"%g","getMultiRegression: err_z_tmp  - ");
                printArrayFmtAllWHdr(stderr,&TC[i],"%g","getMultiRegression: TC[%lld]  - ",i);
                */
                m_c   = *(double *)getMiss(ms);
                b_c   = *(double *)getMiss(bs);
                rsq_c = *(double *)getMiss(rsqs);
                mad_c = *(double *)getMiss(rsqs);
                RegrRef_TheilSen(&TC[i],&err_z_tmp,&m_c,&b_c,&rsq_c,&mad_c);
                /*
                fprintf(stderr,"i = %lld,m_c = %g,b_c = %g,rsq_c = %g,mad_c = %g\n"
                    ,i,m_c,b_c,rsq_c,mad_c);
                */
                if (mad_c < mad_top){
                    m_top = m_c; b_top = b_c; rsq_top = rsq_c; mad_top = mad_c; jtop = i;
                    /*
                    fprintf(stderr,"jtop = %lld,m_top = %g,b_top = %g,rsq_top = %g,mad_top = %g\n"
                        ,jtop,m_top,b_top,rsq_top,mad_top);
                    */
                }
                freeAr(&err_z_tmp);
            }
        }
        freeAr(&err_z);
        /*
        fprintf(stderr,"l=%lld: jtop = %lld,m_top = %g,b_top = %g,rsq_top = %g,mad_top = %g\n"
            ,l,jtop,m_top,b_top,rsq_top,mad_top);
        */
        if (rsq_top > rsq_thresh){
            iIDX(idxs,l) = jtop;
            iDBL(ms,l)   = m_top;
            iDBL(bs,l)   = b_top;
            iDBL(rsqs,l) = rsq_top;
        } else {
            jtop = -1;
            iIDX(idxs,l) = jtop;
            iDBL(ms,l)   = 0;
            iDBL(bs,l)   = 0;
            iDBL(rsqs,l) = 0;
            break;
        }

        double fadj;
        if (jtop > -1){
            cnt = 0;
            for(k=0;k<inlen;++k){
                if(INTG(&valid_TC,jtop,k)){
                    fadj = m_top*iDBL(&TC[jtop],cnt) + b_top;
                    iDBL(&fcst_z,k) -= fadj;
                    ++cnt;
                }
            }
        }
    }
/*    fprintf(stderr," l=%lld",l);  */

    for(i=0;i<ntcs;++i){
        freeAr(&TC[i] );
    }
    free(TC );
    freeAr(&nvalid_TC);
    freeAr(&valid_TC);
	freeAr(&fcst_z);
/*    fprintf(stderr," %d\n",++pcnt);   */
    /*
    tm_end_all = clock();
    double tm_getMultiRegression = (double) (tm_end_all-tm_start_all) / CLOCKS_PER_SEC;

    fprintf(stderr,"tm_getMultiRegression =%5.2f\n",tm_getMultiRegression);
    */
    return;
}

void getMultiRegression_min(arr *restrict fcstens_z,arr *restrict obs_z_in,arr *restrict TC_in,double t_sig,double rsq_thresh,arr *ms,arr *bs,arr *rsqs,arr *idxs){
    /*
	clock_t tm_start_all,tm_end_all;
    tm_start_all = clock();
    */

    typ_idx i,k,l;
    /*
    printArrayFmtAllWHdr(stderr,fcstens_z,"%g","getMultiRegression_min: fcstens_z - ");
    printArrayFmtAllWHdr(stderr,obs_z_in, "%g","getMultiRegression_min: obs_z_in - ");
    printArrayFmtAllWHdr(stderr,TC_in,    "%g","getMultiRegression_min: TC_in - ");
    */
    
    arr fcst_z = arStatArg1ar(wrap_Mean,fcstens_z,1);
    if ((fcst_z.tlen < 1) || (fcst_z.n != 1) || (fcstens_z->n != 2) || (obs_z_in->n != 1) || (TC_in->n != 2)){
        printArrayFmtAllWHdr(stderr,fcstens_z,"%g","getMultiRegression_min: fcstens_z - ");
        printArrayFmtAllWHdr(stderr,TC_in,    "%g","getMultiRegression_min: TC_in     - ");
        printArrayFmtAllWHdr(stderr,&fcst_z,  "%g","getMultiRegression_min: fcst_z    - ");
        fputs("obs_z_in: \n",stderr);
        print_arr_exit(obs_z_in);
        printArrayFmtAllWHdr(stderr,obs_z_in, "%g","getMultiRegression_min: obs_z_in  - ");
    }
    
    typ_idx inlen = obs_z_in->tlen;
    typ_idx ntcs  = TC_in->len[0];
    
/*  int pcnt = 0; */
/*  fprintf(stderr,"getMultiRegression_min: %d",++pcnt);  */
    *ms   = Array(1,DOUBLE,ntcs);
    *bs   = Array(1,DOUBLE,ntcs);
    *rsqs = Array(1,DOUBLE,ntcs);
    *idxs = Array(1,TYPIDX,ntcs);
    fillArWithMiss(ms);
    fillArWithMiss(bs);
    fillArWithMiss(rsqs);
    fillArWithMiss(idxs);

    /* Remove missing values evenly across files. Not dealing with issue if an entire tc is missing for some reason for a given month. */
	typ_idx cnt = 0;
    int valid_fcst, valid_obs, valid_both;
	arr nvalid_TC  = Array(1,TYPIDX,ntcs);
	arr valid_TC   = Array(2,INT,ntcs,inlen);
/*  fprintf(stderr," %d",++pcnt);   */
	for(k=0;k<inlen;++k){
        valid_fcst = !isMiss(&fcst_z,k);
        valid_obs  = !isMiss(obs_z_in,k);
        valid_both = valid_fcst*valid_obs;
        for(i=0;i<ntcs;++i){
            INTG(&valid_TC,i,k)  = (!isMissIdx(TC_in,i,k))*valid_both;
            IDX(&nvalid_TC,i)   += INTG(&valid_TC,i,k);
        }
        cnt += valid_both;
	}
    /*
    printArrayFmtAllWHdr(stderr,nvalid_TC,"%lld","getMultiRegression_min: nvalid_TC");
    printArrayFmtAllWHdr(stderr,valid_TC,"%d","getMultiRegression_min: valid_TC");
    */
    
/*    fprintf(stderr," %d",++pcnt); */
    if (cnt == 0){
        freeAr(&nvalid_TC);
        freeAr(&valid_TC);
        freeAr(&fcst_z);
        return;
    }
    
    arr *TC   = malloc(ntcs*sizeof(arr));
/*    fprintf(stderr," %d",++pcnt); */
    for(i=0;i<ntcs;++i){
        TC[i]   = Array(1,DOUBLE,IDX(&nvalid_TC,i));
        copyMiss(&TC[i],  TC_in    );
    }
    cnt = 0;
/*    fprintf(stderr," %d",++pcnt); */
    for(i=0;i<ntcs;++i){
        cnt = 0;
        for(k=0;k<inlen;++k){
            if(INTG(&valid_TC,i,k)){
                iDBL(&TC[i],cnt)  = DBL(TC_in,i,k);
                ++cnt;
            }
        }
    }
/*    fprintf(stderr," %d",++pcnt); */
    
    /*
    for(i=0;i<ntcs;++i){
        printArrayFmtAllWHdr(stderr,TC[i], "%g","getMultiRegression_min: TC[%lld]  - ",i);
    }
    */

    /* main part of function to compute stepwise regression */
    typ_idx jtop;
    double m_c,b_c,rsq_c,mad_c;
    double m_top,b_top,rsq_top,mad_top;
    arr err_z,err_z_tmp;
    
    /* can use similar to strategy to missarr to filter already used indices */
    /* printArrayFmtAllWHdr(stderr,fcst_z,"%g","getMultiRegression_min: fcst_z     - "); */
    for(l=0;l<ntcs;++l){ /* */ /* Can do up to ntcs iterations, but will stop if acceptable regression not found */
    /* for(l=0;l<2;++l){ */ /* Only does two iterations for speed, probably should also limit array size! */
        jtop    = -1;
        m_top   =  0;
        b_top   =  0;
        rsq_top =  rsq_thresh;
        mad_top =  MAX_DOUBLE; /* Should be set to Max of err? */
        /*
        fprintf(stderr,"l=%lld: jtop = %lld,m_top = %g,b_top = %g,rsq_top = %g,mad_top = %g\n"
            ,l,jtop,m_top,b_top,rsq_top,mad_top);
        */
        
        err_z  = fct2ar(wrap_sub,&fcst_z,obs_z_in);
        /* printArrayFmtAllWHdr(stderr,err_z,"%g","getMultiRegression_min: l=%lld: err_z     - ",l); */
        
        for(i=0;i<ntcs;++i){
            if (IDX(&nvalid_TC,i) > 5){
                err_z_tmp = Array(1,DOUBLE,IDX(&nvalid_TC,i));
                copyMiss(&err_z_tmp,&err_z);
                cnt = 0;
                for(k=0;k<inlen;++k){
                    if(INTG(&valid_TC,i,k)){
                        iDBL(&err_z_tmp,cnt) = iDBL(&err_z,k);
                        ++cnt;
                    }
                }
                /*
                printArrayFmtAllWHdr(stderr,err_z_tmp,"%g","getMultiRegression_min: err_z_tmp  - ");
                printArrayFmtAllWHdr(stderr,TC[i],"%g","getMultiRegression_min: TC[%lld]  - ",i);
                */
                m_c   = *(double *)getMiss(ms);
                b_c   = *(double *)getMiss(bs);
                rsq_c = *(double *)getMiss(rsqs);
                mad_c = *(double *)getMiss(rsqs);
                RegrRef_min(&TC[i],&err_z_tmp,t_sig,&m_c,&b_c,&rsq_c,&mad_c);
                /*
                fprintf(stderr,"i = %lld,m_c = %g,b_c = %g,rsq_c = %g,mad_c = %g\n"
                    ,i,m_c,b_c,rsq_c,mad_c);
                */
                if (rsq_c > rsq_top){
                    m_top = m_c; b_top = b_c; rsq_top = rsq_c; mad_top = mad_c; jtop = i;
                    /*
                    fprintf(stderr,"jtop = %lld,m_top = %g,b_top = %g,rsq_top = %g,mad_top = %g\n"
                        ,jtop,m_top,b_top,rsq_top,mad_top);
                    */
                }
                freeAr(&err_z_tmp);
            }
        }
        freeAr(&err_z);
        /*
        fprintf(stderr,"l=%lld: jtop = %lld,m_top = %g,b_top = %g,rsq_top = %g,mad_top = %g\n"
            ,l,jtop,m_top,b_top,rsq_top,mad_top);
        */
        double fadj;
        if ((jtop > -1) && (m_top != 0)){
            iIDX(idxs,l) = jtop;
            iDBL(ms,l)   = m_top;
            iDBL(bs,l)   = b_top;
            iDBL(rsqs,l) = rsq_top;
            cnt = 0;
            for(k=0;k<inlen;++k){
                if(INTG(&valid_TC,jtop,k)){
                    fadj = m_top*iDBL(&TC[jtop],cnt) + b_top;
                    iDBL(&fcst_z,k) -= fadj;
                    ++cnt;
                }
            }
        } else {
            iIDX(idxs,l) = -1;
            iDBL(ms,l)   = 0;
            iDBL(bs,l)   = 0;
            iDBL(rsqs,l) = 0;
            break;
        }
    }
/*    fprintf(stderr," l=%lld",l);  */

    for(i=0;i<ntcs;++i){
        freeAr(&TC[i] );
    }
    free(TC );
    freeAr(&nvalid_TC);
    freeAr(&valid_TC);
	freeAr(&fcst_z);
/*    fprintf(stderr," %d\n",++pcnt);   */
    /*
    tm_end_all = clock();
    double tm_getMultiRegression = (double) (tm_end_all-tm_start_all) / CLOCKS_PER_SEC;

    fprintf(stderr,"tm_getMultiRegression =%5.2f\n",tm_getMultiRegression);
    */
    return;
}

void getMultiRegression_min_Prescribed(arr *restrict fcstens_z,arr *restrict obs_z_in,arr *restrict TC_in,arr *restrict idxs_in,double t_sig,double rsq_thresh,arr *ms,arr *bs,arr *rsqs){
    /*
	clock_t tm_start_all,tm_end_all;
    tm_start_all = clock();
    */

    typ_idx i,k,l;
    /*
    printArrayFmtAllWHdr(stderr,fcstens_z,"%g","getMultiRegression_min: fcstens_z - ");
    printArrayFmtAllWHdr(stderr,obs_z_in, "%g","getMultiRegression_min: obs_z_in - ");
    printArrayFmtAllWHdr(stderr,TC_in,    "%g","getMultiRegression_min: TC_in - ");
    */
    
    arr fcst_z = arStatArg1ar(wrap_Mean,fcstens_z,1);
    if ((fcst_z.tlen < 1) || (fcst_z.n != 1) || (fcstens_z->n != 2) || (obs_z_in->n != 1) || (TC_in->n != 2)){
        printArrayFmtAllWHdr(stderr,fcstens_z,"%g","getMultiRegression_min: fcstens_z - ");
        printArrayFmtAllWHdr(stderr,TC_in,    "%g","getMultiRegression_min: TC_in     - ");
        printArrayFmtAllWHdr(stderr,&fcst_z,  "%g","getMultiRegression_min: fcst_z    - ");
        fputs("obs_z_in: \n",stderr);
        print_arr_exit(obs_z_in);
        printArrayFmtAllWHdr(stderr,obs_z_in, "%g","getMultiRegression_min: obs_z_in  - ");
    }
    
    typ_idx inlen = obs_z_in->tlen;
    typ_idx ntcs  = TC_in->len[0];
    
/*  int pcnt = 0; */
/*  fprintf(stderr,"getMultiRegression_min: %d",++pcnt);  */
    *ms   = Array(1,DOUBLE,ntcs);
    *bs   = Array(1,DOUBLE,ntcs);
    *rsqs = Array(1,DOUBLE,ntcs);
    fillArWithMiss(ms);
    fillArWithMiss(bs);
    fillArWithMiss(rsqs);

    /* Remove missing values evenly across files. Not dealing with issue if an entire tc is missing for some reason for a given month. */
	typ_idx cnt = 0;
    int valid_fcst, valid_obs, valid_both;
	arr nvalid_TC  = Array(1,TYPIDX,ntcs);
	arr valid_TC   = Array(2,INT,ntcs,inlen);
/*  fprintf(stderr," %d",++pcnt);   */
	for(k=0;k<inlen;++k){
        valid_fcst = !isMiss(&fcst_z,k);
        valid_obs  = !isMiss(obs_z_in,k);
        valid_both = valid_fcst*valid_obs;
        for(i=0;i<ntcs;++i){
            INTG(&valid_TC,i,k)  = (!isMissIdx(TC_in,i,k))*valid_both;
            IDX(&nvalid_TC,i)   += INTG(&valid_TC,i,k);
        }
        cnt += valid_both;
	}
    /*
    printArrayFmtAllWHdr(stderr,nvalid_TC,"%lld","getMultiRegression_min: nvalid_TC");
    printArrayFmtAllWHdr(stderr,valid_TC,"%d","getMultiRegression_min: valid_TC");
    */
    
/*    fprintf(stderr," %d",++pcnt); */
    if (cnt == 0){
        freeAr(&nvalid_TC);
        freeAr(&valid_TC);
        freeAr(&fcst_z);
        return;
    }
    
    arr *TC   = malloc(ntcs*sizeof(arr));
/*    fprintf(stderr," %d",++pcnt); */
    for(i=0;i<ntcs;++i){
        TC[i]   = Array(1,DOUBLE,IDX(&nvalid_TC,i));
        copyMiss(&TC[i],  TC_in    );
    }
    cnt = 0;
/*    fprintf(stderr," %d",++pcnt); */
    for(i=0;i<ntcs;++i){
        cnt = 0;
        for(k=0;k<inlen;++k){
            if(INTG(&valid_TC,i,k)){
                iDBL(&TC[i],cnt)  = DBL(TC_in,i,k);
                ++cnt;
            }
        }
    }
/*    fprintf(stderr," %d",++pcnt); */
    
    /*
    for(i=0;i<ntcs;++i){
        printArrayFmtAllWHdr(stderr,TC[i], "%g","getMultiRegression_min: TC[%lld]  - ",i);
    }
    */

    /* main part of function to compute stepwise regression */
    typ_idx cidx;
    double m_c,b_c,rsq_c,mad_c;
    double m_top,b_top,rsq_top,mad_top;
    arr err_z,err_z_tmp;
    
    /* can use similar to strategy to missarr to filter already used indices */
    /* printArrayFmtAllWHdr(stderr,fcst_z,"%g","getMultiRegression_min: fcst_z     - "); */
    for(l=0;l<ntcs;++l){ /* */ /* Can do up to ntcs iterations, but will stop if acceptable regression not found */
    /* for(l=0;l<2;++l){ */ /* Only does two iterations for speed, probably should also limit array size! */
        if (isMiss(idxs_in,l)){
            break;
        } else {
            cidx    = iIDX(idxs_in,l);
            m_top   =  0;
            b_top   =  0;
            /* rsq_top =  rsq_thresh; */
            rsq_top =  0.0;
            mad_top =  MAX_DOUBLE; /* Should be set to Max of err? */
            /*
            fprintf(stderr,"l=%lld: m_top = %g,b_top = %g,rsq_top = %g,mad_top = %g\n"
                ,l,m_top,b_top,rsq_top,mad_top);
            */
            
            err_z  = fct2ar(wrap_sub,&fcst_z,obs_z_in);
            /* printArrayFmtAllWHdr(stderr,err_z,"%g","getMultiRegression_min: l=%lld: err_z     - ",l); */
            
            if (cidx > -1){
                if (IDX(&nvalid_TC,cidx) > 5){
                    err_z_tmp = Array(1,DOUBLE,IDX(&nvalid_TC,cidx));
                    copyMiss(&err_z_tmp,&err_z);
                    cnt = 0;
                    for(k=0;k<inlen;++k){
                        if(INTG(&valid_TC,cidx,k)){
                            iDBL(&err_z_tmp,cnt) = iDBL(&err_z,k);
                            ++cnt;
                        }
                    }
                    /*
                    printArrayFmtAllWHdr(stderr,err_z_tmp,"%g","getMultiRegression_min: err_z_tmp  - ");
                    printArrayFmtAllWHdr(stderr,TC[cidx],"%g","getMultiRegression_min: TC[%lld]  - ",cidx);
                    */
                    m_c   = *(double *)getMiss(ms);
                    b_c   = *(double *)getMiss(bs);
                    rsq_c = *(double *)getMiss(rsqs);
                    mad_c = *(double *)getMiss(rsqs);
                    RegrRef_min(&TC[cidx],&err_z_tmp,t_sig,&m_c,&b_c,&rsq_c,&mad_c);
                    /*
                    fprintf(stderr,"cidx = %lld,m_c = %g,b_c = %g,rsq_c = %g,mad_c = %g\n"
                        ,cidx,m_c,b_c,rsq_c,mad_c);
                    */
                    if (rsq_c > rsq_top){
                        m_top = m_c; b_top = b_c; rsq_top = rsq_c; mad_top = mad_c;
                        /*
                        fprintf(stderr,"m_top = %g,b_top = %g,rsq_top = %g,mad_top = %g\n"
                            ,m_top,b_top,rsq_top,mad_top);
                        */
                    }
                    freeAr(&err_z_tmp);
                }
            }
            freeAr(&err_z);
            /*
            fprintf(stderr,"l=%lld: m_top = %g,b_top = %g,rsq_top = %g,mad_top = %g\n"
                ,l,m_top,b_top,rsq_top,mad_top);
            */
            double fadj;
            if ((cidx > -1) && (m_top != 0)){
                iDBL(ms,l)   = m_top;
                iDBL(bs,l)   = b_top;
                iDBL(rsqs,l) = rsq_top;
                cnt = 0;
                for(k=0;k<inlen;++k){
                    if(INTG(&valid_TC,cidx,k)){
                        fadj = m_top*iDBL(&TC[cidx],cnt) + b_top;
                        iDBL(&fcst_z,k) -= fadj;
                        ++cnt;
                    }
                }
            } else {
                iDBL(ms,l)   = 0;
                iDBL(bs,l)   = 0;
                iDBL(rsqs,l) = 0;
                break;
            }
        }
    }
/*    fprintf(stderr," l=%lld",l);  */

    for(i=0;i<ntcs;++i){
        freeAr(&TC[i]);
    }
    free(TC );
    freeAr(&nvalid_TC);
    freeAr(&valid_TC);
	freeAr(&fcst_z);
/*    fprintf(stderr," %d\n",++pcnt);   */
    /*
    tm_end_all = clock();
    double tm_getMultiRegression = (double) (tm_end_all-tm_start_all) / CLOCKS_PER_SEC;

    fprintf(stderr,"tm_getMultiRegression =%5.2f\n",tm_getMultiRegression);
    */
    return;
}

double applyMultiRegression(arr *restrict TC,arr *restrict ms,arr *restrict bs,arr *restrict idxs,double fcst_z,typ_idx napply){
    typ_idx i,l;
    /*
    printArrayFmtAllWHdr(stderr,TC,  "%g",  "applyMultiRegression: TC   - ");
    printArrayFmtAllWHdr(stderr,ms,  "%g",  "applyMultiRegression: ms   - ");
    printArrayFmtAllWHdr(stderr,bs,  "%g",  "applyMultiRegression: bs   - ");
    printArrayFmtAllWHdr(stderr,idxs,"%lld","applyMultiRegression: idxs - ");
    fprintf(stderr,"applyMultiRegression: fcst_z=%g, napply=%lld\n",fcst_z,napply);
    */
    double  m,b,fadj,fcst_z_adj=fcst_z;
    for(l=0;l<napply;++l){
        if (isMiss(idxs,l)){
            break;
        } else {
            i = iIDX(idxs,l);
            m = iDBL(ms,l);
            b = iDBL(bs,l);
            if (i > -1){
                if (!isMiss(TC,i)){
                    fadj = m*iDBL(TC,i) + b;
                    /*
                        fprintf(stderr,"%g - ( %g * %g[%lld] + %g ) = ",fcst_z_adj,m,iDBL(TC,i),i,b);
                        fprintf(stderr,"%g - %g\n",fcst_z_adj,fadj);
                    */
                    fcst_z_adj -= fadj;
                /*  fprintf(stderr,"%g\n",fcst_z_adj); */
                }
            } else {
                break;
            }
        /*  fprintf(stderr,"%lld %g\n\n",l,fcst_z_adj); */
        }
    }

    /* fprintf(stderr,"applyMultiRegression: fcst_z=%g, fcst_z_adj=%g\n",fcst_z,fcst_z_adj); */
    return fcst_z_adj;
}



void getTertiaryExtremes(arr *restrict fcstens_in,arr *restrict cdf,gridnd *restrict grd,double *P_vlo,double *P_lo,double *P_mid,double *P_hi,double *P_vhi){
    double miss_P_vlo = *P_vlo;
    double miss_P_lo  = *P_lo;
    double miss_P_mid = *P_mid;
    double miss_P_hi  = *P_hi;
    double miss_P_vhi = *P_vhi;
/*
    printArrayFmtAllWHdr(stderr,fcstens_in,"%g","getTertiaryExtremes: fcstens_in - ");
    printArrayFmtAllWHdr(stderr,cdf,    "%g","getTertiaryExtremes: cdf - ");
    printGridNd(stderr,grd);
 */
    arr fcstens = removeMissing(fcstens_in);
    if (fcstens.tlen < 3){
        freeAr(&fcstens);
        return;
    }
    arr cdf_cut = removeMissing(cdf);
/*
    printArrayFmtAllWHdr(stderr,&fcstens,"%g","getTertiaryExtremes: fcstens - ");
    printArrayFmtAllWHdr(stderr,&cdf_cut,"%g","getTertiaryExtremes: cdf_cut - ");
    printGridNd(stderr,grd);
 */
    
    arr fcstens_srtd = qsortArray(&fcstens);

    /*
    typ_idx last_grd = grd->len[0]-1;
    double obs_min = grd->bcrd[0] - 0.5*grd->dcrd[0];
    double obs_max = grd->bcrd[0] + (last_grd+0.5)*grd->dcrd[0];
    */
    
    static double P_10 = 0.1;
    static double P_33 = 1.0/3.0;
    static double P_66 = 2.0/3.0;
    static double P_90 = 0.9;

    double idx_10 = IdxFromVal(&cdf_cut,P_10);
    double Val_10 = calcGridValNd_Dbl(grd,idx_10,0);
    double P_f_10 = calcPercatValSorted(&fcstens_srtd, Val_10);
    
    double idx_33 = IdxFromVal(&cdf_cut,P_33);
    double Val_33 = calcGridValNd_Dbl(grd,idx_33,0);
    double P_f_33 = calcPercatValSorted(&fcstens_srtd, Val_33);

    double idx_66 = IdxFromVal(&cdf_cut,P_66);
    double Val_66 = calcGridValNd_Dbl(grd,idx_66,0);
    double P_f_66 = calcPercatValSorted(&fcstens_srtd, Val_66);

    double idx_90 = IdxFromVal(&cdf_cut,P_90);
    double Val_90 = calcGridValNd_Dbl(grd,idx_90,0);
    double P_f_90 = calcPercatValSorted(&fcstens_srtd, Val_90);
    
    *P_vlo = P_f_10;
    *P_lo  = P_f_33;
    *P_mid = P_f_66 - P_f_33;
    *P_hi  = 1.0 - P_f_66;
    *P_vhi = 1.0 - P_f_90;
    
    if ((!isfinite(*P_vlo) || !isfinite(*P_lo) || !isfinite(*P_mid) || !isfinite(*P_hi) || !isfinite(*P_vhi))
        || ((*P_vlo < 0) || (*P_lo < 0) || (*P_mid < 0) || (*P_hi < 0) || (*P_vhi < 0))){
        printArrayFmtAllWHdr(stderr,cdf,    "%g","getTertiaryExtremes: cdf - ");
        printArrayFmtAllWHdr(stderr,&cdf_cut,"%g","getTertiaryExtremes: cdf_cut - ");
        printArrayFmtAllWHdr(stderr,fcstens_in,"%g","getTertiaryExtremes: fcstens_in - ");
        printArrayFmtAllWHdr(stderr,&fcstens_srtd,"%g","getTertiaryExtremes: fcstens_srtd - ");
        printGridNd(stderr,grd);
        /* fprintf(stderr,"getTertiaryExtremes: last_grd=%lld, obs_min=%g, obs_max=%g\n",last_grd,obs_min,obs_max); */
        fprintf(stderr,"getTertiaryExtremes: P_10=%g, P_33=%g, P_66=%g, P_90=%g\n",P_10,P_33,P_66,P_90);
        fprintf(stderr,"getTertiaryExtremes: idx_10=%g, Val_10=%g, P_f_10=%g\n",idx_10,Val_10,P_f_10);
        fprintf(stderr,"getTertiaryExtremes: idx_33=%g, Val_33=%g, P_f_33=%g\n",idx_33,Val_33,P_f_33);
        fprintf(stderr,"getTertiaryExtremes: idx_66=%g, Val_66=%g, P_f_66=%g\n",idx_66,Val_66,P_f_66);
        fprintf(stderr,"getTertiaryExtremes: idx_90=%g, Val_90=%g, P_f_90=%g\n",idx_90,Val_90,P_f_90);
        fprintf(stderr,"getTertiaryExtremes: P_vlo=%g, P_lo=%g, P_mid=%g, P_hi=%g, P_vhi=%g\n"
            ,*P_vlo,*P_lo,*P_mid,*P_hi,*P_vhi);
        exit(0);
        *P_vlo = miss_P_vlo;
        *P_lo  = miss_P_lo ;
        *P_mid = miss_P_mid;
        *P_hi  = miss_P_hi ;
        *P_vhi = miss_P_vhi;
    }

    freeAr(&cdf_cut);
    freeAr(&fcstens);
    freeAr(&fcstens_srtd);
    return;
}

void getTertiaryExtremes_z(arr *restrict fcstens_in,double *P_vlo,double *P_lo,double *P_mid,double *P_hi,double *P_vhi){
    double miss_P_vlo = *P_vlo;
    double miss_P_lo  = *P_lo;
    double miss_P_mid = *P_mid;
    double miss_P_hi  = *P_hi;
    double miss_P_vhi = *P_vhi;
/*  printArrayFmtAllWHdr(stderr,fcstens_in,"%g","getTertiaryExtremes_z: fcstens_in - "); */
    arr fcstens = removeMissing(fcstens_in);
    if (fcstens.tlen < 3){
        freeAr(&fcstens);
        return;
    }
/*  printArrayFmtAllWHdr(stderr,&fcstens,"%g","getTertiaryExtremes_z: fcstens - ");  */
    
    arr fcstens_srtd = qsortArray(&fcstens);

    static double P_10 = 0.1;
    static double P_33 = 1.0/3.0;
    static double P_66 = 2.0/3.0;
    static double P_90 = 0.9;

    static double Val_10;
    static double Val_33;
    static double Val_66;
    static double Val_90;
    
    static int constants_not_set = 1;
    
    if (constants_not_set){
        Val_10 = gsl_cdf_ugaussian_Pinv(P_10);
        Val_33 = gsl_cdf_ugaussian_Pinv(P_33);
        Val_66 = gsl_cdf_ugaussian_Pinv(P_66);
        Val_90 = gsl_cdf_ugaussian_Pinv(P_90);
        constants_not_set = 0;
    }

    double P_f_10 = calcPercatValSorted(&fcstens_srtd, Val_10);
    double P_f_33 = calcPercatValSorted(&fcstens_srtd, Val_33);
    double P_f_66 = calcPercatValSorted(&fcstens_srtd, Val_66);
    double P_f_90 = calcPercatValSorted(&fcstens_srtd, Val_90);
    
    *P_vlo = P_f_10;
    *P_lo  = P_f_33;
    *P_mid = P_f_66 - P_f_33;
    *P_hi  = 1.0 - P_f_66;
    *P_vhi = 1.0 - P_f_90;
    
    if ((!isfinite(*P_vlo) || !isfinite(*P_lo) || !isfinite(*P_mid) || !isfinite(*P_hi) || !isfinite(*P_vhi))
        || ((*P_vlo < 0) || (*P_lo < 0) || (*P_mid < 0) || (*P_hi < 0) || (*P_vhi < 0))){
        printArrayFmtAllWHdr(stderr,fcstens_in,"%g","getTertiaryExtremes_z: fcstens_in - ");
        printArrayFmtAllWHdr(stderr,&fcstens_srtd,"%g","getTertiaryExtremes_z: fcstens_srtd - ");
        fprintf(stderr,"getTertiaryExtremes_z: P_10=%g, P_33=%g, P_66=%g, P_90=%g\n",P_10,P_33,P_66,P_90);
        fprintf(stderr,"getTertiaryExtremes_z: Val_10=%g, P_f_10=%g\n",Val_10,P_f_10);
        fprintf(stderr,"getTertiaryExtremes_z: Val_33=%g, P_f_33=%g\n",Val_33,P_f_33);
        fprintf(stderr,"getTertiaryExtremes_z: Val_66=%g, P_f_66=%g\n",Val_66,P_f_66);
        fprintf(stderr,"getTertiaryExtremes_z: Val_90=%g, P_f_90=%g\n",Val_90,P_f_90);
        fprintf(stderr,"getTertiaryExtremes_z: P_vlo=%g, P_lo=%g, P_mid=%g, P_hi=%g, P_vhi=%g\n"
            ,*P_vlo,*P_lo,*P_mid,*P_hi,*P_vhi);
        *P_vlo = miss_P_vlo;
        *P_lo  = miss_P_lo ;
        *P_mid = miss_P_mid;
        *P_hi  = miss_P_hi ;
        *P_vhi = miss_P_vhi;
    }

    freeAr(&fcstens);
    freeAr(&fcstens_srtd);
    return;
}


void getPdfCdf(arr *restrict obs,double kwidth,gridnd *restrict grd,arr *pdf_y,arr *cdf_y){
    /*
    printArrayFmtAllWHdr(stderr,obs,"%5f","obs - ");
    */

    arr obs_cut    = removeMissing(obs);
    if (obs_cut.tlen > 0){
        getMarginalDistribution_kwidth(&obs_cut,kwidth,grd,pdf_y,cdf_y);
    }
    freeAr(&obs_cut);
	return;
}


arr Start2ValidTime(arr *restrict IN /* [leads,dim2,...,dimn] */){
    typ_idx nleads = IN->len[0];
    typ_idx nm     = IN->mlen[0];
    
    arr OUT = ArrayFromList(IN->n,IN->typ,IN->len);
    copyMiss(&OUT,IN);
    fillArWithMiss(&OUT);
    for(typ_idx j=0;j<nleads;++j){
        typ_idx joff = j*nm;
        double *pout = address_of_i(&OUT,joff+j);
        double *pin  = address_of_i(IN  ,joff);
        for(typ_idx i=j;i<nm;++i){
            *pout++ = *pin++;
        }
    }

    return OUT;
}

/*
 *  nleads should be moved to fastest varying dimension.
 */
arr getPersistenceNLeads(arr *restrict obs,typ_idx nleads){
    typ_idx ndims = obs->n + 1;
    typ_idx nobs  = obs->tlen;

    typ_idx *outlen = malloc(ndims*sizeof(typ_idx));
    typ_idx *plen   = outlen;
    *plen++ = nleads;
    for(typ_idx i=0; i < obs->n; ++i){
        *plen++ = obs->len[i];
    }
    
    arr pers = ArrayFromList(ndims,DOUBLE,outlen);
    copyMiss(&pers,obs);
    fillArWithMiss(&pers);
    for(typ_idx j=0; j<nleads; ++j){
        typ_idx jsub = j+1;
        double *pout = address_of_i(&pers,j*nobs+jsub);
        double *pin  = pntr_of(obs);
        for(typ_idx i=jsub; i<nobs; ++i){
            *pout++ = *pin++;
        }
    }

    free(outlen);
    return pers;
}

arr getPersistenceNLeads_Lag(arr *restrict obs,typ_idx nleads,typ_idx lag){
    typ_idx ndims = obs->n + 1;
    typ_idx nobs  = obs->tlen;

    typ_idx *outlen = malloc(ndims*sizeof(typ_idx));
    typ_idx *plen   = outlen;
    *plen++ = nleads;
    for(typ_idx i=0; i < obs->n; ++i){
        *plen++ = obs->len[i];
    }
    
    arr pers = ArrayFromList(ndims,DOUBLE,outlen);
    copyMiss(&pers,obs);
    fillArWithMiss(&pers);
    for(typ_idx j=0; j<nleads; ++j){
    /*  typ_idx jsub = j+1;   */
        typ_idx jsub = j+lag;
        double *pout = address_of_i(&pers,j*nobs+jsub);
        double *pin  = pntr_of(obs);
        for(typ_idx i=jsub; i<nobs; ++i){
            *pout++ = *pin++;
        }
    }

    free(outlen);
    return pers;
}

#endif
