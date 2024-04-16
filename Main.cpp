#include "Game.h"
#define _CRT_SECURE_NO_WARNINGS 1

/*void ReadCountries()
{
    std::string name;
    std::cin >> countries_number;
    for (int i = 0; i < countries_number; i++)
    {
        std::cin >> name;
        countries.push_back(name);
    }
}*/

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