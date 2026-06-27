; Created by Bill Scheftic

if (.not.isdefined("contrib_declared")) then
 loadscript("$NCARG_ROOT/lib/ncarg/nclex/gsun/gsn_code.ncl")
 loadscript("$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_csm.ncl")
 loadscript("$NCARG_ROOT/lib/ncarg/nclscripts/csm/contributed.ncl")
 contrib_declared = 1
end if

undef("printVarStats")
procedure printVarStats(name:string,X)
begin
    print("")
    print("--------")
    print(""+name)
    print("--------")
    printVarSummary(X)
    print(name+" stats:")
    print("nvalid "+num(.not.ismissing(X)))
    print("nmiss  "+num(ismissing(X)))
    print("nzero  "+num(X.eq.0))
    print("min    "+min(X))
    print("max    "+max(X))
    print("")
end

undef("print_array")
procedure print_array(X,fmt:string)
begin
    printVarSummary(X)
    ncl_c_print_array(X,fmt)
end

undef("print_array_head")
procedure print_array_head(X,head:string,fmt:string)
begin
    print(""+head)
    ncl_c_print_array(X,fmt)
end

; This may be needed to circumvent problems assigning same number or variable to lists multiple times.
undef("copy4list")
function copy4list(val)
begin
  return(val)
end


undef("max2")
function max2(X[1]:snumeric,Y[1]:snumeric)
local maxval
begin
  if (X.gt.Y) then
    maxval = X
  else
    maxval = Y
  end if
  return(maxval)
end

undef("maxN")
function minN(VLst:list)
local V, n
begin
    n = ListCount(VLst)
    V = VLst[0]
    do i=1,n-1
        V = V > VLst[i]
    end do
    return(V)
end

undef("min2")
function min2(X[1]:snumeric,Y[1]:snumeric)
local minval
begin
  if (X.lt.Y) then
    minval = X
  else
    minval = Y
  end if
  return(minval)
end

undef("minN")
function minN(VLst:list)
local V, n
begin
    n = ListCount(VLst)
    V = VLst[0]
    do i=1,n-1
        V = V < VLst[i]
    end do
    return(V)
end


undef("max_difference")
function max_difference(crd[*]:numeric)
local n,dmax
begin
  n       := dimsizes(crd)
  dmax    := max(crd(1:n-1) - crd(0:n-2))
  return(dmax)
end

undef("min_difference")
function min_difference(crd[*]:numeric)
local n,dmin
begin
  n       := dimsizes(crd)
  dmin    := min(crd(1:n-1) - crd(0:n-2))
  return(dmin)
end


undef("lon_0_360")
function lon_0_360(ln_in)
local ln_out
begin
  ln_out := where(ln_in .lt. 0,ln_in + 360,ln_in)
  return(ln_out)
end

undef("lon_n180_180")
function lon_n180_180(ln_in)
local ln_out
begin
  ln_out = where(ln_in .gt. 180,ln_in - 360,ln_in)
  return(ln_out)
end

undef("lon_dom2file")
function lon_dom2file(ln_in,file_lon[*]:numeric)
local ln_out
begin
  if (min(file_lon).lt.0.0) then
    ln_out = lon_n180_180(ln_in)
  else
    ln_out = lon_0_360(ln_in)
  end if
  return(ln_out)
end


undef("logical_to_int")
function logical_to_int(X:logical)
local OUT
begin
  OUT = where(X,1,0)
  copy_VarCoords(X,OUT)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("int_to_logical")
function int_to_logical(X:integer)
local OUT
begin
  OUT = where(X.eq.0,False,True)
  copy_VarCoords(X,OUT)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end

undef("to_Type")
function to_Type(X,type:string)
local OUT
begin
  OUT = totype(X,type)
  copy_VarCoords(X,OUT)
  copy_VarAtts_except(X,OUT,"_FillValue")
  return(OUT)
end


undef("get_rank0")
function get_rank0(IN)
local dsizes,rank
begin
  dsizes = dimsizes(IN)
  rank  = dimsizes(dsizes)
  if ((rank.eq.1).and.(dsizes(0).eq.1)) then
    rank = 0;
  end if

  return(rank)
end


; NEED to figure out why qsort won't load, probably a conflict with my C code
undef("sort1d")
function sort1d(X:snumeric)
local rankX, Y, dsz_X
begin
    rankX = get_rank0(X)
    if (rankX.eq.0) then
        return(X)
    elseif (rankX.eq.1) then
        Y     = totype(ncl_c_qsort(X,0),typeof(X))
    elseif (rankX.gt.1) then
        dsz_X = dimsizes(X)
        Y     = totype(onedtond(ncl_c_qsort(ndtooned(X),0),dsz_X),typeof(X))
    end if
    copy_VarMeta(X,Y)
    return(Y)
end

undef("isintegral")
function isintegral(X)
begin
    return(isint(X).or.isint64(X).or.islong(X).or.isbyte(X).or.isshort(X))
end

undef("isfloating")
function isfloating(X)
begin
    return(isfloat(X).or.isdouble(X))
end

undef("coord_by_stride")
function coord_by_stride(name:string,bcrd:snumeric,ecrd:snumeric,dcrd:snumeric)
local crd
begin
    if (isfloating(bcrd).or.isfloating(ecrd)) then
        crd    = fspan(bcrd,ecrd,round((ecrd - bcrd)/dcrd,3)+1)
    else
        crd    = ispan(bcrd,ecrd,dcrd)
    end if
    crd!0      = name
    crd&$name$ = crd
	return(crd);
end

undef("coord_by_n")
function coord_by_n(name:string,bcrd:snumeric,ecrd:snumeric,n:snumeric)
local crd
begin
    if (isfloating(bcrd).or.isfloating(ecrd)) then
        crd    = fspan(bcrd,ecrd,n)
    else
        crd    = ispan(bcrd,ecrd,(ecrd - bcrd)/(n-1))
    end if
    crd!0      = name
    crd&$name$ = crd
	return(crd);
end

undef("crd_idx")
function crd_idx(val:snumeric,crd[*]:snumeric)
; Calculates an index for value with the coordinate.
; should work on arrays of val
local bcrd, ridx, dcrd, is_out
begin
    if (isEqualSpace(crd,0.00001)) then
        bcrd = crd(0)
        dcrd = crd(1)-bcrd
        ridx = round((val - bcrd)/dcrd,3)
        is_out = (ridx .lt. 0) .or. (ridx .ge. dimsizes(crd))
        if( any( is_out ) ) then
            print("crd_idx: "+val(ind(is_out))+" is not within coordinate range: ("+bcrd+"-"+crd(dimsizes(crd)-1)+")")
            exit()
        end if
        return(ridx)
    else
        print("crd_idx: Coordinate is not equally spaced, can't estimate index value.")
        exit()
    end if
end

undef("crd_idx_chk")
function crd_idx_chk(val:snumeric,crd[*]:snumeric,is_in:logical)
; Calculates an index for value with the coordinate.
; - if val is out of range, is_in will be False
local bcrd, ridx, dcrd
begin
    if (isEqualSpace(crd,0.000001)) then
        bcrd = crd(0)
        dcrd = crd(1)-bcrd
        ridx = round((val - bcrd)/dcrd,3)
        is_in = (ridx .ge. 0) .and. (ridx .lt. dimsizes(crd))
        return(ridx)
    else
        print("crd_idx_chk: Coordinate is not equally spaced, can't estimate index value.")
        exit()
    end if
end

undef("crd_idx_chk_dcrd")
function crd_idx_chk_dcrd(val:snumeric,crd[*]:snumeric,dcrd:snumeric,is_in:logical)
; Calculates an index for value with the coordinate.
; - if val is out of range, is_in will be False
local bcrd, ridx
begin
    if (isEqualSpace(crd,0.000001)) then
        bcrd = crd(0)
        dcrd = crd(1)-bcrd
        ridx = round((val - bcrd)/dcrd,3)
        is_in = (ridx .ge. 0) .and. (ridx .lt. dimsizes(crd))
        return(ridx)
    else
        print("crd_idx_chk: Coordinate is not equally spaced, can't estimate index value.")
        exit()
    end if
end


undef("squeeze_n")
function squeeze_n (X, dims)
; remove singleton dimensions only from dims, keeping others. A singleton dimension is size 1.
; NCL philosophy: do not 'lose' information.
; Adapted from rm_single_dims in contributed.ncl and squeeze in NCL_GETools.ncl
local dimx, dimy, rankx, ranky, keep, dnamx, dnamy, dnamrm, nrm, Y, n
begin
    dimx  = dimsizes(X)
    if (any(dimx(dims).gt.1)) then
        print("squeeze_n: some dims asked to be squeezed have length greater than 1")
        exit()
    end if
    
    rankx = dimsizes(dimx)
    keep  = get1Dindex_Exclude(ispan(0,rankx-1,1),dims) 

    dimy = dimx(keep)
    Y    = reshape(X,dimy)
    
    ; Assign dimensions and coordinates of new array
    dnamx = getvardims(X)
    dnamy = dnamx(keep)
    ranky = dimsizes(keep)
    do n=0,ranky-1
        if (.not.ismissing(dnamy(n))) then
            Y!n = dnamy(n)
            if (iscoord(X, dnamy(n))) then
                Y&$dnamy(n)$ = X&$dnamy(n)$ ; attach coord
            end if
        end if
    end do
    
    ; Assign squeezed dimensions as attributes
    dnamrm = dnamx(dims)
    nrm    = dimsizes(dims)
    do n=0,nrm-1
        if (.not.ismissing(dnamrm(n))) then
            if (iscoord(X, dnamrm(n))) then
                Y@$dnamrm(n)$ = X&$dnamrm(n)$ ; attach singleton coord as attribute @
            end if
        end if
    end do
    
    copy_VarAtts(X,Y)
    return(Y)
end

undef("conform_indices")
function conform_indices(X,dims,b_in[*]:integer,e_in[*]:integer,sk_in[*]:integer)
local rankd,b,e,sk,firsts,lasts,sk0,dSizes,dend,singles,sqdims
begin
    rankd = dimsizes(dims)
    if (dimsizes(b_in).eq.1) then
        b = conform_dims(rankd,b_in,-1)
    else
        b = b_in
    end if
    if (dimsizes(e_in).eq.1) then
        e = conform_dims(rankd,e_in,-1)
    else
        e = e_in
    end if
    if (dimsizes(sk_in).eq.1) then
        sk = conform_dims(rankd,sk_in,-1)
    else
        sk = sk_in
    end if

    firsts =  b .eq. -1
    lasts  =  e .eq. -1
    sk0    = sk .eq.  0

    dSizes = dimsizes(X)
    dend   = dSizes(dims)-1
    
    b  = where(firsts,    0, b )
    e  = where(lasts , dend, e )

    singles = (e.eq.b)

    sqdims = singles.and.sk0

    sk = where(sk0, 1, sk)
    return([/b,e,sk,sqdims/])
end

