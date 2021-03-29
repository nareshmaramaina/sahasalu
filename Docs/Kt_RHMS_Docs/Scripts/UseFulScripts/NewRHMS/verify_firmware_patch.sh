#!/bin/bash

if [ ! $1 ] 
then
	echo "$(tput bold ; tput setaf 1;)Please give argument as file .zip  
	Ex: firmware-1.1.zip $(tput sgr0)"
	exit 1
fi
if  test `echo $1 | rev | cut -c1-4 | rev` = .zip
then

	echo  "$(tput bold ; tput setaf 2;) firmware Patch size is  $(du -sh $1)$(tput sgr0)"
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


rm -r /tmp/.firmware_testing > /dev/null 2>&1

mkdir -p /tmp/.firmware_testing
unzip $1 -d /tmp/.firmware_testing 

ret=$?
if [ $ret -ne 0 ]
then
	echo "$(tput bold ; tput setaf 1;)zip extraction failed$(tput sgr0) "
	exit 1
fi
cd /tmp/.firmware_testing
if [ ! -f patch.tar.bz2 ] || [ ! -f patch.md5 ]
then
echo "$(tput bold ; tput setaf 1;) This is not a Firmware patch, patch.tar.bz2/patch.md5 file not found$(tput sgr0) "
exit 1
fi

md5sum -c patch.md5

ret=$?

if [ $ret -ne 0 ]
then
	echo "$(tput bold ; tput setaf 1;)patch.md5 failed$(tput sgr0) "
	exit 1
fi

tar -xvjf patch.tar.bz2 
ret=$?
if [ $ret -ne 0 ]
then 
	echo "$(tput bold ; tput setaf 1;)patch.tar.bz2 Extraction failed$(tput sgr0) "
	exit 1
fi
if  [ ! -d patch ]
then
	echo "$(tput bold ; tput setaf 1;) Note: patch not having a directory $(tput sgr0) "
	exit 1
fi

if [ -d patch/boot_files ]
then
	tput bold ; 
	tput setaf 2;

	cd patch/boot_files/
	if [ -f kernel.IMG ] && [ -f kernel.md5 ]
	then
		echo "Imx6 Kernel Image Found"
		md5sum -c kernel.md5
		if [ $? -ne 0 ]
		then
			echo "$(tput bold ; tput setaf 1;) kernel.md5 checksum failed $(tput sgr0) "	
			exit 1
		fi
	elif [ -f u-boot.bin ] && [ -f  uboot.md5 ]
	then
		echo "Imx6 U-boot Image Found"
		md5sum -c uboot.md5
		if [ $? -ne 0 ]
		then
			echo "$(tput bold ; tput setaf 1;) uboot.md5 checksum failed $(tput sgr0) "	
			exit 1
		fi
	elif [ -f imx25_kernel.IMG ] && [ -f kernel.md5 ]
        then
                echo "IMX25 Kernel Image Found"
                md5sum -c kernel.md5
                if [ $? -ne 0 ]
                then
                        echo "$(tput bold ; tput setaf 1;) kernel.md5 checksum failed $(tput sgr0) "    
                        exit 1
                fi
        elif [ -f imx25_u-boot.bin ] && [ -f  uboot.md5 ]
        then
                echo "IMX25 U-boot Image Found"
                md5sum -c uboot.md5
                if [ $? -ne 0 ]
                then
                        echo "$(tput bold ; tput setaf 1;) uboot.md5 checksum failed $(tput sgr0) "     
                        exit 1
                fi

	else 
		echo "$(tput bold ; tput setaf 1;)  patch/boot_files/  directory used to update Kernel or U-boot of POS devices, Missing u-boot / Kerenl images$(tput sgr0)"
		exit 1
	fi
	if [ -f kernel.IMG ] && [ -f imx25_kernel.IMG ]
        then
               echo "$(tput bold ; tput setaf 1;) kernel.IMG and imx25_kernel.IMG, should not allowed in single patch $(tput sgr0) "    
                exit 1
        fi
        if [ -f imx25_u-boot.bin ] && [ -f  u-boot.bin ]
        then
               echo "$(tput bold ; tput setaf 1;) imx25_u-boot.bin and u-boot.bin should not allowed in single patch $(tput sgr0) "    
        exit 1
        fi

	cd /tmp/.firmware_testing
fi

echo ""
echo "*********** Summary of $1 patch *******************"
tput sgr0
echo "md5sum of Total files in $1 "
print_md5sums patch
if [ -f patch/tmp/start_fw.sh ]
then
	echo "$(tput bold ; tput setaf 1;) patch/tmp/start_fw.sh file commands will run Before firmware patch apply $(tput sgr0) "
	cat patch/tmp/start_fw.sh
	echo ""
fi 
if [ -f patch/tmp/end_fw.sh ]
then
	echo "$(tput bold ; tput setaf 1;)  patch/tmp/end_fw.sh file commands will run After firmware patch apply $(tput sgr0) "
	cat patch/tmp/end_fw.sh
	echo ""
fi 
if [ -f patch/tmp/NonCritical ]
then
	echo "$(tput bold ; tput setaf 1;) Non Critical patch mode enabled  $(tput sgr0) "
	echo ""
else 
	echo "$(tput bold ; tput setaf 1;) Critical patch mode enabled  $(tput sgr0) "
	echo ""
fi
