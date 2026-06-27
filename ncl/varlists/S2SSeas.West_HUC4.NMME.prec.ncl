if (.not.isdefined("s2s_declared")) then
 loadscript("$NCL_USER_DIR/load/s2s.ncl")
 s2s_declared = 1
end if

begin
;---------------------
; General Information.
;---------------------
  cur_year := 2021 ; these NEED to be updated every month
  cur_mm   := 11    ; these NEED to be updated every month
  unitOfTime = "months since 1970-1-1 00:00:00"
  cur_date = cd_inv_calendar(cur_year,cur_mm,1,0,0,0,unitOfTime,0)
  cur_date@units=unitOfTime
  
  project          = "S2SSeas/West_HUC4/NMME"       ; Name of project, serves as a path
  home_dir         = "$HOME"                     ; If you remove this edit all paths that point to home_dir.
  filedir_out      = home_dir+"/data/"+project   ; base directory for data output
  base_img_dir     = home_dir+"/images/"+project ; base directory for image output
  
  variable         = "prec"   ; variable name, generally corresponds to NMME variable
  var_output_units = "mm.d-1" ; desired output unit
  nsigfg           = 2        ; 3 for temperature, 2 for precipitation.  Controls plot axis interval.
  prms_type        = "mixed_gamma"

;---------------------------
; Observed File information.
;---------------------------
  prism_dir        = "$S2S_PRISM"

  OBS_name         = "PRISM"
  fname_OBS        = prism_dir+"/MONTHLY/ppt/%y4/PRISM_ppt_%p_4kmM2_%y4%m2_bil"
  fext_OBS         = "bil"    ; file extension
  var_OBS          = "P"      ; name of variable in file
  OBS_unit_alias   = "mm.d-1" ; define if unit in file cannot be converted to output unit
  lat_OBS          = "lat"    ; name of latitude dimension
  lon_OBS          = "lon"    ; name of longitude dimension

  obs_byear        = 1979
  obs_eyear        = cur_year
  
  domain           = "WestUS"   ; Domain to subset datasets over
  mask_res         = 0.015   ; resolution in degrees of fine grid for mask
                             ; - should have at least twice the resolution of the observation dataset.
  
