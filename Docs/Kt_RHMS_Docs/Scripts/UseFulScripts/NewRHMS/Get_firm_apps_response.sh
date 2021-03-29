if test $1
then
echo "" 
else 
	echo Please Give Serial Number as argument
	exit 0
fi

curl https://rhms2.visiontek.co.in/api/FirmwareStatus?serialNo=$1 > .Testing.xml
echo ""
echo "************ SerialNo=$1 Firmware Response *************"
tput sgr0
xmllint --format .Testing.xml
echo ""
tput bold ; tput setaf 1;
echo "***********************************************"

curl https://rhms2.visiontek.co.in/api/ApplicationStatus?serialNo=$1 > .Testing.xml
echo ""
echo "************ SerialNo=$1 Applications Response *************"
tput sgr0
xmllint --format .Testing.xml
echo ""
tput bold ; tput setaf 1;
echo "***********************************************"
tput sgr0
