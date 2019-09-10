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
	InvalidFace = -1,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
	Ace
}Face;

typedef enum
{
	InvalidSuit = -1,
	Hearts,
	Diamonds,
	Spades,
	Clubs
}Suit;

// typedef enum
// {
// 	InvalidEnum = -1,
// 	addToFront,
// 	addToMiddle,
// 	addToEnd,
// 	NumEnums
// }dealPosition;

typedef struct Card Card;

struct Card{
	Face face;
	Suit suit;
	Card* nextPtr;
};

typedef struct{
	Card hand[HAND_SIZE];
	Score handScore;
	int handSize;
}Player;




/* function prototypes */
char* getSuitName(Suit suit);
char* getFaceName(Face face);
Card* addCard(char* face, char* suit);
void initializeDeck(Card* myDeck);
void printCards(Card* topCard);
bool isEmpty(Card* topOfDeck);
void dealCard(Card** topOfDeck, Card** hand, int handSize);
void discardCard(Card* bottomOfDeck, Card* hand, int index);
int getFaceValue(char *str);

#endif