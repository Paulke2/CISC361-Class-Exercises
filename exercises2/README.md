7) to me, round robin seems better for a larger quantity of small processes, but FCFS may be better for larger processes all about
the same size. in FCFS however, if the largest process arrives first, the average turnaround will be far worse than RR. same for wait time.

8) a scenario where FCFS is better than RR: if we have jobs that are all around the same size, FCFS will be better than RR as we 
do not have to do so many context switches as opposed to RR.

   a scenario when RR is better: if we have a very large job that arrives first, RR is far better than FCFS as the smaller jobs
do not have to wait for the largest job to finish to get CPU time with RR.

9) if the burst times were all less than the quantum, it would pretty much be(or would be) a FCFS algorithm. an easy solution to this,would simply be to decrease the quantum.
