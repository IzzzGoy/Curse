#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string>
#include <chrono>
#include <fcntl.h>
#include <unistd.h>
#include <thread>
#include <vector>

#include "realplay.h"

using namespace std;

class server
{
private:


    //vector<RealPlay> players;
    int serverSock;
    struct sockaddr_in addr;
    int grid[400] = {0};
    //vector<RealPlay*> players;
    RealPlay **players;
    int serverState;
    int numbOfPlayers;
    pthread_t tmp;

public:

    struct Contex
    {
        RealPlay* player;
        int* serverState;
        Contex(RealPlay* _player,int &st)
        {
            player = _player;
            serverState = &st;
        }
    };
    static void* SelfServis(void* args);
    bool DoServer(int numbOfPlayers);

    void SetReal(int numb);
    server();
    ~server();
};

#endif // SERVER_H
