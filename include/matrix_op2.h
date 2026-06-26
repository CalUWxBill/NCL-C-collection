/* Created by Bill Scheftic */
/*-------------------------------------------*/
/* Header for Matrix Processing  */
/*-------------------------------------------*/
#ifndef  _MATRIX_OP_
#define  _MATRIX_OP_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <math_supp.h>
#include <arrayinit2.h>
#include <print_arrays2.h>

/*------------------------*/
/* Function Declarations  */
/*------------------------*/

/* General Operators */
void fillDiag(arr *,double);
double Det(arr *);
arr getDiag(arr *);
arr Diag2Array(arr *);
arr getIdentity(typ_idx);
arr vectorize(arr *);
arr mMult(arr *,arr *);
arr tensorProd(arr *,arr *);
arr Transpose(arr *);
arr gaussElim(arr *,arr *);
arr Inverse(arr *);
void flipRow(arr *,typ_idx,typ_idx);

/*-----------*/
/* Functions */
/*-----------*/

void fillDiag(arr *restrict m,double x){
	typ_idx i;
	if (m->n != 2){
		fprintf(stderr,"Array must be two dimensions\n");
		exit(0);
	}
	if (m->typ != DOUBLE){
		fprintf(stderr,"Array must be type double\n");
		exit(0);
	}

	typ_idx iend = imin(m->len[0],m->len[1]);
	for(i=0;i<iend;i++){ DBL(m,i,i) = x; }

	return;
}

void PermGenLoop(arr *restrict S_x,arr *restrict nops,arr *restrict sgn,typ_idx p_in,typ_idx *p_cur,typ_idx nops_lvl,typ_idx ibeg){
	typ_idx i,j,k;
	typ_idx p_in_next;
	typ_idx slen = S_x->len[1];
	for(i=ibeg;i<slen-1;i++){
		for(j=i+1;j<slen;j++){
 			iIDX(nops,*p_cur) = nops_lvl;
			iIDX(sgn ,*p_cur) = pow(-1,iIDX(nops,*p_cur));
			for(k=0;k<slen;k++){
				IDX(S_x,*p_cur,k) = IDX(S_x,p_in,k);
			}
			IDX(S_x,*p_cur,i) = IDX(S_x,p_in,j);
			IDX(S_x,*p_cur,j) = IDX(S_x,p_in,i);
		/*
			fprintf(stderr,"%3d: %3d %d %2d {",*p_cur,p_in,iIDX(nops,*p_cur),iIDX(sgn ,*p_cur));
			for(k=0;k<slen;k++){
				fprintf(stderr,"%d",IDX(S_x,*p_cur,k));
				if(k<slen-1){
					fputs(",",stderr);
				}
			}
			fputs("}\n",stderr);
		 */

			p_in_next = *p_cur;
			(*p_cur)++;
			PermGenLoop(S_x,nops,sgn,p_in_next,p_cur,nops_lvl+1,i+1);
		}
	}
	return;
}

double Det(arr *restrict X){
	typ_idx i,j,k;

	typ_idx slen = X->len[0];
	arr s = Array(1,TYPIDX,slen);
	for(i=0;i<slen;i++){
		iIDX(&s,i) = i;
	}
	typ_idx n_sigma = fact(slen);
	arr S_x  = Array(2,TYPIDX,n_sigma,slen);
	arr nops = Array(1,TYPIDX,n_sigma);
	arr sgn  = Array(1,TYPIDX,n_sigma);
/*
	fputs("S_x\n",stderr);
	printArrayInfo(stderr,S_x);
 */

	typ_idx p_cur = 0;
 	iIDX(&nops,p_cur) = 0;
	iIDX(&sgn,p_cur)  = pow(-1,iIDX(&nops,p_cur));
/*	fprintf(stderr,"%3d: %3d %d %2d {",p_cur,0,iIDX(&nops,p_cur),iIDX(&sgn,p_cur));	*/
	for(k=0;k<slen;k++){
		IDX(&S_x,p_cur,k) = iIDX(&s,k);
	/*
		fprintf(stderr,"%d",IDX(&S_x,p_cur,k));
		if(k<slen-1){
			fputs(",",stderr);
		}
	 */
	}
/*	fputs("}\n",stderr);	*/
	p_cur++;
	PermGenLoop(&S_x,&nops,&sgn,0,&p_cur,1,0);

/*
	for(j=0;j<n_sigma;j++){
		fprintf(stderr,"%3d: %d %2d {",j,iIDX(&nops,j),iIDX(&sgn,j));
		for(k=0;k<slen;k++){
			fprintf(stderr,"%d",IDX(&S_x,j,k));
			if(k<slen-1){
				fputs(",",stderr);
			}
		}
		fputs("}\n",stderr);
	}
 */

	double Xprod;
	double determ = 0;
	for(i=0;i<n_sigma;i++){
		Xprod = 1;
		for(j=0;j<slen;j++){
			Xprod *= DBL(X,j,IDX(&S_x,i,j));
		}
		determ += iIDX(&sgn,i)*Xprod;
	}

	freeAr(&s);
	freeAr(&S_x);
	freeAr(&nops);
	freeAr(&sgn);
	return determ;
}

