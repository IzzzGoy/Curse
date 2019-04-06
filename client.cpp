#include "client.h"

client::client()
{

}

bool client::StartClient(char address[])
{
    socketClient = socket(AF_INET,SOCK_STREAM,0);
    addr.sin_port = htons(1222);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(address);

    int m = connect(socketClient,(struct sockaddr*)&addr,sizeof(addr));
    //std::cout<<m<<std::endl;

}
