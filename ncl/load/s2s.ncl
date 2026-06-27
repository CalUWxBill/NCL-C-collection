; Created by Bill Scheftic

if (.not.isdefined("named_stats_declared")) then
 loadscript("$NCL_USER_DIR/load/named_stats.ncl")
 named_stats_declared = 1
end if

;--------------------------
; Bias Correction Functions
;--------------------------
undef("get_multi_regr")
function get_multi_regr(fcstens_z:numeric,obs_z:numeric,pred:numeric,rsq_thresh:numeric,dim_args[*]:string)
local pred_dNames,pred_dim,maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts \
      ,alldims,dims,indcopy,dsizes_tc,ntotidxs,idxdim \
      ,ms,bs,rsqs,idxs
begin
  pred_dNames = getvardims(pred)
  pred_dim    = get1Dindex(pred_dNames,dim_args(0))
  dsizes_tc = dimsizes(pred)
  ntotidxs = dsizes_tc(pred_dim)
  idxdim     = new(ntotidxs,"double",-999)
  idxdim!0   = "idxdim"
  idxdim&idxdim = todouble( fspan(0,tofloat(ntotidxs-1),ntotidxs) )
  maplist    := get_mapdims([/fcstens_z, obs_z, pred, rsq_thresh, idxdim/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  
  dims  = DimsFromNames2(dNames_all,dim_args)
  indcopy = get1Dindex_Exclude (alldims,dims)
  if (all(ismissing(indcopy))) then
    indcopy = -1
  end if

  ms   = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  bs   = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  rsqs = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  idxs = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"int64")

  ncl_c_get_multi_regr(fcstens_z,obs_z,pred,rsq_thresh \
        ,ms,bs,rsqs,idxs \
        ,dims,mpdims)

  return([/ ms,bs,rsqs,idxs /])
end


undef("get_multi_regr_min")
function get_multi_regr_min(fcstens_z:numeric,obs_z:numeric,pred:numeric,t_sig:numeric,rsq_thresh:numeric,dim_args[*]:string)
local pred_dNames,pred_dim,maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts \
      ,alldims,dims,indcopy,dsizes_tc,ntotidxs,idxdim \
      ,ms,bs,rsqs,idxs
begin
  pred_dNames = getvardims(pred)
  pred_dim    = get1Dindex(pred_dNames,dim_args(0))
  dsizes_tc = dimsizes(pred)
  ntotidxs = dsizes_tc(pred_dim)
  idxdim     = new(ntotidxs,"double",-999)
  idxdim!0   = "idxdim"
  idxdim&idxdim = todouble( fspan(0,tofloat(ntotidxs-1),ntotidxs) )
  maplist    := get_mapdims([/fcstens_z, obs_z, pred, t_sig, rsq_thresh, idxdim/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  
  dims  = DimsFromNames2(dNames_all,dim_args)
  indcopy = get1Dindex_Exclude (alldims,dims)
  if (all(ismissing(indcopy))) then
    indcopy = -1
  end if

  ms   = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  bs   = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  rsqs = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  idxs = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"int64")

  ncl_c_get_multi_regr_min(fcstens_z,obs_z,pred,t_sig,rsq_thresh \
        ,ms,bs,rsqs,idxs \
        ,dims,mpdims)

  return([/ ms,bs,rsqs,idxs /])
end


undef("get_multi_regr_min_prscrbd")
function get_multi_regr_min_prscrbd(fcstens_z:numeric,obs_z:numeric,pred:numeric,idxs:snumeric,t_sig:numeric,rsq_thresh:numeric,dim_args[*]:string)
local pred_dNames,pred_dim,maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts \
      ,allstdims,idxdims,dim_args2,alldims,dims,dims2,indcopy,idxdim \
      ,ms,bs,rsqs,idxs
begin
  maplist    := get_mapdims([/fcstens_z, obs_z, pred, idxs, t_sig, rsq_thresh/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  
  allstdims    = DimsFromNames2(dim_args,dim_args)
  idxdims    = DimsFromNames2(dim_args,"idxdim")
  dim_args2 = dim_args(get1Dindex_Exclude(allstdims,idxdims))

  alldims = DimsFromNames2(dNames_all,dNames_all)
  dims  = DimsFromNames2(dNames_all,dim_args)
  dims2 = DimsFromNames2(dNames_all,dim_args2)
  indcopy = get1Dindex_Exclude(alldims,dims2)
  if (all(ismissing(indcopy))) then
    indcopy = -1
  end if
  ms   = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  bs   = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  rsqs = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")

  ncl_c_get_multi_regr_min_prscrbd(fcstens_z,obs_z,pred,idxs,t_sig,rsq_thresh \
        ,ms,bs,rsqs \
        ,dims,mpdims)

  return([/ ms,bs,rsqs /])
end


undef("apply_multi_regr")
function apply_multi_regr(pred:numeric,ms:numeric,bs:numeric,idxs:snumeric,fcst_z:numeric,napply:snumeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts \
      ,alldims,dims,indcopy,fcst_tc_z
begin
  ; How to keep dimension order consistent with fcst_z
  maplist    := get_mapdims([/pred, ms, bs, idxs, fcst_z, napply /],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  dims  = DimsFromNames2(dNames_all,dim_args)

  fcst_tc_z := ncl_c_apply_multi_regr(pred,ms,bs,idxs,fcst_z,napply \
        ,dims,mpdims)
  
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
    if (all(ismissing(indcopy))) then
      indcopy = -1
    end if
  end if
  copy_Coords_Fro(dNames_all,dList_all,fcst_tc_z,indcopy)
  copy_VarAtts_except(fcst_z,fcst_tc_z,"_FillValue")
  
  return(fcst_tc_z)
end




undef("get_pdf_cdf")
function get_pdf_cdf(Obs:numeric,kwidth:numeric,bbnd:numeric,ebnd:numeric,len:snumeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts \
      ,alldims,dims,indcopy,maxlen,pdf \
      ,pdf_y,cdf_y
begin
  maxlen = max(len)
  pdf     = new(maxlen,"double",-999)
  pdf!0   = "pdf"
  pdf&pdf = todouble( fspan(0,tofloat(maxlen-1),maxlen) )
  maplist    := get_mapdims([/Obs, kwidth, bbnd, ebnd, len, pdf/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  
  dims  = DimsFromNames2(dNames_all,dim_args)
  indcopy = get1Dindex_Exclude (alldims,dims)
  if (all(ismissing(indcopy))) then
    indcopy = -1
  end if
  pdf_y = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  cdf_y = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")

  ncl_c_get_pdf_cdf(Obs,kwidth,bbnd,ebnd,len \
        ,pdf_y,cdf_y \
        ,dims,mpdims)
  
  return([/ pdf_y,cdf_y /])
end


undef("get_P_z_cdf")
function get_P_z_cdf(Val:numeric,cdf:numeric,bbnd:numeric,ebnd:numeric,len:snumeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts \
      ,alldims,dims,pdfdim,indcopy \
      ,P,z
begin
  maplist    := get_mapdims([/Val, cdf, bbnd, ebnd, len/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  
  dims  = DimsFromNames2(dNames_all,dim_args)
  pdfdim  = DimsFromNames2(dNames_all,"pdf")
  indcopy = get1Dindex_Exclude (alldims,pdfdim)
  if (all(ismissing(indcopy))) then
    indcopy = -1
  end if
  P = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  z = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")

  ncl_c_get_P_z_cdf(Val,cdf,bbnd,ebnd,len \
        ,P,z \
        ,dims,mpdims)
  
  return([/ P,z /])
end



undef("get_P_z_cdf_1")
function get_P_z_cdf_1(Val:numeric,cdf:numeric,bbnd:numeric,ebnd:numeric,len:snumeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts \
      ,alldims,dims,indcopy \
      ,P,z
begin
  maplist    := get_mapdims([/Val, cdf, bbnd, ebnd, len/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  
  dims  = DimsFromNames2(dNames_all,dim_args)
  indcopy = get1Dindex_Exclude (alldims,dims)
  if (all(ismissing(indcopy))) then
    indcopy = -1
  end if
  P = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  z = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")

  ncl_c_get_P_z_cdf_1(Val,cdf,bbnd,ebnd,len \
        ,P,z \
        ,dims,mpdims)
  
  return([/ P,z /])
end

undef("get_tertiary")
function get_tertiary(fcst_ens:numeric,cdf:numeric,bbnd:numeric,ebnd:numeric,len:snumeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts \
      ,alldims,dims,pdfdim,indcopy \
      ,P_vlo,P_lo,P_mid,P_hi,P_vhi
begin
  maplist    := get_mapdims([/fcst_ens, cdf, bbnd, ebnd, len/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  
  dims  = DimsFromNames2(dNames_all,dim_args)
  indcopy = get1Dindex_Exclude (alldims,dims)
  if (all(ismissing(indcopy))) then
    indcopy = -1
  end if
  P_vlo = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  P_lo  = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  P_mid = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  P_hi  = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  P_vhi = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")

  ncl_c_get_tertiary(fcst_ens,cdf,bbnd,ebnd,len \
        ,P_vlo,P_lo,P_mid,P_hi,P_vhi \
        ,dims,mpdims)
  
  return([/ P_vlo,P_lo,P_mid,P_hi,P_vhi /])
end

undef("get_tertiary_z")
function get_tertiary_z(fcst_ens:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts \
      ,alldims,dims,pdfdim,indcopy \
      ,P_vlo,P_lo,P_mid,P_hi,P_vhi
begin
  maplist    := get_mapdims([/fcst_ens/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  
  dims  = DimsFromNames2(dNames_all,dim_args)
  indcopy = get1Dindex_Exclude (alldims,dims)
  if (all(ismissing(indcopy))) then
    indcopy = -1
  end if
  P_vlo = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  P_lo  = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  P_mid = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  P_hi  = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  P_vhi = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")

  ncl_c_get_tertiary_z(fcst_ens \
        ,P_vlo,P_lo,P_mid,P_hi,P_vhi \
        ,dims,mpdims)
  
  return([/ P_vlo,P_lo,P_mid,P_hi,P_vhi /])
end

undef("get_bc2")
function get_bc2(fcst_ens:numeric,obs:numeric,pers_z:numeric,TC:numeric,rsq_thresh:numeric,nsigfig:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts \
      ,alldims,dims,indcopy,maxlen,pdf,tcdim,dsizes_tc,ntotidxs,idxdim \
      ,dim_args_idxdim,dims_idxdim,indcopy_idxdim \
      ,dim_args_pdf,dims_pdf,indcopy_pdf \
      ,dim_args_all,dims_all \
      ,pdf_x,cdf_x,pdf_x_2,cdf_x_2,pdf_y,cdf_y \
      ,kwidth_x,bbnd_x,ebnd_x,len_x \
      ,kwidth_x_2,bbnd_x_2,ebnd_x_2,len_x_2 \
      ,kwidth_y,bbnd_y,ebnd_y,len_y \
      ,ms,bs,rsqs,idxs
begin
  ; what should len be?
  maxlen  = 500
  pdf     = new(maxlen,"double",-999)
  pdf!0   = "pdf"
  pdf&pdf = todouble( fspan(0,tofloat(maxlen-1),maxlen) )

  tcdim  = DimsFromNames(TC,"tcdim")
  dsizes_tc = dimsizes(TC)
  ntotidxs = dsizes_tc(tcdim)+1
  idxdim     = new(ntotidxs,"double",-999)
  idxdim!0   = "idxdim"
  idxdim&idxdim = todouble( fspan(0,tofloat(ntotidxs-1),ntotidxs) )

  maplist    := get_mapdims([/fcst_ens, obs, pers_z, TC, rsq_thresh, nsigfig, pdf, idxdim/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  
  dims  = DimsFromNames2(dNames_all,dim_args)

  dim_args_idxdim = array_append_record (dim_args,"idxdim",0)
  dims_idxdim  = DimsFromNames2(dNames_all,dim_args_idxdim)
  indcopy_idxdim = get1Dindex_Exclude (alldims,dims_idxdim)
  if (all(ismissing(indcopy_idxdim))) then
    indcopy_idxdim = -1
  end if
  pdf_x   = new_Meta(indcopy_idxdim,dSizes_all,dNames_all,dList_all,Atts,"double")
  cdf_x   = new_Meta(indcopy_idxdim,dSizes_all,dNames_all,dList_all,Atts,"double")
  pdf_x_2 = new_Meta(indcopy_idxdim,dSizes_all,dNames_all,dList_all,Atts,"double")
  cdf_x_2 = new_Meta(indcopy_idxdim,dSizes_all,dNames_all,dList_all,Atts,"double")
  pdf_y   = new_Meta(indcopy_idxdim,dSizes_all,dNames_all,dList_all,Atts,"double")
  cdf_y   = new_Meta(indcopy_idxdim,dSizes_all,dNames_all,dList_all,Atts,"double")

  dim_args_all = array_append_record (dim_args,(/"pdf","idxdim"/),0)
  dims_all  = DimsFromNames2(dNames_all,dim_args_all)
  indcopy = get1Dindex_Exclude (alldims,dims_all)
  if (all(ismissing(indcopy))) then
    indcopy = -1
  end if
  kwidth_x = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  bbnd_x   = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  ebnd_x   = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  len_x    = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"int64")
  kwidth_x_2 = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  bbnd_x_2   = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  ebnd_x_2   = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  len_x_2    = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"int64")
  kwidth_y = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  bbnd_y   = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  ebnd_y   = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  len_y    = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"int64")

  dim_args_pdf = array_append_record (dim_args,"pdf",0)
  dims_pdf  = DimsFromNames2(dNames_all,dim_args_pdf)
  indcopy_pdf = get1Dindex_Exclude (alldims,dims_pdf)
  if (all(ismissing(indcopy_pdf))) then
    indcopy_pdf = -1
  end if
  ms   = new_Meta(indcopy_pdf,dSizes_all,dNames_all,dList_all,Atts,"double")
  bs   = new_Meta(indcopy_pdf,dSizes_all,dNames_all,dList_all,Atts,"double")
  rsqs = new_Meta(indcopy_pdf,dSizes_all,dNames_all,dList_all,Atts,"double")
  idxs = new_Meta(indcopy_pdf,dSizes_all,dNames_all,dList_all,Atts,"int64")

  ncl_c_get_bc2(fcst_ens,obs,pers_z,TC,rsq_thresh,nsigfig \
        ,pdf_x,cdf_x,pdf_x_2,cdf_x_2,pdf_y,cdf_y \
        ,ms,bs,rsqs,idxs \
        ,kwidth_x,bbnd_x,ebnd_x \
        ,kwidth_x_2,bbnd_x_2,ebnd_x_2 \
        ,kwidth_y,bbnd_y,ebnd_y \
        ,len_x,len_x_2,len_y \
        ,dims,mpdims)
  
  return([/ pdf_x,cdf_x,pdf_x_2,cdf_x_2,pdf_y,cdf_y \
           ,kwidth_x,bbnd_x,ebnd_x,len_x \
           ,kwidth_x_2,bbnd_x_2,ebnd_x_2,len_x_2 \
           ,kwidth_y,bbnd_y,ebnd_y,len_y \
           ,ms,bs,rsqs,idxs /])
end

;-----------------------
; Verification Functions
;-----------------------
undef("named_verify")
; ex: dim_args = (/"year","ensemble"/)
function named_verify(Fcst:numeric,Obs:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts \
      ,alldims,dims,indcopy,dims1,indcopy1 \
      ,ENSM,ENSMed,ENS_Spread,ENS_AE,obs_Mean,obs_Med,Climo_MAE,ENSM_MAE,Climo_MSE,ENSM_MSE \
      ,ENSM_SS_MAE,SS_MAE_min,SS_MAE_Q1 \
      ,SS_MAE_med,SS_MAE_Q3,SS_MAE_max \
      ,ENSM_SS_MSE,SS_MSE_min,SS_MSE_Q1 \
      ,SS_MSE_med,SS_MSE_Q3,SS_MSE_max \
      ,Climo_MedAE, ENSM_MedAE,ENSM_SS_MedAE \
      ,Climo_MedSE, ENSM_MedSE,ENSM_SS_MedSE \
      ,ENSMed_MedAE,ENSMed_SS_MedAE,ENSMed_MedSE,ENSMed_SS_MedSE \
      ,ENSMed_MAE,ENSMed_MSE,ENSMed_SS_MAE,ENSMed_SS_MSE \
      ,Climo_RPS,fcst_RPS,fcst_RPSS \
      ,Climo_RPSmed,fcst_RPSmed,fcst_RPSSmed \
      ,ENSM_Bias,ENSM_RelBias,ENSM_Corr,ENSM_SpCr \
      ,ENSMed_Bias,ENSMed_RelBias,ENSMed_Corr \
      ,var_fcst,var_obs,var_ensm,var_ensmed,fcst_mean,nvalid
begin
  maplist    := get_mapdims([/Fcst, Obs/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  
  dims  = DimsFromNames2(dNames_all,dim_args)
  indcopy = get1Dindex_Exclude (alldims,dims)
  if (all(ismissing(indcopy))) then
    indcopy = -1
  end if
  dims1  = DimsFromNames2(dNames_all,dim_args(1))
  indcopy1 = get1Dindex_Exclude (alldims,dims1)
  if (all(ismissing(indcopy1))) then
    indcopy1 = -1
  end if
  ENSM            = new_Meta(indcopy1,dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSMed          = new_Meta(indcopy1,dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS_Spread      = new_Meta(indcopy1,dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS_AE          = new_Meta(indcopy1,dSizes_all,dNames_all,dList_all,Atts,"double")
  obs_Mean        = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  obs_Med         = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  Climo_MAE       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSM_MAE        = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  Climo_MSE       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSM_MSE        = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSM_SS_MAE     = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  SS_MAE_min      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  SS_MAE_Q1       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  SS_MAE_med      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  SS_MAE_Q3       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  SS_MAE_max      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSM_SS_MSE     = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  SS_MSE_min      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  SS_MSE_Q1       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  SS_MSE_med      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  SS_MSE_Q3       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  SS_MSE_max      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  Climo_MedAE     = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSM_MedAE      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSM_SS_MedAE   = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  Climo_MedSE     = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSM_MedSE      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSM_SS_MedSE   = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSMed_MedAE    = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSMed_SS_MedAE = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSMed_MedSE    = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSMed_SS_MedSE = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSMed_MAE      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSMed_MSE      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSMed_SS_MAE   = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSMed_SS_MSE   = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  Climo_RPS       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  fcst_RPS        = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  fcst_RPSS       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  Climo_RPSmed    = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  fcst_RPSmed     = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  fcst_RPSSmed    = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSM_Bias       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSM_RelBias    = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSM_Corr       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSM_SpCr       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSMed_Bias     = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSMed_RelBias  = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSMed_Corr     = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  var_fcst        = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  var_obs         = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  var_ensm        = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  var_ensmed      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  fcst_mean       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  nvalid          = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"int64" )

  ncl_c_verify(Fcst,Obs,ENSM,ENSMed,ENS_Spread,ENS_AE,obs_Mean,obs_Med \
        ,Climo_MAE,ENSM_MAE,Climo_MSE,ENSM_MSE \
        ,ENSM_SS_MAE,SS_MAE_min,SS_MAE_Q1 \
        ,SS_MAE_med,SS_MAE_Q3,SS_MAE_max \
        ,ENSM_SS_MSE,SS_MSE_min,SS_MSE_Q1 \
        ,SS_MSE_med,SS_MSE_Q3,SS_MSE_max \
        ,Climo_MedAE, ENSM_MedAE,ENSM_SS_MedAE \
        ,Climo_MedSE, ENSM_MedSE,ENSM_SS_MedSE \
        ,ENSMed_MedAE,ENSMed_SS_MedAE,ENSMed_MedSE,ENSMed_SS_MedSE \
        ,ENSMed_MAE,ENSMed_MSE,ENSMed_SS_MAE,ENSMed_SS_MSE \
        ,Climo_RPS,fcst_RPS,fcst_RPSS \
        ,Climo_RPSmed,fcst_RPSmed,fcst_RPSSmed \
        ,ENSM_Bias,ENSM_RelBias,ENSM_Corr,ENSM_SpCr \
        ,ENSMed_Bias,ENSMed_RelBias,ENSMed_Corr \
        ,var_fcst,var_obs,var_ensm,var_ensmed,fcst_mean,nvalid \
        ,dims,mpdims)
  
  return([/ENSM,ENSMed,ENS_Spread,ENS_AE,obs_Mean,obs_Med \
        ,Climo_MAE,ENSM_MAE,Climo_MSE,ENSM_MSE \
        ,ENSM_SS_MAE,SS_MAE_min,SS_MAE_Q1 \
        ,SS_MAE_med,SS_MAE_Q3,SS_MAE_max \
        ,ENSM_SS_MSE,SS_MSE_min,SS_MSE_Q1 \
        ,SS_MSE_med,SS_MSE_Q3,SS_MSE_max \
        ,Climo_MedAE, ENSM_MedAE,ENSM_SS_MedAE \
        ,Climo_MedSE, ENSM_MedSE,ENSM_SS_MedSE \
        ,ENSMed_MedAE,ENSMed_SS_MedAE,ENSMed_MedSE,ENSMed_SS_MedSE \
        ,ENSMed_MAE,ENSMed_MSE,ENSMed_SS_MAE,ENSMed_SS_MSE \
        ,Climo_RPS,fcst_RPS,fcst_RPSS \
        ,Climo_RPSmed,fcst_RPSmed,fcst_RPSSmed \
        ,ENSM_Bias,ENSM_RelBias,ENSM_Corr,ENSM_SpCr \
        ,ENSMed_Bias,ENSMed_RelBias,ENSMed_Corr \
        ,var_fcst,var_obs,var_ensm,var_ensmed,fcst_mean,nvalid/])
end

undef("named_rps")
function named_rps(Xens:numeric,Y:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,rank_Vars, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/Xens, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars  = maplist[3]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_ensrps1(Xens,Y,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(Xens,OUT,"_FillValue")
  return(OUT)
end


undef("named_verify_2")
; ex: dim_args = (/"year","ensemble"/)
function named_verify_2(Fcst1:numeric,Fcst2:numeric,Obs:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts \
      ,alldims,dims,indcopy,dims1,indcopy1 \
      ,ENS1M,ENS1_Spread,ENS1_AE,ENS1_Err,ENS2M,ENS2_Spread,ENS2_AE,ENS2_Err \
      ,obs_Mean,var_obs,ENSM_SS_MAE,ENSM_SS_MSE,fcst_RPSS \
      ,ENS1M_MAE,ENS1M_MSE,fcst1_RPS_Mean \
      ,ENS1M_Bias,ENS1M_RelBias,ENS1M_Corr,ENS1M_SpCr,var_fcst1,var_ens1m,fcst1_mean \
      ,ENS2M_MAE,ENS2M_MSE,fcst2_RPS_Mean \
      ,ENS2M_Bias,ENS2M_RelBias,ENS2M_Corr,ENS2M_SpCr,var_fcst2,var_ens2m,fcst2_mean,nvalid
begin
  maplist    := get_mapdims([/Fcst1,Fcst2,Obs/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  ; print("named_verify_2")
  ; print(mpdims)
  ; print(dNames_all)
  ; print(dList_all)
  ; print(dSizes_all)
  ; print(Type)
  ; print(Atts)
  alldims = DimsFromNames2(dNames_all,dNames_all)
  
  dims  = DimsFromNames2(dNames_all,dim_args)
  indcopy = get1Dindex_Exclude (alldims,dims)
  if (all(ismissing(indcopy))) then
    indcopy = -1
  end if
  dims1  = DimsFromNames2(dNames_all,dim_args(1))
  indcopy1 = get1Dindex_Exclude (alldims,dims1)
  if (all(ismissing(indcopy1))) then
    indcopy1 = -1
  end if
  ENS1M           = new_Meta(indcopy1,dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS1_Spread     = new_Meta(indcopy1,dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS1_AE         = new_Meta(indcopy1,dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS1_Err        = new_Meta(indcopy1,dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS2M           = new_Meta(indcopy1,dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS2_Spread     = new_Meta(indcopy1,dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS2_AE         = new_Meta(indcopy1,dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS2_Err        = new_Meta(indcopy1,dSizes_all,dNames_all,dList_all,Atts,"double")
  obs_Mean        = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  var_obs         = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSM_SS_MAE     = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSM_SS_MSE     = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  fcst_RPSS       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS1M_MAE       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS1M_MSE       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  fcst1_RPS_Mean  = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS1M_Bias      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS1M_RelBias   = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS1M_Corr      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS1M_SpCr      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  var_fcst1       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  var_ens1m       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  fcst1_mean      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS2M_MAE       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS2M_MSE       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  fcst2_RPS_Mean  = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS2M_Bias      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS2M_RelBias   = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS2M_Corr      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS2M_SpCr      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  var_fcst2       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  var_ens2m       = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  fcst2_mean      = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"double")
  nvalid          = new_Meta(indcopy, dSizes_all,dNames_all,dList_all,Atts,"int64" )

  ncl_c_verify_2(Fcst1,Fcst2,Obs \
                ,ENS1M,ENS1_Spread,ENS1_AE,ENS1_Err,ENS2M,ENS2_Spread,ENS2_AE,ENS2_Err \
                ,obs_Mean,var_obs,ENSM_SS_MAE,ENSM_SS_MSE,fcst_RPSS \
                ,ENS1M_MAE,ENS1M_MSE,fcst1_RPS_Mean \
                ,ENS1M_Bias,ENS1M_RelBias,ENS1M_Corr,ENS1M_SpCr,var_fcst1,var_ens1m,fcst1_mean \
                ,ENS2M_MAE,ENS2M_MSE,fcst2_RPS_Mean \
                ,ENS2M_Bias,ENS2M_RelBias,ENS2M_Corr,ENS2M_SpCr,var_fcst2,var_ens2m,fcst2_mean,nvalid \
                ,dims,mpdims)
  
  return([/ENS1M,ENS1_Spread,ENS1_AE,ENS1_Err,ENS2M,ENS2_Spread,ENS2_AE,ENS2_Err \
          ,obs_Mean,var_obs,ENSM_SS_MAE,ENSM_SS_MSE,fcst_RPSS \
          ,ENS1M_MAE,ENS1M_MSE,fcst1_RPS_Mean \
          ,ENS1M_Bias,ENS1M_RelBias,ENS1M_Corr,ENS1M_SpCr,var_fcst1,var_ens1m,fcst1_mean \
          ,ENS2M_MAE,ENS2M_MSE,fcst2_RPS_Mean \
          ,ENS2M_Bias,ENS2M_RelBias,ENS2M_Corr,ENS2M_SpCr,var_fcst2,var_ens2m,fcst2_mean,nvalid/])
end

undef("named_verify_det_2")
; ex: dim_args = (/"year"/)
function named_verify_det_2(Fcst1:numeric,Fcst2:numeric,Obs:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts \
      ,alldims,dims,indcopy,dims1,indcopy1 \
      ,Fcst1_AE,Fcst1_Err,Fcst2_AE,Fcst2_Err \
      ,obs_Mean,var_obs,SS_MAE,SS_MSE \
      ,Fcst1_MAE,Fcst1_MSE \
      ,Fcst1_Bias,Fcst1_RelBias,Fcst1_Corr,Fcst1_SpCr,var_fcst1,fcst1_mean \
      ,Fcst2_MAE,Fcst2_MSE \
      ,Fcst2_Bias,Fcst2_RelBias,Fcst2_Corr,Fcst2_SpCr,var_fcst2,fcst2_mean,nvalid
begin
  maplist    := get_mapdims([/Fcst1,Fcst2,Obs/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  
  dims  = DimsFromNames2(dNames_all,dim_args)
  indcopy = get1Dindex_Exclude (alldims,dims)
  if (all(ismissing(indcopy))) then
    indcopy = -1
  end if
  Fcst1_AE      = new_Meta(alldims,dSizes_all,dNames_all,dList_all,Atts,"double")
  Fcst1_Err     = new_Meta(alldims,dSizes_all,dNames_all,dList_all,Atts,"double")
  Fcst2_AE      = new_Meta(alldims,dSizes_all,dNames_all,dList_all,Atts,"double")
  Fcst2_Err     = new_Meta(alldims,dSizes_all,dNames_all,dList_all,Atts,"double")
  obs_Mean      = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  var_obs       = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  SS_MAE        = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  SS_MSE        = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  Fcst1_MAE     = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  Fcst1_MSE     = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  Fcst1_Bias    = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  Fcst1_RelBias = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  Fcst1_Corr    = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  Fcst1_SpCr    = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  var_fcst1     = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  fcst1_mean    = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  Fcst2_MAE     = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  Fcst2_MSE     = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  Fcst2_Bias    = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  Fcst2_RelBias = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  Fcst2_Corr    = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  Fcst2_SpCr    = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  var_fcst2     = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  fcst2_mean    = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  nvalid        = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"int64" )

  ncl_c_verify_det_2(Fcst1,Fcst2,Obs \
                    ,Fcst1_AE,Fcst1_Err,Fcst2_AE,Fcst2_Err \
                    ,obs_Mean,var_obs,SS_MAE,SS_MSE \
                    ,Fcst1_MAE,Fcst1_MSE \
                    ,Fcst1_Bias,Fcst1_RelBias,Fcst1_Corr,Fcst1_SpCr,var_fcst1,fcst1_mean \
                    ,Fcst2_MAE,Fcst2_MSE \
                    ,Fcst2_Bias,Fcst2_RelBias,Fcst2_Corr,Fcst2_SpCr,var_fcst2,fcst2_mean,nvalid \
                    ,dims,mpdims)
  
  return([/Fcst1_AE,Fcst1_Err,Fcst2_AE,Fcst2_Err \
          ,obs_Mean,var_obs,SS_MAE,SS_MSE \
          ,Fcst1_MAE,Fcst1_MSE \
          ,Fcst1_Bias,Fcst1_RelBias,Fcst1_Corr,Fcst1_SpCr,var_fcst1,fcst1_mean \
          ,Fcst2_MAE,Fcst2_MSE \
          ,Fcst2_Bias,Fcst2_RelBias,Fcst2_Corr,Fcst2_SpCr,var_fcst2,fcst2_mean,nvalid/])
end

undef("named_verify_1")
function named_verify_1(Fcst:numeric,Obs:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts \
      ,alldims,dims,indcopy,dims1,indcopy1 \
      ,ENSM,ENS_Spread,ENSM_AE,ENSM_SE,ENSM_Bias,fcst_RPS
begin
  maplist    := get_mapdims([/Fcst, Obs/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  
  dims  = DimsFromNames2(dNames_all,dim_args)
  indcopy = get1Dindex_Exclude (alldims,dims)
  if (all(ismissing(indcopy))) then
    indcopy = -1
  end if
  ENSM       = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  ENS_Spread = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSM_AE    = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSM_SE    = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  ENSM_Bias  = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  fcst_RPS   = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")

  ncl_c_verify_1(Fcst,Obs,ENSM,ENS_Spread,ENSM_AE,ENSM_SE,ENSM_Bias,fcst_RPS \
        ,dims,mpdims)
  
  return([/ENSM,ENS_Spread,ENSM_AE,ENSM_SE,ENSM_Bias,fcst_RPS/])
end

undef("pos_ens_r_squared_from_r")
function pos_ens_r_squared_from_r(ENSM_Corr:numeric)
local wgt
begin
    wgt       := where(ENSM_Corr.gt.0.0D,ENSM_Corr^2.0,0.0D)
    copy_VarMeta(ENSM_Corr,wgt)
    return(wgt)
end

undef("pos_ens_r_squared")
function pos_ens_r_squared(Fcst:numeric,Obs:numeric,ensdim_names[*]:string,dim_args[*]:string)
local ENSM_cal,ENSM_Corr,wgt
begin
    ENSM_cal  := named_avg(Fcst,ensdim_names)
    ENSM_Corr := named_corr(ENSM_cal, Obs,dim_args)
    wgt       := pos_ens_r_squared_from_r(ENSM_Corr)
    return(wgt)
end


;--------------------------
; Teleconnections Functions
;--------------------------
undef("getMonthlyIndex")
function getMonthlyIndex(fname:string)
local nmonths,strs,nlins,delim,headstr,byear_tc,eyear_tc,nyears_tc,years_tc,missdbl,im,b
begin
  nmonths = 12
  
  strs = asciiread(fname,-1,"string")
  nlins = dimsizes(strs)
  delim = " "
  headstr = strs(0)
  byear_tc = stringtoint(str_get_field(headstr, 1, delim))
  eyear_tc = stringtoint(str_get_field(headstr, 2, delim))
  nyears_tc = eyear_tc-byear_tc+1
  years_tc  = todouble(fspan(byear_tc,eyear_tc,nyears_tc))
  
  missdbl = stringtodouble( str_get_field(strs(nyears_tc+1), 1, delim) )
  VarIdx = new((/nyears_tc,nmonths/),"double",missdbl)
  VarIdx@_FillValue = missdbl
  VarIdx!0     = "year"
  VarIdx&year  = years_tc
  VarIdx!1     = "month"
  VarIdx&month = todouble( fspan(1,nmonths,nmonths) )
  do im=1,nmonths
      VarIdx(:,im-1) = (/ stringtodouble(str_get_field(strs(1:nyears_tc), im+1, delim) ) /)
  end do

  return(VarIdx)
end

undef("readPSLMonthlyIndex")
function readPSLMonthlyIndex(fname:string)
local nmonths,strs,nlins,delim,headstr,byear_tc,eyear_tc,nyears_tc,years_tc,missdbl,im,Idx
begin
  nmonths = 12
  
  ; Read in .data file
  strs = asciiread(fname,-1,"string")
  nlins = dimsizes(strs)
  delim = " "
  
  ; Process header
  headstr = strs(0)
  byear_tc = stringtoint(str_get_field(headstr, 1, delim))
  eyear_tc = stringtoint(str_get_field(headstr, 2, delim))
  nyears_tc = eyear_tc-byear_tc+1
  years_tc  = todouble(fspan(byear_tc,eyear_tc,nyears_tc))
  
  ; get missing value on line after data
  missdbl = stringtodouble( str_get_field(strs(nyears_tc+1), 1, delim) )
  
  ; create main array and fill it in.
  Idx = new((/nyears_tc,nmonths/),"double",missdbl)
  Idx@_FillValue = missdbl
  Idx!0     = "year"
  Idx&year  = years_tc
  Idx!1     = "month"
  Idx&month = todouble( fspan(1,nmonths,nmonths) )
  do im=1,nmonths
      Idx(:,im-1) = (/ stringtodouble(str_get_field(strs(1:nyears_tc), im+1, delim) ) /)
  end do

  return(Idx)
end

undef("readBOM_MJO_Daily_Index")
function readBOM_MJO_Daily_Index(fname:string)
local strs,nlins,delim,missdbl,missint,year,month,day \
     ,RMM1,RMM2,phase,amplitude,unitOfTime,t0,times
begin
  ; Read in file
  strs = asciiread(fname,-1,"string")
  nlins = dimsizes(strs)
  delim = " "
  
  ; get missing value on line after data
  missdbl = -999.0D
  missint = -999
  
  year      = stringtointeger( str_get_field(strs(2:nlins-1), 1, delim) )
  month     = stringtointeger( str_get_field(strs(2:nlins-1), 2, delim) )
  day       = stringtointeger( str_get_field(strs(2:nlins-1), 3, delim) )
  RMM1      = stringtodouble(  str_get_field(strs(2:nlins-1), 4, delim) )
  RMM2      = stringtodouble(  str_get_field(strs(2:nlins-1), 5, delim) )
  phase     = stringtointeger( str_get_field(strs(2:nlins-1), 6, delim) )
  amplitude = stringtodouble(  str_get_field(strs(2:nlins-1), 7, delim) )

  unitOfTime = "days since 1970-01-01 00:00:00"
  t0    = conform(day,0,-1)
  times = cd_inv_calendar(year,month,day,t0,t0,t0,unitOfTime,0)
  times@units=unitOfTime
  times!0     = "time"
  times&time  = times

  ; create main array and fill it in.
  RMM1@_FillValue = missdbl
  RMM1 = (/ where(RMM1 .lt. 1.0e35,RMM1,RMM1@_FillValue) /)
  RMM1!0     = "time"
  RMM1&time  = times

  RMM2@_FillValue = missdbl
  RMM2 = (/ where(RMM2 .lt. 1.0e35,RMM2,RMM2@_FillValue) /)
  RMM2!0     = "time"
  RMM2&time  = times

  phase@_FillValue = missint
  phase = (/ where(phase .lt. 999,phase,phase@_FillValue) /)
  phase!0     = "time"
  phase&time  = times

  amplitude@_FillValue = missdbl
  amplitude = (/ where(amplitude .lt. 1.0e35,amplitude,amplitude@_FillValue) /)
  amplitude!0     = "time"
  amplitude&time  = times

  return([/year,month,day,times,RMM1,RMM2,phase,amplitude/])
end

undef("readENSO_Weekly_Index")
function readENSO_Weekly_Index(fname:string)
local MONS,strs,nlins,delim,missdbl,datastrs,dsizes_a,indices,ddMONyyyy,year,month,day \
     ,NINO12,NINO12A,NINO3,NINO3A,NINO34,NINO34A,NINO4,NINO4A,unitOfTime,t0,times
begin
  MONS = (/ "NON", "JAN", "FEB", "MAR", "APR", "MAY", "JUN" \
                 , "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" /)
  ; Read in file
  strs = asciiread(fname,-1,"string")
  nlins = dimsizes(strs)
  delim = " "
  
  ; get missing value on line after data
  missdbl = -999.0D
  
  datastrs = strs(4:nlins-1)
  
  ddMONyyyy = str_get_field(datastrs, 1, delim)
  day    = stringtoint(str_get_cols(ddMONyyyy, 0, 1))
  dsizes_a = (/dimsizes(ddMONyyyy),dimsizes(MONS)/)
  indices  = ind_resolve(ind(ndtooned(conform_dims(dsizes_a,MONS,1).eq. \
                                      conform_dims(dsizes_a,str_get_cols(ddMONyyyy, 2, 4),0))) \
                        ,dsizes_a)
  month  = indices(:,1)
  year   = stringtoint(str_get_cols(ddMONyyyy, 5, 8))
  
  NINO12  = stringtodouble(  str_get_field(datastrs, 2, delim) )
  NINO12A = stringtodouble(  str_get_field(datastrs, 3, delim) )
  NINO3   = stringtodouble(  str_get_field(datastrs, 4, delim) )
  NINO3A  = stringtodouble(  str_get_field(datastrs, 5, delim) )
  NINO34  = stringtodouble(  str_get_field(datastrs, 6, delim) )
  NINO34A = stringtodouble(  str_get_field(datastrs, 7, delim) )
  NINO4   = stringtodouble(  str_get_field(datastrs, 8, delim) )
  NINO4A  = stringtodouble(  str_get_field(datastrs, 9, delim) )

  unitOfTime = "days since 1970-01-01 00:00:00"
  t0    = conform(day,0,-1)
  times = cd_inv_calendar(year,month,day,t0,t0,t0,unitOfTime,0)
  times@units=unitOfTime
  times!0     = "time"
  times&time  = times

  ; create main array and fill it in.
  NINO12@_FillValue = missdbl
  NINO12 = (/ where(NINO12 .lt. 1.0e35,NINO12,NINO12@_FillValue) /)
  NINO12!0     = "time"
  NINO12&time  = times

  NINO12A@_FillValue = missdbl
  NINO12A = (/ where(NINO12A .lt. 1.0e35,NINO12A,NINO12A@_FillValue) /)
  NINO12A!0     = "time"
  NINO12A&time  = times

  ; create main array and fill it in.
  NINO3@_FillValue = missdbl
  NINO3 = (/ where(NINO3 .lt. 1.0e35,NINO3,NINO3@_FillValue) /)
  NINO3!0     = "time"
  NINO3&time  = times

  NINO3A@_FillValue = missdbl
  NINO3A = (/ where(NINO3A .lt. 1.0e35,NINO3A,NINO3A@_FillValue) /)
  NINO3A!0     = "time"
  NINO3A&time  = times

  ; create main array and fill it in.
  NINO34@_FillValue = missdbl
  NINO34 = (/ where(NINO34 .lt. 1.0e35,NINO34,NINO34@_FillValue) /)
  NINO34!0     = "time"
  NINO34&time  = times

  NINO34A@_FillValue = missdbl
  NINO34A = (/ where(NINO34A .lt. 1.0e35,NINO34A,NINO34A@_FillValue) /)
  NINO34A!0     = "time"
  NINO34A&time  = times

  ; create main array and fill it in.
  NINO4@_FillValue = missdbl
  NINO4 = (/ where(NINO4 .lt. 1.0e35,NINO4,NINO4@_FillValue) /)
  NINO4!0     = "time"
  NINO4&time  = times

  NINO4A@_FillValue = missdbl
  NINO4A = (/ where(NINO4A .lt. 1.0e35,NINO4A,NINO4A@_FillValue) /)
  NINO4A!0     = "time"
  NINO4A&time  = times

  return([/year,month,day,times,NINO12,NINO12A,NINO3,NINO3A,NINO34,NINO34A,NINO4,NINO4A/])
end

undef("readPSL_Daily_Index")
function readPSL_Daily_Index(fname:string)
local strs,nlins,delim,missdbl,year,month,day \
     ,Idx,unitOfTime,t0,times
begin
  ; Read in file
  strs = asciiread(fname,-1,"string")
  nlins = dimsizes(strs)
  delim = ", "
  
  ; get missing value on line after data
  missdbl = -999.0D
  
  year      = stringtointeger( str_get_field(strs(0:nlins-3), 1, delim) )
  month     = stringtointeger( str_get_field(strs(0:nlins-3), 2, delim) )
  day       = stringtointeger( str_get_field(strs(0:nlins-3), 3, delim) )
  Idx       = stringtodouble(  str_get_field(strs(0:nlins-3), 4, delim) )

  unitOfTime = "days since 1970-01-01 00:00:00"
  t0    = conform(day,0,-1)
  times = cd_inv_calendar(year,month,day,t0,t0,t0,unitOfTime,0)
  times@units=unitOfTime
  times!0     = "time"
  times&time  = times

  ; create main array and fill it in.
  Idx@_FillValue = missdbl
  Idx = (/ where(Idx .lt. 1.0e35,Idx,Idx@_FillValue) /)
  Idx!0     = "time"
  Idx&time  = times

  return([/year,month,day,times,Idx/])
end

undef("readCPC_Daily_Index")
function readCPC_Daily_Index(fname:string)
local strs,nlins,delim,missdbl,year,month,day \
     ,Idx,unitOfTime,t0,times
begin
  ; Read in file
  strs = asciiread(fname,-1,"string")
  nlins = dimsizes(strs)
  delim = " "
  
  ; get missing value on line after data
  missdbl = -999.0D
  
  year      = stringtointeger( str_get_field(strs(0:nlins-1), 1, delim) )
  month     = stringtointeger( str_get_field(strs(0:nlins-1), 2, delim) )
  day       = stringtointeger( str_get_field(strs(0:nlins-1), 3, delim) )
  Idx       = stringtodouble(  str_get_field(strs(0:nlins-1), 4, delim) )

  unitOfTime = "days since 1970-01-01 00:00:00"
  t0    = conform(day,0,-1)
  times = cd_inv_calendar(year,month,day,t0,t0,t0,unitOfTime,0)
  times@units=unitOfTime
  times!0     = "time"
  times&time  = times

  ; create main array and fill it in.
  Idx@_FillValue = missdbl
  Idx = (/ where(Idx .lt. 1.0e35,Idx,Idx@_FillValue) /)
  Idx!0     = "time"
  Idx&time  = times

  return([/year,month,day,times,Idx/])
end

undef("readUSGSRunoff")
function readUSGSRunoff(fname:string)
local nmonths,strs,nlins,delim,byear,eyear,nyears,missdbl,Out,il,iy,ibsn,cstrs
begin
  ; https://waterwatch.usgs.gov/index.php?id=wwds_runoff
  nmonths = 12
  nbasins = 18
  
  ; Read in .data file
  strs  = asciiread(fname,-1,"string")
  nlins = dimsizes(strs)
  delim =  "	"
  
  byear = 1900
  eyear = 2022
  nyears = eyear-byear+1
  
  ; create main array and fill it in.
  Out = new((/nyears,nmonths,nbasins/),"double",-999.0D)
  Out!0     = "year"
  Out&year  = todouble( ispan(byear,eyear,1) ) ; would like to move away from double for coords, but other code uses it!
  Out!1     = "month"
  Out&month = todouble( ispan(1,nmonths,1)   )
  Out!2     = "basin"
  Out&basin = ispan(0,nbasins-1,1)

  il = 1
  iy = 0
  ; First year
  cstrs = strs(il:il+2)
  print("iy="+iy)
  print(""+cstrs)
  do ibsn=1,nbasins
    Out(iy,9:,ibsn-1) = (/ stringtodouble(str_get_field(cstrs, ibsn+1, delim) ) /)
  end do
  il = il + 3
  ; Full years
  do iy=1,nyears-2
    cstrs := strs(il:il+11)
    print("iy="+iy)
    print(""+cstrs)
    do ibsn=1,nbasins
      Out(iy,:,ibsn-1) = (/ stringtodouble(str_get_field(cstrs, ibsn+1, delim) ) /)
    end do
    il = il + 12
  end do
  ; Last year
  iy = nyears-1
  cstrs := strs(il:il+8)
  print("iy="+iy)
  print(""+cstrs)
  do ibsn=1,nbasins
    Out(iy,:8,ibsn-1) = (/ stringtodouble(str_get_field(cstrs, ibsn+1, delim) ) /)
  end do

  return(Out)
end

undef("readUSGSRunoff_HUC4")
function readUSGSRunoff_HUC4(fname:string,HUCs:string)
local nmonths,strs,nlins,delim,byear,eyear,nyears,missdbl,Out,il,iy,ibsn,cstrs
begin
  ; https://waterwatch.usgs.gov/index.php?id=wwds_runoff
  nmonths = 12
  nbasins = dimsizes(HUCs)
  
  ; Read in .data file
  strs  = asciiread(fname,-1,"string")
  nlins = dimsizes(strs)
  delim =  "	"
  
  byear = 1900
  eyear = 2022
  nyears = eyear-byear+1
  
  ; create main array and fill it in.
  Out = new((/nyears,nmonths,nbasins/),"double",-999.0D)
  Out!0     = "year"
  Out&year  = todouble( ispan(byear,eyear,1) ) ; would like to move away from double for coords, but other code uses it!
  Out!1     = "month"
  Out&month = todouble( ispan(1,nmonths,1)   )
  Out!2     = "basin"
  Out&basin = ispan(0,nbasins-1,1)

  hstr  = strs(0)
  hstrs = str_split (hstr,delim)
  do ibsn=0,nbasins-1
    il = 1
    iy = 0
    ; First year
    ifld = str_match_ind(hstrs,HUCs(ibsn)) + 1
    cstrs := strs(il:il+2)
    Out(iy,9:,ibsn) = (/ stringtodouble(str_get_field(cstrs, ifld, delim) ) /)
    il = il + 3
    ; Full years
    do iy=1,nyears-2
      cstrs := strs(il:il+11)
      Out(iy,:,ibsn) = (/ stringtodouble(str_get_field(cstrs, ifld, delim) ) /)
      il = il + 12
    end do
    ; Last year
    iy = nyears-1
    cstrs := strs(il:il+8)
    Out(iy,:8,ibsn) = (/ stringtodouble(str_get_field(cstrs, ifld, delim) ) /)
  end do

  return(Out)
end

undef("writeMonthlyIndex")
procedure writeMonthlyIndex(fname:string,VarIdx[*][*]:snumeric)
local years_tc,nyears_tc,byear_tc,eyear_tc,alist,afmt,header,footer,hlist,flist
begin
  years_tc  = VarIdx&year
  nyears_tc = dimsizes(years_tc)
  byear_tc  = years_tc(0)
  eyear_tc  = years_tc(nyears_tc-1)
  
  alist = [/ years_tc, VarIdx(:,0), VarIdx(:,1), VarIdx(:,2), VarIdx(:,3), VarIdx(:,4), VarIdx(:,5), VarIdx(:,6), VarIdx(:,7), VarIdx(:,8), VarIdx(:,9), VarIdx(:,10), VarIdx(:,11) /]
  afmt  = "%4.0f %9.3f %9.3f %9.3f %9.3f %9.3f %9.3f %9.3f %9.3f %9.3f %9.3f %9.3f %9.3f"

  header = (/"         "+byear_tc+" "+eyear_tc /)
  footer = (/ sprintf("%4.3f",VarIdx@_FillValue), \
              "detrended" /)

  hlist = [/header/]
  flist = [/footer/]
  
  system("/bin/rm -f "+fname)   ; remove any pre-existing file
  print("write to "+fname)
  write_table(fname, "w", hlist, "%s ")
  write_table(fname, "a", alist, afmt)
  write_table(fname, "a", flist, "%s ")
  print("")
end

undef("getMonthlyIndex_Years")
function getMonthlyIndex_Years(fname:string,byear:numeric,eyear:numeric)
local nmonths,TC_Idx_In,TC_Idx,ilag,lag0,years_in,nyears_in,byear_in,eyear_in,byear_max,eyear_min,nyears
begin
  nmonths = 12
  
  ; Get teleconnections index
  TC_Idx_In = getMonthlyIndex(fname)

  years_in  = TC_Idx_In&year
  nyears_in = dimsizes(years_in)
  byear_in  = years_in(0)
  eyear_in  = years_in(nyears_in-1)
  byear_max = byear_in > byear
  eyear_min = eyear_in < eyear

  nyears    = toint(eyear - byear + 1)

  TC_Idx := new((/nyears,12/),typeof(TC_Idx_In),TC_Idx_In@_FillValue)
  TC_Idx!0     = "year"
  TC_Idx&year  = todouble( fspan(byear,eyear,nyears) )
  TC_Idx!1     = "month"
  TC_Idx&month = todouble( fspan(1,nmonths,nmonths) )
  
  TC_Idx({byear_max:eyear_min},:) = (/ TC_Idx_In({byear_max:eyear_min},:) /)

  return(TC_Idx)
end

undef("getMonthlyIndexNLeads")
function getMonthlyIndexNLeads(fname:string,VarCoords[*][*][*]:snumeric,byear:numeric,eyear:numeric)
local dsizes,TC_Idx_In,TC_Idx,ild
begin
  dsizes = dimsizes(VarCoords)
  
  ; Get teleconnections index
  TC_Idx_In = getMonthlyIndex(fname)

  ; Need to set index for different lead times
  TC_Idx := new(dsizes,typeof(TC_Idx_In),TC_Idx_In@_FillValue)
  copy_VarCoords(VarCoords,TC_Idx)
  copy_VarAtts(TC_Idx_In,TC_Idx)

  do ild=0,dsizes(0)-1
    TC_Idx(ild,:,0    :ild) = (/ TC_Idx_In({byear-1:eyear-1},{12-ild:12    }) /)
    TC_Idx(ild,:,ild+1:11 ) = (/ TC_Idx_In({byear  :eyear  },{1     :11-ild}) /)
  end do

  return(TC_Idx)
end

undef("getMonthlyIndexNLeads_Lag")
function getMonthlyIndexNLeads_Lag(fname:string,VarCoords[*][*][*]:snumeric,byear:numeric,eyear:numeric,lag:integer)
local dsizes,TC_Idx_In,TC_Idx,ild,ilag,lag0,years_in,nyears_in,byear_in,eyear_in,byear_max,eyear_min,byear_max_1,eyear_min_1
begin
  lag0 = lag-1
  dsizes = dimsizes(VarCoords)
  
  ; Get teleconnections index
  TC_Idx_In = getMonthlyIndex(fname)

  years_in  = TC_Idx_In&year
  nyears_in = dimsizes(years_in)
  byear_in  = years_in(0)
  eyear_in  = years_in(nyears_in-1)
  byear_max = byear_in > byear
  eyear_min = eyear_in < eyear
  byear_max_1 = byear_in+1 > byear
  eyear_min_1 = eyear_in+1 < eyear

  ; Need to set index for different lead times
  TC_Idx := new(dsizes,typeof(TC_Idx_In),TC_Idx_In@_FillValue)
  copy_VarCoords(VarCoords,TC_Idx)
  copy_VarAtts(TC_Idx_In,TC_Idx)

  do ild=0,dsizes(0)-1
    ilag = lag0 + ild
    TC_Idx(ild,{byear_max_1:eyear_min_1},0     :ilag) = (/ TC_Idx_In({byear_max_1-1:eyear_min_1-1},{12-ilag:12     }) /)
    TC_Idx(ild,{byear_max  :eyear_min  },ilag+1:11  ) = (/ TC_Idx_In({byear_max    :eyear_min    },{1      :11-ilag}) /)
  end do

  return(TC_Idx)
end

undef("get_persNld")
function get_persNld(X:numeric,nleads:snumeric,span_dname:string,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
  alldims,dims,last_dim,out_dsizes,OUT
begin
  maplist    := get_mapdims([/X, nleads/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  
  dims   = DimsFromNames2(dNames_all,dim_args)

  OUT = ncl_c_get_persNld(X,nleads,dims,mpdims)

  out_dsizes = dimsizes(OUT)
  last_dim   = dimsizes(out_dsizes)-1

  copy_Coords_Fro(dNames_all,dList_all,OUT,mpdims(0,:))
  OUT!last_dim = span_dname
  if (isatt(span_dname,"dim")) then
    OUT&$span_dname$ = span_dname@dim
  else
    OUT&$span_dname$ = todouble( fspan(0,nleads-1,nleads) )
  end if
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("get_persNld_Lag")
function get_persNld_Lag(X:numeric,nleads:snumeric,lag:snumeric,span_dname:string,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
  alldims,dims,last_dim,out_dsizes,OUT
begin
  maplist    := get_mapdims([/X, nleads, lag/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  
  dims   = DimsFromNames2(dNames_all,dim_args)

  OUT = ncl_c_get_persNld_Lag(X,nleads,lag,dims,mpdims)

  out_dsizes = dimsizes(OUT)
  last_dim   = dimsizes(out_dsizes)-1

  copy_Coords_Fro(dNames_all,dList_all,OUT,mpdims(0,:))
  OUT!last_dim = span_dname
  if (isatt(span_dname,"dim")) then
    OUT&$span_dname$ = span_dname@dim
  else
    if (nleads.eq.1) then
      OUT&$span_dname$ = 0
    else
      OUT&$span_dname$ = todouble( fspan(0,nleads-1,nleads) )
    end if
  end if
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end


undef("getMonthlyIndexNLeads2_Lag")
function getMonthlyIndexNLeads2_Lag(fname:string,byear:numeric,eyear:numeric,nleads:integer,lag:integer)
local TC_Idx_In,nyears_in,byear_all,eyear_all,years_idx,nyears_idx,byear_idx,eyear_idx,years,TC_Idx_In_2,TC_Idx
begin
  TC_Idx_In  = getMonthlyIndex(fname)
  nyears_in  = dimsizes(TC_Idx_In&year)
  byear_all  = byear<TC_Idx_In&year(0)
  eyear_all  = eyear>TC_Idx_In&year(nyears_in-1)
  
  TC_Idx_In := TC_Idx_In({year|byear_all:eyear_all},month|:)
  
  years_idx  = TC_Idx_In&year
  nyears_idx = dimsizes(years_idx)
  byear_idx  = years_idx(0)
  eyear_idx  = years_idx(nyears_idx-1)
  
  years     := todouble( fspan(byear_all,eyear_all,toint(eyear_all-byear_all+1)) )
  years!0    = "year"
  years&year = years

  TC_Idx_In_2 = new_Meta_by_Coords(typeof(TC_Idx_In),[/years,TC_Idx_In&month/],(/"year","month"/),TC_Idx_In@_FillValue)
  TC_Idx_In_2({byear_idx:eyear_idx},:) = (/ TC_Idx_In(year|:,month|:) /)

  TC_Idx  = get_persNld_Lag(TC_Idx_In_2,nleads,lag,"lead",(/"year","month"/))

  return(TC_Idx(lead|:,{year|byear:eyear},month|:))
end



undef("start_2_valid")
function start_2_valid(X:numeric,dim_args[*]:string)
local maplist,dNames_all,dList_all,ndims, \
  alldims,dims, \
  OUT
begin
  maplist = get_mapdims_1(X)
  alldims    = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  ndims      = maplist[3]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  OUT = ncl_c_start_2_valid(X,dims)
  
  copy_VarMeta(X,OUT)
  return(OUT)
end


undef("getBasinVars")
function getBasinVars(fname:string)
local strs_in,strs,nlins,delim,basin_shpnum,basin_names,shape_where_fld,shape_where_vals,basin_fnames
begin
  strs_in = asciiread(fname,-1,"string")
  strs    = strs_in(get1Dindex_Exclude(strs_in,""))
  nlins   = dimsizes(strs)
  
  delim = ", "+str_get_dq()
  basin_shpnum     = stringtoint(str_get_field(strs, 1, delim))
  basin_names      =             str_get_field(strs, 2, delim)
  shape_where_fld  =             str_get_field(strs, 3, delim)
  shape_where_vals =             str_get_field(strs, 4, delim)
  basin_fnames     =             str_get_field(strs, 5, delim)

  return([/basin_shpnum,basin_names,shape_where_fld,shape_where_vals,basin_fnames/])
end

undef("getTCIndexList")
function getTCIndexList(fname:string)
local strs_in,strs,nlins,delim,tc_idxs_disp,tc_idxs,tc_lag
begin
  strs_in = asciiread(fname,-1,"string")
  strs    = strs_in(get1Dindex_Exclude(strs_in,""))
  nlins   = dimsizes(strs)
  
  delim = ", "+str_get_dq()
  tc_idxs_disp =             str_get_field(strs, 1, delim)
  tc_idxs      =             str_get_field(strs, 2, delim)
  tc_lag       = stringtoint(str_get_field(strs, 3, delim))

  return([/tc_idxs_disp,tc_idxs,tc_lag/])
end


