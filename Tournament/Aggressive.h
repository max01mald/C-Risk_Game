#pragma once
#include "Strategy.h"
//#include "playerClass.h"
#include "game.h"
#include <iostream>
using namespace std;

//implements the aggressive player

class Aggressive : public Strategy {
public:
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
};