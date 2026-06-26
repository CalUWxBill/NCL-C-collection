/* Created by Bill Scheftic */
/*
 *--------------------------------------------------------------------------------------------------
 * arrayinit2.h was built to allow simple C coding of multi-dimensional dynamically allocated arrays 
 *--------------------------------------------------------------------------------------------------
 * Use in Program:                                                      
 *  + all arrays must be declared                                               
 *  Ex: arr variable;                                                   
 *  + all arrays must be initialized                                            
 *  Ex: variable = Array(3,DOUBLE,nz,ny,nx);                                            
 *  Ex: variable = ArrayFromList(3,DOUBLE,nlist);
 *  + all arrays should be deallocated when use is completed
 *  Ex: freeAr(&variable);
 *  + arrays can be declared and initialized in one line                                
 *  Ex: arr variable = Array(3,DOUBLE,nz,ny,nx);                                            
 *  *** The memory for any array that is declared inside of a function MUST be deallocated  ***
 *  ***     before exiting the function UNLESS that array is returned to the calling function ***
 *  *** or program.                                                 ***
 *--------------------------------------------------------------------------------------------------
 */

#ifndef  _ARRAY2_H_
#define  _ARRAY2_H_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <float.h>

#ifdef __linux__ 

#include <byteswap.h>

#elif _WIN32

#else

#endif

#include <math.h>

/* Should I convert this to an enum? */
/*
enum arr_type {
    NAT,
    BYTE,
    CHAR,
    SHORT,
    INT,
    FLOAT,
    DOUBLE,
    UBYTE,
    USHORT,
    UINT,
    INT64,
    UINT64,
    STRING,
    ARR,
    F_INT,
    F_DOUBLE,
    F_INT64
};
*/
#define NAT      0   /* NAT = 'Not A Type' (c.f. NaN) */
#define BYTE     1   /* signed 1 byte integer */
#define CHAR     2   /* ISO/ASCII character */
#define SHORT    3   /* signed 2 byte integer */
#define INT      4   /* signed 4 byte integer */
#define FLOAT    5   /* single precision floating point number */
#define DOUBLE   6   /* double precision floating point number */
#define UBYTE    7   /* unsigned 1 byte int */
#define USHORT   8   /* unsigned 2 byte int */
#define UINT     9   /* unsigned 4 byte int */
#define INT64    10  /* signed   8 byte int */
#define UINT64   11  /* unsigned 8 byte int */
#define STRING   12  /* string */
#define ARR      13  /* arrays */
#define F_INT    14  /* function returning int */
#define F_DOUBLE 15  /* function returning double */
#define F_INT64  16  /* function returning long long int */

#define MAX_BYTE    SCHAR_MAX
#define MAX_CHAR    CHAR_MAX
#define MAX_SHORT   SHRT_MAX
#define MAX_INT     INT_MAX
#define MAX_FLOAT   FLT_MAX
#define MAX_DOUBLE  DBL_MAX
#define MAX_UBYTE   UCHAR_MAX
#define MAX_USHORT  USHRT_MAX
#define MAX_UINT    UINT_MAX
#define MAX_INT64   9223372036854775807LL
#define MAX_UINT64  18446744073709551615ULL

#define MIN_BYTE    SCHAR_MIN
#define MIN_CHAR    CHAR_MIN
#define MIN_SHORT   SHRT_MIN
#define MIN_INT     INT_MIN
#define MIN_FLOAT   -FLT_MAX
#define MIN_DOUBLE  -DBL_MAX
#define MIN_UBYTE   0
#define MIN_USHORT  0
#define MIN_UINT    0
#define MIN_INT64   (-MAX_INT64 - 1LL)
#define MIN_UINT64  0

#define BYT *(signed char *)address_of
#define CHR *(char *)address_of
#define SHT *(short *)address_of
#define INTG *(int *)address_of
#define FLT *(float *)address_of
#define DBL *(double *)address_of
#define UBYT *(unsigned char *)address_of
#define USHT *(unsigned short *)address_of
#define UINTG *(unsigned int *)address_of
#define LINT *(long long *)address_of
#define ULINT *(unsigned long long *)address_of
#define ULINT *(unsigned long long *)address_of
#define F_INTG *(int (*)())address_of
#define F_DBL *(double (*)())address_of
#define F_LINT *(long long (*)())address_of

#define cBYT *(signed char *)address_of_c
#define cCHR *(char *)address_of_c
#define cSHT *(short *)address_of_c
#define cINTG *(int *)address_of_c
#define cFLT *(float *)address_of_c
#define cDBL *(double *)address_of_c
#define cUBYT *(unsigned char *)address_of_c
#define cUSHT *(unsigned short *)address_of_c
#define cUINTG *(unsigned int *)address_of_c
#define cLINT *(long long *)address_of_c
#define cULINT *(unsigned long long *)address_of_c
#define cF_INTG *(int (*)())address_of_c
#define cF_DBL *(double (*)())address_of_c
#define cF_LINT *(long long (*)())address_of_c

#define iBYT *(signed char *)address_of_i
#define iCHR *(char *)address_of_i
#define iSHT *(short *)address_of_i
#define iINTG *(int *)address_of_i
#define iFLT *(float *)address_of_i
#define iDBL *(double *)address_of_i
#define iUBYT *(unsigned char *)address_of_i
#define iUSHT *(unsigned short *)address_of_i
#define iUINTG *(unsigned int *)address_of_i
#define iLINT *(long long *)address_of_i
#define iULINT *(unsigned long long *)address_of_i
#define iF_INTG *(int (*)())address_of_i
#define iF_DBL *(double (*)())address_of_i
#define iF_LINT *(long long (*)())address_of_i

#define fmtBYT   "%hhd"
#define fmtCHR   "%c"
#define fmtSHT   "%hd"
#define fmtINTG  "%d"
#define fmtFLT   "%f"
#define fmtDBL   "%lf"
#define fmtUBYT  "%hhu"
#define fmtUSHT  "%hu"
#define fmtUINTG "%u"
#define fmtLINT  "%lld"
#define fmtULINT "%llu"

#define TYPIDX   INT64
#define MIN_IDX  MIN_INT64
#define MAX_IDX  MAX_INT64
#define IDX      LINT
#define cIDX     cLINT
#define iIDX     iLINT
#define F_TYPIDX F_INT64
#define F_IDX    F_LINT
#define cF_IDX   cF_LINT
#define iF_IDX   iF_LINT
#define fmtIDX   fmtULINT

const char *ARR_TYPE_LBLS[] = {
    "No Type",
    "signed char",
    "char",
    "short",
    "int",
    "float",
    "double",
    "unsigned char",
    "unsigned short",
    "unsigned int",
    "long long",
    "unsigned long long",
    "string",
    "arr",
    "fct int",
    "fct double",
    "fct long long"
    };

/*
 *  I intentionally broke the last format identifier in the Switchcast for readAr1dFromText.
 *  - I'm not sure which other functions or programs use it.
 */
#define ALLTYPECASES                                            \
            case BYTE:                                          \
                SWITCHCAST(byt,missbyt,signed char,BYTE,BYT,cBYT,compare_byts,"%10hhd","%hhd")          \
                break;                                          \
            case CHAR:                                          \
                SWITCHCAST(chr,misschr,char,CHAR,CHR,cCHR,compare_chrs,"%10c","%c")             \
                break;                                          \
            case SHORT:                                         \
                SWITCHCAST(shrt,missshrt,short,SHORT,SHT,cSHT,compare_shrts,"%10hd","%hd")              \
                break;                                          \
            case INT:                                           \
                SWITCHCAST(intg,missintg,int,INT,INTG,cINTG,compare_ints,"%10d","%d")               \
                break;                                          \
            case FLOAT:                                         \
                SWITCHCAST(flt,missflt,float,FLOAT,FLT,cFLT,compare_flts,"%10f","%f")               \
                break;                                          \
            case DOUBLE:                                        \
                SWITCHCAST(dbl,missdbl,double,DOUBLE,DBL,cDBL,compare_dbls,"%10lf","%lf")               \
                break;                                          \
            case UBYTE:                                         \
                SWITCHCAST(ubyt,missubyt,unsigned char,UBYTE,UBYT,cUBYT,compare_ubyts,"%10hhu","%hhu")      \
                break;                                          \
            case USHORT:                                        \
                SWITCHCAST(ushrt,missushrt,unsigned short,USHORT,USHT,cUSHT,compare_ushrts,"%10hu","%hu")       \
                break;                                          \
            case UINT:                                          \
                SWITCHCAST(uint,missuint,unsigned int,UINT,UINTG,cUINTG,compare_uints,"%10u","%u")      \
                break;                                          \
            case INT64:                                         \
                SWITCHCAST(int64,missint64,long long,INT64,LINT,cLINT,compare_int64s,"%10lld","%lld")           \
                break;                                          \
            case UINT64:                                        \
                SWITCHCAST(uint64,missuint64,unsigned long long,UINT64,ULINT,cULINT,compare_uint64s,"%10llu","%llu") \
                break;


#define ALLTYPECASES2                                           \
            case BYTE:                                          \
                SWITCHCAST2(byt,byt,signed char,BYTE,BYT,cBYT,compare_byts,"%10d","%10d")           \
                break;                                          \
            case CHAR:                                          \
                SWITCHCAST2(chr,chr,char,CHAR,CHR,cCHR,compare_chrs,"%10c","%10s")              \
                break;                                          \
            case SHORT:                                         \
                SWITCHCAST2(shrt,shrt,short,SHORT,SHT,cSHT,compare_shrts,"%10d","%10d")             \
                break;                                          \
            case INT:                                           \
                SWITCHCAST2(intg,intg,int,INT,INTG,cINTG,compare_ints,"%10d","%10d")                \
                break;                                          \
            case FLOAT:                                         \
                SWITCHCAST2(flt,flt,float,FLOAT,FLT,cFLT,compare_flts,"%10g","%10g")                \
                break;                                          \
            case DOUBLE:                                        \
                SWITCHCAST2(dbl,dbl,double,DOUBLE,DBL,cDBL,compare_dbls,"%10g","%10g")              \
                break;                                          \
            case UBYTE:                                         \
                SWITCHCAST2(ubyt,ubyt,unsigned char,UBYTE,UBYT,cUBYT,compare_ubyts,"%10d","%10d")       \
                break;                                          \
            case USHORT:                                        \
                SWITCHCAST2(ushrt,ushrt,unsigned short,USHORT,USHT,cUSHT,compare_ushrts,"%10d","%10d")      \
                break;                                          \
            case UINT:                                          \
                SWITCHCAST2(uint,uint,unsigned int,UINT,UINTG,cUINTG,compare_uints,"%10d","%10d")       \
                break;                                          \
            case INT64:                                         \
                SWITCHCAST2(int64,int64,long long,INT64,LINT,cLINT,compare_int64s,"%10d","%10d")            \
                break;                                          \
            case UINT64:                                        \
                SWITCHCAST2(uint64,uint64,unsigned long long,UINT64,ULINT,cULINT,compare_uint64s,"%10d","%10d") \
                break;


#ifndef  _ARRAY2_S_
#define  _ARRAY2_S_
    typedef long long typ_idx;
    typedef typ_idx   typ_dim;
    typedef int       typ_typ;

    #define N_TYPES_INT 7
    #define N_TYPES_FLT 2
    const typ_typ int_types[N_TYPES_INT] = { BYTE, SHORT, INT, UBYTE, UINT, INT64, UINT64 };
    const typ_typ flt_types[N_TYPES_FLT] = { FLOAT, DOUBLE };

/*  Need to implement typsize into all array storage and manipulator functions */
    typedef struct {
/*  typedef struct arr_struct { */      /* If I produce arrays of arrays, I need to declare struct this way */
        typ_dim n;                  /* number of dimensions */
    /*  typ_idx nlast; */           /* last dimension */
        typ_idx tlen;               /* total number of elements */
        size_t typsize;             /* sizeof type */
        typ_typ typ;                /* type of array */
    /*  arr_type typ;  */           /* enum type of array */
    /*  typ_idx tlast; */           /* last element of array */
    /*  typ_idx x;  */              /* len[nlast  ] */
    /*  typ_idx y;  */              /* len[nlast-1] */
    /*  typ_idx z;  */              /* len[nlast-2] */
    /*  typ_idx t;  */              /* len[nlast-3] */
    /*  int isalloc; */             /* Is the pointer internally allocated or point to some other data?
                                       - Array() calls should be set to 1 
                                       - assign1dtoNd() calls should be set to 0 
                                       - Also, some programs may want an assigned pointer freed with array,
                                         - then use a function like setAr2Alloc() */
        typ_idx *len;               /* int array with length of each dimension */
        typ_idx *mlen;              /* number of elements for one increment of a given dimension */
    /*  typ_idx *last;  */          /* last element of each dimension */
        /* The following correspond to pointers for each possible type of array */
        union {
            signed char *byt;           /* BYTE  */
            char *chr;                  /* CHAR   */
            short *shrt;                /* SHORT  */
            int *intg;                  /* INT    */
            float *flt;                 /* FLOAT  */
            double *dbl;                /* DOUBLE */
            unsigned char *ubyt;        /* UBYTE  */
            unsigned short *ushrt;      /* USHORT */
            unsigned int *uint;         /* UINT   */
            long long *int64;           /* INT64  */
            unsigned long long *uint64; /* UINT64 */
        /*  struct arr_struct **arrs; */ /* ARR    */
        /*  double *(*)();            */ /* pointer as array of function pointers returning double */
        };
        /* Could also add complex numbers.  Anything else? */
        /* The following correspond to missing values for each possible type of array */
        union {
            signed char missbyt;
            char misschr;
            short missshrt;
            int missintg;
            float missflt;
            double missdbl;
            unsigned char missubyt;
            unsigned short missushrt;
            unsigned int missuint;
            long long missint64;
            unsigned long long missuint64;
        /*  arr *missarr;    */  /* Not sure if this should be used, or just evaluate missing of all arrays in arrs */
        };
    } arr;

    typedef union{
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
    } MultiTypeVal;
#endif

#define typeOf(x) ((x)->typ)
#define typeOfar(x) x.typ

/*
 * These Functions initialize the size of each dimension of the arrays
 * They also fill each element with a value of 0
 *--------------------------------------------------------------------
 */
arr Array(typ_idx, int, ...);               /* Initialize an array from predetermined num of dims and dim lengths*/
arr ArrayFromList(typ_idx, int, typ_idx *); /* Initialize an array from list of dim lengths */
arr ArrayCpy(arr *);          /* Initialize an array using type and dimensions of another array */
arr NullArray();            /* Set an array to NULL before initialization or after freeAr */

/*
 * These functions map 1D arrays of pointers
 * to any dimension of arrays and free them
 *---------------------------------------------------
 */
arr assign1dtoNd(void *, typ_idx, int, ...);
arr assign1dtoNdFromList(void *, typ_idx, int, typ_idx *);

/*
 * You cannot use "=" to assign one array to another.
 * Instead you need to use these Copy functions.
 *---------------------------------------------------
 */
arr  copyAr(arr *);                   /* Copy an array */
void copyVals(arr *,arr *);             /* Copy values into same size array */
void copyArVals(arr *,arr *);      /* Use this instead of copyVals! */

/*
 * These Functions assign the specified value to all elements of the specified array
 *----------------------------------------------------------------------------------
 */
void fillAr(arr *, void *);           /* Fill an array with a specified value */
void fillArWithMiss(arr *);           /* Fill an array with its missing value */

/*
 * These Functions deallocate (free) the memory being used by the arrays
 * Use these functions prior to reinitializing an array with the Ar* functions
 *----------------------------------------------------------------------------
 */
void freeAr(arr *);                 /* Free memory of an array  */
void freeArShell(arr *);                /* Just free len and mlen arrays */

/*
 * These Functions Swaps bytes in array between little endian and big endian
 *----------------------------------------------------------------------------------
 */
 
#ifdef __linux__ 
   void ByteSwapAr16(arr *);          /* 16-bits (SHORT, USHORT)         */
   void ByteSwapAr32(arr *);          /* 32-bits (INT, FLOAT, UINT)      */
/*   void ByteSwapAr64(arr);    */      /* 64-bits (DOUBLE, INT64, UINT64) */
#elif _WIN32

#else

