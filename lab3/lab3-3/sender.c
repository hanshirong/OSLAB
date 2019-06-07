#include "share.h"

int main(){

    int shmid = shmget(KEY_NUM, 1024, 0666|IPC_CREAT);
    if(shmid < -1){
        printf("error\n");
        exit(EXIT_FAILURE);
    }

    char * shmptr = shmat(shmid, NULL, 0);

    full = sem_open("full_sem", O_CREAT, 0666, 0);
    mutex = sem_open("mutex_sem", O_CREAT, 0666, 1);
    empty = sem_open("empty_sem", O_CREAT, 0666, 1);


    char input[1024];
    printf("Please input the message\n");
    scanf("%s", input);


    sem_wait(empty);
    sem_wait(mutex);

    strcpy(shmptr, input);

    sem_post(mutex);
    sem_post(full);


    char output[1024];
    sem_wait(empty);
    sem_wait(mutex);

    strcpy(output,shmptr);
    printf("[message] %s\n", output);

    sem_post(mutex);
    sem_post(full);

    return 0;
}
