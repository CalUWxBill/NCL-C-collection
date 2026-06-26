/* Created by Bill Scheftic */
/*
 *  Area upscaling of rectilinear grids
 *  - First weights are calculated using Hi2LoIdxWgt_Ar or Hi2LoIdxWgt
 *  - Then upScaleIdxWgt or upScaleStatsIdxWgt uses the weights
 *    to upscale any dataset containing the hi resolution grid
 *  - upScaleIdxWgt calculated the areally averaged value only.
 *  - upScaleStatsIdxWgt calculates additional stats about the upscaled data in each grid.
 */
#ifndef  _HI2LO_H_
#define  _HI2LO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <math_supp.h>
#include <arrayinit2.h>
#include <print_arrays2.h>
#include <wrap_math.h>
#include <arraymath2.h>
#include <stats2.h>
#include <grid2.h>

const double pi_180 = M_PI/180.0;
const double R_sq   = 40680159.61000001;

double dSinLat(double lt1, double lt2) {
	double rlt1 = lt1*pi_180;
	double rlt2 = lt2*pi_180;
	return fabs(sin(rlt1)-sin(rlt2));
}

double dLongitude(double ln1, double ln2) {
	return fabs(ln1-ln2);
}

double earthArea2(double dsnlt, double dln) {
	return pi_180*R_sq*dsnlt*dln;
}