arr getDiag(arr *restrict X){
	typ_idx i;
	if (X->n != 2){
		fprintf(stderr,"Array must be two dimensions\n");
		exit(0);
	}
	if (X->typ != DOUBLE){
		fprintf(stderr,"Array must be type double\n");
		exit(0);
	}

	typ_idx nxy = imin(X->len[0], X->len[1]);

	arr Xi = castAr(X,DOUBLE,0);

	arr m = Array(2,DOUBLE,nxy,nxy);
    copyMiss(&m,&Xi);

	for(i=0;i<nxy;i++){
		DBL(&m,i,i) = DBL(&Xi,i,i);
	}

	freeAr(&Xi);
	return m;
}

arr Diag2Array(arr *restrict X){
	typ_idx i;
	if (X->n != 2){
		fprintf(stderr,"Array must be two dimensions\n");
		exit(0);
	}
	if (X->typ != DOUBLE){
		fprintf(stderr,"Array must be type double\n");
		exit(0);
	}

	typ_idx nxy = imin(X->len[0], X->len[1]);

	arr Xi = castAr(X,DOUBLE,0);

	arr m = Array(1,DOUBLE,nxy);
    copyMiss(&m,&Xi);

	for(i=0;i<nxy;i++){
		DBL(&m,i) = DBL(&Xi,i,i);
	}

	freeAr(&Xi);
	return m;
}

arr getIdentity(typ_idx size){
	typ_idx i;

	arr m = Array(2,DOUBLE,size,size);

	double fillval = 0;
	fillAr(&m,&fillval);
/*
	printArrayInfo(stderr,m);
	printArray(stderr,m);
*/
	for(i=0;i<size;i++){
		DBL(&m,i,i) = 1.0;
	}
/*
	printArrayInfo(stderr,m);
	printArray(stderr,m);
 */
	return m;
}

arr vectorize(arr *restrict X){
	typ_idx i;
	arr Xi = castAr(X,DOUBLE,0);
	arr m = Array(2,DOUBLE,X->tlen,(typ_idx)1);
    copyMiss(&m,&Xi);

	for(i=0;i<m.len[0];i++){
		DBL(&m,(typ_idx)i,(typ_idx)0) = iDBL(&Xi,i);
	}

	freeAr(&Xi);
	return m;
}

arr mMult(arr *restrict X,arr *restrict Y){
	typ_idx i,j,k;

	double sum = 0;
	arr m = Array(2,DOUBLE,X->len[0],Y->len[1]);
	copyMiss(&m,X);

	for(j=0;j<X->len[0];j++){
		for(i=0;i<Y->len[1];i++){
            for(k=0;k<X->len[1];k++){
                sum += DBL(X,j,k)*DBL(Y,k,i);
            }
            DBL(&m,j,i) = sum;
            sum = 0;
		}
	}
	return m;
}

arr tensorProd(arr *restrict X,arr *restrict Y)	/* This could probably be extended to n-dimensions */
{ typ_idx i,j,k,l;
  arr m = Array(2,DOUBLE,X->len[0]*Y->len[0],X->len[1]*Y->len[1]);
  for(j=0;j<X->len[0];j++)
  { for(i=0;i<X->len[1];i++)
    { for(l=0;l<Y->len[0];l++)
      { for(k=0;k<Y->len[1];k++)
        { DBL(&m,(typ_idx)(j*Y->len[0]+l),(typ_idx)(i*Y->len[1]+k)) = DBL(X,j,i)*DBL(Y,l,k);
        }
      }
    }
  }
  return m;
}

arr Transpose(arr *restrict X){
	typ_idx i,j;
	arr m = Array(2,DOUBLE,X->len[1],X->len[0]);
	copyMiss(&m,X);

	for(j=0;j<X->len[0];j++){
	for(i=0;i<X->len[1];i++){
		DBL(&m,i,j) = DBL(X,j,i);
	}
	}
	return m;
}

