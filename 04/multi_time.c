#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#define MAX_NO_OF_THREADS 2
#define MAX_NO_OF_ELEMENTS 100000000
typedef struct arg_data {
    int thread_number;
} arg_data;
//shared data on which threads will work concurrently
//array which will be summed
static int arr[MAX_NO_OF_ELEMENTS];
//sum variable that will store the total sum
static long long int sum;
void* worker_sum(void* arg)
{
    arg_data* current_thread_data = (arg_data*)arg;
 
    printf("Current thread no is : %d\n", current_thread_data->thread_number);
//determine the bounds

    
    printf("Here we will sum %d to %d\n", arr[startpart], arr[endpart - 1]);
//Generate the sum
   
    sum += current_thread_sum;
 
    return NULL;
}
