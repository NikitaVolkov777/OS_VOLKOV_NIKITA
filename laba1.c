#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

int ready = 0;
int i = 0;
void* producer(void* arg) {
    while (i<10) {
        sleep(1);
        pthread_mutex_lock(&mutex);
        ready = 1; 
        printf("Отдача\n");
        pthread_cond_signal(&condition);
        pthread_mutex_unlock(&mutex);
        i++;
    }
    return NULL;
}

void* consumer(void* arg) {
    while (i<10) {
        pthread_mutex_lock(&mutex);

        while (!ready) {
            pthread_cond_wait(&condition, &mutex);
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