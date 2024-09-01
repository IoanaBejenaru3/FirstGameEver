#include "Game.h"
#define _CRT_SECURE_NO_WARNINGS 1


int main()
{
    //initializez un joc
    Game game;

    //GAME LOOP
    while (game.Running())
    {
        game.Update();
        game.Render();
    }

    return 0;
}