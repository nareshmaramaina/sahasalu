#!/bin/bash

if [ ! $1 ]
then
	echo "Please give file name argument"
	exit
fi

if [ ! -f $1 ]
then
	echo "$1 file not found"
	exit 
fi

filename=$(basename $1)
#filename=$(echo $1 | rev | cut -d '/' -f1 | rev)
echo $filename
ret=$(curl --upload-file $1 https://transfer.sh/$filename)

echo $ret

