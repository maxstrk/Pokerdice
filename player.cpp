#include "player.h"
Player::Player()
{
    for (int &i:points) i=0;
    combination.prob=0;
    combination.points1=0;
    combination.points2=0;
    combination.kiker=0;
    //points[0]=4;
    //points[1]=1;
    //points[2]=4;
    //points[3]=2;
    //points[4]=5;
};
void Player::roll(void)//����� ������
{
    for(int i=0; i < 5; i++) points[i]=dice_roll();
}
void Player::showhand(void) const
{
    for(int i=0; i < 5; i++) std::cout << points[i] << " ";
    std::cout << std::endl;
}
void Player::showcombination(void)const
{
    using namespace std;
    cout << combination.prob << " ";
    cout << combination.points1 << " ";
    cout << combination.points2 << " ";
    cout << combination.kiker << " ";
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
    std::cout << "Commands:\n'start'-start game\n'quit'- quit game\n'reroll'- to reroll\n";
}
void check_hand(Player & p)
{
    p.combination.prob=0;//���������
    p.combination.points1=0;
    p.combination.points2=0;
    p.combination.kiker=0;
    int arr[6]={0};
    for (int i=0; i < 5; i++)//�������� �-�� �������� ����� �����
        switch(p.points[i])
    {
        case 1: arr[0]++; break;
        case 2: arr[1]++; break;
        case 3: arr[2]++; break;
        case 4: arr[3]++; break;
        case 5: arr[4]++; break;
        case 6: arr[5]++; break;
    }
    bool find=false; // ������� ��� ��������, �� �������� ����� ���������
    for (int i=0; i <6; i++)
        if (arr[i]==5)
    {
        p.combination.prob=8;
        p.combination.points1=i+1;
        find=true;
    }
    if (!find)//���� �� �������� ��������� ���������
    for (int i=0; i <6; i++)
        if (arr[i]==4) // �������� �� ������ ���������
    {
        p.combination.prob=7;
        p.combination.points1=i+1;
        for (int i=0; i <6; i++)
        if (arr[i]==1) p.combination.kiker=i+1;
        find=true;
    }
    if (!find) // �������� �� ������� � ����� ������
    {
        int seq=0; // �������� �� ������� ���� �����
        for (int i=0; i <5; i++)
        if (arr[i]==1) seq++; else seq=0; // ������ ������ ���� ����� �� ������
        if (seq==4 && arr[5]==1) seq++; //���� � �� ���� ������� �� �������� �� ������
        if (seq==5) //���� ����� �'��� ���� ����� 1-5 ��� 2-6
        {
            if(arr[5]==0)  p.combination.prob=4; else p.combination.prob=5;
            find=true;
        }
    }
    if (!find) // ���� ���� ���������� ���������
    {
        int pairs=0;
        int three=0;
        for (int i=0; i <6; i++) //�������� �� ��������� ����� ��� ���
        {
            if (arr[i]==3)
            {
                three=1;
                p.combination.points1=i+1;
            }
            if (arr[i]==2)
            {
                pairs++;
                if (pairs==2) p.combination.points1=i+1;//��� �� ���� ��� �� 1-6 �� ����� ���� ������ �������������� � ������ �����
                                                        //� ��� ����� �� ���� �����
                if (pairs==1) p.combination.points2=i+1;
            }
        }
            if (three && pairs)// �������� �� ��� ����
            {
                p.combination.prob=6;
                find=true;
            }
            if (three && !pairs) // �������� �� �����
            {
                p.combination.prob=3;
                if (arr[5]==1) p.combination.kiker=6; //��������� ����� ���������� ����� � ���� �� �� ������� � ���������
                else if (arr[4]==1) p.combination.kiker=5;
                else if (arr[3]==1) p.combination.kiker=4;
                else if (arr[2]==1) p.combination.kiker=3;
                else if (arr[1]==1) p.combination.kiker=2;
                else if (arr[0]==1) p.combination.kiker=1;
                find=true;
            }

            if (pairs==2) // �������� �� �� ����
            {
                p.combination.prob=2;
                for (int i=0; i <6; i++)
                    if (arr[i]==1) p.combination.kiker=i+1;//��������� ����� ����� ��� �� ������� � �� ����
                find=true;
            }

            if (pairs==1 && !three) // �������� �� ���� ����
            {
                p.combination.prob=1;
                if (arr[5]==1) p.combination.kiker=6; //��������� ����� ���������� ����� � ���� �� �� ������� � ���������
                else if (arr[4]==1) p.combination.kiker=5;
                else if (arr[3]==1) p.combination.kiker=4;
                else if (arr[2]==1) p.combination.kiker=3;
                else if (arr[1]==1) p.combination.kiker=2;
                else if (arr[0]==1) p.combination.kiker=1;
                find=true;
            }
    }
    if (!find) //����� ���������� �����, ���� ���� ���������
    {
        if (arr[5]==1) p.combination.points1=6;
        else if (arr[4]==1) p.combination.points1=5;
        else if (arr[3]==1) p.combination.points1=4;
        else if (arr[2]==1) p.combination.points1=3;
        else if (arr[1]==1) p.combination.points1=2;
        else if (arr[0]==1) p.combination.points1=1;

    }
}
int compare_players(Player &p1, Player&p2)
{
    bool find=false;
    if(p1.combination.prob == p2.combination.prob) find=false;
    else
    {
        find=true;
        if(p1.combination.prob > p2.combination.prob) return 1; else return -1;
    }
    if (!find)
    if(p1.combination.points1 == p2.combination.points1) find=false;
    else
    {
        find=true;
        if(p1.combination.points1 > p2.combination.points1) return 1; else return -1;
    }
    if (!find)
    if(p1.combination.points2 == p2.combination.points2) find=false;
    else
    {
        find=true;
        if(p1.combination.points2 > p2.combination.points2) return 1; else return -1;
    }
    if (!find)
    if(p1.combination.kiker == p2.combination.kiker) find=false;
    else
    {
        find=true;
        if(p1.combination.kiker > p2.combination.kiker) return 1; else return -1;
    }
    if (!find) return 0;
}
int dice_roll(void)
{
    return rand()%6+1;
}
