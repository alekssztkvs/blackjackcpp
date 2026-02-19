#include "Game.h"
#include "Safe_input.h"
#include <iostream>
#ifdef WIN_32
#include <windows.h>
#define sleep(x) Sleep((x)*1000)
#else
#include <unistd.h>
#endif

Game::Game() : deck() {deck.createdeck();}

void Game::params()
{

    difficulty = (enum Difficulty)input_int("Enter difficulty (1 easy, 2 optimal, 3 hard): ", 1, 3);
    if (difficulty == EASY)
    {
        non_risk = 17;
        blackjack_ratio = 3;
        regular_ratio = 2;
        start_dep = 3000;
    }
    else if (difficulty == OPTIMAL)
    {
        non_risk = 17;
        blackjack_ratio = 3;
        regular_ratio = 2;
        start_dep = 2500;
    }
    else if (difficulty == HARD)
    {
        non_risk = 17;
        blackjack_ratio = 2;
        regular_ratio = 1.5;
        start_dep = 250;
    }
}
void Game::start()
{

    params();
    int max_rounds = 10;
    total_rounds = input_int("How many rounds?(1-10) :", 1, max_rounds);
    sleep(1);
    int min_cards = 10;
    deck.shuffledeck();

    player.get_deck(&deck);
    dealer.get_deck(&deck);
    player.set_dep(start_dep);

    for(gp = 1; gp <= total_rounds; gp++)
    {
        if (deck.get_top_num() < min_cards)
        {
            deck.shuffledeck();
            deck.changetop();
        }
        if (!player.have_money())
            break;

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
    }
    sleep(2);
    std::cout << "\n\nRound " << gp << " is finished...\n" ;
    sleep(1);
    dealer.reset();
    player.reset();
    }

}

int Game::winner()
{
    printf("\n\n\n");
    if (player.isblackjack())
    {
        printf("Player wins: Blackjack!\n");
        return 1;
    }
    else if (player.isoverdraw())
    {
        printf("Player loses due to overdraw!\n");
        return 0;
    }
    else if (dealer.isoverdraw())
    {
        printf("Player wins: dealer overdraw!\n");
        return 1;
    }
    else if (dealer.isblackjack())
    {
        printf("Dealer wins: Blackjack!\n");
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