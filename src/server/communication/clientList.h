#ifndef CHUNGO_CLIENTLIST_H
#define CHUNGO_CLIENTLIST_H

#include <pthread.h>

typedef struct Client
{
    int command_socket;
    int data_socket;
    int connection_start_timestamp;
}
Client;

typedef struct ClientListItem
{
    Client* client;
    struct ClientListItem* next;
} ClientListItem;

typedef struct ClientList
{
    ClientListItem* first;
    ClientListItem* last;
    int count;

    pthread_mutex_t mutex;
} ClientList;

void add_client(int command_socket);
void remove_client(int command_socket);

#endif //CHUNGO_CLIENTLIST_H
