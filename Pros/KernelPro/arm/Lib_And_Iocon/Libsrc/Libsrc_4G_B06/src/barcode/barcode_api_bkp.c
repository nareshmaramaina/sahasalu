#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>

char *keycode[256] = {
   "", "<esc>", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
  "-", "=", "<backspace>",
  "<tab>", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[",
  "]", "\n", "<control>", "a", "s", "d", "f", "g",
  "h", "j", "k", "l", ";", "'", "", "<shift>",
  "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".",
  "/", "<shift>", "", "<alt>", " ", "<capslock>", "<f1>",
  "<f2>", "<f3>", "<f4>", "<f5>", "<f6>", "<f7>", "<f8>", "<f9>",
  "<f10>", "<numlock>", "<scrolllock>", "", "", "", "", "", "", "",
  "", "", "", "\\", "f11", "f12", "", "", "", "", "", "",
  "", "", "<control>", "", "<sysrq>"
};

int event_fd ;
//FILE *event_fd;
char eventid[2]="";
int brcodedev_test (void);

int size;
struct input_event ev[64];
int rd,value,code;




int bar_code_open()
{
	int opt=0,usbaret=0;
	char name[256] = "Unknown";char filename[256]="/dev/input/event";
        int i = 25;

	rd=0;


       size = sizeof (struct input_event);



	usbaret=brcodedev_test();


        if(usbaret == -1)
   	{
			
		fprintf(stderr,"Unabel to detect the device\n");
     		return -1;
	}
        if ((getuid ()) != 0)
                printf ("You are not root! This may not work...\n");
		event_fd =0; 		 
		strncat(filename,eventid,2);
		if ((event_fd = open (filename, O_RDONLY | O_NONBLOCK  )) == -1) 
		{
                fprintf (stderr,"%s is not a vaild device. try using the argument 'scan'\n",filename);
                return -1;
		}

        ioctl (event_fd, EVIOCGNAME (sizeof (name)), name);
        //printf ("Reading From : /dev/input/event%s\n", eventid);
        //printf ("*** %s ***\n",name) ;

	//fprintf(stderr,"Barcode device is ready to use\n");
	//
	return event_fd;	

}

int bar_code_read (unsigned char *rxbuf,int len)

{
	int count=0;

        while (1) 
	{
                rd = read (event_fd, ev, size * 1) ;

                if(rd > 0)
		{
			count =1;
                        value = ev[0].value ;
                        code = ev[0].code ;
                        if (value != ' ' && ev[0].value == 1 && ev[0].type == 1) 
			{
                                if(keycode[code] == "\n")
				{
                                        break ;
                                }
                               // fprintf (stdout, "%s----",keycode[code]);
				sprintf(rxbuf,"%s%s",rxbuf,keycode[code]);
					
                        }
                }
	
	 	else  if(!count) return -1;		

        }

	return strlen(rxbuf);	

        //printf ("\n");
	//puts(rxbuf);

}

int bar_code_close()
{
        close(event_fd) ; 

		return 0;
}
int brcodedev_test ()
{
	char ven[20]="",chr[50]="",flag=0,i,j;
	int value;int tru=0;
	int event=0;
      	FILE *fp; static int off=0;
	fp=fopen("/proc/bus/usb/devices","r");
	if(fp==NULL)
		return -1;
    	//printf("in bardevtest\n");  
	while( fscanf( fp," %s",chr)!=EOF)
	{ 
		if(strstr(chr,"Vendor"))
		{
			if((strcmp(chr,"Vendor=0000")))
      			{  
			j=7;//consider after =
			for(i=0;j<20;i++)
			{ ven[i]=chr[j]; 
			j++;	
			} //ven[20]='\n';
				//strcpy(ven,chr);
				//ven[11]='\n';
				ven[4]=0x20;				      //to verify the vendor id 0c2e
               		if(ven[0]=='0'&&ven[1]=='c'&&ven[2]=='2'&&ven[3]=='e')//followed this method because strcmp didnt work
			 {flag++;break;}
			else { lseek((int)fp,off,SEEK_CUR);
				continue;}
             		} 
			else continue;
          	} 
		else continue;
	 } 
   	fclose(fp);

		if(flag==0)
            	{
			return -1;
		}   
 
          
            	else if( flag ==1 )
             	{
		event=find_eventid();
		return 0;	
            	}  
     	
return 0;
}
int find_eventid()
{
	FILE *fp;char ven[20]="",chr[50]="";
	fp=fopen("/proc/bus/input/devices","r");
	int ret=0;int off=0;int i,j;
	if(fp==NULL)
		return -1;
	while( fscanf( fp," %s",chr)!=EOF)
	{ 
		if(strstr(chr,"Vendor"))
		{
			if((strcmp(chr,"Vendor=0000")))
      			{ 
			j=7;//consider after =
			for(i=0;j<20;i++)
			{ ven[i]=chr[j]; 
			j++;	
			} //ven[20]='\n';
				//strcpy(ven,chr);
				//ven[11]='\n';
				ven[4]=0x20;					//verifying fo device id
               		if(ven[0]=='0'&&ven[1]=='c'&&ven[2]=='2'&&ven[3]=='e')//followed this method because strcmp didnt work
			 {
				ret=return_event(fp);
				return ret;
			 }			
			else { lseek((int)fp,off,SEEK_CUR);
				continue;
			      }
             		} 
			else continue;
          	} 
	else continue;
	 } 

}
int return_event(FILE*fp)
{
	char chr[50]="";
	while( fscanf( fp," %s",chr)!=EOF)
	{ 
		if(strstr(chr,"event"))
		{ 
			eventid[0]=chr[5];//because upto chr[4] "event" is occupying
			eventid[2]='\0';
			//printf("eventid*****=%s",eventid);
			return 0;	
		}
	}
}
