#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#define shmkey 1234
#define buffersize 1024


int main(){
    int shmid;
    char message[buffersize];
    char *shmptr;
    

    while(1){
        shmid = shmget(shmkey, buffersize,IPC_CREAT | 0666);
        shmptr = shmat(shmid, NULL, 0);
        printf("Enter your message");
        fgets(message, buffersize, stdin);
        strcpy(shmptr, message);
        shmdt(shmptr);
        sleep(2);
    }
    return 0;
}