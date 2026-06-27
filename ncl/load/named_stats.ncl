; Created by Bill Scheftic
; - It is necessary to name dimensions and assign coordinate arrays for all dimensions of input variables!

if (.not.isdefined("contrib_declared")) then
 loadscript("$NCARG_ROOT/lib/ncarg/nclex/gsun/gsn_code.ncl")
 loadscript("$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_csm.ncl")
 loadscript("$NCARG_ROOT/lib/ncarg/nclscripts/csm/contributed.ncl")
 contrib_declared = 1
end if
if (.not.isdefined("functions_declared")) then
 loadscript("$NCL_USER_DIR/load/functions.ncl")
 functions_declared = 1
end if

undef("named_skill")
function named_skill(X:numeric,Y:numeric)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,dSizes_all,Type,Atts,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]

  OUT = ncl_c_skill(X,Y,mpdims)
  
  copy_Coords_Fro(dNames_all,dList_all,OUT,DimsFromNames2(dNames_all,dNames_all))
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("inv_skill")
function inv_skill(X:numeric)
local OUT
begin
  OUT = ncl_c_inv_skill(X)
  copy_VarMeta(X,OUT)
  return(OUT)
end

undef("named_tanh")
function named_tanh(X:numeric)
local OUT
begin
  OUT = ncl_c_tanh(X)
  copy_VarMeta(X,OUT)
  return(OUT)
end

undef("named_atanh")
function named_atanh(X:numeric)
local OUT
begin
  OUT = ncl_c_atanh(X)
  copy_VarMeta(X,OUT)
  return(OUT)
end

