/* Created by Bill Scheftic */
#ifndef  _WRAP_FUNC_H_
#define  _WRAP_FUNC_H_

#include <stdio.h>
#include <stdlib.h>
#include <arrayinit2.h>
#include <arrayops2.h>

typedef struct {
    int narrs, ndbls, nints, nidxs, nrarrs, nrdbls, nrints, nridxs;
} n_inputs;

typedef struct {
    int narrs, ndbls, nints, nidxs, nrarrs, nrdbls, nrints, nridxs;
/*  n_inputs; */
    arr     **arrays;
    double  *dblp;
    int     *intp;
    typ_idx *idxp;
    arr     **arrpp;
    double  **dblpp;
    int     **intpp;
    typ_idx **idxpp;
    double  *dblp_miss;
    int     *intp_miss;
    typ_idx *idxp_miss;
    double  *dblpp_miss;
    int     *intpp_miss;
    typ_idx *idxpp_miss;
    void    *missval;
} input_args;


typedef void               (*fctArgsNoRet) (input_args *);
typedef void *             (*fctArgsRgen)  (input_args *);
typedef signed char        (*fctArgsRbyt)  (input_args *);
typedef char               (*fctArgsRchr)  (input_args *);
typedef short              (*fctArgsRsht)  (input_args *);
typedef int                (*fctArgsRint)  (input_args *);
typedef float              (*fctArgsRflt)  (input_args *);
typedef double             (*fctArgsRdbl)  (input_args *);
typedef unsigned char      (*fctArgsRubyt) (input_args *);
typedef unsigned short     (*fctArgsRusht) (input_args *);
typedef unsigned int       (*fctArgsRuint) (input_args *);
typedef long long          (*fctArgsRlint) (input_args *);
typedef unsigned long long (*fctArgsRulint)(input_args *);
typedef arr                (*fctArgsRarr)  (input_args *);

typedef fctArgsRlint       fctArgsRidx;

input_args initInputArgs(void){
    input_args args;
    args.narrs     = 0;
    args.ndbls     = 0;
    args.nints     = 0;
    args.nidxs     = 0;
    args.nrarrs    = 0;
    args.nrdbls    = 0;
    args.nrints    = 0;
    args.nridxs    = 0;
    args.arrays    = NULL;
    args.dblp      = NULL;
    args.intp      = NULL;
    args.idxp      = NULL;
    args.arrpp     = NULL;
    args.dblpp     = NULL;
    args.intpp     = NULL;
    args.idxpp     = NULL;
    args.dblp_miss = NULL;
    args.intp_miss = NULL;
    args.idxp_miss = NULL;
    args.dblpp_miss = NULL;
    args.intpp_miss = NULL;
    args.idxpp_miss = NULL;
    args.missval   = NULL;
    return args;
}

input_args allocInputArgs(int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs){
    input_args args;
    args.narrs      = narrs;
    args.ndbls      = ndbls;
    args.nints      = nints;
    args.nidxs      = nidxs;
    args.nrarrs     = nrarrs;
    args.nrdbls     = nrdbls;
    args.nrints     = nrints;
    args.nridxs     = nridxs;
    args.arrays     = malloc(narrs*sizeof(arr *));
    args.dblp       = malloc(ndbls*sizeof(double));
    args.intp       = malloc(nints*sizeof(int));
    args.idxp       = malloc(nidxs*sizeof(typ_idx));
    args.arrpp      = malloc(nrarrs*sizeof(arr *));
    args.dblpp      = malloc(nrdbls*sizeof(double *));
    args.intpp      = malloc(nrints*sizeof(int *));
    args.idxpp      = malloc(nridxs*sizeof(typ_idx *));
    args.dblp_miss  = malloc(ndbls*sizeof(double));
    args.intp_miss  = malloc(nints*sizeof(int));
    args.idxp_miss  = malloc(nidxs*sizeof(typ_idx));
    args.dblpp_miss = malloc(ndbls*sizeof(double));
    args.intpp_miss = malloc(nints*sizeof(int));
    args.idxpp_miss = malloc(nidxs*sizeof(typ_idx));
    args.missval    = NULL;
    return args;
}

input_args passInputArgs(int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs
    ,arr **arrays,double *dblp,int *intp,typ_idx *idxp,arr **arrpp,double **dblpp,int **intpp,typ_idx **idxpp
    ,double *dblp_miss,int *intp_miss,typ_idx *idxp_miss,double *dblpp_miss,int *intpp_miss,typ_idx *idxpp_miss,void *missval){
    input_args args;
    args.narrs      = narrs;
    args.ndbls      = ndbls;
    args.nints      = nints;
    args.nidxs      = nidxs;
    args.nrarrs     = nrarrs;
    args.nrdbls     = nrdbls;
    args.nrints     = nrints;
    args.nridxs     = nridxs;
    args.arrays     = arrays;
    args.dblp       = dblp;
    args.intp       = intp;
    args.idxp       = idxp;
    args.arrpp      = arrpp;
    args.dblpp      = dblpp;
    args.intpp      = intpp;
    args.idxpp      = idxpp;
    args.dblp_miss  = dblp_miss;
    args.intp_miss  = intp_miss;
    args.idxp_miss  = idxp_miss;
    args.dblpp_miss = dblpp_miss;
    args.intpp_miss = intpp_miss;
    args.idxpp_miss = idxpp_miss;
    args.missval    = missval;
    return args;
}

