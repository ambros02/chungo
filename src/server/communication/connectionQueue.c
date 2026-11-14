#include "connectionQueue.h"

#include <pthread.h>
#include <stdlib.h>


static struct ConnectionQueue* q = NULL;

struct ConnectionQueue* queue_init() {
    q = malloc(sizeof(struct ConnectionQueue));
    q->head = 0;
    q->tail = 0;

    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);
    return q;
}

void add_to_queue(int client_socket){
    if (q->tail == QUEUE_SIZE && q->head == 0){
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }
    if (q->head == q->tail){
        pthread_cond_wait(&q->not_full, &q->mutex);
    }
}