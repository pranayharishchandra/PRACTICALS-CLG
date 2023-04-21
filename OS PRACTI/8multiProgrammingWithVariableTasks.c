
#include <stdio.h>
main()
{
    int i, m, n, tot, pg_size[20];
    printf("Enter total memory size:");
    scanf("%d", &tot);
    printf("Enter number of pages:");
    scanf("%d", &n);
    printf("Enter memory for OS:");

    scanf("%d", &m);

    for (i = 0; i < n; i++) {
        printf("Enter size of page%d:", i + 1);
        scanf("%d", &pg_size[i]);
    }

    // rem_mem -> remaining memory or leftover memory
    int rem_mem = tot - m; // (m) is the reserverd memory of the total memory (tot)

    for (i = 0; i < n; i++)
    {
        if (rem_mem >= pg_size[i])
        {
            printf("Allocate page : %d\n", i + 1);
            rem_mem = rem_mem - pg_size[i];
        }
        else
            printf("process p%d is blocked\n", i + 1);
    }
    printf("External Fragmentation is:%d", rem_mem);
}

/*

[root@localhost~]# gedit mvt.c
root@localhost~]# cc mvt.c
[root@localhost ~]# ./a.out

Enter total memory size: 50
Enter number of pages: 4
Enter memory for OS: 10
Enter size of page1: 10
Enter size of page2: 9
Enter size of page3: 9
Enter size of page4: 10
Allocate page : 1
Allocate page : 2
Allocate page : 3
Allocate page : 4
External Fragmentation is: 2

*/