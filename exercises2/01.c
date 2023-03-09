#include<stdio.h>
#include <stdbool.h>
 
int main()
{
    // Initialize variables
    int i = 0, num_processes = 0, total_time = 0, x, output_flag = 0,
time_quantum =0;
    int wait_time = 0, turnaround_time = 0, arrival_time[10], burst_time[10],
temp[10];
    float average_wait_time = 0, average_turnaround_time = 0;
    bool round_robin_algorithm = true;
    for(i = 0; i < 10; i++)
    {
        arrival_time[i] = 0;
        burst_time[i] = 0;
        temp[i] = 0;
    }
     
    // Define Number of Processes
    while(num_processes < 1 || num_processes > 10)
    {
        printf("\nEnter Total Number of Processes (1 - 10):\t");
        scanf("%d", &num_processes);
        if (num_processes < 1 || num_processes > 10)
        {
            printf("Incorrect Value Entered");
        }
    
    }
// Define Process Details
    x = num_processes;
    for(i = 0; i < num_processes; i++)
    {
        printf("\nEnter Details of Process[%d]\n", i + 1);
        printf("Arrival Time (>-1):\t");
        scanf("%d", &arrival_time[i]);
           
        printf("Burst Time (>0):\t");
        scanf("%d", &burst_time[i]);
        temp[i] = burst_time[i];
       
        if (arrival_time[i] < 0 && burst_time[i] < 1) {
            printf("Incorrect Values Entered");
            i--;
        }
    }
 
    // Define Quantum
    if (round_robin_algorithm)
    {
        while(time_quantum < 1)
        {
            printf("\nEnter Time Quantum (>0):\t");
            scanf("%d", &time_quantum);
            if (time_quantum < 1)
            {
                printf("Incorrect Value Entered");
            }
        }
    }
     
    // Prepare Output
    printf("\nProcess ID\t\tArrival Time\t\tBurst Time\t Turnaround Time\tWaiting Time\n");

    // Perform Scheduling Calculations
    if (round_robin_algorithm)
    {
       //loop through burst times and check if all 0. break out if one >0 and in the for loop have a bool indicating
       //if they are done their burst. if they are, break out of while loop
       while(true){
	       bool done = false;
       for(int i = 0; i < num_processes; i++){
	      // this for loop changes a bool and breaks out of for loop if the processes are not done running
	if(burst_time[i]>0){
		done = false;
		break;
		}
	     done = true;
	   }
       if(done == true){
	   break;
       }
	//if they are not done and need more time, loop through burst times and subtract quantum.
	for(int i = 0; i < num_processes; i++){
		burst_time[i] = burst_time[i]-time_quantum;
	}
		//these are tests so we print something
	   average_wait_time = 10;
	   average_turnaround_time =10;
       }
       //end of while(true) loop. this means all processes are done executing 
    }
    else
    {
	int old_arrival=0;
      for(int i = 0;i<num_processes; i ++){
	average_wait_time = average_wait_time + burst_time[i];
 
	turnaround_time = turnaround_time + burst_time[i]-arrival_time[i]+old_arrival;
	wait_time = turnaround_time-burst_time[i];
	old_arrival = arrival_time[i];
	average_turnaround_time = average_turnaround_time + turnaround_time;
    	printf("\nProcess[%d]\t\t %d \t\t\t %d\t \t \t%d \t\t%d\n",i,arrival_time[i],burst_time[i],turnaround_time,wait_time);


     	
      }
      average_turnaround_time = average_turnaround_time/num_processes;
average_wait_time = average_wait_time/num_processes;
    }
    // Calculate & Print Average Wait and Turnaround Times
    //average_wait_time = 0;
    //average_turnaround_time = 0;
    printf("\n\nAverage Waiting Time:\t%f", average_wait_time);
    printf("\nAvg Turnaround Time:\t%f\n", average_turnaround_time);
    return 0;
}
