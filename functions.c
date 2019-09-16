#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "functions.h"

const char* faces[] = {"Two", "Three", "Four", "Five", "Six", "Seven",
					"Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
const char* suits[] = {"Hearts", "Diamonds", "Spades", "Clubs"};
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
		myDeck[i].face = (Face)(i % numFaces);
		myDeck[i].suit = (Suit)(i / numFaces);

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
	Player* temp = *player;
	temp->handScore = invalidScore;
	temp->highCard = invalidFace;
	temp->handSize = 0;
	handPointer = temp->hand;
	handPointer = NULL;
	return handPointer;
}

const char* getFaceName(Face face)
{
	return faces[face];
}

const char* getSuitName(Suit suit)
{
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
bool dealCard(Card** topOfDeck, Card** hand, int handSize)
{
	assert((*topOfDeck) != NULL);
	assert(handSize < HAND_SIZE);
	assert(handSize >= 0);

	Card* handViewer = *hand;

	//if hand is full
	if(handSize == HAND_SIZE)
	{
		return false;
	}

	//temporary topCard stores top card on deck
	Card* topCard = (*topOfDeck);
	//point deck to the next card
	(*topOfDeck) = (*topOfDeck)->nextPtr;
	//cut off top card connection to deck
	topCard->nextPtr = NULL;
	
	//if the hand is empty
	if (handSize == 0)
	{
		handViewer = topCard;
		return true;
	}
	//insert at front of hand
	else if(handViewer == NULL || handViewer->face >= topCard->face)
	{
		topCard->nextPtr = handViewer;
		handViewer = topCard;
		return true;
	}
	//insert at middle or back of hand
	else
	{
		//find Card node before insertion
		while (handViewer->nextPtr != NULL &&
				handViewer->nextPtr->face < topCard->face)
		{
			handViewer = handViewer->nextPtr;
		}
		//insert at handViewer position
		topCard->nextPtr = handViewer->nextPtr;
		handViewer->nextPtr = topCard;
		return true;
	}
	return false;
	
}

bool discardCard(Card** bottomOfDeck, Card** hand, int index, int handSize)
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
		return false;
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
	return true;
}

//evaluates a player's hand, returns score of current hand
void setHandScore(Player** player)
{
	Score score = invalidScore;


}

Score checkFlushOrStraight(Player* player)
{
	assert(player->hand != NULL);

	int faceCounter, suitCounter = 0;
	Card* temp = player->hand;
	//iterate through hand and count number of faces in order/suits matching
	while(temp->nextPtr != NULL)
	{
		//if the next card is in order by face or loops from ace to two
		if((temp->nextPtr->face = temp->face++) ||
		(temp->face == ace && temp->nextPtr->face == two))
		{
			faceCounter++;
		}
		if(temp->suit == temp->nextPtr->suit)
		{
			suitCounter++;
		}
		temp = temp->nextPtr;
	}
	
	//if the player has a straight
	if(faceCounter==HAND_SIZE-1)
	{
		//check for straight flush
		if(suitCounter==HAND_SIZE-1)
		{
			//check for royal flush
			if(player->hand->face == ten)
			{
				return royalFlush;
			}
			return straightFlush;
		}
		return straight;
	}

	//check for only a flush
	else if(suitCounter==HAND_SIZE-1)
	{
		return flush;
	}

	return invalidScore;
}

Score checktwoThreeFourKind(Player* player)
{
	assert(player->hand != NULL);
	Card* temp = player->hand;
	int counter = 0;

	while(temp->nextPtr != NULL)
	{
		if(temp->face == temp->nextPtr->face)
		{
			counter++;
		}
	}
	return invalidScore;
}