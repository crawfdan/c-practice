#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int main(void) 
{
	int i;
	Player p1;
	Player dealer;

	const char* face[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};

	const char* suit[] = {"Hearts", "Diamonds", "Spades", "Clubs"};

	DeckPtr headPtr = NULL;
	DeckPtr tailPtr = NULL;

	Card deck[DECK_SIZE];
	
	/* seed rand() once */
	srand(time(0));

	initializeDeck(deck, face, suit);
	//test that the deck has been initialized correctly

	shuffleDeck(deck);

	for (i = 0; i < DECK_SIZE; i++)
	{
		enqueue(&headPtr, &tailPtr, deck[i]);
	}
	printDeck(deck);

	return 0;
}