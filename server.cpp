#include "server.h"
#include <QDebug>

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
    addr.sin_port = htons(1488);
    addr.sin_addr.s_addr = INADDR_ANY;

    int bindStatus = bind(serverSock,(struct sockaddr*)&addr,sizeof(addr));

    if (bindStatus == -1)
    {
        perror("Bad bind!");
        exit(-1);
    }
    listen(serverSock,10);

    // Создание типикал сервера для потоков
    serverState = START;    //Переменная состояния сервера на старт игры

}

void* server::SelfServis(void* args)
{

    Contex* player = (Contex*) args;

    chrono::milliseconds dude(333);

    chrono::time_point<chrono::system_clock> start;

    chrono::time_point<chrono::system_clock> end;

    char b = 'B';

    while(true)
    {
        switch (*player->serverState)
        {
        case START:

            break;

        case WAITING:
            cout<<*player->serverState<<endl;
            this_thread::sleep_for(dude);
            break;

        case STARTGAME:

            start = chrono::system_clock::now();
            end = chrono::system_clock::now();

            send(player->player->socket,&b,sizeof(char),0);
            while(true)
            {
                recv(player->player->socket,&player->player->direction,sizeof(char),0);

                player->player->Move(player->grid);

                while(player->player->X != player->player->realX && player->player->Y != player->player->realY)
                {
                    if(chrono::duration_cast<chrono::minutes>(end - start).count() == 15)break;
                    switch (player->player->direction)
                    {
                    case 'u':
                        player->player->realX -= player->player->speed;
                        std::this_thread::sleep_for(dude);
                        break;
                    case 'd':
                        player->player->realX += player->player->speed;
                        std::this_thread::sleep_for(dude);
                        break;
                    case 'l':
                        player->player->realY -= player->player->speed;
                        std::this_thread::sleep_for(dude);
                        break;
                    case 'r':
                        player->player->realY += player->player->speed;
                        std::this_thread::sleep_for(dude);
                        break;
                    default:
                        break;
                    }
                }
                end = chrono::system_clock::now();
            }

            break;

        case RESULTS:

            break;

        case END:

            break;

        default:
            break;
        }
    }






}


bool server::DoServer(int numb)
{
    numbOfPlayers = numb;
    players = new RealPlay*[numb];
    threads = new pthread_t[numb]; //numb заменить на 4, когда сделаю ботов
    coordinats = new Coordinats;
    for(int i = 0; i < numb; i++ )
    {
        int acceptSocket = accept(serverSock,0,0);
        if (acceptSocket > 0)
        {
            RealPlay* player = new RealPlay(grid, acceptSocket);
            players[i] = player;
            coordinats->X[i] = &player->realX;
            coordinats->Y[i] = &player->realY;
            Contex* mess = new Contex(player,serverState,grid,coordinats);
            if(pthread_create(&threads[i],0,&server::SelfServis, reinterpret_cast<void*>(mess)) != 0)
            {
                perror("Bad thread create");
                exit(-1);
            }
        }

    }
    // подключение ботов

    serverState = WAITING;

    chrono::seconds wait(10);
    this_thread::sleep_for(wait);

    serverState = STARTGAME;

    chrono::minutes game(10);
    this_thread::sleep_for(game);

    serverState = RESULTS;

    this_thread::sleep_for(wait);

    serverState = END;

    close(serverSock);
    for(int i = 0;i < numb ;i++)    //Аналогично с потоками
    {
        int ir;
        pthread_join(threads[i],(void**)&ir);
        if(0)
        {
            perror("Bad join thr");
            exit(0);
        }
    }

    return true;

}

server::~server()
{
    for(int i = 0;i < this->numbOfPlayers;i++)
    {
        delete players[i];
    }
    delete[] players;

    delete[] threads;
}