undef("reorder_as")
function reorder_as(Y,X)
local rankX,rankY,r,Xr
begin
  rankX = get_rank0(X)
  rankY = get_rank0(Y)
  if (rankX.ne.rankY) then
    print("reorder_as: can't reorder X as it has "+rankX+" dims and not the "+rankY+" dims that Y has")
    exit()
  end if
  if (rankX.gt.1) then
    r = getvardims(Y)
  else
    Xr = X
    return(Xr)
  end if

  if (rankX .eq. 2) then
    Xr = X( $r(0)$ | :, $r(1)$ | :)
  elseif (rankX .eq. 3) then
    Xr = X( $r(0)$ | :, $r(1)$ | :, $r(2)$ | :)
  elseif (rankX .eq. 4) then
    Xr = X( $r(0)$ | :, $r(1)$ | :, $r(2)$ | :, $r(3)$ | :)
  elseif (rankX .eq. 5) then
    Xr = X( $r(0)$ | :, $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, $r(4)$ | :)
  elseif (rankX .eq. 6) then
    Xr = X( $r(0)$ | :, $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, $r(4)$ | :, \
            $r(5)$ | :)
  elseif (rankX .eq. 7) then
    Xr = X( $r(0)$ | :, $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, $r(4)$ | :, \
            $r(5)$ | :, $r(6)$ | :)
  elseif (rankX .eq. 8) then
    Xr = X( $r(0)$ | :, $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, $r(4)$ | :, \
            $r(5)$ | :, $r(6)$ | :, $r(7)$ | :)
  elseif (rankX .eq. 9) then
    Xr = X( $r(0)$ | :, $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, $r(4)$ | :, \
            $r(5)$ | :, $r(6)$ | :, $r(7)$ | :, $r(8)$ | :)
  elseif (rankX .eq. 10) then
    Xr = X( $r(0)$ | :, $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, $r(4)$ | :, \
            $r(5)$ | :, $r(6)$ | :, $r(7)$ | :, $r(8)$ | :, $r(9)$ | :)
  else
    print("reorder_as: Can only reorder up to 10 dimensions, input array had "+rankX)
    exit()
  end if

  return(Xr)
end

undef("reorder_names")
function reorder_names(r[*]:string,X)
local rankX,nr,Xr
begin
  rankX = get_rank0(X)
  nr    = dimsizes(r)
  if (rankX.ne.nr) then
    print("reorder_names: can't reorder X as it has "+rankX+" dims and the number of passed dims was "+nr)
    exit()
  end if

  if (rankX.lt.2) then
    Xr = X
    return(Xr)
  end if

  if (rankX .eq. 2) then
    Xr = X( $r(0)$ | :, $r(1)$ | :)
  elseif (rankX .eq. 3) then
    Xr = X( $r(0)$ | :, $r(1)$ | :, $r(2)$ | :)
  elseif (rankX .eq. 4) then
    Xr = X( $r(0)$ | :, $r(1)$ | :, $r(2)$ | :, $r(3)$ | :)
  elseif (rankX .eq. 5) then
    Xr = X( $r(0)$ | :, $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, $r(4)$ | :)
  elseif (rankX .eq. 6) then
    Xr = X( $r(0)$ | :, $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, $r(4)$ | :, \
            $r(5)$ | :)
  elseif (rankX .eq. 7) then
    Xr = X( $r(0)$ | :, $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, $r(4)$ | :, \
            $r(5)$ | :, $r(6)$ | :)
  elseif (rankX .eq. 8) then
    Xr = X( $r(0)$ | :, $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, $r(4)$ | :, \
            $r(5)$ | :, $r(6)$ | :, $r(7)$ | :)
  elseif (rankX .eq. 9) then
    Xr = X( $r(0)$ | :, $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, $r(4)$ | :, \
            $r(5)$ | :, $r(6)$ | :, $r(7)$ | :, $r(8)$ | :)
  elseif (rankX .eq. 10) then
    Xr = X( $r(0)$ | :, $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, $r(4)$ | :, \
            $r(5)$ | :, $r(6)$ | :, $r(7)$ | :, $r(8)$ | :, $r(9)$ | :)
  else
    print("reorder_names: Can only reorder up to 10 dimensions, input array had "+rankX)
    exit()
  end if

  return(Xr)
end

undef("arraylist_append_record")
function arraylist_append_record(VLst:list)
local i,n,OUT
begin
    n   = ListCount(VLst)
    OUT = VLst[0]
    do i=1,n-1
        OUT := array_append_record(OUT,VLst[i],0)
    end do
    return(OUT)
end


undef("fill_up_to_10")
procedure fill_up_to_10(called_by:string, X, x, rankx, dim, b, e)
; Use internally for Pad (extend) which already check sizes and dims
begin
  if (rankx.eq.1) then
      if (dim.ne.0) then
          print(called_by+": For a rank-one array dim must be 0: dim="+dim)
          exit
      end if
      X(0:ntim-1)     = (/ x /) 
  elseif (rankx.eq.2) then
      if (dim.eq.0) then
          X(b:e,:)   = (/ x /)
          copy_VarCoords(x(0,:), X(0,:))
      elseif (dim.eq.1) then
          X(:,b:e)   = (/ x /)
          copy_VarCoords(x(:,0), X(:,0))
      end if
  elseif (rankx.eq.3) then
      if (dim.eq.0) then
          X(b:e,:,:)   = (/ x /)
          copy_VarCoords(x(0,:,:), X(0,:,:))
      elseif (dim.eq.1) then
          X(:,b:e,:)   = (/ x /)
          copy_VarCoords(x(:,0,:), X(:,0,:))
      elseif (dim.eq.2) then
          X(:,:,b:e)   = (/ x /)
          copy_VarCoords(x(:,:,0), X(:,:,0))
      end if
  elseif (rankx.eq.4) then
      if (dim.eq.0) then
          X(b:e,:,:,:)   = (/ x /)
          copy_VarCoords(x(0,:,:,:), X(0,:,:,:))
      elseif (dim.eq.1) then
          X(:,b:e,:,:)   = (/ x /)
          copy_VarCoords(x(:,0,:,:), X(:,0,:,:))
      elseif (dim.eq.2) then
          X(:,:,b:e,:)   = (/ x /)
          copy_VarCoords(x(:,:,0,:), X(:,:,0,:))
      elseif (dim.eq.3) then
          X(:,:,:,b:e)   = (/ x /)
          copy_VarCoords(x(:,:,:,0), X(:,:,:,0))
      end if
  elseif (rankx.eq.5) then
      if (dim.eq.0) then
          X(b:e,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(0,:,:,:,:), X(0,:,:,:,:))
      elseif (dim.eq.1) then
          X(:,b:e,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,0,:,:,:), X(:,0,:,:,:))
      elseif (dim.eq.2) then
          X(:,:,b:e,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,0,:,:), X(:,:,0,:,:))
      elseif (dim.eq.3) then
          X(:,:,:,b:e,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,0,:), X(:,:,:,0,:))
      elseif (dim.eq.4) then
          X(:,:,:,:,b:e)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,0), X(:,:,:,:,0))
      end if
  elseif (rankx.eq.6) then
      if (dim.eq.0) then
          X(b:e,:,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(0,:,:,:,:,:), X(0,:,:,:,:,:))
      elseif (dim.eq.1) then
          X(:,b:e,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,0,:,:,:,:), X(:,0,:,:,:,:))
      elseif (dim.eq.2) then
          X(:,:,b:e,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,0,:,:,:), X(:,:,0,:,:,:))
      elseif (dim.eq.3) then
          X(:,:,:,b:e,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,0,:,:), X(:,:,:,0,:,:))
      elseif (dim.eq.4) then
          X(:,:,:,:,b:e,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,0,:), X(:,:,:,:,0,:))
      elseif (dim.eq.5) then
          X(:,:,:,:,:,b:e)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,:,0), X(:,:,:,:,:,0))
      end if
  elseif (rankx.eq.7) then
      if (dim.eq.0) then
          X(b:e,:,:,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(0,:,:,:,:,:,:), X(0,:,:,:,:,:,:))
      elseif (dim.eq.1) then
          X(:,b:e,:,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,0,:,:,:,:,:), X(:,0,:,:,:,:,:))
      elseif (dim.eq.2) then
          X(:,:,b:e,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,0,:,:,:,:), X(:,:,0,:,:,:,:))
      elseif (dim.eq.3) then
          X(:,:,:,b:e,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,0,:,:,:), X(:,:,:,0,:,:,:))
      elseif (dim.eq.4) then
          X(:,:,:,:,b:e,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,0,:,:), X(:,:,:,:,0,:,:))
      elseif (dim.eq.5) then
          X(:,:,:,:,:,b:e,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,:,0,:), X(:,:,:,:,:,0,:))
      elseif (dim.eq.6) then
          X(:,:,:,:,:,:,b:e)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,:,:,0), X(:,:,:,:,:,:,0))
      end if
  elseif (rankx.eq.8) then
      if (dim.eq.0) then
          X(b:e,:,:,:,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(0,:,:,:,:,:,:,:), X(0,:,:,:,:,:,:,:))
      elseif (dim.eq.1) then
          X(:,b:e,:,:,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,0,:,:,:,:,:,:), X(:,0,:,:,:,:,:,:))
      elseif (dim.eq.2) then
          X(:,:,b:e,:,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,0,:,:,:,:,:), X(:,:,0,:,:,:,:,:))
      elseif (dim.eq.3) then
          X(:,:,:,b:e,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,0,:,:,:,:), X(:,:,:,0,:,:,:,:))
      elseif (dim.eq.4) then
          X(:,:,:,:,b:e,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,0,:,:,:), X(:,:,:,:,0,:,:,:))
      elseif (dim.eq.5) then
          X(:,:,:,:,:,b:e,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,:,0,:,:), X(:,:,:,:,:,0,:,:))
      elseif (dim.eq.6) then
          X(:,:,:,:,:,:,b:e,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,:,:,0,:), X(:,:,:,:,:,:,0,:))
      elseif (dim.eq.7) then
          X(:,:,:,:,:,:,:,b:e)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,:,:,:,0), X(:,:,:,:,:,:,:,0))
      end if
  elseif (rankx.eq.9) then
      if (dim.eq.0) then
          X(b:e,:,:,:,:,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(0,:,:,:,:,:,:,:,:), X(0,:,:,:,:,:,:,:,:))
      elseif (dim.eq.1) then
          X(:,b:e,:,:,:,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,0,:,:,:,:,:,:,:), X(:,0,:,:,:,:,:,:,:))
      elseif (dim.eq.2) then
          X(:,:,b:e,:,:,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,0,:,:,:,:,:,:), X(:,:,0,:,:,:,:,:,:))
      elseif (dim.eq.3) then
          X(:,:,:,b:e,:,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,0,:,:,:,:,:), X(:,:,:,0,:,:,:,:,:))
      elseif (dim.eq.4) then
          X(:,:,:,:,b:e,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,0,:,:,:,:), X(:,:,:,:,0,:,:,:,:))
      elseif (dim.eq.5) then
          X(:,:,:,:,:,b:e,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,:,0,:,:,:), X(:,:,:,:,:,0,:,:,:))
      elseif (dim.eq.6) then
          X(:,:,:,:,:,:,b:e,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,:,:,0,:,:), X(:,:,:,:,:,:,0,:,:))
      elseif (dim.eq.7) then
          X(:,:,:,:,:,:,:,b:e,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,:,:,:,0,:), X(:,:,:,:,:,:,:,0,:))
      elseif (dim.eq.8) then
          X(:,:,:,:,:,:,:,:,b:e)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,:,:,:,:,0), X(:,:,:,:,:,:,:,:,0))
      end if
  elseif (rankx.eq.10) then
      if (dim.eq.0) then
          X(b:e,:,:,:,:,:,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(0,:,:,:,:,:,:,:,:,:), X(0,:,:,:,:,:,:,:,:,:))
      elseif (dim.eq.1) then
          X(:,b:e,:,:,:,:,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,0,:,:,:,:,:,:,:,:), X(:,0,:,:,:,:,:,:,:,:))
      elseif (dim.eq.2) then
          X(:,:,b:e,:,:,:,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,0,:,:,:,:,:,:,:), X(:,:,0,:,:,:,:,:,:,:))
      elseif (dim.eq.3) then
          X(:,:,:,b:e,:,:,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,0,:,:,:,:,:,:), X(:,:,:,0,:,:,:,:,:,:))
      elseif (dim.eq.4) then
          X(:,:,:,:,b:e,:,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,0,:,:,:,:,:), X(:,:,:,:,0,:,:,:,:,:))
      elseif (dim.eq.5) then
          X(:,:,:,:,:,b:e,:,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,:,0,:,:,:,:), X(:,:,:,:,:,0,:,:,:,:))
      elseif (dim.eq.6) then
          X(:,:,:,:,:,:,b:e,:,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,:,:,0,:,:,:), X(:,:,:,:,:,:,0,:,:,:))
      elseif (dim.eq.7) then
          X(:,:,:,:,:,:,:,b:e,:,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,:,:,:,0,:,:), X(:,:,:,:,:,:,:,0,:,:))
      elseif (dim.eq.8) then
          X(:,:,:,:,:,:,:,:,b:e,:)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,:,:,:,:,0,:), X(:,:,:,:,:,:,:,:,0,:))
      elseif (dim.eq.9) then
          X(:,:,:,:,:,:,:,:,:,b:e)   = (/ x /)
          copy_VarCoords(x(:,:,:,:,:,:,:,:,:,0), X(:,:,:,:,:,:,:,:,:,0))
      end if
  else
      print(called_by+": Can't operate on more than 10 dimensions: rank="+rankx)
      exit
  end if

  return
