#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    int status;
    int pid = fork();

    if(pid ==0){
	 printf("HELLO IM THE CHILD PROCESS"); 


    }    
	printf("I THINK IM THE PARENT)");
		    
    return 0;
}
