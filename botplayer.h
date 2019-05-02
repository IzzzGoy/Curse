#ifndef BOTPLAYER_H
#define BOTPLAYER_H

#include <ctime>
#include <thread>
#include <chrono>
#include <cmath>


class BotPlayer
{
private:
    void ChangeDir();
    char posDir[4] = {'u','d','l','r'};
    int N =20;
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
    void ClearSteps();
};

#endif // BOTPLAYER_H
