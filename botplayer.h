#ifndef BOTPLAYER_H
#define BOTPLAYER_H

#include <ctime>
#include <thread>
#include <chrono>

class BotPlayer
{
private:

public:
    int* grid;
    int X,Y;
    double realX,realY;
    double speed;
    int score;
    char direction;

    BotPlayer(int* _grid);
    void Move();
    void Step();
};

#endif // BOTPLAYER_H
