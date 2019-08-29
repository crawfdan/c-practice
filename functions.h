#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define DECK_SIZE 52
#define HAND_SIZE 5

typedef enum
{
	InvalidEnum = -1,
	highCard,
	onePair,
	twoPair,
	threeOfKind,
	straight,
	flush,
	fullHouse,
	fourOfKind,
	straightFlush,
	royalFlush,
	NumEnums
}Score;

typedef struct{
	const char *face;
	const char *suit;
	struct Card *nextPtr;
}Card;

typedef Card *DeckPtr;

typedef struct{
	Card hand[5];
	Score handScore;
}Player;




/* function prototypes */
void initializeDeck(Card * const myDeck, const char * myFace[], const char * mySuit[]);
void printDeck(Card * const myDeck);
void shuffleDeck(Card * const myDeck);

#endif