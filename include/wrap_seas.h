#ifndef  _WRAP_SEAS_H_
#define  _WRAP_SEAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arrayinit2.h>
#include <wrap_functions.h>
#include <seasonality.h>

void wrap_OnsetPercTimeBefAftFuzzy(input_args *args){
    return wrap_2ar_r2d(c_OnsetPercTimeBefAftFuzzy,args,7);
}

void wrap_OnsetPercTimeBefAft(input_args *args){
    return wrap_2ar1d_r2d(c_OnsetPercTimeBefAft,args,7);
}

void wrap_OnsetPWAPCPPercTimeBefAft(input_args *args){
    return wrap_3ar2d_r2d(c_OnsetPWAPCPPercTimeBefAft,args,7);
}

void wrap_OnsetAccumFuzzyAbvAnom(input_args *args){
    return wrap_2ar_r2d(c_OnsetAccumFuzzyAbvAnom,args,7);
}

void wrap_OnsetAccumTimeAbvAnom(input_args *args){
    return wrap_2ar1d_r2d(c_OnsetAccumTimeAbvAnom,args,7);
}

void wrap_OnsetPWAPCPAccumTimeAbvAnom(input_args *args){
    return wrap_3ar2d_r2d(c_OnsetPWAPCPAccumTimeAbvAnom,args,7);
}

void wrap_OnsetPWAPCPAccumTimeAbvAnomClimo(input_args *args){
    return wrap_3ar3d_r2d(c_OnsetPWAPCPAccumTimeAbvAnomClimo,args,7);
}

void wrap_PWAPCPPositivePersistenceAroundThresh(input_args *args){
    return wrap_3ar4d_r1d(c_PWAPCPPositivePersistenceAroundThresh,args,7);
}

void wrap_PWAPCPPercentTimeAboveThreshForNDaysPrePost(input_args *args){
    return wrap_3ar4d1i_r1d(c_PWAPCPPercentTimeAboveThreshForNDaysPrePost,args,7);
}

void wrap_PWAPCPPercentTimeAboveThreshForNDays(input_args *args){
    return wrap_3ar4d1i_r1d(c_PWAPCPPercentTimeAboveThreshForNDays,args,7);
}

void wrap_OnsetThreshDays(input_args *args){
    return wrap_2ar1d2i_r2d(c_OnsetThreshDays,args,7);
}

void wrap_NPWIonset(input_args *args){
    return wrap_2ar_r2d(c_NPWIonset,args,7);
}

void wrap_NPWIonsetThresh(input_args *args){
    return wrap_2ar1d_r2d(c_NPWIonsetThresh,args,7);
}

void wrap_NPWIonsetThreshDays(input_args *args){
    return wrap_2ar1d1i_r2d(c_NPWIonsetThreshDays,args,7);
}

void wrap_NPIonsetThresh(input_args *args){
    return wrap_2ar1d_r2d(c_NPIonsetThresh,args,7);
}

void wrap_NPIonset2(input_args *args){
    return wrap_2ar_r2d(c_NPIonset2,args,7);
}

void wrap_NPIonset(input_args *args){
    return wrap_2ar_r2d(c_NPIonset,args,7);
}

void wrap_NPIonsetKerrie(input_args *args){
    return wrap_3ar_r3d(c_NPIonsetKerrie,args,7);
}

void wrap_NPIonsetKerrie2(input_args *args){
    return wrap_2ar1d_r2d(c_NPIonsetKerrie2,args,7);
}

void wrap_WNDonsetThresh(input_args *args){
    return wrap_3ar2d1i_r2d(c_WNDonsetThresh,args,7);
}

void wrap_PWAPCPonsetThresh(input_args *args){
    return wrap_3ar2d_r2d(c_PWAPCPonsetThresh,args,7);
}

void wrap_PWAPCPWNDonsetThresh(input_args *args){
    return wrap_4ar3d_r2d(c_PWAPCPWNDonsetThresh,args,7);
}

