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
#include <cmath>

#include "realplay.h"
#include "botplayer.h"

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
    vector<RealPlay*> players;
    //RealPlay *players;
//    BotPlayer **bots;

    State serverState;
    int numbOfPlayers;
    int numbOfBots;
    vector<pthread_t> threads;
    //pthread_t* threads;
    //vector<pthread_t> threads;
    //pthread_t tmp;
public:
    struct Coordinats
    {
        Coordinats(int* tmp)
        {
            grid = tmp;
        }
        double* Y[4];
        double* X[4];
        int* grid;
        ~Coordinats()
        {
            for(int i = 0;i < 4; i++)
            {
                delete Y[i];
            }
            for(int i = 0;i < 4; i++)
            {
                delete X[i];
            }
            delete[] X;
            delete[] Y;
            delete[] grid;
        }
    };

    struct Contex
    {
        Coordinats* coord;
        int* grid;
        RealPlay* player;
        State* serverState;
        Contex(RealPlay* _player,State &st,int*table,Coordinats* _coord)
        {
            coord = _coord;
            grid = table;
            player = _player;
            serverState = &st;
        }
    };

    struct BotInfo
    {
        State* serverState;
        BotPlayer* bot;
        BotInfo(State* _serverState, BotPlayer* _bot)
        {
            serverState =_serverState;
            bot = _bot;
        }
        ~BotInfo()
        {
            delete bot;
        }
    };
    vector<BotPlayer*> bots;
    vector<BotInfo*> botsi;
    Coordinats* coordinats;
    static void* SelfServis(void* args);
    static void* BotServis(void* args);
    bool DoServer(int numbOfPlayers);

    void SetReal(int numb);
    server();
    ~server();
};

#endif // SERVER_H
