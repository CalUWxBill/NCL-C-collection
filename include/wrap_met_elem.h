#ifndef  _WRAP_MET_ELEM_H_
#define  _WRAP_MET_ELEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <arrayops2.h>
#include <wrap_functions.h>
#include <meteo_elem.h>

void wrap_uvIdx2uv(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 6,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 2,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_6d_r2d(uvIdx2uv,args);
}

void wrap_uv2uvIdx(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 6,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 2,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_6d_r2d(uv2uvIdx,args);
}

void wrap_rotate_cntrclkws(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 2,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_3d_r2d(rotate_cntrclkws,args);
}

void wrap_rotate_clkws(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 2,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); }
    return wrap_3d_r2d(rotate_clkws,args);
}


/* 1 variable functions */
double wrap_svp_from_tmp  (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_1d(svp_from_tmp,args); }
double wrap_satvapor      (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_1d(satvapor,args); }
double wrap_satvap2       (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_1d(satvap2,args); }
double wrap_tmp_from_svp  (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_1d(tmp_from_svp,args); }
double wrap_C_coriolis    (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_1d(C_coriolis,args); }
double wrap_rad_at_lat    (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_1d(rad_at_lat,args); }
double wrap_gamma_QE      (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_1d(gamma_QE,args); }
double wrap_SDR_Annual    (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_1d(SDR_Annual,args); }
double wrap_calcSPIfromH  (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_1d(calcSPIfromH,args); }
double wrap_InternalEnergy(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_1d(InternalEnergy,args); }
double wrap_LatentEnergy  (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_1d(LatentEnergy,args); }
double wrap_latentc       (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_1d(latentc,args); }
double wrap_stdatm_t_z    (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_1d(stdatm_t_z,args); }
double wrap_stdatm_p_z    (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_1d(stdatm_p_z,args); }
double wrap_stdatm_z_p    (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_1d(stdatm_z_p,args); }
double wrap_stdatm_t_p    (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 1,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_1d(stdatm_t_p,args); }

/* 2 variable functions */
double wrap_potTemp              (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(potTemp,args); }
double wrap_GetTheta             (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(GetTheta,args); }
double wrap_vp_from_spfh_prs     (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(vp_from_spfh_prs,args); }
double wrap_spfh_from_vp_prs     (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(spfh_from_vp_prs,args); }
double wrap_mixrat_from_vp_prs   (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(mixrat_from_vp_prs,args); }
double wrap_satmixrat            (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(satmixrat,args); }
double wrap_mixratio             (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(mixratio,args); }
double wrap_dpt2spfh             (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(dpt2spfh,args); }
double wrap_E_spfh2dpt           (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(E_spfh2dpt,args); }
double wrap_E_rh2dpt             (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(E_rh2dpt,args); }
double wrap_E_dpt2rh             (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(E_dpt2rh,args); }
double wrap_C_rh2abshum          (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(C_rh2abshum,args); }
double wrap_C_wdspd              (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(C_wdspd,args); }
double wrap_GetWSpd              (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(GetWSpd,args); }
double wrap_C_wddir              (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(C_wddir,args); }
double wrap_GetWDir              (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(GetWDir,args); }
double wrap_u_wnd                (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(u_wnd,args); }
double wrap_GetUWnd              (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(GetUWnd,args); }
double wrap_v_wnd                (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(v_wnd,args); }
double wrap_GetVWnd              (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(GetVWnd,args); }
double wrap_EddyPeriod           (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(EddyPeriod,args); }
double wrap_EddyDiameter         (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(EddyDiameter,args); }
double wrap_EddyFrequency        (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(EddyFrequency,args); }
double wrap_calcUstar            (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(calcUstar,args); }
double wrap_calcThSfc            (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(calcThSfc,args); }
double wrap_calcQSfc             (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(calcQSfc,args); }
double wrap_calcThMix            (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(calcThMix,args); }
double wrap_calcQMix             (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(calcQMix,args); }
double wrap_ObukhovParameter     (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(ObukhovParameter,args); }
double wrap_dragCoef_uw          (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(dragCoef_uw,args); }
double wrap_dragCoef_ustr        (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(dragCoef_ustr,args); }
double wrap_dragCoefN            (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(dragCoefN,args); }
double wrap_BulkAeroResMomentum  (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(BulkAeroResMomentum,args); }
double wrap_BulkAeroResMomentumCD(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(BulkAeroResMomentumCD,args); }
double wrap_BulkAeroResHeat      (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(BulkAeroResHeat,args); }
double wrap_BulkAeroResMoist     (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(BulkAeroResMoist,args); }
double wrap_BowenRatio_Qflux     (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(BowenRatio_Qflux,args); }
double wrap_BowenRatio_wth_wq    (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(BowenRatio_wth_wq,args); }
double wrap_SoilTransmissivity   (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(SoilTransmissivity,args); }
double wrap_SoilPorosity         (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(SoilPorosity,args); }
double wrap_KineticEnergy        (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(KineticEnergy,args); }
double wrap_soil_cond            (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(soil_cond,args); }
double wrap_tsindex              (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(tsindex,args); }
double wrap_tlcl                 (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(tlcl,args); }
double wrap_Templcl              (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(Templcl,args); }
double wrap_virtual1             (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(virtual1,args); }
double wrap_rho_tv_p             (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(rho_tv_p,args); }
double wrap_rho_t_q_p            (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(rho_t_q_p,args); }
double wrap_GetXLoc              (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(GetXLoc,args); }
double wrap_GetTemp              (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 2,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_2d(GetTemp,args); }