#endif


/*
 * These Functions access elements in an array for assignment
 * - use macros at top to cast into correct type.
 *   - DBL  for *(double *)address_of
 *   - cDBL for *(double *)address_of_c
 *-----------------------------------------------------------------------------------
 */
void *pntr_of(arr *);
void *address_of  (arr *, ...  );
void *address_of_c(arr *, typ_idx *);
void *address_of_i(arr *, typ_idx);

/*
 * These Functions initialize 1d c arrays
 * - can be used for initializing magic numbers in 1-d arrays
 *   - arr A = assign1dtoNd(dbls(5, 0.0625, 0.25, 0.375, 0.25, 0.0625),  1, DOUBLE, 5);
 *--------------------------------------------------------------------
 */
void *init0(typ_idx,int);       /* initializes 1d array of given length and type to zero */
int    *ints(typ_idx,...);      /* Initializes 1d array of integers of given length with multiple values */
double *dbls(typ_idx,...);      /* Initializes 1d array of doubles  of given length with multiple values
                               - if using literals, you must put a decimal (i.e. dbls(3, 1.,2.,3.) ) */
/* float  *flts(int,...); */    /* Initializes 1d array of floats   of given length with multiple values */
int isIdxEqual(typ_idx *,typ_idx *,typ_idx);

/*
 * These Functions handle missing values
 *--------------------------------------------------------------------
 */
void defaultMissing(arr *);
void copyMiss(arr *,arr *);
void *getMissAsType(arr *,int);
void *getMiss(arr *);
int isMiss(arr *,typ_idx);
int isMissc(arr *,typ_idx *);
int isMissIdx(arr *,...);
void setToMiss(arr *,typ_idx);
void setToMissc(arr *,typ_idx *);
void setToMissIdx(arr *,...);

/*
 * These Functions handle type macros
 *--------------------------------------------------------------------
 */
size_t typeSize(int);

/* 
 * Cast any array type to another with option to free original array if copying to itself
 *---------------------------------------------------------------------------------------
 */
arr castAr(arr *,int,int);
void *translateType(void *,char,char);


/*
 *-----------------
 *  Function Code  
 *-----------------
 */

void print_arr_exit(arr *restrict m){
    typ_idx j;
    fprintf(stderr,"print_arr_exit: m->n=%lld\n",m->n);
    fprintf(stderr,"print_arr_exit: m->tlen=%lld\n",m->tlen);
    fprintf(stderr,"print_arr_exit: m->typ=%d\n",m->typ);
    if (m->tlen != 1){
    for (j=0;j<m->n;++j){
        fprintf(stderr,"print_arr_exit: m->len[%lld] =%lld\n",j,m->len[j]);
        fprintf(stderr,"print_arr_exit: m->mlen[%lld]=%lld\n",j,m->mlen[j]);
    }
    }
    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)      \
        for (j=0;j<m->tlen;++j){ fprintf(stderr,fmt1" ",m->swtyp[j]); } \
        fputs("\n",stderr);
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in print_arr_exit: undefined type %d!\n",m->typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST
    exit(0);
}

void *pntr_of(arr *restrict m){
    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)      \
        return m->swtyp;
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in address_of_i: undefined type %d!\n",m->typ);
            print_arr_exit(m);
            break;
    }
    #undef SWITCHCAST

    return NULL;
}

void *address_of_i(arr *restrict m,  typ_idx idx){
    /* Added bounds checking */
    if ((idx >= m->tlen) || (idx < 0)){
        fprintf(stderr,"Error in address_of_i: idx must be from 0 to %lld, it was %lld!\n",m->tlen-1,idx);
        print_arr_exit(m);
    }
    
    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)      \
        return &(m->swtyp[idx]);
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in address_of_i: undefined type %d!\n",m->typ);
            print_arr_exit(m);
            break;
    }
    #undef SWITCHCAST

    return NULL;
}

typ_idx *c_from_idx(arr *restrict m, typ_idx idx){
    typ_idx *c;
    if (m->n == 0){
        c = NULL;
    } else {
        c = malloc(m->n*sizeof(typ_idx));

        typ_idx idx2 = idx;
        typ_idx j;
        for (j=0;j<m->n;++j){
            c[j]  = idx2/m->mlen[j];
            idx2 %= m->mlen[j];
        }
    }

    return c;
}

typ_idx idx_from_c(arr *m, typ_idx *c){
    typ_idx j;
    typ_idx idx = 0;
    if (m->tlen != 1){
        for (j=0;j<m->n;++j){ idx += c[j]*m->mlen[j]; }
    }
    return idx;
}

void *address_of_c(arr *restrict m, typ_idx *c){
    typ_idx idx = idx_from_c(m, c);

    return address_of_i(m, idx);
}

void *address_of(arr *restrict m,  ...){
    typ_idx j;
    void *rptr;

    if (m->n == 0){
        rptr = address_of_c(m, (typ_idx *)NULL);
    } else {
        typ_idx *c = malloc(m->n*sizeof(typ_idx));

        va_list arg_list;
        va_start(arg_list, m);
        for (j=0;j<m->n;++j){
            c[j] = va_arg(arg_list, typ_idx);
        }
        va_end(arg_list);

        rptr = address_of_c(m, c);
        free(c);
    }
    return rptr;
}


void *init0(typ_idx len,int typ){
    typ_idx i;
    size_t typsize = typeSize(typ);
    signed char *byt;
    char *chr;
    short *shrt;
    int *intg;
    float *flt;
    double *dbl;
    unsigned char *ubyt;
    unsigned short *ushrt;
    unsigned int *uint;
    long long *int64;
    unsigned long long *uint64;


    switch (typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2) \
        swtyp = NULL;                           \
        if (len > 0){                           \
            swtyp = malloc(typsize*len);        \
            for(i=0;i<len;++i){ swtyp[i] = 0; } \
        }                                       \
        return swtyp;
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in init0: undefined type %d!\n",typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

}   

int *ints(typ_idx len,...){
    typ_idx i;
    int *m = NULL;

    if (len > 0){
        m = malloc(sizeof(int)*len);

        va_list arg_list;
        va_start(arg_list, len);
        for(i=0;i<len;++i){
            m[i] = va_arg(arg_list, int);
        }
        va_end(arg_list);
    }
    return m;
}   

void set_ints_part(typ_idx ib,typ_idx ie,int *m, ...){
    typ_idx i;
    
    va_list arg_list;
    va_start(arg_list, m);
    for(i=ib;i<=ie;++i){
        m[i] = va_arg(arg_list, int);
    }
    va_end(arg_list);
    
    return;
}   

void set_ints(typ_idx len,int *m, ...){
    typ_idx i;
    if (len > 0){
        va_list arg_list;
        va_start(arg_list, m);
        for(i=0;i<len;++i){
            m[i] = va_arg(arg_list, int);
        }
        va_end(arg_list);
    }
    return;
}   

void set_ints_to_val_part(typ_idx ib,typ_idx ie,int *m,int val){
    typ_idx i;
    for(i=ib;i<=ie;++i){
        m[i] = val;
    }
    return;
}   

void set_ints_to_val(typ_idx len,int *m,int val){
    typ_idx i;
    if (len > 0){
        for(i=0;i<len;++i){
            m[i] = val;
        }
    }
    return;
}   


long long *int64s(typ_idx len,...){
    typ_idx i;
    long long *m = NULL;

    if (len > 0){
        m = malloc(sizeof(long long)*len);

        va_list arg_list;
        va_start(arg_list, len);
        for(i=0;i<len;++i){
            m[i] = va_arg(arg_list, long long);
        }
        va_end(arg_list);
    }
    return m;
}   

void set_int64s_part(typ_idx ib,typ_idx ie,long long *m, ...){
    typ_idx i;
    
    va_list arg_list;
    va_start(arg_list, m);
    for(i=ib;i<=ie;++i){
        m[i] = va_arg(arg_list, long long);
    }
    va_end(arg_list);
    
    return;
}   

void set_int64s(typ_idx len,long long *m, ...){
    typ_idx i;
    if (len > 0){
        va_list arg_list;
        va_start(arg_list, m);
        for(i=0;i<len;++i){
            m[i] = va_arg(arg_list, long long);
        }
        va_end(arg_list);
    }
    return;
}   

void set_int64s_to_val_part(typ_idx ib,typ_idx ie,long long *m,long long val){
    typ_idx i;
    for(i=ib;i<=ie;++i){
        m[i] = val;
    }
    return;
}   

void set_int64s_to_val(typ_idx len,long long *m,long long val){
    typ_idx i;
    if (len > 0){
        for(i=0;i<len;++i){
            m[i] = val;
        }
    }
    return;
}   


double *dbls(typ_idx len,...){
    typ_idx i;
    double *m = NULL;

    if (len > 0){
        m = malloc(sizeof(double)*len);

        va_list arg_list;
        va_start(arg_list, len);
        for(i=0;i<len;++i){
            m[i] = va_arg(arg_list, double);
        }
        va_end(arg_list);
    }
    return m;
}

void set_dbls_part(typ_idx ib,typ_idx ie,double *m, ...){
    typ_idx i;
    
    va_list arg_list;
    va_start(arg_list, m);
    for(i=ib;i<=ie;++i){
        m[i] = va_arg(arg_list, double);
    }
    va_end(arg_list);
    
    return;
}   

void set_dbls(typ_idx len,double *m, ...){
    typ_idx i;
    if (len > 0){
        va_list arg_list;
        va_start(arg_list, m);
        for(i=0;i<len;++i){
            m[i] = va_arg(arg_list, double);
        }
        va_end(arg_list);
    }
    return;
}

void set_dbls_to_val_part(typ_idx ib,typ_idx ie,double *m,double val){
    typ_idx i;
    for(i=ib;i<=ie;++i){
        m[i] = val;
    }
    return;
}

void set_dbls_to_val(typ_idx len,double *m,double val){
    typ_idx i;
    if (len > 0){
        for(i=0;i<len;++i){
            m[i] = val;
        }
    }
    return;
}


arr **arrs(typ_idx len,...){
    typ_idx i;
    arr **m = NULL;

    if (len > 0){
        m = malloc(sizeof(arr *)*len);

        va_list arg_list;
        va_start(arg_list, len);
        for(i=0;i<len;++i){
            m[i] = va_arg(arg_list, arr *);
        }
        va_end(arg_list);
    }
    return m;
}   

void set_arrs_part(typ_idx ib,typ_idx ie,arr **m, ...){
    typ_idx i;
    
    va_list arg_list;
    va_start(arg_list, m);
    for(i=ib;i<=ie;++i){
        m[i] = va_arg(arg_list, arr *);
    }
    va_end(arg_list);
    
    return;
}   

void set_arrs(typ_idx len,arr **m, ...){
    typ_idx i;
    if (len > 0){
        va_list arg_list;
        va_start(arg_list, m);
        for(i=0;i<len;++i){
            m[i] = va_arg(arg_list, arr *);
        }
        va_end(arg_list);
    }
    return;
}


/*  I guess ... doesn't allow floats, would need to downcast doubles    */
/*
float *flts(typ_idx len,...){
    typ_idx i;
    float *m = malloc(sizeof(float)*len);


    va_list arg_list;
    va_start(arg_list, len);
    for(i=0;i<len;++i){
        m[i] = (float)va_arg(arg_list, double);
    }
    va_end(arg_list);
    return m;
}
 */

int isIdxEqual(typ_idx *a,typ_idx *b,typ_idx n){
    typ_idx i;
    for(i=0;i<n;++i){
        if( a[i] != b[i] ){ return 0; }
    }
    return 1;
}

void defaultMissing(arr *m){
    switch (m->typ) {
        case BYTE:
            m->missbyt    = -127;
            break;
        case CHAR:
            m->misschr    = 0;
            break;                                      
        case SHORT:                                         
            m->missshrt   = -999;
            break;                                      
        case INT:                                           
            m->missintg   = -999;
            break;                                      
        case FLOAT:                                         
            m->missflt    = -999.0;
            break;                                      
        case DOUBLE:                                        
            m->missdbl    = -999.0;
            break;                                      
        case UBYTE:                                         
            m->missubyt   = 255;
            break;                                      
        case USHORT:                                        
            m->missushrt  = 65535;
            break;                                      
        case UINT:                                          
            m->missuint   = 4294967295U;
            break;                                      
        case INT64:                                         
            m->missint64  = -9223372036854775807LL;
            break;                                      
        case UINT64:                                        
            m->missuint64 = 18446744073709551615ULL;
            break;
        default:
            fprintf(stderr,"Error in defaultMissing: undefined type! m->typ=%d\n",m->typ);
            print_arr_exit(m);
            break;
    }

    return;
}

void *getDefaultMissAsType(int typ){
    void *rval = NULL;
    switch (typ) {
        case BYTE:
            rval = malloc(sizeof(signed char));
            *(signed char *)rval = -127;
            return rval;
            break;
        case CHAR:
            rval = malloc(sizeof(char));
            *(char *)rval = 0;
            return rval;
            break;
        case SHORT:                                         
            rval = malloc(sizeof(short));
            *(short *)rval = -999;
            return rval;
            break;
        case INT:                                           
            rval = malloc(sizeof(int));
            *(int *)rval = -999;
            return rval;
            break;
        case FLOAT:                                         
            rval = malloc(sizeof(float));
            *(float *)rval = -999.0;
            return rval;
            break;
        case DOUBLE:                                        
            rval = malloc(sizeof(double));
            *(double *)rval = -999.0;
            return rval;
            break;
        case UBYTE:                                         
            rval = malloc(sizeof(unsigned char));
            *(unsigned char *)rval = 255;
            return rval;
            break;
        case USHORT:                                        
            rval = malloc(sizeof(unsigned short));
            *(unsigned short *)rval = 65535;
            return rval;
            break;
        case UINT:                                          
            rval = malloc(sizeof(unsigned int));
            *(unsigned int *)rval = 4294967295U;
            return rval;
            break;
        case INT64:                                         
            rval = malloc(sizeof(long long));
            *(long long *)rval = -9223372036854775807LL;
            return rval;
            break;
        case UINT64:                                        
            rval = malloc(sizeof(unsigned long long));
            *(unsigned long long *)rval = 18446744073709551615ULL;
            return rval;
            break;
        default:
            fprintf(stderr,"Error in getDefaultMissAsType: undefined type! typ=%d\n",typ);
            exit(0);
            break;
    }
    return rval;
}

