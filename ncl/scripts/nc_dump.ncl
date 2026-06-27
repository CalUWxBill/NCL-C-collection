; ------------
; Load scripts
; ------------
if (.not.isdefined("contrib_declared")) then
 loadscript("$NCARG_ROOT/lib/ncarg/nclex/gsun/gsn_code.ncl")
 loadscript("$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_csm.ncl")
 loadscript("$NCARG_ROOT/lib/ncarg/nclscripts/csm/contributed.ncl")
 contrib_declared = 1
end if

; Usage: ncl $NCL_SCRIPTS/nc_dump.ncl 'fname="~/data/precip/udel/precip.mon.total.v301.nc"'
; Usage: ncl $NCL_SCRIPTS/nc_dump.ncl 'fname="~/data/precip/udel/precip.mon.ltm.v301.nc"'
; Usage: ncl $NCL_SCRIPTS/nc_dump.ncl 'fname="~/data/precip/precl/precip.mon.mean.0.5x0.5.nc"'
; Usage: ncl $NCL_SCRIPTS/nc_dump.ncl 'fname="~/data/precip/precl/precip.mon.ltm.0.5x0.5.nc"'
; Usage: ncl $NCL_SCRIPTS/nc_dump.ncl 'fname="~/data/reanalyses/RUC/13km/ruc2_130_20110909_2200_000.grb2"'
; Usage: ncl $NCL_SCRIPTS/nc_dump.ncl 'fname="~/data/MERRA-2/MERRA2_100.inst1_2d_int_Nx.19800104.SUB.nc4"'
; Usage: ncl $NCL_SCRIPTS/nc_dump.ncl 'fname="~/data/SeasClimFcst/Models/C3S/SEAS5/MONTHLY/tref/tref.SEAS5.199301.grib"' 'names=(/"g0_lat_2","g0_lon_3","forecast_time1","ensemble0","ensemble0_info"/)'
begin

  nc_file = addfile(fname, "r") ; Read file for the first time. 

  printVarSummary(nc_file)
  print(nc_file)
  
  nvars = dimsizes(names)
  do i=0,nvars-1
    print(nc_file->$names(i)$)
  end do

  delete(nc_file)
end