arr wrap_StatsGreaterThanThresh(input_args *args){
    return wrap_arr_3ar1d(c_StatsGreaterThanThresh,args,7);
}

arr wrap_StatsLessThanThresh(input_args *args){
    return wrap_arr_3ar1d(c_StatsLessThanThresh,args,7);
}

arr wrap_StatsGreaterThan2Threshes(input_args *args){
    return wrap_arr_4ar2d(c_StatsGreaterThan2Threshes,args,7);
}

void wrap_getOnsetRetreatPeriods(input_args *args){
    return wrap_2ar3d2i_r6ar(c_getOnsetRetreatPeriods,args,7);
}

void wrap_NPWIonsetThreshPercentile(input_args *args){
    return wrap_5ar1d_r6d(c_NPWIonsetThreshPercentile,args,7);
}

void wrap_NPIonsetThreshPercentile(input_args *args){
    return wrap_5ar1d_r6d(c_NPIonsetThreshPercentile,args,7);
}

void wrap_getOnsetRetreatPeriodsPct2Thresh(input_args *args){
    return wrap_2ar4d2i_r6ar(c_getOnsetRetreatPeriodsPct2Thresh,args,7);
}

void wrap_NPIonsetThreshPercGT(input_args *args){
    return wrap_3ar3d_r4d(c_NPIonsetThreshPercGT,args,7);
}

void wrap_NPIdailystats(input_args *args){
    return wrap_2ar_r10d(c_NPIdailystats,args,7);
}

void wrap_PercentTimeAboveThresh(input_args *args){
    return wrap_2ar3d_r1d(c_PercentTimeAboveThresh,args,7);
}

void wrap_PersistenceAroundThresh(input_args *args){
    return wrap_2ar3d_r1d(c_PersistenceAroundThresh,args,7);
}

void wrap_LeastPersistentThresh(input_args *args){
    return wrap_2ar2d_r1d(c_LeastPersistentThresh,args,7);
}

void wrap_LeastPersistentThresh2(input_args *args){
    return wrap_2ar2d_r1d(c_LeastPersistentThresh2,args,7);
}

void wrap_PositivePersistenceAroundThresh(input_args *args){
    return wrap_2ar3d_r1d(c_PositivePersistenceAroundThresh,args,7);
}

void wrap_TotalPositivePersistence(input_args *args){
    return wrap_2ar2d_r1d(c_TotalPositivePersistence,args,7);
}

void wrap_MeanPositivePersistence(input_args *args){
    return wrap_2ar2d_r1d(c_MeanPositivePersistence,args,7);
}

void wrap_ValAtPositivePersistence(input_args *args){
    return wrap_2ar3d_r1d(c_ValAtPositivePersistence,args,7);
}

void wrap_MeanValAtPositivePersistence(input_args *args){
    return wrap_2ar2d_r1d(c_MeanValAtPositivePersistence,args,7);
}

void wrap_MeanValAtPositivePersistencePrePost(input_args *args){
    return wrap_2ar2d_r1d(c_MeanValAtPositivePersistencePrePost,args,7);
}

void wrap_MeanPositivePersistencePrePost(input_args *args){
    return wrap_2ar2d_r1d(c_MeanPositivePersistencePrePost,args,7);
}

void wrap_DifferencePrePost(input_args *args){
    return wrap_2ar2d_r1d(c_DifferencePrePost,args,7);
}

void wrap_PositivePersistenceAroundThreshPrePost(input_args *args){
    return wrap_2ar3d_r1d(c_PositivePersistenceAroundThreshPrePost,args,7);
}

void wrap_PositivePersistenceDiagnostics(input_args *args){
    return wrap_2ar3d_r4d(c_PositivePersistenceDiagnostics,args,7);
}

void wrap_PositivePersistenceDiagnosticsPrePost(input_args *args){
    return wrap_2ar3d_r12d(c_PositivePersistenceDiagnosticsPrePost,args,7);
}

