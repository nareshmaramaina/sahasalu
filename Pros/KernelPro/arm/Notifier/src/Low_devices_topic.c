#include<header.h>
static void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
static void my_connect_callback(struct mosquitto *mosq, void *userdata, int result);
static void on_disconnect(struct mosquitto *mosq,void*,int);
static int Disconnect;
static char topic[128]="";
void *Run_Low_clients_thread(void *arg)
{

	int port =0,value=0;


	int keepalive = 60;

	bool clean_session = false;

	struct mosquitto *mosq = NULL;

	//	sscanf(macid+15,"%X",&value);

	sprintf(topic,"%s_L_%d",Notifier.topic,value);

	port = Notifier.port_no + value + 16 + 1;

	int sleep_time = Notifier.L_Time * 60 ;	

	mosquitto_threaded_set(mosq, true);

	while(1)
	{
		fprintf(stdout,"Low mode Connecting ... \n");


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


		if(mosquitto_connect(mosq, Notifier.ip_addr, port, keepalive))
		{
			fprintf(stdout,"Unable to Connect the host = %s, port_no = %d, topic = %s retry_time = %d secs ... \n",Notifier.ip_addr,port,topic,sleep_time);	

			mosquitto_destroy(mosq);
			sleep(sleep_time);
			continue;
		}

		else
			fprintf(stdout,"*** Low Connection MQTT Success on  host = %s port %d topic = %s retry_time %d secs ***\n",Notifier.ip_addr,port,topic,sleep_time);	


		mosquitto_loop_forever(mosq,-1,1);

		mosquitto_destroy(mosq);
		
		sleep(sleep_time);
	

	}

}
static void on_disconnect(struct mosquitto *mosq,void *k,int result)
{
		fprintf(stdout,"Disconnection from/to ( Low Mode ) \t %d sleeping ...\n",Notifier.L_Time * 60);
/*
	bool clean_session = false;
	while(1)
	{
		mosquitto_destroy(mosq);
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
		sleep(Notifier.L_Time * 60);



		if ( mosquitto_reconnect(mosq) == MOSQ_ERR_SUCCESS )
		{
			printf("Connected to server\n");
			return;
		}

		else
		{	
			printf("Low Mode, Reconnect failed retrying ...\n");
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
		mosquitto_subscribe(mosq,NULL,topic,2);
		fprintf(stdout,"subscribing to %s topic\n",topic);
	}
	else
		fprintf(stderr, "Connection failed\n");
}

static void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
	int ret = 1;
	char cmd[256];
	char *ptr=NULL;
	char IP[64];
	char port[24];
	int i;
	bzero(cmd,sizeof(cmd));
	memset(IP,0,sizeof(IP));
	memset(port,0,sizeof(port));

	if(message->payloadlen)
	{

		printf("%s\n",(char *)message->payload);

		if( ( strstr(message->payload,"#EXIT#IF#NOT#") != NULL) )
		{
			if( ( strstr(message->payload,macid) == NULL) )
			{
				Disconnect=1;
				mosquitto_disconnect(mosq);
				//		pthread_exit(NULL);

			}
		}

		else if(strstr(message->payload,"#GET#REMOTE#") != NULL)
		{

			if( ( strstr(message->payload,macid) != NULL) )
			{
				if( (ptr = strstr(message->payload,"IP#")) != NULL)
				{

					for(ptr=ptr+3, i=0;ptr[i] != '#' && ptr[i] != '\0' ;i++)
						IP[i]=ptr[i];
					IP[i]='\0';	

				}
				if( (ptr = strstr(message->payload,"PORT#")) != NULL)
				{

					for(ptr=ptr+5, i=0;ptr[i] != '#' && ptr[i] != '\0' ;i++)
						port[i]=ptr[i];	
					port[i]='\0';
				}

				sprintf(cmd,"sh /vision/PosDesk.sh %s %s &",IP,port);
				//mosquitto_report("Low",message->payload,"Processing");
				fprintf(stdout," ********** POS REMOTE CONNECTING %s %s **********\n",IP,port);
				ret = system(cmd);
			}
		}
	}
	if ( ret == 0 )
		mosquitto_report("Low",message->payload,"Success");
	else 	
		mosquitto_report("Low",message->payload,"Fail");

	fflush(stdout);
}
