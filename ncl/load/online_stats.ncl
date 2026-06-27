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

; https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Computing_shifted_data
undef("online_1var_stats_init")
function online_1var_stats_init(Y:numeric)
local  t,N,K,Ey,Ey2,Sy,Sy2,St,St2,Sty,Ymin,Ymax
begin
    ; should ideally keep track of an xofYmin and xofYmax to do things like outlier removed trend
    t = 1 ; This is the abscissa (independent) variable for computing trend, usually time.
          ; This could probably be connected to a coordinate or attribute in Y or passed value
          ; right now this only works when each passed field changes monotonically.
    Ymiss = ismissing(Y)
    N = where(Ymiss,0,1)
    copy_VarMeta_except(Y, N, "_FillValue")
    N@_FillValue = -999

    ; Parameters for shifted variance
    K   = Y
    Ey  = conform_wrap(Y,0D)
    Ey2 = conform_wrap(Y,0D)

    Sy  = where(Ymiss,0,Y) 
    Sy2 = where(Ymiss,0,Y*Y)
    copy_VarMeta(Y, Sy )
    copy_VarMeta(Y, Sy2)

    St   = where(Ymiss,0,t)
    St2  = where(Ymiss,0,t*t)
    copy_VarMeta(Y, St )
    copy_VarMeta(Y, St2)

    Sty  = where(Ymiss,0,Y*t)
    copy_VarMeta(Y, Sty)

    Ymin   = where(Ymiss,Y@_FillValue,Y)
    Ymax   = where(Ymiss,Y@_FillValue,Y)
    copy_VarMeta(Y, Ymin)
    copy_VarMeta(Y, Ymax)

    return([/N,K,Ey,Ey2,Sy,Sy2,Ymin,Ymax,t,St,St2,Sty/])
end

undef("online_1var_stats_add")
procedure online_1var_stats_add(Y:numeric,N:snumeric,K:numeric,Ey:numeric,Ey2:numeric \
                               ,Sy:numeric,Sy2:numeric,Ymin:numeric,Ymax:numeric \
                               ,t:numeric,St:numeric,St2:numeric,Sty:numeric)
local Y_K, Ymiss
begin
    t = t + 1

    Ymiss = ismissing(Y)
    N    = (/ where(Ymiss,N  ,N + 1        ) /)

    Y_K  = Y - K
    Ey   = (/ where(Ymiss,Ey ,Ey  + Y_K    ) /)
    Ey2  = (/ where(Ymiss,Ey2,Ey2 + Y_K*Y_K) /)

    Sy   = (/ where(Ymiss,Sy ,Sy  + Y      ) /)
    Sy2  = (/ where(Ymiss,Sy2,Sy2 + Y*Y    ) /)

    St   = (/ where(Ymiss,St ,St  + t      ) /)
    St2  = (/ where(Ymiss,St2,St2 + t*t    ) /)
    Sty  = (/ where(Ymiss,Sty,Sty + Y*t    ) /)

    Ymin = (/ where(Ymiss,Ymin, where(ismissing(Ymin),Y, where(Y.lt.Ymin,Y,Ymin) ) ) /)
    Ymax = (/ where(Ymiss,Ymax, where(ismissing(Ymax),Y, where(Y.gt.Ymax,Y,Ymax) ) ) /)

    return
end

undef("online_1var_stats_rmv")
procedure online_1var_stats_rmv(Y:numeric,N:snumeric,K:numeric,Ey:numeric,Ey2:numeric \
                               ,Sy:numeric,Sy2:numeric,Ymin:numeric,Ymax:numeric \
                               ,t:numeric,St:numeric,St2:numeric,Sty:numeric)