void copyMiss(arr *m,arr *restrict n){
    defaultMissing(m);  /* This line is probably not needed, but for safety we'll keep it */

    if (m->typ == n->typ){
        switch (m->typ){
        #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
            m->swmtyp = n->swmtyp;
            ALLTYPECASES
            default:
                fprintf(stderr,"Error in copyMiss: undefined type! m->typ=%d\n",m->typ);
                print_arr_exit(m);
                break;
        }
        #undef SWITCHCAST
    } else {
        /*
         *  Need to process missing values more rigorously
         *  - I can't just cast values from higher precision to lower precision
         *  - I need to check the value first.
         *  - Then keep default missing value if value is uncastable.
         */
        switch (m->typ) {
            case BYTE:
                switch (n->typ) {
                    case BYTE:
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;
                    case CHAR:
                        #if MAX_BYTE < MAX_CHAR
                        if ( (n->misschr <= MAX_BYTE) )
                        #endif
                        { m->missbyt = (signed char)n->misschr; }
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_BYTE) && (n->missshrt <= MAX_BYTE) ){
                            m->missbyt = (signed char)n->missshrt;                       
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_BYTE) && (n->missintg <= MAX_BYTE) ){
                            m->missbyt = (signed char)n->missintg;                   
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_BYTE) && (n->missflt <= MAX_BYTE) ){
                            m->missbyt = (signed char)n->missflt;                        
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_BYTE) && (n->missdbl <= MAX_BYTE) ){
                            m->missbyt = (signed char)n->missdbl;                        
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        if ( (n->missubyt <= MAX_BYTE) ){
                            m->missbyt = (signed char)n->missubyt;               
                        }                                           
                        break;                                      
                    case USHORT:                                        
                        if ( (n->missushrt <= MAX_BYTE) ){
                            m->missbyt = (signed char)n->missushrt;              
                        }                                           
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_BYTE) ){
                            m->missbyt = (signed char)n->missuint;               
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_BYTE) && (n->missint64 <= MAX_BYTE) ){
                            m->missbyt = (signed char)n->missint64;                  
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_BYTE) ){
                            m->missbyt = (signed char)n->missuint64;         
                        }                                           
                        break;
                    default:
                        fprintf(stderr,"Error in copyMiss: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case CHAR:                                          
                switch (n->typ) {
                    case BYTE:
                        #if MAX_BYTE < MAX_CHAR
                        if ( (n->missbyt >= MIN_CHAR) )
                        #endif
                        { m->misschr = (char)n->missbyt; }
                        break;
                    case CHAR:
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_CHAR) && (n->missshrt <= MAX_CHAR) ){
                            m->misschr = (char)n->missshrt;                      
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_CHAR) && (n->missintg <= MAX_CHAR) ){
                            m->misschr = (char)n->missintg;                  
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_CHAR) && (n->missflt <= MAX_CHAR) ){
                            m->misschr = (char)n->missflt;                       
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_CHAR) && (n->missdbl <= MAX_CHAR) ){
                            m->misschr = (char)n->missdbl;                       
                        }                                           
                        break;                                      
                    case UBYTE: /* treating the same as CHAR, but this isn't necessarily true */
                        m->misschr = (char)n->missubyt;                              
                        break;                                      
                    case USHORT:                                        
                        if ( (n->missushrt <= MAX_CHAR) ){
                            m->misschr = (char)n->missushrt;             
                        }                                           
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_CHAR) ){
                            m->misschr = (char)n->missuint;              
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_CHAR) && (n->missint64 <= MAX_CHAR) ){
                            m->misschr = (char)n->missint64;                 
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_CHAR) ){
                            m->misschr = (char)n->missuint64;            
                        }                                           
                        break;
                    default:
                        fprintf(stderr,"Error in copyMiss: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case SHORT:                                         
                switch (n->typ) {
                    case BYTE:
                        m->missshrt = (short)n->missbyt;
                        break;
                    case CHAR:
                        m->missshrt = (short)n->misschr;
                        break;                                      
                    case SHORT:                                         
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_SHORT) && (n->missintg <= MAX_SHORT) ){
                            m->missshrt = (short)n->missintg;                    
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_SHORT) && (n->missflt <= MAX_SHORT) ){
                            m->missshrt = (short)n->missflt;                     
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_SHORT) && (n->missdbl <= MAX_SHORT) ){
                            m->missshrt = (short)n->missdbl;                     
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        m->missshrt = (short)n->missubyt;
                        break;                                      
                    case USHORT:                                        
                        if ( (n->missushrt <= MAX_SHORT) ){
                            m->missshrt = (short)n->missushrt;               
                        }                                           
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_SHORT) ){
                            m->missshrt = (short)n->missuint;                
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_SHORT) && (n->missint64 <= MAX_SHORT) ){
                            m->missshrt = (short)n->missint64;                   
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_SHORT) ){
                            m->missshrt = (short)n->missuint64;          
                        }                                           
                        break;
                    default:
                        fprintf(stderr,"Error in copyMiss: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case INT:                                           
                switch (n->typ) {
                    case BYTE:
                        m->missintg = (int)n->missbyt;
                        break;
                    case CHAR:
                        m->missintg = (int)n->misschr;
                        break;                                      
                    case SHORT:                                         
                        m->missintg = (int)n->missshrt;
                        break;                                      
                    case INT:                                           
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_INT) && (n->missflt <= MAX_INT) ){
                            m->missintg = (int)n->missflt;                       
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_INT) && (n->missdbl <= MAX_INT) ){
                            m->missintg = (int)n->missdbl;                       
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        m->missintg = (int)n->missubyt;
                        break;                                      
                    case USHORT:    /* INT should be greater than USHORT unless same typesize */
                        m->missintg = (int)n->missushrt;
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_INT) ){
                            m->missintg = (int)n->missuint;              
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_INT) && (n->missint64 <= MAX_INT) ){
                            m->missintg = (int)n->missint64;                 
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_INT) ){
                            m->missintg = (int)n->missuint64;            
                        }                                           
                        break;
                    default:
                        fprintf(stderr,"Error in copyMiss: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case FLOAT:                                         
                switch (n->typ) {
                    case BYTE:
                        m->missflt = (float)n->missbyt;
                        break;
                    case CHAR:
                        m->missflt = (float)n->misschr;
                        break;                                      
                    case SHORT:                                         
                        m->missflt = (float)n->missshrt;
                        break;                                      
                    case INT:                                           
                        m->missflt = (float)n->missintg;
                        break;                                      
                    case FLOAT:                                         
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_FLOAT) && (n->missdbl <= MAX_FLOAT) ){
                            m->missflt = (float)n->missdbl;                      
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        m->missflt = (float)n->missubyt;
                        break;                                      
                    case USHORT:                                        
                        m->missflt = (float)n->missushrt;
                        break;                                      
                    case UINT:                                          
                        m->missflt = (float)n->missuint;
                        break;                                      
                    case INT64:                                         
                        m->missflt = (float)n->missint64;
                        break;                                      
                    case UINT64:                                        
                        m->missflt = (float)n->missuint64;
                        break;
                    default:
                        fprintf(stderr,"Error in copyMiss: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case DOUBLE:                                        
                switch (n->typ) {
                    case BYTE:
                        m->missdbl = (double)n->missbyt;
                        break;
                    case CHAR:
                        m->missdbl = (double)n->misschr;
                        break;                                      
                    case SHORT:                                         
                        m->missdbl = (double)n->missshrt;
                        break;                                      
                    case INT:                                           
                        m->missdbl = (double)n->missintg;
                        break;                                      
                    case FLOAT:                                         
                        m->missdbl = (double)n->missflt;
                        break;                                      
                    case DOUBLE:                                        
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case UBYTE:                                         
                        m->missdbl = (double)n->missubyt;
                        break;                                      
                    case USHORT:                                        
                        m->missdbl = (double)n->missushrt;
                        break;                                      
                    case UINT:                                          
                        m->missdbl = (double)n->missuint;
                        break;                                      
                    case INT64:                                         
                        m->missdbl = (double)n->missint64;
                        break;                                      
                    case UINT64:                                        
                        m->missdbl = (double)n->missuint64;
                        break;
                    default:
                        fprintf(stderr,"Error in copyMiss: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case UBYTE:                                         
                switch (n->typ) {
                    case BYTE:
                        if ( (n->missbyt >= MIN_UBYTE) ){
                            m->missubyt = (unsigned char)n->missbyt;
                        }
                        break;
                    case CHAR:  /* treating CHAR and UBYTE as equal */
                        m->missubyt = (unsigned char)n->misschr;
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_UBYTE) && (n->missshrt <= MAX_UBYTE) ){
                            m->missubyt = (unsigned char)n->missshrt;                        
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_UBYTE) && (n->missintg <= MAX_UBYTE) ){
                            m->missubyt = (unsigned char)n->missintg;                    
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_UBYTE) && (n->missflt <= MAX_UBYTE) ){
                            m->missubyt = (unsigned char)n->missflt;                     
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_UBYTE) && (n->missdbl <= MAX_UBYTE) ){
                            m->missubyt = (unsigned char)n->missdbl;                     
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case USHORT:                                        
                        if ( (n->missushrt <= MAX_UBYTE) ){
                            m->missubyt = (unsigned char)n->missushrt;               
                        }                                           
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_UBYTE) ){
                            m->missubyt = (unsigned char)n->missuint;                
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_UBYTE) && (n->missint64 <= MAX_UBYTE) ){
                            m->missubyt = (unsigned char)n->missint64;                   
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_UBYTE) ){
                            m->missubyt = (unsigned char)n->missuint64;          
                        }                                           
                        break;
                    default:
                        fprintf(stderr,"Error in copyMiss: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case USHORT:                                        
                switch (n->typ) {
                    case BYTE:
                        if ( (n->missbyt >= MIN_USHORT) ){
                            m->missushrt = (unsigned short)n->missbyt;
                        }
                        break;
                    case CHAR:
                        m->missushrt = (unsigned short)n->misschr;
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_USHORT) ){
                            m->missushrt = (unsigned short)n->missshrt;                      
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_USHORT) && (n->missintg <= MAX_USHORT) ){
                            m->missushrt = (unsigned short)n->missintg;                  
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_USHORT) && (n->missflt <= MAX_USHORT) ){
                            m->missushrt = (unsigned short)n->missflt;                       
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_USHORT) && (n->missdbl <= MAX_USHORT) ){
                            m->missushrt = (unsigned short)n->missdbl;                       
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        m->missushrt = (unsigned short)n->missubyt;
                        break;                                      
                    case USHORT:                                        
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_USHORT) ){
                            m->missushrt = (unsigned short)n->missuint;              
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_USHORT) && (n->missint64 <= MAX_USHORT) ){
                            m->missushrt = (unsigned short)n->missint64;                 
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_USHORT) ){
                            m->missushrt = (unsigned short)n->missuint64;            
                        }                                           
                        break;
                    default:
                        fprintf(stderr,"Error in copyMiss: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case UINT:                                          
                switch (n->typ) {
                    case BYTE:
                        if ( (n->missbyt >= MIN_UINT) ){
                            m->missuint = (unsigned int)n->missbyt;
                        }
                        break;
                    case CHAR:
                        m->missuint = (unsigned int)n->misschr;
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_UINT) ){
                            m->missuint = (unsigned int)n->missshrt;                     
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_UINT) ){
                            m->missuint = (unsigned int)n->missintg;                 
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_UINT) && (n->missflt <= MAX_UINT) ){
                            m->missuint = (unsigned int)n->missflt;                      
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_UINT) && (n->missdbl <= MAX_UINT) ){
                            m->missuint = (unsigned int)n->missdbl;                      
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        m->missuint = (unsigned int)n->missubyt;
                        break;                                      
                    case USHORT:                                        
                        m->missuint = (unsigned int)n->missushrt;
                        break;                                      
                    case UINT:                                          
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_UINT) && (n->missint64 <= MAX_UINT) ){
                            m->missuint = (unsigned int)n->missint64;                    
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_UINT) ){
                            m->missuint = (unsigned int)n->missuint64;           
                        }                                           
                        break;
                    default:
                        fprintf(stderr,"Error in copyMiss: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case INT64:                                         
                switch (n->typ) {
                    case BYTE:
                        m->missint64 = (long long)n->missbyt;
                        break;
                    case CHAR:
                        m->missint64 = (long long)n->misschr;
                        break;                                      
                    case SHORT:                                         
                        m->missint64 = (long long)n->missshrt;
                        break;                                      
                    case INT:                                           
                        m->missint64 = (long long)n->missintg;
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_INT64) && (n->missflt <= MAX_INT64) ){
                            m->missint64 = (long long)n->missflt;                        
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_INT64) && (n->missdbl <= MAX_INT64) ){
                            m->missint64 = (long long)n->missdbl;                        
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        m->missint64 = (long long)n->missubyt;
                        break;                                      
                    case USHORT:                                        
                        m->missint64 = (long long)n->missushrt;
                        break;                                      
                    case UINT:  /* hopefully UINT is smaller than INT64, could check typsize */
                        m->missint64 = (long long)n->missuint;
                        break;                                      
                    case INT64:                                         
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_INT64) ){
                            m->missint64 = (long long)n->missuint64;         
                        }                                           
                        break;
                    default:
                        fprintf(stderr,"Error in copyMiss: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case UINT64:                                        
                switch (n->typ) {
                    case BYTE:
                        if ( (n->missbyt >= MIN_UINT64) ){
                            m->missuint64 = (unsigned long long)n->missbyt;
                        }
                        break;
                    case CHAR:
                        m->missuint64 = (unsigned long long)n->misschr;
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_UINT64) ){
                            m->missuint64 = (unsigned long long)n->missshrt;                     
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_UINT64) ){
                            m->missuint64 = (unsigned long long)n->missintg;                 
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_UINT64) && (n->missflt <= MAX_UINT64) ){
                            m->missuint64 = (unsigned long long)n->missflt;                      
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_UINT64) && (n->missdbl <= MAX_UINT64) ){
                            m->missuint64 = (unsigned long long)n->missdbl;                      
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        m->missuint64 = (unsigned long long)n->missubyt;
                        break;                                      
                    case USHORT:                                        
                        m->missuint64 = (unsigned long long)n->missushrt;
                        break;                                      
                    case UINT:                                          
                        m->missuint64 = (unsigned long long)n->missuint;
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_UINT64) ){
                            m->missuint64 = (unsigned long long)n->missint64;                    
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;
                    default:
                        fprintf(stderr,"Error in copyMiss: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            default:
                fprintf(stderr,"Error in copyMiss: undefined type! m->typ=%d\n",m->typ);
                print_arr_exit(m);
                break;
        }
    }

    return;
}

