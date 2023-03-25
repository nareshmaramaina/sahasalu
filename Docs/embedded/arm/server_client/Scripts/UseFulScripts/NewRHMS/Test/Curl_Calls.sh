curl  --cacert curl-ca-bundle.crt  -XPOST -H "content-type: application/xml" https://rhms2.visiontek.co.in/api/HardwareStatus -d @./Hardware_Status.xml 1> ./Hardware_response.xml

curl  --cacert curl-ca-bundle.crt -XPOST -H "content-type: application/xml" https://rhms2.visiontek.co.in/api/BootTimeStatus -d @./BootTime_Status.xml 1> ./BootTime_response.xml

curl  -XPOST -H "content-type: application/xml" https://rhms2.visiontek.co.in/api/HealthStatus -d @./Health_Status.xml 1>./Health_response.xml

curl https://rhms2.visiontek.co.in/api/FirmwareStatus?serialNo=111817161517 
curl https://rhms2.visiontek.co.in/api/ApplicationStatus?serialNo=111817161517
