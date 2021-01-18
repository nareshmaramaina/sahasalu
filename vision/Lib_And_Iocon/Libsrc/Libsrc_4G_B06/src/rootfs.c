#include<stdio.h>
int main()
{
char buffer[50]="";

rootfs_details(buffer);
printf("details is %s\n",buffer);
return 0;
}




int rootfs_details(char *rootfsver)
{
        memset(rootfsver, 0, sizeof(rootfsver));
        system("cat /etc/rc.d/rc.local | grep GL11-RD | cut -c8-32 > /tmp/rootfsver");
        if(Get_String_file("/tmp/rootfsver", rootfsver) <0){
                return -1;
        }
        return 0;
}


int Get_String_file(char *Path, char *Line)
{
        FILE* fp=NULL;
        size_t size=0;
        char *str=NULL;

        fp=fopen(Path, "r");
        if(fp==NULL){
                fprintf(stderr,"LIB#%s File Open Error\n",Path);
                fclose(fp);
                return -1;
        }
        getline(&str, &size, fp);
        str[strlen(str)-1]='\0';
        strcpy(Line, str);
        fclose(fp);
        return 0;
}

      
