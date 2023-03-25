#!/bin/sh
for file in rootfs_patch.tar.bz2 rootfs_update.sh
do
if [ -e $file ]
then
rm -r $file
fi
done
if [ ! -d patch  ]
then
echo "\33[01;31m patch directory not found \33[0m"
exit 1 
fi

	       clear
		chmod -R +x  patch 
	       tar -cvjf rootfs_patch.tar.bz2	patch 
	       sleep 1
	       ret=$?
	       if [ $ret -ne 0 ]
		then
	       echo "*************************************************************************************"
	       echo "FILE NAME : \33[01;31m$1\33[0m"
	       echo "STATUS    : \33[01;31mFAIL\33[0m"
	       echo "\033[1m\033[34 rootfs_patch.tar.bz2 creation failed\33[0m"
	       echo "*************************************************************************************"
		rm rootfs_patch.tar.bz2 > /dev/null
	       exit 1
	       fi

 echo "
#!/bin/sh

update_path=/mnt/jffs2/patch/

rm -rf \$update_path

tar -xvjf /mnt/jffs2/rootfs_patch.tar.bz2 -C /mnt/jffs2/

chmod +x -R \$update_path*

sleep 1;


\`yes | cp -r \$update_path*   /\`

sleep 1;


rm -rf \$update_path

echo "Patch applied successfully"

/vision/buzz_on

sleep 1;

poweroff
" > rootfs_update.sh

if test $1
then 
zip $1.zip rootfs_patch.tar.bz2 rootfs_update.sh -r 
sleep 1
mkdir -p /home/naresh/patch/all_usb_patches/$1 
#cp $1.zip /home/naresh/patch/all_usb_patches/$1
mv rootfs_patch.tar.bz2 rootfs_update.sh /home/naresh/patch/all_usb_patches/$1
fi

echo "*************************************************************************************"
echo "\033[1m\033[32mUSB patch created SUCCESS\33[0m"
echo "\33[01;31mrootfs_patch.tar.bz2  rootfs_update.sh\33[0m"
echo "*************************************************************************************"

exit 0
