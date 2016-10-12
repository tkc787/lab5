#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 20

//int count = 0;
int in = 0;
int out = 0;
int buffer [BUFFER_SIZE];

sem_t mutex, empty, full;

pthread_t tid;

void insert(int item){
   //while (count == BUFFER_SIZE);
   sem_wait(&empty);
   sem_wait(&mutex);
   buffer[in] = item;
   in = (in + 1) % BUFFER_SIZE;
   sem_post(&mutex);
   sem_post(&full);
   //count++;
}

int remove_item(){
   int item;
   //while (count == 0);
   sem_wait(&full);
   sem_wait(&mutex);
   item = buffer[out];
   out = (out + 1) % BUFFER_SIZE;
   //count--;
   sem_post(&mutex);
   sem_post(&empty);
   return item;
}

void * producer(void * param){
   int item;
   while(1){
      item = rand() % BUFFER_SIZE ;
      insert(item);
      printf("inserted: %d\n", item);
   }
}

void * consumer(void * param){
   int item;
   while(1){
   item = remove_item();
   printf("removed: %d\n", item);
   }
}

int main(int argc, char * argv[])
{
    int producers = atoi(argv[1]);
    int consumers = atoi(argv[2]);

    int i;

    sem_init(&mutex, i, 1);
    sem_init(&full, i , 0);
    sem_init(&empty, i, BUFFER_SIZE);

    for (i = 0; i < producers; i++)
       pthread_create(&tid, NULL, producer,NULL);

    for (i = 0; i < consumers; i++)
       pthread_create(&tid, NULL, consumer, NULL);  
    pthread_join(tid,NULL);
}
