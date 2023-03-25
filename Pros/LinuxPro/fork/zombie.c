#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
    // Fork returns process id 
    // in parent process 
    pid_t child_pid = fork(); 
  
    // Parent process  
    if (child_pid > 0)
    {
	printf(" Waiting For Child %d\n",child_pid); 
	  printf("Getpid of Parent = %d\n",getpid()); 
        sleep(1); 

    }
  
    // Child process 
    else       
    {
	  printf("Getpid of Child = %d\n",getpid()); 
        exit(0); 
    }
  
    return 0; 
} 
