#include "table.h"
Table::Table()
{
    for(long &b:bets)
        b=0;
    //bets[1]=20;
    //bets[8]=15;
};
void Table::betting(Player &p,int i,long a)
{
    p.getcash()-=a;
    bets[i-1]+=a;
}
void Table::wintable(Player &p)
{
    for (long b:bets)
        p.getcash()+=b;
    for(long &b:bets)
        b=0;
}
void Table::return_bet(Player &p,int i)
{
    p.getcash()+=bets[i-1];
    bets[i-1]=0;
}
