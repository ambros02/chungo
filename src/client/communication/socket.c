#include "socket.h"

#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "logger.h"


int openClientSocket() {
    int networkSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (networkSocket < 0){
        LOG(ERROR, "Failed to create socket");
        return -1;
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(37037);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");


    int connection_status = connect(networkSocket, (struct sockaddr*) &server_address, sizeof(server_address));


    char server_response[256];
    recv(networkSocket, &server_response, sizeof(server_response), 0);

    printf("The server sent the data : %s\n", server_response);

    close(networkSocket);

    return 0;
}
