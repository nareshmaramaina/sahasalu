

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

rm patch.tar.bz2 patch.md5 > /dev/null 2>&1

#rm patch.tar.bz2 patch.md5 > 2&>1 /dev/null

chmod 777 -R patch/*
ret=$?

if [ $ret -ne 0 ]
then
        echo "$(tput bold ; tput setaf 1;)chmod file permission accessing failed$(tput sgr0) "
        exit 1
fi

if [ -d patch/boot_files ]
then
	tput bold ; 
	tput setaf 2;

	cd patch/boot_files/
	if [ -f kernel.IMG ] && [ -f kernel.md5 ]
	then
		echo "IMX6 Kernel Image Found"
		md5sum -c kernel.md5
		if [ $? -ne 0 ]
		then
			echo "$(tput bold ; tput setaf 1;) kernel.md5 checksum failed $(tput sgr0) "			
			exit 1	

		fi
	elif [ -f u-boot.bin ] && [ -f  uboot.md5 ]
	then
		echo "IMX6 U-boot Image Found"
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
	tput sgr0;
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
	cd ../../ 
fi

tar -cvjf patch.tar.bz2 patch
ret=$?

if [ $ret -ne 0 ]
then 
	echo "$(tput bold ; tput setaf 1;)patch.tar.bz2 creation failed$(tput sgr0) "
	exit 1
fi
sync
md5sum patch.tar.bz2 > patch.md5
md5sum -c patch.md5

ret=$?

if [ $ret -ne 0 ]
then
	echo "$(tput bold ; tput setaf 1;)patch.md5 failed$(tput sgr0) "
	exit 1
fi

rm firmware-$1.zip > /dev/null 2>&1

zip firmware-$1.zip patch.tar.bz2 patch.md5 

ret=$?
if [ $ret -ne 0 ]
then
	echo "$(tput bold ; tput setaf 1;)zip creation failed$(tput sgr0) "
	exit 1
fi
	echo ""
echo "$(tput bold ; tput setaf 2;)  firmware-$1.zip $(tput sgr0) successfully created firmware patch$(tput sgr0)"
	echo ""
	echo ""
echo " Summary of firmware-$1.zip patch "
echo "$(tput bold ; tput setaf 2;)md5sum of Total files in firmware-$1.zip $(tput sgr0)"
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
rm patch.tar.bz2 patch.md5
