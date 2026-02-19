#include "Game.h"
#include "AI.h"
#include "Safe_input.h"
#include <iostream>
#ifdef WIN_32
#include <windows.h>
#define sleep(x) Sleep((x)*1000)
#else
#include <unistd.h>
#endif

Game::Game() : player(), dealer(), deck() {deck.createdeck(); testAI = new AI();}
Game:: ~Game() { delete testAI; }

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

    char ai_mode = input_yes_no("Play with AI (y/n)? Otherwise solo\n");
    with_ai = (ai_mode == 'y') ? true : false;

    deck.shuffledeck();
    player.get_deck(&deck);
    dealer.get_deck(&deck);
    player.set_dep(start_dep);
    need_next_round = true;
    gp = 0;
    
    if (with_ai)
    {
    testAI->set_params();
    testAI->get_deck(&deck);
    }
}
void Game::start()
{

    set_params();
    sleep(1);
    play_until_finish();
    }

void Game::play_until_finish()
{
    ai_play_round();
    determine_winner();
    if (need_next_round)        //change to while if total_rounds is big
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
        std::cout << "Blackjack!You win!\n";
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

    if(with_ai)
        testAI->ai_winner(dealer.get_total());
    sleep(1);
    gp++;
    std::cout << "\n\nRound " << gp << " is finished...\n" ;
    sleep(1);
    dealer.reset();
    player.reset();

    if(with_ai)
        testAI->reset();
}

int Game::winner()
{
    std::cout<<"\n\n";
    if (player.isblackjack())
    {
        std::cout<<"Player wins: Blackjack!\n";
        sleep(1);
        return 1;
    }
    else if (player.isoverdraw())
    {
        std::cout<<"Player loses due to overdraw!\n";
        sleep(1);
        return 0;
    }
    else if (dealer.isoverdraw())
    {
        std::cout << "Player wins: dealer overdraw!\n";
        sleep(1);
        return 1;
    }
    else if (dealer.isblackjack())
    {
        std::cout << "Dealer wins: Blackjack!\n";
        sleep(1);
        return 0;
    }
    else if (player.get_total() > dealer.get_total())
    {
        std::cout << "Player wins with total:" << player.get_total()
        <<", Dealer has: " << dealer.get_total() << std::endl;
        sleep(1);
        return 1;
    }
    else if (player.get_total() == dealer.get_total())
    {
        std::cout << "Draw! Dealer: " << dealer.get_total() << " total, player: "
        << player.get_total() << " total\n";
        sleep(1);
        return -1;
    }   
    else
    {
        std::cout << "Dealer wins with: " << dealer.get_total() << " total against players: "
        << player.get_total() << " total\n";
        sleep(1);
        return 0;
    }
}


void Game :: results()
{
    std::cout << "Game finished:\n";
    std::cout << "Starting deposit:$" << start_dep  << " , money left:$" << player.get_dep()
    << std::endl;
    float winrate = player.get_total_wins()/(float)gp;

    std::cout << "Player won:  " << player.get_total_wins() << "/" << gp  << " games, winrate: "
    << winrate*100 << "% , total win is $" << player.get_dep()-start_dep << std::endl;

    std::cout<<"Press enter to quit...";
    getc(stdin);
}

void Game::ai_play_round()
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
        sleep(1);

        if(with_ai)
        {
            std::cout << "-------------------------------" << std::endl;
            testAI->ai_bet();
        }
        sleep(1);

        if(with_ai)
            testAI->draw_at_start();
        std::cout << "-------------------------------" << std::endl;
        dealer.first_card();
    
    if (player.bj())
    {
        std::cout << "Blackjack!You win!\n";
        player.payout(blackjack_ratio);
    }
    else
    {
        player.hit();
        sleep(1);
        if(with_ai)
        {
            std::cout << "-------------------------------" << std::endl;
            testAI->ai_hit();
        }
        sleep(1);
        std::cout << "-------------------------------" << std::endl;
            dealer.draw(non_risk);
            sleep(1);

        if (dealer.get_total() == 20 && dealer.has_ace())
            player.hit();

    
        return;
    }
    // if(with_ai)
    //     testAI->ai_hit();
    // dealer.draw(non_risk);
    // sleep(1);
    
}

