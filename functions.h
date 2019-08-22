#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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
}Card;

typedef struct{
	Card hand[5];
	Score handScore;
}Player;


/* function prototypes */
void initializeDeck(Card * const myDeck, const char * myFace[], const char * mySuit[]);
void printDeck(Card * const myDeck);

#endif