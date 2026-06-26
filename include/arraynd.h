/* Created by Bill Scheftic */
/*--------------------------------------------------------------------*/
/* Header for Nd gridded ops of equal or higher dimensioned nd arrays */
/*--------------------------------------------------------------------*/

#ifndef  _ARR_ND_H_
#define  _ARR_ND_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <math_supp.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
/*
#define DEBUG_ARRAYND_ENTRY
*/
#ifdef DEBUG_ARRAYND_ENTRY 
#define DBG_ARND_ENTR fprintf (stderr, "%s, %s, line %d\n", __FILE__, __func__, __LINE__)
#else
#define DBG_ARND_ENTR ((void)0)
#endif

/*
#define DEBUG_ARRAYND
*/
#ifdef DEBUG_ARRAYND 
#define DBG_ARND(...) fprintf (stderr, __VA_ARGS__)
#else
#define DBG_ARND(...) ((void)0)
#endif

/* 
#define DEBUG_ARRAYND_LOOPS
 */
#ifdef DEBUG_ARRAYND_LOOPS
#define DBG_ARND_LP(...) fprintf (stderr, __VA_ARGS__)
#else
#define DBG_ARND_LP(...) ((void)0)
#endif


/* Use these for testing a couple function instead of whole header
#define DEBUG_ARRAYND_ENTRY
#define DBG_ARND_ENTR fprintf (stderr, "%s, %s, line %d\n", __FILE__, __func__, __LINE__)

#define DEBUG_ARRAYND
#define DBG_ARND(...) fprintf (stderr, __VA_ARGS__)

#define DEBUG_ARRAYND_LOOPS
#define DBG_ARND_LP(...) fprintf (stderr, __VA_ARGS__)
 */

/* Use these for testing a couple function instead of whole header
#undef DEBUG_ARRAYND_ENTRY
#define DBG_ARND_ENTR ((void)0)

#undef DEBUG_ARRAYND
#define DBG_ARND(...) ((void)0)

#undef DEBUG_ARRAYND_LOOPS
#define DBG_ARND_LP(...) ((void)0)
*/

/*------------------------*/
/* Function Declarations  */
/*------------------------*/
/*
int AndLoop(int (*fct)(int,int),typ_idx,typ_idx*,typ_idx,typ_idx);
int OrLoop(int (*fct)(int,int),typ_idx,typ_idx*,typ_idx,typ_idx);
 */
int OrLoop_idx(int (*fct)(int,int),typ_idx,typ_idx*,typ_idx,typ_idx*);
int OrLoop(int (*fct)(int,int),typ_idx,typ_idx*,typ_idx);
int AndLoop(int (*fct)(int,int),typ_idx,typ_idx*,typ_idx);
int CountCondLoop(int (*fct)(int,int),typ_idx,typ_idx*,typ_idx);
typ_idx *initNdIdx(typ_idx*,typ_idx,typ_idx,typ_idx*);
typ_idx *initNdIdxWMaps(typ_idx*,typ_idx,typ_idx,typ_idx*,typ_idx*,typ_idx*);
typ_idx *initNdIdxWMaps_NoAdims(typ_idx*,typ_idx,typ_idx*);
typ_idx *initNdLoopCounterLengths(typ_idx,typ_idx,typ_idx*,typ_idx*);
typ_idx *initNdLoopCounterLengthsWMaps(typ_idx,typ_idx,typ_idx*,typ_idx*,typ_idx*,typ_idx*);
void getOUTfromOUTnd(arr *,typ_idx,typ_idx,typ_idx*,typ_idx*,typ_idx*,typ_idx*,
    typ_idx*,typ_idx**,typ_idx**,typ_idx**);
void getOUTfromOUTnd2(arr *,typ_idx,typ_idx,typ_idx,typ_idx*,typ_idx*,typ_idx*,typ_idx*,typ_idx*,
    typ_idx*,typ_idx**,typ_idx**,typ_idx**);

/*
int x_not(int);
int x_and(int,int);
int x_or(int, int);
int x_eq(int, int);
int x_ne(int, int);
int x_gt(int, int);
int x_lt(int, int);
int x_ge(int, int);
int x_le(int, int);
*/
/*-----------*/
/* Functions */
/*-----------*/
/*
int AndLoop(int (*fct)(int,int),typ_idx a,typ_idx *b,typ_idx nb,typ_idx rev){
	typ_idx i;
	if (rev){
		for(i=nb-1;i>-1;i--){
			if( !fct(a,b[i]) ){ return 0; }
		}
	} else {
		for(i=0;i<nb;++i){
			if( !fct(a,b[i]) ){ return 0; }
		}
	}
	return 1;
}


int OrLoop(int (*fct)(int,int),typ_idx a,typ_idx *b,typ_idx nb,typ_idx rev){
	typ_idx i;
	if (rev){
		for(i=nb-1;i>-1;i--){
			if( fct(a,b[i]) ){ return 1; }
		}
	} else {
		for(i=0;i<nb;++i){
			if( fct(a,b[i]) ){ return 1; }
		}
	}
	return 0;
}
 */
 
/* Changed to speed up, should test! */
int OrLoop_idx(int (*fct)(int,int),typ_idx a,typ_idx *b,typ_idx nb,typ_idx *idx_i){
	typ_idx i;
	for(i=0;i<nb;++i){
		if( fct(a,*b++) ){ *idx_i = i; return 1; }
	}
    *idx_i = -1;
	return 0;
}

/* Changed to speed up, should test! */
int OrLoop(int (*fct)(int,int),typ_idx a,typ_idx *b,typ_idx nb){
	typ_idx i;
	for(i=0;i<nb;++i){
		if( fct(a,*b++) ){ return 1; }
	}
	return 0;
}

/* Changed to speed up, should test! */
int AndLoop(int (*fct)(int,int),typ_idx a,typ_idx *b,typ_idx nb){
	typ_idx i;
	for(i=0;i<nb;++i){
		if( !fct(a,*b++) ){ return 0; }
	}
	return 1;
}

/* Changed to speed up, should test! */
int CountCondLoop(int (*fct)(int,int),typ_idx a,typ_idx *b,typ_idx nb){
	typ_idx i, cnt=0;
	for(i=0;i<nb;++i){
		if( fct(a,*b++) ){ ++cnt; }
	}
	return cnt;
}


typ_idx *initNdIdx(typ_idx *c,typ_idx ndims,typ_idx n_adims,typ_idx *adims){
	typ_idx i;
	if (n_adims > ndims){
		fprintf(stderr,"Error in initNdIdx: n_adims must be less than or equal to ndims! ndims=%lld, n_adims=%lld\n",ndims,n_adims);
		exit(0);
	}
	for(i=0;i<n_adims;++i){
		if ((adims[i] < 0) || (ndims <= adims[i])){
			fprintf(stderr,"Error in initNdIdx: Invalid dimension as 4th argument! ndims=%lld, adims[%lld]=%lld\n",ndims,i,adims[i]);
			exit(0);
		}
	}
	typ_idx k,n_kpastadims;
	typ_idx *idx = init0(ndims,TYPIDX);
	for (k=0;k<ndims;++k){
		if (OrLoop(ieq,k,adims,n_adims)){
			idx[k] = 0;
		} else {
			n_kpastadims = CountCondLoop(igt,k,adims,n_adims);	/* How many dims of adims k is greater than */
			idx[k] = c[k-n_kpastadims];
		}
	}

	return idx;
}

typ_idx *initNdIdxWMaps(typ_idx *c,typ_idx ndims,typ_idx n_adims,typ_idx *adims,typ_idx *map_all2c,typ_idx *map_a2all){
	typ_idx k;
	typ_idx *idx = init0(ndims,TYPIDX);
	for (k=0;k<ndims;++k){
		if (OrLoop(ieq,k,adims,n_adims)){
		} else {
            idx[k] = c[map_all2c[map_a2all[k]]];
		}
	}

	return idx;
}

typ_idx *initNdIdxWMaps_NoAdims(typ_idx *c,typ_idx ndims,typ_idx *map_a2all){
	typ_idx k;
	typ_idx *idx = init0(ndims,TYPIDX);
	for (k=0;k<ndims;++k){
        typ_idx kmap = map_a2all[k];
        if (kmap >= 0){
            idx[k] = c[kmap];
        }
	}

	return idx;
}


typ_idx *initNdLoopCounterLengths(typ_idx ndims,typ_idx n_adims,typ_idx *adims,typ_idx *all_lens){
	typ_idx k,n_kpastadims;
	typ_idx *clens = init0(ndims-n_adims,TYPIDX);
	for (k=0;k<ndims;++k){
		if (OrLoop(ieq,k,adims,n_adims)){
		} else {
			n_kpastadims = CountCondLoop(igt,k,adims,n_adims);	/* How many dims of adims k is greater than */
			clens[k-n_kpastadims] = all_lens[k];
		}
	}

	return clens;
}

typ_idx *initNdLoopCounterLengthsWMaps(typ_idx ndims,typ_idx n_adims,typ_idx *adims,typ_idx *all_lens,typ_idx *map_all2c,typ_idx *map_c2all){
	typ_idx k,n_kpastadims;
	typ_idx *clens = init0(ndims-n_adims,TYPIDX);
	for (k=0;k<ndims;++k){
		if (OrLoop(ieq,k,adims,n_adims)){
            map_all2c[k] = -1;
		} else {
			n_kpastadims = CountCondLoop(igt,k,adims,n_adims);	/* How many dims of adims k is greater than */
			clens[k-n_kpastadims]   = all_lens[k];
            map_c2all[k-n_kpastadims] = k;
            map_all2c[k]              = k-n_kpastadims;
		}
	}

	return clens;
}

typ_idx *initNdLoopCounterLengthsWMaps2(typ_idx ndims,typ_idx n_adims,typ_idx *adims,typ_idx *all_lens,typ_idx *map_c2all){
	typ_idx k,n_kpastadims;
	typ_idx *clens = init0(ndims-n_adims,TYPIDX);
	for (k=0;k<ndims;++k){
		if (OrLoop(ieq,k,adims,n_adims)){
		} else {
			n_kpastadims = CountCondLoop(igt,k,adims,n_adims);	/* How many dims of adims k is greater than */
			clens[k-n_kpastadims]   = all_lens[k];
            map_c2all[k-n_kpastadims] = k;
		}
	}

	return clens;
}


void getOUTfromOUTnd(arr *restrict OUTnd,typ_idx ncdims,typ_idx ndims,typ_idx *map_c2all,typ_idx *all_len,typ_idx *c,typ_idx *clens,
    typ_idx *noutdims,typ_idx **idx_out,typ_idx **len_out,typ_idx **adim_out){
#ifdef DEBUG_ARRAYND_LOOPS
    printArrayInfoWHdr(stderr, OUTnd,  "getOUTfromOUTnd: OUTnd - ");
#endif
    typ_idx i,k;
    typ_idx *map_on2all  = mapdims_1ar2Nar(OUTnd,ndims,all_len);
    typ_idx nnewdims  = CountCondLoop(ieq,-1,map_on2all,OUTnd->n);
    typ_idx ntmpdims  = ndims+nnewdims;
    
    typ_idx *idxtmp = malloc(ntmpdims*sizeof(typ_idx));
    typ_idx *lentmp = malloc(ntmpdims*sizeof(typ_idx));
    for (i=0;i<ntmpdims;++i){
        idxtmp[i] = -1;
        lentmp[i] = 0;
    }
    
    for(i=0;i<ncdims;++i){
        idxtmp[map_c2all[i]] = c[i];
        lentmp[map_c2all[i]] = clens[i];
    }

    typ_idx ind = 0;
    typ_idx *adimtmp = malloc(OUTnd->n*sizeof(typ_idx));
    for(i=0;i<OUTnd->n;++i){
        if (map_on2all[i] < 0){
            idxtmp[ndims+ind] = 0;
            lentmp[ndims+ind] = OUTnd->len[i];
            adimtmp[i] = ndims+ind;
            ++ind;
        } else {
            idxtmp[map_on2all[i]] = 0;
            lentmp[map_on2all[i]] = OUTnd->len[i];
            adimtmp[i] = map_on2all[i];
        }
    }
    
    free(map_on2all);
#ifdef DEBUG_ARRAYND_LOOPS
    DBG_ARND_LP("idxtmp  = {"); for (i=0;i<ntmpdims;++i){ DBG_ARND_LP(" %lld",idxtmp[i]);  } DBG_ARND_LP(" }\n");
    DBG_ARND_LP("lentmp  = {"); for (i=0;i<ntmpdims;++i){ DBG_ARND_LP(" %lld",lentmp[i]);  } DBG_ARND_LP(" }\n");
    DBG_ARND_LP("adimtmp = {"); for (i=0;i<OUTnd->n;++i) { DBG_ARND_LP(" %lld",adimtmp[i]); } DBG_ARND_LP(" }\n");
#endif
    *noutdims = ncdims+OUTnd->n;
    typ_idx nsub = 0;
    *idx_out  = init0(*noutdims,TYPIDX);
    *len_out  = init0(*noutdims,TYPIDX);
    *adim_out = init0(OUTnd->n, TYPIDX);
    for (i=0;i<ntmpdims;++i){
        if (idxtmp[i]<0){
            ++nsub;
        } else {
            (*idx_out)[i-nsub] = idxtmp[i];
            (*len_out)[i-nsub] = lentmp[i];
            for(k=0;k<OUTnd->n;++k){
                if (adimtmp[k] == i){
                    (*adim_out)[k] = i-nsub;
                }
            }
        }
    }
#ifdef DEBUG_ARRAYND_LOOPS
    DBG_ARND_LP("idx_out  = {"); for (i=0;i<(*noutdims);++i){ DBG_ARND_LP(" %lld",(*idx_out)[i]);  } DBG_ARND_LP(" }\n");
    DBG_ARND_LP("len_out  = {"); for (i=0;i<(*noutdims);++i){ DBG_ARND_LP(" %lld",(*len_out)[i]);  } DBG_ARND_LP(" }\n");
    DBG_ARND_LP("adim_out = {"); for (i=0;i<OUTnd->n;++i)    { DBG_ARND_LP(" %lld",(*adim_out)[i]); } DBG_ARND_LP(" }\n");
#endif
    free(idxtmp);
    free(lentmp);
    free(adimtmp);
}

void getOUTfromOUTnd2(arr *restrict OUTnd,typ_idx ncdims,typ_idx ndims,typ_idx n_adims,typ_idx *map_c2all,typ_idx *all_len,typ_idx *adim_all,typ_idx *c,typ_idx *clens,
    typ_idx *noutdims,typ_idx **idx_out,typ_idx **len_out,typ_idx **adim_out){
#ifdef DEBUG_ARRAYND_LOOPS
    printArrayInfoWHdr(stderr, OUTnd,  "getOUTfromOUTnd2: OUTnd - ");
#endif
    typ_idx i,k;
    
    typ_idx *avail_dims = init0(ndims,  TYPIDX);
    typ_idx *map_on2all = init0(OUTnd->n,TYPIDX);
    for (i=0;i<OUTnd->n;++i){
        map_on2all[i] = -1;
        for (k=0;k<n_adims;++k){
            if (avail_dims[k] == 0){
                if (OUTnd->len[i] == all_len[adim_all[k]]){
                    map_on2all[i] = adim_all[k];
                    avail_dims[k] = 1;
                    break;
                }
            }
        }
    }
    free(avail_dims);

    typ_idx nnewdims  = CountCondLoop(ieq,-1,map_on2all,OUTnd->n);
    typ_idx ntmpdims  = ndims+nnewdims;
#ifdef DEBUG_ARRAYND_LOOPS
    DBG_ARND_LP("map_on2all = {"); for (i=0;i<OUTnd->n;++i){ DBG_ARND_LP(" %lld",map_on2all[i]);  } DBG_ARND_LP(" }\n");
#endif
    typ_idx *idxtmp = malloc(ntmpdims*sizeof(typ_idx));
    typ_idx *lentmp = malloc(ntmpdims*sizeof(typ_idx));
    for (i=0;i<ntmpdims;++i){
        idxtmp[i] = -1;
        lentmp[i] = 0;
    }
    
    for(i=0;i<ncdims;++i){
        idxtmp[map_c2all[i]] = c[i];
        lentmp[map_c2all[i]] = clens[i];
    }

    typ_idx ind = 0;
    typ_idx *adimtmp = malloc(OUTnd->n*sizeof(typ_idx));
    for(i=0;i<OUTnd->n;++i){
        if (map_on2all[i] < 0){
            idxtmp[ndims+ind] = 0;
            lentmp[ndims+ind] = OUTnd->len[i];
            adimtmp[i] = ndims+ind;
            ++ind;
        } else {
            idxtmp[map_on2all[i]] = 0;
            lentmp[map_on2all[i]] = OUTnd->len[i];
            adimtmp[i] = map_on2all[i];
        }
    }
    
    free(map_on2all);
#ifdef DEBUG_ARRAYND_LOOPS
    DBG_ARND_LP("idxtmp  = {"); for (i=0;i<ntmpdims;++i){ DBG_ARND_LP(" %lld",idxtmp[i]);  } DBG_ARND_LP(" }\n");
    DBG_ARND_LP("lentmp  = {"); for (i=0;i<ntmpdims;++i){ DBG_ARND_LP(" %lld",lentmp[i]);  } DBG_ARND_LP(" }\n");
    DBG_ARND_LP("adimtmp = {"); for (i=0;i<OUTnd->n;++i) { DBG_ARND_LP(" %lld",adimtmp[i]); } DBG_ARND_LP(" }\n");
#endif
    *noutdims = ncdims+OUTnd->n;
    typ_idx nsub = 0;
    *idx_out  = init0(*noutdims,TYPIDX);
    *len_out  = init0(*noutdims,TYPIDX);
    *adim_out = init0(OUTnd->n, TYPIDX);
    for (i=0;i<ntmpdims;++i){
        if (idxtmp[i]<0){
            ++nsub;
        } else {
            (*idx_out)[i-nsub] = idxtmp[i];
            (*len_out)[i-nsub] = lentmp[i];
            for(k=0;k<OUTnd->n;++k){
                if (adimtmp[k] == i){
                    (*adim_out)[k] = i-nsub;
                }
            }
        }
    }
#ifdef DEBUG_ARRAYND_LOOPS
    DBG_ARND_LP("idx_out  = {"); for (i=0;i<(*noutdims);++i){ DBG_ARND_LP(" %lld",(*idx_out)[i]);  } DBG_ARND_LP(" }\n");
    DBG_ARND_LP("len_out  = {"); for (i=0;i<(*noutdims);++i){ DBG_ARND_LP(" %lld",(*len_out)[i]);  } DBG_ARND_LP(" }\n");
    DBG_ARND_LP("adim_out = {"); for (i=0;i<OUTnd->n;++i)    { DBG_ARND_LP(" %lld",(*adim_out)[i]); } DBG_ARND_LP(" }\n");
#endif
    free(idxtmp);
    free(lentmp);
    free(adimtmp);
}



/* Changed to speed up, should test! especially cases when a function modifies Rarr. */
void arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_Loop(fctArgsRdbl fct,arr *restrict OUT,
    arr **arrays,double *dbl_ptr,int *int_ptr,typ_idx *idx_ptr,arr **Rarr,arr **Rdbl,arr **Rint,arr **Ridx,
    int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs,input_args *args,
    typ_idx ndims,typ_idx *map_c2all,typ_idx **map_all2as,
    typ_idx n_adims,typ_idx *adim_all,typ_idx **adim_rarr,typ_idx *n_adims_per_arr,typ_idx **adims,
    typ_idx **idxs,int *is_idx_new,typ_idx dim,typ_idx *c,typ_idx *clens,typ_idx *all_len){
/*	This is a recursive n dimensional loop function	*/
	typ_idx i,j,k,l,m;

    DBG_ARND_LP("arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_Loop: dim=%lld\n",dim);
    typ_idx ncdims = ndims-n_adims;
	if (dim == ncdims){
		j = 0; k = 0; l = 0; m = 0;
        typ_idx idim2;
		for(i=0;i<narrs;++i){
            idim2 = n_adims_per_arr[i];
            if (idim2){
                if (is_idx_new[i]){
                    is_idx_new[i] = 0;
                    freeAr(args->arrays[j]);
                    *args->arrays[j] = grabNdAr_NStride(arrays[i], idim2, adims[i], idxs[i]);
                }
                ++j;
            } else {
                if (arrays[i]->typ == DOUBLE){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->dblp[k] = cDBL(arrays[i],idxs[i]);
                    }
                    ++k;
                } else if (arrays[i]->typ == INT){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->intp[l] = cINTG(arrays[i],idxs[i]);
                    }
                    ++l;
                } else if (arrays[i]->typ == TYPIDX){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->idxp[m] = cIDX(arrays[i],idxs[i]);
                    }
                    ++m;
                } else {
                    fprintf(stderr,"arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_Loop: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                    exit(0);
                }
            }
		}

        arr **arrpp = args->arrpp;
		for(i=0;i<nrarrs;++i){ *arrpp[i] = NullArray(); }
		for(i=0;i<nrdbls;++i){ args->dblpp[i] = address_of_c(Rdbl[i],c); }
		for(i=0;i<nrints;++i){ args->intpp[i] = address_of_c(Rint[i],c); }
		for(i=0;i<nridxs;++i){ args->idxpp[i] = address_of_c(Ridx[i],c); }

        cDBL(OUT,c) = fct(args);

        /* Do the same thing for Rarr as was done with OUT! */
        for (i=0;i<nrarrs;++i){
            typ_idx *idx_rarr = NULL;
            typ_idx *len_rarr = NULL;
            arr *pRarr  = Rarr[i];
            arr *parrpp = arrpp[i];
            typ_idx *padim_rarr = adim_rarr[i];
            if (pRarr->tlen < 1){
                if (!isArNull(parrpp)){
                    typ_idx noutdims;
                    getOUTfromOUTnd2(parrpp,ncdims,ndims,n_adims,map_c2all,all_len,adim_all,c,clens,
                        &noutdims,&idx_rarr,&len_rarr,&adim_rarr[i]);
                    *pRarr= ArrayFromList(noutdims,parrpp->typ,len_rarr);
                    copyMiss(pRarr,arrays[0]);
                    fillArWithMiss(pRarr);
                }
            } else {
                if (!isArNull(parrpp)){
                    typ_idx parrpp_n = parrpp->n;
                    typ_idx pRarr_n  = pRarr->n;
                    idx_rarr = initNdIdx(c,    pRarr_n,parrpp_n,padim_rarr);
                    len_rarr = initNdIdx(clens,pRarr_n,parrpp_n,padim_rarr);
                    typ_idx j_adim;
                    int change_len=0;
                    for(j=0;j<parrpp_n;++j){
                        j_adim = padim_rarr[j];
                        len_rarr[j_adim] = parrpp->len[j];
                        /* Don't worry if new dim length is less than current length */
                        if (len_rarr[j_adim] > pRarr->len[j_adim]){
                            change_len = 1;
                        }
                    }
                    if (change_len) { expandDims(pRarr,len_rarr); }
                }
            }
            if (!isArNull(parrpp)){
                assignPart2(pRarr,parrpp,padim_rarr,idx_rarr);
            }
            free(idx_rarr);
            free(len_rarr);
			freeAr(parrpp);
		}
		return;
	} else {
        typ_idx *pc = &c[dim];
        k           = map_c2all[dim];
		for(*pc=0; *pc < clens[dim]; (*pc)++){
            l = *pc;
#ifdef DEBUG_ARRAYND_LOOPS
            fprintf(stderr,"arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_Loop: l=%lld, *pc=%lld\n",l,*pc);
			DBG_ARND_LP("arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_Loop: ");
			for(j=0;j<=dim;++j){
				DBG_ARND_LP("c[%lld]=%lld ",j,c[j]);
			}
			DBG_ARND_LP("\n");
#endif
            /* l = *pc; */
            for (i=0;i<narrs;++i){
                j = map_all2as[i][k];
                if (j >= 0){
                    is_idx_new[i] = 1; /* This should prevent excessive recalculation of arrays */
                    idxs[i][j] = l;
                }
            }
            arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_Loop(fct,OUT,arrays,dbl_ptr,int_ptr,idx_ptr,Rarr,Rdbl,Rint,Ridx,
                narrs,ndbls,nints,nidxs,nrarrs,nrdbls,nrints,nridxs,args,
                ndims,map_c2all,map_all2as,n_adims,adim_all,adim_rarr,n_adims_per_arr,adims,idxs,is_idx_new,dim+1,c,clens,all_len);
		}
	}

	return;
}

