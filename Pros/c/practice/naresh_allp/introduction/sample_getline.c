#include<stdio.h>
int main()
{
 FILE *config,*release;
        int ret,len=30,i=0,count=0,j=0;
        char *line=NULL;
release=fopen("visiontek_release","r");
        if(release==NULL)
        {
                fprintf(stdout,"Release file not found in device\n");
                system("rm -rf /mnt/sysuser/Firmware-Upgrade/*");

        }
        ret = getline(&line, &len, release);
line[strlen(line)-1]='\0';
printf("%s",line);
        fclose(release);
}

