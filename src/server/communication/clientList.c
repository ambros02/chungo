

#include "clientList.h"

#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#include "logger.h"


static ClientList client_list = {
    .first = NULL,
    .last = NULL,
    .count = 0,
};

void init_client_list()
{
    pthread_mutex_init(&client_list.mutex, NULL);
}

void destroy_client_list()
{
    pthread_mutex_destroy(&client_list.mutex);
}

void add_client(int command_socket)
{
    Client client = {
        .command_socket = command_socket,
        .data_socket = -1,
        .connection_start_timestamp = (int)time(NULL)
    };

    ClientListItem new_item = {
        .client = &client,
        .next = NULL,
    };

    pthread_mutex_lock(&client_list.mutex);
    if (client_list.last == NULL)
    {
        client_list.first = &new_item;
    } else
    {
        client_list.last->next = &new_item;
    }
    client_list.last = &new_item;
    client_list.count++;
    
    pthread_mutex_unlock(&client_list.mutex);
};

void remove_client(int command_socket)
{
    ClientListItem* item = client_list.first;
    if (item->client->command_socket == command_socket)
    {
        client_list.first = item->next;
        free(item);
        client_list.count--;
    }

    while (item->next != NULL && item->next->client->command_socket != command_socket)
    {
        item = item->next;
    }
    if (item->next == NULL)
    {
        LOG(WARNING, "could not find client with command socket %d socket not found in active connection list", command_socket);
    } else
    {
        item->next = item->next->next;
        client_list.count--;
    }
}