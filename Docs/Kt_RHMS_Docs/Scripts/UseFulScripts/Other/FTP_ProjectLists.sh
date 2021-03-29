if [ $1 ]
then
if [ $2 ] 
then
echo $2 |grep -q info 
if [ $? -eq 0 ]
then

curl --connect-timeout 32 --max-time 64 -s -u rnd:rnd123  ftp://115.111.229.10/PROJECTS/$1/$2
else 
curl --connect-timeout 32 --max-time 64 -s -u rnd:rnd123  ftp://115.111.229.10/PROJECTS/$1/$2.info

fi
exit
fi
curl --connect-timeout 32 --max-time 64 -s -u rnd:rnd123  ftp://115.111.229.10/PROJECTS/$1/
Devices=$(curl --connect-timeout 32 --max-time 64 -s -u rnd:rnd123  ftp://115.111.229.10/PROJECTS/$1/ | wc -l )
echo $1 = $Devices
exit 
fi

Projects=$(curl --connect-timeout 32 --max-time 64 -s -u rnd:rnd123  ftp://115.111.229.10/PROJECTS/ |cut -c60-84)

for project in $(echo $Projects)
do

Devices=$(curl --connect-timeout 32 --max-time 64 -s -u rnd:rnd123  ftp://115.111.229.10/PROJECTS/$project/ | wc -l )
echo $project = $Devices
Total=$(expr $Total + $Devices  )
done

echo Total Projects  Count = $Total
