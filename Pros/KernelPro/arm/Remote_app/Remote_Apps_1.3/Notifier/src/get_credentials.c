#include<header.h>
/*int get_credentials(void);
  int main()
  {
  get_credentials();
  return 0;
  }
  */
int get_credentials(void)
{

	memset(&Notifier,0x00,sizeof(Notifier));

	int port=0;
	char topic[128]="";
	char ip_addr[128]="";

	FILE *fp=NULL;

	size_t n=0;

	char *line=NULL;

	fp = fopen("/etc/mosq_project.conf","r");
	if( fp == NULL )
	{
		fprintf(stderr,"/etc/mosq_project.conf not found\n");
		return -1;
	}

	while(  getline(&line, &n, fp) != -1 )
	{


		if( strstr(line,"IPADDR:") != NULL)
			strcpy(ip_addr,line+7);

		else if( strstr(line,"PROJECT:") != NULL)
			strcpy(topic,line+8);

		else if (strstr(line,"PORT:") != NULL)
			sscanf(line+5,"%d",&port);

		else if(strstr(line,"H_MODE:") != NULL)
			sscanf(line+7,"%d",&Notifier.H_Time);

		else if(strstr(line,"M_MODE:") != NULL)
			sscanf(line+7,"%d",&Notifier.M_Time);
		
		else if(strstr(line,"L_MODE:") != NULL)
			sscanf(line+7,"%d",&Notifier.L_Time);

	}

	free(line);
	fclose(fp);
	line = NULL;
	printf("%d\n",strlen(topic));
	if( (strlen(ip_addr)<= 1) || (strlen(topic) <= 1) || ( port == 0 ) )
	{
		fprintf(stderr," PROJECT, PORT, IPADDR incorrect or may not found\n");
		return -1;
	}
	
	if(topic[strlen(topic)-1] == '\n')
		topic[strlen(topic)-1] = '\0';
	if(ip_addr[strlen(ip_addr)-1] == '\n')
		ip_addr[strlen(ip_addr)-1] = '\0';

	strcpy( Notifier.topic, topic);
	strcpy( Notifier.ip_addr, ip_addr);
	Notifier.port_no = port;

//fprintf(stdout,"Notifier.ip_addr = %s Notifer.topic = %s Notifier.port_no = %d Notifier.H_Time = %d,Notifier.M_Time=%d,Notifier.L_Time = %d\n",Notifier.ip_addr,Notifier.topic,Notifier.port_no,Notifier.H_Time,Notifier.M_Time,Notifier.L_Time);
	return 0;
}

/*	else if( mode == 'M')
	{
	memset(hexa,0x00,sizeof(hexa));

	sprintf(hexa,"%c",macid[15]);

	sscanf(hexa,"%X",&value);

	sprintf(topic,"%s_M_%d",topic,value);

 *port = atoi(port) + value ;

 return 0;
 }
 else if( mode == 'L')
 {

 sscanf(macid+15,"%X",&value);
 sprintf(topic,"%s_L_%d",topic,value);

 *port = atoi(port) + value + 16;

 return 0;
 }

 else 
 {
 fprintf(stderr," Mode incorrect\n");	
 return -1;

 }*/


