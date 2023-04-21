#include <stdio.h>

// Define a structure for each process, which includes arrays for the maximum, allocated, and needed resources
struct process
{
    int max[10];
    int alloc[10];
    int need[10];
} p[6]; // Create an array of 6 process structures

int avail[10]; // Define an array for the available resources
int n, r;      // Define integers for the number of processes and resources
int safe[10];  // Define an array for the safe sequence of processes

// Declare function prototypes
void getdata();
void banker();

int main()
{
    getdata(); // Call function to get input data
    banker();  // Call function to run the banker's algorithm
    return 0;
}

// Function to get input data from the user
void getdata()
{
    int i, j;

    printf("Enter the number of processes:\n");
    scanf("%d", &n);

    printf("Enter the number of resources:\n");
    scanf("%d", &r);

    // Get the allocated resources for each process from the user
    printf("Enter allocated resources:\n");
    for (i = 0; i < n; i++)
    {
        printf("Process p%d:\n", i);
        for (j = 0; j < r; j++)
        {
            scanf("%d", &p[i].alloc[j]);
        }
    }

    // Get the maximum resources for each process from the user
    printf("Enter the maximum resources for each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("Process p%d:\n", i);
        for (j = 0; j < r; j++)
        {
            scanf("%d", &p[i].max[j]);
        }
    }

    // Get the current available resources from the user
    printf("Enter the current available resources:\n");
    for (i = 0; i < r; i++)
    {
        scanf("%d", &avail[i]);
    }

    // Calculate and display the need matrix for each process
    printf("Need Matrix:\n");
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

// Function to run the banker's algorithm
void banker()
{
    int flag, c = 0, finish[10], i, j, f, s;

    // Initialize the finish array to 0 for all processes
    for (i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    do
    {
        f = 0;

        // Iterate through all processes
        for (i = 0; i < n; i++)
        {
            flag = 0;

            // Check if the need of the process is less than or equal to the available resources
            for (j = 0; j < r; j++)
            {
                if (p[i].need[j] > avail[j])
                {
                    flag = 1; // Set flag to 1 if need is greater than available
                    break;
                }
            }

            // If the need is less than or equal to the available resources and the process is not already finished
            if (flag == 0 && finish[i] == 0)
            {
                f = 1; // Set f to 1 to indicate progress has been made

                // Update the available resources and mark the process as finished
                printf("After process p%d, Available Resources: ", i);
                for (j = 0; j < r; j++)
                {
                    p[i].need[j] = 0;                    // The process no longer needs any resources
                    avail[j] = p[i].alloc[j] + avail[j]; // Add the allocated resources back to the available pool
                    printf("%d\t", avail[j]);            // Print the updated available resources
                }
                printf("\n");

                // Add the finished process to the safe sequence
                safe[c++] = i;
                finish[i] = 1;
            }
        }

        // If no progress was made in this iteration, break out of the loop
        if (f == 0)
        {
            break;
        }

    } while (f == 1);

    // Check if all processes have finished
    s = 1;
    for (i = 0; i < n; i++)
    {
        if (finish[i] == 0)
        {
            printf("Cannot allocate requested resources for process p%d\n", i);
            s = 0; // Set s to 0 to indicate an unsafe state
            break;
        }
    }

    // If all processes finished, print the safe sequence
    if (s != 0)
    {
        printf("\n----SAFE STATE----\n");
        printf("Safe sequence: ");
        for (i = 0; i < c; i++)
        {
            printf("p%d ", safe[i]);
        }
        printf("\n");
    }
    else
        printf("----UNSAFE STATE----\n");
}

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