void *getMissAsType(arr *restrict n,int outtyp){
    signed char *byt;           /* BYTE  */
    char *chr;                  /* CHAR   */
    short *shrt;                /* SHORT  */
    int *intg;                  /* INT    */
    float *flt;                 /* FLOAT  */
    double *dbl;                /* DOUBLE */
    unsigned char *ubyt;        /* UBYTE  */
    unsigned short *ushrt;      /* USHORT */
    unsigned int *uint;         /* UINT   */
    long long *int64;           /* INT64  */
    unsigned long long *uint64; /* UINT64 */


    if (outtyp == n->typ){
        switch (outtyp){
        #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
            swtyp = malloc(sizeof(swcast)); \
            *swtyp = n->swmtyp;  \
            return swtyp;
            ALLTYPECASES
            default:
                fprintf(stderr,"Error in getMissAsType: undefined type! outtyp=%d\n",outtyp);
                print_arr_exit(n);
                break;
        }
    #undef SWITCHCAST
    } else {
        /*
         *  Need to process missing values more rigorously
         *  - I can't just cast values from higher precision to lower precision
         *  - I need to check the value first.
         *  - Then keep default missing value if value is uncastable.
         */
        switch (outtyp) {
            case BYTE:
                switch (n->typ) {
                    case BYTE:
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;
                    case CHAR:
                        #if MAX_BYTE < MAX_CHAR
                        if ( (n->misschr <= MAX_BYTE) )
                        #endif
                        {
                            byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->misschr;
                            return byt;
                        }
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_BYTE) && (n->missshrt <= MAX_BYTE) ){
                            byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->missshrt;                     
                            return byt;
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_BYTE) && (n->missintg <= MAX_BYTE) ){
                            byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->missintg;                 
                            return byt;
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_BYTE) && (n->missflt <= MAX_BYTE) ){
                            byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->missflt;                      
                            return byt;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_BYTE) && (n->missdbl <= MAX_BYTE) ){
                            byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->missdbl;                      
                            return byt;
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        if ( (n->missubyt <= MAX_BYTE) ){
                            byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->missubyt;             
                            return byt;
                        }                                           
                        break;                                      
                    case USHORT:                                        
                        if ( (n->missushrt <= MAX_BYTE) ){
                            byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->missushrt;                
                            return byt;
                        }                                           
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_BYTE) ){
                            byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->missuint;             
                            return byt;
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_BYTE) && (n->missint64 <= MAX_BYTE) ){
                            byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->missint64;                    
                            return byt;
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_BYTE) ){
                            byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->missuint64;           
                            return byt;
                        }                                           
                        break;
                    default:
                        fprintf(stderr,"Error in getMissAsType: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case CHAR:                                          
                switch (n->typ) {
                    case BYTE:
                        #if MAX_BYTE < MAX_CHAR
                        if ( (n->missbyt >= MIN_CHAR) )
                        #endif
                        {
                            chr = malloc(sizeof(char));
                            *chr = (char)n->missbyt;
                            return chr;
                        }
                        break;
                    case CHAR:
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_CHAR) && (n->missshrt <= MAX_CHAR) ){
                            chr = malloc(sizeof(char));
                            *chr = (char)n->missshrt;                        
                            return chr;
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_CHAR) && (n->missintg <= MAX_CHAR) ){
                            chr = malloc(sizeof(char));
                            *chr = (char)n->missintg;                    
                            return chr;
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_CHAR) && (n->missflt <= MAX_CHAR) ){
                            chr = malloc(sizeof(char));
                            *chr = (char)n->missflt;                     
                            return chr;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_CHAR) && (n->missdbl <= MAX_CHAR) ){
                            chr = malloc(sizeof(char));
                            *chr = (char)n->missdbl;                     
                            return chr;
                        }                                           
                        break;                                      
                    case UBYTE: /* treating the same as CHAR, but this isn't necessarily true */
                        chr = malloc(sizeof(char));
                        *chr = (char)n->missubyt;                                
                            return chr;
                        break;                                      
                    case USHORT:                                        
                        if ( (n->missushrt <= MAX_CHAR) ){
                            chr = malloc(sizeof(char));
                            *chr = (char)n->missushrt;               
                            return chr;
                        }                                           
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_CHAR) ){
                            chr = malloc(sizeof(char));
                            *chr = (char)n->missuint;                
                            return chr;
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_CHAR) && (n->missint64 <= MAX_CHAR) ){
                            chr = malloc(sizeof(char));
                            *chr = (char)n->missint64;                   
                            return chr;
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_CHAR) ){
                            chr = malloc(sizeof(char));
                            *chr = (char)n->missuint64;          
                            return chr;
                        }                                           
                        break;
                    default:
                        fprintf(stderr,"Error in getMissAsType: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case SHORT:                                         
                switch (n->typ) {
                    case BYTE:
                        shrt = malloc(sizeof(short));
                        *shrt = (short)n->missbyt;
                            return shrt;
                        break;
                    case CHAR:
                        shrt = malloc(sizeof(short));
                        *shrt = (short)n->misschr;
                            return shrt;
                        break;                                      
                    case SHORT:                                         
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_SHORT) && (n->missintg <= MAX_SHORT) ){
                            shrt = malloc(sizeof(short));
                            *shrt = (short)n->missintg;                  
                            return shrt;
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_SHORT) && (n->missflt <= MAX_SHORT) ){
                            shrt = malloc(sizeof(short));
                            *shrt = (short)n->missflt;                       
                            return shrt;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_SHORT) && (n->missdbl <= MAX_SHORT) ){
                            shrt = malloc(sizeof(short));
                            *shrt = (short)n->missdbl;                       
                            return shrt;
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        shrt = malloc(sizeof(short));
                        *shrt = (short)n->missubyt;
                            return shrt;
                        break;                                      
                    case USHORT:                                        
                        if ( (n->missushrt <= MAX_SHORT) ){
                            shrt = malloc(sizeof(short));
                            *shrt = (short)n->missushrt;             
                            return shrt;
                        }                                           
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_SHORT) ){
                            shrt = malloc(sizeof(short));
                            *shrt = (short)n->missuint;              
                            return shrt;
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_SHORT) && (n->missint64 <= MAX_SHORT) ){
                            shrt = malloc(sizeof(short));
                            *shrt = (short)n->missint64;                 
                            return shrt;
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_SHORT) ){
                            shrt = malloc(sizeof(short));
                            *shrt = (short)n->missuint64;            
                            return shrt;
                        }                                           
                        break;
                    default:
                        fprintf(stderr,"Error in getMissAsType: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case INT:                                           
                switch (n->typ) {
                    case BYTE:
                        intg = malloc(sizeof(int));
                        *intg = (int)n->missbyt;
                            return intg;
                        break;
                    case CHAR:
                        intg = malloc(sizeof(int));
                        *intg = (int)n->misschr;
                            return intg;
                        break;                                      
                    case SHORT:                                         
                        intg = malloc(sizeof(int));
                        *intg = (int)n->missshrt;
                            return intg;
                        break;                                      
                    case INT:                                           
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_INT) && (n->missflt <= MAX_INT) ){
                            intg = malloc(sizeof(int));
                            *intg = (int)n->missflt;                     
                            return intg;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_INT) && (n->missdbl <= MAX_INT) ){
                            intg = malloc(sizeof(int));
                            *intg = (int)n->missdbl;                     
                            return intg;
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        intg = malloc(sizeof(int));
                        *intg = (int)n->missubyt;
                            return intg;
                        break;                                      
                    case USHORT:    /* INT should be greater than USHORT unless same typesize */
                        intg = malloc(sizeof(int));
                        *intg = (int)n->missushrt;
                            return intg;
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_INT) ){
                            intg = malloc(sizeof(int));
                            *intg = (int)n->missuint;                
                            return intg;
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_INT) && (n->missint64 <= MAX_INT) ){
                            intg = malloc(sizeof(int));
                            *intg = (int)n->missint64;                   
                            return intg;
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_INT) ){
                            intg = malloc(sizeof(int));
                            *intg = (int)n->missuint64;          
                            return intg;
                        }                                           
                        break;
                    default:
                        fprintf(stderr,"Error in getMissAsType: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case FLOAT:                                         
                switch (n->typ) {
                    case BYTE:
                        flt = malloc(sizeof(float));
                        *flt = (float)n->missbyt;
                            return flt;
                        break;
                    case CHAR:
                        flt = malloc(sizeof(float));
                        *flt = (float)n->misschr;
                            return flt;
                        break;                                      
                    case SHORT:                                         
                        flt = malloc(sizeof(float));
                        *flt = (float)n->missshrt;
                            return flt;
                        break;                                      
                    case INT:                                           
                        flt = malloc(sizeof(float));
                        *flt = (float)n->missintg;
                            return flt;
                        break;                                      
                    case FLOAT:                                         
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_FLOAT) && (n->missdbl <= MAX_FLOAT) ){
                            flt = malloc(sizeof(float));
                            *flt = (float)n->missdbl;                        
                            return flt;
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        flt = malloc(sizeof(float));
                        *flt = (float)n->missubyt;
                            return flt;
                        break;                                      
                    case USHORT:                                        
                        flt = malloc(sizeof(float));
                        *flt = (float)n->missushrt;
                            return flt;
                        break;                                      
                    case UINT:                                          
                        flt = malloc(sizeof(float));
                        *flt = (float)n->missuint;
                            return flt;
                        break;                                      
                    case INT64:                                         
                        flt = malloc(sizeof(float));
                        *flt = (float)n->missint64;
                            return flt;
                        break;                                      
                    case UINT64:                                        
                        flt = malloc(sizeof(float));
                        *flt = (float)n->missuint64;
                            return flt;
                        break;
                    default:
                        fprintf(stderr,"Error in getMissAsType: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case DOUBLE:                                        
                switch (n->typ) {
                    case BYTE:
                        dbl = malloc(sizeof(double));
                        *dbl = (double)n->missbyt;
                            return dbl;
                        break;
                    case CHAR:
                        dbl = malloc(sizeof(double));
                        *dbl = (double)n->misschr;
                            return dbl;
                        break;                                      
                    case SHORT:                                         
                        dbl = malloc(sizeof(double));
                        *dbl = (double)n->missshrt;
                            return dbl;
                        break;                                      
                    case INT:                                           
                        dbl = malloc(sizeof(double));
                        *dbl = (double)n->missintg;
                            return dbl;
                        break;                                      
                    case FLOAT:                                         
                        dbl = malloc(sizeof(double));
                        *dbl = (double)n->missflt;
                            return dbl;
                        break;                                      
                    case DOUBLE:                                        
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case UBYTE:                                         
                        dbl = malloc(sizeof(double));
                        *dbl = (double)n->missubyt;
                            return dbl;
                        break;                                      
                    case USHORT:                                        
                        dbl = malloc(sizeof(double));
                        *dbl = (double)n->missushrt;
                            return dbl;
                        break;                                      
                    case UINT:                                          
                        dbl = malloc(sizeof(double));
                        *dbl = (double)n->missuint;
                            return dbl;
                        break;                                      
                    case INT64:                                         
                        dbl = malloc(sizeof(double));
                        *dbl = (double)n->missint64;
                            return dbl;
                        break;                                      
                    case UINT64:                                        
                        dbl = malloc(sizeof(double));
                        *dbl = (double)n->missuint64;
                            return dbl;
                        break;
                    default:
                        fprintf(stderr,"Error in getMissAsType: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case UBYTE:                                         
                switch (n->typ) {
                    case BYTE:
                        if ( (n->missbyt >= MIN_UBYTE) ){
                            ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->missbyt;
                            return ubyt;
                        }
                        break;
                    case CHAR:  /* treating CHAR and UBYTE as equal */
                        ubyt = malloc(sizeof(unsigned char));
                        *ubyt = (unsigned char)n->misschr;
                            return ubyt;
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_UBYTE) && (n->missshrt <= MAX_UBYTE) ){
                            ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->missshrt;                      
                            return ubyt;
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_UBYTE) && (n->missintg <= MAX_UBYTE) ){
                            ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->missintg;                  
                            return ubyt;
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_UBYTE) && (n->missflt <= MAX_UBYTE) ){
                            ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->missflt;                       
                            return ubyt;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_UBYTE) && (n->missdbl <= MAX_UBYTE) ){
                            ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->missdbl;                       
                            return ubyt;
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case USHORT:                                        
                        if ( (n->missushrt <= MAX_UBYTE) ){
                            ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->missushrt;             
                            return ubyt;
                        }                                           
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_UBYTE) ){
                            ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->missuint;              
                            return ubyt;
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_UBYTE) && (n->missint64 <= MAX_UBYTE) ){
                            ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->missint64;                 
                            return ubyt;
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_UBYTE) ){
                            ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->missuint64;            
                            return ubyt;
                        }                                           
                        break;
                    default:
                        fprintf(stderr,"Error in getMissAsType: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case USHORT:                                        
                switch (n->typ) {
                    case BYTE:
                        if ( (n->missbyt >= MIN_USHORT) ){
                            ushrt = malloc(sizeof(unsigned short));
                            *ushrt = (unsigned short)n->missbyt;
                            return ushrt;
                        }
                        break;
                    case CHAR:
                        ushrt = malloc(sizeof(unsigned short));
                        *ushrt = (unsigned short)n->misschr;
                            return ushrt;
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_USHORT) ){
                            ushrt = malloc(sizeof(unsigned short));
                            *ushrt = (unsigned short)n->missshrt;                        
                            return ushrt;
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_USHORT) && (n->missintg <= MAX_USHORT) ){
                            ushrt = malloc(sizeof(unsigned short));
                            *ushrt = (unsigned short)n->missintg;                    
                            return ushrt;
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_USHORT) && (n->missflt <= MAX_USHORT) ){
                            ushrt = malloc(sizeof(unsigned short));
                            *ushrt = (unsigned short)n->missflt;                     
                            return ushrt;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_USHORT) && (n->missdbl <= MAX_USHORT) ){
                            ushrt = malloc(sizeof(unsigned short));
                            *ushrt = (unsigned short)n->missdbl;                     
                            return ushrt;
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        ushrt = malloc(sizeof(unsigned short));
                        *ushrt = (unsigned short)n->missubyt;
                            return ushrt;
                        break;                                      
                    case USHORT:                                        
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_USHORT) ){
                            ushrt = malloc(sizeof(unsigned short));
                            *ushrt = (unsigned short)n->missuint;                
                            return ushrt;
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_USHORT) && (n->missint64 <= MAX_USHORT) ){
                            ushrt = malloc(sizeof(unsigned short));
                            *ushrt = (unsigned short)n->missint64;                   
                            return ushrt;
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_USHORT) ){
                            ushrt = malloc(sizeof(unsigned short));
                            *ushrt = (unsigned short)n->missuint64;          
                            return ushrt;
                        }                                           
                        break;
                    default:
                        fprintf(stderr,"Error in getMissAsType: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case UINT:                                          
                switch (n->typ) {
                    case BYTE:
                        if ( (n->missbyt >= MIN_UINT) ){
                            uint = malloc(sizeof(unsigned int));
                            *uint = (unsigned int)n->missbyt;
                            return uint;
                        }
                        break;
                    case CHAR:
                        uint = malloc(sizeof(unsigned int));
                        *uint = (unsigned int)n->misschr;
                            return uint;
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_UINT) ){
                            uint = malloc(sizeof(unsigned int));
                            *uint = (unsigned int)n->missshrt;                       
                            return uint;
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_UINT) ){
                            uint = malloc(sizeof(unsigned int));
                            *uint = (unsigned int)n->missintg;                   
                            return uint;
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_UINT) && (n->missflt <= MAX_UINT) ){
                            uint = malloc(sizeof(unsigned int));
                            *uint = (unsigned int)n->missflt;                        
                            return uint;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_UINT) && (n->missdbl <= MAX_UINT) ){
                            uint = malloc(sizeof(unsigned int));
                            *uint = (unsigned int)n->missdbl;                        
                            return uint;
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        uint = malloc(sizeof(unsigned int));
                        *uint = (unsigned int)n->missubyt;
                            return uint;
                        break;                                      
                    case USHORT:                                        
                        uint = malloc(sizeof(unsigned int));
                        *uint = (unsigned int)n->missushrt;
                            return uint;
                        break;                                      
                    case UINT:                                          
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_UINT) && (n->missint64 <= MAX_UINT) ){
                            uint = malloc(sizeof(unsigned int));
                            *uint = (unsigned int)n->missint64;                  
                            return uint;
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_UINT) ){
                            uint = malloc(sizeof(unsigned int));
                            *uint = (unsigned int)n->missuint64;         
                            return uint;
                        }                                           
                        break;
                    default:
                        fprintf(stderr,"Error in getMissAsType: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case INT64:                                         
                switch (n->typ) {
                    case BYTE:
                        int64 = malloc(sizeof(long long));
                        *int64 = (long long)n->missbyt;
                            return int64;
                        break;
                    case CHAR:
                        int64 = malloc(sizeof(long long));
                        *int64 = (long long)n->misschr;
                            return int64;
                        break;                                      
                    case SHORT:                                         
                        int64 = malloc(sizeof(long long));
                        *int64 = (long long)n->missshrt;
                            return int64;
                        break;                                      
                    case INT:                                           
                        int64 = malloc(sizeof(long long));
                        *int64 = (long long)n->missintg;
                            return int64;
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_INT64) && (n->missflt <= MAX_INT64) ){
                            int64 = malloc(sizeof(long long));
                            *int64 = (long long)n->missflt;                      
                            return int64;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_INT64) && (n->missdbl <= MAX_INT64) ){
                            int64 = malloc(sizeof(long long));
                            *int64 = (long long)n->missdbl;                      
                            return int64;
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        int64 = malloc(sizeof(long long));
                        *int64 = (long long)n->missubyt;
                            return int64;
                        break;                                      
                    case USHORT:                                        
                        int64 = malloc(sizeof(long long));
                        *int64 = (long long)n->missushrt;
                            return int64;
                        break;                                      
                    case UINT:  /* hopefully UINT is smaller than INT64, could check typsize */
                        int64 = malloc(sizeof(long long));
                        *int64 = (long long)n->missuint;
                            return int64;
                        break;                                      
                    case INT64:                                         
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_INT64) ){
                            int64 = malloc(sizeof(long long));
                            *int64 = (long long)n->missuint64;           
                            return int64;
                        }                                           
                        break;
                    default:
                        fprintf(stderr,"Error in getMissAsType: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case UINT64:                                        
                switch (n->typ) {
                    case BYTE:
                        if ( (n->missbyt >= MIN_UINT64) ){
                            uint64 = malloc(sizeof(unsigned long long));
                            *uint64 = (unsigned long long)n->missbyt;
                            return uint64;
                        }
                        break;
                    case CHAR:
                        uint64 = malloc(sizeof(unsigned long long));
                        *uint64 = (unsigned long long)n->misschr;
                            return uint64;
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_UINT64) ){
                            uint64 = malloc(sizeof(unsigned long long));
                            *uint64 = (unsigned long long)n->missshrt;                       
                            return uint64;
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_UINT64) ){
                            uint64 = malloc(sizeof(unsigned long long));
                            *uint64 = (unsigned long long)n->missintg;                   
                            return uint64;
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_UINT64) && (n->missflt <= MAX_UINT64) ){
                            uint64 = malloc(sizeof(unsigned long long));
                            *uint64 = (unsigned long long)n->missflt;                        
                            return uint64;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_UINT64) && (n->missdbl <= MAX_UINT64) ){
                            uint64 = malloc(sizeof(unsigned long long));
                            *uint64 = (unsigned long long)n->missdbl;                        
                            return uint64;
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        uint64 = malloc(sizeof(unsigned long long));
                        *uint64 = (unsigned long long)n->missubyt;
                            return uint64;
                        break;                                      
                    case USHORT:                                        
                        uint64 = malloc(sizeof(unsigned long long));
                        *uint64 = (unsigned long long)n->missushrt;
                            return uint64;
                        break;                                      
                    case UINT:                                          
                        uint64 = malloc(sizeof(unsigned long long));
                        *uint64 = (unsigned long long)n->missuint;
                            return uint64;
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_UINT64) ){
                            uint64 = malloc(sizeof(unsigned long long));
                            *uint64 = (unsigned long long)n->missint64;                  
                            return uint64;
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;
                    default:
                        fprintf(stderr,"Error in getMissAsType: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            default:
                fprintf(stderr,"Error in getMissAsType: undefined type! outtyp=%d\n",outtyp);
                print_arr_exit(n);
                break;
        }
    }

    return NULL;
}

