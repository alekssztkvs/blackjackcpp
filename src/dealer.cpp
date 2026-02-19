
#include "Dealer.h"
#include <iostream>
#ifdef WIN_32
#include <windows.h>
#define sleep(x) Sleep((x)*1000)
#else
#include <unistd.h>
#endif

const int BLACKJACK = 21;
Dealer::Dealer() {}
Dealer::Dealer(Deck* d): Player(d) {}


void Dealer::first_card()
{
    std::cout<< "Dealer has:\n";
    Card c = deck->topdeck();
    if (c.cardnum() == ace)
        num_aces++;
    total_score += c.get_number();
    c.show_card_ascii();
    sleep(1);
    std::cout<<"Dealer score: "<< total_score << std::endl;
    sleep(2);
}

void Dealer::draw(int game_value)
{
    non_risk = game_value;
    while (total_score < non_risk)
    {
        std::cout <<"Dealer draws:\n";
        Card c = deck->topdeck();
        if (c.cardnum() == ace)
            num_aces++;
        total_score += c.get_number();
        c.show_card_ascii();
        sleep(2);
        if (total_score > BLACKJACK)
        {
            if (num_aces>0)
            {
                int get_back = 10;
                total_score -= get_back;
                num_aces--;
            }
            else
            {
            std::cout<<("Dealer overdraw!\n");
            has_overdraw = 1;
            break;
            }
        }
        if (total_score == BLACKJACK)
        {
            std::cout<<("Dealer blackjack!");
            has_blackjack = 1;
            break;
        }

    }
}
