#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<semaphore.h>
#include<stdlib.h>
#define capacity 3

int buffer[capacity];
int ptr = -1;

sem_t full, empty;
pthread_mutex_t mutex;

int producer_no, consumer_no;

void *produce(void *arg){
    int producer = *((int*)arg);
    while(1){
        if(ptr == capacity){
            printf("P%d -> Container is Full\n", producer);
            sleep(3);
        }else{
            sem_wait(&empty);
            pthread_mutex_lock(&mutex);
            int item = rand()%10+1;
            buffer[++ptr] = item;
            printf("P%d -> placed %d\n", producer, item);
            pthread_mutex_unlock(&mutex);
            sem_post(&full);
            sleep(item);
        }
        printf("\n");
        
    }
    pthread_exit(NULL);
}

void *consume(void *arg){
    int consumer = *((int*)arg);
    while(1){
        if(ptr == -1){
            printf("C%d -> Container is Empty\n", consumer);
            sleep(3);
        }else{
            int sle = rand()%10+1;

            sem_wait(&full);
            pthread_mutex_lock(&mutex);
            int item = buffer[ptr--];
            printf("C%d -> cunsumed %d\n", consumer, item);
            pthread_mutex_unlock(&mutex);
            sem_post(&empty);
            sleep(sle);
        }
        printf("\n");
    }
    pthread_exit(NULL);
}

int main(){

    printf("Enter number of Produers\n");
    scanf("%d", &producer_no);
    printf("Enter number of Consumers\n");
    scanf("%d", &consumer_no);

    int producers[producer_no];
    int consumers[consumer_no];
    // printf("array init\n");
    sem_init(&full, 0, 0);
    sem_init(&empty, 0 ,capacity);
    pthread_mutex_init(&mutex, NULL);
    // printf("sem init\n");

    for(int i=0;i<producer_no;i++)producers[i] = i+1;
    for(int i=0;i<consumer_no;i++)consumers[i] = i+1;

    pthread_t producer_threads[producer_no];
    pthread_t consumer_threads[consumer_no];
    // printf("threads init\n");

    for(int i=0; i<producer_no;i++){
        pthread_create(&producer_threads[i], NULL, produce, &producers[i]);
    }
    // printf("created proth\n");


    for(int i=0; i<consumer_no;i++){
        pthread_create(&consumer_threads[i], NULL, consume, &consumers[i]);
    }
    // printf("created conth\n");


    for(int i=0; i<producer_no;i++){
        pthread_join(producer_threads[i], NULL);
    }

    for(int i=0; i<consumer_no;i++){
        pthread_join(consumer_threads[i], NULL);
    }

    // while(1);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}