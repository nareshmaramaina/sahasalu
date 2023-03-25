
if [ ! -f ./PcDesk ]
then	
	echo "./PcDesk not found"
	exit 0
fi
ret=1

kill -9 `pidof PcDesk`

while   true
do
	if test $1 
	then
	./PcDesk $1
	elif test $2
	then
		./PcDesk $1 $2 
	else ./PcDesk
	fi


	ret=$?
	if [ $ret -eq 0 ] 
	then
		echo "Successfully Exiting PcDesk.."
		break
	else echo " ret = $ret, PcDesk failed retrying.."
	fi

	sleep 1
done
