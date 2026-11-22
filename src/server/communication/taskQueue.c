#include "taskQueue.h"

#include <pthread.h>
#include <stdlib.h>

#include "logger.h"


static struct TaskQueue* q = NULL;

int init_taskQueue() {
    /*
     * The insert is at the position of the next insert
     * The head is at the position of the first element if there is any
     */
    q = malloc(sizeof(struct TaskQueue));
    if (q == NULL)
    {
        LOG(ERROR, "Failed to allocate memory for task queue");
        return -1;
    }
    q->head = 0;
    q->insert = 0;
    q->count = 0;

    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);

    return 1;
}

void destroy_taskQueue()
{
    free(q);
}

void add_task(const int client_socket){

    pthread_mutex_lock(&q->mutex);

    while (q->count == QUEUE_SIZE){
        pthread_cond_wait(&q->not_full, &q->mutex);
    }

    q->fileDescriptors[q->insert] = client_socket;
    q->insert = (q->insert + 1) % QUEUE_SIZE;

    q->count++;

    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->mutex);
}

int take_task(){
    pthread_mutex_lock(&q->mutex);

    while (q-> count == 0){
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }

    const int client = q->fileDescriptors[q->head];
    q->head = (q->head + 1) % QUEUE_SIZE;
    q->count--;

    pthread_mutex_unlock(&q->mutex);

    return client;
}