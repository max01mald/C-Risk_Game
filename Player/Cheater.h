#pragma once
#include "Strategy.h"

#include "game.h"

#include <iostream>
using namespace std;

class Cheater : public Strategy {

//implements cheater user

public:
	//constructors
	Cheater();
	
	//methods
	void reinforce(playerClass *p);
	void attack(playerClass* p, game* g);
	void fortify(playerClass* p, game* g);
	
	
	
	
private:
	
	//helper methods
	
	
	Country& playerCountrySelection(playerClass* actor, game* g);
	Country& chooseDefendingCountry(playerClass* actor, game* g, Country* player);
	std::string type;
};