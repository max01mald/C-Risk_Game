/* Deck.h
* Header file for the class Deck.
* Created on: Sept. 2017 for COMP345-Assignment1.
* Author: Team 11, Javier Fernandez-Rial, Portela ID 40044982
*/
#pragma once

#include <vector>
#include <random>
#include "Card.h"
#include "Hand.h"

using namespace std;


class Deck {

private:

	int size; //the size of the deck. Initially, it must be equal to the number of countries on the map
	vector<Card> cardColl; //a collection of cards, must have an equal share of each type

	void fillCardColl(int numOfCountries); //helping function to fill the vector of cards on the contructor
	
	int random(int a, int b); //helping function to generate a random integer on the range [a,b]

public:

	Deck(int numOfCountries); //contructor that sets the size of the deck to the number of countries
							 //and fills the vector with the right amount of cards of each type	
	Deck(); //default contructor

	bool draw(Hand* h);
	

	int getSize() const {return size;};

	void setSize(int numOfCountries) {size = numOfCountries;};

};