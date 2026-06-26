#ifndef  _WRAP_GRID_H_
#define  _WRAP_GRID_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <math_supp.h>

void wrap_C_grad(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 2,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_3ar_r2ar_km(C_grad,args);
}

arr wrap_C_grad_1d(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_3ar1i_km(C_grad_1d,args);
}

arr wrap_dFc(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_3ar1i_km(dFc,args);
}

arr wrap_dFcc(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_3ar1i_km(dFcc,args);
}

arr wrap_dFcd(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_3ar_km(dFcd,args);
}

arr wrap_Fc(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_3ar1i_km(Fc,args);
}

arr wrap_Fcc(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_3ar1i_km(Fcc,args);
}

arr wrap_Fcd(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_3ar_km(Fcd,args);
}

arr wrap_C_div(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 4,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_4ar_km(C_div,args);
}

arr wrap_C_curl(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 4,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_4ar_km(C_curl,args);
}

arr wrap_Laplace(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_3ar_km(Laplace,args);
}

void wrap_LaplaceVec(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 4,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 2,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_4ar_r2ar_km(LaplaceVec,args);
}

arr wrap_LaplaceVec_1d(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 4,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_4ar1i_km(LaplaceVec_1d,args);
}

arr wrap_B_vort(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 4,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_4ar_km(B_vort,args);
}

arr wrap_curv_2d(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_3ar_km(curv_2d,args);
}

arr wrap_C_deform(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 4,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_4ar_km(C_deform,args);
}

arr wrap_C_advect(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 5,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_5ar_km(C_advect,args);
}

arr wrap_C_advcoef(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 5,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_5ar_km(C_advcoef,args);
}

void wrap_C_geownd(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 2,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_3ar_r2ar_km(C_geownd,args);
}

arr wrap_C_geownd_1d(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 3,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_3ar1i_km(C_geownd_1d,args);
}

void wrap_C_Q_tmp(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 5,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 2,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_5ar_r2ar_km(C_Q_tmp,args);
}

arr wrap_C_Q_tmp_1d(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 5,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_5ar1i_km(C_Q_tmp_1d,args);
}

void wrap_C_Q_theta(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 4,/*ndbls*/ 0,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 2,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_4ar_r2ar_km(C_Q_theta,args);
}

arr wrap_C_Q_theta_1d(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 4,/*ndbls*/ 0,/*nints*/ 1,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_arr_4ar1i_km(C_Q_theta_1d,args);
}

#endif
