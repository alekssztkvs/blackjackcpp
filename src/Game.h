#ifndef GAME_H
#define GAME_H
#include "Dealer.h"

class AI;

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
        AI* testAI;
        bool need_next_round;
        bool with_ai;

    public:
        Game();
        ~Game();
        void set_params();
        void play_round();
        void start();
        int winner();
        void results();
        void determine_winner();
        void play_until_finish();

        void ai_play_round();

        

};


#endif