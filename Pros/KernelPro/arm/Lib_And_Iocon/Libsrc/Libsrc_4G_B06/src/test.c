
#include<stdio.h>

int main()	
{

	gl11_iodev_open();
	gl11_wifi_control(1);
	//gl11_wifi_rfcontrol(1);
	gl11_iodev_close();
	system("iwlist wlan0 scan ");

	return 0;
}


