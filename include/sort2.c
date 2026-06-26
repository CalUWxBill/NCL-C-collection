/* Created by Bill Scheftic */
#ifndef  _SORT2_H_
#define  _SORT2_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <print_arrays2.h>

typedef struct {
    typ_idx id;
    int typ, ismiss;
    union {
        signed char byt;
        char chr;
        short shrt;
        int intg;
        float flt;
        double dbl;
        unsigned char ubyt;
        unsigned short ushrt;
        unsigned int uint;
        long long int64;
        unsigned long long uint64;
    } u;
}table;

int compare_tables (const void *, const void *);
int compare_byts (const void *, const void *);
int compare_chrs (const void *, const void *);
int compare_shrts (const void *, const void *);
int compare_ints (const void *, const void *);
int compare_flts (const void *, const void *);
int compare_dbls (const void *, const void *);
int compare_ubyts (const void *, const void *);
int compare_ushrts (const void *, const void *);
int compare_uints (const void *, const void *);
int compare_int64s (const void *, const void *);
int compare_uint64s (const void *, const void *);
void qsortTable(arr *,arr *);
void qsortTable2(arr *,arr *);
arr qsortArray(arr *);

int compare_tables_rev (const void *, const void *);
int compare_byts_rev (const void *, const void *);
int compare_chrs_rev (const void *, const void *);
int compare_shrts_rev (const void *, const void *);
int compare_ints_rev (const void *, const void *);
int compare_flts_rev (const void *, const void *);
int compare_dbls_rev (const void *, const void *);
int compare_ubyts_rev (const void *, const void *);
int compare_ushrts_rev (const void *, const void *);
int compare_uints_rev (const void *, const void *);
int compare_int64s_rev (const void *, const void *);
int compare_uint64s_rev (const void *, const void *);
void qsortTableRev(arr *,arr *);
void qsortTable2Rev(arr *,arr *);
arr qsortArrayRev(arr *);
/*  arr1 reduceAndSort(arr2);   */

