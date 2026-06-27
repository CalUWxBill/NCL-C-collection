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

;---------------------------------------------------------------------------------------------------------
; Usage: ncl $NCL_SCRIPTS/regress_ens.ncl 'varlist="$NCL_USER_DIR/varlists/S2SSeas.West_HUC4.NMME.tref.ncl"' 'imod=0' 'basin="Colorado_Headwaters"' 'ild=2' 'mm=3' 'ismixed=True'
loadscript(varlist)
begin
    ar2d = onedtond(fspan(1.0,100.0,100),(/5,20/))
    A    = dim_avg_n(ar2d,0)
    print(A)

    byear = 1982
    eyear = 2021
    sm2  = sprinti("%0.2i", mm)
    ibsn = str_match_ind(basin_names, basin)
    print("ibsn="+ibsn)
    ;exit()
    mod_name = mod_names(imod)

    fdir_tmp := filedir_out+"/Basins/"+mod_name
    fnameout := fdir_tmp+"/"+mod_name+"_raw_data_"+variable+".nc"
    Lst      := getMultiVarsFromFile(fnameout,"nc",variable)
    Fcst_raw := sub_n_crd_pad(Lst[0],"year",byear,eyear,0)
    years := Fcst_raw&year
    years!0    = "year"
    years&year = years
    nyears  = dimsizes(years)

    printVarSummary(Fcst_raw)

    fdir_tmp := filedir_out+"/Basins/"+OBS_name
    fnameout := fdir_tmp+"/"+OBS_name+"_raw_data_"+variable+".nc"
    Lst      := getMultiVarsFromFile(fnameout,"nc",variable)
    OBS_raw  := sub_n_crd_pad(Lst[0],"year",byear,eyear,0)

    Fcst_EnsM := named_avg(Fcst_raw,"ensemble")
    printVarSummary(OBS_raw)
    printVarSummary(years)

    xens = Fcst_raw(basin|ibsn,lead|ild,{month|mm},year|:,ensemble|:)
    x    = named_avg(xens,"ensemble")
    y    = OBS_raw (basin|ibsn,{month|mm},year|:)

    Lst := reg_lin_stats_n(OBS_raw, Fcst_raw, "year", "ensemble")
    m2       = Lst[0](basin|ibsn,lead|ild,{month|mm})
    b2       = Lst[1](basin|ibsn,lead|ild,{month|mm})
    MSE2     = Lst[2](basin|ibsn,lead|ild,{month|mm})
    N2       = Lst[3](basin|ibsn,lead|ild,{month|mm})
    N_12     = Lst[4](basin|ibsn,lead|ild,{month|mm})
    Xavg2    = Lst[5](basin|ibsn,lead|ild,{month|mm})
    Sxx2     = Lst[6](basin|ibsn,lead|ild,{month|mm})
    sigma_e2 = Lst[7](basin|ibsn,lead|ild,{month|mm})

    Lst := reg_lin_stats_n(y, xens, "year", "ensemble")
    m       = Lst[0]
    b       = Lst[1]
    MSE     = Lst[2]
    N       = Lst[3]
    N_1     = Lst[4]
    Xavg    = Lst[5]
    Sxx     = Lst[6]
    sigma_e = Lst[7]
    
    print("m       "+m      +" | m2       "+m2      )
    print("b       "+b      +" | b2       "+b2      )
    print("MSE     "+MSE    +" | MSE2     "+MSE2    )
    print("N       "+N      +" | N2       "+N2      )
    print("N_1     "+N_1    +" | N_12     "+N_12    )
    print("Xavg    "+Xavg   +" | Xavg2    "+Xavg2   )
    print("Sxx     "+Sxx    +" | Sxx2     "+Sxx2    )
    print("sigma_e "+sigma_e+" | sigma_e2 "+sigma_e2)
    
    QMLst  := QM_fit_n(OBS_raw, Fcst_raw, prms_type, prms_type, "year", "ensemble")
    Y_pLst2 = QMLst[0]
    X_pLst2 = QMLst[1]

    QMLst := QM_fit_n(y, xens, prms_type, prms_type, "year", "ensemble")
    Y_pLst = QMLst[0]
    X_pLst = QMLst[1]

    QMLst  := EQM_fit_n(OBS_raw, Fcst_raw, "year", "ensemble", ismixed)
    Y_EQMLst2 = QMLst[0]
    X_EQMLst2 = QMLst[1]
    print(Y_EQMLst2)
    print(X_EQMLst2)

    QMLst := EQM_fit_n(y, xens, "year", "ensemble", ismixed)
    Y_EQMLst = QMLst[0]
    X_EQMLst = QMLst[1]
    print(xens)
    print(Y_EQMLst)
    print(X_EQMLst)
    print(Y_EQMLst[0]+" "+Y_EQMLst[1])
    print(X_EQMLst[0]+" "+X_EQMLst[1])

    QMLst     := QM_sprd_fit_n(OBS_raw, Fcst_raw, prms_type, prms_type, "year", "ensemble")
    Yse_pLst2  = QMLst[0]
    Xse_pLst2  = QMLst[1]
    X_sprderr2 = QMLst[2]

    QMLst    := QM_sprd_fit_n(y, xens, prms_type, prms_type, "year", "ensemble")
    Yse_pLst  = QMLst[0]
    Xse_pLst  = QMLst[1]
    X_sprderr = QMLst[2]

    QMLst       := QM_sprd2_fit_n(OBS_raw, Fcst_raw, prms_type, prms_type, "year", "ensemble")
    Yse2_pLst2   = QMLst[0]
    Xse2_pLst2   = QMLst[1]
    X_sprderr2_2 = QMLst[2]
    se_pLst2     = QMLst[3]

    QMLst      := QM_sprd2_fit_n(y, xens, prms_type, prms_type, "year", "ensemble")
    Yse2_pLst   = QMLst[0]
    Xse2_pLst   = QMLst[1]
    X_sprderr_2 = QMLst[2]
    se_pLst     = QMLst[3]

    QMLst   := train_MVA(Fcst_raw, OBS_raw, "year", "ensemble")
    o_hat2   = QMLst[0]
    y_hat2   = QMLst[1]
    sigma_MVA2 = QMLst[2]
    sigma_o2 = QMLst[3]

    QMLst  := train_MVA(xens, y, "year", "ensemble")
    o_hat   = QMLst[0]
    y_hat   = QMLst[1]
    sigma_MVA = QMLst[2]
    sigma_o = QMLst[3]

    QMLst := train_CCR(Fcst_raw, OBS_raw, "year", "ensemble")
    o_hat2 = QMLst[0]
    y_hat2 = QMLst[1]
    a_CCR2 = QMLst[2]
    b_CCR2 = QMLst[3]

    QMLst := train_CCR(xens, y, "year", "ensemble")
    o_hat  = QMLst[0]
    y_hat  = QMLst[1]
    a_CCR  = QMLst[2]
    b_CCR  = QMLst[3]

    QMLst := train_RPC(Fcst_raw, OBS_raw, "year", "ensemble")
    o_hat_RPC2     = QMLst[0]
    y_hat_RPC2     = QMLst[1]
    ya_hat_RPC2    = QMLst[2]
    sigmaa_em_RPC2 = QMLst[3]
    sigmaa_o_RPC2  = QMLst[4]
    rho_RPC2       = QMLst[5]
    sqrt1_rho2_2   = QMLst[6]

    QMLst := train_RPC(xens, y, "year", "ensemble")
    o_hat_RPC     = QMLst[0]
    y_hat_RPC     = QMLst[1]
    ya_hat_RPC    = QMLst[2]
    sigmaa_em_RPC = QMLst[3]
    sigmaa_o_RPC  = QMLst[4]
    rho_RPC       = QMLst[5]
    sqrt1_rho2    = QMLst[6]

    nens  = dimsizes(Fcst_raw&ensemble)
    
    optT = True
    optT@calc_sigma = True ; This calculated ensemble sigma for each forecast

    optSV = True
    optSV@nens = nens

    print("*******************************")
    print("*** Predicting Large Arrays ***")
    print("*******************************")
    yout_T2      = reg_lin_ens_n     (Fcst_raw , Lst[0], Lst[1], Lst[2], Lst[4], Lst[5], Lst[6], Lst[7], "ensemble", optT )
    yout_F2      = reg_lin_ens_n     (Fcst_raw , Lst[0], Lst[1], Lst[2], Lst[4], Lst[5], Lst[6], Lst[7], "ensemble", False)
    yout_SV2     = reg_lin_ens_n     (Fcst_EnsM, Lst[0], Lst[1], Lst[2], Lst[4], Lst[5], Lst[6], Lst[7], "ensemble", optSV)
    yout_QM2     = QM_predict_n      (Fcst_raw , Y_pLst2, X_pLst2, prms_type, prms_type)
    yout_EQM2    = EQM_predict_n     (Fcst_raw , Y_EQMLst2, X_EQMLst2, "year", "ensemble", ismixed)
    yout_QMse2   = QM_sprd_predict_n (Fcst_raw , Yse_pLst2, Xse_pLst2, X_sprderr2, prms_type, prms_type, "ensemble")
    yout_QMse2_2 = QM_sprd2_predict_n(Fcst_raw , Yse2_pLst2, Xse2_pLst2, X_sprderr2_2, se_pLst2, prms_type, prms_type, "ensemble")
    yout_MVA2    = test_MVA          (Fcst_raw , o_hat2,y_hat2,sigma_MVA2,sigma_o2)
    yout_CCR2    = test_CCR          (Fcst_raw , o_hat2,y_hat2,a_CCR2,b_CCR2, "ensemble")
    yout_RPC2    = test_RPC          (Fcst_raw , o_hat_RPC2,y_hat_RPC2,ya_hat_RPC2,sigmaa_em_RPC2,sigmaa_o_RPC2,rho_RPC2,sqrt1_rho2_2, "ensemble")

    yout_T2      := yout_T2     (basin|ibsn,lead|ild,{month|mm},year|:,ensemble|:)
    yout_F2      := yout_F2     (basin|ibsn,lead|ild,{month|mm},year|:,ensemble|:)
    yout_SV2     := yout_SV2    (basin|ibsn,lead|ild,{month|mm},year|:,ensemble|:)
    yout_QM2     := yout_QM2    (basin|ibsn,lead|ild,{month|mm},year|:,ensemble|:)
    yout_EQM2    := yout_EQM2   (basin|ibsn,lead|ild,{month|mm},year|:,ensemble|:)
    yout_QMse2   := yout_QMse2  (basin|ibsn,lead|ild,{month|mm},year|:,ensemble|:)
    yout_QMse2_2 := yout_QMse2_2(basin|ibsn,lead|ild,{month|mm},year|:,ensemble|:)
    yout_MVA2    := yout_MVA2   (basin|ibsn,lead|ild,{month|mm},year|:,ensemble|:)
    yout_CCR2    := yout_CCR2   (basin|ibsn,lead|ild,{month|mm},year|:,ensemble|:)
    yout_RPC2    := yout_RPC2   (basin|ibsn,lead|ild,{month|mm},year|:,ensemble|:)
    
    print("*******************************")
    print("*** Predicting Small Arrays ***")
    print("*******************************")
    yout_T      = reg_lin_ens_n     (xens, m, b, MSE, N_1, Xavg, Sxx, sigma_e, "ensemble", optT )
    yout_F      = reg_lin_ens_n     (xens, m, b, MSE, N_1, Xavg, Sxx, sigma_e, "ensemble", False)
    yout_SV     = reg_lin_ens_n     (x   , m, b, MSE, N_1, Xavg, Sxx, sigma_e, "ensemble", optSV)
    yout_QM     = QM_predict_n      (xens, Y_pLst, X_pLst, prms_type, prms_type)
    yout_EQM    = EQM_predict_n     (xens, Y_EQMLst, X_EQMLst, "year", "ensemble", ismixed)

    print(xens+" "+yout_EQM)
    ;exit()

    yout_QMse   = QM_sprd_predict_n (xens, Yse_pLst, Xse_pLst, X_sprderr, prms_type, prms_type, "ensemble")
    yout_QMse_2 = QM_sprd2_predict_n(xens, Yse2_pLst, Xse2_pLst, X_sprderr_2, se_pLst, prms_type, prms_type, "ensemble")
    yout_MVA    = test_MVA          (xens, o_hat,y_hat,sigma_MVA,sigma_o)
    yout_CCR    = test_CCR          (xens, o_hat,y_hat,a_CCR,b_CCR, "ensemble")
    yout_RPC    = test_RPC          (xens, o_hat_RPC,y_hat_RPC,ya_hat_RPC,sigmaa_em_RPC,sigmaa_o_RPC,rho_RPC,sqrt1_rho2, "ensemble")

    F_diff  = sum(abs(yout_F2  - yout_F ))
    T_diff  = sum(abs(yout_T2  - yout_T ))
    SV_diff = sum(abs(yout_SV2 - yout_SV))
    print("F_diff  = "+F_diff)
    print("T_diff  = "+T_diff)
    print("SV_diff = "+SV_diff)
    
    print_array_head(yout_T     ,"yout_T:      ","%6.2f")
    print_array_head(yout_F     ,"yout_F:      ","%6.2f")
    print_array_head(yout_SV    ,"yout_SV:     ","%6.2f")
    print_array_head(yout_QM    ,"yout_QM:     ","%6.2f")
    print_array_head(yout_EQM   ,"yout_EQM:    ","%6.2f")
    print_array_head(yout_QMse  ,"yout_QMse:   ","%6.2f")
    print_array_head(yout_QMse_2,"yout_QMse_2: ","%6.2f")
    print_array_head(yout_MVA   ,"yout_MVA:    ","%6.2f")
    print_array_head(yout_CCR   ,"yout_CCR:    ","%6.2f")
    print_array_head(yout_RPC   ,"yout_RPC:    ","%6.2f")

    validxs = ind((.not.ismissing(x)).and.(.not.ismissing(y)))
    x    := x(validxs)
    xens := xens(validxs,:)
    y    := y(validxs)
    
    y_T      := yout_T (ensemble|:,year|validxs)
    y_F      := yout_F (ensemble|:,year|validxs)
    y_SV     := yout_SV(ensemble|:,year|validxs)
    y_QM     := yout_QM(ensemble|:,year|validxs)
    y_EQM    := yout_EQM(ensemble|:,year|validxs)
    y_QMse   := yout_QMse(ensemble|:,year|validxs)
    y_QMse_2 := yout_QMse_2(ensemble|:,year|validxs)
    y_MVA    := yout_MVA(ensemble|:,year|validxs)
    y_CCR    := yout_CCR(ensemble|:,year|validxs)
    y_RPC    := yout_RPC(ensemble|:,year|validxs)

    y_T2      := yout_T2 (ensemble|:,year|validxs)
    y_F2      := yout_F2 (ensemble|:,year|validxs)
    y_SV2     := yout_SV2(ensemble|:,year|validxs)
    y_QM2     := yout_QM2(ensemble|:,year|validxs)
    y_EQM2    := yout_EQM2(ensemble|:,year|validxs)
    y_QMse2   := yout_QMse2(ensemble|:,year|validxs)
    y_QMse2_2 := yout_QMse2_2(ensemble|:,year|validxs)
    y_MVA2    := yout_MVA2(ensemble|:,year|validxs)
    y_CCR2    := yout_CCR2(ensemble|:,year|validxs)
    y_RPC2    := yout_RPC2(ensemble|:,year|validxs)


    res                     = True                   ; plot mods desired
    res@xyMarkLineModes     = new(nens+2,"string")
    res@xyMarkLineModes(:)  = "Markers"

    res@xyMarkers           = new(nens+2,"integer")
    res@xyMarkers(:)        = 16                     ; choose type of marker 

    res@xyMonoMarkerSize    = False
    res@xyMarkerSizes       = new(nens+2,"double")
    res@xyMarkerSizes(0)    = 0.0075                 ; Marker size (default 0.01)
    res@xyMarkerSizes(1)    = 0.0075                 ; Marker size (default 0.01)
    res@xyMarkerSizes(2:)   = 0.0035                 ; Marker size (default 0.01)

    res@xyDashPatterns      = 0                      ; solid line 

    res@xyMonoMarkerColor   = False
    res@xyMarkerColors      = new(nens+2,"string")
    res@xyMarkerColors(0)   = "red"                  ; Marker size (default 0.01)
    res@xyMarkerColors(1)   = "black"                ; Marker size (default 0.01)
    res@xyMarkerColors(2:)  = "grey"                 ; Marker size (default 0.01)

    res@trXMinF             = min(x)
    res@trXMaxF             = max(x)
    res@trYMinF             = min(y) < min(y_F2) < min(xens)
    res@trYMaxF             = max(y) > max(y_F2) > max(xens)
    res@tmYLFormat          = "f"                    ; not necessary but nicer labels 

    res@tiMainString           = "regline_stats: Brownlee Data"
    res@tiYAxisString          = "Y"
    res@tiXAxisString          = "X"

    nx   = dimsizes(x)


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry       = new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_T,"ensemble")
    pltarry(2:,:) = (/ y_T /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_T")   ; send graphics to PNG file
    
    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_F,"ensemble")
    pltarry(2:,:) = (/ y_F /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_F")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_SV,"ensemble")
    pltarry(2:,:) = (/ y_SV /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_SV")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_QM,"ensemble")
    pltarry(2:,:) = (/ y_QM /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_QM")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_EQM,"ensemble")
    pltarry(2:,:) = (/ y_EQM /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_EQM")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_QMse,"ensemble")
    pltarry(2:,:) = (/ y_QMse /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_QMse")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_QMse_2,"ensemble")
    pltarry(2:,:) = (/ y_QMse_2 /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_QMse_2")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_MVA,"ensemble")
    pltarry(2:,:) = (/ y_MVA /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_MVA")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_CCR,"ensemble")
    pltarry(2:,:) = (/ y_CCR /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_CCR")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_RPC,"ensemble")
    pltarry(2:,:) = (/ y_RPC /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_RPC")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_T2,"ensemble")
    pltarry(2:,:) = (/ y_T2 /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_T2")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_F2,"ensemble")
    pltarry(2:,:) = (/ y_F2 /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_F2")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_SV2,"ensemble")
    pltarry(2:,:) = (/ y_SV2 /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_SV2")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_QM2,"ensemble")
    pltarry(2:,:) = (/ y_QM2 /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_QM2")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_EQM2,"ensemble")
    pltarry(2:,:) = (/ y_EQM2 /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_EQM2")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_QMse2,"ensemble")
    pltarry(2:,:) = (/ y_QMse2 /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_QMse2")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_QMse2_2,"ensemble")
    pltarry(2:,:) = (/ y_QMse2_2 /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_QMse2_2")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_MVA2,"ensemble")
    pltarry(2:,:) = (/ y_MVA2 /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_MVA2")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_CCR2,"ensemble")
    pltarry(2:,:) = (/ y_CCR2 /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_CCR2")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = named_avg(y_RPC2,"ensemble")
    pltarry(2:,:) = (/ y_RPC2 /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_RPC2")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot


;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    pltarry      := new ( (/nens+2,nx/), typeof(x))
    pltarry(0 ,:) = y                                 ; use markers
    pltarry(1 ,:) = x                                 ; use markers
    pltarry(2:,:) = (/ xens(ensemble|:,year|:) /)

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks_type := "png"
    wks_type@wkWidth  = 1600
    wks_type@wkHeight = 1600
    wks  = gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild+"_ens_Orig")   ; send graphics to PNG file

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot











    rc =  regline_stats(x,y) ; linear regression coef
    print(rc)
                                         ; EXTREMES with 95% slope & y-intercept
    Yest_025 = rc@y95(0) + rc@b95(0)*x  
    Yest_975 = rc@y95(1) + rc@b95(1)*x  

;************************************************
; create an array to hold both the original data
; and the calculated regression line   
;************************************************
    nx   := dimsizes(x)
    pltarry     := new ( (/6,nx/), typeof(x))
    pltarry(0,:) = y                                 ; use markers
    pltarry(1,:) = rc@Yest

    pltarry(2,:) = rc@YMR025                         ; mean response
    pltarry(3,:) = rc@YMR975

    pltarry(4,:) = rc@YPI025                         ; prediction limits
    pltarry(5,:) = rc@YPI975

;************************************************
; plotting parameters
; This illustrates one approach. Overlays could also be used.
;************************************************
    wks  := gsn_open_wks(wks_type,"regress_"+mod_name+"."+basin+"."+variable+"."+sm2+".ld"+ild)   ; send graphics to PNG file
    
    res                    := True                   ; plot mods desired
    res@xyMarkLineModes     = (/"Markers","Lines" \  ; choose which have markers
                               ,"Lines"  ,"Lines" \ 
                               ,"Lines"  ,"Lines" /)
    res@xyMarkers           = 16                     ; choose type of marker 
    res@xyMarkerSizeF       = 0.0075                 ; Marker size (default 0.01)

    res@xyDashPatterns      = 0                      ; solid line 
    res@xyLineThicknesses   = (/1,3,2,2,2,2/)     
    res@xyLineColors        = (/ "black", "black" \
                               , "blue" , "blue"  \
                               , "red"  , "red"   /)

    res@trXMinF             = min(x)
    res@trXMaxF             = max(x)
    res@trYMinF             = min(y) < min(y_F2) < min(xens)
    res@trYMaxF             = max(y) > max(y_F2) > max(xens)
    res@tmYLFormat          = "f"                    ; not necessary but nicer labels 

    res@tiMainString           = "regline_stats: Brownlee Data"
    res@tiYAxisString          = "Y"
    res@tiXAxisString          = "X"

;---Make legend smaller and move into plot
    res@pmLegendDisplayMode    = "Always"            ; turn on legend
    res@pmLegendSide           = "Top"               ; Change location of 
    res@pmLegendParallelPosF   = .25                 ; move units right
    res@pmLegendOrthogonalPosF = -0.41               ; move units down
    res@pmLegendWidthF         = 0.175               ; Change width and
    res@pmLegendHeightF        = 0.175               ; height of legend.
    res@lgPerimOn              = True                ; turn off/on box around
    res@lgLabelFontHeightF     = .015                ; label font height
    res@xyExplicitLegendLabels = (/"data"         , "regline"       \
                                  ,"5% response"  , "95% response"  \   
                                  ,"5% prediction", "95% prediction"/)

    plot  = gsn_csm_xy (wks,x,pltarry,res)           ; create plot
end
