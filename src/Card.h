#ifndef CARD_H
#define CARD_H

enum Suit {clubs, hearts, diamonds, spades};
const int jack  = 11;
const int queen = 12;
const int king  = 13;
const int ace   = 14;


class Card
{
    private:
        int number;
        Suit suit;
        int top;
    public: 
        Card();
        Card(int n, Suit s);
        void show_card_ascii();
        void symbol(int);
        int get_number();
        int cardnum();
};

#endif