arr gaussElim(arr *restrict X,arr *restrict v)
{ /* http://karlscalculus.org/cgi-bin/linear.pl */
  typ_idx i,j,k;
  int jtest;
  typ_idx jrow;
  double mult1;

  arr m = Array(1,DOUBLE,X->len[1]);
  arr W = Array(2,DOUBLE,X->len[0],X->len[1]+1);
  /* build W */
  for(j=0;j<W.len[0];j++)
  { for(i=0;i<(W.len[1]-1);i++)
    { DBL(&W,j,i) = DBL(X,j,i);
    }
    DBL(&W,(typ_idx)j,(typ_idx)W.len[1]-1) = iDBL(v,j);
  }
  /*	printArray(stdout,W); */
  /* lower triangle reduction */
  i = 0;
  /*	fprintf(stdout,"i=%d,W.len[1]=%d\n",i,W.len[1]); */
  while(i<(W.len[1]-1))
  { 
    if (DBL(&W,i,i) == 0){
      jtest = 1;
      j = i+1;
      while ((jtest) && (j<W.len[0])) {
        if (DBL(&W,j,i) != 0.0) { jrow = j; jtest = 0; }
        j++;
      }
      if (jtest) {
        i = W.len[1];
      } else {
        flipRow(&W,i,jrow);
        /*	fprintf(stdout,"Swap Row%d with Row%d\n",i+1,jrow+1); */
        /*	printArray(stdout,W); */
      }
    } 
    if (i < W.len[1]) {
      if ((DBL(&W,i,i) != 1) && (DBL(&W,i,i) != 0)) {
        mult1 = 1/DBL(&W,i,i);
        DBL(&W,i,i) = 1;
        for(k=i+1;k<W.len[1];k++) { DBL(&W,i,k) = mult1*DBL(&W,i,k); }
        /*	fprintf(stdout,"Row%d * %6.3f\n",i+1,mult1); */
        /*	printArray(stdout,W); */
      }
      if (DBL(&W,i,i) == 1) {
        for(j=i+1;j<W.len[0];j++)
        { mult1 = -DBL(&W,j,i);
          DBL(&W,j,i) = 0;
          if (mult1 != 0){
            for(k=i+1;k<W.len[1];k++) { DBL(&W,j,k) += mult1*DBL(&W,i,k); }
            /*	fprintf(stdout,"%6.3f * Row%d + Row%d\n",mult1,i+1,j+1); */
            /*	printArray(stdout,W); */
          } 
        }
      }
    }
    i++;
  }
  /*	printArray(stdout,W); */
  /* solve for m */
  double num;
  for(j=(W.len[1]-2);j>=0;j--)
  { num = DBL(&W,(typ_idx)j,(typ_idx)W.len[1]-1);
    for(i=(W.len[1]-2);i>j;i--)
    { num += -(iDBL(&m,i))*(DBL(&W,j,i));
    }
    iDBL(&m,j) = num;
  }

  /*	printArray(stderr,m); */

  freeAr(&W);
  return m;
}

/*
arr gaussElim2(arr *restrict X,arr1 v)
{ */ /* http://karlscalculus.org/cgi-bin/linear.pl */ /*
  typ_idx i,j,k;
  arr W = Array(2,DOUBLE,X->len[0],X->len[1]+1);
  */ /* build W */ /*
  for(j=0;j<W.len[0];j++)
  { for(i=0;i<(W.len[1]-1);i++)
    { DBL(&W,j,i) = DBL(X,j,i);
    }
    DBL(&W,(typ_idx)j,(typ_idx)W.len[1]-1) = iDBL(v,j);
  }
  arr m = GSolve(W);
  freeAr(&W);
  return m;
}
 */

/*
arr GSolve(arr *restrict a)
{
   typ_idx i,j,k,maxrow;
   typ_idx n = a->len[0];
   arr x = Array(1,DOUBLE,a->len[0]);
   double tmp,mult1,mult2,mult3;

   for (i=0;i<n;i++) {

      */ /* Find the row with the largest first value */ /*
      maxrow = i;
      for (j=i+1;j<n;j++) {
         if (fabs(DBL(a,j,i)) > fabs(DBL(a,maxrow,i)))
            maxrow = j;
      }

      */ /* Swap the maxrow and ith row */ /*
      for (k=i;k<n+1;k++) {
         tmp = DBL(a,i,k);
         DBL(a,i,k) = DBL(a,maxrow,k);
         DBL(a,maxrow,k) = tmp;
      }

      */ /* Eliminate the ith element of the jth row */ /*
      mult1 = 1/DBL(a,i,i);
      for (j=i+1;j<n;j++) {
         mult2 = DBL(a,j,i) * mult1;
         for (k=n;k>=i;k--) {
            DBL(a,j,k) -= DBL(a,i,k) * mult2;
         }
      }
   }

   */ /* Do the back substitution */ /*
   for (j=n-1;j>=0;j--) {
      tmp = 0;
      mult3 = 1/DBL(a,j,j);
      for (k=j+1;k<n;k++)
         tmp += DBL(a,j,k) * iDBL(x,k);
      iDBL(&x,j) = (DBL(a,j,n) - tmp) * mult3;
   }

   return x;
}
 */

