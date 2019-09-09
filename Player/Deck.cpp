/* Deck.cpp
* Source file for the class Deck.
* Created on: Sept. 2017 for COMP345-Assignment1.
* Author: Team 11, Javier Fernandez-Rial, Portela ID 40044982
*/

#include "Deck.h"
#include <iostream>



Deck::Deck() {

	size = 0;
	cardColl;
}

Deck::Deck(int numOfCountries) {

	size = numOfCountries;
	cardColl;
	fillCardColl(numOfCountries);
}

void Deck::fillCardColl(int size) {

	int numOfEach = size / 3; //number of cards of each type, a third of the total.

	//These loop fills cardColl with 1 card of a particular type on every iteration
	for (int i = 0; i <= numOfEach - 1; i++) {
		cardColl.push_back(Card(INFANTRY));
		cardColl.push_back(Card(CAVALRY));
		cardColl.push_back(Card(ARTILLERY));
	}

	int extra = size % 3; //if size is divisible by 3 then the share is equal and we are done
	if (extra == 1) cardColl.push_back(Card(INFANTRY)); //if the modulo is 1 we add one extra card of type INFANTRY
	if (extra == 2) {
		cardColl.push_back(Card(INFANTRY)); //if the modulo is 2, we add two extra cards, 
		cardColl.push_back(Card(CAVALRY));  //one of type INFANTRY and one of type CAVALRY
	}
}

/*int Deck::random(int a, int b) {
	thread_local std::mt19937 eng{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(a, b);
	return dist(eng);
}*/

/*bool Deck::draw(Hand* h) {  //Removes a card from the deck and destroys it after adding its value to the hand object

	if (size > 0) {

		int index = random(0, size - 1); //to choose a random card from the remaining cards of the deck

		Card c = cardColl.at(index); //we store a copy of the chosen card on the variable c

		if (c.getType() == INFANTRY) h->setNumOfInf(h->getNumOfInf() + 1); //We increase by one the right type
		else if (c.getType() == CAVALRY) h->setNumOfCav(h->getNumOfCav() + 1); //of instance variable from the 
		else h->setNumOfArt(h->getNumOfArt() + 1);							// hand object passed by pointer

		h->setSize(h->getSize() + 1); //We increase the size of the hand by 1.
		
		cardColl.erase(cardColl.begin() + index); //we erase the card from the deck

		size -= 1; //and reduce the deck's size by one

		return true; //if successful
	}

	else {

		cout << "The deck is empty" << endl;
		return false; //when there are no more cards

	}

}*/