#include "functions.h"

// func name: initializeDeck
// Summary: Fills the empty deck array with cards in order
// Params myDeck: empty deck array
// Param myFace[]: array of names of each face type
// Params mySuit[]: array of names of each suit type
void initializeDeck(Card * const myDeck, const char * myFace[], const char * mySuit[])
{
	int i;

	for (i = 0; i <= 51; i++)
	{
		myDeck[i].face = myFace[i % 13];
		myDeck[i].suit = mySuit[i / 13];
	}
}