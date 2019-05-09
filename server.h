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
#include "semaf.h"

using namespace std;

class server
{
private:

    //vector<RealPlay> players;
    enum State
    {
        START = 0,
        WAITING,
        STARTGAME,
        RESULTS,
        END
    };
    Semaf semaf;
    int serverSock;
    struct sockaddr_in addr;
    int grid[400] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                     -1, 3, 3, 3, 3, 3, 3, 3, 3,-1,-1, 3, 3, 3, 3, 3, 3, 3, 3,-1,
                     -1, 3,-1, 3, 3,-1,-1,-1, 3, 3, 3, 3,-1,-1,-1, 3, 3,-1, 3,-1,
                     -1, 3,-1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,-1, 3,-1,
                     -1, 3,-1,-1,-1, 3, 3,-1,-1, 3, 3,-1,-1, 3, 3,-1,-1,-1, 3,-1,
                     -1, 3, 3, 3, 3, 3, 3,-1,-1, 3, 3,-1,-1, 3, 3, 3, 3, 3, 3,-1,
                     -1,-1,-1,-1,-1, 3, 3,-1,-1, 3, 3,-1,-1, 3, 3,-1,-1,-1,-1,-1,
                     -1, 3, 3, 3,-1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,-1, 3, 3, 3,-1,
                     -1,-1, 3,-1,-1, 3, 3,-1,-1, 3, 3,-1,-1, 3, 3,-1,-1, 3,-1,-1,
                      3, 3, 3, 3, 3, 3, 3,-1, 3, 3, 3, 3,-1, 3, 3, 3, 3, 3, 3, 3,
                      3, 3, 3, 3, 3, 3, 3,-1, 3, 3, 3, 3,-1, 3, 3, 3, 3, 3, 3, 3,
                     -1,-1, 3,-1,-1, 3, 3,-1,-1,-1,-1,-1,-1, 3, 3,-1,-1, 3,-1,-1,
                     -1, 3, 3, 3,-1,-1, 3, 3, 3, 3, 3, 3, 3, 3,-1,-1, 3, 3, 3,-1,
                     -1,-1,-1,-1,-1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,-1,-1,-1,-1,-1,
                     -1, 3, 3, 3, 3, 3, 3,-1,-1,-1,-1,-1,-1, 3, 3, 3, 3, 3, 3,-1,
                     -1, 3, 3, 3,-1,-1, 3, 3, 3,-1,-1, 3, 3, 3,-1,-1, 3, 3, 3,-1,
                     -1,-1,-1, 3, 3, 3, 3,-1, 3, 3, 3, 3,-1, 3, 3, 3, 3,-1,-1,-1,
                     -1, 3, 3, 3,-1,-1,-1,-1,-1, 3, 3,-1,-1,-1,-1,-1, 3, 3, 3,-1,
                     -1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,-1,
                     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    vector<RealPlay*> players;

    State serverState;
    int numbOfPlayers;
    int numbOfBots;
    vector<pthread_t> threads;
public:
    struct Coordinats
    {
        Coordinats(int* tmp)
        {
            X.resize(4);
            Y.resize(4);
            grid = tmp;
        }
        std::vector<double*> Y;
        vector <double*> X;
        int* grid;
        /*~Coordinats()
        {
            X.clear();
            Y.clear();
        }*/
    };

    struct Contex
    {
        Coordinats* coord;
        int* grid;
        RealPlay* player;
        State* serverState;
        Contex(RealPlay* _player,State *st,int*table,Coordinats* _coord)
        {
            coord = _coord;
            grid = table;
            player = _player;
            serverState = st;
        }
    };

    struct BotInfo
    {
        State* serverState;
        BotPlayer* bot;
        Semaf* sem;
        BotInfo(State* _serverState, BotPlayer* _bot,Semaf* _sem)
        {
            serverState =_serverState;
            bot = _bot;
            sem = _sem;
        }
        ~BotInfo()
        {
        }
    };
    vector<BotPlayer*> bots;
    vector<BotInfo*> botsi;
    Coordinats* coordinats;
    static void* SelfServis(void* args);
    static void* BotServis(void* args);
    void DoServer(int numbOfPlayers);

    void SetReal(int numb);
    server();
    ~server();
};

#endif // SERVER_H