end

undef("dim_pad_extend_n")
function dim_pad_extend_n(x, Next[1]:integer, dim_arg[1])
; Pad (extend) the 'size' of the user specified dimension to  size 'N'
; 'dim' 0 through 9 or named dim_arg is supported.
; 
; Coordinate values (if any) along 'dim' dimension are lost.
; A created dimension name will be given to the expanded dimension.  
;
local dim, dimx, ntim, rankx, NTIM, X, DNAM
begin
  dim = dimnames_to_indexes(x,dim_arg)
  if (dim.gt.9) then
      print("dim_pad_extend_n: dim>9 is not supported: dim="+dim)
      exit
  end if

  dimx  = dimsizes(x)
  rankx = dimsizes(dimx)
  if (dim.ge.rankx) then
      print("dim_pad_extend_n: No dim "+dim+" in x of rank "+rankx)
      exit
  end if

  ntim  = dimx(dim) 
  NTIM  = ntim + Next

  dimx(dim) = NTIM
  X    = new( dimx, typeof(x), getVarFillValue(x))
  copy_VarAtts(x,X)

  fill_up_to_10("dim_pad_extend_n", X, x, rankx, dim, 0, ntim-1)

  DNAM   = "extend_"+Next
  if (isdimnamed(x,dim)) then 
      DNAM = x!dim +"_"+DNAM  
  end if
  X!dim    = DNAM
  X@Next   = Next

  return(X)
end

undef("dim_pad_modulo_n")
function dim_pad_modulo_n(x, Nmod[1]:integer, dim_arg[1])
; Pad (expand) the 'size' of the user specified dimension to get a 'SIZE' such that (SIZE % N)=0 
; 'dim' 0 through 9 or named dim_arg is supported.
; 
; Coordinate values (if any) along 'dim' dimension are lost.
; A created dimension name will be given to the expanded dimension.  
;
local dim, dimx, ntim, rankx, NTIM, X, DNAM
begin
  dim = dimnames_to_indexes(x,dim_arg)
  if (dim.gt.9) then
      print("dim_pad_modulo_n: dim>9 is not supported: dim="+dim)
      exit
  end if

  dimx  = dimsizes(x)
  rankx = dimsizes(dimx)
  if (dim.ge.rankx) then
      print("dim_pad_modulo_n: No dim "+dim+" in x of rank "+rankx)
      exit
  end if

  ntim  = dimx(dim)      ; usually the time dimension
  
  if (ntim%Nmod.eq.0) then
      return(x)
  end if

  if (ntim.lt.Nmod) then
      NTIM = Nmod
  else
      NTIM = (ntim/Nmod)*Nmod + Nmod
  end if

  dimx(dim) = NTIM
  X    = new( dimx, typeof(x), getVarFillValue(x))
  copy_VarAtts(x,X)

  fill_up_to_10("dim_pad_modulo_n", X, x, rankx, dim, 0, ntim-1)

  DNAM   = "modulo_"+Nmod
  if (isdimnamed(x,dim)) then 
      DNAM = x!dim +"_"+DNAM  
  end if
  X!dim    = DNAM
  X@Nmod   = Nmod

  return(X)
end


undef("sub_n_1")
function sub_n_1(X_in,dim_args[*],idx[*]:integer)
local dims,rankd,rank0,mdims,rdims,dNames,r,X,Xr
begin
    dims = dimnames_to_indexes(X_in,dim_args)
    rankd = dimsizes(dims)
    if (rankd .gt. 10) then
        print("sub_n_1: Can only subset up to 10 dimensions, tried to subset "+rankd+" dimensions.")
        exit()
    end if

    rank0 = get_rank0(X_in)
    if ((rank0.eq.0) .or. (dims(0).lt.0)) then
        Xr = X_in
        return(Xr)
    end if

    mdims = get1Dindex_Exclude (ispan(0,rank0-1,1),dims)
    if (ismissing(mdims(0))) then
        rdims = dims
    else
        rdims = array_append_record(dims,mdims,0)
    end if

    dNames = getvardims(X_in)
    r      = dNames(rdims)
    
    X = reorder_names(r,X_in)

    if (rank0 .eq. 1) then
        Xr = X(idx(0))
    elseif (rank0 .eq. 2) then
        if (rankd .eq. 1) then
            Xr = X( idx(0), :)
        elseif (rankd .eq. 2) then
            Xr = X( idx(0), idx(1))
        end if
    elseif (rank0 .eq. 3) then
        if (rankd .eq. 1) then
            Xr = X( idx(0), :, :)
        elseif (rankd .eq. 2) then
            Xr = X( idx(0), idx(1), :)
        elseif (rankd .eq. 3) then
            Xr = X( idx(0), idx(1), idx(2))
        end if
    elseif (rank0 .eq. 4) then
        if (rankd .eq. 1) then
            Xr = X( idx(0), :, :, :)
        elseif (rankd .eq. 2) then
            Xr = X( idx(0), idx(1), :, :)
        elseif (rankd .eq. 3) then
            Xr = X( idx(0), idx(1), idx(2), :)
        elseif (rankd .eq. 4) then
            Xr = X( idx(0), idx(1), idx(2), idx(3))
        end if
    elseif (rank0 .eq. 5) then
        if (rankd .eq. 1) then
            Xr = X( idx(0), :, :, :, :)
        elseif (rankd .eq. 2) then
            Xr = X( idx(0), idx(1), :, :, :)
        elseif (rankd .eq. 3) then
            Xr = X( idx(0), idx(1), idx(2), :, :)
        elseif (rankd .eq. 4) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), :)
        elseif (rankd .eq. 5) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4))
        end if
    elseif (rank0 .eq. 6) then
        if (rankd .eq. 1) then
            Xr = X( idx(0), :, :, :, :, :)
        elseif (rankd .eq. 2) then
            Xr = X( idx(0), idx(1), :, :, :, :)
        elseif (rankd .eq. 3) then
            Xr = X( idx(0), idx(1), idx(2), :, :, :)
        elseif (rankd .eq. 4) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), :, :)
        elseif (rankd .eq. 5) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), :)
        elseif (rankd .eq. 6) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), idx(5))
        end if
    elseif (rank0 .eq. 7) then
        if (rankd .eq. 1) then
            Xr = X( idx(0), :, :, :, :, :, :)
        elseif (rankd .eq. 2) then
            Xr = X( idx(0), idx(1), :, :, :, :, :)
        elseif (rankd .eq. 3) then
            Xr = X( idx(0), idx(1), idx(2), :, :, :, :)
        elseif (rankd .eq. 4) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), :, :, :)
        elseif (rankd .eq. 5) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), :, :)
        elseif (rankd .eq. 6) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), idx(5), :)
        elseif (rankd .eq. 7) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), idx(5), idx(6))
        end if
    elseif (rank0 .eq. 8) then
        if (rankd .eq. 1) then
            Xr = X( idx(0), :, :, :, :, :, :, :)
        elseif (rankd .eq. 2) then
            Xr = X( idx(0), idx(1), :, :, :, :, :, :)
        elseif (rankd .eq. 3) then
            Xr = X( idx(0), idx(1), idx(2), :, :, :, :, :)
        elseif (rankd .eq. 4) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), :, :, :, :)
        elseif (rankd .eq. 5) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), :, :, :)
        elseif (rankd .eq. 6) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), idx(5), :, :)
        elseif (rankd .eq. 7) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), idx(5), idx(6), :)
        elseif (rankd .eq. 8) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), idx(5), idx(6), idx(7))
        end if
    elseif (rank0 .eq. 9) then
        if (rankd .eq. 1) then
            Xr = X( idx(0), :, :, :, :, :, :, :, :)
        elseif (rankd .eq. 2) then
            Xr = X( idx(0), idx(1), :, :, :, :, :, :, :)
        elseif (rankd .eq. 3) then
            Xr = X( idx(0), idx(1), idx(2), :, :, :, :, :, :)
        elseif (rankd .eq. 4) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), :, :, :, :, :)
        elseif (rankd .eq. 5) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), :, :, :, :)
        elseif (rankd .eq. 6) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), idx(5), :, :, :)
        elseif (rankd .eq. 7) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), idx(5), idx(6), :, :)
        elseif (rankd .eq. 8) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), idx(5), idx(6), idx(7), :)
        elseif (rankd .eq. 9) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), idx(5), idx(6), idx(7), idx(8))
        end if
    elseif (rank0 .eq. 10) then
        if (rankd .eq. 1) then
            Xr = X( idx(0), :, :, :, :, :, :, :, :, :)
        elseif (rankd .eq. 2) then
            Xr = X( idx(0), idx(1), :, :, :, :, :, :, :, :)
        elseif (rankd .eq. 3) then
            Xr = X( idx(0), idx(1), idx(2), :, :, :, :, :, :, :)
        elseif (rankd .eq. 4) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), :, :, :, :, :, :)
        elseif (rankd .eq. 5) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), :, :, :, :, :)
        elseif (rankd .eq. 6) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), idx(5), :, :, :, :)
        elseif (rankd .eq. 7) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), idx(5), idx(6), :, :, :)
        elseif (rankd .eq. 8) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), idx(5), idx(6), idx(7), :, :)
        elseif (rankd .eq. 9) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), idx(5), idx(6), idx(7), idx(8), :)
        elseif (rankd .eq. 10) then
            Xr = X( idx(0), idx(1), idx(2), idx(3), idx(4), idx(5), idx(6), idx(7), idx(8), idx(9))
        end if
    else
        print("sub_n_1: Can only reorder up to 10 dimensions, input array had "+rank0+" dimensions.")
        exit()
    end if

    return(Xr)
