#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

class client
{
private:
    struct sockaddr_in addr;
    int socketClient;

public:

    bool StartClient(char address[]);
    void SendToServer();
    client();
};

#endif // CLIENT_H
