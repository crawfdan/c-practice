#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int main(void) 
{

	Player p1;
	Player dealer;
	int i;

	const char *face[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};

	const char *suit[] = {"Hearts", "Diamonds", "Spades", "Clubs"};

	Card deck[52];
	
	/* seed rand() once */
	srand(time(0));

	initializeDeck(deck, face, suit);

	for (i = 0; i < 52; i++)
	{
		printf("%s of %s\n", deck[i].face, deck[i].suit);
	}

	return 0;
}