end

undef("sub_n")
function sub_n(X_in,dim_args[*],b_in[*]:integer,e_in[*]:integer,sk_in[*]:integer)
; X             : Input Variable
; dim_args[*]   : dimensions to subset, by name or number but not both
; b[*]:integer  : beginning of slice (-1 for empty, start)
; e[*]:integer  : end of slice (-1 for empty, end)
; sk[*]:integer : stride of slice (0 to squeeze single dim out)
; Ex: X(x | 1, y | :, z | :) would be 
;     sub_n(X,"x",1,1,0)
;
;     X(x | ::-2, y | 1:4, z | 3) would be 
;     sub_n(X,(/"x","y","z"/), \
;             (/ -1,  1,  3/), \
;             (/ -1,  4,  3/), \
;             (/ -2,  1,  0/))
local dims,rankd,rank0,mdims,rdims,iLst,b,e,sk,sqdims,dNames,r,X,Xr
begin
    dims = dimnames_to_indexes(X_in,dim_args)
    rankd = dimsizes(dims)
    if (rankd .gt. 10) then
        print("sub_n: Can only subset up to 10 dimensions, tried to subset "+rankd+" dimensions.")
        exit()
    end if
    
    rank0 = get_rank0(X_in)
    if ((rank0.eq.0) .or. (dims(0).lt.0)) then
        Xr = X_in
        return(Xr)
    end if

    mdims = get1Dindex_Exclude (ispan(0,rank0-1,1),dims)
    if (ismissing(mdims(0))) then
        rdims = dims
    else
        rdims = array_append_record(dims,mdims,0)
    end if

    iLst   = conform_indices(X_in,dims,b_in,e_in,sk_in)
    b      = iLst[0]
    e      = iLst[1]
    sk     = iLst[2]
    sqdims = iLst[3]

    dNames = getvardims(X_in)
    r      = dNames(rdims)
    
    X = reorder_names(r,X_in)

    if (rank0 .eq. 1) then
        Xr = X(b(0):e(0):sk(0))
    elseif (rank0 .eq. 2) then
        if (rankd .eq. 1) then
            Xr = X( b(0):e(0):sk(0), :)
        elseif (rankd .eq. 2) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1))
        end if
    elseif (rank0 .eq. 3) then
        if (rankd .eq. 1) then
            Xr = X( b(0):e(0):sk(0), :, :)
        elseif (rankd .eq. 2) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), :)
        elseif (rankd .eq. 3) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2))
        end if
    elseif (rank0 .eq. 4) then
        if (rankd .eq. 1) then
            Xr = X( b(0):e(0):sk(0), :, :, :)
        elseif (rankd .eq. 2) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), :, :)
        elseif (rankd .eq. 3) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), :)
        elseif (rankd .eq. 4) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3))
        end if
    elseif (rank0 .eq. 5) then
        if (rankd .eq. 1) then
            Xr = X( b(0):e(0):sk(0), :, :, :, :)
        elseif (rankd .eq. 2) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), :, :, :)
        elseif (rankd .eq. 3) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), :, :)
        elseif (rankd .eq. 4) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), :)
        elseif (rankd .eq. 5) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4))
        end if
    elseif (rank0 .eq. 6) then
        if (rankd .eq. 1) then
            Xr = X( b(0):e(0):sk(0), :, :, :, :, :)
        elseif (rankd .eq. 2) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), :, :, :, :)
        elseif (rankd .eq. 3) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), :, :, :)
        elseif (rankd .eq. 4) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), :, :)
        elseif (rankd .eq. 5) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), :)
        elseif (rankd .eq. 6) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), \
                    b(5):e(5):sk(5))
        end if
    elseif (rank0 .eq. 7) then
        if (rankd .eq. 1) then
            Xr = X( b(0):e(0):sk(0), :, :, :, :, :, :)
        elseif (rankd .eq. 2) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), :, :, :, :, :)
        elseif (rankd .eq. 3) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), :, :, :, :)
        elseif (rankd .eq. 4) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), :, :, :)
        elseif (rankd .eq. 5) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), :, :)
        elseif (rankd .eq. 6) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), \
                    b(5):e(5):sk(5), :)
        elseif (rankd .eq. 7) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), \
                    b(5):e(5):sk(5), b(6):e(6):sk(6))
        end if
    elseif (rank0 .eq. 8) then
        if (rankd .eq. 1) then
            Xr = X( b(0):e(0):sk(0), :, :, :, :, :, :, :)
        elseif (rankd .eq. 2) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), :, :, :, :, :, :)
        elseif (rankd .eq. 3) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), :, :, :, :, :)
        elseif (rankd .eq. 4) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), :, :, :, :)
        elseif (rankd .eq. 5) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), :, :, :)
        elseif (rankd .eq. 6) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), \
                    b(5):e(5):sk(5), :, :)
        elseif (rankd .eq. 7) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), \
                    b(5):e(5):sk(5), b(6):e(6):sk(6), :)
        elseif (rankd .eq. 8) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), \
                    b(5):e(5):sk(5), b(6):e(6):sk(6), b(7):e(7):sk(7))
        end if
    elseif (rank0 .eq. 9) then
        if (rankd .eq. 1) then
            Xr = X( b(0):e(0):sk(0), :, :, :, :, :, :, :, :)
        elseif (rankd .eq. 2) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), :, :, :, :, :, :, :)
        elseif (rankd .eq. 3) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), :, :, :, :, :, :)
        elseif (rankd .eq. 4) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), :, :, :, :, :)
        elseif (rankd .eq. 5) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), :, :, :, :)
        elseif (rankd .eq. 6) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), \
                    b(5):e(5):sk(5), :, :, :)
        elseif (rankd .eq. 7) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), \
                    b(5):e(5):sk(5), b(6):e(6):sk(6), :, :)
        elseif (rankd .eq. 8) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), \
                    b(5):e(5):sk(5), b(6):e(6):sk(6), b(7):e(7):sk(7), :)
        elseif (rankd .eq. 9) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), \
                    b(5):e(5):sk(5), b(6):e(6):sk(6), b(7):e(7):sk(7), b(8):e(8):sk(8))
        end if
    elseif (rank0 .eq. 10) then
        if (rankd .eq. 1) then
            Xr = X( b(0):e(0):sk(0), :, :, :, :, :, :, :, :, :)
        elseif (rankd .eq. 2) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), :, :, :, :, :, :, :, :)
        elseif (rankd .eq. 3) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), :, :, :, :, :, :, :)
        elseif (rankd .eq. 4) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), :, :, :, :, :, :)
        elseif (rankd .eq. 5) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), :, :, :, :, :)
        elseif (rankd .eq. 6) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), \
                    b(5):e(5):sk(5), :, :, :, :)
        elseif (rankd .eq. 7) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), \
                    b(5):e(5):sk(5), b(6):e(6):sk(6), :, :, :)
        elseif (rankd .eq. 8) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), \
                    b(5):e(5):sk(5), b(6):e(6):sk(6), b(7):e(7):sk(7), :, :)
        elseif (rankd .eq. 9) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), \
                    b(5):e(5):sk(5), b(6):e(6):sk(6), b(7):e(7):sk(7), b(8):e(8):sk(8), :)
        elseif (rankd .eq. 10) then
            Xr = X( b(0):e(0):sk(0), b(1):e(1):sk(1), b(2):e(2):sk(2), b(3):e(3):sk(3), b(4):e(4):sk(4), \
                    b(5):e(5):sk(5), b(6):e(6):sk(6), b(7):e(7):sk(7), b(8):e(8):sk(8), b(9):e(9):sk(9))
        end if
    else
        print("sub_n: Can only reorder up to 10 dimensions, input array had "+rank0+" dimensions.")
        exit()
    end if

    Xr := reorder_names(dNames,Xr)
    if (any(sqdims)) then
        Xr := squeeze_n(Xr,dims(ind(sqdims)))
    end if

    return(Xr)
end

undef("sub_n_crd")
function sub_n_crd(X,dim_args[*],bcrd[*]:snumeric,ecrd[*]:snumeric,sk[*]:integer)
; Array should maintain same number of dimensions even if some are single element
local ncrd,b,e,crd,i
begin
    ncrd = dimsizes(dim_args)
    b    = new(ncrd,integer)
    e    = new(ncrd,integer)
    do i=0,ncrd-1
        crd := X&$dim_args(i)$
        b(i) = crd_idx(bcrd(i),crd)
        e(i) = crd_idx(ecrd(i),crd)
    end do
    return(sub_n(X,dim_args,b,e,sk))
end

undef("sub_n_1crd")
function sub_n_1crd(X,dim_args[*],bcrd[*]:snumeric)
; Array should be reduced by number of dimensions subset
local ncrd,b,crd,i
begin
    ncrd = dimsizes(dim_args)
    b  = new(ncrd,integer)
    do i=0,ncrd-1
        crd := X&$dim_args(i)$
        b(i) = crd_idx(bcrd(i),crd)
    end do
    return(sub_n_1(X,dim_args,b))
end

