#!/bin/bash
# . my_functions.sh

if [ $# -ne 5 ]; then
  echo $0" iyb imb iye ime n_mo_inc"
  exit
fi

iyb=$1
imb=$2
iye=$3
ime=$4
n_mo_inc=$5

printf -v iy4 "%04d" $iyb
printf -v im2 "%02d" $imb

bdate=$(date +'%Y-%m-%d' -d "$iy4-$im2-01")
echo "bdate "$bdate

printf -v iy4 "%04d" $iye
printf -v im2 "%02d" $ime

edate=$(date +'%Y-%m-%d' -d "$iy4-$im2-01")
echo "edate "$edate
edate_s=$(date -d "$edate" +%s)

cdate=$bdate
echo "cdate "$cdate
cdate_s=$(date -d "$cdate" +%s)

while [ $edate_s -ge $cdate_s ]
do
  read iy4 im2 id2 <<< ${cdate//[-]/ }
  echo $iy4" "$im2" "$id2
  cdate=$(date +'%Y-%m-%d' -d "$cdate+$n_mo_inc months")
  cdate_s=$(date -d "$cdate" +%s)
done
