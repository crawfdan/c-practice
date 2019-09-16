#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define DECK_SIZE 52
#define HAND_SIZE 5

#define SCORE_SIZE 2

typedef enum
{
	invalidScore = -1,
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
	NumScores
}Score;

typedef enum
{
	invalidFace = -1,
	two,
	three,
	four,
	five,
	six,
	seven,
	eight,
	nine,
	ten,
	jack,
	queen,
	king,
	ace,
	numFaces
}Face;

typedef enum
{
	invalidSuit = -1,
	hearts,
	diamonds,
	spades,
	clubs,
	numSuits
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
	//Score stores a tuple; one for the score and one for highest card
	Score handScore;
	Face highCard;
	int handSize;
}Player;




/* function prototypes */
Card* initializePlayer(Player** player);
const char* getSuitName(Suit suit);
const char* getFaceName(Face face);
Card* addCard(char* face, char* suit);
void initializeDeck(Card* myDeck, Card** bottomOfDeck);
void printCards(Card* topCard);
bool dealCard(Card** topOfDeck, Card** hand, int handSize);
bool discardCard(Card** bottomOfDeck, Card** hand, int index, int handSize);
int getFaceValue(char *str);
void setHandScore(Player** player);
Score checkFlushOrStraight(Player* player);
#endif