undef("asgn_to_1")
procedure asgn_to_1(X,dim_args[*],idx[*]:integer,Y_in)
local dims,rankd,rank0,mdims,rdims,dNames,r,Y,rankY,dnm_Y,rY_dims1,rY
begin
    dims = dimnames_to_indexes(X,dim_args)
    rankd = dimsizes(dims)
    if (rankd .gt. 3) then
        print("asgn_to_1: Can only subset up to 3 dimensions, tried to subset "+rankd+" dimensions.")
        exit()
    end if
    
    rank0 = get_rank0(X)
    if ((rank0.eq.0) .or. (dims(0).lt.0)) then
        X = (/ Y_in /)
        return(X)
    end if

    mdims = get1Dindex_Exclude (ispan(0,rank0-1,1),dims)
    if (ismissing(mdims(0))) then
        rdims = dims
    else
        rdims = array_append_record(dims,mdims,0)
    end if

    dNames = getvardims(X)
    r      = dNames(rdims)
    rankY = get_rank0(Y_in)
    if (rankY .gt. 0) then
        if (all(isdimnamed(Y_in,-1))) then
            dnm_Y = getvardims(Y_in)
            rY_dims1 = get1Dindex(r,dnm_Y)
            if (any(ismissing(rY_dims1))) then
                print("asgn_to_1: some dimensions("+str_join(dnm_Y(ind(ismissing(rY_dims1)))," ")+") of Y are not in X; cannot be assigned.")
                exit()
            end if
            rY = r(sort1d(rY_dims1))
            Y  = reorder_names(rY,Y_in)
        else
            print("asgn_to_1: all dimensions must be named.")
            exit()
        end if
    else
        Y = Y_in
    end if

    if (rank0 .eq. 1) then
        X( idx(0) ) = (/ Y /)
    elseif (rank0 .eq. 2) then
        if (rankd .eq. 1) then
            X( $r(0)$ | idx(0), $r(1)$ | :) \
            = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | idx(0), $r(1)$ | idx(1)) \
            = (/ Y /)
        end if
    elseif (rank0 .eq. 3) then
        if (rankd .eq. 1) then
            X( $r(0)$ | idx(0), $r(1)$ | :, $r(2)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | idx(0), $r(1)$ | idx(1), $r(2)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 3) then
            X( $r(0)$ | idx(0), $r(1)$ | idx(1), $r(2)$ | idx(2)) \
               = (/ Y /)
        end if
    elseif (rank0 .eq. 4) then
        if (rankd .eq. 1) then
            X( $r(0)$ | idx(0), $r(1)$ | :, $r(2)$ | :, $r(3)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | idx(0), $r(1)$ | idx(1), $r(2)$ | :, $r(3)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 3) then
            X( $r(0)$ | idx(0), $r(1)$ | idx(1), $r(2)$ | idx(2), $r(3)$ | :) \
               = (/ Y /)
        end if
    elseif (rank0 .eq. 5) then
        if (rankd .eq. 1) then
            X( $r(0)$ | idx(0), $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, $r(4)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | idx(0), $r(1)$ | idx(1), $r(2)$ | :, $r(3)$ | :, $r(4)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 3) then
            X( $r(0)$ | idx(0), $r(1)$ | idx(1), $r(2)$ | idx(2), $r(3)$ | :, $r(4)$ | :) \
               = (/ Y /)
        end if
    elseif (rank0 .eq. 6) then
        if (rankd .eq. 1) then
            X( $r(0)$ | idx(0), $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | idx(0), $r(1)$ | idx(1), $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 3) then
            X( $r(0)$ | idx(0), $r(1)$ | idx(1), $r(2)$ | idx(2), $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :) \
               = (/ Y /)
        end if
    elseif (rank0 .eq. 7) then
        if (rankd .eq. 1) then
            X( $r(0)$ | idx(0), $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | idx(0), $r(1)$ | idx(1), $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 3) then
            X( $r(0)$ | idx(0), $r(1)$ | idx(1), $r(2)$ | idx(2), $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :) \
               = (/ Y /)
        end if
    elseif (rank0 .eq. 8) then
        if (rankd .eq. 1) then
            X( $r(0)$ | idx(0), $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | idx(0), $r(1)$ | idx(1), $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 3) then
            X( $r(0)$ | idx(0), $r(1)$ | idx(1), $r(2)$ | idx(2), $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :) \
               = (/ Y /)
        end if
    elseif (rank0 .eq. 9) then
        if (rankd .eq. 1) then
            X( $r(0)$ | idx(0), $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :, \
               $r(8)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | idx(0), $r(1)$ | idx(1), $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :, \
               $r(8)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 3) then
            X( $r(0)$ | idx(0), $r(1)$ | idx(1), $r(2)$ | idx(2), $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :, \
               $r(8)$ | :) \
               = (/ Y /)
        end if
    elseif (rank0 .eq. 10) then
        if (rankd .eq. 1) then
            X( $r(0)$ | idx(0), $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :, \
               $r(8)$ | :, $r(9)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | idx(0), $r(1)$ | idx(1), $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :, \
               $r(8)$ | :, $r(9)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 3) then
            X( $r(0)$ | idx(0), $r(1)$ | idx(1), $r(2)$ | idx(2), $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :, \
               $r(8)$ | :, $r(9)$ | :) \
               = (/ Y /)
        end if
    else
        print("asgn_to_1 error: Can only reorder up to 10 dimensions, input array had "+rank0+" dimensions.")
        exit()
    end if

    return
end

undef("asgn_to")
procedure asgn_to(X,dim_args[*],b_in[*]:integer,e_in[*]:integer,sk_in[*]:integer,Y_in)
local dims,rankd,rank0,mdims,rdims,iLst,b,e,sk,dNames,r,Y
begin
    dims = dimnames_to_indexes(X,dim_args)
    rankd = dimsizes(dims)
    if (rankd .gt. 3) then
        print("asgn_to: Can only subset up to 3 dimensions, tried to subset "+rankd+" dimensions.")
        exit()
    end if
    
    rank0 = get_rank0(X)
    if ((rank0.eq.0) .or. (dims(0).lt.0)) then
        X = (/ Y_in /)
        return
    end if

    mdims = get1Dindex_Exclude (ispan(0,rank0-1,1),dims)
    if (ismissing(mdims(0))) then
        rdims = dims
    else
        rdims = array_append_record(dims,mdims,0)
    end if

    iLst   = conform_indices(X,dims,b_in,e_in,sk_in)
    b      = iLst[0]
    e      = iLst[1]
    sk     = iLst[2]

    dNames = getvardims(X)
    r      = dNames(rdims)
    if (get_rank0(Y_in) .gt. 0) then
        if (all(isdimnamed(Y_in,-1))) then
            Y = reorder_names(r,Y_in)
        else
            print("asgn_to: all dimensions must be named.")
            exit()
        end if
    else
        Y = Y_in
    end if

    if (rank0 .eq. 1) then
        X( b(0):e(0):sk(0)) = (/ Y /)
    elseif (rank0 .eq. 2) then
        if (rankd .eq. 1) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | b(1):e(1):sk(1)) \
               = (/ Y /)
        end if
    elseif (rank0 .eq. 3) then
        if (rankd .eq. 1) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | :, $r(2)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | b(1):e(1):sk(1), $r(2)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 3) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | b(1):e(1):sk(1), $r(2)$ | b(2):e(2):sk(2)) \
               = (/ Y /)
        end if
    elseif (rank0 .eq. 4) then
        if (rankd .eq. 1) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | :, $r(2)$ | :, $r(3)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | b(1):e(1):sk(1), $r(2)$ | :, $r(3)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 3) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | b(1):e(1):sk(1), $r(2)$ | b(2):e(2):sk(2), $r(3)$ | :) \
               = (/ Y /)
        end if
    elseif (rank0 .eq. 5) then
        if (rankd .eq. 1) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, $r(4)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | b(1):e(1):sk(1), $r(2)$ | :, $r(3)$ | :, $r(4)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 3) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | b(1):e(1):sk(1), $r(2)$ | b(2):e(2):sk(2), $r(3)$ | :, $r(4)$ | :) \
               = (/ Y /)
        end if
    elseif (rank0 .eq. 6) then
        if (rankd .eq. 1) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | b(1):e(1):sk(1), $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 3) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | b(1):e(1):sk(1), $r(2)$ | b(2):e(2):sk(2), $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :) \
               = (/ Y /)
        end if
    elseif (rank0 .eq. 7) then
        if (rankd .eq. 1) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | b(1):e(1):sk(1), $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 3) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | b(1):e(1):sk(1), $r(2)$ | b(2):e(2):sk(2), $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :) \
               = (/ Y /)
        end if
    elseif (rank0 .eq. 8) then
        if (rankd .eq. 1) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | b(1):e(1):sk(1), $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 3) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | b(1):e(1):sk(1), $r(2)$ | b(2):e(2):sk(2), $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :) \
               = (/ Y /)
        end if
    elseif (rank0 .eq. 9) then
        if (rankd .eq. 1) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :, \
               $r(8)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | b(1):e(1):sk(1), $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :, \
               $r(8)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 3) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | b(1):e(1):sk(1), $r(2)$ | b(2):e(2):sk(2), $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :, \
               $r(8)$ | :) \
               = (/ Y /)
        end if
    elseif (rank0 .eq. 10) then
        if (rankd .eq. 1) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | :, $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :, \
               $r(8)$ | :, $r(9)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 2) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | b(1):e(1):sk(1), $r(2)$ | :, $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :, \
               $r(8)$ | :, $r(9)$ | :) \
               = (/ Y /)
        elseif (rankd .eq. 3) then
            X( $r(0)$ | b(0):e(0):sk(0), $r(1)$ | b(1):e(1):sk(1), $r(2)$ | b(2):e(2):sk(2), $r(3)$ | :, \
               $r(4)$ | :, $r(5)$ | :, $r(6)$ | :, $r(7)$ | :, \
               $r(8)$ | :, $r(9)$ | :) \
               = (/ Y /)
        end if
    else
        print("asgn_to: Can only reorder up to 10 dimensions, input array had "+rank0+" dimensions.")
        exit()
    end if

    return
end

undef("asgn_to_1crd")
procedure asgn_to_1crd(X,dim_args[*],bcrd[*]:snumeric,Y_in)
; Array should be reduced by number of dimensions subset
local r,ncrd,b,crd,i
begin
    ncrd = dimsizes(dim_args)
    b  = new(ncrd,integer)
    do i=0,ncrd-1
        crd := X&$dim_args(i)$
        b(i) = crd_idx(bcrd(i),crd)
    end do
    asgn_to_1(X,dim_args,b,Y_in)
    return
end

undef("asgn_to_crd")
procedure asgn_to_crd(X,dim_args[*],bcrd[*]:snumeric,ecrd[*]:snumeric,sk[*]:integer,Y_in)
; Array should maintain same number of dimensions even if some are single element
local r,ncrd,b,e,crd,i
begin
    ncrd = dimsizes(dim_args)
    b  = new(ncrd,integer)
    e  = new(ncrd,integer)
    do i=0,ncrd-1
        crd := X&$dim_args(i)$
        b(i) = crd_idx(bcrd(i),crd)
        e(i) = crd_idx(ecrd(i),crd)
    end do
    asgn_to(X,dim_args,b,e,sk,Y_in)
    return
end

