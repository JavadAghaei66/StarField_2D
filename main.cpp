#include <iostream>
#include "GameEngine.h"
using namespace std;

int main()
{
    GameEngine game;
    if (!game.InitGameEngine())
    {
        cout << "Unexpected error!" << endl;
        return 1;
    }

    while (game.IsRunning())
    {
        game.Input();
        game.MoveStars();
        game.Render();
        game.Delay();
    }

    game.Quit();
    return 0;
}
