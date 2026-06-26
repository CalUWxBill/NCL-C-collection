/* Created by Bill Scheftic */
/*------------------------------------------*/
/* Header for typedefs of function pointers */
/*------------------------------------------*/

#ifndef  _ARR_F_TYPES_H_
#define  _ARR_F_TYPES_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>

typedef void               (*fctNoRet)();
typedef void *             (*fctRgen)();
typedef signed char        (*fctRbyt)();
typedef char               (*fctRchr)();
typedef short              (*fctRsht)();
typedef int                (*fctRint)();
typedef float              (*fctRflt)();
typedef double             (*fctRdbl)();
typedef unsigned char      (*fctRubyt)();
typedef unsigned short     (*fctRusht)();
typedef unsigned int       (*fctRuint)();
typedef long long          (*fctRlint)();
typedef unsigned long long (*fctRulint)();
typedef arr                (*fctRarr)();
typedef arr *              (*fctRarrp)();

#endif
