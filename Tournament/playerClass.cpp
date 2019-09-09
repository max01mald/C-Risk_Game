/*
* playerClass.cpp
*
*  Created on: Sep 27, 2017
*      Author: DianaFede
*/

#include <iostream>
#include "playerClass.h"


using namespace std;



// TODO Auto-generated constructor stub




//Constructors

playerClass::playerClass()
{
	playerName = "";
	playerUnits = 0;
	playerOrder = 0;
	Hand playerHand;
	DiceFactory playerDiceFactory;
	vector<Country> countries;
	vector<Continent> continents;

}

playerClass::playerClass(Strategy* strat,string name,int unit,int order)
{
	this->strategy = strat;
	playerName = name;
	playerUnits = unit;
	playerOrder = order;
}

playerClass::playerClass(std::string new_name)
{
	this->strategy = NULL;
	playerName = new_name;
	playerUnits = 0;
	playerOrder = 0;
	Hand playerHand;
	DiceFactory playerDiceFactory;
	vector<Country> countries;
	vector<Continent> continents;
}

playerClass::playerClass(std::string new_name, int units)
{
	this->strategy = NULL;
	playerName = new_name;
	playerUnits = units;
	playerOrder = 0;
	Hand playerHand;
	DiceFactory playerDiceFactory;
	vector<Country> countries;
	vector<Continent> continents;
}

playerClass::playerClass(std::string new_name, int units, int order)
{
	this->strategy = NULL;
	playerName = new_name;
	playerUnits = units;
	playerOrder = order;
	Hand playerHand;
	DiceFactory playerDiceFactory;
	vector<Country> countries;
	vector<Continent> continents;
}

playerClass::playerClass(int unit, int order)
{
	this->strategy = NULL;
	playerName = "";
	playerUnits = unit;
	playerOrder = order;
	Hand playerHand;
	DiceFactory playerDiceFactory;
	vector<Country> countries;
	vector<Continent> continents;
}

playerClass::playerClass(vector<Country> cntry, vector<Continent> cont, Hand hand)
{
	this->strategy = NULL;
	playerName = "";
	playerUnits = 0;
	playerOrder = 0;
	playerHand = hand;
	DiceFactory playerDiceFactory;
	countries = cntry;
	continents = cont;

}


playerClass::playerClass(playerClass* pc)
{
	this->strategy = pc->strategy;
	playerName = pc->playerName;
	playerUnits = pc->playerUnits;
	playerOrder = pc->playerOrder;
	playerHand = pc->playerHand;
	playerDiceFactory = pc->playerDiceFactory;
	countries = pc->countries;
	continents = pc->continents;


}

playerClass& playerClass::operator=(playerClass &pc)
{
	
	this->strategy = pc.strategy;
	this->playerName = pc.playerName;
	this->playerUnits = pc.playerUnits;
	this->playerOrder = pc.playerOrder;
	this->playerHand = pc.playerHand;
	this->playerDiceFactory = pc.playerDiceFactory;
	this->countries = pc.countries;
	this->continents = pc.continents;
	
	return *this;
}


playerClass::~playerClass()
{
	//delete strategy;
}



//Setters

void playerClass::setStrategy(Strategy* strat)
{
	this->strategy = strat;
}

void playerClass::setPlayerName(string name)
{
		playerName= name;
}

void playerClass::setPlayerUnits(int unit)
{
	playerUnits = unit;
}

void playerClass::setPlayerOrder(int order)
{
	playerOrder = order;
}

void playerClass::setCountries(vector<Country> cntry)
{
	countries = cntry;
}

void playerClass::setContinents(vector <Continent> conti)
{
	continents = conti;
}

void playerClass::setPlayerHand(Hand hand)
{
	playerHand = hand;
}


//Getters
std::string playerClass::getPlayerName()
{
	return playerName;
}

int& playerClass::getPlayerUnits()
{
	return playerUnits;
}

int playerClass::getPlayerOrder()
{
	return playerOrder;
}

Hand* playerClass::getPlayerHand()
{
	return &playerHand;
}

vector<Country>& playerClass::getCountries()
{
	return countries;
}

vector<Continent>& playerClass::getContinents()
{
	return continents;
}

//Methods


void playerClass::FillOwned(Map& map)
{
	countries.clear();
	
	for (int i=0; i< map.getAmountCountries(); i++)
	{
		if (map.getCountries()[i].getowner() == this->getPlayerName())
		{	
			
			this->countries.push_back(map.getCountries()[i]);
			
		}
	}

}





void playerClass::changeOwner(int pos)
{
	countries[pos].setowner(getPlayerName());
}

void playerClass::addCountry(Country cntry, int pos)
{
	countries.push_back(cntry);
}

void playerClass::printCountries()
{
	for (int i=0; i<getPlayerCountriesSize(); i++)
	{
		cout << countries[i].getname() << endl;
	}
}




//Method from Hand Object
int playerClass::playerHandSize()
{
	return playerHand.getSize();
}

void playerClass::hasContinent(Map map)
{
	int counter = 0;

	vector<Continent> conti;

	conti = map.getContinents();



	for (int i = 0; i< conti.size(); i++)
	{

		for (int k = 0; k<this->getCountries().size(); k++)
		{
			//cout << conti[i].getname() << endl;
			if (conti[i].getname().compare(this->getCountries()[k].getcontinent()))
			{
				counter += 1;

				if (counter == conti[i].getamount())
				{
					this->setConti(conti[i]);
				}
			}
		}
		counter = 0;
	}

	for (int i = 0; i<continents.size(); i++)
	{
		for (int j = i + 1; j<continents.size(); j++)
		{
			if (continents[i].getname() == continents[j].getname())
			{
				continents.erase(continents.begin() + j);
			}
		}

	}

	/*cout << "size " << continents.size() << endl;
	for (int i = 0; i<continents.size(); i++)
	{
		cout << this->continents[i].getname() << endl;
	}*/

}