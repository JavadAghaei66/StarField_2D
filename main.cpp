#include <iostream>
#include "StarField.h"
using namespace std;

int main()
{
    StarField sf;
    if (!sf.InitStarField())
    {
        cout << "Unexpected error!" << endl;
        return 1;
    }

    while (sf.IsRunning())
    {
        sf.Input();
        sf.MoveStars();
        sf.Render();
        sf.Delay();
    }

    sf.Quit();
    return 0;
}
