#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/wait.h>

int rl = 0;
int rwl = 0;

int data;

void *readd(void *arg){
    int reader = *(int*)arg;
    while(1){
        if(rwl){
            printf("R%d someone is writing\n");
            sleep(rand()%5+1);  
        }else{
            rwl = 1;
            int temp = data;
            printf("R%d reads -> %d\n", reader, temp);
            rwl = 0;
            sleep(rand()%5+1);
        }
        printf("\n");
    }
    pthread_exit(NULL);
}

void *writee(void *arg){
    int writer = *(int*)arg;
    while(1){
        if(rwl){
            printf("W%d someone is writing\n");
            sleep(rand()%5+1); 
        }else{
            rwl = 1;
            data = rand()%10+1;
            printf("W%d writes -> %d\n",writer, data);
            rwl = 0;
            sleep(rand()%5+1);
        }
        printf("\n");
    }
}


int main(){

    int writer_no, reader_no;
    printf("Enter number of writers\n");
    scanf("%d", &writer_no);
    printf("\n");
    printf("Enter number of readers\n");
    scanf("%d", &reader_no);
    printf("\n");

    pthread_t writer_thread[writer_no];
    pthread_t reader_thread[reader_no];

    int writers[writer_no];
    int readers[reader_no];

    for(int i=0;i<writer_no;i++){
        writers[i] = i+1;
        pthread_create(&writer_thread[i], NULL, writee, &writers[i]);
        // pthread_join(writer_thread[i], NULL);
    }
    for(int i=0;i<reader_no;i++){
        readers[i] = i+1;
        pthread_create(reader_thread[i], NULL, readd, &readers[i]);
        // pthread_join(reader_thread[i], NULL);
    }
    for(int i=0;i<writer_no;i++){
        pthread_join(writer_thread[i], NULL);
    }
    for(int i=0;i<reader_no;i++){
        pthread_join(reader_thread[i], NULL);
    }


    return 0;
}