void Hi2LoIdxWgt(grid *restrict grd_hi,grid *restrict grd_lo,arr *N,arr *jIdxs,arr *iIdxs,arr *Wgts,arr *WgtSum){
    fprintf(stderr,"Hi2LoIdxWgt: hi: lt=%g, ln=%g, dy=%g, dx = %g, y=%lld, x=%lld\n"
        ,grd_hi->lt,grd_hi->ln,grd_hi->dy,grd_hi->dx,grd_hi->y,grd_hi->x);
    fprintf(stderr,"Hi2LoIdxWgt: lo: lt=%g, ln=%g, dy=%g, dx = %g, y=%lld, x=%lld\n"
        ,grd_lo->lt,grd_lo->ln,grd_lo->dy,grd_lo->dx,grd_lo->y,grd_lo->x);
    typ_idx nyhiplo = (grd_lo->dy/grd_hi->dy+2);
	arr jIdxsTmp = Array(2,TYPIDX,grd_lo->y,nyhiplo);
	arr jWgtsTmp = Array(2,DOUBLE,grd_lo->y,nyhiplo);
	arr    jNTmp = Array(1,TYPIDX,grd_lo->y);
    fillArWithMiss(&jIdxsTmp);
    fillArWithMiss(&jWgtsTmp);
    fillArWithMiss(&jNTmp);
	typ_idx j,l,il,linit,lend;
    double bot,top,lt1,lt2;
	for (j=0;j<grd_lo->y;j++) {
		bot = grd_lo->lt + ((double)j-0.5)*grd_lo->dy;
		top = grd_lo->lt + ((double)j+0.5)*grd_lo->dy;
		linit = myRound2((bot-grd_hi->lt)/grd_hi->dy);
		lend  = myRound2((top-grd_hi->lt)/grd_hi->dy);
        if ((linit >= grd_hi->y) || (lend  <  0)){
            iIDX(&jNTmp,j) = 0;
        } else {
            if (linit <  0)        { linit = 0; }
            if (lend  >= grd_hi->y) { lend  = grd_hi->y-1; }
            iIDX(&jNTmp,j) = lend-linit+1;
            for (l=linit;l<=lend;l++) {
                il = l-linit;
                IDX(&jIdxsTmp,j,il) = l;
                lt1 = grd_hi->lt + ((double)l-0.5)*grd_hi->dy;
                lt2 = grd_hi->lt + ((double)l+0.5)*grd_hi->dy;
                if (bot > lt1) { lt1 = bot; }
                if (top < lt2) { lt2 = top; }
                DBL(&jWgtsTmp,j,il) = dSinLat(lt1,lt2);
            }
        }
	}
/*
    printArrayFmtAllWHdr(stderr, jNTmp,    "%lld", "Hi2LoIdxWgt: jNTmp - ");
    printArrayFmtAllWHdr(stderr, jIdxsTmp, "%lld", "Hi2LoIdxWgt: jIdxsTmp - ");
    printArrayFmtAllWHdr(stderr, jWgtsTmp, "%.5f",  "Hi2LoIdxWgt: jWgtsTmp - ");
*/
    typ_idx nxhiplo = (grd_lo->dx/grd_hi->dx+2);
	arr iIdxsTmp = Array(2,TYPIDX,grd_lo->x,nxhiplo);
	arr iWgtsTmp = Array(2,DOUBLE,grd_lo->x,nxhiplo);
	arr    iNTmp = Array(1,TYPIDX,grd_lo->x);
    fillArWithMiss(&iIdxsTmp);
    fillArWithMiss(&iWgtsTmp);
    fillArWithMiss(&iNTmp);
	typ_idx i,k,ik,kinit,kend;
    double left,right,ln1,ln2;
    for (i=0;i<grd_lo->x;i++) {
        left  = grd_lo->ln + ((double)i-0.5)*grd_lo->dx;
        right = grd_lo->ln + ((double)i+0.5)*grd_lo->dx;
        kinit = myRound2((left-grd_hi->ln)/grd_hi->dx);
        kend  = myRound2((right-grd_hi->ln)/grd_hi->dx);
        if ((kinit >= grd_hi->x) || (kend  <  0)){
            iIDX(&iNTmp,i) = 0;
        } else {
            if (kinit <  0)        { kinit = 0; }
            if (kend  >= grd_hi->x) { kend  = grd_hi->x-1; }
            iIDX(&iNTmp,i) = kend-kinit+1;
            for (k=kinit;k<=kend;k++) {
                ik = k-kinit;
                IDX(&iIdxsTmp,i,ik) = k;
                ln1 = grd_hi->ln + ((double)k-0.5)*grd_hi->dx;
                ln2 = grd_hi->ln + ((double)k+0.5)*grd_hi->dx;
                if (left > ln1) { ln1 = left; }
                if (right < ln2) { ln2 = right; }
                DBL(&iWgtsTmp,i,ik) = dLongitude(ln1,ln2);
            }
        }
    }
/*
    printArrayFmtAllWHdr(stderr, iNTmp,    "%lld", "Hi2LoIdxWgt: iNTmp - ");
    printArrayFmtAllWHdr(stderr, iIdxsTmp, "%lld", "Hi2LoIdxWgt: iIdxsTmp - ");
    printArrayFmtAllWHdr(stderr, iWgtsTmp, "%.2f", "Hi2LoIdxWgt: iWgtsTmp - ");
*/
    typ_idx n, nj, nhiplo = 0;
	*N = Array(2,TYPIDX,grd_lo->y,grd_lo->x);
    fillArWithMiss(N);
	for (j=0;j<grd_lo->y;j++) {
        nj = iIDX(&jNTmp,j);
		for (i=0;i<grd_lo->x;i++) {
            n = nj*iIDX(&iNTmp,i);
			IDX(N,j,i) = n;
            if (n > nhiplo){ nhiplo = n; }
		}
	}
    
/*
    printArrayFmtAllWHdr(stderr, *N, "%lld", "Hi2LoIdxWgt: N - ");
    
    fprintf(stderr,"Hi2LoIdxWgt: nhiplo=%lld\n",nhiplo);
*/
	*jIdxs  = Array(3,TYPIDX,grd_lo->y,grd_lo->x,nhiplo);
	*iIdxs  = Array(3,TYPIDX,grd_lo->y,grd_lo->x,nhiplo);
	*Wgts   = Array(3,DOUBLE,grd_lo->y,grd_lo->x,nhiplo);
	*WgtSum = Array(2,DOUBLE,grd_lo->y,grd_lo->x);
    fillArWithMiss(jIdxs);
    fillArWithMiss(iIdxs);
    fillArWithMiss(Wgts);
    fillArWithMiss(WgtSum);
    typ_idx m;
    double area,areasum,dsnlt;
	for (j=0;j<grd_lo->y;j++) {
		for (i=0;i<grd_lo->x;i++) {
            m = 0;
			areasum = 0.0;
			for (l=0;l<iIDX(&jNTmp,j);l++) {
                dsnlt = DBL(&jWgtsTmp,j,l);
                il    = IDX(&jIdxsTmp,j,l);
				for (k=0;k<iIDX(&iNTmp,i);k++) {
					IDX(jIdxs,j,i,m) = il;
					IDX(iIdxs,j,i,m) = IDX(&iIdxsTmp,i,k);
                    area     = earthArea2(dsnlt, DBL(&iWgtsTmp,i,k));
					areasum += area;
					DBL(Wgts,j,i,m) = area;
                    m++;
				}
			}
            DBL(WgtSum,j,i) = areasum;
		}
	}
    /* printArrayFmtAllWHdr(stderr, *jIdxs, "%lld", "Hi2LoIdxWgt: jIdxs - ");
    printArrayFmtAllWHdr(stderr, *iIdxs, "%lld", "Hi2LoIdxWgt: iIdxs - ");
    printArrayFmtAllWHdr(stderr, *Wgts, "%lld", "Hi2LoIdxWgt: Wgts - ");
    printArrayFmtAllWHdr(stderr, *WgtSum, "%lld", "Hi2LoIdxWgt: WgtSum - "); */
	freeAr(&jIdxsTmp);
	freeAr(&jWgtsTmp);
	freeAr(&   jNTmp);
	freeAr(&iIdxsTmp);
	freeAr(&iWgtsTmp);
	freeAr(&   iNTmp);
    return;
}


