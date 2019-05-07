#include "semaf.h"

Semaf::Semaf()
{
    semId = semget(IPC_PRIVATE, 400, 0600|IPC_CREAT);

}
void Semaf::Get(int Number)
{
    op.sem_op = 1;
    op.sem_flg = 0;
    op.sem_num = Number;
}

void Semaf::Take(int Number)
{
        op.sem_op = -1;
        op.sem_flg = 0;
        op.sem_num = Number;
}

Semaf::~Semaf()
{
    semctl(semId, IPC_RMID, 0);
}

void Semaf::Stop()
{
    semop(semId, &op, 0);
}
