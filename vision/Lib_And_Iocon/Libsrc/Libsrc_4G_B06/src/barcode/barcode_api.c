 
//#include "libgl11pos.h"
#include "barcode.h"

#define SHIFTL	42
#define SHIFTR	54
#define CAPS	58
#define NUM	69

ssize_t getline(char **lineptr, size_t *n, FILE *stream);

static char *Keycode[256] ={"", "<Esc>", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "<Backspace>", "\t", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "\n", "<Ctrl>", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "`", "<Shift>", "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", "<Shift>", "*", "<Alt>", " ", "<CapsLock>", "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>", "<NumLock>", "<ScrollLock>", "<Home>", "<UpArrow>", "<PageUp>", "-", "<LeftArrow>", "<Center>", "<RightArrow>", "+", "<End>", "<DownArrow>", "<PageDown>", "<Insert>", "<Del>", "", "", "<Ctrl+P>", "<F11>", "<F12>", "", "", "", "", "", "", "", "\n", "<Ctrl>", "/", "<PrScr/SysRq>", "<AltGr>", "", "<Home>", "<UpArrow>", "<PageUp>", "<LeftArrow>", "<RightArrow>", "<End>", "<DownArrow>", "<PageDown>", "<Insert>", "<Del>", "", "", "", "", "", "", "", "<Pause/Break>", "", ".", "", "", "", "<WinLeft>", "<WinRight>", "<SelKey>",""};

static char *Shiftcode[256] ={"", "<Esc>", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", "<Backspace>", "\t", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "\n", "<Ctrl>", "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", "\"", "~", "<Shift>", "|", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?", "<Shift>", "*", "<Alt>", " ", "<CapsLock>", "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>", "<NumLock>", "<ScrollLock>", "7", "8", "9", "-", "4", "5", "6", "+", "1", "2", "3", "0", ".", "", "", "<Ctrl+P>", "<F11>", "<F12>", "", "", "", "", "", "", "", "\n", "<Ctrl>", "/", "<PrScr/SysRq>", "<AltGr>", "", "<Home>", "<UpArrow>", "<PageUp>", "<LeftArrow>", "<RightArrow>", "<End>", "<DownArrow>", "<PageDown>", "<Insert>", "<Del>", "", "", "", "", "", "", "", "<Pause/Break>", "", ".", "", "", "", "<WinLeft>", "<WinRight>", "<SelKey>",""};

static int bar_fd=-1;

int bar_code_open(void)
{
	FILE *fp=NULL;
	size_t size=0;
	char flag=0, *str=NULL, *str1=NULL, *token=NULL;
	char *name="Unknown", Bnode_file[25]="/dev/input/";
	int ret=0;

	sleep(1);	
	fp=fopen("/proc/bus/input/devices", "r"); //To Verify Devices Existance
	if(fp==NULL){
		fprintf(stderr,"/proc/bus/input/devices\n");
		return -1;
	}
	while(getline(&str, &size, fp) !=EOF)
	{
	    ret = (strstr(str, "N: Name=") !=NULL) ? ((strcasestr(str, "Key") ==NULL) ? ((strcasestr(str, "Mouse") ==NULL) ? 
			((strcasestr(str, "SMI") ==NULL) ? ((strcasestr(str, "Screen") ==NULL)?1:0):0):0):0):0;
	    if(strcasestr(str, "Scanner") || ret==1)
		flag=1;
	    else if(strstr(str, "H: Handlers=kbd ") && flag==1)
	    {
		for(str1=str; ; str1=NULL){
			token = strtok(str1, " ");
			if(token==NULL)
				break;
			else if(strstr(token, "event") && flag==1){
				flag=2;
				break;
			}
		}
	    }
	    if(flag==2)
		break;
	}
	fclose(fp);
	if(!strcmp(Bnode_file, "/dev/input/")){
		fprintf(stderr,"/dev/input/\n");
		return -1;
	}
	if(getuid() !=0)
		fprintf(stderr,"LIB#You are not root! This may not Work...\n");
	fprintf(stdout,"Barcode_Node is:%s\n",Bnode_file);
	if(bar_fd >0)
		close(bar_fd);
	if((bar_fd = open(Bnode_file, O_RDONLY | O_NOCTTY | O_NONBLOCK)) ==-1){
		fprintf(stderr,"LIB#%s is not a vaild Device.\n",Bnode_file);
		return -1;
	}
	ioctl(bar_fd, EVIOCGNAME(sizeof(name)), name);
	return 0;
}

int bar_code_read(char *Bar, int len)
{
	char shift=0, caps=0, num=0;
	struct input_event ev[64];
	int i=0, type=0, value=0, code=0, size =sizeof(struct input_event);

	memset(Bar, 0, sizeof(Bar));
	while(1)
	{
		if((len=read(bar_fd, ev, size*1)) >0)
		{
			type = ev[0].type;
			value = ev[0].value;
			code = ev[0].code;
			
			//fprintf(stdout,"LIB#Type:%d Value:%d Code:%d Keycode:%s\n",type,value,code,Keycode[code]);
			if(type ==1 && (code ==SHIFTL || code ==SHIFTR))
				shift =! shift;
			else if(type ==1 && code ==CAPS)
				caps =! caps;
			else if(type ==1 && code ==NUM)
				num =! num;
			else if(value !=' ' && value ==1 && type ==1)
			{
				if(strcmp(Keycode[code], "\n") ==0){
					len = len-3;	break;
				}
				else if(shift==1)
					strcat(Bar, Shiftcode[code]);
				else if(caps ==1 && ((code >15 && code <26) || (code >29 && code <39) || (code >43 && code <51)))
					strcat(Bar, Shiftcode[code]);
				else if(num ==1 && (code >70 && code <84))
					strcat(Bar, Shiftcode[code]);
				else
					strcat(Bar, Keycode[code]);
				i=0;
			}
		}
		else if(i++ >70000){
			len = (strlen(Bar) <1?-1:strlen(Bar));
			break;
		}
	}
	//fprintf(stdout,"LIB#Barcode:%s===>Len:%d\n",Bar,strlen(Bar));
	return (strlen(Bar) <1?-1:strlen(Bar));
}

int bar_code_close(void)
{
	close(bar_fd);
	return 0;
}

