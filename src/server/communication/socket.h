//
// Created by greenman on 11/4/26.
//

#ifndef CHUNGO_SOCKET_H
#define CHUNGO_SOCKET_H

int openServerSocket();

int closeServerSocket();

int receiveResponse(int networkSocket);

#endif //CHUNGO_SOCKET_H
