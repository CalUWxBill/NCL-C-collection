; Created by Bill Scheftic
; Index of Functions and Procedures
;
; Retrieve variables from files
; function getGridFromOpenedFile(file_in:file,vname:string)
; function getGridFromFile(fname:string,fext:string,vname:string)
; function getAllVarsFromFile(fname:string,fext:string)
; function getMultiVarsFromFile(fname:string,fext:string,vnames[*]:string)
;
; Output variables to files
; function outputListRecursive(fout:file,Lst:list,vname[*]:string)
; procedure outputListToFileSimple(Lst:list,vname[*]:string,fname:string,title:string,fAttIn:logical)

if (.not.isdefined("contrib_declared")) then
 loadscript("$NCARG_ROOT/lib/ncarg/nclex/gsun/gsn_code.ncl")
 loadscript("$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_csm.ncl")
 loadscript("$NCARG_ROOT/lib/ncarg/nclscripts/csm/contributed.ncl")
 contrib_declared = 1
end if
if (.not.isdefined("convert_units_declared")) then
 loadscript("$NCL_USER_DIR/load/convert_units.ncl")
 convert_units_declared = 1
end if
if (.not.isdefined("functions_declared")) then
 loadscript("$NCL_USER_DIR/load/functions.ncl")
 functions_declared = 1
end if

;==============================
; Retrieve variables from files
;==============================
undef("getGridFromOpenedFile")
function getGridFromOpenedFile(file_in:file,vname:string)
local data,file_ltln
begin
  if (isfilevar(file_in,vname)) then
    data = file_in->$vname$
    if ( (typeof(data).eq."float").or.(typeof(data).eq."double") ) then
      if (any(isnan_ieee(data))) then
        value = default_fillvalue(typeof(data))
        replace_ieeenan (data, value, 0)
        data@_FillValue = value
      end if
    end if
    if (isatt(file_in,"lat2d")) then
      data@lat2d = file_in->lat2d
      data@lon2d = file_in->lon2d
    elseif (isatt(file_in,"latlonfile")) then
      file_ltln = addfile(file_in@latlonfile, "r") ; Read file for the first time.
      data@lat2d = file_ltln->lat2d
      data@lon2d = file_ltln->lon2d
      delete(file_ltln)
    end if
    if (isatt(data,"units"))
      if ((data@units.eq."kg.m-2.s-1").or.(data@units.eq."kg m-2 s-1")) then
        data = convertTo(data,"kg.m-2.d-1")
      end if
    end if
  else
    print("No variable named "+vname+" found!")
    print(getfilevarnames(file_in))
    data = False
  end if

  return(data)
end

undef("getGridFromFile")
function getGridFromFile(fname:string,fext:string,vname:string)
local docompress,file_in,data
begin
  docompress = False
  if (fileexists(fname + ".gz")) then
    system("gzip -df " + fname + ".gz")     ; decompress .gz file
    docompress = True
  end if
  file_in = addfile(fname+"."+fext, "r") ; Read file for the first time.
  print ("opened "+fname)

  data := getGridFromOpenedFile(file_in,vname)

  if (docompress) then
    system("gzip -f " + fname)     		; compress .gz file
  end if

  delete(file_in)
  return(data)
end

undef("getAllVarsFromFile")
function getAllVarsFromFile(fname:string,fext:string)
local docompress,file_in,vnames,nfiles,VLst
begin
  docompress = False
  if (fileexists(fname + ".gz")) then
    system("gzip -df " + fname + ".gz")     ; decompress .gz file
    docompress = True
  end if
  file_in = addfile(fname+"."+fext, "r") ; Read file for the first time.
  print ("opened "+fname)
  ; printVarSummary(file_in)
  
  vnames = getfilevarnames(file_in)
  print(vnames)
  
  nfiles = dimsizes(vnames)
 
  VLst  := NewList("fifo")
  do i=0,nfiles-1
    ListAppend(VLst,getGridFromOpenedFile(file_in,vnames(i)))
  end do
  ; print(VLst)

  if (docompress) then
    system("gzip -f " + fname)     		; compress .gz file
  end if

  delete(file_in)
  return(VLst)
end

