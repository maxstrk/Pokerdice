#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include <ctime>
#include <cstdlib>

struct Combination_pair
{
    int prob;
    int points1;
    int points2;
    int kiker;
};

int dice_roll(void);
void help(void);

class Player
{
    int points[5];
    Combination_pair combination;
public:
    Player()
    {
        for (int &i:points) i=0;
        combination.prob=0;
        combination.points1=0;
        combination.points2=0;
        combination.kiker=0;

    };
    void roll(void)
    {
        for(int i=0; i < 5; i++) points[i]=dice_roll();
    }
    void showhand(void) const
    {
        for(int i=0; i < 5; i++) std::cout << points[i] << " ";
        std::cout << std::endl;
    }
    void showcombination(void)
    {
        using namespace std;
        cout << combination.prob << " ";
        cout << combination.points1 << " ";
        cout << combination.points2 << " ";
        cout << combination.kiker << " ";
    }
    void tell_combination(void)
    {
        using namespace std;
        switch(combination.prob)
        {
            case 0: cout << "Bust (High card, no pair, no straight)" << endl; break;
            case 1: cout << "One pair" << endl; break;
            case 2: cout << "Two pair" << endl; break;
            case 3: cout << "Three of a kind" << endl; break;
            case 4: cout << "Small straight" << endl; break;
            case 5: cout << "Great straight" << endl; break;
            case 6: cout << "Full house" << endl; break;
            case 7: cout << "Four of a kind" << endl; break;
            case 8: cout << "Five of a kind" << endl; break;
        }
    }
    ~Player(){};
    friend void check_hand(Player & p);

};

void help(void)
{
    std::cout << "Commands:\n'start'-start game\n'quit'- quit game\n'reroll'- to reroll\n";
}
void check_hand(Player & p)
{
    p.combination.prob=0;
    p.combination.points1=0;
    p.combination.points2=0;
    p.combination.kiker=0;
    int arr[6]={0};
    for (int i=0; i < 5; i++)
        switch(p.points[i])
    {
        case 1: arr[0]++; break;
        case 2: arr[1]++; break;
        case 3: arr[2]++; break;
        case 4: arr[3]++; break;
        case 5: arr[4]++; break;
        case 6: arr[5]++; break;
    }
    bool find=false;
    for (int i=0; i <6; i++)
        if (arr[i]==5)
    {
        p.combination.prob=8;
        p.combination.points1=i+1;
        find=true;
    }
    if (!find)
    for (int i=0; i <6; i++)
        if (arr[i]==4)
    {
        p.combination.prob=7;
        p.combination.points1=i+1;
        for (int i=0; i <6; i++)
        if (arr[i]==1) p.combination.kiker=i+1;
        find=true;
    }
    if (!find)
    {
        int seq=0;
        for (int i=0; i <5; i++)
        if (arr[i]==1) seq++; else seq=0;
        if (seq==4 && arr[5]==1) seq++;
        if (seq==5)
        {
            if(arr[5]==0)  p.combination.prob=4; else p.combination.prob=5;
            find=true;
        }
    }
    if (!find)
    {
        int pairs=0;
        int three=0;
        for (int i=0; i <6; i++)
        {
            if (arr[i]==3)
            {
                three=1;
                p.combination.points1=i+1;
            }
            if (arr[i]==2)
            {
                pairs++;
                if (pairs==2) p.combination.points1=i+1;
                if (pairs==1) p.combination.points2=i+1;
            }
        }
            if (three && pairs)
            {
                p.combination.prob=6;
                find=true;
            }
            if (three && !pairs)
            {
                p.combination.prob=3;
                if (arr[5]==1) p.combination.kiker=6;
                else if (arr[4]==1) p.combination.kiker=5;
                else if (arr[3]==1) p.combination.kiker=4;
                else if (arr[2]==1) p.combination.kiker=3;
                else if (arr[1]==1) p.combination.kiker=2;
                else if (arr[0]==1) p.combination.kiker=1;
                find=true;
            }

            if (pairs==2)
            {
                p.combination.prob=2;
                for (int i=0; i <6; i++)
                    if (arr[i]==1) p.combination.kiker=i+1;
                find=true;
            }

            if (pairs==1 && !three)
            {
                p.combination.prob=1;
                if (arr[5]==1) p.combination.kiker=6;
                else if (arr[4]==1) p.combination.kiker=5;
                else if (arr[3]==1) p.combination.kiker=4;
                else if (arr[2]==1) p.combination.kiker=3;
                else if (arr[1]==1) p.combination.kiker=2;
                else if (arr[0]==1) p.combination.kiker=1;
                find=true;
            }
    }
    if (!find)
    {
        if (arr[5]==1) p.combination.points1=6;
        else if (arr[4]==1) p.combination.points1=5;
        else if (arr[3]==1) p.combination.points1=4;
        else if (arr[2]==1) p.combination.points1=3;
        else if (arr[1]==1) p.combination.points1=2;
        else if (arr[0]==1) p.combination.points1=1;

    }
}
int dice_roll(void)
{
    return rand()%6+1;
}

#endif // PLAYER_H_
