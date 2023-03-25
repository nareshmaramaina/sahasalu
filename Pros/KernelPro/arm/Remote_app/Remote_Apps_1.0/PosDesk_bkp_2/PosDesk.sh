if [ ! -f /vision/PosDesk ]
then	
	echo "/vision/PosDesk not found"
	exit 0
fi
ret=1

if [ ! -x /vision/PosDesk ] 
then
chmod +x /vision/PosDesk
fi

if [ ! -f /tmp/.pidsof_posdesk ]
then	
kill -9 `cat /tmp/.pidsof_posdesk`
fi

echo $$ > /tmp/.pidsof_posdesk 

kill -9 `pidof PosDesk`

for i in $(seq 50)
do


	if test $2  
	then
		echo "Arg1= $1 and Arg2 = $2"
		/vision/PosDesk $1 $2
		ret=$?
	elif test $1
	then
		echo "Arg1= $1"
		/vision/PosDesk $1
		ret=$?

	else 
		/vision/PosDesk
		ret=$?
	fi

	if [ $ret -eq 0 ] 
	then
		echo "Successfully Exiting PosDesk.."
		break
	else echo " ret = $ret, PosDesk failed retrying... $i "
	fi

	sleep 4

	if test $i -gt 25
	then
		echo "Sleep 60 form PosDesk"
		sleep 60
	fi

done
