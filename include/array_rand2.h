#ifndef  _ARRAY_RAND_H_
#define  _ARRAY_RAND_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <math_supp.h>
#include <arrayinit2.h>
#include <arrayops2.h>

arr randomIntArray(typ_idx count, typ_idx max){
	typ_idx i;
	arr m = Array(1,TYPIDX,count);
    int *intg = pntr_of(&m);
	for(i=0;i<count;++i){ intg[i] = rand()%max; }

	return m;
}

arr randomArray(typ_idx count, typ_idx max){
	typ_idx i;
	arr m = Array(1,DOUBLE,count);
    double *dbl = pntr_of(&m);
	for(i=0;i<count;++i){ dbl[i] = (double)(rand()%max)/max; }

	return m;
}

arr randomArrayNoRepl(typ_idx count, typ_idx max){
	typ_idx i,j;
	arr m = Array(1,TYPIDX,count);
    typ_idx *idx = pntr_of(&m);
	for(i=0;i<count;++i){ 
		idx[i] = rand()%max;
		for(j=0;j<i;++j){
			if (idx[i] == idx[j]){ i--; break; }
		}
	}

	return m;
}

arr randomArrayNoRepl_Test(typ_idx count, typ_idx max){
	typ_idx i,j,tidx;
	arr m = Array(1,TYPIDX,count);
    typ_idx *idx = pntr_of(&m);
    int     *set = calloc(count,sizeof *set);
	for(i=0;i<count;++i){
        while(!set[tidx=rand()%max]){
            idx[i] = tidx;
            set[tidx] = 1;
        }
	}

	return m;
}

arr createRandomSamples(typ_idx nsamples, typ_idx nx){
	typ_idx i;

	typ_idx count = (typ_idx)nx;
	typ_idx       max = nx;

	arr randmatrix = Array(2,TYPIDX,nsamples,count);
	arr randarr;
	typ_idx *aidx = malloc(sizeof(typ_idx));
	typ_idx *adim = malloc(sizeof(typ_idx));
	adim[0] = 0;
	for(i=0;i<nsamples;++i){
		randarr = randomArrayNoRepl(count,max);
		aidx[0] = i;
		assignPart(&randmatrix, &randarr, adim, aidx);
		freeAr(&randarr);
	}
	
	free(aidx);
	free(adim);
	return randmatrix;
}

#endif
