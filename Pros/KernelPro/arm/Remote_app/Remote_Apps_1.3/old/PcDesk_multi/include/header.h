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

//#define BACKLOG 5
#define LENGTH 512 






int  Check_Remote_Id(char *clientid);

int get_app_details();
int get_macid(char*);
void file_recv_func(int sockfd,int size,FILE *fp);
void get_time(char *,char *time); 
int get_Machineid(char *);
int size_of_file(const char *file);
void file_send_func(int sockfd);
int wait_for_data(int sockid);