void *getMiss(arr *m){

    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)      \
        return &(m->swmtyp);
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in getMiss: undefined type %d!\n",m->typ);
            print_arr_exit(m);
            break;
    }
    #undef SWITCHCAST

    return NULL;
}

int isMiss(arr *restrict m,typ_idx idx){

    /* Added bounds checking */
    if ((idx >= m->tlen) || (idx < 0)){
        fprintf(stderr,"Error in isMiss: idx must be from 0 to %lld, it was %lld!\n",m->tlen-1,idx);
        print_arr_exit(m);
    }
    
    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        if (m->swtyp[idx] == m->swmtyp) { return 1; } else { return 0; }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in isMiss: undefined type %d!\n",m->typ);
            print_arr_exit(m);
            break;
    }
    #undef SWITCHCAST
    
    return -1;
}

int isMissc(arr *restrict m,  typ_idx *c){
    typ_idx j;
    typ_idx idx = 0;

    if (m->tlen != 1){
        for (j=0;j<m->n;++j){ idx += c[j]*m->mlen[j]; }
    }

    return isMiss(m,idx);
}

int isMissIdx(arr *restrict m,  ...){
    typ_idx j;
    int ir;

    if (m->n == 0){
        ir = isMissc(m,NULL);
    } else {
        typ_idx *c = malloc(sizeof(typ_idx)*m->n);

        va_list arg_list;
        va_start(arg_list, m);
        for(j=0;j<m->n;++j){
            c[j] = va_arg(arg_list, typ_idx);
        }
        va_end(arg_list);

        ir = isMissc(m,c);
        free(c);
    }
    return ir;
}

int isAnyMiss(arr *restrict m){
    typ_idx i;
    for(i=0;i<m->tlen;++i){ if(isMiss(m,i)){ return 1; } }
    return 0;
}

int isAnyNonMiss(arr *restrict m){
    typ_idx i;
    for(i=0;i<m->tlen;++i){ if(!isMiss(m,i)){ return 1; } }
    return 0;
}

typ_idx countNonMiss(arr *restrict X){
    typ_idx i,count = X->tlen;
    for(i=0;i<X->tlen;++i){
        if(isMiss(X,i)){ --count; }
    }
    return count;
}

typ_idx countMiss(arr *restrict X){
    typ_idx i,count = 0;
    for(i=0;i<X->tlen;++i){
        if(isMiss(X,i)){ ++count; }
    }
    return count;
}

int isAnyMissMultiAr(int narrs,arr **arrays,typ_idx idx){
    typ_idx i;
    for(i=0;i<narrs;++i){
        if(isMiss(arrays[i],idx)){ return 1; }
    }
    return 0;
}

int isAnyMisscMultiAr(int narrs,arr **arrays,typ_idx *c){
    typ_idx j;
    typ_idx idx = 0;
    if (arrays[0]->tlen != 1){
        for (j=0;j<arrays[0]->n;++j){
            idx += c[j]*arrays[0]->mlen[j];
        }
    }

    return isAnyMissMultiAr(narrs,arrays,idx);
}

int isAnyMissIdxMultiAr(int narrs,arr **arrays, ...){
    typ_idx j;
    int ir;

    if (arrays[0]->n == 0){
        ir = isAnyMisscMultiAr(narrs,arrays,NULL);
    } else {
        typ_idx *c = malloc(sizeof(typ_idx)*arrays[0]->n);

        va_list arg_list;
        va_start(arg_list, arrays);
        for(j=0;j<arrays[0]->n;++j){
            c[j] = va_arg(arg_list, typ_idx);
        }
        va_end(arg_list);

        ir = isAnyMisscMultiAr(narrs,arrays,c);
        free(c);
    }
    return ir;
}

void setToMiss(arr *restrict m,typ_idx idx){
    /* Added bounds checking */
    if ((idx >= m->tlen) || (idx < 0)){
        fprintf(stderr,"Error in setToMiss: idx must be from 0 to %lld, it was %lld!\n",m->tlen-1,idx);
        print_arr_exit(m);
    }
    
    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        m->swtyp[idx] = m->swmtyp;
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in isMiss: undefined type %d!\n",m->typ);
            print_arr_exit(m);
            break;
    }
    #undef SWITCHCAST
    
    return;
}

void setToMissc(arr *restrict m, typ_idx *c){
    typ_idx j;
    typ_idx idx = 0;
    if (m->tlen != 1){
        for (j=0;j<m->n;++j){ idx += c[j]*m->mlen[j]; }
    }

    setToMiss(m,idx);
    return;
}

void setToMissIdx(arr *restrict m,  ...){
    typ_idx j;
    
    if (m->n == 0){
        setToMissc(m,NULL);
    } else {
        typ_idx *c = malloc(sizeof(typ_idx)*m->n);

        va_list arg_list;
        va_start(arg_list, m);
        for(j=0;j<m->n;++j){
            c[j] = va_arg(arg_list, typ_idx);
        }
        va_end(arg_list);

        setToMissc(m,c);
        free(c);
    }
    return;
}

typ_idx Last(arr *restrict m,typ_idx dim){
    if (dim < m->n){
        return m->len[dim]-1;
    } else {
        fprintf(stderr,"Last: dim out of range, there are %lld dims, you requested dim = %lld\n", m->n, dim);
        print_arr_exit(m);
    }
    return -1;
}

size_t typeSize(int typ){
    size_t rettypesize;

    switch (typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        rettypesize = sizeof(swcast);
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in typeSize: undefined type %d!\n",typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST

    return rettypesize;
}

/*
void setXYZT(arr *m){
    m->x = 0;
    m->y = 0;
    m->z = 0;
    m->t = 0;
    typ_idx i = m->n - 1;
    if (i < 0){ return; } else { m->x = m->len[i]; --i; }
    if (i < 0){ return; } else { m->y = m->len[i]; --i; }
    if (i < 0){ return; } else { m->z = m->len[i]; --i; }
    if (i < 0){ return; } else { m->t = m->len[i]; --i; }
    return;
}
*/

arr ArrayFromList(typ_idx ndims, int typ, typ_idx *len) {
    typ_idx j;
    arr m;
    m.n       = ndims;
    m.typ     = typ;
    m.typsize = typeSize(typ);
    m.tlen    = 1;

    if (ndims == 0){
        m.len  = NULL;
        m.mlen = NULL;
    } else {
        typ_idx *mlen  = m.len  = malloc(ndims*sizeof(typ_idx));
        typ_idx *mmlen = m.mlen = malloc(ndims*sizeof(typ_idx));

        for (j=0; j<ndims; ++j) {
            mlen[j] = len[j];
            m.tlen *= mlen[j];
        }

        mmlen[ndims - 1] = 1;
        for (j=ndims - 2; j>-1; --j) {
            mmlen[j] = mmlen[j + 1] * mlen[j + 1];
        }
    }

    switch (typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        m.swtyp = init0(m.tlen,swmacro);
        ALLTYPECASES
    default:
        fprintf(stderr, "Error in ArrayFromList: undefined type %d!\n",m.typ);
        print_arr_exit(&m);
        break;
    }
    #undef SWITCHCAST

/*  setXYZT(&m);  */
    defaultMissing(&m);

    return m;
}

arr Array(typ_idx ndims, int typ, ... ) {
    typ_idx j;
    typ_idx *len = NULL;

    if (ndims > 0){
        len = malloc(sizeof(typ_idx)*ndims);
        va_list arg_list;
        va_start(arg_list, typ);
        for (j=0; j<ndims; ++j) {
            len[j] = va_arg(arg_list, typ_idx);
        }
        va_end(arg_list);
    }

    arr m = ArrayFromList(ndims, typ, len);

    free(len);
    return m;
}

arr Scalar2Array(int typ,void *val){
    arr m = ArrayFromList(0, typ, NULL);
    switch (m.typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        m.swtyp[0] = *(swcast *)val;
        ALLTYPECASES
    default:
        fprintf(stderr, "Error in Scalar2Array: undefined type %d!\n",m.typ);
        print_arr_exit(&m);
        break;
    }
    #undef SWITCHCAST
    
    return m;
}

int isArNull(arr *restrict m){
    if (m->tlen){
        return 0;
    } else {
        return 1;
    }
}

arr NullArray() {
    arr m;
    m.n = 0;
    m.typ = 0;
    m.typsize = 0;

    m.len = NULL;
    m.mlen = NULL;
    m.tlen = 0;

/*  setXYZT(&m);  */

    /* Set largest union members */
    m.missuint64 = 0;
    m.uint64 = NULL;

    return m;
}

arr ArrayCpy(arr *restrict n) {
    typ_idx j;
    arr m;
    m.n       = n->n;
    m.typ     = n->typ;
    m.typsize = n->typsize;
    m.tlen    = n->tlen;

    if (m.n == 0){
        m.len  = NULL;
        m.mlen = NULL;
    } else {
        m.len  = malloc(m.n*sizeof(typ_idx));
        m.mlen = malloc(m.n*sizeof(typ_idx));

        for (j=0;j<m.n;++j){ m.len[j]  = n->len[j]; }
        for (j=0;j<m.n;++j){ m.mlen[j] = n->mlen[j]; }
    }

/*  setXYZT(&m);  */

    switch (m.typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2) \
        m.swmtyp = n->swmtyp;                                                               \
        m.swtyp  = (swcast *)init0(m.tlen,swmacro);
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in ArrayCpy: undefined type %d!\n",m.typ);
            print_arr_exit(&m);
            break;
    }
    #undef SWITCHCAST

    return m;
}

arr copyAr(arr *restrict n){
    typ_idx i;
    arr m = ArrayCpy(n);

    switch (m.typ) {
    /* should I use memccpy here? */
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        for(i=0;i<m.tlen;++i){ m.swtyp[i] = n->swtyp[i]; }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in copyAr: undefined type %d!\n",m.typ);
            print_arr_exit(&m);
            break;
    }
    #undef SWITCHCAST

    return m;
}

#ifdef __linux__ 

void ByteSwapAr16(arr *restrict m){
    if ((m->typ != SHORT) && (m->typ != USHORT)){
        fprintf(stderr,"Error in ByteSwapAr16: invalid type passed! m->typ=%d\n",m->typ);
        print_arr_exit(m);
    }
    typ_idx i;

    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        for(i=0;i<m->tlen;++i){ m->swtyp[i] = bswap_16(m->swtyp[i]); }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in ByteSwapAr16: undefined type %d!\n",m->typ);
            print_arr_exit(m);
            break;
    }
    #undef SWITCHCAST

}

void ByteSwapAr32(arr *restrict m){
    if ((m->typ != INT) && (m->typ != FLOAT) && (m->typ != UINT)){
        fprintf(stderr,"Error in ByteSwapAr32: invalid type passed! m->typ=%d\n",m->typ);
        print_arr_exit(m);
    }
    typ_idx i;

    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        for(i=0;i<m->tlen;++i){ m->swtyp[i] = bswap_32(m->swtyp[i]); }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in ByteSwapAr32: undefined type %d!\n",m->typ);
            print_arr_exit(m);
            break;
    }
    #undef SWITCHCAST

}

/*
void ByteSwapAr64(arr *restrict m){
    if ((m->typ != INT64) && (m->typ != DOUBLE) && (m->typ != UINT64)){
        fprintf(stderr,"Error in ByteSwapAr64: invalid type passed! m->typ=%d\n",m->typ);
        print_arr_exit(m);
    }
    typ_idx i;

    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        for(i=0;i<m->tlen;++i){ m->swtyp[i] = bswap_64(m->swtyp[i]); }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in ByteSwapAr64: undefined type %d!\n",m->typ);
            print_arr_exit(m);
            break;
    }
    #undef SWITCHCAST

}
 */
#elif _WIN32

#else

#endif

void copyVals(arr *restrict m,arr *restrict n){
    if (m->tlen != n->tlen){
        fprintf(stderr,"Error in copyVals: both arrays must have same number or total elements!\n"
                           "\tm->tlen=%lld, n->tlen=%lld\n",m->tlen,n->tlen);
        print_arr_exit(m);
    }
    typ_idx i;

    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)   \
        m->swmtyp = n->swmtyp;                                                               \
        for(i=0;i<m->tlen;++i){ m->swtyp[i] = n->swtyp[i]; }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in copyVals: undefined type %d!\n",m->typ);
            print_arr_exit(m);
            break;
    }
    #undef SWITCHCAST

    return;
}

void fillAr(arr *restrict m,void *x){
    typ_idx i;

    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        for(i=0;i<m->tlen;++i){ m->swtyp[i] = *(swcast *)x; }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in fillAr: undefined type %d!\n",m->typ);
            print_arr_exit(m);
            break;
    }
    #undef SWITCHCAST

    return;
}

void fillArWithMiss(arr *restrict m){
    typ_idx i;

    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        for(i=0;i<m->tlen;++i){ m->swtyp[i] = m->swmtyp; }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in fillArWithMiss: undefined type %d!\n",m->typ);
            print_arr_exit(m);
            break;
    }
    #undef SWITCHCAST

    return;
}

void reshapeArList(arr *m, typ_idx ndims, typ_idx *len){
    typ_idx j;
    typ_idx tlenorig = m->tlen;
    m->tlen = 1;

    m->n    = ndims;
    if (ndims == 0){
        if (ndims > 0) {
            free(m->len);
            free(m->mlen);
        }
        m->len  = NULL;
        m->mlen = NULL;
    } else {
        m->len  = malloc(ndims*sizeof(typ_idx));
        m->mlen = malloc(ndims*sizeof(typ_idx));
    
        for (j=0;j<ndims;++j){
            m->len[j] = len[j];
            m->tlen  *= m->len[j];
        }
        
        if (m->tlen != tlenorig){
            fprintf(stderr,"reshapeArList: tlen of input must be same as original array, tlen=%lld, tlenorig=%lld\n",
                m->tlen,tlenorig);
            print_arr_exit(m);
        }
    
        m->mlen[ndims-1] = 1;
        for (j=ndims-2;j>-1;--j){
            m->mlen[j] = m->mlen[j+1]*m->len[j+1];
        }
    }
/*  setXYZT(m);  */

    return;
}

void reshapeAr(arr *m, typ_idx ndims, ...){
    typ_idx *len = NULL;

    if (ndims > 0){
        len = malloc(ndims*sizeof(typ_idx));
        typ_idx j;
    
        va_list arg_list;
        va_start(arg_list, ndims);
        for (j=0;j<ndims;++j){
            len[j] = va_arg(arg_list, typ_idx);
        }
        va_end(arg_list);
    }

    reshapeArList(m, ndims, len);
    free(len);
    return;
}

arr assign1dtoNdFromList(void *n, typ_idx ndims, int typ, typ_idx *len){
    typ_idx j;
    arr m;
    m.n = ndims;
    m.typ = typ;
    m.typsize = typeSize(typ);
    m.tlen = 1;

    if (m.n == 0){
        m.len  = NULL;
        m.mlen = NULL;
    } else {
        m.len  = malloc(m.n*sizeof(typ_idx));
        m.mlen = malloc(m.n*sizeof(typ_idx));
    
        for (j=0;j<m.n;++j){
            m.len[j] = len[j];
            m.tlen  *= m.len[j];
        }
    
        m.mlen[m.n-1] = 1;
        for (j=m.n-2;j>-1;--j){
            m.mlen[j] = m.mlen[j+1]*m.len[j+1];
        }
    }

    switch (m.typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        m.swtyp = (swcast *)n;
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in assign1dtoNdFromList: undefined type %d!\n",m.typ);
            print_arr_exit(&m);
            break;
    }
    #undef SWITCHCAST

/*  setXYZT(&m);  */
    defaultMissing(&m);

    return m;
}

