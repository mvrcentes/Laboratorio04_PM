//Programación de Microprocesadores
//Laboratorio 4 Parte 1 secuencial
//Marco Ramirez 21032

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#define NTHREADS 3

pthread_t threads[NTHREADS];
int silo;
int bodega;
pthread_mutex_t lock;

void* toaster(void *arg){
    long i = (long)arg;
    i += + 1;
    					
    while((bodega < 400) && ((silo + bodega) < 400)){
        pthread_mutex_lock(&lock);      //establecer bloqueo antes utilizar recursos compartidos
        silo += 1;               

        pthread_mutex_unlock(&lock);    //liberar el bloqueo
        
        std::cout << "Tostadora " << i << ":\tTosto una libra" << std::endl;
        std::cout << "\n\n\t\tLibras de cafe en silo " << silo << std::endl;
        
        sleep(1);
    }           	
    return NULL;							
}

void* baler(void *arg){
    while (bodega < 400){
        if((silo >= 5) || (bodega >= 5)){
            pthread_mutex_lock(&lock);

            bodega += 1;
            silo -= 1;
            
            pthread_mutex_unlock(&lock);
            
            std::cout << "\n\nSe ha empacado 1 libra de cafe" << std::endl;
            std::cout << "\n\nLbras en bodega:\t" << bodega << std::endl;
            
            sleep(1);
        }
    }           								
    return NULL;
}

int main(void){
    int i = 0;
    int err;
    if (pthread_mutex_init(&lock, NULL) != 0){
        printf("\n mutex init failed\n");
        return 1;
    }

    pthread_create(&(threads[0]),NULL,&toaster,(void *)0);
    pthread_create(&(threads[1]),NULL,&toaster,(void *)1);
    pthread_create(&(threads[2]),NULL,&baler,(void *)2);

	for(i=0;i<NTHREADS;i++){
		pthread_join(threads[i], NULL);
    }

    printf ("\n------------------------------------------------\n");
    std::cout << "Libras de cafe en silo:\t" << silo << std::endl;
    std::cout << "Cantidad de empaques en bodega: \t" << bodega << std::endl;
    printf ("\n------------------------------------------------\n");

    pthread_mutex_destroy(&lock);									//destruccion de mutex dinamica ya usada

    return 0;
}