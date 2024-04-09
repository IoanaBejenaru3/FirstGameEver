#include "Game.h"

int main()
{
    //facem un random seed pentru alegerea tarilor care vor aparea in joc
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
