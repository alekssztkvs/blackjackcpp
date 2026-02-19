#include "Player.h"
#include "Safe_input.h"
#include <iostream>
#include <iomanip>
#ifdef WIN_32
#include <windows.h>
#define sleep(x) Sleep((x)*1000)
#else

#include <unistd.h>
#endif
const int BLACKJACK = 21;

Player::Player() : total_score(0), has_blackjack(0), has_overdraw(0), num_aces(0), deck() {}
Player::Player(Deck* d) : deck(d) {}

int Player::hit()
{

char ans = 'a';
    while (total_score <= BLACKJACK)
    {
        ans = input_yes_no("Draw another card? (y/n) : ");
        if (ans == 'n')
            return 1;

        sleep(1);
        Card c = deck->topdeck();
        if (c.cardnum() == ace)
            num_aces++;
        total_score += c.get_number();
        c.show_card_ascii();
        sleep(2);
        std::cout << "Your score now: " << total_score << std::endl;
        sleep(1);

        if (total_score > BLACKJACK)
        {
            if (num_aces > 0)
            {
                int get_back = 10;
                total_score -= get_back;
                num_aces--;
                std::cout << "Overdraw with Ace, score now: " << total_score << std::endl;
            }
            else
            {
            printf("Overdraw!\n");
            has_overdraw = true;
            }
            return 1;
            
        }
        if (total_score == BLACKJACK)
        {
            printf("Blackjack!\n");
            has_blackjack = true;
            return 1;
        }
    }
    return 0;
}

void Player::reset()
{
    total_score = 0;
    has_blackjack = 0;
    has_overdraw = 0;
    num_aces = 0;
}

int Player::dep()
{
    int dep_max = 5000;
    int max_bet = deposit >dep_max ? dep_max : deposit;
    std::cout << "Money left:$" << deposit << std::endl;
    bet = input_int("Enter your bet:$", 1, max_bet);
    deposit -= bet;
    return bet;
    
}

bool Player::have_money()
{
    if (deposit <= 0)
    {
        std::cout << "No money left!\n";
        return false;
    }
    else
        return true;
}

void Player::draw()
{
    std::cout << "Your cards:\n";

    Card c = deck->topdeck();
    total_score += c.get_number();
    c.show_card_ascii();
    sleep(1);

    c = deck->topdeck();
    total_score+=c.get_number();
    c.show_card_ascii();
    sleep(1);

    std::cout << "Your score is:" << total_score << std::endl;
    sleep(1);

}

void Player::get_deck(Deck* d)
{
    deck = d;
}

bool Player::bj()
{
    if (total_score == BLACKJACK)
        {
            has_blackjack = true;
            win_count++;
        }
    return has_blackjack;
}

void Player::payout(float ratio)
{
    float win = bet * ratio;
    deposit += (int)win;
    total_win += (int)win;
    std::cout << "+$" << std::fixed << std::setprecision(2)
    << win << std::endl;
}

bool Player::isoverdraw()
{
    return has_overdraw;
}

int Player::get_total()
{
    return total_score;
}

bool Player::has_ace()
{
    return (num_aces>0) ? true : false;
}

bool Player::isblackjack()
{
    return has_blackjack;
}

void Player::return_bet(int dep)
{
    deposit += dep;
}

void Player::plus_win()
{
    win_count++;
}

void Player::set_dep(int money)
{
    deposit = money;
}