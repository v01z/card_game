/* GNU General Public License v3.0 */
/******************************************************************************
 *
 * Name: task3.cpp - source code for card_game project
 *
 * Copyright (C) 2021, binary_cat, v01z@mail.ru
 *
 *****************************************************************************/

#include "task3.h"

Card::Card(): face{""}, suit{""} {}

Card::Card(const std::string input_face, const std::string input_suit):
   face{input_face}, suit{input_suit} {}


const std::string Card::getFace() const { return face; }
const std::string Card::getSuit() const { return suit; }

void Card::setFace(const std::string s){
    face = s;
}
void Card::setSuit(const std::string s){
    suit = s;
}

bool Card::operator==(const Card &card)const {
    if (this->getFace().compare(card.getFace()) == 0 &&
        this->getSuit().compare(card.getSuit()) == 0)
            return true;

    return false; //else
}

Card& Card::operator=(const Card &other) {
    if (this == &other)
        return *this;

    face = other.getFace();
    suit = other.getSuit();

    return *this;
}

Deck::Deck(): size {} {

    cards[size].setFace("Joker");
    cards[size].setSuit("Joker");

    for (size_t i{1}; i < MAX_CARDS_COUNT; ++i)
    {
        do{
            //Избегаем повторов
        } while (pushCard(getRandCard()) == false);

    }
}

Deck::~Deck() {}

size_t Deck::getSize() const { return size; }

Card Deck::getRandCard() const {

        size_t random_face = rand()%MAX_FACE;
        size_t random_suit = rand()%MAX_SUIT;

        Card ret_val(Face[random_face], Suit[random_suit]);

        return ret_val;
}

bool Deck::pushCard(const Card &card) {

    for (size_t i{1}; i <= size; ++i)
    {
        if (card == cards[i])
            return false;
    }

    size++;

 //   std::cout << size << std::endl; //debug

    cards[size].setFace(card.getFace());
    cards[size].setSuit(card.getSuit());

//    std::cout << size << std::endl; //debug

    return true;
}

Card Deck::pullCard(){
    if (size == 0)
    {
    std::cerr << "Deck is empty." << std::endl;
//    return Card("Joker", "Spades");
    return cards[size];
    }

    return cards[size--];
}


Game::Game(Deck *deck) {
    srand(time(NULL));

    //debug
    for (size_t i{}; i < 53; ++i)
    {
        std::cout << i << ": ";
        std::cout << deck->cards[i].getFace() << std::endl;
    }
    //end debug
}

size_t Game::getTotal(Deck *deck, size_t count, bool isHuman)
{
    size_t total {};
    Card *cards;

    if (count == 0)
    {
        totalInfoMsg(isHuman, total);
        return total;
    }

    cards = new Card[count];

    std::cout << "Let' see what we have..\n";
    for (size_t j{}; j < count; ++j)
    {
        cards[j] = deck->pullCard();

        std::cout << cards[j].getFace() << " of ";
        std::cout << cards[j].getSuit() << ".\n";
    }

    for (size_t i{}; i < count; ++i)
    {
        if (cards[i].getFace().compare("Ace") == 0)
            total += 11;
        if (cards[i].getFace().compare("Deuce") == 0)
            total += 2;
        if (cards[i].getFace().compare("Three") == 0)
            total += 3;
        if (cards[i].getFace().compare("Four") == 0)
            total += 4;
        if (cards[i].getFace().compare("Five") == 0)
            total += 5;
        if (cards[i].getFace().compare("Six") == 0)
            total += 6;
        if (cards[i].getFace().compare("Seven") == 0)
            total += 7;
        if (cards[i].getFace().compare("Eight") == 0)
            total += 8;
        if (cards[i].getFace().compare("Nine") == 0)
            total += 9;
        if (cards[i].getFace().compare("Ten") == 0)
            total += 10;
        if (cards[i].getFace().compare("Jack") == 0)
            total += 2;
        if (cards[i].getFace().compare("Queen") == 0)
            total += 3;
        if (cards[i].getFace().compare("King") == 0)
            total += 4;
    }

    delete []cards;

    totalInfoMsg(isHuman, total);
    return total;
}

size_t Game::askForCardsCount() {
    size_t cards_count;

    do {
        std::cout << "Home many cards do u want?" << std::endl;
        std::cout << "Enter an integer value (zero to pass).";
        std::cout << std::endl;
        std::cin >> cards_count;
        if(std::cin.good())
            break;
        std::cin.clear();
        std::cin.ignore();
    }while (true);

    return cards_count;
}

size_t Game::machineTurn(Deck *deck) {
    size_t ret_val;
    std::cout << "Machine's turn.." << std::endl;
    //3 - magick number. This code should be
    //improved in the future
    ret_val = rand() % 3;

    return ret_val;
}

void Game::process(Deck *deck) {
    size_t machine_total{};
    size_t human_total {};


    do {
        size_t x = askForCardsCount();

        machine_total += getTotal(deck, machineTurn(deck), false);
        showTotal(machine_total);

        human_total += getTotal(deck, x, true);
        showTotal(human_total);

       if (possibleToPlay(human_total, machine_total))
           if (!askForContinue())
               break;

    } while (possibleToPlay(human_total, machine_total));


    if (isDraw(human_total, machine_total))
        std::cout << "Draw." << std::endl;

    if (winStatus(human_total, machine_total))
        std::cout << "You won!" << std::endl;

    if  (winStatus(machine_total, human_total))
        std::cout << "Machine won!" << std::endl;

}

bool Game::possibleToPlay(size_t human_total,
        size_t machine_total) {

//    if (human_total > MAX || machine_total > MAX)
 //       return false;
  //  if (winStatus(human_total, machine_total))
   //     return false;
    if (human_total > MAX || machine_total > MAX)
        return false;


    return true; //else
}

bool Game::winStatus(size_t total, size_t opponent_total){

    if ((total <= MAX) && ((total > opponent_total) ||
        opponent_total > MAX))
                return true;

    return false;
}

bool Game::isDraw(size_t first, size_t second) {
    if ((first == second) || (first > MAX && second > MAX))
        return true;

    return false; //else
}

void Game::totalInfoMsg(bool isHuman,
    size_t just_got) {
    std::string who;

    who = isHuman?"You've ":"Machine's ";

    std::cout << who << "got " << just_got << " scores.\n";
//    std::cout << "Total amount is  " << total << std::endl;
}

bool Game::askForContinue() {
    std::string answer;

    do{
        std::cout << "Do you want to continue? (y/n):";
        std::cin >> answer;
        if (std::cin.good())
        std::cin.clear();
            break;

        std::cin.ignore();
    }while(true);

    if ((answer.compare("y") == 0) || (answer.compare("yes") == 0))
        return true;

    return false; //else
}

void Game::showTotal(size_t amount) {
    std::cout << "Total is :" << amount << std::endl;
}
