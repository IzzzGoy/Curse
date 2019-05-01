#include "client.h"

client::client()
{

}

bool client::StartClient(char address[])
{
    socketClient = socket(AF_INET,SOCK_STREAM,0);
    addr.sin_port = htons(9018);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(address);

    connect(socketClient,(struct sockaddr*)&addr,sizeof(addr));
    return true;
}

void client::CloseClient()
{
    close(socketClient);
}
