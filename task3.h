/* GNU General Public License v3.0 */
/******************************************************************************
 *
 * Name: task3.h  - Header file for card_game project
 *
 * Copyright (C) 2021, binary_cat, v01z@mail.ru
 *
 *****************************************************************************/

#ifndef TASK3_H
#define TASK3_H

#include "main.h"

const std::string Face[] = { "Ace", "Deuce", "Three", "Four", "Five",
                              "Six", "Seven", "Eight", "Nine", "Ten",
                              "Jack", "Queen", "King" };

const std::string Suit[] = { "Hearths", "Diamonds", "Clubs", "Spades" };

class Card {
private:
    std::string face;
    std::string suit;
public:
    const std::string getFace() const;
    const std::string getSuit() const;

    void setFace(const std::string);
    void setSuit(const std::string);

    Card();
    Card(const std::string, const std::string);
    Card& operator=(const Card&);

    //Для сравнения созданной в функции Deck::getRandCard() объекта Card, с
    //уже имеющимися в массиве Deck::cards[] (если не совпадает, то функция
    //Deck::getRandCard() прогоняется заново (до тех пор, пока не success).
    bool operator==(const Card&)const;
};

//Объекты Сard хранятся в массиве Deck::cards. Работа с массивом производится
//как со стеком.
class Deck: public Card {
private:
    static const size_t MAX_FACE { 13 };
    static const size_t MAX_SUIT { 4 };
    static const size_t MAX_CARDS_COUNT { 52 + 1}; //one (0) is for Joker
    size_t size; //размер "cтека"
public:
    Card cards[MAX_CARDS_COUNT];
    size_t getSize() const;
    Card getRandCard() const;
    bool pushCard(const Card &);
    Card pullCard();
    Deck();
    ~Deck();
};

class Game {
private:
    static const size_t MAX { 21 }; //total for win
    Game() = delete;
public:
    Game(Deck *);
    size_t machineTurn(Deck *);
    size_t getTotal(Deck*, size_t, bool);
    void totalInfoMsg(bool, size_t);
    size_t askForCardsCount();
    bool askForContinue();
    void process(Deck *);
    bool possibleToPlay(size_t, size_t);
    bool isDraw (size_t, size_t);
    bool winStatus(size_t, size_t);
    void showTotal(size_t);

};



#endif //TASK3_H
