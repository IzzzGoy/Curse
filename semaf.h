#ifndef SEMAF_H
#define SEMAF_H

#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>

class Semaf
{
public:
    struct sembuf op;
    int semId;
    void Get(int Number);
    void Take(int Number);
    void Stop();
    Semaf();
    ~Semaf();
};

#endif // SEMAF_H
