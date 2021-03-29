

#!/bin/bash
if [ ! $1 ] || [ `echo ${#1}` -ne 3 ] 
then
	echo "$(tput bold ; tput setaf 1;)Please give argument 1  i.e, Version Number
	ex:) 1.1   $(tput sgr0)"
	exit 1
fi

if [ ! -e patch ]
then 
	echo "$(tput bold ; tput setaf 1;)patch  Directory not found in YOUR \033[1m\033[35m`pwd` directory$(tput sgr0) " 
	exit 1
fi

if  [ ! -d patch ]
then
	echo "$(tput bold ; tput setaf 1;) Note: patch is not a directory $(tput sgr0) "
	exit 1
fi

rm patch.tar.bz2 patch.md5 > /dev/null 2>&1

#rm patch.tar.bz2 patch.md5 > 2&>1 /dev/null

chmod 777 -R patch/*

if [ ! -e patch/tmp/start_fw.sh ]
then
	echo "$(tput bold ; tput setaf 1;) patch/tmp/start_fw.sh file not found ( create file ) and also add \"chmod 777 -R /mnt/sysuser/Firmware-Upgrade/patch/*\" command to the same file $(tput sgr0) "
	exit 1
fi 


cat patch/tmp/start_fw.sh | grep "/mnt/sysuser/Firmware-Upgrade" | grep "chmod" | grep "\-R "

if [ $? -ne 0 ]
then
	echo "$(tput bold ; tput setaf 1;) chmod 777 -R /mnt/sysuser/Firmware-Upgrade/patch/* <-- command not found in patch/tmp/start_fw.sh $(tput sgr0) "
	exit 1
fi


tar -cvjf patch.tar.bz2 patch
ret=$?

if [ $ret -ne 0 ]
then 
	echo "$(tput bold ; tput setaf 1;)patch.tar.bz2 creation failed$(tput sgr0) "
	exit 1
fi

sleep 2
md5sum patch.tar.bz2 > patch.md5
sleep 1

md5sum -c patch.md5

ret=$?

if [ $ret -ne 0 ]
then
	echo "$(tput bold ; tput setaf 1;)patch.md5 failed$(tput sgr0) "
	exit 1
fi

rm patch-$1.zip > /dev/null 2>&1

zip patch-$1.zip patch.tar.bz2 patch.md5 -r

ret=$?
if [ $ret -ne 0 ]
then
	echo "$(tput bold ; tput setaf 1;)zip creation failed$(tput sgr0) "
	exit 1
fi
echo "PATCH_VERSION=$1" > config-patchversions

echo "$(tput bold ; tput setaf 1;)  patch-$1.zip $(tput sgr0)config-patchversions 
$(tput bold ; tput setaf 2;)  successfully created$(tput sgr0)"

rm patch.tar.bz2 patch.md5
