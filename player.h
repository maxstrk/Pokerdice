#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include <ctime>
#include <cstdlib>

struct Combination_pair// з цих чисел буде складатися представлення кожної комбінації
{
    int prob;// сила комбінації
    int points1;//означає перше число, яке треба порівняти, якщо комбінації у гравців однакові
    int points2;//друге число, якщо два попередні однакові
    int kiker;//наступне
    int kiker2;//наступне
    int kiker3;//третій кікер -якщо і він однаковий, то комбінації ідентичні
};

int dice_roll(void); //кидок кубика (рендом 1-6)
void help(void);//виводить список консольних команд

class Player
{
    int points[5];//цифри на кожному кубику
    Combination_pair combination;
    long cash;
public:
    Player();
    long& getcash()
    {
        return cash;
    }
    void showcash()
    {
        std::cout << cash << std::endl;
    }
    void roll(void);
    void reroll(int a,int b=0,int c=0,int d=0,int e=0);
    void showhand(void) const;
    void showcombination(void)const;
    void tell_combination(void)const;
    ~Player() {};
    friend void check_hand(Player & p);
    friend int compare_players(Player &p1, Player&p2);
};


#endif // PLAYER_H_

/*class maxstring fixed, added reroll func, added table class, test version is playable
*/
