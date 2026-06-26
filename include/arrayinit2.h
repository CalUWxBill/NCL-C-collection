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

#define ALLTYPECASES3                                            \
            case BYTE:                                          \
                SWITCHCAST(byt,missbyt,signed char,BYTE,BYT,cBYT,iBYT,compare_byts,"%10hhd","%hhd") \
                break;                                          \
            case CHAR:                                          \
                SWITCHCAST(chr,misschr,char,CHAR,CHR,cCHR,iCHR,compare_chrs,"%10c","%c")           \
                break;                                          \
            case SHORT:                                         \
                SWITCHCAST(shrt,missshrt,short,SHORT,SHT,cSHT,iSHT,compare_shrts,"%10hd","%hd") \
                break;                                          \
            case INT:                                           \
                SWITCHCAST(intg,missintg,int,INT,INTG,cINTG,iINTG,compare_ints,"%10d","%d")               \
                break;                                          \
            case FLOAT:                                         \
                SWITCHCAST(flt,missflt,float,FLOAT,FLT,cFLT,iFLT,compare_flts,"%10f","%f")               \
                break;                                          \
            case DOUBLE:                                        \
                SWITCHCAST(dbl,missdbl,double,DOUBLE,DBL,cDBL,iDBL,compare_dbls,"%10lf","%lf")               \
                break;                                          \
            case UBYTE:                                         \
                SWITCHCAST(ubyt,missubyt,unsigned char,UBYTE,UBYT,cUBYT,iUBYT,compare_ubyts,"%10hhu","%hhu")    \
                break;                                          \
            case USHORT:                                        \
                SWITCHCAST(ushrt,missushrt,unsigned short,USHORT,USHT,cUSHT,iUSHT,compare_ushrts,"%10hu","%hu")  \
                break;                                          \
            case UINT:                                          \
                SWITCHCAST(uint,missuint,unsigned int,UINT,UINTG,cUINTG,iUINTG,compare_uints,"%10u","%u")      \
                break;                                          \
            case INT64:                                         \
                SWITCHCAST(int64,missint64,long long,INT64,LINT,cLINT,iLINT,compare_int64s,"%10lld","%lld")    \
                break;                                          \
            case UINT64:                                        \
                SWITCHCAST(uint64,missuint64,unsigned long long,UINT64,ULINT,cULINT,iULINT,compare_uint64s,"%10llu","%llu") \
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
        /* ([a-zA-Z_]\w*)(\-\>|\.)(ubyt|ushrt|uint64|int64|uint|byt|chr|shrt|intg|flt|dbl|swtyp) */
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
        } ud;
        /* Could also add complex numbers.  Anything else? */
        /* The following correspond to missing values for each possible type of array */
        /* ([a-zA-Z_]\w*)(\->|\.)(missubyt|missushrt|missuint64|missint64|missuint|missbyt|misschr|missshrt|missintg|missflt|missdbl|swmtyp) */
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
        } um;
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
void *ppntr_of(arr *);
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
    static typ_idx maxlen = 100;
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
    typ_idx n = m->tlen;
    if (n > maxlen) { n = maxlen; }
    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)      \
        for (j=0;j<n;++j){ fprintf(stderr,fmt1" ",m->ud.swtyp[j]); } \
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
        return m->ud.swtyp;
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in pntr_of: undefined type %d!\n",m->typ);
            print_arr_exit(m);
            break;
    }
    #undef SWITCHCAST

    return NULL;
}

void *ppntr_of(arr *restrict m){
    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)      \
        return &m->ud.swtyp;
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in ppntr_of: undefined type %d!\n",m->typ);
            print_arr_exit(m);
            break;
    }
    #undef SWITCHCAST

    return NULL;
}

/*
 *  USE WITH CARE!! some arrays accept memory blocks allocated elsewhere so it is safe
 *    to assign a new pointer guaranteed to have at least the same length as long as
 *    the old one will still get freed at its source.
 */
void set_pntr(arr *restrict m,void *n){
    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)      \
        m->ud.swtyp = (swcast *)n;
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in set_pntr: undefined type %d!\n",m->typ);
            print_arr_exit(m);
            break;
    }
    #undef SWITCHCAST

    return;
}

void *address_of_i(arr *restrict m,  typ_idx idx){
    /* Added bounds checking */
    if ((idx >= m->tlen) || (idx < 0)){
        fprintf(stderr,"Error in address_of_i: idx must be from 0 to %lld, it was %lld!\n",m->tlen-1,idx);
        print_arr_exit(m);
    }
    
    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)      \
        return &(m->ud.swtyp[idx]);
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

typ_idx idx_from_c(arr *m, typ_idx *cin){
    typ_idx idx = 0;
    if (m->tlen != 1){
        typ_idx *mlen = m->mlen;
        typ_idx *c    = cin;
        typ_idx n = m->n;
        for (typ_idx j=0;j<n;++j){ idx += *c++ * *mlen++; }
    }
    if ((idx >= m->tlen) || (idx < 0)){
        fprintf(stderr,"Error in idx_from_c: idx must be from 0 to %lld, it was %lld!\n",m->tlen-1,idx);
        typ_idx *mlen = m->mlen;
        typ_idx *c    = cin;
        typ_idx n = m->n;
        for (typ_idx j=0;j<n;++j,c++,mlen++){ 
            fprintf(stderr,"j=%lld, c=%lld, mlen=%lld, idxj=%lld\n", j, *c, *mlen, *c * *mlen);
        }
        print_arr_exit(m);
    }
    return idx;
}