arr arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_WMaps(fctArgsRdbl fct
    ,int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs,
    arr **arrays,double *dbl_ptr,int *int_ptr,typ_idx *idx_ptr,arr **Rarr,arr **Rdbl,arr **Rint,arr **Ridx
    ,typ_idx n_adims,typ_idx *adim_all,typ_idx ndims,typ_idx *all_len,typ_idx **map_as2all) {
    DBG_ARND_ENTR;
	typ_idx i,j,k,l,m;

#ifdef DEBUG_ARRAYND
    DBG_ARND("arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_WMaps: all_len");
	for(i=0;i<ndims;++i){
		DBG_ARND(" %lld",all_len[i]);
	}
	DBG_ARND("\n");
	for(j=0;j<narrs;++j){
        DBG_ARND("arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_WMaps: map_as2all[%lld]",j);
		for(i=0;i<arrays[j]->n;++i){
			DBG_ARND(" %lld",map_as2all[j][i]);
		}
        DBG_ARND("\n");
	}
#endif

    typ_idx **map_all2as = malloc(narrs*sizeof(typ_idx *));
	for(i=0;i<narrs;++i){ map_all2as[i] = mapdims_inverse(arrays[i]->n,ndims,map_as2all[i]); }
#ifdef DEBUG_ARRAYND
	for(j=0;j<narrs;++j){
        DBG_ARND("arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_WMaps: map_all2as[%lld]",j);
		for(i=0;i<ndims;++i){
			DBG_ARND(" %lld",map_all2as[j][i]);
		}
        DBG_ARND("\n");
	}
#endif

    typ_idx **adims = malloc(narrs*sizeof *adims);
	for(i=0;i<narrs;++i){
        adims[i] = malloc(n_adims*sizeof **adims);
        for(k=0;k<n_adims;++k){
            adims[i][k] = -1;
        }
        for(k=0;k<n_adims;++k){
            for(j=0;j<arrays[i]->n;++j){
                if (map_as2all[i][j]==adim_all[k]){
                    adims[i][k] = j;
                    break;
                }
            }
        }
	}
#ifdef DEBUG_ARRAYND
	for(i=0;i<narrs;++i){
        DBG_ARND("arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_WMaps: adims[%lld]",i);
        for(k=0;k<n_adims;++k){
			DBG_ARND(" %2lld",adims[i][k]);
        }
        DBG_ARND("\n");
	}
#endif

    typ_idx **adim_tmp      = malloc(narrs*sizeof *adim_tmp);
    typ_idx *n_adims_per_arr= malloc(narrs*sizeof *n_adims_per_arr);
    for(i=0;i<narrs;++i){
        adim_tmp[i] = malloc(n_adims*sizeof(typ_idx));
        for(k=0,n_adims_per_arr[i]=0;k<n_adims;++k){
            if (adims[i][k] > -1){
                adim_tmp[i][n_adims_per_arr[i]] = adims[i][k];
                n_adims_per_arr[i]++;
            }
        }
    }

	typ_idx *c,*clens,*map_all2c,*map_c2all;
	arr OUT;
	if (ndims < n_adims){
        OUT = NullArray();
        for (i=0;i<nrarrs;++i){ *Rarr[i] = NullArray(); }
        for (i=0;i<nrdbls;++i){ *Rdbl[i] = NullArray(); }
        for (i=0;i<nrints;++i){ *Rint[i] = NullArray(); }
        for (i=0;i<nridxs;++i){ *Ridx[i] = NullArray(); }
    } else {
        map_all2c = init0((ndims),TYPIDX);
        map_c2all = init0((ndims-n_adims),TYPIDX);
		clens = initNdLoopCounterLengthsWMaps(ndims,n_adims,adim_all,all_len,map_all2c,map_c2all);
		c 	= init0(ndims-n_adims,TYPIDX);
        typ_idx **idxs = malloc(narrs*sizeof(typ_idx *));
        for (i=0;i<narrs;++i){
            idxs[i] = initNdIdxWMaps(c,arrays[i]->n,n_adims,adims[i],map_all2c,map_as2all[i]);
        }
        
		OUT	= ArrayFromList(ndims-n_adims,DOUBLE,clens);
	/*	copyMiss(&OUT,arrays[maxar]);   */

        for (i=0;i<nrarrs;++i){ *Rarr[i] = NullArray(); }
        for (i=0;i<nrdbls;++i){
            *Rdbl[i] = ArrayFromList(ndims-n_adims,DOUBLE,clens);
        /*  copyMiss(Rdbl[i],arrays[maxar]);    */
            fillArWithMiss(Rdbl[i]);
        }
        for (i=0;i<nrints;++i){
            *Rint[i] = ArrayFromList(ndims-n_adims,INT,clens);
        /*  copyMiss(Rint[i],arrays[maxar]);    */
            fillArWithMiss(Rint[i]);
        }
        for (i=0;i<nridxs;++i){
            *Ridx[i] = ArrayFromList(ndims-n_adims,TYPIDX,clens);
        /*  copyMiss(Ridx[i],arrays[maxar]);    */
            fillArWithMiss(Ridx[i]);
        }


        int narnds,ndbls2,nints2,nidxs2;

		j = 0; k = 0; l = 0; m = 0;
		arr   **arnd = malloc(narrs*sizeof(arr *));
		double *dblp = malloc((narrs+ndbls)*sizeof(double));
		int    *intp = malloc((narrs+nints)*sizeof(int));
		typ_idx*idxp = malloc((narrs+nidxs)*sizeof(typ_idx));
		double *dblp_miss = malloc((narrs+ndbls)*sizeof(double));
		int    *intp_miss = malloc((narrs+nints)*sizeof(int));
		typ_idx*idxp_miss = malloc((narrs+nidxs)*sizeof(typ_idx));
		for(i=0;i<narrs;++i){
			if (n_adims_per_arr[i]){
                arnd[j]  = malloc(sizeof(arr));
                *arnd[j] = NullArray();
				++j;
			} else {
                if (arrays[i]->typ == DOUBLE){
                    dblp_miss[k] = *(double *)getMiss(arrays[i]);
                    ++k;
                } else if (arrays[i]->typ == INT){
                    intp_miss[l] = *(int *)getMiss(arrays[i]);
                    ++l;
                } else if (arrays[i]->typ == TYPIDX){
                    idxp_miss[m] = *(typ_idx *)getMiss(arrays[i]);
                    ++m;
                } else {
                    fprintf(stderr,"arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_Loop: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                    exit(0);
                }
			}
		}
		for(i=0;i<ndbls;++i){
			dblp[k] = dbl_ptr[i];
            dblp_miss[k] = -999.0;
			++k;
		}
		for(i=0;i<nints;++i){
			intp[l] = int_ptr[i];
            intp_miss[l] = -999;
			++l;
		}
		for(i=0;i<nidxs;++i){
			idxp[m] = idx_ptr[i];
            idxp_miss[m] = -999;
			++m;
		}
		narnds = j;
		ndbls2 = k;
		nints2 = l;
		nidxs2 = m;

		arr    **arrpp = malloc(nrarrs*sizeof(arr *));
		for(i=0;i<nrarrs;++i){
            arrpp[i] = malloc(sizeof(arr));
		}
		double     **dblpp = malloc(nrdbls*sizeof(double *));
		double *dblpp_miss = malloc(nrdbls*sizeof(double));
		for(i=0;i<nrdbls;++i){
			dblpp_miss[i] = *(double *)getMiss(Rdbl[i]);
		}
		int     **intpp = malloc(nrints*sizeof(int *));
		int *intpp_miss = malloc(nrints*sizeof(int));
		for(i=0;i<nrints;++i){
			intpp_miss[i] = *(int *)getMiss(Rint[i]);
		}
		typ_idx     **idxpp = malloc(nridxs*sizeof(typ_idx *));
		typ_idx *idxpp_miss = malloc(nridxs*sizeof(typ_idx));
		for(i=0;i<nridxs;++i){
			idxpp_miss[i] = *(typ_idx *)getMiss(Ridx[i]);
		}

        input_args args=passInputArgs(narnds,ndbls2,nints2,nidxs2,nrarrs,nrdbls,nrints,nridxs
            ,arnd,dblp,intp,idxp,arrpp,dblpp,intpp,idxpp,dblp_miss,intp_miss,idxp_miss,dblpp_miss,intpp_miss,idxpp_miss,getMiss(&OUT));

		int *is_idx_new = malloc(narrs*sizeof(int));
        set_ints_to_val(narrs,is_idx_new,1);

        typ_idx **adim_rarr = malloc(nrarrs*sizeof(typ_idx *));
        for (i=0;i<nrarrs;++i){ adim_rarr[i] = NULL; }

		arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_Loop(fct,&OUT,arrays,dbl_ptr,int_ptr,idx_ptr,Rarr,Rdbl,Rint,Ridx,
            narrs,ndbls,nints,nidxs,nrarrs,nrdbls,nrints,nridxs,&args,
            ndims,map_c2all,map_all2as,n_adims,adim_all,adim_rarr,n_adims_per_arr,adim_tmp,idxs,is_idx_new,(typ_idx)0,c,clens,all_len);
            
        free(c);
		free(clens);
		free(map_all2c);
		free(map_c2all);
        for (i=0;i<nrarrs;++i){ free(adim_rarr[i]); }
        free(adim_rarr);
        for (i=0;i<narrs;++i){ free(idxs[i]); }
        free(idxs);

        free(is_idx_new);

		for (i=0;i<narnds;++i){
			freeAr(arnd[i]);
			free(arnd[i]);
		}
		for (i=0;i<nrarrs;++i){
			free(arrpp[i]);
		}
        freeInputArgs(&args);
	}

    for(i=0;i<narrs;++i){
        free(adims[i]);
        free(adim_tmp[i]);
        free(map_all2as[i]);
    }
    free(adims);
    free(adim_tmp);
    free(n_adims_per_arr);
    free(map_all2as);
	return OUT;
}

arr arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx(fctArgsRdbl fct
    ,int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs,
    arr **arrays,double *dbl_ptr,int *int_ptr,typ_idx *idx_ptr,arr **Rarr,arr **Rdbl,arr **Rint,arr **Ridx
    ,typ_idx n_adims,typ_idx *adims_in) {
	typ_idx i,ndims;
	typ_idx **map_as2all;
	typ_idx *all_len = mapdims_Nar(narrs,arrays,&ndims,&map_as2all);

	typ_idx maxn = -1,maxar = -1;
	for(i=0;i<narrs;++i){
		if (arrays[i]->n > maxn){
			maxn  = arrays[i]->n;
			maxar = i;
		}
	}

	if (maxn < n_adims){
		fprintf(stderr,"Error in arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx: n_adims must be less than or equal to %lld! n_adims=%lld\n"
			,maxn,n_adims);
		exit(0);
	}

    typ_idx *adim_all = malloc(n_adims*sizeof(typ_idx));
    for(i=0;i<n_adims;++i){
        adim_all[i]= map_as2all[maxar][adims_in[i]];
    }

    arr OUT = arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_WMaps(fct,narrs,ndbls,nints,nidxs,nrarrs,nrdbls,nrints,nridxs,
        arrays,dbl_ptr,int_ptr,idx_ptr,Rarr,Rdbl,Rint,Ridx,n_adims,adim_all,ndims,all_len,map_as2all);
    
    for(i=0;i<narrs;++i){
        free(map_as2all[i]);
    }
	free(map_as2all);
	free(all_len);
	free(adim_all);
	return OUT;
}

arr arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_VArg(
    fctArgsRdbl fct,typ_idx n_adims,typ_idx *adims_in,int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs,...){
	int i;

	arr   **arrays  = malloc(narrs *sizeof(arr *));
	double *dbl_ptr = malloc(ndbls *sizeof(double));
	int    *int_ptr = malloc(nints *sizeof(int));
	typ_idx*idx_ptr = malloc(nidxs *sizeof(typ_idx));
	arr   **Rarr    = malloc(nrarrs*sizeof(arr *));
	arr   **Rdbl    = malloc(nrdbls*sizeof(arr *));
	arr   **Rint    = malloc(nrints*sizeof(arr *));
	arr   **Ridx    = malloc(nridxs*sizeof(arr *));

	va_list arg_list;
	va_start(arg_list, nridxs);
	for (i=0;i<narrs;++i){
		arrays[i]  = va_arg(arg_list, arr *);
	}
	for (i=0;i<ndbls;++i){
		dbl_ptr[i] = va_arg(arg_list, double);
	}
	for (i=0;i<nints;++i){
		int_ptr[i] = va_arg(arg_list, int);
	}
	for (i=0;i<nidxs;++i){
		idx_ptr[i] = va_arg(arg_list, typ_idx);
	}
	for (i=0;i<nrarrs;++i){
		Rarr[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrdbls;++i){
		Rdbl[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrints;++i){
		Rint[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nridxs;++i){
		Ridx[i]   = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

    arr OUT = arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx(fct,narrs,ndbls,nints,nidxs,nrarrs,nrdbls,nrints,nridxs,
        arrays,dbl_ptr,int_ptr,idx_ptr,Rarr,Rdbl,Rint,Ridx,n_adims,adims_in);

	free(arrays);
	free(dbl_ptr);
	free(int_ptr);
	free(idx_ptr);
	free(Rarr);
	free(Rdbl);
	free(Rint);
	free(Ridx);
	return OUT;
}



void arNdArgNarNsNintRet1dblNarrNDblNInt_Loop(fctArgsRdbl fct,arr *restrict OUT,
    arr **arrays,arr **Rarr,arr **Rdbl,arr **Rint,
    int narrs,int nrarrs,int nrdbls,int nrints,input_args *args,
    typ_idx ndims,typ_idx *map_c2all,typ_idx **map_all2as,
    typ_idx n_adims,typ_idx *adim_all,typ_idx **adim_rarr,typ_idx *n_adims_per_arr,typ_idx **adims,
    typ_idx **idxs,int *is_idx_new,typ_idx dim,typ_idx *c,typ_idx *clens,typ_idx *all_len){
/*	This is a recursive n dimensional loop function	*/
	typ_idx i,j,k,l;

    DBG_ARND_LP("arNdArgNarNsNintRet1dblNarrNDblNInt_Loop: dim=%lld\n",dim);
    typ_idx ncdims = ndims-n_adims;
	if (dim == ncdims){
		j = 0; k = 0; l = 0;
        typ_idx idim2;
		for(i=0;i<narrs;++i){
            idim2 = n_adims_per_arr[i];
            if (idim2){
                if (is_idx_new[i]){
                    is_idx_new[i] = 0;
                    freeAr(args->arrays[j]);
                    *args->arrays[j] = grabNdAr_NStride(arrays[i], idim2, adims[i], idxs[i]);
                }
                ++j;
            } else {
                if (arrays[i]->typ == DOUBLE){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->dblp[k] = cDBL(arrays[i],idxs[i]);
                    }
                    ++k;
                } else if (arrays[i]->typ == INT){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->intp[l] = cINTG(arrays[i],idxs[i]);
                    }
                    ++l;
                } else {
                    fprintf(stderr,"arNdArgNarNsNintRet1dblNarrNDblNInt_Loop: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                    exit(0);
                }
            }
		}

        arr **arrpp = args->arrpp;
		for(i=0;i<nrarrs;++i){ *arrpp[i] = NullArray(); }
		for(i=0;i<nrdbls;++i){ args->dblpp[i] = address_of_c(Rdbl[i],c); }
		for(i=0;i<nrints;++i){ args->intpp[i] = address_of_c(Rint[i],c); }

        cDBL(OUT,c) = fct(args);

        /* Do the same thing for Rarr as was done with OUT! */
        for (i=0;i<nrarrs;++i){
            typ_idx *idx_rarr = NULL;
            typ_idx *len_rarr = NULL;
            if (Rarr[i]->tlen < 1){
                if (!isArNull(arrpp[i])){
                    typ_idx noutdims;
                    getOUTfromOUTnd2(arrpp[i],ncdims,ndims,n_adims,map_c2all,all_len,adim_all,c,clens,
                        &noutdims,&idx_rarr,&len_rarr,&adim_rarr[i]);
                    *Rarr[i]= ArrayFromList(noutdims,arrpp[i]->typ,len_rarr);
                    copyMiss(Rarr[i],arrays[0]);
                    fillArWithMiss(Rarr[i]);
                }
            } else {
                if (!isArNull(arrpp[i])){
                    idx_rarr = initNdIdx(c,    Rarr[i]->n,arrpp[i]->n,adim_rarr[i]);
                    len_rarr = initNdIdx(clens,Rarr[i]->n,arrpp[i]->n,adim_rarr[i]);
                    typ_idx j_adim;
                    int change_len=0;
                    for(j=0;j<arrpp[i]->n;++j){
                        j_adim = adim_rarr[i][j];
                        len_rarr[j_adim] = arrpp[i]->len[j];
                        /* Don't worry if new dim length is less than current length */
                        if (len_rarr[j_adim] > Rarr[i]->len[j_adim]){
                            change_len = 1;
                        }
                    }
                    if (change_len) { expandDims(Rarr[i],len_rarr); }
                }
            }
            if (!isArNull(arrpp[i])){
                assignPart2(Rarr[i],arrpp[i],adim_rarr[i],idx_rarr);
            }
            free(idx_rarr);
            free(len_rarr);
        }

		for (i=0;i<nrarrs;++i){
			freeAr(arrpp[i]);
		}
		return;
	} else {
		for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
#ifdef DEBUG_ARRAYND_LOOPS
			DBG_ARND_LP("arNdArgNarNsNintRet1dblNarrNDblNInt_Loop: ");
			for(j=0;j<=dim;++j){
				DBG_ARND_LP("c[%lld]=%lld ",j,c[j]);
			}
			DBG_ARND_LP("\n");
#endif
            k = map_c2all[dim];
            l = c[dim];
            for (i=0;i<narrs;++i){
                j = map_all2as[i][k];
                if (j >= 0){
                    is_idx_new[i] = 1; /* This should prevent excessive recalculation of arrays */
                    idxs[i][j] = l;
                }
            }
            arNdArgNarNsNintRet1dblNarrNDblNInt_Loop(fct,OUT,arrays,Rarr,Rdbl,Rint,
                narrs,nrarrs,nrdbls,nrints,args,
                ndims,map_c2all,map_all2as,n_adims,adim_all,adim_rarr,n_adims_per_arr,adims,idxs,is_idx_new,dim+1,c,clens,all_len);
		}
	}

	return;
}

arr arNdArgNarNsNintRet1dblNarrNDblNInt_WMaps(fctArgsRdbl fct,int narrs,int ndbls,int nints,int nrarrs,int nrdbls,int nrints,
    arr **arrays,double *dbl_ptr,int *int_ptr,arr **Rarr,arr **Rdbl,arr **Rint,typ_idx n_adims,typ_idx *adim_all,typ_idx ndims,typ_idx *all_len,typ_idx **map_as2all) {
    DBG_ARND_ENTR;
	typ_idx i,j,k,l;

#ifdef DEBUG_ARRAYND
    DBG_ARND("arNdArgNarNsNintRet1dblNarrNDblNInt_WMaps: all_len");
	for(i=0;i<ndims;++i){
		DBG_ARND(" %lld",all_len[i]);
	}
	DBG_ARND("\n");
	for(j=0;j<narrs;++j){
        DBG_ARND("arNdArgNarNsNintRet1dblNarrNDblNInt_WMaps: map_as2all[%lld]",j);
		for(i=0;i<arrays[j]->n;++i){
			DBG_ARND(" %lld",map_as2all[j][i]);
		}
        DBG_ARND("\n");
	}
#endif

    typ_idx **map_all2as = malloc(narrs*sizeof(typ_idx *));
	for(i=0;i<narrs;++i){ map_all2as[i] = mapdims_inverse(arrays[i]->n,ndims,map_as2all[i]); }
#ifdef DEBUG_ARRAYND
	for(j=0;j<narrs;++j){
        DBG_ARND("arNdArgNarNsNintRet1dblNarrNDblNInt_WMaps: map_all2as[%lld]",j);
		for(i=0;i<ndims;++i){
			DBG_ARND(" %lld",map_all2as[j][i]);
		}
        DBG_ARND("\n");
	}
#endif

    typ_idx **adims = malloc(narrs*sizeof *adims);
	for(i=0;i<narrs;++i){
        adims[i] = malloc(n_adims*sizeof **adims);
        for(k=0;k<n_adims;++k){
            adims[i][k] = -1;
        }
        for(k=0;k<n_adims;++k){
            for(j=0;j<arrays[i]->n;++j){
                if (map_as2all[i][j]==adim_all[k]){
                    adims[i][k] = j;
                    break;
                }
            }
        }
	}
#ifdef DEBUG_ARRAYND
	for(i=0;i<narrs;++i){
        DBG_ARND("arNdArgNarNsNintRet1dblNarrNDblNInt_WMaps: adims[%lld]",i);
        for(k=0;k<n_adims;++k){
			DBG_ARND(" %2lld",adims[i][k]);
        }
        DBG_ARND("\n");
	}
#endif

    typ_idx **adim_tmp      = malloc(narrs*sizeof *adim_tmp);
    typ_idx *n_adims_per_arr= malloc(narrs*sizeof *n_adims_per_arr);
    for(i=0;i<narrs;++i){
        adim_tmp[i] = malloc(n_adims*sizeof(typ_idx));
        for(k=0,n_adims_per_arr[i]=0;k<n_adims;++k){
            if (adims[i][k] > -1){
                adim_tmp[i][n_adims_per_arr[i]] = adims[i][k];
                n_adims_per_arr[i]++;
            }
        }
    }

	typ_idx *c,*clens,*map_all2c,*map_c2all;
	arr OUT;
	if (ndims < n_adims){
        OUT = NullArray();
        for (i=0;i<nrarrs;++i){ *Rarr[i] = NullArray(); }
        for (i=0;i<nrdbls;++i){ *Rdbl[i] = NullArray(); }
        for (i=0;i<nrints;++i){ *Rint[i] = NullArray(); }
    } else {
        map_all2c = init0((ndims),TYPIDX);
        map_c2all = init0((ndims-n_adims),TYPIDX);
		clens = initNdLoopCounterLengthsWMaps(ndims,n_adims,adim_all,all_len,map_all2c,map_c2all);
		c 	= init0(ndims-n_adims,TYPIDX);
        typ_idx **idxs = malloc(narrs*sizeof(typ_idx *));
        for (i=0;i<narrs;++i){
            idxs[i] = initNdIdxWMaps(c,arrays[i]->n,n_adims,adims[i],map_all2c,map_as2all[i]);
        }
        
		OUT	= ArrayFromList(ndims-n_adims,DOUBLE,clens);
	/*	copyMiss(&OUT,arrays[maxar]);   */

        for (i=0;i<nrarrs;++i){ *Rarr[i] = NullArray(); }
        for (i=0;i<nrdbls;++i){
            *Rdbl[i] = ArrayFromList(ndims-n_adims,DOUBLE,clens);
        /*  copyMiss(Rdbl[i],arrays[maxar]);    */
            fillArWithMiss(Rdbl[i]);
        }
        for (i=0;i<nrints;++i){
            *Rint[i] = ArrayFromList(ndims-n_adims,INT,clens);
        /*  copyMiss(Rint[i],arrays[maxar]);    */
            fillArWithMiss(Rint[i]);
        }


		j = 0; k = 0; l = 0;
		arr   **arnd = malloc(narrs*sizeof(arr *));
		double *dblp = malloc((narrs+ndbls)*sizeof(double));
		int    *intp = malloc((narrs+nints)*sizeof(int));
		double *dblp_miss = malloc((narrs+ndbls)*sizeof(double));
		int    *intp_miss = malloc((narrs+nints)*sizeof(int));
		for(i=0;i<narrs;++i){
			if (n_adims_per_arr[i]){
                arnd[j]  = malloc(sizeof(arr));
                *arnd[j] = NullArray();
				++j;
			} else {
                if (arrays[i]->typ == DOUBLE){
                    dblp_miss[k] = *(double *)getMiss(arrays[i]);
                    ++k;
                } else if (arrays[i]->typ == INT){
                    intp_miss[l] = *(int *)getMiss(arrays[i]);
                    ++l;
                } else {
                    fprintf(stderr,"arNdArgNarNsNintRet1dblNarrNDblNInt_WMaps: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                    exit(0);
                }
			}
		}
		for(i=0;i<ndbls;++i){
			dblp[k] = dbl_ptr[i];
            dblp_miss[k] = -999.0;
			++k;
		}
		for(i=0;i<nints;++i){
			intp[l] = int_ptr[i];
            intp_miss[l] = -999;
			++l;
		}
		int narnds = j;
		int ndbls2 = k;
		int nints2 = l;

		arr    **arrpp = malloc(nrarrs*sizeof(arr *));
		for(i=0;i<nrarrs;++i){
            arrpp[i] = malloc(sizeof(arr));
		}
		double     **dblpp = malloc(nrdbls*sizeof(double *));
		double *dblpp_miss = malloc(nrdbls*sizeof(double));
		for(i=0;i<nrdbls;++i){
			dblpp_miss[i] = *(double *)getMiss(Rdbl[i]);
		}
		int     **intpp = malloc(nrints*sizeof(int *));
		int *intpp_miss = malloc(nrints*sizeof(int));
		for(i=0;i<nrints;++i){
			intpp_miss[i] = *(int *)getMiss(Rint[i]);
		}

        input_args args=passInputArgs(narnds,ndbls2,nints2,0,nrarrs,nrdbls,nrints,0
            ,arnd,dblp,intp,NULL,arrpp,dblpp,intpp,NULL,dblp_miss,intp_miss,NULL,dblpp_miss,intpp_miss,NULL,getMiss(&OUT));

		int *is_idx_new = malloc(narrs*sizeof(int));
        set_ints_to_val(narrs,is_idx_new,1);

        typ_idx **adim_rarr = malloc(nrarrs*sizeof(typ_idx *));
        for (i=0;i<nrarrs;++i){ adim_rarr[i] = NULL; }

		arNdArgNarNsNintRet1dblNarrNDblNInt_Loop(fct,&OUT,arrays,Rarr,Rdbl,Rint,
            narrs,nrarrs,nrdbls,nrints,&args,
            ndims,map_c2all,map_all2as,n_adims,adim_all,adim_rarr,n_adims_per_arr,adim_tmp,idxs,is_idx_new,(typ_idx)0,c,clens,all_len);

        free(c);
		free(clens);
		free(map_all2c);
		free(map_c2all);
        for (i=0;i<nrarrs;++i){ free(adim_rarr[i]); }
        free(adim_rarr);
        for (i=0;i<narrs;++i){ free(idxs[i]); }
        free(idxs);

        free(is_idx_new);

		for (i=0;i<narnds;++i){
			freeAr(arnd[i]);
			free(arnd[i]);
		}
		for (i=0;i<nrarrs;++i){
			free(arrpp[i]);
		}
        freeInputArgs(&args);
	}

    for(i=0;i<narrs;++i){
        free(adims[i]);
        free(adim_tmp[i]);
        free(map_all2as[i]);
    }
    free(adims);
    free(adim_tmp);
    free(n_adims_per_arr);
    free(map_all2as);
	return OUT;
}

arr arNdArgNarNsNintRet1dblNarrNDblNInt(fctArgsRdbl fct,int narrs,int ndbls,int nints,int nrarrs,int nrdbls,int nrints,
    arr **arrays,double *dbl_ptr,int *int_ptr,arr **Rarr,arr **Rdbl,arr **Rint,typ_idx n_adims,typ_idx *adims_in) {
	typ_idx i,ndims;
	typ_idx **map_as2all;
	typ_idx *all_len = mapdims_Nar(narrs,arrays,&ndims,&map_as2all);

	typ_idx maxn = -1,maxar = -1;
	for(i=0;i<narrs;++i){
		if (arrays[i]->n > maxn){
			maxn  = arrays[i]->n;
			maxar = i;
		}
	}

	if (maxn < n_adims){
		fprintf(stderr,"Error in arNdArgNarNsNintRet1dblNarrNDblNInt: n_adims must be less than or equal to %lld! n_adims=%lld\n"
			,maxn,n_adims);
		exit(0);
	}

    typ_idx *adim_all = malloc(n_adims*sizeof(typ_idx));
    for(i=0;i<n_adims;++i){
        adim_all[i]= map_as2all[maxar][adims_in[i]];
    }

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt_WMaps(fct,narrs,ndbls,nints,nrarrs,nrdbls,nrints,
        arrays,dbl_ptr,int_ptr,Rarr,Rdbl,Rint,n_adims,adim_all,ndims,all_len,map_as2all);

    for(i=0;i<narrs;++i){
        free(map_as2all[i]);
    }
	free(map_as2all);
	free(all_len);
	free(adim_all);
	return OUT;
}

arr arNdArgNarNsNintRet1dblNarrNDblNInt_VArg(
    fctArgsRdbl fct,typ_idx n_adims,typ_idx *adims_in,int narrs,int ndbls,int nints,int nrarrs,int nrdbls,int nrints,...){
	int i;

	arr   **arrays  = malloc(narrs *sizeof(arr *));
	double *dbl_ptr = malloc(ndbls *sizeof(double));
	int    *int_ptr = malloc(nints *sizeof(int));
	arr   **Rarr    = malloc(nrarrs*sizeof(arr *));
	arr   **Rdbl    = malloc(nrdbls*sizeof(arr *));
	arr   **Rint    = malloc(nrints*sizeof(arr *));

	va_list arg_list;
	va_start(arg_list, nrints);
	for (i=0;i<narrs;++i){
		arrays[i]  = va_arg(arg_list, arr *);
	}
	for (i=0;i<ndbls;++i){
		dbl_ptr[i] = va_arg(arg_list, double);
	}
	for (i=0;i<nints;++i){
		int_ptr[i] = va_arg(arg_list, int);
	}
	for (i=0;i<nrarrs;++i){
		Rarr[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrdbls;++i){
		Rdbl[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrints;++i){
		Rint[i]   = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,ndbls,nints,nrarrs,nrdbls,nrints,
        arrays,dbl_ptr,int_ptr,Rarr,Rdbl,Rint,n_adims,adims_in);

	free(arrays);
	free(dbl_ptr);
	free(int_ptr);
	free(Rarr);
	free(Rdbl);
	free(Rint);
	return OUT;
}

arr arNdArg1arRet1Dbl(fctArgsRdbl fct, arr *restrict X, typ_idx n_adims, typ_idx *adims) {
	int narrs = 1;

	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,0,0,0,0,0,arrays,NULL,NULL,NULL,NULL,NULL,n_adims,adims);
	free(arrays);
	return OUT;
}

arr arNdArg2arRet1Dbl(fctArgsRdbl fct, arr *restrict X, arr *restrict Y, typ_idx n_adims, typ_idx *adims) {
	int narrs = 2;

	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,0,0,0,0,0,arrays,NULL,NULL,NULL,NULL,NULL,n_adims,adims);
	free(arrays);
	return OUT;
}

arr arNdArg3arRet1Dbl(fctArgsRdbl fct, arr *restrict X, arr *restrict Y, arr *restrict Z, typ_idx n_adims, typ_idx *adims) {
	int narrs = 3;

	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,0,0,0,0,0,arrays,NULL,NULL,NULL,NULL,NULL,n_adims,adims);
	free(arrays);
	return OUT;
}

arr arNdArg4arRet1Dbl(fctArgsRdbl fct, arr *restrict X, arr *restrict Y, arr *restrict Z, arr *restrict T, typ_idx n_adims, typ_idx *adims) {
	int narrs = 4;

	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = T;

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,0,0,0,0,0,arrays,NULL,NULL,NULL,NULL,NULL,n_adims,adims);
	free(arrays);
	return OUT;
}

arr arNdArg1ar1sRet1Dbl(fctArgsRdbl fct, arr *restrict X, double xdbl, typ_idx n_adims, typ_idx *adims) {
	int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

	int ndbls = 1;
	double *dbl_ptr = dbls(ndbls, xdbl);

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL,NULL,n_adims,adims);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr arNdArg2ar1sRet1Dbl(fctArgsRdbl fct, arr *restrict X, arr *restrict Y, double xdbl, typ_idx n_adims, typ_idx *adims) {
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	int ndbls = 1;
	double *dbl_ptr = dbls(ndbls, xdbl);

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL,NULL,n_adims,adims);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr arNdArg2ar2sRet1Dbl(fctArgsRdbl fct, arr *restrict X, arr *restrict Y, double xdbl, double ydbl, typ_idx n_adims, typ_idx *adims) {
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	int ndbls = 2;
	double *dbl_ptr = dbls(ndbls, xdbl, ydbl);

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL,NULL,n_adims,adims);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr arNdArg3ar2sRet1Dbl(fctArgsRdbl fct, arr *restrict X, arr *restrict Y, arr *restrict Z, double xdbl, double ydbl, typ_idx n_adims, typ_idx *adims) {
	int narrs = 3;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

	int ndbls = 2;
	double *dbl_ptr = dbls(ndbls, xdbl, ydbl);

    arr OUT = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL,NULL,n_adims,adims);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}



void arNdArgNarNsNintNidxRet1idxNarrNDblNIntNIdx_Loop(fctArgsRidx fct,arr *restrict OUT,
    arr **arrays,double *dbl_ptr,int *int_ptr,typ_idx *idx_ptr,arr **Rarr,arr **Rdbl,arr **Rint,arr **Ridx,
    int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs,input_args *args,
    typ_idx ndims,typ_idx *map_c2all,typ_idx **map_all2as,
    typ_idx n_adims,typ_idx *adim_all,typ_idx **adim_rarr,typ_idx *n_adims_per_arr,typ_idx **adims,
    typ_idx **idxs,int *is_idx_new,typ_idx dim,typ_idx *c,typ_idx *clens,typ_idx *all_len){
/*	This is a recursive n dimensional loop function	*/
	typ_idx i,j,k,l,m;

    DBG_ARND_LP("arNdArgNarNsNintNidxRet1idxNarrNDblNIntNIdx_Loop: dim=%lld\n",dim);
    typ_idx ncdims = ndims-n_adims;
	if (dim == ncdims){
		j = 0; k = 0; l = 0; m = 0;
        typ_idx idim2;
		for(i=0;i<narrs;++i){
            idim2 = n_adims_per_arr[i];
            if (idim2){
                if (is_idx_new[i]){
                    is_idx_new[i] = 0;
                    freeAr(args->arrays[j]);
                    *args->arrays[j] = grabNdAr_NStride(arrays[i], idim2, adims[i], idxs[i]);
                }
                ++j;
            } else {
                if (arrays[i]->typ == DOUBLE){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->dblp[k] = cDBL(arrays[i],idxs[i]);
                    }
                    ++k;
                } else if (arrays[i]->typ == INT){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->intp[l] = cINTG(arrays[i],idxs[i]);
                    }
                    ++l;
                } else if (arrays[i]->typ == TYPIDX){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->idxp[m] = cIDX(arrays[i],idxs[i]);
                    }
                    ++m;
                } else {
                    fprintf(stderr,"arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_Loop: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                    exit(0);
                }
            }
		}

        arr **arrpp = args->arrpp;
		for(i=0;i<nrarrs;++i){ *arrpp[i] = NullArray(); }
		for(i=0;i<nrdbls;++i){ args->dblpp[i] = address_of_c(Rdbl[i],c); }
		for(i=0;i<nrints;++i){ args->intpp[i] = address_of_c(Rint[i],c); }
		for(i=0;i<nridxs;++i){ args->idxpp[i] = address_of_c(Ridx[i],c); }

        cIDX(OUT,c) = fct(args);

        /* Do the same thing for Rarr as was done with OUT! */
        for (i=0;i<nrarrs;++i){
            typ_idx *idx_rarr = NULL;
            typ_idx *len_rarr = NULL;
            if (Rarr[i]->tlen < 1){
                if (!isArNull(arrpp[i])){
                    typ_idx noutdims;
                    getOUTfromOUTnd2(arrpp[i],ncdims,ndims,n_adims,map_c2all,all_len,adim_all,c,clens,
                        &noutdims,&idx_rarr,&len_rarr,&adim_rarr[i]);
                    *Rarr[i]= ArrayFromList(noutdims,arrpp[i]->typ,len_rarr);
                    copyMiss(Rarr[i],arrays[0]);
                    fillArWithMiss(Rarr[i]);
                }
            } else {
                if (!isArNull(arrpp[i])){
                    idx_rarr = initNdIdx(c,    Rarr[i]->n,arrpp[i]->n,adim_rarr[i]);
                    len_rarr = initNdIdx(clens,Rarr[i]->n,arrpp[i]->n,adim_rarr[i]);
                    typ_idx j_adim;
                    int change_len=0;
                    for(j=0;j<arrpp[i]->n;++j){
                        j_adim = adim_rarr[i][j];
                        len_rarr[j_adim] = arrpp[i]->len[j];
                        /* Don't worry if new dim length is less than current length */
                        if (len_rarr[j_adim] > Rarr[i]->len[j_adim]){
                            change_len = 1;
                        }
                    }
                    if (change_len) { expandDims(Rarr[i],len_rarr); }
                }
            }
            if (!isArNull(arrpp[i])){
                assignPart2(Rarr[i],arrpp[i],adim_rarr[i],idx_rarr);
            }
            free(idx_rarr);
            free(len_rarr);
        }

		for (i=0;i<nrarrs;++i){
			freeAr(arrpp[i]);
		}
		return;
	} else {
		for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
#ifdef DEBUG_ARRAYND_LOOPS
			DBG_ARND_LP("arNdArgNarNsNintNidxRet1idxNarrNDblNIntNIdx_Loop: ");
			for(j=0;j<=dim;++j){
				DBG_ARND_LP("c[%lld]=%lld ",j,c[j]);
			}
			DBG_ARND_LP("\n");
#endif
            k = map_c2all[dim];
            l = c[dim];
            for (i=0;i<narrs;++i){
                j = map_all2as[i][k];
                if (j >= 0){
                    is_idx_new[i] = 1; /* This should prevent excessive recalculation of arrays */
                    idxs[i][j] = l;
                }
            }
            arNdArgNarNsNintNidxRet1idxNarrNDblNIntNIdx_Loop(fct,OUT,arrays,dbl_ptr,int_ptr,idx_ptr,Rarr,Rdbl,Rint,Ridx,
                narrs,ndbls,nints,nidxs,nrarrs,nrdbls,nrints,nridxs,args,
                ndims,map_c2all,map_all2as,n_adims,adim_all,adim_rarr,n_adims_per_arr,adims,idxs,is_idx_new,dim+1,c,clens,all_len);
		}
	}

	return;
}

