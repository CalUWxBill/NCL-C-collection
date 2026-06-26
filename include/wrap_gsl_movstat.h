#ifndef  _WRAP_GSL_MOVSTAT_H_
#define  _WRAP_GSL_MOVSTAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <gsl/gsl_movstat.h>

arr wrap_gsl_movstat_1ar1i(int (*fct)(const gsl_movstat_end_t, const gsl_vector *, gsl_vector *, gsl_movstat_workspace *),
    input_args *args){
    arr **A   = args->arrays;
    typ_idx n = A[0]->tlen;
    typ_idx nnonmiss = 0;
    arr missidx = getMissingIdxsNArraysList(args->narrs, A, &nnonmiss);
/*   */	printArrayAllWHdr(stdout,&missidx,  "missidx - ");
    size_t K = (size_t)args->intp[0];                       /* window size */
    arr rv   = Array(1,DOUBLE,n);
    copyMiss(&rv,A[0]);
    fillArWithMiss(&rv);

    if (nnonmiss){
        gsl_movstat_workspace * w = gsl_movstat_alloc(K);
        gsl_vector_view view      = gsl_vector_view_array(pntr_of(A[0]), n);
        gsl_vector_view viewout   = gsl_vector_view_array(pntr_of(&rv), n);
        if (nnonmiss == A[0]->tlen){
            fct(GSL_MOVSTAT_END_PADVALUE, &view.vector, &viewout.vector, w);
        } else {
            typ_idx i=0,k=0,ibeg,iend,nprt;
            for (;;){
            /*  fprintf(stderr,"wrap_gsl_movstat_mean: k=%lld n=%lld iINTG(&missidx,%lld)=%d\n",k,n,i,iINTG(&missidx,i));  */
                for(;(i<n) && (!iINTG(&missidx,i));++i);
                ibeg = i;
                if (ibeg >=n) { break; }
                for(;(i<n) && iINTG(&missidx,i);++i);
                iend = i;
                nprt = iend-ibeg;
            /*  fprintf(stderr,"wrap_gsl_movstat_mean: i=%lld ibeg=%lld iend=%lld nprt=%lld\n",i,ibeg,iend,nprt);  */
                gsl_vector_view view_tmp    = gsl_vector_subvector(&view.vector,    (size_t)ibeg, (size_t)nprt);
                gsl_vector_view viewout_tmp = gsl_vector_subvector(&viewout.vector, (size_t)ibeg, (size_t)nprt);
                fct(GSL_MOVSTAT_END_PADVALUE, &view_tmp.vector, &viewout_tmp.vector, w);
                ++k;
                if (i >=n) { break; }
            }
        }
        gsl_movstat_free(w);
    }

    freeAr(&missidx);
    return rv;
}

arr wrap_gsl_movstat_mean(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_movstat_1ar1i(gsl_movstat_mean,args);
}

arr wrap_gsl_movstat_variance(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_movstat_1ar1i(gsl_movstat_variance,args);
}

arr wrap_gsl_movstat_sd(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_movstat_1ar1i(gsl_movstat_sd,args);
}

arr wrap_gsl_movstat_min(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_movstat_1ar1i(gsl_movstat_min,args);
}

arr wrap_gsl_movstat_max(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_movstat_1ar1i(gsl_movstat_max,args);
}

arr wrap_gsl_movstat_sum(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_movstat_1ar1i(gsl_movstat_sum,args);
}

arr wrap_gsl_movstat_median(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_movstat_1ar1i(gsl_movstat_median,args);
}

arr wrap_gsl_movstat_Sn(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_movstat_1ar1i(gsl_movstat_Sn,args);
}

arr wrap_gsl_movstat_Qn(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_movstat_1ar1i(gsl_movstat_Qn,args);
}


