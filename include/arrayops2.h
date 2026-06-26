/* Created by Bill Scheftic */
#ifndef  _ARRAYOPS2_H_
#define  _ARRAYOPS2_H_
/*
 *  Things to add:
 *  --------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <math_supp.h>
#include <arrayinit2.h>
#include <print_arrays2.h>
#include <arrayftypes.h>

typ_idx *mapdims_Nar_Backup(int,arr**,typ_idx*,typ_idx***);
typ_idx *mapdims_Nar(int,arr**,typ_idx*,typ_idx***);
typ_idx *mapdims_Nar_2(int,arr**,typ_idx**,typ_idx*);
typ_idx *mapdims_inverse(typ_idx,typ_idx,typ_idx*);
typ_idx *mapdims_1ar2Nar(arr *,typ_idx,typ_idx*);
arr ArrayFromIdxs(arr *,arr *);
arr cyclicArray(arr *,typ_idx);
void resetMiss(arr *,double);
int isNanInf(arr *,typ_idx);
void setMissNanInf(arr *);
int isOutOfRange(arr *,typ_idx,void*,void*);
void setMissOutOfRange(arr *,void*,void*);
arr removeMissing(arr *);
void removeMissingNArraysList(int, arr**, arr**);
arr *removeMissingNArraysList_alloc(int,arr**);
void removeMissingNArrays(int, ...);
void removeMissing2Arrays(arr*,arr*,arr *,arr *);
arr getMissingIdxsNArraysList(int, arr **, typ_idx*);
arr getMissingIdxsNArrays(int, typ_idx*, ...);
void removeMissingNArraysFromMissArList(typ_idx, arr *, int, arr**, arr**);
arr *removeMissingNArraysFromMissArList_alloc(typ_idx,arr *,int,arr**);
void removeMissingNArraysFromMissAr(typ_idx,arr *,int, ...);
int isMiss_Loop(arr *, typ_idx, typ_idx, typ_idx, typ_idx*, typ_idx*);
void assignNonMiss_Loop(arr *, arr *, typ_idx, typ_idx, typ_idx, typ_idx, typ_idx*, typ_idx*);
arr RemoveIfAnyMissFromDim(arr *, typ_idx);
arr FilterBetweenFromDim(arr *, double, double, typ_idx, typ_idx*);
arr *FilterBetween1dArraysFromDim(arr**, int, double, double, typ_idx);
void filter2Arrays(double,double,arr*,arr*,arr *,arr *);
void filter3Arrays(double,double,arr*,arr*,arr*,arr *,arr *,arr *);
void setToValGT(arr *,double);
double sumAllAr(arr *);
arr grabSlice(arr *, typ_idx, typ_idx);
arr grab1dAr(arr *, typ_idx, typ_idx*);
arr grab2dAr(arr *, typ_idx, typ_idx, typ_idx*);
arr grabNdAr(arr *, typ_idx, typ_idx*, typ_idx*);
void grabNdAr_Loop(arr *, arr *, typ_idx*, typ_idx*, typ_idx, typ_idx*);
void fillArColWith1d(arr *,arr *,typ_idx,typ_idx*);
void fillArColWithVal(arr *,void*,typ_idx,typ_idx*);
void fillArColWithMiss(arr *,typ_idx,typ_idx*);
void removeOneElemDims(arr*);
arr reverseDim(arr *, typ_idx);
    void reverseDimLoop(arr *, arr *, typ_idx, typ_idx, typ_idx*);
arr grabSect(arr *, typ_idx*, typ_idx*);
    void grabSectLoop(arr *, arr *, typ_idx*, typ_idx*, typ_idx, typ_idx*, typ_idx *);
arr grabThinnedArray(arr *, typ_idx*);
    void grabThinnedArrayLoop(arr *, arr *, typ_idx*, typ_idx, typ_idx*);
arr grabSectThinned(arr *, typ_idx*, typ_idx*, typ_idx*);
void sumIncAr(arr*, arr *);
void expandDims(arr*,typ_idx*);
    void expandDims_loop(arr *, arr *, typ_idx, typ_idx*, typ_idx*);
void assignSect(arr *, typ_idx*, typ_idx*, arr *, typ_idx*, typ_idx*);
    void assignSectLoop(arr *,typ_idx*,typ_idx*,arr *,typ_idx*,typ_idx*,
        typ_idx*,typ_idx*,typ_idx*,typ_idx*,
        typ_idx,typ_idx,typ_idx*,typ_idx*);
void fillSect(arr *, typ_idx *, typ_idx *, void *);
    void fillSectLoop(arr *,typ_idx *,typ_idx *,void *,
        typ_idx *,typ_idx *,typ_idx,typ_idx,typ_idx *,typ_idx *);
void fillSectToMiss(arr *, typ_idx *, typ_idx *);
    void fillSectToMissLoop(arr *,typ_idx *,typ_idx *,
        typ_idx *,typ_idx *,typ_idx,typ_idx,typ_idx *,typ_idx *);
void assignPart(arr *,arr *,typ_idx*,typ_idx*);
    void assignPartLoop(arr *, arr *, typ_idx*, typ_idx*, typ_idx, typ_idx*);
void assignPart2(arr *,arr *,typ_idx*,typ_idx*);
    void assignPart2Loop(arr *, arr *, typ_idx*, typ_idx*, typ_idx, typ_idx*);
arr reorderDims(arr *, typ_idx*);
    void reorderDimsLoop(arr *, arr *, typ_idx*, typ_idx, typ_idx*);
arr expandAr(arr *,arr *,typ_idx*);
arr expandArExp(arr *,typ_idx,typ_idx*,typ_idx*);
    void expandAr_loop(arr *, arr *, typ_idx*, typ_idx, typ_idx*);
arr combineArraysList(int, typ_idx, arr**);
arr combineArrays(int, typ_idx, ...);
    void combineArraysLoop(arr *, arr**, int, typ_idx, typ_idx, typ_idx*, typ_idx, typ_idx, typ_idx*);
arr combineArrays2List(int, typ_idx, arr**);
arr combineArrays2(int, typ_idx, ...);
    void combineArrays2Loop(arr *, arr**, int, typ_idx, typ_idx, typ_idx*, typ_idx, typ_idx, typ_idx*);

/* --------------------------------------------------------- */
typ_idx *mapdims_Nar_Backup(int narrs,arr **INs,typ_idx *ndims,typ_idx ***maps){
/*  I need to detect ambiguity and display a warning    */
    typ_idx i,j,h=0;
    typ_idx n_pos_dims = 0;
    typ_idx *c  = init0(narrs,TYPIDX);
/*  typ_idx *ns = init0(narrs,TYPIDX); */

    for(i=0;i<narrs;++i){ n_pos_dims += INs[i]->n; }

    typ_idx *tmplens = init0(n_pos_dims,TYPIDX);
    typ_idx **avails = malloc(narrs*sizeof(typ_idx *));
    *maps        = malloc(narrs*sizeof(typ_idx *));

    for(i=0;i<narrs;++i){
        avails[i]  = init0(INs[i]->n,TYPIDX);
        (*maps)[i] = init0(INs[i]->n,TYPIDX);
    }
    
    for(i=0;i<narrs;++i){
    /*  fprintf(stderr,"mapdims_Nar: i=%lld\n",i);    */
        for (c[i]=0;c[i]<INs[i]->n;c[i]++){
        /*  fprintf(stderr,"mapdims_Nar: c[%lld]=%lld\n",i,c[i]);   */
            if (avails[i][c[i]] == 0){
                tmplens[h] = INs[i]->len[c[i]];
                (*maps)[i][c[i]] = h;
                avails[i][c[i]]  = 1;
                for(j=i+1;j<narrs;++j){
                /*  fprintf(stderr,"mapdims_Nar: j=%lld\n",j);    */
                    for (c[j]=0;c[j]<INs[j]->n;c[j]++){
                    /*  fprintf(stderr,"mapdims_Nar: c[%lld]=%lld\n",j,c[j]);   */
                    /*  fprintf(stderr,"mapdims_Nar: c[%lld]=%lld c[%lld]=%lld\n",i,c[i],j,c[j]);   */
                        if (avails[j][c[j]] == 0){
                            if (INs[i]->len[c[i]] == INs[j]->len[c[j]]){
                                (*maps)[j][c[j]] = h;
                                avails[j][c[j]]  = 1;
                                c[j] = INs[j]->n;
                            /*  ns[j]++; */
                            }
                        }
                    }
                }
                h++;
            }
        }
    }
    
    *ndims = h;
    typ_idx *lens   = init0(*ndims,TYPIDX);
    for(h=0;h < *ndims;++h){
        lens[h] = tmplens[h];
    }

    for(i=0;i<narrs;++i){
        free(avails[i]);
    }
    free(avails);
    free(tmplens);
    free(c);
/*  free(ns); */

    return lens;
}

typ_idx *mapdims_Nar(int narrs,arr **INs,typ_idx *ndims,typ_idx ***maps_in2out){
/*  I need to detect ambiguity and display a warning    */
    typ_idx i,j,h=0;
    typ_idx n_pos_dims = 0;
    typ_idx *c  = init0(narrs,TYPIDX);
/*  typ_idx *ns = init0(narrs,TYPIDX); */

    for(i=0;i<narrs;++i){ n_pos_dims += INs[i]->n; }

    typ_idx *tmplens = init0(n_pos_dims,TYPIDX);
    typ_idx **avails = malloc(narrs*sizeof(typ_idx *));
    *maps_in2out = malloc(narrs*sizeof(typ_idx *));

    for(i=0;i<narrs;++i){
        avails[i]  = init0(INs[i]->n,TYPIDX);
        (*maps_in2out)[i]  = init0(INs[i]->n,TYPIDX);
    }
    
    for(i=0;i<narrs;++i){
        for (c[i]=0;c[i]<INs[i]->n;c[i]++){
            if (avails[i][c[i]] == 0){
                tmplens[h] = INs[i]->len[c[i]];
                (*maps_in2out)[i][c[i]] = h;
                avails[i][c[i]]  = 1;
                for(j=i+1;j<narrs;++j){
                    for (c[j]=0;c[j]<INs[j]->n;c[j]++){
                        if (avails[j][c[j]] == 0){
                            if (INs[i]->len[c[i]] == INs[j]->len[c[j]]){
                                (*maps_in2out)[j][c[j]] = h;
                                avails[j][c[j]]  = 1;
                                c[j] = INs[j]->n;
                            /*  ns[j]++; */
                            }
                        }
                    }
                }
                h++;
            }
        }
    }
    
    *ndims = h;
    typ_idx *lens    = init0(*ndims,TYPIDX);
    for(h=0;h < *ndims;++h){
        lens[h] = tmplens[h];
    }
    
    for(i=0;i<narrs;++i){
        free(avails[i]);
    }
    free(avails);
    free(tmplens);
    free(c);
/*  free(ns); */

    return lens;
}

typ_idx *mapdims_Nar_2(int narrs,arr **INs,typ_idx **maps_in2out,typ_idx *ndims){
/*  I need to detect ambiguity and display a warning    */
    typ_idx i,j,k,h=0;
    typ_idx n_pos_dims = 0;

    for(i=0;i<narrs;++i){ n_pos_dims += INs[i]->n; }

    typ_idx *tmplens = init0(n_pos_dims,TYPIDX);
    typ_idx *avails  = init0(n_pos_dims,TYPIDX);
    for(i=0;i<narrs;++i){
        for (j=0;j<INs[i]->n;++j){
            k = maps_in2out[i][j];
            if ((k > -1) && (avails[k] == 0)){
                tmplens[k] = INs[i]->len[j];
                avails[k]  = 1;
                h++;
            }
        }
    }
    free(avails);
    
    *ndims = h;
    typ_idx *lens    = init0(*ndims,TYPIDX);
    for(h=0;h < *ndims;++h){
        lens[h] = tmplens[h];
    }
    free(tmplens);

    return lens;
}

