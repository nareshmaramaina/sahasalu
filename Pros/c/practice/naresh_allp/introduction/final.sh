x=sample.txt
echo "From: <$1>">$x
echo "To: <$2>">>$x
echo "subject:
Reply-to:<$2>" >> $x
echo "Content-Type:$3 file
Content-Transfer-Encoding: base64
Content-Disposition: $3 ">> $x
base64 $3 >> $x
echo " --MULTIPART-MIXED-BOUNDARY" >> $x
