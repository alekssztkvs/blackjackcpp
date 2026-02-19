#ifndef DEALER_H
#define DEALER_H
#include "Player.h"
class Dealer : public Player
{
    private:
        int non_risk;
    public:

        Dealer();
        
        Dealer(Deck* );
        void draw(int );
        void first_card();
};

#endif
