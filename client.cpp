#include "client.h"

client::client()
{

}

bool client::StartClient(char address[])
{
    socketClient = socket(AF_INET,SOCK_STREAM,0);
    addr.sin_port = htons(3488);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(address);

    connect(socketClient,(struct sockaddr*)&addr,sizeof(addr));
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
    bool tmp;
    recv(socketClient,&tmp,sizeof(bool),0);
    if(tmp)
    {
        recv(socketClient,&coordinats,sizeof(coordinats),0);
        return true;
    }
    else
    {
     return false;
    }
}
