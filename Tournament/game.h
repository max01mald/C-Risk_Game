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
		Deck* getDeck() { return &deck; };

		//Setters
		void setDeck(int size) {
			Deck d(size);
			deck = d;
		};


		//Methods
		void RandomCountries(Map& map);
		void OrderCountries(Map& map);
		void DistributeCountries(Map& map);
		void AllocateCountries(Map& map);
		void Linker();

		string MainGame(Map board, int N_D);



	private:
	string name;
	vector<playerClass> playing_cast;
	Deck deck;


};

#endif