arr arNdArgNarNsNintNidxRet1idxNarrNDblNIntNIdx_WMaps(fctArgsRidx fct
    ,int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs,
    arr **arrays,double *dbl_ptr,int *int_ptr,typ_idx *idx_ptr,arr **Rarr,arr **Rdbl,arr **Rint,arr **Ridx
    ,typ_idx n_adims,typ_idx *adim_all,typ_idx ndims,typ_idx *all_len,typ_idx **map_as2all) {
    DBG_ARND_ENTR;
	typ_idx i,j,k,l,m;

#ifdef DEBUG_ARRAYND
    DBG_ARND("arNdArgNarNsNintNidxRet1idxNarrNDblNIntNIdx_WMaps: all_len");
	for(i=0;i<ndims;++i){
		DBG_ARND(" %lld",all_len[i]);
	}
	DBG_ARND("\n");
	for(j=0;j<narrs;++j){
        DBG_ARND("arNdArgNarNsNintNidxRet1idxNarrNDblNIntNIdx_WMaps: map_as2all[%lld]",j);
		for(i=0;i<arrays[j]->n;++i){
			DBG_ARND(" %lld",map_as2all[j][i]);
		}
        DBG_ARND("\n");
	}
#endif

    typ_idx **map_all2as = malloc(narrs*sizeof(typ_idx *));
	for(i=0;i<narrs;++i){ map_all2as[i] = mapdims_inverse(arrays[i]->n,ndims,map_as2all[i]); }
#ifdef DEBUG_ARRAYND
	for(j=0;j<narrs;++j){
        DBG_ARND("arNdArgNarNsNintNidxRet1idxNarrNDblNIntNIdx_WMaps: map_all2as[%lld]",j);
		for(i=0;i<ndims;++i){
			DBG_ARND(" %lld",map_all2as[j][i]);
		}
        DBG_ARND("\n");
	}
#endif

    typ_idx **adims = malloc(narrs*sizeof *adims);
	for(i=0;i<narrs;++i){
        adims[i] = malloc(n_adims*sizeof **adims);
        for(k=0;k<n_adims;++k){
            adims[i][k] = -1;
        }
        for(k=0;k<n_adims;++k){
            for(j=0;j<arrays[i]->n;++j){
                if (map_as2all[i][j]==adim_all[k]){
                    adims[i][k] = j;
                    break;
                }
            }
        }
	}
#ifdef DEBUG_ARRAYND
	for(i=0;i<narrs;++i){
        DBG_ARND("arNdArgNarNsNintNidxRet1idxNarrNDblNIntNIdx_WMaps: adims[%lld]",i);
        for(k=0;k<n_adims;++k){
			DBG_ARND(" %2lld",adims[i][k]);
        }
        DBG_ARND("\n");
	}
#endif

    typ_idx **adim_tmp      = malloc(narrs*sizeof *adim_tmp);
    typ_idx *n_adims_per_arr= malloc(narrs*sizeof *n_adims_per_arr);
    for(i=0;i<narrs;++i){
        adim_tmp[i] = malloc(n_adims*sizeof(typ_idx));
        for(k=0,n_adims_per_arr[i]=0;k<n_adims;++k){
            if (adims[i][k] > -1){
                adim_tmp[i][n_adims_per_arr[i]] = adims[i][k];
                n_adims_per_arr[i]++;
            }
        }
    }

	typ_idx *c,*clens,*map_all2c,*map_c2all;
	arr OUT;
	if (ndims < n_adims){
        OUT = NullArray();
        for (i=0;i<nrarrs;++i){ *Rarr[i] = NullArray(); }
        for (i=0;i<nrdbls;++i){ *Rdbl[i] = NullArray(); }
        for (i=0;i<nrints;++i){ *Rint[i] = NullArray(); }
        for (i=0;i<nridxs;++i){ *Ridx[i] = NullArray(); }
    } else {
        map_all2c = init0((ndims),TYPIDX);
        map_c2all = init0((ndims-n_adims),TYPIDX);
		clens = initNdLoopCounterLengthsWMaps(ndims,n_adims,adim_all,all_len,map_all2c,map_c2all);
		c 	= init0(ndims-n_adims,TYPIDX);
        typ_idx **idxs = malloc(narrs*sizeof(typ_idx *));
        for (i=0;i<narrs;++i){
            idxs[i] = initNdIdxWMaps(c,arrays[i]->n,n_adims,adims[i],map_all2c,map_as2all[i]);
        }
        
		OUT	= ArrayFromList(ndims-n_adims,TYPIDX,clens);
	/*	copyMiss(&OUT,arrays[maxar]);   */

        for (i=0;i<nrarrs;++i){ *Rarr[i] = NullArray(); }
        for (i=0;i<nrdbls;++i){
            *Rdbl[i] = ArrayFromList(ndims-n_adims,DOUBLE,clens);
        /*  copyMiss(Rdbl[i],arrays[maxar]);    */
            fillArWithMiss(Rdbl[i]);
        }
        for (i=0;i<nrints;++i){
            *Rint[i] = ArrayFromList(ndims-n_adims,INT,clens);
        /*  copyMiss(Rint[i],arrays[maxar]);    */
            fillArWithMiss(Rint[i]);
        }
        for (i=0;i<nridxs;++i){
            *Ridx[i] = ArrayFromList(ndims-n_adims,TYPIDX,clens);
        /*  copyMiss(Ridx[i],arrays[maxar]);    */
            fillArWithMiss(Ridx[i]);
        }


        int narnds,ndbls2,nints2,nidxs2;

		j = 0; k = 0; l = 0; m = 0;
		arr   **arnd = malloc(narrs*sizeof(arr *));
		double *dblp = malloc((narrs+ndbls)*sizeof(double));
		int    *intp = malloc((narrs+nints)*sizeof(int));
		typ_idx*idxp = malloc((narrs+nidxs)*sizeof(typ_idx));
		double *dblp_miss = malloc((narrs+ndbls)*sizeof(double));
		int    *intp_miss = malloc((narrs+nints)*sizeof(int));
		typ_idx*idxp_miss = malloc((narrs+nidxs)*sizeof(typ_idx));
		for(i=0;i<narrs;++i){
			if (n_adims_per_arr[i]){
                arnd[j]  = malloc(sizeof(arr));
                *arnd[j] = NullArray();
				++j;
			} else {
                if (arrays[i]->typ == DOUBLE){
                    dblp_miss[k] = *(double *)getMiss(arrays[i]);
                    ++k;
                } else if (arrays[i]->typ == INT){
                    intp_miss[l] = *(int *)getMiss(arrays[i]);
                    ++l;
                } else if (arrays[i]->typ == TYPIDX){
                    idxp_miss[m] = *(typ_idx *)getMiss(arrays[i]);
                    ++m;
                } else {
                    fprintf(stderr,"arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_Loop: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                    exit(0);
                }
			}
		}
		for(i=0;i<ndbls;++i){
			dblp[k] = dbl_ptr[i];
            dblp_miss[k] = -999.0;
			++k;
		}
		for(i=0;i<nints;++i){
			intp[l] = int_ptr[i];
            intp_miss[l] = -999;
			++l;
		}
		for(i=0;i<nidxs;++i){
			idxp[m] = idx_ptr[i];
            idxp_miss[m] = -999;
			++m;
		}
		narnds = j;
		ndbls2 = k;
		nints2 = l;
		nidxs2 = m;

		arr    **arrpp = malloc(nrarrs*sizeof(arr *));
		for(i=0;i<nrarrs;++i){
            arrpp[i] = malloc(sizeof(arr));
		}
		double     **dblpp = malloc(nrdbls*sizeof(double *));
		double *dblpp_miss = malloc(nrdbls*sizeof(double));
		for(i=0;i<nrdbls;++i){
			dblpp_miss[i] = *(double *)getMiss(Rdbl[i]);
		}
		int     **intpp = malloc(nrints*sizeof(int *));
		int *intpp_miss = malloc(nrints*sizeof(int));
		for(i=0;i<nrints;++i){
			intpp_miss[i] = *(int *)getMiss(Rint[i]);
		}
		typ_idx     **idxpp = malloc(nridxs*sizeof(typ_idx *));
		typ_idx *idxpp_miss = malloc(nridxs*sizeof(typ_idx));
		for(i=0;i<nridxs;++i){
			idxpp_miss[i] = *(typ_idx *)getMiss(Ridx[i]);
		}

        input_args args=passInputArgs(narnds,ndbls2,nints2,nidxs2,nrarrs,nrdbls,nrints,nridxs
            ,arnd,dblp,intp,idxp,arrpp,dblpp,intpp,idxpp,dblp_miss,intp_miss,idxp_miss,dblpp_miss,intpp_miss,idxpp_miss,getMiss(&OUT));

		int *is_idx_new = malloc(narrs*sizeof(int));
        set_ints_to_val(narrs,is_idx_new,1);

        typ_idx **adim_rarr = malloc(nrarrs*sizeof(typ_idx *));
        for (i=0;i<nrarrs;++i){ adim_rarr[i] = NULL; }

		arNdArgNarNsNintNidxRet1idxNarrNDblNIntNIdx_Loop(fct,&OUT,arrays,dbl_ptr,int_ptr,idx_ptr,Rarr,Rdbl,Rint,Ridx,
            narrs,ndbls,nints,nidxs,nrarrs,nrdbls,nrints,nridxs,&args,
            ndims,map_c2all,map_all2as,n_adims,adim_all,adim_rarr,n_adims_per_arr,adim_tmp,idxs,is_idx_new,(typ_idx)0,c,clens,all_len);

        free(c);
		free(clens);
		free(map_all2c);
		free(map_c2all);
        for (i=0;i<nrarrs;++i){ free(adim_rarr[i]); }
        free(adim_rarr);
        for (i=0;i<narrs;++i){ free(idxs[i]); }
        free(idxs);

        free(is_idx_new);

		for (i=0;i<narnds;++i){
			freeAr(arnd[i]);
			free(arnd[i]);
		}
		for (i=0;i<nrarrs;++i){
			free(arrpp[i]);
		}
        freeInputArgs(&args);
	}

    for(i=0;i<narrs;++i){
        free(adims[i]);
        free(adim_tmp[i]);
        free(map_all2as[i]);
    }
    free(adims);
    free(adim_tmp);
    free(n_adims_per_arr);
    free(map_all2as);
	return OUT;
}

arr arNdArgNarNsNintNidxRet1idxNarrNDblNIntNIdx(fctArgsRidx fct
    ,int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs,
    arr **arrays,double *dbl_ptr,int *int_ptr,typ_idx *idx_ptr,arr **Rarr,arr **Rdbl,arr **Rint,arr **Ridx
    ,typ_idx n_adims,typ_idx *adims_in) {
	typ_idx i,ndims;
	typ_idx **map_as2all;
	typ_idx *all_len = mapdims_Nar(narrs,arrays,&ndims,&map_as2all);

	typ_idx maxn = -1,maxar = -1;
	for(i=0;i<narrs;++i){
		if (arrays[i]->n > maxn){
			maxn  = arrays[i]->n;
			maxar = i;
		}
	}

	if (maxn < n_adims){
		fprintf(stderr,"Error in arNdArgNarNsNintNidxRet1idxNarrNDblNIntNIdx: n_adims must be less than or equal to %lld! n_adims=%lld\n"
			,maxn,n_adims);
		exit(0);
	}

    typ_idx *adim_all = malloc(n_adims*sizeof(typ_idx));
    for(i=0;i<n_adims;++i){
        adim_all[i]= map_as2all[maxar][adims_in[i]];
    }

    arr OUT = arNdArgNarNsNintNidxRet1idxNarrNDblNIntNIdx_WMaps(fct,narrs,ndbls,nints,nidxs,nrarrs,nrdbls,nrints,nridxs,
        arrays,dbl_ptr,int_ptr,idx_ptr,Rarr,Rdbl,Rint,Ridx,n_adims,adim_all,ndims,all_len,map_as2all);
    
    for(i=0;i<narrs;++i){
        free(map_as2all[i]);
    }
	free(map_as2all);
	free(all_len);
	free(adim_all);
	return OUT;
}

arr arNdArgNarNsNintNidxRet1idxNarrNDblNIntNIdx_VArg(
    fctArgsRidx fct,typ_idx n_adims,typ_idx *adims_in,int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs,...){
	int i;

	arr   **arrays  = malloc(narrs *sizeof(arr *));
	double *dbl_ptr = malloc(ndbls *sizeof(double));
	int    *int_ptr = malloc(nints *sizeof(int));
	typ_idx*idx_ptr = malloc(nidxs *sizeof(typ_idx));
	arr   **Rarr    = malloc(nrarrs*sizeof(arr *));
	arr   **Rdbl    = malloc(nrdbls*sizeof(arr *));
	arr   **Rint    = malloc(nrints*sizeof(arr *));
	arr   **Ridx    = malloc(nridxs*sizeof(arr *));

	va_list arg_list;
	va_start(arg_list, nridxs);
	for (i=0;i<narrs;++i){
		arrays[i]  = va_arg(arg_list, arr *);
	}
	for (i=0;i<ndbls;++i){
		dbl_ptr[i] = va_arg(arg_list, double);
	}
	for (i=0;i<nints;++i){
		int_ptr[i] = va_arg(arg_list, int);
	}
	for (i=0;i<nidxs;++i){
		idx_ptr[i] = va_arg(arg_list, typ_idx);
	}
	for (i=0;i<nrarrs;++i){
		Rarr[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrdbls;++i){
		Rdbl[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrints;++i){
		Rint[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nridxs;++i){
		Ridx[i]   = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

    arr OUT = arNdArgNarNsNintNidxRet1idxNarrNDblNIntNIdx(fct,narrs,ndbls,nints,nidxs,nrarrs,nrdbls,nrints,nridxs,
        arrays,dbl_ptr,int_ptr,idx_ptr,Rarr,Rdbl,Rint,Ridx,n_adims,adims_in);

	free(arrays);
	free(dbl_ptr);
	free(int_ptr);
	free(idx_ptr);
	free(Rarr);
	free(Rdbl);
	free(Rint);
	free(Ridx);
	return OUT;
}



void arNdArgNarNsNintRet1intNarrNDblNInt_Loop(fctArgsRint fct,arr *restrict OUT,
    arr **arrays,arr **Rarr,arr **Rdbl,arr **Rint,
    int narrs,int nrarrs,int nrdbls,int nrints,input_args *args,
    typ_idx ndims,typ_idx *map_c2all,typ_idx **map_all2as,
    typ_idx n_adims,typ_idx *adim_all,typ_idx **adim_rarr,typ_idx *n_adims_per_arr,typ_idx **adims,
    typ_idx **idxs,int *is_idx_new,typ_idx dim,typ_idx *c,typ_idx *clens,typ_idx *all_len){
/*	This is a recursive n dimensional loop function	*/
	typ_idx i,j,k,l;

    DBG_ARND_LP("arNdArgNarNsNintRet1intNarrNDblNInt_Loop: dim=%lld\n",dim);
    typ_idx ncdims = ndims-n_adims;
	if (dim == ncdims){
		j = 0; k = 0; l = 0;
        typ_idx idim2;
		for(i=0;i<narrs;++i){
            idim2 = n_adims_per_arr[i];
            if (idim2){
                if (is_idx_new[i]){
                    is_idx_new[i] = 0;
                    freeAr(args->arrays[j]);
                    *args->arrays[j] = grabNdAr_NStride(arrays[i], idim2, adims[i], idxs[i]);
                }
                ++j;
            } else {
                if (arrays[i]->typ == DOUBLE){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->dblp[k] = cDBL(arrays[i],idxs[i]);
                    }
                    ++k;
                } else if (arrays[i]->typ == INT){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->intp[l] = cINTG(arrays[i],idxs[i]);
                    }
                    ++l;
                } else {
                    fprintf(stderr,"arNdArgNarNsNintRet1intNarrNDblNInt_Loop: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                    exit(0);
                }
            }
		}

        arr **arrpp = args->arrpp;
		for(i=0;i<nrarrs;++i){ *arrpp[i] = NullArray(); }
		for(i=0;i<nrdbls;++i){ args->dblpp[i] = address_of_c(Rdbl[i],c); }
		for(i=0;i<nrints;++i){ args->intpp[i] = address_of_c(Rint[i],c); }

        cINTG(OUT,c) = fct(args);

        /* Do the same thing for Rarr as was done with OUT! */
        for (i=0;i<nrarrs;++i){
            typ_idx *idx_rarr = NULL;
            typ_idx *len_rarr = NULL;
            if (Rarr[i]->tlen < 1){
                if (!isArNull(arrpp[i])){
                    typ_idx noutdims;
                    getOUTfromOUTnd2(arrpp[i],ncdims,ndims,n_adims,map_c2all,all_len,adim_all,c,clens,
                        &noutdims,&idx_rarr,&len_rarr,&adim_rarr[i]);
                    *Rarr[i]= ArrayFromList(noutdims,arrpp[i]->typ,len_rarr);
                    copyMiss(Rarr[i],arrays[0]);
                    fillArWithMiss(Rarr[i]);
                }
            } else {
                if (!isArNull(arrpp[i])){
                    idx_rarr = initNdIdx(c,    Rarr[i]->n,arrpp[i]->n,adim_rarr[i]);
                    len_rarr = initNdIdx(clens,Rarr[i]->n,arrpp[i]->n,adim_rarr[i]);
                    typ_idx j_adim;
                    int change_len=0;
                    for(j=0;j<arrpp[i]->n;++j){
                        j_adim = adim_rarr[i][j];
                        len_rarr[j_adim] = arrpp[i]->len[j];
                        /* Don't worry if new dim length is less than current length */
                        if (len_rarr[j_adim] > Rarr[i]->len[j_adim]){
                            change_len = 1;
                        }
                    }
                    if (change_len) { expandDims(Rarr[i],len_rarr); }
                }
            }
            if (!isArNull(arrpp[i])){
                assignPart2(Rarr[i],arrpp[i],adim_rarr[i],idx_rarr);
            }
            free(idx_rarr);
            free(len_rarr);
        }

		for (i=0;i<nrarrs;++i){
			freeAr(arrpp[i]);
		}
		return;
	} else {
		for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
#ifdef DEBUG_ARRAYND_LOOPS
			DBG_ARND_LP("arNdArgNarNsNintRet1intNarrNDblNInt_Loop: ");
			for(j=0;j<=dim;++j){
				DBG_ARND_LP("c[%lld]=%lld ",j,c[j]);
			}
			DBG_ARND_LP("\n");
#endif
            k = map_c2all[dim];
            l = c[dim];
            for (i=0;i<narrs;++i){
                j = map_all2as[i][k];
                if (j >= 0){
                    is_idx_new[i] = 1; /* This should prevent excessive recalculation of arrays */
                    idxs[i][j] = l;
                }
            }
            arNdArgNarNsNintRet1intNarrNDblNInt_Loop(fct,OUT,arrays,Rarr,Rdbl,Rint,
                narrs,nrarrs,nrdbls,nrints,args,
                ndims,map_c2all,map_all2as,n_adims,adim_all,adim_rarr,n_adims_per_arr,adims,idxs,is_idx_new,dim+1,c,clens,all_len);
		}
	}

	return;
}

arr arNdArgNarNsNintRet1intNarrNDblNInt_WMaps(fctArgsRint fct,int narrs,int ndbls,int nints,int nrarrs,int nrdbls,int nrints,
    arr **arrays,double *dbl_ptr,int *int_ptr,arr **Rarr,arr **Rdbl,arr **Rint,typ_idx n_adims,typ_idx *adim_all,typ_idx ndims,typ_idx *all_len,typ_idx **map_as2all) {
    DBG_ARND_ENTR;
	typ_idx i,j,k,l;

#ifdef DEBUG_ARRAYND
    DBG_ARND("arNdArgNarNsNintRet1intNarrNDblNInt_WMaps: all_len");
	for(i=0;i<ndims;++i){
		DBG_ARND(" %lld",all_len[i]);
	}
	DBG_ARND("\n");
	for(j=0;j<narrs;++j){
        DBG_ARND("arNdArgNarNsNintRet1intNarrNDblNInt_WMaps: map_as2all[%lld]",j);
		for(i=0;i<arrays[j]->n;++i){
			DBG_ARND(" %lld",map_as2all[j][i]);
		}
        DBG_ARND("\n");
	}
#endif

    typ_idx **map_all2as = malloc(narrs*sizeof(typ_idx *));
	for(i=0;i<narrs;++i){ map_all2as[i] = mapdims_inverse(arrays[i]->n,ndims,map_as2all[i]); }
#ifdef DEBUG_ARRAYND
	for(j=0;j<narrs;++j){
        DBG_ARND("arNdArgNarNsNintRet1intNarrNDblNInt_WMaps: map_all2as[%lld]",j);
		for(i=0;i<ndims;++i){
			DBG_ARND(" %lld",map_all2as[j][i]);
		}
        DBG_ARND("\n");
	}
#endif

    typ_idx **adims = malloc(narrs*sizeof *adims);
	for(i=0;i<narrs;++i){
        adims[i] = malloc(n_adims*sizeof **adims);
        for(k=0;k<n_adims;++k){
            adims[i][k] = -1;
        }
        for(k=0;k<n_adims;++k){
            for(j=0;j<arrays[i]->n;++j){
                if (map_as2all[i][j]==adim_all[k]){
                    adims[i][k] = j;
                    break;
                }
            }
        }
	}
#ifdef DEBUG_ARRAYND
	for(i=0;i<narrs;++i){
        DBG_ARND("arNdArgNarNsNintRet1intNarrNDblNInt_WMaps: adims[%lld]",i);
        for(k=0;k<n_adims;++k){
			DBG_ARND(" %2lld",adims[i][k]);
        }
        DBG_ARND("\n");
	}
#endif

    typ_idx **adim_tmp      = malloc(narrs*sizeof *adim_tmp);
    typ_idx *n_adims_per_arr= malloc(narrs*sizeof *n_adims_per_arr);
    for(i=0;i<narrs;++i){
        adim_tmp[i] = malloc(n_adims*sizeof(typ_idx));
        for(k=0,n_adims_per_arr[i]=0;k<n_adims;++k){
            if (adims[i][k] > -1){
                adim_tmp[i][n_adims_per_arr[i]] = adims[i][k];
                n_adims_per_arr[i]++;
            }
        }
    }

	typ_idx *c,*clens,*map_all2c,*map_c2all;
	arr OUT;
	if (ndims < n_adims){
        OUT = NullArray();
        for (i=0;i<nrarrs;++i){ *Rarr[i] = NullArray(); }
        for (i=0;i<nrdbls;++i){ *Rdbl[i] = NullArray(); }
        for (i=0;i<nrints;++i){ *Rint[i] = NullArray(); }
    } else {
        map_all2c = init0((ndims),TYPIDX);
        map_c2all = init0((ndims-n_adims),TYPIDX);
		clens = initNdLoopCounterLengthsWMaps(ndims,n_adims,adim_all,all_len,map_all2c,map_c2all);
		c 	= init0(ndims-n_adims,TYPIDX);
        typ_idx **idxs = malloc(narrs*sizeof(typ_idx *));
        for (i=0;i<narrs;++i){
            idxs[i] = initNdIdxWMaps(c,arrays[i]->n,n_adims,adims[i],map_all2c,map_as2all[i]);
        }
        
		OUT	= ArrayFromList(ndims-n_adims,INT,clens);
	/*	copyMiss(&OUT,arrays[maxar]);   */

        for (i=0;i<nrarrs;++i){ *Rarr[i] = NullArray(); }
        for (i=0;i<nrdbls;++i){
            *Rdbl[i] = ArrayFromList(ndims-n_adims,DOUBLE,clens);
        /*  copyMiss(Rdbl[i],arrays[maxar]);    */
            fillArWithMiss(Rdbl[i]);
        }
        for (i=0;i<nrints;++i){
            *Rint[i] = ArrayFromList(ndims-n_adims,INT,clens);
        /*  copyMiss(Rint[i],arrays[maxar]);    */
            fillArWithMiss(Rint[i]);
        }


		j = 0; k = 0; l = 0;
		arr   **arnd = malloc(narrs*sizeof(arr *));
		double *dblp = malloc((narrs+ndbls)*sizeof(double));
		int    *intp = malloc((narrs+nints)*sizeof(int));
		double *dblp_miss = malloc((narrs+ndbls)*sizeof(double));
		int    *intp_miss = malloc((narrs+nints)*sizeof(int));
		for(i=0;i<narrs;++i){
			if (n_adims_per_arr[i]){
                arnd[j]  = malloc(sizeof(arr));
                *arnd[j] = NullArray();
				++j;
			} else {
                if (arrays[i]->typ == DOUBLE){
                    dblp_miss[k] = *(double *)getMiss(arrays[i]);
                    ++k;
                } else if (arrays[i]->typ == INT){
                    intp_miss[l] = *(int *)getMiss(arrays[i]);
                    ++l;
                } else {
                    fprintf(stderr,"arNdArgNarNsNintRet1intNarrNDblNInt_WMaps: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                    exit(0);
                }
			}
		}
		for(i=0;i<ndbls;++i){
			dblp[k] = dbl_ptr[i];
            dblp_miss[k] = -999.0;
			++k;
		}
		for(i=0;i<nints;++i){
			intp[l] = int_ptr[i];
            intp_miss[l] = -999;
			++l;
		}
		int narnds = j;
		int ndbls2 = k;
		int nints2 = l;

		arr    **arrpp = malloc(nrarrs*sizeof(arr *));
		for(i=0;i<nrarrs;++i){
            arrpp[i] = malloc(sizeof(arr));
		}
		double     **dblpp = malloc(nrdbls*sizeof(double *));
		double *dblpp_miss = malloc(nrdbls*sizeof(double));
		for(i=0;i<nrdbls;++i){
			dblpp_miss[i] = *(double *)getMiss(Rdbl[i]);
		}
		int     **intpp = malloc(nrints*sizeof(int *));
		int *intpp_miss = malloc(nrints*sizeof(int));
		for(i=0;i<nrints;++i){
			intpp_miss[i] = *(int *)getMiss(Rint[i]);
		}

        input_args args=passInputArgs(narnds,ndbls2,nints2,0,nrarrs,nrdbls,nrints,0
            ,arnd,dblp,intp,NULL,arrpp,dblpp,intpp,NULL,dblp_miss,intp_miss,NULL,dblpp_miss,intpp_miss,NULL,getMiss(&OUT));

		int *is_idx_new = malloc(narrs*sizeof(int));
        set_ints_to_val(narrs,is_idx_new,1);

        typ_idx **adim_rarr = malloc(nrarrs*sizeof(typ_idx *));
        for (i=0;i<nrarrs;++i){ adim_rarr[i] = NULL; }

		arNdArgNarNsNintRet1intNarrNDblNInt_Loop(fct,&OUT,arrays,Rarr,Rdbl,Rint,
            narrs,nrarrs,nrdbls,nrints,&args,
            ndims,map_c2all,map_all2as,n_adims,adim_all,adim_rarr,n_adims_per_arr,adim_tmp,idxs,is_idx_new,(typ_idx)0,c,clens,all_len);

        free(c);
		free(clens);
		free(map_all2c);
		free(map_c2all);
        for (i=0;i<nrarrs;++i){ free(adim_rarr[i]); }
        free(adim_rarr);
        for (i=0;i<narrs;++i){ free(idxs[i]); }
        free(idxs);

        free(is_idx_new);

		for (i=0;i<narnds;++i){
			freeAr(arnd[i]);
			free(arnd[i]);
		}
		for (i=0;i<nrarrs;++i){
			free(arrpp[i]);
		}
        freeInputArgs(&args);
	}

    for(i=0;i<narrs;++i){
        free(adims[i]);
        free(adim_tmp[i]);
        free(map_all2as[i]);
    }
    free(adims);
    free(adim_tmp);
    free(n_adims_per_arr);
    free(map_all2as);
	return OUT;
}

arr arNdArgNarNsNintRet1intNarrNDblNInt(fctArgsRint fct,int narrs,int ndbls,int nints,int nrarrs,int nrdbls,int nrints,
    arr **arrays,double *dbl_ptr,int *int_ptr,arr **Rarr,arr **Rdbl,arr **Rint,typ_idx n_adims,typ_idx *adims_in) {
	typ_idx i,ndims;
	typ_idx **map_as2all;
	typ_idx *all_len = mapdims_Nar(narrs,arrays,&ndims,&map_as2all);

	typ_idx maxn = -1,maxar = -1;
	for(i=0;i<narrs;++i){
		if (arrays[i]->n > maxn){
			maxn  = arrays[i]->n;
			maxar = i;
		}
	}

	if (maxn < n_adims){
		fprintf(stderr,"Error in arNdArgNarNsNintRet1intNarrNDblNInt: n_adims must be less than or equal to %lld! n_adims=%lld\n"
			,maxn,n_adims);
		exit(0);
	}

    typ_idx *adim_all = malloc(n_adims*sizeof(typ_idx));
    for(i=0;i<n_adims;++i){
        adim_all[i]= map_as2all[maxar][adims_in[i]];
    }

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt_WMaps(fct,narrs,ndbls,nints,nrarrs,nrdbls,nrints,
        arrays,dbl_ptr,int_ptr,Rarr,Rdbl,Rint,n_adims,adim_all,ndims,all_len,map_as2all);
    
    for(i=0;i<narrs;++i){
        free(map_as2all[i]);
    }
	free(map_as2all);
	free(all_len);
	free(adim_all);
	return OUT;
}

arr arNdArgNarNsNintRet1intNarrNDblNInt_VArg(
    fctArgsRint fct,typ_idx n_adims,typ_idx *adims_in,int narrs,int ndbls,int nints,int nrarrs,int nrdbls,int nrints,...){
	int i;

	arr   **arrays  = malloc(narrs *sizeof(arr *));
	double *dbl_ptr = malloc(ndbls *sizeof(double));
	int    *int_ptr = malloc(nints *sizeof(int));
	arr   **Rarr    = malloc(nrarrs*sizeof(arr *));
	arr   **Rdbl    = malloc(nrdbls*sizeof(arr *));
	arr   **Rint    = malloc(nrints*sizeof(arr *));

	va_list arg_list;
	va_start(arg_list, nrints);
	for (i=0;i<narrs;++i){
		arrays[i]  = va_arg(arg_list, arr *);
	}
	for (i=0;i<ndbls;++i){
		dbl_ptr[i] = va_arg(arg_list, double);
	}
	for (i=0;i<nints;++i){
		int_ptr[i] = va_arg(arg_list, int);
	}
	for (i=0;i<nrarrs;++i){
		Rarr[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrdbls;++i){
		Rdbl[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrints;++i){
		Rint[i]   = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

    arr OUT = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,ndbls,nints,nrarrs,nrdbls,nrints,
        arrays,dbl_ptr,int_ptr,Rarr,Rdbl,Rint,n_adims,adims_in);

	free(arrays);
	free(dbl_ptr);
	free(int_ptr);
	free(Rarr);
	free(Rdbl);
	free(Rint);
	return OUT;
}



void arNdArgNarNsNintRetVoidNarrNDblNInt_Loop(fctArgsNoRet fct,
    arr **arrays,double *dbl_ptr,int *int_ptr,arr **Rarr,arr **Rdbl,arr **Rint,
    int narrs,int ndbls,int nints,int nrarrs,int nrdbls,int nrints,input_args *args,
    typ_idx ndims,typ_idx *map_c2all,typ_idx **map_all2as,
    typ_idx n_adims,typ_idx *adim_all,typ_idx **adim_rarr,typ_idx *n_adims_per_arr,typ_idx **adims,
    typ_idx **idxs,int *is_idx_new,typ_idx dim,typ_idx *c,typ_idx *clens,typ_idx *all_len){
/*	This is a recursive n dimensional loop function	*/
	typ_idx i,j,k,l;

    DBG_ARND_LP("arNdArgNarNsNintRetVoidNarrNDblNInt_Loop: dim=%lld\n",dim);
    typ_idx ncdims = ndims-n_adims;
	if (dim == ncdims){
		j = 0; k = 0; l = 0;
        typ_idx idim2;
		for(i=0;i<narrs;++i){
            idim2 = n_adims_per_arr[i];
            if (idim2){
                if (is_idx_new[i]){
                    is_idx_new[i] = 0;
                    freeAr(args->arrays[j]);
                    *args->arrays[j] = grabNdAr_NStride(arrays[i], idim2, adims[i], idxs[i]);
                }
                ++j;
            } else {
                if (arrays[i]->typ == DOUBLE){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->dblp[k] = cDBL(arrays[i],idxs[i]);
                    }
                    ++k;
                } else if (arrays[i]->typ == INT){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->intp[l] = cINTG(arrays[i],idxs[i]);
                    }
                    ++l;
                } else {
                    fprintf(stderr,"arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_Loop: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                    exit(0);
                }
            }
		}
        
        arr **arrpp = args->arrpp;
		for(i=0;i<nrarrs;++i){ *arrpp[i] = NullArray(); }
		for(i=0;i<nrdbls;++i){ args->dblpp[i] = address_of_c(Rdbl[i],c); }
		for(i=0;i<nrints;++i){ args->intpp[i] = address_of_c(Rint[i],c); }

        fct(args);

        /* Do the same thing for Rarr as was done with OUT! */
        for (i=0;i<nrarrs;++i){
            typ_idx *idx_rarr = NULL;
            typ_idx *len_rarr = NULL;
            if (Rarr[i]->tlen < 1){
                if (!isArNull(arrpp[i])){
                    typ_idx noutdims;
                    getOUTfromOUTnd2(arrpp[i],ncdims,ndims,n_adims,map_c2all,all_len,adim_all,c,clens,
                        &noutdims,&idx_rarr,&len_rarr,&adim_rarr[i]);
                    *Rarr[i]= ArrayFromList(noutdims,arrpp[i]->typ,len_rarr);
                    copyMiss(Rarr[i],arrays[0]);
                    fillArWithMiss(Rarr[i]);
                }
            } else {
                if (!isArNull(arrpp[i])){
                    idx_rarr = initNdIdx(c,    Rarr[i]->n,arrpp[i]->n,adim_rarr[i]);
                    len_rarr = initNdIdx(clens,Rarr[i]->n,arrpp[i]->n,adim_rarr[i]);
                    typ_idx j_adim;
                    int change_len=0;
                    for(j=0;j<arrpp[i]->n;++j){
                        j_adim = adim_rarr[i][j];
                        len_rarr[j_adim] = arrpp[i]->len[j];
                        /* Don't worry if new dim length is less than current length */
                        if (len_rarr[j_adim] > Rarr[i]->len[j_adim]){
                            change_len = 1;
                        }
                    }
                    if (change_len) { expandDims(Rarr[i],len_rarr); }
                }
            }
            if (!isArNull(arrpp[i])){
                assignPart2(Rarr[i],arrpp[i],adim_rarr[i],idx_rarr);
            }
            free(idx_rarr);
            free(len_rarr);
        }

		for (i=0;i<nrarrs;++i){
			freeAr(arrpp[i]);
		}
		return;
	} else {
		for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
#ifdef DEBUG_ARRAYND_LOOPS
			DBG_ARND_LP("arNdArgNarNsNintRetVoidNarrNDblNInt_Loop: ");
			for(j=0;j<=dim;++j){
				DBG_ARND_LP("c[%lld]=%lld ",j,c[j]);
			}
			DBG_ARND_LP("\n");
#endif
            k = map_c2all[dim];
            l = c[dim];
            for (i=0;i<narrs;++i){
                j = map_all2as[i][k];
                if (j >= 0){
                    is_idx_new[i] = 1; /* This should prevent excessive recalculation of arrays */
                    idxs[i][j] = l;
                }
            }
            arNdArgNarNsNintRetVoidNarrNDblNInt_Loop(fct,arrays,dbl_ptr,int_ptr,Rarr,Rdbl,Rint,
                narrs,ndbls,nints,nrarrs,nrdbls,nrints,args,
                ndims,map_c2all,map_all2as,n_adims,adim_all,adim_rarr,n_adims_per_arr,adims,idxs,is_idx_new,dim+1,c,clens,all_len);
		}
	}

	return;
}

void arNdArgNarNsNintRetVoidNarrNDblNInt_WMaps(fctArgsNoRet fct,int narrs,int ndbls,int nints,int nrarrs,int nrdbls,int nrints,
    arr **arrays,double *dbl_ptr,int *int_ptr,arr **Rarr,arr **Rdbl,arr **Rint,typ_idx n_adims,typ_idx *adim_all,typ_idx ndims,typ_idx *all_len,typ_idx **map_as2all) {
    DBG_ARND_ENTR;
	typ_idx i,j,k,l;

#ifdef DEBUG_ARRAYND
    DBG_ARND("arNdArgNarNsNintRetVoidNarrNDblNInt_WMaps: all_len");
	for(i=0;i<ndims;++i){
		DBG_ARND(" %lld",all_len[i]);
	}
	DBG_ARND("\n");
	for(j=0;j<narrs;++j){
        DBG_ARND("arNdArgNarNsNintRetVoidNarrNDblNInt_WMaps: map_as2all[%lld]",j);
		for(i=0;i<arrays[j]->n;++i){
			DBG_ARND(" %lld",map_as2all[j][i]);
		}
        DBG_ARND("\n");
	}
#endif

    typ_idx **map_all2as = malloc(narrs*sizeof(typ_idx *));
	for(i=0;i<narrs;++i){ map_all2as[i] = mapdims_inverse(arrays[i]->n,ndims,map_as2all[i]); }
#ifdef DEBUG_ARRAYND
	for(j=0;j<narrs;++j){
        DBG_ARND("arNdArgNarNsNintRetVoidNarrNDblNInt_WMaps: map_all2as[%lld]",j);
		for(i=0;i<ndims;++i){
			DBG_ARND(" %lld",map_all2as[j][i]);
		}
        DBG_ARND("\n");
	}
#endif

    typ_idx **adims = malloc(narrs*sizeof *adims);
	for(i=0;i<narrs;++i){
        adims[i] = malloc(n_adims*sizeof **adims);
        for(k=0;k<n_adims;++k){
            adims[i][k] = -1;
        }
        for(k=0;k<n_adims;++k){
            for(j=0;j<arrays[i]->n;++j){
                if (map_as2all[i][j]==adim_all[k]){
                    adims[i][k] = j;
                    break;
                }
            }
        }
	}
#ifdef DEBUG_ARRAYND
	for(i=0;i<narrs;++i){
        DBG_ARND("arNdArgNarNsNintRetVoidNarrNDblNInt_WMaps: adims[%lld]",i);
        for(k=0;k<n_adims;++k){
			DBG_ARND(" %2lld",adims[i][k]);
        }
        DBG_ARND("\n");
	}
#endif

    typ_idx **adim_tmp      = malloc(narrs*sizeof *adim_tmp);
    typ_idx *n_adims_per_arr= malloc(narrs*sizeof *n_adims_per_arr);
    for(i=0;i<narrs;++i){
        adim_tmp[i] = malloc(n_adims*sizeof(typ_idx));
        for(k=0,n_adims_per_arr[i]=0;k<n_adims;++k){
            if (adims[i][k] > -1){
                adim_tmp[i][n_adims_per_arr[i]] = adims[i][k];
                n_adims_per_arr[i]++;
            }
        }
    }

	typ_idx *c,*clens,*map_all2c,*map_c2all;
	if (ndims < n_adims){
        for (i=0;i<nrarrs;++i){ *Rarr[i] = NullArray(); }
        for (i=0;i<nrdbls;++i){ *Rdbl[i] = NullArray(); }
        for (i=0;i<nrints;++i){ *Rint[i] = NullArray(); }
    } else {
        map_all2c = init0((ndims),TYPIDX);
        map_c2all = init0((ndims-n_adims),TYPIDX);
		clens = initNdLoopCounterLengthsWMaps(ndims,n_adims,adim_all,all_len,map_all2c,map_c2all);
		c 	= init0(ndims-n_adims,TYPIDX);
        typ_idx **idxs = malloc(narrs*sizeof(typ_idx *));
        for (i=0;i<narrs;++i){
            idxs[i] = initNdIdxWMaps(c,arrays[i]->n,n_adims,adims[i],map_all2c,map_as2all[i]);
        }
        
        for (i=0;i<nrarrs;++i){ *Rarr[i] = NullArray(); }
        for (i=0;i<nrdbls;++i){
            *Rdbl[i] = ArrayFromList(ndims-n_adims,DOUBLE,clens);
        /*  copyMiss(Rdbl[i],arrays[maxar]);    */
            fillArWithMiss(Rdbl[i]);
        }
        for (i=0;i<nrints;++i){
            *Rint[i] = ArrayFromList(ndims-n_adims,INT,clens);
        /*  copyMiss(Rint[i],arrays[maxar]);    */
            fillArWithMiss(Rint[i]);
        }


        int narnds,ndbls2,nints2;

		j = 0; k = 0; l = 0;
		arr   **arnd = malloc(narrs*sizeof(arr *));
		double *dblp = malloc((narrs+ndbls)*sizeof(double));
		int    *intp = malloc((narrs+nints)*sizeof(int));
		double *dblp_miss = malloc((narrs+ndbls)*sizeof(double));
		int    *intp_miss = malloc((narrs+nints)*sizeof(int));
		for(i=0;i<narrs;++i){
			if (n_adims_per_arr[i]){
                arnd[j]  = malloc(sizeof(arr));
                *arnd[j] = NullArray();
				++j;
			} else {
                if (arrays[i]->typ == DOUBLE){
                    dblp_miss[k] = *(double *)getMiss(arrays[i]);
                    ++k;
                } else if (arrays[i]->typ == INT){
                    intp_miss[l] = *(int *)getMiss(arrays[i]);
                    ++l;
                } else {
                    fprintf(stderr,"arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_Loop: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                    exit(0);
                }
			}
		}
		for(i=0;i<ndbls;++i){
			dblp[k] = dbl_ptr[i];
            dblp_miss[k] = -999.0;
			++k;
		}
		for(i=0;i<nints;++i){
			intp[l] = int_ptr[i];
            intp_miss[l] = -999;
			++l;
		}
		narnds = j;
		ndbls2 = k;
		nints2 = l;

		arr    **arrpp = malloc(nrarrs*sizeof(arr *));
		for(i=0;i<nrarrs;++i){
            arrpp[i] = malloc(sizeof(arr));
		}
		double     **dblpp = malloc(nrdbls*sizeof(double *));
		double *dblpp_miss = malloc(nrdbls*sizeof(double));
		for(i=0;i<nrdbls;++i){
			dblpp_miss[i] = *(double *)getMiss(Rdbl[i]);
		}
		int     **intpp = malloc(nrints*sizeof(int *));
		int *intpp_miss = malloc(nrints*sizeof(int));
		for(i=0;i<nrints;++i){
			intpp_miss[i] = *(int *)getMiss(Rint[i]);
		}

        input_args args=passInputArgs(narnds,ndbls2,nints2,0,nrarrs,nrdbls,nrints,0
            ,arnd,dblp,intp,NULL,arrpp,dblpp,intpp,NULL,dblp_miss,intp_miss,NULL,dblpp_miss,intpp_miss,NULL,NULL);

		int *is_idx_new = malloc(narrs*sizeof(int));
        set_ints_to_val(narrs,is_idx_new,1);

        typ_idx **adim_rarr = malloc(nrarrs*sizeof(typ_idx *));
        for (i=0;i<nrarrs;++i){ adim_rarr[i] = NULL; }

		arNdArgNarNsNintRetVoidNarrNDblNInt_Loop(fct,arrays,dbl_ptr,int_ptr,Rarr,Rdbl,Rint,
            narrs,ndbls,nints,nrarrs,nrdbls,nrints,&args,
            ndims,map_c2all,map_all2as,n_adims,adim_all,adim_rarr,n_adims_per_arr,adim_tmp,idxs,is_idx_new,(typ_idx)0,c,clens,all_len);

        free(c);
		free(clens);
		free(map_all2c);
		free(map_c2all);
        for (i=0;i<nrarrs;++i){ free(adim_rarr[i]); }
        free(adim_rarr);
        for (i=0;i<narrs;++i){ free(idxs[i]); }
        free(idxs);

        free(is_idx_new);

		for (i=0;i<narnds;++i){
			freeAr(arnd[i]);
			free(arnd[i]);
		}
		for (i=0;i<nrarrs;++i){
			free(arrpp[i]);
		}
        freeInputArgs(&args);
	}

    for(i=0;i<narrs;++i){
        free(adims[i]);
        free(adim_tmp[i]);
        free(map_all2as[i]);
    }
    free(adims);
    free(adim_tmp);
    free(n_adims_per_arr);
    free(map_all2as);
	return;
}

void arNdArgNarNsNintRetVoidNarrNDblNInt(fctArgsNoRet fct,int narrs,int ndbls,int nints,int nrarrs,int nrdbls,int nrints,
    arr **arrays,double *dbl_ptr,int *int_ptr,arr **Rarr,arr **Rdbl,arr **Rint,typ_idx n_adims,typ_idx *adims_in) {
	typ_idx i,ndims;
	typ_idx **map_as2all;
	typ_idx *all_len = mapdims_Nar(narrs,arrays,&ndims,&map_as2all);

	typ_idx maxn = -1,maxar = -1;
	for(i=0;i<narrs;++i){
		if (arrays[i]->n > maxn){
			maxn  = arrays[i]->n;
			maxar = i;
		}
	}

	if (maxn < n_adims){
		fprintf(stderr,"Error in arNdArgNarNsNintRetVoidNarrNDblNInt: n_adims must be less than or equal to %lld! n_adims=%lld\n"
			,maxn,n_adims);
		exit(0);
	}

    typ_idx *adim_all = malloc(n_adims*sizeof(typ_idx));
    for(i=0;i<n_adims;++i){
        adim_all[i]= map_as2all[maxar][adims_in[i]];
    }

    arNdArgNarNsNintRetVoidNarrNDblNInt_WMaps(fct,narrs,ndbls,nints,nrarrs,nrdbls,nrints,
        arrays,dbl_ptr,int_ptr,Rarr,Rdbl,Rint,n_adims,adim_all,ndims,all_len,map_as2all);
    
    for(i=0;i<narrs;++i){
        free(map_as2all[i]);
    }
	free(map_as2all);
	free(all_len);
	free(adim_all);
	return;
}

void arNdArgNarNsNintRetVoidNarrNDblNInt_VArg(
    fctArgsNoRet fct,typ_idx n_adims,typ_idx *adims_in,int narrs,int ndbls,int nints,int nrarrs,int nrdbls,int nrints,...){
	int i;

	arr   **arrays  = malloc(narrs *sizeof(arr *));
	double *dbl_ptr = malloc(ndbls *sizeof(double));
	int    *int_ptr = malloc(nints *sizeof(int));
	arr   **Rarr    = malloc(nrarrs*sizeof(arr *));
	arr   **Rdbl    = malloc(nrdbls*sizeof(arr *));
	arr   **Rint    = malloc(nrints*sizeof(arr *));

	va_list arg_list;
	va_start(arg_list, nrints);
	for (i=0;i<narrs;++i){
		arrays[i]  = va_arg(arg_list, arr *);
	}
	for (i=0;i<ndbls;++i){
		dbl_ptr[i] = va_arg(arg_list, double);
	}
	for (i=0;i<nints;++i){
		int_ptr[i] = va_arg(arg_list, int);
	}
	for (i=0;i<nrarrs;++i){
		Rarr[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrdbls;++i){
		Rdbl[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrints;++i){
		Rint[i]   = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

    arNdArgNarNsNintRetVoidNarrNDblNInt(fct,narrs,ndbls,nints,nrarrs,nrdbls,nrints,
        arrays,dbl_ptr,int_ptr,Rarr,Rdbl,Rint,n_adims,adims_in);

	free(arrays);
	free(dbl_ptr);
	free(int_ptr);
	free(Rarr);
	free(Rdbl);
	free(Rint);
	return;
}



void arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_Loop(fctArgsRidx fct,
    arr **arrays,double *dbl_ptr,int *int_ptr,typ_idx *idx_ptr,arr **Rarr,arr **Rdbl,arr **Rint,arr **Ridx,
    int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs,input_args *args,
    typ_idx ndims,typ_idx *map_c2all,typ_idx **map_all2as,
    typ_idx n_adims,typ_idx *adim_all,typ_idx **adim_rarr,typ_idx *n_adims_per_arr,typ_idx **adims,
    typ_idx **idxs,int *is_idx_new,typ_idx dim,typ_idx *c,typ_idx *clens,typ_idx *all_len){
/*	This is a recursive n dimensional loop function	*/
	typ_idx i,j,k,l,m;

    DBG_ARND_LP("arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_Loop: dim=%lld\n",dim);
    typ_idx ncdims = ndims-n_adims;
	if (dim == ncdims){
		j = 0; k = 0; l = 0; m = 0;
        typ_idx idim2;
		for(i=0;i<narrs;++i){
            idim2 = n_adims_per_arr[i];
            if (idim2){
                if (is_idx_new[i]){
                    is_idx_new[i] = 0;
                    freeAr(args->arrays[j]);
                    *args->arrays[j] = grabNdAr_NStride(arrays[i], idim2, adims[i], idxs[i]);
                }
                ++j;
            } else {
                if (arrays[i]->typ == DOUBLE){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->dblp[k] = cDBL(arrays[i],idxs[i]);
                    }
                    ++k;
                } else if (arrays[i]->typ == INT){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->intp[l] = cINTG(arrays[i],idxs[i]);
                    }
                    ++l;
                } else if (arrays[i]->typ == TYPIDX){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->idxp[m] = cIDX(arrays[i],idxs[i]);
                    }
                    ++m;
                } else {
                    fprintf(stderr,"arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_Loop: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                    exit(0);
                }
            }
		}
        
        arr **arrpp = args->arrpp;
		for(i=0;i<nrarrs;++i){ *arrpp[i] = NullArray(); }
		for(i=0;i<nrdbls;++i){ args->dblpp[i] = address_of_c(Rdbl[i],c); }
		for(i=0;i<nrints;++i){ args->intpp[i] = address_of_c(Rint[i],c); }
		for(i=0;i<nridxs;++i){ args->idxpp[i] = address_of_c(Ridx[i],c); }

        fct(args);

        /* Do the same thing for Rarr as was done with OUT! */
        for (i=0;i<nrarrs;++i){
            typ_idx *idx_rarr = NULL;
            typ_idx *len_rarr = NULL;
            if (Rarr[i]->tlen < 1){
                if (!isArNull(arrpp[i])){
                    typ_idx noutdims;
                    getOUTfromOUTnd2(arrpp[i],ncdims,ndims,n_adims,map_c2all,all_len,adim_all,c,clens,
                        &noutdims,&idx_rarr,&len_rarr,&adim_rarr[i]);
                    *Rarr[i]= ArrayFromList(noutdims,arrpp[i]->typ,len_rarr);
                    copyMiss(Rarr[i],arrays[0]);
                    fillArWithMiss(Rarr[i]);
                }
            } else {
                if (!isArNull(arrpp[i])){
                    idx_rarr = initNdIdx(c,    Rarr[i]->n,arrpp[i]->n,adim_rarr[i]);
                    len_rarr = initNdIdx(clens,Rarr[i]->n,arrpp[i]->n,adim_rarr[i]);
                    typ_idx j_adim;
                    int change_len=0;
                    for(j=0;j<arrpp[i]->n;++j){
                        j_adim = adim_rarr[i][j];
                        len_rarr[j_adim] = arrpp[i]->len[j];
                        /* Don't worry if new dim length is less than current length */
                        if (len_rarr[j_adim] > Rarr[i]->len[j_adim]){
                            change_len = 1;
                        }
                    }
                    if (change_len) { expandDims(Rarr[i],len_rarr); }
                }
            }
            if (!isArNull(arrpp[i])){
                assignPart2(Rarr[i],arrpp[i],adim_rarr[i],idx_rarr);
            }
            free(idx_rarr);
            free(len_rarr);
        }

		for (i=0;i<nrarrs;++i){
			freeAr(arrpp[i]);
		}
		return;
	} else {
		for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
#ifdef DEBUG_ARRAYND_LOOPS
			DBG_ARND_LP("arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_Loop: ");
			for(j=0;j<=dim;++j){
				DBG_ARND_LP("c[%lld]=%lld ",j,c[j]);
			}
			DBG_ARND_LP("\n");
#endif
            k = map_c2all[dim];
            l = c[dim];
            for (i=0;i<narrs;++i){
                j = map_all2as[i][k];
                if (j >= 0){
                    is_idx_new[i] = 1; /* This should prevent excessive recalculation of arrays */
                    idxs[i][j] = l;
                }
            }
            arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_Loop(fct,arrays,dbl_ptr,int_ptr,idx_ptr,Rarr,Rdbl,Rint,Ridx,
                narrs,ndbls,nints,nidxs,nrarrs,nrdbls,nrints,nridxs,args,
                ndims,map_c2all,map_all2as,n_adims,adim_all,adim_rarr,n_adims_per_arr,adims,idxs,is_idx_new,dim+1,c,clens,all_len);
		}
	}

	return;
}

void arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_WMaps(fctArgsRidx fct
    ,int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs,
    arr **arrays,double *dbl_ptr,int *int_ptr,typ_idx *idx_ptr,arr **Rarr,arr **Rdbl,arr **Rint,arr **Ridx
    ,typ_idx n_adims,typ_idx *adim_all,typ_idx ndims,typ_idx *all_len,typ_idx **map_as2all) {
    DBG_ARND_ENTR;
	typ_idx i,j,k,l,m;

#ifdef DEBUG_ARRAYND
    DBG_ARND("arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_WMaps: all_len");
	for(i=0;i<ndims;++i){
		DBG_ARND(" %lld",all_len[i]);
	}
	DBG_ARND("\n");
	for(j=0;j<narrs;++j){
        DBG_ARND("arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_WMaps: map_as2all[%lld]",j);
		for(i=0;i<arrays[j]->n;++i){
			DBG_ARND(" %2lld",map_as2all[j][i]);
		}
        DBG_ARND("\n");
	}
#endif

    typ_idx **map_all2as = malloc(narrs*sizeof(typ_idx *));
	for(i=0;i<narrs;++i){ map_all2as[i] = mapdims_inverse(arrays[i]->n,ndims,map_as2all[i]); }
#ifdef DEBUG_ARRAYND
	for(j=0;j<narrs;++j){
        DBG_ARND("arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_WMaps: map_all2as[%lld]",j);
		for(i=0;i<ndims;++i){
			DBG_ARND(" %2lld",map_all2as[j][i]);
		}
        DBG_ARND("\n");
	}
#endif

    typ_idx **adims = malloc(narrs*sizeof *adims);
	for(i=0;i<narrs;++i){
        adims[i] = malloc(n_adims*sizeof **adims);
        for(k=0;k<n_adims;++k){
            adims[i][k] = -1;
        }
        for(k=0;k<n_adims;++k){
            for(j=0;j<arrays[i]->n;++j){
                if (map_as2all[i][j]==adim_all[k]){
                    adims[i][k] = j;
                    break;
                }
            }
        }
	}
#ifdef DEBUG_ARRAYND
	for(i=0;i<narrs;++i){
        DBG_ARND("arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_WMaps: adims[%lld]",i);
        for(k=0;k<n_adims;++k){
			DBG_ARND(" %2lld",adims[i][k]);
        }
        DBG_ARND("\n");
	}
#endif

    typ_idx **adim_tmp      = malloc(narrs*sizeof *adim_tmp);
    typ_idx *n_adims_per_arr= malloc(narrs*sizeof *n_adims_per_arr);
    for(i=0;i<narrs;++i){
        adim_tmp[i] = malloc(n_adims*sizeof(typ_idx));
        for(k=0,n_adims_per_arr[i]=0;k<n_adims;++k){
            if (adims[i][k] > -1){
                adim_tmp[i][n_adims_per_arr[i]] = adims[i][k];
                n_adims_per_arr[i]++;
            }
        }
    }

DBG_ARND("arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_WMaps: 1\n");
	typ_idx *c,*clens,*map_all2c,*map_c2all;
	if (ndims < n_adims){
DBG_ARND("arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_WMaps: 1.1\n");
        for (i=0;i<nrarrs;++i){ *Rarr[i] = NullArray(); }
        for (i=0;i<nrdbls;++i){ *Rdbl[i] = NullArray(); }
        for (i=0;i<nrints;++i){ *Rint[i] = NullArray(); }
        for (i=0;i<nridxs;++i){ *Ridx[i] = NullArray(); }
    } else {
        map_all2c = init0((ndims),TYPIDX);
        map_c2all = init0((ndims-n_adims),TYPIDX);
		clens = initNdLoopCounterLengthsWMaps(ndims,n_adims,adim_all,all_len,map_all2c,map_c2all);

		c 	= init0(ndims-n_adims,TYPIDX);
        typ_idx **idxs = malloc(narrs*sizeof(typ_idx *));
        for (i=0;i<narrs;++i){
            idxs[i] = initNdIdxWMaps(c,arrays[i]->n,n_adims,adims[i],map_all2c,map_as2all[i]);
        }
        
        for (i=0;i<nrarrs;++i){ *Rarr[i] = NullArray(); }
        for (i=0;i<nrdbls;++i){
            *Rdbl[i] = ArrayFromList(ndims-n_adims,DOUBLE,clens);
        /*  copyMiss(Rdbl[i],arrays[maxar]);    */
            fillArWithMiss(Rdbl[i]);
        }
        for (i=0;i<nrints;++i){
            *Rint[i] = ArrayFromList(ndims-n_adims,INT,clens);
        /*  copyMiss(Rint[i],arrays[maxar]);    */
            fillArWithMiss(Rint[i]);
        }
        for (i=0;i<nridxs;++i){
            *Ridx[i] = ArrayFromList(ndims-n_adims,TYPIDX,clens);
        /*  copyMiss(Ridx[i],arrays[maxar]);    */
            fillArWithMiss(Ridx[i]);
        }


        int narnds,ndbls2,nints2,nidxs2;

		j = 0; k = 0; l = 0; m = 0;
		arr   **arnd = malloc(narrs*sizeof(arr *));
		double *dblp = malloc((narrs+ndbls)*sizeof(double));
		int    *intp = malloc((narrs+nints)*sizeof(int));
		typ_idx*idxp = malloc((narrs+nidxs)*sizeof(typ_idx));
		double *dblp_miss = malloc((narrs+ndbls)*sizeof(double));
		int    *intp_miss = malloc((narrs+nints)*sizeof(int));
		typ_idx*idxp_miss = malloc((narrs+nidxs)*sizeof(typ_idx));
		for(i=0;i<narrs;++i){
			if (n_adims_per_arr[i]){
                arnd[j]  = malloc(sizeof(arr));
                *arnd[j] = NullArray();
				++j;
			} else {
                if (arrays[i]->typ == DOUBLE){
                    dblp_miss[k] = *(double *)getMiss(arrays[i]);
                    ++k;
                } else if (arrays[i]->typ == INT){
                    intp_miss[l] = *(int *)getMiss(arrays[i]);
                    ++l;
                } else if (arrays[i]->typ == TYPIDX){
                    idxp_miss[m] = *(typ_idx *)getMiss(arrays[i]);
                    ++m;
                } else {
                    fprintf(stderr,"arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_Loop: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                    exit(0);
                }
			}
		}
		for(i=0;i<ndbls;++i){
			dblp[k] = dbl_ptr[i];
            dblp_miss[k] = -999.0;
			++k;
		}
		for(i=0;i<nints;++i){
			intp[l] = int_ptr[i];
            intp_miss[l] = -999;
			++l;
		}
		for(i=0;i<nidxs;++i){
			idxp[m] = idx_ptr[i];
            idxp_miss[m] = -999;
			++m;
		}
		narnds = j;
		ndbls2 = k;
		nints2 = l;
		nidxs2 = m;

		arr    **arrpp = malloc(nrarrs*sizeof(arr *));
		for(i=0;i<nrarrs;++i){
            arrpp[i] = malloc(sizeof(arr));
		}
		double     **dblpp = malloc(nrdbls*sizeof(double *));
		double *dblpp_miss = malloc(nrdbls*sizeof(double));
		for(i=0;i<nrdbls;++i){
			dblpp_miss[i] = *(double *)getMiss(Rdbl[i]);
		}
		int     **intpp = malloc(nrints*sizeof(int *));
		int *intpp_miss = malloc(nrints*sizeof(int));
		for(i=0;i<nrints;++i){
			intpp_miss[i] = *(int *)getMiss(Rint[i]);
		}
		typ_idx     **idxpp = malloc(nridxs*sizeof(typ_idx *));
		typ_idx *idxpp_miss = malloc(nridxs*sizeof(typ_idx));
		for(i=0;i<nridxs;++i){
			idxpp_miss[i] = *(typ_idx *)getMiss(Ridx[i]);
		}

        input_args args=passInputArgs(narnds,ndbls2,nints2,nidxs2,nrarrs,nrdbls,nrints,nridxs
            ,arnd,dblp,intp,idxp,arrpp,dblpp,intpp,idxpp,dblp_miss,intp_miss,idxp_miss,dblpp_miss,intpp_miss,idxpp_miss,NULL);

		int *is_idx_new = malloc(narrs*sizeof(int));
        set_ints_to_val(narrs,is_idx_new,1);

        typ_idx **adim_rarr = malloc(nrarrs*sizeof(typ_idx *));
        for (i=0;i<nrarrs;++i){ adim_rarr[i] = NULL; }

DBG_ARND("arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_WMaps: 1.2.1\n");
		arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_Loop(fct,arrays,dbl_ptr,int_ptr,idx_ptr,Rarr,Rdbl,Rint,Ridx,
            narrs,ndbls,nints,nidxs,nrarrs,nrdbls,nrints,nridxs,&args,
            ndims,map_c2all,map_all2as,n_adims,adim_all,adim_rarr,n_adims_per_arr,adim_tmp,idxs,is_idx_new,(typ_idx)0,c,clens,all_len);

DBG_ARND("arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_WMaps: 1.2.2\n");
        free(c);
		free(clens);
		free(map_all2c);
		free(map_c2all);
        for (i=0;i<nrarrs;++i){ free(adim_rarr[i]); }
        free(adim_rarr);
        for (i=0;i<narrs;++i){ free(idxs[i]); }
        free(idxs);

        free(is_idx_new);

		for (i=0;i<narnds;++i){
			freeAr(arnd[i]);
			free(arnd[i]);
		}
		for (i=0;i<nrarrs;++i){
			free(arrpp[i]);
		}
        freeInputArgs(&args);
	}

DBG_ARND("arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_WMaps: 2\n");
    for(i=0;i<narrs;++i){
        free(adims[i]);
        free(adim_tmp[i]);
        free(map_all2as[i]);
    }
DBG_ARND("arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_WMaps: 3\n");
    free(adims);
    free(adim_tmp);
    free(n_adims_per_arr);
    free(map_all2as);
	return;
}

void arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx(fctArgsRidx fct
    ,int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs,
    arr **arrays,double *dbl_ptr,int *int_ptr,typ_idx *idx_ptr,arr **Rarr,arr **Rdbl,arr **Rint,arr **Ridx
    ,typ_idx n_adims,typ_idx *adims_in) {
	typ_idx i,ndims;
	typ_idx **map_as2all;
	typ_idx *all_len = mapdims_Nar(narrs,arrays,&ndims,&map_as2all);

	typ_idx maxn = -1,maxar = -1;
	for(i=0;i<narrs;++i){
		if (arrays[i]->n > maxn){
			maxn  = arrays[i]->n;
			maxar = i;
		}
	}

	if (maxn < n_adims){
		fprintf(stderr,"Error in arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx: n_adims must be less than or equal to %lld! n_adims=%lld\n"
			,maxn,n_adims);
		exit(0);
	}

    typ_idx *adim_all = malloc(n_adims*sizeof(typ_idx));
    for(i=0;i<n_adims;++i){
        adim_all[i]= map_as2all[maxar][adims_in[i]];
    }

    arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_WMaps(fct,narrs,ndbls,nints,nidxs,nrarrs,nrdbls,nrints,nridxs,
        arrays,dbl_ptr,int_ptr,idx_ptr,Rarr,Rdbl,Rint,Ridx,n_adims,adim_all,ndims,all_len,map_as2all);
    
    for(i=0;i<narrs;++i){
        free(map_as2all[i]);
    }
	free(map_as2all);
	free(all_len);
	free(adim_all);
	return;
}

void arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_VArg(
    fctArgsRidx fct,typ_idx n_adims,typ_idx *adims_in,int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs,...){
	int i;

	arr   **arrays  = malloc(narrs *sizeof(arr *));
	double *dbl_ptr = malloc(ndbls *sizeof(double));
	int    *int_ptr = malloc(nints *sizeof(int));
	typ_idx*idx_ptr = malloc(nidxs *sizeof(typ_idx));
	arr   **Rarr    = malloc(nrarrs*sizeof(arr *));
	arr   **Rdbl    = malloc(nrdbls*sizeof(arr *));
	arr   **Rint    = malloc(nrints*sizeof(arr *));
	arr   **Ridx    = malloc(nridxs*sizeof(arr *));

	va_list arg_list;
	va_start(arg_list, nridxs);
	for (i=0;i<narrs;++i){
		arrays[i]  = va_arg(arg_list, arr *);
	}
	for (i=0;i<ndbls;++i){
		dbl_ptr[i] = va_arg(arg_list, double);
	}
	for (i=0;i<nints;++i){
		int_ptr[i] = va_arg(arg_list, int);
	}
	for (i=0;i<nidxs;++i){
		idx_ptr[i] = va_arg(arg_list, typ_idx);
	}
	for (i=0;i<nrarrs;++i){
		Rarr[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrdbls;++i){
		Rdbl[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrints;++i){
		Rint[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nridxs;++i){
		Ridx[i]   = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

    arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx(fct,narrs,ndbls,nints,nidxs,nrarrs,nrdbls,nrints,nridxs,
        arrays,dbl_ptr,int_ptr,idx_ptr,Rarr,Rdbl,Rint,Ridx,n_adims,adims_in);

	free(arrays);
	free(dbl_ptr);
	free(int_ptr);
	free(idx_ptr);
	free(Rarr);
	free(Rdbl);
	free(Rint);
	free(Ridx);
	return;
}



/*
#define DEBUG_ARRAYND_ENTRY
#define DBG_ARND_ENTR fprintf (stderr, "%s, %s, line %d\n", __FILE__, __func__, __LINE__)

#define DEBUG_ARRAYND
#define DBG_ARND(...) fprintf (stderr, __VA_ARGS__)

#define DEBUG_ARRAYND_LOOPS
#define DBG_ARND_LP(...) fprintf (stderr, __VA_ARGS__)
*/
void arNdArgNarNsNintRet1arrNarrNDblNInt_Loop(fctArgsRarr fct,arr *OUT,
    arr **arrays,double *dbl_ptr,int *int_ptr,arr **Rarr,arr **Rdbl,arr **Rint,
    int narrs,int ndbls,int nints,int nrarrs,int nrdbls,int nrints,input_args *args,
    typ_idx ndims,typ_idx *map_c2all,typ_idx **map_all2as,
    typ_idx n_adims,typ_idx *adim_all,typ_idx **adim_out,typ_idx **adim_rarr,typ_idx *n_adims_per_arr,typ_idx **adims,
    typ_idx **idxs,int *is_idx_new,typ_idx dim,typ_idx *c,typ_idx *clens,typ_idx *all_len){
/*	This is a recursive n dimensional loop function	*/
	typ_idx i,j,k,l;

    DBG_ARND_LP("arNdArgNarNsNintRet1arrNarrNDblNInt_Loop: dim=%lld\n",dim);
    typ_idx ncdims = ndims-n_adims;
	if (dim == ncdims){
		j = 0; k = 0; l = 0;
        typ_idx idim2;
    DBG_ARND_LP("arNdArgNarNsNintRet1arrNarrNDblNInt_Loop: 1\n");
		for(i=0;i<narrs;++i){
            idim2 = n_adims_per_arr[i];
            if (idim2){
                if (is_idx_new[i]){
                    is_idx_new[i] = 0;
                    freeAr(args->arrays[j]);
                    *args->arrays[j] = grabNdAr_NStride(arrays[i], idim2, adims[i], idxs[i]);
                }
                ++j;
            } else {
                if (arrays[i]->typ == DOUBLE){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->dblp[k] = cDBL(arrays[i],idxs[i]);
                    }
                    ++k;
                } else if (arrays[i]->typ == INT){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->intp[l] = cINTG(arrays[i],idxs[i]);
                    }
                    ++l;
                } else {
                    fprintf(stderr,"arNdArgNarNsNintRet1arrNarrNDblNInt_Loop: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                    exit(0);
                }
            }
		}
        
    DBG_ARND_LP("arNdArgNarNsNintRet1arrNarrNDblNInt_Loop: 2\n");
        arr **arrpp = args->arrpp;
		for(i=0;i<nrarrs;++i){ *arrpp[i] = NullArray(); }
		for(i=0;i<nrdbls;++i){ args->dblpp[i] = address_of_c(Rdbl[i],c); }
		for(i=0;i<nrints;++i){ args->intpp[i] = address_of_c(Rint[i],c); }

        arr OUTnd = fct(args);
#ifdef DEBUG_ARRAYND_LOOPS
        printArrayInfoWHdr(stderr,&OUTnd,"arNdArgNarNsNintRet1arrNarrNDblNInt_Loop: OUTnd - ");
#endif

    DBG_ARND_LP("arNdArgNarNsNintRet1arrNarrNDblNInt_Loop: 3\n");
        typ_idx *idx_out = NULL;
        typ_idx *len_out = NULL;
        if (isArNull(OUT)){
            if (!isArNull(&OUTnd)){
                typ_idx noutdims;
                getOUTfromOUTnd2(&OUTnd,ncdims,ndims,n_adims,map_c2all,all_len,adim_all,c,clens,&noutdims,&idx_out,&len_out,adim_out);
                *OUT = ArrayFromList(noutdims,OUTnd.typ,len_out);
                copyMiss(OUT,arrays[0]);
                fillArWithMiss(OUT);
            }
        } else {
            if (!isArNull(&OUTnd)){
                idx_out = initNdIdx(c,    OUT->n,OUTnd.n,*adim_out);
                len_out = initNdIdx(clens,OUT->n,OUTnd.n,*adim_out);
                typ_idx j_adim;
                int change_len=0;
                for(j=0;j<OUTnd.n;++j){
                    j_adim = (*adim_out)[j];
                    len_out[j_adim] = OUTnd.len[j];
                    /* Don't worry if new dim length is less than current length */
                    if (len_out[j_adim] > OUT->len[j_adim]){
                        change_len = 1;
                    }
                }
                if (change_len) { expandDims(OUT,len_out); }
            }
        }
    DBG_ARND_LP("arNdArgNarNsNintRet1arrNarrNDblNInt_Loop: 4\n");
        if (!isArNull(&OUTnd)){
            assignPart2(OUT,&OUTnd,*adim_out,idx_out);
        }
        free(idx_out);
        free(len_out);
        
    DBG_ARND_LP("arNdArgNarNsNintRet1arrNarrNDblNInt_Loop: 5\n");
        /* Do the same thing for Rarr as was done with OUT! */
        for (i=0;i<nrarrs;++i){
            typ_idx *idx_rarr = NULL;
            typ_idx *len_rarr = NULL;
            if (isArNull(Rarr[i])){
                if (!isArNull(arrpp[i])){
                    typ_idx noutdims;
                    getOUTfromOUTnd2(arrpp[i],ncdims,ndims,n_adims,map_c2all,all_len,adim_all,c,clens,
                        &noutdims,&idx_rarr,&len_rarr,&adim_rarr[i]);
                    *Rarr[i]= ArrayFromList(noutdims,arrpp[i]->typ,len_rarr);
                    copyMiss(Rarr[i],arrays[0]);
                    fillArWithMiss(Rarr[i]);
                }
            } else {
                if (!isArNull(arrpp[i])){
                    idx_rarr = initNdIdx(c,    Rarr[i]->n,arrpp[i]->n,adim_rarr[i]);
                    len_rarr = initNdIdx(clens,Rarr[i]->n,arrpp[i]->n,adim_rarr[i]);
                    typ_idx j_adim;
                    int change_len=0;
                    for(j=0;j<arrpp[i]->n;++j){
                        j_adim = adim_rarr[i][j];
                        len_rarr[j_adim] = arrpp[i]->len[j];
                        /* Don't worry if new dim length is less than current length */
                        if (len_rarr[j_adim] > Rarr[i]->len[j_adim]){
                            change_len = 1;
                        }
                    }
                    if (change_len) { expandDims(Rarr[i],len_rarr); }
                }
            }
            if (!isArNull(arrpp[i])){
                assignPart2(Rarr[i],arrpp[i],adim_rarr[i],idx_rarr);
            }
            free(idx_rarr);
            free(len_rarr);
        }

    DBG_ARND_LP("arNdArgNarNsNintRet1arrNarrNDblNInt_Loop: 6\n");
		freeAr(&OUTnd);
		for (i=0;i<nrarrs;++i){
			freeAr(arrpp[i]);
		}
    DBG_ARND_LP("arNdArgNarNsNintRet1arrNarrNDblNInt_Loop: 7\n");
		return;
	} else {
		for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
#ifdef DEBUG_ARRAYND_LOOPS
			DBG_ARND_LP("arNdArgNarNsNintRet1arrNarrNDblNInt_Loop: ");
			for(j=0;j<=dim;++j){
				DBG_ARND_LP("c[%lld]=%lld ",j,c[j]);
			}
			DBG_ARND_LP("\n");
#endif
            k = map_c2all[dim];
            l = c[dim];
            for (i=0;i<narrs;++i){
                j = map_all2as[i][k];
                if (j >= 0){
                    is_idx_new[i] = 1; /* This should prevent excessive recalculation of arrays */
                    idxs[i][j] = l;
                }
            }
            arNdArgNarNsNintRet1arrNarrNDblNInt_Loop(fct,OUT,arrays,dbl_ptr,int_ptr,Rarr,Rdbl,Rint,
                narrs,ndbls,nints,nrarrs,nrdbls,nrints,args,
                ndims,map_c2all,map_all2as,n_adims,adim_all,adim_out,adim_rarr,n_adims_per_arr,adims,idxs,is_idx_new,dim+1,c,clens,all_len);
		}
	}

	return;
}

arr arNdArgNarNsNintRet1arrNarrNDblNInt_WMaps(fctArgsRarr fct,int narrs,int ndbls,int nints,int nrarrs,int nrdbls,int nrints,
    arr **arrays,double *dbl_ptr,int *int_ptr,arr **Rarr,arr **Rdbl,arr **Rint,typ_idx n_adims,typ_idx *adim_all,typ_idx ndims,typ_idx *all_len,typ_idx **map_as2all) {
    DBG_ARND_ENTR;
	typ_idx i,j,k,l;
    /*
	for(j=0;j<narrs;++j){ printArrayInfoWHdr(stderr,arrays[j],"arNdArgNarNsNintRet1arrNarrNDblNInt_WMaps: arrays[%lld] - ",(int)j); }
	*/

#ifdef DEBUG_ARRAYND
    DBG_ARND("arNdArgNarNsNintRet1arrNarrNDblNInt_WMaps: all_len");
	for(i=0;i<ndims;++i){
		DBG_ARND(" %lld",all_len[i]);
	}
	DBG_ARND("\n");
	for(j=0;j<narrs;++j){
        DBG_ARND("arNdArgNarNsNintRet1arrNarrNDblNInt_WMaps: map_as2all[%lld]",j);
		for(i=0;i<arrays[j]->n;++i){
			DBG_ARND(" %lld",map_as2all[j][i]);
		}
        DBG_ARND("\n");
	}
#endif

    typ_idx **map_all2as = malloc(narrs*sizeof(typ_idx *));
	for(i=0;i<narrs;++i){ map_all2as[i] = mapdims_inverse(arrays[i]->n,ndims,map_as2all[i]); }
#ifdef DEBUG_ARRAYND
	for(j=0;j<narrs;++j){
        DBG_ARND("arNdArgNarNsNintRet1arrNarrNDblNInt_WMaps: map_all2as[%lld]",j);
		for(i=0;i<ndims;++i){
			DBG_ARND(" %lld",map_all2as[j][i]);
		}
        DBG_ARND("\n");
	}
#endif

    typ_idx **adims = malloc(narrs*sizeof *adims);
	for(i=0;i<narrs;++i){
        adims[i] = malloc(n_adims*sizeof **adims);
        for(k=0;k<n_adims;++k){
            adims[i][k] = -1;
        }
        for(k=0;k<n_adims;++k){
            for(j=0;j<arrays[i]->n;++j){
                if (map_as2all[i][j]==adim_all[k]){
                    adims[i][k] = j;
                    break;
                }
            }
        }
	}
#ifdef DEBUG_ARRAYND
	for(i=0;i<narrs;++i){
        DBG_ARND("arNdArgNarNsNintRet1arrNarrNDblNInt_WMaps: adims[%lld]",i);
        for(k=0;k<n_adims;++k){
			DBG_ARND(" %2lld",adims[i][k]);
        }
        DBG_ARND("\n");
	}
#endif

    typ_idx **adim_tmp      = malloc(narrs*sizeof *adim_tmp);
    typ_idx *n_adims_per_arr= malloc(narrs*sizeof *n_adims_per_arr);
    for(i=0;i<narrs;++i){
        adim_tmp[i] = malloc(n_adims*sizeof(typ_idx));
        for(k=0,n_adims_per_arr[i]=0;k<n_adims;++k){
            if (adims[i][k] > -1){
                adim_tmp[i][n_adims_per_arr[i]] = adims[i][k];
                n_adims_per_arr[i]++;
            }
        }
    }

	typ_idx *c,*clens,*map_all2c,*map_c2all;
	arr OUT = NullArray();
	if (ndims < n_adims){
        for (i=0;i<nrarrs;++i){ *Rarr[i] = NullArray(); }
        for (i=0;i<nrdbls;++i){ *Rdbl[i] = NullArray(); }
        for (i=0;i<nrints;++i){ *Rint[i] = NullArray(); }
    } else {
        map_all2c = init0((ndims),TYPIDX);
        map_c2all = init0((ndims-n_adims),TYPIDX);
		clens = initNdLoopCounterLengthsWMaps(ndims,n_adims,adim_all,all_len,map_all2c,map_c2all);
		c 	= init0(ndims-n_adims,TYPIDX);
        typ_idx **idxs = malloc(narrs*sizeof(typ_idx *));
        for (i=0;i<narrs;++i){
            idxs[i] = initNdIdxWMaps(c,arrays[i]->n,n_adims,adims[i],map_all2c,map_as2all[i]);
        }
        
        for (i=0;i<nrarrs;++i){ *Rarr[i] = NullArray(); }
        for (i=0;i<nrdbls;++i){
            *Rdbl[i] = ArrayFromList(ndims-n_adims,DOUBLE,clens);
        /*  copyMiss(Rdbl[i],arrays[maxar]);    */
            fillArWithMiss(Rdbl[i]);
        }
        for (i=0;i<nrints;++i){
            *Rint[i] = ArrayFromList(ndims-n_adims,INT,clens);
        /*  copyMiss(Rint[i],arrays[maxar]);    */
            fillArWithMiss(Rint[i]);
        }


        int narnds,ndbls2,nints2;

		j = 0; k = 0; l = 0;
		arr   **arnd = malloc(narrs*sizeof(arr *));
		double *dblp = malloc((narrs+ndbls)*sizeof(double));
		int    *intp = malloc((narrs+nints)*sizeof(int));
		double *dblp_miss = malloc((narrs+ndbls)*sizeof(double));
		int    *intp_miss = malloc((narrs+nints)*sizeof(int));
		for(i=0;i<narrs;++i){
			if (n_adims_per_arr[i]){
                arnd[j]  = malloc(sizeof(arr));
                *arnd[j] = NullArray();
				++j;
			} else {
                if (arrays[i]->typ == DOUBLE){
                    dblp_miss[k] = *(double *)getMiss(arrays[i]);
                    ++k;
                } else if (arrays[i]->typ == INT){
                    intp_miss[l] = *(int *)getMiss(arrays[i]);
                    ++l;
                } else {
                    fprintf(stderr,"arNdArgNarNsNintRet1arrNarrNDblNInt_WMaps: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                    exit(0);
                }
			}
		}
		for(i=0;i<ndbls;++i){
			dblp[k] = dbl_ptr[i];
            dblp_miss[k] = -999.0;
			++k;
		}
		for(i=0;i<nints;++i){
			intp[l] = int_ptr[i];
            intp_miss[l] = -999;
			++l;
		}
		narnds = j;
		ndbls2 = k;
		nints2 = l;

		arr    **arrpp = malloc(nrarrs*sizeof(arr *));
		for(i=0;i<nrarrs;++i){
            arrpp[i] = malloc(sizeof(arr));
		}
		double     **dblpp = malloc(nrdbls*sizeof(double *));
		double *dblpp_miss = malloc(nrdbls*sizeof(double));
		for(i=0;i<nrdbls;++i){
			dblpp_miss[i] = *(double *)getMiss(Rdbl[i]);
		}
		int     **intpp = malloc(nrints*sizeof(int *));
		int *intpp_miss = malloc(nrints*sizeof(int));
		for(i=0;i<nrints;++i){
			intpp_miss[i] = *(int *)getMiss(Rint[i]);
		}

        arr OUTnd = NullArray();
        input_args args=passInputArgs(narnds,ndbls2,nints2,0,nrarrs,nrdbls,nrints,0
            ,arnd,dblp,intp,NULL,arrpp,dblpp,intpp,NULL,dblp_miss,intp_miss,NULL,dblpp_miss,intpp_miss,NULL,&OUTnd);

		int *is_idx_new = malloc(narrs*sizeof(int));
        set_ints_to_val(narrs,is_idx_new,1);

        typ_idx *adim_out = NULL;
        typ_idx **adim_rarr = malloc(nrarrs*sizeof(typ_idx *));
        for (i=0;i<nrarrs;++i){ adim_rarr[i] = NULL; }

		arNdArgNarNsNintRet1arrNarrNDblNInt_Loop(fct,&OUT,arrays,dbl_ptr,int_ptr,Rarr,Rdbl,Rint,
            narrs,ndbls,nints,nrarrs,nrdbls,nrints,&args,
            ndims,map_c2all,map_all2as,n_adims,adim_all,&adim_out,adim_rarr,n_adims_per_arr,adim_tmp,idxs,is_idx_new,(typ_idx)0,c,clens,all_len);
            
#ifdef DEBUG_ARRAYND
        printArrayInfoWHdr(stderr,&OUT,"arNdArgNarNsNintRet1arrNarrNDblNInt_WMaps: OUT\n");
#endif

        free(c);
		free(clens);
		free(map_all2c);
		free(map_c2all);
        free(adim_out);
        for (i=0;i<nrarrs;++i){ free(adim_rarr[i]); }
        free(adim_rarr);
        for (i=0;i<narrs;++i){ free(idxs[i]); }
		free(idxs);

        free(is_idx_new);

		for (i=0;i<narnds;++i){
			freeAr(arnd[i]);
			free(arnd[i]);
		}
		for (i=0;i<nrarrs;++i){
			free(arrpp[i]);
		}
        freeInputArgs(&args);
	}

    for(i=0;i<narrs;++i){
        free(adims[i]);
        free(adim_tmp[i]);
        free(map_all2as[i]);
    }
    free(adims);
    free(adim_tmp);
    free(n_adims_per_arr);
    free(map_all2as);
	return OUT;
}
/*
#undef DEBUG_ARRAYND_ENTRY
#define DBG_ARND_ENTR ((void)0)

#undef DEBUG_ARRAYND
#define DBG_ARND(...) ((void)0)

#undef DEBUG_ARRAYND_LOOPS
#define DBG_ARND_LP(...) ((void)0)
*/
arr arNdArgNarNsNintRet1arrNarrNDblNInt(fctArgsRarr fct,int narrs,int ndbls,int nints,int nrarrs,int nrdbls,int nrints,
    arr **arrays,double *dbl_ptr,int *int_ptr,arr **Rarr,arr **Rdbl,arr **Rint,typ_idx n_adims,typ_idx *adims_in) {
	typ_idx i,ndims;
	typ_idx **map_as2all;
	typ_idx *all_len = mapdims_Nar(narrs,arrays,&ndims,&map_as2all);

	typ_idx maxn = -1,maxar = -1;
	for(i=0;i<narrs;++i){
		if (arrays[i]->n > maxn){
			maxn  = arrays[i]->n;
			maxar = i;
		}
	}

	if (maxn < n_adims){
		fprintf(stderr,"Error in arNdArgNarNsNintRet1arrNarrNDblNInt: n_adims must be less than or equal to %lld! n_adims=%lld\n"
			,maxn,n_adims);
		exit(0);
	}

    typ_idx *adim_all = malloc(n_adims*sizeof(typ_idx));
    for(i=0;i<n_adims;++i){
        adim_all[i]= map_as2all[maxar][adims_in[i]];
    }

    arr OUT = arNdArgNarNsNintRet1arrNarrNDblNInt_WMaps(fct,narrs,ndbls,nints,nrarrs,nrdbls,nrints,
        arrays,dbl_ptr,int_ptr,Rarr,Rdbl,Rint,n_adims,adim_all,ndims,all_len,map_as2all);

    for(i=0;i<narrs;++i){
        free(map_as2all[i]);
    }
	free(map_as2all);
	free(all_len);
	free(adim_all);
	return OUT;
}

arr arNdArgNarNsNintRet1arrNarrNDblNInt_VArg(
    fctArgsRarr fct,typ_idx n_adims,typ_idx *adims_in,int narrs,int ndbls,int nints,int nrarrs,int nrdbls,int nrints,...){
	int i;

	arr   **arrays  = malloc(narrs *sizeof(arr *));
	double *dbl_ptr = malloc(ndbls *sizeof(double));
	int    *int_ptr = malloc(nints *sizeof(int));
	arr   **Rarr    = malloc(nrarrs*sizeof(arr *));
	arr   **Rdbl    = malloc(nrdbls*sizeof(arr *));
	arr   **Rint    = malloc(nrints*sizeof(arr *));

	va_list arg_list;
	va_start(arg_list, nrints);
	for (i=0;i<narrs;++i){
		arrays[i]  = va_arg(arg_list, arr *);
	}
	for (i=0;i<ndbls;++i){
		dbl_ptr[i] = va_arg(arg_list, double);
	}
	for (i=0;i<nints;++i){
		int_ptr[i] = va_arg(arg_list, int);
	}
	for (i=0;i<nrarrs;++i){
		Rarr[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrdbls;++i){
		Rdbl[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrints;++i){
		Rint[i]   = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

    arr OUT = arNdArgNarNsNintRet1arrNarrNDblNInt(fct,narrs,ndbls,nints,nrarrs,nrdbls,nrints,
        arrays,dbl_ptr,int_ptr,Rarr,Rdbl,Rint,n_adims,adims_in);

	free(arrays);
	free(dbl_ptr);
	free(int_ptr);
	free(Rarr);
	free(Rdbl);
	free(Rint);
	return OUT;
}

arr arNdArg1(fctArgsRarr fct, arr *restrict X, typ_idx n_adims, typ_idx *adims) {
	int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

    arr OUT = arNdArgNarNsNintRet1arrNarrNDblNInt(fct,narrs,0,0,0,0,0,arrays,NULL,NULL,NULL,NULL,NULL,n_adims,adims);
	free(arrays);
	return OUT;
}

arr arNdArg2(fctArgsRarr fct, arr *restrict X, arr *restrict Y, typ_idx n_adims, typ_idx *adims) {
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

    arr OUT = arNdArgNarNsNintRet1arrNarrNDblNInt(fct,narrs,0,0,0,0,0,arrays,NULL,NULL,NULL,NULL,NULL,n_adims,adims);
	free(arrays);
	return OUT;
}

arr arNdArg3(fctArgsRarr fct, arr *restrict X, arr *restrict Y, arr *restrict Z, typ_idx n_adims, typ_idx *adims) {
	int narrs = 3;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

    arr OUT = arNdArgNarNsNintRet1arrNarrNDblNInt(fct,narrs,0,0,0,0,0,arrays,NULL,NULL,NULL,NULL,NULL,n_adims,adims);
	free(arrays);
	return OUT;
}

arr arNdArg4(fctArgsRarr fct, arr *restrict X, arr *restrict Y, arr *restrict Z, arr *restrict T, typ_idx n_adims, typ_idx *adims) {
	int narrs = 4;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;
	arrays[3] = T;

    arr OUT = arNdArgNarNsNintRet1arrNarrNDblNInt(fct,narrs,0,0,0,0,0,arrays,NULL,NULL,NULL,NULL,NULL,n_adims,adims);
	free(arrays);
	return OUT;
}

arr arNdArg1ar1s(fctArgsRarr fct, arr *restrict X, double xdbl, typ_idx n_adims, typ_idx *adims) {
	int narrs = 1;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;

	int ndbls = 1;
	double *dbl_ptr = dbls(ndbls, xdbl);

    arr OUT = arNdArgNarNsNintRet1arrNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL,NULL,n_adims,adims);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr arNdArg2ar1s(fctArgsRarr fct, arr *restrict X, arr *restrict Y, double xdbl, typ_idx n_adims, typ_idx *adims) {
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	int ndbls = 1;
	double *dbl_ptr = dbls(ndbls, xdbl);

    arr OUT = arNdArgNarNsNintRet1arrNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL,NULL,n_adims,adims);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr arNdArg2ar2s(fctArgsRarr fct, arr *restrict X, arr *restrict Y, double xdbl, double ydbl, typ_idx n_adims, typ_idx *adims) {
	int narrs = 2;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;

	int ndbls = 2;
	double *dbl_ptr = dbls(ndbls, xdbl, ydbl);

    arr OUT = arNdArgNarNsNintRet1arrNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL,NULL,n_adims,adims);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr arNdArg3ar1s(fctArgsRarr fct, arr *restrict X, arr *restrict Y, arr *restrict Z, double xdbl, typ_idx n_adims, typ_idx *adims) {
	int narrs = 3;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

	int ndbls = 1;
	double *dbl_ptr = dbls(ndbls, xdbl);

    arr OUT = arNdArgNarNsNintRet1arrNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL,NULL,n_adims,adims);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}

arr arNdArg3ar2s(fctArgsRarr fct, arr *restrict X, arr *restrict Y, arr *restrict Z, double xdbl, double ydbl, typ_idx n_adims, typ_idx *adims) {
	int narrs = 3;
	arr **arrays = malloc(narrs*sizeof(arr *));
	arrays[0] = X;
	arrays[1] = Y;
	arrays[2] = Z;

	int ndbls = 2;
	double *dbl_ptr = dbls(ndbls, xdbl, ydbl);

    arr OUT = arNdArgNarNsNintRet1arrNarrNDblNInt(fct,narrs,ndbls,0,0,0,0,arrays,dbl_ptr,NULL,NULL,NULL,NULL,n_adims,adims);
	free(arrays);
	free(dbl_ptr);
	return OUT;
}



void arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx_Loop(fctArgsRarr fct,arr *OUT,
    arr **arrays,double *dbl_ptr,int *int_ptr,typ_idx *idx_ptr,arr **Rarr,arr **Rdbl,arr **Rint,arr **Ridx,
    int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs,input_args *args,
    typ_idx ndims,typ_idx *map_c2all,typ_idx **map_all2as,
    typ_idx n_adims,typ_idx *adim_all,typ_idx **adim_out,typ_idx **adim_rarr,typ_idx *n_adims_per_arr,typ_idx **adims,
    typ_idx **idxs,int *is_idx_new,typ_idx dim,typ_idx *c,typ_idx *clens,typ_idx *all_len){
/*	This is a recursive n dimensional loop function	*/
	typ_idx i,j,k,l,m;

    DBG_ARND_LP("arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx_Loop: dim=%lld\n",dim);
    typ_idx ncdims = ndims-n_adims;
	if (dim == ncdims){
		j = 0; k = 0; l = 0; m = 0;
        typ_idx idim2;
		for(i=0;i<narrs;++i){
            idim2 = n_adims_per_arr[i];
            if (idim2){
                if (is_idx_new[i]){
                    is_idx_new[i] = 0;
                    freeAr(args->arrays[j]);
                    *args->arrays[j] = grabNdAr_NStride(arrays[i], idim2, adims[i], idxs[i]);
                }
                ++j;
            } else {
                if (arrays[i]->typ == DOUBLE){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->dblp[k] = cDBL(arrays[i],idxs[i]);
                    }
                    ++k;
                } else if (arrays[i]->typ == INT){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->intp[l] = cINTG(arrays[i],idxs[i]);
                    }
                    ++l;
                } else if (arrays[i]->typ == TYPIDX){
                    if (is_idx_new[i]){
                        is_idx_new[i] = 0;
                        args->idxp[m] = cIDX(arrays[i],idxs[i]);
                    }
                    ++m;
                } else {
                    fprintf(stderr,"arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx_Loop: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                    exit(0);
                }
            }
		}
        
        arr **arrpp = args->arrpp;
		for(i=0;i<nrarrs;++i){ *arrpp[i] = NullArray(); }
		for(i=0;i<nrdbls;++i){ args->dblpp[i] = address_of_c(Rdbl[i],c); }
		for(i=0;i<nrints;++i){ args->intpp[i] = address_of_c(Rint[i],c); }
		for(i=0;i<nridxs;++i){ args->idxpp[i] = address_of_c(Ridx[i],c); }

        arr OUTnd = fct(args);

        typ_idx *idx_out = NULL;
        typ_idx *len_out = NULL;
        if (OUT->tlen < 1){
            if (OUTnd.tlen > 0){
                typ_idx noutdims;
                getOUTfromOUTnd2(&OUTnd,ncdims,ndims,n_adims,map_c2all,all_len,adim_all,c,clens,&noutdims,&idx_out,&len_out,adim_out);
                *OUT = ArrayFromList(noutdims,OUTnd.typ,len_out);
                copyMiss(OUT,arrays[0]);
                fillArWithMiss(OUT);
            }
        } else {
            if (OUTnd.tlen > 0){
                idx_out = initNdIdx(c,    OUT->n,OUTnd.n,*adim_out);
                len_out = initNdIdx(clens,OUT->n,OUTnd.n,*adim_out);
                typ_idx j_adim;
                int change_len=0;
                for(j=0;j<OUTnd.n;++j){
                    j_adim = (*adim_out)[j];
                    len_out[j_adim] = OUTnd.len[j];
                    /* Don't worry if new dim length is less than current length */
                    if (len_out[j_adim] > OUT->len[j_adim]){
                        change_len = 1;
                    }
                }
                if (change_len) { expandDims(OUT,len_out); }
            }
        }
        if (OUTnd.tlen > 0){
            assignPart2(OUT,&OUTnd,*adim_out,idx_out);
        }
        free(idx_out);
        free(len_out);
        
        /* Do the same thing for Rarr as was done with OUT! */
        for (i=0;i<nrarrs;++i){
            typ_idx *idx_rarr = NULL;
            typ_idx *len_rarr = NULL;
            if (Rarr[i]->tlen < 1){
                if (!isArNull(arrpp[i])){
                    typ_idx noutdims;
                    getOUTfromOUTnd2(arrpp[i],ncdims,ndims,n_adims,map_c2all,all_len,adim_all,c,clens,
                        &noutdims,&idx_rarr,&len_rarr,&adim_rarr[i]);
                    *Rarr[i]= ArrayFromList(noutdims,arrpp[i]->typ,len_rarr);
                    copyMiss(Rarr[i],arrays[0]);
                    fillArWithMiss(Rarr[i]);
                }
            } else {
                if (!isArNull(arrpp[i])){
                    idx_rarr = initNdIdx(c,    Rarr[i]->n,arrpp[i]->n,adim_rarr[i]);
                    len_rarr = initNdIdx(clens,Rarr[i]->n,arrpp[i]->n,adim_rarr[i]);
                    typ_idx j_adim;
                    int change_len=0;
                    for(j=0;j<arrpp[i]->n;++j){
                        j_adim = adim_rarr[i][j];
                        len_rarr[j_adim] = arrpp[i]->len[j];
                        /* Don't worry if new dim length is less than current length */
                        if (len_rarr[j_adim] > Rarr[i]->len[j_adim]){
                            change_len = 1;
                        }
                    }
                    if (change_len) { expandDims(Rarr[i],len_rarr); }
                }
            }
            if (!isArNull(arrpp[i])){
                assignPart2(Rarr[i],arrpp[i],adim_rarr[i],idx_rarr);
            }
            free(idx_rarr);
            free(len_rarr);
        }

		freeAr(&OUTnd);
		for (i=0;i<nrarrs;++i){
			freeAr(arrpp[i]);
		}
		return;
	} else {
		for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
#ifdef DEBUG_ARRAYND_LOOPS
			DBG_ARND_LP("arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx_Loop: ");
			for(j=0;j<=dim;++j){
				DBG_ARND_LP("c[%lld]=%lld ",j,c[j]);
			}
			DBG_ARND_LP("\n");
#endif
            k = map_c2all[dim];
            l = c[dim];
            for (i=0;i<narrs;++i){
                j = map_all2as[i][k];
                if (j >= 0){
                    is_idx_new[i] = 1; /* This should prevent excessive recalculation of arrays */
                    idxs[i][j] = l;
                }
            }
            arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx_Loop(fct,OUT,arrays,dbl_ptr,int_ptr,idx_ptr,Rarr,Rdbl,Rint,Ridx,
                narrs,ndbls,nints,nidxs,nrarrs,nrdbls,nrints,nridxs,args,
                ndims,map_c2all,map_all2as,n_adims,adim_all,adim_out,adim_rarr,n_adims_per_arr,adims,idxs,is_idx_new,dim+1,c,clens,all_len);
		}
	}

	return;
}

arr arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx_WMaps(fctArgsRarr fct,int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs,
    arr **arrays,double *dbl_ptr,int *int_ptr,typ_idx *idx_ptr,arr **Rarr,arr **Rdbl,arr **Rint,arr **Ridx,typ_idx n_adims,typ_idx *adim_all,typ_idx ndims,typ_idx *all_len,typ_idx **map_as2all) {
    DBG_ARND_ENTR;
	typ_idx i,j,k,l,m;
    /*
	for(j=0;j<narrs;++j){ printArrayInfoWHdr(stderr,arrays[j],"arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx_WMaps: arrays[%lld] - ",(int)j); }
	*/

#ifdef DEBUG_ARRAYND
    DBG_ARND("arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx_WMaps: all_len");
	for(i=0;i<ndims;++i){
		DBG_ARND(" %lld",all_len[i]);
	}
	DBG_ARND("\n");
	for(j=0;j<narrs;++j){
        DBG_ARND("arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx_WMaps: map_as2all[%lld]",j);
		for(i=0;i<arrays[j]->n;++i){
			DBG_ARND(" %lld",map_as2all[j][i]);
		}
        DBG_ARND("\n");
	}
#endif

    typ_idx **map_all2as = malloc(narrs*sizeof(typ_idx *));
	for(i=0;i<narrs;++i){ map_all2as[i] = mapdims_inverse(arrays[i]->n,ndims,map_as2all[i]); }
#ifdef DEBUG_ARRAYND
	for(j=0;j<narrs;++j){
        DBG_ARND("arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx_WMaps: map_all2as[%lld]",j);
		for(i=0;i<ndims;++i){
			DBG_ARND(" %lld",map_all2as[j][i]);
		}
        DBG_ARND("\n");
	}
#endif

    typ_idx **adims = malloc(narrs*sizeof *adims);
	for(i=0;i<narrs;++i){
        adims[i] = malloc(n_adims*sizeof **adims);
        for(k=0;k<n_adims;++k){
            adims[i][k] = -1;
        }
        for(k=0;k<n_adims;++k){
            for(j=0;j<arrays[i]->n;++j){
                if (map_as2all[i][j]==adim_all[k]){
                    adims[i][k] = j;
                    break;
                }
            }
        }
	}
#ifdef DEBUG_ARRAYND
	for(i=0;i<narrs;++i){
        DBG_ARND("arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx_WMaps: adims[%lld]",i);
        for(k=0;k<n_adims;++k){
			DBG_ARND(" %2lld",adims[i][k]);
        }
        DBG_ARND("\n");
	}
#endif

    typ_idx **adim_tmp      = malloc(narrs*sizeof *adim_tmp);
    typ_idx *n_adims_per_arr= malloc(narrs*sizeof *n_adims_per_arr);
    for(i=0;i<narrs;++i){
        adim_tmp[i] = malloc(n_adims*sizeof(typ_idx));
        for(k=0,n_adims_per_arr[i]=0;k<n_adims;++k){
            if (adims[i][k] > -1){
                adim_tmp[i][n_adims_per_arr[i]] = adims[i][k];
                n_adims_per_arr[i]++;
            }
        }
    }

	typ_idx *c,*clens,*map_all2c,*map_c2all;
	arr OUT = NullArray();
	if (ndims < n_adims){
        for (i=0;i<nrarrs;++i){ *Rarr[i] = NullArray(); }
        for (i=0;i<nrdbls;++i){ *Rdbl[i] = NullArray(); }
        for (i=0;i<nrints;++i){ *Rint[i] = NullArray(); }
        for (i=0;i<nridxs;++i){ *Ridx[i] = NullArray(); }
    } else {
        map_all2c = init0((ndims),TYPIDX);
        map_c2all = init0((ndims-n_adims),TYPIDX);
		clens = initNdLoopCounterLengthsWMaps(ndims,n_adims,adim_all,all_len,map_all2c,map_c2all);
		c 	= init0(ndims-n_adims,TYPIDX);
        typ_idx **idxs = malloc(narrs*sizeof(typ_idx *));
        for (i=0;i<narrs;++i){
            idxs[i] = initNdIdxWMaps(c,arrays[i]->n,n_adims,adims[i],map_all2c,map_as2all[i]);
        }
        
        for (i=0;i<nrarrs;++i){ *Rarr[i] = NullArray(); }
        for (i=0;i<nrdbls;++i){
            *Rdbl[i] = ArrayFromList(ndims-n_adims,DOUBLE,clens);
        /*  copyMiss(Rdbl[i],arrays[maxar]);    */
            fillArWithMiss(Rdbl[i]);
        }
        for (i=0;i<nrints;++i){
            *Rint[i] = ArrayFromList(ndims-n_adims,INT,clens);
        /*  copyMiss(Rint[i],arrays[maxar]);    */
            fillArWithMiss(Rint[i]);
        }
        for (i=0;i<nridxs;++i){
            *Ridx[i] = ArrayFromList(ndims-n_adims,TYPIDX,clens);
        /*  copyMiss(Ridx[i],arrays[maxar]);    */
            fillArWithMiss(Ridx[i]);
        }


        int narnds,ndbls2,nints2,nidxs2;

		j = 0; k = 0; l = 0; m = 0;
		arr   **arnd = malloc(narrs*sizeof(arr *));
		double *dblp = malloc((narrs+ndbls)*sizeof(double));
		int    *intp = malloc((narrs+nints)*sizeof(int));
		typ_idx*idxp = malloc((narrs+nidxs)*sizeof(typ_idx));
		double *dblp_miss = malloc((narrs+ndbls)*sizeof(double));
		int    *intp_miss = malloc((narrs+nints)*sizeof(int));
		typ_idx*idxp_miss = malloc((narrs+nidxs)*sizeof(typ_idx));
		for(i=0;i<narrs;++i){
			if (n_adims_per_arr[i]){
                arnd[j]  = malloc(sizeof(arr));
                *arnd[j] = NullArray();
				++j;
			} else {
                if (arrays[i]->typ == DOUBLE){
                    dblp_miss[k] = *(double *)getMiss(arrays[i]);
                    ++k;
                } else if (arrays[i]->typ == INT){
                    intp_miss[l] = *(int *)getMiss(arrays[i]);
                    ++l;
                } else if (arrays[i]->typ == TYPIDX){
                    idxp_miss[m] = *(typ_idx *)getMiss(arrays[i]);
                    ++m;
                } else {
                    fprintf(stderr,"arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_Loop: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                    exit(0);
                }
			}
		}
		for(i=0;i<ndbls;++i){
			dblp[k] = dbl_ptr[i];
            dblp_miss[k] = -999.0;
			++k;
		}
		for(i=0;i<nints;++i){
			intp[l] = int_ptr[i];
            intp_miss[l] = -999;
			++l;
		}
		for(i=0;i<nidxs;++i){
			idxp[m] = idx_ptr[i];
            idxp_miss[m] = -999;
			++m;
		}
		narnds = j;
		ndbls2 = k;
		nints2 = l;
		nidxs2 = m;

		arr    **arrpp = malloc(nrarrs*sizeof(arr *));
		for(i=0;i<nrarrs;++i){
            arrpp[i] = malloc(sizeof(arr));
		}
		double     **dblpp = malloc(nrdbls*sizeof(double *));
		double *dblpp_miss = malloc(nrdbls*sizeof(double));
		for(i=0;i<nrdbls;++i){
			dblpp_miss[i] = *(double *)getMiss(Rdbl[i]);
		}
		int     **intpp = malloc(nrints*sizeof(int *));
		int *intpp_miss = malloc(nrints*sizeof(int));
		for(i=0;i<nrints;++i){
			intpp_miss[i] = *(int *)getMiss(Rint[i]);
		}
		typ_idx     **idxpp = malloc(nridxs*sizeof(typ_idx *));
		typ_idx *idxpp_miss = malloc(nridxs*sizeof(typ_idx));
		for(i=0;i<nridxs;++i){
			idxpp_miss[i] = *(typ_idx *)getMiss(Ridx[i]);
		}

        arr OUTnd = NullArray();
        input_args args=passInputArgs(narnds,ndbls2,nints2,nidxs2,nrarrs,nrdbls,nrints,nridxs
            ,arnd,dblp,intp,idxp,arrpp,dblpp,intpp,idxpp,dblp_miss,intp_miss,idxp_miss,dblpp_miss,intpp_miss,idxpp_miss,&OUTnd);

		int *is_idx_new = malloc(narrs*sizeof(int));
        set_ints_to_val(narrs,is_idx_new,1);

        typ_idx *adim_out = NULL;
        typ_idx **adim_rarr = malloc(nrarrs*sizeof(typ_idx *));
        for (i=0;i<nrarrs;++i){ adim_rarr[i] = NULL; }

		arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx_Loop(fct,&OUT,arrays,dbl_ptr,int_ptr,idx_ptr,Rarr,Rdbl,Rint,Ridx,
            narrs,ndbls,nints,nidxs,nrarrs,nrdbls,nrints,nridxs,&args,
            ndims,map_c2all,map_all2as,n_adims,adim_all,&adim_out,adim_rarr,n_adims_per_arr,adim_tmp,idxs,is_idx_new,(typ_idx)0,c,clens,all_len);
            
#ifdef DEBUG_ARRAYND
        printArrayInfoWHdr(stderr,&OUT,"arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx_WMaps: OUT\n");
#endif

        free(c);
		free(clens);
		free(map_all2c);
		free(map_c2all);
        free(adim_out);
        for (i=0;i<nrarrs;++i){ free(adim_rarr[i]); }
        free(adim_rarr);
        for (i=0;i<narrs;++i){ free(idxs[i]); }
		free(idxs);

        free(is_idx_new);

		for (i=0;i<narnds;++i){
			freeAr(arnd[i]);
			free(arnd[i]);
		}
		for (i=0;i<nrarrs;++i){
			free(arrpp[i]);
		}
        freeInputArgs(&args);
	}

    for(i=0;i<narrs;++i){
        free(adims[i]);
        free(adim_tmp[i]);
        free(map_all2as[i]);
    }
    free(adims);
    free(adim_tmp);
    free(n_adims_per_arr);
    free(map_all2as);
	return OUT;
}

arr arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx(fctArgsRarr fct,int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs,
    arr **arrays,double *dbl_ptr,int *int_ptr,typ_idx *idx_ptr,arr **Rarr,arr **Rdbl,arr **Rint,arr **Ridx,typ_idx n_adims,typ_idx *adims_in) {
	typ_idx i,ndims;
	typ_idx **map_as2all;
	typ_idx *all_len = mapdims_Nar(narrs,arrays,&ndims,&map_as2all);

	typ_idx maxn = -1,maxar = -1;
	for(i=0;i<narrs;++i){
		if (arrays[i]->n > maxn){
			maxn  = arrays[i]->n;
			maxar = i;
		}
	}

	if (maxn < n_adims){
		fprintf(stderr,"Error in arNdArgNarNsNintRet1arrNarrNDblNInt: n_adims must be less than or equal to %lld! n_adims=%lld\n"
			,maxn,n_adims);
		exit(0);
	}

    typ_idx *adim_all = malloc(n_adims*sizeof(typ_idx));
    for(i=0;i<n_adims;++i){
        adim_all[i]= map_as2all[maxar][adims_in[i]];
    }

    arr OUT = arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx_WMaps(fct,narrs,ndbls,nints,nidxs,nrarrs,nrdbls,nrints,nridxs,
        arrays,dbl_ptr,int_ptr,idx_ptr,Rarr,Rdbl,Rint,Ridx,n_adims,adim_all,ndims,all_len,map_as2all);

    for(i=0;i<narrs;++i){
        free(map_as2all[i]);
    }
	free(map_as2all);
	free(all_len);
	free(adim_all);
	return OUT;
}

arr arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx_VArg(
    fctArgsRarr fct,typ_idx n_adims,typ_idx *adims_in,int narrs,int ndbls,int nints,int nidxs,int nrarrs,int nrdbls,int nrints,int nridxs,...){
	int i;

	arr   **arrays  = malloc(narrs *sizeof(arr *));
	double *dbl_ptr = malloc(ndbls *sizeof(double));
	int    *int_ptr = malloc(nints *sizeof(int));
	typ_idx*idx_ptr = malloc(nidxs *sizeof(typ_idx));
	arr   **Rarr    = malloc(nrarrs*sizeof(arr *));
	arr   **Rdbl    = malloc(nrdbls*sizeof(arr *));
	arr   **Rint    = malloc(nrints*sizeof(arr *));
	arr   **Ridx    = malloc(nridxs*sizeof(arr *));

	va_list arg_list;
	va_start(arg_list, nridxs);
	for (i=0;i<narrs;++i){
		arrays[i]  = va_arg(arg_list, arr *);
	}
	for (i=0;i<ndbls;++i){
		dbl_ptr[i] = va_arg(arg_list, double);
	}
	for (i=0;i<nints;++i){
		int_ptr[i] = va_arg(arg_list, int);
	}
	for (i=0;i<nidxs;++i){
		idx_ptr[i] = va_arg(arg_list, typ_idx);
	}
	for (i=0;i<nrarrs;++i){
		Rarr[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrdbls;++i){
		Rdbl[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrints;++i){
		Rint[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nridxs;++i){
		Ridx[i]   = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

    arr OUT = arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx(fct,narrs,ndbls,nints,nidxs,nrarrs,nrdbls,nrints,nridxs,
        arrays,dbl_ptr,int_ptr,idx_ptr,Rarr,Rdbl,Rint,Ridx,n_adims,adims_in);

	free(arrays);
	free(dbl_ptr);
	free(int_ptr);
	free(idx_ptr);
	free(Rarr);
	free(Rdbl);
	free(Rint);
	free(Ridx);
	return OUT;
}




void ndmath_dbl_NarNsNint_RNDblNInt_Loop(fctArgsRdbl fct,arr *restrict OUT,
    arr **arrays,arr **Rdbl,arr **Rint,
    int narrs,int nrdbls,int nrints,input_args *args,
    typ_idx ndims,typ_idx **map_c2as,typ_idx **idxs,typ_idx dim,typ_idx *c,typ_idx *clens){
/*	This is a recursive n dimensional loop function	*/
    typ_idx i,j;

    DBG_ARND_LP("ndmath_dbl_NarNsNint_RNDblNInt_Loop: dim=%lld\n",dim);
	if (dim == ndims){
		int k = 0, l = 0;
		for(i=0;i<narrs;++i){
            if (arrays[i]->typ == DOUBLE){
                args->dblp[k] = cDBL(arrays[i],idxs[i]);
                ++k;
            } else if (arrays[i]->typ == INT){
                args->intp[l] = cINTG(arrays[i],idxs[i]);
                ++l;
            } else {
                fprintf(stderr,"ndmath_dbl_NarNsNint_RNDblNInt_Loop: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                exit(0);
            }
		}

		for(i=0;i<nrdbls;++i){ args->dblpp[i] = address_of_c(Rdbl[i],c); }
		for(i=0;i<nrints;++i){ args->intpp[i] = address_of_c(Rint[i],c); }

        cDBL(OUT,c) = fct(args);

		return;
	} else {
		for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
#ifdef DEBUG_ARRAYND_LOOPS
			DBG_ARND_LP("ndmath_dbl_NarNsNint_RNDblNInt_Loop: ");
			for(j=0;j<=dim;++j){
				DBG_ARND_LP("c[%lld]=%lld ",j,c[j]);
			}
			DBG_ARND_LP("\n");
#endif
            for (i=0;i<narrs;++i){
                j = map_c2as[i][dim];
                if (j >= 0){
                    idxs[i][j] = c[dim];
                }
            }
            ndmath_dbl_NarNsNint_RNDblNInt_Loop(fct,OUT,arrays,Rdbl,Rint,
                narrs,nrdbls,nrints,args,
                ndims,map_c2as,idxs,dim+1,c,clens);
		}
	}

	return;
}

arr ndmath_dbl_NarNsNint_RNDblNInt_WMaps(fctArgsRdbl fct,int narrs,int ndbls,int nints,int nrdbls,int nrints,
    arr **arrays,double *dbl_ptr,int *int_ptr,arr **Rdbl,arr **Rint,typ_idx ndims,typ_idx *clens,typ_idx **map_as2c) {
	typ_idx i;
/*
#ifdef DEBUG_ARRAYND
	typ_idx j;
    DBG_ARND("ndmath_dbl_NarNsNint_RNDblNInt_WMaps: narrs=%d, ndbls=%d, nints=%d, nrdbls=%d, nrints=%d, ndims=%lld\n"
        ,narrs,ndbls,nints,nrdbls,nrints,ndims);
    DBG_ARND("ndmath_dbl_NarNsNint_RNDblNInt_WMaps: clens");
	for(i=0;i<ndims;++i){
		DBG_ARND(" %lld",clens[i]);
	}
	DBG_ARND("\n");
	for(j=0;j<narrs;++j){
        DBG_ARND("ndmath_dbl_NarNsNint_RNDblNInt_WMaps: map_as2c[%lld]",j);
		for(i=0;i<arrays[j]->n;++i){
			DBG_ARND(" %lld",map_as2c[j][i]);
		}
        DBG_ARND("\n");
	}
#endif
*/
    
    typ_idx **map_c2as = malloc(narrs*sizeof(typ_idx *));
	for(i=0;i<narrs;++i){ map_c2as[i] = mapdims_inverse(arrays[i]->n,ndims,map_as2c[i]); }
/*
#ifdef DEBUG_ARRAYND
	for(j=0;j<narrs;++j){
        DBG_ARND("ndmath_dbl_NarNsNint_RNDblNInt_WMaps: map_c2as[%lld]",j);
		for(i=0;i<ndims;++i){
			DBG_ARND(" %lld",map_c2as[j][i]);
		}
        DBG_ARND("\n");
	}
#endif
*/

	typ_idx maxn = -1,maxar = -1;
	for(i=0;i<narrs;++i){
		if (arrays[i]->n > maxn){
			maxn  = arrays[i]->n;
			maxar = i;
		}
	}
/*  DBG_ARND("ndmath_dbl_NarNsNint_RNDblNInt_WMaps: maxn=%lld, maxar=%lld\n",maxn,maxar); */

	arr OUT;
	if (ndims < 0){
        OUT = NullArray();
        for (i=0;i<nrdbls;++i){ *Rdbl[i] = NullArray(); }
        for (i=0;i<nrints;++i){ *Rint[i] = NullArray(); }
    } else {
		typ_idx *c 	   = init0(ndims,TYPIDX);
        typ_idx **idxs = malloc(narrs*sizeof(typ_idx *));
        for (i=0;i<narrs;++i){
            idxs[i] = initNdIdxWMaps_NoAdims(c,arrays[i]->n,map_as2c[i]);
        }
        
		OUT	= ArrayFromList(ndims,DOUBLE,clens);
		copyMiss(&OUT,arrays[maxar]);

        for (i=0;i<nrdbls;++i){
            *Rdbl[i] = ArrayFromList(ndims,DOUBLE,clens);
            copyMiss(Rdbl[i],arrays[maxar]);
            fillArWithMiss(Rdbl[i]);
        }
        for (i=0;i<nrints;++i){
            *Rint[i] = ArrayFromList(ndims,INT,clens);
            copyMiss(Rint[i],arrays[maxar]);
            fillArWithMiss(Rint[i]);
        }


		int k = 0, l = 0;
		double *dblp = malloc((narrs+ndbls)*sizeof(double));
		int    *intp = malloc((narrs+nints)*sizeof(int));
		double *dblp_miss = malloc((narrs+ndbls)*sizeof(double));
		int    *intp_miss = malloc((narrs+nints)*sizeof(int));
		for(i=0;i<narrs;++i){
            if (arrays[i]->typ == DOUBLE){
                dblp_miss[k] = *(double *)getMiss(arrays[i]);
                ++k;
            } else if (arrays[i]->typ == INT){
                intp_miss[l] = *(int *)getMiss(arrays[i]);
                ++l;
            } else {
                fprintf(stderr,"ndmath_dbl_NarNsNint_RNDblNInt_WMaps: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                exit(0);
            }
		}
		for(i=0;i<ndbls;++i){
			dblp[k]      = dbl_ptr[i];
            dblp_miss[k] = *(double *)getMiss(&OUT);
			++k;
		}
		for(i=0;i<nints;++i){
			intp[l]      = int_ptr[i];
            intp_miss[l] = -999;
			++l;
		}
		int ndbls2 = k;
		int nints2 = l;

		double **dblpp = malloc(nrdbls*sizeof(double *));
		double *dblpp_miss = malloc(nrdbls*sizeof(double));
		for(i=0;i<nrdbls;++i){
			dblpp_miss[i] = *(double *)getMiss(Rdbl[i]);
		}
		int **intpp = malloc(nrints*sizeof(int *));
		int    *intpp_miss = malloc(nrints*sizeof(int));
		for(i=0;i<nrints;++i){
			intpp_miss[i] = *(int *)getMiss(Rint[i]);
		}

        input_args args=passInputArgs(0,ndbls2,nints2,0,0,nrdbls,nrints,0
            ,NULL,dblp,intp,NULL,NULL,dblpp,intpp,NULL,dblp_miss,intp_miss,NULL,dblpp_miss,intpp_miss,NULL,getMiss(&OUT));

		ndmath_dbl_NarNsNint_RNDblNInt_Loop(fct,&OUT,arrays,Rdbl,Rint,
            narrs,nrdbls,nrints,&args,
            ndims,map_c2as,idxs,(typ_idx)0,c,clens);

        free(c);
        for (i=0;i<narrs;++i){
			free(idxs[i]);
		}
		free(idxs);

        freeInputArgs(&args);
	}

    for(i=0;i<narrs;++i){
        free(map_c2as[i]);
    }
	free(map_c2as);
	return OUT;
}

arr ndmath_dbl_NarNsNint_RNDblNInt(fctArgsRdbl fct,int narrs,int ndbls,int nints,int nrdbls,int nrints,
    arr **arrays,double *dbl_ptr,int *int_ptr,arr **Rdbl,arr **Rint) {
	typ_idx i,ndims;
	typ_idx **map_as2c;
	typ_idx *clens = mapdims_Nar(narrs,arrays,&ndims,&map_as2c);

    arr OUT = ndmath_dbl_NarNsNint_RNDblNInt_WMaps(fct,narrs,ndbls,nints,nrdbls,nrints,
        arrays,dbl_ptr,int_ptr,Rdbl,Rint,ndims,clens,map_as2c);

    for(i=0;i<narrs;++i){
        free(map_as2c[i]);
    }
	free(map_as2c);
	free(clens);
	return OUT;
}

arr ndmath_dbl_NarNsNint_RNDblNInt_VArg(
    fctArgsRdbl fct,int narrs,int ndbls,int nints,int nrdbls,int nrints,...){
	int i;

	arr   **arrays  = malloc(narrs *sizeof(arr *));
	double *dbl_ptr = malloc(ndbls *sizeof(double));
	int    *int_ptr = malloc(nints *sizeof(int));
	arr   **Rdbl    = malloc(nrdbls*sizeof(arr *));
	arr   **Rint    = malloc(nrints*sizeof(arr *));

	va_list arg_list;
	va_start(arg_list, nrints);
	for (i=0;i<narrs;++i){
		arrays[i]  = va_arg(arg_list, arr *);
	}
	for (i=0;i<ndbls;++i){
		dbl_ptr[i] = va_arg(arg_list, double);
	}
	for (i=0;i<nints;++i){
		int_ptr[i] = va_arg(arg_list, int);
	}
	for (i=0;i<nrdbls;++i){
		Rdbl[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrints;++i){
		Rint[i]   = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

    arr OUT = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,ndbls,nints,nrdbls,nrints,
        arrays,dbl_ptr,int_ptr,Rdbl,Rint);

	free(arrays);
	free(dbl_ptr);
	free(int_ptr);
	free(Rdbl);
	free(Rint);
	return OUT;
}

arr ndmath_dbl_NarNsNint_RNDblNInt_WMaps_VArg(
    fctArgsRdbl fct,typ_idx ndims,typ_idx *clens,typ_idx **map_as2c,int narrs,int ndbls,int nints,int nrdbls,int nrints,...){
	int i;

	arr   **arrays  = malloc(narrs *sizeof(arr *));
	double *dbl_ptr = malloc(ndbls *sizeof(double));
	int    *int_ptr = malloc(nints *sizeof(int));
	arr   **Rdbl    = malloc(nrdbls*sizeof(arr *));
	arr   **Rint    = malloc(nrints*sizeof(arr *));

	va_list arg_list;
	va_start(arg_list, nrints);
	for (i=0;i<narrs;++i){
		arrays[i]  = va_arg(arg_list, arr *);
	}
	for (i=0;i<ndbls;++i){
		dbl_ptr[i] = va_arg(arg_list, double);
	}
	for (i=0;i<nints;++i){
		int_ptr[i] = va_arg(arg_list, int);
	}
	for (i=0;i<nrdbls;++i){
		Rdbl[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrints;++i){
		Rint[i]   = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

    arr OUT = ndmath_dbl_NarNsNint_RNDblNInt_WMaps(fct,narrs,ndbls,nints,nrdbls,nrints,
        arrays,dbl_ptr,int_ptr,Rdbl,Rint,ndims,clens,map_as2c);

	free(arrays);
	free(dbl_ptr);
	free(int_ptr);
	free(Rdbl);
	free(Rint);
	return OUT;
}



void ndmath_int_NarNsNint_RNDblNInt_Loop(fctArgsRint fct,arr *restrict OUT,
    arr **arrays,arr **Rdbl,arr **Rint,
    int narrs,int nrdbls,int nrints,input_args *args,
    typ_idx ndims,typ_idx **map_c2as,typ_idx **idxs,typ_idx dim,typ_idx *c,typ_idx *clens){
/*	This is a recursive n dimensional loop function	*/
    typ_idx i,j;

    DBG_ARND_LP("ndmath_int_NarNsNint_RNDblNInt_Loop: dim=%lld\n",dim);
	if (dim == ndims){
		int k = 0, l = 0;
		for(i=0;i<narrs;++i){
            if (arrays[i]->typ == DOUBLE){
                args->dblp[k] = cDBL(arrays[i],idxs[i]);
                ++k;
            } else if (arrays[i]->typ == INT){
                args->intp[l] = cINTG(arrays[i],idxs[i]);
                ++l;
            } else {
                fprintf(stderr,"ndmath_int_NarNsNint_RNDblNInt_Loop: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                exit(0);
            }
		}

		for(i=0;i<nrdbls;++i){ args->dblpp[i] = address_of_c(Rdbl[i],c); }
		for(i=0;i<nrints;++i){ args->intpp[i] = address_of_c(Rint[i],c); }

        cINTG(OUT,c) = fct(args);

		return;
	} else {
		for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
#ifdef DEBUG_ARRAYND_LOOPS
			DBG_ARND_LP("ndmath_int_NarNsNint_RNDblNInt_Loop: ");
			for(j=0;j<=dim;++j){
				DBG_ARND_LP("c[%lld]=%lld ",j,c[j]);
			}
			DBG_ARND_LP("\n");
#endif
            for (i=0;i<narrs;++i){
                j = map_c2as[i][dim];
                if (j >= 0){
                    idxs[i][j] = c[dim];
                }
            }
            ndmath_int_NarNsNint_RNDblNInt_Loop(fct,OUT,arrays,Rdbl,Rint,
                narrs,nrdbls,nrints,args,
                ndims,map_c2as,idxs,dim+1,c,clens);
		}
	}

	return;
}

arr ndmath_int_NarNsNint_RNDblNInt_WMaps(fctArgsRint fct,int narrs,int ndbls,int nints,int nrdbls,int nrints,
    arr **arrays,double *dbl_ptr,int *int_ptr,arr **Rdbl,arr **Rint,typ_idx ndims,typ_idx *clens,typ_idx **map_as2c) {
	typ_idx i;
/*
#ifdef DEBUG_ARRAYND
	typ_idx j;
    DBG_ARND("ndmath_int_NarNsNint_RNDblNInt: clens");
	for(i=0;i<ndims;++i){
		DBG_ARND(" %lld",clens[i]);
	}
	DBG_ARND("\n");
	for(j=0;j<narrs;++j){
        DBG_ARND("ndmath_int_NarNsNint_RNDblNInt: map_as2c[%lld]",j);
		for(i=0;i<arrays[j]->n;++i){
			DBG_ARND(" %lld",map_as2c[j][i]);
		}
        DBG_ARND("\n");
	}
#endif
*/
    typ_idx **map_c2as = malloc(narrs*sizeof(typ_idx *));
	for(i=0;i<narrs;++i){ map_c2as[i] = mapdims_inverse(arrays[i]->n,ndims,map_as2c[i]); }
/*
#ifdef DEBUG_ARRAYND
	for(j=0;j<narrs;++j){
        DBG_ARND("ndmath_int_NarNsNint_RNDblNInt: map_c2as[%lld]",j);
		for(i=0;i<ndims;++i){
			DBG_ARND(" %lld",map_c2as[j][i]);
		}
        DBG_ARND("\n");
	}
#endif
*/

	typ_idx maxn = -1,maxar = -1;
	for(i=0;i<narrs;++i){
		if (arrays[i]->n > maxn){
			maxn  = arrays[i]->n;
			maxar = i;
		}
	}

	arr OUT;
	if (ndims < 0){
        OUT = NullArray();
        for (i=0;i<nrdbls;++i){ *Rdbl[i] = NullArray(); }
        for (i=0;i<nrints;++i){ *Rint[i] = NullArray(); }
    } else {
		typ_idx *c 	   = init0(ndims,TYPIDX);
        typ_idx **idxs = malloc(narrs*sizeof(typ_idx *));
        for (i=0;i<narrs;++i){
            idxs[i] = initNdIdxWMaps_NoAdims(c,arrays[i]->n,map_as2c[i]);
        }
        
		OUT	= ArrayFromList(ndims,INT,clens);
		copyMiss(&OUT,arrays[maxar]);

        for (i=0;i<nrdbls;++i){
            *Rdbl[i] = ArrayFromList(ndims,DOUBLE,clens);
            copyMiss(Rdbl[i],arrays[maxar]);
            fillArWithMiss(Rdbl[i]);
        }
        for (i=0;i<nrints;++i){
            *Rint[i] = ArrayFromList(ndims,INT,clens);
            copyMiss(Rint[i],arrays[maxar]);
            fillArWithMiss(Rint[i]);
        }


		int k = 0, l = 0;
		double *dblp = malloc((narrs+ndbls)*sizeof(double));
		int    *intp = malloc((narrs+nints)*sizeof(int));
		double *dblp_miss = malloc((narrs+ndbls)*sizeof(double));
		int    *intp_miss = malloc((narrs+nints)*sizeof(int));
		for(i=0;i<narrs;++i){
            if (arrays[i]->typ == DOUBLE){
                dblp_miss[k] = *(double *)getMiss(arrays[i]);
                ++k;
            } else if (arrays[i]->typ == INT){
                intp_miss[l] = *(int *)getMiss(arrays[i]);
                ++l;
            } else {
                fprintf(stderr,"ndmath_int_NarNsNint_RNDblNInt_WMaps: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                exit(0);
            }
		}
		for(i=0;i<ndbls;++i){
			dblp[k]      = dbl_ptr[i];
            dblp_miss[k] = *(double *)getMiss(&OUT);
			++k;
		}
		for(i=0;i<nints;++i){
			intp[l]      = int_ptr[i];
            intp_miss[l] = -999;
			++l;
		}
		int ndbls2 = k;
		int nints2 = l;

		double **dblpp = malloc(nrdbls*sizeof(double *));
		double *dblpp_miss = malloc(nrdbls*sizeof(double));
		for(i=0;i<nrdbls;++i){
			dblpp_miss[i] = *(double *)getMiss(Rdbl[i]);
		}
		int **intpp = malloc(nrints*sizeof(int *));
		int    *intpp_miss = malloc(nrints*sizeof(int));
		for(i=0;i<nrints;++i){
			intpp_miss[i] = *(int *)getMiss(Rint[i]);
		}

        input_args args=passInputArgs(0,ndbls2,nints2,0,0,nrdbls,nrints,0
            ,NULL,dblp,intp,NULL,NULL,dblpp,intpp,NULL,dblp_miss,intp_miss,NULL,dblpp_miss,intpp_miss,NULL,getMiss(&OUT));

		ndmath_int_NarNsNint_RNDblNInt_Loop(fct,&OUT,arrays,Rdbl,Rint,
            narrs,nrdbls,nrints,&args,
            ndims,map_c2as,idxs,(typ_idx)0,c,clens);

        free(c);
        for (i=0;i<narrs;++i){
			free(idxs[i]);
		}
		free(idxs);

        freeInputArgs(&args);
	}

    for(i=0;i<narrs;++i){
        free(map_c2as[i]);
    }
	free(map_c2as);
	return OUT;
}

arr ndmath_int_NarNsNint_RNDblNInt(fctArgsRint fct,int narrs,int ndbls,int nints,int nrdbls,int nrints,
    arr **arrays,double *dbl_ptr,int *int_ptr,arr **Rdbl,arr **Rint) {
	typ_idx i,ndims;
	typ_idx **map_as2c;
	typ_idx *clens = mapdims_Nar(narrs,arrays,&ndims,&map_as2c);

    arr OUT = ndmath_int_NarNsNint_RNDblNInt_WMaps(fct,narrs,ndbls,nints,nrdbls,nrints,
        arrays,dbl_ptr,int_ptr,Rdbl,Rint,ndims,clens,map_as2c);

    for(i=0;i<narrs;++i){
        free(map_as2c[i]);
    }
	free(map_as2c);
	free(clens);
	return OUT;
}

arr ndmath_int_NarNsNint_RNDblNInt_VArg(
    fctArgsRint fct,int narrs,int ndbls,int nints,int nrdbls,int nrints,...){
	int i;

	arr   **arrays  = malloc(narrs *sizeof(arr *));
	double *dbl_ptr = malloc(ndbls *sizeof(double));
	int    *int_ptr = malloc(nints *sizeof(int));
	arr   **Rdbl    = malloc(nrdbls*sizeof(arr *));
	arr   **Rint    = malloc(nrints*sizeof(arr *));

	va_list arg_list;
	va_start(arg_list, nrints);
	for (i=0;i<narrs;++i){
		arrays[i]  = va_arg(arg_list, arr *);
	}
	for (i=0;i<ndbls;++i){
		dbl_ptr[i] = va_arg(arg_list, double);
	}
	for (i=0;i<nints;++i){
		int_ptr[i] = va_arg(arg_list, int);
	}
	for (i=0;i<nrdbls;++i){
		Rdbl[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrints;++i){
		Rint[i]   = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

    arr OUT = ndmath_int_NarNsNint_RNDblNInt(fct,narrs,ndbls,nints,nrdbls,nrints,
        arrays,dbl_ptr,int_ptr,Rdbl,Rint);

	free(arrays);
	free(dbl_ptr);
	free(int_ptr);
	free(Rdbl);
	free(Rint);
	return OUT;
}

arr ndmath_int_NarNsNint_RNDblNInt_WMaps_VArg(
    fctArgsRint fct,typ_idx ndims,typ_idx *clens,typ_idx **map_as2c,int narrs,int ndbls,int nints,int nrdbls,int nrints,...){
	int i;

	arr   **arrays  = malloc(narrs *sizeof(arr *));
	double *dbl_ptr = malloc(ndbls *sizeof(double));
	int    *int_ptr = malloc(nints *sizeof(int));
	arr   **Rdbl    = malloc(nrdbls*sizeof(arr *));
	arr   **Rint    = malloc(nrints*sizeof(arr *));

	va_list arg_list;
	va_start(arg_list, nrints);
	for (i=0;i<narrs;++i){
		arrays[i]  = va_arg(arg_list, arr *);
	}
	for (i=0;i<ndbls;++i){
		dbl_ptr[i] = va_arg(arg_list, double);
	}
	for (i=0;i<nints;++i){
		int_ptr[i] = va_arg(arg_list, int);
	}
	for (i=0;i<nrdbls;++i){
		Rdbl[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrints;++i){
		Rint[i]   = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

    arr OUT = ndmath_int_NarNsNint_RNDblNInt_WMaps(fct,narrs,ndbls,nints,nrdbls,nrints,
        arrays,dbl_ptr,int_ptr,Rdbl,Rint,ndims,clens,map_as2c);

	free(arrays);
	free(dbl_ptr);
	free(int_ptr);
	free(Rdbl);
	free(Rint);
	return OUT;
}



void ndmath_NarNsNint_RNDblNInt_Loop(fctArgsNoRet fct,
    arr **arrays,arr **Rdbl,arr **Rint,
    int narrs,int nrdbls,int nrints,input_args *args,
    typ_idx ndims,typ_idx **map_c2as,typ_idx **idxs,typ_idx dim,typ_idx *c,typ_idx *clens){
/*	This is a recursive n dimensional loop function	*/
    typ_idx i,j;

    DBG_ARND_LP("ndmath_NarNsNint_RNDblNInt_Loop: dim=%lld\n",dim);
	if (dim == ndims){
		int k = 0, l = 0;
		for(i=0;i<narrs;++i){
            if (arrays[i]->typ == DOUBLE){
                args->dblp[k] = cDBL(arrays[i],idxs[i]);
                ++k;
            } else if (arrays[i]->typ == INT){
                args->intp[l] = cINTG(arrays[i],idxs[i]);
                ++l;
            } else {
                fprintf(stderr,"ndmath_NarNsNint_RNDblNInt_Loop: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                exit(0);
            }
		}

		for(i=0;i<nrdbls;++i){ args->dblpp[i] = address_of_c(Rdbl[i],c); }
		for(i=0;i<nrints;++i){ args->intpp[i] = address_of_c(Rint[i],c); }

        fct(args);

		return;
	} else {
		for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
#ifdef DEBUG_ARRAYND_LOOPS
			DBG_ARND_LP("ndmath_NarNsNint_RNDblNInt_Loop: ");
			for(j=0;j<=dim;++j){
				DBG_ARND_LP("c[%lld]=%lld ",j,c[j]);
			}
			DBG_ARND_LP("\n");
#endif
            for (i=0;i<narrs;++i){
                j = map_c2as[i][dim];
                if (j >= 0){
                    idxs[i][j] = c[dim];
                }
            }
            ndmath_NarNsNint_RNDblNInt_Loop(fct,arrays,Rdbl,Rint,
                narrs,nrdbls,nrints,args,
                ndims,map_c2as,idxs,dim+1,c,clens);
		}
	}

	return;
}

void ndmath_NarNsNint_RNDblNInt_WMaps(fctArgsNoRet fct,int narrs,int ndbls,int nints,int nrdbls,int nrints,
    arr **arrays,double *dbl_ptr,int *int_ptr,arr **Rdbl,arr **Rint,typ_idx ndims,typ_idx *clens,typ_idx **map_as2c) {
	typ_idx i;
/*
#ifdef DEBUG_ARRAYND
	typ_idx j;
    DBG_ARND("ndmath_NarNsNint_RNDblNInt: clens");
	for(i=0;i<ndims;++i){
		DBG_ARND(" %lld",clens[i]);
	}
	DBG_ARND("\n");
	for(j=0;j<narrs;++j){
        DBG_ARND("ndmath_NarNsNint_RNDblNInt: map_as2c[%lld]",j);
		for(i=0;i<arrays[j]->n;++i){
			DBG_ARND(" %lld",map_as2c[j][i]);
		}
        DBG_ARND("\n");
	}
#endif
*/
    typ_idx **map_c2as = malloc(narrs*sizeof(typ_idx *));
	for(i=0;i<narrs;++i){ map_c2as[i] = mapdims_inverse(arrays[i]->n,ndims,map_as2c[i]); }
/*
#ifdef DEBUG_ARRAYND
	for(j=0;j<narrs;++j){
        DBG_ARND("ndmath_NarNsNint_RNDblNInt: map_c2as[%lld]",j);
		for(i=0;i<ndims;++i){
			DBG_ARND(" %lld",map_c2as[j][i]);
		}
        DBG_ARND("\n");
	}
#endif
*/

	typ_idx maxn = -1,maxar = -1;
	for(i=0;i<narrs;++i){
		if (arrays[i]->n > maxn){
			maxn  = arrays[i]->n;
			maxar = i;
		}
	}

	if (ndims < 0){
        for (i=0;i<nrdbls;++i){ *Rdbl[i] = NullArray(); }
        for (i=0;i<nrints;++i){ *Rint[i] = NullArray(); }
    } else {
		typ_idx *c 	   = init0(ndims,TYPIDX);
        typ_idx **idxs = malloc(narrs*sizeof(typ_idx *));
        for (i=0;i<narrs;++i){
            idxs[i] = initNdIdxWMaps_NoAdims(c,arrays[i]->n,map_as2c[i]);
        }
        
        for (i=0;i<nrdbls;++i){
            *Rdbl[i] = ArrayFromList(ndims,DOUBLE,clens);
            copyMiss(Rdbl[i],arrays[maxar]);
            fillArWithMiss(Rdbl[i]);
        }
        for (i=0;i<nrints;++i){
            *Rint[i] = ArrayFromList(ndims,INT,clens);
            copyMiss(Rint[i],arrays[maxar]);
            fillArWithMiss(Rint[i]);
        }


		int k = 0, l = 0;
		double *dblp = malloc((narrs+ndbls)*sizeof(double));
		int    *intp = malloc((narrs+nints)*sizeof(int));
		double *dblp_miss = malloc((narrs+ndbls)*sizeof(double));
		int    *intp_miss = malloc((narrs+nints)*sizeof(int));
		for(i=0;i<narrs;++i){
            if (arrays[i]->typ == DOUBLE){
                dblp_miss[k] = *(double *)getMiss(arrays[i]);
                ++k;
            } else if (arrays[i]->typ == INT){
                intp_miss[l] = *(int *)getMiss(arrays[i]);
                ++l;
            } else {
                fprintf(stderr,"ndmath_NarNsNint_RNDblNInt_WMaps: Type must be DOUBLE or INT! Type is %d\n",arrays[i]->typ);
                exit(0);
            }
		}
		for(i=0;i<ndbls;++i){
			dblp[k]      = dbl_ptr[i];
            dblp_miss[k] = -999.0;
			++k;
		}
		for(i=0;i<nints;++i){
			intp[l]      = int_ptr[i];
            intp_miss[l] = -999;
			++l;
		}
		int ndbls2 = k;
		int nints2 = l;

		double **dblpp = malloc(nrdbls*sizeof(double *));
		double *dblpp_miss = malloc(nrdbls*sizeof(double));
		for(i=0;i<nrdbls;++i){
			dblpp_miss[i] = *(double *)getMiss(Rdbl[i]);
		}
		int **intpp = malloc(nrints*sizeof(int *));
		int    *intpp_miss = malloc(nrints*sizeof(int));
		for(i=0;i<nrints;++i){
			intpp_miss[i] = *(int *)getMiss(Rint[i]);
		}

        input_args args=passInputArgs(0,ndbls2,nints2,0,0,nrdbls,nrints,0
            ,NULL,dblp,intp,NULL,NULL,dblpp,intpp,NULL,dblp_miss,intp_miss,NULL,dblpp_miss,intpp_miss,NULL,NULL);

		ndmath_NarNsNint_RNDblNInt_Loop(fct,arrays,Rdbl,Rint,
            narrs,nrdbls,nrints,&args,
            ndims,map_c2as,idxs,(typ_idx)0,c,clens);

        free(c);
        for (i=0;i<narrs;++i){
			free(idxs[i]);
		}
		free(idxs);

        freeInputArgs(&args);
	}

    for(i=0;i<narrs;++i){
        free(map_c2as[i]);
    }
	free(map_c2as);
	return;
}

void ndmath_NarNsNint_RNDblNInt(fctArgsNoRet fct,int narrs,int ndbls,int nints,int nrdbls,int nrints,
    arr **arrays,double *dbl_ptr,int *int_ptr,arr **Rdbl,arr **Rint) {
	typ_idx i,ndims;
	typ_idx **map_as2c;
	typ_idx *clens = mapdims_Nar(narrs,arrays,&ndims,&map_as2c);

    ndmath_NarNsNint_RNDblNInt_WMaps(fct,narrs,ndbls,nints,nrdbls,nrints,
        arrays,dbl_ptr,int_ptr,Rdbl,Rint,ndims,clens,map_as2c);

    for(i=0;i<narrs;++i){
        free(map_as2c[i]);
    }
	free(map_as2c);
	free(clens);
	return;
}

void ndmath_NarNsNint_RNDblNInt_VArg(
    fctArgsNoRet fct,int narrs,int ndbls,int nints,int nrdbls,int nrints,...){
	int i;

	arr   **arrays  = malloc(narrs *sizeof(arr *));
	double *dbl_ptr = malloc(ndbls *sizeof(double));
	int    *int_ptr = malloc(nints *sizeof(int));
	arr   **Rdbl    = malloc(nrdbls*sizeof(arr *));
	arr   **Rint    = malloc(nrints*sizeof(arr *));

	va_list arg_list;
	va_start(arg_list, nrints);
	for (i=0;i<narrs;++i){
		arrays[i]  = va_arg(arg_list, arr *);
	}
	for (i=0;i<ndbls;++i){
		dbl_ptr[i] = va_arg(arg_list, double);
	}
	for (i=0;i<nints;++i){
		int_ptr[i] = va_arg(arg_list, int);
	}
	for (i=0;i<nrdbls;++i){
		Rdbl[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrints;++i){
		Rint[i]   = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

    ndmath_NarNsNint_RNDblNInt(fct,narrs,ndbls,nints,nrdbls,nrints,
        arrays,dbl_ptr,int_ptr,Rdbl,Rint);

	free(arrays);
	free(dbl_ptr);
	free(int_ptr);
	free(Rdbl);
	free(Rint);
	return;
}

void ndmath_NarNsNint_RNDblNInt_WMaps_VArg(
    fctArgsNoRet fct,typ_idx ndims,typ_idx *clens,typ_idx **map_as2c,int narrs,int ndbls,int nints,int nrdbls,int nrints,...){
	int i;

	arr   **arrays  = malloc(narrs *sizeof(arr *));
	double *dbl_ptr = malloc(ndbls *sizeof(double));
	int    *int_ptr = malloc(nints *sizeof(int));
	arr   **Rdbl    = malloc(nrdbls*sizeof(arr *));
	arr   **Rint    = malloc(nrints*sizeof(arr *));

	va_list arg_list;
	va_start(arg_list, nrints);
	for (i=0;i<narrs;++i){
		arrays[i]  = va_arg(arg_list, arr *);
	}
	for (i=0;i<ndbls;++i){
		dbl_ptr[i] = va_arg(arg_list, double);
	}
	for (i=0;i<nints;++i){
		int_ptr[i] = va_arg(arg_list, int);
	}
	for (i=0;i<nrdbls;++i){
		Rdbl[i]   = va_arg(arg_list, arr *);
	}
	for (i=0;i<nrints;++i){
		Rint[i]   = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

    ndmath_NarNsNint_RNDblNInt_WMaps(fct,narrs,ndbls,nints,nrdbls,nrints,
        arrays,dbl_ptr,int_ptr,Rdbl,Rint,ndims,clens,map_as2c);

	free(arrays);
	free(dbl_ptr);
	free(int_ptr);
	free(Rdbl);
	free(Rint);
	return;
}



void printMultiArrayNdFmt_Loop(FILE *fout,int narrs,arr **A,char *fmt,
    typ_idx ndims,typ_idx **map_c2as,typ_idx **idxs,typ_idx dim,typ_idx *c,typ_idx *clens){
/*	This is a recursive n dimensional loop function	*/
    typ_idx i,j;

	if (dim == ndims){
        int k = 0;
        if (dim > 0){
            fprintf(fout,"[%lld",c[k]);
            for(k=1;k<dim;++k){
                fprintf(fout,",%lld",c[k]);
            }
            fprintf(fout,"] =");
        }
        for(k=0;k<narrs;++k){
            switch (A[k]->typ) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)	\
                fprintf(fout," ");  \
                fprintf(fout,fmt,cswassign(A[k],idxs[k]));
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
		for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
            for (i=0;i<narrs;++i){
                j = map_c2as[i][dim];
                if (j >= 0){
                    idxs[i][j] = c[dim];
                }
            }
            printMultiArrayNdFmt_Loop(fout,narrs,A,fmt,ndims,map_c2as,idxs,dim+1,c,clens);
		}
	}

	return;
}

void printMultiArrayNdFmt_WMaps(FILE *fout,int narrs,arr **A,char *fmt,typ_idx ndims,typ_idx *clens,typ_idx **map_as2c) {
	typ_idx i;
    
    typ_idx **map_c2as = malloc(narrs*sizeof(typ_idx *));
	for(i=0;i<narrs;++i){ map_c2as[i] = mapdims_inverse(A[i]->n,ndims,map_as2c[i]); }

	if (ndims < 0){
    } else {
		typ_idx *c 	   = init0(ndims,TYPIDX);
        typ_idx **idxs = malloc(narrs*sizeof(typ_idx *));
        for (i=0;i<narrs;++i){
            idxs[i] = initNdIdxWMaps_NoAdims(c,A[i]->n,map_as2c[i]);
        }
        
		printMultiArrayNdFmt_Loop(fout,narrs,A,fmt,ndims,map_c2as,idxs,(typ_idx)0,c,clens);

        free(c);
        for (i=0;i<narrs;++i){
			free(idxs[i]);
		}
		free(idxs);
	}

    for(i=0;i<narrs;++i){
        free(map_c2as[i]);
    }
	free(map_c2as);
	return;
}

void printMultiArrayNdFmtHdr_List(FILE *fout,int narrs,char **hdrs,char *fmt,arr **A) {
	typ_idx i,ndims;
	typ_idx **map_as2c;
	typ_idx *clens = mapdims_Nar(narrs,A,&ndims,&map_as2c);

    int j = 0;
    if (ndims > 0){
        fprintf(fout,"[%lld",clens[j]);
        for(j=1;j<ndims;++j){
            fprintf(fout,",%lld",clens[j]);
        }
        fprintf(fout,"] =");
    }
    for(j=0;j<narrs;++j){
        fprintf(fout," %s",hdrs[j]);
    }
    fprintf(fout,"\n");

    printMultiArrayNdFmt_WMaps(fout,narrs,A,fmt,ndims,clens,map_as2c);

    for(i=0;i<narrs;++i){
        free(map_as2c[i]);
    }
	free(map_as2c);
	free(clens);
	return;
}

void printMultiArrayNdFmtHdr(FILE *fout,int narrs,char *fmt,...){
    int i;
    char **hdrs = malloc(narrs*sizeof(char *));
    arr  **A    = malloc(narrs*sizeof(arr *));
	va_list arg_list;
	va_start(arg_list, fmt);
	for (i=0;i<narrs;++i){
		hdrs[i] = va_arg(arg_list, char *);
	}
	for (i=0;i<narrs;++i){
		A[i]    = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

	printMultiArrayNdFmtHdr_List(fout,narrs,hdrs,fmt,A);
    free(hdrs);
    free(A);
	return;
}



void printMultiArrayNdFmts_Loop(FILE *fout,int narrs,arr **A,char **fmts,
    typ_idx ndims,typ_idx **map_c2as,typ_idx **idxs,typ_idx dim,typ_idx *c,typ_idx *clens){
/*	This is a recursive n dimensional loop function	*/
    typ_idx i,j;

	if (dim == ndims){
        int k = 0;
        if (dim > 0){
            fprintf(fout,"[%lld",c[k]);
            for(k=1;k<dim;++k){
                fprintf(fout,",%lld",c[k]);
            }
            fprintf(fout,"] =");
        }
        for(k=0;k<narrs;++k){
            switch (A[k]->typ) {
            #define SWITCHCAST(swtyp,swmtyp,swcast,swmacro,swassign,cswassign,swcompare,fmt1,fmt2)	\
                fprintf(fout," ");  \
                fprintf(fout,fmts[k],cswassign(A[k],idxs[k]));
                ALLTYPECASES
                default:
                    fprintf(fout,"undefined type for array %d!\n",k);
                    print_arr_exit(A[k]);
                    exit(0);
                    break;
            }
            #undef SWITCHCAST
        }
        fprintf(fout,"\n");
		return;
	} else {
		for(c[dim]=0;c[dim]<clens[dim];c[dim]++){
            for (i=0;i<narrs;++i){
                j = map_c2as[i][dim];
                if (j >= 0){
                    idxs[i][j] = c[dim];
                }
            }
            printMultiArrayNdFmts_Loop(fout,narrs,A,fmts,ndims,map_c2as,idxs,dim+1,c,clens);
		}
	}

	return;
}

void printMultiArrayNdFmts_WMaps(FILE *fout,int narrs,arr **A,char **fmts,typ_idx ndims,typ_idx *clens,typ_idx **map_as2c) {
	typ_idx i;
    
    typ_idx **map_c2as = malloc(narrs*sizeof(typ_idx *));
	for(i=0;i<narrs;++i){ map_c2as[i] = mapdims_inverse(A[i]->n,ndims,map_as2c[i]); }

	if (ndims < 0){
    } else {
		typ_idx *c 	   = init0(ndims,TYPIDX);
        typ_idx **idxs = malloc(narrs*sizeof(typ_idx *));
        for (i=0;i<narrs;++i){
            idxs[i] = initNdIdxWMaps_NoAdims(c,A[i]->n,map_as2c[i]);
        }
        
		printMultiArrayNdFmts_Loop(fout,narrs,A,fmts,ndims,map_c2as,idxs,(typ_idx)0,c,clens);

        free(c);
        for (i=0;i<narrs;++i){
			free(idxs[i]);
		}
		free(idxs);
	}

    for(i=0;i<narrs;++i){
        free(map_c2as[i]);
    }
	free(map_c2as);
	return;
}

void printMultiArrayNdFmtsHdr_List(FILE *fout,int narrs,char **hdrs,char **fmts,arr **A) {
	typ_idx i,ndims;
	typ_idx **map_as2c;
	typ_idx *clens = mapdims_Nar(narrs,A,&ndims,&map_as2c);

    int j = 0;
    if (ndims > 0){
        fprintf(fout,"[%lld",clens[j]);
        for(j=1;j<ndims;++j){
            fprintf(fout,",%lld",clens[j]);
        }
        fprintf(fout,"] =");
    }
    for(j=0;j<narrs;++j){
        fprintf(fout," %s",hdrs[j]);
    }
    fprintf(fout,"\n");

    printMultiArrayNdFmts_WMaps(fout,narrs,A,fmts,ndims,clens,map_as2c);

    for(i=0;i<narrs;++i){
        free(map_as2c[i]);
    }
	free(map_as2c);
	free(clens);
	return;
}

void printMultiArrayNdFmtsHdr(FILE *fout,int narrs,...){
    int i;
    char **fmts = malloc(narrs*sizeof(char *));
    char **hdrs = malloc(narrs*sizeof(char *));
    arr  **A    = malloc(narrs*sizeof(arr *));
	va_list arg_list;
	va_start(arg_list, narrs);
	for (i=0;i<narrs;++i){
		fmts[i] = va_arg(arg_list, char *);
	}
	for (i=0;i<narrs;++i){
		hdrs[i] = va_arg(arg_list, char *);
	}
	for (i=0;i<narrs;++i){
		A[i]    = va_arg(arg_list, arr *);
	}
	va_end(arg_list);

	printMultiArrayNdFmtsHdr_List(fout,narrs,hdrs,fmts,A);
    free(fmts);
    free(hdrs);
    free(A);
	return;
}

#endif
