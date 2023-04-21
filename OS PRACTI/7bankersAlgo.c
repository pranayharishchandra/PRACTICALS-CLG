
#include <stdio.h>

struct process
{
    int max[10], alloc[10], need[10];
} p[6];

int avail[10], n, r, safe[10];
void getdata();
void banker();

main()
{
    getdata();
    banker();
}

void getdata()
{
    int i, j;
    printf("Enter the number of process=>\n");
    scanf("%d", &n);
    printf("Enter the number of resources=>\n");
    scanf("%d", &r);
    printf("Enter Allocated Resources=>\n");
    for (i = 0; i < n; i++)
    {
        printf("Process p%d\n", i);
        for (j = 0; j < r; j++)
            scanf("%d", &p[i].alloc[j]);
    }
    printf("Enter Max of Each Process\n");
    for (i = 0; i < n; i++)
    {
        printf("Process p%d\n", i);
        for (j = 0; j < r; j++)
            scanf("%d", &p[i].max[j]);
    }
    printf("Enter the Current Available Resources \n");
    for (i = 0; i < r; i++)
        scanf("%d", &avail[i]);
    printf("Need Matrix\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < r; j++)
        {
            p[i].need[j] = p[i].max[j] - p[i].alloc[j];
            printf("%d\t", p[i].need[j]);
        }
        printf("\n");
    }
}

void banker()
{
    int flag, c = 0, finish[10], i, j, f, s;
    for (i = 0; i < n; i++)
        finish[i] = 0;
    do
    {
        f = 0;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < r; j++)
            {
                flag = 0;
                if (p[i].need[j] > avail[j])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0 && finish[i] == 0)
            {
                f = 1;
                printf("After process p%d Available Resources=", i);
                for (j = 0; j < r; j++)
                {
                    p[i].need[j] = 0;
                    avail[j] = p[i].alloc[j] + avail[j];
                    printf("%d\t", avail[j]);
                }
                printf("\n");
                safe[c++] = i;
                finish[i] = 1;
            } // if
        }     // for
        if (f == 0)
            break;
    } while (f == 1);
    s = 1;
    for (i = 0; i < n; i++)
        if (finish[i] == 0)
        {
            printf("Cannot Allocate Requested Resources for Process p%d", i);
            s = 0;
            break;
        }
    if (s != 0)
    {
        printf("----SAFE STATE----\n");
        printf("Safe sequence:\n");
        for (i = 0; i < c; i++)
            printf("p%d\t", safe[i]);
        printf("\n");
    }
    else
        printf("----UNSAFE STATE----\n");
} // banker

/*

For Safe State

root@localhost~]# gedit banker.c
root@localhost~]# cc banker.c
[root@localhost ~]# ./a.out

Enter the number of process=> 5
Enter the number of resources=> 3
Enter Allocated Resources=>
Process p0
0 1 0
Process p1
2 0 0
Process p2
3 0 2
Process p3
2 1 1
Process p4
0 0 2

Enter Max of Each Process
Process p0
7 5 3
Process p1
3 2 2
Process p2
9 0 2
Process p3
2 2 2
Process p4
4 3 3

Enter the Current Available Resources
3 3 2

Need Matrix
7	4	3
1	2	2
6	0	0
0	1	1
4	3	1

After process p1 Available Resources= 5 3 2
After process p3 Available Resources= 7 4 3
After process p4 Available Resources= 7 4 5
After process p0 Available Resources= 7 5 5
After process p2 Available Resources= 10 5 7

----SAFE STATE----

Safe Sequence:
p1	p3	p4	p0	p2


For Unsafe State

root@localhost~]# gedit banker.c
root@localhost~]# cc banker.c
[root@localhost ~]# ./a.out


Enter the number of process=> 4
Enter the number of resources=> 3
Enter Allocated Resources=>
Process p0
0 1 2
Process p1
3 1 0
Process p2
0 2 2
Process p3
2 1 1

Enter Max of Each Process
Process p0
6 3 2
Process p1
4 3 2
Process p2
8 3 3
Process p3
8 1 8

Enter the Current Available Resources
2 3 2

Need Matrix
6	2	0
1	2	2
8	1	1
6	0	7

After process p1 Available Resources= 5 4 2
Cannot Allocate Requested Resources for Process p0

----UNSAFE STATE----



*/