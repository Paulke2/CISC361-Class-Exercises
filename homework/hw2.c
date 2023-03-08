#include <pthread.h>
#include <stdio.h>
#include <sys/wait.h>
//#include <sys/types.h>
#include <unistd.h>
int value =0;
void *runner(void *param); /*the thread */

int main(int argcm, char *argv[]) {
pid_t pid = fork();
pthread_t tid;
pthread_attr_t attr;


if (pid ==0) {
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr,runner,NULL);
	pthread_join(tid,NULL);
	printf("CHILD : value = %d \n", value); /*line C */

   }else if(pid >0) { //parent
	wait(NULL);
	printf("Parent: value = %d",value); //line P
	}

}


void *runner(void *param) {
	value =5;
	pthread_exit(0);
    }
