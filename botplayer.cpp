#include "botplayer.h"

BotPlayer::BotPlayer(int* _grid)
{
    grid = _grid;
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
        if(grid[(X - 1)*N + Y] != 0)
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
        break;
    case 'd':
        if(grid[(X + 1) * N + Y] != 0)
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
        break;
    case 'l':
        if(grid[X*N + Y - 1] != 0)
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

        break;

    case 'r':
        if(grid[X * N + Y + 1] != 0)
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
