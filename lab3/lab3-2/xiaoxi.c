#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>


typedef struct msgbuf
{
    long mtype;
    char mtext[128];
}msgbuf;


sem_t full;
sem_t empty;
sem_t mutex;


int msgid;

msgbuf buf;

void *receive(void *a)
{

    int flag=0;
    while(1)
    {

        if(flag==2){
            sem_destroy(&full);
            sem_destroy(&empty);
            sem_destroy(&mutex);
            break;
        }

        sem_wait(&full);
        sem_wait(&mutex);


        msgrcv(msgid,&buf,sizeof(buf.mtext),1,0);

        printf("Receiver thread: %s\n\n",buf.mtext);        
        if(strcmp(buf.mtext,"end1") == 0)
        {
            flag=flag+1;
            buf.mtype=2;
            strcpy(buf.mtext,"over1");
            msgsnd(msgid,&buf,sizeof(buf.mtext),0);
        }else if(strcmp(buf.mtext,"end2") == 0)
        {
            flag=flag+1;
            buf.mtype=2;
            strcpy(buf.mtext,"over2");
            msgsnd(msgid,&buf,sizeof(buf.mtext),0);
        }else {
            sem_post(&empty);
        }
                sem_post(&mutex);



    }
   msgctl(msgid,IPC_RMID,NULL);
   pthread_exit(NULL);
}

void *sender(void *a)
{
    char s[100];
    char end[10];
    char send[20];
    sprintf(end,"end%d",*(int *)a);
    sprintf(send," (sender %d)",*(int *)a);

    buf.mtype = 1;
    int flag=0;
    while(1)
    {
        sem_wait(&empty);
        sem_wait(&mutex);

        printf("Input the message to sender %d\n",*(int *)a);
        scanf("%s",s);
        if(strcmp(s,"exit") == 0)
        {
            strcpy(s,end);
            strcpy(buf.mtext,s);
            msgsnd(msgid,&buf,sizeof(buf.mtext),0);
            printf("Sender process: %s\n",buf.mtext );
            sem_post(&mutex);
            sem_post(&full);
        }
    }
    while (1)
    {
        ssize_t st = msgrcv(msgid,&buf,sizeof(buf.mtext),2,IPC_NOWAIT);
        if(st!=-1){
            printf("Response content: ");
            printf("%s\n",buf.mtext );
            printf("Thanks for use sender%d!\n",*(int *)a);
            buf.mtype=1;
            break;
        }
    }
        sem_post(&empty);
    pthread_exit(NULL);
}

int main()
{

    pthread_t sender1;
    pthread_t sender2;
    pthread_t receive1;
    key_t key = 0;

    int send1=1,send2=2;
    sem_init(&full,0,0);
    sem_init(&empty,0,1);
    sem_init(&mutex,0,1);


    if((msgid = msgget(key, IPC_EXCL|IPC_CREAT)) == -1) {
        printf("Create  Error\n");
        exit(0);
    }
    pthread_create(&sender1,NULL,sender,&send1);
    pthread_create(&sender2,NULL,sender,&send2);
    pthread_create(&receive1,NULL,receive,NULL);

    pthread_join(sender1,NULL);
    pthread_join(sender2,NULL);
    pthread_join(receive1,NULL);

    return 0;
}
