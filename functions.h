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

typedef enum {
	st_highCard,
	st_onePair,
	st_twoPair,
	st_threeOfKind,
	st_straight,
	st_flush,
	st_fullHouse,
	st_fourOfKind,
	st_straightFlush,
	st_royalFlush,
	num_states
} State_t;

typedef enum {
	ev_none,
	ev_nextCard,
	ev_matchPair,
	ev_matchSecondPair,
	ev_matchThreeOfKind,
	ev_matchFourOfKind,
	ev_matchStraight,
	ev_matchFlush,
	ev_matchStraightFlush,
	ev_matchRoyalFlush
} Event_t;

typedef struct {
	State_t currentState;
	Event_t event;
	State_t nextState;
} stateTransMatrixRow_t;

static stateTransMatrixRow_t stateTransMatrix[] = {
	// CURR STATE		// EVENT					// NEXT STATE
	{st_highCard,	   ev_matchPair,				st_onePair },
	{st_onePair,	   ev_matchThreeOfKind, 		st_threeOfKind},
	{st_threeOfKind,   ev_matchFourOfKind, 			st_fourOfKind},
	{st_threeOfKind,   ev_matchSecondPair, 			st_fullHouse},
	{st_onePair, 	   ev_matchSecondPair, 			st_twoPair},
	{st_twoPair, 	   ev_matchThreeOfKind, 		st_fullHouse},
	{st_highCard, 	   ev_matchStraight, 			st_straight},
	{st_highCard, 	   ev_matchFlush, 				st_flush},
	{st_highCard, 	   ev_matchStraightFlush, 		st_straightFlush},
	{st_highCard,	   ev_matchRoyalFlush, 			st_royalFlush},
	{st_highCard,	   ev_nextCard,					st_highCard},
	{st_onePair,	   ev_nextCard,					st_onePair},
	{st_threeOfKind,   ev_nextCard,					st_threeOfKind},
	{st_twoPair,	   ev_nextCard,					st_twoPair},
	{st_fourOfKind,	   ev_nextCard,					st_fourOfKind}
};

typedef struct {
	const char* name;
	Event_t (*func)(Card, Card);
} stateFunctionRow_t;



typedef struct {

	State_t currState;

} stateMachine_t;

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
Event_t func_highCard(Card currCard, Card prevCard);
Event_t func_onePair(Card currCard, Card prevCard);
Event_t func_twoPair(Card currCard, Card prevCard);
Event_t func_threeOfKind(Card currCard, Card prevCard);
Event_t func_fourOfKind(Card currCard, Card prevCard);
Event_t func_done(Card currCard, Card prevCard);

static stateFunctionRow_t stateFunction[] = {
	//NAME					//FUNC
	{"st_highCard",			&func_highCard},
	{"st_onePair",			&func_onePair},
	{"st_twoPair",			&func_twoPair},
	{"st_threeOfKind",		&func_threeOfKind},
	{"st_straight",			&func_done},
	{"st_flush",			&func_done},
	{"st_fullHouse",		&func_done},
	{"st_fourOfKind",		&func_fourOfKind},
	{"st_straightFlush",	&func_done},	
	{"st_royalFlush",		&func_done},
	{NULL,					NULL}
};


#endif