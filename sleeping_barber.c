//Benjamin Acevedo Franqui
//Lab 4
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 5

sem_t barberoo;
sem_t clientes;
sem_t silla; 
int sillasLibres;
int Numthreads;


void * barbero(void * param);
void * cliente(void * param);

void * barbero(void * param)
{
  while(1){
      sem_wait(&clientes);
      sem_wait(&silla);
      sillasLibres++;
      printf("Sillas libres: %d\n", sillasLibres);
      sem_post(&barberoo); 
      sem_post(&silla);
      printf("Cient with barbero\n");
  }
}

void * cliente(void * param)
{
   while(1){
   sem_wait(&silla);
   if(sillasLibres>0)
   {
  sillasLibres--;
  printf("cliente se sienta y espera\n");
  printf("sillas libres: %d\n", sillasLibres);
    sem_post(&clientes);
        sem_post(&silla);
    sem_wait(&barberoo);
   } 
   else
   {
    sem_post(&silla);
  printf("no chairs");
   }
}
}

int main(int argc, char * argv[])
{
    sillasLibres = atoi(argv[1]);
    Numthreads = atoi(argv[2]);
    int sillas = sillasLibres;
    printf("sillas libres: %d\n", sillasLibres);

    pthread_t barbertr; 
    pthread_t clientetr;

    sem_init(&barberoo, 0, 0);
    sem_init(&clientes,0,0);
    sem_init(&silla,0,1);

    int i; 
    for (i = 0; i < Numthreads; i++){
       pthread_create(&clientetr, NULL, cliente ,NULL);
  pthread_create(&barbertr, NULL, barbero,NULL);
    }
    pthread_join(clientetr, NULL);
    pthread_join(barbertr, NULL);
    return 0;

}