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
    addr.sin_port = htons(9018);
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

    double x,y;

    while(true)
    {
        switch (*botInf->serverState)
        {
        case STARTGAME:
            cout<<"I am behind X:"<<botInf->bot->realX<<" and Y: "<<botInf->bot->realY<<endl;
            botInf->bot->Move();
            x = abs(botInf->bot->X - botInf->bot->realX);
            y = abs(botInf->bot->Y - botInf->bot->realY);
            while(!( x < 0.001 && y < 0.01) )
            {
                botInf->bot->Step();
                x = abs(botInf->bot->X - botInf->bot->realX);
                y = abs(botInf->bot->Y - botInf->bot->realY);
                std::this_thread::sleep_for(dude);
                cout<<"I am behind X:"<<botInf->bot->realX<<" and Y: "<<botInf->bot->realY<<endl;           //Проверка
            }
            break;
        case WAITING:
            std::this_thread::sleep_for(dude);
            break;

        case RESULTS:
            std::this_thread::sleep_for(dude);
            break;

        case END:
            pthread_exit(0);
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
    double x,y;


    char b = 'B';

    while(true)
    {
        switch (*info->serverState)
        {
        case START:

            break;

        case WAITING:
            this_thread::sleep_for(dude);
            break;

        case STARTGAME:
            for(int i = 0;i<4;i++)
            {
                cout<<"player"<<i<<"in X: "<<*info->coord->X[i]<<" Y:"<<*info->coord->Y[i]<<endl;
            }
            send(info->player->socket,&b,sizeof(char),0);

            while(*info->serverState == STARTGAME)
            {

                recv(info->player->socket,&info->player->direction,sizeof(char),0);

                info->player->Move();

                x = abs(info->player->X - info->player->realX);
                y = abs(info->player->Y - info->player->realY);

               while(!( x < 0.001 && y < 0.01) )
                {
                    send(info->player->socket,info->coord,sizeof(Coordinats),0);
                    info->player->Step();
                    x = abs(info->player->X - info->player->realX);
                    y = abs(info->player->Y - info->player->realY);
                    std::this_thread::sleep_for(dude); //Задержка, чтобы time(NULL) выводил действительно случайные значения
                }
            }

            break;

        case RESULTS:

            break;

        case END:
            pthread_exit(0);
            break;

        default:
            std::this_thread::sleep_for(dude);
            break;
        }
    }






}


bool server::DoServer(int numb)
{
    chrono::milliseconds dude(333);
    chrono::seconds threadT(1);
    numbOfPlayers = numb;
    numbOfBots = 4 - numb;
//    players = new RealPlay[numb];
    players.resize(numbOfPlayers);
//    threads = new pthread_t[4]; //numb заменить на 4, когда сделаю ботов
    threads.resize(4);
    botsi.resize(numbOfBots);
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
//    bots = new BotPlayer*[4-numb];
    bots.resize(numbOfBots);
    for(int i = numb;i < 4; i++)
    {
//        BotPlayer tmp(grid);
        bots[i - numb] = new BotPlayer(grid);

        coordinats->X[i] = &bots[i - numb]->realX;
        coordinats->Y[i] = &bots[i - numb]->realY;
        BotInfo* bot = new BotInfo(&serverState,bots[i - numb]);
        botsi[i - numb] = bot;
        pthread_create(&threads[i],0,BotServis,static_cast<void*>(botsi[i - numb]));
        this_thread::sleep_for(threadT);
    }

    serverState = WAITING;

    chrono::seconds wait(10);

    this_thread::sleep_for(wait);

    serverState = STARTGAME;

    int summ;
    do
    {
      summ = 0;
      for(int i = 0; i < numbOfPlayers; i++)
      {
          summ += players[i]->score;
      }
      for(int i = 0; i < 4 - numbOfPlayers; i++)
      {
          summ += bots[i]->score;
      }

      chrono::seconds check(1);
      this_thread::sleep_for(check);

    }while(summ != 0);                //Не 0!!!!!

    serverState = RESULTS;

    this_thread::sleep_for(wait);

    serverState = END;


    for(int i = 0;i < 4 ;i++)    //Аналогично с потоками
    {

        pthread_join(threads[i],NULL);
        if(0)
        {
            perror("Bad join thr");
            exit(0);
        }
    }
    close(serverSock);

    return true;

}

server::~server()
{
    /*for(int i = 0;i < this->numbOfPlayers;i++)
    {
        delete players[i];
    }*/
    //delete[] players;
    players.clear();

    threads.clear();

    for(size_t i = 0 ; i < bots.size(); i++)
    {
        delete bots[i];
    }
    bots.clear();
    for(size_t i = 0 ; i < players.size(); i++)
    {
        delete players[i];
    }
    players.clear();
    close(serverSock);

    delete coordinats;
}


