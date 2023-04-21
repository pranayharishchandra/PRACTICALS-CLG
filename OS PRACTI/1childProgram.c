#include <stdio.h>
#include <unistd.h> // for the fork function

int main()
{
    int ch;
    char cmd[20];
    int pid = fork(); // The return value of fork() is stored in the variable pid.

    if (pid == 0) /* child process execution */
    {
        printf("\n Child process");
        do
        {
            printf("\n Enter the command:");
            scanf("%s", &cmd);
            system(cmd);
            printf("\n Enter 1 to continue or 0 to exit:");
            scanf("%d", &ch);
        } while (ch != 0);
    }
    else        /* parent execution*/
        wait(); /* Block the parent until the completion of the child*/
}

/*
The system() function is a C standard library function that allows a program to execute a command as if it were typed on the command line.
*/

/*
Expected Results


[root@localhost~]# gedit child.c
[root@localhost~]# cc child.c
[root@localhost~]# ./a.out

 Child process
 Enter the command: date
 Thu May 07 13:17:32 IST 2009

 Enter 1 to continue or 0 to exit:1

 Enter the command: ls
 1a.sh  2a.sh  3a.sh  4a.sh  5a.sh  6a.sh  7a.sh  1b.c   2b.c   3b.c   4b.c   5b.c   6b.c   7b.c    child.c a.out  cc    

 Enter 1 to continue or 0 to exit: 1

 Enter the command: who
 root     :0           Sep 10 12:54
 root     pts/1        Sep 10 12:55 (:0.0)

 Enter 1 to continue or 0 to exit: 1

 Enter the command: ps
  PID TTY          TIME CMD
 3620 pts/1    00:00:00 bash
 3705 pts/1    00:00:00 a.out
 3706 pts/1    00:00:00 a.out
 3711 pts/1    00:00:00 ps

 Enter 1 to continue or 0 to exit: 1

 Enter the command: pwd
/root/hema/unix

 Enter 1 to continue or 0 to exit: 0
[root@localhost~]# 

*/