undef("getMultiVarsFromFile")
function getMultiVarsFromFile(fname:string,fext:string,vnames[*]:string)
local docompress,file_in,nfiles,VLst
begin
  docompress = False
  if (fileexists(fname + ".gz")) then
    system("gzip -df " + fname + ".gz")     ; decompress .gz file
    docompress = True
  end if
  file_in = addfile(fname+"."+fext, "r") ; Read file for the first time.
  print ("opened "+fname)
  ; printVarSummary(file_in)
  
  nfiles = dimsizes(vnames)
 
  VLst  := NewList("fifo")
  do i=0,nfiles-1
    ListAppend(VLst,getGridFromOpenedFile(file_in,vnames(i)))
  end do
  ; print(VLst)

  if (docompress) then
    system("gzip -f " + fname)     		; compress .gz file
  end if

  delete(file_in)
  return(VLst)
end

undef("getWeeklyGridFromFiles_y4m2d2")
function getWeeklyGridFromFiles_y4m2d2(filenametemplate:string,fext:string,vname:string,yb:integer,mb:integer,db:integer,ye:integer,me:integer,de:integer)
local data_unset,nyears,nmonths,iy,im,yyyy,sy4,mm,sm2,filename,data_tmp,dsizes_tmp,ndims,indims,outdims,dsizes,data
begin
  data_unset := True
  unitOfTime = "days since 1970-1-1 00:00:00"
  
  initDate = cd_inv_calendar(yb,mb,db,0,0,0,unitOfTime,0)
  initDate@units=unitOfTime
  
  endDate = cd_inv_calendar(ye,me,de,0,0,0,unitOfTime,0)
  endDate@units=unitOfTime
  
  times = todouble( ispan(toint(initDate),toint(endDate),7) )
  ntimes = dimsizes(times)
  times@units=unitOfTime
  print(times)
  print(ntimes)

  it = 0
  do while (initDate .le. endDate)
    initDateAr = cd_calendar(initDate, 0)
    yyyy := tointeger(initDateAr(:,0))
    mm   := tointeger(initDateAr(:,1))
    dd   := tointeger(initDateAr(:,2))
    
    siyy = sprinti("%0.4i", yyyy)
    simm = sprinti("%0.2i", mm)
    sidd = sprinti("%0.2i", dd)

    filename := str_sub_str_multi(filenametemplate,  (/ "%v", "%y4", "%m2", "%d2" /), (/ vname, siyy, simm, sidd /))
    if (isfilepresent(filename)) then
      data_tmp := getGridFromFile(filename,fext,vname)
      if (data_unset) then
        dsizes_tmp := dimsizes(data_tmp)
        ndims      := dimsizes(dsizes_tmp)
        indims     := ispan(0,ndims-1,1)
        outdims    := indims+1
        dsizes     := array_append_record ((/ntimes/),dsizes_tmp,0)
        data       := new(dsizes,typeof(data_tmp),data_tmp@_FillValue)
        data!0     = "time"
        data&time  = times
        copy_VarMetaFroTo(data_tmp,data,indims,outdims)
        ; print(dsizes_tmp)
        ; print(ndims)
        ; print(indims)
        ; print(outdims)
        ; print(dsizes)
        ; printVarSummary(data)
        ; exit()
        data_unset = False
      end if
      ; printVarSummary(data_tmp)
      data(it,:,:) = (/ data_tmp /)
      delete(data_tmp)
    end if

    initDate = (/ initDate + 7 /)
    it = it + 1
  end do
  return(data)
end

