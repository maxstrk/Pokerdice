#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include <ctime>
#include <cstdlib>

struct Combination_pair// � ��� ����� ���� ���������� ������������� ����� ���������
{
    int prob;// ���� ���������
    int points1;//������ ����� �����, ��� ����� ��������, ���� ��������� � ������� �������
    int points2;//����� �����, ���� ��� �������� �������
    int kiker;//��������
    int kiker2;//��������
    int kiker3;//����� ���� -���� � �� ���������, �� ��������� ��������
};

int dice_roll(void); //����� ������ (������ 1-6)
void help(void);//�������� ������ ���������� ������

class Player
{
    int points[5];//����� �� ������� ������
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
