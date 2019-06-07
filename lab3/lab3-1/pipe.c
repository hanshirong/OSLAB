# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#define PIPLEN 100

sem_t sem;
int pipeSize(){
        int ret,count=0,filedes[2];
        pipe(filedes);
        fcntl(filedes[1],F_SETFL,O_NONBLOCK);
        while(1) {
                 ret=write(filedes[1],"1",1);
                 if(ret==-1)
                         break;
                 count++;
                }
         printf("The length of unamed pipe is:%dB\n\n",count);
        close(filedes[0]);
         close(filedes[1]);
        return count;
 }
 void err(){
        printf("fork error!\n");
         exit(0);
 }

int main(){
        int fd[2];
        pid_t p1,p2,p3;
        char message[PIPLEN];
        char out[PIPLEN];
        int maxSize=pipeSize();
        pipe(fd);
        sem_init(&sem,1,1);
        if (( p1=fork())==-1){
                err();
        }
        if (p1==0)
        {
                sem_wait(&sem);
                close(fd[0]);
                char message[PIPLEN] = "i am the child1 message\n";
                printf("child1\n");
                write(fd[1],message,sizeof(message));
          sem_post(&sem);
                exit(0);
        }
        else{
                if (( p2=fork())==-1){
                err();
                }
                 if (p2==0)
                 {
                        sem_wait(&sem);
                        close(fd[0]);
                      char message[PIPLEN] = "i am the child2 message\n";
                        printf("child2\n");
                         write(fd[1],message,sizeof(message));
                        sem_post(&sem);
                        exit(0);

                }
                else{
                         if (( p3=fork())==-1){
                                err();
                                }
                         if (p3==0)
                         {
                        sem_wait(&sem);
                        close(fd[0]);
                        char message[PIPLEN] = "i am the child3 message\n";
                        printf("child3\n");
                        write(fd[1],message,sizeof(message));
                        sem_post(&sem);
                         exit(0);

}
                        else{
                                waitpid(p1,NULL,WUNTRACED);
                                 waitpid(p2,NULL,WUNTRACED);
                                waitpid(p3,NULL,WUNTRACED);
                                close(fd[1]);
                            while(1){
                                        int status=read(fd[0],out,sizeof(out));
                                        if(status<=0)
                                        break;
                                        else
                                        printf("%s",out);
                                }
                        return 0;
                        }
                }
        }


        return 0;
}
