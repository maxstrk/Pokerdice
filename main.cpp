#include <iostream>
#include "maxstring.h"
#include "player.h"

using namespace std;




int main()
{
    srand(time(0));
    Player first;
    Player second;
    String command=" ";
    while (command!="quit")
    {
        command.get();
        if (command=="help") help();
        else if (command=="start")
        {
            cout << "     You roll: ";
            //first.roll();
            check_hand(first);
            first.showhand();
            first.showcombination();
            first.tell_combination();
            cout << "Opponent roll: ";
            second.roll();
            check_hand(second);
            second.showhand();
            second.tell_combination();
            while(command!="quit")
            {
                command.get();
                if (command=="reroll")
                {
                    second.roll();
                    check_hand(second);
                    second.showhand();
                    second.showcombination();
                    second.tell_combination();
                    int a=compare_players(first,second);
                    if (a==1) cout<< " You win!\n";
                    else if (a==-1) cout << " You lose!\n";
                    else if (a==0) cout << " Draw!\n";
                }
            }
        }
    }
    return 0;
}
