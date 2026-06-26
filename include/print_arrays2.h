/* Created by Bill Scheftic */
/*-------------------------*/
/* Header for Print Arrays */
/*-------------------------*/
/*
 *  Things to add:
 *  --------------
 *  + print both information and values of arrays
 *  + print section of an array
 */
#ifndef  _PRINT_ARR2_H_
#define  _PRINT_ARR2_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <arrayinit2.h>

/*------------------------*/
/* Function Declarations  */
/*------------------------*/
void printArrayAllWHdr(FILE *, arr *, char *,...);
void printArrayInfoWHdr(FILE *, arr *, char *,...);
void printArrayWHdr(FILE *, arr *, char *,...);
void printArrayInfo(FILE *,arr *);
void printArray(FILE *,arr *);
void printArrayLoop(FILE *,arr *, int, typ_idx *);

void printArrayFmtAllWHdr(FILE *, arr *, char *, char *,...);
void printArrayFmtWHdr(FILE *, arr *, char *, char *,...);
void printArrayFmt(FILE *, arr *, char *);
void printArrayFmtLoop(FILE *,arr *, char *, int, typ_idx *);

/* These ones just omit the trailing newlines */
void printArrayFmt2AllWHdr(FILE *, arr *, char *, char *,...);
void printArrayFmt2WHdr(FILE *, arr *, char *, char *,...);
void printArrayFmt2(FILE *, arr *, char *);
void printArrayFmt2Loop(FILE *,arr *, char *, int, typ_idx *);


void printMultiArrayFmtHdr (FILE *,int,char *,...);
void printMultiArrayFmt(FILE *,int,char *,...);
void printMultiArrayFmtList(FILE *,int,char *,arr **);
void printMultiArrayFmtLoop(FILE *,int,arr **, char *, int, typ_idx *);

void printMultiArrayFmts    (FILE *fout,int,...);
void printMultiArrayFmtsHdr (FILE *fout,int,...);
void printMultiArrayFmtsList(FILE *fout,int,char **,arr **);
void printMultiArrayFmtsLoop(FILE *fout,int,arr **, char **, int, typ_idx *);

void printMultiArraySectFmt(FILE *,typ_idx *,typ_idx *,int,char *,...);
void printMultiArraySectFmtHdr(FILE *,typ_idx *,typ_idx *,int,char *,...);
void printMultiArraySectFmtList(FILE *,typ_idx *,typ_idx *,int,char *,arr **);
void printMultiArraySectFmtLoop(FILE *,int,arr **, char *, typ_idx *, typ_idx *, int, typ_idx *);

/*-----------*/
/* Functions */
/*-----------*/
void printArrayAllWHdr(FILE *fout, arr *restrict m, char *hdr,...) {
	va_list args;
	va_start(args, hdr);

	vfprintf(fout, hdr, args);

	va_end(args);

	printArrayInfo(fout, m);
	printArray(fout, m);
	return;
}

void printArrayInfoWHdr(FILE *fout, arr *restrict m, char *hdr, ...) {
	va_list args;
	va_start(args, hdr);

	vfprintf(fout, hdr, args);

	va_end(args);

	printArrayInfo(fout, m);
	return;
}

void printArrayWHdr(FILE *fout, arr *restrict m, char *hdr, ...) {
	va_list args;
	va_start(args, hdr);

	vfprintf(fout, hdr, args);

	va_end(args);

	printArray(fout, m);
	return;
}

void printArrayInfo(FILE *fout,arr *restrict m){
	int i;
/*
	fprintf(fout,"Array Type: %d %s\n",m->typ,ARR_TYPE_LBLS[m->typ]);
	fprintf(fout,"Array # of Dims: %lld\n",m->n);
	fprintf(fout,"Array Size of Dims:");
	for(i=0;i<m->n;i++){
		fprintf(fout," %lld",m->len[i]);
	}
    fprintf(fout,"\n");
*/
    if (isArNull(m)){
        fprintf(fout,"Null\n");
        return;
    }
	fprintf(fout,"%s",ARR_TYPE_LBLS[m->typ]);
	if (m->n == 0){
        fprintf(fout," - scalar\t - ");
    } else {
        fprintf(fout,"[%lld",m->len[0]);
        for(i=1;i<m->n;i++){
            fprintf(fout,",%lld",m->len[i]);
        }
        fprintf(fout,"]\t - ");
    }

	switch (m->typ) {
	#define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)	\
		fprintf(fout,"missing value: "fmt1"\n",*(swcast *)getMiss(m));
		ALLTYPECASES
		default:
			fprintf(stderr,"printArrayInfo: undefined type %d!\n", m->typ);
			break;
	}
	#undef SWITCHCAST

	return;
}

