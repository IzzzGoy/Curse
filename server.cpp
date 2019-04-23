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

void* server::BotServis(void *args)
{
    BotInfo* botInf = reinterpret_cast<BotInfo*>(args);

    chrono::milliseconds dude(333);

    while(true)
    {
        switch (*botInf->serverState)
        {
        case STARTGAME:
            botInf->bot->Move();

            while(botInf->bot->X != botInf->bot->realX && botInf->bot->Y != botInf->bot->realY)
            {
                botInf->bot->Step();
                std::this_thread::sleep_for(dude);
            }
            break;
        default:
            std::this_thread::sleep_for(dude);
            break;
        }
    }

}



void* server::SelfServis(void* args)
{

    Contex* info = (Contex*) args;

    chrono::milliseconds dude(333);
    fcntl(info->player->socket, F_SETFL, O_NONBLOCK);


    char b = 'B';

    while(true)
    {
        switch (*info->serverState)
        {
        case START:

            break;

        case WAITING:
            cout<<*info->serverState<<endl;
            this_thread::sleep_for(dude);
            break;

        case STARTGAME:

            send(info->player->socket,&b,sizeof(char),0);

            while(*info->serverState == STARTGAME)
            {

                recv(info->player->socket,&info->player->direction,sizeof(char),0);

                info->player->Move();

                while(info->player->X != info->player->realX && info->player->Y != info->player->realY)
                {
                    send(info->player->socket,info->coord,sizeof(Coordinats),0);
                    info->player->Step();
                    std::this_thread::sleep_for(dude);
                }
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
    threads = new pthread_t[4]; //numb заменить на 4, когда сделаю ботов
    coordinats = new Coordinats(grid);
    for(int i = 0; i < numb; i++ )
    {
        int acceptSocket = accept(serverSock,0,0);
        if (acceptSocket > 0)
        {
            players[i] = new RealPlay(grid, acceptSocket);
            coordinats->X[i] = &players[i]->realX;
            coordinats->Y[i] = &players[i]->realY;
            Contex* mess = new Contex(players[i],serverState,grid,coordinats);
            if(pthread_create(&threads[i],0,&server::SelfServis, static_cast<void*>(mess)) != 0)
            {
                perror("Bad thread create");
                exit(-1);
            }
        }

    }
    bots = new BotPlayer*[4-numb];
    for(int i = numb;i < 4; i++)
    {
        bots[i - numb] = new BotPlayer(grid);
        coordinats->X[i - numb] = &bots[i - numb]->realX;
        coordinats->Y[i - numb] = &bots[i - numb]->realY;
        BotInfo bot = BotInfo(&serverState,bots[i - numb]);
        pthread_create(&threads[i],0,BotServis,static_cast<void*>(&bot));

    }

    serverState = WAITING;

    chrono::seconds wait(10);
    this_thread::sleep_for(wait);

    serverState = STARTGAME;

    int summ;
    do
    {
      summ = 0;
      for(size_t i = 0; i < numbOfPlayers; i++)
      {
          summ += players[i]->score;
      }
      for(size_t i = 0; i < 4 - numbOfPlayers; i++)
      {
          summ += bots[i]->score;
      }

      chrono::seconds check(1);
      this_thread::sleep_for(check);

    }while(summ != 210);

    serverState = RESULTS;

    this_thread::sleep_for(wait);

    serverState = END;

    close(serverSock);
    for(int i = 0;i < 4 ;i++)    //Аналогично с потоками
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

    delete[] bots;

    delete coordinats;
}


