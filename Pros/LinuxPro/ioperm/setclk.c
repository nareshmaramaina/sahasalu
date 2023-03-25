# include <unistd.h>
# include <sys/io.h>

void setval(int what,unsigned val){
	outb(what,0x70);
	outb(val,0x71);
}
int main(){
	/* get the permission to access rtc ports */
	int res,a,b;
	res=ioperm(0x70,0x04,1);/* we can access ports 70,71,72,73*/
	printf("res =%d \n",res);
	setval(4,0x07);
	setval(2,0x27);
	setval(0,0x00);
	return 0;
}