void wrap_PercentTimeAboveThreshFor3Days(input_args *args){
    return wrap_2ar3d_r1d(c_PercentTimeAboveThreshFor3Days,args,7);
}

void wrap_PercentTimeAboveThreshFor5Days(input_args *args){
    return wrap_2ar3d_r1d(c_PercentTimeAboveThreshFor5Days,args,7);
}

void wrap_PercentTimeAboveThreshForNDays(input_args *args){
    return wrap_2ar3d1i_r1d(c_PercentTimeAboveThreshForNDays,args,7);
}

void wrap_PercentTimeAboveThreshForNDaysPrePost(input_args *args){
    return wrap_2ar3d1i_r1d(c_PercentTimeAboveThreshForNDaysPrePost,args,7);
}

void wrap_StdDevAboveThresh(input_args *args){
    return wrap_2ar3d_r1d(c_StdDevAboveThresh,args,7);
}

void wrap_IQRAboveThresh(input_args *args){
    return wrap_2ar3d_r1d(c_IQRAboveThresh,args,7);
}

void wrap_StdDevAbovePrePost(input_args *args){
    return wrap_2ar2d_r1d(c_StdDevAbovePrePost,args,7);
}

void wrap_NPIdailystatsThreshRemFirstLast(input_args *args){
    return wrap_2ar3d_r5d(c_NPIdailystatsThreshRemFirstLast,args,7);
}

void wrap_NPIdailystatsThresh(input_args *args){
    return wrap_2ar3d_r5d(c_NPIdailystatsThresh,args,7);
}

void wrap_NPIdailystatsThreshPreMidPost(input_args *args){
    return wrap_2ar1d_r15d(c_NPIdailystatsThreshPreMidPost,args,7);
}

void wrap_NPIdailystatsHistogram(input_args *args){
    return wrap_2ar3d_r2ar(c_NPIdailystatsHistogram,args,7);
}

void wrap_NPIdailystatsRuns(input_args *args){
    return wrap_2ar3d_r2ar(c_NPIdailystatsRuns,args,7);
}

double wrap_findonset(input_args *args){
    return wrap_dbl_2ar(c_findonset,args,7);
}

void wrap_findtimestats(input_args *args){
    return wrap_2ar_r8d(c_findtimestats,args,7);
}

void wrap_findtimestats2(input_args *args){
    return wrap_2ar1d_r8d(c_findtimestats2,args,7);
}

void wrap_timestatssum(input_args *args){
    return wrap_2ar2d_r5ar1d1i(c_timestatssum,args,7);
}

void wrap_timestatssummin(input_args *args){
    return wrap_2ar2d_r5ar1d1i(c_timestatssummin,args,7);
}

void wrap_closestmax(input_args *args){
    return wrap_2ar1d_r1d(c_closestmax,args,7);
}

void wrap_closestmin(input_args *args){
    return wrap_2ar1d_r1d(c_closestmin,args,7);
}

double wrap_nextmin(input_args *args){
    return wrap_dbl_2ar2i(c_nextmin,args,7);
}

double wrap_nextmax(input_args *args){
    return wrap_dbl_2ar2i(c_nextmax,args,7);
}

typ_idx wrap_nextminidx(input_args *args){
    return wrap_int_1ar2i(c_nextminidx,args,7);
}

typ_idx wrap_prevminidx(input_args *args){
    return wrap_int_1ar2i(c_prevminidx,args,7);
}

typ_idx wrap_nextmaxidx(input_args *args){
    return wrap_int_1ar2i(c_nextmaxidx,args,7);
}

typ_idx wrap_prevmaxidx(input_args *args){
    return wrap_int_1ar2i(c_prevmaxidx,args,7);
}

double wrap_seasend(input_args *args){
    return wrap_dbl_3ar1i(c_seasend,args,7);
}

arr wrap_allmaxmodes(input_args *args){
    return wrap_arr_1ar2i(c_allmaxmodes,args,7);
}

arr wrap_allminmodes(input_args *args){
    return wrap_arr_1ar2i(c_allminmodes,args,7);
}

#endif
