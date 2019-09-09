/*
 * Dice.h
 *
 *  Created on: Sep 24, 2017
 *      Author: Mair
 */

#ifndef DICEFACTORY_H_
#define DICEFACTORY_H_



#include <ctime>
#include <cstdlib>
#include <iostream>
#include <random>
#include "Country.h"
using namespace std;

class DiceFactory
{
public:
	DiceFactory();
	int getNumDiceRolls();
	void userInput();
	

	//getters
	double getDicePercentageArray(int i);
	int getCountArrayElement(int i);
	int getCount();
	int getSize(){return size;};
	
	//setters
	void setArraySize(int numSize);
	void setNumDiceRolls(int numOfRolls);

	void dicePercentage(int diceValue);
	void displayAllIndividualPercentages();

	//returns the index position of the country attacking player selected
	int playerCountrySelection();

	int chooseDefendingCountry(DiceFactory& def);

	//atacking player rolls dice
	void attackPhase(DiceFactory &d1);

	//defending player rolls dice
	void rollDicesDefendingPlayer(DiceFactory &d1, int pos);

	//compare dice value to determine winner
	void compareDiceRolls(DiceFactory &p2, int pos1, int pos2);

	void setCount(int count) {
		this->count = count;
	}

	const int* getCountArray() const {
		return countArray;
	}

	const double* getDiceValuePercentage() const {
		return diceValuePercentage;
	}

	void setSize(int size) {
		this->size = size;
	}

	vector<int>& getV() {
		return v;
	}

	void setV(vector<int>& v) {
		this->v = v;
	}

	int getNumArmies() const {
		return numArmies;
	}

	void setNumArmies(int numArmies) {
		this->numArmies = numArmies;
	}

	vector<Country>& getPlayersCountries() {
		return playersCountries;
	}

	void setPlayersCountries(vector<Country>& playersCountries) {
		this->playersCountries = playersCountries;
	}

private:
	int numDiceRolls;
	double diceValuePercentage[6];
	int count;
	//these array will keep track to the percentage of each respective dice roll
		/*
		 * The element of the following array corresponds to the count of each dice roll
		 * 0 reprensents 1 value
		 * 1 represent 2 value rolled
		 * 2 is 3 value rolled and so on
		 */
	int countArray[6];
	int size;
	
	//has a reference to the list of countries belonging to the player
	vector<Country> playersCountries;

	int numArmies;
	vector<int> v;

	int random(int a, int b); //helping function to generate a random integer on the range [a,b]


};



#endif /* DICEFACTORY_H_ */
