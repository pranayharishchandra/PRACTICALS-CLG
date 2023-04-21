/*
this program is a parallel implementation of the Fibonacci series generator using OpenMP, which is a popular API for parallel programming in C and C++.
*/
#include <stdio.h>
#include <omp.h>

int fib(int n)
{
    if (n < 2)
        return n;
    else
        return fib(n - 1) + fib(n - 2);
}

int main()
{
    int fibnum[100], i, j, n;
    printf("Enter the series limit: ");
    scanf("% d", &n);

#pragma omp parallel num_threads(2) shared(fibnum, n) private(i, j) // openmp directive
/*
The #pragma omp parallel directive tells the compiler to create a parallel section of the code. 
The num_threads(2) clause specifies that two threads should be used to execute the code. 
The shared(fibnum, n) clause indicates that the arrays fibnum and variable n should be shared among all threads, 
while the private(i, j) clause specifies that the loop variables i and j should be private to each thread.
*/
    {
        if (omp_get_thread_num() == 0)
        {
            printf("There are % d threads\n", omp_get_num_threads());
            printf("Thread % d is generating number.\n", omp_get_thread_num());
            for (i = 0; i < n; i++)
                fibnum[i] = fib(i);
        }

#pragma omp barrier // To make the second thread wait till first one finishes the work
/*
The #pragma omp barrier directive is used to synchronize the two threads. 
It ensures that the second thread (identified by omp_get_thread_num() != 0) will wait until the first thread (thread 0) completes its work.
*/
        if (omp_get_thread_num() != 0)
        {
            printf("Thread % d is printing number.\n", omp_get_thread_num());
            for (j = 0; j < n; j++)
                printf("% d\t", fib(j));
                // printf("% d\t", fibum[j]); // it's actually correct.. 
            printf("\n");
        }
    }
    return 0;
}

/*
Enter the series limit: 7
There are 2 threads
Thread 1 is generating number.
Thread 2 is printing number.
1     1     2     3     5     8     13

chatGPT -- mathematica
cc -fopenmp filename.c

Enter the series limit: 7
There are 2 threads
Thread 0 is generating number.
Thread 1 is printing number.
0	1	1	2	3	5	8	
*/
