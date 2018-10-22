#include <iostream>
#include "maxstring.h"
#include <ctime>
#include <cstdlib>
using namespace std;


int dice_roll(void);

int main()
{
    srand(time(0));
    String str="Hello world!";
    str.show();
    return 0;
}
int dice_roll(void)
{
    return rand()%6+1;
}
