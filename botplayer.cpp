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
}

void BotPlayer::Move()
{
    int N = 20;
    int tmp;
    switch (direction)
    {
    case 'u':
        if(grid[(X - 1)*N + Y] != 0 && X > 0)
        {
            while(direction == 'u')
            {
                tmp = rand() % 4;
                switch (tmp)
                {
                case 0:
                    direction = 'u';
                    Move();
                    break;
                case 1:
                    direction = 'd';
                    Move();
                    break;
                case 2:
                    direction = 'l';
                    Move();
                    break;
                case 3:
                    direction = 'r';
                    Move();
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            X--;
        }
        break;
    case 'd':
        if(grid[(X + 1) * N + Y] != 0 && X < 20)
        {
            while(direction == 'd')
            {
                tmp = rand() % 4;
                switch (tmp)
                {
                case 0:
                    direction = 'u';
                    Move();
                    break;
                case 1:
                    direction = 'd';
                    Move();
                    break;
                case 2:
                    direction = 'l';
                    Move();
                    break;
                case 3:
                    direction = 'r';
                    Move();
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            X++;
        }
        break;
    case 'l':
        if(grid[X*N + Y - 1] != 0 && Y > 0)
        {
            while(direction == 'l')
            {
                tmp = rand() % 4;
                switch (tmp)
                {
                case 0:
                    direction = 'u';
                    Move();
                    break;
                case 1:
                    direction = 'd';
                    Move();
                    break;
                case 2:
                    direction = 'l';
                    Move();
                    break;
                case 3:
                    direction = 'r';
                    Move();
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            Y--;
        }

        break;

    case 'r':
        if(grid[X * N + Y + 1] != 0 && Y < 20)
        {
            while(direction == 'r')
            {
                tmp = rand() % 4;
                switch (tmp)
                {
                case 0:
                    direction = 'u';
                    Move();
                    break;
                case 1:
                    direction = 'd';
                    Move();
                    break;
                case 2:
                    direction = 'l';
                    Move();
                    break;
                case 3:
                    direction = 'r';
                    Move();
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            Y++;
        }
        break;
    default:
        break;
    }
}
void BotPlayer::Step()
{
    int N = 20;
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