typ_idx *mapdims_inverse(typ_idx ndims_in,typ_idx ndims_out,typ_idx *maps_in2out){
    typ_idx c;

    typ_idx *maps_out2in = malloc(ndims_out*sizeof(typ_idx));
    for(c=0;c<ndims_out;++c){ maps_out2in[c] = -1; }

    for (c=0;c<ndims_in;++c){
        maps_out2in[maps_in2out[c]] = c;
    }
    
    return maps_out2in;
}

typ_idx *mapdims_1ar2Nar(arr *restrict IN,typ_idx ndims,typ_idx *lens){
/*  I need to detect ambiguity and display a warning    */
    typ_idx c = 0,d = 0;

    typ_idx *avail_dims = init0(ndims,TYPIDX);
    typ_idx *map        = init0(IN->n, TYPIDX);
    
    for (c=0;c<IN->n;++c){
        map[c] = -1;
        for (d=0;d<ndims;++d){
            if (avail_dims[d] == 0){
                if (IN->len[c] == lens[d]){
                    map[c]        = d;
                    avail_dims[d] = 1;
                    break;
                }
            }
        }
    }
    
    free(avail_dims);
    return map;
}

/* Changed to speed up, should test! */
arr ArrayFromIdxs(arr *restrict X,arr *restrict idxs){ 
/*  Ideally, this would select on a specific dimension for n-dimensional arrays */
    if (X->n != 1) { fprintf(stderr,"ArrayFromIdxs: Must be 1 dimension\n"); exit(0); }
    typ_typ typ  = X->typ;
    typ_idx tlen = idxs->tlen;
    arr m = Array(1,typ,tlen);

    switch (typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        { \
            typ_idx *pidx = pntr_of(idxs); \
            swcast  *p    = pntr_of(&m);   \
            swcast  *pX   = pntr_of(X);    \
            for(typ_idx i=0;i<tlen;++i){   \
                *p++ = pX[*pidx++];  \
            } \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"ArrayFromIdxs: undefined type %d!\n",typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return m;
}

arr cyclicArray(arr *restrict X,typ_idx ncycpts){ 
    if (X->n != 1) { fprintf(stderr,"cyclicArray: Must be 1 dimension\n"); exit(0); }
    typ_idx i;
    arr m = Array(1,X->typ,(typ_idx)X->tlen + 2*ncycpts);

    switch (m.typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pin  = pntr_of(X); \
        swcast *pout = pntr_of(&m); \
        for(i=0;i<ncycpts;++i){                 \
            pout[i]                = pin[X->tlen-ncycpts+i];   \
        }                               \
        for(i=0;i<X->tlen;++i){                 \
            pout[i+ncycpts]        = pin[i];       \
        }                               \
        for(i=0;i<ncycpts;++i){                 \
            pout[m.tlen-ncycpts+i] = pin[i];    \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"cyclicArray: undefined type %d!\n",m.typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return m;
}

/* Changed to speed up, should test! */
void resetMiss(arr *restrict X,double oldmiss){
    switch (X->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        { \
            swcast swmtyp = *(swcast *)getMiss(X); \
            swcast *p     = pntr_of(X); \
            for(typ_idx i=0;i<X->tlen;++i,p++){  \
                if (isNear((double)*p,oldmiss)){ \
                    *p = swmtyp;                 \
                }                                \
            } \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in resetMiss: undefined type %d!\n",X->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return;
}

int isNanInf(arr *restrict X,typ_idx idx){
    switch (X->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,iswassign,swcompare,fmt1,fmt2)  \
        return isnan((double)iswassign(X,idx)) || isinf((double)iswassign(X,idx));
        ALLTYPECASES3
        default:
            fprintf(stderr,"Error in isNanInf: undefined type %d!\n",X->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST
}

/* Should probably step through pointer comparing to NaN Inf */
int isAnyNanInf(arr *restrict m){
    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        { \
            swcast *p     = pntr_of(m); \
            swcast swmtyp = *(swcast *)getMiss(m); \
            for(typ_idx i=0;i<m->tlen;++i){ \
                swcast x = *p++; \
                if (x!=swmtyp){ \
                    if(isnan((double)x) || isinf((double)x)){ \
                        return 1; \
                    } \
                } \
            } \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in isAnyNanInf: undefined type %d!\n",m->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST
    return 0;
}


/* Should probably step through pointer comparing to NaN Inf, and setting to retrieved missing value */
void setMissNanInf(arr *restrict X){
    switch (X->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        { \
            swcast *p     = pntr_of(X); \
            swcast swmtyp = *(swcast *)getMiss(X); \
            for(typ_idx i=0;i<X->tlen;++i,p++){ \
                swcast x = *p; \
                if (x!=swmtyp){ \
                    if(isnan((double)x) || isinf((double)x)){ \
                        *p = swmtyp; \
                    } \
                } \
            } \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in isAnyNanInf: undefined type %d!\n",X->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST
    return;
}

int isOutOfRange(arr *restrict X,typ_idx idx,void *min,void *max){
    switch (X->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,iswassign,swcompare,fmt1,fmt2)  \
        return ( (iswassign(X,idx) < *(swcast *)min) || (iswassign(X,idx) > *(swcast *)max) );
        ALLTYPECASES3
        default:
            fprintf(stderr,"Error in isOutOfRange: undefined type %d!\n",X->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST
}

/* Should probably step through pointer comparing to NaN Inf */
int isAnyOutOfRange(arr *restrict m,void *min,void *max){
    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        { \
            swcast *p     = pntr_of(m); \
            swcast swmtyp = *(swcast *)getMiss(m); \
            swcast min_c  = *(swcast *)min; \
            swcast max_c  = *(swcast *)max; \
            for(typ_idx i=0; i < m->tlen; ++i){ \
                swcast x = *p++; \
                if (x!=swmtyp){ \
                    if((x < min_c) || (x > max_c)){ \
                        return 1; \
                    } \
                } \
            } \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in isAnyOutOfRange: undefined type %d!\n",m->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST
    return 0;
}

/* Should probably step through pointer comparing to NaN Inf */
void setMissOutOfRange(arr *restrict X,void *min,void *max){
    switch (X->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        { \
            swcast *p     = pntr_of(X); \
            swcast swmtyp = *(swcast *)getMiss(X); \
            swcast min_c  = *(swcast *)min; \
            swcast max_c  = *(swcast *)max; \
            for(typ_idx i=0; i < X->tlen; ++i,p++){ \
                swcast x = *p; \
                if (x!=swmtyp){ \
                    if((x < min_c) || (x > max_c)){ \
                        *p = swmtyp; \
                    } \
                } \
            } \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in isAnyOutOfRange: undefined type %d!\n",X->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST
    return;
}

/* Can speed up significantly, and this is used a lot! */
arr removeMissing(arr *restrict X){
/*  intended for 1d, will convert nd to a 1d array with missing values removed  */
    arr m;
    typ_idx cnt  = 0;
    typ_idx tlen = X->tlen;
    arr missarr = Array(1, INT, tlen);
    int  *pmiss = pntr_of(&missarr);

    switch (X->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        { \
            swcast xmiss = *(swcast *)getMiss(X); \
            swcast *pin  = pntr_of(X);           \
            for(typ_idx i=0; i < tlen; ++i){     \
                if(*pin++ == xmiss){             \
                    *pmiss++ = 0;                \
                } else {                         \
                    *pmiss++ = 1;                \
                    cnt++;                       \
                }                                \
            }                                    \
                                                 \
            pmiss        = pntr_of(&missarr);    \
            m            = Array(1,swmacro,cnt); \
            copyMiss(&m,X); \
            pin          = pntr_of(X);           \
            swcast *pout = pntr_of(&m);              \
            for(typ_idx i=0; i < tlen; ++i,pin++){       \
                if(*pmiss++){                    \
                    *pout++ = *pin;              \
                }                                \
            } \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in removeMissing: undefined type %d!\n",X->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    freeAr(&missarr);

    return m;
}

/* Can speed up significantly, and this is used a lot! */
void removeMissingNArraysList(int narrs, arr **out_arrays, arr **arrays){
    typ_idx j;
    typ_idx i;

    /*  fputs("removeMissingNArraysList: 1\n",stderr);  */
    typ_idx inlen = 0;
    for (j=0;j<narrs;++j){
        if (j == 0){ inlen = arrays[j]->tlen; }
        if (arrays[j]->tlen != inlen) {
            fprintf(stderr,"Error in removeMissingNArraysList: arrays must be same length!\n");
            exit(0);
        }
    }

    typ_idx cnt = 0;
    arr missarr = Array(1,INT,inlen);
    int  *pmiss = pntr_of(&missarr);

    for(i=0;i<inlen;++i){
        *pmiss = 1;
        for (j=0;j<narrs;++j){
            if( isMiss(arrays[j],i) ){ *pmiss = 0; break;}
        }
        if (*pmiss++){ cnt++; }
    }

    for (j=0;j<narrs;++j){ /* Making this the outer loop will allow multitype filtering */
        switch (arrays[j]->typ) {
        #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
            { \
                *out_arrays[j] = Array(1,swmacro,cnt);     \
                copyMiss(out_arrays[j],arrays[j]);         \
                int    *pmiss = pntr_of(&missarr);         \
                swcast *pin   = pntr_of(arrays[j]);        \
                swcast *pout  = pntr_of(out_arrays[j]);    \
                for(i=0; i < inlen; ++i,pin++){            \
                    if(*pmiss++){                          \
                        *pout++ = *pin;                    \
                    }                                      \
                }                                          \
            }
            ALLTYPECASES
            default:
                fprintf(stderr,"Error in removeMissingNArraysList: undefined type %d!\n",arrays[j]->typ);
                exit(0);
                break;
        }
        #undef SWITCHCAST
    }

    freeAr(&missarr);

    return;
}

arr *removeMissingNArraysList_alloc(int narrs,arr **arrays){
    typ_idx i;
    arr  *out_arrays  = malloc(narrs*sizeof(arr));
    arr **par_cut = malloc(narrs*sizeof(arr *));
    for (i=0;i<narrs;++i){
        par_cut[i] = &out_arrays[i];
    }
    removeMissingNArraysList(narrs, par_cut, arrays);
    free(par_cut);
    return out_arrays;
}

void removeMissingNArrays(int narrs, ...){
    arr **arrays     = malloc(narrs*sizeof(arr *));
    arr **out_arrays = malloc(narrs*sizeof(arr *));

    int j;
    va_list arg_list;
    va_start(arg_list, narrs);
    for (j=0;j<narrs;++j){
        out_arrays[j] = va_arg(arg_list, arr *);
    }
    for (j=0;j<narrs;++j){
        arrays[j] = va_arg(arg_list, arr *);
    }
    va_end(arg_list);
    
    removeMissingNArraysList(narrs,out_arrays,arrays);

    free(arrays);
    free(out_arrays);

    return;
}

void removeMissing2Arrays(arr *m,arr *n,arr *restrict X,arr *restrict Y){
    int narrs=2;
    arr **out_arrays = malloc(narrs*sizeof(arr *));
    out_arrays[0] = m;
    out_arrays[1] = n;
    
    arr **arrays   = malloc(narrs*sizeof(arr *));
    arrays[0] = X;
    arrays[1] = Y;

    removeMissingNArraysList(narrs,out_arrays,arrays);

    free(arrays);
    free(out_arrays);

    return;
}

arr getMissingIdxs1Array(arr *array, typ_idx *cnt){
    typ_idx inlen = array->tlen;
    arr missarr   = ArrayFromList(array->n,INT,array->len);
    typ_idx i;
    *cnt = 0;
    for(i=0;i<inlen;++i){
        if (iINTG(&missarr,i) = !isMiss(array,i)){ (*cnt)++; }
    }

    return missarr;
}

arr getMissingIdxsNArraysList(int narrs, arr **arrays, typ_idx *cnt){
    int j;
    typ_idx i;

    /*  fputs("getMissingIdxsNArraysList: 1\n",stderr);  */
    typ_idx inlen = 0;
    for (j=0;j<narrs;++j){
        if (j == 0){ inlen = arrays[j]->tlen; }
        if (arrays[j]->tlen != inlen) {
            fprintf(stderr,"Error in getMissingIdxsNArraysList: arrays must be same length!\n");
            exit(0);
        }
    }

    *cnt = 0;
    arr missarr = Array(1,INT,inlen);

    for(i=0;i<inlen;++i){
        iINTG(&missarr,i) = 1;
        for (j=0;j<narrs;++j){
            if( isMiss(arrays[j],i) ){ iINTG(&missarr,i) = 0; }
        }
        if (iINTG(&missarr,i)){ (*cnt)++; }
    }

    return missarr;
}

arr getMissingIdxsNArrays(int narrs, typ_idx *cnt, ...){
    int j;
    arr **arrays      = malloc(narrs*sizeof(arr *));

    va_list arg_list;
    va_start(arg_list, cnt);
    for (j=0;j<narrs;++j){
        arrays[j] = va_arg(arg_list, arr *);
    }
    va_end(arg_list);
    
    arr missarr = getMissingIdxsNArraysList(narrs,arrays,cnt);

    free(arrays);
    return missarr;
}

typ_idx countNonMissNArraysList(int narrs, arr **arrays){
    int j;
    typ_idx i;

    /*  fputs("countNonMissNArraysList: 1\n",stderr);  */
    typ_idx inlen = 0;
    for (j=0;j<narrs;++j){
        if (j == 0){ inlen = arrays[j]->tlen; }
        if (arrays[j]->tlen != inlen) {
            fprintf(stderr,"Error in countNonMissNArraysList: arrays must be same length!\n");
            exit(0);
        }
    }

    typ_idx cnt = 0;
    for(i=0;i<inlen;++i){
        int ismiss = 1;
        for (j=0;j<narrs;++j){
            if( isMiss(arrays[j],i) ){ ismiss = 0; }
        }
        if (ismiss){ ++cnt; }
    }

    return cnt;
}

typ_idx countNonMissNArrays(int narrs, ...){
    int j;
    arr **arrays      = malloc(narrs*sizeof(arr *));

    va_list arg_list;
    va_start(arg_list, narrs);
    for (j=0;j<narrs;++j){
        arrays[j] = va_arg(arg_list, arr *);
    }
    va_end(arg_list);
    
    typ_idx cnt = countNonMissNArraysList(narrs,arrays);

    free(arrays);
    return cnt;
}

void removeMissingNArraysFromMissArList(typ_idx nnonmiss, arr *restrict missarr, int narrs, arr **out_arrays, arr **arrays){
    int j;
    typ_idx i;

    typ_idx cnt = 0;
    switch (arrays[0]->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,iswassign,swcompare,fmt1,fmt2)  \
        for (j=0;j<narrs;++j){                          \
            *out_arrays[j] = Array(1,swmacro,nnonmiss); \
            copyMiss(out_arrays[j],arrays[j]);          \
            cnt = 0;                                    \
            int *pmiss = pntr_of(missarr);              \
            for(i=0;i<arrays[j]->tlen;++i){             \
                if(*pmiss++){                           \
                    iswassign(out_arrays[j],cnt) = iswassign(arrays[j],i); \
                    cnt++;                              \
                }                                       \
            }                                           \
        }
        ALLTYPECASES3
        default:
            fprintf(stderr,"Error in removeMissingNArraysFromMissArList: undefined type %d!\n",arrays[0]->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return;
}

arr *removeMissingNArraysFromMissArList_alloc(typ_idx nnonmiss,arr *restrict missarr,int narrs,arr **arrays){
    int i;
    arr  *out_arrays = malloc(narrs*sizeof(arr));
    arr **par_cut    = malloc(narrs*sizeof(arr *));
    for (i=0;i<narrs;++i){
        par_cut[i] = &out_arrays[i];
    }
    removeMissingNArraysFromMissArList(nnonmiss, missarr, narrs, par_cut, arrays);
    free(par_cut);
    return out_arrays;
}

void removeMissingNArraysFromMissAr(typ_idx nnonmiss,arr *restrict missarr,int narrs, ...){
    int j;
    arr **arrays     = malloc(narrs*sizeof(arr *));
    arr **out_arrays = malloc(narrs*sizeof(arr *));

    va_list arg_list;
    va_start(arg_list, narrs);
    for (j=0;j<narrs;++j){
        out_arrays[j] = va_arg(arg_list, arr *);
    }
    for (j=0;j<narrs;++j){
        arrays[j] = va_arg(arg_list, arr *);
    }
    va_end(arg_list);
    
    removeMissingNArraysFromMissArList(nnonmiss,missarr,narrs,out_arrays,arrays);

    free(arrays);
    free(out_arrays);

    return;
}

int isMiss_Loop(arr *restrict IN, typ_idx missdim, typ_idx missidx, typ_idx dim, typ_idx *c, typ_idx *clens){
    typ_idx i;
    typ_idx *idx;
    int stat = 1;

    if (dim == IN->n-1){
        idx = init0(IN->n,TYPIDX);
        for(i=0;i<IN->n;++i){
            if (i < missdim){
                idx[i] = c[i];
            } else if (i == missdim){
                idx[i] = missidx;
            } else {
                idx[i] = c[i-1];
            }
        }
        if( isMissc(IN,idx) ){ free(idx); return 0; }
        free(idx);
        return 1;
    } else {
        for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
        /*  Uncomment to print loop counter c
            fputs("isMiss_Loop: ",stderr);
            for(j=0;j<=dim;++j){
                fprintf(stderr,"c[%lld]=%lld ",j,c[j]);
            }
            fputs("\n",stderr);
         */
            stat = isMiss_Loop(IN,missdim,missidx,dim+1,c,clens);
            if (!stat){ return 0; }
        }
    }
    return 1;
}

void assignNonMiss_Loop(arr *restrict OUT, arr *restrict IN, typ_idx OUTidx, typ_idx INidx, typ_idx missdim, typ_idx dim, typ_idx *c, typ_idx *clens){
    typ_idx i;
    typ_idx *idx_o,*idx_i;

    if (dim == IN->n-1){
        idx_o = init0(IN->n,TYPIDX);
        idx_i = init0(IN->n,TYPIDX);
        for(i=0;i<IN->n;++i){
            if (i < missdim){
                idx_o[i] = c[i];
                idx_i[i] = c[i];
            } else if (i == missdim){
                idx_o[i] = OUTidx;
                idx_i[i] = INidx;
            } else {
                idx_o[i] = c[i-1];
                idx_i[i] = c[i-1];
            }
        }
        switch (IN->typ) {
        #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
            cswassign(OUT,idx_o) = cswassign(IN,idx_i);
            ALLTYPECASES
            default:
                fprintf(stderr,"Error in assignNonMiss_Loop: undefined type %d!\n",IN->typ);
                exit(0);
                break;
        }
        #undef SWITCHCAST
        free(idx_o);
        free(idx_i);
        return;
    } else {
        for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
        /*  Uncomment to print loop counter c
            fputs("assignNonMiss_Loop: ",stderr);
            for(j=0;j<=dim;++j){
                fprintf(stderr,"c[%lld]=%lld ",j,c[j]);
            }
            fputs("\n",stderr);
         */
            assignNonMiss_Loop(OUT,IN,OUTidx,INidx,missdim,dim+1,c,clens);
        }
    }
    return;
}

arr RemoveIfAnyMissFromDim(arr *restrict IN, typ_idx statdim){
/*  fputs("RemoveIfAnyMissFromDim: 1\n",stderr);    */
    typ_idx i;

    typ_idx inlen = IN->len[statdim];

/*  fputs("RemoveIfAnyMissFromDim: 4\n",stderr);    */
    typ_idx cnt = 0;
    int missfill = 1;
    arr missarr = Array(1,INT,inlen);
    fillAr(&missarr, &missfill);

/*  fputs("RemoveIfAnyMissFromDim: 5\n",stderr);    */
    typ_idx *clens = init0((IN->n-1),TYPIDX);
    for (i=0;i<IN->n;++i){
        if (i < statdim){
            clens[i] = IN->len[i];
        } else if (i > statdim) {
            clens[i-1] = IN->len[i];
        }
    }
    typ_idx *c = init0(IN->n-1,TYPIDX);
    for(i=0;i<inlen;++i){
       iINTG(&missarr,i) = isMiss_Loop(IN,statdim,i,(typ_idx)0,c,clens);
        if (iINTG(&missarr,i)){ cnt++; }
    }

/*  fprintf(stderr,"RemoveIfAnyMissFromDim: 6 cnt = %lld\n",cnt);   */
    typ_idx *OUTlens = init0(IN->n,TYPIDX);
    for (i=0;i<IN->n;++i){
        if (i == statdim){
            OUTlens[i] = cnt;
        } else {
            OUTlens[i] = IN->len[i];
        }
    }

    arr OUT = ArrayFromList(IN->n,IN->typ,OUTlens);
    cnt = 0;
    for(i=0;i<inlen;++i){
        if(iINTG(&missarr,i)){
            assignNonMiss_Loop(&OUT,IN,cnt,i,statdim,(typ_idx)0,c,clens);
            cnt++;
        }
    }

/*  fputs("RemoveIfAnyMissFromDim: 7\n",stderr);    */
    freeAr(&missarr);
    free(OUTlens);
    free(clens);
    free(c);

/*  fputs("RemoveIfAnyMissFromDim: 8\n",stderr);    */
    return OUT;
}

arr FilterBetweenFromDim(arr *restrict IN, double lval, double hval, typ_idx statdim, typ_idx *cfilt){
/*  fputs("FilterBetweenFromDim: 1\n",stderr);  */
    typ_idx i;

    typ_idx inlen = IN->len[statdim];

/*  fputs("FilterBetweenFromDim: 2\n",stderr);  */
    typ_idx cnt = 0;
    int missfill = 1;
    arr missarr = Array(1,INT,inlen);
    fillAr(&missarr, &missfill);

/*  fputs("FilterBetweenFromDim: 3\n",stderr);  */
    typ_idx *clens = init0((IN->n-1),TYPIDX);
    for (i=0;i<IN->n;++i){
        if (i < statdim){
            clens[i] = IN->len[i];
        } else if (i > statdim) {
            clens[i-1] = IN->len[i];
        }
    }

/*  fputs("FilterBetweenFromDim: 4\n",stderr);  */
    typ_idx *idx = init0(IN->n,TYPIDX);
    for(i=0;i<IN->n;++i){
        if (i < statdim){
            idx[i] = cfilt[i];
        } else if (i == statdim) {
            idx[i] = 0;
        } else {
            idx[i] = cfilt[i-1];
        }
    }

    for(i=0;i<inlen;++i){
        idx[statdim] = i;
        iINTG(&missarr,i) = ( (cDBL(IN,idx) > lval) && (cDBL(IN,idx) < hval) );
        if (iINTG(&missarr,i)){ cnt++; }
    }

/*  fprintf(stderr,"FilterBetweenFromDim: 5 cnt = %lld\n",cnt); */
    typ_idx *OUTlens = init0(IN->n,TYPIDX);
    for (i=0;i<IN->n;++i){
        if (i == statdim){
            OUTlens[i] = cnt;
        } else {
            OUTlens[i] = IN->len[i];
        }
    }

    arr OUT = ArrayFromList(IN->n,IN->typ,OUTlens);
    typ_idx *c = init0(IN->n-1,TYPIDX);
    cnt = 0;
    for(i=0;i<inlen;++i){
        if(iINTG(&missarr,i)){
            assignNonMiss_Loop(&OUT,IN,cnt,i,statdim,(typ_idx)0,c,clens);
            cnt++;
        }
    }

/*  fputs("FilterBetweenFromDim: 6\n",stderr);  */
    freeAr(&missarr);
    free(OUTlens);
    free(clens);
    free(idx);
    free(c);

/*  fputs("FilterBetweenFromDim: 7\n",stderr);  */
    return OUT;
}

arr *FilterBetween1dArraysFromDim(arr **IN, int narrs, double lval, double hval, typ_idx filt_ar_idx){
/*  fputs("FilterBetween1dArraysFromDim: 1\n",stderr);  */
    int j;
    typ_idx i;
    arr *INdbl = malloc(narrs*sizeof(arr));
    for (i=0;i<narrs;++i){
        INdbl[i] = castAr(IN[i],DOUBLE,0);
    }

    typ_idx inlen = INdbl[0].tlen;

/*  fputs("FilterBetween1dArraysFromDim: 2\n",stderr);  */
    typ_idx cnt = 0;
    int missfill = 1;
    arr missarr = Array(1,INT,inlen);
    fillAr(&missarr, &missfill);

/*  fputs("FilterBetween1dArraysFromDim: 3\n",stderr);  */
    for(i=0;i<inlen;++i){
        iINTG(&missarr,i) = ( (iDBL(&INdbl[filt_ar_idx],i) > lval) && (iDBL(&INdbl[filt_ar_idx],i) < hval) );
        if (iINTG(&missarr,i)){ cnt++; }
    }

/*  fprintf(stderr,"FilterBetween1dArraysFromDim: 4 cnt = %lld\n",cnt); */
    arr *OUT = malloc(narrs*sizeof(arr));
    for (i=0;i<narrs;++i){
        OUT[i] = Array(1,DOUBLE,cnt);
        copyMiss(&OUT[i],&INdbl[i]);
    }

/*  fputs("FilterBetween1dArraysFromDim: 5\n",stderr);  */
    cnt = 0;
    for(i=0;i<inlen;++i){
        if(iINTG(&missarr,i)){
            for(j=0;j<narrs;++j){
                iDBL(&OUT[j],cnt) = iDBL(&INdbl[j],i);
            }
            cnt++;
        }
    }

/*  fputs("FilterBetween1dArraysFromDim: 6\n",stderr);  */
    freeAr(&missarr);
    for (i=0;i<narrs;++i){
        freeAr(&INdbl[i]);
    }
    free(INdbl);

/*  fputs("FilterBetween1dArraysFromDim: 7\n",stderr);  */
    return OUT;
}

void filter2Arrays(double lo,double hi,arr *m,arr *n,arr *restrict X,arr *restrict Y){
/*  filter criteria only applies to Y   */
    if ((X->n != 1) || (Y->n != 1)){
        fprintf(stderr,"Error in filter2Arrays only accepts one dimensional arrays! \n");
        exit(0);
    }
    if (X->tlen != Y->tlen) { fprintf(stderr,"Error in filter2Arrays: arrays must be same length!\n"); }

    typ_idx i,cnt = 0;
    arr missarr = Array(1,INT,X->tlen);

    switch (Y->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pY = pntr_of(Y); \
        int *pmiss = pntr_of(&missarr); \
        for(i=0;i<Y->tlen;++i){                               \
            if( (*pY > (swcast)lo) && (*pY++ < (swcast)hi) ){ \
                *pmiss++ = 1;                                 \
                cnt++;                                        \
            } else {                                          \
                *pmiss++ = 0;                                 \
            }                                                 \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in filter2Arrays: undefined type %d!\n",Y->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    switch (X->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pX = pntr_of(X); \
        int *pmiss = pntr_of(&missarr); \
        *m = Array(1,swmacro,cnt);      \
        copyMiss(m,X);                  \
        swcast *p  = pntr_of(m);        \
        for(i=0; i<X->tlen; ++i,pX++){  \
            if(*pmiss++){               \
                *p++ = *pX;             \
            }                           \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in filter2Arrays: undefined type %d!\n",X->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    switch (Y->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pY = pntr_of(Y); \
        int *pmiss = pntr_of(&missarr); \
        *n = Array(1,swmacro,cnt);      \
        copyMiss(n,Y);                  \
        swcast *p  = pntr_of(n);        \
        for(i=0; i<Y->tlen; ++i,pY++){  \
            if(*pmiss++){               \
                *p++ = *pY;             \
            }                           \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in filter2Arrays: undefined type %d!\n",Y->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    freeAr(&missarr);

    return;
}

void filter3Arrays(double y_thrsh,double z_thrsh,arr *m,arr *n,arr *o,arr *restrict Xin,arr *restrict Yin,arr *restrict Zin){
/*  filter criteria only applies to Y   */
    if ((Xin->n != 1) || (Yin->n != 1) || (Zin->n != 1)){
        fprintf(stderr,"Error in filter3Arrays only accepts one dimensional arrays! \n");
        exit(0);
    }
    if (Xin->tlen != Yin->tlen) { fprintf(stderr,"Error in filter3Arrays: arrays must be same length!\n"); }

    typ_idx i,cnt = 0;
    arr X = castAr(Xin,DOUBLE,0);
    arr Y = castAr(Yin,DOUBLE,0);
    arr Z = castAr(Zin,DOUBLE,0);

    arr missarr = Array(1,INT,X.tlen);
    int *pmiss = pntr_of(&missarr);

    for(i=0;i<Y.tlen;++i){
        if( (iDBL(&Y,i) > y_thrsh) && (iDBL(&Z,i) > z_thrsh) ){
            *pmiss++ = 1;
            cnt++;
        } else {
            *pmiss++ = 0;
        }
    }

    *m = Array(1,DOUBLE,cnt);
    *n = Array(1,DOUBLE,cnt);
    *o = Array(1,DOUBLE,cnt);
    copyMiss(m,&X);
    copyMiss(n,&Y);
    copyMiss(o,&Z);
    double *pm = pntr_of(m);
    double *pn = pntr_of(n);
    double *po = pntr_of(o);
    double *pX = pntr_of(&X);
    double *pY = pntr_of(&Y);
    double *pZ = pntr_of(&Z);
    pmiss      = pntr_of(&missarr);

    for(i=0; i<X.tlen; ++i,pX++,pY++,pZ++){
        if(*pmiss++){
            *pm++ = *pX;
            *pn++ = *pY;
            *po++ = *pZ;
        }
    }

    freeAr(&missarr);
    freeAr(&X);
    freeAr(&Y);
    freeAr(&Z);

    return;
}

/* Changed to speed up, should test! */
void setToValGT(arr *restrict m,double condval){
    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        { \
            swcast *p    = pntr_of(m); \
            swcast mmiss = *(swcast *)getMiss(m);  \
            for(typ_idx i=0; i < m->tlen; ++i,p++){ \
                if(*p > condval){ *p = mmiss; }     \
            } \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in setToValGT: undefined type %d!\n",m->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST
    return;
}

/* Changed to speed up, should test! */
double sumAllAr(arr *restrict X){
    typ_idx i;
    double sum;

    switch (X->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        { \
            swcast *p    = pntr_of(X);      \
            swcast Xmiss = *(swcast *)getMiss(X);       \
            swcast swsum = 0;               \
            for(i=0; i < X->tlen; ++i,p++){ \
                if (*p != Xmiss){           \
                    swsum += *p;            \
                }                           \
            } \
            sum = (double)swsum; \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in sumAllAr: undefined type %d!\n",X->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST
    return sum;
}

arr grabSlice(arr *restrict in, typ_idx dim, typ_idx idx){
    if ((in->n <= dim) || (dim < 0)){
        fprintf(stderr,"Error in grabSlice: Invalid dimension as 2nd argument! in->n=%lld, dim=%lld\n",in->n,dim);
        exit(0);
    }
    typ_idx i;

    typ_idx *lo = malloc(in->n*sizeof(typ_idx));
    typ_idx *hi = malloc(in->n*sizeof(typ_idx));
    for (i=0;i<in->n;++i){ lo[i] = 0; hi[i] = in->len[i]-1; }
    lo[dim]=idx;
    hi[dim]=idx;

    arr m = grabSect(in,lo,hi);

    free(lo);
    free(hi);

    return m;
}

arr grab1dAr(arr *restrict in, typ_idx dim, typ_idx *idx){
    if (in->n == 1){
        return copyAr(in);
    }
    if ((in->n <= dim) || (dim < 0)){
        fprintf(stderr,"Error in grab1dAr: Invalid dimension as 2nd argument! in->n=%lld, dim=%lld\n",in->n,dim);
        exit(0);
    }
    typ_idx k;

    arr m = Array(1, in->typ, in->len[dim]);
    copyMiss(&m,in);

    switch (m.typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *p = pntr_of(&m); \
        for(k=0;k<m.tlen;++k){         \
            idx[dim] = k;              \
            *p++ = cswassign(in,idx);  \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in grab1dAr: undefined type %d!\n",m.typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return m;
}

arr grab2dAr(arr *restrict in, typ_idx dimy, typ_idx dimx, typ_idx *idx){
    if (in->n == 2){
        return copyAr(in);
    }
    if ((in->n <= dimy) || (dimy < 0)){
        fprintf(stderr,"Error in grab2dAr: Invalid dimension as 2nd argument! in->n=%lld, dimy=%lld\n",in->n,dimy);
        exit(0);
    }
    if ((in->n <= dimx) || (dimx < 0)){
        fprintf(stderr,"Error in grab2dAr: Invalid dimension as 3rd argument! in->n=%lld, dimx=%lld\n",in->n,dimx);
        exit(0);
    }
    typ_idx j,i;

    arr m = Array(2, in->typ, in->len[dimy], in->len[dimx]);
    copyMiss(&m,in);

    switch (m.typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        for(j=0;j<m.len[0];++j){                \
        for(i=0;i<m.len[1];++i){                \
            idx[dimy] = j;                  \
            idx[dimx] = i;                  \
            swassign(&m,j,i) = cswassign(in,idx);   \
        }                               \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in grab2dAr: undefined type %d!\n",m.typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return m;
}

arr grabNdAr(arr *restrict IN, typ_idx n_adims, typ_idx *adims, typ_idx *idx){
    typ_idx i;
    /*
    if (IN->n == n_adims){
        return copyAr(IN);
    }
    */
    if (n_adims > IN->n){
        fprintf(stderr,"Error in grabNdAr: n_adams must be less than or equal to IN->n! IN->n=%lld, n_adims=%lld\n",IN->n,n_adims);
        exit(0);
    }
    for(i=0;i<n_adims;++i){
        if ((adims[i] < 0) || (IN->n <= adims[i])){
            fprintf(stderr,"Error in grabNdAr: Invalid dimension as 3rd argument! IN->n=%lld, adims[%lld]=%lld\n",IN->n,i,adims[i]);
            exit(0);
        }
    }

    typ_idx *lens = init0(n_adims,TYPIDX);
    for(i=0;i<n_adims;++i){
        lens[i] = IN->len[adims[i]];
    }
    arr OUT = ArrayFromList(n_adims, IN->typ, lens);
    copyMiss(&OUT,IN);
    /*
    printArrayInfoWHdr(stderr, IN,  "grabNdAr: IN  - ");
    printArrayInfoWHdr(stderr, OUT, "grabNdAr: OUT - ");
    */
    typ_idx *c = init0(OUT.n,TYPIDX);
    grabNdAr_Loop(&OUT,IN,adims,idx,(typ_idx)0,c);

    free(c);
    free(lens);
    return OUT;
}

/* Changed to speed up, should test! */
void grabNdAr_Loop(arr *restrict OUT, arr *restrict IN, typ_idx *adims, typ_idx *idx, typ_idx dim, typ_idx *c){
    if (dim == OUT->n){
        switch (OUT->typ) {
        #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
            cswassign(OUT,c) = cswassign(IN,idx);
            ALLTYPECASES
            default:
                fprintf(stderr,"Error in grabNdAr: undefined type %d!\n",OUT->typ);
                exit(0);
                break;
        }
        #undef SWITCHCAST
        return;
    } else {
        /* typ_idx cadim = adims[dim]; */
        typ_idx *pidx = &idx[adims[dim]];
        typ_idx *pc   = &c[dim];
        typ_idx dlen  = OUT->len[dim];
        for(*pc=0; *pc < dlen; (*pc)++){
        /*  Uncomment to print loop counter c
            typ_idx j;
            fputs("grabNdAr_Loop: ",stderr);
            for(j=0;j<=dim;++j){
                fprintf(stderr,"c[%lld]=%lld ",j,c[j]);
            }
            fputs("\n",stderr);
         */
            /* idx[cadim] = c[dim]; */
            *pidx = *pc;
            grabNdAr_Loop(OUT,IN,adims,idx,dim+1,c);
        }
    }

    return;
}


/* Changed to speed up, should test! */
void grabNdAr_NStride_Loop(void *pOUT, void *pIN, typ_typ typ, typ_idx ndims, typ_idx *nstride, typ_idx *mstride, typ_idx *olen, typ_idx dim, typ_idx *c){
    if (dim == ndims){
        switch (typ) {
        #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
            *(swcast *)pOUT = *(swcast *)pIN;
            ALLTYPECASES
            default:
                fprintf(stderr,"Error in grabNdAr_NStride: undefined type %d!\n",typ);
                exit(0);
                break;
        }
        #undef SWITCHCAST
        return;
    } else {
        typ_idx *pc   = &c[dim];
        typ_idx dlen  = olen[dim];
        switch (typ) {
        #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
            for(*pc=0; *pc < dlen; (*pc)++){                        \
                grabNdAr_NStride_Loop(pOUT,pIN,typ,ndims,nstride,mstride,olen,dim+1,c); \
                pOUT = ((swcast*)pOUT) + mstride[dim];                        \
                pIN  = ((swcast*)pIN)  + nstride[dim];             \
            }
            ALLTYPECASES
            default:
                fprintf(stderr,"Error in grabNdAr_NStride: undefined type %d!\n",typ);
                exit(0);
                break;
        }
        #undef SWITCHCAST
        return;
    }

    return;
}

arr grabNdAr_NStride(arr *restrict IN, typ_idx n_adims, typ_idx *adims, typ_idx *idx){
    typ_idx i;
    if (n_adims > IN->n){
        fprintf(stderr,"Error in grabNdAr_NStride: n_adams must be less than or equal to IN->n! IN->n=%lld, n_adims=%lld\n",IN->n,n_adims);
        exit(0);
    }
    for(i=0;i<n_adims;++i){
        if ((adims[i] < 0) || (IN->n <= adims[i])){
            fprintf(stderr,"Error in grabNdAr_NStride: Invalid dimension as 3rd argument! IN->n=%lld, adims[%lld]=%lld\n",IN->n,i,adims[i]);
            exit(0);
        }
    }

    typ_idx *lens = init0(n_adims,TYPIDX);
    for(i=0;i<n_adims;++i){
        lens[i] = IN->len[adims[i]];
    }
    arr OUT = ArrayFromList(n_adims, IN->typ, lens);
    copyMiss(&OUT,IN);

    typ_idx *nstride = init0(n_adims,TYPIDX);
    // typ_idx nstride[8] = { 0 };
    if (nstride){
        i = n_adims-1;
        nstride[i] = IN->mlen[adims[i]];
        for(--i; i>=0; --i){
            nstride[i] = IN->mlen[adims[i]];
        }
    }
    
    typ_idx *c = init0(OUT.n,TYPIDX);
    grabNdAr_NStride_Loop(pntr_of(&OUT),address_of_c(IN,idx),OUT.typ,n_adims,nstride,OUT.mlen,lens,(typ_idx)0,c);

    free(nstride);
    free(c);
    free(lens);
    return OUT;
}


void fillArColWith1d(arr *restrict m,arr *restrict ar1d,typ_idx dim,typ_idx *idx){
    if (ar1d->n != 1){
        fprintf(stderr,"Error in fillArColWith1d: 2nd argument must be one dimensional! \n");
        exit(0);
    }
    if ((m->n <= dim) || (dim < 0)){
        fprintf(stderr,"Error in fillArColWith1d: Invalid dimension as 3rd argument! m->n=%lld, dim=%lld\n",m->n,dim);
        exit(0);
    }
    if (m->len[dim] != ar1d->tlen){
        fprintf(stderr,"Error in fillArColWith1d: Dimension length mismatch!\n"
                           "\tm->len[%lld]=%lld, ar1d->len[0]=%lld\n",dim,m->len[dim],ar1d->len[0]);
        exit(0);
    }
    typ_idx k;

    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *par1d = pntr_of(ar1d);\
        for(k=0;k<ar1d->tlen;++k){             \
            idx[dim] = k;                      \
            cswassign(m,idx) = *par1d++; \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in fillArColWith1d: undefined type %d!\n",m->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return;
}

void fillArColWithVal(arr *restrict m,void *x,typ_idx dim,typ_idx *idx){
    if ((m->n <= dim) || (dim < 0)){
        fprintf(stderr,"Error in fillArColWithVal: Invalid dimension as 3rd argument! m->n=%lld, dim=%lld\n",m->n,dim);
        exit(0);
    }
    typ_idx k;

    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        for(k=0;k<m->len[dim];++k){             \
            idx[dim] = k;                   \
            cswassign(m,idx) = *(swcast *)x;        \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in fillArColWithVal: undefined type %d!\n",m->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return;
}

void fillArColWithMiss(arr *restrict m,typ_idx dim,typ_idx *idx){
    if ((m->n <= dim) || (dim < 0)){
        fprintf(stderr,"Error in fillArColWithMiss: Invalid dimension as 2nd argument! m->n=%lld, dim=%lld\n",m->n,dim);
        exit(0);
    }
    typ_idx k;

    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        for(k=0;k<m->len[dim];++k){         \
            idx[dim] = k;               \
            cswassign(m,idx) = *(swcast *)getMiss(m);       \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in fillArColWithMiss: undefined type %d!\n",m->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return;
}


void removeOneElemDims(arr *m){
    if (m->tlen == 1) {
        if (m->n > 0) {
            reshapeArList(m,0,NULL);
        }
    } else {
        typ_idx *newlen  = malloc(m->n*sizeof(typ_idx));
        typ_idx i, cnt = 0;
        for (i=0; i < m->n; i++) {
            if (m->len[i] != 1) {
                newlen[cnt] = m->len[i];
                cnt++;
            }
        }
        reshapeArList(m,cnt,newlen);
    }
    return;
}

arr reverseDim(arr *restrict in, typ_idx revdim){
    if (in->n <= revdim){
        fprintf(stderr,"Error in reverseDim: Invalid dimension as 2nd argument! in->n = %lld, revdim = %lld\n",in->n,revdim);
        exit(0);
    }


    arr m = copyAr(in);

    typ_idx *c = init0(m.n,TYPIDX);
    reverseDimLoop(&m,in,revdim,(typ_idx)0,c);

    free(c);
    return m;
}

    /*  Used only in reverseDim */
    void reverseDimLoop(arr *restrict m, arr *restrict in, typ_idx revdim, typ_idx dim, typ_idx *c){
        typ_idx *idx;
        typ_idx i;

        if (dim == m->n){
            idx = init0(m->n,TYPIDX);
            for(i=0;i<m->n;++i){ idx[i] = c[i]; }
            /*  reverse index for revdims (if c[j] = 0 then idx[j] = jmax)  */
            idx[revdim] = in->len[revdim]-1-c[revdim];
            switch (m->typ) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                cswassign(m,idx) = cswassign(in,c); 
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in reverseDimLoop: undefined type %d!\n",m->typ);
                    exit(0);
                    break;
            }
            #undef SWITCHCAST
            free(idx);
            return;
        } else {
            for(c[dim]=0;c[dim]<m->len[dim];c[dim]++){
                reverseDimLoop(m,in,revdim,dim+1,c);
            }
        }

        return;
    }

    

arr grabSect(arr *restrict in, typ_idx *lo, typ_idx *hi){
    typ_idx i;

    typ_idx *outlen = malloc(in->n*sizeof(typ_idx));
    for (i=0;i<in->n;++i){ outlen[i] = hi[i]-lo[i]+1; }

    arr m = ArrayFromList(in->n, in->typ, outlen);
    copyMiss(&m,in);

    typ_idx *c   = init0(m.n,TYPIDX);
    typ_idx *idx = init0(m.n,TYPIDX);
    grabSectLoop(&m,in,lo,hi,(typ_idx)0,c,idx);

    removeOneElemDims(&m);

    free(c);
    free(idx);
    free(outlen);
    return m;
}

    /*  Used only in grabSect   */
/* Changed to speed up, should test! */
    void grabSectLoop(arr *restrict m, arr *restrict in, typ_idx *lo, typ_idx *hi, typ_idx dim, typ_idx *c, typ_idx *idx){
        if (dim == m->n){
            /* for(i=0;i<m->n;++i){ idx[i] = c[i]-lo[i]; } */
            switch (m->typ) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                cswassign(m,idx) = cswassign(in,c); 
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in grabSectLoop: undefined type %d!\n",m->typ);
                    exit(0);
                    break;
            }
            #undef SWITCHCAST
            return;
        } else {
            typ_idx *pidx = &idx[dim];
            typ_idx *pc   = &c[dim];
            typ_idx  clo  =  lo[dim];
            typ_idx  chi  =  hi[dim];
            for(*pc=clo;*pc<=chi;(*pc)++){
                *pidx = *pc-clo;
                grabSectLoop(m,in,lo,hi,dim+1,c,idx);
            }
        }

        return;
    }



arr grabThinnedArray(arr *restrict in, typ_idx *sk){
    typ_idx i;

/*  fprintf(stderr,"in->n=%lld\n",in->n);   */
    typ_idx *outlen = malloc(in->n*sizeof(typ_idx));
    for (i=0;i<in->n;++i){ 
        outlen[i] = (in->len[i]+sk[i]-1)/sk[i];
    /*  fprintf(stderr,"outlen[%lld]=%lld\n",i,outlen[i]);  */
    }

    arr m = ArrayFromList(in->n, in->typ, outlen);
    copyMiss(&m,in);

    typ_idx *c = init0(m.n,TYPIDX);
    grabThinnedArrayLoop(&m,in,sk,(typ_idx)0,c);

    removeOneElemDims(&m);

    free(c);
    free(outlen);
    return m;
}

    /*  Used only in grabThinnedArray   */
    void grabThinnedArrayLoop(arr *restrict m, arr *restrict in, typ_idx *sk, typ_idx dim, typ_idx *c){
        typ_idx *idx;
        typ_idx i;
        
        if (dim == m->n){
            idx = init0(m->n,TYPIDX);
            for(i=0;i<m->n;++i){ idx[i] = c[i]*sk[i]; }
            switch (m->typ) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                cswassign(m,c) = cswassign(in,idx); 
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in grabThinnedArrayLoop: undefined type %d!\n",m->typ);
                    exit(0);
                    break;
            }
            #undef SWITCHCAST
            free(idx);
            return;
        } else {
            for(c[dim]=0;c[dim]<m->len[dim];c[dim]++){
                grabThinnedArrayLoop(m,in,sk,dim+1,c);
            }
        }

        return;
    }

arr grabSectThinned(arr *restrict IN, typ_idx *lo, typ_idx *hi, typ_idx *sk){
    arr m;
    arr arrtmp = grabSect(IN, lo, hi);
/*  printArrayAllWHdr(stderr,&arrtmp,"arrtmp\n",3); */
    if (sk) {
        typ_idx k, l=0;
        typ_idx maxn = IN->n;
        for (k=0; k < maxn; k++) {
            while ((hi[l] - lo[l] == 0) && (l < IN->n)) {
                /*  This removes 1-element dimensions from lo, hi, and sk
                 *  that were removed from IN to create arrtmp.
                 */
                l++;
                maxn--;
            }
            /*  if (l > maxn) { break; }    */
            lo[k] = lo[l];
            hi[k] = hi[l];
            sk[k] = sk[l];
            l++;
        }
        /*  fputs("Thinning Array\n",stderr);   */
        m = grabThinnedArray(&arrtmp, sk);
        freeAr(&arrtmp);
    } else {
        m = arrtmp;
        /* m = copyAr(&arrtmp); */
        /* freeAr(&arrtmp);     */
    }
    return m;
}

/* Changed to speed up, should test! */
/* - do I need to put (*psum) += *pinc; instead? */
void sumIncAr(arr *sum, arr *inc){
    if (sum->tlen != inc->tlen){
        fprintf(stderr,"Error in sumIncAr: both arrays must have same number of total elements!\n"
                           "\tsum->tlen=%lld, inc->tlen=%lld\n",sum->tlen,inc->tlen);
        exit(0);
    }

    switch (sum->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        { \
            swcast sum_miss = *(swcast *)getMiss(sum); \
            swcast inc_miss = *(swcast *)getMiss(inc); \
            swcast *psum    = pntr_of(sum); \
            swcast *pinc    = pntr_of(inc); \
            for(typ_idx i=0; i<sum->tlen; ++i,psum++,pinc++){      \
                if ((*psum == sum_miss) || (*pinc == inc_miss)){ \
                } else {                               \
                    *psum += *pinc;    \
                }                                      \
            } \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in sumIncAr: undefined type %d!\n",sum->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return; 
}


void expandDims(arr *A,typ_idx *outlen){
    typ_idx i;
    typ_idx outtlen = 1;
    for(i=0;i<A->n;++i){ outtlen *= outlen[i]; }
    
    if (A->tlen == outtlen){
        return; /* No change to array */
    }
    
    typ_idx *clens = init0(A->n,TYPIDX);
    for(i=0;i<A->n;++i){
        clens[i] = amin2(outlen[i],A->len[i]);
    }

    arr Acopy = copyAr(A);
    freeAr(A);
    *A = ArrayFromList(Acopy.n,Acopy.typ,outlen);
    copyMiss(A,&Acopy);
    fillArWithMiss(A);
    
    typ_idx *c = init0(A->n,TYPIDX);
    expandDims_loop(A,&Acopy,(typ_idx)0,c,clens);
    
    free(c);
    free(clens);
    freeAr(&Acopy);
    return;
}

    /*  Used only in expandDims */
    void expandDims_loop(arr *restrict OUT, arr *restrict IN, typ_idx dim, typ_idx *c, typ_idx *clens){
        if (dim == OUT->n){
            if(isMissc(IN,c)){
                setToMissc(OUT,c);
            } else {
                switch (OUT->typ) {
                #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                    cswassign(OUT,c) = cswassign(IN,c);
                    ALLTYPECASES
                    default:
                        fprintf(stderr,"Error in expandDims_loop: undefined type %d!\n",OUT->typ);
                        exit(0);
                        break;
                }
                #undef SWITCHCAST
            }
            return;
        } else {
            for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
                expandDims_loop(OUT,IN,dim+1,c,clens);
            }
        }
        return;
    }
    

void assignSect(arr *restrict to, typ_idx *lo_to, typ_idx *hi_to, arr *restrict fro, typ_idx *lo, typ_idx *hi){
    typ_idx i=0,j=0,k=0;

/*    printArrayInfoWHdr(stderr,to,"to - "); */
/*    printArrayInfoWHdr(stderr,fro,"fro - "); */
/*    for(i=0;i<to->n; i++){ fprintf(stderr,"to[%lld] : lo=%lld, hi=%lld\n",i,lo_to[i],hi_to[i]); } */
/*    for(i=0;i<fro->n;++i){ fprintf(stderr,"fro[%lld]: lo=%lld, hi=%lld\n",i,lo[i],hi[i]); } */
    typ_idx ndims     = imin(to->n,fro->n);
    typ_idx *idx_to   = NULL;
    typ_idx *idx_fro  = NULL;
    typ_idx *clen     = NULL;
    typ_idx *dims_to  = NULL;
    typ_idx *dims_fro = NULL;
    typ_idx len_to  = 0;
    typ_idx len_fro = 0;

    if (to->n > 0){
        idx_to  = malloc(to->n *sizeof(typ_idx));
        for(i=0;i<to->n;++i){  idx_to[i] =lo_to[i]; }
    }
    
    if (fro->n > 0){
        idx_fro = malloc(fro->n*sizeof(typ_idx));
        for(i=0;i<fro->n;++i){ idx_fro[i]=lo[i];    }
    }
    
    i=0;
    if (ndims > 0){
        clen     = malloc(to->n*sizeof(typ_idx));
        dims_to  = malloc(ndims*sizeof(typ_idx));
        dims_fro = malloc(ndims*sizeof(typ_idx));
        len_to   = hi_to[i] - lo_to[i];
        len_fro  = hi[j]    - lo[j];
        while (i<to->n){
            if (len_to){
                if (len_fro){
                    if (len_to==len_fro){
                        clen[k]     = len_to+1;
                        dims_to[k]  = i;
                        dims_fro[k] = j;
                        i++; j++; k++;
                        if (i == to->n) { break; }
                        len_to  = hi_to[i] - lo_to[i];
                        if (j == fro->n) { j = 0; }
                        len_fro = hi[j]    - lo[j];
                    } else {
                        j++;
                        if (j == fro->n) { j = 0; }
                        len_fro = hi[j] - lo[j];
                    }
                } else {
                    j++;
                    if (j == fro->n) { j = 0; }
                    len_fro = hi[j] - lo[j];
                }
            } else {
                i++;
                len_to = hi_to[i] - lo_to[i];
            }
        }
        ndims = k;
    }

/*    fprintf(stderr,"ndims = %lld\n",ndims); */
/*    for(i=0;i<ndims;++i){ fprintf(stderr,"to[%lld] : dims=%lld, idx=%lld\n",i,dims_to[i], idx_to[i] ); } */
/*    for(i=0;i<ndims;++i){ fprintf(stderr,"fro[%lld]: dims=%lld, idx=%lld\n",i,dims_fro[i],idx_fro[i]); } */

    typ_idx *c = init0(ndims,TYPIDX);
    assignSectLoop(to,lo_to,hi_to,fro,lo,hi,dims_to,dims_fro,idx_to,idx_fro,ndims,(typ_idx)0,c,clen);

    free(c);
    free(clen);
    free(idx_to);
    free(idx_fro);
    free(dims_to);
    free(dims_fro);
    return;
}

    /*  Used only in assignSect */
/* Changed to speed up, should test! */
    void assignSectLoop(arr *restrict to,typ_idx *lo_to,typ_idx *hi_to,arr *restrict fro,typ_idx *lo_fro,typ_idx *hi_fro,
        typ_idx *dims_to,typ_idx *dims_fro,typ_idx *idx_to,typ_idx *idx_fro,
        typ_idx ndims,typ_idx dim,typ_idx *c,typ_idx *clen){
        
        if (dim == ndims){
        /*  Uncomment to print loop counter c
            typ_idx j;
            fputs("assignSectLoop: ",stderr);
            fputs("to[",stderr);
            for(j=0;j<to->n-1;++j){
                fprintf(stderr,"%lld,",idx_to[j]);
            }
            fprintf(stderr,"%lld] = ",idx_to[dim-1]);
            fputs("fro[",stderr);
            for(j=0;j<fro->n-1;++j){
                fprintf(stderr,"%lld,",idx_fro[j]);
            }
            fprintf(stderr,"%lld]",idx_fro[dim-1]);
            fputs("\n",stderr);
         */

            switch (to->typ) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                if (isMissc(fro,idx_fro)){ \
                    setToMissc(to,idx_to); \
                } else { \
                    cswassign(to,idx_to) = cswassign(fro,idx_fro);  \
                }
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in assignSectLoop: undefined type %d!\n",to->typ);
                    exit(0);
                    break;
            }
            #undef SWITCHCAST
            return;
        } else {
            typ_idx  dto      = dims_to[dim];
            typ_idx  dfro     = dims_fro[dim];
            typ_idx *pc       = &c[dim];
            typ_idx *pidx_fro = &idx_fro[dfro];
            typ_idx *pidx_to  = &idx_to[dto];
            for(
                *pc=0, *pidx_to=lo_to[dto], *pidx_fro=lo_fro[dfro];
                *pc < clen[dim];
                (*pc)++, (*pidx_to)++, (*pidx_fro)++
                ){
                assignSectLoop(to,lo_to,hi_to,fro,lo_fro,hi_fro,
                    dims_to,dims_fro,idx_to,idx_fro,
                    ndims,dim+1,c,clen);
            }
        }

        return;
    }


/* No regards to dimension, just fill total array as if 1-d */
void assignSect1d(arr *restrict to, typ_idx lo_to, typ_idx hi_to, arr *restrict fro, typ_idx lo_fro, typ_idx hi_fro){
    typ_idx ito  = lo_to ;
    typ_idx ifro = lo_fro;

    for(;ito<=hi_to;++ito,++ifro){
        switch (to->typ) {
        #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
            if (isMiss(fro,ifro)){ \
                setToMiss(to,ito); \
            } else { \
                to->ud.swtyp[ito] = fro->ud.swtyp[ifro]; \
            }
            ALLTYPECASES
            default:
                fprintf(stderr,"Error in assignSect1d: undefined type %d!\n",to->typ);
                exit(0);
                break;
        }
        #undef SWITCHCAST
    }
    return;
}


void fillSect(arr *restrict to, typ_idx *lo_to, typ_idx *hi_to, void *x){
    typ_idx i=0,k=0;

/*    printArrayInfoWHdr(stderr,to,"to - "); */
/*    for(i=0;i<to->n; i++){ fprintf(stderr,"to[%lld] : lo=%lld, hi=%lld\n",i,lo_to[i],hi_to[i]); } */
    typ_idx ndims     = to->n;
    typ_idx *idx_to   = NULL;
    typ_idx *clen     = NULL;
    typ_idx *dims_to  = NULL;
    typ_idx len_to  = 0;

    if (to->n > 0){
        idx_to  = malloc(to->n *sizeof(typ_idx));
        for(i=0;i<to->n;++i){  idx_to[i] =lo_to[i]; }
    }
    
    i=0;
    if (ndims > 0){
        clen     = malloc(to->n*sizeof(typ_idx));
        dims_to  = malloc(ndims*sizeof(typ_idx));
        len_to   = hi_to[i] - lo_to[i];
        while (i<to->n){
            if (len_to){
                clen[k]     = len_to+1;
                dims_to[k]  = i;
                i++; k++;
                if (i == to->n) { break; }
            } else {
                i++;
            }
            len_to  = hi_to[i] - lo_to[i];
        }
        ndims = k;
    }

/*    fprintf(stderr,"ndims = %lld\n",ndims); */
/*    for(i=0;i<ndims;++i){ fprintf(stderr,"to[%lld] : dims=%lld, idx=%lld\n",i,dims_to[i], idx_to[i] ); } */

    typ_idx *c = init0(ndims,TYPIDX);
    fillSectLoop(to,lo_to,hi_to,x,dims_to,idx_to,ndims,(typ_idx)0,c,clen);

    free(c);
    free(clen);
    free(idx_to);
    free(dims_to);
    return;
}

    /*  Used only in fillSect   */
/* Changed to speed up, should test! */
    void fillSectLoop(arr *restrict to,typ_idx *lo_to,typ_idx *hi_to,void *x,
        typ_idx *dims_to,typ_idx *idx_to,typ_idx ndims,typ_idx dim,typ_idx *c,typ_idx *clen){
        
        if (dim == ndims){
        /*  Uncomment to print loop counter c
            typ_idx j;
            fputs("fillSectLoop: ",stderr);
            fputs("to[",stderr);
            for(j=0;j<to->n-1;++j){
                fprintf(stderr,"%lld,",idx_to[j]);
            }
            fprintf(stderr,"%lld] = ",idx_to[dim-1]);
            fputs("\n",stderr);
         */

            switch (to->typ) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                cswassign(to,idx_to) = *(swcast *)x;
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in fillSectLoop: undefined type %d!\n",to->typ);
                    exit(0);
                    break;
            }
            #undef SWITCHCAST
            return;
        } else {
            typ_idx  dto     = dims_to[dim];
            typ_idx *pc      = &c[dim];
            typ_idx *pidx_to = &idx_to[dto];
            for(
                *pc=0, *pidx_to=lo_to[dto];
                *pc < clen[dim];
                (*pc)++, (*pidx_to)++
                ){
                fillSectLoop(to,lo_to,hi_to,x,dims_to,idx_to,ndims,dim+1,c,clen);
            }
        }

        return;
    }

void fillSectToMiss(arr *restrict to, typ_idx *lo_to, typ_idx *hi_to){
    typ_idx i=0,k=0;

/*    printArrayInfoWHdr(stderr,to,"to - "); */
/*    for(i=0;i<to->n; i++){ fprintf(stderr,"to[%lld] : lo=%lld, hi=%lld\n",i,lo_to[i],hi_to[i]); } */
    typ_idx ndims     = to->n;
    typ_idx *idx_to   = NULL;
    typ_idx *clen     = NULL;
    typ_idx *dims_to  = NULL;
    typ_idx len_to  = 0;

    if (to->n > 0){
        idx_to  = malloc(to->n *sizeof(typ_idx));
        for(i=0;i<to->n;++i){  idx_to[i] =lo_to[i]; }
    }
    
    i=0;
    if (ndims > 0){
        clen     = malloc(to->n*sizeof(typ_idx));
        dims_to  = malloc(ndims*sizeof(typ_idx));
        len_to   = hi_to[i] - lo_to[i];
        while (i<to->n){
            if (len_to){
                clen[k]     = len_to+1;
                dims_to[k]  = i;
                i++; k++;
                if (i == to->n) { break; }
            } else {
                i++;
            }
            len_to  = hi_to[i] - lo_to[i];
        }
        ndims = k;
    }

/*    fprintf(stderr,"ndims = %lld\n",ndims); */
/*    for(i=0;i<ndims;++i){ fprintf(stderr,"to[%lld] : dims=%lld, idx=%lld\n",i,dims_to[i], idx_to[i] ); } */

    typ_idx *c = init0(ndims,TYPIDX);
    fillSectToMissLoop(to,lo_to,hi_to,dims_to,idx_to,ndims,(typ_idx)0,c,clen);

    free(c);
    free(clen);
    free(idx_to);
    free(dims_to);
    return;
}

    /*  Used only in fillSectToMiss   */
/* Changed to speed up, should test! */
    void fillSectToMissLoop(arr *restrict to,typ_idx *lo_to,typ_idx *hi_to,
        typ_idx *dims_to,typ_idx *idx_to,typ_idx ndims,typ_idx dim,typ_idx *c,typ_idx *clen){
        
        if (dim == ndims){
            setToMissc(to, idx_to);
            return;
        } else {
            typ_idx  dto     = dims_to[dim];
            typ_idx *pc      = &c[dim];
            typ_idx *pidx_to = &idx_to[dto];
            for( *pc=0, *pidx_to=lo_to[dto];
                 *pc < clen[dim];
                 (*pc)++, (*pidx_to)++ ){
                fillSectToMissLoop(to,lo_to,hi_to,dims_to,idx_to,ndims,dim+1,c,clen);
            }
        }

        return;
    }

/* For this one adim are the dimensions of X that aren't in Y and aidx are the indices of adim to be filled    */
/* Major changes, Must test! */
void assignPart(arr *restrict X,arr *restrict Y,typ_idx *adim,typ_idx *aidx){
/*
 *  I need to make sure even if the dimensions are ordered differently than I expect 
 *  that the part will still be input correctly.
 */

    typ_idx *c     = init0(Y->n,TYPIDX);
    typ_idx *idx   = init0(X->n,TYPIDX);
    typ_idx *cdim  = init0(Y->n,TYPIDX);
    typ_idx  nadim = X->n - Y->n;
    for(typ_idx k=0;k<nadim;++k){
        idx[adim[k]] = aidx[k];
    }
    for(typ_idx i=0,j=0; i < X->n; ++i){
        int cond = 1;
        for(typ_idx k=0;k<nadim;++k){
            if(i == adim[k]){ cond = 0; }
        }
        if (cond){
            cdim[j++] = i;
        }
    }
    assignPartLoop(X,Y,cdim,idx,(typ_idx)0,c);

    free(c);
    free(idx);
    free(cdim);
    return;
}

    /*  Used only in assignPart */
/* Changed to speed up, should test! */
    void assignPartLoop(arr *restrict X, arr *restrict Y, typ_idx *cdim, typ_idx *idx, typ_idx dim, typ_idx *c){
        if (dim == Y->n){
            switch (Y->typ) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                if (isMissc(Y,c)){ \
                    setToMissc(X,idx); \
                } else { \
                    cswassign(X,idx) = cswassign(Y,c);  \
                }
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in assignPartLoop: undefined type %d!\n",Y->typ);
                    exit(0);
                    break;
            }
            #undef SWITCHCAST
            return;
        } else {
            typ_idx *pidx = &idx[cdim[dim]];
            typ_idx *pc   = &c[dim];
            typ_idx dlen  = Y->len[dim];
            for(*pc=0; *pc < dlen; (*pc)++){
                *pidx = *pc;
                assignPartLoop(X,Y,cdim,idx,dim+1,c);
            }
        }
        return;
    }


/*
 *  For this one adim are the dimensions of X that correspond to Y 
 *  and idx are the indices of X to be filled with the adim indices set to zero
 */
void assignPart2(arr *restrict X,arr *restrict Y,typ_idx *adim,typ_idx *idx){
/*
 *  I need to make sure even if the dimensions are ordered differently than I expect 
 *  that the part will still be input correctly.
 */
/*
    typ_idx i;
    for(i=0;i<Y->n;++i){
        fprintf(stderr,"assignPart2: adim[%lld]=%lld\n",i,adim[i]);
    }
    for(i=0;i<X->n;++i){
        fprintf(stderr,"assignPart2: idx[%lld] =%lld\n",i,idx[i]);
    }
*/
    typ_idx *c = init0(Y->n,TYPIDX);
    assignPart2Loop(X,Y,adim,idx,(typ_idx)0,c);

    free(c);
    return;
}

    /*  Used only in assignPart2    */
/* Changed to speed up, should test! */
    void assignPart2Loop(arr *restrict X, arr *restrict Y, typ_idx *adim, typ_idx *idx, typ_idx dim, typ_idx *c){
        if (dim == Y->n){
        /*  typ_idx i;
            for(i=0;i<Y->n;++i){ idx[adim[i]] = c[i]; } */
        /*  Uncomment to print loop counter c
            typ_idx j;
            fputs("assignPart2Loop: ",stderr);
            fputs("X[",stderr);
            for(j=0;j<dim-1;++j){
                fprintf(stderr,"%lld,",idx[j]);
            }
            fprintf(stderr,"%lld] = ",idx[dim-1]);
            fputs("Y[",stderr);
            for(j=0;j<dim-1;++j){
                fprintf(stderr,"%lld,",c[j]);
            }
            fprintf(stderr,"%lld]",c[dim-1]);
            fputs("\n",stderr);
         */

            switch (Y->typ) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                if (isMissc(Y,c)){ \
                    setToMissc(X,idx); \
                } else { \
                    cswassign(X,idx) = cswassign(Y,c);  \
                }
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in assignPart2Loop: undefined type %d!\n",Y->typ);
                    exit(0);
                    break;
            }
            #undef SWITCHCAST
            return;
        } else {
        /*  typ_idx cadim = adim[dim]; */
            typ_idx *pidx = &idx[adim[dim]];
            typ_idx *pc   = &c[dim];
            typ_idx dlen  = Y->len[dim];
            for(*pc=0; *pc < dlen; (*pc)++){
            /*  Uncomment to print loop counter c
                typ_idx j;
                fputs("assignPart2Loop: ",stderr);
                for(j=0;j<=dim;++j){
                    fprintf(stderr,"c[%lld]=%lld ",j,c[j]);
                }
                fputs("\n",stderr);
            */
            /*  idx[cadim] = c[dim]; */
                *pidx = *pc;
                assignPart2Loop(X,Y,adim,idx,dim+1,c);
            }
        }
        return;
    }


arr reorderDims(arr *restrict n, typ_idx *trans){
    typ_idx i;
    typ_idx *translen = malloc(n->n*sizeof(typ_idx));
    for(i=0;i<n->n;++i){ translen[i] = n->len[trans[i]]; }
    arr m = ArrayFromList(n->n,n->typ,translen);

    typ_idx *c = init0(n->n,TYPIDX);
    reorderDimsLoop(&m,n,trans,(typ_idx)0,c);

    free(c);
    free(translen);
    return m;
}

    /*  Used only in reorderDims    */
    void reorderDimsLoop(arr *restrict X, arr *restrict Y, typ_idx *trans, typ_idx dim, typ_idx *c){
        typ_idx *idx;
        typ_idx i;
        
        if (dim == Y->n){
            idx = init0(X->n,TYPIDX);
            for(i=0;i<X->n;++i){ idx[trans[i]] = c[i]; }
            switch (Y->typ) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                cswassign(X,idx) = cswassign(Y,c);  
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in reorderDimsLoop: undefined type %d!\n",Y->typ);
                    exit(0);
                    break;
            }
            #undef SWITCHCAST
            free(idx);
            return;
        } else {
            for(c[dim]=0;c[dim]<Y->len[dim];c[dim]++){
                reorderDimsLoop(X,Y,trans,dim+1,c);
            }
        }

        return;
    }


arr expandAr(arr *restrict IN,arr *restrict OUT_sz,typ_idx *map){
    arr m = expandArExp(IN,OUT_sz->n,OUT_sz->len,map);
    
    return m;
}


/* No reason why this can't be multitype */
arr expandArExp(arr *restrict IN,typ_idx ndims,typ_idx *outlen,typ_idx *map){
    /* How do I deal with arrays of different dimensions?     */
    /* Can I assume certain operations given dimension sizes? */
    typ_idx i;

    typ_idx outtlen = 1;
/*  fputs("expandArExp: outlen",stderr); */
    for(i=0;i<ndims;++i){
        outtlen *= outlen[i];
    /*  fprintf(stderr," %lld",outlen[i]); */
    }
/*  fputs("\n",stderr);
    if (map){
        fputs("expandArExp: map",stderr);
        for(i=0;i<IN->n;++i){
            fprintf(stderr," %lld",map[i]);
        }
        fputs("\n",stderr);
    } */
    
    int are_maps_eq = 1;
    if ((IN->n != ndims) || (IN->tlen != outtlen)){
        are_maps_eq = 0;
    }
    
    arr m;
    if (are_maps_eq){
        m = copyAr(IN);
    } else  {
        m = ArrayFromList(ndims,IN->typ,outlen);
        copyMiss(&m,IN);
        typ_idx *c = init0(ndims,TYPIDX);
        expandAr_loop(&m,IN,map,(typ_idx)0,c);
        free(c);
    }

    return m;
}


    /*  Used only in expandAr   */
    void expandAr_loop(arr *restrict OUT, arr *restrict IN, typ_idx *map, typ_idx dim, typ_idx *c){
        if (dim == OUT->n){
            typ_idx j;
            typ_idx *idx = init0(IN->n,TYPIDX);
            for(j=0;j<IN->n;++j){ idx[j] = c[map[j]]; }
            if(isMissc(IN,idx)){
                setToMissc(OUT,c);
            } else {
                switch (OUT->typ) {
                #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                    cswassign(OUT,c) = cswassign(IN,idx);
                    ALLTYPECASES
                    default:
                        fprintf(stderr,"expandAr_loop: undefined type %d!\n",OUT->typ);
                        exit(0);
                        break;
                }
                #undef SWITCHCAST
            }
            free(idx);
            return;
        } else {
            for(c[dim]=0;c[dim]<OUT->len[dim];c[dim]++){
                expandAr_loop(OUT,IN,map,dim+1,c);
            }
        }

        return;
    }
    


arr combineArraysList(int narrs, typ_idx indim, arr **inarrs){
/*
 *  It is possible to combine arrays in the direction of all dimensions plus 1 extra!
 *  This extra dimension will be input as -1 and will signal the creation of a new
 *    leftmost dimension and shift all other dims to the right.
 */

    typ_idx i,j,k,indimsum,ndims;
    arr **arrays = malloc(narrs*sizeof(arr *));
    arr m;

    for (j=0;j<narrs;++j){
        arrays[j]  = malloc(sizeof(arr));
        *arrays[j] = copyAr(inarrs[j]);
    }

/*
 *      Loop through all of the input arrays to make sure
 *      they all contain the same number of dimensions and same size on all dimensions
 *      except for the input dimension.  The array with the least amount of dimensions
 *      must have only 1 fewer dimensions than the array with the most dimensions then
 *      the small arrays dimensions must match all of the larger arrays dimensions 
 *      except for the input dimension.  Once this is determined, the small arrays dimensions
 *      will be increased by one (and be the input dimension) and the size of this dimension will be one.
 */

/*  Check for array with most and least dimensions  */
    typ_idx jmostdims = 0;
    typ_idx mostdims  = 0;
    typ_idx leastdims = 100;
    for (j=0;j<narrs;++j){
        if (arrays[j]->n > mostdims){
            jmostdims = j;
            mostdims = arrays[j]->n;
        }
        if (arrays[j]->n < leastdims){
            leastdims = arrays[j]->n;
        }
        if ((mostdims-leastdims) > 0) {
            if (indim == -1){
                fprintf(stderr,"Error in combineArraysList:\n\tinput arrays need to have equal dimensions when indim == -1\n");
                exit(0);
            }
            if ((mostdims-leastdims) > 1) {
                fprintf(stderr,"Error in combineArraysList:\n\tinput arrays can only vary by up to one dimension\n");
                exit(0);
            }
        }
    }

    typ_idx *newlen;
    for (j=0;j<narrs;++j){
    /*  Add dimension for smaller arrays    */
        if (arrays[j]->n < mostdims){
            newlen  = malloc(mostdims*sizeof(typ_idx));
            for(i=0;i<mostdims;++i){
                if (i < indim){
                    newlen[i] = arrays[j]->len[i];
                } else if (i == indim) {
                    newlen[i] = 1;
                } else {
                    newlen[i] = arrays[j]->len[i-1];
                }
            }
            reshapeArList(arrays[j],mostdims,newlen);
            free(newlen);
        } 
    /*  Check that dimensions are correct sizes */
        for(i=0;i<arrays[jmostdims]->n;++i){
            if (i != indim){
                if ((arrays[j]->len[i]) != (arrays[jmostdims]->len[i])){
                    fprintf(stderr,"Error in combineArraysList:\n\tdimension sizes do not match up\n");
                    exit(0);
                }
            }
        }
    }

    /*  Find total size of indim    */
    indimsum = 0;
    for (j=0;j<narrs;++j){
        if (indim == -1){
            indimsum++;
        } else {
            indimsum += arrays[j]->len[indim];
        }
    }

    /*  Allocate output arrays at either the dimension of largest array or one more */
    typ_idx *dimlist;
    if (indim == -1){
        ndims = arrays[0]->n+1;
        dimlist = init0(ndims,TYPIDX);
        dimlist[0] = indimsum;
        for (i=1;i<ndims;++i){
            dimlist[i] = arrays[0]->len[i-1];
        }
        m = ArrayFromList(ndims,arrays[0]->typ,dimlist);
        copyMiss(&m,arrays[0]);
    } else {
        ndims = arrays[0]->n;
        dimlist = init0(ndims,TYPIDX);
        for (i=0;i<ndims;++i){
            if (i == indim){
                dimlist[i] = indimsum;
            } else {
                dimlist[i] = arrays[0]->len[i];
            }
        }
        m = ArrayFromList(ndims,arrays[0]->typ,dimlist);
        copyMiss(&m,arrays[0]);
    }

    typ_idx *c = init0(arrays[0]->n,TYPIDX);

    k = 0;
    typ_idx totk = 0;
    for (j=0;j<narrs;++j){
        if (indim == 0) { k = totk; }
        combineArraysLoop(&m,arrays,narrs,indim,j,&k,totk,(typ_idx)0,c);
        if (indim == -1 ){
            k++;
        } else {
            totk += arrays[j]->len[indim];
        }
    }

    for (j=0;j<narrs;++j){
        freeAr(arrays[j]);
        free(arrays[j]);
    }
    free(arrays);
    free(c);
    free(dimlist);
    return m;
}

arr combineArrays(int narrs, typ_idx indim, ...){
    typ_idx j;
    arr **arrays = malloc(narrs*sizeof(arr *));

    va_list arg_list;
    va_start(arg_list, indim);
    for (j=0;j<narrs;++j){
        arrays[j] = va_arg(arg_list, arr *);
    }
    va_end(arg_list);
    
    arr m = combineArraysList(narrs, indim, arrays);

    free(arrays);
    return m;
}

    /*  Used only in combineArrays  */
    void combineArraysLoop(arr *restrict X, arr **arrays, int narrs, typ_idx indim, typ_idx j, typ_idx *k, typ_idx totk, typ_idx dim, typ_idx *c){
        typ_idx *idx;
        typ_idx i;
        
        if (dim == arrays[j]->n){
            idx = init0(X->n,TYPIDX);
            if (indim == -1){
                idx[0] = *k;
                for(i=1;i<X->n;++i){
                    idx[i] = c[i-1];
                }
            } else {
                for(i=0;i<X->n;++i){
                    if(i == indim){
                        idx[i] = *k;
                    } else {
                        idx[i] = c[i];
                    }
                }
            }
            switch (arrays[j]->typ) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                cswassign(X,idx) = cswassign(arrays[j],c);
                ALLTYPECASES
                default:
                    fprintf(stderr,"combineArraysLoop: undefined type %d!\n",arrays[j]->typ);
                    exit(0);
                    break;
            }
            #undef SWITCHCAST
            free(idx);
            return;
        } else {
            for(c[dim]=0;c[dim]<arrays[j]->len[dim];c[dim]++){
                if (indim == dim+1) { *k = totk; }
                combineArraysLoop(X,arrays,narrs,indim,j,k,totk,dim+1,c);
                if (dim == indim){ (*k)++; }
            }
        }

        return;
    }



    

/* Should be able to simplify this and speed it up a lot */
arr combineArrays2List(int narrs, typ_idx indim, arr **inarrs){
/*
 *  It is possible to combine arrays in the direction of all dimensions plus 1 extra!
 *  This extra dimension will be input as -1 and will signal the creation of a new
 *    leftmost dimension and shift all other dims to the right.
 */

    typ_idx i,j,k,indimsum,ndims;
    arr **arrays = malloc(narrs*sizeof(arr *));
    arr m;

    for (j=0;j<narrs;++j){
        arrays[j]  = malloc(sizeof(arr));
        *arrays[j] = copyAr(inarrs[j]);
    }

/*
 *      Loop through all of the input arrays to make sure
 *      they all contain the same number of dimensions and same size on all dimensions
 *      except for the input dimension.  The array with the least amount of dimensions
 *      must have only 1 fewer dimensions than the array with the most dimensions then
 *      the small arrays dimensions must match all of the larger arrays dimensions 
 *      except for the input dimension.  Once this is determined, the small arrays dimensions
 *      will be increased by one (and be the input dimension) and the size of this dimension will be one.
 */

/*  Check for array with most and least dimensions  */
    typ_idx jmostdims = 0;
    typ_idx mostdims  = 0;
    typ_idx leastdims = 100;
    for (j=0;j<narrs;++j){
        if (arrays[j]->n > mostdims){
            jmostdims = j;
            mostdims = arrays[j]->n;
        }
        if (arrays[j]->n < leastdims){
            leastdims = arrays[j]->n;
        }
        if ((mostdims-leastdims) > 0) {
            if (indim == -1){
                fprintf(stderr,"Error in combineArrays2List:\n\tinput arrays need to have equal dimensions when indim == -1\n");
                exit(0);
            }
            if ((mostdims-leastdims) > 1) {
                fprintf(stderr,"Error in combineArrays2List:\n\tinput arrays can only vary by up to one dimension\n");
                exit(0);
            }
        }
    }

    typ_idx *newlen;
    for (j=0;j<narrs;++j){
    /*  Add dimension for smaller arrays    */
        if (arrays[j]->n < mostdims){
            newlen  = malloc(mostdims*sizeof(typ_idx));
            for(i=0;i<mostdims;++i){
                if (i < indim){
                    newlen[i] = arrays[j]->len[i];
                } else if (i == indim) {
                    newlen[i] = 1;
                } else {
                    newlen[i] = arrays[j]->len[i-1];
                }
            }
            reshapeArList(arrays[j],mostdims,newlen);
            free(newlen);
        } 
    /*  Check that dimensions are correct sizes */
        for(i=0;i<arrays[jmostdims]->n;++i){
            if (i != indim){
                if ((arrays[j]->len[i]) != (arrays[jmostdims]->len[i])){
                    fprintf(stderr,"Error in combineArrays2List:\n\tdimension sizes do not match up\n");
                    exit(0);
                }
            }
        }
    }

    /*  Find total size of indim    */
    indimsum = 0;
    for (j=0;j<narrs;++j){
        if (indim == -1){
            indimsum++;
        } else {
            indimsum += arrays[j]->len[indim];
        }
    }

    /*  Allocate output arrays at either the dimension of largest array or one more */
    typ_idx *dimlist;
    if (indim == -1){
        ndims = arrays[0]->n+1;
        dimlist = init0(ndims,TYPIDX);
        dimlist[0] = indimsum;
        for (i=1;i<ndims;++i){
            dimlist[i] = arrays[0]->len[i-1];
        }
        m = ArrayFromList(ndims,arrays[0]->typ,dimlist);
        copyMiss(&m,arrays[0]);
    } else {
        ndims = arrays[0]->n;
        dimlist = init0(ndims,TYPIDX);
        for (i=0;i<ndims;++i){
            if (i == indim){
                dimlist[i] = indimsum;
            } else {
                dimlist[i] = arrays[0]->len[i];
            }
        }
        m = ArrayFromList(ndims,arrays[0]->typ,dimlist);
        copyMiss(&m,arrays[0]);
    }

    typ_idx *c = init0(arrays[0]->n,TYPIDX);

    k = 0;
    typ_idx totk = 0;
    for (j=0;j<narrs;++j){
        if (indim == 0) { k = totk; }
        combineArrays2Loop(&m,arrays,narrs,indim,j,&k,totk,(typ_idx)0,c);
        if (indim == -1 ){
            k++;
        } else {
            totk += arrays[j]->len[indim];
        }
    }

    for (j=0;j<narrs;++j){
        freeAr(arrays[j]);
        free(arrays[j]);
    }
    free(arrays);
    free(c);
    free(dimlist);
    return m;
}

arr combineArrays2(int narrs, typ_idx indim, ...){
    typ_idx j;
    arr **arrays = malloc(narrs*sizeof(arr *));

    va_list arg_list;
    va_start(arg_list, indim);
    for (j=0;j<narrs;++j){
        arrays[j] = va_arg(arg_list, arr *);
    }
    va_end(arg_list);
    
    arr m = combineArrays2List(narrs, indim, arrays);

    free(arrays);
    return m;
}

    /*  Used only in combineArrays2  */
    void combineArrays2Loop(arr *restrict X, arr **arrays, int narrs, typ_idx indim, typ_idx j, typ_idx *k, typ_idx totk, typ_idx dim, typ_idx *c){
        typ_idx *idx;
        typ_idx i;
        
        if (dim == arrays[j]->n){
            idx = init0(X->n,TYPIDX);
            if (indim == -1){
                idx[0] = *k;
                for(i=1;i<X->n;++i){
                    idx[i] = c[i-1];
                }
            } else {
                for(i=0;i<X->n;++i){
                    if(i == indim){
                        idx[i] = *k;
                    } else {
                        idx[i] = c[i];
                    }
                }
            }
            switch (arrays[j]->typ) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                cswassign(X,idx) = cswassign(arrays[j],c);
                ALLTYPECASES
                default:
                    fprintf(stderr,"combineArrays2Loop: undefined type %d!\n",arrays[j]->typ);
                    exit(0);
                    break;
            }
            #undef SWITCHCAST
            free(idx);
            return;
        } else {
            for(c[dim]=0;c[dim]<arrays[j]->len[dim];c[dim]++){
                if (indim == dim+1) { *k = totk; }
                combineArrays2Loop(X,arrays,narrs,indim,j,k,totk,dim+1,c);
                if (dim == indim){ (*k)++; }
            }
        }

        return;
    }


#endif