/* should pass pointer of args, since struct members won't actually be changed to NULL here */
void freeInputArgs(input_args *args){
    free(args->arrays);
    free(args->dblp);
    free(args->intp);
    free(args->idxp);
    free(args->arrpp);
    free(args->dblpp);
    free(args->intpp);
    free(args->idxpp);
    free(args->dblp_miss);
    free(args->intp_miss);
    free(args->idxp_miss);
    free(args->dblpp_miss);
    free(args->intpp_miss);
    free(args->idxpp_miss);
    args->arrays     = NULL;
    args->dblp       = NULL;
    args->intp       = NULL;
    args->idxp       = NULL;
    args->arrpp      = NULL;
    args->dblpp      = NULL;
    args->intpp      = NULL;
    args->idxpp      = NULL;
    args->dblp_miss  = NULL;
    args->intp_miss  = NULL;
    args->idxp_miss  = NULL;
    args->dblpp_miss = NULL;
    args->intpp_miss = NULL;
    args->idxpp_miss = NULL;
    return;
}

void printInputArgs(FILE *fout,input_args *args){
    fprintf(fout,"printInputArgs: narrs=%d, ndbls=%d, nints=%d, nidxs=%d, nrarrs=%d, nrdbls=%d, nrints=%d, nridxs=%d\n",
        args->narrs,args->ndbls,args->nints,args->nidxs,args->nrarrs,args->nrdbls,args->nrints,args->nridxs);
    return;
}

int argNumsInvalid(const char *fct_name,input_args *args,int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs){
    if ( (args->narrs != narrs) || 
         (args->ndbls != ndbls) ||
         (args->nints != nints) ||
         (args->nidxs != nidxs) ||
         (args->nrarrs != nrarrs) ||
         (args->nrdbls != nrdbls) ||
         (args->nrints != nrints) ||
         (args->nridxs != nridxs) ){
        fprintf(stderr,"%s expects %d arrays,      received %d arrays\n"  ,fct_name,narrs,args->narrs);
        fprintf(stderr,"%s expects %d doubles,     received %d doubles\n" ,fct_name,ndbls,args->ndbls);
        fprintf(stderr,"%s expects %d ints,        received %d ints\n"    ,fct_name,nints,args->nints);
        fprintf(stderr,"%s expects %d typ_idxs,    received %d typ_idxs\n",fct_name,nidxs,args->nidxs);
        fprintf(stderr,"%s expects %d arr *s,      received %d arr *s\n"    ,fct_name,nrarrs,args->nrarrs);
        fprintf(stderr,"%s expects %d double *s,   received %d double *s\n" ,fct_name,nrdbls,args->nrdbls);
        fprintf(stderr,"%s expects %d int *s,      received %d int *s\n"    ,fct_name,nrints,args->nrints);
        fprintf(stderr,"%s expects %d typ_idxs *s, received %d typ_idx *s\n",fct_name,nridxs,args->nridxs);
        return 1;
    }
    return 0;
}


double wrap_dbl_1d1i(double (*fct)(double,int),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x    = args->dblp[0];
    double xint = args->intp[0];

    double rv = fct(x,xint);
    if (isfinite(rv)){ return rv; } else { return *(double *)args->missval; }
}

double wrap_dbl_1d(double (*fct)(double),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x = args->dblp[0];

    double rv = fct(x);
    if (isfinite(rv)){ return rv; } else { return *(double *)args->missval; }
}

double wrap_dbl_2d(double (*fct)(double,double),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    double y = args->dblp[1];

    double rv = fct(x,y);
    if (isfinite(rv)){ return rv; } else { return *(double *)args->missval; }
}

double wrap_dbl_3d(double (*fct)(double,double,double),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    double y = args->dblp[1];
    double z = args->dblp[2];

    double rv = fct(x,y,z);
    if (isfinite(rv)){ return rv; } else { return *(double *)args->missval; }
}

double wrap_dbl_4d(double (*fct)(double,double,double,double),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    double y = args->dblp[1];
    double z = args->dblp[2];
    double t = args->dblp[3];

    double rv = fct(x,y,z,t);
    if (isfinite(rv)){ return rv; } else { return *(double *)args->missval; }
}

double wrap_dbl_6d(double (*fct)(double,double,double,double,double,double),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    double y = args->dblp[1];
    double z = args->dblp[2];
    double t = args->dblp[3];
    double u = args->dblp[4];
    double v = args->dblp[5];

    double rv = fct(x,y,z,t,u,v);
    if (isfinite(rv)){ return rv; } else { return *(double *)args->missval; }
}

