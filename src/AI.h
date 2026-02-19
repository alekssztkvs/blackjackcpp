#ifndef AI_H
#define AI_H
#include <iostream>
#include <vector>

#include "Game.h"

/*
    enum AI_Difficulty{EASY = 1, MEDIUEM, HARD,};
    optional
*/
class AI : public Player
{
    private:

        std::string name;
        int ai_non_risk;
        int ai_dep;
        
    public:

        AI();
        AI(Deck *);
        void set_name(std::string s);
        void draw_at_start();
        void ai_bet();
        void set_params();
        void ai_hit();
        void emote(std::vector<std::string>);
        int ai_winner(int);
};


#endif