local Y_K, Ymiss
begin
    t = t - 1

    Ymiss = ismissing(Y)
    N    = (/ where(Ymiss,N  ,N - 1        ) /)

    Y_K  = Y - K
    Ey   = (/ where(Ymiss,Ey ,Ey  - Y_K    ) /)
    Ey2  = (/ where(Ymiss,Ey2,Ey2 - Y_K*Y_K) /)

    Sy   = (/ where(Ymiss,Sy ,Sy  - Y      ) /)
    Sy2  = (/ where(Ymiss,Sy2,Sy2 - Y*Y    ) /)

    St   = (/ where(Ymiss,St ,St  - t      ) /)
    St2  = (/ where(Ymiss,St2,St2 - t*t    ) /)
    Sty  = (/ where(Ymiss,Sty,Sty - Y*t    ) /)
    
    ; Warning: Ymin and Ymax are not valid after use of online_1var_stats_rmv.

    return
end

undef("online_1var_stats_mean")
function online_1var_stats_mean(N:snumeric,K:numeric,Ey:numeric)
local Y, N2
begin
    N2 = where(N.gt.0,N,N@_FillValue)
    Y = K + Ey / todouble(N2)
    copy_VarMeta(Ey,Y)

    return(Y)
end

undef("online_1var_stats_variance")
function online_1var_stats_variance(N:snumeric,Ey:numeric,Ey2:numeric)
local Ndbl, Y
begin
    N2 = where(N.gt.1,N,N@_FillValue) ; N must be at least 2 because of N-1
    Ndbl = todouble(N2)
    Y = (Ey2 - (Ey * Ey) / Ndbl) / (Ndbl - 1)
    copy_VarMeta(Ey,Y)

    return(Y)
end

undef("online_1var_stats_trend")
function online_1var_stats_trend(N:snumeric,Sy:numeric,Sy2:numeric,St:numeric,St2:numeric,Sty:numeric)
local N2, Ndbl, S2tt, S2yy, S2ty, Mt, Ytrend, Yint, rty, SSR, MSE, N_1
begin
    N2   = where(N.gt.2,N,N@_FillValue) ; N must be at least 2 because of N-1
    Ndbl = todouble(N2)

    S2tt = St2 - (St*St)/Ndbl
    S2tt = (/ where(S2tt.gt.0.0,S2tt,S2tt@_FillValue) /)

    S2yy = Sy2 - (Sy*Sy)/Ndbl
    S2yy = (/ where(S2yy.gt.0.0,S2yy,S2yy@_FillValue) /)

    S2ty = Sty - (St*Sy)/Ndbl
    
    Mt = St/Ndbl

    Ytrend = S2ty/S2tt
    Yint   = (Sy - Ytrend*St)/Ndbl

    rty = S2ty/(sqrt(S2yy*S2tt));
    
    SSR = S2yy*(1.0 - rty^2)

    MSE = SSR/(Ndbl-2)
    
    N_1 = 1.0 + 1.0/Ndbl

    copy_VarMeta(Sy, Ytrend)
    copy_VarMeta(Sy, Yint  )
    copy_VarMeta(Sy, rty   )
    copy_VarMeta(Sy, MSE   )
    copy_VarMeta(Sy, N_1   )
    copy_VarMeta(Sy, Mt    )
    copy_VarMeta(Sy, S2tt  )

    ; MSE,N_1,Mt,S2tt can be used for confidence and prediction intervals
    ; confidence interval: +/-tval*sqrt(MSE*(1/N + ((t-Mt)^2)/S2tt))
    ; prediction interval: +/-tval*sqrt(MSE*(N_1 + ((t-Mt)^2)/S2tt))
    return([/Ytrend,Yint,rty,MSE,N_1,Mt,S2tt/])
end

undef("online_1var_stats_mean_naive")
function online_1var_stats_mean_naive(N:snumeric,Sy:numeric)
local Y, N2
begin
    N2 = where(N.gt.0,N,N@_FillValue)
    Y = Sy / todouble(N2)
    copy_VarMeta(Sy,Y)

    return(Y)
end

undef("online_1var_stats_variance_naive")
function online_1var_stats_variance_naive(N:snumeric,Sy:numeric,Sy2:numeric)
local N2, Ndbl, Y
begin
    N2 = where(N.gt.1,N,N@_FillValue) ; N must be at least 2 because of N-1
    Ndbl = todouble(N2)
    Y = (Sy2 - (Sy * Sy) / Ndbl) / (Ndbl - 1)
    copy_VarMeta(Sy,Y)

    return(Y)
