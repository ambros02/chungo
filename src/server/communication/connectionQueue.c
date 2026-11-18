#include "connectionQueue.h"

#include <pthread.h>
#include <stdlib.h>


static struct ConnectionQueue* q = NULL;

struct ConnectionQueue* queue_init() {
    q = malloc(sizeof(struct ConnectionQueue));
    q->head = 0;
    q->tail = 0;
    q->count = 0;

    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);
    return q;
}

void add_client(int client_socket){
    pthread_mutex_lock(&q->mutex);
    if (q->count == QUEUE_SIZE){
        pthread_cond_wait(&q->not_full, &q->mutex);
    }
    q->fileDescriptors[q->tail] = client_socket;
    q->tail = (q->tail + 1) % QUEUE_SIZE;
    pthread_mutex_unlock(&q->mutex);
}

int take_client(){
    pthread_mutex_lock(&q->mutex);
    if (q-> count == 0){
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }
    const int client = q->fileDescriptors[q->head];
    q->head = (q->head + 1) % QUEUE_SIZE;
    pthread_mutex_unlock(&q->mutex);
    return client;
}