undef("getMonthlyGridFromFiles_y4m2")
function getMonthlyGridFromFiles_y4m2(filenametemplate:string,fext:string,vname:string,yb:integer,mb:integer,ye:integer,me:integer)
local data_unset,nyears,nmonths,it,iy,im,yyyy,sy4,mm,sm2,filename,data_tmp,dsizes_tmp,ndims,indims,outdims,dsizes,data
begin
  print("getMonthlyGridFromFiles_y4m2: "+filenametemplate+" "+fext+" "+vname+" "+yb+" "+mb+" "+ye+" "+me)

  data_unset := True
  unitOfTime = "months since 1970-1-1 00:00:00"
  
  initDate = cd_inv_calendar(yb,mb,1,0,0,0,unitOfTime,0)
  initDate@units=unitOfTime
  print(initDate)
  
  endDate = cd_inv_calendar(ye,me,1,0,0,0,unitOfTime,0)
  endDate@units=unitOfTime
  print(endDate)
  
  nyears = toint(ye-yb+1)
  
  if ((endDate-initDate).eq.0)
    initDateAr = cd_calendar(initDate, 0)
    yyyy := tointeger(initDateAr(:,0))
    mm   := tointeger(initDateAr(:,1))
    
    siyy = sprinti("%0.4i", yyyy)
    simm = sprinti("%0.2i", mm)

    filename := str_sub_str_multi(filenametemplate,  (/ "%v", "%y4", "%m2" /), (/ vname, siyy, simm /))
    data     := getGridFromFile(filename,fext,vname)
  else
    it = 0
    do while (initDate .le. endDate)
      initDateAr = cd_calendar(initDate, 0)
      yyyy := tointeger(initDateAr(:,0))
      mm   := tointeger(initDateAr(:,1))
      
      siyy = sprinti("%0.4i", yyyy)
      simm = sprinti("%0.2i", mm)
    
      filename := str_sub_str_multi(filenametemplate,  (/ "%v", "%y4", "%m2" /), (/ vname, siyy, simm /))
      if (isfilepresent(filename)) then
        data_tmp := rm_single_dims(getGridFromFile(filename,fext,vname))
        if (data_unset) then
          dsizes_tmp := dimsizes(data_tmp)
          ndims      := dimsizes(dsizes_tmp)
          indims     := ispan(0,ndims-1,1)
          outdims    := indims+2
          dsizes     := array_append_record ((/nyears,12/),dsizes_tmp,0)
          data       := new(dsizes,typeof(data_tmp),data_tmp@_FillValue)
          data!0     = "year"
          data&year  = todouble( fspan(yb,ye,toint(ye-yb+1)) )
          data!1     = "month"
          data&month = todouble( fspan(1,12,12) )
          copy_VarMetaFroTo(data_tmp,data,indims,outdims)
          ; print(dsizes_tmp)
          ; print(ndims)
          ; print(indims)
          ; print(outdims)
          ; print(dsizes)
          ; printVarSummary(data)
          ; exit()
          data_unset = False
        end if
        ; printVarSummary(data_tmp)
        iy = yyyy-yb
        im = mm - 1
        data(iy,im,:,:) = (/ data_tmp /)
        delete(data_tmp)
      end if
    
      initDate = (/ initDate + 1 /)
      it = it + 1
    end do
  end if
  return(data)
end

undef("getMonthlyGridFromFiles_m2")
function getMonthlyGridFromFiles_m2(filenametemplate:string,fext:string,vname:string,mb:integer,me:integer)
local data_unset,nyears,nmonths,it,iy,im,yyyy,sy4,mm,sm2,filename,data_tmp,dsizes_tmp,ndims,indims,outdims,dsizes,data
begin
  print("getMonthlyGridFromFiles_m2: "+filenametemplate+" "+fext+" "+vname+" "+mb+" "+me)

  data_unset := True

  if ((me-mb).eq.0)
    simm = sprinti("%0.2i", mb)

    filename := str_sub_str_multi(filenametemplate,  (/ "%v", "%m2" /), (/ vname, simm /))
    data     := getGridFromFile(filename,fext,vname)
  else
    it = 0
    do mm=mb,me
      simm = sprinti("%0.2i", mm)
    
      filename := str_sub_str_multi(filenametemplate,  (/ "%v", "%m2" /), (/ vname, simm /))
      if (isfilepresent(filename)) then
        data_tmp := rm_single_dims(getGridFromFile(filename,fext,vname))
        if (data_unset) then
          dsizes_tmp := dimsizes(data_tmp)
          ndims      := dimsizes(dsizes_tmp)
          indims     := ispan(0,ndims-1,1)
          outdims    := (/ 0, 2, 3 /)
          dsizes     := array_append_record ((/dsizes_tmp(0),12/),dsizes_tmp(1:),0)
          data       := new(dsizes,typeof(data_tmp),data_tmp@_FillValue)
          data!1     = "month"
          data&month = ispan(mb,me,1)
          copy_VarMetaFroTo(data_tmp,data,indims,outdims)
          ; print(dsizes_tmp)
          ; print(ndims)
          ; print(indims)
          ; print(outdims)
          ; print(dsizes)
          ; printVarSummary(data)
          ; exit()
          data_unset = False
        end if
        ; printVarSummary(data_tmp)
        im = mm - 1
        data(:,im,:,:) = (/ data_tmp /)
        delete(data_tmp)
      end if
    end do
  end if
  return(data)