undef("sub_n_crd_pad")
function sub_n_crd_pad(X,dim_args[*],bcrd[*]:snumeric,ecrd[*]:snumeric,sk[*]:integer)
; Extract coordinates from array and pad missing for coordinates not available.
local dims,r,dnms,ncrd,b,e,isb,ise,isin,any_is_out,crd,dsz_dims,dsz_X,dsz_Xr,Xr,dend,b2,e2,b3,e3,i
begin
    dims  = dimnames_to_indexes(X,dim_args)
    r     = getvardims(X)
    dnms  = r(dims) ; dim_args is likely a string but not guaranteed, so we get the dimension names back.

    ncrd  = dimsizes(dims)
    b     = new(ncrd,integer)
    e     = new(ncrd,integer)
    isb   = new(ncrd,logical)
    ise   = new(ncrd,logical)
    isin  = new(ncrd,logical)
    any_is_out = False
    do i=0,ncrd-1
        crd    := X&$r(dims(i))$
        b(i)    = crd_idx_chk(bcrd(i),crd,isb(i))
        e(i)    = crd_idx_chk(ecrd(i),crd,ise(i))
        isin(i) = isb(i) .and. ise(i)
        if (.not.isin(i)) then
            any_is_out = True
        end if
    end do

    if (any_is_out) then
        dsz_dims    = e - b + 1 ; not accounting for skip
        dsz_X       = dimsizes(X)
        dsz_Xr       = dsz_X
        dsz_Xr(dims) = dsz_dims
        
        Xr = new(dsz_Xr,typeof(X),getVarFillValue(X))
        copy_VarCoords_not_n(X,Xr,dims)
        do i=0,ncrd-1
            Xr!dims(i)   = dnms(i)
            Xr&$dnms(i)$ = totype( fspan(bcrd(i),ecrd(i),dsz_dims(i)), typeof(X&$dnms(i)$) )
        end do
        
        dend   = dsz_X(dims)-1

        b2 = where(isb,  b, 0   )
        e2 = where(ise , e, dend)
        
        b3 = b2 - b
        e3 = e2 - b

        asgn_to(Xr,dims,b3,e3,sk,sub_n(X,dims,b2,e2,sk))
    else
        Xr = sub_n(X,dims,b,e,sk)
    end if
    return(Xr)
end


undef("DimsFromNames2")
function DimsFromNames2(dNames:string,dim_args[*]:string)
local i,id,nout,rank,outdims
begin
    if (dim_args(0).eq."none") then
        return(-1)
    end if

    nout    = dimsizes(dim_args)
    rank    = dimsizes(dNames)
    outdims = new(nout,integer,-1)

    do i =0,nout-1
    do id=0,rank-1
        if (.not.ismissing(dNames(id))) then
        if (dNames(id).eq.dim_args(i)) then
            outdims(i) = id
        end if
        end if
    end do
    end do

    return(outdims)
end

; look at dimnames_to_indexes which does something similar and will even pass numbered dimensions.
undef("DimsFromNames")
function DimsFromNames(invar,dim_args[*]:string)
local dNames
begin
    dNames  = getvardims(invar)

    return(DimsFromNames2(dNames,dim_args))
end

undef("DimsFromNames_trimmed")
function DimsFromNames_trimmed(invar,dim_args[*]:string)
local dims
begin
    dims  = DimsFromNames(invar,dim_args)
    dims := dims(get1Dindex_Exclude(dims,-1))
    return(dims)
end

undef("DimsFromNames2_trimmed")
function DimsFromNames2_trimmed(dNames:string,dim_args[*]:string)
local dims
begin
    dims  = DimsFromNames2(dNames,dim_args)
    dims := dims(get1Dindex_Exclude(dims,-1))
    return(dims)
end


undef("dims2beg")
function dims2beg(X,dim_args[*])
local rank0,dNames,Xr,alldims,dims,mdims,rdims
begin
  rank0 = get_rank0(X)
  if (rank0.gt.1) then
    dNames = getvardims(X)
  else
    Xr = X
    return(Xr)
  end if
  
  alldims = ispan(0,rank0-1,1)
  dims    = DimsFromNames2(dNames,dim_args)
  if (dims(0).lt.0) then
    Xr = X
    return(Xr)
  else
    mdims = get1Dindex_Exclude (alldims,dims)
    if (ismissing(mdims(0))) then
      rdims = dims
    else
      rdims = array_append_record(dims,mdims,0)
    end if
  end if

  Xr = reorder_names(dNames(rdims),X)

  return(Xr)
end

undef("dims2end")
function dims2end(X,dim_args[*]:string)
local rank0,dNames,Xr,alldims,dims,mdims,rdims
begin
  rank0 = get_rank0(X)
  if (rank0.gt.1) then
    dNames = getvardims(X)
  else
    Xr = X
    return(Xr)
  end if
  
  alldims = ispan(0,rank0-1,1)
  dims    = DimsFromNames2(dNames,dim_args)
  if (dims(0).lt.0) then
    rdims = alldims
  else
    mdims = get1Dindex_Exclude (alldims,dims)
    if (ismissing(mdims(0))) then
      rdims = dims
    else
      rdims = array_append_record(mdims,dims,0)
    end if
  end if

  Xr = reorder_names(dNames(rdims),X)

  return(Xr)
end

undef("rename_dims")
procedure rename_dims(var,dimsfro:string,dimsto:string) 
local ids,id,id_f,rfrom,rto
begin
    ids   = DimsFromNames(var,dimsfro)
    rfrom = dimsizes(dimsfro)
    rto   = dimsizes(dimsto)
    if (rfrom.eq.rto) then
      do id=0,rfrom-1
        if (.not.ismissing(ids(id))) then
          id_f     = ids(id)
          var!id_f = dimsto(id)
        end if
      end do
    else
      print("rename_dims: # of dims renamed must be equal, rfrom="+rfrom+", rto="+rto)
    end if
end


; undef("getvar_dims_coords")
; function getvar_dims_coords(X)
; local rank0,dList,id
; begin
;     rank0  = get_rank0(X)
;     dNames = getvardims(X)
;     dims   = ind(.not.ismissing(dNames))
;     if (rank0.gt.0) then
;         if (.not.all(ismissing(dims)))then
;             ndims = dimsizes(dims)
;             do id=0,ndims-1
;                 id_c = dims(id)
;                 if (iscoord(X,X!id_c))then
;                     dNames(id_c)@coord = X&$X!id_c$
;                 end if
;             end do
;         end if
;     end if
; 
;     return(dNames)
; end



undef("subList")
function subList(Lst:list,idx[*]:integer)
local oLst,rank,id,id_f
begin
  oLst := NewList("fifo")
  if (.not.ismissing(idx(0))) then
    if (idx(0).gt.-1) then
      rank  = dimsizes(idx)
      do id=0,rank-1
        ListAppend(oLst,Lst[idx(id)])
      end do
    end if
  end if
  return oLst
end


; Applies selected name and coordinate dims to all dims of X
undef("copy_Coords_Fro")
procedure copy_Coords_Fro(dNames[*]:string,dList:list,var_to,dims_fro[*]:integer)
local rank,id,id_f
begin
  if (.not.ismissing(dims_fro(0))) then
  if (dims_fro(0).gt.-1) then
    rank  = dimsizes(dims_fro)
    if (.not.all(ismissing(dNames))) then
      do id=0,rank-1
        id_f = dims_fro(id)
        if (.not.ismissing(dNames(id_f))) then
            var_to!id = dNames(id_f)
            var_to&$var_to!id$ = dList[id_f]
        end if 
      end do
    end if
  end if
  end if
end

; Applies all names and coordinates to selected dims of X
undef("copy_Coords_To")
procedure copy_Coords_To(dNames[*]:string,dList:list,var_to,dims_to[*]:integer)
local rank,id,id_t
begin
  if (.not.ismissing(dims_to(0))) then
  if (dims_to(0).gt.-1) then
    rank  = dimsizes(dims_to)
    if (.not.all(ismissing(dNames))) then
      do id=0,rank-1
        id_t = dims_to(id)
        if (.not.ismissing(dNames(id))) then
            var_to!id_t = dNames(id)
            var_to&$X!id_t$ = dList[id]
        end if 
      end do
    end if
  end if
  end if
end

; Applies each name and coordinate to dims of X
undef("copy_Coords")
procedure copy_Coords(dNames[*]:string,dList:list,X)
local rank,rankX,id
begin
    rank  = dimsizes(dNames)
    rankX = get_rank0(X)
    if (rankX.lt.rank) then
        print("copy_Coords: Cannot copy more coord dims than exist in X.")
        print("             Attempted to copy "+rank+" dims into array with "+rankX+" dims.")
        exit()
    end if
    do id=0,rank-1
        X!id     = dNames(id)
        X&$X!id$ = dList[id]
    end do
end

undef("copy_CoordsFroTo")
procedure copy_CoordsFroTo(dNames:string,dList:list,var_to,dimsfro:integer,dimsto:integer) 
local id,id_f,id_t,rfrom,rto
begin
  if (dimsfro(0).gt.-1) then
    rfrom = dimsizes(dimsfro)
    rto  = dimsizes(dimsto)
    if (rfrom.eq.rto) then
      if (.not.all(ismissing(dNames))) then
      do id=0,rfrom-1
        id_f = dimsfro(id)
        id_t = dimsto(id)
        if (.not.ismissing(dNames(id_f))) then
            var_to!id_t = dNames(id_f)
            var_to&$var_to!id_t$ = dList[id_f]
        end if 
      end do
      end if
    else
      print("copy_CoordsFroTo: # of dims copied must be equal, rfrom="+rfrom+", rto="+rto)
      print("                   only attributes have been copied.")
    end if
  end if
end

undef("copy_VarCoords_Fro")
procedure copy_VarCoords_Fro(var_from,var_to,dims_fro:integer) 
local id,id_f,dNames,rank 
begin
    if (.not.ismissing(dims_fro(0))) then
    if (dims_fro(0).gt.-1) then
        rank   = dimsizes(dims_fro)
        dNames = getvardims(var_from)

        if (.not.all(ismissing(dNames))) then
            do id=0,rank-1
                id_f = dims_fro(id)
                if (.not.ismissing(dNames(id_f))) then
                    var_to!id = var_from!id_f
                    if (iscoord(var_from,var_from!id_f))then
                        var_to&$var_to!id$ = var_from&$var_from!id_f$
                    end if
                end if 
            end do
        end if
    end if
    end if
end

undef("copy_VarCoords_To")
procedure copy_VarCoords_To(var_from,var_to,dims_to:integer) 
local id,id_t,dNames,rank 
begin
    if (.not.ismissing(dims_to(0))) then
    if (dims_to(0).gt.-1) then
        rank   = dimsizes(dims_to)
        dNames = getvardims(var_from)

        if (.not.all(ismissing(dNames))) then
            do id=0,rank-1
                id_t = dims_to(id)
                if (.not.ismissing(dNames(id))) then
                    var_to!id_t = var_from!id
                    if (iscoord(var_from,var_from!id))then
                        var_to&$var_to!id_t$ = var_from&$var_from!id$
                    end if
                end if 
            end do
        end if
    end if
    end if
end

undef("copy_VarCoordsFroTo")
procedure copy_VarCoordsFroTo(var_from,var_to,dimsfro:integer,dimsto:integer) 
local id,id_f,id_t,dNames,rfrom,rto
begin
  if (dimsfro(0).gt.-1) then
    rfrom = dimsizes(dimsfro)
    rto   = dimsizes(dimsto)
    if (rfrom.eq.rto) then
      dNames = getvardims(var_from)
      
      if (.not.all(ismissing(dNames))) then
      do id=0,rfrom-1
             id_f = dimsfro(id)
             id_t = dimsto(id)
             if (.not.ismissing(dNames(id_f))) then
                 var_to!id_t = var_from!id_f
                 if (iscoord(var_from,var_from!id_f))then
                     var_to&$var_to!id_t$ = var_from&$var_from!id_f$
                 end if
             end if 
      end do
      end if
    else
      print("copy_VarCoordsFroTo: # of dims copied must be equal, rfrom="+rfrom+", rto="+rto)
      print("                   only attributes have been copied.")
    end if
  end if