/* 3 variable functions */
double wrap_omega2w              (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(omega2w,args); }
double wrap_gradwnd              (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(gradwnd,args); }
double wrap_rossnum              (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(rossnum,args); }
double wrap_TotalTotals          (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(TotalTotals,args); }
double wrap_E_spfh2rhprs         (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(E_spfh2rhprs,args); }
double wrap_getrh                (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(getrh,args); }
double wrap_rh2spfh              (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(rh2spfh,args); }
double wrap_rh2mixrat            (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(rh2mixrat,args); }
double wrap_GetThet2             (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(GetThet2,args); }
double wrap_C_thetae             (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(C_thetae,args); }
double wrap_Thetae               (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(Thetae,args); }
double wrap_calcUProf            (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(calcUProf,args); }
double wrap_psiM                 (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(psiM,args); }
double wrap_psiH                 (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(psiH,args); }
double wrap_psiE                 (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(psiE,args); }
double wrap_dragCoef_psiM        (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(dragCoef_psiM,args); }
double wrap_dragCoefRatio        (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(dragCoefRatio,args); }
double wrap_HeatTransfCoefN      (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(HeatTransfCoefN,args); }
double wrap_MoistTransfCoefN     (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(MoistTransfCoefN,args); }
double wrap_resCoefTemplate      (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(resCoefTemplate,args); }
double wrap_BulkAeroResHeat_theta(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(BulkAeroResHeat_theta,args); }
double wrap_BulkAeroResMoist_q   (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(BulkAeroResMoist_q,args); }
double wrap_LatentHeat_Bowen     (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(LatentHeat_Bowen,args); }
double wrap_HWR519_Ea            (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(HWR519_Ea,args); }
double wrap_wchill               (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(wchill,args); }
double wrap_plcl                 (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(plcl,args); }
double wrap_Preslcl              (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(Preslcl,args); }
double wrap_gammaw               (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(gammaw,args); }
double wrap_virtual2             (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 3,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_3d(virtual2,args); }

/* 4 variable functions */
double wrap_calcWstar                (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(calcWstar,args); }
double wrap_ObukhovLength            (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(ObukhovLength,args); }
double wrap_SfcLayWindProf           (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(SfcLayWindProf,args); }
double wrap_HeatTransfCoef_wth       (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(HeatTransfCoef_wth,args); }
double wrap_MoistTransfCoef_wq       (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(MoistTransfCoef_wq,args); }
double wrap_BulkAeroRes_taos         (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(BulkAeroRes_taos,args); }
double wrap_BulkAeroResHeat_theta_alt(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(BulkAeroResHeat_theta_alt,args); }
double wrap_BulkAeroResMoist_q_alt   (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(BulkAeroResMoist_q_alt,args); }
double wrap_LatentHtFlx_raV          (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(LatentHtFlx_raV,args); }
double wrap_BulkHeatFlux             (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(BulkHeatFlux,args); }
double wrap_Delta_e                  (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(Delta_e,args); }
double wrap_PenmanVPDTerm            (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(PenmanVPDTerm,args); }
double wrap_PenmanMoistFlux_saturated(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(PenmanMoistFlux_saturated,args); }
double wrap_PriestlyTaylor_alphacnst (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(PriestlyTaylor_alphacnst,args); }
double wrap_BowenRatio_BulkTransf    (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(BowenRatio_BulkTransf,args); }
double wrap_SDR_SWAT                 (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(SDR_SWAT,args); }
double wrap_SoilVolWaterFlowRate     (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(SoilVolWaterFlowRate,args); }
double wrap_LinearGroundwaterVel     (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(LinearGroundwaterVel,args); }
double wrap_epi                      (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(epi,args); }
double wrap_trop_env                 (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 4,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_4d(trop_env,args); }

