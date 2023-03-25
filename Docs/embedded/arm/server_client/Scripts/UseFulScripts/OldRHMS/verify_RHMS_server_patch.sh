
Name=$(basename $1)
echo $Name

if test `echo $Name  | grep "patch-"` && test `echo $Name | cut -c10-13` = .zip
then 
version=`echo $Name | cut -c7-9`
clear
else echo "$(tput bold ; tput setaf 1;)Please Enter argment 1) patch-x.x.zip 2) config-patchversions $(tput sgr0)"
exit 1
fi

if test $2 
then
	Config_fileName=$2
else 
	Config_fileName=config-patchversions
fi

if [ ! -f $Config_fileName ]
then
	echo "$(tput bold ; tput setaf 1;) $Config_fileName  file not found,  Give argument 2) config-patchversions file $(tput sgr0)"
	exit 1
fi
if [ $(echo "$(head -n1 $Config_fileName | cut -c15-17) == $version" | bc) -eq 1 ] 
then 
	PREV_VER=$version
	FLAG=1
else 
	echo "*************************************************************************************"
	echo "FILES	: $(tput bold ; tput setaf 1;)1) $1 2)$Config_fileName$(tput sgr0)"
	echo "STATUS	: $(tput bold ; tput setaf 1;)FAIL$(tput sgr0)"
	echo "$(tput bold ; tput setaf 1;)$Config_fileName failed$(tput sgr0)"
	echo "$(tput bold ; tput setaf 1;)Error:version mismatch in $Config_fileName file, Add \"PATCH_VERSION=$version\" to  first line of the $Config_fileName file, Version is Depends on patch  $(tput sgr0)"
	echo "*************************************************************************************"
	exit 1
fi

for line in $(cat $Config_fileName)
do

	if [ $FLAG -eq 1 ]
	then
		FLAG=0
		echo "$(tput bold ; tput setaf 2;)PATCH_VERSION=$version	OK$(tput sgr0)"
		continue
	fi

	CURRENT_VER=$(echo $line | cut -c15-17)
	Status=$(echo "$CURRENT_VER < $PREV_VER" | bc)
	if [ $Status -eq 1 ]
	then
		echo "$(tput bold ; tput setaf 2;)PATCH_VERSION=$CURRENT_VER	OK$(tput sgr0)"
		PREV_VER=$CURRENT_VER
	else
		echo "$(tput bold ; tput setaf 1;)PATCH_VERSION=$CURRENT_VER      ERROR$(tput sgr0)"
		echo "$(tput bold ; tput setaf 1;)Error: Wrong order version $CURRENT_VER in $Config_fileName"
		echo "Note: config-patchversions file should have Higher order to lower order patch versions$(tput sgr0)"
		exit 1
	fi
done


rm -rf testing > /dev/null
unzip $1 -d testing > /dev/null
cd testing
md5sum -c patch.md5 > /dev/null 
ret=$?
cd ..
if test $ret -ne 0
then
	rm -rf testing
	echo "*************************************************************************************"
	echo "FILE NAME : $(tput bold ; tput setaf 1;)$1$(tput sgr0)"
	echo "STATUS    : $(tput bold ; tput setaf 1;)FAIL$(tput sgr0)"
	echo "$(tput bold ; tput setaf 1;)md5sum failed$(tput sgr0)"
	echo "*************************************************************************************"
	exit 1

else 
	tar -xvjf testing/patch.tar.bz2  -C testing
	du -sh testing/*
	ret=$?
	if [ $ret -eq 0 ]
	then
		echo "*************************************************************************************"
		echo "FILES	: $(tput bold ; tput setaf 1;)$1	$Config_fileName$(tput sgr0)"
		echo "STATUS	: $(tput bold ; tput setaf 2;)SUCCESS$(tput sgr0)"
		#echo "PATCH_VERSION=$version" > config-patchversions
		#cat config-patchversions
		echo "*************************************************************************************"

	else 
		echo "*************************************************************************************"
		echo "FILE NAME : $(tput bold ; tput setaf 1;)$1$(tput sgr0)"
		echo "STATUS    : $(tput bold ; tput setaf 1;)FAIL$(tput sgr0)"
		echo "\033[1m\033[34patch.tar.bz2 EXTRATION failed$(tput sgr0)"
		echo "*************************************************************************************"
	fi

fi

rm -rf testing
exit 0