end



undef("online_2var_stats_init")
function online_2var_stats_init(Y:numeric,X:numeric)
local  t,N,St,St2,Ky,Ey,Ey2,Sy,Sy2,Sty,Ymin,Ymax,Kx,Ex,Ex2,Sx,Sx2,Stx,Xmin,Xmax,Exy,Sxy
begin
    ; should ideally keep track of an xofYmin and xofYmax to do things like outlier removed trend
    t = 1 ; This is the abscissa (independent) variable for computing trend, usually time.
          ; This could probably be connected to a coordinate or attribute in Y or passed value
          ; right now this only works when each passed field changes monotonically.
    XYmiss = ismissing(Y).or.ismissing(X)
    N = where(XYmiss,0,1)
    copy_VarMeta_except(Y, N, "_FillValue")
    N@_FillValue = -999

    St   = where(XYmiss,0,t)
    St2  = where(XYmiss,0,t*t)
    copy_VarMeta(Y, St )
    copy_VarMeta(Y, St2)

    ; Parameters for shifted variance
    Ky  = Y
    Ey  = conform_wrap(Y,0D)
    Ey2 = conform_wrap(Y,0D)

    Sy  = where(XYmiss,0,Y) 
    Sy2 = where(XYmiss,0,Y*Y)
    copy_VarMeta(Y, Sy )
    copy_VarMeta(Y, Sy2)

    Sty  = where(XYmiss,0,Y*t)
    copy_VarMeta(Y, Sty)

    Ymin   = where(XYmiss,Y@_FillValue,Y)
    Ymax   = where(XYmiss,Y@_FillValue,Y)
    copy_VarMeta(Y, Ymin)
    copy_VarMeta(Y, Ymax)

    ; Parameters for shifted variance
    Kx   = X
    Ex  = conform_wrap(X,0D)
    Ex2 = conform_wrap(X,0D)

    Sx  = where(XYmiss,0,X) 
    Sx2 = where(XYmiss,0,X*X)
    copy_VarMeta(X, Sx )
    copy_VarMeta(X, Sx2)

    Stx  = where(XYmiss,0,X*t)
    copy_VarMeta(X, Stx)

    Xmin   = where(XYmiss,X@_FillValue,X)
    Xmax   = where(XYmiss,X@_FillValue,X)
    copy_VarMeta(X, Xmin)
    copy_VarMeta(X, Xmax)

    Exy = conform_wrap(X,0D)
    Sxy = where(XYmiss,0,X*Y)
    copy_VarMeta(X, Sxy)

    return([/N,t,St,St2,Ky,Ey,Ey2,Sy,Sy2,Ymin,Ymax,Sty,Kx,Ex,Ex2,Sx,Sx2,Xmin,Xmax,Stx,Exy,Sxy/])
end

undef("online_2var_stats_add")
procedure online_2var_stats_add(Y:numeric,X:numeric,N:snumeric,t:numeric,St:numeric,St2:numeric \
                               ,Ky:numeric,Ey:numeric,Ey2:numeric \
                               ,Sy:numeric,Sy2:numeric,Ymin:numeric,Ymax:numeric,Sty:numeric \
                               ,Kx:numeric,Ex:numeric,Ex2:numeric \
                               ,Sx:numeric,Sx2:numeric,Xmin:numeric,Xmax:numeric,Stx:numeric \
                               ,Exy:numeric,Sxy:numeric)
