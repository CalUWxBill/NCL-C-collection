; Created by Bill Scheftic
; ------------
; Load scripts
; ------------
if (.not.isdefined("contrib_declared")) then
 loadscript("$NCARG_ROOT/lib/ncarg/nclex/gsun/gsn_code.ncl")
 loadscript("$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_csm.ncl")
 loadscript("$NCARG_ROOT/lib/ncarg/nclscripts/csm/contributed.ncl")
 contrib_declared = 1
end if
if (.not.isdefined("my_io_declared")) then
 loadscript("$NCL_USER_DIR/load/my_io.ncl")
 my_io_declared = 1
end if
if (.not.isdefined("named_stats_declared")) then
 loadscript("$NCL_USER_DIR/load/named_stats.ncl")
 named_stats_declared = 1
end if
if (.not.isdefined("plot_routines_declared")) then
 loadscript("$NCL_USER_DIR/load/plot_routines.ncl")
 plot_routines_declared = 1
end if

; Usage: ncl $NCL_SCRIPTS/Plot_Ens_Fcst.ncl 'fname="~/data/SeasClimFcst/Models/C3S/SEAS5/MONTHLY/evaporation/evaporation.SEAS5.202006.grib"' 'var="ERATE_GDS0_SFC"' 'ltdim="g0_lat_2"' 'lndim="g0_lon_3"' 'lddim="forecast_time1"' 'ild=0' 'ensdim="ensemble0"' 'iens=-1' 'domain=""' 'cntrs=""'
; Usage: ncl $NCL_SCRIPTS/Plot_Ens_Fcst.ncl 'fname="~/data/SeasClimFcst/Models/CFSv2/MONTHLY/ET/ET.CFSv2.202006.nc"' 'var="ET"' 'ltdim="lat"' 'lndim="lon"' 'lddim="lead"' 'ild=0' 'ensdim="ensemble"' 'iens=-1'
begin
  if (.not.isvar("domain")) then
    domain = "Global360"
  end if
  if (.not.isvar("cntrs")) then
      cntrs=""
  end if
  if (.not.isvar("fext")) then
      nfields = str_fields_count(fname(0), ".")
      print(nfields)   ; nfields = 15
      
      fext = str_get_field(fname(0), nfields, ".")
      print(fext)
  end if
  
  nc_file = addfile(fname, "r") ; Read file for the first time.

  names = getfilevarnames(nc_file)
  print(names)
  nvars = dimsizes(names)

  fc = str_fields_count(fname, "/")
  print(fc)

  fname_nd = str_get_field(fname, fc, "/")
  print(fname_nd)

  VAR_IN = getGridFromFile(fname,fext,var)
  printVarSummary(VAR_IN)
  if (isvar("in_units")) then
    VAR_IN@units = in_units
  end if
  if (isvar("units_to")) then
    VAR_IN = convertTo(VAR_IN,units_to)
  end if
  if (isvar("scale")) then
    VAR_IN = (/ scale*VAR_IN /)
  end if

  wks_type := "png"
  wks_type@wkWidth  = 2000
  wks_type@wkHeight = 2000
  
  img_name  = "~/images/"+fname_nd+"_"+domain+"_"+var+"_ld"+ild+"_ens"+iens
  img_title = ""
  if (iens.lt.0) then
    VAR_IN := named_avg(VAR_IN,ensdim)
    VAR_Plot := VAR_IN($lddim$|ild,$ltdim$|:,$lndim$|:)
    plotGrid(VAR_Plot,img_name,img_title,domain,cntrs,False,wks_type)
  else
    VAR_Plot := VAR_IN($lddim$|ild,$ensdim$|iens,$ltdim$|:,$lndim$|:)
    plotGrid(VAR_Plot,img_name,img_title,domain,cntrs,False,wks_type)
  end if
  printMinMax(VAR_Plot,False)
  printVarStats(var,VAR_Plot)

  print(num(VAR_Plot.lt.0.0))
  a1D      := ndtooned(VAR_Plot)
  dsizes_a := dimsizes(VAR_Plot)
  dnames_a := getvardims(VAR_Plot)
  indices  := ind_resolve(ind(a1D.lt.0.0),dsizes_a)
  printVarSummary(VAR_Plot)
  printVarSummary(indices)

  dim_ida  := dimsizes(indices)     
  npts     := dim_ida(0)       ; number of elements > 5 (here 9)
  ndim     := dim_ida(1)       ; rank of "VAR_Plot"  (here 3)
  
  do n=0,npts-1
    print(VAR_Plot&$dnames_a(0)$(indices(n,0))+" "+VAR_Plot&$dnames_a(1)$(indices(n,1))+" "+VAR_Plot(indices(n,0),indices(n,1)))
  end do
end
