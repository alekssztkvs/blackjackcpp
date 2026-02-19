
#include <iostream>
#include <vector>
#include "Deck.h"
#include <cstdlib>
#include <ctime>

const int BLACKJACK = 21;

Deck::Deck() {}

void Deck::createdeck()
{
    top = SIZE;
    int cards = 13;
    for (int i = 0 ; i < SIZE; i++)
    {
        int num = (i % cards) + 2;
        Suit suit = (Suit)(i / cards);
        deck.push_back(Card(num,suit));
        
    }
}
void Deck::shuffledeck()
{
    srand(time(NULL));

    for (int i = SIZE - 1; i > 0; i--) {
        int k = rand() % (i + 1);
        Card temp = deck.at(i);
        deck.at(i) = deck.at(k);
        deck.at(k) = temp;
    }
}

void Deck::showdeck()
{
    for (int i = 0; i < SIZE; i++)
        deck.at(i).show_card_ascii();
}
Card Deck::topdeck()
{
    return deck[--top];

}

int Deck::get_top_num()
{
    return top;
}

void Deck::changetop()
{
    top = SIZE;
}
