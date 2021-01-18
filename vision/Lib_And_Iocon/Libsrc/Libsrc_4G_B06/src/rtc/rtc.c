#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <linux/input.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <net/if.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>

int lib_checkdriver(char *drv);

struct rtc_time{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
}rtc_time;

#define RTC_RD_TIME	_IOR('p', 0x09, struct rtc_time)
#define RTC_SET_TIME	_IOW('p', 0x0a, struct rtc_time) /* Set RTC time    */
#define RTC_ALM_SET	_IOW('p', 0x07, struct rtc_time) /* Set alarm time  */
#define RTC_ALM_READ	_IOR('p', 0x08, struct rtc_time) /* Read alarm time */

int gl11_getrtc(struct tm *curt)
{
	static int TimeErr=0;
	struct tm tc, td, *tt;
	static int cnt=1;
	struct timeval tv;

	tt=&td;

	/*tt = (struct tm *)malloc(1*sizeof(struct tm));*/
	memset(&tc, 0, sizeof(struct tm));

	if(gettimeofday(&tv, NULL) ==-1)
	{
		fprintf(stdout,"LIB#gettimeofday Error1\n");
		return -1;
	}

	tt = gmtime(&tv.tv_sec);

	if(cnt++ ==1 || TimeErr)
	{
		if(getrtc_old(&tc) <0)
		{
			fprintf(stderr,"LIB#Error2\n");
			goto ERROR_OUT;
		}
		if((tc.tm_sec >=0 && tc.tm_sec <=59) && (tc.tm_min >=0 && tc.tm_min <=59) && (tc.tm_hour >=0 && tc.tm_hour <=23))
		{
			if((tc.tm_mday >=1 && tc.tm_mday <=31) && (tc.tm_mon >=0 && tc.tm_mon <=11) && (tc.tm_year >=100 && tc.tm_year <=137))
			{

			} else {
				fprintf(stderr,"LIB#Error3\n");
				goto ERROR_OUT;
			}
		} else {
			fprintf(stderr,"LIB#Error4\n");
			goto ERROR_OUT;
		}
		if((tt->tm_sec >=0 && tt->tm_sec <=59) && (tt->tm_min >=0 && tt->tm_min <=59) && (tt->tm_hour >=0 && tt->tm_hour <=23))
		{
			if((tt->tm_mday >=1 && tt->tm_mday <=31) && (tt->tm_mon >=0 && tt->tm_mon <=11) && (tt->tm_year >=100 && tt->tm_year <=137))
			{

			} else {
				fprintf(stderr,"LIB#Error5\n");
				goto ERROR_OUT;
			}
		} else {
			fprintf(stderr,"LIB#Error6\n");
			goto ERROR_OUT;
		}
	}

	curt->tm_hour = tt->tm_hour;
	curt->tm_min  = tt->tm_min;
	curt->tm_sec  = tt->tm_sec;
	curt->tm_year = tt->tm_year;
	curt->tm_mon  = tt->tm_mon;
	curt->tm_mday = tt->tm_mday;
	curt->tm_wday = tt->tm_wday;
	curt->tm_yday = tt->tm_yday;
	curt->tm_isdst = tt->tm_isdst;
	return 0;

ERROR_OUT:
	TimeErr = 1;
	return -1;
}

int gl11_setrtc(struct tm *rtc_tm)
{
	int fd=0;
	int ret=0;
	struct timeval tv;
	unsigned long t=0;

	fd = open("/dev/rtc", O_RDONLY, 0);
	if(fd <0)
	{
		fprintf(stderr,"LIB#RTC_Open Error\n");
		return -1;
	}

	t = mktime(rtc_tm);
	tv.tv_sec = t;
	tv.tv_usec = 0;
	settimeofday(&tv, NULL);

	gettimeofday (&tv, NULL);
	rtc_tm = gmtime(&tv.tv_sec);

	ret = ioctl(fd, RTC_SET_TIME,rtc_tm);
	close(fd);
	if(ret <0)
	{
		fprintf(stderr,"LIB#RTC Setting Error\n");
		return -1;
	}
	return 0;
}

int getrtc_old(struct tm *tt)
{
	int rtc_fd=0;
	int ret=0;

	rtc_fd = open("/dev/rtc", O_RDONLY, 0);

	if(rtc_fd <0){
		fprintf(stderr,"LIB#Unable to Open RTC Device\n");
		return -1;
	}

	ret = ioctl(rtc_fd, RTC_RD_TIME, tt);

	close(rtc_fd);
	if(ret <0){
		fprintf(stderr,"LIB#RTC ioctl Error\n");
		return -1;
	}
	return 0;
}

int lib_checkdriver(char *drv)//Check Driver Insert or Not
{
        FILE *fp=NULL;
        char str[1024]="";

        if((fp =fopen("/proc/modules", "r")) ==NULL){
                fprintf(stderr,"LIB#Unable to Open(/proc/modules)File\n");
                return -1;
        }
        while(fscanf(fp, " %s", str) !=EOF){
                if(strstr(str, drv)){
                        return 0;//Found
                }
        }
        return -2;
}


