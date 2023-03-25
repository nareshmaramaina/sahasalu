#!/bin/bash
if [ ! $1 ]  
then
	echo "$(tput bold ; tput setaf 1;)Please give argument 1 is Application Name
	ex:) app.zip  $(tput sgr0)"
	exit 1
fi

if [ ! -e app ]
then 
	echo "$(tput bold ; tput setaf 1;)app  Directory not found in YOUR \033[1m\033[35m`pwd` directory$(tput sgr0) " 
	exit 1
fi

if  [ ! -d app ]
then
	echo "$(tput bold ; tput setaf 1;) Note: app is not a directory $(tput sgr0) "
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

rm app.tar.bz2 app.md5 > /dev/null 2>&1

#rm app.tar.bz2 app.md5 > 2&>1 /dev/null

chmod 777 -R app/*
ret=$?

if [ $ret -ne 0 ]
then
        echo "$(tput bold ; tput setaf 1;)chmod file permission accessing failed$(tput sgr0) "
        exit 1
fi


tar -cvjf app.tar.bz2 app
ret=$?

if [ $ret -ne 0 ]
then 
	echo "$(tput bold ; tput setaf 1;)app.tar.bz2 creation failed$(tput sgr0) "
	exit 1
fi
sync
md5sum app.tar.bz2 > app.md5
md5sum -c app.md5

ret=$?

if [ $ret -ne 0 ]
then
	echo "$(tput bold ; tput setaf 1;)app.md5 failed$(tput sgr0) "
	exit 1
fi

rm $1 > /dev/null 2>&1

zip $1 app.tar.bz2 app.md5 

ret=$?
if [ $ret -ne 0 ]
then
	echo "$(tput bold ; tput setaf 1;)zip creation failed$(tput sgr0) "
	exit 1
fi
	echo ""
echo "$(tput bold ; tput setaf 2;)  $1 $(tput sgr0) successfully created  app$(tput sgr0)"
	echo ""
	echo ""
echo " Summary of $1 app "
echo "$(tput bold ; tput setaf 2;)md5sum of Total files in $1 $(tput sgr0)"
print_md5sums app
if [ -f app/tmp/start_app.sh ]
then
	echo "$(tput bold ; tput setaf 1;) app/tmp/start_app.sh file commands will run Before  app apply $(tput sgr0) "
	cat app/tmp/start_app.sh
	echo ""
fi 
if [ -f app/tmp/end_app.sh ]
then
	echo "$(tput bold ; tput setaf 1;)  app/tmp/end_app.sh file commands will run Before  app apply $(tput sgr0) "
	cat app/tmp/end_app.sh
	echo ""
fi 
if [ -f app/tmp/NonCritical ]
then
	echo "$(tput bold ; tput setaf 1;) Non Critical app mode enabled  $(tput sgr0) "
	echo ""
else 
	echo "$(tput bold ; tput setaf 1;) Critical app mode enabled  $(tput sgr0) "
	echo ""
fi
rm app.tar.bz2 app.md5