/* 5 variable functions */
double wrap_SfcLayWindShear      (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(SfcLayWindShear,args); }
double wrap_SfcLayThetaProf      (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(SfcLayThetaProf,args); }
double wrap_SfcLayThetaVProf     (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(SfcLayThetaVProf,args); }
double wrap_SfcLayThetaDiff      (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(SfcLayThetaDiff,args); }
double wrap_SfcLayThetaVDiff     (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(SfcLayThetaVDiff,args); }
double wrap_SfcLayMoistProf      (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(SfcLayMoistProf,args); }
double wrap_SfcLayMoistDiff      (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(SfcLayMoistDiff,args); }
double wrap_HeatTransfCoef_psiMH (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(HeatTransfCoef_psiMH,args); }
double wrap_HeatTransfCoefRatio  (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(HeatTransfCoefRatio,args); }
double wrap_MoistTransfCoef_psiME(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(MoistTransfCoef_psiME,args); }
double wrap_MoistTransfCoefRatio (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(MoistTransfCoefRatio,args); }
double wrap_LatHtFlux_e          (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(LatHtFlux_e,args); }
double wrap_LatHtFlux_gamma      (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(LatHtFlux_gamma,args); }
double wrap_LatHtFlux_SfcSat     (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(LatHtFlux_SfcSat,args); }
double wrap_PenmanEquationQE     (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(PenmanEquationQE,args); }
double wrap_PenmanVPDTerm_e      (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(PenmanVPDTerm_e,args); }
double wrap_PriestlyTaylor       (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(PriestlyTaylor,args); }
double wrap_USLE                 (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 5,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_5d(USLE,args); }

/* 6 variable functions */
double wrap_ustr_2lev                 (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 6,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_6d(ustr_2lev,args); }
double wrap_LatHtFlux_theta           (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 6,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_6d(LatHtFlux_theta,args); }
double wrap_LatHtFlux_tmp             (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 6,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_6d(LatHtFlux_tmp,args); }
double wrap_BowenRatio_BulkTransfCoef (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 6,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_6d(BowenRatio_BulkTransfCoef,args); }
double wrap_HWR519_fe                 (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 6,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_6d(HWR519_fe,args); }
double wrap_USLE_per_storm            (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 6,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_6d(USLE_per_storm,args); }
double wrap_SoilVolWaterFlowRate_Darcy(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 6,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_6d(SoilVolWaterFlowRate_Darcy,args); }
double wrap_ConfinedAquiferStorageCoef(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 6,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_6d(ConfinedAquiferStorageCoef,args); }

/* 7 variable functions */
double wrap_SfcLayVertThetaFlux (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 7,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_7d(SfcLayVertThetaFlux,args); }
double wrap_SfcLayVertThetaVFlux(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 7,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_7d(SfcLayVertThetaVFlux,args); }
double wrap_SfcLayVertMoistFlux (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 7,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_7d(SfcLayVertMoistFlux,args); }
double wrap_LatHtFlx_Delta_e    (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 7,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_7d(LatHtFlx_Delta_e,args); }
double wrap_hail_param          (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 7,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_7d(hail_param,args); }

/* 8 variable functions */
double wrap_HeatTransfCoef_wth_2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 8,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_8d(HeatTransfCoef_wth_2,args); }
double wrap_MoistTransfCoef_wq_2(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 8,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_8d(MoistTransfCoef_wq_2,args); }
double wrap_sweat_index         (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 8,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_8d(sweat_index,args); }

/* 9 variable functions */
double wrap_PenmanEquation_Full(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 9,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 0,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_dbl_9d(PenmanEquation_Full,args); }


/* multiple output functions */
void wrap_Atmo579_Flux_Prof_Method(input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 11,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 4,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_11d_r4d(Atmo579_Flux_Prof_Method,args); }
void wrap_Atmo579_Penman_Method   (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 10,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 4,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_10d_r4d(Atmo579_Penman_Method,   args); }
void wrap_Atmo579_Bowen_Method    (input_args *args){
    if (argNumsInvalid(__func__,args,/*narrs*/ 0,/*ndbls*/ 7,/*nints*/ 0,/*nidxs*/ 0,/*nrarrs*/ 0,/*nrdbls*/ 2,/*nrints*/ 0,/*nridxs*/ 0)){ exit(EXIT_FAILURE); } return wrap_7d_r2d( Atmo579_Bowen_Method,    args); }

#endif