undef("named_amin2")
function named_amin2(X:numeric,Y:numeric)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  OUT = ncl_c_amin2(X,Y,mpdims)
  
  copy_Coords_Fro(dNames_all,dList_all,OUT,DimsFromNames2(dNames_all,dNames_all))
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_amax2")
function named_amax2(X:numeric,Y:numeric)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  OUT = ncl_c_amax2(X,Y,mpdims)
  
  copy_Coords_Fro(dNames_all,dList_all,OUT,DimsFromNames2(dNames_all,dNames_all))
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_mx_b")
function named_mx_b(m:double,x:double,b:double)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,OUT
begin
  maplist    = get_mapdims([/x, m, b/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars  = maplist[3]
  
  OUT = ncl_c_mx_b(m,x,b,mpdims((/1,0,2/),:))
  
  copy_Coords_Fro(dNames_all,dList_all,OUT,DimsFromNames2(dNames_all,dNames_all))
  copy_VarAtts_except(m,OUT,"_FillValue")
  return(OUT)
end

undef("named_avg")
function named_avg(IN:numeric,dim_args[*]:string)
local dims,OUT
begin
  if (get_rank0(IN).gt.dimsizes(dim_args)) then
    dims = dimnames_to_indexes(IN,dim_args)
    OUT  = dim_avg_n_Wrap(IN, dims)
  else
    OUT  = avg(IN)
    copy_VarAtts(IN,OUT)
  end if

  return(OUT)
end

undef("fisher_avg")
function fisher_avg(IN:double,dim_args[*]:string)
local IN_z,OUT_z,OUT
begin
  IN_z  = named_atanh(IN)
  OUT_z = named_avg(IN_z,dim_args)
  OUT   = named_tanh(OUT_z)

  return(OUT)
end

undef("named_median")
function named_median(X:snumeric,dim_args[*]:string)
local maplist,dNames_all,dList_all,alldims,dims,indcopy,OUT
begin
  maplist = get_mapdims([/X/],False)
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  OUT = dim_median_n(X, dims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts(X,OUT)
  return(OUT)
end

undef("named_extval_mlegam")
function named_extval_mlegam(X:snumeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,alldims,dims,indcopy,OUT,rank_out
begin
  maplist = get_mapdims([/X/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims = DimsFromNames2(dNames_all,dim_args)
  OUT = extval_mlegam(X, dims, False)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if

  rank_out = get_rank0(OUT)-1
  if (.not.ismissing(indcopy(0))) then
    if (rank_out.gt.1) then
      copy_CoordsFroTo(dNames_all,dList_all,OUT,mpdims(0,indcopy),ispan(1,rank_out,1))
    else
      copy_CoordsFroTo(dNames_all,dList_all,OUT,mpdims(0,indcopy),1)
    end if
  end if

  OUT!0 = "param"
  OUT&param = ispan(0,4,1)
  OUT@param_type = (/ "center", "scale", "shape", "variance", "median" /)
  copy_VarAtts(X,OUT)
  return(OUT)
end

undef("named_gamfit")
function named_gamfit(X:snumeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,alldims,dims,indcopy,OUT,rank_out
begin
  maplist = get_mapdims([/X/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims = DimsFromNames2(dNames_all,dim_args)
  OUT = dim_gamfit_n(X, False, dims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if

  rank_out = get_rank0(OUT)-1
  if (.not.ismissing(indcopy(0))) then
    if (rank_out.gt.1) then
      copy_CoordsFroTo(dNames_all,dList_all,OUT,mpdims(0,indcopy),ispan(1,rank_out,1))
    else
      copy_CoordsFroTo(dNames_all,dList_all,OUT,mpdims(0,indcopy),1)
    end if
  end if

  OUT!0 = "param"
  OUT&param = ispan(0,2,1)
  OUT@param_type = (/ "shape", "scale", "unconditional probability" /)
  copy_VarAtts(X,OUT)
  return(OUT)
end

; If dimensions are unordered this will be better.
undef("named_c_median")
function named_c_median(X:snumeric,dim_args[*]:string)
local maplist,dNames_all,dList_all,alldims,dims,indcopy,OUT
begin
  maplist = get_mapdims_1(X)
  alldims    = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  OUT = ncl_c_median(X,dims)
  
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_mean")
function named_mean(X:snumeric,dim_args[*]:string)
local maplist,dNames_all,dList_all,alldims,dims,indcopy,OUT
begin
  maplist = get_mapdims_1(X)
  alldims    = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims = DimsFromNames2(dNames_all,dim_args)
  OUT  = ncl_c_mean(X,dims)
  
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_min")
function named_min(X:snumeric,dim_args[*]:string)
local maplist,dNames_all,dList_all,alldims,dims,indcopy,OUT
begin
  maplist = get_mapdims_1(X)
  alldims    = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  OUT = ncl_c_min(X,dims)
  
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_max")
function named_max(X:snumeric,dim_args[*]:string)
local maplist,dNames_all,dList_all,alldims,dims,indcopy,OUT
begin
  maplist = get_mapdims_1(X)
  alldims    = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  OUT = ncl_c_max(X,dims)
  
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_sum")
function named_sum(IN:numeric,dim_args[*]:string)
local dims,OUT
begin
  if (dimsizes(dim_args).eq.dimsizes(dimsizes(IN))) then
    OUT = sum(IN)
    copy_VarAtts(IN,OUT)
  else
    dims = DimsFromNames(IN,dim_args)
    OUT = dim_sum_n_Wrap(IN, dims)
  end if
  return(OUT)
end

undef("named_cumsum")
function named_cumsum(IN:numeric,opt:integer,dim_args[*]:string)
local dims,OUT
begin
  dims = DimsFromNames(IN,dim_args)
  OUT = dim_cumsum_n_Wrap(IN,opt,dims)
  return(OUT)
end

undef("named_runave")
function named_runave(IN:numeric,nave[1]:numeric,opt:integer,dim_args[*]:string)
local dims,OUT
begin
  dims = DimsFromNames(IN,dim_args)
  OUT = runave_n_Wrap(IN,nave,opt,dims)
  return(OUT)
end

undef("named_num")
function named_num(X:logical,dim_args[*]:string)
local maplist,dNames_all,dList_all,alldims,dims,indcopy,OUT
begin
  maplist = get_mapdims([/X/],False)
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims = DimsFromNames2(dNames_all,dim_args)
  OUT  = dim_num_n(X, dims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end


undef("nvalid_1")
function nvalid_1(X:numeric,dim_args[*]:string)
local maplist,dNames_all,dList_all, \
      alldims,dims,indcopy,OUT
begin
  maplist    = get_mapdims_1(X)
  alldims    = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  OUT = ncl_c_nnonmiss(X,dims)
  
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("nvalid_2")
function nvalid_2(X:numeric,Y:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,rank, \
      alldims,dims,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank       = maplist[7]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  OUT = ncl_c_nvalid_2(X,Y,dims,mpdims)
  
  alldims = ispan(0,rank-1,1)
  ; alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("nvalid_3")
function nvalid_3(X:numeric,Y:numeric,Z:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y, Z/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  OUT = ncl_c_nvalid_3(X,Y,Z,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("nvalid_4")
function nvalid_4(X:numeric,Y:numeric,Z:numeric,U:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y, Z, U/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  OUT = ncl_c_nvalid_4(X,Y,Z,U,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("nvalid_Lst")
function nvalid_Lst(V:list,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,indcopy,OUT
begin
  maplist = get_mapdims(V,False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  nLsts = ListCount(V)
  if (nLsts.eq.1) then
    OUT = ncl_c_nnonmiss(V[0],dims)
  elseif (nLsts.eq.2) then
    OUT = ncl_c_nvalid_2(V[0],V[1],dims,mpdims)
  elseif (nLsts.eq.3) then
    OUT = ncl_c_nvalid_3(V[0],V[1],V[2],dims,mpdims)
  elseif (nLsts.eq.4) then
    OUT = ncl_c_nvalid_4(V[0],V[1],V[2],V[3],dims,mpdims)
  else
    print("nvalid_Lst: Error: No function named ncl_c_nvalid_"+n+" exists")
    exit()
  end if
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end


undef("named_stat4")
function named_stat4(X:numeric,dim_args[*]:string)
local maplist,dNames_all,dList_all,alldims,dims,indcopy,OUT,rank_out
begin
  maplist = get_mapdims([/X/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims = DimsFromNames2(dNames_all,dim_args)
  OUT  = rm_single_dims(dim_stat4_n(X, dims))

  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if

  rank_out = get_rank0(OUT)-1
  if (rank_out.gt.1) then
    copy_CoordsFroTo(dNames_all,dList_all,OUT,mpdims(0,indcopy),ispan(1,rank_out,1))
  else
    copy_CoordsFroTo(dNames_all,dList_all,OUT,mpdims(0,indcopy),1)
  end if

  OUT!0 = "stat"
  OUT&stat = ispan(0,3,1)
  OUT@stat_type = (/ "average", "variance", "skewness", "kurtosis" /)
  copy_VarAtts(X,OUT)
  return(OUT)
end

undef("nvalid_one")
function nvalid_one(X,dim_args[*]:string)
local VAR_True,NValid
begin
    VAR_True    = .not.ismissing(X)
    copy_VarMeta_except(X,VAR_True,"_FillValue")
    
    NValid = named_num(VAR_True,dim_args)
    return(NValid)
end

undef("nvalid_pair")
function nvalid_pair(X,Y,dim_args[*]:string)
local maplist,dNames_all,dList_all,X_cnfrm,Y_cnfrm,VAR_True,NValid
begin
    maplist = get_mapdims([/X, Y/],False)
    dNames_all = maplist[1]
    dList_all  = maplist[2]
    dSizes_all = maplist[4]
    
    X_cnfrm = conform_dims_wrap(dNames_all,dList_all,dSizes_all,X,False)
    Y_cnfrm = conform_dims_wrap(dNames_all,dList_all,dSizes_all,Y,False)
    
    VAR_True    = (.not.ismissing(X_cnfrm)).and.(.not.ismissing(Y_cnfrm))
    copy_VarMeta_except(X_cnfrm,VAR_True,"_FillValue")
    
    NValid = named_num(VAR_True,dim_args)
    return(NValid)
end


undef("named_equiv_sample_size")
function named_equiv_sample_size(X:numeric,siglvl[1]:numeric,dim_args[*]:string)
local Xr,OUT
begin
  Xr = dims2end(X,dim_args) ; probably need to merge dims through reshape if dim_args > 1
  
  OUT = equiv_sample_size(Xr, siglvl, 0)
  
  copy_VarCoords_1(Xr,OUT)
  copy_VarAtts_except(Xr,OUT,"_FillValue")
  return(OUT)
end



undef("named_stddev")
function named_stddev(IN:numeric,dim_args[*]:string)
local dims,OUT
begin
  if (get_rank0(IN).gt.dimsizes(dim_args)) then
    dims = dimnames_to_indexes(IN,dim_args)
    OUT  = dim_stddev_n_Wrap(IN, dims)
  else
    OUT  = stddev(IN)
    copy_VarAtts(IN,OUT)
  end if
  return(OUT)
end


undef("named_variance")
function named_variance(IN:numeric,dim_args[*]:string)
local dims,OUT
begin
  if (get_rank0(IN).gt.dimsizes(dim_args)) then
    dims = dimnames_to_indexes(IN,dim_args)
    OUT  = dim_variance_n_Wrap(IN, dims)
  else
    OUT  = variance(IN)
    copy_VarAtts(IN,OUT)
  end if
  return(OUT)
end


undef("named_ttest")
function named_ttest(xAve:numeric,xVar:numeric,xN:numeric,yAve:numeric,yVar:numeric,yN:numeric,opt:logical)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,cnfrm_xAve,cnfrm_xVar,cnfrm_xN,cnfrm_yAve,cnfrm_yVar,cnfrm_yN, \
      iflag,tval_opt,indcopy,rank_out,OUT
begin
  maplist    = get_mapdims([/xAve, xVar, xN, yAve, yVar, yN/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  dSizes_all = maplist[4]

  ; Must be same size for ttest. 
  cnfrm_xAve = conform_dims_wrap(dNames_all,dList_all,dSizes_all,xAve,True)
  cnfrm_xVar = conform_dims_wrap(dNames_all,dList_all,dSizes_all,xVar,True)
  cnfrm_xN   = conform_dims_wrap(dNames_all,dList_all,dSizes_all,xN  ,True)
  cnfrm_yAve = conform_dims_wrap(dNames_all,dList_all,dSizes_all,yAve,True)
  cnfrm_yVar = conform_dims_wrap(dNames_all,dList_all,dSizes_all,yVar,True)
  cnfrm_yN   = conform_dims_wrap(dNames_all,dList_all,dSizes_all,yN  ,True)

  iflag    = False ; Test on assumption that population variance between X and Y are the same
  tval_opt = False ; Only provide probabilities
  if (opt) then
    if isatt(opt,"iflag") then
        iflag = opt@iflag
    end if
    if isatt(opt,"tval_opt") then
        tval_opt = opt@tval_opt
    end if
  end if

  OUT = ttest(cnfrm_xAve,cnfrm_xVar,cnfrm_xN,cnfrm_yAve,cnfrm_yVar,cnfrm_yN, iflag, tval_opt)

  indcopy = DimsFromNames2(dNames_all,dNames_all)
  if (tval_opt) then
    rank_out = get_rank0(OUT)-1
    if (.not.ismissing(indcopy(0))) then
      if (rank_out.gt.1) then
        copy_CoordsFroTo(dNames_all,dList_all,OUT,indcopy,ispan(1,rank_out,1))
      else
        copy_CoordsFroTo(dNames_all,dList_all,OUT,indcopy,1)
      end if
    end if
    
    OUT!0 = "stat"
    OUT&stat = ispan(0,1,1)
    OUT@stat_type = (/ "pval", "tval" /)
    copy_VarAtts(xAve,OUT)
  else
    rank_out = get_rank0(OUT)
    if (.not.ismissing(indcopy(0))) then
      if (rank_out.gt.1) then
        copy_CoordsFroTo(dNames_all,dList_all,OUT,indcopy,ispan(0,rank_out-1,1))
      else
        copy_CoordsFroTo(dNames_all,dList_all,OUT,indcopy,0)
      end if
    end if
    
    copy_VarAtts(cnfrm_xAve,OUT)
  end if
  return(OUT)
end


undef("named_dim_ttest")
function named_dim_ttest(X:numeric,Y:numeric,opt:logical,dim_args[*]:string)
local iflag,tval_opt,OUT
begin
  xAve = named_avg(X,dim_args)
  xVar = named_variance(X,dim_args)
  xN   = nvalid_one(X,dim_args)
  yAve = named_avg(Y,dim_args)
  yVar = named_variance(Y,dim_args)
  yN   = nvalid_one(Y,dim_args)
  OUT  = named_ttest(xAve,xVar,xN,yAve,yVar,yN,opt)
  return(OUT)
end


undef("named_firstidx")
function named_firstidx(X:logical,dim_args[*]:string)
local maplist,dNames_all,dList_all,rank_Vars, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims_1(X)
  alldims    = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars  = maplist[3]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_firstidx(logical_to_int(X),dims)
  
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_lastidx")
function named_lastidx(X:logical,dim_args[*]:string)
local maplist,dNames_all,dList_all,rank_Vars, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims_1(X)
  alldims    = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_lastidx(logical_to_int(X),dims)
  
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end


undef("named_minind")
function named_minind(X:numeric,dim_args[*]:string)
local maplist,dNames_all,dList_all,rank_Vars, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims_1(X)
  alldims    = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_minind_n(X,dims)
  
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_maxind")
function named_maxind(X:numeric,dim_args[*]:string)
local maplist,dNames_all,dList_all,rank_Vars, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims_1(X)
  alldims    = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_maxind_n(X,dims)
  
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end


undef("named_intmode")
function named_intmode(X:snumeric,dim_args[*]:string)
local maplist,dNames_all,dList_all,rank_Vars,X_type, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims_1(X)
  alldims    = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  X_type     = maplist[5]
  
  dims  = DimsFromNames2(dNames_all,dim_args)
  rankd = dimsizes(dims)
  OUT = totype( ncl_c_intmode(toint(X),dims), X_type )
  
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_corr")
function named_corr(X:numeric,Y:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_corr(X,Y,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("r_squared")
function r_squared(X:numeric,Y:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_r_squared(X,Y,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("rsq_ols")
function rsq_ols(X:numeric,Y:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_corr(X,Y,dims,mpdims)
  OUT = (/ OUT*OUT /)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("rsq_ols_cv")
function rsq_ols_cv(X:numeric,Y:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_rsq_ols_cv(X,Y,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("rsq_ols_cv_n")
function rsq_ols_cv_n(X:numeric,Y:numeric,nout:snumeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y, nout/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_rsq_ols_cv_n(X,Y,nout,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("rsq_ols_fv_n")
function rsq_ols_fv_n(X:numeric,Y:numeric,nout:snumeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y, nout/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_rsq_ols_fv_n(X,Y,nout,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("combined_predictor_index")
function combined_predictor_index(X:numeric,r:numeric,p:numeric,p_thresh:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, r, p, p_thresh/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_combined_predictor_index(X,r,p,p_thresh,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_spcorr")
function named_spcorr(X:numeric,Y:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims  = DimsFromNames2(dNames_all,dim_args)
  rankd = dimsizes(dims)
  OUT   = ncl_gsl_stats_spearman(X,Y,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_spvar")
function named_spvar(X:numeric,Y:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_gsl_stats_spearman(X,Y,dims,mpdims)
  OUT = (/ OUT*OUT /)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_spwgt")
function named_spwgt(X:numeric,Y:numeric,wgt[1]:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_gsl_stats_spearman(X,Y,dims,mpdims)
  OUT = (/ OUT*OUT+wgt/)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_wmean")
function named_wmean(X:numeric,W:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, W/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_wmean(X,W,dims,mpdims)
  ; printVarSummary(X)
  ; printVarSummary(W)
  ; printVarSummary(OUT)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  ; printVarSummary(OUT)
  return(OUT)
end

undef("named_msd")
function named_msd(X:numeric,Y:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,rank_Vars, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars  = maplist[3]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_msd(X,Y,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_rmsd")
function named_rmsd(X:numeric,Y:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,rank_Vars, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars  = maplist[3]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_rmsd(X,Y,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_mae")
function named_mae(X:numeric,Y:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,rank_Vars, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars  = maplist[3]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_mae(X,Y,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end


undef("named_valatperc")
function named_valatperc(X:numeric,Y:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,rank_Vars, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  dims = DimsFromNames2(dNames_all,dim_args)
  OUT  = ncl_c_valatperc(X,Y,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_percatval")
function named_percatval(X:numeric,Y:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,rank_Vars, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims = DimsFromNames2(dNames_all,dim_args)
  OUT  = ncl_c_percatval(X,Y,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end


undef("named_idxfromval")
function named_idxfromval(X:numeric,Y:numeric,dim_args[*]:string)
local Ytmp,tmp_args,maplist,mpdims,dNames_all,dList_all,ndims_Vars, \
      alldims,dims,indcopy,OUT,id,isd
begin
  tmp_args = dim_args+"_tmp"
  Ytmp = Y
  rename_dims(Ytmp,dim_args,tmp_args)

  maplist   := get_mapdims([/X, Ytmp/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]

  dims      := DimsFromNames2(dNames_all,dim_args)

  OUT = ncl_c_idxfromval(X,Ytmp,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Collapse (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")

  rename_dims(OUT,tmp_args,dim_args)
  return(OUT)
end


undef("named_valfromidx")
function named_valfromidx(X:numeric,Y:numeric,dim_args[*]:string)
local Ytmp,tmp_args,maplist,mpdims,dNames_all,dList_all,ndims_Vars, \
      alldims,dims,indcopy,OUT,id,isd
begin
  tmp_args = dim_args+"_tmp"
  Ytmp = Y
  rename_dims(Ytmp,dim_args,tmp_args)

  maplist   := get_mapdims([/X, Ytmp/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]

  dims     := DimsFromNames2(dNames_all,dim_args)

  OUT = ncl_c_valfromidx(X,Ytmp,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Collapse (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")

  rename_dims(OUT,tmp_args,dim_args)
  return(OUT)
end



undef("named_percatvalsrtd")
function named_percatvalsrtd(X:numeric,val:numeric,dim_args[*]:string)
local tmp_args,maplist,mpdims,dNames_all,dList_all,ndims_Vars, \
      alldims,dims,indcopy,OUT,id,isd
begin
  tmp_args = dim_args+"_tmp"
  rename_dims(val,dim_args,tmp_args)

  maplist   := get_mapdims([/X, val/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]

  dims      := DimsFromNames2(dNames_all,dim_args)

  OUT = ncl_c_percatvalsrtd(X,val,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Collapse (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")

  rename_dims(val  ,tmp_args,dim_args)
  rename_dims(OUT,tmp_args,dim_args)
  return(OUT)
end

undef("named_valatpercsrtd")
function named_valatpercsrtd(X:numeric,perc:numeric,dim_args[*]:string)
local tmp_args,maplist,mpdims,dNames_all,dList_all,ndims_Vars, \
      alldims,dims,indcopy,OUT,id,isd
begin
  tmp_args = dim_args+"_tmp"
  rename_dims(perc,dim_args,tmp_args)

  maplist   := get_mapdims([/X, perc/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]

  dims     := DimsFromNames2(dNames_all,dim_args)

  OUT = ncl_c_valatpercsrtd(X,perc,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Collapse (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")

  rename_dims(perc,tmp_args,dim_args)
  rename_dims(OUT ,tmp_args,dim_args)
  return(OUT)
end



undef("dist_multigausswgt")
function dist_multigausswgt(X:numeric,Y:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_dist_multigausswgt(X,Y,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("dist_gausswgt")
function dist_gausswgt(X:numeric,Y:numeric)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  OUT = ncl_c_dist_gausswgt(X,Y,mpdims)
  
  copy_Coords_Fro(dNames_all,dList_all,OUT,DimsFromNames2(dNames_all,dNames_all))
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("dist_gausswgt_ave")
function dist_gausswgt_ave(X:numeric,Y:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_dist_gausswgt_ave(X,Y,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("dist_gausswgt_ave_h2")
function dist_gausswgt_ave_h2(X:numeric,Y:numeric,h2:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y, h2/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_dist_gausswgt_ave_h2(X,Y,h2,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("dist_gausswgt_wave")
function dist_gausswgt_wave(X:numeric,Y:numeric,W:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y, W/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_dist_gausswgt_wave(X,Y,W,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("dist_gausswgt_wave_h2")
function dist_gausswgt_wave_h2(X:numeric,Y:numeric,W:numeric,h2:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all, \
      alldims,dims,rankd,indcopy,OUT
begin
  maplist = get_mapdims([/X, Y, W, h2/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_dist_gausswgt_wave_h2(X,Y,W,h2,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end


undef("named_lagcorr")
function named_lagcorr(X:numeric,dim_args[*]:string)
local maplist,dNames_all,dList_all,alldims,dims,indcopy,OUT
begin
  maplist = get_mapdims_1(X)
  alldims    = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  OUT = ncl_c_lagcorr(X,dims)
  
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_lagcorrn")
function named_lagcorrn(X:numeric,n:numeric,dim_args[*]:string)
local maplist,dNames_all,dList_all,alldims,dims,indcopy,OUT
begin
  maplist = get_mapdims([/X, n/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  OUT = ncl_c_lagcorrn(X,n,dims,mpdims)
  
  alldims = DimsFromNames2(dNames_all,dNames_all)
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_nstar")
function named_nstar(X:numeric,dim_args[*]:string)
local maplist,dNames_all,dList_all,alldims,dims,indcopy,r,VAR_True,N,Nstar
begin
  maplist = get_mapdims_1(X)
  alldims    = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  r        = ncl_c_lagcorr(X,dims)
  VAR_True = .not.ismissing(X)
  N        = dim_num_n(VAR_True, dims)
  r0       = where(r.gt.0,r,0.0)
  Nstar    = todouble(N)*((1-r0)/(1+r0));
  
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,Nstar,indcopy)
  copy_VarAtts_except(X,Nstar,"_FillValue")
  copy_VarMeta(Nstar,N)
  copy_VarMeta(Nstar,r)
  return([/Nstar,N,r/])
end

undef("named_regr")
function named_regr(X:numeric,Y:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts,alldims,dims,indcopy,m,b,r,n
begin
  maplist    := get_mapdims([/X, Y/],False)
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
  m = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,Type)
  b = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,Type)
  r = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,Type)
  n = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,Type)

  ncl_c_regr_mbrn(X,Y,m,b,r,n,dims,mpdims)
  
  return([/m,b,r,n/])
end


undef("theil_sen")
function theil_sen(X:numeric,Y:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts,alldims,dims,indcopy,m,b,rsq
begin
  maplist    := get_mapdims([/X, Y/],False)
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
  m   = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,Type)
  b   = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,Type)
  rsq = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,Type)
  mad = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,Type)

  ncl_c_theil_sen(X,Y,m,b,rsq,mad,dims,mpdims)
  
  return([/m,b,rsq,mad/])
end


undef("named_stat")
function named_stat(stat_name:string,X:numeric,dim_args[*]:string)
begin
  if (stat_name.eq."avg") then
    return (named_avg(X,dim_args))
  elseif (stat_name.eq."mean") then
    return (named_mean(X,dim_args))
  elseif (stat_name.eq."fisher") then
    return (fisher_avg(X,dim_args))
  elseif (stat_name.eq."median") then
    return (named_median(X,dim_args))
  elseif (stat_name.eq."min") then
    return (named_min(X,dim_args))
  elseif (stat_name.eq."max") then
    return (named_max(X,dim_args))
  else
    print("Error in named_stat: stat_name "+stat_name+" unknown.")
  end if
end



undef("fit_cos")
procedure fit_cos(X:numeric,Y:numeric,T:numeric,P1:numeric,P2:numeric,P3:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dims
begin
  maplist    := get_mapdims([/X, Y, T/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  
  dims  = DimsFromNames2(dNames_all,dim_args)
  ncl_c_fit_cos(X,Y,T,P1,P2,P3,dims,mpdims)
  
  return([/P1,P2,P3/])
end

undef("fit_cos_Lst")
function fit_cos_Lst(X:numeric,Y:numeric,T:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts,alldims,dims,indcopy,p1,p2,p3
begin
  maplist    := get_mapdims([/X, Y, T/],False)
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
  p1 = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  p2 = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  p3 = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")

  ncl_c_fit_cos(X,Y,T,p1,p2,p3,dims,mpdims)

  return([/p1,p2,p3/])
end

undef("cos_fun")
function cos_fun(X:numeric,P1:numeric,P2:numeric,T:numeric,P3:numeric)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,P
begin
  maplist = get_mapdims([/X, P1, P2, T, P3/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  P = ncl_c_cos_fun(X,P1,P2,T,P3,mpdims)

  copy_Coords_Fro(dNames_all,dList_all,P,DimsFromNames2(dNames_all,dNames_all))
  copy_VarAtts_except(X,P,"_FillValue")
  return(P)
end


undef("fit_gumbel2")
procedure fit_gumbel2(X:numeric,P1:numeric,P2:numeric,dim_args[*]:string)
local dNames_all,dims
begin
  dNames_all = getvardims(X)
  dims = DimsFromNames2(dNames_all,dim_args)
  ncl_c_gumbel2(X,P1,P2,dims)
end

undef("fit_gumbel2_Lst")
function fit_gumbel2_Lst(X:numeric,dim_args[*]:string)
local maplist,alldims,dNames,dsizes,dims,nondims,p1,p2
begin
  maplist   = get_mapdims_1(X)
  alldims   = maplist[0]
  dNames    = maplist[1]
  dsizes    = dimsizes(X)
  dims    = DimsFromNames2(dNames,dim_args)
  nondims = get1Dindex_Exclude (alldims,dims)
    
  if (all(ismissing(nondims))) then
    p1 = 0D
    p2 = 0D
    copy_VarAtts(X,p1)
    copy_VarAtts(X,p2)
  else
    p1 = conform_dims(dsizes(nondims),0D,-1)
    p2 = conform_dims(dsizes(nondims),0D,-1)
    copy_VarMeta_Fro(X,p1,nondims)
    copy_VarMeta_Fro(X,p2,nondims)
  end if
  fit_gumbel2(X,p1,p2,dim_args)

  return([/p1,p2/])
end

undef("dist_gumbel2_P")
function dist_gumbel2_P(X:numeric,P1:numeric,P2:numeric)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,P
begin
  maplist = get_mapdims([/X, P1, P2/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  P = ncl_c_gumbel2_P(X,P1,P2,mpdims)
  
  copy_Coords_Fro(dNames_all,dList_all,P,DimsFromNames2(dNames_all,dNames_all))
  copy_VarAtts_except(X,P,"_FillValue")
  return(P)
end

undef("dist_gumbel2_Pinv")
function dist_gumbel2_Pinv(P:numeric,P1:numeric,P2:numeric)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,X
begin
  maplist = get_mapdims([/P, P1, P2/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  X = ncl_c_gumbel2_Pinv(P,P1,P2,mpdims)
  
  copy_Coords_Fro(dNames_all,dList_all,X,DimsFromNames2(dNames_all,dNames_all))
  copy_VarAtts_except(P,X,"_FillValue")
  return(X)
end


undef("fit_weibull")
procedure fit_weibull(X:numeric,P1:numeric,P2:numeric,dim_args[*]:string)
local dNames_all,mpdims,dims
begin
  dNames_all = getvardims(X)
  dims = DimsFromNames2(dNames_all,dim_args)
  ncl_c_weibull(X,P1,P2,dims)
end

undef("fit_weibull_Lst")
function fit_weibull_Lst(X:numeric,dim_args[*]:string)
local maplist,alldims,dNames,dsizes,dims,nondims,p1,p2
begin
  maplist   = get_mapdims_1(X)
  alldims   = maplist[0]
  dNames    = maplist[1]
  dsizes    = dimsizes(X)
  dims    = DimsFromNames2(dNames,dim_args)
  nondims = get1Dindex_Exclude (alldims,dims)
    
  if (all(ismissing(nondims))) then
    p1 = 0D
    p2 = 0D
    copy_VarAtts(X,p1)
    copy_VarAtts(X,p2)
  else
    p1 = conform_dims(dsizes(nondims),0D,-1)
    p2 = conform_dims(dsizes(nondims),0D,-1)
    copy_VarMeta_Fro(X,p1,nondims)
    copy_VarMeta_Fro(X,p2,nondims)
  end if
  fit_weibull(X,p1,p2,dim_args)

  return([/p1,p2/])
end

undef("dist_weibull_P")
function dist_weibull_P(X:numeric,P1:numeric,P2:numeric)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,P
begin
  maplist = get_mapdims([/X, P1, P2/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  P = ncl_c_weibull_P(X,P1,P2,mpdims)
  
  copy_Coords_Fro(dNames_all,dList_all,P,DimsFromNames2(dNames_all,dNames_all))
  copy_VarAtts_except(X,P,"_FillValue")
  return(P)
end

undef("dist_weibull_Pinv")
function dist_weibull_Pinv(P:numeric,P1:numeric,P2:numeric)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,X
begin
  maplist = get_mapdims([/P, P1, P2/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  X = ncl_c_weibull_Pinv(P,P1,P2,mpdims)
  
  copy_Coords_Fro(dNames_all,dList_all,X,DimsFromNames2(dNames_all,dNames_all))
  copy_VarAtts_except(P,X,"_FillValue")
  return(X)
end


undef("fit_gamma")
procedure fit_gamma(X:numeric,P1:numeric,P2:numeric,dim_args[*]:string)
local dNames_all,dims
begin
  dNames_all = getvardims(X)
  dims = DimsFromNames2(dNames_all,dim_args)
  ncl_c_gamma(X,P1,P2,dims)
end

undef("fit_gamma_Lst")
function fit_gamma_Lst(X:numeric,dim_args[*]:string)
local maplist,alldims,dNames,dsizes,dims,nondims,p1,p2
begin
  maplist   = get_mapdims_1(X)
  alldims   = maplist[0]
  dNames    = maplist[1]
  dsizes    = dimsizes(X)
  dims    = DimsFromNames2(dNames,dim_args)
  nondims = get1Dindex_Exclude (alldims,dims)
    
  if (all(ismissing(nondims))) then
    p1 = 0D
    p2 = 0D
    copy_VarAtts(X,p1)
    copy_VarAtts(X,p2)
  else
    p1 = conform_dims(dsizes(nondims),0D,-1)
    p2 = conform_dims(dsizes(nondims),0D,-1)
    copy_VarMeta_Fro(X,p1,nondims)
    copy_VarMeta_Fro(X,p2,nondims)
  end if
  copy_VarMeta_Fro(X,p1,nondims)
  copy_VarMeta_Fro(X,p2,nondims)

  fit_gamma(X,p1,p2,dim_args)

  return([/p1,p2/])
end

undef("dist_gamma_P")
function dist_gamma_P(X:numeric,P1:numeric,P2:numeric)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,P
begin
  maplist = get_mapdims([/X, P1, P2/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  P = ncl_c_gamma_P(X,P1,P2,mpdims)
  
  copy_Coords_Fro(dNames_all,dList_all,P,DimsFromNames2(dNames_all,dNames_all))
  copy_VarAtts_except(X,P,"_FillValue")
  return(P)
end

undef("dist_gamma_Pinv")
function dist_gamma_Pinv(P:numeric,P1:numeric,P2:numeric)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,X
begin
  maplist = get_mapdims([/P, P1, P2/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  X = ncl_c_gamma_Pinv(P,P1,P2,mpdims)
  
  copy_Coords_Fro(dNames_all,dList_all,X,DimsFromNames2(dNames_all,dNames_all))
  copy_VarAtts_except(P,X,"_FillValue")
  return(X)
end


undef("fit_mixed_gamma")
procedure fit_mixed_gamma(X:numeric,P1:numeric,P2:numeric,P3:numeric,dim_args[*]:string)
local dNames_all,dims
begin
  dNames_all = getvardims(X)
  dims = DimsFromNames2(dNames_all,dim_args)
  ncl_c_mixed_gamma(X,P1,P2,P3,dims)
end

undef("fit_mixed_gamma_Lst")
function fit_mixed_gamma_Lst(X:numeric,dim_args[*]:string)
local maplist,alldims,dNames,dsizes,dims,nondims,p1,p2,p3
begin
  maplist   = get_mapdims_1(X)
  alldims   = maplist[0]
  dNames    = maplist[1]
  dsizes    = dimsizes(X)
  dims    = DimsFromNames2(dNames,dim_args)
  nondims = get1Dindex_Exclude (alldims,dims)
    
  if (all(ismissing(nondims))) then
    p1 = 0D
    p2 = 0D
    p3 = 0D
    copy_VarAtts(X,p1)
    copy_VarAtts(X,p2)
    copy_VarAtts(X,p3)
  else
    p1 = conform_dims(dsizes(nondims),0D,-1)
    p2 = conform_dims(dsizes(nondims),0D,-1)
    p3 = conform_dims(dsizes(nondims),0D,-1)
    copy_VarMeta_Fro(X,p1,nondims)
    copy_VarMeta_Fro(X,p2,nondims)
    copy_VarMeta_Fro(X,p3,nondims)
  end if
  copy_VarMeta_Fro(X,p1,nondims)
  copy_VarMeta_Fro(X,p2,nondims)
  copy_VarMeta_Fro(X,p3,nondims)

  fit_mixed_gamma(X,p1,p2,p3,dim_args)

  return([/p1,p2,p3/])
end

undef("dist_mixed_gamma_P")
function dist_mixed_gamma_P(X:numeric,P1:numeric,P2:numeric,P3:numeric)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,P
begin
  maplist = get_mapdims([/X, P1, P2, P3/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  P = ncl_c_mixed_gamma_P(X,P1,P2,P3,mpdims)
  
  copy_Coords_Fro(dNames_all,dList_all,P,DimsFromNames2(dNames_all,dNames_all))
  copy_VarAtts_except(X,P,"_FillValue")
  return(P)
end

undef("dist_mixed_gamma_Pinv")
function dist_mixed_gamma_Pinv(P:numeric,P1:numeric,P2:numeric,P3:numeric)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,X
begin
  maplist = get_mapdims([/P, P1, P2, P3/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  X = ncl_c_mixed_gamma_Pinv(P,P1,P2,P3,mpdims)
  
  copy_Coords_Fro(dNames_all,dList_all,X,DimsFromNames2(dNames_all,dNames_all))
  copy_VarAtts_except(P,X,"_FillValue")
  return(X)
end


undef("fit_beta")
procedure fit_beta(X:numeric,P1:numeric,P2:numeric,dim_args[*]:string)
local dNames_all,dims
begin
  dNames_all = getvardims(X)
  dims = DimsFromNames2(dNames_all,dim_args)
  ncl_c_beta(X,P1,P2,dims)
end

undef("fit_beta_Lst")
function fit_beta_Lst(X:numeric,dim_args[*]:string)
local maplist,alldims,dNames,dsizes,dims,nondims,p1,p2
begin
  maplist   = get_mapdims_1(X)
  alldims   = maplist[0]
  dNames    = maplist[1]
  dsizes    = dimsizes(X)
  dims    = DimsFromNames2(dNames,dim_args)
  nondims = get1Dindex_Exclude (alldims,dims)
    
  if (all(ismissing(nondims))) then
    p1 = 0D
    p2 = 0D
    copy_VarAtts(X,p1)
    copy_VarAtts(X,p2)
  else
    p1 = conform_dims(dsizes(nondims),0D,-1)
    p2 = conform_dims(dsizes(nondims),0D,-1)
    copy_VarMeta_Fro(X,p1,nondims)
    copy_VarMeta_Fro(X,p2,nondims)
  end if
  copy_VarMeta_Fro(X,p1,nondims)
  copy_VarMeta_Fro(X,p2,nondims)

  fit_beta(X,p1,p2,dim_args)

  return([/p1,p2/])
end

undef("dist_beta_P")
function dist_beta_P(X:numeric,P1:numeric,P2:numeric)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,P
begin
  maplist = get_mapdims([/X, P1, P2/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  P = ncl_c_beta_P(X,P1,P2,mpdims)
  
  copy_Coords_Fro(dNames_all,dList_all,P,DimsFromNames2(dNames_all,dNames_all))
  copy_VarAtts_except(X,P,"_FillValue")
  return(P)
end

undef("dist_beta_Pinv")
function dist_beta_Pinv(P:numeric,P1:numeric,P2:numeric)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,X
begin
  maplist = get_mapdims([/P, P1, P2/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  X = ncl_c_beta_Pinv(P,P1,P2,mpdims)
  
  copy_Coords_Fro(dNames_all,dList_all,X,DimsFromNames2(dNames_all,dNames_all))
  copy_VarAtts_except(P,X,"_FillValue")
  return(X)
end


undef("fit_gauss")
procedure fit_gauss(X:numeric,P1:numeric,P2:numeric,dim_args[*]:string)
local dNames_all,dims
begin
  dNames_all = getvardims(X)
  dims = DimsFromNames2(dNames_all,dim_args)
  ncl_c_gauss(X,P1,P2,dims)
end

undef("fit_gauss_Lst")
function fit_gauss_Lst(X:numeric,dim_args[*]:string)
local maplist,alldims,dNames,dsizes,dims,nondims,p1,p2
begin
  maplist   = get_mapdims_1(X)
  alldims   = maplist[0]
  dNames    = maplist[1]
  dsizes    = dimsizes(X)
  dims    = DimsFromNames2(dNames,dim_args)
  nondims = get1Dindex_Exclude (alldims,dims)
  
  if (all(ismissing(nondims))) then
    p1 = 0D
    p2 = 0D
    copy_VarAtts(X,p1)
    copy_VarAtts(X,p2)
  else
    p1 = conform_dims(dsizes(nondims),0D,-1)
    p2 = conform_dims(dsizes(nondims),0D,-1)
    copy_VarMeta_Fro(X,p1,nondims)
    copy_VarMeta_Fro(X,p2,nondims)
  end if
  fit_gauss(X,p1,p2,dim_args)
  
  return([/p1,p2/])
end

undef("dist_gauss_P")
function dist_gauss_P(X:numeric,P1:numeric,P2:numeric)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Xanom,mpdims2,alldims,P
begin
  maplist = get_mapdims([/X, P2/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  dSizes_all = maplist[4]
  
  Xanom = conform_dims_wrap(dNames_all,dList_all,dSizes_all,X,True) - \
          conform_dims_wrap(dNames_all,dList_all,dSizes_all,P1,True)
  mpdims2 = mpdims
  alldims = DimsFromNames2(dNames_all,dNames_all)
  mpdims2(0,:) = alldims
  P     = ncl_c_gaussian_P(Xanom,P2,mpdims2)
  
  copy_Coords_Fro(dNames_all,dList_all,P,alldims)
  copy_VarAtts_except(X,P,"_FillValue")
  return(P)
end

undef("dist_gauss_Pinv")
function dist_gauss_Pinv(P:numeric,P1:numeric,P2:numeric)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,Xanom,X
begin
  maplist = get_mapdims([/P, P2/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  
  Xanom = ncl_c_gaussian_Pinv(P,P2,mpdims)

  copy_Coords_Fro(dNames_all,dList_all,Xanom,DimsFromNames2(dNames_all,dNames_all))
  copy_VarAtts_except(P,Xanom,"_FillValue")

  X     = Xanom + conform_wrap(Xanom,P1)
 
  copy_VarMeta(Xanom,X)
  return(X)
end



undef("fit_cdf")
function fit_cdf(X:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts, \
      alldims,ndims,dims, \
      rankd,indcopy,nstelems,X_sorted,X_P,idx,sortedDName,id,stdim_sizes
begin
  maplist    := get_mapdims([/X/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  ndims   = dimsizes(alldims)
  
  dims  = DimsFromNames2(dNames_all,dim_args)
  rankd = dimsizes(dims)

  if (rankd.gt.1) then
    indcopy = get1Dindex_Exclude (alldims,dims)
    nstelems = product( dSizes_all(dims));
    if (all(ismissing(indcopy))) then
      indcopy = -1
      stdim_sizes = nstelems
    else
      stdim_sizes = array_append_record(dSizes_all(indcopy),nstelems,0)
    end if
    X_sorted = new(stdim_sizes,"double",getVarFillValue(Atts))  
    copy_Coords_Fro(dNames_all,dList_all,X_sorted,indcopy)

    idx = ndims-rankd
    sortedDName = dNames_all(dims(0))
    do id=1,rankd-1
      sortedDName := sortedDName+"_"+dNames_all(dims(id))
    end do
    X_sorted!idx       = sortedDName
    X_sorted&$X_sorted!idx$ = todouble( fspan(0,tofloat(nstelems-1),nstelems) )
  else
    X_sorted = new_Meta(alldims,dSizes_all,dNames_all,dList_all,Atts,"double")
  end if
  X_P = X_sorted ; X_P has same dimensions as X_sorted
  
  ncl_c_fit_cdf(X,X_sorted,X_P,dims,mpdims)

  return([/X_sorted, X_P/])
end

undef("fit_cdf_Lst")
function fit_cdf_Lst(X:numeric,dim_args[*]:string)
begin
    return(fit_cdf(X, dim_args))
end

undef("dist_cdf_P")
function dist_cdf_P(X:numeric,X_sorted:numeric,dim_args)
local P
begin
  P = named_percatvalsrtd(X_sorted,X,dim_args)

  return(P)
end

undef("dist_cdf_Pinv")
function dist_cdf_Pinv(P:numeric,X_sorted:numeric,dim_args)
local X
begin
  X = named_valatpercsrtd(X_sorted,P,dim_args)

  return(X)
end






undef("fit_cdf0")
function fit_cdf0(X:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts, \
      alldims,ndims,dims,rankd,indcopy,p0, \
      nstelems,X_sorted,X_P,idx,sortedDName,id,stdim_sizes
begin
  maplist    := get_mapdims([/X/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  ndims   = dimsizes(alldims)
  
  dims  = DimsFromNames2(dNames_all,dim_args)
  rankd = dimsizes(dims)

  indcopy = get1Dindex_Exclude (alldims,dims)
  if (all(ismissing(indcopy))) then
    p0 = 0D
    copy_VarAtts(X,p0)
  else
    p0 = conform_dims(dSizes_all(indcopy),0D,-1)
    copy_VarMeta_Fro(X,p0,indcopy)
  end if

  if (rankd.gt.1) then
    nstelems = product( dSizes_all(dims));
    if (all(ismissing(indcopy))) then
      indcopy = -1
      stdim_sizes = nstelems
    else
      stdim_sizes = array_append_record(dSizes_all(indcopy),nstelems,0)
    end if
    X_sorted = new(stdim_sizes,"double",getVarFillValue(Atts))  
    copy_Coords_Fro(dNames_all,dList_all,X_sorted,indcopy)

    idx = ndims-rankd
    sortedDName = dNames_all(dims(0))
    do id=1,rankd-1
      sortedDName := sortedDName+"_"+dNames_all(dims(id))
    end do
    X_sorted!idx       = sortedDName
    X_sorted&$X_sorted!idx$ = todouble( fspan(0,tofloat(nstelems-1),nstelems) )
  else
    X_sorted = new_Meta(alldims,dSizes_all,dNames_all,dList_all,Atts,"double")
  end if
  X_P = X_sorted ; X_P has same dimensions as X_sorted
  
  ncl_c_fit_cdf0(X,X_sorted,X_P,p0,dims,mpdims)

  return([/X_sorted, X_P, p0/])
end

undef("fit_cdf0_Lst")
function fit_cdf0_Lst(X:numeric,dim_args[*]:string)
begin
    return(fit_cdf0(X, dim_args))
end

undef("dist_cdf0_P")
function dist_cdf0_P(X:numeric,X_sorted:numeric,p0:numeric,dim_args)
local maplist, dNames, dList, dSizes, P, X_, p0_
begin
    maplist = get_mapdims([/X,p0/],False)
    dNames  = maplist[1]
    dList   = maplist[2]
    dSizes  = maplist[4]
    
    X_  = conform_dims_wrap(dNames,dList,dSizes,X,False)
    p0_ = conform_dims_wrap(dNames,dList,dSizes,p0,False)
    
    P = reorder_as(X_,named_percatvalsrtd(X_sorted,X_,dim_args))
    P = (/ where(X_.gt.0.0 \
                ,(1.0-p0_)*P + p0_ \
                ,random_uniform(0.0D,1.0D,dimsizes(p0_))*p0_) /)

    return(P)
end

undef("dist_cdf0_Pinv")
function dist_cdf0_Pinv(P:numeric,X_sorted:numeric,p0:numeric,dim_args)
local maplist, dNames, dList, dSizes, X, P_, p0_
begin
    maplist    := get_mapdims([/P,p0/],False)
    dNames := maplist[1]
    dList  := maplist[2]
    dSizes := maplist[4]
    
    P_  = conform_dims_wrap(dNames,dList,dSizes,P,False)
    p0_ = conform_dims_wrap(dNames,dList,dSizes,p0,False)

    X = P_
    X = (/ (P_-p0_)/(1.0-p0_) /) ; X serves as pG
    X = (/ where(P_.gt.p0_ \
                ,reorder_as(X,named_valatpercsrtd(X_sorted,X,dim_args)) \
                ,0.0) /)
    X = (/ where(X.gt.0.0,X,0.0) /) ; There may be cases where X goes below zero with named_valatpercsrtd

    return(X)
end


undef("fit_dist_Lst")
function fit_dist_Lst(X:numeric,prms_type:string,dim_args[*]:string)
local maplist,alldims,dNames,dsizes,dims,nondims,p1,p2,p3
begin
    if (prms_type.eq."gauss") then
        Lst      := fit_gauss_Lst(X,dim_args)
    elseif (prms_type.eq."gamma") then
        Lst      := fit_gamma_Lst(X,dim_args)
    elseif (prms_type.eq."mixed_gamma") then
        Lst      := fit_mixed_gamma_Lst(X,dim_args)
    else
        print("prms_type "+prms_type+" not accepted")
        exit()
    end if
    return(Lst)
end

undef("dist_P")
function dist_P(X:numeric,Lst:list,prms_type:string)
local P
begin
    if (prms_type.eq."gauss") then
        P := dist_gauss_P(X, Lst[0],Lst[1])
    elseif (prms_type.eq."gamma") then
        P := dist_gamma_P(X, Lst[0],Lst[1])
    elseif (prms_type.eq."mixed_gamma") then
        P := dist_mixed_gamma_P(X, Lst[0],Lst[1],Lst[2])
    else
        print("prms_type "+prms_type+" not accepted")
        exit()
    end if
    return(P)
end

undef("dist_Pinv")
function dist_Pinv(P:numeric,Lst:list,prms_type:string)
local X
begin
    if (prms_type.eq."gauss") then
        X := dist_gauss_Pinv(P, Lst[0],Lst[1])
    elseif (prms_type.eq."gamma") then
        X := dist_gamma_Pinv(P, Lst[0],Lst[1])
    elseif (prms_type.eq."mixed_gamma") then
        X := dist_mixed_gamma_Pinv(P, Lst[0],Lst[1],Lst[2])
    else
        print("prms_type "+prms_type+" not accepted")
        exit()
    end if
    return(X)
end

undef("prm_Vars")
function prm_Vars(beg_str:string,prms_type:string)
local rstr,beg_str2
begin
    if (beg_str.eq."") then
      beg_str2 = beg_str
    else
      beg_str2 = beg_str+"_"
    end if
    if (prms_type.eq."gauss") then
        rstr := beg_str2+(/"mu","sigma"/)
    elseif (prms_type.eq."gamma") then
        rstr := beg_str2+(/"shape","scale"/)
    elseif (prms_type.eq."mixed_gamma") then
        rstr := beg_str2+(/"p1","p2","p3"/)
    else
        print("prms_type "+prms_type+" not accepted")
        exit()
    end if
    return(rstr)
end

undef("dist_nPrms")
function dist_nPrms(prms_type:string)
local n
begin
    if (prms_type.eq."gauss") then
        n = 2
    elseif (prms_type.eq."gamma") then
        n = 2
    elseif (prms_type.eq."mixed_gamma") then
        n = 3
    else
        print("prms_type "+prms_type+" not accepted")
        exit()
    end if
    return(n)
end


undef("dist_ugauss_pdf")
function dist_ugauss_pdf(X:numeric)
local P
begin
  P     = ncl_c_ugaussian_pdf(X)
  copy_VarMeta(X,P)
  return(P)
end

undef("dist_ugauss_P")
function dist_ugauss_P(X:numeric)
local P
begin
  P     = ncl_c_ugaussian_P(X)
  copy_VarMeta(X,P)
  return(P)
end

undef("dist_ugauss_Pinv")
function dist_ugauss_Pinv(P:numeric)
local X
begin
  X = ncl_c_ugaussian_Pinv(P)
  copy_VarMeta(P,X)
  return(X)
end


undef("named_qsort")
function named_qsort(X:numeric,dim_args[*]:string)
local maplist,dNames_all,dList_all,rank, \
      id,idx,alldims,dims,rankd,indcopy,sortedDName,nstelems,OUT
begin
  maplist = get_mapdims_1(X)
  alldims    = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank      = maplist[3]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_qsort(X,dims)
  
  if (rankd.le.1) then
    copy_Coords_Fro(dNames_all,dList_all,OUT,alldims)
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
    copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
    idx = rank-rankd
    sortedDName := dNames_all(dims(0))
    nstelems    = dimsizes(dList_all[dims(0)])
    do id=1,rankd-1
      sortedDName := sortedDName+"_"+dNames_all(dims(id))
      nstelems    = nstelems*dimsizes(dList_all[dims(id)])
    end do
    OUT!idx       = sortedDName
    OUT&$OUT!idx$ = todouble( fspan(0,nstelems-1,nstelems) )
  end if
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_qsort_idx")
function named_qsort_idx(X:numeric,dim_args[*]:string)
local maplist,dNames_all,dList_all,rank, \
      id,idx,alldims,dims,rankd,indcopy,sortedDName,nstelems,OUT
begin
  maplist = get_mapdims_1(X)
  alldims    = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank      = maplist[3]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_qsort_idx(X,dims)
  
  if (rankd.le.1) then
    copy_Coords_Fro(dNames_all,dList_all,OUT,alldims)
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
    copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
    idx = rank-rankd
    sortedDName := dNames_all(dims(0))
    nstelems    = dimsizes(dList_all[dims(0)])
    do id=1,rankd-1
      sortedDName := sortedDName+"_"+dNames_all(dims(id))
      nstelems    = nstelems*dimsizes(dList_all[dims(id)])
    end do
    OUT!idx       = sortedDName
    OUT&$OUT!idx$ = todouble( fspan(0,nstelems-1,nstelems) )
  end if
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_qsort_rev")
function named_qsort_rev(X:numeric,dim_args[*]:string)
local maplist,dNames_all,dList_all,rank, \
      id,idx,alldims,dims,rankd,indcopy,sortedDName,nstelems,OUT
begin
  maplist = get_mapdims_1(X)
  alldims    = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank      = maplist[3]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_qsort_rev(X,dims)
  
  if (rankd.le.1) then
    copy_Coords_Fro(dNames_all,dList_all,OUT,alldims)
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
    copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
    idx = rank-rankd
    sortedDName := dNames_all(dims(0))
    nstelems    = dimsizes(dList_all[dims(0)])
    do id=1,rankd-1
      sortedDName := sortedDName+"_"+dNames_all(dims(id))
      nstelems    = nstelems*dimsizes(dList_all[dims(id)])
    end do
    OUT!idx       = sortedDName
    OUT&$OUT!idx$ = todouble( fspan(0,nstelems-1,nstelems) )
  end if
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_qsort_idx_rev")
function named_qsort_idx_rev(X:numeric,dim_args[*]:string)
local maplist,dNames_all,dList_all,rank, \
      id,idx,alldims,dims,rankd,indcopy,sortedDName,nstelems,OUT
begin
  maplist = get_mapdims_1(X)
  alldims    = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank      = maplist[3]
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  OUT = ncl_c_qsort_idx_rev(X,dims)
  
  if (rankd.le.1) then
    copy_Coords_Fro(dNames_all,dList_all,OUT,alldims)
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
    copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
    idx = rank-rankd
    sortedDName := dNames_all(dims(0))
    nstelems    = dimsizes(dList_all[dims(0)])
    do id=1,rankd-1
      sortedDName := sortedDName+"_"+dNames_all(dims(id))
      nstelems    = nstelems*dimsizes(dList_all[dims(id)])
    end do
    OUT!idx       = sortedDName
    OUT&$OUT!idx$ = todouble( fspan(0,nstelems-1,nstelems) )
  end if
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end


undef("named_runmed")
function named_runmed(X:numeric,len:snumeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,rank_Vars, \
      rank,id,idx,alldims,dims, \
      rankd,indcopy,sortedDName,nstelems,OUT
begin
  maplist    = get_mapdims([/X,len/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  rank   = dimsizes(alldims)
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)

  OUT = ncl_c_runmed(X,len,dims,mpdims)

  if (get_rank0(OUT).eq.rank) then
    copy_Coords_Fro(dNames_all,dList_all,OUT,alldims)
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
    copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
    idx = rank-rankd
    sortedDName = dNames_all(dims(0))
    nstelems    = dimsizes(dList_all[dims(0)])
    do id=1,rankd-1
      sortedDName := sortedDName+"_"+dNames_all(dims(id))
      nstelems    = nstelems*dimsizes(dList_all[dims(id)])
    end do
    OUT!idx       = sortedDName
    OUT&$OUT!idx$ = todouble( fspan(0,nstelems-1,nstelems) )
  end if
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_runmean")
function named_runmean(X:numeric,len:snumeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,rank_Vars, \
      rank,id,idx,alldims,dims, \
      rankd,indcopy,sortedDName,nstelems,OUT
begin
  maplist    = get_mapdims([/X,len/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  rank   = dimsizes(alldims)
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)

  OUT = ncl_c_runmean(X,len,dims,mpdims)

  if (get_rank0(OUT).eq.rank) then
    copy_Coords_Fro(dNames_all,dList_all,OUT,alldims)
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
    copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
    idx = rank-rankd
    sortedDName = dNames_all(dims(0))
    nstelems    = dimsizes(dList_all[dims(0)])
    do id=1,rankd-1
      sortedDName := sortedDName+"_"+dNames_all(dims(id))
      nstelems    = nstelems*dimsizes(dList_all[dims(id)])
    end do
    OUT!idx       = sortedDName
    OUT&$OUT!idx$ = todouble( fspan(0,nstelems-1,nstelems) )
  end if
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_runmean_end")
function named_runmean_end(X:numeric,len:snumeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,rank_Vars, \
      rank,id,idx,alldims,dims, \
      rankd,indcopy,sortedDName,nstelems,OUT
begin
  maplist    = get_mapdims([/X,len/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  rank   = dimsizes(alldims)
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)

  OUT = ncl_c_runmean_end(X,len,dims,mpdims)

  if (get_rank0(OUT).eq.rank) then
    copy_Coords_Fro(dNames_all,dList_all,OUT,alldims)
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
    copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
    idx = rank-rankd
    sortedDName = dNames_all(dims(0))
    nstelems    = dimsizes(dList_all[dims(0)])
    do id=1,rankd-1
      sortedDName := sortedDName+"_"+dNames_all(dims(id))
      nstelems    = nstelems*dimsizes(dList_all[dims(id)])
    end do
    OUT!idx       = sortedDName
    OUT&$OUT!idx$ = todouble( fspan(0,nstelems-1,nstelems) )
  end if
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end




undef("named_runmedsmth")
function named_runmedsmth(X:numeric,len:snumeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,rank_Vars, \
      rank,id,idx,alldims,dims, \
      rankd,indcopy,sortedDName,nstelems,lensmth,Xmed,OUT
begin
  maplist    = get_mapdims([/X,len/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  rank   = dimsizes(alldims)
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)

  lensmth = ((len-1)/2)
  lensmth = where((lensmth%2).eq.0,lensmth+1,lensmth)

  Xmed = ncl_c_runmed(X,len,dims,mpdims)
  OUT  = ncl_c_runmean(Xmed,lensmth,dims,mpdims)

  if (get_rank0(OUT).eq.rank) then
    copy_Coords_Fro(dNames_all,dList_all,OUT,alldims)
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
    copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
    idx = rank-rankd
    sortedDName = dNames_all(dims(0))
    nstelems    = dimsizes(dList_all[dims(0)])
    do id=1,rankd-1
      sortedDName := sortedDName+"_"+dNames_all(dims(id))
      nstelems    = nstelems*dimsizes(dList_all[dims(id)])
    end do
    OUT!idx       = sortedDName
    OUT&$OUT!idx$ = todouble( fspan(0,nstelems-1,nstelems) )
  end if
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end


undef("named_runregr")
function named_runregr(X:numeric,len:snumeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,rank_Vars, \
      rank,id,idx,alldims,dims, \
      rankd,indcopy,sortedDName,nstelems,OUT
begin
  maplist    = get_mapdims([/X,len/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  rank   = dimsizes(alldims)
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)

  OUT = ncl_c_runregr(X,len,dims,mpdims)

  if (get_rank0(OUT).eq.rank) then
    copy_Coords_Fro(dNames_all,dList_all,OUT,alldims)
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
    copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
    idx = rank-rankd
    sortedDName = dNames_all(dims(0))
    nstelems    = dimsizes(dList_all[dims(0)])
    do id=1,rankd-1
      sortedDName := sortedDName+"_"+dNames_all(dims(id))
      nstelems    = nstelems*dimsizes(dList_all[dims(id)])
    end do
    OUT!idx       = sortedDName
    OUT&$OUT!idx$ = todouble( fspan(0,nstelems-1,nstelems) )
  end if
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_runslope_end")
function named_runslope_end(X:numeric,Y:numeric,len:snumeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,rank_Vars, \
      rank,id,idx,alldims,dims, \
      rankd,indcopy,sortedDName,nstelems,OUT
begin
  maplist    = get_mapdims([/X,Y,len/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  rank   = dimsizes(alldims)
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)

  OUT = ncl_c_runslope_end(X,Y,len,dims,mpdims)

  if (get_rank0(OUT).eq.rank) then
    copy_Coords_Fro(dNames_all,dList_all,OUT,alldims)
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
    copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
    idx = rank-rankd
    sortedDName = dNames_all(dims(0))
    nstelems    = dimsizes(dList_all[dims(0)])
    do id=1,rankd-1
      sortedDName := sortedDName+"_"+dNames_all(dims(id))
      nstelems    = nstelems*dimsizes(dList_all[dims(id)])
    end do
    OUT!idx       = sortedDName
    OUT&$OUT!idx$ = todouble( fspan(0,nstelems-1,nstelems) )
  end if
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end



undef("named_runwgtmean")
function named_runwgtmean(X:numeric,W:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,rank_Vars, \
      rank,id,idx,alldims,dims, \
      OUT,dNames_OUT,outdims
begin
  maplist    = get_mapdims([/X,W/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  rank   = dimsizes(alldims)
  
  dims   = DimsFromNames2(dNames_all,dim_args)

  OUT = ncl_c_runwgtmean(X,W,dims,mpdims)
  
  dNames_OUT = getvardims(X)
  outdims    = DimsFromNames2(dNames_all,dNames_OUT)
  copy_Coords_Fro(dNames_all,dList_all,OUT,outdims)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_runwgtperc_nm")
function named_runwgtperc_nm(X:numeric,W:numeric,perc:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,rank_Vars, \
      rank,id,idx,alldims,dims, \
      OUT,dNames_OUT,outdims
begin
  maplist    = get_mapdims([/X,W,perc/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  rank   = dimsizes(alldims)
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  
  OUT = ncl_c_runwgtperc_nm(X,W,perc,dims,mpdims)
  
  dNames_OUT = getvardims(X)
  outdims    = DimsFromNames2(dNames_all,dNames_OUT)
  copy_Coords_Fro(dNames_all,dList_all,OUT,outdims)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_runwgtperc")
function named_runwgtperc(X:numeric,Xbar:numeric,W:numeric,perc:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,rank_Vars, \
      rank,id,idx,alldims,dims, \
      OUT,dNames_OUT,outdims
begin
  maplist    = get_mapdims([/X,Xbar,W,perc/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  rank   = dimsizes(alldims)
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)
  
  OUT = ncl_c_runwgtperc(X,Xbar,W,perc,dims,mpdims)
  
  dNames_OUT = getvardims(X)
  outdims    = DimsFromNames2(dNames_all,dNames_OUT)
  copy_Coords_Fro(dNames_all,dList_all,OUT,outdims)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("named_runwgtpercs")
function named_runwgtpercs(X:numeric,Xbar:numeric,W:numeric,percs:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,rank_Vars, \
      rank,id,idx,alldims,dims, \
      rankd,OUT,dNames_OUT,dNames_percs,stdims_percs,outdims
begin
  maplist    = get_mapdims([/X,Xbar,W,percs/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars = maplist[3]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  rank   = dimsizes(alldims)
  
  dims   = DimsFromNames2(dNames_all,dim_args)
  rankd  = dimsizes(dims)

  OUT = ncl_c_runwgtpercs(X,Xbar,W,percs,dims,mpdims)
  
  dNames_OUT   = getvardims(X)
  dNames_percs = getvardims(percs)
  stdims_percs = DimsFromNames2_trimmed(dNames_percs,dim_args)
  outdims      = venn2_union(DimsFromNames2(dNames_all,dNames_OUT),DimsFromNames2(dNames_all,dNames_percs(stdims_percs)))  

  copy_Coords_Fro(dNames_all,dList_all,OUT,outdims)
  copy_VarAtts_except(X,OUT,"_FillValue")

  return(OUT)
end




undef("regress_out")
function regress_out(X:numeric,Xrm:numeric,dim_args[*]:string)
local Lst,m,b,rsq,mad,Xrm_Mod,OUT
begin
    Lst := theil_sen(Xrm,X,dim_args)
    m   := Lst[0]
    b   := Lst[1]
    rsq := Lst[2]
    mad := Lst[3]
    
    Xrm_Mod := named_mx_b(m,Xrm,b)

    OUT := X - reorder_as(X,Xrm_Mod)

    copy_VarMeta(X,OUT)
    return(OUT)
end

undef("regress_out_prms")
function regress_out_prms(X:numeric,Xrm:numeric,dim_args[*]:string)
local Lst,m,b,rsq,mad,Xrm_Mod,OUT
begin
    Lst := theil_sen(Xrm,X,dim_args)
    m   := Lst[0]
    b   := Lst[1]
    rsq := Lst[2]
    mad := Lst[3]
    
    Xrm_Mod := named_mx_b(m,Xrm,b)

    OUT := X - reorder_as(X,Xrm_Mod)

    copy_VarMeta(X,OUT)
    return([/OUT,m,b,rsq,mad/])
end

undef("regress_out_apply")
function regress_out_apply(X:numeric,Xrm:numeric,m:numeric,b:numeric)
local Xrm_Mod,OUT
begin
    Xrm_Mod := named_mx_b(m,Xrm,b)

    OUT := X - conform_wrap(X,Xrm_Mod)

    copy_VarMeta(X,OUT)
    return(OUT)
end




undef("named_gsl_multifit_linear_fit")
function named_gsl_multifit_linear_fit(X:numeric,Y:numeric,dim_args[*]:string)
local ndargs,pred2,maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts,alldims \
     ,dim_args_samples,dim_args_pred2,dim_args_out,dims,indcopy,OUT,Pcov,chisq,TSS,MSE,r2,stdims
begin
  ndargs   = dimsizes(dim_args)
  pred2       = X&$dim_args(ndargs-1)$
  pred2!0     = "pred2"
  pred2&pred2 = pred2

  maplist    := get_mapdims([/X, Y, pred2/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  alldims = DimsFromNames2(dNames_all,dNames_all)
  
  ; Need to set indcopy and create the extra dim for Pcov
  dim_args_samples = dim_args(0:(ndargs-2))
  dims    := DimsFromNames2(dNames_all,dim_args_samples)
  indcopy := get1Dindex_Exclude (alldims,dims)
  if (all(ismissing(indcopy))) then
    indcopy = -1
  end if
  Pcov = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,Type)

  dim_args_pred2 = array_append_record(dim_args,"pred2",0)
  dims    := DimsFromNames2(dNames_all,dim_args_pred2)
  indcopy := get1Dindex_Exclude (alldims,dims)
  if (all(ismissing(indcopy))) then
    indcopy = -1
  end if
  chisq = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,Type)
  TSS   = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,Type)
  MSE   = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,Type)
  r2    = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,Type)

  stdims    := DimsFromNames2(dNames_all,dim_args)
  OUT = ncl_gsl_multifit_linear_fit(X,Y,Pcov,chisq,TSS,MSE,r2,stdims,mpdims)
  
  dim_args_out = array_append_record(dim_args_samples,"pred2",0)
  dims  := DimsFromNames2(dNames_all,dim_args_out)
  if (dims(0).lt.0) then
    indcopy := alldims
  else
    indcopy := get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  
  return([/OUT,Pcov,chisq,TSS,MSE,r2/])
end

undef ("multilin_ens_fit")
function multilin_ens_fit(Y:numeric, Xens:numeric, regr_dim[*], ens_dim[*]) ; should be float or double
; Y    - dependent variable (size NY)
; Xens - independent variable ensemble, regression done on mean across ens_dim.
local X, Lst, P, Pcov, chisq, TSS, MSE, r2, sigma_e
begin
    X       = named_avg(Xens,ens_dim)
    sigma_e = named_avg(named_stddev(Xens,ens_dim),regr_dim)

    Lst  := named_gsl_multifit_linear_fit(X,Y,regr_dim)
    P     = Lst[0]
    Pcov  = Lst[1]
    chisq = Lst[2]
    TSS   = Lst[3]
    MSE   = Lst[4]
    r2    = Lst[5]

    return([/P,Pcov,chisq,TSS,MSE,r2,sigma_e/])
end

undef("named_gsl_multifit_linear_predict")
function named_gsl_multifit_linear_predict(X:numeric,P:numeric,Pcov:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts,alldims \
     ,dims,indcopy,yerr,OUT
begin
  maplist    := get_mapdims([/X, P, Pcov/],False)
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
  yerr = new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,Type)

  OUT = ncl_gsl_multifit_linear_predict(X,P,Pcov,yerr,dims,mpdims)
  
  if (dims(0).lt.0) then
    indcopy = alldims
  else
    indcopy = get1Dindex_Exclude (alldims,dims)
  end if
  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(X,OUT,"_FillValue")
  
  return([/OUT,yerr/])
end

undef ("multilin_ens_predict")
function multilin_ens_predict(X:numeric, P:numeric ,Pcov:numeric, \
                              MSE:numeric, sigma_e:numeric, \
                              ens_dim[*], pred_dim[*], opt:logical)
; Get adjusted ensemble forecast from OLS regression coefficients and prediction interval .
local X0, rank0, dsizes, Prand, xbar, Lst, Yest, ei, ei_, MSE_, zz \
    , xbar_, sigma_e_1, sigma_e_, xz, Yest_, zz_, yout
begin
    ; Includes option for generating ensembles from single value forecasts
    ; using a randomly spaced normal distribution
    ; The random spacing will change the mean value of the output forecast.

    ; Should set, but should only do once per program.
    ; rseed1 = toint(systemfunc(" date +%s"))
    ; rseed2 = toint((12345l*rseed1)%2147483398l)
    ; random_setallseed(rseed1, rseed2)

    ; NEED TO REMOVE pred_dim from X for final ensemble output.
    if (isdim(X,ens_dim)) then
        xbar = named_avg(X,ens_dim)
    else
        xbar = X
    end if

    X0 := sub_n_1(xbar,pred_dim(0),0)
    rank0 = get_rank0(X0)
    if (rank0.gt.1) then
        dsizes = array_append_record(dimsizes(X0),opt@nens,0)
        Prand  = random_uniform(0.0D,1.0D,dsizes)
        copy_VarMeta_To_except(X0,Prand,"_FillValue",ispan(0,rank0-1,1))
    else
        Prand  = random_uniform(0.0D,1.0D,opt@nens)
        copy_VarMeta_To_except(X0,Prand,"_FillValue",-1)
    end if
    Prand!rank0    = ens_dim
    Prand&ensemble = ispan(1,opt@nens,1)
    
    xz    = dist_gauss_Pinv(Prand,0.0D,1.0D)

    Lst  := named_gsl_multifit_linear_predict(xbar,P,Pcov,pred_dim)
    Yest := Lst[0]
    ei   := Lst[1]

    MSE_  = conform_wrap(Yest,MSE)
    ei_   = conform_wrap(Yest,ei)
    zz    = Yest
    zz    = (/ sqrt(MSE_ + ei_*ei_) /)

    Yest_ = conform_wrap(xz,Yest)
    zz_   = conform_wrap(xz,zz)
    yout  = xz
    yout  = (/ Yest_ + xz*zz_ /)

    return(yout)
end




undef ("reg_lin_stats_n")
function reg_lin_stats_n(Y:double, Xens:double, regr_dim[*], ens_dim[*]) ; should be float or double
; Y    - dependent variable (size NY)
; Xens - independent variable ensemble, regression done on mean across ens_dim.
;
; Very readable discussions:
; http://www.ltrr.arizona.edu/~dmeko/notes_11.pdf
; http://reliawiki.org/index.php/Multiple_Linear_Regression_Analysis
; http://homepages.rpi.edu/~tealj2/stat03.pdf
; ---
local N, NP, X, sigma_e, Lst, m, b \
    , Yavg, Xavg, Xavg_, dof, Yest \
    , Yres, SE, SSE, MSE, xx, Sxx, N_1
begin
    NP    = 1                     ; one predictor
    
    X       = named_avg(Xens,ens_dim)
    sigma_e = named_avg(named_stddev(Xens,ens_dim),regr_dim)

    Lst  := named_regr(X,Y,regr_dim)
    m     = Lst[0]
    b     = Lst[1]

    N     = nvalid_2(X,Y,regr_dim) ; Number of valid (non-missing) pairs

    ; Yavg  = named_avg(Y,regr_dim)
    Xavg  = named_avg(X,regr_dim)

    Yest = named_mx_b(m,X,b)       ; Model estimates: Yest = m*x + b

    dof  = N  ; For metadata  and coords assign first
    dof  = (/ N-(NP+1) /) 

    Y_   = conform_wrap(Yest,Y)
    Yres = Yest
    Yres = (/ Yest-Y_ /)          ; residuals

    SE   = Yres
    SE   = (/ Yres^2 /)
    SSE  = named_sum(SE,regr_dim) ; residual SS
 
    MSE  = SSE
    MSE  = (/ SSE/dof /)          ; Mean SSE    [dof=N-NP-1] 

    Xavg_ = conform_wrap(X,Xavg)
    xx   = X
    xx   = (/ (X-Xavg_)^2 /)
    Sxx  = named_sum(xx,regr_dim) ; = sum((x-rc@Xavg)^2)
                                  ; = sum(x^2)-((sum(x)^2)/N)

    N    = (/ where(N.gt.0, N, N@_FillValue) /)
    N_1  = N
    N_1 := to_Type(N_1,"double")
    N_1  = (/ 1.0+1.0/todouble(N) /) ; N_1 = 1 + 1/N

    return([/m,b,MSE,N,N_1,Xavg,Sxx,sigma_e/])
end

undef ("reg_lin_ens_n")
function reg_lin_ens_n(x:double, m:double ,b:double, \
                       MSE:double, N_1:double, Xavg:double, Sxx:double, sigma_e:double, \
                       ens_dim[*], opt:logical)
; Get adjusted ensemble forecast from OLS regression coefficients and prediction interval .
local xbar, Yest, MSE_, N_1_, Xavg_, Sxx_, zz \
    , xbar_, sigma_e_, xz, Yest_, zz_, yout
begin
    ; Includes option for generating ensembles from single value forecasts
    ; using a randomly spaced normal distribution
    ; The random spacing will change the mean value of the output forecast.
    if (isatt(opt,"nens")) then
        ; Should set, but should only do once per program.
        ; rseed1 = toint(systemfunc(" date +%s"))
        ; rseed2 = toint((12345l*rseed1)%2147483398l)
        ; random_setallseed(rseed1, rseed2)

        rank0 = get_rank0(x)
        if (rank0.gt.0) then
            dsizes = array_append_record(dimsizes(x),opt@nens,0)
            ; print(dsizes)
            Prand  = random_uniform(0.0D,1.0D,dsizes)
            ; printVarSummary(Prand)
            copy_VarMeta_To_except(x,Prand,"_FillValue",ispan(0,rank0-1,1))
        else
            Prand  = random_uniform(0.0D,1.0D,opt@nens)
            copy_VarMeta_To_except(x,Prand,"_FillValue",-1)
        end if
        Prand!rank0     = ens_dim
        Prand&$ens_dim$ = ispan(1,opt@nens,1)
        
        xz    = dist_gauss_Pinv(Prand,0.0D,1.0D)

        xbar  = x
    else
        xbar  = named_avg(x,ens_dim)
        if (isatt(opt,"calc_sigma").and.opt@calc_sigma) then
            sigma_e_1 = named_stddev(x,ens_dim) ; Manzanas calculates sigma for each forecast!
        else
            sigma_e_1 = sigma_e                 ; Would seem more stable to use average of training sigmas.
        end if
    end if

    Yest  = named_mx_b(m,xbar,b)

    MSE_  = conform_wrap(xbar,MSE)
    N_1_  = conform_wrap(xbar,N_1)
    Xavg_ = conform_wrap(xbar,Xavg)
    Sxx   = (/ where(Sxx.eq.0,Sxx@_FillValue,Sxx) /)
    Sxx_  = conform_wrap(xbar,Sxx)
    zz    = xbar
    zz    = (/ sqrt(MSE_*(N_1_ + ((xbar-Xavg_)^2)/Sxx_)) /)

    if (.not.isatt(opt,"nens")) then
        xbar_    = conform_wrap(x,xbar)
        sigma_e_1 = (/ where(sigma_e_1.eq.0,sigma_e_1@_FillValue,sigma_e_1) /)
        sigma_e_ = conform_wrap(x,sigma_e_1)
        
        xz       = x
        xz       = (/ (x - xbar_)/sigma_e_ /)
    end if

    Yest_ = conform_wrap(xz,Yest)
    zz_   = conform_wrap(xz,zz)
    yout  = xz
    yout  = (/ Yest_ + xz*zz_ /)

    return(yout)
end



undef ("QM_fit_n")
function QM_fit_n(Y:double, Xens:double, prm_type_y:string, prm_type_x:string, regr_dim[*], ens_dim[*]) ; should be float or double
; Y    - dependent variable (size NY)
; Xens - independent variable ensemble.
local pooled_dims, Y_pLst, X_pLst
begin
    pooled_dims = array_append_record(regr_dim,ens_dim,0)
    Y_pLst := fit_dist_Lst(Y   ,prm_type_y,  regr_dim          )
    X_pLst := fit_dist_Lst(Xens,prm_type_x,pooled_dims)

    return([/Y_pLst,X_pLst/])
end

undef ("QM_predict_n")
function QM_predict_n(x:double, Y_pLst:list, X_pLst:list, prm_type_y:string, prm_type_x:string, retopt:integer)
; Get adjusted ensemble forecast from OLS regression coefficients and prediction interval .
local X_tmp_p, X_tmp_z, X_tmp
begin
    ; retopt: 0 - standardized anomalies, 1 - absolute values or 2 - both
    X_tmp_p  = dist_P(x,X_pLst,prm_type_x)
    if retopt.eq.0 then
        X_tmp_z  = dist_ugauss_Pinv(X_tmp_p)
        return(X_tmp_z)
    elseif retopt.eq.1 then
        X_tmp = dist_Pinv(X_tmp_p,Y_pLst,prm_type_y)
        return(X_tmp)
    elseif retopt.eq.2 then
        X_tmp_z = dist_ugauss_Pinv(X_tmp_p)
        X_tmp   = dist_Pinv(X_tmp_p,Y_pLst,prm_type_y)
        return([/X_tmp_z,X_tmp/])
    end if
end



; Should create a mixed_EQM, conditioned on 0
undef ("EQM_fit_n")
function EQM_fit_n(Y:double, Xens:double, regr_dim[*], ens_dim[*], ismixed:logical) ; should be float or double
; Y    - dependent variable (size NY)
; Xens - independent variable ensemble.
; ismixed - True when distribution is bounded by zero
local pooled_dims, Y_pLst, X_pLst
begin
    pooled_dims = array_append_record(regr_dim,ens_dim,0)
    if (ismixed) then
        Y_pLst = fit_cdf0(Y,     regr_dim          )
        X_pLst = fit_cdf0(Xens,pooled_dims) ; fit_cdf joins regr_dim+"_"+ens_dim
    else
        Y_pLst = fit_cdf(Y,     regr_dim          )
        X_pLst = fit_cdf(Xens,pooled_dims)
    end if

    return([/Y_pLst,X_pLst/])
end

undef ("EQM_predict_n")
function EQM_predict_n(x:double, Y_pLst:list, X_pLst:list, regr_dim[*], ens_dim[*], ismixed:logical, retopt:integer)
; ismixed - True when distribution is bounded by zero
local pooled_dims, X_tmp_p, X_tmp_z, X_tmp
begin
    ; retopt: 0 - standardized anomalies, 1 - absolute values or 2 - both
    pooled_dims = array_append_record(regr_dim,ens_dim,0)
    if (ismixed) then
        X_tmp_p  = dist_cdf0_P(x  ,X_pLst[0],X_pLst[2],str_join(pooled_dims,"_"))
    else
        X_tmp_p  = dist_cdf_P (x  ,X_pLst[0],str_join(pooled_dims,"_"))
    end if
    if retopt.eq.0 then
        X_tmp_z  = dist_ugauss_Pinv(X_tmp_p)
        return(X_tmp_z)
    elseif retopt.eq.1 then
        if (ismixed) then
            X_tmp = dist_cdf0_Pinv(X_tmp_p,Y_pLst[0],Y_pLst[2],regr_dim)
        else
            X_tmp = dist_cdf_Pinv (X_tmp_p,Y_pLst[0],regr_dim)
        end if
        return(X_tmp)
    elseif retopt.eq.2 then
        X_tmp_z = dist_ugauss_Pinv(X_tmp_p)
        if (ismixed) then
            X_tmp = dist_cdf0_Pinv(X_tmp_p,Y_pLst[0],Y_pLst[2],regr_dim)
        else
            X_tmp = dist_cdf_Pinv (X_tmp_p,Y_pLst[0],regr_dim)
        end if
        return([/X_tmp_z,X_tmp/])
    end if
end



undef ("QM_sprd_fit_n")
function QM_sprd_fit_n(Y:double, Xens:double, prm_type_y:string, prm_type_x:string, regr_dim[*], ens_dim[*]) ; should be float or double
; Y    - dependent variable (size NY)
; Xens - independent variable ensemble.
local pooled_dims, Y_pLst, X_pLst, Y_z, Xens_z, X_z, X_rmsd, X_spread, X_sprderr
begin
    pooled_dims = array_append_record(regr_dim,ens_dim,0)
    Y_pLst = fit_dist_Lst(Y   ,prm_type_y,regr_dim   )
    X_pLst = fit_dist_Lst(Xens,prm_type_x,pooled_dims)

    Y_z    = dist_ugauss_Pinv(dist_P(Y   ,Y_pLst,prm_type_y))
    Xens_z = dist_ugauss_Pinv(dist_P(Xens,X_pLst,prm_type_x))

    X_z       = named_avg(Xens_z,ens_dim)
    X_rmsd    = named_rmsd(X_z,Y_z,regr_dim)
    X_spread  = named_avg(named_stddev(Xens_z,ens_dim),regr_dim)
    X_spread  = (/ where(X_spread.le.0.0,X_spread@_FillValue,X_spread) /)
    X_sprderr = X_rmsd/X_spread
    copy_VarMeta_except(X_spread,X_sprderr,"_FillValue")

    return([/Y_pLst,X_pLst,X_sprderr/])
end

undef ("QM_sprd_predict_n")
function QM_sprd_predict_n(x:double, Y_pLst:list, X_pLst:list, X_sprderr:double, prm_type_y:string, prm_type_x:string, ens_dim[*], retopt:integer)
; Get adjusted ensemble forecast from OLS regression coefficients and prediction interval .
local Xens_z, X_z, X_z_, X_sprderr_, X_sprderr_z, X_tmp_p, X_tmp_z, X_tmp
begin
    Xens_z = dist_ugauss_Pinv(dist_P(x,X_pLst,prm_type_x))

; subtract ensemble mean from ensemble 
    ; multiply this from mean by sprderr
    ; add ensemble mean back
    X_z         = named_avg(Xens_z,ens_dim) ; calc ensemble mean
    X_z_        = conform_wrap(Xens_z,X_z)
    X_sprderr_  = conform_wrap(Xens_z,X_sprderr)
    X_sprderr_z = (Xens_z - X_z_)*X_sprderr_ + X_z_
    copy_VarMeta_except(Xens_z,X_sprderr_z,"_FillValue")

    ; retopt: 0 - standardized anomalies, 1 - absolute values or 2 - both
    X_tmp_p  = dist_ugauss_P(X_sprderr_z)
    if retopt.eq.0 then
        X_tmp_z  = dist_ugauss_Pinv(X_tmp_p)
        return(X_tmp_z)
    elseif retopt.eq.1 then
        X_tmp = dist_Pinv(X_tmp_p,Y_pLst,prm_type_y)
        return(X_tmp)
    elseif retopt.eq.2 then
        X_tmp_z = dist_ugauss_Pinv(X_tmp_p)
        X_tmp   = dist_Pinv(X_tmp_p,Y_pLst,prm_type_y)
        return([/X_tmp_z,X_tmp/])
    end if
end



undef ("QM_sprd2_fit_n")
function QM_sprd2_fit_n(Y:double, Xens:double, prm_type_y:string, prm_type_x:string, regr_dim[*], ens_dim[*]) ; should be float or double
; Y    - dependent variable (size NY)
; Xens - independent variable ensemble.
local pooled_dims, Y_pLst, X_pLst, Y_z, Xens_z, X_z, X_rmsd, X_spread, X_sprderr, X_z_, X_sprderr_, X_sprderr_z, se_pLst
begin
    pooled_dims = array_append_record(regr_dim,ens_dim,0)
    Y_pLst = fit_dist_Lst(Y   ,prm_type_y,  regr_dim          )
    X_pLst = fit_dist_Lst(Xens,prm_type_x,pooled_dims)

    Y_z    = dist_ugauss_Pinv(dist_P(Y   ,Y_pLst,prm_type_y))
    Xens_z = dist_ugauss_Pinv(dist_P(Xens,X_pLst,prm_type_x))

    X_z       = named_avg(Xens_z,ens_dim)
    X_rmsd    = named_rmsd(X_z,Y_z,regr_dim)
    X_spread  = named_avg(named_stddev(Xens_z,ens_dim),regr_dim)
    X_spread  = (/ where(X_spread.le.0.0,X_spread@_FillValue,X_spread) /)
    X_sprderr = X_rmsd/X_spread
    copy_VarMeta_except(X_spread,X_sprderr,"_FillValue")

    ; subtract ensemble mean from ensemble 
    ; multiply this from mean by sprderr
    ; add ensemble mean back
    X_z_        = conform_wrap(Xens_z,X_z)
    X_sprderr_  = conform_wrap(Xens_z,X_sprderr)
    X_sprderr_z = (Xens_z - X_z_)*X_sprderr_ + X_z_
    copy_VarMeta_except(Xens_z,X_sprderr_z,"_FillValue")

    ; readjust distribution
    se_pLst = fit_dist_Lst(X_sprderr_z,"gauss",pooled_dims)
    return([/Y_pLst,X_pLst,X_sprderr,se_pLst/])
end

undef ("QM_sprd2_predict_n")
function QM_sprd2_predict_n(x:double, Y_pLst:list, X_pLst:list, X_sprderr:double, se_pLst:list, prm_type_y:string, prm_type_x:string, ens_dim[*], retopt:integer)
; Get adjusted ensemble forecast from OLS regression coefficients and prediction interval .
local Xens_z, X_z, X_z_, X_sprderr_, X_sprderr_z, X_tmp_z, X_tmp_p, X_tmp
begin
    Xens_z = dist_ugauss_Pinv(dist_P(x,X_pLst,prm_type_x))

    ; subtract ensemble mean from ensemble 
    ; multiply this from mean by sprderr
    ; add ensemble mean back
    X_z         = named_avg(Xens_z,ens_dim) ; calc ensemble mean
    X_z_        = conform_wrap(Xens_z,X_z)
    X_sprderr_  = conform_wrap(Xens_z,X_sprderr)
    X_sprderr_z = (Xens_z - X_z_)*X_sprderr_ + X_z_
    copy_VarMeta_except(Xens_z,X_sprderr_z,"_FillValue")

    ; retopt: 0 - standardized anomalies, 1 - absolute values or 2 - both
    X_tmp_p  = dist_P(X_sprderr_z,se_pLst,"gauss")
    if retopt.eq.0 then
        X_tmp_z  = dist_ugauss_Pinv(X_tmp_p)
        return(X_tmp_z)
    elseif retopt.eq.1 then
        X_tmp = dist_Pinv(X_tmp_p,Y_pLst,prm_type_y)
        return(X_tmp)
    elseif retopt.eq.2 then
        X_tmp_z = dist_ugauss_Pinv(X_tmp_p)
        X_tmp   = dist_Pinv(X_tmp_p,Y_pLst,prm_type_y)
        return([/X_tmp_z,X_tmp/])
    end if
end


undef("train_MVA")
function train_MVA(y_m_t:double,o_t:double,regr_dim,ens_dim)
local pooled_dims, y_m_t_, y_hat, o_hat, sigma_e, sigma_o
begin
    pooled_dims = array_append_record(regr_dim,ens_dim,0)
    y_m_t_  = dims2end(y_m_t,pooled_dims) ; named_avg and named_stddev fail if dims are not ordered

    o_hat   = named_avg(   o_t   ,  regr_dim          )
    y_hat   = named_avg(   y_m_t_,pooled_dims)
    sigma_e = named_stddev(y_m_t_,pooled_dims)
    sigma_o = named_stddev(o_t   ,  regr_dim          )


    return([/o_hat,y_hat,sigma_e,sigma_o/])
end

undef("test_MVA")
function test_MVA(y_m_t:double,o_hat:double,y_hat:double,sigma_e:double,sigma_o:double)
local sigma_e_na,o_hat_,y_hat_,sigma_o_,sigma_e_,yout_m_t
begin

    sigma_e_na = sigma_e
    sigma_e_na = (/ where(sigma_e.gt.0.0,sigma_e,sigma_e@_FillValue) /)

    o_hat_   = conform_wrap(y_m_t,o_hat)
    y_hat_   = conform_wrap(y_m_t,y_hat)
    sigma_o_ = conform_wrap(y_m_t,sigma_o)
    sigma_e_ = conform_wrap(y_m_t,sigma_e_na)
    yout_m_t = y_m_t
    yout_m_t = (/ ((y_m_t - y_hat_)*(sigma_o_/sigma_e_)) + o_hat_ /)

    return(yout_m_t)
end


undef("train_CCR")
function train_CCR(y_m_t:double,o_t:double,regr_dim[*],ens_dim[*])
local pooled_dims, o_hat, y_m_t_, y_hat, o_hat_, oa_t, y_hat_, ya_m_t, yabar_t \
    , sigmaa_em, sigmaa_o, yabar_t_, yadev, sigma_es \
    , rho, rho_, sigmaa_o_, a, b
begin
    pooled_dims = array_append_record(regr_dim,ens_dim,0)
    o_hat  = named_avg(o_t   ,  regr_dim          )

    y_m_t_ = dims2end(y_m_t  ,pooled_dims) ; named_avg and named_stddev fail if dims are not ordered
    y_hat  = named_avg(y_m_t_,pooled_dims)

    o_hat_ = conform_wrap(o_t  ,o_hat)
    oa_t   = o_t
    oa_t   = (/ o_t    - o_hat_ /)

    y_hat_ = conform_wrap(y_m_t_,y_hat)
    ya_m_t = y_m_t_
    ya_m_t = (/ y_m_t_ - y_hat_ /)
    
    yabar_t   = named_avg   (ya_m_t ,ens_dim )

    sigmaa_em = named_stddev(yabar_t,regr_dim)
    sigmaa_em = (/ where(sigmaa_em.gt.0.0,sigmaa_em,sigmaa_em@_FillValue) /)

    sigmaa_o  = named_stddev(oa_t   ,regr_dim)

    yabar_t_  = conform_wrap(ya_m_t,yabar_t)
    yadev     = ya_m_t
    yadev     = (/ ya_m_t - yabar_t_ /)
    sigma_es  = named_stddev(yadev, pooled_dims)
    sigma_es  = (/ where(sigma_es.gt.0.0,sigma_es,sigma_es@_FillValue) /)
    
    rho = named_corr(oa_t, yabar_t, regr_dim)
    rho = (/ abs(rho) /)

    rho_      = reorder_as(sigmaa_em,rho)
    sigmaa_o_ = conform_wrap(rho_,sigmaa_o)
    a         = rho_
    a         = (/ rho_*(sigmaa_o_/sigmaa_em) /)

    b         = rho_
    b         = (/ sqrt(1.0-(rho_^2))*(sigmaa_o_/sigma_es) /)

    return([/o_hat,y_hat,a,b/])
end

undef("test_CCR")
function test_CCR(y_m_t:double,o_hat:double,y_hat:double,a:double,b:double,ens_dim[*])
local y_hat_, ya_m_t, yabar_t, yabar_t_, zeta, a_, b_, o_hat_, yout_m_t
begin
    y_hat_   = conform_wrap(y_m_t,y_hat)
    ya_m_t   = y_m_t
    ya_m_t   = (/ y_m_t - y_hat_ /)

    yabar_t  = named_avg(ya_m_t,ens_dim)

    yabar_t_ = conform_wrap(ya_m_t,yabar_t)
    zeta     = ya_m_t
    zeta     = (/ ya_m_t - yabar_t_ /)

    a_       = conform_wrap(yabar_t_,a)
    b_       = conform_wrap(yabar_t_,b)
    o_hat_   = conform_wrap(yabar_t_,o_hat)
    yout_m_t = yabar_t_
    yout_m_t = (/ a_*yabar_t_ + b_*zeta + o_hat_ /)

    return(yout_m_t)
end


undef("train_RPC")
function train_RPC(y_m_t:double,o_t:double,regr_dim,ens_dim)
local pooled_dims, o_hat, y_hat, oa_t, ya_m_t, yabar_t, ya_hat, sigmaa_em, sigmaa_o, rho
begin
    pooled_dims = array_append_record(regr_dim,ens_dim,0)
    o_hat  = named_avg(o_t   ,  regr_dim          )

    y_m_t_ = dims2end(y_m_t  ,pooled_dims) ; named_avg and named_stddev fail if dims are not ordered
    y_hat  = named_avg(y_m_t_,pooled_dims)

    o_hat_ = conform_wrap(o_t  ,o_hat)
    oa_t   = o_t
    oa_t   = (/ o_t   - o_hat_ /)

    y_hat_ = conform_wrap(y_m_t_,y_hat)
    ya_m_t = y_m_t_
    ya_m_t = (/ y_m_t_ - y_hat_ /)

    yabar_t   = named_avg(   ya_m_t ,ens_dim )
    ya_hat    = named_avg(   yabar_t,regr_dim)
    sigmaa_em = named_stddev(yabar_t,regr_dim)
    sigmaa_o  = named_stddev(oa_t   ,regr_dim)

    rho = named_corr(oa_t, yabar_t, regr_dim)
    rho = (/ abs(rho) /)
    
    sqrt1_rho2 = rho
    sqrt1_rho2 = (/ sqrt(1-(rho^2)) /) ; For efficiency calculate as extra parameter

    return([/o_hat,y_hat,ya_hat,sigmaa_em,sigmaa_o,rho,sqrt1_rho2/])
end

undef("test_RPC")
function test_RPC(y_m_t:double,o_hat:double,y_hat:double,ya_hat:double,sigmaa_em:double,sigmaa_o:double,rho:double,sqrt1_rho2:double,ens_dim)
local y_hat_, ya_m_t, yabar_t, sigmaa_em_na, ya_hat_, sigmaa_o_, rho_, sigmaa_em_, adj_em \
    , yabar_t_, yadev, sigma_noi, sqrt1_rho2_, sigma_noi_, adj_em_, o_hat_, yout_m_t
begin
    y_hat_    = conform_wrap(y_m_t,y_hat)
    ya_m_t    = y_m_t
    ya_m_t    = (/ y_m_t - y_hat_ /)

    yabar_t   = named_avg(ya_m_t,ens_dim)
    
    sigmaa_em_na = sigmaa_em
    sigmaa_em_na = (/ where(sigmaa_em.gt.0.0,sigmaa_em,sigmaa_em@_FillValue) /)

    ya_hat_    = conform_wrap(yabar_t,ya_hat)
    sigmaa_o_  = conform_wrap(yabar_t,sigmaa_o)
    rho_       = conform_wrap(yabar_t,reorder_as(sigmaa_em_na,rho))
    sigmaa_em_ = conform_wrap(yabar_t,sigmaa_em_na)
    adj_em     = yabar_t
    adj_em     = (/ (yabar_t - ya_hat_)*(sigmaa_o_*rho_/sigmaa_em_) + ya_hat_ /)
    
    yabar_t_  = conform_wrap(ya_m_t,yabar_t)
    yadev     = ya_m_t
    yadev     = (/ ya_m_t - yabar_t_ /)
    sigma_noi = named_variance(yadev, ens_dim)
    sigma_noi = (/ sqrt(sigma_noi) /)
    sigma_noi = (/ where(sigma_noi.eq.0.0,sigma_noi@_FillValue,sigma_noi) /)
    
    sigmaa_o_  := conform_wrap(ya_m_t,sigmaa_o)
    sqrt1_rho2_ = conform_wrap(ya_m_t,reorder_as(sigmaa_em_na,sqrt1_rho2))
    sigma_noi_  = conform_wrap(ya_m_t,sigma_noi)
    adj_em_     = conform_wrap(ya_m_t,adj_em)
    o_hat_      = conform_wrap(ya_m_t,o_hat)
    yout_m_t    = ya_m_t
    yout_m_t    = ((ya_m_t - yabar_t_)*((sigmaa_o_*sqrt1_rho2_) / sigma_noi_)) \
                   + adj_em_ + o_hat_

    return(yout_m_t)
end



undef("hi2lo_idxwgt_ar")
function hi2lo_idxwgt_ar(lat_hi[*]:numeric,lon_hi[*]:numeric,lat_lo[*]:numeric,lon_lo[*]:numeric)
local dy_hi,dx_hi,dy_lo,dx_lo,nposhi2lo,idxvar,maplist,dNames_all,dList_all,dSizes_all,Atts \
     ,N,jIdxs,iIdxs,Wgts,WgtSum
begin
  dy_hi     := min_difference(lat_hi)
  dx_hi     := min_difference(lon_hi)
  dy_lo     := max_difference(lat_lo)
  dx_lo     := max_difference(lon_lo)

  nposhi2lo := toint64((dy_lo/dy_hi+2)*(dx_lo/dx_hi+2))
  idxvar      := ispan(0,nposhi2lo-1,1)
  idxvar!0     = "hipts"
  idxvar&hipts = idxvar
  
  maplist    := get_mapdims([/lat_hi, lon_hi, lat_lo, lon_lo, idxvar/],False)
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Atts       := todouble(maplist[6])
  
  Atts_idx = toint64(0)
  copy_VarAtts(Atts,Atts_idx)
  
  Atts@_FillValue     = totype(-999.0,"double")
  Atts_idx@_FillValue = toint64(-999)
  
  N      = new_Meta((/2,3/),  dSizes_all,dNames_all,dList_all,Atts_idx,"int64")
  jIdxs  = new_Meta((/2,3,4/),dSizes_all,dNames_all,dList_all,Atts_idx,"int64")
  iIdxs  = new_Meta((/2,3,4/),dSizes_all,dNames_all,dList_all,Atts_idx,"int64")
  Wgts   = new_Meta((/2,3,4/),dSizes_all,dNames_all,dList_all,Atts,"double")
  WgtSum = new_Meta((/2,3/),  dSizes_all,dNames_all,dList_all,Atts,"double")

  ncl_c_hi2lo_idxwgt_ar(lat_hi,lon_hi,lat_lo,lon_lo, \
                     N,jIdxs,iIdxs,Wgts,WgtSum,(/0,1,2,3/),(/0,1,2,3/))

  return([/ N,jIdxs,iIdxs,Wgts,WgtSum /])
end

undef("hi2lo_mean")
function hi2lo_mean(data_hi:numeric,N:snumeric,jIdxs:snumeric,iIdxs:snumeric,Wgts:numeric,WgtSum:numeric \
                       ,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all \
     ,alldims,dims,OUT,dNames_Wgts,Wgtsdims,indcopy
begin
  ; will require matching both dim name and length
  maplist    := get_mapdims([/data_hi,N,jIdxs,iIdxs,Wgts,WgtSum/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]

  alldims  := DimsFromNames2(dNames_all,dNames_all)
  dims   := DimsFromNames2(dNames_all,dim_args)

  OUT := ncl_c_hi2lo_mean(data_hi,N,jIdxs,iIdxs,Wgts,WgtSum \
                             ,dims,mpdims)

  Wgtsdims := DimsFromNames2(dNames_all,dim_args((/0,1,4/)))
  indcopy := get1Dindex_Exclude (alldims,Wgtsdims)

  copy_Coords_Fro(dNames_all,dList_all,OUT,indcopy)
  copy_VarAtts_except(data_hi,OUT,"_FillValue")
  return(OUT)
end

undef("hi2lo_stats")
function hi2lo_stats(IN:numeric,N:snumeric,jIdxs:snumeric,iIdxs:snumeric,Wgts:numeric,AbvThresh:numeric,dim_args[*]:string)
local maplist,mpdims,dNames_all,dList_all,dSizes_all,Type,Atts,alldims,dims,indcopy,nondims \
     ,dims_hi,dNames_hi,dsizes_hi,stdims_hi,nondims_hi \
     ,dims_lo,dNames_lo,dsizes_lo,stdims_lo,nondims_lo \
     ,dNames_out,long_name,units \
     ,UpMn,UpMin,UpMax,UpMed,UpFrac,UpSigma,UpMnAbv
begin
  maplist    := get_mapdims([/IN,N,jIdxs,iIdxs,Wgts,AbvThresh/],False)
  mpdims     := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  alldims    := DimsFromNames2(dNames_all,dNames_all)
  dims     := DimsFromNames2(dNames_all,dim_args)
  nondims  := get1Dindex_Exclude (alldims,dims)

  maplist      := get_mapdims_1(IN)
  dims_hi      := maplist[0]
  dNames_hi    := maplist[1]
  dsizes_hi    := dimsizes(IN)
  stdims_hi    := DimsFromNames2_trimmed(dNames_hi,dim_args)
  nondims_hi := get1Dindex_Exclude (dims_hi,stdims_hi)

  maplist      := get_mapdims_1(N)
  dims_lo      := maplist[0]
  dNames_lo    := maplist[1]
  dsizes_lo    := dimsizes(N)
  stdims_lo    := DimsFromNames2_trimmed(dNames_lo,dim_args)
  nondims_lo := get1Dindex_Exclude (dims_lo,stdims_lo)

  if (all(ismissing(nondims_hi))) then
    dNames_out := dNames_lo(stdims_lo)
  else
    dNames_out := array_append_record(dNames_hi(nondims_hi),dNames_lo(stdims_lo),0)
  end if

  indcopy    := DimsFromNames2(dNames_all,dNames_out)
  if (all(ismissing(indcopy))) then
    indcopy = -1
  end if
  UpMn    := new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  UpMin   := new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  UpMax   := new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  UpMed   := new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  UpFrac  := new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  UpSigma := new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")
  UpMnAbv := new_Meta(indcopy,dSizes_all,dNames_all,dList_all,Atts,"double")

  if (isatt(IN,"long_name")) then
    long_name = IN@long_name
  else
    long_name = ""
  end if
  if (isatt(IN,"units")) then
    units = IN@units
  else
    units = ""
  end if
  UpMn@units    = units
  UpMin@units   = units
  UpMax@units   = units
  UpMed@units   = units
  UpFrac@units  = ""
  UpSigma@units = units
  UpMnAbv@units = units
  UpMn@long_name    = "Mean "+long_name
  UpMin@long_name   = "Minimum "+long_name
  UpMax@long_name   = "Maximum "+long_name
  UpMed@long_name   = "Median "+long_name
  UpFrac@long_name  = "Frac area with "+long_name+" over "+sprintf("%1.0f",AbvThresh)+" "+units
  UpSigma@long_name = "Std. Dev. of "+long_name
  UpMnAbv@long_name = "Mean "+long_name+" where over "+sprintf("%1.0f",AbvThresh)+" "+units

  ncl_c_hi2lo_stats(IN,N,jIdxs,iIdxs,Wgts,AbvThresh, \
                   UpMn,UpMin,UpMax,UpMed,UpFrac,UpSigma,UpMnAbv, \
                   dims,mpdims)
  
  return([/UpMn,UpMin,UpMax,UpMed,UpFrac,UpSigma,UpMnAbv/])
end

