#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:
    int ID;
    char direction;
    player(int m,char d)
    {
        ID = m;
        direction = d;
    }
    ~player()
    {}
    Player();
};

#endif // PLAYER_H
