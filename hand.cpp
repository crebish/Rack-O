/*
 * hand.cpp
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date last edited for starter code: 11/8/2022
 * Edited for HW10 by: Chance Rebish
 * Date: 11/16/23
 * Purpose: Implement the methods for the Hand class in the Rack-O game.
 *
 */
#include "card.h"
#include "hand.h"
#include <iostream>

using namespace std;

// Constructor: Store the provided card pointers in our hand.
Hand::Hand(Card *c1, Card *c2, Card *c3, Card *c4, Card *c5)
{
    cards[0] = c1;
    cards[1] = c2;
    cards[2] = c3;
    cards[3] = c4;
    cards[4] = c5;
}

// Destructor: Deallocate any cards in our hand
Hand::~Hand()
{
    for (int i = 0; i < HAND_SIZE; i++) {
        delete cards[i];
    }
}

// isWinningHand
// Input: none
// Description: Determines if the hand is winning
// Output: true if winning, false otherwise
bool Hand::isWinningHand()
{
    //Makes sure that the numbers increase left to right
    if(cards[0]->getNum() < cards[1]->getNum() && 
    cards[1]->getNum() < cards[2]->getNum() &&
    cards[2]->getNum() < cards[3]->getNum() && 
    cards[3]->getNum() < cards[4]->getNum()){
        return true;
    } 
    return false;
    
}

// replaceCard
// Input: pointer to a card
// Description: Replaces the chosen card with the input card
// Output: pointer to the replaced card
Card *Hand::replaceCard(Card *newCard)
{
    print();
    cout << endl;

    //Print discard choice
    int index = -1;
    while(index < 0 || index > 4){
        cout << "Enter the index of the card you'd like to discard: ";
        cin >> index;
    }
    
    //Replace card and return the replaced card
    Card *oldCard = cards[index];
    cards[index] = newCard;

    return oldCard;
}

/*
 * Everything below this comment is purely for "drawing" hands on the screen.
 * Students won't need to read through or modify any of these methods.
 *
 */

void Hand::print()
{
    for (int i = 0; i < HAND_SIZE; i++) {
        if (cards[i] == NULL) {
            cerr << "ERROR: hand does not have " << HAND_SIZE << " cards!"
                 << endl;
            exit(EXIT_FAILURE);
        }
    }

    // print Top Edge
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i > 0) {
            cout << "  ";
        }
        cout << cards[i]->getTopEdge();
    }
    cout << endl;

    // print Blank Line
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i > 0) {
            cout << "  ";
        }
        cout << cards[i]->getBlankLine();
    }
    cout << endl;

    // print Number Line
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i > 0) {
            cout << "  ";
        }
        cout << cards[i]->getNumberLine();
    }
    cout << endl;

    // print Blank Line
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i > 0) {
            cout << "  ";
        }
        cout << cards[i]->getBlankLine();
    }
    cout << endl;

    // print Bottom Edge
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i > 0) {
            cout << "  ";
        }
        cout << cards[i]->getBottomEdge();
    }
    cout << endl;

    // print index numbers
    for (int i = 0; i < HAND_SIZE; i++) {
        cout << "   ";
        if (i > 0) {
            cout << "    ";
        }
        cout << i;
    }
    cout << endl;
}
