/*
 * deck.cpp
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date last edited for starter code: 11/8/2022
 * Edited for HW10 by: Chance Rebish
 * Date: 11/16/23
 * Purpose: Implement the methods for the Deck class in the Rack-O game.
 *
 */

#include "deck.h"
#include <fstream>
#include <iostream>

using namespace std;

// Constructor: read in the numbers listed in a "deck file", create a Card on
// the heap for each number, and store the resulting Card pointers in the deck.
Deck::Deck(string deckFileName)
{
    ifstream deckFile(deckFileName);
    if (deckFile.fail()) {
        cerr << "Failed to open deck file: " << deckFileName << endl;
        exit(EXIT_FAILURE);
    }

    // Read in all the numbers from the file, making a card for each one and
    // stroring it in the deck array.
    int cardNum;
    for (int i = 0; i < MAX_DECK_SIZE; i++) {
        // Read in the next number, making sure we didn't run into any errors
        deckFile >> cardNum;
        if (deckFile.eof()) {
            cerr << "File does not contain " << MAX_DECK_SIZE << " cards!"
                 << endl;
            exit(EXIT_FAILURE);
        } else if (deckFile.fail()) {
            cerr << "Failed to read from file: " << deckFileName << endl;
            exit(EXIT_FAILURE);
        }

        // Allocate a new Card object on the heap, and store a pointer to that
        // Card in the ith slot of "deck".
        deck[i] = new Card(cardNum);
    }

    // No cards have been drawn, so the top card of the deck is captured with
    // the Card pointer at index 0 of "deck".
    topCard = 0;
}

// Destructor: deallocate any Card pointers remaining in the deck
Deck::~Deck()
{
    for (int i = topCard; i < MAX_DECK_SIZE; i++) {
        delete deck[i];
    }
}

// isEmpty
// Input: none
// Description: Determines if the draw deck still has cards left
// Output: true if deck is empty, false otherwise
bool Deck::isEmpty()
{
    //topCard must be smaller than MAX_DECK_SIZE
    return topCard == MAX_DECK_SIZE;
}

// draw
// Input: none
// Description: Draws the top card on the draw deck
// Output: pointer to the top card in the draw deck
Card *Deck::draw()
{
    if (isEmpty()) {
        cerr << "ERROR: Drawing from an empty deck" << endl;
        exit(EXIT_FAILURE);
    }

    //increment topCard and return the previous card
    topCard++;
    return deck[topCard - 1];
}
