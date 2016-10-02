/**
* @file Project #2
* @author  Michael Rossi <rossisantomauro.m@husky.neu.edu>
* @version 1.0
*
* @section LICENSE
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2 of
* the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details at
* https://www.gnu.org/copyleft/gpl.html
*
*/

#include "node.h"
#include "card.h"
#include "deck.h"
#include <iostream>
#include <time.h>

bool checkSet(card, card, card);
bool checkSetInHand(std::vector<card>&);
void playSet();
void findLargestNonSet();



int main()
{
	srand(time(NULL));
	try {
		std::cout << "CARDS HAVE BEEN DEALT!" << std::endl;
		playSet();
		std::cout << std::endl << std::endl << std::endl;
		findLargestNonSet();
	}
	catch (const std::out_of_range& e)
	{
		std::cout << "EXCEPTION THROWN: OUT OF RANGE";
		exit(0);
	}
	catch (const std::length_error& e)
	{
		std::cout << "EXCEPTION THROWN: VECTOR EITHER EMPTY OR NOT EMPTY";
		exit(0);
	}
}

//! Checks if passed 3 cards make a set
/*!
* \param card A First card
* \param card B Second card
* \param card C Third card
* \return bool True if the 3 cards make a set, false otherwise
*/
bool checkSet(card A, card B, card C) //!< Each if statement checks whether each parameter is all the same or uniquely different
{
	if ((A.getNumber() == B.getNumber() && B.getNumber() == C.getNumber()) || ((A.getNumber() != B.getNumber()) && (B.getNumber() != C.getNumber()) && (A.getNumber() != C.getNumber())))
	{
		if ((A.getSymbol() == B.getSymbol() && B.getSymbol() == C.getSymbol()) || ((A.getSymbol() != B.getSymbol()) && (B.getSymbol() != C.getSymbol()) && (A.getSymbol() != C.getSymbol())))
		{
			if ((A.getShading() == B.getShading() && B.getShading() == C.getShading()) || ((A.getShading() != B.getShading()) && (B.getShading() != C.getShading()) && (A.getShading() != C.getShading())))
			{
				if ((A.getColor() == B.getColor() && B.getColor() == C.getColor()) || ((A.getColor() != B.getColor()) && (B.getColor() != C.getColor()) && (A.getColor() != C.getColor())))
				{
					return true;
				}
			}
		}
	}
	return false;
}

//! Checks if a passed hand (collection of cards) makes a set at all
/*!
* \param vector<card>& hand Vector that contains collection of cards
* \return bool True if any 3 combination of cards in hand makes a set, false otherwise
*/
bool checkSetInHand(std::vector<card> &hand)
{
	for (int i = 0; i < hand.size(); i++)
	{
		for (int j = i + 1; j < hand.size(); j++)
		{
			for (int k = j + 1; k < hand.size(); k++)
			{
				if (checkSet(hand[i], hand[j], hand[k]))
				{
					return true;
				}
			}
		}
	}
	return false;
}

//! Plays a game of Set. Initailizes a deck, shuffles the deck, deals to a hand 12 cards, and outputs how many sets are possible within said hand
void playSet()
{
	deck<card> SetDeck;
	std::vector<card> hand;
	SetDeck.shuffle();
	SetDeck.deal(12, hand);
	int you;
	for (you = 0; you < 12; you++)
		std::cout << hand[you] << std::endl;
	int numOfSets = 0;
	std::cout << std::endl;

	for (int i = 0; i < 12; i++)
	{
		for (int j = i + 1; j < 12; j++)
		{
			for (int k = j + 1; k < 12; k++)
			{
				if (checkSet(hand[i], hand[j], hand[k]))
				{
					//std::cout << "Set: " << hand[i] << "        " << hand[j] << "        " << hand[k] << std::endl;
					std::cout << "Set:    " << hand[i] << std::endl << "        "  << hand[j] << std::endl << "        " << hand[k] << std::endl;
					numOfSets++;
				}
			}
		}
	}

}

//! Finds the largest collection of cards that doesn't make a set and outputs it to console
void findLargestNonSet()
{
	deck<card> SetDeck; //!< Creates a new deck
	std::vector<card> hand; //!< Creates a vector hand, where handsize = full size of the deck (81)
	std::vector<card> NonSets; //!< Vector of cards that don't contain a set collectively
	card temp; //!< Temporary card object
	int i = 0;
	SetDeck.deal(81, hand); //!< Deals the entire deck into vector hand
	NonSets.push_back(hand[0]); //!< Puts the first 2 cards of the deck (hand) onto nonsets
	NonSets.push_back(hand[1]);
	hand.erase(hand.begin()); //!< Removes first 2 cards from the deck (hand)
	hand.erase(hand.begin());
	while (i < hand.size()) //!< Goes through each element in the deck (hand)
	{
		temp = hand[0]; //!< Sets temp equal to the first element in the deck (hand)
		NonSets.push_back(temp); //!< Adds temp onto the back of Nonsets
		if (checkSetInHand(NonSets)) //!< Checks if by adding temp (first element in deck), a set was form.
		{
			NonSets.pop_back(); //!< If a set was formed, removes the just-added card from the nonsets
			hand.erase(hand.begin()); //!< Also erases it from the deck (hand)
		}
		else
		{
			hand.erase(hand.begin()); //!< If no sets were formed, keeps the just-added card in nonsets, but still deletes it from the deck (hand)
		}
	}
	std::cout << "Largest Collection of Cards that don't contain a Set = " << NonSets.size() << std::endl;
	for (int i = 0; i < NonSets.size(); i++)
	{
		std::cout << NonSets[i] << std::endl;
	}

}