arr wrap_gsl_movstat_1ar1d1i(int (*fct)(const gsl_movstat_end_t, const gsl_vector *, const double, gsl_vector *, gsl_movstat_workspace *),
    input_args *args){
    arr **A  = args->arrays;
    typ_idx  n = A[0]->tlen;
    typ_idx nnonmiss = 0;
    arr missidx = getMissingIdxsNArraysList(args->narrs, A, &nnonmiss);
/*	printArrayAllWHdr(stdout,&missidx,  "missidx - ");   */
    size_t K = (size_t)args->intp[0];                       /* window size */
    double dbl1 = args->dblp[0];
    arr rv   = Array(1,DOUBLE,n);
    copyMiss(&rv,A[0]);
    fillArWithMiss(&rv);

    if (nnonmiss){
        gsl_movstat_workspace * w = gsl_movstat_alloc(K);
        gsl_vector_view view      = gsl_vector_view_array(pntr_of(A[0]), n);
        gsl_vector_view viewout   = gsl_vector_view_array(pntr_of(&rv), n);
        if (nnonmiss == A[0]->tlen){
            fct(GSL_MOVSTAT_END_PADVALUE, &view.vector, dbl1, &viewout.vector, w);
        } else {
            typ_idx i=0,k=0,ibeg,iend,nprt;
            for (;;){
            /*  fprintf(stderr,"wrap_gsl_movstat_mean: k=%lld\n",k); */
                for(;(i<n) && (iINTG(&missidx,i)==0);++i);
                ibeg = i;
                if (ibeg >=n) { break; }
                for(;(i<n) && (iINTG(&missidx,i)==1);++i);
                iend = i;
                nprt = iend-ibeg;
            /*  fprintf(stderr,"wrap_gsl_movstat_mean: ibeg=%lld iend=%lld nprt=%lld\n",ibeg,iend,nprt); */
                gsl_vector_view view_tmp    = gsl_vector_subvector(&view.vector,    (size_t)ibeg, (size_t)nprt);
                gsl_vector_view viewout_tmp = gsl_vector_subvector(&viewout.vector, (size_t)ibeg, (size_t)nprt);
                fct(GSL_MOVSTAT_END_PADVALUE, &view_tmp.vector, dbl1, &viewout_tmp.vector, w);
                ++k;
                if (i >=n) { break; }
            }
        }
        gsl_movstat_free(w);
    }

    freeAr(&missidx);
    return rv;
}

arr wrap_gsl_movstat_qqr(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 1,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_movstat_1ar1d1i(gsl_movstat_qqr,args);
}


void wrap_gsl_movstat_1ar1i_r2ar(int (*fct)(const gsl_movstat_end_t, const gsl_vector *, gsl_vector *, gsl_vector *, gsl_movstat_workspace *),
    input_args *args){
/*  printInputArgs(stderr,args);    */
    arr **A  = args->arrays;
    typ_idx  n = A[0]->tlen;
    typ_idx nnonmiss = 0;
    arr missidx = getMissingIdxsNArraysList(args->narrs, A, &nnonmiss);
/*	printArrayAllWHdr(stdout,&missidx,"missidx - "); */
    size_t K = (size_t)args->intp[0];                       /* window size */

    if (nnonmiss){
        arr *par0 = args->arrpp[0];
        arr *par1 = args->arrpp[1];
        
        *par0 = Array(1,DOUBLE,n);
        copyMiss(par0,A[0]);
        fillArWithMiss(par0);
        *par1 = Array(1,DOUBLE,n);
        copyMiss(par1,A[0]);
        fillArWithMiss(par1);
    
        gsl_movstat_workspace * w = gsl_movstat_alloc(K);
        gsl_vector_view view      = gsl_vector_view_array(pntr_of(A[0]), n);
        gsl_vector_view vwr0      = gsl_vector_view_array(pntr_of(par0),  n);
        gsl_vector_view vwr1      = gsl_vector_view_array(pntr_of(par1),  n);
        if (nnonmiss == A[0]->tlen){
            fct(GSL_MOVSTAT_END_PADVALUE, &view.vector, &vwr0.vector, &vwr1.vector, w);
        } else {
            typ_idx i=0,k=0,ibeg,iend,nprt;
            for (;;){
                for(;(i<n) && (iINTG(&missidx,i)==0);++i);
                ibeg = i;
                if (ibeg >=n) { break; }
                for(;(i<n) && (iINTG(&missidx,i)==1);++i);
                iend = i;
                nprt = iend-ibeg;
                gsl_vector_view view_tmp = gsl_vector_subvector(&view.vector, (size_t)ibeg, (size_t)nprt);
                gsl_vector_view vwr0_tmp = gsl_vector_subvector(&vwr0.vector, (size_t)ibeg, (size_t)nprt);
                gsl_vector_view vwr1_tmp = gsl_vector_subvector(&vwr1.vector, (size_t)ibeg, (size_t)nprt);
                fct(GSL_MOVSTAT_END_PADVALUE, &view_tmp.vector, &vwr0_tmp.vector, &vwr1_tmp.vector, w);
                ++k;
                if (i >=n) { break; }
            }
        }
        gsl_movstat_free(w);
    } else {
        args->arrpp[0] = NULL;
        args->arrpp[1] = NULL;
    }

    freeAr(&missidx);
    return;
}

void wrap_gsl_movstat_mad0(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 2,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_movstat_1ar1i_r2ar(gsl_movstat_mad0,args);
}

void wrap_gsl_movstat_mad(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 2,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_movstat_1ar1i_r2ar(gsl_movstat_mad,args);
}

void wrap_gsl_movstat_minmax(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 2,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_gsl_movstat_1ar1i_r2ar(gsl_movstat_minmax,args);
}

#endif
