#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include <ctime>
#include <cstdlib>

int dice_roll(void);

class Player
{
    int dnumber;


public:
    int points[5];
    Player() : dnumber(5)
    {
    for (int &i:points) i=0;
    };
    void lose(void)
    {
        dnumber--;
    }
    void roll(void)
    {
        for(int &i: points) i=dice_roll();
        std::cout << "You rolled." << std::endl;
    }
    void showhand(void) const
    {
        for(int i: points) std::cout << i << " ";
        std::cout << std::endl;
    }
    ~Player(){};
};

int dice_roll(void)
{
    return rand()%6+1;
}

#endif // PLAYER_H_
