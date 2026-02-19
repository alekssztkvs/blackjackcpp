#ifndef GAME_H
#define GAME_H
#include "Dealer.h"

enum Difficulty {EASY = 1, OPTIMAL, HARD};

class Game
{
    private:
        int total_rounds;
        int gp;
        Difficulty difficulty;
        float blackjack_ratio;
        float regular_ratio;
        int non_risk;
        int start_dep;
        Player player;
        Dealer dealer;
        Deck deck;
    public:
        Game();
        void params();
        void start();
        int winner();


};


#endif