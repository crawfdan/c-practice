#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "functions.h"

int main(void)
{
	Player* p1 = (Player*)calloc(1, sizeof(Player));
	Player* dealer = (Player*)calloc(1, sizeof(Player));
	Card* deck = (Card*)calloc(DECK_SIZE, sizeof(Card));
	Card* deckBottom;

	Card* pHand = initializePlayer(&p1);
	Card* dHand = initializePlayer(&dealer);
	
	/* seed rand() once */
	srand(time(0));
	int i;
	//initialize the deck
	initializeDeck(deck, &deckBottom);
	//test that the deck has been initialized correctly
	printCards(deck);
	//deal 5 cards to each player
	for (i = 0; i < HAND_SIZE; i++)
	{
		dealCard(&deck, &pHand, p1->handSize);
		dealCard(&deck, &dHand, dealer->handSize);
		p1->handSize++;
		dealer->handSize++;
	}

	printf("\nDealer's hand:\n");
	printf("-----------------------------------\n");
	printCards(dHand);
	printf("-----------------------------------\n");

	printf("\nYour hand:\n");
	printf("-----------------------------------\n");
	printCards(pHand);
	printf("-----------------------------------\n");

	int index = 0;
	while(index < 1 || index > 5)
	{
		printf("Enter the number of the card you want to discard: ");
		scanf("%d", &index);
	}
	index--;
	discardCard(&deckBottom, &pHand, index, p1->handSize);

	printf("\nYour hand:\n");
	printf("-----------------------------------\n");
	printCards(pHand);
	printf("-----------------------------------\n");

	return 0;
}