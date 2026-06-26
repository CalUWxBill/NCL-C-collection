/* Created by Bill Scheftic */
#ifndef  _WRAP_MATH_H_
#define  _WRAP_MATH_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <math_supp.h>

double wrap_cos(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(cos,args);
}

double wrap_tanh(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(tanh,args);
}

double wrap_atanh(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    double y = args->dblp[0];
    if ((y > -1) && (y < 1)){
        return wrap_dbl_1d(atanh,args);
    } else { /* Set NaN and infinity to missing */
        return *(double *)args->missval;
    }
}


double wrap_floor(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(floor,args);
}

double wrap_ln(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(log,args);
}

double wrap_sin(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(sin,args);
}

double wrap_sgn(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(signof,args);
}

double wrap_rint(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(rint,args);
}

int wrap_myRound(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_int_1d(myRound,args);
}

double wrap_devSq(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(devSq,args);
}

double wrap_devAbs(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(devAbs,args);
}

double wrap_amax2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(amax2,args);
}

double wrap_amin2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(amin2,args);
}

double wrap_dim(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(dim,args);
}

double wrap_dist(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(dist,args);
}

double wrap_add(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(add,args);
}

double wrap_sub(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(sub,args);
}

double wrap_mult(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(mult,args);
}

double wrap_mult3(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(mult3,args);
}

double wrap_mult4(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_4d(mult4,args);
}

double wrap_mult5(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_5d(mult5,args);
}

double wrap_Div(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    double y = args->dblp[1];
    if (y == 0){
        return *(double *)args->missval;
    } else {
        return wrap_dbl_2d(Div,args);
    }
}

double wrap_pow(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(pow,args);
}

double wrap_amax3(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(amax3,args);
}

double wrap_amin3(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(amin3,args);
}

double wrap_dist3d(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(dist3d,args);
}

double wrap_mx_b(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(mx_b,args);
}

double wrap_dist2d(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_4d(dist2d,args);
}

double wrap_linInterp(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_5d(linInterp,args);
}


double wrap_ceq_mean(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(ceq_mean,args);
}

double wrap_eq_ndvi(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(eq_ndvi,args);
}

double wrap_ceq_var(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(ceq_var,args);
}

double wrap_ceq_std_s(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(ceq_std_s,args);
}

double wrap_ceq_std_p(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_3d(ceq_std_p,args);
}

double wrap_ceq_cov(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_4d(ceq_cov,args);
}

double wrap_ceq_slope(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_5d(ceq_slope,args);
}

double wrap_ceq_orthoslope(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 6,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_6d(ceq_orthoslope,args);
}

double wrap_ceq_corr(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 6,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_6d(ceq_corr,args);
}



double wrap_angbtwpi(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_1d(angbtwpi,args);
}

double wrap_angadd(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(angadd,args);
}

double wrap_angsub(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(angsub,args);
}

double wrap_angmult(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(angmult,args);
}

double wrap_angdiv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_dbl_2d(angdiv,args);
}

#endif
