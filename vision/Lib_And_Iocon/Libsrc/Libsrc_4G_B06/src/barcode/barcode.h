#define _GNU_SOURCE
#ifndef LIBGL11EPOS_H
#define LIBGL11EPOS_H
/* Standard Headers */
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

#define NFOUND  -2   //Not Found Return Value
#define AERROR  -2   //Argument Error Return Value
#define ERROR   -1   //Failure Return Value
#define SUCCESS  0   //Success Return Value
#define ADDED    1   //Already Assigned Value
#define WORNG    1   //Enter Worng Value
#define MME      999 //Maximum Menu Entries
#define MEL      256 //Maximum Entries Length
#define DBLE     0   //Set To Flag Disable
#define EBLE     1   //Set To Flag Enable

/* Device Keys */

#define STAR     10  //Star(*) Key Number
#define YASH     11  //#/00 Key Number
#define CANCEL   12  //Cancel Key Number
#define ENTER    15  //Enter Key Number
#define F1       17  //F1 Key Number
#define F2       18  //F2 Key Number
#define F3       19  //F3 Key Number
#define F4       20  //F4 Key Number
#define F5       21  //F5 Key Number
#define F6       22  //F6 Key Number



#endif

