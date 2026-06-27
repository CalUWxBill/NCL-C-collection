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
if (.not.isdefined("functions_declared")) then
 loadscript("$NCL_USER_DIR/load/functions.ncl")
 functions_declared = 1
end if
if (.not.isdefined("my_io_declared")) then
 loadscript("$NCL_USER_DIR/load/my_io.ncl")
 my_io_declared = 1
end if
if (.not.isdefined("named_stats_declared")) then
 loadscript("$NCL_USER_DIR/load/named_stats.ncl")
 named_stats_declared = 1
end if
if (.not.isdefined("qm_michael_declared")) then
 loadscript("$NCL_USER_DIR/load/qm_michael.ncl")
 qm_michael_declared = 1
end if

;---------------------------------------------------------------------------------------------------------
begin

    nvals    = 300
    p      = random_uniform(0.0, 1.0, nvals)
    p!0    = "dim0"
    p&dim0 = ispan(0,nvals-1,1)

    p0    = 0.7
    shape = 1.5
    scale = 5.0
    rate  = 1.0/scale
    X  = dist_mixed_gamma_Pinv(p,p0,shape,scale)
    Xm = named_cdfgam_mixed_x(p,shape,rate,p0)
    printVarSummary(X)
    printVarSummary(Xm)

    print("C mixed_gamma fit")
    X_p   := fit_dist_Lst(X,"mixed_gamma","dim0")
    Xm_p  := named_fit_Lst(Xm,"mixed_gamma","dim0")
    printVarSummary(X_p)
    printVarSummary(Xm_p)
    print(X_p[0]+" "+Xm_p[2])
    print(X_p[1]+" "+Xm_p[0])
    print(X_p[2]+" "+Xm_p[1])
    X_P   := dist_P(X,X_p,"mixed_gamma")
    Xm_P  := named_P(Xm,Xm_p,"mixed_gamma")
    printVarSummary(X_P)
    printVarSummary(Xm_P)
    X_z   := dist_ugauss_Pinv(X_P)
    Xm_z  := named_cdfnor_std_x(Xm_P)
    printVarSummary(X_z)
    printVarSummary(Xm_z)
    print("")
    
    print(p+" "+X+" "+Xm+" "+X_P+" "+Xm_P+" "+X_z+" "+Xm_z)

    X_p_gamfit = named_gamfit(X,False,"dim0")
    print(X_p_gamfit)
    print("")
end