void *address_of_c(arr *restrict m, typ_idx *c){
    return address_of_i(m, idx_from_c(m, c));
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


/* This operation is independent of array2 except for the macros, could move into file with ints ... */
void *init0(typ_idx len,int typ){
    switch (typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2) \
        { \
            swcast *m = NULL;                   \
            if (len > 0){                           \
                swcast *p = m = malloc(len*sizeof *m);  \
                for(typ_idx i=0;i<len;++i){ *p++ = 0; } \
            }                                       \
            return m; \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in init0: undefined type %d!\n",typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST
}   

void *init_to_val(typ_idx len,int typ,void *val){
    switch (typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2) \
        { \
            swcast *m    = NULL;                           \
            if (len > 0){                                  \
                swcast   cval = *(swcast *)val;            \
                swcast *p = m = malloc(len*sizeof *m);     \
                for(typ_idx i=0;i<len;++i){ *p++ = cval; } \
            }                                              \
            return m;                                      \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in init0: undefined type %d!\n",typ);
            exit(0);
            break;
    }
    #undef SWITCHCAST
}   


/* These operations are independent of array2 and should be moved outside */
int *ints(typ_idx len,...){
    typ_idx i;
    int *m = NULL;

    if (len > 0){
        int *p = m = malloc(sizeof(int)*len);

        va_list arg_list;
        va_start(arg_list, len);
        for(i=0;i<len;++i){
            *p++ = va_arg(arg_list, int);
        }
        va_end(arg_list);
    }
    return m;
}   

int *ints_to_val(typ_idx len,int val){
    typ_idx i;
    int *m = NULL;

    if (len > 0){
        int *p = m = malloc(sizeof(int)*len);
        for(i=0;i<len;++i){
            *p++ = val;
        }
    }
    return m;
}   

void set_ints_part(typ_idx ib,typ_idx ie,int *m, ...){
    typ_idx i;
    
    va_list arg_list;
    va_start(arg_list, m);
    for(i=ib;i<=ie;++i){
        *m++ = va_arg(arg_list, int);
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
            *m++ = va_arg(arg_list, int);
        }
        va_end(arg_list);
    }
    return;
}   

void set_ints_to_val_part(typ_idx ib,typ_idx ie,int *m,int val){
    typ_idx i;
    for(i=ib;i<=ie;++i){
        *m++ = val;
    }
    return;
}   

void set_ints_to_val(typ_idx len,int *m,int val){
    typ_idx i;
    if (len > 0){
        for(i=0;i<len;++i){
            *m++ = val;
        }
    }
    return;
}   

int *ints_coord(int xbeg, int xend, int dx, typ_idx *nx_out){
    int *m = NULL;
    typ_idx nx = (xend - xbeg)/dx + 1;

    if (nx > 0){
        int *p = m = malloc(nx*sizeof *m);

        for(int x=xbeg; x<=xend; x += dx){
            *p++ = x;
        }
    }
    *nx_out = nx;
    return m;
}



long long *int64s(typ_idx len,...){
    typ_idx i;
    long long *m = NULL;

    if (len > 0){
        long long *p = m = malloc(sizeof(long long)*len);

        va_list arg_list;
        va_start(arg_list, len);
        for(i=0;i<len;++i){
            *p++ = va_arg(arg_list, long long);
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
        *m++ = va_arg(arg_list, long long);
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
            *m++ = va_arg(arg_list, long long);
        }
        va_end(arg_list);
    }
    return;
}   

void set_int64s_to_val_part(typ_idx ib,typ_idx ie,long long *m,long long val){
    typ_idx i;
    for(i=ib;i<=ie;++i){
        *m++ = val;
    }
    return;
}   

void set_int64s_to_val(typ_idx len,long long *m,long long val){
    typ_idx i;
    if (len > 0){
        for(i=0;i<len;++i){
            *m++ = val;
        }
    }
    return;
}   

long long *int64s_coord(long long xbeg, long long xend, long long dx, typ_idx *nx_out){
    long long *m = NULL;
    typ_idx nx = (xend - xbeg)/dx + 1;

    if (nx > 0){
        long long *p = m = malloc(nx*sizeof *m);

        for(long long x=xbeg; x<=xend; x += dx){
            *p++ = x;
        }
    }
    *nx_out = nx;
    return m;
}


float *flt_coord_dx(float xbeg, float xend, float dx, typ_idx *nx_out){
    float *m = NULL;
    typ_idx nx = (xend - xbeg)/dx + 1;

    if (nx > 0){
        float *p = m = malloc(nx*sizeof *m);
        for(typ_idx i=0;i<nx;++i){
            *p++ = xbeg + i*dx;
        }
    }
    *nx_out = nx;
    return m;
}

float *flt_coord_nx(float xbeg, float xend, typ_idx nx){
    float *m = NULL;
	float dx = (xend - xbeg)/(float)(nx - 1);

    if (nx > 0){
        float *p = m = malloc(nx*sizeof *m);
        for(typ_idx i=0;i<nx;++i){
            *p++ = xbeg + i*dx;
        }
    }
    return m;
}



double *dbls(typ_idx len,...){
    typ_idx i;
    double *m = NULL;

    if (len > 0){
        double *p = m = malloc(sizeof(double)*len);

        va_list arg_list;
        va_start(arg_list, len);
        for(i=0;i<len;++i){
            *p++ = va_arg(arg_list, double);
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
        *m++ = va_arg(arg_list, double);
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
            *m++ = va_arg(arg_list, double);
        }
        va_end(arg_list);
    }
    return;
}

void set_dbls_to_val_part(typ_idx ib,typ_idx ie,double *m,double val){
    typ_idx i;
    for(i=ib;i<=ie;++i){
        *m++ = val;
    }
    return;
}

void set_dbls_to_val(typ_idx len,double *m,double val){
    typ_idx i;
    if (len > 0){
        for(i=0;i<len;++i){
            *m++ = val;
        }
    }
    return;
}

double *dbl_coord_dx(double xbeg, double xend, double dx, typ_idx *nx_out){
    double *m = NULL;
    typ_idx nx = (xend - xbeg)/dx + 1;

    if (nx > 0){
        double *p = m = malloc(nx*sizeof *m);
        for(typ_idx i=0;i<nx;++i){
            *p++ = xbeg + i*dx;
        }
    }
    *nx_out = nx;
    return m;
}

double *dbl_coord_nx(double xbeg, double xend, typ_idx nx){
    double *m = NULL;
	double dx = (xend - xbeg)/(double)(nx - 1);

    if (nx > 0){
        double *p = m = malloc(nx*sizeof *m);
        for(typ_idx i=0;i<nx;++i){
            *p++ = xbeg + i*dx;
        }
    }
    return m;
}



arr **arrs(typ_idx len,...){
    typ_idx i;
    arr **m = NULL;

    if (len > 0){
        arr **p = m = malloc(sizeof(arr *)*len);

        va_list arg_list;
        va_start(arg_list, len);
        for(i=0;i<len;++i){
            *p++ = va_arg(arg_list, arr *);
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
        *m++ = va_arg(arg_list, arr *);
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
            *m++ = va_arg(arg_list, arr *);
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
        *p++ = (float)va_arg(arg_list, double);
    }
    va_end(arg_list);
    return m;
}
 */

int isIdxEqual(typ_idx *a,typ_idx *b,typ_idx n){
    typ_idx i;
    for(i=0;i<n;++i){
        if( *a++ != *b++ ){ return 0; }
    }
    return 1;
}

void defaultMissing(arr *m){
    switch (m->typ) {
        case BYTE:
            m->um.missbyt    = -127;
            break;
        case CHAR:
            m->um.misschr    = 0;
            break;                                      
        case SHORT:                                         
            m->um.missshrt   = -999;
            break;                                      
        case INT:                                           
            m->um.missintg   = -999;
            break;                                      
        case FLOAT:                                         
            m->um.missflt    = -999.0;
            break;                                      
        case DOUBLE:                                        
            m->um.missdbl    = -999.0;
            break;                                      
        case UBYTE:                                         
            m->um.missubyt   = 255;
            break;                                      
        case USHORT:                                        
            m->um.missushrt  = 65535;
            break;                                      
        case UINT:                                          
            m->um.missuint   = 4294967295U;
            break;                                      
        case INT64:                                         
            m->um.missint64  = -9223372036854775807LL;
            break;                                      
        case UINT64:                                        
            m->um.missuint64 = 18446744073709551615ULL;
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
            m->um.swmtyp = n->um.swmtyp;
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
                        if ( (n->um.misschr <= MAX_BYTE) )
                        #endif
                        { m->um.missbyt = (signed char)n->um.misschr; }
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_BYTE) && (n->um.missshrt <= MAX_BYTE) ){
                            m->um.missbyt = (signed char)n->um.missshrt;                       
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_BYTE) && (n->um.missintg <= MAX_BYTE) ){
                            m->um.missbyt = (signed char)n->um.missintg;                   
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_BYTE) && (n->um.missflt <= MAX_BYTE) ){
                            m->um.missbyt = (signed char)n->um.missflt;                        
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_BYTE) && (n->um.missdbl <= MAX_BYTE) ){
                            m->um.missbyt = (signed char)n->um.missdbl;                        
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        if ( (n->um.missubyt <= MAX_BYTE) ){
                            m->um.missbyt = (signed char)n->um.missubyt;               
                        }                                           
                        break;                                      
                    case USHORT:                                        
                        if ( (n->um.missushrt <= MAX_BYTE) ){
                            m->um.missbyt = (signed char)n->um.missushrt;              
                        }                                           
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_BYTE) ){
                            m->um.missbyt = (signed char)n->um.missuint;               
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_BYTE) && (n->um.missint64 <= MAX_BYTE) ){
                            m->um.missbyt = (signed char)n->um.missint64;                  
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_BYTE) ){
                            m->um.missbyt = (signed char)n->um.missuint64;         
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
                        if ( (n->um.missbyt >= MIN_CHAR) )
                        #endif
                        { m->um.misschr = (char)n->um.missbyt; }
                        break;
                    case CHAR:
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_CHAR) && (n->um.missshrt <= MAX_CHAR) ){
                            m->um.misschr = (char)n->um.missshrt;                      
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_CHAR) && (n->um.missintg <= MAX_CHAR) ){
                            m->um.misschr = (char)n->um.missintg;                  
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_CHAR) && (n->um.missflt <= MAX_CHAR) ){
                            m->um.misschr = (char)n->um.missflt;                       
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_CHAR) && (n->um.missdbl <= MAX_CHAR) ){
                            m->um.misschr = (char)n->um.missdbl;                       
                        }                                           
                        break;                                      
                    case UBYTE: /* treating the same as CHAR, but this isn't necessarily true */
                        m->um.misschr = (char)n->um.missubyt;                              
                        break;                                      
                    case USHORT:                                        
                        if ( (n->um.missushrt <= MAX_CHAR) ){
                            m->um.misschr = (char)n->um.missushrt;             
                        }                                           
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_CHAR) ){
                            m->um.misschr = (char)n->um.missuint;              
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_CHAR) && (n->um.missint64 <= MAX_CHAR) ){
                            m->um.misschr = (char)n->um.missint64;                 
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_CHAR) ){
                            m->um.misschr = (char)n->um.missuint64;            
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
                        m->um.missshrt = (short)n->um.missbyt;
                        break;
                    case CHAR:
                        m->um.missshrt = (short)n->um.misschr;
                        break;                                      
                    case SHORT:                                         
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_SHORT) && (n->um.missintg <= MAX_SHORT) ){
                            m->um.missshrt = (short)n->um.missintg;                    
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_SHORT) && (n->um.missflt <= MAX_SHORT) ){
                            m->um.missshrt = (short)n->um.missflt;                     
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_SHORT) && (n->um.missdbl <= MAX_SHORT) ){
                            m->um.missshrt = (short)n->um.missdbl;                     
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        m->um.missshrt = (short)n->um.missubyt;
                        break;                                      
                    case USHORT:                                        
                        if ( (n->um.missushrt <= MAX_SHORT) ){
                            m->um.missshrt = (short)n->um.missushrt;               
                        }                                           
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_SHORT) ){
                            m->um.missshrt = (short)n->um.missuint;                
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_SHORT) && (n->um.missint64 <= MAX_SHORT) ){
                            m->um.missshrt = (short)n->um.missint64;                   
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_SHORT) ){
                            m->um.missshrt = (short)n->um.missuint64;          
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
                        m->um.missintg = (int)n->um.missbyt;
                        break;
                    case CHAR:
                        m->um.missintg = (int)n->um.misschr;
                        break;                                      
                    case SHORT:                                         
                        m->um.missintg = (int)n->um.missshrt;
                        break;                                      
                    case INT:                                           
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_INT) && (n->um.missflt <= MAX_INT) ){
                            m->um.missintg = (int)n->um.missflt;                       
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_INT) && (n->um.missdbl <= MAX_INT) ){
                            m->um.missintg = (int)n->um.missdbl;                       
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        m->um.missintg = (int)n->um.missubyt;
                        break;                                      
                    case USHORT:    /* INT should be greater than USHORT unless same typesize */
                        m->um.missintg = (int)n->um.missushrt;
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_INT) ){
                            m->um.missintg = (int)n->um.missuint;              
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_INT) && (n->um.missint64 <= MAX_INT) ){
                            m->um.missintg = (int)n->um.missint64;                 
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_INT) ){
                            m->um.missintg = (int)n->um.missuint64;            
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
                        m->um.missflt = (float)n->um.missbyt;
                        break;
                    case CHAR:
                        m->um.missflt = (float)n->um.misschr;
                        break;                                      
                    case SHORT:                                         
                        m->um.missflt = (float)n->um.missshrt;
                        break;                                      
                    case INT:                                           
                        m->um.missflt = (float)n->um.missintg;
                        break;                                      
                    case FLOAT:                                         
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_FLOAT) && (n->um.missdbl <= MAX_FLOAT) ){
                            m->um.missflt = (float)n->um.missdbl;                      
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        m->um.missflt = (float)n->um.missubyt;
                        break;                                      
                    case USHORT:                                        
                        m->um.missflt = (float)n->um.missushrt;
                        break;                                      
                    case UINT:                                          
                        m->um.missflt = (float)n->um.missuint;
                        break;                                      
                    case INT64:                                         
                        m->um.missflt = (float)n->um.missint64;
                        break;                                      
                    case UINT64:                                        
                        m->um.missflt = (float)n->um.missuint64;
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
                        m->um.missdbl = (double)n->um.missbyt;
                        break;
                    case CHAR:
                        m->um.missdbl = (double)n->um.misschr;
                        break;                                      
                    case SHORT:                                         
                        m->um.missdbl = (double)n->um.missshrt;
                        break;                                      
                    case INT:                                           
                        m->um.missdbl = (double)n->um.missintg;
                        break;                                      
                    case FLOAT:                                         
                        m->um.missdbl = (double)n->um.missflt;
                        break;                                      
                    case DOUBLE:                                        
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case UBYTE:                                         
                        m->um.missdbl = (double)n->um.missubyt;
                        break;                                      
                    case USHORT:                                        
                        m->um.missdbl = (double)n->um.missushrt;
                        break;                                      
                    case UINT:                                          
                        m->um.missdbl = (double)n->um.missuint;
                        break;                                      
                    case INT64:                                         
                        m->um.missdbl = (double)n->um.missint64;
                        break;                                      
                    case UINT64:                                        
                        m->um.missdbl = (double)n->um.missuint64;
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
                        if ( (n->um.missbyt >= MIN_UBYTE) ){
                            m->um.missubyt = (unsigned char)n->um.missbyt;
                        }
                        break;
                    case CHAR:  /* treating CHAR and UBYTE as equal */
                        m->um.missubyt = (unsigned char)n->um.misschr;
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_UBYTE) && (n->um.missshrt <= MAX_UBYTE) ){
                            m->um.missubyt = (unsigned char)n->um.missshrt;                        
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_UBYTE) && (n->um.missintg <= MAX_UBYTE) ){
                            m->um.missubyt = (unsigned char)n->um.missintg;                    
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_UBYTE) && (n->um.missflt <= MAX_UBYTE) ){
                            m->um.missubyt = (unsigned char)n->um.missflt;                     
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_UBYTE) && (n->um.missdbl <= MAX_UBYTE) ){
                            m->um.missubyt = (unsigned char)n->um.missdbl;                     
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case USHORT:                                        
                        if ( (n->um.missushrt <= MAX_UBYTE) ){
                            m->um.missubyt = (unsigned char)n->um.missushrt;               
                        }                                           
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_UBYTE) ){
                            m->um.missubyt = (unsigned char)n->um.missuint;                
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_UBYTE) && (n->um.missint64 <= MAX_UBYTE) ){
                            m->um.missubyt = (unsigned char)n->um.missint64;                   
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_UBYTE) ){
                            m->um.missubyt = (unsigned char)n->um.missuint64;          
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
                        if ( (n->um.missbyt >= MIN_USHORT) ){
                            m->um.missushrt = (unsigned short)n->um.missbyt;
                        }
                        break;
                    case CHAR:
                        m->um.missushrt = (unsigned short)n->um.misschr;
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_USHORT) ){
                            m->um.missushrt = (unsigned short)n->um.missshrt;                      
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_USHORT) && (n->um.missintg <= MAX_USHORT) ){
                            m->um.missushrt = (unsigned short)n->um.missintg;                  
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_USHORT) && (n->um.missflt <= MAX_USHORT) ){
                            m->um.missushrt = (unsigned short)n->um.missflt;                       
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_USHORT) && (n->um.missdbl <= MAX_USHORT) ){
                            m->um.missushrt = (unsigned short)n->um.missdbl;                       
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        m->um.missushrt = (unsigned short)n->um.missubyt;
                        break;                                      
                    case USHORT:                                        
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_USHORT) ){
                            m->um.missushrt = (unsigned short)n->um.missuint;              
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_USHORT) && (n->um.missint64 <= MAX_USHORT) ){
                            m->um.missushrt = (unsigned short)n->um.missint64;                 
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_USHORT) ){
                            m->um.missushrt = (unsigned short)n->um.missuint64;            
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
                        if ( (n->um.missbyt >= MIN_UINT) ){
                            m->um.missuint = (unsigned int)n->um.missbyt;
                        }
                        break;
                    case CHAR:
                        m->um.missuint = (unsigned int)n->um.misschr;
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_UINT) ){
                            m->um.missuint = (unsigned int)n->um.missshrt;                     
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_UINT) ){
                            m->um.missuint = (unsigned int)n->um.missintg;                 
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_UINT) && (n->um.missflt <= MAX_UINT) ){
                            m->um.missuint = (unsigned int)n->um.missflt;                      
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_UINT) && (n->um.missdbl <= MAX_UINT) ){
                            m->um.missuint = (unsigned int)n->um.missdbl;                      
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        m->um.missuint = (unsigned int)n->um.missubyt;
                        break;                                      
                    case USHORT:                                        
                        m->um.missuint = (unsigned int)n->um.missushrt;
                        break;                                      
                    case UINT:                                          
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_UINT) && (n->um.missint64 <= MAX_UINT) ){
                            m->um.missuint = (unsigned int)n->um.missint64;                    
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_UINT) ){
                            m->um.missuint = (unsigned int)n->um.missuint64;           
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
                        m->um.missint64 = (long long)n->um.missbyt;
                        break;
                    case CHAR:
                        m->um.missint64 = (long long)n->um.misschr;
                        break;                                      
                    case SHORT:                                         
                        m->um.missint64 = (long long)n->um.missshrt;
                        break;                                      
                    case INT:                                           
                        m->um.missint64 = (long long)n->um.missintg;
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_INT64) && (n->um.missflt <= MAX_INT64) ){
                            m->um.missint64 = (long long)n->um.missflt;                        
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_INT64) && (n->um.missdbl <= MAX_INT64) ){
                            m->um.missint64 = (long long)n->um.missdbl;                        
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        m->um.missint64 = (long long)n->um.missubyt;
                        break;                                      
                    case USHORT:                                        
                        m->um.missint64 = (long long)n->um.missushrt;
                        break;                                      
                    case UINT:  /* hopefully UINT is smaller than INT64, could check typsize */
                        m->um.missint64 = (long long)n->um.missuint;
                        break;                                      
                    case INT64:                                         
                        fprintf(stderr,"Error in copyMiss: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_INT64) ){
                            m->um.missint64 = (long long)n->um.missuint64;         
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
                        if ( (n->um.missbyt >= MIN_UINT64) ){
                            m->um.missuint64 = (unsigned long long)n->um.missbyt;
                        }
                        break;
                    case CHAR:
                        m->um.missuint64 = (unsigned long long)n->um.misschr;
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_UINT64) ){
                            m->um.missuint64 = (unsigned long long)n->um.missshrt;                     
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_UINT64) ){
                            m->um.missuint64 = (unsigned long long)n->um.missintg;                 
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_UINT64) && (n->um.missflt <= MAX_UINT64) ){
                            m->um.missuint64 = (unsigned long long)n->um.missflt;                      
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_UINT64) && (n->um.missdbl <= MAX_UINT64) ){
                            m->um.missuint64 = (unsigned long long)n->um.missdbl;                      
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        m->um.missuint64 = (unsigned long long)n->um.missubyt;
                        break;                                      
                    case USHORT:                                        
                        m->um.missuint64 = (unsigned long long)n->um.missushrt;
                        break;                                      
                    case UINT:                                          
                        m->um.missuint64 = (unsigned long long)n->um.missuint;
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_UINT64) ){
                            m->um.missuint64 = (unsigned long long)n->um.missint64;                    
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
    // signed char *byt;           /* BYTE  */
    // char *chr;                  /* CHAR   */
    // short *shrt;                /* SHORT  */
    // int *intg;                  /* INT    */
    // float *flt;                 /* FLOAT  */
    // double *dbl;                /* DOUBLE */
    // unsigned char *ubyt;        /* UBYTE  */
    // unsigned short *ushrt;      /* USHORT */
    // unsigned int *uint;         /* UINT   */
    // long long *int64;           /* INT64  */
    // unsigned long long *uint64; /* UINT64 */


    if (outtyp == n->typ){
        switch (outtyp){
        #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
            { \
                swcast *swtyp = malloc(sizeof(swcast)); \
                *swtyp = n->um.swmtyp;  \
                return swtyp; \
            }
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
                        if ( (n->um.misschr <= MAX_BYTE) )
                        #endif
                        {
                            signed char *byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->um.misschr;
                            return byt;
                        }
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_BYTE) && (n->um.missshrt <= MAX_BYTE) ){
                            signed char *byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->um.missshrt;                     
                            return byt;
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_BYTE) && (n->um.missintg <= MAX_BYTE) ){
                            signed char *byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->um.missintg;                 
                            return byt;
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_BYTE) && (n->um.missflt <= MAX_BYTE) ){
                            signed char *byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->um.missflt;                      
                            return byt;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_BYTE) && (n->um.missdbl <= MAX_BYTE) ){
                            signed char *byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->um.missdbl;                      
                            return byt;
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        if ( (n->um.missubyt <= MAX_BYTE) ){
                            signed char *byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->um.missubyt;             
                            return byt;
                        }                                           
                        break;                                      
                    case USHORT:                                        
                        if ( (n->um.missushrt <= MAX_BYTE) ){
                            signed char *byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->um.missushrt;                
                            return byt;
                        }                                           
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_BYTE) ){
                            signed char *byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->um.missuint;             
                            return byt;
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_BYTE) && (n->um.missint64 <= MAX_BYTE) ){
                            signed char *byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->um.missint64;                    
                            return byt;
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_BYTE) ){
                            signed char *byt = malloc(sizeof(signed char));
                            *byt = (signed char)n->um.missuint64;           
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
                        if ( (n->um.missbyt >= MIN_CHAR) )
                        #endif
                        {
                            char *chr = malloc(sizeof(char));
                            *chr = (char)n->um.missbyt;
                            return chr;
                        }
                        break;
                    case CHAR:
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_CHAR) && (n->um.missshrt <= MAX_CHAR) ){
                            char *chr = malloc(sizeof(char));
                            *chr = (char)n->um.missshrt;                        
                            return chr;
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_CHAR) && (n->um.missintg <= MAX_CHAR) ){
                            char *chr = malloc(sizeof(char));
                            *chr = (char)n->um.missintg;                    
                            return chr;
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_CHAR) && (n->um.missflt <= MAX_CHAR) ){
                            char *chr = malloc(sizeof(char));
                            *chr = (char)n->um.missflt;                     
                            return chr;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_CHAR) && (n->um.missdbl <= MAX_CHAR) ){
                            char *chr = malloc(sizeof(char));
                            *chr = (char)n->um.missdbl;                     
                            return chr;
                        }                                           
                        break;                                      
                    case UBYTE: /* treating the same as CHAR, but this isn't necessarily true */
                        {
                            char *chr = malloc(sizeof(char));
                            *chr = (char)n->um.missubyt;                                
                                return chr;
                        }
                        break;                                      
                    case USHORT:                                        
                        if ( (n->um.missushrt <= MAX_CHAR) ){
                            char *chr = malloc(sizeof(char));
                            *chr = (char)n->um.missushrt;               
                            return chr;
                        }                                           
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_CHAR) ){
                            char *chr = malloc(sizeof(char));
                            *chr = (char)n->um.missuint;                
                            return chr;
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_CHAR) && (n->um.missint64 <= MAX_CHAR) ){
                            char *chr = malloc(sizeof(char));
                            *chr = (char)n->um.missint64;                   
                            return chr;
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_CHAR) ){
                            char *chr = malloc(sizeof(char));
                            *chr = (char)n->um.missuint64;          
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
                        {
                            short *shrt = malloc(sizeof(short));
                            *shrt = (short)n->um.missbyt;
                                return shrt;
                        }                                           
                        break;
                    case CHAR:
                        {
                            short *shrt = malloc(sizeof(short));
                            *shrt = (short)n->um.misschr;
                                return shrt;
                        }                                           
                        break;                                      
                    case SHORT:                                         
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_SHORT) && (n->um.missintg <= MAX_SHORT) ){
                            short *shrt = malloc(sizeof(short));
                            *shrt = (short)n->um.missintg;                  
                            return shrt;
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_SHORT) && (n->um.missflt <= MAX_SHORT) ){
                            short *shrt = malloc(sizeof(short));
                            *shrt = (short)n->um.missflt;                       
                            return shrt;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_SHORT) && (n->um.missdbl <= MAX_SHORT) ){
                            short *shrt = malloc(sizeof(short));
                            *shrt = (short)n->um.missdbl;                       
                            return shrt;
                        }                                           
                        break;                                      
                    case UBYTE:                                       
                        {
                            short *shrt = malloc(sizeof(short));
                            *shrt = (short)n->um.missubyt;
                                return shrt;
                        }                                           
                        break;                                      
                    case USHORT:                                        
                        if ( (n->um.missushrt <= MAX_SHORT) ){
                            short *shrt = malloc(sizeof(short));
                            *shrt = (short)n->um.missushrt;             
                            return shrt;
                        }                                           
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_SHORT) ){
                            short *shrt = malloc(sizeof(short));
                            *shrt = (short)n->um.missuint;              
                            return shrt;
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_SHORT) && (n->um.missint64 <= MAX_SHORT) ){
                            short *shrt = malloc(sizeof(short));
                            *shrt = (short)n->um.missint64;                 
                            return shrt;
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_SHORT) ){
                            short *shrt = malloc(sizeof(short));
                            *shrt = (short)n->um.missuint64;            
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
                        {
                            int *intg = malloc(sizeof(int));
                            *intg = (int)n->um.missbyt;
                                return intg;
                        }                                           
                        break;
                    case CHAR:
                        {
                            int *intg = malloc(sizeof(int));
                            *intg = (int)n->um.misschr;
                                return intg;
                        }                                           
                        break;                                      
                    case SHORT:                                         
                        {
                            int *intg = malloc(sizeof(int));
                            *intg = (int)n->um.missshrt;
                                return intg;
                        }                                           
                        break;                                      
                    case INT:                                           
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_INT) && (n->um.missflt <= MAX_INT) ){
                            int *intg = malloc(sizeof(int));
                            *intg = (int)n->um.missflt;                     
                            return intg;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_INT) && (n->um.missdbl <= MAX_INT) ){
                            int *intg = malloc(sizeof(int));
                            *intg = (int)n->um.missdbl;                     
                            return intg;
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        {
                            int *intg = malloc(sizeof(int));
                            *intg = (int)n->um.missubyt;
                                return intg;
                        }                                           
                        break;                                      
                    case USHORT:    /* INT should be greater than USHORT unless same typesize */
                        {
                            int *intg = malloc(sizeof(int));
                            *intg = (int)n->um.missushrt;
                                return intg;
                        }                                           
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_INT) ){
                            int *intg = malloc(sizeof(int));
                            *intg = (int)n->um.missuint;                
                            return intg;
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_INT) && (n->um.missint64 <= MAX_INT) ){
                            int *intg = malloc(sizeof(int));
                            *intg = (int)n->um.missint64;                   
                            return intg;
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_INT) ){
                            int *intg = malloc(sizeof(int));
                            *intg = (int)n->um.missuint64;          
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
                        {
                            float *flt = malloc(sizeof(float));
                            *flt = (float)n->um.missbyt;
                                return flt;
                        }                                           
                        break;
                    case CHAR:
                        {
                            float *flt = malloc(sizeof(float));
                            *flt = (float)n->um.misschr;
                                return flt;
                        }                                           
                        break;                                      
                    case SHORT:                                         
                        {
                            float *flt = malloc(sizeof(float));
                            *flt = (float)n->um.missshrt;
                                return flt;
                        }                                           
                        break;                                      
                    case INT:                                           
                        {
                            float *flt = malloc(sizeof(float));
                            *flt = (float)n->um.missintg;
                                return flt;
                        }                                           
                        break;                                      
                    case FLOAT:                                         
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_FLOAT) && (n->um.missdbl <= MAX_FLOAT) ){
                            float *flt = malloc(sizeof(float));
                            *flt = (float)n->um.missdbl;                        
                            return flt;
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        {
                            float *flt = malloc(sizeof(float));
                            *flt = (float)n->um.missubyt;
                                return flt;
                        }                                           
                        break;                                      
                    case USHORT:                                        
                        {
                            float *flt = malloc(sizeof(float));
                            *flt = (float)n->um.missushrt;
                                return flt;
                        }                                           
                        break;                                      
                    case UINT:                                          
                        {
                            float *flt = malloc(sizeof(float));
                            *flt = (float)n->um.missuint;
                                return flt;
                        }                                           
                        break;                                      
                    case INT64:                                         
                        {
                            float *flt = malloc(sizeof(float));
                            *flt = (float)n->um.missint64;
                                return flt;
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        {
                            float *flt = malloc(sizeof(float));
                            *flt = (float)n->um.missuint64;
                                return flt;
                        }                                           
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
                        {
                        double *dbl = malloc(sizeof(double));
                        *dbl = (double)n->um.missbyt;
                            return dbl;
                        }                                           
                        break;
                    case CHAR:
                        {
                        double *dbl = malloc(sizeof(double));
                        *dbl = (double)n->um.misschr;
                            return dbl;
                        }                                           
                        break;                                      
                    case SHORT:                                         
                        {
                        double *dbl = malloc(sizeof(double));
                        *dbl = (double)n->um.missshrt;
                            return dbl;
                        }                                           
                        break;                                      
                    case INT:                                           
                        {
                        double *dbl = malloc(sizeof(double));
                        *dbl = (double)n->um.missintg;
                            return dbl;
                        }                                           
                        break;                                      
                    case FLOAT:                                         
                        {
                        double *dbl = malloc(sizeof(double));
                        *dbl = (double)n->um.missflt;
                            return dbl;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case UBYTE:                                         
                        {
                        double *dbl = malloc(sizeof(double));
                        *dbl = (double)n->um.missubyt;
                            return dbl;
                        }                                           
                        break;                                      
                    case USHORT:                                        
                        {
                        double *dbl = malloc(sizeof(double));
                        *dbl = (double)n->um.missushrt;
                            return dbl;
                        }                                           
                        break;                                      
                    case UINT:                                          
                        {
                        double *dbl = malloc(sizeof(double));
                        *dbl = (double)n->um.missuint;
                            return dbl;
                        }                                           
                        break;                                      
                    case INT64:                                         
                        {
                        double *dbl = malloc(sizeof(double));
                        *dbl = (double)n->um.missint64;
                            return dbl;
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        {
                        double *dbl = malloc(sizeof(double));
                        *dbl = (double)n->um.missuint64;
                            return dbl;
                        }                                           
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
                        if ( (n->um.missbyt >= MIN_UBYTE) ){
                            unsigned char *ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->um.missbyt;
                            return ubyt;
                        }
                        break;
                    case CHAR:  /* treating CHAR and UBYTE as equal */
                        {
                        unsigned char *ubyt = malloc(sizeof(unsigned char));
                        *ubyt = (unsigned char)n->um.misschr;
                            return ubyt;
                        }                                           
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_UBYTE) && (n->um.missshrt <= MAX_UBYTE) ){
                            unsigned char *ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->um.missshrt;                      
                            return ubyt;
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_UBYTE) && (n->um.missintg <= MAX_UBYTE) ){
                            unsigned char *ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->um.missintg;                  
                            return ubyt;
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_UBYTE) && (n->um.missflt <= MAX_UBYTE) ){
                            unsigned char *ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->um.missflt;                       
                            return ubyt;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_UBYTE) && (n->um.missdbl <= MAX_UBYTE) ){
                            unsigned char *ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->um.missdbl;                       
                            return ubyt;
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case USHORT:                                        
                        if ( (n->um.missushrt <= MAX_UBYTE) ){
                            unsigned char *ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->um.missushrt;             
                            return ubyt;
                        }                                           
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_UBYTE) ){
                            unsigned char *ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->um.missuint;              
                            return ubyt;
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_UBYTE) && (n->um.missint64 <= MAX_UBYTE) ){
                            unsigned char *ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->um.missint64;                 
                            return ubyt;
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_UBYTE) ){
                            unsigned char *ubyt = malloc(sizeof(unsigned char));
                            *ubyt = (unsigned char)n->um.missuint64;            
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
                        if ( (n->um.missbyt >= MIN_USHORT) ){
                            unsigned short *ushrt = malloc(sizeof(unsigned short));
                            *ushrt = (unsigned short)n->um.missbyt;
                            return ushrt;
                        }
                        break;
                    case CHAR:
                        {
                        unsigned short *ushrt = malloc(sizeof(unsigned short));
                        *ushrt = (unsigned short)n->um.misschr;
                            return ushrt;
                        }                                           
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_USHORT) ){
                            unsigned short *ushrt = malloc(sizeof(unsigned short));
                            *ushrt = (unsigned short)n->um.missshrt;                        
                            return ushrt;
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_USHORT) && (n->um.missintg <= MAX_USHORT) ){
                            unsigned short *ushrt = malloc(sizeof(unsigned short));
                            *ushrt = (unsigned short)n->um.missintg;                    
                            return ushrt;
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_USHORT) && (n->um.missflt <= MAX_USHORT) ){
                            unsigned short *ushrt = malloc(sizeof(unsigned short));
                            *ushrt = (unsigned short)n->um.missflt;                     
                            return ushrt;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_USHORT) && (n->um.missdbl <= MAX_USHORT) ){
                            unsigned short *ushrt = malloc(sizeof(unsigned short));
                            *ushrt = (unsigned short)n->um.missdbl;                     
                            return ushrt;
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        {
                        unsigned short *ushrt = malloc(sizeof(unsigned short));
                        *ushrt = (unsigned short)n->um.missubyt;
                            return ushrt;
                        }                                           
                        break;                                      
                    case USHORT:                                        
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_USHORT) ){
                            unsigned short *ushrt = malloc(sizeof(unsigned short));
                            *ushrt = (unsigned short)n->um.missuint;                
                            return ushrt;
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_USHORT) && (n->um.missint64 <= MAX_USHORT) ){
                            unsigned short *ushrt = malloc(sizeof(unsigned short));
                            *ushrt = (unsigned short)n->um.missint64;                   
                            return ushrt;
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_USHORT) ){
                            unsigned short *ushrt = malloc(sizeof(unsigned short));
                            *ushrt = (unsigned short)n->um.missuint64;          
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
                        if ( (n->um.missbyt >= MIN_UINT) ){
                            unsigned int *uint = malloc(sizeof(unsigned int));
                            *uint = (unsigned int)n->um.missbyt;
                            return uint;
                        }
                        break;
                    case CHAR:
                        {
                        unsigned int *uint = malloc(sizeof(unsigned int));
                        *uint = (unsigned int)n->um.misschr;
                            return uint;
                        }                                           
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_UINT) ){
                            unsigned int *uint = malloc(sizeof(unsigned int));
                            *uint = (unsigned int)n->um.missshrt;                       
                            return uint;
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_UINT) ){
                            unsigned int *uint = malloc(sizeof(unsigned int));
                            *uint = (unsigned int)n->um.missintg;                   
                            return uint;
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_UINT) && (n->um.missflt <= MAX_UINT) ){
                            unsigned int *uint = malloc(sizeof(unsigned int));
                            *uint = (unsigned int)n->um.missflt;                        
                            return uint;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_UINT) && (n->um.missdbl <= MAX_UINT) ){
                            unsigned int *uint = malloc(sizeof(unsigned int));
                            *uint = (unsigned int)n->um.missdbl;                        
                            return uint;
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        {
                        unsigned int *uint = malloc(sizeof(unsigned int));
                        *uint = (unsigned int)n->um.missubyt;
                            return uint;
                        }                                           
                        break;                                      
                    case USHORT:                                        
                        {
                        unsigned int *uint = malloc(sizeof(unsigned int));
                        *uint = (unsigned int)n->um.missushrt;
                            return uint;
                        }                                           
                        break;                                      
                    case UINT:                                          
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_UINT) && (n->um.missint64 <= MAX_UINT) ){
                            unsigned int *uint = malloc(sizeof(unsigned int));
                            *uint = (unsigned int)n->um.missint64;                  
                            return uint;
                        }                                           
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_UINT) ){
                            unsigned int *uint = malloc(sizeof(unsigned int));
                            *uint = (unsigned int)n->um.missuint64;         
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
                        {
                        long long *int64 = malloc(sizeof(long long));
                        *int64 = (long long)n->um.missbyt;
                            return int64;
                        }                                           
                        break;
                    case CHAR:
                        {
                        long long *int64 = malloc(sizeof(long long));
                        *int64 = (long long)n->um.misschr;
                            return int64;
                        }                                           
                        break;                                      
                    case SHORT:                                         
                        {
                        long long *int64 = malloc(sizeof(long long));
                        *int64 = (long long)n->um.missshrt;
                            return int64;
                        }                                           
                        break;                                      
                    case INT:                                           
                        {
                        long long *int64 = malloc(sizeof(long long));
                        *int64 = (long long)n->um.missintg;
                            return int64;
                        }                                           
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_INT64) && (n->um.missflt <= MAX_INT64) ){
                            long long *int64 = malloc(sizeof(long long));
                            *int64 = (long long)n->um.missflt;                      
                            return int64;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_INT64) && (n->um.missdbl <= MAX_INT64) ){
                            long long *int64 = malloc(sizeof(long long));
                            *int64 = (long long)n->um.missdbl;                      
                            return int64;
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        {
                        long long *int64 = malloc(sizeof(long long));
                        *int64 = (long long)n->um.missubyt;
                            return int64;
                        }                                           
                        break;                                      
                    case USHORT:                                        
                        {
                        long long *int64 = malloc(sizeof(long long));
                        *int64 = (long long)n->um.missushrt;
                            return int64;
                        }                                           
                        break;                                      
                    case UINT:  /* hopefully UINT is smaller than INT64, could check typsize */
                        {
                        long long *int64 = malloc(sizeof(long long));
                        *int64 = (long long)n->um.missuint;
                            return int64;
                        }                                           
                        break;                                      
                    case INT64:                                         
                        fprintf(stderr,"Error in getMissAsType: equal types shouldn't reach this point! outtyp=%d n->typ=%d\n",outtyp,n->typ);
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_INT64) ){
                            long long *int64 = malloc(sizeof(long long));
                            *int64 = (long long)n->um.missuint64;           
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
                        if ( (n->um.missbyt >= MIN_UINT64) ){
                            unsigned long long *uint64 = malloc(sizeof(unsigned long long));
                            *uint64 = (unsigned long long)n->um.missbyt;
                            return uint64;
                        }
                        break;
                    case CHAR:
                        {
                        unsigned long long *uint64 = malloc(sizeof(unsigned long long));
                        *uint64 = (unsigned long long)n->um.misschr;
                            return uint64;
                        }                                           
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_UINT64) ){
                            unsigned long long *uint64 = malloc(sizeof(unsigned long long));
                            *uint64 = (unsigned long long)n->um.missshrt;                       
                            return uint64;
                        }                                           
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_UINT64) ){
                            unsigned long long *uint64 = malloc(sizeof(unsigned long long));
                            *uint64 = (unsigned long long)n->um.missintg;                   
                            return uint64;
                        }                                       
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_UINT64) && (n->um.missflt <= MAX_UINT64) ){
                            unsigned long long *uint64 = malloc(sizeof(unsigned long long));
                            *uint64 = (unsigned long long)n->um.missflt;                        
                            return uint64;
                        }                                           
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_UINT64) && (n->um.missdbl <= MAX_UINT64) ){
                            unsigned long long *uint64 = malloc(sizeof(unsigned long long));
                            *uint64 = (unsigned long long)n->um.missdbl;                        
                            return uint64;
                        }                                           
                        break;                                      
                    case UBYTE:                                         
                        {
                        unsigned long long *uint64 = malloc(sizeof(unsigned long long));
                        *uint64 = (unsigned long long)n->um.missubyt;
                            return uint64;
                        }                                           
                        break;                                      
                    case USHORT:                                        
                        {
                        unsigned long long *uint64 = malloc(sizeof(unsigned long long));
                        *uint64 = (unsigned long long)n->um.missushrt;
                            return uint64;
                        }                                           
                        break;                                      
                    case UINT:                                          
                        {
                        unsigned long long *uint64 = malloc(sizeof(unsigned long long));
                        *uint64 = (unsigned long long)n->um.missuint;
                            return uint64;
                        }                                           
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_UINT64) ){
                            unsigned long long *uint64 = malloc(sizeof(unsigned long long));
                            *uint64 = (unsigned long long)n->um.missint64;                  
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
        return &(m->um.swmtyp);
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
        if (m->ud.swtyp[idx] == m->um.swmtyp) { return 1; } else { return 0; }
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
    return isMiss(m,idx_from_c(m, c));
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

/* Should probably retrieve missing value, then step through pointer comparing to missing value */
int isAnyMiss(arr *restrict m){
    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        { \
            swcast swmtyp = m->um.swmtyp; \
            swcast *p     = m->ud.swtyp;  \
            for(typ_idx i=0;i<m->tlen;++i){ if(*p++ == swmtyp){ return 1; } } \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in isAnyMiss: undefined type %d!\n",m->typ);
            print_arr_exit(m);
            break;
    }
    #undef SWITCHCAST
    return 0;
}

/* Should probably retrieve missing value, then step through pointer comparing to missing value */
int isAnyNonMiss(arr *restrict m){
    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        { \
            swcast swmtyp = m->um.swmtyp; \
            swcast *p     = m->ud.swtyp;  \
            for(typ_idx i=0;i<m->tlen;++i){ if(*p++ != swmtyp){ return 1; } } \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in isAnyNonMiss: undefined type %d!\n",m->typ);
            print_arr_exit(m);
            break;
    }
    #undef SWITCHCAST
    return 0;
}

/* Should probably retrieve missing value, then step through pointer comparing to missing value */
typ_idx countNonMiss(arr *restrict X){
    typ_idx count = X->tlen;
    switch (X->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        { \
            swcast mtyp = X->um.swmtyp; \
            swcast *p   = X->ud.swtyp;  \
            for(typ_idx i=0;i<X->tlen;++i){ if(*p++ == mtyp){ --count; } } \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in countNonMiss: undefined type %d!\n",X->typ);
            print_arr_exit(X);
            break;
    }
    #undef SWITCHCAST
    return count;
}

/* Should probably retrieve missing value, then step through pointer comparing to missing value */
typ_idx countMiss(arr *restrict X){
    typ_idx count = 0;
    switch (X->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        { \
            swcast mtyp = X->um.swmtyp; \
            swcast *p   = X->ud.swtyp;  \
            for(typ_idx i=0;i<X->tlen;++i){ if(*p++ == mtyp){ ++count; } } \
        }
        ALLTYPECASES
        default:
            fprintf(stderr,"Error in countMiss: undefined type %d!\n",X->typ);
            print_arr_exit(X);
            break;
    }
    #undef SWITCHCAST
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
    // typ_idx j;
    // typ_idx idx = 0;
    // if (arrays[0]->tlen != 1){
    //     for (j=0;j<arrays[0]->n;++j){
    //         idx += c[j]*arrays[0]->mlen[j];
    //     }
    // }
    // 
    // return isAnyMissMultiAr(narrs,arrays,idx);
    return isAnyMissMultiAr(narrs,arrays,idx_from_c(arrays[0], c));
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
        m->ud.swtyp[idx] = m->um.swmtyp;
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
    // typ_idx j;
    // typ_idx idx = 0;
    // if (m->tlen != 1){
    //     for (j=0;j<m->n;++j){ idx += c[j]*m->mlen[j]; }
    // }

    setToMiss(m,idx_from_c(m, c));
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
        typ_idx *m_len  = m.len  = malloc(ndims*sizeof(typ_idx));
        typ_idx *m_mlen = m.mlen = malloc(ndims*sizeof(typ_idx));

        for (j=0; j<ndims; ++j) {
            m_len[j] = len[j];
            m.tlen *= m_len[j];
        }

        m_mlen[ndims - 1] = 1;
        for (j=ndims - 2; j>-1; --j) {
            m_mlen[j] = m_mlen[j + 1] * m_len[j + 1];
        }
    }

    switch (typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        m.ud.swtyp = init0(m.tlen,swmacro);
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
        m.ud.swtyp[0] = *(swcast *)val;
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
    m.um.missuint64 = 0;
    m.ud.uint64 = NULL;

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
        m.um.swmtyp = n->um.swmtyp;                                                               \
        m.ud.swtyp  = (swcast *)init0(m.tlen,swmacro);
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
        { \
            swcast *pin  = n->ud.swtyp;                   \
            swcast *pout = m.ud.swtyp;                    \
            for(i=0;i<m.tlen;++i){ *pout++ = *pin++; } \
        }
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
        for(i=0;i<m->tlen;++i){ m->ud.swtyp[i] = bswap_16(m->ud.swtyp[i]); }
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
        for(i=0;i<m->tlen;++i){ m->ud.swtyp[i] = bswap_32(m->ud.swtyp[i]); }
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
        for(i=0;i<m->tlen;++i){ m->ud.swtyp[i] = bswap_64(m->ud.swtyp[i]); }
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
        {                                               \
            m->um.swmtyp    = n->um.swmtyp;                   \
            swcast *pin  = n->ud.swtyp;                    \
            swcast *pout = m->ud.swtyp;                    \
            for(i=0;i<m->tlen;++i){ *pout++ = *pin++; } \
        }
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
    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        { \
            swcast xc    = *(swcast *)x; \
            swcast *pout = m->ud.swtyp;     \
            for(typ_idx i=0;i<m->tlen;++i){ *pout++ = xc; } \
        }
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
    switch (m->typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)  \
        { \
            swcast xc    = m->um.swmtyp; \
            swcast *pout = m->ud.swtyp;  \
            for(typ_idx i=0;i<m->tlen;++i){ *pout++ = xc; } \
        }
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
        typ_idx *m_len  = m->len  = malloc(ndims*sizeof(typ_idx));
        typ_idx *m_mlen = m->mlen = malloc(ndims*sizeof(typ_idx));

        for (j=0; j<ndims; ++j) {
            m_len[j] = len[j];
            m->tlen *= m_len[j];
        }

        if (m->tlen != tlenorig){
            fprintf(stderr,"reshapeArList: tlen of input must be same as original array, tlen=%lld, tlenorig=%lld\n",
                m->tlen,tlenorig);
            print_arr_exit(m);
        }
    
        m_mlen[ndims - 1] = 1;
        for (j=ndims - 2; j>-1; --j) {
            m_mlen[j] = m_mlen[j + 1] * m_len[j + 1];
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
        typ_idx *m_len  = m.len  = malloc(ndims*sizeof(typ_idx));
        typ_idx *m_mlen = m.mlen = malloc(ndims*sizeof(typ_idx));

        for (j=0; j<ndims; ++j) {
            m_len[j] = len[j];
            m.tlen  *= m_len[j];
        }

        m_mlen[ndims - 1] = 1;
        for (j=ndims - 2; j>-1; --j) {
            m_mlen[j] = m_mlen[j + 1] * m_len[j + 1];
        }
    }

    switch (m.typ) {
    #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)              \
        m.ud.swtyp = (swcast *)n;
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
        if (m->ud.swtyp != NULL){ \
            free(m->ud.swtyp); \
            m->ud.swtyp = NULL; \
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
    // signed char *byt;               /* BYTE  */
    // char *chr;                  /* CHAR   */
    // short *shrt;                /* SHORT  */
    // int *intg;                  /* INT    */
    // float *flt;                 /* FLOAT  */
    // double *dbl;                /* DOUBLE */
    // unsigned char *ubyt;            /* UBYTE  */
    // unsigned short *ushrt;          /* USHORT */
    // unsigned int *uint;         /* UINT   */
    // long long *int64;               /* INT64  */
    // unsigned long long *uint64;     /* UINT64 */

    switch (outtyp) {
        case BYTE:
            {
            signed char *byt = malloc(sizeof(signed char));
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
            }
    #undef SWITCHCAST
            break;
        case CHAR:
            {
                char *chr = malloc(sizeof(char));
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
            }
    #undef SWITCHCAST
            break;
        case SHORT:
            {
            short *shrt = malloc(sizeof(short));
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
            }
    #undef SWITCHCAST
            break;
        case INT:
            {
            int *intg = malloc(sizeof(int));
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
            }
    #undef SWITCHCAST
            break;
        case FLOAT:
            {
            float *flt = malloc(sizeof(float));
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
            }
    #undef SWITCHCAST
            break;
        case DOUBLE:
            {
            double *dbl = malloc(sizeof(double));
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
            }
    #undef SWITCHCAST
            break;
        case UBYTE:
            {
            unsigned char *ubyt = malloc(sizeof(unsigned char));
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
            }
    #undef SWITCHCAST
            break;
        case USHORT:
            {
            unsigned short *ushrt = malloc(sizeof(unsigned short));
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
            }
    #undef SWITCHCAST
            break;
        case UINT:
            {
            unsigned int *uint = malloc(sizeof(unsigned int));
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
            }
    #undef SWITCHCAST
            break;
        case INT64:
            {
            long long *int64 = malloc(sizeof(long long));
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
            }
    #undef SWITCHCAST
            break;
        case UINT64:
            {
            unsigned long long *uint64 = malloc(sizeof(unsigned long long));
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

void copyArVals(arr *restrict m,arr *restrict n) {
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
            {                              \
                swcast *pin   = n->ud.swtyp;  \
                swcast *pout  = m->ud.swtyp;  \
                swcast n_miss = n->um.swmtyp; \
                swcast m_miss = m->um.swmtyp; \
                for(i=0;i<n->tlen;++i){    \
                    if (*pin == n_miss){   \
                        *pout++ = m_miss;  \
                        pin++;             \
                    } else {               \
                        *pout++ = *pin++;  \
                    }                      \
                }                          \
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
                            if (n->ud.chr[i] == n->um.misschr){
                                m->ud.byt[i] = m->um.missbyt;
                            } else {
                                m->ud.byt[i] = (signed char)n->ud.chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.shrt[i] == n->um.missshrt){
                                m->ud.byt[i] = m->um.missbyt;
                            } else {
                                m->ud.byt[i] = (signed char)n->ud.shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.intg[i] == n->um.missintg){
                                m->ud.byt[i] = m->um.missbyt;
                            } else {
                                m->ud.byt[i] = (signed char)n->ud.intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.flt[i] == n->um.missflt){
                                m->ud.byt[i] = m->um.missbyt;
                            } else {
                                m->ud.byt[i] = (signed char)n->ud.flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.dbl[i] == n->um.missdbl){
                                m->ud.byt[i] = m->um.missbyt;
                            } else {
                                m->ud.byt[i] = (signed char)n->ud.dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ubyt[i] == n->um.missubyt){
                                m->ud.byt[i] = m->um.missbyt;
                            } else {
                                m->ud.byt[i] = (signed char)n->ud.ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ushrt[i] == n->um.missushrt){
                                m->ud.byt[i] = m->um.missbyt;
                            } else {
                                m->ud.byt[i] = (signed char)n->ud.ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint[i] == n->um.missuint){
                                m->ud.byt[i] = m->um.missbyt;
                            } else {
                                m->ud.byt[i] = (signed char)n->ud.uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.int64[i] == n->um.missint64){
                                m->ud.byt[i] = m->um.missbyt;
                            } else {
                                m->ud.byt[i] = (signed char)n->ud.int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint64[i] == n->um.missuint64){
                                m->ud.byt[i] = m->um.missbyt;
                            } else {
                                m->ud.byt[i] = (signed char)n->ud.uint64[i];
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
                            if (n->ud.byt[i] == n->um.missbyt){
                                m->ud.chr[i] = m->um.misschr;
                            } else {
                                m->ud.chr[i] = (char)n->ud.byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.shrt[i] == n->um.missshrt){
                                m->ud.chr[i] = m->um.misschr;
                            } else {
                                m->ud.chr[i] = (char)n->ud.shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.intg[i] == n->um.missintg){
                                m->ud.chr[i] = m->um.misschr;
                            } else {
                                m->ud.chr[i] = (char)n->ud.intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.flt[i] == n->um.missflt){
                                m->ud.chr[i] = m->um.misschr;
                            } else {
                                m->ud.chr[i] = (char)n->ud.flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.dbl[i] == n->um.missdbl){
                                m->ud.chr[i] = m->um.misschr;
                            } else {
                                m->ud.chr[i] = (char)n->ud.dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE: /* treating the same as CHAR, but this isn't necessarily true */
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ubyt[i] == n->um.missubyt){
                                m->ud.chr[i] = m->um.misschr;
                            } else {
                                m->ud.chr[i] = (char)n->ud.ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ushrt[i] == n->um.missushrt){
                                m->ud.chr[i] = m->um.misschr;
                            } else {
                                m->ud.chr[i] = (char)n->ud.ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint[i] == n->um.missuint){
                                m->ud.chr[i] = m->um.misschr;
                            } else {
                                m->ud.chr[i] = (char)n->ud.uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.int64[i] == n->um.missint64){
                                m->ud.chr[i] = m->um.misschr;
                            } else {
                                m->ud.chr[i] = (char)n->ud.int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint64[i] == n->um.missuint64){
                                m->ud.chr[i] = m->um.misschr;
                            } else {
                                m->ud.chr[i] = (char)n->ud.uint64[i];
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
                            if (n->ud.byt[i] == n->um.missbyt){
                                m->ud.shrt[i] = m->um.missshrt;
                            } else {
                                m->ud.shrt[i] = (short)n->ud.byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.chr[i] == n->um.misschr){
                                m->ud.shrt[i] = m->um.missshrt;
                            } else {
                                m->ud.shrt[i] = (short)n->ud.chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.intg[i] == n->um.missintg){
                                m->ud.shrt[i] = m->um.missshrt;
                            } else {
                                m->ud.shrt[i] = (short)n->ud.intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.flt[i] == n->um.missflt){
                                m->ud.shrt[i] = m->um.missshrt;
                            } else {
                                m->ud.shrt[i] = (short)n->ud.flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.dbl[i] == n->um.missdbl){
                                m->ud.shrt[i] = m->um.missshrt;
                            } else {
                                m->ud.shrt[i] = (short)n->ud.dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ubyt[i] == n->um.missubyt){
                                m->ud.shrt[i] = m->um.missshrt;
                            } else {
                                m->ud.shrt[i] = (short)n->ud.ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ushrt[i] == n->um.missushrt){
                                m->ud.shrt[i] = m->um.missshrt;
                            } else {
                                m->ud.shrt[i] = (short)n->ud.ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint[i] == n->um.missuint){
                                m->ud.shrt[i] = m->um.missshrt;
                            } else {
                                m->ud.shrt[i] = (short)n->ud.uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.int64[i] == n->um.missint64){
                                m->ud.shrt[i] = m->um.missshrt;
                            } else {
                                m->ud.shrt[i] = (short)n->ud.int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint64[i] == n->um.missuint64){
                                m->ud.shrt[i] = m->um.missshrt;
                            } else {
                                m->ud.shrt[i] = (short)n->ud.uint64[i];
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
                            if (n->ud.byt[i] == n->um.missbyt){
                                m->ud.intg[i] = m->um.missintg;
                            } else {
                                m->ud.intg[i] = (int)n->ud.byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.chr[i] == n->um.misschr){
                                m->ud.intg[i] = m->um.missintg;
                            } else {
                                m->ud.intg[i] = (int)n->ud.chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.shrt[i] == n->um.missshrt){
                                m->ud.intg[i] = m->um.missintg;
                            } else {
                                m->ud.intg[i] = (int)n->ud.shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           

                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.flt[i] == n->um.missflt){
                                m->ud.intg[i] = m->um.missintg;
                            } else {
                                m->ud.intg[i] = (int)n->ud.flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.dbl[i] == n->um.missdbl){
                                m->ud.intg[i] = m->um.missintg;
                            } else {
                                m->ud.intg[i] = (int)n->ud.dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ubyt[i] == n->um.missubyt){
                                m->ud.intg[i] = m->um.missintg;
                            } else {
                                m->ud.intg[i] = (int)n->ud.ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:    /* INT should be greater than USHORT unless same typesize */
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ushrt[i] == n->um.missushrt){
                                m->ud.intg[i] = m->um.missintg;
                            } else {
                                m->ud.intg[i] = (int)n->ud.ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint[i] == n->um.missuint){
                                m->ud.intg[i] = m->um.missintg;
                            } else {
                                m->ud.intg[i] = (int)n->ud.uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.int64[i] == n->um.missint64){
                                m->ud.intg[i] = m->um.missintg;
                            } else {
                                m->ud.intg[i] = (int)n->ud.int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint64[i] == n->um.missuint64){
                                m->ud.intg[i] = m->um.missintg;
                            } else {
                                m->ud.intg[i] = (int)n->ud.uint64[i];
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
                            if (n->ud.byt[i] == n->um.missbyt){
                                m->ud.flt[i] = m->um.missflt;
                            } else {
                                m->ud.flt[i] = (float)n->ud.byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.chr[i] == n->um.misschr){
                                m->ud.flt[i] = m->um.missflt;
                            } else {
                                m->ud.flt[i] = (float)n->ud.chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.shrt[i] == n->um.missshrt){
                                m->ud.flt[i] = m->um.missflt;
                            } else {
                                m->ud.flt[i] = (float)n->ud.shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.intg[i] == n->um.missintg){
                                m->ud.flt[i] = m->um.missflt;
                            } else {
                                m->ud.flt[i] = (float)n->ud.intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.dbl[i] == n->um.missdbl){
                                m->ud.flt[i] = m->um.missflt;
                            } else {
                                m->ud.flt[i] = (float)n->ud.dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ubyt[i] == n->um.missubyt){
                                m->ud.flt[i] = m->um.missflt;
                            } else {
                                m->ud.flt[i] = (float)n->ud.ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ushrt[i] == n->um.missushrt){
                                m->ud.flt[i] = m->um.missflt;
                            } else {
                                m->ud.flt[i] = (float)n->ud.ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint[i] == n->um.missuint){
                                m->ud.flt[i] = m->um.missflt;
                            } else {
                                m->ud.flt[i] = (float)n->ud.uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.int64[i] == n->um.missint64){
                                m->ud.flt[i] = m->um.missflt;
                            } else {
                                m->ud.flt[i] = (float)n->ud.int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint64[i] == n->um.missuint64){
                                m->ud.flt[i] = m->um.missflt;
                            } else {
                                m->ud.flt[i] = (float)n->ud.uint64[i];
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
                            if (n->ud.byt[i] == n->um.missbyt){
                                m->ud.dbl[i] = m->um.missdbl;
                            } else {
                                m->ud.dbl[i] = (double)n->ud.byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.chr[i] == n->um.misschr){
                                m->ud.dbl[i] = m->um.missdbl;
                            } else {
                                m->ud.dbl[i] = (double)n->ud.chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.shrt[i] == n->um.missshrt){
                                m->ud.dbl[i] = m->um.missdbl;
                            } else {
                                m->ud.dbl[i] = (double)n->ud.shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.intg[i] == n->um.missintg){
                                m->ud.dbl[i] = m->um.missdbl;
                            } else {
                                m->ud.dbl[i] = (double)n->ud.intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.flt[i] == n->um.missflt){
                                m->ud.dbl[i] = m->um.missdbl;
                            } else {
                                m->ud.dbl[i] = (double)n->ud.flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ubyt[i] == n->um.missubyt){
                                m->ud.dbl[i] = m->um.missdbl;
                            } else {
                                m->ud.dbl[i] = (double)n->ud.ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ushrt[i] == n->um.missushrt){
                                m->ud.dbl[i] = m->um.missdbl;
                            } else {
                                m->ud.dbl[i] = (double)n->ud.ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint[i] == n->um.missuint){
                                m->ud.dbl[i] = m->um.missdbl;
                            } else {
                                m->ud.dbl[i] = (double)n->ud.uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.int64[i] == n->um.missint64){
                                m->ud.dbl[i] = m->um.missdbl;
                            } else {
                                m->ud.dbl[i] = (double)n->ud.int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint64[i] == n->um.missuint64){
                                m->ud.dbl[i] = m->um.missdbl;
                            } else {
                                m->ud.dbl[i] = (double)n->ud.uint64[i];
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
                            if (n->ud.byt[i] == n->um.missbyt){
                                m->ud.ubyt[i] = m->um.missubyt;
                            } else {
                                m->ud.ubyt[i] = (unsigned char)n->ud.byt[i];
                            }
                        }
                        break;
                    case CHAR:  /* treating CHAR and UBYTE as equal */
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.chr[i] == n->um.misschr){
                                m->ud.ubyt[i] = m->um.missubyt;
                            } else {
                                m->ud.ubyt[i] = (unsigned char)n->ud.chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.shrt[i] == n->um.missshrt){
                                m->ud.ubyt[i] = m->um.missubyt;
                            } else {
                                m->ud.ubyt[i] = (unsigned char)n->ud.shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.intg[i] == n->um.missintg){
                                m->ud.ubyt[i] = m->um.missubyt;
                            } else {
                                m->ud.ubyt[i] = (unsigned char)n->ud.intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.flt[i] == n->um.missflt){
                                m->ud.ubyt[i] = m->um.missubyt;
                            } else {
                                m->ud.ubyt[i] = (unsigned char)n->ud.flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.dbl[i] == n->um.missdbl){
                                m->ud.ubyt[i] = m->um.missubyt;
                            } else {
                                m->ud.ubyt[i] = (unsigned char)n->ud.dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ushrt[i] == n->um.missushrt){
                                m->ud.ubyt[i] = m->um.missubyt;
                            } else {
                                m->ud.ubyt[i] = (unsigned char)n->ud.ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint[i] == n->um.missuint){
                                m->ud.ubyt[i] = m->um.missubyt;
                            } else {
                                m->ud.ubyt[i] = (unsigned char)n->ud.uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.int64[i] == n->um.missint64){
                                m->ud.ubyt[i] = m->um.missubyt;
                            } else {
                                m->ud.ubyt[i] = (unsigned char)n->ud.int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint64[i] == n->um.missuint64){
                                m->ud.ubyt[i] = m->um.missubyt;
                            } else {
                                m->ud.ubyt[i] = (unsigned char)n->ud.uint64[i];
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
                            if (n->ud.byt[i] == n->um.missbyt){
                                m->ud.ushrt[i] = m->um.missushrt;
                            } else {
                                m->ud.ushrt[i] = (unsigned short)n->ud.byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.chr[i] == n->um.misschr){
                                m->ud.ushrt[i] = m->um.missushrt;
                            } else {
                                m->ud.ushrt[i] = (unsigned short)n->ud.chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.shrt[i] == n->um.missshrt){
                                m->ud.ushrt[i] = m->um.missushrt;
                            } else {
                                m->ud.ushrt[i] = (unsigned short)n->ud.shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.intg[i] == n->um.missintg){
                                m->ud.ushrt[i] = m->um.missushrt;
                            } else {
                                m->ud.ushrt[i] = (unsigned short)n->ud.intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.flt[i] == n->um.missflt){
                                m->ud.ushrt[i] = m->um.missushrt;
                            } else {
                                m->ud.ushrt[i] = (unsigned short)n->ud.flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.dbl[i] == n->um.missdbl){
                                m->ud.ushrt[i] = m->um.missushrt;
                            } else {
                                m->ud.ushrt[i] = (unsigned short)n->ud.dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ubyt[i] == n->um.missubyt){
                                m->ud.ushrt[i] = m->um.missushrt;
                            } else {
                                m->ud.ushrt[i] = (unsigned short)n->ud.ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint[i] == n->um.missuint){
                                m->ud.ushrt[i] = m->um.missushrt;
                            } else {
                                m->ud.ushrt[i] = (unsigned short)n->ud.uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.int64[i] == n->um.missint64){
                                m->ud.ushrt[i] = m->um.missushrt;
                            } else {
                                m->ud.ushrt[i] = (unsigned short)n->ud.int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint64[i] == n->um.missuint64){
                                m->ud.ushrt[i] = m->um.missushrt;
                            } else {
                                m->ud.ushrt[i] = (unsigned short)n->ud.uint64[i];
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
                            if (n->ud.byt[i] == n->um.missbyt){
                                m->ud.uint[i] = m->um.missuint;
                            } else {
                                m->ud.uint[i] = (unsigned int)n->ud.byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.chr[i] == n->um.misschr){
                                m->ud.uint[i] = m->um.missuint;
                            } else {
                                m->ud.uint[i] = (unsigned int)n->ud.chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.shrt[i] == n->um.missshrt){
                                m->ud.uint[i] = m->um.missuint;
                            } else {
                                m->ud.uint[i] = (unsigned int)n->ud.shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.intg[i] == n->um.missintg){
                                m->ud.uint[i] = m->um.missuint;
                            } else {
                                m->ud.uint[i] = (unsigned int)n->ud.intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.flt[i] == n->um.missflt){
                                m->ud.uint[i] = m->um.missuint;
                            } else {
                                m->ud.uint[i] = (unsigned int)n->ud.flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.dbl[i] == n->um.missdbl){
                                m->ud.uint[i] = m->um.missuint;
                            } else {
                                m->ud.uint[i] = (unsigned int)n->ud.dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ubyt[i] == n->um.missubyt){
                                m->ud.uint[i] = m->um.missuint;
                            } else {
                                m->ud.uint[i] = (unsigned int)n->ud.ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ushrt[i] == n->um.missushrt){
                                m->ud.uint[i] = m->um.missuint;
                            } else {
                                m->ud.uint[i] = (unsigned int)n->ud.ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.int64[i] == n->um.missint64){
                                m->ud.uint[i] = m->um.missuint;
                            } else {
                                m->ud.uint[i] = (unsigned int)n->ud.int64[i];
                            }
                        }
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint64[i] == n->um.missuint64){
                                m->ud.uint[i] = m->um.missuint;
                            } else {
                                m->ud.uint[i] = (unsigned int)n->ud.uint64[i];
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
                            if (n->ud.byt[i] == n->um.missbyt){
                                m->ud.int64[i] = m->um.missint64;
                            } else {
                                m->ud.int64[i] = (long long)n->ud.byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.chr[i] == n->um.misschr){
                                m->ud.int64[i] = m->um.missint64;
                            } else {
                                m->ud.int64[i] = (long long)n->ud.chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.shrt[i] == n->um.missshrt){
                                m->ud.int64[i] = m->um.missint64;
                            } else {
                                m->ud.int64[i] = (long long)n->ud.shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.intg[i] == n->um.missintg){
                                m->ud.int64[i] = m->um.missint64;
                            } else {
                                m->ud.int64[i] = (long long)n->ud.intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.flt[i] == n->um.missflt){
                                m->ud.int64[i] = m->um.missint64;
                            } else {
                                m->ud.int64[i] = (long long)n->ud.flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.dbl[i] == n->um.missdbl){
                                m->ud.int64[i] = m->um.missint64;
                            } else {
                                m->ud.int64[i] = (long long)n->ud.dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ubyt[i] == n->um.missubyt){
                                m->ud.int64[i] = m->um.missint64;
                            } else {
                                m->ud.int64[i] = (long long)n->ud.ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ushrt[i] == n->um.missushrt){
                                m->ud.int64[i] = m->um.missint64;
                            } else {
                                m->ud.int64[i] = (long long)n->ud.ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:  /* hopefully UINT is smaller than INT64, could check typsize */
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint[i] == n->um.missuint){
                                m->ud.int64[i] = m->um.missint64;
                            } else {
                                m->ud.int64[i] = (long long)n->ud.uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        fprintf(stderr,"Error in copyArVals: equal types shouldn't reach this point! m->typ=%d n->typ=%d\n",m->typ,n->typ);
                        break;                                      
                    case UINT64:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint64[i] == n->um.missuint64){
                                m->ud.int64[i] = m->um.missint64;
                            } else {
                                m->ud.int64[i] = (long long)n->ud.uint64[i];
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
                            if (n->ud.byt[i] == n->um.missbyt){
                                m->ud.uint64[i] = m->um.missuint64;
                            } else {
                                m->ud.uint64[i] = (unsigned long long)n->ud.byt[i];
                            }
                        }
                        break;
                    case CHAR:
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.chr[i] == n->um.misschr){
                                m->ud.uint64[i] = m->um.missuint64;
                            } else {
                                m->ud.uint64[i] = (unsigned long long)n->ud.chr[i];
                            }
                        }
                        break;                                      
                    case SHORT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.shrt[i] == n->um.missshrt){
                                m->ud.uint64[i] = m->um.missuint64;
                            } else {
                                m->ud.uint64[i] = (unsigned long long)n->ud.shrt[i];
                            }
                        }
                        break;                                      
                    case INT:                                           
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.intg[i] == n->um.missintg){
                                m->ud.uint64[i] = m->um.missuint64;
                            } else {
                                m->ud.uint64[i] = (unsigned long long)n->ud.intg[i];
                            }
                        }
                        break;                                      
                    case FLOAT:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.flt[i] == n->um.missflt){
                                m->ud.uint64[i] = m->um.missuint64;
                            } else {
                                m->ud.uint64[i] = (unsigned long long)n->ud.flt[i];
                            }
                        }
                        break;                                      
                    case DOUBLE:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.dbl[i] == n->um.missdbl){
                                m->ud.uint64[i] = m->um.missuint64;
                            } else {
                                m->ud.uint64[i] = (unsigned long long)n->ud.dbl[i];
                            }
                        }
                        break;                                      
                    case UBYTE:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ubyt[i] == n->um.missubyt){
                                m->ud.uint64[i] = m->um.missuint64;
                            } else {
                                m->ud.uint64[i] = (unsigned long long)n->ud.ubyt[i];
                            }
                        }
                        break;                                      
                    case USHORT:                                        
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.ushrt[i] == n->um.missushrt){
                                m->ud.uint64[i] = m->um.missuint64;
                            } else {
                                m->ud.uint64[i] = (unsigned long long)n->ud.ushrt[i];
                            }
                        }
                        break;                                      
                    case UINT:                                          
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.uint[i] == n->um.missuint){
                                m->ud.uint64[i] = m->um.missuint64;
                            } else {
                                m->ud.uint64[i] = (unsigned long long)n->ud.uint[i];
                            }
                        }
                        break;                                      
                    case INT64:                                         
                        for(i=0;i<n->tlen;++i){
                            if (n->ud.int64[i] == n->um.missint64){
                                m->ud.uint64[i] = m->um.missuint64;
                            } else {
                                m->ud.uint64[i] = (unsigned long long)n->ud.int64[i];
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
    int dbgcond = ( (n->tlen == 80) && (n->um.missdbl > 1e10) );
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
            m.ud.swtyp = malloc(m.tlen*m.typsize);                                     \
            {                                              \
                m.um.swmtyp = n->um.swmtyp;                      \
                swcast *pin  = n->ud.swtyp;                   \
                swcast *pout = m.ud.swtyp;                    \
                for(i=0;i<m.tlen;++i){ *pout++ = *pin++; } \
            }
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
                m.ud.byt = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;
                    case CHAR:
                        #if MAX_BYTE < MAX_CHAR
                        if ( (n->um.misschr <= MAX_BYTE) )
                        #endif
                        {
                            m.um.missbyt = (signed char)n->um.misschr;
                        }
                        for(i=0;i<m.tlen;++i){ m.ud.byt[i] = (signed char)n->ud.chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_BYTE) && (n->um.missshrt <= MAX_BYTE) ){
                            m.um.missbyt = (signed char)n->um.missshrt;                        
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.byt[i] = (signed char)n->ud.shrt[i]; }
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_BYTE) && (n->um.missintg <= MAX_BYTE) ){
                            m.um.missbyt = (signed char)n->um.missintg;                    
                        }                                       
                        for(i=0;i<m.tlen;++i){ m.ud.byt[i] = (signed char)n->ud.intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_BYTE) && (n->um.missflt <= MAX_BYTE) ){
                            m.um.missbyt = (signed char)n->um.missflt;                     
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.byt[i] = (signed char)n->ud.flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_BYTE) && (n->um.missdbl <= MAX_BYTE) ){
                            m.um.missbyt = (signed char)n->um.missdbl;                     
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.byt[i] = (signed char)n->ud.dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        if ( (n->um.missubyt <= MAX_BYTE) ){
                            m.um.missbyt = (signed char)n->um.missubyt;                
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.byt[i] = (signed char)n->ud.ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        if ( (n->um.missushrt <= MAX_BYTE) ){
                            m.um.missbyt = (signed char)n->um.missushrt;               
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.byt[i] = (signed char)n->ud.ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_BYTE) ){
                            m.um.missbyt = (signed char)n->um.missuint;                
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.byt[i] = (signed char)n->ud.uint[i]; }
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_BYTE) && (n->um.missint64 <= MAX_BYTE) ){
                            m.um.missbyt = (signed char)n->um.missint64;                   
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.byt[i] = (signed char)n->ud.int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_BYTE) ){
                            m.um.missbyt = (signed char)n->um.missuint64;          
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.byt[i] = (signed char)n->ud.uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case CHAR:                                          
                m.ud.chr = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        #if MAX_BYTE < MAX_CHAR
                        if ( (n->um.missbyt >= MIN_CHAR) )
                        #endif
                        {
                            m.um.misschr = (char)n->um.missbyt;
                        }
                        for(i=0;i<m.tlen;++i){ m.ud.chr[i] = (char)n->ud.byt[i]; }
                        break;
                    case CHAR:
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_CHAR) && (n->um.missshrt <= MAX_CHAR) ){
                            m.um.misschr = (char)n->um.missshrt;                       
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.chr[i] = (char)n->ud.shrt[i]; }
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_CHAR) && (n->um.missintg <= MAX_CHAR) ){
                            m.um.misschr = (char)n->um.missintg;                   
                        }                                       
                        for(i=0;i<m.tlen;++i){ m.ud.chr[i] = (char)n->ud.intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_CHAR) && (n->um.missflt <= MAX_CHAR) ){
                            m.um.misschr = (char)n->um.missflt;                        
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.chr[i] = (char)n->ud.flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_CHAR) && (n->um.missdbl <= MAX_CHAR) ){
                            m.um.misschr = (char)n->um.missdbl;                        
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.chr[i] = (char)n->ud.dbl[i]; }
                        break;                                      
                    case UBYTE: /* treating the same as CHAR, but this isn't necessarily true */
                        m.um.misschr = (char)n->um.missubyt;                               
                        for(i=0;i<m.tlen;++i){ m.ud.chr[i] = (char)n->ud.ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        if ( (n->um.missushrt <= MAX_CHAR) ){
                            m.um.misschr = (char)n->um.missushrt;              
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.chr[i] = (char)n->ud.ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_CHAR) ){
                            m.um.misschr = (char)n->um.missuint;               
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.chr[i] = (char)n->ud.uint[i]; }
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_CHAR) && (n->um.missint64 <= MAX_CHAR) ){
                            m.um.misschr = (char)n->um.missint64;                  
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.chr[i] = (char)n->ud.int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_CHAR) ){
                            m.um.misschr = (char)n->um.missuint64;         
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.chr[i] = (char)n->ud.uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case SHORT:                                         
                m.ud.shrt = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        m.um.missshrt = (short)n->um.missbyt;
                        for(i=0;i<m.tlen;++i){ m.ud.shrt[i] = (short)n->ud.byt[i]; }
                        break;
                    case CHAR:
                        m.um.missshrt = (short)n->um.misschr;
                        for(i=0;i<m.tlen;++i){ m.ud.shrt[i] = (short)n->ud.chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_SHORT) && (n->um.missintg <= MAX_SHORT) ){
                            m.um.missshrt = (short)n->um.missintg;                 
                        }                                       
                        for(i=0;i<m.tlen;++i){ m.ud.shrt[i] = (short)n->ud.intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_SHORT) && (n->um.missflt <= MAX_SHORT) ){
                            m.um.missshrt = (short)n->um.missflt;                      
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.shrt[i] = (short)n->ud.flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_SHORT) && (n->um.missdbl <= MAX_SHORT) ){
                            m.um.missshrt = (short)n->um.missdbl;                      
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.shrt[i] = (short)n->ud.dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        m.um.missshrt = (short)n->um.missubyt;
                        for(i=0;i<m.tlen;++i){ m.ud.shrt[i] = (short)n->ud.ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        if ( (n->um.missushrt <= MAX_SHORT) ){
                            m.um.missshrt = (short)n->um.missushrt;                
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.shrt[i] = (short)n->ud.ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_SHORT) ){
                            m.um.missshrt = (short)n->um.missuint;             
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.shrt[i] = (short)n->ud.uint[i]; }
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_SHORT) && (n->um.missint64 <= MAX_SHORT) ){
                            m.um.missshrt = (short)n->um.missint64;                    
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.shrt[i] = (short)n->ud.int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_SHORT) ){
                            m.um.missshrt = (short)n->um.missuint64;           
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.shrt[i] = (short)n->ud.uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case INT:                                           
                m.ud.intg = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        m.um.missintg = (int)n->um.missbyt;
                        for(i=0;i<m.tlen;++i){ m.ud.intg[i] = (int)n->ud.byt[i]; }
                        break;
                    case CHAR:
                        m.um.missintg = (int)n->um.misschr;
                        for(i=0;i<m.tlen;++i){ m.ud.intg[i] = (int)n->ud.chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        m.um.missintg = (int)n->um.missshrt;
                        for(i=0;i<m.tlen;++i){ m.ud.intg[i] = (int)n->ud.shrt[i]; }
                        break;                                      
                    case INT:                                           
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_INT) && (n->um.missflt <= MAX_INT) ){
                            m.um.missintg = (int)n->um.missflt;                        
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.intg[i] = (int)n->ud.flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_INT) && (n->um.missdbl <= MAX_INT) ){
                            m.um.missintg = (int)n->um.missdbl;                        
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.intg[i] = (int)n->ud.dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        m.um.missintg = (int)n->um.missubyt;
                        for(i=0;i<m.tlen;++i){ m.ud.intg[i] = (int)n->ud.ubyt[i]; }
                        break;                                      
                    case USHORT:    /* INT should be greater than USHORT unless same typesize */
                        m.um.missintg = (int)n->um.missushrt;
                        for(i=0;i<m.tlen;++i){ m.ud.intg[i] = (int)n->ud.ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_INT) ){
                            m.um.missintg = (int)n->um.missuint;               
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.intg[i] = (int)n->ud.uint[i]; }
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_INT) && (n->um.missint64 <= MAX_INT) ){
                            m.um.missintg = (int)n->um.missint64;                  
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.intg[i] = (int)n->ud.int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_INT) ){
                            m.um.missintg = (int)n->um.missuint64;         
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.intg[i] = (int)n->ud.uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case FLOAT:                                         
                m.ud.flt = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        m.um.missflt = (float)n->um.missbyt;
                        for(i=0;i<m.tlen;++i){ m.ud.flt[i] = (float)n->ud.byt[i]; }
                        break;
                    case CHAR:
                        m.um.missflt = (float)n->um.misschr;
                        for(i=0;i<m.tlen;++i){ m.ud.flt[i] = (float)n->ud.chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        m.um.missflt = (float)n->um.missshrt;
                        for(i=0;i<m.tlen;++i){ m.ud.flt[i] = (float)n->ud.shrt[i]; }
                        break;                                      
                    case INT:                                           
                        m.um.missflt = (float)n->um.missintg;
                        for(i=0;i<m.tlen;++i){ m.ud.flt[i] = (float)n->ud.intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_FLOAT) && (n->um.missdbl <= MAX_FLOAT) ){
                            m.um.missflt = (float)n->um.missdbl;                       
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.flt[i] = (float)n->ud.dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        m.um.missflt = (float)n->um.missubyt;
                        for(i=0;i<m.tlen;++i){ m.ud.flt[i] = (float)n->ud.ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        m.um.missflt = (float)n->um.missushrt;
                        for(i=0;i<m.tlen;++i){ m.ud.flt[i] = (float)n->ud.ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        m.um.missflt = (float)n->um.missuint;
                        for(i=0;i<m.tlen;++i){ m.ud.flt[i] = (float)n->ud.uint[i]; }
                        break;                                      
                    case INT64:                                         
                        m.um.missflt = (float)n->um.missint64;
                        for(i=0;i<m.tlen;++i){ m.ud.flt[i] = (float)n->ud.int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        m.um.missflt = (float)n->um.missuint64;
                        for(i=0;i<m.tlen;++i){ m.ud.flt[i] = (float)n->ud.uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case DOUBLE:                                        
                m.ud.dbl = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        m.um.missdbl = (double)n->um.missbyt;
                        for(i=0;i<m.tlen;++i){ m.ud.dbl[i] = (double)n->ud.byt[i]; }
                        break;
                    case CHAR:
                        m.um.missdbl = (double)n->um.misschr;
                        for(i=0;i<m.tlen;++i){ m.ud.dbl[i] = (double)n->ud.chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        m.um.missdbl = (double)n->um.missshrt;
                        for(i=0;i<m.tlen;++i){ m.ud.dbl[i] = (double)n->ud.shrt[i]; }
                        break;                                      
                    case INT:                                           
                        m.um.missdbl = (double)n->um.missintg;
                        for(i=0;i<m.tlen;++i){ m.ud.dbl[i] = (double)n->ud.intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        m.um.missdbl = (double)n->um.missflt;
                        for(i=0;i<m.tlen;++i){ m.ud.dbl[i] = (double)n->ud.flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case UBYTE:                                         
                        m.um.missdbl = (double)n->um.missubyt;
                        for(i=0;i<m.tlen;++i){ m.ud.dbl[i] = (double)n->ud.ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        m.um.missdbl = (double)n->um.missushrt;
                        for(i=0;i<m.tlen;++i){ m.ud.dbl[i] = (double)n->ud.ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        m.um.missdbl = (double)n->um.missuint;
                        for(i=0;i<m.tlen;++i){ m.ud.dbl[i] = (double)n->ud.uint[i]; }
                        break;                                      
                    case INT64:                                         
                        m.um.missdbl = (double)n->um.missint64;
                        for(i=0;i<m.tlen;++i){ m.ud.dbl[i] = (double)n->ud.int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        m.um.missdbl = (double)n->um.missuint64;
                        for(i=0;i<m.tlen;++i){ m.ud.dbl[i] = (double)n->ud.uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case UBYTE:                                         
                m.ud.ubyt = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        if ( (n->um.missbyt >= MIN_UBYTE) ){
                            m.um.missubyt = (unsigned char)n->um.missbyt;
                        }
                        for(i=0;i<m.tlen;++i){ m.ud.ubyt[i] = (unsigned char)n->ud.byt[i]; }
                        break;
                    case CHAR:  /* treating CHAR and UBYTE as equal */
                        m.um.missubyt = (unsigned char)n->um.misschr;
                        for(i=0;i<m.tlen;++i){ m.ud.ubyt[i] = (unsigned char)n->ud.chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_UBYTE) && (n->um.missshrt <= MAX_UBYTE) ){
                            m.um.missubyt = (unsigned char)n->um.missshrt;                     
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.ubyt[i] = (unsigned char)n->ud.shrt[i]; }
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_UBYTE) && (n->um.missintg <= MAX_UBYTE) ){
                            m.um.missubyt = (unsigned char)n->um.missintg;                 
                        }                                       
                        for(i=0;i<m.tlen;++i){ m.ud.ubyt[i] = (unsigned char)n->ud.intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_UBYTE) && (n->um.missflt <= MAX_UBYTE) ){
                            m.um.missubyt = (unsigned char)n->um.missflt;                      
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.ubyt[i] = (unsigned char)n->ud.flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_UBYTE) && (n->um.missdbl <= MAX_UBYTE) ){
                            m.um.missubyt = (unsigned char)n->um.missdbl;                      
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.ubyt[i] = (unsigned char)n->ud.dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case USHORT:                                        
                        if ( (n->um.missushrt <= MAX_UBYTE) ){
                            m.um.missubyt = (unsigned char)n->um.missushrt;                
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.ubyt[i] = (unsigned char)n->ud.ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_UBYTE) ){
                            m.um.missubyt = (unsigned char)n->um.missuint;             
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.ubyt[i] = (unsigned char)n->ud.uint[i]; }
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_UBYTE) && (n->um.missint64 <= MAX_UBYTE) ){
                            m.um.missubyt = (unsigned char)n->um.missint64;                    
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.ubyt[i] = (unsigned char)n->ud.int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_UBYTE) ){
                            m.um.missubyt = (unsigned char)n->um.missuint64;           
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.ubyt[i] = (unsigned char)n->ud.uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case USHORT:                                        
                m.ud.ushrt = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        if ( (n->um.missbyt >= MIN_USHORT) ){
                            m.um.missushrt = (unsigned short)n->um.missbyt;
                        }
                        for(i=0;i<m.tlen;++i){ m.ud.ushrt[i] = (unsigned short)n->ud.byt[i]; }
                        break;
                    case CHAR:
                        m.um.missushrt = (unsigned short)n->um.misschr;
                        for(i=0;i<m.tlen;++i){ m.ud.ushrt[i] = (unsigned short)n->ud.chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_USHORT) ){
                            m.um.missushrt = (unsigned short)n->um.missshrt;                       
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.ushrt[i] = (unsigned short)n->ud.shrt[i]; }
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_USHORT) && (n->um.missintg <= MAX_USHORT) ){
                            m.um.missushrt = (unsigned short)n->um.missintg;                   
                        }                                       
                        for(i=0;i<m.tlen;++i){ m.ud.ushrt[i] = (unsigned short)n->ud.intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_USHORT) && (n->um.missflt <= MAX_USHORT) ){
                            m.um.missushrt = (unsigned short)n->um.missflt;                        
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.ushrt[i] = (unsigned short)n->ud.flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_USHORT) && (n->um.missdbl <= MAX_USHORT) ){
                            m.um.missushrt = (unsigned short)n->um.missdbl;                        
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.ushrt[i] = (unsigned short)n->ud.dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        m.um.missushrt = (unsigned short)n->um.missubyt;
                        for(i=0;i<m.tlen;++i){ m.ud.ushrt[i] = (unsigned short)n->ud.ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case UINT:                                          
                        if ( (n->um.missuint <= MAX_USHORT) ){
                            m.um.missushrt = (unsigned short)n->um.missuint;               
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.ushrt[i] = (unsigned short)n->ud.uint[i]; }
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_USHORT) && (n->um.missint64 <= MAX_USHORT) ){
                            m.um.missushrt = (unsigned short)n->um.missint64;                  
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.ushrt[i] = (unsigned short)n->ud.int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_USHORT) ){
                            m.um.missushrt = (unsigned short)n->um.missuint64;         
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.ushrt[i] = (unsigned short)n->ud.uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case UINT:                                          
                m.ud.uint = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        if ( (n->um.missbyt >= MIN_UINT) ){
                            m.um.missuint = (unsigned int)n->um.missbyt;
                        }
                        for(i=0;i<m.tlen;++i){ m.ud.uint[i] = (unsigned int)n->ud.byt[i]; }
                        break;
                    case CHAR:
                        m.um.missuint = (unsigned int)n->um.misschr;
                        for(i=0;i<m.tlen;++i){ m.ud.uint[i] = (unsigned int)n->ud.chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_UINT) ){
                            m.um.missuint = (unsigned int)n->um.missshrt;                      
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.uint[i] = (unsigned int)n->ud.shrt[i]; }
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_UINT) ){
                            m.um.missuint = (unsigned int)n->um.missintg;                  
                        }                                       
                        for(i=0;i<m.tlen;++i){ m.ud.uint[i] = (unsigned int)n->ud.intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_UINT) && (n->um.missflt <= MAX_UINT) ){
                            m.um.missuint = (unsigned int)n->um.missflt;                       
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.uint[i] = (unsigned int)n->ud.flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_UINT) && (n->um.missdbl <= MAX_UINT) ){
                            m.um.missuint = (unsigned int)n->um.missdbl;                       
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.uint[i] = (unsigned int)n->ud.dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        m.um.missuint = (unsigned int)n->um.missubyt;
                        for(i=0;i<m.tlen;++i){ m.ud.uint[i] = (unsigned int)n->ud.ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        m.um.missuint = (unsigned int)n->um.missushrt;
                        for(i=0;i<m.tlen;++i){ m.ud.uint[i] = (unsigned int)n->ud.ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_UINT) && (n->um.missint64 <= MAX_UINT) ){
                            m.um.missuint = (unsigned int)n->um.missint64;                 
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.uint[i] = (unsigned int)n->ud.int64[i]; }
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_UINT) ){
                            m.um.missuint = (unsigned int)n->um.missuint64;            
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.uint[i] = (unsigned int)n->ud.uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case INT64:                                         
                m.ud.int64 = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        m.um.missint64 = (long long)n->um.missbyt;
                        for(i=0;i<m.tlen;++i){ m.ud.int64[i] = (long long)n->ud.byt[i]; }
                        break;
                    case CHAR:
                        m.um.missint64 = (long long)n->um.misschr;
                        for(i=0;i<m.tlen;++i){ m.ud.int64[i] = (long long)n->ud.chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        m.um.missint64 = (long long)n->um.missshrt;
                        for(i=0;i<m.tlen;++i){ m.ud.int64[i] = (long long)n->ud.shrt[i]; }
                        break;                                      
                    case INT:                                           
                        m.um.missint64 = (long long)n->um.missintg;
                        for(i=0;i<m.tlen;++i){ m.ud.int64[i] = (long long)n->ud.intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_INT64) && (n->um.missflt <= MAX_INT64) ){
                            m.um.missint64 = (long long)n->um.missflt;                     
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.int64[i] = (long long)n->ud.flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_INT64) && (n->um.missdbl <= MAX_INT64) ){
                            m.um.missint64 = (long long)n->um.missdbl;                     
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.int64[i] = (long long)n->ud.dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        m.um.missint64 = (long long)n->um.missubyt;
                        for(i=0;i<m.tlen;++i){ m.ud.int64[i] = (long long)n->ud.ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        m.um.missint64 = (long long)n->um.missushrt;
                        for(i=0;i<m.tlen;++i){ m.ud.int64[i] = (long long)n->ud.ushrt[i]; }
                        break;                                      
                    case UINT:  /* hopefully UINT is smaller than INT64, could check typsize */
                        m.um.missint64 = (long long)n->um.missuint;
                        for(i=0;i<m.tlen;++i){ m.ud.int64[i] = (long long)n->ud.uint[i]; }
                        break;                                      
                    case INT64:                                         
                        fprintf(stderr,"Error in castAr: equal types shouldn't reach this point! m.typ=%d n->typ=%d\n",m.typ,n->typ);
                        break;                                      
                    case UINT64:                                        
                        if ( (n->um.missuint64 <= MAX_INT64) ){
                            m.um.missint64 = (long long)n->um.missuint64;          
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.int64[i] = (long long)n->ud.uint64[i]; }
                        break;
                    default:
                        fprintf(stderr,"Error in castAr: undefined type! n->typ=%d\n",n->typ);
                        print_arr_exit(n);
                        break;
                }
                break;                                      
            case UINT64:                                        
                m.ud.uint64 = malloc(m.tlen*m.typsize);
                switch (n->typ) {
                    case BYTE:
                        if ( (n->um.missbyt >= MIN_UINT64) ){
                            m.um.missuint64 = (unsigned long long)n->um.missbyt;
                        }
                        for(i=0;i<m.tlen;++i){ m.ud.uint64[i] = (unsigned long long)n->ud.byt[i]; }
                        break;
                    case CHAR:
                        m.um.missuint64 = (unsigned long long)n->um.misschr;
                        for(i=0;i<m.tlen;++i){ m.ud.uint64[i] = (unsigned long long)n->ud.chr[i]; }
                        break;                                      
                    case SHORT:                                         
                        if ( (n->um.missshrt >= MIN_UINT64) ){
                            m.um.missuint64 = (unsigned long long)n->um.missshrt;                      
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.uint64[i] = (unsigned long long)n->ud.shrt[i]; }
                        break;                                      
                    case INT:                                           
                        if ( (n->um.missintg >= MIN_UINT64) ){
                            m.um.missuint64 = (unsigned long long)n->um.missintg;                  
                        }                                       
                        for(i=0;i<m.tlen;++i){ m.ud.uint64[i] = (unsigned long long)n->ud.intg[i]; }
                        break;                                      
                    case FLOAT:                                         
                        if ( (n->um.missflt >= MIN_UINT64) && (n->um.missflt <= MAX_UINT64) ){
                            m.um.missuint64 = (unsigned long long)n->um.missflt;                       
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.uint64[i] = (unsigned long long)n->ud.flt[i]; }
                        break;                                      
                    case DOUBLE:                                        
                        if ( (n->um.missdbl >= MIN_UINT64) && (n->um.missdbl <= MAX_UINT64) ){
                            m.um.missuint64 = (unsigned long long)n->um.missdbl;                       
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.uint64[i] = (unsigned long long)n->ud.dbl[i]; }
                        break;                                      
                    case UBYTE:                                         
                        m.um.missuint64 = (unsigned long long)n->um.missubyt;
                        for(i=0;i<m.tlen;++i){ m.ud.uint64[i] = (unsigned long long)n->ud.ubyt[i]; }
                        break;                                      
                    case USHORT:                                        
                        m.um.missuint64 = (unsigned long long)n->um.missushrt;
                        for(i=0;i<m.tlen;++i){ m.ud.uint64[i] = (unsigned long long)n->ud.ushrt[i]; }
                        break;                                      
                    case UINT:                                          
                        m.um.missuint64 = (unsigned long long)n->um.missuint;
                        for(i=0;i<m.tlen;++i){ m.ud.uint64[i] = (unsigned long long)n->ud.uint[i]; }
                        break;                                      
                    case INT64:                                         
                        if ( (n->um.missint64 >= MIN_UINT64) ){
                            m.um.missuint64 = (unsigned long long)n->um.missint64;                 
                        }                                           
                        for(i=0;i<m.tlen;++i){ m.ud.uint64[i] = (unsigned long long)n->ud.int64[i]; }
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