;---------------------------------
; NMME information for each model.
;---------------------------------
  fname_Fcst_1     = "$S2S_NMME/%mod/MONTHLY/%v/%v.%mod.%y4%m2.nc"
  mod_names        = (/      "CFSv2",    "CanCM4i",   "GEM-NEMO", "GFDL-SPEAR",      "CCSM4",    "GEOSS2S" /)
  fcst_name        = (/       "NMME",       "NMME",       "NMME",       "NMME",       "NMME",       "NMME" /)
  fname_fcst       = (/ fname_Fcst_1, fname_Fcst_1, fname_Fcst_1, fname_Fcst_1, fname_Fcst_1, fname_Fcst_1 /)
  fext_fcst        = (/         "nc",         "nc",         "nc",         "nc",         "nc",         "nc" /)
  var_fcst         = (/     variable,     variable,     variable,     variable,     variable,     variable /)
  alias_fcst       = (/     "mm.d-1",     "mm.d-1",     "mm.d-1",     "mm.d-1",     "mm.d-1",     "mm.d-1" /)
  lead_fcst        = (/          "L",          "L",          "L",          "L",          "L",          "L" /)
  ens_fcst         = (/          "M",          "M",          "M",          "M",          "M",          "M" /)
  lat_fcst         = (/          "Y",          "Y",          "Y",          "Y",          "Y",          "Y" /)
  lon_fcst         = (/          "X",          "X",          "X",          "X",          "X",          "X" /)
  modsnens         = (/           24,           10,           10,           15,           10,            4 /)
  modsnens_fcst    = (/           32,           10,           10,           30,           10,           10 /)
  modsnmons        = (/           10,           12,           12,           12,           12,            9 /)
  mods_byear_hcst  = (/         1982,         1981,         1981,         1991,         1982,         1981 /)
  mods_bmm_hcst    = (/            1,            1,            1,            1,            1,            2 /)
  mods_eyear_hcst  = (/         2010,         2018,         2018,         2020,     cur_year,         2017 /)
  mods_emm_hcst    = (/           12,           12,           12,           12,       cur_mm,            1 /)
  mods_byear_fcst  = (/         2011,         2019,         2019,         2021,     cur_year,         2017 /)
  mods_bmm_fcst    = (/            3,            8,            8,            1,       cur_mm,           11 /)
  mods_eyear_fcst  = (/     cur_year,     cur_year,     cur_year,     cur_year,     cur_year,     cur_year /)
  mods_emm_fcst    = (/       cur_mm,       cur_mm,       cur_mm,       cur_mm,       cur_mm,       cur_mm /)
  mods_fcst_hcst_diff = (/      True,         True,         True,         True,        False,         True /)
  mbeg             = 1
  mend             = 12
  
  lead_time        = 5  ; number of lead times (not including 0)
  
  d1 := conform(mods_bmm_hcst,1,-1) ; The one  has to have the same dimension as other date components
  m0 := conform(mods_bmm_hcst,0,-1) ; The zero has to have the same dimension as other date components
  hcst_bdate = cd_inv_calendar(mods_byear_hcst,mods_bmm_hcst,d1,m0,m0,m0,unitOfTime,0)
  hcst_bdate@units=unitOfTime
  hcst_edate = cd_inv_calendar(mods_eyear_hcst,mods_emm_hcst,d1,m0,m0,m0,unitOfTime,0)
  hcst_edate@units=unitOfTime
  fcst_bdate = cd_inv_calendar(mods_byear_fcst,mods_bmm_fcst,d1,m0,m0,m0,unitOfTime,0)
  fcst_bdate@units=unitOfTime
  fcst_edate = cd_inv_calendar(mods_eyear_fcst,mods_emm_fcst,d1,m0,m0,m0,unitOfTime,0)
  fcst_edate@units=unitOfTime
  fcst_last_date = fcst_edate + lead_time
  fcst_last_date@units=unitOfTime

  maxnens  = max(modsnens) > max(modsnens_fcst) ; The > is greater-than selection operator

  missdbl          = -9.99d8  ; Missing value to use for output files

;-------------------------------------
; Teleconnections Indices information.
;-------------------------------------
  ; PDO hasn't been updated lately, but is important mode.  Perhaps there's a way to calculate it. [removed]
  ; NP is also behind, back in 2019. [removed]
  ; GMSST has been updated to v4 by GISS, but not updated on PSL website. Produced manually for now.
  ; - https://data.giss.nasa.gov/gistemp/tabledata_v4/GLB.Ts+dSST.txt
  ; - Still need to use format of gmsst.data file.  Use saved one provided in package for now.
  ;   - Copy most recent value from the link to gmsst.data.
  ;   - If you add a year row then update the year range in the first line.
  ; Solar can be updated from ftp://ftp.swpc.noaa.gov/pub/weekly/RecentIndices.txt, multiply Observed 10.7 cm by 10.
  ; Trend isn't regularly updated despite its simplicity. I have edited it manually as months since Dec 1947.
  tc_dir       = "$S2S_TCDIR"

  Lst          := getTCIndexList(home_dir+"/data/teleconnections/lists/tc_8_list.txt")
  tc_idxs_disp := Lst[0] ; Names used on plots for display
  tc_idxs      := Lst[1] ; These are the filenames without the .data
  tc_lag       := Lst[2] ; tc_lag is the months behind that index is available.
                         ; Typically 1, but for 3 month averages the lag is 2 and can be longer based on timing of data release.
                         ; - calibration is done according to this expected lag.
                         ; AAO may only update yearly, for now put lag of 5
                         ; CAR_ersst/NTA_ersst/TNI are lag 3, perhaps delayed processing
                         ; GMSST doesn't really update until around the 13th of the month, so might be better to use lag 2 rather than 1
                         ;   if you want to run earlier in the month.