local Y_K, X_K, XYmiss
begin
    t = t + 1

    XYmiss = ismissing(Y).or.ismissing(X)
    N    = (/ where(XYmiss,N  ,N + 1        ) /)

    St   = (/ where(XYmiss,St ,St  + t      ) /)
    St2  = (/ where(XYmiss,St2,St2 + t*t    ) /)

    Y_K  = Y - Ky
    Ey   = (/ where(XYmiss,Ey ,Ey  + Y_K    ) /)
    Ey2  = (/ where(XYmiss,Ey2,Ey2 + Y_K*Y_K) /)

    Sy   = (/ where(XYmiss,Sy ,Sy  + Y      ) /)
    Sy2  = (/ where(XYmiss,Sy2,Sy2 + Y*Y    ) /)

    Sty  = (/ where(XYmiss,Sty,Sty + Y*t    ) /)

    Ymin = (/ where(XYmiss,Ymin, where(ismissing(Ymin),Y, where(Y.lt.Ymin,Y,Ymin) ) ) /)
    Ymax = (/ where(XYmiss,Ymax, where(ismissing(Ymax),Y, where(Y.gt.Ymax,Y,Ymax) ) ) /)

    X_K  = X - Kx
    Ex   = (/ where(XYmiss,Ex ,Ex  + X_K    ) /)
    Ex2  = (/ where(XYmiss,Ex2,Ex2 + X_K*X_K) /)

    Sx   = (/ where(XYmiss,Sx ,Sx  + X      ) /)
    Sx2  = (/ where(XYmiss,Sx2,Sx2 + X*X    ) /)

    Stx  = (/ where(XYmiss,Stx,Stx + X*t    ) /)

    Xmin = (/ where(XYmiss,Xmin, where(ismissing(Xmin),X, where(X.lt.Xmin,X,Xmin) ) ) /)
    Xmax = (/ where(XYmiss,Xmax, where(ismissing(Xmax),X, where(X.gt.Xmax,X,Xmax) ) ) /)

    Exy  = (/ where(XYmiss,Exy,Exy + X_K*Y_K) /)
    Sxy  = (/ where(XYmiss,Sxy,Sxy + X*Y    ) /)

    return
end

undef("online_2var_stats_rmv")
procedure online_2var_stats_rmv(Y:numeric,X:numeric,N:snumeric,t:numeric,St:numeric,St2:numeric \
                               ,Ky:numeric,Ey:numeric,Ey2:numeric \
                               ,Sy:numeric,Sy2:numeric,Ymin:numeric,Ymax:numeric,Sty:numeric \
                               ,Kx:numeric,Ex:numeric,Ex2:numeric \
                               ,Sx:numeric,Sx2:numeric,Xmin:numeric,Xmax:numeric,Stx:numeric \
                               ,Exy:numeric,Sxy:numeric)
local Y_K, X_K, XYmiss
begin
    t = t - 1

    XYmiss = ismissing(Y).or.ismissing(X)
    N    = (/ where(XYmiss,N  ,N - 1        ) /)

    St   = (/ where(XYmiss,St ,St  - t      ) /)
    St2  = (/ where(XYmiss,St2,St2 - t*t    ) /)

    Y_K  = Y - Ky
    Ey   = (/ where(XYmiss,Ey ,Ey  - Y_K    ) /)
    Ey2  = (/ where(XYmiss,Ey2,Ey2 - Y_K*Y_K) /)

    Sy   = (/ where(XYmiss,Sy ,Sy  - Y      ) /)
    Sy2  = (/ where(XYmiss,Sy2,Sy2 - Y*Y    ) /)

    Sty  = (/ where(XYmiss,Sty,Sty - Y*t    ) /)

    X_K  = X - Kx
    Ex   = (/ where(XYmiss,Ex ,Ex  - X_K    ) /)
    Ex2  = (/ where(XYmiss,Ex2,Ex2 - X_K*X_K) /)

    Sx   = (/ where(XYmiss,Sx ,Sx  - X      ) /)
    Sx2  = (/ where(XYmiss,Sx2,Sx2 - X*X    ) /)

    Stx  = (/ where(XYmiss,Stx,Stx - X*t    ) /)

    Exy  = (/ where(XYmiss,Exy,Exy - X_K*Y_K) /)
    Sxy  = (/ where(XYmiss,Sxy,Sxy - X*Y    ) /)
    
    ; Warning: Xmin and Xmax are not valid after use of online_2var_stats_rmv.

    return
end


