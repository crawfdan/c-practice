#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "functions.h"

int main(void)
{
	Player p1;
	Player dealer;

	//initialize data to NULL or 0
	memset(&p1, 0, sizeof(p1));
	memset(&dealer, 0, sizeof(dealer));

	char* face[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};

	char* suit[] = {"Hearts", "Diamonds", "Spades", "Clubs"};

	Card* headPtr = NULL;
	Card* tailPtr = NULL;

	Card* deck = {(Card*)calloc(DECK_SIZE, sizeof(Card))};
	//Card* pDeck = &deck[0];
	Card* pHand = &p1.hand[0];
	
	/* seed rand() once */
	srand(time(0));

	initializeDeck(deck, face, suit);
	//test that the deck has been initialized correctly
	printCards(deck);

	int i;
	for (i = 0; i < HAND_SIZE; i++)
	{
		dealCard(&deck, &pHand, p1.handSize);
		printf("-----------------------------------\n");
		printCards(pHand);
		printf("-----------------------------------\n");
		p1.handSize++;
	}

	//printCards(pDeck);
	printf("Your hand:\n"); 
	printCards(pHand);

	free(deck);
	return 0;
}