#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX_ITEMS_TO_PRODUCE 10
#define MAX_ITEMS_TO_CONSUME 10
#define BUFFER_SIZE 5
#define NumProducer 1
#define NumConsumer 1
sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[BUFFER_SIZE];
pthread_mutex_t mutex;
typedef struct arg_data {
int thread_number;
} arg_data;
void* producer(void* arg)
{
int item;
arg_data* current_thread_data = (arg_data*)arg;
for(int i = 0; i < MAX_ITEMS_TO_PRODUCE; i++) {
//another QUESTION: why is one a counting semaphore and another a binary? i think this Q means i do not understand counting semaphores
//make sure to review them soon. 
sem_wait(&full);
item = rand();
//start of critical section

printf("Producer %d: Inserted item %d into index %d\n", current_thread_data->thread_number, item,
in);
buffer[in]=item;
in = in+1;
in = in %BUFFER_SIZE;
sem_post(&full);
//end of critical section
}
return NULL;
}


void* consumer(void* arg)
{
arg_data* current_thread_data = (arg_data*)arg;
for(int i = 0; i < MAX_ITEMS_TO_CONSUME; i++) {
//start of critical section
//before i start with consumer, the empty semaphore is a counting semaphore of size buffer_size. the main idea is probably to
//grab item from the buffer(we just need item) to confirm we have removed the correct element,if the semaphore is locked(0 elements in buffer)  we wait i suppose(sem_wait(&empty)), then once there is an element in buffer, thread wakes up and removes item 
sem_wait(&empty);
//grab item. this is a circular array so we mod by array size to point back to index 0
int item = buffer[out];
buffer[out] = 0;
//out = out+1;	
//out = out&BUFFER_SIZE;
	printf("Consumer %d: Removed item %d from index %d\n", current_thread_data->thread_number, item, out);
	out = out-1;
	out =out%BUFFER_SIZE;
	//do we need to adjust buffer size seeing as the empty is never increased 
	
sem_post(&empty);
	}
	return NULL;
}



int main()
{
pthread_t producers[NumProducer], consumers[NumConsumer];
arg_data producer_arg_arr[NumProducer];
arg_data consumer_arg_arr[NumConsumer];
//QUESTION: what is the purpose of pthead_mutex? i assume it is to ensure other producers/consumers do not modify the buffer?
pthread_mutex_init(&mutex, NULL);
//maybe since empty is a count, there can be buffer size threads before semaphore locks?
sem_init(&empty, 0, BUFFER_SIZE);
sem_init(&full, 0, 0);
for (int thread_no = 1; thread_no <= NumProducer; thread_no++) {
producer_arg_arr[thread_no - 1].thread_number = thread_no;
pthread_create(&producers[thread_no - 1], NULL, producer, &producer_arg_arr[thread_no - 1]);
}
for (int thread_no = 1; thread_no <= NumConsumer; thread_no++) {
consumer_arg_arr[thread_no - 1].thread_number = thread_no;
pthread_create(&consumers[thread_no - 1], NULL, consumer, &consumer_arg_arr[thread_no - 1]);
}
for(int i = 0; i < NumProducer; i++) {
pthread_join(producers[i], NULL);
}
for(int i = 0; i < NumConsumer; i++) {
pthread_join(consumers[i], NULL);
}
pthread_mutex_destroy(&mutex);
sem_destroy(&empty);
sem_destroy(&full);
return 0;
}
