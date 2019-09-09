#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define DECK_SIZE 52
#define HAND_SIZE 5

#define NUM_FACES 13
#define NUM_SUITS 4

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

typedef enum
{
	InvalidEnum = -1,
	addToFront,
	addToMiddle,
	addToEnd,
	NumEnums
}dealPosition;

typedef struct Card Card;

struct Card{
	char *face;
	char *suit;
	Card* nextPtr;
};

typedef struct{
	Card hand[HAND_SIZE];
	Score handScore;
	int handSize;
}Player;




/* function prototypes */
void initializeDeck(Card* myDeck, char* faceNames[], char* suitNames[]);
void printCards(Card* topCard);
bool isEmpty(Card* topOfDeck);
void dealCard(Card** topOfDeck, Card** hand, int handSize);
void discardCard(Card* bottomOfDeck, Card* hand, int index);
int getFaceValue(char *str);

#endif