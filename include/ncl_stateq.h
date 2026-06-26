/* Created by Bill Scheftic */
#ifndef  _NCL_STATSEQ_H_
#define  _NCL_STATSEQ_H_

#include <stdio.h>
/*
 * The following are the required NCAR Graphics include files.
 * They should be located in ${NCARG_ROOT}/include
 */

#include <ncl_c_wrap.h>		/* Contains all included headers, Type conversion Macros, and getVarFromNCL function */
int mydebug = 0;
#include <arrayinit2.h>
#include <stats2.h>
#include <arraystats2.h>
#include <print_arrays2.h>

typ_idx **get_map_as2all(int narrs,arr *restrict Maps2All){
/*  fputs("get_map_as2all: \n",stderr);   */
    int i,j;
    typ_idx **map_as2all = NULL;
    typ_idx ndimspar;
    if (Maps2All->n == 0){
        ndimspar = 1; /* this may be 0? */
        map_as2all       = malloc(sizeof(typ_idx *));
        map_as2all[0]    = malloc(sizeof(typ_idx));
        map_as2all[0][0] = iINTG(Maps2All,(typ_idx)0);
    } else if (Maps2All->n == 1){
        if (narrs == 1){
            map_as2all = malloc(sizeof(typ_idx *));
            map_as2all[0] = malloc(Maps2All->tlen*sizeof(typ_idx));
            for (i=0;i<Maps2All->tlen;i++) {
                map_as2all[0][i] = iINTG(Maps2All,(typ_idx)i);
            }
        } else if (narrs > 1){
            map_as2all       = malloc(narrs*sizeof(typ_idx *));
            for (i=0;i<narrs;i++) {
                map_as2all[i]    = malloc(sizeof(typ_idx));
                map_as2all[i][0] = iINTG(Maps2All,(typ_idx)i);
            }
        } else {
            fprintf(stderr,"st_int_eqNarRNarNdblNint_Maps: narrs less than one, narrs=%d\n",narrs);
            exit(0);
        }
    } else if (Maps2All->n == 2){
        ndimspar = Maps2All->len[1];
        map_as2all       = malloc(narrs*sizeof(typ_idx *));
        for (i=0;i<narrs;i++) {
            map_as2all[i]    = malloc(ndimspar*sizeof(typ_idx));
            for (j=0;j<ndimspar;j++){
                map_as2all[i][j] = INTG(Maps2All,(typ_idx)i,(typ_idx)j);
            }
        }
    } else {
        /* shouldn't get here */
    }
    return map_as2all;
}
    
NhlErrorTypes st_dbl_eqNarRNarNdblNint( fctArgsRdbl fct,int narrs,int nrarrs,int nrdbls,int nrints ) {
    fprintf(stderr,"st_dbl_eqNarRNarNdblNint: input: %d arrays, output: %d arrays, %d doubles, %d ints\n",narrs,nrarrs,nrdbls,nrints);
    int i;
    typ_idx j;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    ng_size_t nstatdims;
    typ_idx n_dims;
    int ntot = narrs+nrarrs+nrdbls+nrints+1;
    int iarg = 0;
	arr  **arrays = malloc(narrs *sizeof(arr *));
	arr   *Rarr   = malloc(nrarrs*sizeof(arr));
	arr   *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr   *Rint   = malloc(nrints*sizeof(arr));

	for (i=0;i<narrs; ++i){ arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); ++iarg; }
	for (i=0;i<nrarrs;++i){ Rarr[i]   = getVarFromNCL (iarg,ntot); ++iarg; }
	for (i=0;i<nrdbls;++i){ Rdbl[i]   = getVarFromNCL (iarg,ntot); ++iarg; }
	for (i=0;i<nrints;++i){ Rint[i]   = getVarFromNCL (iarg,ntot); ++iarg; }
    arr StatDims = getVarFromNCL (iarg,ntot);
    typ_idx nstdims = 0;
    typ_idx *stdims = NULL;
    arr StatDims2 = castAr(&StatDims,TYPIDX,0);
    if (iIDX(&StatDims2,(typ_idx)0) > -1){
        nstdims = StatDims2.tlen;
        stdims  = pntr_of(&StatDims2);
    }

