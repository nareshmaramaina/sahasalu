out=$(rhms_run $1 | egrep "FTP_PATH_FIRMWARE|FirmWarePatchVersion|ProjectName")
if [ $? -ne 0 ]
then
	echo $out
	exit 1
fi
Link=$(echo $out | grep FTP_PATH_FIRMWARE | cut -d '>' -f2 | cut -d '<' -f1)

file="config-patchversions"

rm /tmp/RHMS_TEST -r
mkdir /tmp/RHMS_TEST 
cd /tmp/RHMS_TEST
echo $Link/$file
wget $Link/$file  >/dev/null 2>&1

if [ $? -ne 0 ]
then
	echo "File Download Fail "
	exit 0
else echo $file Download success
fi
tput bold ;
tput setaf 2;
echo $out
cat config-patchversions 
Versions=$(cut /tmp/RHMS_TEST/config-patchversions -d '=' -f2)
for version in $(echo $Versions)
do
	file=patch-$version.zip
	echo $file Downloading...
	
	wget $Link/$file  >/dev/null 2>&1
	
	if [ $? -ne 0 ]
	then
		echo "wget $Link/$file File Download Fail "
		md5sum $file
		exit 0
	else
		echo "$file File Download Success"
		md5sum $file	
	fi
done
ls -lrth /tmp/RHMS_TEST
tput sgr0
