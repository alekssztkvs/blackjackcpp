#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include <vector>



class Deck
{
    private:
        static const int SIZE = 52;
        std::vector<Card> deck;
        int top;
    public:
        Deck();
        void createdeck();
        void shuffledeck();
        void showdeck();
        Card topdeck();
        int get_top_num();
        void changetop();
};

#endif
