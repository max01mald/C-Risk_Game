/*
 * playerClass.h
 *
 *  Created on: Sep 27, 2017
 *      Author: Federico
 */

#ifndef PLAYERCLASS_H_
#define PLAYERCLASS_H_

#include "Hand.h"
#include "DiceFactory.h"
#include "filler.h"
#include "Map.h"
#include "Strategy.h"


using namespace std;

class playerClass
{

private:
	
	Strategy *strategy;
	std::string playerName;
	int playerUnits;
	int playerOrder;
	DiceFactory playerDiceFactory;
	Hand playerHand;
	vector<Country> countries;
	vector<Continent> continents;
	bool haveDrawn = false;


	//helping methods
	int getArmies();
	void placeArmies(int armies);

public:

	//Constructors
	playerClass();
	playerClass(Strategy* strat, string name, int unit, int order);
	playerClass(std::string new_name);
	playerClass(std::string new_name, int units);
	playerClass(std::string new_name, int units, int order);
	playerClass(int units, int order);
	playerClass(vector <Country> cntry, vector<Continent> cont, Hand hand);
	playerClass(playerClass* pc);
	
	playerClass& operator=(playerClass &pc);

	~playerClass();
	//Setters
	void setStrategy(Strategy* strat);
	void setPlayerName(string name);
	void setPlayerUnits(int units);
	void setPlayerOrder(int order);
	void setCountries(vector<Country> cntry);
	void setContinents(vector<Continent> cntnent);
	void setPlayerHand(Hand hand);
	void setHaveDrawn(bool b) {
		haveDrawn = b;
	};
	void setConti(Continent conti) { continents.push_back(conti); };

	//Getters
	std::string getPlayerName();
	int getPlayerCountriesSize(){return countries.size();};
	int& getPlayerUnits();
	int getPlayerOrder();
	Hand* getPlayerHand();
	DiceFactory& getPlayerDiceFactory(){return playerDiceFactory;};
	vector<Country>& getCountries();
	vector<Continent>& getContinents();
	int getNumOfCountries() {return countries.size();};
	bool getHaveDrawn() { return haveDrawn; };

	//Methods
	
	void reinforceStrat() {
		return this->strategy->reinforce(this);
	}
	void attackStrat(game* g) {
		return this->strategy->attack(this, g);
	}
	void fortifyStrat(game* g) {
		return this->strategy->fortify(this, g);
	}
	
	void FillOwned(Map& map);
	
	void printCountries();
	void changeOwner(int pos);
	
	void addCountry(Country cntry, int pos);
	int playerHandSize();
	
	void hasContinent(Map map);
};

#endif /* PLAYERCLASS_H_ */