double wrap_dbl_7d(double (*fct)(double,double,double,double,double,double,double),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    double y = args->dblp[1];
    double z = args->dblp[2];
    double t = args->dblp[3];
    double u = args->dblp[4];
    double v = args->dblp[5];
    double a = args->dblp[6];

    double rv = fct(x,y,z,t,u,v,a);
    if (isfinite(rv)){ return rv; } else { return *(double *)args->missval; }
}

double wrap_dbl_8d(double (*fct)(double,double,double,double,double,double,double,double),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    double y = args->dblp[1];
    double z = args->dblp[2];
    double t = args->dblp[3];
    double u = args->dblp[4];
    double v = args->dblp[5];
    double a = args->dblp[6];
    double b = args->dblp[7];

    double rv = fct(x,y,z,t,u,v,a,b);
    if (isfinite(rv)){ return rv; } else { return *(double *)args->missval; }
}

double wrap_dbl_9d(double (*fct)(double,double,double,double,double,double,double,double,double),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double x = args->dblp[0];
    double y = args->dblp[1];
    double z = args->dblp[2];
    double t = args->dblp[3];
    double u = args->dblp[4];
    double v = args->dblp[5];
    double a = args->dblp[6];
    double b = args->dblp[7];
    double c = args->dblp[8];

    double rv = fct(x,y,z,t,u,v,a,b,c);
    if (isfinite(rv)){ return rv; } else { return *(double *)args->missval; }
}