void Hi2LoIdxWgt_Ar(arr *restrict lt_hi,arr *restrict ln_hi,arr *restrict lt_lo,arr *restrict ln_lo,arr *N,arr *jIdxs,arr *iIdxs,arr *Wgts,arr *WgtSum){
/*
    printArrayFmtAllWHdr(stderr, lt_hi, "%.2f", "Hi2LoIdxWgt_Ar: lt_hi - ");
    printArrayFmtAllWHdr(stderr, ln_hi, "%.2f", "Hi2LoIdxWgt_Ar: ln_hi - ");
    printArrayFmtAllWHdr(stderr, lt_lo, "%.2f", "Hi2LoIdxWgt_Ar: lt_lo - ");
    printArrayFmtAllWHdr(stderr, ln_lo, "%.2f", "Hi2LoIdxWgt_Ar: ln_lo - ");
*/
	typ_idx j,l,il,linit,lend;
    typ_idx ny_lo = lt_lo->tlen;
    double dy_lo_max = 0;
    double dy_lo;
    for (j=1;j<ny_lo;j++){
        dy_lo = iDBL(lt_lo,j)-iDBL(lt_lo,j-1);
        if (dy_lo > dy_lo_max){ dy_lo_max = dy_lo; }
    }
    typ_idx ny_hi = lt_hi->tlen;
    double dy_hi_min = iDBL(lt_hi,1)-iDBL(lt_hi,0);
    double dy_hi;
    for (j=2;j<ny_hi;j++){
        dy_hi = iDBL(lt_hi,j)-iDBL(lt_hi,j-1);
        if (dy_hi < dy_hi_min){ dy_hi_min = dy_hi; }
    }
    typ_idx nyhiplo = (dy_lo_max/dy_hi_min+2);
	arr jIdxsTmp = Array(2,TYPIDX,ny_lo,nyhiplo);
	arr jWgtsTmp = Array(2,DOUBLE,ny_lo,nyhiplo);
	arr    jNTmp = Array(1,TYPIDX,ny_lo);
    fillArWithMiss(&jIdxsTmp);
    fillArWithMiss(&jWgtsTmp);
    fillArWithMiss(&jNTmp);
    double bot=0,top=0,lt1=0,lt2=0;
	for (j=0;j<ny_lo;j++) {
        if (j == 0){
            top = 0.5*(iDBL(lt_lo,j)+iDBL(lt_lo,j+1));
            bot = 2*iDBL(lt_lo,j) - top;
            linit = myRound2(IdxFromVal(lt_hi,bot));
        } else if (j == ny_lo-1){
            bot = top;
            top = 2*iDBL(lt_lo,j) - bot;
            linit = lend;
        } else {
            bot = top;
            top = 0.5*(iDBL(lt_lo,j  )+iDBL(lt_lo,j+1));
            linit = lend;
        }
        lend  = myRound2(IdxFromVal(lt_hi,top));
        if ((linit >= ny_hi) || (lend  <  0)){
            iIDX(&jNTmp,j) = 0;
        } else {
            if (linit <  0)     { linit = 0; }
            if (lend  >= ny_hi) { lend  = ny_hi-1; }
            iIDX(&jNTmp,j) = lend-linit+1;
            for (l=linit;l<=lend;l++) {
                il = l-linit;
                IDX(&jIdxsTmp,j,il) = l;
                if (l == linit){
                    lt2 = 0.5*(iDBL(lt_hi,l)+iDBL(lt_hi,l+1));
                    lt1 = 2*iDBL(lt_hi,l) - lt2;
                } else if (l == ny_hi-1){
                    lt1 = lt2;
                    lt2 = 2*iDBL(lt_hi,l) - lt1;
                } else {
                    lt1 = lt2;
                    lt2 = 0.5*(iDBL(lt_hi,l  )+iDBL(lt_hi,l+1));
                }
                if (bot > lt1) { lt1 = bot; }
                if (top < lt2) { lt2 = top; }
                DBL(&jWgtsTmp,j,il) = dSinLat(lt1,lt2);
            }
        }
	}
/*
    printArrayFmtAllWHdr(stderr, jNTmp,    "%lld", "Hi2LoIdxWgt_Ar: jNTmp - ");
    printArrayFmtAllWHdr(stderr, jIdxsTmp, "%lld", "Hi2LoIdxWgt_Ar: jIdxsTmp - ");
    printArrayFmtAllWHdr(stderr, jWgtsTmp, "%.5f", "Hi2LoIdxWgt_Ar: jWgtsTmp - ");
*/
	typ_idx i,k,ik,kinit,kend;
    typ_idx nx_lo = ln_lo->tlen;
    double dx_lo_max = 0;
    double dx_lo;
    for (i=1;i<nx_lo;i++){
        dx_lo = iDBL(ln_lo,i)-iDBL(ln_lo,i-1);
        if (dx_lo > dx_lo_max){ dx_lo_max = dx_lo; }
    }
    typ_idx nx_hi = ln_hi->tlen;
    double dx_hi_min = iDBL(ln_hi,1)-iDBL(ln_hi,0);
    double dx_hi;
    for (i=2;i<nx_hi;i++){
        dx_hi = iDBL(ln_hi,i)-iDBL(ln_hi,i-1);
        if (dx_hi < dx_hi_min){ dx_hi_min = dx_hi; }
    }
    typ_idx nxhiplo = (dx_lo_max/dx_hi_min+2);
    arr iIdxsTmp = Array(2,TYPIDX,nx_lo,nxhiplo);
	arr iWgtsTmp = Array(2,DOUBLE,nx_lo,nxhiplo);
	arr    iNTmp = Array(1,TYPIDX,nx_lo);
    fillArWithMiss(&iIdxsTmp);
    fillArWithMiss(&iWgtsTmp);
    fillArWithMiss(&iNTmp);
    double left=0,right=0,ln1=0,ln2=0;
    for (i=0;i<nx_lo;i++) {
        if (i == 0){
            right = 0.5*(iDBL(ln_lo,i)+iDBL(ln_lo,i+1));
            left = 2*iDBL(ln_lo,i) - right;
            kinit = myRound2(IdxFromVal(ln_hi,left));
        } else if (i == nx_lo-1){
            left  = right;
            right = 2*iDBL(ln_lo,i) - left;
            kinit = kend;
        } else {
            left  = right;
            right = 0.5*(iDBL(ln_lo,i  )+iDBL(ln_lo,i+1));
            kinit = kend;
        }
        kend  = myRound2(IdxFromVal(ln_hi,right));
        if ((kinit >= nx_hi) || (kend  <  0)){
            iIDX(&iNTmp,i) = 0;
        } else {
            if (kinit <  0)     { kinit = 0; }
            if (kend  >= nx_hi) { kend  = nx_hi-1; }
            iIDX(&iNTmp,i) = kend-kinit+1;
            for (k=kinit;k<=kend;k++) {
                ik = k-kinit;
                IDX(&iIdxsTmp,i,ik) = k;
                if (k == kinit){
                    ln2 = 0.5*(iDBL(ln_hi,k)+iDBL(ln_hi,k+1));
                    ln1 = 2*iDBL(ln_hi,k) - ln2;
                } else if (k == nx_hi-1){
                    ln1 = ln2;
                    ln2 = 2*iDBL(ln_hi,k) - ln1;
                } else {
                    ln1 = ln2;
                    ln2 = 0.5*(iDBL(ln_hi,k  )+iDBL(ln_hi,k+1));
                }
                if (left  > ln1) { ln1 = left; }
                if (right < ln2) { ln2 = right; }
                DBL(&iWgtsTmp,i,ik) = dLongitude(ln1,ln2);
            }
        }
    }
/*
    printArrayFmtAllWHdr(stderr, iNTmp,    "%lld", "Hi2LoIdxWgt_Ar: iNTmp - ");
    printArrayFmtAllWHdr(stderr, iIdxsTmp, "%lld", "Hi2LoIdxWgt_Ar: iIdxsTmp - ");
    printArrayFmtAllWHdr(stderr, iWgtsTmp, "%.2f", "Hi2LoIdxWgt_Ar: iWgtsTmp - ");
*/
    typ_idx n, nj, nhiplo = 0;
	*N = Array(2,TYPIDX,ny_lo,nx_lo);
    fillArWithMiss(N);
	for (j=0;j<ny_lo;j++) {
        nj = iIDX(&jNTmp,j);
		for (i=0;i<nx_lo;i++) {
            n = nj*iIDX(&iNTmp,i);
			IDX(N,j,i) = n;
            if (n > nhiplo){ nhiplo = n; }
		}
	}
    
/*
    printArrayFmtAllWHdr(stderr, *N, "%lld", "Hi2LoIdxWgt_Ar: N - ");
    fprintf(stderr,"Hi2LoIdxWgt_Ar: nhiplo=%lld\n",nhiplo);
*/
	*jIdxs  = Array(3,TYPIDX,ny_lo,nx_lo,nhiplo);
	*iIdxs  = Array(3,TYPIDX,ny_lo,nx_lo,nhiplo);
	*Wgts   = Array(3,DOUBLE,ny_lo,nx_lo,nhiplo);
	*WgtSum = Array(2,DOUBLE,ny_lo,nx_lo);
    fillArWithMiss(jIdxs);
    fillArWithMiss(iIdxs);
    fillArWithMiss(Wgts);
    fillArWithMiss(WgtSum);
    typ_idx m;
    double area,areasum,dsnlt;
	for (j=0;j<ny_lo;j++) {
		for (i=0;i<nx_lo;i++) {
            m = 0;
			areasum = 0.0;
			for (l=0;l<iIDX(&jNTmp,j);l++) {
                dsnlt = DBL(&jWgtsTmp,j,l);
                il    = IDX(&jIdxsTmp,j,l);
				for (k=0;k<iIDX(&iNTmp,i);k++) {
					IDX(jIdxs,j,i,m) = il;
					IDX(iIdxs,j,i,m) = IDX(&iIdxsTmp,i,k);
                    area     = earthArea2(dsnlt, DBL(&iWgtsTmp,i,k));
					areasum += area;
					DBL(Wgts,j,i,m) = area;
                    m++;
				}
			}
            DBL(WgtSum,j,i) = areasum;
		}
	}
    /*
    printArrayFmtAllWHdr(stderr, *jIdxs,  "%lld", "Hi2LoIdxWgt_Ar: jIdxs - ");
    printArrayFmtAllWHdr(stderr, *iIdxs,  "%lld", "Hi2LoIdxWgt_Ar: iIdxs - ");
    printArrayFmtAllWHdr(stderr, *Wgts,   "%.2f", "Hi2LoIdxWgt_Ar: Wgts - ");
    printArrayFmtAllWHdr(stderr, *WgtSum, "%.2f", "Hi2LoIdxWgt_Ar: WgtSum - ");
    */
	freeAr(&jIdxsTmp);
	freeAr(&jWgtsTmp);
	freeAr(&   jNTmp);
	freeAr(&iIdxsTmp);
	freeAr(&iWgtsTmp);
	freeAr(&   iNTmp);
    return;
}

