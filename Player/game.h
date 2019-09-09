/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 2 due 26 October 2017
*/

#ifndef GAME_H
# define GAME_H


#include "start.h"
using namespace std;

class game
{
	public:
		//Constructors
		game();
		game(std::string New_name, start match);
		
		game& operator =(const game &risk);
		
		//Getters
		playerClass& getPlayer(int i){return playing_cast[i];};
		int getCastSize();
		string getName(){return name;};
		
		//Methods
		void RandomCountries(Map& map);
		void OrderCountries(Map& map);
		void DistributeCountries(Map& map);
		void AllocateCountries(Map& map);
		void Linker();
		void attack(playerClass& actor);
		Country& playerCountrySelection(playerClass& actor);
		Country& chooseDefendingCountry(playerClass& actor, Country* player);
		void compareDiceRolls(playerClass& actor, playerClass& villan, Country* player1, Country* player2);
		string MainGame(Map board, int N_D);
		
		
		
	private:
	string name;
	vector<playerClass> playing_cast;
	

};

#endif