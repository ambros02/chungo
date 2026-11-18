#ifndef CHUNGO_CONNECTIONQUEUE_H
#define CHUNGO_CONNECTIONQUEUE_H
#include <pthread.h>

#define QUEUE_SIZE 256

struct ConnectionQueue {
    int fileDescriptors[QUEUE_SIZE];
    int head;
    int tail;
    int count;

    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
};


#endif