arr upScaleIdxWgt(arr *restrict IN,arr *restrict N,arr *restrict jIdxs,arr *restrict iIdxs,arr *restrict Wgts,arr *restrict WgtSum) {
	arr OUT = ArrayFromList(2,DOUBLE,N->len);
    fillArWithMiss(&OUT);
    typ_idx i,j,m,nm,k,l;
	double wgtsum,wgt,val,areasum;
	
	for (j=0;j<OUT.len[0];j++) {
		for (i=0;i<OUT.len[1];i++) {
        /*  fprintf(stderr,"upScaleIdxWgt: [j,i]=[%lld,%lld]\n",j,i);   */
			wgtsum  = 0.0;
            areasum = 0.0;
            nm = IDX(N,j,i);
        /*  fprintf(stderr,"upScaleIdxWgt: nm=%lld\n", nm); */
            for (m=0;m<nm;m++){
                l = IDX(jIdxs,j,i,m);
                k = IDX(iIdxs,j,i,m);
                if (!isMissIdx(IN,l,k)){
                    wgt      = DBL(Wgts,j,i,m);
                    areasum += wgt;
                    wgtsum  += wgt*DBL(IN,l,k);
                }
            }
            if (areasum > 0){
                DBL(&OUT,j,i) = wgtsum/areasum;
            }
		}
	}

	return OUT;
}

