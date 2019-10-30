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

void processHand(Card* yourHand)
{
	assert (yourHand != NULL);
	Event_t event = ev_nextCard;
	stateMachine_t *SMT = &stateTransMatrix[0];

	//state

	while(yourHand->nextPtr != NULL)
	{
		Card prevCard = *yourHand;
		yourHand = yourHand->nextPtr;
		Card currCard = *yourHand;

		int i;
		for(i=0; i < sizeof(stateTransMatrix)/sizeof(stateTransMatrix[0]); i++)
		{
			if(stateTransMatrix[i].currentState == SMT->currState)
			{
				if(stateTransMatrix[i].event == event)
				{
					//Transition to next state
					SMT->currState = stateTransMatrix[i].nextState;

					//Call state function
					(Event_t *)stateFunction[SMT->currState].func(currCard, prevCard);
					break;
				}
			}
		}
	}
}

Event_t func_highCard(Card currCard, Card prevCard)
{
	static int flushCounter, straightCounter = 0;
	//if faces match, return onePair event
	Event_t result = (currCard.face == prevCard.face) ? ev_matchPair:ev_nextCard;

	//check pair for a straight
	if (currCard.face == prevCard.face++)
	{
		straightCounter++;

		if(straightCounter == HAND_SIZE - 1)
		{
			result = ev_matchStraight;
			straightCounter = 0;
		}
	}
	//check pair for a flush
	else if (currCard.suit == prevCard.suit)
	{
		flushCounter++;

		if(flushCounter == HAND_SIZE-1 && result == ev_matchStraight)
		{
			result = ev_matchStraightFlush;
			flushCounter = 0;
		}

		else if(result = ev_matchStraightFlush && currCard.face == ace)
		{
			result = ev_matchRoyalFlush;
		}

		else if(flushCounter == HAND_SIZE - 1)
		{
			result = ev_matchStraight;
			flushCounter = 0;
		}
	}
	return result;
}

Event_t func_onePair(Card currCard, Card prevCard)
{
	Event_t result = ev_none;
	static bool visited = false;

	if(prevCard.face == currCard.face)
	{
		//twoPair if you have visited this state, three of a kind if not
		result = visited ? ev_matchSecondPair:ev_matchThreeOfKind;
		visited = false;
	}

	else
	{
		result = ev_nextCard;
		visited = true;
	}
	return result;
}

Event_t func_twoPair(Card currCard, Card prevCard)
{
	//if result matches, you have 3 of a kind as last card
	Event_t result = (currCard.face == prevCard.face) ? ev_matchThreeOfKind:ev_nextCard;
	return result;
}

Event_t func_threeOfKind(Card currCard, Card prevCard)
{
	Event_t result = ev_none;
	static bool visited = false;

	if(prevCard.face == currCard.face)
	{
		//full house if you have visited this state, four of a kind if not
		result = visited ? ev_matchSecondPair:ev_matchFourOfKind;
		visited = false;
	}

	else
	{
		result = ev_nextCard;
		visited = true;
	}
	return result;
}

Event_t func_fourOfKind(Card currCard, Card prevCard)
{
	return ev_nextCard;
}

Event_t func_done(Card currCard, Card prevCard)
{
	return ev_none;
}