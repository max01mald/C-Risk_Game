#pragma once
#include "Strategy.h"
#include "game.h"
#include <iostream>

using namespace std;

class Random : public Strategy {

//implements random user

public:
	//constructors
	Random();
	
	//methods
	void reinforce(playerClass *p);
	void attack(playerClass* p, game* g);
	void fortify(playerClass* p, game* g);
	
	
	
	
private:
	
	//helper methods
	int getArmies(playerClass *p);
	void placeArmies(int armies, playerClass* p);
	
	Country& playerCountrySelection(playerClass* actor, game* g, Country &stop);
	Country& chooseDefendingCountry(playerClass* actor, game* g, Country* player, Country &stop);
	void compareDiceRolls(playerClass* actor, game* g, playerClass& villan, Country* player1, Country* player2);
	void rollDicesDefendingPlayer(playerClass* villan, Country* cntry);
	std::string type;

	int random(int a, int b);
};