/*
 * Call the C function.
 */
	arr  **Rarr_t = malloc(nrarrs*sizeof(arr *));
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	for (i=0;i<nrarrs;i++){ Rarr_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }
    arr data = arNdArgNarNsNintRet1dblNarrNDblNInt(fct,narrs,0,0,nrarrs,nrdbls,nrints,
        arrays,NULL,NULL,Rarr_t,Rdbl_t,Rint_t,nstdims,stdims);
  
    NhlErrorTypes retval = returnArToNCL(&data);
    freeAr(&data);
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
	}
    typ_idx *lo = NULL;
    typ_idx *hi = NULL;
	for (i=0;i<nrarrs;i++){
        if (Rarr[i].n == Rarr_t[i]->n){
            lo = init0(Rarr[i].n,TYPIDX);
            hi = malloc(Rarr[i].n*sizeof *hi);
            for (j=0;j<Rarr[i].n;j++){
                hi[j] = imin(Rarr[i].len[j],Rarr_t[i]->len[j])-1;
            }
            assignSect(&Rarr[i], lo, hi, Rarr_t[i], lo, hi);
            freeAr(Rarr_t[i]);
            free(Rarr_t[i]);
            freeArShell(&Rarr[i]);
            free(lo);
            free(hi);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rarr[i].n,Rarr_t[i]->n);
            printArrayInfoWHdr(stderr,Rarr_t[i],"st_dbl_eqNarRNarNdblNint: Expected output, Rarr_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rarr[i]   ,"st_dbl_eqNarRNarNdblNint: Received output, Rarr[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"st_dbl_eqNarRNarNdblNint: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"st_dbl_eqNarRNarNdblNint: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"st_dbl_eqNarRNarNdblNint: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"st_dbl_eqNarRNarNdblNint: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
    freeArShell(&StatDims);
    
    freeAr(&StatDims2);
	free(arrays);
	free(Rarr  );
	free(Rdbl  );
	free(Rint  );
	free(Rarr_t);
	free(Rdbl_t);
	free(Rint_t);
    return(NhlNOERROR);
}

NhlErrorTypes st_int_eqNarRNarNdblNint( fctArgsRint fct,int narrs,int nrarrs,int nrdbls,int nrints ) {
    fprintf(stderr,"st_int_eqNarRNarNdblNint: input: %d arrays, output: %d arrays, %d doubles, %d ints\n",narrs,nrarrs,nrdbls,nrints);
    int i;
    typ_idx j;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    ng_size_t nstatdims;
    typ_idx n_dims;
    int ntot = narrs+nrarrs+nrdbls+nrints+1;
    int iarg = 0;
	arr  **arrays = malloc(narrs *sizeof(arr *));
	arr   *Rarr   = malloc(nrarrs*sizeof(arr));
	arr   *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr   *Rint   = malloc(nrints*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrarrs;i++){ Rarr[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }
    arr StatDims = getVarFromNCL (iarg,ntot);
    typ_idx nstdims = 0;
    typ_idx *stdims = NULL;
    arr StatDims2 = castAr(&StatDims,TYPIDX,0);
    if (iIDX(&StatDims2,(typ_idx)0) > -1){
        nstdims = StatDims2.tlen;
        stdims  = pntr_of(&StatDims2);
    }

/*
 * Call the C function.
 */
	arr  **Rarr_t = malloc(nrarrs*sizeof(arr *));
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	for (i=0;i<nrarrs;i++){ Rarr_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }
    arr data = arNdArgNarNsNintRet1intNarrNDblNInt(fct,narrs,0,0,nrarrs,nrdbls,nrints,
        arrays,NULL,NULL,Rarr_t,Rdbl_t,Rint_t,nstdims,stdims);
  
    NhlErrorTypes retval = returnArToNCL(&data);
    freeAr(&data);
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
	}
    typ_idx *lo = NULL;
    typ_idx *hi = NULL;
	for (i=0;i<nrarrs;i++){
        if (Rarr[i].n == Rarr_t[i]->n){
            lo = init0(Rarr[i].n,TYPIDX);
            hi = malloc(Rarr[i].n*sizeof *hi);
            for (j=0;j<Rarr[i].n;j++){
                hi[j] = imin(Rarr[i].len[j],Rarr_t[i]->len[j])-1;
            }
            assignSect(&Rarr[i], lo, hi, Rarr_t[i], lo, hi);
            freeAr(Rarr_t[i]);
            free(Rarr_t[i]);
            freeArShell(&Rarr[i]);
            free(lo);
            free(hi);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rarr[i].n,Rarr_t[i]->n);
            printArrayInfoWHdr(stderr,Rarr_t[i],"st_int_eqNarRNarNdblNint: Expected output, Rarr_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rarr[i]   ,"st_int_eqNarRNarNdblNint: Received output, Rarr[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"st_int_eqNarRNarNdblNint: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"st_int_eqNarRNarNdblNint: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"st_int_eqNarRNarNdblNint: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"st_int_eqNarRNarNdblNint: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
    freeArShell(&StatDims);

    freeAr(&StatDims2);
	free(arrays);
	free(Rarr  );
	free(Rdbl  );
	free(Rint  );
	free(Rarr_t);
	free(Rdbl_t);
	free(Rint_t);
    return(NhlNOERROR);
}

NhlErrorTypes st_idx_eqNarRNarNdblNintNidx( fctArgsRidx fct,int narrs,int nrarrs,int nrdbls,int nrints,int nridxs ) {
    fprintf(stderr,"st_idx_eqNarRNarNdblNintNidx: input: %d arrays, output: %d arrays, %d doubles, %d ints, %d idxs\n",narrs,nrarrs,nrdbls,nrints,nridxs);
    int i;
    typ_idx j;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    ng_size_t nstatdims;
    typ_idx n_dims;
    int ntot = narrs+nrarrs+nrdbls+nrints+nridxs+1;
    int iarg = 0;
	arr  **arrays = malloc(narrs *sizeof(arr *));
	arr   *Rarr   = malloc(nrarrs*sizeof(arr));
	arr   *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr   *Rint   = malloc(nrints*sizeof(arr));
	arr   *Ridx   = malloc(nridxs*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrarrs;i++){ Rarr[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nridxs;i++){ Ridx[i]   = getVarFromNCL (iarg,ntot); iarg++; }
    arr StatDims = getVarFromNCL (iarg,ntot);
    typ_idx nstdims = 0;
    typ_idx *stdims = NULL;
    arr StatDims2 = castAr(&StatDims,TYPIDX,0);
    if (iIDX(&StatDims2,(typ_idx)0) > -1){
        nstdims = StatDims2.tlen;
        stdims  = pntr_of(&StatDims2);
    }

/*
 * Call the C function.
 */
	arr  **Rarr_t = malloc(nrarrs*sizeof(arr *));
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	arr  **Ridx_t = malloc(nridxs*sizeof(arr *));
	for (i=0;i<nrarrs;i++){ Rarr_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nridxs;i++){ Ridx_t[i] = malloc(sizeof(arr)); }

    arr data = arNdArgNarNsNintNidxRet1idxNarrNDblNIntNIdx(fct,narrs,0,0,0,nrarrs,nrdbls,nrints,nridxs,
        arrays,NULL,NULL,NULL,Rarr_t,Rdbl_t,Rint_t,Ridx_t,nstdims,stdims);
  
    NhlErrorTypes retval = returnArToNCL(&data);
    freeAr(&data);
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
	}
    typ_idx *lo = NULL;
    typ_idx *hi = NULL;
	for (i=0;i<nrarrs;i++){
        if (Rarr[i].n == Rarr_t[i]->n){
            lo = init0(Rarr[i].n,TYPIDX);
            hi = malloc(Rarr[i].n*sizeof *hi);
            for (j=0;j<Rarr[i].n;j++){
                hi[j] = imin(Rarr[i].len[j],Rarr_t[i]->len[j])-1;
            }
            assignSect(&Rarr[i], lo, hi, Rarr_t[i], lo, hi);
            freeAr(Rarr_t[i]);
            free(Rarr_t[i]);
            freeArShell(&Rarr[i]);
            free(lo);
            free(hi);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rarr[i].n,Rarr_t[i]->n);
            printArrayInfoWHdr(stderr,Rarr_t[i],"st_idx_eqNarRNarNdblNintNidx: Expected output, Rarr_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rarr[i]   ,"st_idx_eqNarRNarNdblNintNidx: Received output, Rarr[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"st_idx_eqNarRNarNdblNintNidx: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"st_idx_eqNarRNarNdblNintNidx: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"st_idx_eqNarRNarNdblNintNidx: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"st_idx_eqNarRNarNdblNintNidx: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nridxs;i++){
        if (Ridx[i].n == Ridx_t[i]->n){
            copyArVals(&Ridx[i],Ridx_t[i]);
            freeAr(Ridx_t[i]);
            free(Ridx_t[i]);
            freeArShell(&Ridx[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Ridx[i].n,Ridx_t[i]->n);
            printArrayInfoWHdr(stderr,Ridx_t[i],"st_idx_eqNarRNarNdblNintNidx: Expected output, Ridx_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Ridx[i]   ,"st_idx_eqNarRNarNdblNintNidx: Received output, Ridx[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
    freeArShell(&StatDims);
    
    freeAr(&StatDims2);
	free(arrays);
	free(Rarr  );
	free(Rdbl  );
	free(Rint  );
	free(Ridx  );
	free(Rarr_t);
	free(Rdbl_t);
	free(Rint_t);
	free(Ridx_t);
    return(NhlNOERROR);
}

NhlErrorTypes st_eqNarRNarNdblNint( fctArgsNoRet fct,int narrs,int nrarrs,int nrdbls,int nrints ) {
    fprintf(stderr,"st_eqNarRNarNdblNint: input: %d arrays, output: %d arrays, %d doubles, %d ints\n",narrs,nrarrs,nrdbls,nrints);
    int i;
    typ_idx j;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    ng_size_t nstatdims;
    typ_idx n_dims;
    int ntot = narrs+nrarrs+nrdbls+nrints+1;
    int iarg = 0;
	arr  **arrays = malloc(narrs *sizeof(arr *));
	arr   *Rarr   = malloc(nrarrs*sizeof(arr));
	arr   *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr   *Rint   = malloc(nrints*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrarrs;i++){ Rarr[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }
    arr StatDims = getVarFromNCL (iarg,ntot);
    typ_idx nstdims = 0;
    typ_idx *stdims = NULL;
    arr StatDims2 = castAr(&StatDims,TYPIDX,0);
    if (iIDX(&StatDims2,(typ_idx)0) > -1){
        nstdims = StatDims2.tlen;
        stdims  = pntr_of(&StatDims2);
    }

/*
 * Call the C function.
 */
	arr  **Rarr_t = malloc(nrarrs*sizeof(arr *));
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	for (i=0;i<nrarrs;i++){ Rarr_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }
    arNdArgNarNsNintRetVoidNarrNDblNInt(fct,narrs,0,0,nrarrs,nrdbls,nrints,
        arrays,NULL,NULL,Rarr_t,Rdbl_t,Rint_t,nstdims,stdims);
  
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
	}
    typ_idx *lo = NULL;
    typ_idx *hi = NULL;
	for (i=0;i<nrarrs;i++){
        if (Rarr[i].n == Rarr_t[i]->n){
            lo = init0(Rarr[i].n,TYPIDX);
            hi = malloc(Rarr[i].n*sizeof *hi);
            for (j=0;j<Rarr[i].n;j++){
                hi[j] = imin(Rarr[i].len[j],Rarr_t[i]->len[j])-1;
            }
            assignSect(&Rarr[i], lo, hi, Rarr_t[i], lo, hi);
            freeAr(Rarr_t[i]);
            free(Rarr_t[i]);
            freeArShell(&Rarr[i]);
            free(lo);
            free(hi);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rarr[i].n,Rarr_t[i]->n);
            printArrayInfoWHdr(stderr,Rarr_t[i],"st_eqNarRNarNdblNint: Expected output, Rarr_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rarr[i]   ,"st_eqNarRNarNdblNint: Received output, Rarr[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"st_eqNarRNarNdblNint: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"st_eqNarRNarNdblNint: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"st_eqNarRNarNdblNint: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"st_eqNarRNarNdblNint: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
    freeArShell(&StatDims);

    freeAr(&StatDims2);
	free(arrays);
	free(Rarr  );
	free(Rdbl  );
	free(Rint  );
	free(Rarr_t);
	free(Rdbl_t);
	free(Rint_t);
    return(NhlNOERROR);
}

NhlErrorTypes st_arr_eqNarRNarNdblNint( fctArgsRarr fct,int narrs,int nrarrs,int nrdbls,int nrints ) {
    fprintf(stderr,"st_arr_eqNarRNarNdblNint: input: %d arrays, output: %d arrays, %d doubles, %d ints\n",narrs,nrarrs,nrdbls,nrints);
    int i;
    typ_idx j;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    ng_size_t nstatdims;
    int ntot = narrs+nrarrs+nrdbls+nrints+1;
    int iarg = 0;
	arr  **arrays = malloc(narrs *sizeof(arr *));
	arr   *Rarr   = malloc(nrarrs*sizeof(arr));
	arr   *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr   *Rint   = malloc(nrints*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrarrs;i++){ Rarr[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }
    arr StatDims = getVarFromNCL (iarg,ntot);

/*
 * Call the C function.
 */
	arr  **Rarr_t = malloc(nrarrs*sizeof(arr *));
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	for (i=0;i<nrarrs;i++){ Rarr_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }

    typ_idx nstdims = 0;
    typ_idx *stdims = NULL;
    arr StatDims2 = castAr(&StatDims,TYPIDX,0);
    if (iIDX(&StatDims2,(typ_idx)0) > -1){
        nstdims = StatDims2.tlen;
        stdims  = pntr_of(&StatDims2);
    }
    
    arr data = arNdArgNarNsNintRet1arrNarrNDblNInt(fct,narrs,0,0,nrarrs,nrdbls,nrints,
        arrays,NULL,NULL,Rarr_t,Rdbl_t,Rint_t,nstdims,stdims);
  
    NhlErrorTypes retval = returnArToNCL(&data);
    freeAr(&data);
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
	}
    typ_idx *lo = NULL;
    typ_idx *hi = NULL;
	for (i=0;i<nrarrs;i++){
        if (Rarr[i].n == Rarr_t[i]->n){
            lo = init0(Rarr[i].n,TYPIDX);
            hi = malloc(Rarr[i].n*sizeof *hi);
            for (j=0;j<Rarr[i].n;j++){
                hi[j] = imin(Rarr[i].len[j],Rarr_t[i]->len[j])-1;
            }
            assignSect(&Rarr[i], lo, hi, Rarr_t[i], lo, hi);
            freeAr(Rarr_t[i]);
            free(Rarr_t[i]);
            freeArShell(&Rarr[i]);
            free(lo);
            free(hi);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rarr[i].n,Rarr_t[i]->n);
            printArrayInfoWHdr(stderr,Rarr_t[i],"st_arr_eqNarRNarNdblNint: Expected output, Rarr_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rarr[i]   ,"st_arr_eqNarRNarNdblNint: Received output, Rarr[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"st_arr_eqNarRNarNdblNint: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"st_arr_eqNarRNarNdblNint: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"st_arr_eqNarRNarNdblNint: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"st_arr_eqNarRNarNdblNint: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
    freeArShell(&StatDims);

    freeAr(&StatDims2);
	free(arrays);
	free(Rarr  );
	free(Rdbl  );
	free(Rint  );
	free(Rarr_t);
	free(Rdbl_t);
	free(Rint_t);
    return(NhlNOERROR);
}

NhlErrorTypes st_arr_eqNarRNarNdblNintNidx( fctArgsRarr fct,int narrs,int nrarrs,int nrdbls,int nrints,int nridxs ) {
    fprintf(stderr,"st_arr_eqNarRNarNdblNintNidx: input: %d arrays, output: %d arrays, %d doubles, %d ints, %d idxs\n",narrs,nrarrs,nrdbls,nrints,nridxs);
    int i;
    typ_idx j;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    ng_size_t nstatdims;
    int ntot = narrs+nrarrs+nrdbls+nrints+nridxs+1;
    int iarg = 0;
	arr  **arrays = malloc(narrs *sizeof(arr *));
	arr   *Rarr   = malloc(nrarrs*sizeof(arr));
	arr   *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr   *Rint   = malloc(nrints*sizeof(arr));
	arr   *Ridx   = malloc(nridxs*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrarrs;i++){ Rarr[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nridxs;i++){ Ridx[i]   = getVarFromNCL (iarg,ntot); iarg++; }
    arr StatDims = getVarFromNCL (iarg,ntot);

/*
 * Call the C function.
 */
	arr  **Rarr_t = malloc(nrarrs*sizeof(arr *));
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	arr  **Ridx_t = malloc(nridxs*sizeof(arr *));
	for (i=0;i<nrarrs;i++){ Rarr_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nridxs;i++){ Ridx_t[i] = malloc(sizeof(arr)); }

    typ_idx nstdims = 0;
    typ_idx *stdims = NULL;
    arr StatDims2 = castAr(&StatDims,TYPIDX,0);
    if (iIDX(&StatDims2,(typ_idx)0) > -1){
        nstdims = StatDims2.tlen;
        stdims  = pntr_of(&StatDims2);
    }
    
    arr data = arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx(fct,narrs,0,0,0,nrarrs,nrdbls,nrints,nridxs,
        arrays,NULL,NULL,NULL,Rarr_t,Rdbl_t,Rint_t,Ridx_t,nstdims,stdims);
  
    NhlErrorTypes retval = returnArToNCL(&data);
    freeAr(&data);
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
	}
    typ_idx *lo = NULL;
    typ_idx *hi = NULL;
	for (i=0;i<nrarrs;i++){
        if (Rarr[i].n == Rarr_t[i]->n){
            lo = init0(Rarr[i].n,TYPIDX);
            hi = malloc(Rarr[i].n*sizeof *hi);
            for (j=0;j<Rarr[i].n;j++){
                hi[j] = imin(Rarr[i].len[j],Rarr_t[i]->len[j])-1;
            }
            assignSect(&Rarr[i], lo, hi, Rarr_t[i], lo, hi);
            freeAr(Rarr_t[i]);
            free(Rarr_t[i]);
            freeArShell(&Rarr[i]);
            free(lo);
            free(hi);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rarr[i].n,Rarr_t[i]->n);
            printArrayInfoWHdr(stderr,Rarr_t[i],"st_arr_eqNarRNarNdblNintNidx: Expected output, Rarr_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rarr[i]   ,"st_arr_eqNarRNarNdblNintNidx: Received output, Rarr[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"st_arr_eqNarRNarNdblNintNidx: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"st_arr_eqNarRNarNdblNintNidx: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"st_arr_eqNarRNarNdblNintNidx: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"st_arr_eqNarRNarNdblNintNidx: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nridxs;i++){
        if (Ridx[i].n == Ridx_t[i]->n){
            copyArVals(&Ridx[i],Ridx_t[i]);
            freeAr(Ridx_t[i]);
            free(Ridx_t[i]);
            freeArShell(&Ridx[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Ridx[i].n,Ridx_t[i]->n);
            printArrayInfoWHdr(stderr,Ridx_t[i],"st_arr_eqNarRNarNdblNintNidx: Expected output, Ridx_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Ridx[i]   ,"st_arr_eqNarRNarNdblNintNidx: Received output, Ridx[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
    freeArShell(&StatDims);

    freeAr(&StatDims2);
	free(arrays);
	free(Rarr  );
	free(Rdbl  );
	free(Rint  );
	free(Ridx  );
	free(Rarr_t);
	free(Rdbl_t);
	free(Rint_t);
	free(Ridx_t);
    return(NhlNOERROR);
}



NhlErrorTypes st_dbl_eqNarRNarNdblNint_Maps( fctArgsRdbl fct,int narrs,int nrarrs,int nrdbls,int nrints ) {
    fprintf(stderr,"st_dbl_eqNarRNarNdblNint_Maps: input: %d arrays, output: %d arrays, %d doubles, %d ints\n",narrs,nrarrs,nrdbls,nrints);
    int i;
    typ_idx j;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    ng_size_t nstatdims;
    typ_idx n_dims;
    int ntot = narrs+nrarrs+nrdbls+nrints+2;
    int iarg = 0;
	arr  **arrays = malloc(narrs *sizeof(arr *));
	arr   *Rarr   = malloc(nrarrs*sizeof(arr));
	arr   *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr   *Rint   = malloc(nrints*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrarrs;i++){ Rarr[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }
    arr StatDims = getVarFromNCL (iarg,ntot); iarg++;
    arr Maps2All = getVarFromNCL (iarg,ntot);

/*
 * Call the C function.
 */
	arr  **Rarr_t = malloc(nrarrs*sizeof(arr *));
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	for (i=0;i<nrarrs;i++){ Rarr_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }

    typ_idx **map_as2all = get_map_as2all(narrs,&Maps2All);

    /* allows for no dimension to be acted on by passing -1 */
    typ_idx nstdims = 0;
    typ_idx *stdims = NULL;
    arr StatDims2 = castAr(&StatDims,TYPIDX,0);
    if (iIDX(&StatDims2,(typ_idx)0) > -1){
        nstdims = StatDims2.tlen;
        stdims  = pntr_of(&StatDims2);
    }
    
    typ_idx nalldims;
    typ_idx *all_len = mapdims_Nar_2(narrs,arrays,map_as2all,&nalldims);
    arr data = arNdArgNarNsNintRet1dblNarrNDblNInt_WMaps(fct,narrs,0,0,nrarrs,nrdbls,nrints,
        arrays,NULL,NULL,Rarr_t,Rdbl_t,Rint_t,nstdims,stdims,nalldims,all_len,map_as2all);
  
    NhlErrorTypes retval = returnArToNCL(&data);
    freeAr(&data);
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
        free(map_as2all[i]);
	}
    free(map_as2all);
    typ_idx *lo = NULL;
    typ_idx *hi = NULL;
	for (i=0;i<nrarrs;i++){
        if (Rarr[i].n == Rarr_t[i]->n){
            lo = init0(Rarr[i].n,TYPIDX);
            hi = malloc(Rarr[i].n*sizeof *hi);
            for (j=0;j<Rarr[i].n;j++){
                hi[j] = imin(Rarr[i].len[j],Rarr_t[i]->len[j])-1;
            }
            assignSect(&Rarr[i], lo, hi, Rarr_t[i], lo, hi);
            freeAr(Rarr_t[i]);
            free(Rarr_t[i]);
            freeArShell(&Rarr[i]);
            free(lo);
            free(hi);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rarr[i].n,Rarr_t[i]->n);
            printArrayInfoWHdr(stderr,Rarr_t[i],"st_dbl_eqNarRNarNdblNint_Maps: Expected output, Rarr_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rarr[i]   ,"st_dbl_eqNarRNarNdblNint_Maps: Received output, Rarr[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"st_dbl_eqNarRNarNdblNint_Maps: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"st_dbl_eqNarRNarNdblNint_Maps: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"st_dbl_eqNarRNarNdblNint_Maps: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"st_dbl_eqNarRNarNdblNint_Maps: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
    freeArShell(&StatDims);
    freeArShell(&Maps2All);
    
    free(all_len);
    freeAr(&StatDims2);
	free(arrays);
	free(Rarr  );
	free(Rdbl  );
	free(Rint  );
	free(Rarr_t);
	free(Rdbl_t);
	free(Rint_t);
    return(NhlNOERROR);
}

NhlErrorTypes st_dbl_eqNarRNarNdblNintNidx_Maps( fctArgsRdbl fct,int narrs,int nrarrs,int nrdbls,int nrints,int nridxs ) {
    fprintf(stderr,"st_dbl_eqNarRNarNdblNintNidx_Maps: input: %d arrays, output: %d arrays, %d doubles, %d ints, %d idxs\n",narrs,nrarrs,nrdbls,nrints,nridxs);
    int i;
    typ_idx j;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    ng_size_t nstatdims;
    typ_idx n_dims;
    int ntot = narrs+nrarrs+nrdbls+nrints+nridxs+2;
    int iarg = 0;
	arr  **arrays = malloc(narrs *sizeof(arr *));
	arr   *Rarr   = malloc(nrarrs*sizeof(arr));
	arr   *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr   *Rint   = malloc(nrints*sizeof(arr));
	arr   *Ridx   = malloc(nridxs*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrarrs;i++){ Rarr[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nridxs;i++){ Ridx[i]   = getVarFromNCL (iarg,ntot); iarg++; }
    arr StatDims = getVarFromNCL (iarg,ntot); iarg++;
    arr Maps2All = getVarFromNCL (iarg,ntot);

/*
 * Call the C function.
 */
	arr  **Rarr_t = malloc(nrarrs*sizeof(arr *));
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	arr  **Ridx_t = malloc(nridxs*sizeof(arr *));
	for (i=0;i<nrarrs;i++){ Rarr_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nridxs;i++){ Ridx_t[i] = malloc(sizeof(arr)); }

    typ_idx **map_as2all = get_map_as2all(narrs,&Maps2All);

    typ_idx nstdims = 0;
    typ_idx *stdims = NULL;
    arr StatDims2 = castAr(&StatDims,TYPIDX,0);
    if (iIDX(&StatDims2,(typ_idx)0) > -1){
        nstdims = StatDims2.tlen;
        stdims  = pntr_of(&StatDims2);
    }
    
    typ_idx nalldims;
    typ_idx *all_len = mapdims_Nar_2(narrs,arrays,map_as2all,&nalldims);
    arr data = arNdArgNarNsNintNidxRet1dblNarrNDblNIntNIdx_WMaps(fct,narrs,0,0,0,nrarrs,nrdbls,nrints,nridxs,
        arrays,NULL,NULL,NULL,Rarr_t,Rdbl_t,Rint_t,Ridx_t,nstdims,stdims,nalldims,all_len,map_as2all);
  
    NhlErrorTypes retval = returnArToNCL(&data);
    freeAr(&data);
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
        free(map_as2all[i]);
	}
    free(map_as2all);
    typ_idx *lo = NULL;
    typ_idx *hi = NULL;
	for (i=0;i<nrarrs;i++){
        if (Rarr[i].n == Rarr_t[i]->n){
            lo = init0(Rarr[i].n,TYPIDX);
            hi = malloc(Rarr[i].n*sizeof *hi);
            for (j=0;j<Rarr[i].n;j++){
                hi[j] = imin(Rarr[i].len[j],Rarr_t[i]->len[j])-1;
            }
            assignSect(&Rarr[i], lo, hi, Rarr_t[i], lo, hi);
            freeAr(Rarr_t[i]);
            free(Rarr_t[i]);
            freeArShell(&Rarr[i]);
            free(lo);
            free(hi);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rarr[i].n,Rarr_t[i]->n);
            printArrayInfoWHdr(stderr,Rarr_t[i],"st_dbl_eqNarRNarNdblNintNidx_Maps: Expected output, Rarr_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rarr[i]   ,"st_dbl_eqNarRNarNdblNintNidx_Maps: Received output, Rarr[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"st_dbl_eqNarRNarNdblNintNidx_Maps: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"st_dbl_eqNarRNarNdblNintNidx_Maps: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"st_dbl_eqNarRNarNdblNintNidx_Maps: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"st_dbl_eqNarRNarNdblNintNidx_Maps: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nridxs;i++){
        if (Ridx[i].n == Ridx_t[i]->n){
            copyArVals(&Ridx[i],Ridx_t[i]);
            freeAr(Ridx_t[i]);
            free(Ridx_t[i]);
            freeArShell(&Ridx[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Ridx[i].n,Ridx_t[i]->n);
            printArrayInfoWHdr(stderr,Ridx_t[i],"st_dbl_eqNarRNarNdblNintNidx_Maps: Expected output, Ridx_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Ridx[i]   ,"st_dbl_eqNarRNarNdblNintNidx_Maps: Received output, Ridx[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
    freeArShell(&StatDims);
    freeArShell(&Maps2All);
    
    free(all_len);
    freeAr(&StatDims2);
	free(arrays);
	free(Rarr  );
	free(Rdbl  );
	free(Rint  );
	free(Ridx  );
	free(Rarr_t);
	free(Rdbl_t);
	free(Rint_t);
	free(Ridx_t);
    return(NhlNOERROR);
}

NhlErrorTypes st_int_eqNarRNarNdblNint_Maps( fctArgsRint fct,int narrs,int nrarrs,int nrdbls,int nrints ) {
    fprintf(stderr,"st_int_eqNarRNarNdblNint_Maps: input: %d arrays, output: %d arrays, %d doubles, %d ints\n",narrs,nrarrs,nrdbls,nrints);
    int i;
    typ_idx j;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    ng_size_t nstatdims;
    typ_idx n_dims;
    int ntot = narrs+nrarrs+nrdbls+nrints+2;
    int iarg = 0;
	arr  **arrays = malloc(narrs *sizeof(arr *));
	arr   *Rarr   = malloc(nrarrs*sizeof(arr));
	arr   *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr   *Rint   = malloc(nrints*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrarrs;i++){ Rarr[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }
    arr StatDims = getVarFromNCL (iarg,ntot); iarg++;
    arr Maps2All = getVarFromNCL (iarg,ntot);

/*
 * Call the C function.
 */
	arr  **Rarr_t = malloc(nrarrs*sizeof(arr *));
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	for (i=0;i<nrarrs;i++){ Rarr_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }

    typ_idx **map_as2all = get_map_as2all(narrs,&Maps2All);

    typ_idx nstdims = 0;
    typ_idx *stdims = NULL;
    arr StatDims2 = castAr(&StatDims,TYPIDX,0);
    if (iIDX(&StatDims2,(typ_idx)0) > -1){
        nstdims = StatDims2.tlen;
        stdims  = pntr_of(&StatDims2);
    }
    
    typ_idx nalldims;
    typ_idx *all_len = mapdims_Nar_2(narrs,arrays,map_as2all,&nalldims);
    arr data = arNdArgNarNsNintRet1intNarrNDblNInt_WMaps(fct,narrs,0,0,nrarrs,nrdbls,nrints,
        arrays,NULL,NULL,Rarr_t,Rdbl_t,Rint_t,nstdims,stdims,nalldims,all_len,map_as2all);
  
    NhlErrorTypes retval = returnArToNCL(&data);
    freeAr(&data);
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
        free(map_as2all[i]);
	}
    free(map_as2all);
    typ_idx *lo = NULL;
    typ_idx *hi = NULL;
	for (i=0;i<nrarrs;i++){
        if (Rarr[i].n == Rarr_t[i]->n){
            lo = init0(Rarr[i].n,TYPIDX);
            hi = malloc(Rarr[i].n*sizeof *hi);
            for (j=0;j<Rarr[i].n;j++){
                hi[j] = imin(Rarr[i].len[j],Rarr_t[i]->len[j])-1;
            }
            assignSect(&Rarr[i], lo, hi, Rarr_t[i], lo, hi);
            freeAr(Rarr_t[i]);
            free(Rarr_t[i]);
            freeArShell(&Rarr[i]);
            free(lo);
            free(hi);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rarr[i].n,Rarr_t[i]->n);
            printArrayInfoWHdr(stderr,Rarr_t[i],"st_int_eqNarRNarNdblNint_Maps: Expected output, Rarr_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rarr[i]   ,"st_int_eqNarRNarNdblNint_Maps: Received output, Rarr[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"st_int_eqNarRNarNdblNint_Maps: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"st_int_eqNarRNarNdblNint_Maps: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"st_int_eqNarRNarNdblNint_Maps: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"st_int_eqNarRNarNdblNint_Maps: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
    freeArShell(&StatDims);
    freeArShell(&Maps2All);
    
    free(all_len);
    freeAr(&StatDims2);
	free(arrays);
	free(Rarr  );
	free(Rdbl  );
	free(Rint  );
	free(Rarr_t);
	free(Rdbl_t);
	free(Rint_t);
    return(NhlNOERROR);
}

NhlErrorTypes st_idx_eqNarRNarNdblNintNidx_Maps( fctArgsRidx fct,int narrs,int nrarrs,int nrdbls,int nrints,int nridxs ) {
    fprintf(stderr,"st_idx_eqNarRNarNdblNintNidx_Maps: input: %d arrays, output: %d arrays, %d doubles, %d ints, %d idxs\n",narrs,nrarrs,nrdbls,nrints,nridxs);
    int i;
    typ_idx j;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    ng_size_t nstatdims;
    typ_idx n_dims;
    int ntot = narrs+nrarrs+nrdbls+nrints+nridxs+2;
    int iarg = 0;
	arr  **arrays = malloc(narrs *sizeof(arr *));
	arr   *Rarr   = malloc(nrarrs*sizeof(arr));
	arr   *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr   *Rint   = malloc(nrints*sizeof(arr));
	arr   *Ridx   = malloc(nridxs*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrarrs;i++){ Rarr[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nridxs;i++){ Ridx[i]   = getVarFromNCL (iarg,ntot); iarg++; }
    arr StatDims = getVarFromNCL (iarg,ntot); iarg++;
    arr Maps2All = getVarFromNCL (iarg,ntot);

/*
 * Call the C function.
 */
	arr  **Rarr_t = malloc(nrarrs*sizeof(arr *));
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	arr  **Ridx_t = malloc(nridxs*sizeof(arr *));
	for (i=0;i<nrarrs;i++){ Rarr_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nridxs;i++){ Ridx_t[i] = malloc(sizeof(arr)); }

    typ_idx **map_as2all = get_map_as2all(narrs,&Maps2All);

    typ_idx nstdims = 0;
    typ_idx *stdims = NULL;
    arr StatDims2 = castAr(&StatDims,TYPIDX,0);
    if (iIDX(&StatDims2,(typ_idx)0) > -1){
        nstdims = StatDims2.tlen;
        stdims  = pntr_of(&StatDims2);
    }
    
    typ_idx nalldims;
    typ_idx *all_len = mapdims_Nar_2(narrs,arrays,map_as2all,&nalldims);
    arr data = arNdArgNarNsNintNidxRet1idxNarrNDblNIntNIdx_WMaps(fct,narrs,0,0,0,nrarrs,nrdbls,nrints,nridxs,
        arrays,NULL,NULL,NULL,Rarr_t,Rdbl_t,Rint_t,Ridx_t,nstdims,stdims,nalldims,all_len,map_as2all);
  
    NhlErrorTypes retval = returnArToNCL(&data);
    freeAr(&data);
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
        free(map_as2all[i]);
	}
    free(map_as2all);
    typ_idx *lo = NULL;
    typ_idx *hi = NULL;
	for (i=0;i<nrarrs;i++){
        if (Rarr[i].n == Rarr_t[i]->n){
            lo = init0(Rarr[i].n,TYPIDX);
            hi = malloc(Rarr[i].n*sizeof *hi);
            for (j=0;j<Rarr[i].n;j++){
                hi[j] = imin(Rarr[i].len[j],Rarr_t[i]->len[j])-1;
            }
            assignSect(&Rarr[i], lo, hi, Rarr_t[i], lo, hi);
            freeAr(Rarr_t[i]);
            free(Rarr_t[i]);
            freeArShell(&Rarr[i]);
            free(lo);
            free(hi);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rarr[i].n,Rarr_t[i]->n);
            printArrayInfoWHdr(stderr,Rarr_t[i],"st_idx_eqNarRNarNdblNintNidx_Maps: Expected output, Rarr_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rarr[i]   ,"st_idx_eqNarRNarNdblNintNidx_Maps: Received output, Rarr[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"st_idx_eqNarRNarNdblNintNidx_Maps: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"st_idx_eqNarRNarNdblNintNidx_Maps: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"st_idx_eqNarRNarNdblNintNidx_Maps: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"st_idx_eqNarRNarNdblNintNidx_Maps: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nridxs;i++){
        if (Ridx[i].n == Ridx_t[i]->n){
            copyArVals(&Ridx[i],Ridx_t[i]);
            freeAr(Ridx_t[i]);
            free(Ridx_t[i]);
            freeArShell(&Ridx[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Ridx[i].n,Ridx_t[i]->n);
            printArrayInfoWHdr(stderr,Ridx_t[i],"st_idx_eqNarRNarNdblNintNidx_Maps: Expected output, Ridx_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Ridx[i]   ,"st_idx_eqNarRNarNdblNintNidx_Maps: Received output, Ridx[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
    freeArShell(&StatDims);
    freeArShell(&Maps2All);
    
    free(all_len);
    freeAr(&StatDims2);
	free(arrays);
	free(Rarr  );
	free(Rdbl  );
	free(Rint  );
	free(Ridx  );
	free(Rarr_t);
	free(Rdbl_t);
	free(Rint_t);
	free(Ridx_t);
    return(NhlNOERROR);
}

NhlErrorTypes st_eqNarRNarNdblNint_Maps( fctArgsNoRet fct,int narrs,int nrarrs,int nrdbls,int nrints ) {
    fprintf(stderr,"st_eqNarRNarNdblNint_Maps: input: %d arrays, output: %d arrays, %d doubles, %d ints\n",narrs,nrarrs,nrdbls,nrints);
    int i;
    typ_idx j;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    ng_size_t nstatdims;
    typ_idx n_dims;
    int ntot = narrs+nrarrs+nrdbls+nrints+2;
    int iarg = 0;
	arr  **arrays = malloc(narrs *sizeof(arr *));
	arr   *Rarr   = malloc(nrarrs*sizeof(arr));
	arr   *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr   *Rint   = malloc(nrints*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrarrs;i++){ Rarr[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }
    arr StatDims = getVarFromNCL (iarg,ntot); iarg++;
    arr Maps2All = getVarFromNCL (iarg,ntot);

/*
 * Call the C function.
 */
	arr  **Rarr_t = malloc(nrarrs*sizeof(arr *));
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	for (i=0;i<nrarrs;i++){ Rarr_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }

    typ_idx **map_as2all = get_map_as2all(narrs,&Maps2All);

    typ_idx nstdims = 0;
    typ_idx *stdims = NULL;
    arr StatDims2 = castAr(&StatDims,TYPIDX,0);
    if (iIDX(&StatDims2,(typ_idx)0) > -1){
        nstdims = StatDims2.tlen;
        stdims  = pntr_of(&StatDims2);
    }
    
    typ_idx nalldims;
    typ_idx *all_len = mapdims_Nar_2(narrs,arrays,map_as2all,&nalldims);
    arNdArgNarNsNintRetVoidNarrNDblNInt_WMaps(fct,narrs,0,0,nrarrs,nrdbls,nrints,
        arrays,NULL,NULL,Rarr_t,Rdbl_t,Rint_t,nstdims,stdims,nalldims,all_len,map_as2all);
  
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
        free(map_as2all[i]);
	}
    free(map_as2all);
    typ_idx *lo = NULL;
    typ_idx *hi = NULL;
	for (i=0;i<nrarrs;i++){
        if (Rarr[i].n == Rarr_t[i]->n){
            lo = init0(Rarr[i].n,TYPIDX);
            hi = malloc(Rarr[i].n*sizeof *hi);
            for (j=0;j<Rarr[i].n;j++){
                hi[j] = imin(Rarr[i].len[j],Rarr_t[i]->len[j])-1;
            }
            assignSect(&Rarr[i], lo, hi, Rarr_t[i], lo, hi);
            freeAr(Rarr_t[i]);
            free(Rarr_t[i]);
            freeArShell(&Rarr[i]);
            free(lo);
            free(hi);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rarr[i].n,Rarr_t[i]->n);
            printArrayInfoWHdr(stderr,Rarr_t[i],"st_eqNarRNarNdblNint_Maps: Expected output, Rarr_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rarr[i]   ,"st_eqNarRNarNdblNint_Maps: Received output, Rarr[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"st_eqNarRNarNdblNint_Maps: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"st_eqNarRNarNdblNint_Maps: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"st_eqNarRNarNdblNint_Maps: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"st_eqNarRNarNdblNint_Maps: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
    freeArShell(&StatDims);
    freeArShell(&Maps2All);
    
    free(all_len);
    freeAr(&StatDims2);
	free(arrays);
	free(Rarr  );
	free(Rdbl  );
	free(Rint  );
	free(Rarr_t);
	free(Rdbl_t);
	free(Rint_t);
    return(NhlNOERROR);
}

NhlErrorTypes st_eqNarRNarNdblNintNidx_Maps( fctArgsNoRet fct,int narrs,int nrarrs,int nrdbls,int nrints,int nridxs ) {
    fprintf(stderr,"st_eqNarRNarNdblNintNidx_Maps: input: %d arrays, output: %d arrays, %d doubles, %d ints, %d idxs\n",narrs,nrarrs,nrdbls,nrints,nridxs);
    int i;
    typ_idx j;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    ng_size_t nstatdims;
    typ_idx n_dims;
    int ntot = narrs+nrarrs+nrdbls+nrints+nridxs+2;
    int iarg = 0;
	arr  **arrays = malloc(narrs *sizeof(arr *));
	arr   *Rarr   = malloc(nrarrs*sizeof(arr));
	arr   *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr   *Rint   = malloc(nrints*sizeof(arr));
	arr   *Ridx   = malloc(nridxs*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrarrs;i++){ Rarr[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nridxs;i++){ Ridx[i]   = getVarFromNCL (iarg,ntot); iarg++; }
/*
	for (i=0;i<narrs;i++) { printArrayInfoWHdr(stderr,arrays[i],"arrays[%d] - ",i); }
	for (i=0;i<nrarrs;i++){ printArrayInfoWHdr(stderr,&Rarr[i], "Rarr[%d] - ",  i); }
	for (i=0;i<nrdbls;i++){ printArrayInfoWHdr(stderr,&Rdbl[i], "Rdbl[%d] - ",  i); }
	for (i=0;i<nrints;i++){ printArrayInfoWHdr(stderr,&Rint[i], "Rint[%d] - ",  i); }
	for (i=0;i<nridxs;i++){ printArrayInfoWHdr(stderr,&Ridx[i], "Ridx[%d] - ",  i); }
*/
    arr StatDims = getVarFromNCL (iarg,ntot); iarg++;
    arr Maps2All = getVarFromNCL (iarg,ntot);
/*
    printArrayInfoWHdr(stderr,&StatDims,"StatDims - ");
    printArrayInfoWHdr(stderr,&Maps2All,"Maps2All - ");
*/
/*
 * Call the C function.
 */
	arr  **Rarr_t = malloc(nrarrs*sizeof(arr *));
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	arr  **Ridx_t = malloc(nridxs*sizeof(arr *));
	for (i=0;i<nrarrs;i++){ Rarr_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nridxs;i++){ Ridx_t[i] = malloc(sizeof(arr)); }

    typ_idx **map_as2all = get_map_as2all(narrs,&Maps2All);

    typ_idx nstdims = 0;
    typ_idx *stdims = NULL;
    arr StatDims2 = castAr(&StatDims,TYPIDX,0);
    if (iIDX(&StatDims2,(typ_idx)0) > -1){
        nstdims = StatDims2.tlen;
        stdims  = pntr_of(&StatDims2);
    }
    
    typ_idx nalldims;
    typ_idx *all_len = mapdims_Nar_2(narrs,arrays,map_as2all,&nalldims);
/*  fputs("st_eqNarRNarNdblNintNidx_Maps: before arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_WMaps\n",stderr); */
    arNdArgNarNsNintNidxRetVoidNarrNDblNIntNIdx_WMaps(fct,narrs,0,0,0,nrarrs,nrdbls,nrints,nridxs,
        arrays,NULL,NULL,NULL,Rarr_t,Rdbl_t,Rint_t,Ridx_t,nstdims,stdims,nalldims,all_len,map_as2all);
  
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
        free(map_as2all[i]);
	}
    free(map_as2all);
    typ_idx *lo = NULL;
    typ_idx *hi = NULL;
	for (i=0;i<nrarrs;i++){
        if (isArNull(Rarr_t[i])){
            fillArWithMiss(&Rarr[i]);
        } else {
            if (Rarr[i].n == Rarr_t[i]->n){
                lo = init0(Rarr[i].n,TYPIDX);
                hi = malloc(Rarr[i].n*sizeof *hi);
                for (j=0;j<Rarr[i].n;j++){
                    hi[j] = imin(Rarr[i].len[j],Rarr_t[i]->len[j])-1;
                /*  fprintf(stderr,"dim %lld: lo=%lld, hi=%lld\n",j,lo[j],hi[j]);   */
                }
                assignSect(&Rarr[i], lo, hi, Rarr_t[i], lo, hi);
                freeAr(Rarr_t[i]);
                free(lo);
                free(hi);
            } else {
                fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rarr[i].n,Rarr_t[i]->n);
                printArrayInfoWHdr(stderr,Rarr_t[i],"st_eqNarRNarNdblNintNidx_Maps: Expected output, Rarr_t[%d] - ",i);
                printArrayInfoWHdr(stderr,&Rarr[i]   ,"st_eqNarRNarNdblNintNidx_Maps: Received output, Rarr[%d]   - ",i);
                exit(EXIT_FAILURE);
            }
        }
        free(Rarr_t[i]);
        freeArShell(&Rarr[i]);
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"st_eqNarRNarNdblNintNidx_Maps: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"st_eqNarRNarNdblNintNidx_Maps: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"st_eqNarRNarNdblNintNidx_Maps: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"st_eqNarRNarNdblNintNidx_Maps: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nridxs;i++){
        if (Ridx[i].n == Ridx_t[i]->n){
            copyArVals(&Ridx[i],Ridx_t[i]);
            freeAr(Ridx_t[i]);
            free(Ridx_t[i]);
            freeArShell(&Ridx[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Ridx[i].n,Ridx_t[i]->n);
            printArrayInfoWHdr(stderr,Ridx_t[i],"st_eqNarRNarNdblNintNidx_Maps: Expected output, Ridx_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Ridx[i]   ,"st_eqNarRNarNdblNintNidx_Maps: Received output, Ridx[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
    freeArShell(&StatDims);
    freeArShell(&Maps2All);
    
    free(all_len);
    freeAr(&StatDims2);
	free(arrays);
	free(Rarr  );
	free(Rdbl  );
	free(Rint  );
	free(Ridx  );
	free(Rarr_t);
	free(Rdbl_t);
	free(Rint_t);
	free(Ridx_t);
    return(NhlNOERROR);
}


NhlErrorTypes st_arr_eqNarRNarNdblNint_Maps( fctArgsRarr fct,int narrs,int nrarrs,int nrdbls,int nrints ) {
    fprintf(stderr,"st_arr_eqNarRNarNdblNint_Maps: input: %d arrays, output: %d arrays, %d doubles, %d ints\n",narrs,nrarrs,nrdbls,nrints);
    int i;
    typ_idx j;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    ng_size_t nstatdims;
    typ_idx n_dims;
    int ntot = narrs+nrarrs+nrdbls+nrints+2;
    int iarg = 0;
	arr  **arrays = malloc(narrs *sizeof(arr *));
	arr   *Rarr   = malloc(nrarrs*sizeof(arr));
	arr   *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr   *Rint   = malloc(nrints*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrarrs;i++){ Rarr[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }
    arr StatDims = getVarFromNCL (iarg,ntot); iarg++;
    arr Maps2All = getVarFromNCL (iarg,ntot);
    /*
    printArrayFmtAllWHdr(stderr,&StatDims,"%d","StatDims - ");
    printArrayFmtAllWHdr(stderr,&Maps2All,"%d","Maps2All - ");
     */

/*
 * Call the C function.
 */
	arr  **Rarr_t = malloc(nrarrs*sizeof(arr *));
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	for (i=0;i<nrarrs;i++){ Rarr_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }

    typ_idx **map_as2all = get_map_as2all(narrs,&Maps2All);

    typ_idx nstdims = 0;
    typ_idx *stdims = NULL;
    arr StatDims2 = castAr(&StatDims,TYPIDX,0);
    if (iIDX(&StatDims2,(typ_idx)0) > -1){
        nstdims = StatDims2.tlen;
        stdims  = pntr_of(&StatDims2);
    }
    
    typ_idx nalldims;
    typ_idx *all_len = mapdims_Nar_2(narrs,arrays,map_as2all,&nalldims);
    arr data = arNdArgNarNsNintRet1arrNarrNDblNInt_WMaps(fct,narrs,0,0,nrarrs,nrdbls,nrints,
        arrays,NULL,NULL,Rarr_t,Rdbl_t,Rint_t,nstdims,stdims,nalldims,all_len,map_as2all);
  
    NhlErrorTypes retval = returnArToNCL(&data);
    freeAr(&data);
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
        free(map_as2all[i]);
	}
    free(map_as2all);
    typ_idx *lo = NULL;
    typ_idx *hi = NULL;
	for (i=0;i<nrarrs;i++){
        if (Rarr[i].n == Rarr_t[i]->n){
            lo = init0(Rarr[i].n,TYPIDX);
            hi = malloc(Rarr[i].n*sizeof *hi);
            for (j=0;j<Rarr[i].n;j++){
                hi[j] = imin(Rarr[i].len[j],Rarr_t[i]->len[j])-1;
            }
            assignSect(&Rarr[i], lo, hi, Rarr_t[i], lo, hi);
            freeAr(Rarr_t[i]);
            free(Rarr_t[i]);
            freeArShell(&Rarr[i]);
            free(lo);
            free(hi);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rarr[i].n,Rarr_t[i]->n);
            printArrayInfoWHdr(stderr,Rarr_t[i],"st_arr_eqNarRNarNdblNint_Maps: Expected output, Rarr_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rarr[i]   ,"st_arr_eqNarRNarNdblNint_Maps: Received output, Rarr[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"st_arr_eqNarRNarNdblNint_Maps: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"st_arr_eqNarRNarNdblNint_Maps: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"st_arr_eqNarRNarNdblNint_Maps: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"st_arr_eqNarRNarNdblNint_Maps: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
    freeArShell(&StatDims);
    freeArShell(&Maps2All);
    
    free(all_len);
    freeAr(&StatDims2);
	free(arrays);
	free(Rarr  );
	free(Rdbl  );
	free(Rint  );
	free(Rarr_t);
	free(Rdbl_t);
	free(Rint_t);
    return(NhlNOERROR);
}

NhlErrorTypes st_arr_eqNarRNarNdblNintNidx_Maps( fctArgsRarr fct,int narrs,int nrarrs,int nrdbls,int nrints,int nridxs ) {
    fprintf(stderr,"st_arr_eqNarRNarNdblNintNidx_Maps: input: %d arrays, output: %d arrays, %d doubles, %d ints, %d idxs\n",narrs,nrarrs,nrdbls,nrints,nridxs);
    int i;
    typ_idx j;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    ng_size_t nstatdims;
    typ_idx n_dims;
    int ntot = narrs+nrarrs+nrdbls+nrints+nridxs+2;
    int iarg = 0;
	arr  **arrays = malloc(narrs *sizeof(arr *));
	arr   *Rarr   = malloc(nrarrs*sizeof(arr));
	arr   *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr   *Rint   = malloc(nrints*sizeof(arr));
	arr   *Ridx   = malloc(nridxs*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrarrs;i++){ Rarr[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nridxs;i++){ Ridx[i]   = getVarFromNCL (iarg,ntot); iarg++; }
/*
	for (i=0;i<narrs;i++) { printArrayInfoWHdr(stderr,arrays[i],"arrays[%d] - ",i); }
	for (i=0;i<nrarrs;i++){ printArrayInfoWHdr(stderr,Rarr[i]  ,"Rarr[%d]   - ",i); }
	for (i=0;i<nrdbls;i++){ printArrayInfoWHdr(stderr,Rdbl[i]  ,"Rdbl[%d]   - ",i); }
	for (i=0;i<nrints;i++){ printArrayInfoWHdr(stderr,Rint[i]  ,"Rint[%d]   - ",i); }
	for (i=0;i<nridxs;i++){ printArrayInfoWHdr(stderr,Ridx[i]  ,"Ridx[%d]   - ",i); }
*/
    arr StatDims = getVarFromNCL (iarg,ntot); iarg++;
    arr Maps2All = getVarFromNCL (iarg,ntot);
/*
    printArrayInfoWHdr(stderr,StatDims,"StatDims - ");
    printArrayInfoWHdr(stderr,Maps2All,"Maps2All - ");
*/
/*
 * Call the C function.
 */
	arr  **Rarr_t = malloc(nrarrs*sizeof(arr *));
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	arr  **Ridx_t = malloc(nridxs*sizeof(arr *));
	for (i=0;i<nrarrs;i++){ Rarr_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nridxs;i++){ Ridx_t[i] = malloc(sizeof(arr)); }

    typ_idx **map_as2all = get_map_as2all(narrs,&Maps2All);

    typ_idx nstdims = 0;
    typ_idx *stdims = NULL;
    arr StatDims2 = castAr(&StatDims,TYPIDX,0);
    if (iIDX(&StatDims2,(typ_idx)0) > -1){
        nstdims = StatDims2.tlen;
        stdims  = pntr_of(&StatDims2);
    }
    
    typ_idx nalldims;
    typ_idx *all_len = mapdims_Nar_2(narrs,arrays,map_as2all,&nalldims);
    arr data = arNdArgNarNsNintNidxRet1arrNarrNDblNIntNIdx_WMaps(fct,narrs,0,0,0,nrarrs,nrdbls,nrints,nridxs,
        arrays,NULL,NULL,NULL,Rarr_t,Rdbl_t,Rint_t,Ridx_t,nstdims,stdims,nalldims,all_len,map_as2all);
  
    NhlErrorTypes retval = returnArToNCL(&data);
    /* printArrayAllWHdr(stderr,&data,"data - "); */
    freeAr(&data);
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
        free(map_as2all[i]);
	}
    free(map_as2all);
    typ_idx *lo = NULL;
    typ_idx *hi = NULL;
	for (i=0;i<nrarrs;i++){
        if (Rarr[i].n == Rarr_t[i]->n){
            lo = init0(Rarr[i].n,TYPIDX);
            hi = malloc(Rarr[i].n*sizeof *hi);
            for (j=0;j<Rarr[i].n;j++){
                hi[j] = imin(Rarr[i].len[j],Rarr_t[i]->len[j])-1;
            /*  fprintf(stderr,"dim %lld: lo=%lld, hi=%lld\n",j,lo[j],hi[j]);    */
            }
            assignSect(&Rarr[i], lo, hi, Rarr_t[i], lo, hi);
            freeAr(Rarr_t[i]);
            free(Rarr_t[i]);
            freeArShell(&Rarr[i]);
            free(lo);
            free(hi);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rarr[i].n,Rarr_t[i]->n);
            printArrayInfoWHdr(stderr,Rarr_t[i],"st_arr_eqNarRNarNdblNintNidx_Maps: Expected output, Rarr_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rarr[i]   ,"st_arr_eqNarRNarNdblNintNidx_Maps: Received output, Rarr[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"st_arr_eqNarRNarNdblNintNidx_Maps: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"st_arr_eqNarRNarNdblNintNidx_Maps: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"st_arr_eqNarRNarNdblNintNidx_Maps: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"st_arr_eqNarRNarNdblNintNidx_Maps: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nridxs;i++){
        if (Ridx[i].n == Ridx_t[i]->n){
            copyArVals(&Ridx[i],Ridx_t[i]);
            freeAr(Ridx_t[i]);
            free(Ridx_t[i]);
            freeArShell(&Ridx[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Ridx[i].n,Ridx_t[i]->n);
            printArrayInfoWHdr(stderr,Ridx_t[i],"st_arr_eqNarRNarNdblNintNidx_Maps: Expected output, Ridx_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Ridx[i]   ,"st_arr_eqNarRNarNdblNintNidx_Maps: Received output, Ridx[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
    freeArShell(&StatDims);
    freeArShell(&Maps2All);
    
    free(all_len);
    freeAr(&StatDims2);
	free(arrays);
	free(Rarr  );
	free(Rdbl  );
	free(Rint  );
	free(Ridx  );
	free(Rarr_t);
	free(Rdbl_t);
	free(Rint_t);
	free(Ridx_t);
    return(NhlNOERROR);
}




NhlErrorTypes mth_dbl_eqNarRNdblNint( fctArgsRdbl fct,int narrs,int nrdbls,int nrints ) {
    fprintf(stderr,"mth_dbl_eqNarRNdblNint: input: %d arrays, output: %d doubles, %d ints\n",narrs,nrdbls,nrints);
    int i;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    typ_idx n_dims;
    int ntot = narrs+nrdbls+nrints;
    int iarg = 0;
	arr **arrays = malloc(narrs *sizeof(arr *));
	arr *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr *Rint   = malloc(nrints*sizeof(arr));
    
	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }

/*
 * Call the C function.
 */
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }

    arr data = ndmath_dbl_NarNsNint_RNDblNInt(fct,narrs,0,0,nrdbls,nrints,
        arrays,NULL,NULL,Rdbl_t,Rint_t);
  
    NhlErrorTypes retval = returnArToNCL(&data);
    freeAr(&data);
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"mth_dbl_eqNarRNdblNint: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"mth_dbl_eqNarRNdblNint: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"mth_dbl_eqNarRNdblNint: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"mth_dbl_eqNarRNdblNint: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}

	free(arrays);
	free(Rdbl  );
	free(Rint  );
	free(Rdbl_t);
	free(Rint_t);
    return(NhlNOERROR);
}

NhlErrorTypes mth_int_eqNarRNdblNint( fctArgsRint fct,int narrs,int nrdbls,int nrints ) {
    fprintf(stderr,"mth_int_eqNarRNdblNint: input: %d arrays, output: %d doubles, %d ints\n",narrs,nrdbls,nrints);
    int i;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    typ_idx n_dims;
    int ntot = narrs+nrdbls+nrints;
    int iarg = 0;
	arr **arrays = malloc(narrs *sizeof(arr *));
	arr *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr *Rint   = malloc(nrints*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }

/*
 * Call the C function.
 */
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }
    arr data = ndmath_int_NarNsNint_RNDblNInt(fct,narrs,0,0,nrdbls,nrints,
        arrays,NULL,NULL,Rdbl_t,Rint_t);
  
    NhlErrorTypes retval = returnArToNCL(&data);
    freeAr(&data);
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"mth_int_eqNarRNdblNint: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"mth_int_eqNarRNdblNint: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"mth_int_eqNarRNdblNint: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"mth_int_eqNarRNdblNint: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}

	free(arrays);
	free(Rdbl  );
	free(Rint  );
	free(Rdbl_t);
	free(Rint_t);
    return(NhlNOERROR);
}

NhlErrorTypes mth_eqNarRNdblNint    ( fctArgsNoRet fct,int narrs,int nrdbls,int nrints ) {
    fprintf(stderr,"mth_eqNarRNdblNint: input: %d arrays, output: %d doubles, %d ints\n",narrs,nrdbls,nrints);
    int i;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    typ_idx n_dims;
    int ntot = narrs+nrdbls+nrints;
    int iarg = 0;
	arr **arrays = malloc(narrs *sizeof(arr *));
	arr *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr *Rint   = malloc(nrints*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }

/*
 * Call the C function.
 */
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }
    ndmath_NarNsNint_RNDblNInt(fct,narrs,0,0,nrdbls,nrints,
        arrays,NULL,NULL,Rdbl_t,Rint_t);
  
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"mth_eqNarRNdblNint: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"mth_eqNarRNdblNint: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"mth_eqNarRNdblNint: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"mth_eqNarRNdblNint: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}

	free(arrays);
	free(Rdbl  );
	free(Rint  );
	free(Rdbl_t);
	free(Rint_t);
    return(NhlNOERROR);
}



NhlErrorTypes mth_dbl_eqNarRNdblNint_Maps( fctArgsRdbl fct,int narrs,int nrdbls,int nrints ) {
    fprintf(stderr,"mth_dbl_eqNarRNdblNint_Maps: input: %d arrays, output: %d doubles, %d ints\n",narrs,nrdbls,nrints);
    int i;
    typ_idx j;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    typ_idx n_dims;
    int ntot = narrs+nrdbls+nrints+1;
    int iarg = 0;
	arr **arrays = malloc(narrs *sizeof(arr *));
	arr *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr *Rint   = malloc(nrints*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }
    arr Maps = getVarFromNCL (iarg,ntot);
    
    typ_idx **map_as2c = get_map_as2all(narrs,&Maps);

    typ_idx ndims = 0;
    typ_idx *clens = mapdims_Nar_2(narrs,arrays,map_as2c,&ndims);
/*
 * Call the C function.
 */
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }
    arr data = ndmath_dbl_NarNsNint_RNDblNInt_WMaps(fct,narrs,0,0,nrdbls,nrints,
        arrays,NULL,NULL,Rdbl_t,Rint_t,ndims,clens,map_as2c);
  
    for(i=0;i<narrs;i++){
        free(map_as2c[i]);
    }
	free(map_as2c);
	free(clens);
  
    NhlErrorTypes retval = returnArToNCL(&data);
    freeAr(&data);
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"mth_dbl_eqNarRNdblNint_Maps: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"mth_dbl_eqNarRNdblNint_Maps: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"mth_dbl_eqNarRNdblNint_Maps: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"mth_dbl_eqNarRNdblNint_Maps: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
    freeArShell(&Maps);

	free(arrays);
	free(Rdbl  );
	free(Rint  );
	free(Rdbl_t);
	free(Rint_t);
    return(NhlNOERROR);
}

NhlErrorTypes mth_int_eqNarRNdblNint_Maps( fctArgsRint fct,int narrs,int nrdbls,int nrints ) {
    fprintf(stderr,"mth_int_eqNarRNdblNint_Maps: input: %d arrays, output: %d doubles, %d ints\n",narrs,nrdbls,nrints);
    int i;
    typ_idx j;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    typ_idx n_dims;
    int ntot = narrs+nrdbls+nrints+1;
    int iarg = 0;
	arr **arrays = malloc(narrs *sizeof(arr *));
	arr *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr *Rint   = malloc(nrints*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }
    arr Maps = getVarFromNCL (iarg,ntot);
    
    typ_idx **map_as2c = get_map_as2all(narrs,&Maps);

    typ_idx ndims = 0;
    typ_idx *clens = mapdims_Nar_2(narrs,arrays,map_as2c,&ndims);
/*
 * Call the C function.
 */
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }
    arr data = ndmath_int_NarNsNint_RNDblNInt_WMaps(fct,narrs,0,0,nrdbls,nrints,
        arrays,NULL,NULL,Rdbl_t,Rint_t,ndims,clens,map_as2c);

    for(i=0;i<narrs;i++){
        free(map_as2c[i]);
    }
	free(map_as2c);
	free(clens);
  
    NhlErrorTypes retval = returnArToNCL(&data);
    freeAr(&data);
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"mth_int_eqNarRNdblNint_Maps: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"mth_int_eqNarRNdblNint_Maps: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"mth_int_eqNarRNdblNint_Maps: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"mth_int_eqNarRNdblNint_Maps: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
    freeArShell(&Maps);

	free(arrays);
	free(Rdbl  );
	free(Rint  );
	free(Rdbl_t);
	free(Rint_t);
    return(NhlNOERROR);
}

NhlErrorTypes mth_eqNarRNdblNint_Maps    ( fctArgsNoRet fct,int narrs,int nrdbls,int nrints ) {
    fprintf(stderr,"mth_eqNarRNdblNint_Maps: input: %d arrays, output: %d doubles, %d ints\n",narrs,nrdbls,nrints);
    int i;
    typ_idx j;

/*
 * Retrieve arguments from NCL function call. It doesn't matter
 * what order you call them in.
 */
    typ_idx n_dims;
    int ntot = narrs+nrdbls+nrints+1;
    int iarg = 0;
	arr **arrays = malloc(narrs *sizeof(arr *));
	arr *Rdbl   = malloc(nrdbls*sizeof(arr));
	arr *Rint   = malloc(nrints*sizeof(arr));

	for (i=0;i<narrs;i++) { arrays[i] = malloc(sizeof(arr)); *arrays[i] = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrdbls;i++){ Rdbl[i]   = getVarFromNCL (iarg,ntot); iarg++; }
	for (i=0;i<nrints;i++){ Rint[i]   = getVarFromNCL (iarg,ntot); iarg++; }
    arr Maps = getVarFromNCL (iarg,ntot);
    
    typ_idx **map_as2c = get_map_as2all(narrs,&Maps);

    typ_idx ndims = 0;
    typ_idx *clens = mapdims_Nar_2(narrs,arrays,map_as2c,&ndims);
/*
 * Call the C function.
 */
	arr  **Rdbl_t = malloc(nrdbls*sizeof(arr *));
	arr  **Rint_t = malloc(nrints*sizeof(arr *));
	for (i=0;i<nrdbls;i++){ Rdbl_t[i] = malloc(sizeof(arr)); }
	for (i=0;i<nrints;i++){ Rint_t[i] = malloc(sizeof(arr)); }
    ndmath_NarNsNint_RNDblNInt_WMaps(fct,narrs,0,0,nrdbls,nrints,
        arrays,NULL,NULL,Rdbl_t,Rint_t,ndims,clens,map_as2c);
  
    for(i=0;i<narrs;i++){
        free(map_as2c[i]);
    }
	free(map_as2c);
	free(clens);
  
	for (i=0;i<narrs;i++){
        freeArShell(arrays[i]);
        free(arrays[i]);
	}
	for (i=0;i<nrdbls;i++){
        if (Rdbl[i].n == Rdbl_t[i]->n){
            copyArVals(&Rdbl[i],Rdbl_t[i]);
            freeAr(Rdbl_t[i]);
            free(Rdbl_t[i]);
            freeArShell(&Rdbl[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rdbl[i].n,Rdbl_t[i]->n);
            printArrayInfoWHdr(stderr,Rdbl_t[i],"mth_eqNarRNdblNint_Maps: Expected output, Rdbl_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rdbl[i]   ,"mth_eqNarRNdblNint_Maps: Received output, Rdbl[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
	for (i=0;i<nrints;i++){
        if (Rint[i].n == Rint_t[i]->n){
            copyArVals(&Rint[i],Rint_t[i]);
            freeAr(Rint_t[i]);
            free(Rint_t[i]);
            freeArShell(&Rint[i]);
        } else {
            fprintf(stderr,"Dimension mismatch of output array, expected %lld dims, received %lld",Rint[i].n,Rint_t[i]->n);
            printArrayInfoWHdr(stderr,Rint_t[i],"mth_eqNarRNdblNint_Maps: Expected output, Rint_t[%d] - ",i);
            printArrayInfoWHdr(stderr,&Rint[i]   ,"mth_eqNarRNdblNint_Maps: Received output, Rint[%d]   - ",i);
            exit(EXIT_FAILURE);
        }
	}
    freeArShell(&Maps);

	free(arrays);
	free(Rdbl  );
	free(Rint  );
	free(Rdbl_t);
	free(Rint_t);
    return(NhlNOERROR);
}

#endif
