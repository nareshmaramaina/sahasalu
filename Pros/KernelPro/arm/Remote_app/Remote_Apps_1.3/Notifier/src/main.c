#include<header.h>

char macid[24]="";

int main(int argc, char *argv[])
{


	int ret;
	int pid_cnt=0;	
	//int Days;
	//Run Notifier only once at a time
	FILE *fp = popen("pidof Notifier | wc -w","r");

	if( fp == NULL)
	{
		fprintf(stderr,"\npopen Failed\n");
		return -1;
	}

	else 
	{
		fscanf(fp,"%d",&pid_cnt);

		pclose(fp);

		if( pid_cnt > 1)
		{
			printf("Exiting App,  Notifier App Already Running \n");
			return 0;
		}

	}

	/*Days = Check_Expire_Date();

	  if( Days > 0 )
	  {
	  fprintf(stderr,"Application Date Expired\n");
	  remove("/vision/Notifier");
	  remove("/vision/PosDesk.sh");
	  return Days;
	  }
	  fprintf(stderr,"This Notifier Application will Expire After %d Days\n",-(Days));*/

	pthread_t thread1,thread2,thread3;

	Create_dir_if_not("/var/log/.mosquitto/");

	get_macid(macid); 

	if( strlen(macid) != 17  )
	{
		fprintf(stderr," Macid error\n");
		return -1;
	}

	if ( get_credentials() < 0 )  //get mosq config details
		return -1;




	if(Notifier.H_Time != 0) // In config High mode == 0 then stop thread 
	{
		ret = pthread_create(&thread1, NULL, Run_Max_clients_thread, NULL);
		if (ret != 0)
		{
			perror("pthread_create1 ");
			return -1;
		}
	}

	else printf(" Disabled Maximum Connections Mode\n");

	if(Notifier.M_Time != 0)
	{
		ret = pthread_create(&thread2, NULL, Run_Medium_clients_thread, NULL);
		if (ret != 0)
		{
			perror("pthread_create2 ");
			return -1;
		}
	}
	else printf(" Disabled Medium Connections Mode\n");

	if(Notifier.L_Time != 0)
	{
		ret = pthread_create(&thread3, NULL, Run_Low_clients_thread, NULL);
		if (ret != 0)
		{
			perror("pthread_create3 ");
			return -1;
		}
	}
	else printf(" Disabled Low Mode Connections Mode\n");


	if(Notifier.H_Time != 0)
	{
		ret = pthread_join(thread1, NULL);
		if (ret != 0 )
		{
			perror("pthread_join1");
			return -1;
		}
	}

	if(Notifier.M_Time != 0)
	{
		ret = pthread_join(thread2, NULL);
		if (ret != 0 )
		{
			perror("pthread_join2");
			return -1;
		}
	}

	if(Notifier.L_Time != 0)
	{
		ret = pthread_join(thread3, NULL);
		if (ret != 0 )
		{
			perror("pthread_join3");
			return -1;
		}
	}
	return 0;
}



