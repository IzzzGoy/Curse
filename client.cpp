#include "client.h"

client::client()
{

}

bool client::StartClient(char address[])
{
    socketClient = socket(AF_INET,SOCK_STREAM,0);
    addr.sin_port = htons(6488);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(address);

    connect(socketClient,(struct sockaddr*)&addr,sizeof(addr));
//    fcntl(socketClient, F_SETFL, O_NONBLOCK);
    return true;
}

void client::CloseClient()
{
    close(socketClient);
}

void client::setdirection(char direct)
{
    send(socketClient,&direct,sizeof(char),0);
}

bool client::acceptcoord()
{
    chrono::milliseconds dude(33);
//    this_thread::sleep_for(dude);
    recv(socketClient,&t,sizeof(bool),0);
    if(t)
    {
        recv(socketClient,&coordinats,sizeof(coordinats),0);
        return true;
    }
    else
    {
     return false;
    }
}
