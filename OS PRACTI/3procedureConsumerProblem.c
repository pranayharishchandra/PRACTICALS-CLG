/*
mutual exclusion object
In computer programming, a mutex (mutual exclusion object) is a program object that is created so that multiple program threads can take turns sharing the same resource, such as access to a file.
*/
#include <stdio.h>
#include <stdlib.h> // to use exit(0)

void producer();
void consumer();
int wait(int);
int signal(int);

/* 
mutex is the variable used by the 2 threads... 
just to take feeling of parallel programming with two threads.
so we are decreasing he value of mutex so other thread don't start before this thread ends it's work.. 
of may be calling a consumer or producer funciton
*/

// av_spc   -> avalible space for items in buffer
// av_itms  -> current no of items in buffer
// x        -> item no. which is same as av_itms

int mutex = 1, av_itms = 0, av_spc = 3, x = 0;

int main() {
    int n;

    printf("\n1. PRODUCER\n2. CONSUMER\n3. EXIT\n");

    while (1) {
        printf("\nENTER YOUR CHOICE: ");
        scanf("%d", &n);

        switch (n) {
            case 1:
                if ((mutex == 1) && (av_spc > 0))
                    producer();
                else
                    printf("BUFFER IS FULL\n");
                break;

            case 2:
                if ((mutex == 1) && (av_itms > 0))
                    consumer();
                else
                    printf("BUFFER IS EMPTY\n");
                break;

            case 3:
                exit(0);
                break;
        }
    }
}

int wait(int s) {
    return (--s);
}

int signal(int s) {
    return (++s);
}

void producer() {
    mutex   = wait(mutex);        // mutex dec to 0

    av_itms = signal(av_itms);
    av_spc  = wait(av_spc);        // producer can store 3 items buffer
    x++; // x is same as av_itms?
    printf("PRODUCER PRODUCES ITEM %d\n", x);
    
    mutex  = signal(mutex);      // mutex inc to 1
}

void consumer() {
    mutex   = wait(mutex);        // mutex dec to 0

    av_itms = wait(av_itms);
    av_spc  = signal(av_spc);
    printf("CONSUMER CONSUMES ITEM %d\n", x);
    x--; // x is same as av_itms?

    mutex   = signal(mutex);      // mutex inc to 1
}


/*
root@localhost~]# gedit prodcons.c
root@localhost~]# cc prodcons.c
[root@localhost ~]# ./a.out

1.PRODUCER 2.CONSUMER 3.EXIT 
ENTER YOUR CHOICE 
2
BUFFER IS av_spc
ENTER YOUR CHOICE 
1
producer produces the item1 
ENTER YOUR CHOICE 
1
producer produces the item2 
ENTER YOUR CHOICE 
1
producer produces the item3
ENTER YOUR CHOICE 
1
BUFFER IS av_itms 
ENTER YOUR CHOICE 
2
consumer consumes item3 
ENTER YOUR CHOICE 
2
consumer consumes item2
ENTER YOUR CHOICE 
2
consumer consumes item1
ENTER YOUR CHOICE 
2
BUFFER IS av_spc 
*/
