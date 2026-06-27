; Created by Bill Scheftic
; These functions use UdUnits2.h to convert between units
; Index of Functions and Procedures
; function deAliasUnits(units:string)
; function convertTo(indata:numeric,to_units:string)
; function convertFromTo(indata:numeric,from_units:string,to_units:string)

if (.not.isdefined("contrib_declared")) then
 loadscript("$NCARG_ROOT/lib/ncarg/nclex/gsun/gsn_code.ncl")
 loadscript("$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_csm.ncl")
 loadscript("$NCARG_ROOT/lib/ncarg/nclscripts/csm/contributed.ncl")
 contrib_declared = 1
end if

undef("deAliasUnits")
function deAliasUnits(units:string)
local ret_units
begin
  if (units.eq."Kelvin_scale") then
    ret_units = "K"
  else
    ret_units = units
  end if

  return(ret_units)
end

undef("convertTo")
function convertTo(indata:numeric,to_units:string)
local from_units, data
begin
  if (isatt(indata,"units")) then
    from_units = deAliasUnits(indata@units)
    from_units = str_sub_str (from_units," ",".")
    if ((from_units.ne.to_units).and.(from_units.ne."").and.(to_units.ne."")) then
      data = ncl_c_convert(indata,from_units,to_units)
      copy_VarMeta(indata,data)
      data@units = to_units
    else
      data = indata
    end if
  else
    print("convert_units.ncl: convertTo: input variable has no units attribute.")
    print("                              No conversion applied!")
    data = indata
  end if

  return(data)
end

undef("convertFromTo")
function convertFromTo(indata:numeric,from_units:string,to_units:string)
local data
begin
  if (from_units.ne.to_units) then
    data = ncl_c_convert(indata,from_units,to_units)
    copy_VarMeta(indata,data)
    data@units = to_units
  else
    data = indata
  end if

  return(data)
end

