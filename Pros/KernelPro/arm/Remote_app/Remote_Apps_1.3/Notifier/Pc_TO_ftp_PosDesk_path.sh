if test $1
then

	if test ! -f  $1 
	then
		echo " $1 file not found, for Uploading"
		exit 1
	fi
	curl  --connect-timeout 32 --max-time 64 -s -u rnd:rnd123 -T $1 ftp://115.111.229.10/PosDesk_Update/
	if test $? -eq 0
	then
		echo "Successfully Uploaded $1 file"
		echo "If You Want To Download at Pos side, Enter Below Cmds"
		tput  bold
		tput setaf  1
		file=$(basename $1)
		echo "/usr/bin/wget -c -T 24  ftp://rnd:rnd123@115.111.229.10/PosDesk_Update/$file  -O /tmp/$file"
		echo ""
		echo "chmod +x /tmp/$file"
		tput sgr0
		echo " -O option for Your ------Pos Side Download Directory ----------, And After give chmod +x permissions, if file is executable, then copy appropriate place"
	else echo $1 file Upload Failed
	fi
else 
	echo "Give arg 1) File name "
fi
