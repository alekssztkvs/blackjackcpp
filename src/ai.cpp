#include "AI.h"
#include "Quotes.h"

#include <iostream>
#include <cstdlib>
#ifdef WIN_32
#include <windows.h>
#define sleep(x) Sleep((x)*1000)
#else
#include <unistd.h>
#endif

AI::AI() { }
AI::AI(Deck *d) : Player(d) { }

const int BLACKJACK = 21;

void AI::set_params()
{
    ai_non_risk = 18;
    ai_dep = 2500;
    name = "CPU";

}
void AI::ai_hit()
{
    
    while (total_score < ai_non_risk)
    {
        std::cout << name <<  " draws:\n";
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
                continue;
            }
            else
            {
            std::cout<< name << " overdraw!\n";
            has_overdraw = 1;
            sleep(1);
            emote(evil_quotes);
            sleep(1);
            break;
            }
        }
        if (total_score == BLACKJACK)
        {
            std::cout<< name << "blackjack!";
            has_blackjack = 1;
            sleep(2);
            emote(win_quotes);
            sleep(2);
            break;
        }

    }   
}

void AI::emote(std::vector<std::string> q)
{
    int idx = rand()% q.size();
    std::cout << name <<": " << q.at(idx) << std::endl;
}

void AI::draw_at_start()
{
    std::cout << name <<" cards: \n";

    Card c = deck->topdeck();
    total_score += c.get_number();
    c.show_card_ascii();
    sleep(1);

    c = deck->topdeck();
    total_score+=c.get_number();
    c.show_card_ascii();
    sleep(1);

    std::cout << name << " score is: " << total_score << std::endl;
    sleep(1);

}

void AI::ai_bet()
{
    int bet = 1 + rand() % ai_dep;
    std::cout << name << " bets:$" << bet << std::endl; 
}

void AI::set_name(std::string s)
{
    name = s;
}

int AI::ai_winner(int dealer)
{
    if(has_blackjack)
    {
        std::cout << name << " wins!\n";
        sleep(1);
        return 1;
    }
    else if (has_overdraw)
    {
        std::cout << name << " lose!\n";
        sleep(1);
        return 0;
    }
    else if (get_total() > dealer)
    {
        std::cout << name << " wins!\n";
        sleep(1);
        return 1;
    } 
    else if(get_total() < dealer && dealer > BLACKJACK)
    {
        std::cout << name << " wins!\n";
        sleep(1);
        return 1;
    }
    else
    {
        std::cout << name << " lose\n";
        sleep(1);
        return 0;
    }
}
