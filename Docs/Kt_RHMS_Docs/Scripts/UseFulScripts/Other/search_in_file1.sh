if test ! -f $1 
then
	echo " Please give argument arg1 target file, arg2 search content file"
	echo " \"$1\"  file not found "
	exit 1
fi
if test ! -f $2 
then
	echo " Please give argument arg1 target file, arg2 search content file"
	echo " \"$2\" file not found "
	exit 1
fi

for line in $(cat $2)
do 


	if test  $3 -a $3 = -v
	then
		grep $line $1 
		res=$?
	else 
		grep -i $line $1 > /dev/null
	#	grep $line $1 
		res=$?
	fi
	if [ $res -eq 0 ]
	then
		echo "$line OK"
	else
		echo "$line ERROR"
	fi
done
