#ifndef REALPLAY_H
#define REALPLAY_H

#include <QTimer>
#include <ctime>
#include <thread>
#include <chrono>
#include <cmath>

#include "semaf.h"

class RealPlay
{
private:


//void Wait();

public:
    Semaf* sem;
    char direction;
    int X;
    int Y;
    double realX;
    double realY;
    double speed;
    int score;
    int socket;
    int* grid;

    void Step();

    RealPlay(int *grid, int sock,Semaf* sem);
    //void SetDirection(char s);

    void Move ();
    void ClearSteps();

};

#endif // REALPLAY_H
