#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    int status;
     pid_t pid = fork();
    if(pid ==0) {
	pid_t pid_grand = fork();
	if(pid_grand==0){
	
	printf("I am the grandchild %d\n",getpid());
	}else{	
        wait(NULL);	
	printf("I am the child %d\n",getpid());
    	}
    }
	
     else{
	    wait(NULL);
	    int pid_parent = getpid();
	    printf("I am the parent %d\n",pid_parent);

     	 }
    
     return 0;
}


