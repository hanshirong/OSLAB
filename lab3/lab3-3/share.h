#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>
#include <errno.h>

#define KEY_NUM 1024

sem_t * full;
sem_t * empty;
sem_t * mutex;             
