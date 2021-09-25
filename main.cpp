/* GNU General Public License v3.0 */
/******************************************************************************
 *
 * Name: main.cpp - Main source code for card_game project 
 *
 * Copyright (C) 2021, binary_cat, v01z@mail.ru
 *
 *****************************************************************************/

#include "task3.h"

int main(void)
{
     
   Deck *deck = new Deck;
   Game game(deck);

   game.process(deck);

   delete deck;

   return 0;
}