#ifndef TABLE_H_
#define TABLE_H_
#include "player.h"
class Table
{
    long bets[10];
public:
    Table()
    {
        for(long &b:bets)b=0;
        //bets[1]=20;
        //bets[8]=15;
    };
    void betting(Player &p,int i,long a)
    {
        p.getcash()-=a;
        bets[i-1]+=a;
    }
    void wintable(Player &p)
    {
        for (long b:bets) p.getcash()+=b;
        for(long &b:bets)b=0;
    }
    void return_bet(Player &p,int i)
    {
        p.getcash()+=bets[i-1];
        bets[i-1]=0;
    }
    long bet(int i) {return bets[i-1];}
    bool bets_done(int a,int b){if(bets[a-1]==bets[b-1]) return true; else return false;}
};

#endif // TABLE_H_
