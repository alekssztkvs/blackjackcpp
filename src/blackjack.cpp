#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"


int main()
{
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
    srand(time(NULL));
   Game game;
   
    game.start();
    game.results();

   return 0;
}