int wrap_int_1ar1i_r1d(int (*fct)(arr *,int,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(int *)args->missval;
            }
        }
    }
    int rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(int *)args->missval;
    } else {
        int     x   = args->intp[0];
        double *pd1 = args->dblpp[0];
        rv = fct(&A[0],x,pd1);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

void wrap_1ar_r2i(void (*fct)(arr *,int *,int *),input_args *args,typ_idx nneeded){
    int i;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        int *pi1 = args->intpp[0];
        int *pi2 = args->intpp[1];
        fct(&A[0],pi1,pi2);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
}

void wrap_2ar_r3d(void (*fct)(arr *,arr *,double *,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double *pd1 = args->dblpp[0];
        double *pd2 = args->dblpp[1];
        double *pd3 = args->dblpp[2];
        fct(&A[0],&A[1],pd1,pd2,pd3);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
}

void wrap_2ar_r4d(void (*fct)(arr *,arr *,double *,double *,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double *pd1 = args->dblpp[0];
        double *pd2 = args->dblpp[1];
        double *pd3 = args->dblpp[2];
        double *pd4 = args->dblpp[3];
        fct(&A[0],&A[1],pd1,pd2,pd3,pd4);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
}

int wrap_int_1ar(int (*fct)(arr *),input_args *args,typ_idx nneeded){
    int i;
    int rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        /*
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        */
        rv = *(int *)args->missval;
    } else {
        rv = fct(&A[0]);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

int wrap_int_1ar1d(int (*fct)(arr *,double),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(int *)args->missval;
            }
        }
    }
    int rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        /*
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        */
        rv = *(int *)args->missval;
    } else {
        double x = args->dblp[0];
        rv = fct(&A[0],x);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_dbl_1ar(double (*fct)(arr *),input_args *args,typ_idx nneeded){
    int i;
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        rv = *(double *)args->missval;
    } else {
        rv = fct(&A[0]);
        if (!isfinite(rv)){ rv = *(double *)args->missval; }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_dbl_2ar(double (*fct)(arr *,arr *),input_args *args,typ_idx nneeded){
    int i;
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        /*
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        */
        rv = *(double *)args->missval;
    } else {
        rv = fct(&A[0],&A[1]);
        if (!isfinite(rv) /* || (rv == A[0].missdbl) || (rv == A[1].missdbl) */){ rv = *(double *)args->missval; }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_dbl_3ar(double (*fct)(arr *,arr *,arr *),input_args *args,typ_idx nneeded){
    int i;
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        /*
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        */
        rv = *(double *)args->missval;
    } else {
        rv = fct(&A[0],&A[1],&A[2]);
        if (!isfinite(rv)){ rv = *(double *)args->missval; }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_dbl_1ar1d(double (*fct)(arr *,double),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        /*
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        */
        rv = *(double *)args->missval;
    } else {
        double x = args->dblp[0];
        rv = fct(&A[0],x);
        if (!isfinite(rv)){ rv = *(double *)args->missval; }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_dbl_2ar1d(double (*fct)(arr *,arr *,double),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        /*
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        */
        rv = *(double *)args->missval;
    } else {
        double x = args->dblp[0];
        rv = fct(&A[0],&A[1],x);
        if (!isfinite(rv)){ rv = *(double *)args->missval; }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_dbl_3ar1d(double (*fct)(arr *,arr *,arr *,double),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        /*
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        */
        rv = *(double *)args->missval;
    } else {
        double x = args->dblp[0];
        rv = fct(&A[0],&A[1],&A[2],x);
        if (!isfinite(rv)){ rv = *(double *)args->missval; }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_dbl_1ar1i(double (*fct)(arr *,int),input_args *args,typ_idx nneeded){
    int i;
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        /*
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        */
        rv = *(double *)args->missval;
    } else {
        int x = args->intp[0];
        rv = fct(&A[0],x);
        if (!isfinite(rv)){ rv = *(double *)args->missval; }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_dbl_2ar1i(double (*fct)(arr *,arr *,int),input_args *args,typ_idx nneeded){
    int i;
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        /*
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        */
        rv = *(double *)args->missval;
    } else {
        int x = args->intp[0];
        rv = fct(&A[0],&A[1],x);
        if (!isfinite(rv)){ rv = *(double *)args->missval; }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}


/* Generated Functions */
void wrap_1ar_r2d(void (*fct)(arr *,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        fct(&A[0],pdbl0,pdbl1);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_1ar_r3d(void (*fct)(arr *,double *,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        double *pdbl2 = args->dblpp[2];
        fct(&A[0],pdbl0,pdbl1,pdbl2);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_1ar1d_r3d(void (*fct)(arr *,double,double *,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        double *pdbl2 = args->dblpp[2];
        fct(&A[0],dbl0,pdbl0,pdbl1,pdbl2);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar1d1i_r2d(void (*fct)(arr *,arr *,double,int,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        int     int0  = args->intp[0];
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        fct(&A[0],&A[1],dbl0,int0,pdbl0,pdbl1);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar1d2i_r2d(void (*fct)(arr *,arr *,double,int,int,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        int     int0  = args->intp[0];
        int     int1  = args->intp[1];
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        fct(&A[0],&A[1],dbl0,int0,int1,pdbl0,pdbl1);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar1d_r15d(void (*fct)(arr *,arr *,double,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        double *pdbl2 = args->dblpp[2];
        double *pdbl3 = args->dblpp[3];
        double *pdbl4 = args->dblpp[4];
        double *pdbl5 = args->dblpp[5];
        double *pdbl6 = args->dblpp[6];
        double *pdbl7 = args->dblpp[7];
        double *pdbl8 = args->dblpp[8];
        double *pdbl9 = args->dblpp[9];
        double *pdbl10 = args->dblpp[10];
        double *pdbl11 = args->dblpp[11];
        double *pdbl12 = args->dblpp[12];
        double *pdbl13 = args->dblpp[13];
        double *pdbl14 = args->dblpp[14];
        fct(&A[0],&A[1],dbl0,pdbl0,pdbl1,pdbl2,pdbl3,pdbl4,pdbl5,pdbl6,pdbl7,pdbl8,pdbl9,pdbl10,pdbl11,pdbl12,pdbl13,pdbl14);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar1d_r1d(void (*fct)(arr *,arr *,double,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double *pdbl0 = args->dblpp[0];
        fct(&A[0],&A[1],dbl0,pdbl0);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar1d_r2d(void (*fct)(arr *,arr *,double,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        fct(&A[0],&A[1],dbl0,pdbl0,pdbl1);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar1d_r3d(void (*fct)(arr *,arr *,double,double *,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        double *pdbl2 = args->dblpp[2];
        fct(&A[0],&A[1],dbl0,pdbl0,pdbl1,pdbl2);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar1d_r8d(void (*fct)(arr *,arr *,double,double *,double *,double *,double *,double *,double *,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        double *pdbl2 = args->dblpp[2];
        double *pdbl3 = args->dblpp[3];
        double *pdbl4 = args->dblpp[4];
        double *pdbl5 = args->dblpp[5];
        double *pdbl6 = args->dblpp[6];
        double *pdbl7 = args->dblpp[7];
        fct(&A[0],&A[1],dbl0,pdbl0,pdbl1,pdbl2,pdbl3,pdbl4,pdbl5,pdbl6,pdbl7);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar2d_r1d(void (*fct)(arr *,arr *,double,double,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        double *pdbl0 = args->dblpp[0];
        fct(&A[0],&A[1],dbl0,dbl1,pdbl0);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar2d_r5ar1d1i(void (*fct)(arr *,arr *,double,double,arr *,arr *,arr *,arr *,arr *,double *,int *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        /*
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        */
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        arr    *par0  = args->arrpp[0];
        arr    *par1  = args->arrpp[1];
        arr    *par2  = args->arrpp[2];
        arr    *par3  = args->arrpp[3];
        arr    *par4  = args->arrpp[4];
        double *pdbl0 = args->dblpp[0];
        int    *pint0 = args->intpp[0];
        fct(&A[0],&A[1],dbl0,dbl1,par0,par1,par2,par3,par4,pdbl0,pint0);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar3d1i_r1d(void (*fct)(arr *,arr *,double,double,double,int,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        double  dbl2  = args->dblp[2];
        int     int0  = args->intp[0];
        double *pdbl0 = args->dblpp[0];
        fct(&A[0],&A[1],dbl0,dbl1,dbl2,int0,pdbl0);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar3d2i_r6ar(void (*fct)(arr *,arr *,double,double,double,int,int,arr *,arr *,arr *,arr *,arr *,arr *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        /*
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        */
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        double  dbl2  = args->dblp[2];
        int     int0  = args->intp[0];
        int     int1  = args->intp[1];
        arr    *par0  = args->arrpp[0];
        arr    *par1  = args->arrpp[1];
        arr    *par2  = args->arrpp[2];
        arr    *par3  = args->arrpp[3];
        arr    *par4  = args->arrpp[4];
        arr    *par5  = args->arrpp[5];
        fct(&A[0],&A[1],dbl0,dbl1,dbl2,int0,int1,par0,par1,par2,par3,par4,par5);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar3d_r12d(void (*fct)(arr *,arr *,double,double,double,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        double  dbl2  = args->dblp[2];
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        double *pdbl2 = args->dblpp[2];
        double *pdbl3 = args->dblpp[3];
        double *pdbl4 = args->dblpp[4];
        double *pdbl5 = args->dblpp[5];
        double *pdbl6 = args->dblpp[6];
        double *pdbl7 = args->dblpp[7];
        double *pdbl8 = args->dblpp[8];
        double *pdbl9 = args->dblpp[9];
        double *pdbl10 = args->dblpp[10];
        double *pdbl11 = args->dblpp[11];
        fct(&A[0],&A[1],dbl0,dbl1,dbl2,pdbl0,pdbl1,pdbl2,pdbl3,pdbl4,pdbl5,pdbl6,pdbl7,pdbl8,pdbl9,pdbl10,pdbl11);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar3d_r1d(void (*fct)(arr *,arr *,double,double,double,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        double  dbl2  = args->dblp[2];
        double *pdbl0 = args->dblpp[0];
        fct(&A[0],&A[1],dbl0,dbl1,dbl2,pdbl0);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar3d_r2ar(void (*fct)(arr *,arr *,double,double,double,arr *,arr *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        /*
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        */
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        double  dbl2  = args->dblp[2];
        arr    *par0  = args->arrpp[0];
        arr    *par1  = args->arrpp[1];
        fct(&A[0],&A[1],dbl0,dbl1,dbl2,par0,par1);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar3d_r4d(void (*fct)(arr *,arr *,double,double,double,double *,double *,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        double  dbl2  = args->dblp[2];
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        double *pdbl2 = args->dblpp[2];
        double *pdbl3 = args->dblpp[3];
        fct(&A[0],&A[1],dbl0,dbl1,dbl2,pdbl0,pdbl1,pdbl2,pdbl3);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar3d_r5d(void (*fct)(arr *,arr *,double,double,double,double *,double *,double *,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        double  dbl2  = args->dblp[2];
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        double *pdbl2 = args->dblpp[2];
        double *pdbl3 = args->dblpp[3];
        double *pdbl4 = args->dblpp[4];
        fct(&A[0],&A[1],dbl0,dbl1,dbl2,pdbl0,pdbl1,pdbl2,pdbl3,pdbl4);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar4d2i_r6ar(void (*fct)(arr *,arr *,double,double,double,double,int,int,arr *,arr *,arr *,arr *,arr *,arr *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        /*
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        */
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        double  dbl2  = args->dblp[2];
        double  dbl3  = args->dblp[3];
        int     int0  = args->intp[0];
        int     int1  = args->intp[1];
        arr    *par0  = args->arrpp[0];
        arr    *par1  = args->arrpp[1];
        arr    *par2  = args->arrpp[2];
        arr    *par3  = args->arrpp[3];
        arr    *par4  = args->arrpp[4];
        arr    *par5  = args->arrpp[5];
        fct(&A[0],&A[1],dbl0,dbl1,dbl2,dbl3,int0,int1,par0,par1,par2,par3,par4,par5);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar_r10d(void (*fct)(arr *,arr *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        double *pdbl2 = args->dblpp[2];
        double *pdbl3 = args->dblpp[3];
        double *pdbl4 = args->dblpp[4];
        double *pdbl5 = args->dblpp[5];
        double *pdbl6 = args->dblpp[6];
        double *pdbl7 = args->dblpp[7];
        double *pdbl8 = args->dblpp[8];
        double *pdbl9 = args->dblpp[9];
        fct(&A[0],&A[1],pdbl0,pdbl1,pdbl2,pdbl3,pdbl4,pdbl5,pdbl6,pdbl7,pdbl8,pdbl9);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar_r2d(void (*fct)(arr *,arr *,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        fct(&A[0],&A[1],pdbl0,pdbl1);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_2ar_r8d(void (*fct)(arr *,arr *,double *,double *,double *,double *,double *,double *,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        double *pdbl2 = args->dblpp[2];
        double *pdbl3 = args->dblpp[3];
        double *pdbl4 = args->dblpp[4];
        double *pdbl5 = args->dblpp[5];
        double *pdbl6 = args->dblpp[6];
        double *pdbl7 = args->dblpp[7];
        fct(&A[0],&A[1],pdbl0,pdbl1,pdbl2,pdbl3,pdbl4,pdbl5,pdbl6,pdbl7);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_3ar2d1i_r2d(void (*fct)(arr *,arr *,arr *,double,double,int,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        int     int0  = args->intp[0];
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        fct(&A[0],&A[1],&A[2],dbl0,dbl1,int0,pdbl0,pdbl1);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_3ar2d_r2d(void (*fct)(arr *,arr *,arr *,double,double,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        fct(&A[0],&A[1],&A[2],dbl0,dbl1,pdbl0,pdbl1);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_3ar3d_r4d(void (*fct)(arr *,arr *,arr *,double,double,double,double *,double *,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        double  dbl2  = args->dblp[2];
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        double *pdbl2 = args->dblpp[2];
        double *pdbl3 = args->dblpp[3];
        fct(&A[0],&A[1],&A[2],dbl0,dbl1,dbl2,pdbl0,pdbl1,pdbl2,pdbl3);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_3ar4d1i_r1d(void (*fct)(arr *,arr *,arr *,double,double,double,double,int,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        double  dbl2  = args->dblp[2];
        double  dbl3  = args->dblp[3];
        int     int0  = args->intp[0];
        double *pdbl0 = args->dblpp[0];
        fct(&A[0],&A[1],&A[2],dbl0,dbl1,dbl2,dbl3,int0,pdbl0);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_3ar4d_r1d(void (*fct)(arr *,arr *,arr *,double,double,double,double,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        double  dbl2  = args->dblp[2];
        double  dbl3  = args->dblp[3];
        double *pdbl0 = args->dblpp[0];
        fct(&A[0],&A[1],&A[2],dbl0,dbl1,dbl2,dbl3,pdbl0);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_3ar_r3d(void (*fct)(arr *,arr *,arr *,double *,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        double *pdbl2 = args->dblpp[2];
        fct(&A[0],&A[1],&A[2],pdbl0,pdbl1,pdbl2);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_4ar3d_r2d(void (*fct)(arr *,arr *,arr *,arr *,double,double,double,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        double  dbl2  = args->dblp[2];
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        fct(&A[0],&A[1],&A[2],&A[3],dbl0,dbl1,dbl2,pdbl0,pdbl1);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

void wrap_5ar1d_r6d(void (*fct)(arr *,arr *,arr *,arr *,arr *,double,double *,double *,double *,double *,double *,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        double  dbl0  = args->dblp[0];
        double *pdbl0 = args->dblpp[0];
        double *pdbl1 = args->dblpp[1];
        double *pdbl2 = args->dblpp[2];
        double *pdbl3 = args->dblpp[3];
        double *pdbl4 = args->dblpp[4];
        double *pdbl5 = args->dblpp[5];
        fct(&A[0],&A[1],&A[2],&A[3],&A[4],dbl0,pdbl0,pdbl1,pdbl2,pdbl3,pdbl4,pdbl5);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return;
}

arr wrap_arr_1ar2i(arr (*fct)(arr *,int,int),input_args *args,typ_idx nneeded){
    int i;
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }
    arr rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(arr *)args->missval;
    } else {
        int     int0  = args->intp[0];
        int     int1  = args->intp[1];
        rv = fct(&A[0],int0,int1);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

arr wrap_arr_3ar1d(arr (*fct)(arr *,arr *,arr *,double),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }
    arr rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(arr *)args->missval;
    } else {
        double  dbl0  = args->dblp[0];
        rv = fct(&A[0],&A[1],&A[2],dbl0);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

arr wrap_arr_4ar2d(arr (*fct)(arr *,arr *,arr *,arr *,double,double),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }
    arr rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(arr *)args->missval;
    } else {
        double  dbl0  = args->dblp[0];
        double  dbl1  = args->dblp[1];
        rv = fct(&A[0],&A[1],&A[2],&A[3],dbl0,dbl1);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

arr wrap_arr_1ar(arr (*fct)(arr *),input_args *args,typ_idx nneeded){
    arr rv;
    arr A = removeMissing(args->arrays[0]);
    if (A.tlen < nneeded){
        rv = *(arr *)args->missval;
    } else {
        rv = fct(&A);
    }
    freeAr(&A);
    return rv;
}

arr wrap_arr_2ar(arr (*fct)(arr *,arr *),input_args *args,typ_idx nneeded){
    int i;
    arr rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(arr *)args->missval;
    } else {
        rv = fct(&A[0],&A[1]);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}


double wrap_dbl_2ar2i(double (*fct)(arr *,arr *,int,int),input_args *args,typ_idx nneeded){
    int i;
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(double *)args->missval;
    } else {
        int     int0  = args->intp[0];
        int     int1  = args->intp[1];
        rv = fct(&A[0],&A[1],int0,int1);
        if (!isfinite(rv)){ rv = *(double *)args->missval; }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

double wrap_dbl_3ar1i(double (*fct)(arr *,arr *,arr *,int),input_args *args,typ_idx nneeded){
    int i;
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(double *)args->missval;
    } else {
        int     int0  = args->intp[0];
        rv = fct(&A[0],&A[1],&A[2],int0);
        if (!isfinite(rv)){ rv = *(double *)args->missval; }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

int wrap_int_1ar2i(int (*fct)(arr *,int,int),input_args *args,typ_idx nneeded){
    int i;
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(int *)args->missval;
            }
        }
    }
    int rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(int *)args->missval;
    } else {
        int     int0  = args->intp[0];
        int     int1  = args->intp[1];
        rv = fct(&A[0],int0,int1);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}



int wrap_int_1d(int (*fct)(double),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(int *)args->missval;
            }
        }
    }
    int rv;
    double  dbl0  = args->dblp[0];
    rv = fct(dbl0);
    return rv;
}

int wrap_int_2d(int (*fct)(double,double),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(int *)args->missval;
            }
        }
    }
    int rv;
    double  dbl0  = args->dblp[0];
    double  dbl1  = args->dblp[1];
    rv = fct(dbl0,dbl1);
    return rv;
}

int wrap_int_1i(int (*fct)(int),input_args *args){
    int i;
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(int *)args->missval;
            }
        }
    }
    int rv;
    int     int0  = args->intp[0];
    rv = fct(int0);
    return rv;
}

int wrap_int_2i(int (*fct)(int,int),input_args *args){
    int i;
    if (args->intp_miss){
        for(i=0;i<args->nints;i++){
            if (args->intp[i] == args->intp_miss[i]){
                return *(int *)args->missval;
            }
        }
    }
    int rv;
    int     int0  = args->intp[0];
    int     int1  = args->intp[1];
    rv = fct(int0,int1);
    return rv;
}

double wrap_dbl_5d(double (*fct)(double,double,double,double,double),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double rv;
    double  dbl0  = args->dblp[0];
    double  dbl1  = args->dblp[1];
    double  dbl2  = args->dblp[2];
    double  dbl3  = args->dblp[3];
    double  dbl4  = args->dblp[4];
    rv = fct(dbl0,dbl1,dbl2,dbl3,dbl4);
    if (!isfinite(rv)){ rv = *(double *)args->missval; }
    return rv;
}




void wrap_3ar_r2ar_km(void (*fct)(arr *,arr *,arr *,arr *,arr *),input_args *args){
    arr **A   = args->arrays;
    arr *par0 = args->arrpp[0];
    arr *par1 = args->arrpp[1];
    fct(A[0],A[1],A[2],par0,par1);
    return;
}





typ_idx wrap_idx_1ar_km(typ_idx (*fct)(arr *),input_args *args){
    typ_idx rv;
    arr **A = args->arrays;
    rv      = fct(A[0]);
    return rv;
}

typ_idx wrap_idx_1ar(typ_idx (*fct)(arr *),input_args *args,typ_idx nneeded){
    int i;
    typ_idx rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        /*
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        */
        rv = *(typ_idx *)args->missval;
    } else {
        rv = fct(&A[0]);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}

typ_idx wrap_idx_1ar1d(typ_idx (*fct)(arr *,double),input_args *args,typ_idx nneeded){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(typ_idx *)args->missval;
            }
        }
    }
    typ_idx rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        /*
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        */
        rv = *(typ_idx *)args->missval;
    } else {
        double x = args->dblp[0];
        rv = fct(&A[0],x);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}


typ_idx wrap_idx_1ar1x_r1d(typ_idx (*fct)(arr *,typ_idx,double *),input_args *args,typ_idx nneeded){
    int i;
    if (args->idxp_miss){
        for(i=0;i<args->nidxs;i++){
            if (args->idxp[i] == args->idxp_miss[i]){
                return *(typ_idx *)args->missval;
            }
        }
    }
    typ_idx rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        rv = *(typ_idx *)args->missval;
    } else {
        typ_idx     x   = args->idxp[0];
        double *pd1 = args->dblpp[0];
        rv = fct(&A[0],x,pd1);
        if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}


void wrap_1ar_r2x(void (*fct)(arr *,typ_idx *,typ_idx *),input_args *args,typ_idx nneeded){
    int i;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
    } else {
        typ_idx *pi1 = args->idxpp[0];
        typ_idx *pi2 = args->idxpp[1];
        fct(&A[0],pi1,pi2);
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
}

double wrap_dbl_2ar1x(double (*fct)(arr *,arr *,typ_idx),input_args *args,typ_idx nneeded){
    int i;
    if (args->idxp_miss){
        for(i=0;i<args->nidxs;i++){
            if (args->idxp[i] == args->idxp_miss[i]){
                return *(double *)args->missval;
            }
        }
    }
    double rv;
    arr  *A = removeMissingNArraysList_alloc(args->narrs, args->arrays);
    if (A[0].tlen < nneeded){
        /*
        for (i=0;i<args->nrarrs;i++){
            args->arrpp[i] = NULL;
        }
        */
        rv = *(double *)args->missval;
    } else {
        typ_idx x = args->idxp[0];
        rv = fct(&A[0],&A[1],x);
        if (!isfinite(rv)){ rv = *(double *)args->missval; }
    }
    for (i=0;i<args->narrs;i++){
        freeAr(&A[i]);
    }
    free(A);
    return rv;
}




void wrap_3d_r2d(void (*fct)(double,double,double,double *,double *),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    double   dbl0  = args->dblp[0];
    double   dbl1  = args->dblp[1];
    double   dbl2  = args->dblp[2];
    double *pdbl0  = args->dblpp[0];
    double *pdbl1  = args->dblpp[1];
    fct(dbl0,dbl1,dbl2,pdbl0,pdbl1);
    if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    return;
}

void wrap_6d_r2d(void (*fct)(double,double,double,double,double,double,double *,double *),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    double   dbl0  = args->dblp[0];
    double   dbl1  = args->dblp[1];
    double   dbl2  = args->dblp[2];
    double   dbl3  = args->dblp[3];
    double   dbl4  = args->dblp[4];
    double   dbl5  = args->dblp[5];
    double *pdbl0  = args->dblpp[0];
    double *pdbl1  = args->dblpp[1];
    fct(dbl0,dbl1,dbl2,dbl3,dbl4,dbl5,pdbl0,pdbl1);
    if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    return;
}

void wrap_7d_r2d(void (*fct)(double,double,double,double,double,double,double,double *,double *),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    double   dbl0  = args->dblp[0];
    double   dbl1  = args->dblp[1];
    double   dbl2  = args->dblp[2];
    double   dbl3  = args->dblp[3];
    double   dbl4  = args->dblp[4];
    double   dbl5  = args->dblp[5];
    double   dbl6  = args->dblp[6];
    double *pdbl0  = args->dblpp[0];
    double *pdbl1  = args->dblpp[1];
    fct(dbl0,dbl1,dbl2,dbl3,dbl4,dbl5,dbl6,pdbl0,pdbl1);
    if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    return;
}

void wrap_10d_r4d(void (*fct)(double,double,double,double,double,double,double,double,double,double
    ,double *,double *,double *,double *),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    double   dbl0  = args->dblp[0];
    double   dbl1  = args->dblp[1];
    double   dbl2  = args->dblp[2];
    double   dbl3  = args->dblp[3];
    double   dbl4  = args->dblp[4];
    double   dbl5  = args->dblp[5];
    double   dbl6  = args->dblp[6];
    double   dbl7  = args->dblp[7];
    double   dbl8  = args->dblp[8];
    double   dbl9  = args->dblp[9];
    double *pdbl0  = args->dblpp[0];
    double *pdbl1  = args->dblpp[1];
    double *pdbl2  = args->dblpp[2];
    double *pdbl3  = args->dblpp[3];
    fct(dbl0,dbl1,dbl2,dbl3,dbl4,dbl5,dbl6,dbl7,dbl8,dbl9,pdbl0,pdbl1,pdbl2,pdbl3);
    if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    return;
}

void wrap_11d_r4d(void (*fct)(double,double,double,double,double,double,double,double,double,double,double
    ,double *,double *,double *,double *),input_args *args){
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    double   dbl0  = args->dblp[0];
    double   dbl1  = args->dblp[1];
    double   dbl2  = args->dblp[2];
    double   dbl3  = args->dblp[3];
    double   dbl4  = args->dblp[4];
    double   dbl5  = args->dblp[5];
    double   dbl6  = args->dblp[6];
    double   dbl7  = args->dblp[7];
    double   dbl8  = args->dblp[8];
    double   dbl9  = args->dblp[9];
    double   dbl10 = args->dblp[10];
    double *pdbl0  = args->dblpp[0];
    double *pdbl1  = args->dblpp[1];
    double *pdbl2  = args->dblpp[2];
    double *pdbl3  = args->dblpp[3];
    fct(dbl0,dbl1,dbl2,dbl3,dbl4,dbl5,dbl6,dbl7,dbl8,dbl9,dbl10,pdbl0,pdbl1,pdbl2,pdbl3);
    if (args->dblpp_miss){ for(i=0;i<args->nrdbls;i++){ if (!isfinite(*args->dblpp[i])){ *args->dblpp[i] = args->dblpp_miss[i]; } } }
    return;
}

#endif
