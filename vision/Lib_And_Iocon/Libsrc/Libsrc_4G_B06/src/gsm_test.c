#include<stdio.h>
#include<stdlib.h>


inline void  msleep(int val)
{
	usleep(val*1000);
}


int main()
{
	int ret=0;
	ret=gl11_iodev_open();
	gl11_gsm_pwroff();
	sleep(1);
	ret=gl11_gsm_select(1,115200);
	if(ret!=0)
	{
		fprintf(stdout,"gsm power on failure\n");
		return -1;
	}
	gl11_gsm_reset_pwr_ctrl(0);
	msleep(100);
	gl11_gsm_reset_pwr_ctrl(1);
	sleep(1);
	gl11_gsm_reset_pwr_ctrl(0);
	sleep(2);
	gl11_iodev_close();
	return 0;
}












