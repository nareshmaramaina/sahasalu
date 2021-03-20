#include<header.h>
static void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
static void my_connect_callback(struct mosquitto *mosq, void *userdata, int result);
static void on_disconnect(struct mosquitto *mosq,void*,int);
//static int Disconnect;
static char topic[128];

void *Run_Medium_clients_thread(void *arg)
{


	int port =0,value=0;


	//char hexa[3]="";

	int keepalive = 60;


	bool clean_session = false;
	struct mosquitto *mosq = NULL;


	/*	sprintf(hexa,"%c",macid[15]);

		sscanf(hexa,"%X",&value);*/


	sprintf(topic,"%s_M_%d",Notifier.topic,value);

	port = Notifier.port_no + value + 1 ;

	int sleep_time = Notifier.M_Time * 60 ;	

	//	keepalive = sleep_time;

	mosquitto_threaded_set(mosq, true);

	while(1)
	{

		fprintf(stdout,"Medium mode Connecting ... \n");

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
			fprintf(stdout,"*** Medium Connection MQTT Success on  host = %s port %d topic = %s retry_time %d secs ***\n",Notifier.ip_addr,port,topic,sleep_time);	


		mosquitto_loop_forever(mosq,-1,1);
	
		mosquitto_destroy(mosq);

		sleep(sleep_time);

	}

}
static void on_disconnect(struct mosquitto *mosq,void *k,int result)
{		
	fprintf(stdout,"Disconnection from/to ( Medium Mode ) \t %d sleeping ...\n",Notifier.M_Time * 60);
	
	/*bool clean_session = false;
	mosquitto_destroy(mosq);	
	while(1)
	{

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
			printf("Medium Mode, Reconnect failed retrying ...\n");
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
	int ret=1;

	if(message->payloadlen)
	{

		printf("Processing Command %s\n",(char *)message->payload);

		if( ( strstr(message->payload,"#EXIT#IF#NOT#") != NULL) )
		{
			if( ( strstr(message->payload,macid) == NULL) )
			{
				mosquitto_disconnect(mosq);
				mosquitto_destroy(mosq);
				mosquitto_report("Medium",message->payload,"Success");
				fprintf(stdout,"ALL OUT ( IT'S MOSQUITTO KILLER )\n");
				exit(0);

			}
			return;
		}

		ret = system(message->payload);

	}
	if ( ret == 0 )
		mosquitto_report("Medium",message->payload,"Success");
	else 	
		mosquitto_report("Medium",message->payload,"Fail");

	fflush(stdout);
}
