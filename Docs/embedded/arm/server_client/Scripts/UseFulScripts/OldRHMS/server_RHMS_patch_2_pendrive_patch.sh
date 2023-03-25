#!/bin/sh

if test `basename $1  | grep "patch-"` && test `echo $1 | cut -c10-13` = .zip
then 
version=`echo $1 | cut -c7-9`
else echo "\33[01;31mPlease Enter argment 1) patch-x.x.zip\33[0m"
exit 1
fi

for file in patch tmp  patch.md5  patch.tar.bz2 rootfs_patch.tar.bz2 rootfs_update.sh
do
if [ -e $file ]
then
rm -r $file
fi
done 

#extract_patch
unzip $1 > /dev/null
md5sum -c patch.md5 > /dev/null 
ret=$?
patch_sum=`cat patch.md5| cut -d ' ' -f1`
rm patch.md5
if test $ret -ne 0
then
echo "*************************************************************************************"
echo "FILE NAME : \33[01;31m$1\33[0m"
echo "STATUS    : \33[01;31mFAIL\33[0m"
echo "\033[1m\033[34mmd5sum failed\33[0m"
echo "*************************************************************************************"
rm  patch.tar.bz2 > /dev/null
exit 1
fi
tar -xvjf patch.tar.bz2 > /dev/null 
ret=$?
	       rm patch.tar.bz2
	       if [ $ret -ne 0 ]
		then
	       echo "*************************************************************************************"
	       echo "FILE NAME : \33[01;31m$1\33[0m"
	       echo "STATUS    : \33[01;31mFAIL\33[0m"
	       echo "\033[1m\033[34patch.tar.bz2 EXTRATION failed\33[0m"
	       echo "*************************************************************************************"
	       exit 1
	       fi






mkdir -p patch/etc/
		
echo "PATCH_VERSION=$version
PATCH_DATE=$( date +%d%m%Y-%H:%M )
PATCH_MD5SUM=$patch_sum" > patch/etc/visiontek_release
	       sleep 1 
	       clear
if [ ! -e patch/tmp/start_fw.sh ]
then
echo "\33[01;31m patch/tmp/start_fw.sh file not found \33[0m "
#exit 1
fi 




 echo "
#!/bin/sh

update_path=/mnt/jffs2/patch/

rm -rf \$update_path

tar -xvjf /mnt/jffs2/rootfs_patch.tar.bz2 -C /mnt/jffs2/

chmod +x -R \$update_path

" > rootfs_update.sh


cmd=$(cat patch/tmp/start_fw.sh | grep "/mnt/sysuser/Firmware-Upgrade/patch" | grep "chmod" | grep "\-R ")

if [  $? -eq 0 ]  && [  echo $(echo $cmd | grep "+x" ) ] ||  [ echo $(echo $cmd | grep "777" ) ]
then
echo " "
sed -i 's:$cmd::'  patch/tmp/start_fw.sh	
else 
echo "\33[01;31m chmod 777 -R /mnt/sysuser/Firmware-Upgrade <-- command not found in patch/tmp/start_fw.sh \33[0m "
exit 1
fi
#before applying patch 


if [ -e patch/tmp/start_fw.sh ]
then 
cat patch/tmp/start_fw.sh  |  sed  's:/mnt/sysuser/Firmware-Upgrade/patch:\$update_path:g' >> 	rootfs_update.sh
rm -f patch/tmp/start_fw.sh
fi
	
echo "

\`yes | cp -r \$update_path*   /\`

sleep 1;

" >> rootfs_update.sh

#After  applying patch 
if [ -e patch/tmp/end_fw.sh ]
then 
cat patch/tmp/end_fw.sh |  sed  's:/mnt/sysuser/Firmware-Upgrade/patch:\$updatepath:g'  >> 	rootfs_update.sh
rm -f patch/tmp/end_fw.sh
fi	

no=$(ls patch/tmp | wc -l)
                if [ $no -eq 0 ]
	        then
		rm patch/tmp -r 	
                fi

	sleep 1
	       tar -cvjf rootfs_patch.tar.bz2	patch 
	       ret=$?
	       sleep 1
	       if [ $ret -ne 0 ]
		then
	       echo "*************************************************************************************"
	       echo "FILE NAME : \33[01;31m$1\33[0m"
	       echo "STATUS    : \33[01;31mFAIL\33[0m"
	       echo "\033[1m\033[34 rootfs_patch.tar.bz2 creation failed\33[0m"
	       echo "*************************************************************************************"
		rm rootfs_patch.tar.bz2 rootfs_update.sh  > /dev/null
	       exit 1
	       fi



echo "

rm -rf \$update_path

echo "Patch applied successfully"

/vision/buzz_on

sleep 1;

poweroff
" >> rootfs_update.sh





echo "*************************************************************************************"
echo "STATUS    : \033[1m\033[32mPendrive patch created SUCCESS\33[0m"
echo "\33[01;31mrootfs_patch.tar.bz2  rootfs_update.sh\33[0m"
echo "*************************************************************************************"


exit 0