undef("online_2var_stats_regr_naive")
function online_2var_stats_regr_naive(N:snumeric,Sy:numeric,Sy2:numeric,Sx:numeric,Sx2:numeric,Sxy:numeric)
local N2, Ndbl, S2xx, S2yy, S2xy, Mx, Ytrend, Yint, rxy, SSR, MSE, N_1
begin
    N2   = where(N.gt.2,N,N@_FillValue) ; N must be at least 2 because of N-1
    Ndbl = todouble(N2)

    S2xx = Sx2 - (Sx*Sx)/Ndbl
    S2xx = (/ where(S2xx.gt.0.0,S2xx,S2xx@_FillValue) /)

    S2yy = Sy2 - (Sy*Sy)/Ndbl
    S2yy = (/ where(S2yy.gt.0.0,S2yy,S2yy@_FillValue) /)

    S2xy = Sxy - (Sx*Sy)/Ndbl
    
    Mx = Sx/Ndbl

    Yslope = S2xy/S2xx
    Yint   = (Sy - Yslope*Sx)/Ndbl

    rxy = S2xy/(sqrt(S2yy*S2xx));
    
    SSR = S2yy*(1.0 - rxy^2)

    MSE = SSR/(Ndbl-2)
    
    N_1 = 1.0 + 1.0/Ndbl

    copy_VarMeta(Sy, Yslope)
    copy_VarMeta(Sy, Yint  )
    copy_VarMeta(Sy, rxy   )
    copy_VarMeta(Sy, MSE   )
    copy_VarMeta(Sy, N_1   )
    copy_VarMeta(Sy, Mx    )
    copy_VarMeta(Sy, S2xx  )

    ; MSE,N_1,Mx,S2xx can be used for confidence and prediction intervals
    ; confidence interval: +/-tval*sqrt(MSE*(1/N + ((x-Mx)^2)/S2xx))
    ; prediction interval: +/-tval*sqrt(MSE*(N_1 + ((x-Mx)^2)/S2xx))
    return([/Yslope,Yint,rxy,MSE,N_1,Mx,S2xx/])
end



undef("online_2var_stats_regr")
function online_2var_stats_regr(N:snumeric,Ey:numeric,Ey2:numeric,Ex:numeric,Ex2:numeric,Exy:numeric)
local N2, Ndbl, E2xx, E2yy, E2xy, Mx, Ytrend, Yint, rxy, SSR, MSE, N_1
begin
    N2   = where(N.gt.2,N,N@_FillValue) ; N must be at least 2 because of N-1
    Ndbl = todouble(N2)

    E2xx = Ex2 - (Ex*Ex)/Ndbl
    E2xx = (/ where(E2xx.gt.0.0,E2xx,E2xx@_FillValue) /)

    E2yy = Ey2 - (Ey*Ey)/Ndbl
    E2yy = (/ where(E2yy.gt.0.0,E2yy,E2yy@_FillValue) /)

    E2xy = Exy - (Ex*Ey)/Ndbl
    
    Mx = Kx + Ex/Ndbl

    Yslope = E2xy/E2xx
    Yint   = (Ey - Yslope*Ex)/Ndbl

    rxy = E2xy/(sqrt(E2yy*E2xx));
    
    SSR = E2yy*(1.0 - rxy^2)

    MSE = SSR/(Ndbl-2)
    
    N_1 = 1.0 + 1.0/Ndbl

    copy_VarMeta(Ey, Yslope)
    copy_VarMeta(Ey, Yint  )
    copy_VarMeta(Ey, rxy   )
    copy_VarMeta(Ey, MSE   )
    copy_VarMeta(Ey, N_1   )
    copy_VarMeta(Ey, Mx    )
    copy_VarMeta(Ey, E2xx  )

    ; MSE,N_1,Mx,E2xx can be used for confidence and prediction intervals
    ; confidence interval: +/-tval*sqrt(MSE*(1/N + ((x-Mx)^2)/E2xx))
    ; prediction interval: +/-tval*sqrt(MSE*(N_1 + ((x-Mx)^2)/E2xx))
    return([/Yslope,Yint,rxy,MSE,N_1,Mx,E2xx/])
end