void printArray(FILE *fout,arr *restrict m){
	if (m->tlen == 0){ fputs("No values in array!\n",stderr); return; }
	typ_idx *c = init0(m->n,TYPIDX);
	printArrayLoop(fout,m,0,c);
    fprintf(fout,"\n");
	free(c);
	return;
}

void printArrayLoop(FILE *fout,arr *restrict m, int dim, typ_idx *c){
/*	This is a recursive function	*/
	if (dim == m->n){
		switch (m->typ) {
		#define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)	\
			fprintf(fout,fmt1" ",cswassign(m,c));
			ALLTYPECASES
			default:
				fprintf(stderr,"undefined type!\n");
				exit(0);
				break;
		}
		#undef SWITCHCAST
		return;
	} else {
		for(c[dim]=0;c[dim]<m->len[dim];c[dim]++){
			printArrayLoop(fout,m,dim+1,c);
		}
		fprintf(fout,"\n");
	}
	return;
}


void printArrayFmtAllWHdr(FILE *fout, arr *restrict m, char *fmt, char *hdr,...) {
	va_list args;
	va_start(args, hdr);

	vfprintf(fout, hdr, args);

	va_end(args);

	printArrayInfo(fout, m);
	printArrayFmt(fout, m, fmt);
	return;
}

void printArrayFmtWHdr(FILE *fout, arr *restrict m, char *fmt, char *hdr, ...) {
	va_list args;
	va_start(args, hdr);

	vfprintf(fout, hdr, args);

	va_end(args);

	printArrayFmt(fout, m, fmt);
	return;
}

void printArrayFmt(FILE *fout,arr *restrict m, char *fmt){
	if (m->tlen == 0){ fputs("No values in array!\n",stderr); return; }
	typ_idx *c = init0(m->n,TYPIDX);
	printArrayFmtLoop(fout, m, fmt, 0, c);
    fprintf(fout,"\n");
	free(c);
	return;
}

void printArrayFmtLoop(FILE *fout,arr *restrict m, char *fmt, int dim, typ_idx *c){
/*	This is a recursive function	*/
	if (dim == m->n){
		switch (m->typ) {
		#define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)	\
			fprintf(fout,fmt,cswassign(m,c));  \
			fprintf(fout," ");
			ALLTYPECASES
			default:
				fprintf(stderr,"undefined type!\n");
				exit(0);
				break;
		}
		#undef SWITCHCAST
		return;
	} else {
		for(c[dim]=0;c[dim]<m->len[dim];c[dim]++){
			printArrayFmtLoop(fout,m,fmt,dim+1,c);
		}
		fprintf(fout,"\n");
	}
	return;
}






void printArrayFmt2AllWHdr(FILE *fout, arr *restrict m, char *fmt, char *hdr,...) {
	va_list args;
	va_start(args, hdr);

	vfprintf(fout, hdr, args);

	va_end(args);

	printArrayInfo(fout, m);
	printArrayFmt2(fout, m, fmt);
	return;
}

void printArrayFmt2WHdr(FILE *fout, arr *restrict m, char *fmt, char *hdr, ...) {
	va_list args;
	va_start(args, hdr);

	vfprintf(fout, hdr, args);

	va_end(args);

	printArrayFmt2(fout, m, fmt);
	return;
}

void printArrayFmt2(FILE *fout,arr *restrict m, char *fmt){
	if (m->tlen == 0){ fputs("No values in array!\n",stderr); return; }
	typ_idx *c = init0(m->n,TYPIDX);
	printArrayFmt2Loop(fout, m, fmt, 0, c);
    fprintf(fout,"\n");
	free(c);
	return;
}

void printArrayFmt2Loop(FILE *fout,arr *restrict m, char *fmt, int dim, typ_idx *c){
/*	This is a recursive function	*/
	if (dim == m->n){
		switch (m->typ) {
		#define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)	\
			fprintf(fout,fmt,cswassign(m,c));  \
			fprintf(fout," ");
			ALLTYPECASES
			default:
				fprintf(stderr,"undefined type!\n");
				exit(0);
				break;
		}
		#undef SWITCHCAST
		return;
	} else {
		for(c[dim]=0;c[dim]<m->len[dim];c[dim]++){
			printArrayFmt2Loop(fout,m,fmt,dim+1,c);
		}
        typ_idx j=0;
        /*
        fprintf(fout,"[%lld",c[j]);
        for(j=1;j<m->n;j++){
            fprintf(fout,",%lld",c[j]);
        }
        fprintf(fout,"]\n");
        j=0; */
        for(;j<m->n;++j){
            if (c[j] < m->len[j]-1){ break;}
        }
        if (j < m->n){
            fprintf(fout,"\n");
        }
	}
	return;
}




