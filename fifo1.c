#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#define buffsize 1024


int main(){

    char stringg[1024];
    int res = mkfifo("fifo", 0666);
    while (1){
        int fifo = open("fifo", O_RDWR);
        printf("Enter a string\n");
        fgets(stringg, 1024,stdin);
        printf("%s\n", stringg);
        write(fifo, stringg, buffsize);
        close(fifo);
        sleep(10);
    }
    


    return 0;
}