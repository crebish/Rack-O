/*
 * game.cpp
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date last edited for starter code: 11/9/2022
 * Edited for HW10 by: Chance Rebish
 * Date: 11/16/23
 * Purpose: Implement the methods for the Game class in the Rack-O game.
 *
 */
#include "game.h"
#include <iostream>

using namespace std;

// Constructor: initialize the deck, player hands, and the discard pile with new
// objects allocated on the heap
Game::Game(string deckFileName)
{
    deck = new Deck(deckFileName);
    for (int i = 0; i < NUM_PLAYERS; i++) {
        hands[i] = new Hand(deck->draw(), deck->draw(), deck->draw(),
                            deck->draw(), deck->draw());
    }
    discard = new DiscardPile(deck->draw());
}

// Destructor: deallocate all of the objects ''owned'' by the Game object
Game::~Game()
{
    for (int i = 0; i < NUM_PLAYERS; i++) {
        delete hands[i];
    }
    delete discard;
    delete deck;
}

// play
// Input: none
// Description: Play through a game of rack-o!
// Output: None
void Game::play()
{
    int playerNum = 0;

    // Take the first turn
    cout << "PLAYER " << playerNum + 1 << "'s TURN:" << endl;
    takeTurn(playerNum);
    cout << endl;

    // Keep taking turns until either one player wins, or the deck runs out of
    // cards.
    while (!didPlayerWin(playerNum) && !deck->isEmpty()) {
        playerNum = (playerNum + 1) % NUM_PLAYERS;
        cout << "PLAYER " << playerNum + 1 << "'s TURN:" << endl;
        takeTurn(playerNum);
        cout << endl;
    }

    if (didPlayerWin(playerNum)) {
        // A player won!
        cout << "CONGRATULATIONS PLAYER " << playerNum + 1 << "! YOU WIN!!"
             << endl;
    } else {
        // deck is empty
        cout << "The deck is empty. IT'S A TIE!" << endl;
    }
}

// takeTurn
// Input: Which player is playing
// Description: Shows the user thier cards and gives them the option
//              to take the discard card or draw a new one
// Output: None
void Game::takeTurn(int playerNum)
{
    if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
        cerr << "Invalid player number: " << playerNum << endl;
        exit(EXIT_FAILURE);
    }

    //Print statements
    cout << "Your hand:" << endl;
    hands[playerNum]->print();
    cout << endl << "Discard pile:" << endl;
    discard->print();
    cout << endl << "Would you like to" << endl << 
        " 1. take the top discard?" << endl << " 2. draw from the deck?" 
        << endl; 
    
    //Determines if user wants to take discard card or draw from deck
    int num = -1;
    while(num < 0 || num > 2){
        cout << "Enter the number for your choice: ";
        cin >> num;
        if(num == 1){
            takeDiscard(playerNum);
        } else if(num == 2){
            drawFromDeck(playerNum);
        }
    }
}

// takeDiscard
// Input: Which player is playing
// Description: Move discard card to hand and the replaced card to discard pile
// Output: None
void Game::takeDiscard(int playerNum)
{
    if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
        cerr << "Invalid player number:" << playerNum << endl;
        exit(EXIT_FAILURE);
    }

    //Uses the card in the discard pile to replace the card selected in the hand
    //and places the replaced card on top of the discard pile
    cout << endl;
    discard->discard(hands[playerNum]->replaceCard(discard->takeDiscard()));
    
    //Prints the end result
    cout << endl << "Your new hand:" << endl;
    hands[playerNum]->print();
}

// drawFromDeck
// Input: Which player is playing
// Description: Draws card from the deck, asks the user if they want the card,
//              and replaces the card or places the drawn card on discard pile
// Output: None
void Game::drawFromDeck(int playerNum)
{
    if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
        cerr << "Invalid player number: " << playerNum << endl;
        exit(EXIT_FAILURE);
    }

    //Print out what card was drawn and save drawn card to new pointer
    cout << endl << "You drew:" << endl;
    Card *drawnCard = deck->draw();
    cout << drawnCard->toString() << endl;
    
    //If they want to use the card, replace the old card 
    //and move it to discard. If not, discard the drawn card
    char answer;
    while(answer != 'y' && answer != 'n'){
        cout << "Would you like to keep this card? (y/n) ";
        cin >> answer;
        if(answer == 'y'){
            cout << endl;
            discard->discard(hands[playerNum]->replaceCard(drawnCard));
            
            cout << endl << "Your new hand:" << endl;
            hands[playerNum]->print();
        } else if(answer == 'n'){
            discard->discard(drawnCard);

            cout << endl << endl << "Your new hand:" << endl;
            hands[playerNum]->print();
        }
    }
}

// didPlayerWin
// Input: The player whose turn it is.
// Description: Check if the player has triggered the win condition
// Output: True if the given player has won; false otherwise.
bool Game::didPlayerWin(int playerNum)
{
    if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
        cerr << "Invalid player number: " << playerNum << endl;
        exit(EXIT_FAILURE);
    }

    return hands[playerNum]->isWinningHand();
}