;---------------------------------------
; Basin or region Shapefile information.
;---------------------------------------
  fname_temp_mask  = home_dir+"/data/masks/temporary"   ; Edit this for your system, is reused as a temporary file
                                                        ; No need to create the file, it will be created automatically
  Lst              := getBasinVars(home_dir+"/data/shapefiles/lists/HUC_4_West.txt")
  basin_shpnum     := Lst[0] ; shape number for each polygon in its shapefile
  basin_names      := Lst[1] ; Name you want for each polygon, no spaces
  shape_where_fld  := Lst[2] ; Some field in the shapefile to identify the polygons by.  This is used by GDAL whereas NCL uses the shape number
  shape_where_vals := Lst[3] ; Value of that field that corresponds to the given polygon
  basin_fnames     := Lst[4] ; file path to the shapefile for each polygon
  bsnidxs           := ispan(0,dimsizes(basin_shpnum)-1,1) ; Indices from above to be plotted in maps
  print(basin_shpnum+", "+basin_names+", "+shape_where_fld+", "+shape_where_vals+", "+basin_fnames)

;-----------------------
; Calibration Parameters
;-----------------------
  ; rsq_thresh     = 0.15   ; For NMME
  rsq_thresh       = 0.125  ; For Empirical
  t_sig            = 0.95
  n_idx_max        = 2
  min_idx_pctyr    = 0.8

;----------------------------------------------------
; Image plotting variables.  Not necessary to change.
;----------------------------------------------------
  img_res_x        = 1600
  img_res_y        = 1600
  
  ; color scale and colorbar to use for plotting raw values of variable
  var_scl          = ""
  var_scl@colmap   = "pcp_mo3"
  var_scl@min      =  0.0
  var_scl@max      = 10.0
  var_scl@interval =  0.5
  var_scl@stride   =  2
  var_scl@fmt      = "%4.1f"

  ; color scale and colorbar to use for z-score
  z_score_scl          = ""
  z_score_scl@colmap   = "dry_wet3"
  z_score_scl@min      = -3.0
  z_score_scl@max      =  3.0
  z_score_scl@interval =  0.5
  z_score_scl@stride   =  2
  z_score_scl@fmt      = "%4.1f"
  
  ; color scale and colorbar to use for percentile plots (not used now).
  percentile_scl          = ""
  percentile_scl@colmap   = "dry_wet3"
  percentile_scl@min      = 0.0
  percentile_scl@max      = 1.0
  percentile_scl@interval = 0.05
  percentile_scl@stride   = 2
  percentile_scl@fmt      = "%4.2f"
  
  ALL_colmap_vrf  = "CPC_P_all_verify_2"
  ALL_colmap      = "CPC_P_all"

  ALL_colmap_vrf_cat = "CPC_P_all_verify_cat"
  ALL_colmap_cat     = "CPC_P_all_cat"       

  ; above normal probability scale
  AN_scl          = ""
  AN_scl@colmap   = "CPC_P_abv"
  AN_scl@min      = 0.4
  AN_scl@max      = 0.9
  AN_scl@interval =  0.1
  AN_scl@stride   =  1
  AN_scl@fmt      = "%3.1f"

  ; below normal probability scale
  BN_scl          = ""
  BN_scl@colmap   = "CPC_P_bel"
  BN_scl@min      = 0.4
  BN_scl@max      = 0.9
  BN_scl@interval =  0.1
  BN_scl@stride   =  1
  BN_scl@fmt      = "%3.1f"

  ; near normal probability scale
  NN_scl          = ""
  NN_scl@colmap   = "CPC_NN"
  NN_scl@min      = 0.4
  NN_scl@max      = 0.9
  NN_scl@interval =  0.1
  NN_scl@stride   =  1
  NN_scl@fmt      = "%3.1f"

end
