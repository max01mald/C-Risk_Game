#pragma once
class playerClass;
class game;
class start;

class Strategy {

//abstract for Aggressive, Benevolent, Human Strategies

public:
	virtual void reinforce(playerClass* p);
	virtual void attack(playerClass* p, game* g);
	virtual void fortify(playerClass* p, game* g);
};