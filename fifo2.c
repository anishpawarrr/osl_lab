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

    char string[1024];
    int res = mkfifo("fifo", 0666);
    while (1){
        int fifo = open("fifo", O_RDWR);
        printf("the string\n");
        read(fifo, string, buffsize);
        printf("%s\n", string);
        int txt = open("file.txt", O_WRONLY);
        write(txt, string, strlen(string));
        close(txt);
        close(fifo);
        sleep(10);
    }
    return 0;
}