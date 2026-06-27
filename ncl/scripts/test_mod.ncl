; Created by Bill Scheftic
; ------------
; Load scripts
; ------------
if (.not.isdefined("functions_declared")) then
 loadscript("$NCL_USER_DIR/load/functions.ncl")
 functions_declared = 1
end if

;---------------------------------------------------------------------------------------------------------
; Usage: ncl $NCL_SCRIPTS/test_mod.ncl
begin
    x = fspan(-20,20,81)
    x_mod_10 = mod(x,10)
    x_cmod_10 = cycmod(x,10)
    x_cmod_be = cycmod_be(x,-5, 5)
    fmt = "%6.1f"
    print("   x    x_mod_10 x_cmod_10 x_cmod_be")
    print(sprintf(fmt,x)+"   "+sprintf(fmt,x_mod_10)+"   "+sprintf(fmt,x_cmod_10)+"   "+sprintf(fmt,x_cmod_be))

    x         := fspan(-360,360,73)
    x_0_360    = cycmod_be(x,   0,360)
    x_m180_180 = cycmod_be(x,-180,180)
    fmt = "%6.0f"
    print("   x    x_0_360 x_m180_180")
    print(sprintf(fmt,x)+"   "+sprintf(fmt,x_0_360)+"   "+sprintf(fmt,x_m180_180))
end
