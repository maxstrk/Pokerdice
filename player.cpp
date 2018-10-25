#include "player.h"
Player::Player()
{
    for (int &i:points) i=0;
    combination.prob=0;
    combination.points1=0;
    combination.points2=0;
    combination.kiker=0;
    combination.kiker2=0;
    combination.kiker3=0;
    cash=100;
    points[0]=6;
    points[1]=4;
    points[2]=3;
    points[3]=5;
    points[4]=1;
};
void Player::roll(void)//кидок кубиків
{
    for(int i=0; i < 5; i++) points[i]=dice_roll();
}
void Player::reroll(int a,int b,int c,int d,int e)
{
    for(int i=0; i < 5; i++)
    {
        if(a==i+1) points[i]=dice_roll();
        if(b==i+1) points[i]=dice_roll();
        if(c==i+1) points[i]=dice_roll();
        if(d==i+1) points[i]=dice_roll();
        if(e==i+1) points[i]=dice_roll();
    }
}
void Player::showhand(void) const
{
    for(int i=0; i < 5; i++) std::cout << points[i] << "  ";
    std::cout << std::endl;
}
void Player::showcombination(void)const
{
    using namespace std;
    cout << combination.prob << " ";
    cout << combination.points1 << " ";
    cout << combination.points2 << " ";
    cout << combination.kiker << " ";
    cout << combination.kiker2 << " ";
    cout << combination.kiker3 << " ";
}
void Player::tell_combination(void)const
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
void help(void)
{
    std::cout << "Commands:\n'bet n'- bet some money\n'quit'- quit game\n'check,call,fold or raise'- to check,call,fold or raise\n";
    std::cout << "to reroll dice you must first use command 'reroll',\n";
    std::cout<< "then put number, how many dices you want to reroll,\n and then put numbers of positions of this dices\n";
    std::cout << "For example: 'reroll 3 2 5 4' means reroll second fifth and fourth dice.\n";
}
void check_hand(Player & p)
{
    p.combination.prob=0;//занулення
    p.combination.points1=0;
    p.combination.points2=0;
    p.combination.kiker=0;
    p.combination.kiker2=0;
    p.combination.kiker3=0;
    int arr[6]={0};
    for (int i=0; i < 5; i++)//перевірка к-сті випадань кожної цифри
        switch(p.points[i])
    {
        case 1: arr[0]++; break;
        case 2: arr[1]++; break;
        case 3: arr[2]++; break;
        case 4: arr[3]++; break;
        case 5: arr[4]++; break;
        case 6: arr[5]++; break;
    }
    bool find=false; // потрібна для перевірки, чи знайдена якась комбінація
    for (int i=0; i <6; i++)//Перевірка нав п'ятірку однакових
        if (arr[i]==5)
    {
        p.combination.prob=8;
        p.combination.points1=i+1;
        find=true;
    }
    if (!find)//якщо не знайдена попередня комбінація
    for (int i=0; i <6; i++)
        if (arr[i]==4) // перевірка на чотири однакових
    {
        p.combination.prob=7;
        p.combination.points1=i+1;
        for (int i=0; i <6; i++)
        if (arr[i]==1) p.combination.kiker=i+1;
        find=true;
    }
    if (!find) // перевірки на великий і малий стрейт
    {
        int seq=0; // перевірка на кількість очків підряд
        for (int i=0; i <5; i++)
        if (arr[i]==1) seq++; else seq=0; // скільки випало очків підряд до шістки
        if (seq==4 && arr[5]==1) seq++; //якщо є усі окрім одиниці то перевірка на шістку
        if (seq==5) //якщо стоїть п'ять очок підряд 1-5 або 2-6
        {
            if(arr[5]==0)  p.combination.prob=4; else p.combination.prob=5;
            find=true;
        }
    }
    if (!find) // якщо нема попередніх комбінацій
    {
        int pairs=0;
        int three=0;
        for (int i=0; i <6; i++) //перевірка на наявність трійки або пар
        {
            if (arr[i]==3)
            {
                three=1;
                p.combination.points1=i+1;
            }
            if (arr[i]==2)
            {
                pairs++;
                if (pairs==2) p.combination.points1=i+1;//так як цикл йде від 1-6 то друга пара завжди складатиметься з більших чисел
                                                        //і при цьому не буде трійки
                if (pairs==1) p.combination.points2=i+1;
            }
        }
            if (three && pairs)// перевірка на фул хаус
            {
                p.combination.prob=6;
                find=true;
            }
            if (three && !pairs) // перевірка на трійку
            {
                p.combination.prob=3;
                int as=0;//потрібно для збереження інформації про значення двох кікерів
                int bs=0;
                for (int i=5; i >= 0; i--)//реверс цикл
                {
                    if (arr[i]==1 && as==0) as=i+1;
                    if (arr[i]==1 && bs==0 && as!=i+1) bs=i+1;
                }
                p.combination.kiker=as;
                p.combination.kiker2=bs;
                find=true;
            }

            if (pairs==2) // перевірка на дві пари
            {
                p.combination.prob=2;
                for (int i=0; i <6; i++)
                    if (arr[i]==1) p.combination.kiker=i+1;//присвоєння кікеру числа яке не входить у дві пари
                find=true;
            }

            if (pairs==1 && !three) // перевірка на одну пару
            {
                p.combination.prob=1;
                int as=0;//потрібно для збереження інформації про значення трьох кікерів
                int bs=0;
                int cs=0;
                for (int i=5; i >= 0; i--)//реверс цикл
                {
                    if (arr[i]==1 && as==0) as=i+1;
                    if (arr[i]==1 && bs==0 && as!=i+1) bs=i+1;
                    if (arr[i]==1 && cs==0 && as!=i+1 && bs!=i+1) cs=i+1;
                }
                p.combination.kiker=as;
                p.combination.kiker2=bs;
                p.combination.kiker3=cs;
                find=true;
            }
    }
    if (!find) //запис цифри якої нема
    {
        int as=0;
        for (int i=0; i < 6; i++) if(!arr[i]) as=i+1;
        p.combination.prob=0;
        p.combination.points1=6-as;
    }
}
int compare_players(Player &p1, Player&p2)
{
    bool find=false;
    if(!find)
    {
        if(p1.combination.prob == p2.combination.prob) find=false;
    else
    {
        find=true;
        if(p1.combination.prob > p2.combination.prob) return 1; else return -1;
    }
    }
    if (!find)
    {
        if(p1.combination.points1 == p2.combination.points1) find=false;
    else
    {
        find=true;
        if(p1.combination.points1 > p2.combination.points1) return 1; else return -1;
    }
    }
    if (!find)
    {
        if(p1.combination.points2 == p2.combination.points2) find=false;
    else
    {
        find=true;
        if(p1.combination.points2 > p2.combination.points2) return 1; else return -1;
    }
    }
    if (!find)
    {
        if(p1.combination.kiker == p2.combination.kiker) find=false;
    else
    {
        find=true;
        if(p1.combination.kiker > p2.combination.kiker) return 1; else return -1;
    }
    }
    if (!find)
    {
        if(p1.combination.kiker2 == p2.combination.kiker2) find=false;
    else
    {
        find=true;
        if(p1.combination.kiker2 > p2.combination.kiker2) return 1; else return -1;
    }
    }
    if (!find)
    {
        if(p1.combination.kiker3 == p2.combination.kiker3) find=false;
    else
    {
        find=true;
        if(p1.combination.kiker3 > p2.combination.kiker3) return 1; else return -1;
    }
    }
    if (!find) return 0;
}
int dice_roll(void)
{
    return rand()%6+1;
}