arr Inverse(arr *restrict X)
{ typ_idx i,j,k;
  int jtest;
  typ_idx jrow;
  double mult;
  arr W = Array(2,DOUBLE,X->len[1],2*X->len[1]);
  arr Y = Array(2,DOUBLE,X->len[1],X->len[1]);
  /* build W */
  for(j=0;j<W.len[0];j++)
  { for(i=0;i<X->len[1];i++)
    { DBL(&W,j,i) = DBL(X,j,i);
    }
    DBL(&W,(typ_idx)j,(typ_idx)X->len[1]+j) = 1;
  }
  /*  fputs("before lower triangle reduction\n",stderr); */
  /*  printArray(stdout,W); */
  /* lower triangle reduction */
  i = 0;
  while(i<X->len[1])
  { if (DBL(&W,i,i) == 0){
      jtest = 1;
      j = i+1;
      while ((jtest) && (j<W.len[0])) {
        if (DBL(&W,j,i) != 0.0) { jrow = j; jtest = 0; }
        j++;
      }
      if (jtest) {
        i = W.len[1];
      } else {
        flipRow(&W,i,jrow);
        /*	fprintf(stdout,"Swap Row%d with Row%d\n",i+1,jrow+1); */
        /*	printArray(stdout,W); */
      }
    } 
    if (i < W.len[1]) {
      if ((DBL(&W,i,i) != 1) && (DBL(&W,i,i) != 0)) {
        mult = 1/DBL(&W,i,i);
        DBL(&W,i,i) = 1;
        for(k=i+1;k<W.len[1];k++) { DBL(&W,i,k) = mult*DBL(&W,i,k); }
        /*	fprintf(stdout,"Row%d * %6.3f\n",i+1,mult); */
        /*	printArray(stdout,W); */
      }
      if (DBL(&W,i,i) == 1) {
        for(j=(i+1);j<W.len[0];j++)
        { mult = -DBL(&W,j,i);
          for(k=0;k<W.len[1];k++) { DBL(&W,j,k) = mult*DBL(&W,i,k) + DBL(&W,j,k); }
          /*	fprintf(stdout,"%6.3f * Row%d + Row%d\n",mult,i+1,j+1); */
          /*	printArray(stdout,W); */
        }
      }
    }
    i++;
  }
  /* fputs("after lower triangle reduction\n",stderr); */
  /* printArray(stdout,W); */

  /* upper triangle reduction */
  for(i=X->len[1]-1;i>0;i--){
    if (DBL(&W,i,i) != 0){
      for(j=i-1;j>=0;j--){
        mult = -DBL(&W,j,i);
        DBL(&W,j,i)=0;
        for(k=(i+1);k<W.len[1];k++){
          DBL(&W,j,k) = mult*DBL(&W,i,k) + DBL(&W,j,k);
        }
      }
    }
  }
  /* fputs("after upper triangle reduction\n",stderr); */
  /* printArray(stdout,W); */

  for(j=0;j<Y.len[0];j++){
    for(i=0;i<Y.len[1];i++){
      DBL(&Y,j,i) = DBL(&W,(typ_idx)j,(typ_idx)X->len[1]+i);
    }
  }

  freeAr(&W);
  return Y;
}

void flipRow(arr *X,typ_idx x,typ_idx y){
  typ_idx i;
  double val;
  for(i=0;i<X->len[1];++i){
    val        = DBL(X,x,i);
    DBL(X,x,i) = DBL(X,y,i);
    DBL(X,y,i) = val;
  }
  return;
}

/* Potentially faster
void flipRow(arr *X,typ_idx x,typ_idx y){
  typ_idx i;
  double val;
  double *rowx = address_of(X,x,(typ_idx)0);
  double *rowy = address_of(X,y,(typ_idx)0);
  for(i=0;i<X->len[1];++i){
    val     = *rowx;
    *rowx++ = *rowy;
    *rowy++ = val;
  }
  return;
}
*/

/* Backup
arr flipRow(arr *restrict X,typ_idx x,typ_idx y){
  typ_idx i;
  arr Y = copyAr(X);
  for(i=0;i<Y.len[1];i++){
    DBL(&Y,x,i) = DBL(X,y,i);
    DBL(&Y,y,i) = DBL(X,x,i);
  }
  freeAr(&X);
  return Y;
} */

#endif
