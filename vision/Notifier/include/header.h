 #include <sys/stat.h>
#include <sys/time.h>
#include <pthread.h>
#include <errno.h>
#include<unistd.h>
#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <dirent.h>

extern char macid[24];
struct mosq_config
{
	char ip_addr[32];
	char topic[128];
	int  port_no;
	int H_Time;
	int M_Time;
	int L_Time;

}Notifier;
int get_credentials(void);
int get_macid(char *);
int get_port_and_topic(char,char *,int *);
void *Run_Medium_clients_thread(void *);
void *Run_Max_clients_thread(void *);
void *Run_Low_clients_thread(void *);
void get_date(int *day,int *month,int *year,int*,int*,int*);
int  Check_Expire_Date(void);
int wget_download (char *url,char *Taget_filename);
void Wait_for_internet(void);
int Download(char*);
void Create_dir_if_not(char *file);
int Upload_file(char *filename);
int Upload(char *filename);
void mosquitto_report(char *mode,char *msg,char *cmd_status);