arr assign1dtoNd(void *n, typ_idx ndims, int typ, ...){
    typ_idx *len = NULL;

    if (ndims > 0){
        len = malloc(ndims*sizeof(typ_idx));
        typ_idx j;
    
        va_list arg_list;
        va_start(arg_list, typ);
        for (j=0;j<ndims;++j){
            len[j] = va_arg(arg_list, typ_idx);
        }
        va_end(arg_list);
    }

    arr m = assign1dtoNdFromList(n, ndims, typ, len);
    free(len);
    return m;
}

void freeArShell(arr *m){
    free(m->len);
    free(m->mlen);
    *m = NullArray();

    return;
}

void freeAr(arr *m){
    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        if (m->swtyp != NULL){ \
            free(m->swtyp); \
            m->swtyp = NULL; \
        }
        ALLTYPECASES
        case 0:
            break;
        default:
            fprintf(stderr,"Error in freeAr: undefined type %d!\n",m->typ);
            print_arr_exit(m);
            break;
    }
    #undef SWITCHCAST

    freeArShell(m);
    return;
}

void *translateType(void *inval,char intyp,char outtyp){
    signed char *byt;               /* BYTE  */
    char *chr;                  /* CHAR   */
    short *shrt;                /* SHORT  */
    int *intg;                  /* INT    */
    float *flt;                 /* FLOAT  */
    double *dbl;                /* DOUBLE */
    unsigned char *ubyt;            /* UBYTE  */
    unsigned short *ushrt;          /* USHORT */
    unsigned int *uint;         /* UINT   */
    long long *int64;               /* INT64  */
    unsigned long long *uint64;     /* UINT64 */

    switch (outtyp) {
        case BYTE:
            byt = malloc(sizeof(signed char));
            switch (intyp) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                *byt = (signed char)(*(swcast *)inval);                 \
                return byt;
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in translateType: cannot process this type! intyp=%d\n",intyp);
                    exit(0);
                    break;
                }
    #undef SWITCHCAST
            break;
        case CHAR:
            chr = malloc(sizeof(char));
            switch (intyp) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                *chr = (char)(*(swcast *)inval);                    \
                return chr;
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in translateType: cannot process this type! intyp=%d\n",intyp);
                    exit(0);
                    break;
                }
    #undef SWITCHCAST
            break;
        case SHORT:
            shrt = malloc(sizeof(short));
            switch (intyp) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                *shrt = (short)(*(swcast *)inval);                  \
                return shrt;
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in translateType: cannot process this type! intyp=%d\n",intyp);
                    exit(0);
                    break;
                }
    #undef SWITCHCAST
            break;
        case INT:
            intg = malloc(sizeof(int));
            switch (intyp) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                *intg = (int)(*(swcast *)inval);                    \
                return intg;
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in translateType: cannot process this type! intyp=%d\n",intyp);
                    exit(0);
                    break;
                }
    #undef SWITCHCAST
            break;
        case FLOAT:
            flt = malloc(sizeof(float));
            switch (intyp) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                *flt = (float)(*(swcast *)inval);                   \
                return flt;
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in translateType: cannot process this type! intyp=%d\n",intyp);
                    exit(0);
                    break;
                }
    #undef SWITCHCAST
            break;
        case DOUBLE:
            dbl = malloc(sizeof(double));
            switch (intyp) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                *dbl = (double)(*(swcast *)inval);                  \
                return dbl;
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in translateType: cannot process this type! intyp=%d\n",intyp);
                    exit(0);
                    break;
                }
    #undef SWITCHCAST
            break;
        case UBYTE:
            ubyt = malloc(sizeof(unsigned char));
            switch (intyp) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                *ubyt = (unsigned char)(*(swcast *)inval);                  \
                return ubyt;
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in translateType: cannot process this type! intyp=%d\n",intyp);
                    exit(0);
                    break;
                }
    #undef SWITCHCAST
            break;
        case USHORT:
            ushrt = malloc(sizeof(unsigned short));
            switch (intyp) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                *ushrt = (unsigned short)(*(swcast *)inval);                    \
                return ushrt;
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in translateType: cannot process this type! intyp=%d\n",intyp);
                    exit(0);
                    break;
                }
    #undef SWITCHCAST
            break;
        case UINT:
            uint = malloc(sizeof(unsigned int));
            switch (intyp) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                *uint = (unsigned int)(*(swcast *)inval);                   \
                return uint;
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in translateType: cannot process this type! intyp=%d\n",intyp);
                    exit(0);
                    break;
                }
    #undef SWITCHCAST
            break;
        case INT64:
            int64 = malloc(sizeof(long long));
            switch (intyp) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                *int64 = (long long)(*(swcast *)inval);                 \
                return int64;
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in translateType: cannot process this type! intyp=%d\n",intyp);
                    exit(0);
                    break;
                }
    #undef SWITCHCAST
            break;
        case UINT64:
            uint64 = malloc(sizeof(unsigned long long));
            switch (intyp) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
                *uint64 = (unsigned long long)(*(swcast *)inval);                   \
                return uint64;
                ALLTYPECASES
                default:
                    fprintf(stderr,"Error in translateType: cannot process this type! intyp=%d\n",intyp);
                    exit(0);
                    break;
                }
    #undef SWITCHCAST
            break;
        default:
            fprintf(stderr,"Error in translateType: cannot process this type! outtyp=%d\n",outtyp);
            exit(0);
            break;
    }
    
    return NULL;
}

