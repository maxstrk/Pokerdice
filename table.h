#ifndef TABLE_H_
#define TABLE_H_
#include "player.h"
class Table
{
    long bets[10];
public:
    Table();
    void betting(Player &p,int i,long a);
    void wintable(Player &p);
    void return_bet(Player &p,int i);
    long bet(int i) {return bets[i-1];}
    bool bets_done(int a,int b){if(bets[a-1]==bets[b-1]) return true; else return false;}
};

#endif // TABLE_H_
