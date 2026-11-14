#ifndef CHUNGO_CLIENTCONNECTION_H
#define CHUNGO_CLIENTCONNECTION_H
#include <pthread.h>

#define QUEUE_SIZE 128

struct ConnectionQueue {
    int fileDescriptor[QUEUE_SIZE];
    int head;
    int tail;

    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
};


#endif //CHUNGO_CLIENTCONNECTION_Hi