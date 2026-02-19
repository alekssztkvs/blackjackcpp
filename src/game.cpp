#include "Game.h"
#include "Safe_input.h"
#include <iostream>
#ifdef WIN_32
#include <windows.h>
#define sleep(x) Sleep((x)*1000)
#else
#include <unistd.h>
#endif

Game::Game() : player(), dealer(), deck() {deck.createdeck();}

void Game::set_params()
{

    difficulty = (enum Difficulty)input_int("Enter difficulty (1 easy, 2 optimal, 3 hard): ", 1, 3);
    if (difficulty == EASY)
    {
        non_risk = 17;
        blackjack_ratio = 3;
        regular_ratio = 2;
        start_dep = 3000 + rand()%1000;
    }
    else if (difficulty == OPTIMAL)
    {
        non_risk = 17;
        blackjack_ratio = 3;
        regular_ratio = 2;
        start_dep = 2500 + rand()%500;
    }
    else if (difficulty == HARD)
    {
        non_risk = 17;
        blackjack_ratio = 2;
        regular_ratio = 1.5;
        start_dep = 250 + rand()%100;
    }
    int max_rounds = 10;
    total_rounds = input_int("How many rounds?(1-10) :", 1, max_rounds);

    sleep(1);
    deck.shuffledeck();

    player.get_deck(&deck);
    dealer.get_deck(&deck);
    player.set_dep(start_dep);
    need_next_round = true;
    gp = 0;
}
void Game::start()
{

    set_params();
    sleep(1);
    play_until_finish();
    }

void Game::play_until_finish()
{
    play_round();
    determine_winner();
    while (need_next_round)
        play_until_finish();
}

void Game::play_round()
{

        if (gp == total_rounds )
        {
            need_next_round = false;
            return;
        }    
        int min_cards = 10;

        if (deck.get_top_num() < min_cards)
        {
            deck.shuffledeck();
            deck.changetop();
        }
        if (!player.have_money())
        {
            need_next_round = false;
            return;
        }
        int dep = player.dep();
        sleep(1);
        player.draw();
        dealer.first_card();
    
    if (player.bj())
    {
        std::cout << "Blackjack!You win\n";
        player.payout(blackjack_ratio);
    }
    else
    {
        player.hit();
        sleep(2);
        if(!player.isoverdraw())
        {
            dealer.draw(non_risk);
            sleep(2);
        }
        if (dealer.get_total() == 20 && dealer.has_ace())
            player.hit();
    }
    
    
}
void Game:: determine_winner()
{
    if(need_next_round == false)
        return;

    int dep = player.get_dep();
    int who_won = winner();
        if (who_won == 1)
        {
            player.plus_win();
            if (player.isblackjack())
                player.payout(blackjack_ratio);
            else
                player.payout(regular_ratio);
        }
        else if (who_won == -1)
            player.return_bet(dep);

    sleep(2);
    gp++;
    std::cout << "\n\nRound " << gp << " is finished...\n" ;
    sleep(1);
    dealer.reset();
    player.reset();
}

int Game::winner()
{
    std::cout<<"\n\n\n";
    if (player.isblackjack())
    {
        std::cout<<"Player wins: Blackjack!\n";
        return 1;
    }
    else if (player.isoverdraw())
    {
        std::cout<<"Player loses due to overdraw!\n";
        return 0;
    }
    else if (dealer.isoverdraw())
    {
        std::cout << "Player wins: dealer overdraw!\n";
        return 1;
    }
    else if (dealer.isblackjack())
    {
        std::cout << "Dealer wins: Blackjack!\n";
        return 0;
    }
    else if (player.get_total() > dealer.get_total())
    {
        std::cout << "Player wins with total:" << player.get_total()
        <<", Dealer has: " << dealer.get_total() << std::endl;
        return 1;
    }
    else if (player.get_total() == dealer.get_total())
    {
        std::cout << "Draw! Dealer: " << dealer.get_total() << " total, player: "
        << player.get_total() << " total\n";
        return -1;
    }   
    else
    {
        std::cout << "Dealer wins with: " << dealer.get_total() << " total against players: "
        << player.get_total() << " total\n";
        return 0;
    }
}


void Game :: results()
{
    std::cout << "Game finished:\n";
    std::cout << "Starting deposit:" << start_dep  << " , money left:" << player.get_dep()
    << std::endl;
    float winrate = player.get_total_wins()/(float)gp;
    std::cout << "Player won:  " << player.get_total_wins() << "/" << gp  << " games, winrate: "
    << winrate*100 << "% , total win is $" << player.get_dep()-start_dep << std::endl;
    getc(stdin);
}

