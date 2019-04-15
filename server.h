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
    enum State
    {
        START,
        WAITING,
        STARTGAME,
        RESULTS,
        END
    };

    int serverSock;
    struct sockaddr_in addr;
    int grid[400] = {0};
    //vector<RealPlay*> players;
    RealPlay **players;
    State serverState;
    int numbOfPlayers;
    pthread_t* threads;
    //vector<pthread_t> threads;
    //pthread_t tmp;
public:
    struct Coordinats
    {
        double* Y[4];
        double* X[4];
    };

    struct Contex
    {
        Coordinats* coord;
        int* grid;
        RealPlay* player;
        State* serverState;
        Contex(RealPlay* _player,State &st,int*table,Coordinats* coords)
        {
            coord = coords;
            grid = table;
            player = _player;
            serverState = &st;
        }
    };
    Coordinats* coordinats;
    static void* SelfServis(void* args);
    bool DoServer(int numbOfPlayers);

    void SetReal(int numb);
    server();
    ~server();
};

#endif // SERVER_H
