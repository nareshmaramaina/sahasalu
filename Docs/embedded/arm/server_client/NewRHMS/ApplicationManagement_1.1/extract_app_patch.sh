#!/bin/sh
if test $1
then
	FILENAME=$(basename $1)
else 
	echo "$(tput bold ; tput setaf 1;) Please Enter argment 1) app.zip$(tput sgr0)"
exit 1
fi

for file in app  app.md5  app.tar.bz2 
do
if [ -e $file ]
then
rm -r $file
fi
done 

unzip $1 
tar -xvf app.tar.bz2
rm app.tar.bz2 app.md5
