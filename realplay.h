#ifndef REALPLAY_H
#define REALPLAY_H

#include <QTimer>
#include <ctime>
#include <thread>
#include <chrono>

class RealPlay
{
private:


//void Wait();

public:
    char direction;
    int X;
    int Y;
    double realX;
    double realY;
    int sleepTime;
    double speed;
    int score;
    int socket;

    RealPlay(int* grid,int sock);
    //void SetDirection(char s);

    void Move (int *grid);

};

#endif // REALPLAY_H