void WeightedStats(arr *restrict X, arr *restrict W, double thresh,
    double *mean,
    double *min,
    double *max,
    double *med,
    double *frac,
    double *sigma,
    double *mnabv
    ){
    static double maxdbl = MAX_DOUBLE;
    double pval;
    typ_idx n = X->tlen;

    if (n == 1) {
        double val = iDBL(X,(typ_idx)0);
        *mean  = val;
        *min   = val;
        *max   = val;
        *med   = val;
        *frac  = (double)(val > thresh);
        return;
    } else {
        typ_idx i;
        double Wsum,areaabv = 0,sumabv = 0;
        WMomentStats(X,W,&Wsum,mean,sigma,NULL,NULL);
        /*
        arr Xcpy = copyAr(X);
        setMissOutOfRange(Xcpy,&thresh,&maxdbl);
        arr Xt, Wt;
        removeMissing2Arrays(&Xt,&Wt,Xcpy,W);
        double Wsumt,meant,sigraw;
        if (Xt.tlen > 1){
            WMomentStats(Xt,Wt,NULL,mnabv,NULL,NULL,NULL);
        }
        freeAr(&Xcpy); freeAr(&Xt); freeAr(&Wt);
        */
        double cX, cW;
        for (i=0;i<n;i++){
            cX = iDBL(X,i);
            if (cX > thresh){
                cW = iDBL(W,i);
                sumabv  += cX*cW;
                areaabv += cW;
            }
        }
        if (Wsum > 0){
            *frac = areaabv/Wsum;
            if (areaabv > 0){ *mnabv = sumabv/areaabv; }

            arr idx = Array((typ_idx)1,TYPIDX,n);
            qsortTable2(X,&idx);
            
            *min = iDBL(X,iIDX(&idx,0));
            *max = iDBL(X,iIDX(&idx,n-1));
            
            /*
             *  Should pre-sort these arrays, then if there are multiple values of Xs that are the same
             *  , then the corresponding weights should be averaged for that value.
             */
            double Wsump1 = Wsum + Wsum/(double)n; /* This is the analog to Y->tlen + 1 in calcValatPerc */
            double Wstot = 0;
            double perc  = 0.5;
            double pPerc, cPerc, pX;
            for(i=0;i<n;i++){
                cX     = iDBL(X,iIDX(&idx,i));
                cW     = iDBL(W,iIDX(&idx,i));
                Wstot += cW;
                cPerc  = Wstot/Wsump1;
                if (cPerc >= perc){
                    if (i == 0) { /* percentile of all values greater than desired percentile */
                        *med = cX;
                    } else {
                        if (pPerc == cPerc) {
                            *med = cX;  /* This may never occur */
                        } else {
                            *med = linInterp(perc,pPerc,cPerc,pX,cX);
                        }
                    }
                    break;
                }
                pPerc = cPerc;
                pX    = cX;
            }
        
            if (i == n){ /* percentile never reached */
                *med = cX;
            }

            freeAr(&idx);
        }
        return;
    }
}


