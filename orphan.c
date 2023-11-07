#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void sort(int arr[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=i;i<n-i-1; j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}


int main(){
    pid_t cid;
    int n;
    printf("Enter number of integers -> ");
    scanf("%d", &n);
    printf("erfwer\n");
    int arr[n];
    for(int i=0; i<n; i++){
        printf("%d -> ",i+1);
        scanf("%d", &arr[i]);
    }
    cid = fork();
    
    if(cid == 0){
        printf("This is child process and it's id is -> %d", getpid());
        printf("Child is sorting array\n");
        printf("Parent id -> %d", getppid());
        printf("Child id -> %d", getpid());
        // sort(arr,n);
        sleep(1);
        printf("Sorting done\n");
        printf("Parent id -> %d", getppid());
        printf("Child id -> %d", getpid());
    }else{
        printf("This is parent process and it's id is -> %d", getpid());
    }


    return 0;
}