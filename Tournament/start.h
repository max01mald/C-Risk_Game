/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 2 due 26 October 2017
*/

#ifndef START_H
#define START_H

#include "Map.h"
#include "file.h"
#include "playerClass.h"
#include "Deck.h"
#include "Human.h"
#include "Aggressive.h"
#include "Benevolent.h"
#include "Cheater.h"
#include "Random.h"


using namespace std;

class start{

	public:
		//Constructors
		start();
		start(std::string name);
		
		//getters
		std::string getFile(std::string name);
		std::string getFile(int number);
		playerClass& getPlayer(std::string name);
		playerClass& getPlayer(int i){return cast[i];};
		int getVecSize(){return cast.size();};
		
		//setters
		void setFile(std::string New_name);
		void setCast(int unit, int order, string name);
		void setCast(int unit, int order, string name, string type);
		void OrderCast();
		
		//Methods
		void PlayerSelection();
		void PlayerSelection(int pos);
		void displayFolder();
		Map MapStartUp();
		Map MapStartUp(int pos);
		start PlayerStartUp();
		start PlayerStartUp(int pos);
	
	private:
		string name;
		vector<file> folder;
		vector<playerClass> cast;



};



#endif