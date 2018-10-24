#include <iostream>
#include "maxstring.h"
#include "table.h"

using namespace std;

int main()
{
    srand(time(0));
    Player first;
    Player second;
    String command=" ";
    int numb_to_reroll;
    int to_reroll[5]={0};
    bool rerolled=false;
    Table table;
    cout << "Let`s start the game! " << endl;
    cout << "Your money: ";
    first.showcash();
    cout << "Herald`s money: ";
    second.showcash();
    while (command!="quit")
    {
        command.get();
        if (command=="help") help();
        else if (command=="play")
        {
            cout << "     You roll: ";
            first.roll();
            check_hand(first);
            first.showhand();
            cout << "Opponent roll: ";
            second.roll();
            check_hand(second);
            second.showhand();
            cout << "Herald bets 10.\n";
            table.betting (second,2,10);
            cout << "Your bet: 0, Herald bet: " << table.bet(2) << endl;
            while(command!="quit")
            {
                command.get();
                if (command=="ihave") first.tell_combination();
                if (command=="hehas") second.tell_combination();
                if (command=="call")
                {
                    table.betting(first,1,10);
                    cout << "Your bet: "<< table.bet(1) <<", Herald bet: " << table.bet(2) << endl;
                }
                if (command=="reroll" && !table.bets_done(1,2)) cout << "You must deal with Herald first.\n";
                if (command=="reroll" && table.bets_done(1,2) && rerolled) cout << "You rerolled your dice already.\n";
                if (command=="reroll" && table.bets_done(1,2) && !rerolled)
                {
                    cin >> numb_to_reroll;
                    if(numb_to_reroll==5) first.reroll(1,2,3,4,5);
                    else
                    {
                        for (int i=0;i <numb_to_reroll; i++) cin >> to_reroll[i];
                        for (int a:to_reroll) cout <<a << " ";
                        first.reroll(to_reroll[0],to_reroll[1],to_reroll[2],to_reroll[3],to_reroll[4]);
                    }
                    for (int &t:to_reroll) t=0;
                    cout << "You rerolled. Now you have: ";
                    check_hand(first);
                    first.showhand();
                    rerolled=true;
                }
                if (command=="open" && !table.bets_done(1,2)) cout << "You must deal with Herald first.\n";
                if (command=="open" && table.bets_done(1,2))
                {

                }
            }
        }
    }
    return 0;
}
