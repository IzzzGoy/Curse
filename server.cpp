#include "server.h"
#include <QDebug>
/*struct Contex
{
    int** table;
    RealPlay* player;
    int* serverState;
    Contex(int* grid[],RealPlay* _player,int* st)
    {
        table = grid;
        player = _player;
        serverState = st;
    }
};*/

server::server()
{
    serverSock = socket(AF_INET,SOCK_STREAM,0);
    //cout<<serverSock<<endl;
    //fcntl(serverSock, F_SETFL, O_NONBLOCK);///Помни, это только, если while будет рaботать по таймеру chrono
    if(serverSock == -1)
    {
        cout<<"Bad socket!"<<endl;
        exit(-1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1222);
    addr.sin_addr.s_addr = INADDR_ANY;

    int bindStatus = bind(serverSock,(struct sockaddr*)&addr,sizeof(addr));

    if (bindStatus == -1)
    {
        perror("Bad bind!");
        exit(-1);
    }
    listen(serverSock,10);
    serverState = 0;

}

void* server::SelfServis(void* args)
{
    /*int* tmp = (int*) args;
    int N = tmp[0];*/

    Contex* player = (Contex*) args;

    int y =*player->serverState;

    cout<<y<<endl;
   // if(pthread_join(pthread_self(),))
    //player = NULL;
    //delete player;
    pthread_exit(0);
}


bool server::DoServer(int numb)
{
    players = new RealPlay*[numb];
    //players.resize(numb);
    for(size_t i = 0; i < numb; i++ )
    {
        int acceptSocket = accept(serverSock,0,0);
        if (acceptSocket > 0)
        {
            RealPlay* player = new RealPlay(grid, acceptSocket);
            players[i] = player;
            Contex mess = Contex(player,serverState);
            pthread_create(&tmp,0,&server::SelfServis,(void*)&mess);
            cout<<"Thread started!";
            serverState = 8;
        }

    }
    serverState = 8;
    return true;

}

server::~server()
{
  /*  for(int i = 0;i<players.size();i++)
    {
        close(players[i]->socket);
    }
    players.clear();

*/
}


