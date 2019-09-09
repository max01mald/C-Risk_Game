/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 2 due 26 October 2017
*/

#include "game.h"

//Constructors
game::game(): name("Noone")
{
	vector<playerClass> playing_cast;
}

game::game(std::string New_name, start match): name(New_name)
{
	vector<playerClass> playing_cast;

	for(int i=0; i<match.getVecSize(); i++)
	{
		this->playing_cast.push_back(match.getPlayer(i));
	}


}

game& game::operator =(const game &risk)
{
	name = risk.name;

	playing_cast = risk.playing_cast;

	return *this;
}

//Getters
int game::getCastSize()
{
	int temp =0;

	temp = this->playing_cast.size();

	return temp;

}


void game::RandomCountries(Map& map)
{
	for (int i=0; i< map.getAmountCountries(); i++)
	{
		if(map.getCountries()[i].getname() != "")
		{
			map.getCountries()[i].setNumOrder(rand() % 1000);
		}
	}

}

void game::OrderCountries(Map& map)
{

	Country temp;

	for (int i=0; i < map.getAmountCountries()-1; i++)
	{
		for (int j= 1; j < map.getAmountCountries(); j++)
		{
			if(map.getCountries()[i].getNumOrder() < map.getCountries()[j].getNumOrder())
			{
				temp = map.getCountries()[i];
				map.getCountries()[i] = map.getCountries()[j];
				map.getCountries()[j] = temp;
			}

		}
	}

}

void game::DistributeCountries(Map& map)
{
	int playCounter = 0;


	RandomCountries(map);
	OrderCountries(map);


	for (int i = 0; i < map.getAmountCountries(); i++)
	{
		if (playCounter >= this->getCastSize())
		{
			playCounter = 0;
		}

		if(map.getCountries()[i].getname() != "")
		{
			map.getCountries()[i].setowner(this->getPlayer(playCounter).getPlayerName());
			map.getCountries()[i].setNumUnits(map.getCountries()[i].getNumUnits() + 1);
			this->getPlayer(playCounter).setPlayerUnits(this->getPlayer(playCounter).getPlayerUnits() - 1);

			playCounter++;
		}
	}

	cout << "..." << endl;
	cout << "Countries have been assigned at random." << endl;
	cout << endl;

}

void game::AllocateCountries(Map& map)
{
	DistributeCountries(map);

	for (int i=0; i<this->getCastSize(); i++)
	{
		this->getPlayer(i).FillOwned(map);
	}


	int playCounter = 0;
	int sum = 0;

	string stringInput = "";

	while (this->getPlayer(this->getCastSize()-1).getPlayerUnits() > 0)
	{
		int disp = this->getPlayer(this->getCastSize()-1).getPlayerUnits();

		cout << "there are " << disp << " Units left" << endl;

		if (playCounter > this->getCastSize()-1)
		{
			playCounter = 0;
		}

		cout << this->getPlayer(playCounter).getPlayerName() << "" << endl;


		int count = 1;

		this->getPlayer(playCounter).printCountries();

		cout << endl;

		bool test = false;
		while (test == false)
		{
			sum = 0;

			int temp = rand() % this->getPlayer(playCounter).getPlayerCountriesSize();

			for (int i = 0; i < this->getPlayer(playCounter).getPlayerCountriesSize(); i++)
			{
				if (this->getPlayer(playCounter).getCountries()[i].getname() == this->getPlayer(playCounter).getCountries()[temp].getname()) //stringInput
				{

					this->getPlayer(playCounter).getCountries()[i].setNumUnits(this->getPlayer(playCounter).getCountries()[i].getNumUnits() + 1);
					this->getPlayer(playCounter).setPlayerUnits(this->getPlayer(playCounter).getPlayerUnits() - 1);



					test = true;
					sum = 2;

					cout << this->getPlayer(playCounter).getCountries()[i].getname() << " has a new unit." << endl;
					cout << this->getPlayer(playCounter).getCountries()[i].getname() << " has " << this->getPlayer(playCounter).getCountries()[i].getNumUnits() << " units." << endl;
					cout << endl;

					playCounter++;
					break;
				}
			} //end for loop


			if (sum <= 0)
			{
			cout << "\nCountry not found, please enter the name of the country to which you wish to add a unit\n" << endl;

			for (int i = 0; i < this->getPlayer(playCounter).getPlayerCountriesSize(); i++)
			{
				if (this->getPlayer(playCounter).getCountries()[i].getowner() == this->getPlayer(playCounter).getPlayerName())
				{
					cout << this->getPlayer(playCounter).getCountries()[i].getname() << endl;
				}
			}
			cin >> stringInput;
			}

		} //end second while loop



	} //end first while loop


}

void game::Linker()
{
	for(int i=0; i<this->getCastSize(); i++)
		{
			for(int l=0; l<this->getCastSize(); l++)
			{
				for(int j=0; j<this->getPlayer(i).getCountries().size(); j++)
				{
					for(int k=0; k< this->getPlayer(i).getCountries()[j].getN_vec().size(); k++)
					{
						if(this->getPlayer(i).getCountries()[j].getN_vec()[k] == this->getPlayer(l).getCountries()[j].getname())
						{
							this->getPlayer(i).getCountries()[j].setN(k, this->getPlayer(l).getCountries()[j]);

						}

					}

				}
			}

		}

}

//Methods



string game::MainGame(Map board, int N_D)
{
	int round = 0;
	int number = 0;
	int exit1 = 0;
	int exit2 =0;
	int battle = 0;
	int reinforce = 0;
	int attack = 0;
	int fortify = 0;

	this->setDeck(board.getAmountCountries());

	playerClass* winner;
	playerClass* temp;



	while (exit1 != -1)
	{
		if(round != N_D)
		{
			for (int i = 0; i<getCastSize(); i++)
			{

				temp = &this->getPlayer(i);

				if (temp->getCountries().size() != 0) {


					exit2 = 0;
					battle = 0;

					temp->reinforceStrat();


					cout << "about to attack" << endl;
					temp->attackStrat(this);

					temp->hasContinent(board);

					//checks if the player has the full map worth of countires
					if (temp->getPlayerCountriesSize() == board.getAmountCountries())
					{
						winner = temp;
						exit1 = -1;
						break;
					}


					temp->fortifyStrat(this);


					if (!(i == getCastSize() - 1))
					{
						cout << "Next Players Turn!" << endl;
					}


				}
			}
		}
		else
		{
			return "DRAW";
		}
	}
	//declares winner
	return winner->getPlayerName();

}
