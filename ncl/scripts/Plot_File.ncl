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
if (.not.isdefined("plot_routines_declared")) then
 loadscript("$NCL_USER_DIR/load/plot_routines.ncl")
 plot_routines_declared = 1
end if

; Usage: ncl $NCL_SCRIPTS/Plot_File.ncl 'fname="~/data/SeasClimFcst/Models/C3S/SEAS5/MONTHLY/tref/tref.SEAS5.202006.grib"' 'domain=""' 'contours=""'
; Usage: ncl $NCL_SCRIPTS/Plot_File.ncl 'fname="~/data/SeasClimFcst/Models/C3S/SEAS5/MONTHLY/tref/tref.SEAS5.202006.grib"'
begin
  if (.not.isvar("domain")) then
      domain=""
  end if
  if (.not.isvar("contours")) then
      contours=""
  end if
  if (.not.isvar("fext")) then
      nfields = str_fields_count(fname(0), ".")
      print(nfields)   ; nfields = 15
      
      fext = str_get_field(fname(0), nfields, ".")
      print(filetype)
  end if
  
  nc_file = addfile(fname, "r") ; Read file for the first time.

  names = getfilevarnames(nc_file)
  print(names)
  nvars = dimsizes(names)

  fc = str_fields_count(fname, "/")
  print(fc)

  fname_nd = str_get_field(fname, fc, "/")
  print(fname_nd)

  do i=0,nvars-1
    VAR_IN = getGridFromFile(fname,filetype,names(i))
    img_name  = "~/images/"+fname_nd+"_"+domain+"_"+names(i)
    img_title = ""
    plotGrid(VAR_IN(0,0,:,:),img_name,img_title,domain,contours,False,"png")
    delete(VAR_IN)
  end do

end
