#pragma once
#include "Strategy.h"
#include "game.h"
#include <iostream>
using namespace std;

//implements behaviour for benevolent user
class Benevolent : public Strategy {
public:
	//methods 
	void reinforce(playerClass *p);
	void attack(playerClass* p, game* g);
	void fortify(playerClass* p, game* g);
private:
	//helper methods
	int getArmies(playerClass *p);
	void placeArmies(int armies, playerClass* p);
};