/* Created by Bill Scheftic */
#ifndef  _WRAP_HI2LO_H_
#define  _WRAP_HI2LO_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <hi2lo.h>

void wrap_Hi2LoIdxWgt(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 8,/*nints*/ 0,/*nidxs*/ 4,/*nrarrs*/ 5,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return;
            }
        }
    }
    grid grd_hi;
    grd_hi.lt = args->dblp[0];
    grd_hi.ln = args->dblp[1];
    grd_hi.dy = args->dblp[2];
    grd_hi.dx = args->dblp[3];
    grd_hi.y  = args->idxp[0];
    grd_hi.x  = args->idxp[1];
    
    grid grd_lo;
    grd_lo.lt = args->dblp[4];
    grd_lo.ln = args->dblp[5];
    grd_lo.dy = args->dblp[6];
    grd_lo.dx = args->dblp[7];
    grd_lo.y  = args->idxp[2];
    grd_lo.x  = args->idxp[3];

    arr    *N      = args->arrpp[0];
    arr    *jIdxs  = args->arrpp[1];
    arr    *iIdxs  = args->arrpp[2];
    arr    *Wgts   = args->arrpp[3];
    arr    *WgtSum = args->arrpp[4];
    Hi2LoIdxWgt(&grd_hi,&grd_lo,N,jIdxs,iIdxs,Wgts,WgtSum);
    return;
}

void wrap_Hi2LoIdxWgt_Ar(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 4,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 5,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr *lt_hi = args->arrays[0];
    arr *ln_hi = args->arrays[1];
    arr *lt_lo = args->arrays[2];
    arr *ln_lo = args->arrays[3];

    arr    *N      = args->arrpp[0];
    arr    *jIdxs  = args->arrpp[1];
    arr    *iIdxs  = args->arrpp[2];
    arr    *Wgts   = args->arrpp[3];
    arr    *WgtSum = args->arrpp[4];
    Hi2LoIdxWgt_Ar(lt_hi,ln_hi,lt_lo,ln_lo,N,jIdxs,iIdxs,Wgts,WgtSum);
    return;
}

arr wrap_upScaleIdxWgt(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 6,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr *IN     = args->arrays[0];
    arr *N      = args->arrays[1];
    arr *jIdxs  = args->arrays[2];
    arr *iIdxs  = args->arrays[3];
    arr *Wgts   = args->arrays[4];
    arr *WgtSum = args->arrays[5];
    
    arr rv     = upScaleIdxWgt(IN,N,jIdxs,iIdxs,Wgts,WgtSum);
    return rv;
}

void wrap_upScaleStatsIdxWgt(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 5,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 7,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    arr *IN        = args->arrays[0];
    arr *N         = args->arrays[1];
    arr *jIdxs     = args->arrays[2];
    arr *iIdxs     = args->arrays[3];
    arr *Wgts      = args->arrays[4];
    double thresh = args->dblp[0];
    arr    *Mn    = args->arrpp[0];
    arr    *min   = args->arrpp[1];
    arr    *max   = args->arrpp[2];
    arr    *med   = args->arrpp[3];
    arr    *FrAbv = args->arrpp[4];
    arr    *sigma = args->arrpp[5];
    arr    *MnAbv = args->arrpp[6];
    
    upScaleStatsIdxWgt(IN,N,jIdxs,iIdxs,Wgts,thresh,Mn,min,max,med,FrAbv,sigma,MnAbv);
    return;
}

#endif