void upScaleStatsIdxWgt(arr *restrict IN,arr *restrict N,arr *restrict jIdxs,arr *restrict iIdxs,arr *restrict Wgts,double thresh
    ,arr *Mn,arr *min,arr *max,arr *med,arr *FrAbv,arr *sigma,arr *MnAbv) {
    *Mn    = ArrayFromList(2,DOUBLE,N->len);
    *min   = ArrayFromList(2,DOUBLE,N->len);
    *max   = ArrayFromList(2,DOUBLE,N->len);
    *med   = ArrayFromList(2,DOUBLE,N->len);
    *FrAbv = ArrayFromList(2,DOUBLE,N->len);
    *sigma = ArrayFromList(2,DOUBLE,N->len);
    *MnAbv = ArrayFromList(2,DOUBLE,N->len);
    fillArWithMiss(Mn);
    fillArWithMiss(min);
    fillArWithMiss(max);
    fillArWithMiss(med);
    fillArWithMiss(FrAbv);
    fillArWithMiss(sigma);
    fillArWithMiss(MnAbv);
    typ_idx i,j,m,nm,n,k,l;
	double wgtsum,wgt,val,areasum,areaabv;
    arr X,W;
	double *pval = malloc(Wgts->len[2]*sizeof(double));
	double *pwgt = malloc(Wgts->len[2]*sizeof(double));
	for (j=0;j<N->len[0];j++) {
		for (i=0;i<N->len[1];i++) {
        /*  fprintf(stderr,"upScaleIdxWgt: [j,i]=[%lld,%lld]\n",j,i);   */
			wgtsum  = 0;
            areasum = 0;
            areaabv = 0;
            n = 0;
            nm = IDX(N,j,i);
        /*  fprintf(stderr,"upScaleIdxWgt: nm=%lld\n", nm); */
            for (m=0;m<nm;m++){
                l = IDX(jIdxs,j,i,m);
                k = IDX(iIdxs,j,i,m);
                if (!isMissIdx(IN,l,k)){
                    pwgt[n] = DBL(Wgts,j,i,m);
                    pval[n] = DBL(IN,l,k);
                    n++;
                }
            }
            if (n > 0){
                X = assign1dtoNd(pval, 1, DOUBLE, n);
                W = assign1dtoNd(pwgt, 1, DOUBLE, n);
                
                WeightedStats(&X, &W, thresh,
                    address_of(Mn,   j,i),
                    address_of(min,  j,i),
                    address_of(max,  j,i),
                    address_of(med,  j,i),
                    address_of(FrAbv,j,i),
                    address_of(sigma,j,i),
                    address_of(MnAbv,j,i)
                    );
                freeArShell(&X);
                freeArShell(&W);
            }
		}
	}

	return;
}

#endif
