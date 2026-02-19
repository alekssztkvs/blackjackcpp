#ifndef PLAYER_H
#define PLAYER_H
#include "Deck.h"

class Player
{
    protected:
        int total_score;
        bool has_blackjack;
        bool has_overdraw;
        Deck* deck;
        int num_aces;
    private:
        int deposit;
        int bet;
        int win_count;
        int total_win;
    public:
        Player();
        Player(Deck*);
        int hit();
        void reset();
        int dep();
        void draw();
        void get_deck(Deck*);
        bool have_money();
        bool bj();
        void payout(float ratio);
        bool isoverdraw();
        int get_total();
        bool has_ace();
        bool isblackjack();
        void return_bet(int);
        void plus_win();
        void set_dep(int);

};

#endif
