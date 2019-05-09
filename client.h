#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <chrono>
#include <thread>
#include <fcntl.h>

using namespace std;

class client
{
private:
    struct sockaddr_in addr;
    int socketClient;

public:

    bool StartClient(char address[]);
    //void SendToServer();
    void CloseClient();
    client();
    void setdirection(char direct);
    bool acceptcoord();
    bool t;
    char direction = 'u';


    struct Coordinats
    {
        vector<double*> Y;
        vector <double*> X;
        int* grid;
        /*~Coordinats()
        {
            for(int i = 0;i < 4; i++)
            {
                delete Y[i];
            }
            for(int i = 0;i < 4; i++)
            {
                delete X[i];
            }
            X.clear();
            Y.clear();
        }*/
    };
    Coordinats coordinats;
};

#endif // CLIENT_H
