#include "realplay.h"

RealPlay::RealPlay(int *grid,int sock)
{
    srand(time(NULL));
    int tmpX,tmpY;
    do
    {
        tmpX = rand() % 20;
        tmpY = rand() % 20;
    }
    while(grid[20*tmpX + tmpY] != 1);
    X = tmpX;
    Y = tmpY;
    realX = X;
    realY = Y;
    score = 0;
    socket = sock;
    speed = 0.1;
}

void RealPlay::Move(int *grid)
{
    int N = 20;
    switch (this->direction)
    {
    case 'u':
        if(X>0)X--;
        if(grid[X*N + Y] == 3)
        {
            score++;
            grid[X*N + Y] = 2;
        }
        /*while (realX != X)
        {
            realX -= speed;
            std::chrono::milliseconds dude(333);
            std::this_thread::sleep_for(dude);
        }*/
        break;
    case 'd':
        if(X<20)X++;
        if(grid[X*N + Y] == 3)
        {
            score++;
            grid[X*N + Y] = 2;
        }
        /*while (realX != X)
        {
            realX += speed;
            std::chrono::milliseconds dude(33);
            std::this_thread::sleep_for(dude);
        }*/

        break;
    case 'l':
        if(Y>0)Y--;
        if(grid[X*N + Y] == 3)
        {
            score++;
            grid[X*N + Y] = 2;
        }
        /*while (realY != Y)
        {
            realY -= speed;
            std::chrono::milliseconds dude(33);
            std::this_thread::sleep_for(dude);
        }*/
        break;
    case 'r':
        if(Y<20)Y++;
        if(grid[X*N + Y] == 3)
        {
            score++;
            grid[X*N + Y] = 2;
        }
        /*while (realY != Y)
        {
            realY += speed;
            std::chrono::milliseconds dude(33);
            std::this_thread::sleep_for(dude);
        }*/
        break;
    default:
        break;
    }
}

/*void RealPlay::SetDirection(char s)
{
    this->direction = s;
}*/