end

undef("copy_VarCoordsFroTo_Named")
procedure copy_VarCoordsFroTo_Named(var_from,var_to,dimsfro:string,dimsto:integer) 
begin
    copy_VarCoordsFroTo(var_from,var_to,DimsFromNames(var_from,dimsfro),dimsto) 
end

undef("copy_VarMeta_Fro")
procedure copy_VarMeta_Fro(var_from,var_to,dims_fro:integer) 
begin
    copy_VarCoords_Fro(var_from,var_to,dims_fro)

    copy_VarAtts(var_from,var_to)
end

undef("copy_VarMeta_Fro_except")
procedure copy_VarMeta_Fro_except(var_from,var_to,Except[*]:string,dims_fro:integer) 
begin
    copy_VarCoords_Fro(var_from,var_to,dims_fro)

    copy_VarAtts_except(var_from,var_to,Except)
end

undef("copy_VarMeta_To")
procedure copy_VarMeta_To(var_from,var_to,dims_to:integer) 
begin
    copy_VarCoords_To(var_from,var_to,dims_to)

    copy_VarAtts(var_from,var_to)
end

undef("copy_VarMeta_To_except")
procedure copy_VarMeta_To_except(var_from,var_to,Except[*]:string,dims_to:integer) 
begin
    copy_VarCoords_To(var_from,var_to,dims_to)

    copy_VarAtts_except(var_from,var_to,Except)
end

undef("copy_VarMetaFroTo")
procedure copy_VarMetaFroTo(var_from,var_to,dimsfro:integer,dimsto:integer) 
begin
    copy_VarCoordsFroTo(var_from,var_to,dimsfro,dimsto)

    copy_VarAtts(var_from,var_to)
end

undef("copy_VarMetaFroTo_except")
procedure copy_VarMetaFroTo_except(var_from,var_to,Except[*]:string,dimsfro:integer,dimsto:integer) 
begin
    copy_VarCoordsFroTo(var_from,var_to,dimsfro,dimsto)

    copy_VarAtts_except(var_from,var_to,Except)
end

undef("copy_VarMeta_except")
procedure copy_VarMeta_except(var_from,var_to,Except[*]:string) 
begin
    copy_VarCoords(var_from,var_to)

    copy_VarAtts_except(var_from,var_to,Except)    ; DJS 20 Jan 2005
end


undef("get_mapdims_1")
function get_mapdims_1(V)
local id,dNames,dList,rank,mpdims,Type,Atts,dSizes
begin
  Type = typeof(V) 
  if (Type.eq."logical") then
    Atts = False
  else
    Atts = totype(0,Type)
  end if
  copy_VarAtts(V,Atts)

  rank  = get_rank0(V)
  dList := NewList("fifo")
  if (rank.gt.0) then
    dNames = getvardims(V)
    dSizes = dimsizes(V)
    mpdims = ispan(0,rank-1,1)
    ; mpdims = DimsFromNames2(dNames,dNames)
    do id=0,rank-1
      ListAppend(dList,V&$V!id$)
    end do
  else
    dNames = "missing"
    mpdims = -1
  end if

  return([/mpdims,dNames,dList,rank,dSizes,Type,Atts/])
end

undef("get_mapdims")
function get_mapdims(VLst:list,nozero:logical)
local Type,Atts,nvars,rank_Vars,iv,V,rank_max,dList_all,mpdims, \
      dNames_Vars,dSizes_Vars,dNames_tmp,dSizes_tmp,rank,id, \
      eqdims,dNames_all,dSizes_all
begin
  Type = typeof(VLst[0])
  if (Type.eq."logical") then
    Atts = False
  else
    Atts = totype(0,Type)
  end if

  nvars = ListCount(VLst)
  rank_Vars = new(nvars,integer,-1)
  do iv=0,nvars-1
    V := VLst[iv]
    if (nozero) then
        rank_Vars(iv)= dimsizes(V)
    else
        rank_Vars(iv)= get_rank0(V)
    end if
    copy_VarAtts(V,Atts)
  end do

  rank_max  = max(rank_Vars)
  dList_all := NewList("fifo")
  if (rank_max.lt.1) then
    mpdims = new((/nvars,1/),integer,-1)
    return([/mpdims,"none",dList_all,rank_Vars,1,Type,Atts,rank_max/])
  else
    dNames_Vars = new((/nvars,rank_max/),string,"none")
    dSizes_Vars = new((/nvars,rank_max/),integer)
    do iv=0,nvars-1
      V := VLst[iv]
      if (rank_Vars(iv).gt.0) then
        dNames_Vars(iv,0:rank_Vars(iv)-1)= getvardims(V)
        dSizes_Vars(iv,0:rank_Vars(iv)-1)= totype(dimsizes(V),typeof(dSizes_Vars))
      end if
    end do
    
    ; Need to find way to preserve order better.
    ; As different operation will create order than doesn't work for native NCL functions
    ; Basically, if certained named sequences
    ; dNames_tmp = venn2_union(dNames_tmp, dNames_Vars(iv,:)  )
    dNames_tmp := new(sum(rank_Vars),string)
    dSizes_tmp := new(sum(rank_Vars),integer)
    
    rank = 0
    do iv=0,nvars-1
      V := VLst[iv]
      do id=0,rank_Vars(iv)-1
        eqdims := ind(dNames_tmp.eq.dNames_Vars(iv,id))
        if (ismissing(eqdims(0))) then
          dNames_tmp(rank) = dNames_Vars(iv,id)
          dSizes_tmp(rank) = dSizes_Vars(iv,id)
          ListAppend(dList_all,V&$V!id$)
          rank = rank + 1
        end if
      end do
    end do
    
    dNames_all := dNames_tmp(0:rank-1)
    dSizes_all := dSizes_tmp(0:rank-1)
    
    mpdims = new((/nvars,rank_max/),integer,-1)
    do iv=0,nvars-1
      if (rank_Vars(iv).gt.0) then
        mpdims(iv,0:rank_Vars(iv)-1) = DimsFromNames2(dNames_all,dNames_Vars(iv,0:rank_Vars(iv)-1))
      end if
    end do
    
    return([/mpdims,dNames_all,dList_all,rank_Vars,dSizes_all,Type,Atts,rank/])
  end if
end


undef("new_Meta")
function new_Meta(subdims:integer,dSizes:snumeric,dNames:string,dList:list,Atts_in:snumeric,Type:string)
local Atts,rank,outvar,id
begin
  Atts = to_Type(Atts_in, Type)
  
  if (subdims(0).lt.0) then
    rank = 0
    outvar = new(1,Type,getVarFillValue(Atts))
  else
    rank = dimsizes(subdims)
    outvar = new(dSizes((/subdims/)),Type,getVarFillValue(Atts))
  end if

  copy_VarAtts(Atts,outvar)

  do id=0,rank-1
    outvar!id          = dNames(subdims(id))
    outvar&$outvar!id$ = dList[subdims(id)]
  end do
  
  return(outvar)
end

undef("new_Meta_by_Coords")
function new_Meta_by_Coords(Type:string,dList:list,dNames:string,in_FillValue)
local rank,dSizes,id,outvar
begin
  rank = ListCount(dList)
  dSizes = new(rank,"integer")
  do id=0,rank-1
    dSizes(id) = totype(dimsizes(dList[id]),typeof(dSizes))
  end do

  outvar = new(dSizes,Type,to_Type(in_FillValue,Type))
  
  do id=0,rank-1
    outvar!id          = dNames(id)
    outvar&$outvar!id$ = dList[id]
  end do
  
  return(outvar)
end

undef("new_From_Lst")
function new_From_Lst(VLst:list)
local maplist,dNames_all,dList_all,dSizes_all,Type,Atts,alldims
begin
  maplist    := get_mapdims(VLst,False)
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  alldims = DimsFromNames2(dNames_all,dNames_all)

  return(new_Meta(alldims,dSizes_all,dNames_all,dList_all,Atts,Type))
end

undef("new_From_1")
function new_From_1(V)
local maplist,dNames_all,dList_all,dSizes_all,Type,Atts,alldims
begin
  maplist = get_mapdims_1(V)
  alldims    := maplist[0]
  dNames_all := maplist[1]
  dList_all  := maplist[2]
  dSizes_all := maplist[4]
  Type       := maplist[5]
  Atts       := maplist[6]
  return(new_Meta(alldims,dSizes_all,dNames_all,dList_all,Atts,Type))
end


undef("conform_wrap")
function conform_wrap(xin,r)
local dNames_x,x,dSizes,OUT
begin
  dSizes  = dimsizes(r)
  if (dimsizes(dSizes).eq.1) then
    if (dSizes.eq.1) then
      OUT := conform(xin,r,-1)
      copy_VarMeta(xin,OUT)
      return(OUT)
    end if
  end if
  dNames_x = getvardims(xin)
  x = dims2end(xin,getvardims(r))
  OUT := conform(x,r,DimsFromNames(x,getvardims(r)))
  if isatt(r,"_FillValue") then
    OUT@_FillValue = r@_FillValue
  end if
  copy_VarMeta_except(x,OUT,"_FillValue")
  OUT := reorder_names(dNames_x,OUT)
  return(OUT)
end

undef("conform_wrap_names")
function conform_wrap_names(xin,r,dNames)
local dNames_x,x,dSizes,OUT
begin
  dSizes  = dimsizes(r)
  if (dimsizes(dSizes).eq.1) then
    if (dSizes.eq.1) then
      OUT := conform(xin,r,-1)
      copy_VarMeta(xin,OUT)
      return(OUT)
    end if
  end if
  dNames_x = getvardims(xin)
  x = dims2end(xin,dNames)
  OUT := conform(x,r,DimsFromNames(x,dNames))
  if isatt(r,"_FillValue") then
    OUT@_FillValue = r@_FillValue
  end if
  copy_VarMeta_except(x,OUT,"_FillValue")
  OUT := reorder_names(dNames_x,OUT)
  return(OUT)
end

undef("conform_dims_wrap")
function conform_dims_wrap(dNames_all,dList_all,dSizes_all,r,keep_scalar:logical)
local dSizes,OUT
begin
  dSizes = dimsizes(r)
  if (dimsizes(dSizes).eq.1) then
    if (dSizes.eq.1) then
      if (keep_scalar) then
        OUT = r
        return(OUT)
      else
        OUT = conform_dims(dSizes_all,r,-1)
        copy_Coords(dNames_all,dList_all,OUT)
        copy_VarAtts_except(r,OUT,"_FillValue")
        return(OUT)
      end if
    end if
  end if
  OUT = conform_dims(dSizes_all,r,DimsFromNames2(dNames_all,getvardims(r)))
  copy_Coords(dNames_all,dList_all,OUT)
  copy_VarAtts_except(r,OUT,"_FillValue")
  return(OUT)
end

