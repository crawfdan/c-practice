#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
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
		//myDeck[i].nextPtr = NULL;

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

	//change only face and suit values to keep nextPtr in order
		temp.face = myDeck[i].face;
		temp.suit = myDeck[i].suit;

		myDeck[i].face = myDeck[j].face;
		myDeck[i].suit = myDeck[j].suit;

		myDeck[j].face = temp.face;
		myDeck[j].suit = temp.suit;
	}
}

int getFaceValue(char *str)
{
	char* face[NUM_FACES] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
	assert(str != NULL);
	int i;
	for (i=0; i < NUM_FACES; i++)
	{
		if (strcmp(str, &(face[i][0])) == 0) 
		{
			return i;
		}
	}
	printf("\nCould not determine card face value.\n");
	return -1;
}

// func name: printDeck
// Summary: Prints the current deck
// Params myDeck: deck head pointer
void printCards(Card* topCard)
{
	int i = 1;
	if ((topCard->face == NULL) && (topCard->suit == NULL))
	{
		printf("The deck or hand is empty.\n\n");
	}
	else
	{
		Card* cardViewer = topCard;
		while(cardViewer != NULL)
		{
			printf("%d: %s of %s\n", i, cardViewer->face, cardViewer->suit);
			cardViewer = cardViewer->nextPtr;
			i++;
			
		}
		return;
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


void dealCard(Card** topOfDeck, Card** hand, int handSize)
{
	assert((*topOfDeck) != NULL);
	assert(handSize < HAND_SIZE);
	assert(handSize >= 0);

	//if hand is full
	if(handSize == HAND_SIZE)
	{
		return;
	}
	
	//temporary topCard stores head pointer
	Card* topCard = *topOfDeck;
	printf("Start:\n");
	printf("\n%s", topCard->face);
	printf("\n%s", topCard->nextPtr->face);
	printf("\n%s", (*topOfDeck)->face);

	*topOfDeck = (*topOfDeck)->nextPtr;
	topCard->nextPtr = NULL;
	printf("\ntopCard:%s , topOfDeck: %s \n", topCard->face,
											(*topOfDeck)->face);
	//										(*topOfDeck)->nextPtr->face
	//topCard->nextPtr = NULL;
	
	
	printf("%s: %s of %s\n", __FUNCTION__, topCard->face, topCard->suit);
	//if hand is empty
	if(handSize == 0)
	{
		printf("a\n");
		(*hand)[0] = *topCard;
	}
	//if hand is not empty
	else
	{
		printf("b\n");
		Card* handViewer = *hand;
		int i;
		// find where the card belongs
		for(i = 0; i < handSize; i++)
		{
			printf("\n%d\t%d\n", getFaceValue(topCard->face), getFaceValue(handViewer->face));
			if(getFaceValue(topCard->face) < getFaceValue(handViewer->face))
			{
				break;
			}

			else if (handViewer->nextPtr != NULL)
			{
				printf("c\n");
				handViewer = handViewer->nextPtr;
			}

		}
		// if inserting to front of hand
		if (i == 0)
		{
		printf("d\n");
		topCard->nextPtr = *hand;
		*hand = topCard;
			//topCard->nextPtr = handViewer;
		}
		// if inserting at end
		else if (i == handSize)
		{
			//(*hand)[i-1].nextPtr = topCard;
			printf("e\n");
			Card* tempCard = *hand;
			while(tempCard->nextPtr != NULL)
			{
				tempCard = tempCard->nextPtr;
			}
			tempCard->nextPtr = topCard;
		}
		// if inserting in middle
		else if (i < handSize)
		{
			printf("f\n");
			topCard->nextPtr = handViewer;
			handViewer->nextPtr = topCard;

			(*hand)[i-1].nextPtr = topCard;
		}
		else
		{
			printf("Error dealing card.\n");
		}
		
	}
	//free(topCard);
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