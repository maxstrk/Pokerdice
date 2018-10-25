#include <iostream>
#include "maxstring.h"
#include "table.h"

using namespace std;

int main()
{
    srand(time(0));
    Player zoltan;
    Player herald;
    String command=" ";
    while(command!="quit")
    {
        int numb_to_reroll;
        int to_reroll[5]= {0};
        bool zoltan_rerolled=false;
        bool zoltan_herald=false;
        bool zoltan_raise=false;
        bool herald_raise=false;
        //bool herald_call=false;
        bool next_round=false;
        bool herald_lose=false;
        bool zoltan_lose=false;
        bool bets_done=false;
        Table table;
        cout << "Let`s start the game!\n\n";
        cout << "Zoltan: ";
        zoltan.showcash();
        cout << "Herald: ";
        herald.showcash();
        cout << "bets: "<< table.bet(1) << " " << table.bet(2) << endl << endl;
        cout << "Do your bet`s!\n";
        while (command!="quit" && !herald_lose && !bets_done)
        {
            next_round=true;
            if (!zoltan_herald)
            {
                cout << "> Zoltan: ";
            }
            if (zoltan_herald)
            {
                cout << "> Herald: ";
            }
            command.get();
            if (!zoltan_herald)
            {
                if (command=="help") help();
                if (command=="bet")
                {
                    long a=0;
                    cin >> a;
                    table.betting(zoltan,1,a);
                    cout << "bets: "<< table.bet(1) << " " << table.bet(2) << endl << endl;
                    zoltan_herald=true;
                    zoltan_raise=true;
                    next_round=false;
                }
                if (command=="call" && herald_raise)
                {
                    table.betting(zoltan,1,table.bet(2)-table.bet(1));
                    herald_raise=false;
                }

                if (command=="call" && !herald_raise)
                    cout << "Herald don`t raise now.\n";
            }
            if (zoltan_herald && next_round)
            {
                if (command=="call" && !zoltan_raise)
                    cout << "Zoltan don`t raise now.\n";
                if (command=="call" && zoltan_raise)
                {
                    table.betting(herald,2,table.bet(1)-table.bet(2));
                    cout << "bets: "<< table.bet(1) << " " << table.bet(2) << endl << endl;
                    zoltan_herald=false;
                    zoltan_raise=false;
                    bets_done=true;
                }
                if (command=="fold")
                {
                    herald_lose=true;
                    table.return_bet(zoltan,1);
                    cout << "Herald lose.\n\n\n\n";
                }
            }

        }
        if (command!="quit" && !herald_lose && !zoltan_lose)
        {
            bets_done=false;
            next_round=false;
            cout << "Zoltan roll: ";
            zoltan.roll();
            check_hand(zoltan);
            zoltan.showhand();
            cout << "Herald roll: ";
            herald.roll();
            check_hand(herald);
            herald.showhand();
            cout << "bets: "<< table.bet(1) << " " << table.bet(2) << endl << endl;
        }
        while (command!="quit" && !herald_lose && !bets_done && !zoltan_lose)
        {
            next_round=true;
            if (!zoltan_herald)
            {
                cout << "> Zoltan: ";
            }
            if (zoltan_herald)
            {
                cout << "> Herald: ";
            }
            command.get();
            if (!zoltan_herald)
            {
                if (command=="ihave")
                    zoltan.tell_combination();
                if (command=="hehas")
                    herald.tell_combination();
                if (command=="raise" && !herald_raise)
                {
                    long a=0;
                    cin >> a;
                    table.betting(zoltan,1,a);
                    cout << "bets: "<< table.bet(1) << " " << table.bet(2) << endl << endl;
                    zoltan_herald=true;
                    zoltan_raise=true;
                    next_round=false;
                }
                if (command=="call" && !herald_raise)
                    cout << "Herald don`t raise now.\n";
                if (command=="call" && herald_raise)
                {
                    table.betting(zoltan,1,table.bet(2)-table.bet(1));
                    cout << "bets: "<< table.bet(1) << " " << table.bet(2) << endl << endl;
                    herald_raise=false;
                    bets_done=true;
                }
                if (command=="check" && herald_raise)
                    cout << "You can`t check, because Herald raise!\n";
                if (command=="check" && !herald_raise)
                {
                    zoltan_herald=true;
                    next_round=false;
                }
                if (command=="fold")
                {
                    zoltan_lose=true;
                    cout << "Zoltan lose.\n\n\n\n";
                    table.wintable(herald);
                }
            }
            if (zoltan_herald && next_round)
            {
                if (command=="ihave")
                    herald.tell_combination();
                if (command=="hehas")
                    zoltan.tell_combination();
                if (command=="check" && !zoltan_raise)
                {
                    zoltan_herald=false;
                    bets_done=true;
                }
                if (command=="raise")
                {
                    long a=0;
                    cin >> a;
                    table.betting(herald,2,table.bet(1)-table.bet(2)+a);
                    cout << "bets: "<< table.bet(1) << " " << table.bet(2) << endl << endl;
                    zoltan_herald=false;
                    herald_raise=true;
                    //next_round=false;
                }
                if (command=="call" && zoltan_raise)
                {
                    table.betting(herald,2,table.bet(1)-table.bet(2));
                    cout << "bets: "<< table.bet(1) << " " << table.bet(2) << endl << endl;
                    zoltan_herald=false;
                    bets_done=true;
                }
                if (command=="call" && !zoltan_raise)
                    cout << "Zoltan don`t raise now.\n";
                if (command=="fold")
                {
                    herald_lose=true;
                    cout << "Herald lose.\n\n\n\n";
                    table.wintable(zoltan);
                }
            }
        }
        bets_done=false;
        next_round=false;
        if(command!="quit" && !herald_lose && !zoltan_lose) cout << "\nNow you can reroll some dice if you want.\n";
        while (command!="quit" && !herald_lose && !bets_done && !zoltan_lose)
        {
            next_round=true;
            if (!zoltan_herald)
            {
                cout << "> Zoltan: ";
            }
            if (zoltan_herald)
            {
                cout << "> Herald: ";
            }
            command.get();
            if (!zoltan_herald)
            {
                if (command=="ihave")
                    zoltan.tell_combination();
                if (command=="hehas")
                    herald.tell_combination();
                if (command=="no")
                {
                    next_round=false;
                    zoltan_herald=true;
                    zoltan_rerolled=true;
                }
                if (command=="reroll")
                {
                    cin >> numb_to_reroll;
                    if(numb_to_reroll==5)
                        zoltan.reroll(1,2,3,4,5);
                    else
                    {
                        for (int i=0; i <numb_to_reroll; i++)
                            cin >> to_reroll[i];
                        zoltan.reroll(to_reroll[0],to_reroll[1],to_reroll[2],to_reroll[3],to_reroll[4]);
                    }
                    for (int &t:to_reroll)
                        t=0;
                    cout << "Zoltan rerolled. Now he has: ";
                    check_hand(zoltan);
                    zoltan.showhand();
                    zoltan.tell_combination();
                    cout << endl;
                    zoltan_rerolled=true;
                    next_round=false;
                    zoltan_herald=true;
                }
            }
            if (zoltan_herald && next_round)
            {
                if (command=="ihave")
                    herald.tell_combination();
                if (command=="hehas")
                    zoltan.tell_combination();
                if (command=="no" && zoltan_rerolled)
                {
                    zoltan_herald=false;
                    bets_done=true;
                }
                if (command=="reroll")
                {
                    cin >> numb_to_reroll;
                    if(numb_to_reroll==5)
                        herald.reroll(1,2,3,4,5);
                    else
                    {
                        for (int i=0; i <numb_to_reroll; i++)
                            cin >> to_reroll[i];
                        herald.reroll(to_reroll[0],to_reroll[1],to_reroll[2],to_reroll[3],to_reroll[4]);
                    }
                    for (int &t:to_reroll)
                        t=0;
                    cout << "Herald rerolled. Now he has: ";
                    check_hand(herald);
                    herald.showhand();
                    herald.tell_combination();
                    cout << endl;
                    bets_done=true;
                    zoltan_herald=false;
                }

            }
        }
        int result=0;
        if(command!="quit" && !herald_lose && !zoltan_lose)
        {
            result=compare_players(zoltan,herald);
        if (result==1)
        {
            cout << "Zoltan wins!\n\n\n\n";
            table.wintable(zoltan);
        }
        if (result==-1)
        {
            cout << "Herald wins!\n\n\n\n";
            table.wintable(herald);
        }
        if (result==0)
        {
            cout << "Draw!\n\n\n\n";
            table.return_bet(zoltan,1);
            table.return_bet(herald,2);
        }
        }
    }
    return 0;
}
