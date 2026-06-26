#ifndef  _ARRAY_IO2_H_
#define  _ARRAY_IO2_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
/* */ #include <other.h> 

#define READ_LINE_LENGTH 128
/*
 *  Things to add:
 *  --------------
 */

/*
*/
arr readAr1dFromText(FILE *infile, char intyp){
	typ_idx i;

	arr m;
	char line[READ_LINE_LENGTH];
	typ_idx size = findNumLines(infile,READ_LINE_LENGTH);

	m = Array(1,intyp,size);

	switch (m.typ) {
	#define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)				\
    { \
        swcast *p = pntr_of(&m); \
		for(i=0;i<m.tlen;i++){   \
			fgets(line,READ_LINE_LENGTH,infile); \
			sscanf (line, fmt2, p++); \
		} \
    }
		ALLTYPECASES
		default:
			fprintf(stderr,"Error in readAr1dFromText: undefined type!\n");
			exit(0);
			break;
	}
	#undef SWITCHCAST

	return m;
}

arr getArNdFromText(char *fpin){ /* doubles only */
	FILE *fin;
	fin = fopen(fpin,"r");
	if(!fin) {
		fprintf(stderr,"getArNdFromText: Unable to open file %s for read!\n", fpin);
		exit(EXIT_FAILURE);
	}	else { fprintf(stderr,"getArNdFromText: file %s is opened for read.\n", fpin); }

	int c;

	typ_idx i,j,k;
	typ_idx max_len  = 10000;
	typ_idx max_dims = 10;
	double *allnums = malloc(max_len*sizeof(double));

	typ_idx *dlentot = malloc(max_dims*sizeof(typ_idx));
	for(i=0;i<max_dims;i++){ dlentot[i] = 0; }

	char *curnum = malloc(20*sizeof(char));

	k = 0;
	typ_idx newline_count = 0;
	while ( (c=fgetc(fin)) != EOF ) {
	/*	fprintf(stderr,"getArNdFromText: character: %c\n",c);	*/
		if ( c != '\n' && c != '\t' && c != ' ' ){
			curnum[k] = c;
			newline_count = 0;
		/*	fprintf(stderr,"getArNdFromText: curnum[%lld]=%c\n",k,curnum[k]);	*/
			k++;
		} else {
			if (k > 0){
				// Process curnum
				curnum[k]           = '\0';
				allnums[dlentot[0]] = atof(curnum);
			/*	fprintf(stderr,"getArNdFromText: allnums[%lld]=%g\n",dlentot[0],allnums[dlentot[0]]);	*/
				k = 0;
				dlentot[0]++;
			}
			if ( c == '\n' ){
				newline_count++;
				dlentot[newline_count]++;
			/*	fprintf(stderr,"getArNdFromText: dlentot[%lld]=%lld\n",newline_count,dlentot[newline_count]);	*/
			} else {
				newline_count = 0;
			/*	fprintf(stderr,"getArNdFromText: space or tab\n");	*/
			}
		}
	}	

	typ_idx ndims = 0;
	for(i=0 ; dlentot[i]!=0 ; i++){
		if (i > 1) { dlentot[i]++; }
	/*	fprintf(stderr,"getArNdFromText: dlentot[%lld] = %lld\n",i,dlentot[i]);	*/
	}
	ndims = i;
/*	fprintf(stderr,"getArNdFromText: ndims = %lld\n",ndims);	*/
	typ_idx *dlen = malloc(ndims*sizeof(typ_idx));
	dlen[0] = dlentot[ndims-1];
/*	fprintf(stderr,"getArNdFromText: dlen[0] = %lld\n",dlen[0]);	*/
	j=1;
	for(i=ndims-2;i>=0;i--){
		dlen[j] = dlentot[i]/dlentot[i+1];
	/*	fprintf(stderr,"getArNdFromText: dlen[%lld] = %lld\n",j,dlen[j]);	*/
		j++;
	}

    allnums = realloc(allnums, dlentot[0]*sizeof(double));
    arr R = assign1dtoNdFromList(allnums, ndims, DOUBLE, dlen);
    removeOneElemDims(&R);

	free(curnum);
	free(dlentot);
	fclose(fin);
	return R;
}


arr readArFromList(FILE *infile,typ_idx ndims,int intyp,int outtyp,typ_idx *len){
	typ_idx j;
/*  typ_idx i; */

	arr m;
	m.n = ndims;
	m.typ = intyp;
	m.typsize = typeSize(intyp);

	m.len = malloc(m.n*sizeof(typ_idx));
	m.mlen = malloc(m.n*sizeof(typ_idx));
	m.tlen = 1;

	for (j=0;j<m.n;j++){
		m.len[j] = len[j];
		m.tlen *= m.len[j];
	}

	m.mlen[m.n-1] = 1;
	for (j=m.n-2;j>-1;j--){
		m.mlen[j] = m.mlen[j+1]*m.len[j+1];
	}

    /* https://www.seebs.net/c/c_tcn4e.html
       normally, you'd write this with fwrite(buf, sizeof(some_type), MAX, fp),
       since that's the entire reason fwrite() takes both a size per object and a number of objects */
	switch (m.typ) {
	#define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)				\
		m.ud.swtyp = malloc(m.tlen*m.typsize);	\
        fread(m.ud.swtyp,m.typsize,m.tlen,infile);
		ALLTYPECASES
		default:
			fprintf(stderr,"Error in readAr: undefined type %d!\n",m.typ);
			exit(0);
			break;
	}
	#undef SWITCHCAST
	
	if (intyp != outtyp){
		m = castAr(&m,outtyp,1);
	}

	return m;
}

arr readAr(FILE *infile,typ_idx ndims,int intyp,int outtyp, ...){
	typ_idx j;
	typ_idx *len = malloc(sizeof(typ_idx)*ndims);

	va_list arg_list;
	va_start(arg_list, outtyp);
	for(j=0;j<ndims;j++){
		len[j] = va_arg(arg_list, typ_idx);
	}
	va_end(arg_list);

	arr m = readArFromList(infile,ndims,intyp,outtyp,len);

	free(len);
	return m;
}

void writeAr(FILE *infile,arr *n,int typ){
/*	typ_idx i; */
	arr m;
	if (n->typ != typ){
		m = castAr(n,typ,0);
	} else {
		m = *n;
	}
	
    /* https://www.seebs.net/c/c_tcn4e.html
       normally, you'd write this with fwrite(buf, sizeof(some_type), MAX, fp),
       since that's the entire reason fwrite() takes both a size per object and a number of objects */
	switch (typ) {
	#define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)				\
		fwrite(&m.ud.swtyp,m.typsize,m.tlen,infile);
		ALLTYPECASES
		default:
			fprintf(stderr,"Error in writeAr: undefined type %d!\n",typ);
			exit(0);
			break;
	}
	#undef SWITCHCAST
	
	if (n->typ != typ){
		freeAr(&m);
	}

	return;
}


#endif
