
#include <stdio.h>

typedef struct rr
{
    int pid, bt, tat, wt, bt_bal;
} RR;

int main()
{
    RR p[10];
    int i, j, n, tq;
    int sum_bt = 0, sum_wt = 0, sum_tat = 0, tq_used = 0;

    printf("\nEnter the number of processes:\t");
    scanf("% d", &n);

    // JUST TAKING BURST TIME FROM USER
    for (i = 0; i < n; i++)
    {
        printf("\nEnter the burst time of process % d:\t", i + 1);
        p[i].pid = i + 1;
        scanf("% d", &p[i].bt);
        p[i].bt_bal = p[i].bt;
        // initially bt time and bt_bal will be equal for a perticular process
        // we will reduce bal_bt as we process or execute it
    }

    printf("Enter the time quantum number:\t");
    scanf("% d", tq);

    // CALC TOTAL BURST TIME
    for (i = 0; i < n; i++)
        sum_bt += p[i].bt;

    printf("\nSum of burst time = % d\n", sum_bt);

    for (i = 0; i < n; i++)
    {
        if (p[i].bt_bal < 0) // invalid process 
        {
            printf("\nError: Burst time is negative\n");
            exit(1);
        }
    }
    

    do
    {
        // ITERATING OVER ALL PROCESSES
        for (i = 0; i < n; i++)
        {
            // p[i].bt_bal > 0    -> means valid bt_balance
            // p[i].bt_bal <= tq  -> means we can complete that complete process in the tq

            if (p[i].bt_bal == 0) // completely executed process
                continue;
            else if (p[i].bt_bal > 0 && p[i].bt_bal <= tq)
            {
                tq_used    += p[i].bt_bal;         // not full but bt_bal tq could only be used
                p[i].tat    = tq_used;             // tat = ct - at; tat = ct; since at = 0 assume
                                                   // ct  = tq_used
                p[i].wt     = p[i].tat - p[i].bt;
                p[i].bt_bal = 0;
            }
            else if (p[i].bt_bal > tq)
            {
                tq_used     += tq; // full tq will be used since process is bigger than the tq
                p[i].bt_bal -= tq; // remaining process after tq time
            }
        }
    } while (tq_used < sum_bt); // until all process gets executed completely

    for (i = 0; i < n; i++)
        sum_wt += p[i].wt;

    for (i = 0; i < n; i++)
        sum_tat += p[i].tat;

    printf("\nTotal waiting time    = % d    \n", sum_wt);
    printf("Average waiting time    = % .2f  \n", (float)sum_wt / n) ;
    printf("\n");
    printf("Total turnaround time   = % d    \n", sum_tat);
    printf("Average turnaround time = % .2f  \n", (float)sum_tat / n);
}


/*

root@localhost~]# gedit rounrobin.c
root@localhost~]# cc roundrobin.c
[root@localhost ~]# ./a.out

Enter the  number of processes:     3
Enter the burst time of process 1:     24
Enter the burst time of process 2:      3
Enter the burst time of process 3:      3

Sum of burst time=30

Total waiting time=17
Average waiting time=5.67

Total turnaround time=47
Average turnaround time=15.67

*/