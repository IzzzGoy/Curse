#include "realplay.h"
#include <iostream>
RealPlay::RealPlay(int* _grid,int sock,Semaf* sem)
{
    srand(time(NULL));
    std::cout << "_grid: " << _grid << std::endl;
    grid = _grid;
    std::cout << "new grid: " << grid << std::endl;
    std::cout << "0 " << grid[0];
    int tmpX,tmpY;
    do
    {
        tmpX = rand() % 20;
        tmpY = rand() % 20;
    }
    while(grid[20*tmpX + tmpY] != 0);
    X = tmpX;
    Y = tmpY;
    realX = X;
    realY = Y;
    score = 0;
    socket = sock;
    speed = 0.1;
    direction = 'u';
    this->sem = sem;

}

void RealPlay::Move()
{
    int N = 20;
    switch (this->direction)
    {
    case 'u':
        if(grid[(X - 1)*N + Y] != -1 && X != 0)X--;
        sem->Stop();
        sem->Take(X*N + Y);
        if(grid[X*N + Y] == 3)
        {           
            score++;
            grid[X*N + Y] = 0;
        }
        sem->Get(X*N + Y);
        break;
    case 'd':
        if(grid[(X + 1) * N + Y] != -1 && X != 19)X++;
        sem->Stop();
        sem->Take(X*N + Y);
        if(grid[X*N + Y] == 3)
        {          
            score++;
            grid[X*N + Y] = 0;           
        }
        sem->Get(X*N + Y);
        break;
    case 'l':
        if(grid[X*N + Y - 1] != -1 &&  Y != 1)Y--;
        sem->Stop();
        sem->Take(X*N + Y);
        if(grid[X*N + Y] == 3)
        {
            score++;
            grid[X*N + Y] = 0;          
        }
        sem->Get(X*N + Y);
        break;
    case 'r':
        if(grid[X * N + Y + 1] != -1 && Y != 19)Y++;
        sem->Stop();
        sem->Take(X*N + Y);
        if(grid[X*N + Y] == 3)
        {  
            score++;
            grid[X*N + Y] = 0;
        }
        sem->Get(X*N + Y);
        break;
    default:
        break;
    }
}

void RealPlay::Step()
{
    switch (this->direction)
    {
    case 'u':
        realX -= speed;
        break;

    case 'd':
        realX += speed;
        break;

    case 'l':
        realY -= speed;
        break;

    case 'r':
        realY += speed;
        break;

    default:
        break;
    }
}

void RealPlay::ClearSteps()
{
    modf(realX,&realX);
    modf(realY,&realY);
}
