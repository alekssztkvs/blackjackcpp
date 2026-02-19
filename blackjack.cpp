#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"


int main()
{
    srand(time(NULL));
   Game game;
   game.start();

   return 0;
}