void copyArVals(arr *m,arr *restrict n) {
    if (m->tlen < n->tlen){
        fprintf(stderr,"Error in copyArVals: both arrays must have same number or total elements!\n"
                           "\tm->tlen=%lld, n->tlen=%lld\n",m->tlen,n->tlen);
        print_arr_exit(m);
    }
    typ_idx i;

    /*  fputs("copyArVals: 6\n",stderr);  */
    if (m->typ == n->typ){
        switch (m->typ){
        #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)      \
            for(i=0;i<n->tlen;++i){ \
                if (n->swtyp[i] == n->swmtyp){ \
                    m->swtyp[i] = m->swmtyp; \
                } else { \
                    m->swtyp[i] = n->swtyp[i]; \
                } \
            }
            ALLTYPECASES
            default:
                fprintf(stderr,"Error in copyArVals: undefined type! m->typ=%d\n",m->typ);
                print_arr_exit(m);
                break;
        }
        #undef SWITCHCAST
    } else {
    /*  fputs("copyArVals: 6.2\n",stderr);    */
        /*
         *  Need to process missing values more rigorously
         *  - I can't just cast values from higher precision to lower precision
         *  - I need to check the value first.
         *  - technically I should also check every value of an array and set uncastable value to missing
         */
        switch (m->typ) {
            case BYTE:
                switch (n->typ) {
                    case BYTE:
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;
                    case CHAR:
                        for(i=0;i<n->tlen;++i){
                            if (n->chr[i] == n->misschr){
                                m->byt[i] = m->missbyt;
                            } else {
                                m->byt[i] = (signed char)n->chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->shrt[i] == n->missshrt){
                                m->byt[i] = m->missbyt;
                            } else {
                                m->byt[i] = (signed char)n->shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->intg[i] == n->missintg){
                                m->byt[i] = m->missbyt;
                            } else {
                                m->byt[i] = (signed char)n->intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->flt[i] == n->missflt){
                                m->byt[i] = m->missbyt;
                            } else {
                                m->byt[i] = (signed char)n->flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->dbl[i] == n->missdbl){
                                m->byt[i] = m->missbyt;
                            } else {
                                m->byt[i] = (signed char)n->dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ubyt[i] == n->missubyt){
                                m->byt[i] = m->missbyt;
                            } else {
                                m->byt[i] = (signed char)n->ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ushrt[i] == n->missushrt){
                                m->byt[i] = m->missbyt;
                            } else {
                                m->byt[i] = (signed char)n->ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->uint[i] == n->missuint){
                                m->byt[i] = m->missbyt;
                            } else {
                                m->byt[i] = (signed char)n->uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->int64[i] == n->missint64){
                                m->byt[i] = m->missbyt;
                            } else {
                                m->byt[i] = (signed char)n->int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->uint64[i] == n->missuint64){
                                m->byt[i] = m->missbyt;
                            } else {
                                m->byt[i] = (signed char)n->uint64[i];
                            }
                        }
                        break;
                    default:
                        fprintf(stderr,"Error in copyArVals: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case CHAR:                                          
                switch (n->typ) {
                    case BYTE:
                        for(i=0;i<n->tlen;++i){
                            if (n->byt[i] == n->missbyt){
                                m->chr[i] = m->misschr;
                            } else {
                                m->chr[i] = (char)n->byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->shrt[i] == n->missshrt){
                                m->chr[i] = m->misschr;
                            } else {
                                m->chr[i] = (char)n->shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->intg[i] == n->missintg){
                                m->chr[i] = m->misschr;
                            } else {
                                m->chr[i] = (char)n->intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->flt[i] == n->missflt){
                                m->chr[i] = m->misschr;
                            } else {
                                m->chr[i] = (char)n->flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->dbl[i] == n->missdbl){
                                m->chr[i] = m->misschr;
                            } else {
                                m->chr[i] = (char)n->dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE: /* treating the same as CHAR, but this isn't necessarily true */
                        for(i=0;i<n->tlen;++i){
                            if (n->ubyt[i] == n->missubyt){
                                m->chr[i] = m->misschr;
                            } else {
                                m->chr[i] = (char)n->ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ushrt[i] == n->missushrt){
                                m->chr[i] = m->misschr;
                            } else {
                                m->chr[i] = (char)n->ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->uint[i] == n->missuint){
                                m->chr[i] = m->misschr;
                            } else {
                                m->chr[i] = (char)n->uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->int64[i] == n->missint64){
                                m->chr[i] = m->misschr;
                            } else {
                                m->chr[i] = (char)n->int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->uint64[i] == n->missuint64){
                                m->chr[i] = m->misschr;
                            } else {
                                m->chr[i] = (char)n->uint64[i];
                            }
                        }
                        break;
                    default:
                        fprintf(stderr,"Error in copyArVals: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case SHORT:                                         
                switch (n->typ) {
                    case BYTE:
                        for(i=0;i<n->tlen;++i){
                            if (n->byt[i] == n->missbyt){
                                m->shrt[i] = m->missshrt;
                            } else {
                                m->shrt[i] = (short)n->byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        for(i=0;i<n->tlen;++i){
                            if (n->chr[i] == n->misschr){
                                m->shrt[i] = m->missshrt;
                            } else {
                                m->shrt[i] = (short)n->chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->intg[i] == n->missintg){
                                m->shrt[i] = m->missshrt;
                            } else {
                                m->shrt[i] = (short)n->intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->flt[i] == n->missflt){
                                m->shrt[i] = m->missshrt;
                            } else {
                                m->shrt[i] = (short)n->flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->dbl[i] == n->missdbl){
                                m->shrt[i] = m->missshrt;
                            } else {
                                m->shrt[i] = (short)n->dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ubyt[i] == n->missubyt){
                                m->shrt[i] = m->missshrt;
                            } else {
                                m->shrt[i] = (short)n->ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ushrt[i] == n->missushrt){
                                m->shrt[i] = m->missshrt;
                            } else {
                                m->shrt[i] = (short)n->ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->uint[i] == n->missuint){
                                m->shrt[i] = m->missshrt;
                            } else {
                                m->shrt[i] = (short)n->uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->int64[i] == n->missint64){
                                m->shrt[i] = m->missshrt;
                            } else {
                                m->shrt[i] = (short)n->int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->uint64[i] == n->missuint64){
                                m->shrt[i] = m->missshrt;
                            } else {
                                m->shrt[i] = (short)n->uint64[i];
                            }
                        }
                        break;
                    default:
                        fprintf(stderr,"Error in copyArVals: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case INT:                                           
                switch (n->typ) {
                    case BYTE:
                        for(i=0;i<n->tlen;++i){
                            if (n->byt[i] == n->missbyt){
                                m->intg[i] = m->missintg;
                            } else {
                                m->intg[i] = (int)n->byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        for(i=0;i<n->tlen;++i){
                            if (n->chr[i] == n->misschr){
                                m->intg[i] = m->missintg;
                            } else {
                                m->intg[i] = (int)n->chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->shrt[i] == n->missshrt){
                                m->intg[i] = m->missintg;
                            } else {
                                m->intg[i] = (int)n->shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           

                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->flt[i] == n->missflt){
                                m->intg[i] = m->missintg;
                            } else {
                                m->intg[i] = (int)n->flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->dbl[i] == n->missdbl){
                                m->intg[i] = m->missintg;
                            } else {
                                m->intg[i] = (int)n->dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ubyt[i] == n->missubyt){
                                m->intg[i] = m->missintg;
                            } else {
                                m->intg[i] = (int)n->ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:    /* INT should be greater than USHORT unless same typesize */
                        for(i=0;i<n->tlen;++i){
                            if (n->ushrt[i] == n->missushrt){
                                m->intg[i] = m->missintg;
                            } else {
                                m->intg[i] = (int)n->ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->uint[i] == n->missuint){
                                m->intg[i] = m->missintg;
                            } else {
                                m->intg[i] = (int)n->uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->int64[i] == n->missint64){
                                m->intg[i] = m->missintg;
                            } else {
                                m->intg[i] = (int)n->int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->uint64[i] == n->missuint64){
                                m->intg[i] = m->missintg;
                            } else {
                                m->intg[i] = (int)n->uint64[i];
                            }
                        }
                        break;
                    default:
                        fprintf(stderr,"Error in copyArVals: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case FLOAT:                                         
                switch (n->typ) {
                    case BYTE:
                        for(i=0;i<n->tlen;++i){
                            if (n->byt[i] == n->missbyt){
                                m->flt[i] = m->missflt;
                            } else {
                                m->flt[i] = (float)n->byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        for(i=0;i<n->tlen;++i){
                            if (n->chr[i] == n->misschr){
                                m->flt[i] = m->missflt;
                            } else {
                                m->flt[i] = (float)n->chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->shrt[i] == n->missshrt){
                                m->flt[i] = m->missflt;
                            } else {
                                m->flt[i] = (float)n->shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->intg[i] == n->missintg){
                                m->flt[i] = m->missflt;
                            } else {
                                m->flt[i] = (float)n->intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->dbl[i] == n->missdbl){
                                m->flt[i] = m->missflt;
                            } else {
                                m->flt[i] = (float)n->dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ubyt[i] == n->missubyt){
                                m->flt[i] = m->missflt;
                            } else {
                                m->flt[i] = (float)n->ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ushrt[i] == n->missushrt){
                                m->flt[i] = m->missflt;
                            } else {
                                m->flt[i] = (float)n->ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->uint[i] == n->missuint){
                                m->flt[i] = m->missflt;
                            } else {
                                m->flt[i] = (float)n->uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->int64[i] == n->missint64){
                                m->flt[i] = m->missflt;
                            } else {
                                m->flt[i] = (float)n->int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->uint64[i] == n->missuint64){
                                m->flt[i] = m->missflt;
                            } else {
                                m->flt[i] = (float)n->uint64[i];
                            }
                        }
                        break;
                    default:
                        fprintf(stderr,"Error in copyArVals: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case DOUBLE:                                        
                switch (n->typ) {
                    case BYTE:
                        for(i=0;i<n->tlen;++i){
                            if (n->byt[i] == n->missbyt){
                                m->dbl[i] = m->missdbl;
                            } else {
                                m->dbl[i] = (double)n->byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        for(i=0;i<n->tlen;++i){
                            if (n->chr[i] == n->misschr){
                                m->dbl[i] = m->missdbl;
                            } else {
                                m->dbl[i] = (double)n->chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->shrt[i] == n->missshrt){
                                m->dbl[i] = m->missdbl;
                            } else {
                                m->dbl[i] = (double)n->shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->intg[i] == n->missintg){
                                m->dbl[i] = m->missdbl;
                            } else {
                                m->dbl[i] = (double)n->intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->flt[i] == n->missflt){
                                m->dbl[i] = m->missdbl;
                            } else {
                                m->dbl[i] = (double)n->flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ubyt[i] == n->missubyt){
                                m->dbl[i] = m->missdbl;
                            } else {
                                m->dbl[i] = (double)n->ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ushrt[i] == n->missushrt){
                                m->dbl[i] = m->missdbl;
                            } else {
                                m->dbl[i] = (double)n->ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->uint[i] == n->missuint){
                                m->dbl[i] = m->missdbl;
                            } else {
                                m->dbl[i] = (double)n->uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->int64[i] == n->missint64){
                                m->dbl[i] = m->missdbl;
                            } else {
                                m->dbl[i] = (double)n->int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->uint64[i] == n->missuint64){
                                m->dbl[i] = m->missdbl;
                            } else {
                                m->dbl[i] = (double)n->uint64[i];
                            }
                        }
                        break;
                    default:
                        fprintf(stderr,"Error in copyArVals: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case UBYTE:                                         
                switch (n->typ) {
                    case BYTE:
                        for(i=0;i<n->tlen;++i){
                            if (n->byt[i] == n->missbyt){
                                m->ubyt[i] = m->missubyt;
                            } else {
                                m->ubyt[i] = (unsigned char)n->byt[i];
                            }
                        }
                        break;
                    case CHAR:  /* treating CHAR and UBYTE as equal */
                        for(i=0;i<n->tlen;++i){
                            if (n->chr[i] == n->misschr){
                                m->ubyt[i] = m->missubyt;
                            } else {
                                m->ubyt[i] = (unsigned char)n->chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->shrt[i] == n->missshrt){
                                m->ubyt[i] = m->missubyt;
                            } else {
                                m->ubyt[i] = (unsigned char)n->shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->intg[i] == n->missintg){
                                m->ubyt[i] = m->missubyt;
                            } else {
                                m->ubyt[i] = (unsigned char)n->intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->flt[i] == n->missflt){
                                m->ubyt[i] = m->missubyt;
                            } else {
                                m->ubyt[i] = (unsigned char)n->flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->dbl[i] == n->missdbl){
                                m->ubyt[i] = m->missubyt;
                            } else {
                                m->ubyt[i] = (unsigned char)n->dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ushrt[i] == n->missushrt){
                                m->ubyt[i] = m->missubyt;
                            } else {
                                m->ubyt[i] = (unsigned char)n->ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->uint[i] == n->missuint){
                                m->ubyt[i] = m->missubyt;
                            } else {
                                m->ubyt[i] = (unsigned char)n->uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->int64[i] == n->missint64){
                                m->ubyt[i] = m->missubyt;
                            } else {
                                m->ubyt[i] = (unsigned char)n->int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->uint64[i] == n->missuint64){
                                m->ubyt[i] = m->missubyt;
                            } else {
                                m->ubyt[i] = (unsigned char)n->uint64[i];
                            }
                        }
                        break;
                    default:
                        fprintf(stderr,"Error in copyArVals: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case USHORT:                                        
                switch (n->typ) {
                    case BYTE:
                        for(i=0;i<n->tlen;++i){
                            if (n->byt[i] == n->missbyt){
                                m->ushrt[i] = m->missushrt;
                            } else {
                                m->ushrt[i] = (unsigned short)n->byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        for(i=0;i<n->tlen;++i){
                            if (n->chr[i] == n->misschr){
                                m->ushrt[i] = m->missushrt;
                            } else {
                                m->ushrt[i] = (unsigned short)n->chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->shrt[i] == n->missshrt){
                                m->ushrt[i] = m->missushrt;
                            } else {
                                m->ushrt[i] = (unsigned short)n->shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->intg[i] == n->missintg){
                                m->ushrt[i] = m->missushrt;
                            } else {
                                m->ushrt[i] = (unsigned short)n->intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->flt[i] == n->missflt){
                                m->ushrt[i] = m->missushrt;
                            } else {
                                m->ushrt[i] = (unsigned short)n->flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->dbl[i] == n->missdbl){
                                m->ushrt[i] = m->missushrt;
                            } else {
                                m->ushrt[i] = (unsigned short)n->dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ubyt[i] == n->missubyt){
                                m->ushrt[i] = m->missushrt;
                            } else {
                                m->ushrt[i] = (unsigned short)n->ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->uint[i] == n->missuint){
                                m->ushrt[i] = m->missushrt;
                            } else {
                                m->ushrt[i] = (unsigned short)n->uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->int64[i] == n->missint64){
                                m->ushrt[i] = m->missushrt;
                            } else {
                                m->ushrt[i] = (unsigned short)n->int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->uint64[i] == n->missuint64){
                                m->ushrt[i] = m->missushrt;
                            } else {
                                m->ushrt[i] = (unsigned short)n->uint64[i];
                            }
                        }
                        break;
                    default:
                        fprintf(stderr,"Error in copyArVals: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case UINT:                                          
                switch (n->typ) {
                    case BYTE:
                        for(i=0;i<n->tlen;++i){
                            if (n->byt[i] == n->missbyt){
                                m->uint[i] = m->missuint;
                            } else {
                                m->uint[i] = (unsigned int)n->byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        for(i=0;i<n->tlen;++i){
                            if (n->chr[i] == n->misschr){
                                m->uint[i] = m->missuint;
                            } else {
                                m->uint[i] = (unsigned int)n->chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->shrt[i] == n->missshrt){
                                m->uint[i] = m->missuint;
                            } else {
                                m->uint[i] = (unsigned int)n->shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->intg[i] == n->missintg){
                                m->uint[i] = m->missuint;
                            } else {
                                m->uint[i] = (unsigned int)n->intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->flt[i] == n->missflt){
                                m->uint[i] = m->missuint;
                            } else {
                                m->uint[i] = (unsigned int)n->flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->dbl[i] == n->missdbl){
                                m->uint[i] = m->missuint;
                            } else {
                                m->uint[i] = (unsigned int)n->dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ubyt[i] == n->missubyt){
                                m->uint[i] = m->missuint;
                            } else {
                                m->uint[i] = (unsigned int)n->ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ushrt[i] == n->missushrt){
                                m->uint[i] = m->missuint;
                            } else {
                                m->uint[i] = (unsigned int)n->ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->int64[i] == n->missint64){
                                m->uint[i] = m->missuint;
                            } else {
                                m->uint[i] = (unsigned int)n->int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->uint64[i] == n->missuint64){
                                m->uint[i] = m->missuint;
                            } else {
                                m->uint[i] = (unsigned int)n->uint64[i];
                            }
                        }
                        break;
                    default:
                        fprintf(stderr,"Error in copyArVals: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case INT64:                                         
                switch (n->typ) {
                    case BYTE:
                        for(i=0;i<n->tlen;++i){
                            if (n->byt[i] == n->missbyt){
                                m->int64[i] = m->missint64;
                            } else {
                                m->int64[i] = (long long)n->byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        for(i=0;i<n->tlen;++i){
                            if (n->chr[i] == n->misschr){
                                m->int64[i] = m->missint64;
                            } else {
                                m->int64[i] = (long long)n->chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->shrt[i] == n->missshrt){
                                m->int64[i] = m->missint64;
                            } else {
                                m->int64[i] = (long long)n->shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->intg[i] == n->missintg){
                                m->int64[i] = m->missint64;
                            } else {
                                m->int64[i] = (long long)n->intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->flt[i] == n->missflt){
                                m->int64[i] = m->missint64;
                            } else {
                                m->int64[i] = (long long)n->flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->dbl[i] == n->missdbl){
                                m->int64[i] = m->missint64;
                            } else {
                                m->int64[i] = (long long)n->dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ubyt[i] == n->missubyt){
                                m->int64[i] = m->missint64;
                            } else {
                                m->int64[i] = (long long)n->ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ushrt[i] == n->missushrt){
                                m->int64[i] = m->missint64;
                            } else {
                                m->int64[i] = (long long)n->ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:  /* hopefully UINT is smaller than INT64, could check typsize */
                        for(i=0;i<n->tlen;++i){
                            if (n->uint[i] == n->missuint){
                                m->int64[i] = m->missint64;
                            } else {
                                m->int64[i] = (long long)n->uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->uint64[i] == n->missuint64){
                                m->int64[i] = m->missint64;
                            } else {
                                m->int64[i] = (long long)n->uint64[i];
                            }
                        }
                        break;
                    default:
                        fprintf(stderr,"Error in copyArVals: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case UINT64:                                        
                switch (n->typ) {
                    case BYTE:
                        for(i=0;i<n->tlen;++i){
                            if (n->byt[i] == n->missbyt){
                                m->uint64[i] = m->missuint64;
                            } else {
                                m->uint64[i] = (unsigned long long)n->byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        for(i=0;i<n->tlen;++i){
                            if (n->chr[i] == n->misschr){
                                m->uint64[i] = m->missuint64;
                            } else {
                                m->uint64[i] = (unsigned long long)n->chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->shrt[i] == n->missshrt){
                                m->uint64[i] = m->missuint64;
                            } else {
                                m->uint64[i] = (unsigned long long)n->shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->intg[i] == n->missintg){
                                m->uint64[i] = m->missuint64;
                            } else {
                                m->uint64[i] = (unsigned long long)n->intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->flt[i] == n->missflt){
                                m->uint64[i] = m->missuint64;
                            } else {
                                m->uint64[i] = (unsigned long long)n->flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->dbl[i] == n->missdbl){
                                m->uint64[i] = m->missuint64;
                            } else {
                                m->uint64[i] = (unsigned long long)n->dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ubyt[i] == n->missubyt){
                                m->uint64[i] = m->missuint64;
                            } else {
                                m->uint64[i] = (unsigned long long)n->ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ushrt[i] == n->missushrt){
                                m->uint64[i] = m->missuint64;
                            } else {
                                m->uint64[i] = (unsigned long long)n->ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->uint[i] == n->missuint){
                                m->uint64[i] = m->missuint64;
                            } else {
                                m->uint64[i] = (unsigned long long)n->uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->int64[i] == n->missint64){
                                m->uint64[i] = m->missuint64;
                            } else {
                                m->uint64[i] = (unsigned long long)n->int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;
                    default:
                        fprintf(stderr,"Error in copyArVals: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            default:
                fprintf(stderr,"Error in copyArVals: undefined type! m->typ=%d\n",m->typ);
                print_arr_exit(m);
                break;
        }
    }

    /*  fputs("copyArVals: 7\n",stderr);  */
    return;
}

arr castAr(arr *restrict n,int typ,int freecnd) {
    typ_idx i;
    typ_idx j;
    arr m;
/*
    int dbgcond = ( (n->tlen == 80) && (n->missdbl > 1e10) );
    fputs("castAr: 1\n",stderr);
 */
    m.n       = n->n;
    m.typ     = typ;
    m.typsize = typeSize(typ);
    m.tlen    = n->tlen;

    if (m.n == 0){
        m.len  = NULL;
        m.mlen = NULL;
    } else {
        m.len  = malloc(m.n*sizeof(typ_idx));
        m.mlen = malloc(m.n*sizeof(typ_idx));

        for (j=0;j<m.n;++j){ m.len[j]  = n->len[j]; }
        for (j=0;j<m.n;++j){ m.mlen[j] = n->mlen[j]; }
    }

    /*  fputs("castAr: 5\n",stderr);  */
/*  setXYZT(&m);  */
    defaultMissing(&m);

    /*  fputs("castAr: 6\n",stderr);  */
    if (m.typ == n->typ){
    /*  fputs("castAr: 6.1\n",stderr); */
        switch (m.typ){
        #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)      \
            m.swtyp = malloc(m.tlen*m.typsize);                                     \
            if (NULL == m.swtyp) {                                              \
                perror("castAr");                                               \
                fprintf(stderr,"castAr: Failed to allocate memory for m.swtyp size: %zu\n",(size_t)m.tlen*m.typsize); \
                print_arr_exit(&m); \
            }                                                           \
            m.swmtyp = n->swmtyp;                                                \
            for(i=0;i<m.tlen;++i){ m.swtyp[i] = n->swtyp[i]; }
            ALLTYPECASES
            default:
                fprintf(stderr,"Error in castAr: undefined type! m.typ=%d\n",m.typ);
                print_arr_exit(&m);
                break;
        }
        #undef SWITCHCAST
    } else {
    /*  fputs("castAr: 6.2\n",stderr);    */
        /*
         *  Need to process missing values more rigorously
         *  - I can't just cast values from higher precision to lower precision
         *  - I need to check the value first.
         *  - technically I should also check every value of an array an set uncastable value to missing (not doing yet)
         */
        switch (m.typ) {
            case BYTE:
                m.byt = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;
                    case CHAR:
                        #if MAX_BYTE < MAX_CHAR
                        if ( (n->misschr <= MAX_BYTE) )
                        #endif
                        {
                            m.missbyt = (signed char)n->misschr;
                        }
                        for(i=0;i<m.tlen;++i){ m.byt[i] = (signed char)n->chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_BYTE) && (n->missshrt <= MAX_BYTE) ){
                            m.missbyt = (signed char)n->missshrt;                        
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.byt[i] = (signed char)n->shrt[i]; }
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_BYTE) && (n->missintg <= MAX_BYTE) ){
                            m.missbyt = (signed char)n->missintg;                    
                        }                                       
                        for(i=0;i<m.tlen;++i){ m.byt[i] = (signed char)n->intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_BYTE) && (n->missflt <= MAX_BYTE) ){
                            m.missbyt = (signed char)n->missflt;                     
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.byt[i] = (signed char)n->flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_BYTE) && (n->missdbl <= MAX_BYTE) ){
                            m.missbyt = (signed char)n->missdbl;                     
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.byt[i] = (signed char)n->dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        if ( (n->missubyt <= MAX_BYTE) ){
                            m.missbyt = (signed char)n->missubyt;                
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.byt[i] = (signed char)n->ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        if ( (n->missushrt <= MAX_BYTE) ){
                            m.missbyt = (signed char)n->missushrt;               
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.byt[i] = (signed char)n->ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_BYTE) ){
                            m.missbyt = (signed char)n->missuint;                
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.byt[i] = (signed char)n->uint[i]; }
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_BYTE) && (n->missint64 <= MAX_BYTE) ){
                            m.missbyt = (signed char)n->missint64;                   
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.byt[i] = (signed char)n->int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_BYTE) ){
                            m.missbyt = (signed char)n->missuint64;          
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.byt[i] = (signed char)n->uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case CHAR:                                          
                m.chr = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        #if MAX_BYTE < MAX_CHAR
                        if ( (n->missbyt >= MIN_CHAR) )
                        #endif
                        {
                            m.misschr = (char)n->missbyt;
                        }
                        for(i=0;i<m.tlen;++i){ m.chr[i] = (char)n->byt[i]; }
                        break;
                    case CHAR:
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_CHAR) && (n->missshrt <= MAX_CHAR) ){
                            m.misschr = (char)n->missshrt;                       
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.chr[i] = (char)n->shrt[i]; }
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_CHAR) && (n->missintg <= MAX_CHAR) ){
                            m.misschr = (char)n->missintg;                   
                        }                                       
                        for(i=0;i<m.tlen;++i){ m.chr[i] = (char)n->intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_CHAR) && (n->missflt <= MAX_CHAR) ){
                            m.misschr = (char)n->missflt;                        
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.chr[i] = (char)n->flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_CHAR) && (n->missdbl <= MAX_CHAR) ){
                            m.misschr = (char)n->missdbl;                        
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.chr[i] = (char)n->dbl[i]; }
                        break;                                      
                    case UBYTE: /* treating the same as CHAR, but this isn't necessarily true */
                        m.misschr = (char)n->missubyt;                               
                        for(i=0;i<m.tlen;++i){ m.chr[i] = (char)n->ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        if ( (n->missushrt <= MAX_CHAR) ){
                            m.misschr = (char)n->missushrt;              
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.chr[i] = (char)n->ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_CHAR) ){
                            m.misschr = (char)n->missuint;               
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.chr[i] = (char)n->uint[i]; }
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_CHAR) && (n->missint64 <= MAX_CHAR) ){
                            m.misschr = (char)n->missint64;                  
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.chr[i] = (char)n->int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_CHAR) ){
                            m.misschr = (char)n->missuint64;         
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.chr[i] = (char)n->uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case SHORT:                                         
                m.shrt = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        m.missshrt = (short)n->missbyt;
                        for(i=0;i<m.tlen;++i){ m.shrt[i] = (short)n->byt[i]; }
                        break;
                    case CHAR:
                        m.missshrt = (short)n->misschr;
                        for(i=0;i<m.tlen;++i){ m.shrt[i] = (short)n->chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_SHORT) && (n->missintg <= MAX_SHORT) ){
                            m.missshrt = (short)n->missintg;                 
                        }                                       
                        for(i=0;i<m.tlen;++i){ m.shrt[i] = (short)n->intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_SHORT) && (n->missflt <= MAX_SHORT) ){
                            m.missshrt = (short)n->missflt;                      
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.shrt[i] = (short)n->flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_SHORT) && (n->missdbl <= MAX_SHORT) ){
                            m.missshrt = (short)n->missdbl;                      
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.shrt[i] = (short)n->dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        m.missshrt = (short)n->missubyt;
                        for(i=0;i<m.tlen;++i){ m.shrt[i] = (short)n->ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        if ( (n->missushrt <= MAX_SHORT) ){
                            m.missshrt = (short)n->missushrt;                
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.shrt[i] = (short)n->ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_SHORT) ){
                            m.missshrt = (short)n->missuint;             
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.shrt[i] = (short)n->uint[i]; }
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_SHORT) && (n->missint64 <= MAX_SHORT) ){
                            m.missshrt = (short)n->missint64;                    
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.shrt[i] = (short)n->int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_SHORT) ){
                            m.missshrt = (short)n->missuint64;           
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.shrt[i] = (short)n->uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case INT:                                           
                m.intg = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        m.missintg = (int)n->missbyt;
                        for(i=0;i<m.tlen;++i){ m.intg[i] = (int)n->byt[i]; }
                        break;
                    case CHAR:
                        m.missintg = (int)n->misschr;
                        for(i=0;i<m.tlen;++i){ m.intg[i] = (int)n->chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        m.missintg = (int)n->missshrt;
                        for(i=0;i<m.tlen;++i){ m.intg[i] = (int)n->shrt[i]; }
                        break;                                      
                    case INT:                                           
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_INT) && (n->missflt <= MAX_INT) ){
                            m.missintg = (int)n->missflt;                        
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.intg[i] = (int)n->flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_INT) && (n->missdbl <= MAX_INT) ){
                            m.missintg = (int)n->missdbl;                        
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.intg[i] = (int)n->dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        m.missintg = (int)n->missubyt;
                        for(i=0;i<m.tlen;++i){ m.intg[i] = (int)n->ubyt[i]; }
                        break;                                      
                    case USHORT:    /* INT should be greater than USHORT unless same typesize */
                        m.missintg = (int)n->missushrt;
                        for(i=0;i<m.tlen;++i){ m.intg[i] = (int)n->ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_INT) ){
                            m.missintg = (int)n->missuint;               
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.intg[i] = (int)n->uint[i]; }
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_INT) && (n->missint64 <= MAX_INT) ){
                            m.missintg = (int)n->missint64;                  
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.intg[i] = (int)n->int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_INT) ){
                            m.missintg = (int)n->missuint64;         
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.intg[i] = (int)n->uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case FLOAT:                                         
                m.flt = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        m.missflt = (float)n->missbyt;
                        for(i=0;i<m.tlen;++i){ m.flt[i] = (float)n->byt[i]; }
                        break;
                    case CHAR:
                        m.missflt = (float)n->misschr;
                        for(i=0;i<m.tlen;++i){ m.flt[i] = (float)n->chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        m.missflt = (float)n->missshrt;
                        for(i=0;i<m.tlen;++i){ m.flt[i] = (float)n->shrt[i]; }
                        break;                                      
                    case INT:                                           
                        m.missflt = (float)n->missintg;
                        for(i=0;i<m.tlen;++i){ m.flt[i] = (float)n->intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_FLOAT) && (n->missdbl <= MAX_FLOAT) ){
                            m.missflt = (float)n->missdbl;                       
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.flt[i] = (float)n->dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        m.missflt = (float)n->missubyt;
                        for(i=0;i<m.tlen;++i){ m.flt[i] = (float)n->ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        m.missflt = (float)n->missushrt;
                        for(i=0;i<m.tlen;++i){ m.flt[i] = (float)n->ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        m.missflt = (float)n->missuint;
                        for(i=0;i<m.tlen;++i){ m.flt[i] = (float)n->uint[i]; }
                        break;                                      
                    case INT64:                                         
                        m.missflt = (float)n->missint64;
                        for(i=0;i<m.tlen;++i){ m.flt[i] = (float)n->int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        m.missflt = (float)n->missuint64;
                        for(i=0;i<m.tlen;++i){ m.flt[i] = (float)n->uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case DOUBLE:                                        
                m.dbl = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        m.missdbl = (double)n->missbyt;
                        for(i=0;i<m.tlen;++i){ m.dbl[i] = (double)n->byt[i]; }
                        break;
                    case CHAR:
                        m.missdbl = (double)n->misschr;
                        for(i=0;i<m.tlen;++i){ m.dbl[i] = (double)n->chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        m.missdbl = (double)n->missshrt;
                        for(i=0;i<m.tlen;++i){ m.dbl[i] = (double)n->shrt[i]; }
                        break;                                      
                    case INT:                                           
                        m.missdbl = (double)n->missintg;
                        for(i=0;i<m.tlen;++i){ m.dbl[i] = (double)n->intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        m.missdbl = (double)n->missflt;
                        for(i=0;i<m.tlen;++i){ m.dbl[i] = (double)n->flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case UBYTE:                                         
                        m.missdbl = (double)n->missubyt;
                        for(i=0;i<m.tlen;++i){ m.dbl[i] = (double)n->ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        m.missdbl = (double)n->missushrt;
                        for(i=0;i<m.tlen;++i){ m.dbl[i] = (double)n->ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        m.missdbl = (double)n->missuint;
                        for(i=0;i<m.tlen;++i){ m.dbl[i] = (double)n->uint[i]; }
                        break;                                      
                    case INT64:                                         
                        m.missdbl = (double)n->missint64;
                        for(i=0;i<m.tlen;++i){ m.dbl[i] = (double)n->int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        m.missdbl = (double)n->missuint64;
                        for(i=0;i<m.tlen;++i){ m.dbl[i] = (double)n->uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case UBYTE:                                         
                m.ubyt = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        if ( (n->missbyt >= MIN_UBYTE) ){
                            m.missubyt = (unsigned char)n->missbyt;
                        }
                        for(i=0;i<m.tlen;++i){ m.ubyt[i] = (unsigned char)n->byt[i]; }
                        break;
                    case CHAR:  /* treating CHAR and UBYTE as equal */
                        m.missubyt = (unsigned char)n->misschr;
                        for(i=0;i<m.tlen;++i){ m.ubyt[i] = (unsigned char)n->chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_UBYTE) && (n->missshrt <= MAX_UBYTE) ){
                            m.missubyt = (unsigned char)n->missshrt;                     
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ubyt[i] = (unsigned char)n->shrt[i]; }
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_UBYTE) && (n->missintg <= MAX_UBYTE) ){
                            m.missubyt = (unsigned char)n->missintg;                 
                        }                                       
                        for(i=0;i<m.tlen;++i){ m.ubyt[i] = (unsigned char)n->intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_UBYTE) && (n->missflt <= MAX_UBYTE) ){
                            m.missubyt = (unsigned char)n->missflt;                      
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ubyt[i] = (unsigned char)n->flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_UBYTE) && (n->missdbl <= MAX_UBYTE) ){
                            m.missubyt = (unsigned char)n->missdbl;                      
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ubyt[i] = (unsigned char)n->dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case USHORT:                                        
                        if ( (n->missushrt <= MAX_UBYTE) ){
                            m.missubyt = (unsigned char)n->missushrt;                
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ubyt[i] = (unsigned char)n->ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_UBYTE) ){
                            m.missubyt = (unsigned char)n->missuint;             
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ubyt[i] = (unsigned char)n->uint[i]; }
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_UBYTE) && (n->missint64 <= MAX_UBYTE) ){
                            m.missubyt = (unsigned char)n->missint64;                    
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ubyt[i] = (unsigned char)n->int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_UBYTE) ){
                            m.missubyt = (unsigned char)n->missuint64;           
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ubyt[i] = (unsigned char)n->uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case USHORT:                                        
                m.ushrt = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        if ( (n->missbyt >= MIN_USHORT) ){
                            m.missushrt = (unsigned short)n->missbyt;
                        }
                        for(i=0;i<m.tlen;++i){ m.ushrt[i] = (unsigned short)n->byt[i]; }
                        break;
                    case CHAR:
                        m.missushrt = (unsigned short)n->misschr;
                        for(i=0;i<m.tlen;++i){ m.ushrt[i] = (unsigned short)n->chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_USHORT) ){
                            m.missushrt = (unsigned short)n->missshrt;                       
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ushrt[i] = (unsigned short)n->shrt[i]; }
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_USHORT) && (n->missintg <= MAX_USHORT) ){
                            m.missushrt = (unsigned short)n->missintg;                   
                        }                                       
                        for(i=0;i<m.tlen;++i){ m.ushrt[i] = (unsigned short)n->intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_USHORT) && (n->missflt <= MAX_USHORT) ){
                            m.missushrt = (unsigned short)n->missflt;                        
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ushrt[i] = (unsigned short)n->flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_USHORT) && (n->missdbl <= MAX_USHORT) ){
                            m.missushrt = (unsigned short)n->missdbl;                        
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ushrt[i] = (unsigned short)n->dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        m.missushrt = (unsigned short)n->missubyt;
                        for(i=0;i<m.tlen;++i){ m.ushrt[i] = (unsigned short)n->ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case UINT:                                          
                        if ( (n->missuint <= MAX_USHORT) ){
                            m.missushrt = (unsigned short)n->missuint;               
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ushrt[i] = (unsigned short)n->uint[i]; }
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_USHORT) && (n->missint64 <= MAX_USHORT) ){
                            m.missushrt = (unsigned short)n->missint64;                  
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ushrt[i] = (unsigned short)n->int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_USHORT) ){
                            m.missushrt = (unsigned short)n->missuint64;         
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ushrt[i] = (unsigned short)n->uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case UINT:                                          
                m.uint = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        if ( (n->missbyt >= MIN_UINT) ){
                            m.missuint = (unsigned int)n->missbyt;
                        }
                        for(i=0;i<m.tlen;++i){ m.uint[i] = (unsigned int)n->byt[i]; }
                        break;
                    case CHAR:
                        m.missuint = (unsigned int)n->misschr;
                        for(i=0;i<m.tlen;++i){ m.uint[i] = (unsigned int)n->chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_UINT) ){
                            m.missuint = (unsigned int)n->missshrt;                      
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.uint[i] = (unsigned int)n->shrt[i]; }
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_UINT) ){
                            m.missuint = (unsigned int)n->missintg;                  
                        }                                       
                        for(i=0;i<m.tlen;++i){ m.uint[i] = (unsigned int)n->intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_UINT) && (n->missflt <= MAX_UINT) ){
                            m.missuint = (unsigned int)n->missflt;                       
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.uint[i] = (unsigned int)n->flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_UINT) && (n->missdbl <= MAX_UINT) ){
                            m.missuint = (unsigned int)n->missdbl;                       
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.uint[i] = (unsigned int)n->dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        m.missuint = (unsigned int)n->missubyt;
                        for(i=0;i<m.tlen;++i){ m.uint[i] = (unsigned int)n->ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        m.missuint = (unsigned int)n->missushrt;
                        for(i=0;i<m.tlen;++i){ m.uint[i] = (unsigned int)n->ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_UINT) && (n->missint64 <= MAX_UINT) ){
                            m.missuint = (unsigned int)n->missint64;                 
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.uint[i] = (unsigned int)n->int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_UINT) ){
                            m.missuint = (unsigned int)n->missuint64;            
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.uint[i] = (unsigned int)n->uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case INT64:                                         
                m.int64 = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        m.missint64 = (long long)n->missbyt;
                        for(i=0;i<m.tlen;++i){ m.int64[i] = (long long)n->byt[i]; }
                        break;
                    case CHAR:
                        m.missint64 = (long long)n->misschr;
                        for(i=0;i<m.tlen;++i){ m.int64[i] = (long long)n->chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        m.missint64 = (long long)n->missshrt;
                        for(i=0;i<m.tlen;++i){ m.int64[i] = (long long)n->shrt[i]; }
                        break;                                      
                    case INT:                                           
                        m.missint64 = (long long)n->missintg;
                        for(i=0;i<m.tlen;++i){ m.int64[i] = (long long)n->intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_INT64) && (n->missflt <= MAX_INT64) ){
                            m.missint64 = (long long)n->missflt;                     
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.int64[i] = (long long)n->flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_INT64) && (n->missdbl <= MAX_INT64) ){
                            m.missint64 = (long long)n->missdbl;                     
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.int64[i] = (long long)n->dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        m.missint64 = (long long)n->missubyt;
                        for(i=0;i<m.tlen;++i){ m.int64[i] = (long long)n->ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        m.missint64 = (long long)n->missushrt;
                        for(i=0;i<m.tlen;++i){ m.int64[i] = (long long)n->ushrt[i]; }
                        break;                                      
                    case UINT:  /* hopefully UINT is smaller than INT64, could check typsize */
                        m.missint64 = (long long)n->missuint;
                        for(i=0;i<m.tlen;++i){ m.int64[i] = (long long)n->uint[i]; }
                        break;                                      
                    case INT64:                                         
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case UINT64:                                        
                        if ( (n->missuint64 <= MAX_INT64) ){
                            m.missint64 = (long long)n->missuint64;          
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.int64[i] = (long long)n->uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case UINT64:                                        
                m.uint64 = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        if ( (n->missbyt >= MIN_UINT64) ){
                            m.missuint64 = (unsigned long long)n->missbyt;
                        }
                        for(i=0;i<m.tlen;++i){ m.uint64[i] = (unsigned long long)n->byt[i]; }
                        break;
                    case CHAR:
                        m.missuint64 = (unsigned long long)n->misschr;
                        for(i=0;i<m.tlen;++i){ m.uint64[i] = (unsigned long long)n->chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        if ( (n->missshrt >= MIN_UINT64) ){
                            m.missuint64 = (unsigned long long)n->missshrt;                      
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.uint64[i] = (unsigned long long)n->shrt[i]; }
                        break;                                      
                    case INT:                                           
                        if ( (n->missintg >= MIN_UINT64) ){
                            m.missuint64 = (unsigned long long)n->missintg;                  
                        }                                       
                        for(i=0;i<m.tlen;++i){ m.uint64[i] = (unsigned long long)n->intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->missflt >= MIN_UINT64) && (n->missflt <= MAX_UINT64) ){
                            m.missuint64 = (unsigned long long)n->missflt;                       
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.uint64[i] = (unsigned long long)n->flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->missdbl >= MIN_UINT64) && (n->missdbl <= MAX_UINT64) ){
                            m.missuint64 = (unsigned long long)n->missdbl;                       
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.uint64[i] = (unsigned long long)n->dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        m.missuint64 = (unsigned long long)n->missubyt;
                        for(i=0;i<m.tlen;++i){ m.uint64[i] = (unsigned long long)n->ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        m.missuint64 = (unsigned long long)n->missushrt;
                        for(i=0;i<m.tlen;++i){ m.uint64[i] = (unsigned long long)n->ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        m.missuint64 = (unsigned long long)n->missuint;
                        for(i=0;i<m.tlen;++i){ m.uint64[i] = (unsigned long long)n->uint[i]; }
                        break;                                      
                    case INT64:                                         
                        if ( (n->missint64 >= MIN_UINT64) ){
                            m.missuint64 = (unsigned long long)n->missint64;                 
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.uint64[i] = (unsigned long long)n->int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            default:
                fprintf(stderr,"Error in castAr: undefined type! m.typ=%d\n",m.typ);
                print_arr_exit(&m);
                break;
        }
    }

    /*  fputs("castAr: 7\n",stderr);  */
    if (freecnd) { freeAr(n); }

    /*  fputs("castAr: 8\n",stderr);  */
    return m;
}

#endif
