#!/bin/sh
if test $1
then
	FILENAME=$(basename $1)
else 
	echo "$(tput bold ; tput setaf 1;) Please Enter argment 1) firmware-x.x.zip$(tput sgr0)"
exit 1
fi

for file in patch  patch.md5  patch.tar.bz2 
do
if [ -e $file ]
then
rm -r $file
fi
done 

unzip $1 
tar -xvf patch.tar.bz2
rm patch.tar.bz2 patch.md5
