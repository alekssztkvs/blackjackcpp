#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <locale>

int main()
{
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConcoleCP(CP_UTF8);
    #endif
    std::locale::global(std::locale(""));

    srand(time(NULL));

    Game game;
    game.start();
    game.results();

   return 0;
}