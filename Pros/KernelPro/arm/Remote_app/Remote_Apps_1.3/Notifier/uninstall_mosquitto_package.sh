rm -rf /etc/mosq_project.conf
rm -rf /usr/bin/mosquitto_pub
rm -rf /usr/bin/mosquitto_sub
rm -rf /usr/bin/mosquitto_passwd
rm -rf /usr/bin/mosquitto
rm -rf /usr/local/etc/mosquitto/
rm -rf /lib/libmosquitto*
rm -rf /lib/libwebsockets.so.5
rm -rf /vision/Notifier
rm -rf /vision/PosDesk.sh
rm -rf /vision/PosDesk
sed -i '/Notifier/d' /home/rhms_update_script
