#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

int ready = 0;
void* producer(void* arg) {
    int i = 0;
    while (i<10) {
        i++;
        sleep(1);
        pthread_mutex_lock(&mutex);
        while(ready) 
        {
            pthread_cond_wait(&condition, &mutex);
        }
        
        if(i == 10)
        {
            ready = -1;
            printf("Отдаю последний сигнал\n");
        }
        else 
        {
            ready = 1; 
            printf("Отдача\n");
        }
        pthread_cond_signal(&condition);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        while (!ready) {
            pthread_cond_wait(&condition, &mutex);
        }

        if(ready == -1){
            printf("Обрабатываю последний сигнал\n");
            pthread_mutex_unlock(&mutex);
            break;
        }

        printf("Принятие. Обработка\n");
        ready = 0;

        pthread_mutex_unlock(&mutex);

    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition);

    printf("End of Programm\n");
    return 0;
}
