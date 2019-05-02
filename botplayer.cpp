#include "botplayer.h"
#include <iostream>

BotPlayer::BotPlayer(int* _grid)
{
    std::cout << "bot _grid: " << _grid << std::endl;
    grid = _grid;
    std::cout << "bot new grid: " << grid << std::endl;
    srand(time(NULL));
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
    speed = 0.1;
    int tmp = rand() % 4;
    switch (tmp)
    {
    case 0:
        direction = 'u';
        break;
    case 1:
        direction = 'd';
        break;
    case 2:
        direction = 'l';
        break;
    case 3:
        direction = 'r';
        break;
    default:
        break;
    }
    direction = 'u';
}

void BotPlayer::Move()
{
    int N = 20;
    switch (direction)
    {
    case 'u':
        if(grid[(X - 1)*N + Y] != 0 && abs(X-0)<0.1 )
        {
            ChangeDir();
            Move();
        }
        else
        {
            X--;
            if(grid[X*N + Y] == 3)
            {
                score++;
                grid[X*N + Y] = 0;
            }
        }
        break;
    case 'd':
        if(grid[(X + 1) * N + Y] != 0 && X < 20)
        {
            ChangeDir();
            Move();
        }
        else
        {
            X++;
            if(grid[X*N + Y] == 3)
            {
                score++;
                grid[X*N + Y] = 0;
            }
        }
        break;
    case 'l':
        if(grid[X*N + Y - 1] != 0 && abs(Y-0)<0.1)
        {
            ChangeDir();
            Move();
        }
        else
        {
            Y--;
            if(grid[X*N + Y] == 3)
            {
                score++;
                grid[X*N + Y] = 0;
            }
        }

        break;

    case 'r':
        if(grid[X * N + Y + 1] != 0 && Y < 20)
        {
            ChangeDir();
            Move();
        }
        else
        {
            Y++;
            if(grid[X*N + Y] == 3)
            {
                score++;
                grid[X*N + Y] = 0;
            }
        }
        break;
    default:
        break;
    }
}

void BotPlayer::ChangeDir()
{

    bool tmp[4] = {true};

    if(grid[(X - 1)*N + Y] != 0 && X == 0)tmp[0] = false;
    else tmp[0] = true;

    if(grid[(X + 1) * N + Y] != 0 && X < 20)tmp[1] = false;
    else tmp[1] = true;

    if(grid[X*N + Y - 1] != 0 && Y == 0)tmp[2] = false;
    else tmp[2] = true;

    if(grid[X * N + Y + 1] != 0 && Y < 20)tmp[3] = false;
    else tmp[3] = true;

    size_t mp = rand()% 4;
    size_t i = mp++;

    while(mp != i)
    {
        if(i > 3) i = 0;
        if(tmp[i])
        {
            direction = posDir[i];
            break;
        }
    }

}
void BotPlayer::Step()
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

void BotPlayer::ClearSteps()
{
    modf(realX,&realX);
    modf(realY,&realY);
}
