
// FCFS
 
#include <stdio.h>
int main()
{
      int b[10], t[10], w[10];
      int n, i, j;
      float tot_wt, tot_tat;

      printf("Enter the number of processes:\t");
      scanf("%d", &n);

      // ONLY TAKING BURST TIME AS INPUT
      for (i = 0; i < n; i++)
      {
            printf("\n Enter the burst time of process %d:\t", i);
            scanf("%d", &b[i]);
      }

      w[0] = 0; // since first come first serve and waiting time of 1st process will be 0

      for (i = 1; i < n; i++) {
            w[i] = w[i - 1] + b[i - 1]; // completion time of previous process -- after it curr procs starts
      }

      for (i = 0; i < n; i++) {
            t[i] = w[i] + b[i];         // tat = wt + bt + at=0;
      }

      for (i = 0; i < n; i++) {
            tot_wt  += w[i];
            tot_tat += t[i];
      }

      printf("Total waiting time      = %f\n", tot_wt);

      printf("Average waiting time    = %f\n", (float)tot_wt / n);
      printf("\n");
      printf("Total turnaround time   = %f\n", tot_tat);

      printf("Average turnaround time = %f\n", (float)tot_tat / n);
}

// SJF

#include <stdio.h>
/* int p[10], b[10], w[10], t[10] 
   make a structure and put them in it so swapping will be easier
*/
int main()
{
      int p[10], b[10], w[10], t[10], i, n, j, temp, temp1;
      float tot_wt = 0, tot_tat = 0;

      printf("Enter the number of processes:\t");
      scanf("%d", &n);

      // ONLY ENTER THE BURST TIME
      for (i = 0; i < n; i++)
      {
            printf("Enter the burst time of process %d:\t", i);
            scanf("%d", &b[i]);
            p[i] = i;
      }

      // SWAPPING ACCORDING TO BURST TIME
      for (i = 0; i < n - 1; i++)
      {
            for (j = i + 1; j < n; j++)
            {
                  if (b[i] > b[j])
                  {
                        temp  =  b[i];
                        temp1 =  p[i];
                        b[i]  =  b[j];
                        p[i]  =  p[j];
                        b[j]  =  temp;
                        p[j]  =  temp1;
                  }
            }
      }

      w[0] = 0; //      WAITING TIME OF THE FIRST PROCESS (SMALLEST BT PROCESS) WILL BE 0

      for (i = 1; i < n; i++) {
            w[i] = w[i - 1] + b[i - 1]; // completion time of previous process -- after it curr procs starts
      }

      for (i = 0; i < n; i++) {
            t[i] = w[i] + b[i];         // tat = wt + bt + at=0;
      }

      for (i = 0; i < n; i++) {
            tot_wt = tot_wt + w[i];
            tot_tat = tot_tat + t[i];
      }

      printf("\n\t Processes \t waiting time \t turnaround time\n");

      for (i = 0; i < n; i++)
            printf("\t P%d     %d       %d\n", p[i], w[i], t[i]);

      printf("Total waiting time      = %f\n", tot_wt);
      
      printf("Average waiting time    = %f\n", (float) tot_wt / n);
      printf("\n");
      printf("Total turnaround time   = %f\n", tot_tat);
      
      printf("Average turnaround time = %f\n", (float)tot_tat / n);
}


/*
FCFS
root@localhost~]# gedit fcfs.c
root@localhost~]# cc fcfs.c
[root@localhost ~]# ./a.out

Enter the  number of processes:     3
Enter the burst time of process 0:     24
Enter the burst time of process 1:      3
Enter the burst time of process 2:      3

Total waiting time=51.000000
Average waiting time=17.000000

Total turnaround time=81.000000
Average turnaround time=27.000000

SJF
root@localhost~]# gedit sjf.c
root@localhost~]# cc sjf.c
[root@localhost ~]# ./a.out

Enter the  number of processes:     3
Enter the burst time of process 0:     24
Enter the burst time of process 1:      3
Enter the burst time of process 2:      3

Processes               waiting time               turnaround time
      P1                                 0                                    3
      P2                                 3                                    6
      P0                                 6                                   30   

Total waiting time=9.000000
Average waiting time=3.000000

Total turnaround time=39.000000
Average turnaround time=13.000000

*/