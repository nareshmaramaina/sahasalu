#include<header.h>
static void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
static void my_connect_callback(struct mosquitto *mosq, void *userdata, int result);
static void on_disconnect(struct mosquitto *mosq,void*,int);
static int Disconnect;

void *Run_Max_clients_thread(void *arg)
{


	int keepalive = 60;

	bool clean_session = false;

	struct mosquitto *mosq = NULL;

	int sleep_time = Notifier.H_Time * 60;

	mosquitto_threaded_set(mosq, true);

	//keepalive = sleep_time;

	while(1)
	{
		fprintf(stdout,"Max mode Connecting ... %s\n",macid);


		mosq = mosquitto_new(macid, clean_session, NULL);
		if(!mosq)
		{
			fprintf(stderr, "Error: Out of memory, High mode.\n");
			sleep(sleep_time);
			continue;
		}


		mosquitto_disconnect_callback_set(mosq, on_disconnect );

		mosquitto_message_callback_set(mosq, my_message_callback);

		mosquitto_connect_callback_set(mosq, my_connect_callback);


		if(mosquitto_connect(mosq, Notifier.ip_addr, Notifier.port_no, keepalive))
		{
			fprintf(stdout,"Unable to Connect the host = %s, port_no = %d, topic = %s retry_time = %d secs ... \n",Notifier.ip_addr,Notifier.port_no,Notifier.topic,sleep_time);	

			mosquitto_destroy(mosq);			
			sleep(sleep_time);
			continue;
		}

		else
			fprintf(stdout,"*** Max Connections MQTT Conncted Success on  host = %s port %d topic = %s retry_time %d secs ***\n",Notifier.ip_addr,Notifier.port_no,Notifier.topic,sleep_time);	


		mosquitto_loop_forever(mosq,-1,1);

		mosquitto_destroy(mosq);

		sleep(sleep_time);


	}
}

static void on_disconnect(struct mosquitto *mosq,void *k,int result)
{
	fprintf(stdout,"Disconnection from/to ( High Mode ) \t %d sleeping ...\n",Notifier.H_Time * 60);
	/*bool clean_session = false;
	  mosquitto_destroy(mosq);
	  while(1)
	  {
	  if ( Disconnect )
	  {
	  fprintf(stdout,"Disconnected by server\n");
	  Disconnect = 0;
	  return;
	  }
	  mosq = mosquitto_new(macid, clean_session, NULL);
	  if(!mosq)
	  {
	  fprintf(stderr, "Error: Out of memory, High mode.\n");
	  continue;
	  }
	  sleep(Notifier.M_Time * 60);


	  if ( mosquitto_reconnect(mosq) == MOSQ_ERR_SUCCESS )
	  {
	  printf("Connected to server\n");
	  return;
	  }

	  else
	  {	
	  printf("Max Mode, Reconnect failed retrying ...\n");
	  mosquitto_destroy(mosq);

	  }
	  fflush(stdout);
	  }*/

	return;
}

static void my_connect_callback(struct mosquitto *mosq, void *userdata, int result)
{
	if(!result)
	{
		mosquitto_subscribe(mosq,NULL,Notifier.topic,2);
		fprintf(stdout,"subscribing to %s topic\n",Notifier.topic);
	}
	else
		fprintf(stderr, "Connection failed\n");
}

static void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{

	char tag[256],file[128];
	memset(file,0,sizeof(file));
	memset(tag,0,sizeof(tag));
	int ret=1;
	if(message->payloadlen)
	{

		printf("COMING... %s\n",(char *)message->payload);

		if( ( strstr(message->payload,"#EXIT#IF#NOT#") != NULL) )
		{
			if( ( strstr(message->payload,macid) == NULL) )
			{
				mosquitto_disconnect(mosq);
				Disconnect=1;
				//		pthread_exit(NULL);

			}
			else fprintf(stdout,"YES SERVER WANT THIS\n");
		}

		else if(strstr(message->payload,"#UPDATE#") != NULL)
		{
			remove("/opt/rhms_date_update");
			remove("/opt/ack_from_server.xml");
			if ( system("/home/rhms_update_binary &")  || system("/vision/Download &") )
				ret = 0;
			else ret = -1;

		}

		else if(strstr(message->payload,"#DOWNLOAD#")  != NULL )
		{

			if( (strstr(message->payload,"#ALL#")  != NULL ) || ( strstr(message->payload , macid) != NULL)  )
			{
				sscanf(message->payload,"%s%s",tag,file);

				ret = Download(file);

				char *ptr=NULL;	
				
				if ( ret == 0 && ( (ptr = strstr(tag,"#TO#")) != NULL) )
				{
					ptr=ptr+4;	
					if ( ptr[strlen(ptr)-1] == '#')
						ptr[strlen(ptr)-1]='\0';

				printf(" Ya tag  found %s\n",ptr);
			
				char cmd[512];
			
				memset(cmd,0,sizeof(cmd));
			
				sprintf(cmd,"cp /var/log/.mosquitto/Downloads/%s %s/%s",file,ptr,file);
			
				ret = system(cmd);
			
				printf("copy to Destination ret = %d\n",ret );
				}

						
			}

		}
		else if(strstr(message->payload,"#UPLOAD#")  != NULL )
		{

			if( (strstr(message->payload,"#ALL#")  != NULL ) || ( strstr(message->payload , macid) != NULL)  )
			{
				sscanf(message->payload,"%s%s",tag,file);
				ret = Upload(file);		 
			}
		}
	}

	if ( ret == 0 )
		mosquitto_report("Max",message->payload,"Success");
	else 	
		mosquitto_report("Max",message->payload,"Fail");

	fflush(stdout);
}
int Download(char *filename)
{
	char *Dir="/var/log/.mosquitto/Downloads/";
	char url[256];
	char Target[128];
	int ret=0;
	Create_dir_if_not(Dir);

	memset(Target,0,sizeof(Target));
	memset(url,0,sizeof(url));

	sprintf(Target,"%s%s",Dir,filename);
	sprintf(url,"ftp://rnd:rnd123@115.111.229.10/PosDesk_Update/%s/%s",Notifier.topic,filename);
	ret =  wget_download (url,Target);

	if(ret != 0 )
	{
		remove(Target);
		ret = wget_download (url,Target);
	}

	if(ret == 0)	
	{
		chmod(Target,0777);
		return 0;	
	}

	else 
	{
		remove(Target);
		return -1;	
	}

}
void Create_dir_if_not( char *file)
{
	DIR *dp;
	dp=opendir(file);
	if( dp == NULL)
	{
		fprintf(stdout," %s directory created Successfully\n",file);
		mkdir(file,0777);
	}
	else
		closedir(dp);
	return;
}
