#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "functions.h"

// func name: initializeDeck
// Summary: Fills the empty deck array with cards in order
// Params myDeck: empty deck array
// Param myFace[]: array of names of each face type
// Params mySuit[]: array of names of each suit type
void initializeDeck(Card* myDeck, char* faceNames[], char* suitNames[])
{
	assert(myDeck != NULL);
	Card temp;
	int i;
	for (i = 0; i < DECK_SIZE; i++)
	{
		myDeck[i].face = faceNames[i % NUM_FACES];
		myDeck[i].suit = suitNames[i / NUM_FACES];
		myDeck[i].nextPtr = NULL;

		if (i > 0)
		{
			myDeck[i-1].nextPtr = &(myDeck[i]);
		}
	}

	//shuffle the deck
	int j;
	for (i = 0; i < DECK_SIZE; i++)
	{
		j = rand() % DECK_SIZE;

		temp.face = myDeck[i].face;
		temp.suit = myDeck[i].suit;

		myDeck[i].face = myDeck[j].face;
		myDeck[i].suit = myDeck[j].suit;

		myDeck[j].face = temp.face;
		myDeck[j].suit = temp.suit;
	}
}

// func name: printDeck
// Summary: Prints the current deck
// Params myDeck: deck head pointer
void printCards(Card* topCard)
{
	int i = 1;
	if (topCard->nextPtr == NULL)
	{
		printf("The deck is empty.\n\n");
	}
	else 
	{
		while(topCard != NULL)
		{
			printf("%d: %s of %s\n", i, topCard->face, topCard->suit);
			topCard = topCard->nextPtr;
			i++;
			
		}
	}
	
}


bool isEmpty(Card* topOfDeck)
{
	return topOfDeck == NULL;
}

// void enqueue(DeckPtr *headPtr, DeckPtr *tailPtr, Card * const myCard)
// {
// 	DeckPtr newPtr;
// 	newPtr = malloc(sizeof(Deck));

// 	if (newPtr != NULL) {
// 		newPtr->card = myCard;
// 		newPtr->nextPtr = NULL;

// 		if (isEmpty(*headPtr)) {
// 			*headPtr = newPtr;
// 		}
// 		else {
// 			(*tailPtr)->nextPtr = newPtr;
// 		}

// 		*tailPtr = newPtr;
// 	}

// }

// Card dequeue(DeckPtr *headPtr, DeckPtr *tailPtr)
// {
// 	Card topCard;
// 	DeckPtr tempPtr;

// 	topCard = (*headPtr)->card;
// 	tempPtr = *headPtr;
// 	*headPtr = (*headPtr)->nextPtr;

// 	if (isEmpty(*headPtr)) {
// 		*tailPtr = NULL;
// 	}

// 	free(tempPtr);
// 	return topCard;
// }


void dealCard(Card* topOfDeck, Card* hand, int handSize)
{
	assert(topOfDeck != NULL);
	assert(handSize < HAND_SIZE);
	assert(handSize > 0);
	assert((handSize == 0) && (hand == NULL));

	//if hand is full
	if(handSize == HAND_SIZE)
	{
		return;
	}
	//temporary topCard stores head pointer
	Card* topCard = topOfDeck;
	topOfDeck = topOfDeck->nextPtr;
	topCard->nextPtr = NULL;

	//if hand is empty
	if(hand == NULL)
	{
		hand = topCard;
	}
	//if hand is not empty
	else
	{
		Card* handViewer = hand;
		int i;
		for(i = 0; i < handSize; i++)
		{
			if(topCard->face < handViewer->face)
			{
				break;
			}
			handViewer = handViewer->nextPtr;
		}
		//if inserting to front of hand
		if (i == 0)
		{
			hand = topCard;
			hand->nextPtr = handViewer;
		}
		//if inserting in middle
		else if (i < handSize)
		{
			hand[i-1].nextPtr = topCard;
			topCard->nextPtr = hand[i].nextPtr;
		}
		//if inserting at end of hand
		else
		{
			hand[i].nextPtr = topCard;
		}
	}
	
}

void discardCard(Card* bottomOfDeck, Card* hand, int index)
{
	assert(index < HAND_SIZE);
	assert(index >= 0);
	assert(hand != NULL);

	Card* tempCard = &hand[index];

	//if removing from front of hand
	if (index == 0)
	{
		hand = hand->nextPtr;
	}
	//if removing from middle
	else if (hand[index].nextPtr != NULL)
	{
		hand[index - 1].nextPtr = tempCard->nextPtr;
	}
	//if removing from end
	else
	{
		hand[index - 1].nextPtr = NULL;
	}
	//for all cases, place card at back of deck
	tempCard->nextPtr = NULL;
	bottomOfDeck->nextPtr = tempCard;
}