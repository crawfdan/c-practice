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
void initializeDeck(Card* myDeck)
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

char* getFaceName(Face face)
{
	switch(face)
	{
		case Two: return "Two";
		case Three: return "Three";
		case Four: return "Four";
		case Five: return "Five";
		case Six: return "Six";
		case Seven: return "Seven";
		case Eight: return "Eight";
		case Nine: return "Nine";
		case Ten: return "Ten";
		case Jack: return "Jack";
		case Queen: return "Queen";
		case King: return "King";
		case Ace: return "Ace";
		default: return "InvalidFace";
	}
}

char* getSuitName(Suit suit)
{
	switch(suit)
	{
		case Hearts: return "Hearts";
		case Diamonds: return "Diamonds";
		case Spades: return "Spades";
		case Clubs: return "Clubs";
		default: return "InvalidSuit";
	}
}

// func name: printDeck
// Summary: Prints the current deck
// Params myDeck: deck head pointer
void printCards(Card* topCard)
{
	int i = 1;
	if (topCard == NULL)
	{
		printf("The deck or hand is empty.\n\n");
	}
	else
	{
		Card* cardViewer = topCard;
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


bool isEmpty(Card* topOfDeck)
{
	return topOfDeck == NULL;
}


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
	
	Card* handViewer;
	// int handValue = getFaceValue(handViewer->face);
	// int topValue = getFaceValue(topCard->face)
	if(*hand == NULL || (*hand)->face >= topCard->face)
	{
		topCard->nextPtr = *hand;
		*hand = topCard;
	}
	
	else
	{
		handViewer = *hand;
		while (handViewer->nextPtr != NULL &&
				handViewer->nextPtr->face < topCard->face)
		{
			handViewer = handViewer->nextPtr;
		}
		topCard->nextPtr = handViewer->nextPtr;
		handViewer->nextPtr = topCard;
	}
	
}

// void discardCard(Card* bottomOfDeck, Card* hand, int index)
// {
// 	assert(index < HAND_SIZE);
// 	assert(index >= 0);
// 	assert(hand != NULL);

// 	Card* tempCard = &hand[index];

// 	//if removing from front of hand
// 	if (index == 0)
// 	{
// 		hand = hand->nextPtr;
// 	}
// 	//if removing from middle
// 	else if (hand[index].nextPtr != NULL)
// 	{
// 		hand[index - 1].nextPtr = tempCard->nextPtr;
// 	}
// 	//if removing from end
// 	else
// 	{
// 		hand[index - 1].nextPtr = NULL;
// 	}
// 	//for all cases, place card at back of deck
// 	tempCard->nextPtr = NULL;
// 	bottomOfDeck->nextPtr = tempCard;
// }