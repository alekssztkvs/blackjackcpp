#include "Card.h"
#include <iostream>
#include <iomanip>

Card::Card() : number(2), suit(clubs) {}
Card::Card(int n, Suit s) : number(n), suit(s) {}

void Card::show_card_ascii()
{
    std::cout << "------\n";
    symbol(0);
    switch(suit)
        {
            case clubs :std::cout << "|  ♣ |\n"; break;
            case diamonds: std::cout << "|  ♦ |\n"; break;
            case hearts: std::cout << "|  ♥ |\n"; break;
            case spades: std::cout << "|  ♠ |\n"; break;
        }
    symbol(1);
    std::cout << "------\n";
}

void Card::symbol(int rev)
{
    if (number >= 2 && number <= 10)
    {
        if (rev == 0)
        std::cout << "|" << std::setw(2)
        << number << "  |" << std::endl;
        else
        std::cout << "|  " << std::setw(2)
        << number << "|" << std::endl;
    }
    else
    {
        if (rev == 0)
        switch(number)
        {
            case jack: std::cout << "|" << std::setw(2)
            << "J " << "  |" << std::endl; break;
            case queen: std::cout << "|" << std::setw(2)
            << "Q " << "  |" << std::endl; break;
            case ace: std::cout << "|" << std::setw(2)
            << "A " << "  |" << std::endl; break;
            case king: std::cout << "|" << std::setw(2)
            << "K " << "  |" << std::endl; break;
        }
        else
            switch(number)
            {
            case jack: std::cout << "|  " << std::setw(2)
            << " J" << "|" << std::endl; break;
            case queen: std::cout << "|  " << std::setw(2)
            << " Q" << "|" << std::endl; break;
            case ace: std::cout << "|  " << std::setw(2)
            << " A" << "|" << std::endl; break;
            case king: std::cout << "|  " << std::setw(2)
            << " K" << "|" << std::endl; break;
            }
    }

}

int Card::get_number()
{
    int face = 10;
    if (number >= jack && number < ace)
        return face;
    else if (number == ace)
    {
        int def_ace = 11;
        return def_ace;
    }
    else
        return number;
}

int Card::cardnum()
{
    return number;
}