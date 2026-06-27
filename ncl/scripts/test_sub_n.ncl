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

;---------------------------------------------------------------------------------------------------------
; Usage: ncl $NCL_SCRIPTS/test_sub_n.ncl
begin
    dimsX = (/ 3, 4, 5 /)
    rankX = dimsizes(dimsX)
    X = onedtond(ispan(1,product(dimsX),1),dimsX)
    dLst = NewList("fifo")
    do i=0,rankX-1
        ListAppend(dLst,ispan(0,dimsX(i)-1,1))
    end do
    ; copy_Coords_To((/"x","y","z"/),dLst,X,(/0,1,2/))
    copy_Coords((/"x","y","z"/),dLst,X)
    print_array_head(X,"X:","%4d")

    ; X(0:1,:,:)
    Xx = sub_n(X,"x",0,1,1)
    print_array_head(Xx,"Xx:","%4d")
    if (any(Xx .ne. X(0:1,:,:))) then
        print("Xx != X(0:1,:,:)")
        print_array(X(0:1,:,:),"%4d")
        exit()
    end if

    ; X(:,0:1,:)
    Xy = sub_n(X,"y",0,1,1)
    print_array_head(Xy,"Xy:","%4d")
    if (any(Xy .ne. X(:,0:1,:))) then
        print("Xy != X(:,0:1,:)")
        print_array(X(:,0:1,:),"%4d")
        exit()
    end if

    ; X(:,1,:) easier syntax if you only want to grab on single indices
    Xy1 = sub_n_1(X,"y",1)
    print_array_head(Xy1,"Xy1:","%4d")
    if (any(Xy1 .ne. X(:,1,:))) then
        print("Xy1 != X(:,1,:)")
        print_array(X(:,1,:),"%4d")
        exit()
    end if

    ; X(:,1:1,:)
    Xy1_2 = sub_n(X,"y",1,1,1)
    print_array_head(Xy1_2,"Xy1_2:","%4d")
    if (any(Xy1_2 .ne. X(:,1:1,:))) then
        print("Xy1_2 != X(:,1:1,:)")
        print_array(X(:,1:1,:),"%4d")
        exit()
    end if

    ; X(:,1,:)
    Xy1_3 = sub_n(X,"y",1,1,0)
    print_array_head(Xy1_3,"Xy1_3:","%4d")
    if (any(Xy1_3 .ne. X(:,1,:))) then
        print("Xy1_3 != X(:,1,:)")
        print_array(X(:,1,:),"%4d")
        exit()
    end if

    ; X(:,:,0:1)
    Xz = sub_n(X,"z",0,1,1)
    print_array_head(Xz,"Xz:","%4d")
    if (any(Xz .ne. X(:,:,0:1))) then
        print("Xz != X(:,:,0:1)")
        print_array(X(:,:,0:1),"%4d")
        exit()
    end if

    ; X(0:2:2,:,:)
    Xx2 = sub_n(X,"x",0,2,2)
    print_array_head(Xx2,"Xx2:","%4d")
    if (any(Xx2 .ne. X(0:2:2,:,:))) then
        print("Xx2 != X(0:2:2,:,:)")
        print_array(X(0:2:2,:,:),"%4d")
        exit()
    end if

    ; X(:,0:3:2,:)
    Xy2 = sub_n(X,"y",0,3,2)
    print_array_head(Xy2,"Xy2:","%4d")
    if (any(Xy2 .ne. X(:,0:3:2,:))) then
        print("Xy2 != X(:,0:3:2,:)")
        print_array(X(:,0:3:2,:),"%4d")
        exit()
    end if

    ; X(:,:,0:4:2)
    Xz2 = sub_n(X,"z",0,4,2)
    print_array_head(Xz2,"Xz2:","%4d")
    if (any(Xz2 .ne. X(:,:,0:4:2))) then
        print("Xz2 != X(:,:,0:4:2)")
        print_array(X(:,:,0:4:2),"%4d")
        exit()
    end if

    ; X(:,:,0:4:-2)
    Xz2_ = sub_n(X,"z",0,4,-2)
    print_array_head(Xz2_,"Xz2_:","%4d")
    if (any(Xz2_ .ne. X(:,:,0:4:-2))) then
        print("Xz2_ != X(:,:,0:4:-2)")
        print_array(X(:,:,0:4:-2),"%4d")
        exit()
    end if

    ; X(:,:,4:0:2)
    Xz2_2 = sub_n(X,"z",4,0,2)
    print_array_head(Xz2_2,"Xz2_2:","%4d")
    if (any(Xz2_2 .ne. X(:,:,4:0:2))) then
        print("Xz2_2 != X(:,:,4:0:2)")
        print_array(X(:,:,4:0:2),"%4d")
        exit()
    end if

    ; X(0:2:2,:,0:2)
    Xxz = sub_n(X,(/ "x", "z" /), \ ; dimensions to select on
                  (/   0,   0 /), \ ; beginning index element
                  (/   2,   2 /), \ ; ending index element
                  (/   2,   1 /))   ; stride (not sure if neg stride works)
    print_array_head(Xxz,"Xxz:","%4d")
    if (any(Xxz .ne. X(0:2:2,:,0:2))) then
        print("Xxz != X(0:2:2,:,0:2)")
        print_array(X(0:2:2,:,0:2),"%4d")
        exit()
    end if

    ; X(0,:,1:1)
    Xxz_1 = sub_n(X,(/ "x", "z" /), \ ; dimensions to select on
                    (/   0,   1 /), \ ; beginning index element
                    (/   0,   1 /), \ ; ending index element
                    (/   0,   1 /))   ; stride
    print_array_head(Xxz_1,"Xxz_1:","%4d")
    if (any(Xxz_1 .ne. X(0,:,1:1))) then
        print("Xxz_1 != X(0,:,1:1)")
        print_array(X(0,:,1:1),"%4d")
        exit()
    end if

    ; X(0,:,1)
    Xxz_2 = sub_n(X,(/ "x", "z" /), \ ; dimensions to select on
                    (/   0,   1 /), \ ; beginning index element
                    (/   0,   1 /), \ ; ending index element
                         0)   ; stride can be scalar,
    print_array_head(Xxz_2,"Xxz_2:","%4d")
    if (any(Xxz_2 .ne. X(0,:,1))) then
        print("Xxz_2 != X(0,:,1)")
        print_array(X(0,:,1),"%4d")
        exit()
    end if

    ; X(0:0,:,1:1)
    Xxz_3 = sub_n(X,(/ "x", "z" /), \ ; dimensions to select on
                    (/   0,   1 /), \ ; beginning index element
                    (/   0,   1 /), \ ; ending index element
                         1)   ; stride can be scalar
    print_array_head(Xxz_3,"Xxz_3:","%4d")
    if (any(Xxz_3 .ne. X(0:0,:,1:1))) then
        print("Xxz_3 != X(0:0,:,1:1)")
        print_array(X(0:0,:,1:1),"%4d")
        exit()
    end if

    ; X(0,:,1:2)
    Xxz_4 = sub_n(X,(/ "x", "z" /), \ ; dimensions to select on
                    (/   0,   1 /), \ ; beginning index element
                    (/   0,   2 /), \ ; ending index element
                         0)   ; stride can be scalar,
    print_array_head(Xxz_4,"Xxz_4:","%4d")
    if (any(Xxz_4 .ne. X(0,:,1:2))) then
        print("Xxz_4 != X(0,:,1:2)")
        print_array(X(0,:,1:2),"%4d")
        exit()
    end if

    ; X(1:,1:,:)
    ; Xxy_1 = sub_n(X,(/ "x", "y" /), \ ; dimensions to select on
    ;                      1,         \ ; select each dim from 1
    ;                     -1,         \ ; select each dim to last
    ;                      0)           ; stride of 1 squeezing any singletons,
    Xxy_1 = sub_n(X,(/"x","y"/),1,-1,0) ; Concise selection from 1 to last of x an y.
    print_array_head(Xxy_1,"Xxy_1:","%4d")
    if (any(Xxy_1 .ne. X(1:,1:,:))) then
        print("Xxy_1 != X(1:,1:,:)")
        print_array(X(1:,1:,:),"%4d")
        exit()
    end if

    ; X(:,::-1,:)
    Xyr = sub_n(X,"y",-1,-1,-1)
    print_array_head(Xyr,"Xyr:","%4d")
    if (any(Xyr .ne. X(:,::-1,:))) then
        print("Xyr != X(:,::-1,:)")
        print_array(X(:,::-1,:),"%4d")
        exit()
    end if



    ; X(0:2:2,:,0:2) = (/ -1 /)
    Y := X
    Y(0:2:2,:,0:2) = (/ -1 /)
    asgn_to(X,(/ "x", "z" /), \ ; dimensions to select on
              (/   0,   0 /), \ ; beginning index element
              (/   2,   2 /), \ ; ending index element
              (/   2,   1 /), -1)   ; stride (not sure if neg stride works)
    print_array_head(X,"X:","%4d")
    if (any(X .ne. Y)) then
        print("X != X(0:2:2,:,0:2)=(/-1/)")
        print_array(Y,"%4d")
        exit()
    end if


    Y := X
    Y(0,:,1) = (/ Xxz_2 /)
    asgn_to_1(X,(/"x","z"/),(/0,1/),Xxz_2)
    print_array_head(X,"X:","%4d")
    if (any(X .ne. Y)) then
        print("X != X(0,:,1)=(/Xxz_2/)")
        print_array(Y,"%4d")
        exit()
    end if


    Y := X
    Y(:,1,:) = (/ Xy1_3 /)
    asgn_to_1(X,"y",1,Xy1_3)
    print_array_head(X,"X asgn_to_1:","%4d")
    if (any(X .ne. Y)) then
        print("X != X(:,1,:)=(/Xy1_3/)")
        print_array(Y,"%4d")
        exit()
    end if


    Y := X
    Y(:,:,{4}) = (/ X(:,:,1) /)
    asgn_to_1crd(X,"z",4,sub_n_1(X,"z",1))
    print_array_head(X,"X asgn_to_1crd:","%4d")
    if (any(X .ne. Y)) then
        print("X != X(:,:,{4})=(/X(:,:,1)/)")
        print_array(Y,"%4d")
        exit()
    end if


    ; This correctly fails
    ; XZ = sub_n_1(X,"y",1)
    ; print_array_head(XZ,"XZ:","%4d")
    ; asgn_to_1(XZ,"x",1,sub_n_1(X,"x",1))
    ; print_array_head(XZ,"XZ:","%4d")


    X@_FillValue = -999
    Xxz2 = sub_n_crd_pad(X,(/ "x", "z" /), \ ; dimensions to select on
                           (/  -1,   0 /), \ ; beginning index element
                           (/   2,  10 /), 0)   ; ending index element
    print_array_head(Xxz2,"Xxz2:","%4d")

    ntotidxs = 9
    idxdim  := coord_by_n("idxdim",0,ntotidxs-1,ntotidxs)
    print(idxdim)


    print(arraylist_append_record([/(/"Hi"/),(/"How", "are", "you?"/),(/"I'm", "good,", "thanks!"/)/]))

end
