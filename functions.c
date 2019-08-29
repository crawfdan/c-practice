#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

// func name: initializeDeck
// Summary: Fills the empty deck array with cards in order
// Params myDeck: empty deck array
// Param myFace[]: array of names of each face type
// Params mySuit[]: array of names of each suit type
void initializeDeck(Card * const myDeck, const char * myFace[], const char * mySuit[])
{
	int i;

	for (i = 0; i < DECK_SIZE; i++)
	{
		myDeck[i].face = myFace[i % 13];
		myDeck[i].suit = mySuit[i / 13];
		myDeck[i].nextPtr = NULL;
	}
}

// func name: printDeck
// Summary: Prints the current deck
// Params myDeck: deck head pointer
void printDeck(DeckPtr currentPtr)
{
	int i;

	if (currentPtr == NULL)
	{
		printf("The deck is empty.\n\n");
	}
	else 
	{
		while(currentPtr != NULL)
		{
			printf("%s of %s\n", (*currentPtr)->card.face, (*currentPtr)->card.suit);
			*currentPtr = (*currentPtr)->nextPtr;
		}

	}
	
}

// func name: shuffleDeck
// Summary: For each card in the deck, save to a temporary var, assign a random card to that position
// and swap places with another card
// Params myDeck: deck array
void shuffleDeck(Card * const myDeck)
{
	int i;
	int j;
	Card temp;

	//Iterate through deck and swap current card with another position
	for (i = 0; i < DECK_SIZE; i++)
	{
		j = rand() % 52;
		temp = myDeck[i];
		myDeck[i] = myDeck[j];
		myDeck[j] = temp;
	}
}

bool isEmpty(DeckPtr headPtr)
{
	return headPtr == NULL;
}

void enqueue(DeckPtr *headPtr, DeckPtr *tailPtr, Card * const myCard)
{
	DeckPtr newPtr;
	newPtr = malloc(sizeof(Deck));

	if (newPtr != NULL) {
		newPtr->card = myCard;
		newPtr->nextPtr = NULL;

		if (isEmpty(*headPtr)) {
			*headPtr = newPtr;
		}
		else {
			(*tailPtr)->nextPtr = newPtr;
		}

		*tailPtr = newPtr;
	}

}

Card dequeue(DeckPtr *headPtr, DeckPtr *tailPtr)
{
	Card topCard;
	DeckPtr tempPtr;

	topCard = (*headPtr)->card;
	tempPtr = *headPtr;
	*headPtr = (*headPtr)->nextPtr;

	if (isEmpty(*headPtr)) {
		*tailPtr = NULL;
	}

	free(tempPtr);
	return topCard;
}