#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "functions.h"

// Card* addCard(char* face, char* suit)
// {
// 	Card* temp = (Card*)malloc(sizeof(Card));
// 	temp->face = face;
// 	temp->suit = suit;
// 	temp->nextPtr = NULL;

// 	return temp;
// }

// func name: initializeDeck
// Summary: Fills the empty deck array with cards in order
// Params myDeck: empty deck array
// Param myFace[]: array of names of each face type
// Params mySuit[]: array of names of each suit type
void initializeDeck(Card* myDeck, Card** bottomOfDeck)
{
	assert(myDeck != NULL);

	Card temp;
	//initialize deck with cards in order
	int i;
	for (i = 0; i < DECK_SIZE; i++)
	{
		myDeck[i].face = (Face)(i % NUM_FACES);
		myDeck[i].suit = (Suit)(i / NUM_FACES);

		if (i > 0)
		{
			myDeck[i-1].nextPtr = &(myDeck[i]);
		}
		if (i == DECK_SIZE-1)
		{
			myDeck[i].nextPtr = NULL;
			*(bottomOfDeck) = &(myDeck[i]);
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

Card* initializePlayer(Player** player)
{
	Card* handPointer;
	(*player)->handScore = (Score)-1;
	(*player)->handSize = 0;
	handPointer = (*player)->hand;
	handPointer = NULL;
	return handPointer;
}

char* getFaceName(Face face)
{
	char* faces[] = {"Two", "Three", "Four", "Five", "Six", "Seven",
					"Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};

	return faces[face];
}

char* getSuitName(Suit suit)
{
	char* suits[] = {"Hearts", "Diamonds", "Spades", "Clubs"};
	
	return suits[suit];
}

// func name: printDeck
// Summary: Prints the current deck
// Params myDeck: deck head pointer
void printCards(Card* topCard)
{
	if (!topCard)
	{
		printf("The deck or hand is empty.\n\n");
	}
	else
	{
		Card* cardViewer = topCard;
		int i = 1;
		while(cardViewer != NULL)
		{
			printf("%d: %s of %s\n", i, getFaceName(cardViewer->face),
										getSuitName(cardViewer->suit));
			cardViewer = cardViewer->nextPtr;		
			i++;	
		}
		return;
	}
	
}


// bool isEmpty(Card* topOfDeck)
// {
// 	return topOfDeck == NULL;
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
	Card* topCard = (*topOfDeck);
	(*topOfDeck) = (*topOfDeck)->nextPtr;
	topCard->nextPtr = NULL;
	
	//if the hand is empty
	if (handSize == 0)
	{
		*hand = topCard;
	}
	//insert at front of hand
	else if((*hand) == NULL || (*hand)->face >= topCard->face)
	{
		topCard->nextPtr = *hand;
		*hand = topCard;
	}
	//insert at middle or back of hand
	else
	{
		Card* handViewer = *hand;
		//find Card node before insertion
		while (handViewer->nextPtr != NULL &&
				handViewer->nextPtr->face < topCard->face)
		{
			handViewer = handViewer->nextPtr;
		}
		//insert at handViewer position
		topCard->nextPtr = handViewer->nextPtr;
		handViewer->nextPtr = topCard;
	}
	
}

void discardCard(Card** bottomOfDeck, Card** hand, int index, int handSize)
{
	assert(index < handSize);
	assert(index >= 0);
	assert(hand != NULL);

	//ptr to keep track of position in hand
	Card* handPtr = *hand;
	//card to be discarded
	Card* temp;

	//if hand is empty or index out of range
	if(!hand || index >= handSize)
	{
		return;
	}
	//if removing head
	else if (index == 0)
	{
		temp = *hand;
		*hand = handPtr->nextPtr;
	}

	else
	{
		//find pointer position of previous card to discard
		int i;
		for(i=0; handPtr != NULL && i < (index-1); i++)
		{
			handPtr = handPtr->nextPtr;
		}
		//save position of card after discarded card
		Card* next = handPtr->nextPtr->nextPtr;
		temp = handPtr->nextPtr;
		handPtr->nextPtr = next;
	}
	
	//place card at back of deck
	temp->nextPtr = NULL;
	(*bottomOfDeck)->nextPtr = temp;
}