void printMultiArrayFmt(FILE *fout,int narrs,char *fmt,...){
    int i;
    arr **m = malloc(narrs*sizeof(arr *));
	va_list arg_list;
	va_start(arg_list, fmt);
	for (i=0;i<narrs;i++){
		m[i]  = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

	printMultiArrayFmtList(fout,narrs,fmt,m);
    free(m);
	return;
}

void printMultiArrayFmtHdr(FILE *fout,int narrs,char *fmt,...){
    int i;
    char **hdrs = malloc(narrs*sizeof(char *));
    arr  **m    = malloc(narrs*sizeof(arr *));
	va_list arg_list;
	va_start(arg_list, fmt);
	for (i=0;i<narrs;i++){
		hdrs[i] = va_arg(arg_list, char *);
	}
	for (i=0;i<narrs;i++){
		m[i]    = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

    int j = 0;
    if (m[0]->n > 0){
        fprintf(fout,"[%lld",m[0]->len[j]);
        for(j=1;j<m[0]->n;j++){
            fprintf(fout,",%lld",m[0]->len[j]);
        }
        fprintf(fout,"] =");
    }
    for(j=0;j<narrs;j++){
        fprintf(fout," %s",hdrs[j]);
    }
    fprintf(fout,"\n");
    free(hdrs);
	printMultiArrayFmtList(fout,narrs,fmt,m);
    free(m);
	return;
}

void printMultiArrayFmtList(FILE *fout,int narrs,char *fmt,arr **m){
	if (m[0]->tlen == 0){ fputs("No values in array!\n",stderr); return; }
	typ_idx *c = init0(m[0]->n,TYPIDX);
	printMultiArrayFmtLoop(fout, narrs, m, fmt,0,c);
    fprintf(fout,"\n");
	free(c);
	return;
}

void printMultiArrayFmtLoop(FILE *fout,int narrs,arr **m, char *fmt, int dim, typ_idx *c){
/*	This is a recursive function	*/
	if (dim == m[0]->n){
        int j = 0;
        if (dim > 0){
            fprintf(fout,"[%lld",c[j]);
            for(j=1;j<dim;j++){
                fprintf(fout,",%lld",c[j]);
            }
            fprintf(fout,"] =");
        }
		switch (m[0]->typ) {
		#define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)	\
            for(j=0;j<narrs;j++){ \
                fprintf(fout," ");  \
                fprintf(fout,fmt,cswassign(m[j],c)); \
            }
			ALLTYPECASES
			default:
				fprintf(fout,"undefined type!\n");
				exit(0);
				break;
		}
		#undef SWITCHCAST
        fprintf(fout,"\n");
		return;
	} else {
		for(c[dim]=0;c[dim]<m[0]->len[dim];c[dim]++){
			printMultiArrayFmtLoop(fout,narrs,m,fmt,dim+1,c);
		}
	}
	return;
}







void printMultiArrayFmts(FILE *fout,int narrs,...){
    int i;
    char **fmts = malloc(narrs*sizeof(char *));
    arr **m = malloc(narrs*sizeof(arr *));
	va_list arg_list;
	va_start(arg_list, narrs);
	for (i=0;i<narrs;i++){
		fmts[i] = va_arg(arg_list, char *);
	}
	for (i=0;i<narrs;i++){
		m[i]  = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

	printMultiArrayFmtsList(fout,narrs,fmts,m);
    free(m);
	return;
}

void printMultiArrayFmtsHdr(FILE *fout,int narrs,...){
    int i;
    char **fmts = malloc(narrs*sizeof(char *));
    char **hdrs = malloc(narrs*sizeof(char *));
    arr  **m    = malloc(narrs*sizeof(arr *));
	va_list arg_list;
	va_start(arg_list, narrs);
	for (i=0;i<narrs;i++){
		fmts[i] = va_arg(arg_list, char *);
	}
	for (i=0;i<narrs;i++){
		hdrs[i] = va_arg(arg_list, char *);
	}
	for (i=0;i<narrs;i++){
		m[i]    = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

    int j = 0;
    if (m[0]->n > 0){
        fprintf(fout,"[%lld",m[0]->len[j]);
        for(j=1;j<m[0]->n;j++){
            fprintf(fout,",%lld",m[0]->len[j]);
        }
        fprintf(fout,"] =");
    }
    for(j=0;j<narrs;j++){
        fprintf(fout," %s",hdrs[j]);
    }
    fprintf(fout,"\n");
    free(hdrs);
	printMultiArrayFmtsList(fout,narrs,fmts,m);
    free(fmts);
    free(m);
	return;
}

void printMultiArrayFmtsList(FILE *fout,int narrs,char **fmts,arr **m){
	if (m[0]->tlen == 0){ fputs("No values in array!\n",stderr); return; }
	typ_idx *c = init0(m[0]->n,TYPIDX);
	printMultiArrayFmtsLoop(fout, narrs, m, fmts,0,c);
    fprintf(fout,"\n");
	free(c);
	return;
}

void printMultiArrayFmtsLoop(FILE *fout,int narrs,arr **m, char **fmts, int dim, typ_idx *c){
/*	This is a recursive function	*/
	if (dim == m[0]->n){
        int j = 0;
        if (dim > 0){
            fprintf(fout,"[%lld",c[j]);
            for(j=1;j<dim;j++){
                fprintf(fout,",%lld",c[j]);
            }
            fprintf(fout,"] =");
        }
        for(j=0;j<narrs;j++){
            switch (m[j]->typ) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)	\
                    fprintf(fout," ");  \
                    fprintf(fout,fmts[j],cswassign(m[j],c));
                ALLTYPECASES
                default:
                    fprintf(fout,"undefined type!\n");
                    exit(0);
                    break;
            }
            #undef SWITCHCAST
        }
        fprintf(fout,"\n");
		return;
	} else {
		for(c[dim]=0;c[dim]<m[0]->len[dim];c[dim]++){
			printMultiArrayFmtsLoop(fout,narrs,m,fmts,dim+1,c);
		}
	}
	return;
}







void printMultiArraySectFmt(FILE *fout,typ_idx *lo,typ_idx *hi,int narrs,char *fmt,...){
    int i;
    arr **m = malloc(narrs*sizeof(arr));
	va_list arg_list;
	va_start(arg_list, fmt);
	for (i=0;i<narrs;i++){
		m[i]  = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

	printMultiArraySectFmtList(fout,lo,hi,narrs,fmt,m);
    free(m);
	return;
}

void printMultiArraySectFmtHdr(FILE *fout,typ_idx *lo,typ_idx *hi,int narrs,char *fmt,...){
    int i;
    char **hdrs = malloc(narrs*sizeof(char *));
    arr  **m    = malloc(narrs*sizeof(arr *));
	va_list arg_list;
	va_start(arg_list, fmt);
	for (i=0;i<narrs;i++){
		hdrs[i] = va_arg(arg_list, char *);
	}
	for (i=0;i<narrs;i++){
		m[i]    = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

    int j = 0;
    if (m[0]->n > 0){
        if (lo[j]==hi[j]){
            fprintf(fout,"[%lld",lo[j]);
        } else {
            fprintf(fout,"[%lld:%lld",lo[j],hi[j]);
        }
        for(j=1;j<m[0]->n;j++){
            if (lo[j]==hi[j]){
                fprintf(fout,",%lld",lo[j]);
            } else {
                fprintf(fout,",%lld:%lld",lo[j],hi[j]);
            }
        }
        fprintf(fout,"] =");
    }
    for(j=0;j<narrs;j++){
        fprintf(fout," %s",hdrs[j]);
    }
    fprintf(fout,"\n");
    free(hdrs);
	printMultiArraySectFmtList(fout,lo,hi,narrs,fmt,m);
    free(m);
	return;
}

void printMultiArraySectFmtList(FILE *fout,typ_idx *lo,typ_idx *hi,int narrs,char *fmt,arr **m){
	if (m[0]->tlen == 0){ fputs("No values in array!\n",stderr); return; }
	typ_idx *c = init0(m[0]->n,TYPIDX);
	printMultiArraySectFmtLoop(fout,narrs,m,fmt,lo,hi,0,c);
    fprintf(fout,"\n");
	free(c);
	return;
}

void printMultiArraySectFmtLoop(FILE *fout,int narrs,arr **m, char *fmt, typ_idx *lo, typ_idx *hi, int dim, typ_idx *c){
/*	This is a recursive function	*/
	if (dim == m[0]->n){
        int j = 0;
        if (dim > 0){
            fprintf(fout,"[%lld",c[j]);
            for(j=1;j<dim;j++){
                fprintf(fout,",%lld",c[j]);
            }
            fprintf(fout,"] =");
        }
		switch (m[0]->typ) {
		#define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)	\
            for(j=0;j<narrs;j++){ \
                fprintf(fout," ");  \
                fprintf(fout,fmt,cswassign(m[j],c)); \
            }
			ALLTYPECASES
			default:
				fprintf(fout,"undefined type!\n");
				exit(0);
				break;
		}
		#undef SWITCHCAST
        fprintf(fout,"\n");
		return;
	} else {
        for(c[dim]=lo[dim];c[dim]<=hi[dim];c[dim]++){
			printMultiArraySectFmtLoop(fout,narrs,m,fmt,lo,hi,dim+1,c);
		}
	}
	return;
}

#endif
