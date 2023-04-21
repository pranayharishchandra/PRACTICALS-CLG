#include <stdio.h>
#include <stdlib.h>

// block -> memory block

int main()
{
    int block[50], p, i, j, range, a, st_idx, len, n, c;

    // FULL MEMORY UNALLOCATED INITIALLY
    for (i = 0; i < 50; i++)
        block[i] = 0;

    // MARKING THE ALREADY ALLOCATED BLOCKS
    printf("Enter the blocks already allocated:\n");
    scanf("%d", &p);

    printf("\nEnter the block numbers:\n");
    for (i = 0; i < p; i++)
    {
        scanf("%d", &a);
        block[a] = 1;
    }

    // it's like a do-while loop
X:
    printf("Enter index starting block and length:\n");
    scanf("%d%d", &st_idx, &len);
    range = len;

    // len or range is basically the no of BLOCKS I WANT TO ALLOCATE apart from the already allocated memory blocks

    for (j = st_idx; j < (range + st_idx); j++)
    {
        if (block[j] == 0)
        {
            block[j] = 1;
            printf("\n%d->%d", j, block[j]);
        }
        else
        {
            printf("\n %d->file is already allocated", j);
            range++;
        }
    }

    printf("\nIf you want enter one more time (yes-1/no-0)");
    scanf("%d", &c);
    if (c == 1)
        goto X;
    else
        exit(0);
    
    return 0;
}

/*

[root@localhost~]# gedit contiguous.c
root@localhost~]# cc contiguous.c
[root@localhost ~]# ./a.out

Enter theblocks already allocated:
5
Enter the block numbers:
3
7
9
10
14
Enter index starting block and length:
4
10

4->1
5->1
6->1
7->file is already allocated
8->1
9->file is already allocated
10->file is already allocated
11->1
12->1
13->1
14->file is already allocated
15->1
16->1
17->1

*/
