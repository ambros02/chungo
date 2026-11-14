#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "socket.h"

#include <string.h>
#include <unistd.h>

#include "connectionQueue.h"
#include "logger.h"

static int serverSocket = -1;

int openServerSocket() {

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

    if (serverSocket < 0) {
        LOG(ERROR, "Failed to create socket");
        return -1;
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(37037);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serverSocket, (struct sockaddr*) &server_address, sizeof(server_address));
    listen(serverSocket, QUEUE_SIZE);
    return serverSocket;
}

int waitAndAcceptClients(struct ConnectionQueue queue) {
    int client_socket = accept(serverSocket,NULL,NULL);
    if (client_socket > 0) {

    }
}

int closeClientSocket(int client_socket) {
    close(client_socket);
    return 0;
}

int sendResponse(int client_socket, char* response) {
    send(client_socket, response, strlen(response), 0);
}

int closeServerSocket() {
    close(serverSocket);
    return 0;
}

int receiveResponse(int networkSocket)
{
    char server_response[1024];
    recv(networkSocket, &server_response, sizeof(server_response), 0);

    return 0;
}