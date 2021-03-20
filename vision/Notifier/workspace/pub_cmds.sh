
if test $1 -a $2 
then
	if test  ${#1} -ne 17
	then
		echo "Please Enter correct macid ex: 7C:F0:BA:06:01:5D"
		exit 1
	fi
	if test ! -f $2
	then
		echo "$2 file not found"
		exit 1
	fi

else 
	echo "Please Give argument 1) macid and argument 2)mosq_project.conf file"
	exit 1
fi
TWO_DIGITS=$(echo $1 | cut -d ':' -f6 )
if test ${#TWO_DIGITS} -eq 0
then
	echo "incorrect macid, Please Enter format macid ex: 7C:F0:BA:06:01:5D"
	exit 1
fi

port=$(cat $2 | grep PORT | cut -d ':' -f2)
project=$(cat $2 | grep PROJECT | cut -d ':' -f2)
ipaddr=$(cat $2 | grep IPADDR | cut -d ':' -f2)

if test ${#project} -eq 0 -o  ${#ipaddr} -eq 0 -o ${#port} -eq 0 
then
	echo "project/ipaddr/port  not found"
	exit 1
fi


if test  $port -ge 65534
then
	echo "Port Number should be  with in the range of 65534"
	exit 1
fi
if test  ${#ipaddr} -lt 11
then
	echo "incorrect ip address"
	exit 1
fi
DIGIT1=`echo $TWO_DIGITS | cut -c1`
NUM=`printf "%d" 0X$TWO_DIGITS`
NUM1=`printf "%d" 0X$DIGIT1`

MAX_TOPIC=$project
MEDIUM_TOPIC=$(echo "$project""_M_$NUM1")
LOW_TOPIC=$(echo "$project""_L_$NUM")

MAX_PORT=$port
MEDIUM_PORT=$(expr $NUM1  + $port + 1 )
LOW_PORT=$(expr $NUM  + 16 + $port + 1 )
tput  bold
tput setaf  1
echo "mosquitto_pub -p $MAX_PORT -t $MAX_TOPIC -m \"Maximum connections topic command\" -q 2" 
echo "mosquitto_pub -p $MEDIUM_PORT -t $MEDIUM_TOPIC -m \"Medium connections topic command\" -q 2" 
echo "mosquitto_pub -p $LOW_PORT -t $LOW_TOPIC -m \"minimum connections topic command\" -q 2" 
tput sgr0



tput setaf  3
echo "All Modes Possible Meassages"
tput sgr0
tput  bold
tput setaf  4
echo "		\"#EXIT#IF#NOT#7C:F0:BA:06:01:00#\" `tput setaf  0` <--- In Any mode You can Use this message"
echo "		Exit  client connection if it is not matched with given macid, Remove connection from server until mode time."
tput sgr0

tput setaf  3
echo "Maximum Mode"
tput sgr0
tput  bold
tput setaf  4
echo "		\"#UPDATE#\"`tput setaf  0` Message to run rhms and Download binaries in device. If any new Update found, these are Download and Update client"
tput sgr0
tput  bold
tput setaf  4
echo "Before Using this command you should be uploaded the  target file into proper ftp path"
#echo "		\"#DOWNLOAD#ALL# FILENAME\" `tput setaf  0` This Command will DOWNLOAD ALL DEVICES THAT ARE SUBSCRIBED TO PATCHTEST, and Download from ftp://rnd:rnd123@115.111.229.10/PosDesk_Update/$MAX_TOPIC/(FILENAME)  <-- Path( Mention FILENAME is whatever you want to download)" 
echo "		\"#DOWNLOAD#ALL#TO#DESTINATION_DIRECTORY# FILENAME\" `tput setaf  0` (DESTINATION_DIRECTORY) Mention the directory path, That Where you want to keep the file in the device. And this Command will DOWNLOAD into ALL DEVICES, who are SUBSCRIBED TO PATCHTEST topic and It is Download from ftp://rnd:rnd123@115.111.229.10/PosDesk_Update/$MAX_TOPIC/(FILENAME)  <-- Path( Mention FILENAME is whatever you want to download)" 
tput sgr0
tput  bold
tput setaf  4
echo "Before Using this command you should be uploaded the  target file into proper ftp path"
echo "		\"#DOWNLOAD#7C:F0:BA:06:01:5D#TO#DESTINATION_DIRECTORY# FILENAME\" `tput setaf  0` (DESTINATION_DIRECTORY) Mention the directory path, That Where you want to keep the file in the device. And This Command will DOWNLOAD That particular 7C:F0:BA:06:01:5D macid  DEVICE only Download file from ftp://rnd:rnd123@115.111.229.10/PosDesk_Update/$MAX_TOPIC/(FILENAME)  <-- Path( Mention FILENAME is whatever you want to download)" 

#echo "		\"#DOWNLOAD#7C:F0:BA:06:01:5D# FILENAME\" `tput setaf  0` This Command will DOWNLOAD That particular 7C:F0:BA:06:01:5D macid  DEVICE only Download file from ftp://rnd:rnd123@115.111.229.10/PosDesk_Update/$MAX_TOPIC/(FILENAME)  <-- Path( Mention FILENAME is whatever you want to download)" 
tput sgr0
tput  bold
tput setaf  4
echo "		\"#UPLOAD#ALL# REPORT\" `tput setaf  0` This Command will Upload the file /var/log/.mosquitto/All_Modes_Report, i.e, ALL $MAX_TOPIC subscribers to ftp://rnd:rnd123@115.111.229.10/PosDesk_Uploads/$MAX_TOPIC/(FILENAME)  <-- Path(  FILENAME is .Machineid/Macid_report)" 
tput sgr0
tput  bold
tput setaf  4
echo "		\"#UPLOAD#ALL# /usr/bin/autoapn\" `tput setaf  0` This Command will Upload the file /var/log/.mosquitto/All_Modes_Report, i.e, ALL $MAX_TOPIC subscribers to ftp://rnd:rnd123@115.111.229.10/PosDesk_Uploads/$MAX_TOPIC/(FILENAME)  <-- Path(  FILENAME is .Machineid/Macid_report) NOTE:Fielename not extractly what your send file name"  
tput sgr0
tput  bold
tput setaf  4
echo "		\"#UPLOAD#7C:F0:BA:06:01:5D# FILENAME\" `tput setaf  0` This Command will Upload That particular 7C:F0:BA:06:01:5D macid  DEVICE only to ftp://rnd:rnd123@115.111.229.10/PosDesk_Update/$MAX_TOPIC/(FILENAME)  <-- Path( Mention FILENAME is .Machineid/Macid_report) NOTE:Fielename not extractly what your send file name" 
tput sgr0

#tput  bold

tput setaf  3
echo "Medium Mode"
tput sgr0
tput  bold
tput setaf  4
echo "		This Mode is used to run  commands on device, i.e, Linux commands only ex:ls cp mv etc.," 
tput sgr0
tput setaf  3
echo "Minimum Mode"
tput sgr0
tput  bold
tput setaf  4
echo "		 #GET#REMOTE#7C:F0:BA:06:01:00# `tput setaf  0` To take remote of particular macid"
tput sgr0
tput  bold
tput setaf  4
echo "		 #GET#REMOTE#7C:F0:BA:06:01:00#PORT#2223# `tput setaf  0` You can give different Port Number to PosDesk client on ip address 115.111.229.7 only"
tput sgr0
tput  bold
tput setaf  4
echo "		 #GET#REMOTE#7C:F0:BA:06:01:00#IP#115.111.229.10#PORT#2222# `tput setaf  0` You Can give also your own PUBLIC IP and PORT, otherwise PosDesk application will take default Ip Address: 115.111.229.7 and Port no: 2222 "
tput sgr0

#echo MAX_TOPIC= $MAX_TOPIC 
#echo MEDIUM_TOPIC= $MEDIUM_TOPIC 
#echo LOW_TOPIC= $LOW_TOPIC
#echo MAX_PORT= $MAX_PORT 
#echo MEDIUM_PORT= $MEDIUM_PORT
#echo LOW_PORT= $LOW_PORT
