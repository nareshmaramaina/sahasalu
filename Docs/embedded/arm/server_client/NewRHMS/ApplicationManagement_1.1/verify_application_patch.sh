#!/bin/bash

if [ ! $1 ] 
then
	echo "$(tput bold ; tput setaf 1;)Please give argument as file .zip  
	Ex: Application-1.1.zip $(tput sgr0)"
	exit 1
fi
if  test `echo $1 | rev | cut -c1-4 | rev` = .zip
then

	echo  "$(tput bold ; tput setaf 1;) Application Patch size is  $(du -sh $1)$(tput sgr0)"
else
	echo "$(tput bold ; tput setaf 1;)Please Enter argment as xxxx.zip name file  $(tput sgr0)"
	exit 1
fi




print_md5sum()
{

	for file in `ls -a $1`
	do
		if [ $file = "."  ] || [ $file = ".." ]
		then
			continue;
		fi
		if [ -f $1/$file ]
		then
			md5sum $1/$file
		else print_md5sum $1/$file
		fi
	done
}
print_md5sums()
{
	if test $1  
	then 
		if test   ! -d $1 
		then
			echo "Please Give argment 1 as directory"
			exit 1
		fi
	else 
		echo "Please Give argment 1, as directory"
		exit 1
	fi
	for file in `ls -a $1`
	do
		if [ $file = "."  ] || [ $file = ".." ]
		then
			continue;
		fi

		if [ -f $1/$file ]
		then
			md5sum $1/$file
		else 
			print_md5sum $1/$file 
		fi


	done
}


rm -r /tmp/.Application_testing > /dev/null 2>&1

mkdir -p /tmp/.Application_testing
unzip $1 -d /tmp/.Application_testing 

ret=$?
if [ $ret -ne 0 ]
then
	echo "$(tput bold ; tput setaf 1;)zip extraction failed$(tput sgr0) "
	exit 1
fi
cd /tmp/.Application_testing
if [ ! -f app.tar.bz2 ] || [ ! -f app.md5 ]
then
echo "$(tput bold ; tput setaf 1;) This is not a application patch, app.tar.bz2/app.md5 file not found$(tput sgr0) "
exit 1
fi

md5sum -c app.md5

ret=$?

if [ $ret -ne 0 ]
then
	echo "$(tput bold ; tput setaf 1;)app.md5 failed$(tput sgr0) "
	exit 1
fi

tar -xvjf app.tar.bz2 
ret=$?
if [ $ret -ne 0 ]
then 
	echo "$(tput bold ; tput setaf 1;)app.tar.bz2 Extraction failed$(tput sgr0) "
	exit 1
fi
if  [ ! -d app ]
then
	echo "$(tput bold ; tput setaf 1;) Note: not having a app directory $(tput sgr0) "
	exit 1
fi
echo ""
echo "$(tput bold ; tput setaf 2;)***** Summary of $1 Patch *****$(tput sgr0)"
echo "md5sum of Total files in $1 "
print_md5sums app
if [ -f app/tmp/start_app.sh ]
then
	echo "$(tput bold ; tput setaf 1;) app/tmp/start_app.sh file commands will run Before Application patch apply $(tput sgr0) "
	cat app/tmp/start_app.sh
	echo ""
fi 
if [ -f app/tmp/end_app.sh ]
then
	echo "$(tput bold ; tput setaf 1;)  app/tmp/end_app.sh file commands will run After Application patch apply $(tput sgr0) "
	cat app/tmp/end_app.sh
	echo ""
fi 
if [ -f app/tmp/NonCritical ]
then
	echo "$(tput bold ; tput setaf 1;) Non Critical patch mode enabled  $(tput sgr0) "
	echo ""
else 
	echo "$(tput bold ; tput setaf 1;) Critical patch mode enabled  $(tput sgr0) "
	echo ""
fi
