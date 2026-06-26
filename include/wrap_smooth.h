#ifndef  _WRAP_SMTH_H_
#define  _WRAP_SMTH_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <smoothing.h>

arr wrap_smthGauss2d(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }

    arr data = args->arrays[0];
    if (countNonMiss(&data) < 4){
        return *(arr *)args->missval;
    } else {
        arr bcrd = args->arrays[1];
        arr dcrd = args->arrays[2];
        double maxh = args->dblp[0];
        
        gridnd grd;
        setGridNdFromList(data.n,&grd,pntr_of(&bcrd),pntr_of(&dcrd),data.len);
        arr rv = smthGauss2d(&data,&grd,maxh);
        freeGridNd(&grd);
        return rv;
    }
}

arr wrap_smthGauss1d(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 1,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    int i;
    if (args->dblp_miss){
        for(i=0;i<args->ndbls;i++){
            if (args->dblp[i] == args->dblp_miss[i]){
                return *(arr *)args->missval;
            }
        }
    }

    arr data = args->arrays[0];
    if (countNonMiss(&data) < 4){
        return *(arr *)args->missval;
    } else {
        double bcrd = args->dblp[0];
        double dcrd = args->dblp[1];
        double maxh = args->dblp[2];
        
        typ_idx j = data.tlen-1;
        while(isMiss(&data,j)){ j--; } j++;

        gridnd grd;
        setGridNdFromList(data.n,&grd,&bcrd,&dcrd,&j);

        arr rv = smthGauss1d(&data,&grd,maxh);
        freeGridNd(&grd);
        return rv;
    }
}

#endif