end


;==========================
; Output variables to files
;==========================
undef("outputListRecursive")
function outputListRecursive(fout:file,Lst:list,vname[*]:string)
local lstcnt,nvnames,iv,il,cvar,nvarslst
begin
  lstcnt = ListCount(Lst)   ; Get total list count
  nvnames  = dimsizes(vname)
  iv = 0
  do il=0,lstcnt-1
    cvar := Lst[il]
    ; printVarSummary(cvar)
    if (typeof(cvar).eq."list") then
      nvarslst = outputListRecursive(fout,cvar,vname(iv:nvnames-1))
      iv = iv + nvarslst
    else
      fout->$vname(il)$ = cvar
      iv = iv + 1
    end if
  end do
  return(iv)
end

undef("outputListToFileSimple")
procedure outputListToFileSimple(Lst:list,vname[*]:string,fname:string,title:string,fAttIn:logical)
local nvnames,nvarslst,lstcnt,cvar,iv,il,fout,fAtt,time,time_FillValue,cvar_FillValue
begin
; This link gives more complete info on writing out coordinate variables
; http://www.ncl.ucar.edu/Applications/method_2.shtml

  if (isatt(fname,"Format")) then
    setfileoption("nc","Format",fname@Format)
  else
    setfileoption("nc","Format","NetCDF4")
  end if
  if (isatt(fname,"CompressionLevel")) then
    setfileoption("nc","CompressionLevel",fname@CompressionLevel)
  end if
  if (isatt(fname,"MissingToFillValue")) then
    setfileoption("nc","MissingToFillValue",fname@MissingToFillValue)
  end if
  if (isatt(fname,"Shuffle")) then
    setfileoption("nc","Shuffle",fname@Shuffle)
  end if
  if (isatt(fname,"PreFill")) then
    setfileoption("nc","PreFill",fname@PreFill)
  end if
  if (isatt(fname,"HeaderReserveSpace")) then
    setfileoption("nc","HeaderReserveSpace",fname@HeaderReserveSpace)
  end if
  system("/bin/rm -f " + fname)    ; remove if exists
  system("/bin/rm -f " + fname + ".gz")    ; remove if exists
  fout  = addfile (fname, "c")  ; open output file

;===================================================================
; create global attributes of the file
;===================================================================
  if (fAttIn) then
    fAtt = fAttIn
  else
    fAtt = True
  end if
  fAtt@title         = title
  if (.not.isatt(fAtt,"Conventions")) then
    fAtt@Conventions   = "None"
  end if
  ; fAtt@creation_date = systemfunc ("date")        
  fileattdef( fout, fAtt )            ; copy file attributes

;===================================================================
; make time an UNLIMITED dimension; recommended  for most applications
;===================================================================
; filedimdef(fout,"time",-1,True) 

;===================================================================
; output variables directly; NCL will call appropriate functions
; to write the meta data associated with each variable
;===================================================================
  printVarSummary(Lst)
  lstcnt = ListCount(Lst)   ; Get total list count
  nvnames = dimsizes(vname)
  iv = 0
  do il=0,lstcnt-1
    cvar := Lst[il]
    ; printVarSummary(cvar)
    ; cvar_FillValue = cvar@_FillValue
    ; printVarSummary(cvar_FillValue)
    ; time := cvar&time
    ; printVarSummary(time)
    ; time_FillValue = time@_FillValue
    ; printVarSummary(time_FillValue)
    if (typeof(cvar).eq."list") then
      nvarslst = outputListRecursive(fout,cvar,vname(iv:nvnames-1))
      iv = iv + nvarslst
    else
      fout->$vname(iv)$ = cvar ; changed il to iv!
      iv = iv + 1
    end if
  end do
  printVarSummary(fout)
  delete(fout)
  print(iv+" vars written to file "+fname)
end

