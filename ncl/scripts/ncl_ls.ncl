; ------------
; Load scripts
; ------------
if (.not.isdefined("contrib_declared")) then
 loadscript("$NCARG_ROOT/lib/ncarg/nclex/gsun/gsn_code.ncl")
 loadscript("$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_csm.ncl")
 loadscript("$NCARG_ROOT/lib/ncarg/nclscripts/csm/contributed.ncl")
 contrib_declared = 1
end if

; Usage: ncl $NCL_SCRIPTS/ncl_ls.ncl 'instr=""'
begin
    fnames = systemfunc("ls "+instr)
    if (.not.any(ismissing(fnames))) then
      print(fnames)
    end if
end
