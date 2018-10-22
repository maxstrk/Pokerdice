#include <iostream>
#include "maxstring.h"
#include "player.h"

using namespace std;




int main()
{
    srand(time(0));
    Player first;
    Player second;
    first.roll();
    second.roll();
    first.showhand();
    second.showhand();

    return 0;
}