int compare_tables (const void *a, const void *b) {
    const table *da = (const table *) a;
    const table *db = (const table *) b;
     
    switch (da->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        if (da->ismiss){ if (db->ismiss) { return 0; } else { return  1; } }    \
        if (db->ismiss){ return -1; }                                           \
        return (da->u.swtyp > db->u.swtyp) - (da->u.swtyp < db->u.swtyp);
        ALLTYPECASES
        default:
            fprintf(stderr,"compare_tables: undefined type %d!\n",da->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return -9;
}

int compare_tables_rev (const void *a, const void *b) {
    const table *da = (const table *) a;
    const table *db = (const table *) b;
     
    switch (da->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        if (da->ismiss){ if (db->ismiss) { return 0; } else { return  1; } }    \
        if (db->ismiss){ return -1; }                                           \
        return (da->u.swtyp < db->u.swtyp) - (da->u.swtyp > db->u.swtyp);
        ALLTYPECASES
        default:
            fprintf(stderr,"compare_tables: undefined type %d!\n",da->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return -9;
}

int compare_byts (const void *a, const void *b) {
    return (*(const signed char *)a > *(const signed char *)b) 
         - (*(const signed char *)a < *(const signed char *)b);
}

int compare_chrs (const void *a, const void *b) {
    return (*(const char *)a > *(const char *)b) 
         - (*(const char *)a < *(const char *)b);
}

int compare_shrts (const void *a, const void *b) {
    return (*(const short *)a > *(const short *)b) 
         - (*(const short *)a < *(const short *)b);
}

int compare_ints (const void *a, const void *b) {
    return (*(const int *)a > *(const int *)b) 
         - (*(const int *)a < *(const int *)b);
}

int compare_flts (const void *a, const void *b) {
    return (*(const float *)a > *(const float *)b) 
         - (*(const float *)a < *(const float *)b);
}

int compare_dbls (const void *a, const void *b) {
    return (*(const double *)a > *(const double *)b) 
         - (*(const double *)a < *(const double *)b);
}

int compare_ubyts (const void *a, const void *b) {
    return (*(const unsigned char *)a > *(const unsigned char *)b) 
         - (*(const unsigned char *)a < *(const unsigned char *)b);
}

int compare_ushrts (const void *a, const void *b) {
    return (*(const unsigned short *)a > *(const unsigned short *)b) 
         - (*(const unsigned short *)a < *(const unsigned short *)b);
}

int compare_uints (const void *a, const void *b) {
    return (*(const unsigned int *)a > *(const unsigned int *)b) 
         - (*(const unsigned int *)a < *(const unsigned int *)b);
}

int compare_int64s (const void *a, const void *b) {
    return (*(const long long *)a > *(const long long *)b) 
         - (*(const long long *)a < *(const long long *)b);
}

int compare_uint64s (const void *a, const void *b) {
    return (*(const unsigned long long *)a > *(const unsigned long long *)b) 
         - (*(const unsigned long long *)a < *(const unsigned long long *)b);
}

/* Reverse comparators */
int compare_byts_rev (const void *a, const void *b) {
    return (*(const signed char *)a < *(const signed char *)b) 
         - (*(const signed char *)a >*(const signed char *)b);
}

int compare_chrs_rev (const void *a, const void *b) {
    return (*(const char *)a < *(const char *)b) 
         - (*(const char *)a > *(const char *)b);
}

int compare_shrts_rev (const void *a, const void *b) {
    return (*(const short *)a < *(const short *)b) 
         - (*(const short *)a > *(const short *)b);
}

int compare_ints_rev (const void *a, const void *b) {
    return (*(const int *)a < *(const int *)b) 
         - (*(const int *)a > *(const int *)b);
}

int compare_flts_rev (const void *a, const void *b) {
    return (*(const float *)a < *(const float *)b) 
         - (*(const float *)a > *(const float *)b);
}

int compare_dbls_rev (const void *a, const void *b) {
    return (*(const double *)a < *(const double *)b) 
         - (*(const double *)a > *(const double *)b);
}

int compare_ubyts_rev (const void *a, const void *b) {
    return (*(const unsigned char *)a < *(const unsigned char *)b) 
         - (*(const unsigned char *)a > *(const unsigned char *)b);
}

int compare_ushrts_rev (const void *a, const void *b) {
    return (*(const unsigned short *)a < *(const unsigned short *)b) 
         - (*(const unsigned short *)a > *(const unsigned short *)b);
}

int compare_uints_rev (const void *a, const void *b) {
    return (*(const unsigned int *)a < *(const unsigned int *)b) 
         - (*(const unsigned int *)a > *(const unsigned int *)b);
}

int compare_int64s_rev (const void *a, const void *b) {
    return (*(const long long *)a < *(const long long *)b) 
         - (*(const long long *)a > *(const long long *)b);
}

int compare_uint64s_rev (const void *a, const void *b) {
    return (*(const unsigned long long *)a < *(const unsigned long long *)b) 
         - (*(const unsigned long long *)a > *(const unsigned long long *)b);
}

/*
int compare_rev (const void *a, const void *b, typ_idx typ) {
    switch (typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        return -1*swcompare(a,b);
        ALLTYPECASES
        default:
            fprintf(stderr,"compare_rev: undefined type %d!\n",da->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return -9;
}
*/

/* Missing values are sorted depending on their value */
arr qsortArray(arr *restrict X) {
    arr D = copyAr(X);  /* dummy storage array */
    switch (D.typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        qsort (pntr_of(&D), D.tlen, D.typsize, swcompare);
        ALLTYPECASES
        default:
            fprintf(stderr,"qsortArray: undefined type %d!\n",D.typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return D;
}

/* Missing values are sorted depending on their value */
arr qsortArrayRev(arr *restrict X) {
    arr D = copyAr(X);  /* dummy storage array */
    switch (D.typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        qsort (pntr_of(&D), D.tlen, D.typsize, swcompare##_rev);
        ALLTYPECASES
        default:
            fprintf(stderr,"qsortArrayRev: undefined type %d!\n",D.typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return D;
}

/* Missing values placed at end */
void qsortTable(arr *restrict val,arr *restrict idx){
    typ_idx i;
    table *tbl;

    switch (val->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pval = pntr_of(val); \
        tbl = malloc(val->tlen*sizeof(table));                 \
        for (i = 0;i < val->tlen;i++){                             \
            tbl[i].ismiss  = isMiss(val,i);                     \
            tbl[i].u.swtyp  = pval[i];                               \
            tbl[i].id     = iIDX(idx,i);                                \
            tbl[i].typ    = val->typ;                                \
        }                                                   \
        qsort (tbl, val->tlen, sizeof(table), compare_tables);             \
        for (i = 0;i < val->tlen;i++){                             \
            iIDX(idx,i)  = tbl[i].id;                               \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"qsortTable: undefined type %d!\n",val->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    free(tbl);
    return;
}

/* Missing values placed at end */
void qsortTableRev(arr *restrict val,arr *restrict idx){
    typ_idx i;
    table *tbl;

    switch (val->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pval = pntr_of(val); \
        tbl = malloc(val->tlen*sizeof(table));                 \
        for (i = 0;i < val->tlen;i++){                             \
            tbl[i].ismiss  = isMiss(val,i);                     \
            tbl[i].u.swtyp  = pval[i];                               \
            tbl[i].id     = iIDX(idx,i);                                \
            tbl[i].typ    = val->typ;                                \
        }                                                   \
        qsort (tbl, val->tlen, sizeof(table), compare_tables_rev);             \
        for (i = 0;i < val->tlen;i++){                             \
            iIDX(idx,i)  = tbl[i].id;                               \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"qsortTable: undefined type %d!\n",val->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    free(tbl);
    return;
}

/* Missing values placed at end */
void qsortTable2(arr *restrict val,arr *restrict idx){
    typ_idx i;
    table *tbl;

    switch (val->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pval = pntr_of(val); \
        tbl = malloc(val->tlen*sizeof(table));                 \
        for (i = 0;i < val->tlen;i++){                             \
            tbl[i].ismiss  = isMiss(val,i);                     \
            tbl[i].u.swtyp  = pval[i];                               \
            tbl[i].id     = i;                              \
            tbl[i].typ    = val->typ;                                \
        }                                                   \
        qsort (tbl, val->tlen, sizeof(table), compare_tables);             \
        for (i = 0;i < val->tlen;i++){                             \
            iIDX(idx,i)  = tbl[i].id;                               \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"qsortTable2: undefined type %d!\n",val->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    free(tbl);
    return;
}

/* Missing values placed at end */
void qsortTable2Rev(arr *restrict val,arr *restrict idx){
    typ_idx i;
    table *tbl;

    switch (val->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pval = pntr_of(val); \
        tbl = malloc(val->tlen*sizeof(table));                 \
        for (i = 0;i < val->tlen;i++){                             \
            tbl[i].ismiss  = isMiss(val,i);                     \
            tbl[i].u.swtyp  = pval[i];                               \
            tbl[i].id     = i;                              \
            tbl[i].typ    = val->typ;                                \
        }                                                   \
        qsort (tbl, val->tlen, sizeof(table), compare_tables_rev);             \
        for (i = 0;i < val->tlen;i++){                             \
            iIDX(idx,i)  = tbl[i].id;                               \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"qsortTable2: undefined type %d!\n",val->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    free(tbl);
    return;
}

/* Missing values placed at end */
arr qsortArrayIdx(arr *restrict val){
    typ_idx i;
    table *tbl;

    arr ridx = Array((typ_idx)1,TYPIDX,val->tlen);
    switch (val->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pval = pntr_of(val); \
        tbl = malloc(val->tlen*sizeof(table));                   \
        for (i = 0;i < val->tlen;i++){                           \
            tbl[i].ismiss  = isMiss(val,i);                     \
            tbl[i].u.swtyp   = pval[i];                      \
            tbl[i].id      = i;                                 \
            tbl[i].typ     = val->typ;                           \
        }                                                       \
        qsort (tbl, val->tlen, sizeof(table), compare_tables);   \
        for (i = 0;i < val->tlen;i++){                           \
            iIDX(&ridx,i)  = tbl[i].id;                          \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"qsortArrayIdx: undefined type %d!\n",val->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    free(tbl);
    return ridx;
}

/* Missing values placed at end */
arr qsortArrayIdxRev(arr *restrict val){
    typ_idx i;
    table *tbl;

    arr ridx = Array((typ_idx)1,TYPIDX,val->tlen);
    switch (val->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pval = pntr_of(val); \
        tbl = malloc(val->tlen*sizeof(table));                   \
        for (i = 0;i < val->tlen;i++){                           \
            tbl[i].ismiss  = isMiss(val,i);                     \
            tbl[i].u.swtyp   = pval[i];                      \
            tbl[i].id      = i;                                 \
            tbl[i].typ     = val->typ;                           \
        }                                                       \
        qsort (tbl, val->tlen, sizeof(table), compare_tables_rev);   \
        for (i = 0;i < val->tlen;i++){                           \
            iIDX(&ridx,i)  = tbl[i].id;                          \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"qsortArrayIdx: undefined type %d!\n",val->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    free(tbl);
    return ridx;
}

/* Missing values placed at end */
void qsortArrayIdxWRev(arr *restrict val,arr *idx,arr *revidx){
    typ_idx i;
    table *tbl;

    *idx    = Array((typ_idx)1,TYPIDX,val->tlen);
    *revidx = Array((typ_idx)1,TYPIDX,val->tlen);
    switch (val->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pval = pntr_of(val); \
        tbl = malloc(val->tlen*sizeof(table));                 \
        for (i = 0;i < val->tlen;i++){                         \
            tbl[i].ismiss  = isMiss(val,i);                   \
            tbl[i].u.swtyp = pval[i];                    \
            tbl[i].id      = i;                               \
            tbl[i].typ     = val->typ;                         \
        }                                                     \
        qsort (tbl, val->tlen, sizeof(table), compare_tables); \
        for (i = 0;i < val->tlen;i++){                         \
            iIDX(idx,i)            = tbl[i].id;              \
            iIDX(revidx,tbl[i].id) = i;                      \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"qsortArrayIdxWRev: undefined type %d!\n",val->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    free(tbl);
    return;
}

arr sortOnIdx(arr *restrict X,arr *restrict XIdx) {
    typ_idx i;
    arr Y = ArrayFromList(X->n,X->typ,X->len);
    copyMiss(&Y,X);
    switch (X->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
    { \
        swcast *pX = pntr_of(X); \
        swcast *pY = pntr_of(&Y); \
        for (i=0;i<X->tlen;i++){ \
            if (isMiss(XIdx,i)) { \
                setToMiss(&Y,i); \
            } else { \
                pY[i] = pX[ iIDX(XIdx,i) ]; \
            } \
        } \
    }
        ALLTYPECASES
        default:
            fprintf(stderr,"sortOnIdx: undefined type %d!\n",X->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST
    return Y;
}

#endif
