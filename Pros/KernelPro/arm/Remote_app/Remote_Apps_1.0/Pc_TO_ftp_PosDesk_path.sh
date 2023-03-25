if test $1
then
	
	curl  --connect-timeout 32 --max-time 64 -s -u rnd:rnd123 -T $1 ftp://115.111.229.10/PosDesk_Update/PATCHTEST/
	
	
	if test $? -eq 0
	then
		echo "Successfully Uploaded $1 file"
		echo "If You Want To Download at Pos side, Enter Below Cmd"
		tput  bold
		tput setaf  1
		file=$(basename $1)
		echo "/usr/bin/wget -c -T 24  ftp://rnd:rnd123@115.111.229.10/PosDesk_Update/$file  -O /tmp/$file"
		tput sgr0
		echo " -O option for Your ------Pos Side Directory ----------, And After give chmod +x permissions, if file is executable"
	else echo $1 file Upload Failed
	fi
else 
	echo "Give arg 1) File name "
fi
