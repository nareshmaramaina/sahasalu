#!/bin/sh
if test $1
then
	FILENAME=$(basename $1)
else 
	echo "$(tput bold ; tput setaf 1;) Please Enter argment 1) patch-x.x.zip$(tput sgr0)"
exit 1
fi

if test `echo $FILENAME  | grep "patch-"` && test `echo $FILENAME | cut -c10-13` = .zip
then 
echo ""
else 
	echo "$(tput bold ; tput setaf 1;) Please Enter argment 1) patch-x.x.zip, x.x  should be like  only 1.1 2.1 (3digits) $(tput sgr0)"
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
tar -xvjf patch.tar.bz2
rm patch.tar.bz2 patch.md5
