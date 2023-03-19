#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
sem_t mutex;
int cnt = 0;
#define MAX_NO_OF_THREADS 4
#define MAX_TIMES_TO_INCREMENT 5
typedef struct arg_data {
int thread_number;
} arg_data;
void* thread(void* arg)
{
arg_data* current_thread_data = (arg_data*)arg;
//start of critical section
//before starting to enter critical section, check to see if semaphore is locked. if its not, decrease value to 0 to lock semaphore

sem_wait(&mutex);
printf("\nThread %d entering critical section...\n", current_thread_data->thread_number);
int local_cnt = cnt;
for (int i=0; i<MAX_TIMES_TO_INCREMENT; i++) {
local_cnt++;
printf("\nThread %d Value: %d\n", current_thread_data->thread_number, local_cnt);
}
cnt = local_cnt;
printf("\nThread %d exiting critical section...\n", current_thread_data->thread_number);
//decrease semaphore/unlock iti
//
//from my understanding, if sem_wait sees the semephore is locked, it will sleep the thread, once sem_post is called, does it wake up
//every thread? is it a race for which thread then executes or are they in a queue 
sem_post(&mutex);
//end of critical section
return NULL;
}

int main()
{
//I will initiate a semephore with the mutex object created above, 2nd arg 0 b/c not shared between processes and 3rd arg 1 b/c semephoe will first be unlocked
//pthread objects
pthread_t id[MAX_NO_OF_THREADS];
//argument data to send in worker functions
arg_data arg_arr[MAX_NO_OF_THREADS];
//total number of threads we will create
int no_of_threads = MAX_NO_OF_THREADS;
printf("Creating %d threads...\n", no_of_threads);
int thread_no = 1;
//creating the child threads
sem_init(&mutex,0,1);
for (thread_no = 1; thread_no <= MAX_NO_OF_THREADS; thread_no++) {
arg_arr[thread_no - 1].thread_number = thread_no;
pthread_create(&id[thread_no - 1], NULL, thread, &arg_arr[thread_no - 1]);
}
//joining the threads one by one
for (int i = 1; i <= MAX_NO_OF_THREADS; i++)
pthread_join(id[i - 1], NULL);
//check
if (cnt != (int) MAX_TIMES_TO_INCREMENT * MAX_NO_OF_THREADS)
printf("Value Incorrect! cnt=%d\n", cnt);
else
printf("Value Correct! cnt=%d\n", cnt);
return 0;
}
