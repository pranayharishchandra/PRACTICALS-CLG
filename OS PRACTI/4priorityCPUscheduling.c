#include <stdio.h>

typedef struct priority
{
    int pid, bt, tat, wt, prty;
} PRIORITY;

// at -> of all process are assumed to be 0
// tat = ct - at = at + sum_bt = sum_bt
// tat = sum_bt
// wt  = tat - bt
int main()
{
    PRIORITY p[10], temp;
    int i, j, n;
    int sum_bt = 0, sum_wt = 0, sum_tat = 0;
    printf("\nEnter the number of processes:\t");
    scanf("% d", &n);

    // TAKING INPUT
    for (i = 0; i < n; i++)
    {
        printf("\nEnter the burst time and priority of the process % d :\t", i + 1);
        p[i].pid = i + 1;
        scanf("% d % d", &p[i].bt, &p[i].prty);
    }

    // SORTING BASED ON PRIORITY -- prty no lesser -- more prty -- process in beginning
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (p[i].prty > p[j].prty)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }

    // MAIN LOOP
    for (i = 0; i < n; i++)
    {
        sum_bt   += p[i].bt;              // adding the burst time to calc tat

        p[i].tat  = sum_bt ;              // tat = bt + at but at = 0 so tat = bt,
                                          // tat for all the process 
                                          // tat = sum_bt
        p[i].wt   = p[i].tat - p[i].bt;
                                          
        sum_wt   += p[i].wt ;             // calc sum_wt and sum_tat to calc avg of them
        sum_tat  += p[i].tat;
    }

    printf("\nTotal waiting time    = % d   \n", sum_wt);
    printf("Average waiting time    = % .2f \n", (float)sum_wt / n);
    printf("\n");
    printf("Total turnaround time   = % d   \n", sum_tat);
    printf("Average turnaround time = % .2f \n", (float)sum_tat / n);
}


/*

root@localhost~]# gedit priority.c
root@localhost~]# cc priority.c
[root@localhost ~]# ./a.out

Enter the number of processes:     5
Enter the burst time and priority of the process 1:       10    3
Enter the burst time and priority of the process 2:       1     1
Enter the burst time and priority of the process 3:       2     4
Enter the burst time and priority of the process 5:       1     5
Enter the burst time and priority of the process 1:       5     2

Total waiting time=41
Average waiting time=8.20

Total turnaround time=60
Average turnaround time=12.00

*/