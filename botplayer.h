#ifndef BOTPLAYER_H
#define BOTPLAYER_H

#include <ctime>
#include <thread>
#include <chrono>
#include <cmath>
#include "semaf.h"

class BotPlayer
{
private:
    void ChangeDir();
    char posDir[4] = {'u','d','l','r'};
    int N =20;
public:
    Semaf* sem;
    int* grid;
    int X,Y;
    double realX,realY;
    double speed;
    int score;
    char direction;

    BotPlayer(int* _grid,Semaf* sem);
    void Move();
    void Step();
    void ClearSteps();
};

#endif // BOTPLAYER_H
