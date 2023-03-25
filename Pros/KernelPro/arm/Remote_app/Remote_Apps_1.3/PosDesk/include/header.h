#include <fcntl.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <signal.h>
#include <ctype.h>          
#include <arpa/inet.h>
#include <netdb.h>
#include<signal.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <termios.h>
#include <arpa/inet.h>
#include <resolv.h>
#include <netdb.h>

#define BACKLOG 5
#define LENGTH 512 



int Foreground_process;
int sockfd; 
char Check_CmD[128];




int get_app_details();
int get_macid(char*);
void get_time(char *,char *time); 
int get_Machineid(char *);
int size_of_file(const char *file);
void file_send_func(int sockfd,char* );
int wait_for_data(int sockid,int); 
void alarmHandler(int signo);
int check_cmd(char *cmd_buff);
int Upload_file(char *filename);
int Upload(char *filename);
int DevInfo();
void Wait_for_internet(void);
int hostname_to_ip(char *host);
