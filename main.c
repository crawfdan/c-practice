#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "functions.h"

int main(void)
{
	Player p1;
	Player dealer;

	char* face[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};

	char* suit[] = {"Hearts", "Diamonds", "Spades", "Clubs"};

	Card* headPtr = NULL;
	Card* tailPtr = NULL;

	Card deck[DECK_SIZE] = {NULL};
	
	/* seed rand() once */
	srand(time(0));

	initializeDeck(&deck[0], face, suit);
	//test that the deck has been initialized correctly

	printCards(deck);

	return 0;
}