undef("combine_dims")
function combine_dims(X:numeric,dim_args[*]:string)
local Xnew,rankd,Xnew_sizes,ndims,idx,newsz,out_sizes,OUT,sortedDName,id
begin
  Xnew  = dims2end(X,dim_args)
  rankd = dimsizes(dim_args)

  if (rankd.gt.1) then
    Xnew_sizes = dimsizes(Xnew)
    ndims = dimsizes(Xnew_sizes)
    idx = ndims-rankd
    newsz = idx + 1
    
    out_sizes = new(newsz,"integer")
    if (idx.gt.0)
      out_sizes(:idx-1) = Xnew_sizes(:idx-1)
    end if
    out_sizes(idx)    = product(Xnew_sizes(idx:))

    OUT = reshape(Xnew,out_sizes)
    if (idx.gt.0)
      copy_VarCoords_Fro(Xnew,OUT,ispan(0,idx-1,1))
    end if

    sortedDName = dim_args(0)
    do id=1,rankd-1
      sortedDName := sortedDName+"_"+dim_args(id)
    end do
    OUT!idx       = sortedDName
    OUT&$OUT!idx$ = todouble( fspan(0,tofloat(out_sizes(idx)-1),out_sizes(idx)) )
  else
    OUT = Xnew
  end if

  return(OUT)
end


undef("str_sub_str_multi")
function str_sub_str_multi(instr:string,strfind[*]:string,strrepl[*]:string )
local nstr,i,outstr
begin
  nstr = dimsizes(strfind)
  outstr = instr
  if ( nstr.eq.dimsizes(strrepl) ) then
    do i=0,nstr-1
      outstr = str_sub_str(outstr,  strfind(i), strrepl(i))
    end do
  else
    print("str_sub_str_multi: 2nd and 3rd arguments need to have the same number of strings!")
  end if

  return outstr
end


undef("getMirroredAxisFromMinMax")
function getMirroredAxisFromMinMax(minval:numeric,maxval:numeric,nints:numeric,nsigfig:numeric)
local absminval,maxval2,minone,maxpow,maxone,fltint,intpow,intone,nsym,sigmult
begin
  absminval := abs(minval)
  maxabsval := absminval>maxval
  
  sigmult := 0.5*(10.0^(nsigfig-1.0))

  maxpow := 10.0^floor(log10(maxabsval))
  maxone := ceil(sigmult*maxabsval/maxpow)*maxpow/sigmult
  
  nsym   := ceil(0.5*nints)
  fltint := maxone/nsym
  intpow := 10^floor(log10(fltint))
  intone := ceil(fltint/intpow)*intpow
  
  maxone := nsym*intone
  minone := -maxone
  
  copy_VarMeta(minval,minone)
  copy_VarMeta(maxval,maxone)
  copy_VarMeta(minval,intone)
  return([/minone,maxone,intone/])
end

undef("getAxisFromMinMaxPos")
function getAxisFromMinMaxPos(minval:numeric,maxval:numeric,nints:numeric,nsigfig:numeric)
local mnmxrat,minpow,minone,maxpow,maxone,fltint,intpow,intone,sigmult
begin
  mnmxrat := minval/maxval
  
  sigmult := 0.5*(10.0^(nsigfig-1.0))
  minpow  := 10.0^floor(log10(minval))
  minpow@_FillValue = -999
  minpow   = (/ where(minpow.gt.0.0,minpow,minpow@_FillValue) /)
  minone  := floor(sigmult*minval/minpow)*minpow/sigmult
  minone   = (/ where(mnmxrat.le.0.2,0.0,minone) /)
  
  maxpow := 10.0^floor(log10(maxval))
  maxone  = ceil(sigmult*maxval/maxpow)*maxpow/sigmult
  
  fltint := (maxone-minone)/nints
  intpow := 10^floor(log10(fltint))
  intone = ceil(fltint/intpow)*intpow
  
  copy_VarMeta(minval,minone)
  copy_VarMeta(maxval,maxone)
  copy_VarMeta(minval,intone)
  return([/minone,maxone,intone/])
end

undef("getAxisFromMinMaxNeg")
function getAxisFromMinMaxNeg(minval:numeric,maxval:numeric,nints:numeric,nsigfig:numeric)
local absminval,absmaxval,mnmxrat,minpow,minone,maxpow,maxone,fltint,intpow,intone,sigmult
begin
  absminval := abs(maxval)
  absmaxval := abs(minval)
  mnmxrat := absminval/absmaxval
  
  sigmult := 0.5*(10.0^(nsigfig-1.0))
  minpow  := 10.0^floor(log10(absminval))
  minpow@_FillValue = -999
  minpow   = (/ where(minpow.gt.0.0,minpow,minpow@_FillValue) /)
  minone  := floor(sigmult*absminval/minpow)*minpow/sigmult
  minone   = (/ where(mnmxrat.le.0.2,0.0,minone) /)
  
  maxpow := 10.0^floor(log10(absmaxval))
  maxone  = ceil(sigmult*absmaxval/maxpow)*maxpow/sigmult
  
  fltint := (maxone-minone)/nints
  intpow := 10^floor(log10(fltint))
  intone = ceil(fltint/intpow)*intpow
  
  maxone = -maxone
  minone = where(minone.gt.0.0,-minone,minone)
  copy_VarMeta(minval,minone)
  copy_VarMeta(maxval,maxone)
  copy_VarMeta(minval,intone)
  return([/maxone,minone,intone/])
end

undef("getAxisFromMinMax")
function getAxisFromMinMax(minval[1]:numeric,maxval[1]:numeric,nints:numeric,nsigfig:numeric)
local minone,maxone,intone,rLst
begin

  if (all(ismissing(minval)).or.all(ismissing(maxval))) then
    ; probably should return missing, but for now just generic -1 to 1
    minone = conform_wrap(minval, -1.0)
    maxone = conform_wrap(minval,  1.0)
    intone = conform_wrap(minval, 2.0/nints)
    rLst = [/ minone, maxone, intone /]
    return(rLst)
  elseif ((minval.lt.0.0).and.(maxval.gt.0.0)) then
    rLst = getMirroredAxisFromMinMax(minval,maxval,nints,nsigfig)
    return(rLst)
  elseif (maxval.le.0.0) then
    rLst = getAxisFromMinMaxNeg(minval,maxval,nints,nsigfig)
    return(rLst)
  else
    rLst = getAxisFromMinMaxPos(minval,maxval,nints,nsigfig)
    return(rLst)
  end if
end


undef("lts_nm")
function lts_nm(X:numeric,Y:numeric)
local Z
begin
  Z = where(ismissing(Y),X,where(ismissing(X),Y,X<Y))
  if (get_rank0(X) .ge. get_rank0(Y)) then
    copy_VarMeta(X,Z)
  else
    copy_VarMeta(Y,Z)
  end if
  return(Z)
end

undef("gts_nm")
function gts_nm(X:numeric,Y:numeric)
local Z
begin
  Z = where(ismissing(Y),X,where(ismissing(X),Y,X>Y))
  if (get_rank0(X) .ge. get_rank0(Y)) then
    copy_VarMeta(X,Z)
  else
    copy_VarMeta(Y,Z)
  end if
  return(Z)
end


undef("earth_area_latlon")
function earth_area_latlon(lat[*]:numeric,dln[1]:numeric)
local d2r,R_sq,dlt,lt1,lt2,rlt1,rlt2,dsnlt,area
begin
  d2r  = get_d2r("double");
  R_sq = 40680159.61000001D;
  dlt   := lat(1)-lat(0) ; assumes monotically increasing latitude.
  lt1   := lat - 0.5*dlt
  lt2   := lat + 0.5*dlt
  rlt1  := lt1*d2r;
  rlt2  := lt2*d2r;
  dsnlt := abs(sin(rlt1)-sin(rlt2));
  area  := d2r*R_sq*dsnlt*dln;
  area!0   = "lat"
  area&lat = lat
  return(area)
end


undef("pvalue_r_N")
function pvalue_r_N(r:numeric,N:numeric)
local maplist,mpdims,dNames_all,dList_all,rank_Vars,dSizes_all,r_cnfrm,N_cnfrm,df,t,p,t1d,df1d,idxs,p1d
begin
  maplist = get_mapdims([/r, N/],False)
  mpdims     = maplist[0]
  dNames_all = maplist[1]
  dList_all  = maplist[2]
  rank_Vars  = maplist[3]
  dSizes_all = maplist[4]

  if (rank_Vars(0).gt.0) then
    r_cnfrm = conform_dims(dSizes_all,r,mpdims(0,0:rank_Vars(0)-1))
  else
    r_cnfrm = conform_dims(dSizes_all,r,-1)
  end if
  if (rank_Vars(1).gt.0) then
    N_cnfrm = conform_dims(dSizes_all,N,mpdims(1,0:rank_Vars(1)-1))
  else
    N_cnfrm = conform_dims(dSizes_all,N,-1)
  end if

  df = where(N_cnfrm.gt.2,todouble(N_cnfrm)-2.0,N_cnfrm@_FillValue)
  t  = fabs(r_cnfrm)*sqrt(df)/sqrt(1-r_cnfrm*r_cnfrm)
  ; p  = where(ismissing(df).or.ismissing(t),true_value,cdft_p ( t, df ))
  
  t1d  = ndtooned(t)
  df1d = ndtooned(df)
  idxs = ind(.not.(ismissing(t1d).or.ismissing(df1d)))
  
  p1d       = new(dimsizes(t1d),typeof(t1d),r_cnfrm@_FillValue)
  p1d(idxs) = (/ cdft_p(t1d(idxs),df1d(idxs)) /)
  
  p = reshape(p1d,dimsizes(r_cnfrm))

  copy_Coords(dNames_all,dList_all,p)
  copy_VarAtts_except(r,p,"_FillValue")
  return(p)
end

undef("cycmod")
function cycmod(x:snumeric,y:snumeric)
local x_mod_y
begin
    x_mod_y = mod(x,y)
    x_mod_y = (/ where(x_mod_y.lt.0,y+x_mod_y,x_mod_y) /)

    return(x_mod_y)
end

undef("cycmod_be")
function cycmod_be(x:snumeric,b:snumeric,e:snumeric)
local x_mod_y,x2,y
begin
    x2      = x - b
    y       = e - b
    x_mod_y = cycmod(x2,y) + b

    return(x_mod_y)
end


undef("areDimsOrdered")
function areDimsOrdered(dims[*]:integer)
local i, ndims
begin
    n    = dimsizes(dims)
    cdim = dims(0)
    do i=1,n-1
        cdim = cdim + 1
        if (dims(i).ne.cdim) then
            return(False)
        end if
    end do
    return(True)
end
;
;    dims = dimnames_to_indexes(IN,dim_args)
;    if (areDimsOrdered(dims)) then
;        OUT  = dim_avg_n_Wrap(IN, dims)
;    else
;        X    = dims2end(IN,dim_args)
;        rank = get_rank0(X)-1
;        OUT      = dim_avg_n_Wrap(X, ispan(rank-dimsizes(dim_args),rank-1,1))
;    end if
;