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


    char result[1024];

    sem_wait(full);
    sem_wait(mutex);

    strcpy(result, shmptr);
    printf("[message] %s\n", result);
    strcpy(shmptr,"over");

    sem_post(mutex);
    sem_post(empty);

    sem_wait(full);

    sem_close(mutex);
    sem_unlink("mutex_sem");

    sem_close(full);
    sem_unlink("full_sem");

    sem_close(empty);
    sem_unlink("empty_sem");

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
