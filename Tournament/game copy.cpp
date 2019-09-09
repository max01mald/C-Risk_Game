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
		cout << "\nPlease choose a country to which you wish to add a unit: " << endl;
		//cin >> stringInput;

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

	void game::attack(playerClass* actor)
	{
		
		
		int p1count = 0;
		int temp =0;
		string answer = "";

		Country* player1 = new Country("");
		Country* player2 = new Country("");
		
		
			cout << "Do you wish to attack? yes/no" << endl;
			cin >> answer;

			if(answer != "no")
			{
				cout << endl;
				while(answer != "no")
				{
					
					
					player1 = &playerCountrySelection(actor);
					
					cout<<"selecting defending country" <<endl;
					player2 = &chooseDefendingCountry(actor, player1);
				
			
					cout << player2->getname() <<endl;
				
					cout << "\n \t\t ATTACKING PLAYER DICE ROLL \n" << endl;
					
					actor.getPlayerDiceFactory().getV().clear();
					
					while(actor.getPlayerDiceFactory().getNumDiceRolls() < 1 || actor.getPlayerDiceFactory().getNumDiceRolls() > 3)
					{
						cout << "From 1-" << 3 << " , enter amount of dice rolls to put: " << endl;
						cout << player1->getname() << " has " << player1->getNumUnits()-1 << " available units"<<endl; 
						cin >> temp;
						actor.getPlayerDiceFactory().setNumDiceRolls(temp);
						if(actor.getPlayerDiceFactory().getNumDiceRolls() < 1 || actor.getPlayerDiceFactory().getNumDiceRolls() > 3)
							cerr << "The number you entered is invalid and must be 1 - 3 inclusive." << endl;
					}

					//temporary variable that holds count of available dice rolls
					p1count = actor.getPlayerDiceFactory().getNumDiceRolls();

					//checks that user selected valid number of dice rolls for attacking country
					while(p1count > player1->getNumUnits()-1 || p1count < 0)
					{
						cerr << "Sorry, your dice rolls cannot exceed your number of armies for " << player1->getname()  << " which is " << player1->getNumUnits()-1 << ". \nEnter new number: " << endl;
						cin >> p1count;
					}
				
					int size = 0;
				
					//set size to numDiceRolls, represents the array size
					size = actor.getPlayerDiceFactory().getNumDiceRolls();

					//set numDiceRolls to validated dice roll
					actor.getPlayerDiceFactory().setNumDiceRolls(p1count);

					actor.getPlayerDiceFactory().dicePercentage(actor.getPlayerDiceFactory().getNumDiceRolls());

					//this method keeps track of the percentage of all individual values rolled up to now
					actor.getPlayerDiceFactory().displayAllIndividualPercentages();

					//display all values rolled during this sequence
					cout << endl;

					temp = 0;
					//sort array from largest to smallest
					for(int i = 0; i < actor.getPlayerDiceFactory().getNumDiceRolls(); i++)
					{
						for(int j = i+1; j < actor.getPlayerDiceFactory().getNumDiceRolls(); j++)
						{
							if(actor.getPlayerDiceFactory().getV()[i] < actor.getPlayerDiceFactory().getV()[j])
							{
								temp = actor.getPlayerDiceFactory().getV()[j];
								actor.getPlayerDiceFactory().getV()[j] = actor.getPlayerDiceFactory().getV()[i];
								actor.getPlayerDiceFactory().getV()[i] = temp;
							}
						}
					}
				
					playerClass* villan = new playerClass("",0,0);
				
					for (int i=0; i< this->getCastSize(); i++)
					{
						if(player2->getowner() == this->getPlayer(i).getPlayerName())
						{
							villan = &this->getPlayer(i);
				
						}
					
					}
				
				

					cout << "Values stored in the container" << endl;
					for(int i=0; i < p1count; i++)
						cout << actor.getPlayerDiceFactory().getV()[i] << endl;

					//rol dice for defending player
					actor.rollDicesDefendingPlayer(villan, player2);
				
					playerClass villan2(villan);
				
					//compare values of dices to determine winner
					this->compareDiceRolls(actor, villan2, player1, player2);
				
					//reset to 0
					actor.getPlayerDiceFactory().setNumDiceRolls(0);

					cout << endl;
					cout << "Do you want to roll again: ";
					cin >> answer;
				
					
				
				}// end of while loop
			}
		
	}
	
	Country& game::playerCountrySelection(playerClass& actor)
	{

		int choice;
		int counter; 
		int break1;
		int break2;
		cout << endl;
		
		break1 = 0;
		
		
		Country* arr = new Country[actor.getCountries().size()];
		string* arr2 = new string[actor.getCountries().size()];
		Country* arr3 = new Country[actor.getCountries().size()];
		
		while(break1 != -1)
		{	
			break2 = 0;
			
			while(break2 != -1)
			{
				counter = 1;
			
				cout << "Please select your country to attack with from your Countries: " << endl;
				
				
				for(int l=0; l < actor.getCountries().size(); l++)
				{
					for(int k=0; k< actor.getCountries()[l].getN_vec().size(); k++)
					{
						for(int i=0; i < this->getCastSize(); i++)
						{	
							if(actor.getPlayerName() != this->getPlayer(i).getPlayerName())
							{
								for(int j=0; j< this->getPlayer(i).getPlayerCountriesSize(); j++)
								{
								
									if(actor.getCountries()[l].getN_vec()[k] == this->getPlayer(i).getCountries()[j].getname())
									{
										if(actor.getCountries()[l].getNumUnits() > 1)
										{
											if(actor.getPlayerName() != this->getPlayer(i).getCountries()[j].getowner())
											{	
												if(l == 0)
												{
													arr2[l] = actor.getCountries()[l].getname();
													arr[l] = actor.getCountries()[l];
													counter++;
										
												}
												else if(arr2[l-1] != actor.getCountries()[l].getname())
												{													
													arr2[l] = actor.getCountries()[l].getname();
													arr[l] = actor.getCountries()[l];
													counter++;
			
												}
											}	
										}
									}
								}
							}	
						}	
					}
				}	
				
				counter = 1;
				int temp =0;
				for(int i=0; i<actor.getCountries().size(); i++)
				{
					
					if(arr[i].getname() != "")
					{
						arr3[temp] = arr[i];
						temp += 1;
					
					}
				}
				
				for(int i=0; i<	actor.getCountries().size(); i++)
				{
					if(arr3[i].getname() != "")
					{
						cout << counter << " " << arr3[i].getname() << endl;
								
						counter++;
					}
				}
				
				
				cout << "Whats your choice: ";
				cin >> choice;
				cout << endl;
			
				cout << choice << " <- choice counter-> " << counter << endl;
				if(choice <= counter)
				{	
					cout << "hello" << endl;
					break2 = -1;
				}
			}
			
			counter = 0;
			break2 = 0;
			
			/*while(break2 != -1)
			{
				if(choice > actor.getPlayerCountriesSize())
				{
					cerr << "\n Sorry not a valid choice, exceeded bounds of your list" <<endl;
					cerr << "Enter new option" << endl;

					cout << "Please select your country to attack with from your Countries: " << endl;
					for(int i=0; i < actor.getPlayerCountriesSize(); i++)
						cout << i+1 << " " << actor.getCountries()[i].getname() << endl;

					cout << "Whats your choice: ";	
					cin >> choice;
				}
				else
				{
					break2 = -1;
				}
			}
			
			
			break2 =0;
			
			while(break2 != -1)
			{
				if(actor.getCountries()[choice-1].getNumUnits() < 2)
				{
					cerr << "Sorry your country must have at least 2 armies to attack with" << endl;
					cout << actor.getCountries()[choice-1].getname() << " only has " << actor.getCountries()[choice-1].getNumUnits() << endl;
					cout << " Please enter new choice: " << endl;

					for(int i=0; i < actor.getPlayerCountriesSize(); i++)
						cout << i+1 << " " << actor.getCountries()[i].getname() << endl;

					cin >> choice;
					cout << endl;
				}
				else
				{
					break2 = -1;
				}
			}
			
			for(int i=0; i < this->getCastSize(); i++)
			{	
				for(int j=0; j< this->getPlayer(i).getPlayerCountriesSize(); j++)
				{
					for(int k=0; k< actor.getCountries()[choice-1].getN_vec().size(); k++)
					{
						if(actor.getCountries()[choice-1].getN_vec()[k] == this->getPlayer(i).getCountries()[j].getname())
						{
							if(actor.getPlayerName() != this->getPlayer(i).getCountries()[j].getowner())
							{
								
								counter += 1;
							}
						}
					}
				}
			}		
			
			if(counter != 0)
			{
				break1 = -1;
			
			}
			else
			{
				cout << "Please select another country to Attack from" << endl;
			}
			*/
			break1 = -1;
			
		}
		
		int temp2 = 0;
		
		for(int i=0; i<actor.getCountries().size(); i++)
		{
			if(arr3[choice-1].getname() == actor.getCountries()[i].getname())
			{
				temp2 = i;
			}
		
		}
		
		
		
		return actor.getCountries()[temp2];
	}

	Country& game::chooseDefendingCountry(playerClass& actor, Country* player)
	{
		int choice;
		int counter = 1;
		int temp =0;
		int break1 =0;
		vector<string> store;
		
		cout << "\nHere is the list of viable targets, Please select one of them: " << endl;
		
		int** arr = new int*[50];
		for(int i=0; i<50; i++)
		{
			arr[i] = new int[3];
		}
		
		
		for(int i=0; i < this->getCastSize(); i++)
		{	
			for(int j=0; j< this->getPlayer(i).getPlayerCountriesSize(); j++)
			{
				for(int k=0; k< player->getN_vec().size(); k++)
				{
					if(player->getN_vec()[k] == this->getPlayer(i).getCountries()[j].getname())
					{
						if(actor.getPlayerName() != this->getPlayer(i).getCountries()[j].getowner())
						{
							arr[counter-1][0] =counter;
							arr[counter-1][1] = i;
							arr[counter-1][2] = j;
							
							cout << counter << " " << this->getPlayer(i).getCountries()[j].getname() << endl;
							counter += 1;
							
							
						}
					}
				}
			}
		}		
		
		 
		
		cout << "What's your choice: ";
		cin >> choice;
		cout <<  endl;
		
		if(choice <= counter)
		{
			break1 = -1;
		}
		
		counter = 0;
		
		while(break1 != -1)
		{
			cerr << "Sorry not a valid choice, exceeded bounds of the list" <<endl;
			cerr << "Enter new option" << endl;

			cout << "Please select your country to attack: " << endl;
			
			
			for(int i=0; i < this->getCastSize(); i++)
			{	
				for(int j=0; j< this->getPlayer(i).getPlayerCountriesSize(); j++)
				{
					for(int k=0; k< player->getN_vec().size(); k++)
					{
						if(player->getN_vec()[k] == this->getPlayer(i).getCountries()[j].getname())
						{
							if(actor.getPlayerName() != this->getPlayer(i).getCountries()[j].getowner())
							{
								arr[counter-1][0] =counter;
								arr[counter-1][1] = i;
								arr[counter-1][2] = j;
						
								counter += 1;
							
							
							}
						}
					}
				}
			}		
				
			
			
			cout << "Whats your choice: ";
			cin >> choice;
			cout << endl;
			
			if(choice > counter)
			{
				break1 = -1;
			}
			
		}
		
		
		int i =arr[choice-1][1];
		int j = arr[choice-1][2];
		
		for(int i=0; i<50; i++)
		{
			delete arr[i];
		}
		
		delete []arr;
		
		arr = NULL;
		
		
		return this->getPlayer(i).getCountries()[j];
		
	}
	
	
	
	
	void game::compareDiceRolls(playerClass& actor, playerClass& villan, Country* player1, Country* player2)
	{
		
		vector<int> v1 = actor.getPlayerDiceFactory().getV();
		vector<int> v2 = villan.getPlayerDiceFactory().getV();

		//now we compare dice rolls pair wise in each players vector to determine who loses an army
		for(int i = 0; i < v2.size() && i < v1.size(); i++)
		{
			cout << "Attacking player dice rolled a: " << v1[i] << endl;
			cout << "Defending player dice rolled a: " << v2[i] << endl;

			//if player 1 won the round subtract 1 from defending players country
			if(v1[i] > v2[i])
			{
				cout << "Attacking player won this round." << endl;

				player2->setNumUnits(player2->getNumUnits() - 1);

				cout << "Defending player remaining army is : " << player2->getNumUnits() << endl;

				if(player2->getNumUnits() == 0)
				{
					cout << "Attacking player has conquered the territory." << endl;;
					//add the country to attacking layer list and remove it from the defending list
					
					
					int position=0;
					playerClass* opponent = new playerClass("");
					
					for(int i=0; i< this->getCastSize(); i++)
					{
						for(int j=0; j<this->getPlayer(i).getPlayerCountriesSize(); j++)
						{	
							if(player2->getname() == this->getPlayer(i).getCountries()[j].getname())
							{
								opponent = &this->getPlayer(i);
								position = j;
							}
							
						}
					}
					
					//player2->setowner(player1->getname());
				
					//actor.getCountries().push_back(temp);
					
					opponent->getCountries()[position].setowner(player1->getname());
					actor.getCountries().push_back(opponent->getCountries()[position]);
					
					opponent->getCountries().erase(opponent->getCountries().begin() + position);

					//check if player is able to move his armies
					if(player1->getNumUnits() > 1)
					{
						int max = player1->getNumUnits() - 1;
						int army;
						cout << "\n How many armies do you wish to move to your newly acquired country: " << endl;
						cin >> army;

						//make sure player does not send all armies to newly conquered country. Must leave 1 behind
						// make sure at least 1 army has been moved
						while(army > max || army == 0)
						{
							if(army > max)
							{
								cerr << "Sorry, you must leave at least 1 army behind." << endl;
								cerr << "The maximum number of armies you can move is: " << max << endl;
								cout << "Enter new amount: " << endl;
								cin >> army;
							}

							if(army == 0)
							{
								cerr << "Sorry, you must move at least 1 army." << endl;
								cerr << "You cannot move 0 armies: " << endl;
								cout << "Enter new amount: " << endl;
								cin >> army;
							}
						}

						cout << endl;
						//move armies to the country
						actor.getCountries()[actor.getPlayerCountriesSize()-1].setNumUnits(army);

						player1->setNumUnits(player1->getNumUnits() - army);

						cout << "You have moved " << army << " armies from " << player1->getname()<< " to " << actor.getCountries()[actor.getPlayerCountriesSize()-1].getname() << endl;
						cout << "\n" << player1->getname() << " now has " << player1->getNumUnits() << endl;
						cout << actor.getCountries()[actor.getPlayerCountriesSize()-1].getname() << " has " << actor.getCountries()[actor.getPlayerCountriesSize()-1].getNumUnits()<< endl;
						cout << "End of the fight"<<endl;
						break;
					}
					else
					{
						cout << "Unfortunately, you only have 1 army left so you cannot move any to your newly acquired country. " <<  endl;
					}
				}
			}
			else
			{
				cout << "Defending player won this round." << endl;
				//subtracy an army from attacking players country
	
				player1->setNumUnits(player1->getNumUnits() - 1);
				cout << "Attacking player remaining army is : " << player1->getNumUnits() << endl;

				if(player1->getNumUnits() == 0)
				{
						cout << "Defending country player has successfully defended his territory.";
				}
			}

		}// end of comparing for loop

		//make sure container is not empty
		actor.getPlayerDiceFactory().getV().clear();
		villan.getPlayerDiceFactory().getV().clear();
	}
	
void game::MainGame(Map board)
{
	int round = 0;
	int number = 0;
	int exit1 = 0;
	int exit2 =0;
	int battle = 0;
	int reinforce = 0;
	int attack = 0;
	int fortify = 0;
	
	playerClass winner("",0,0);
	playerClass* temp = new playerClass("",0,0);
	
	
	
	while (exit1 != -1)
	{
		
		for (int i = 0; i<getCastSize(); i++)
		{
			
			for (int i=0; i< this->getCastSize(); i++)
	{
		cout << this->getPlayer(i).getPlayerName() <<endl;
		cout << this->getPlayer(i).getCountries()[0].getname() <<endl;
		cout << this->getPlayer(i).getCountries()[0].getNumUnits() <<endl;
	}
			
			temp = &this->getPlayer(i);
			
			if (i == 0)
			{
				//sets Player1 to have all the countries
				//temp.setCountries(board.getCountries());
				
			}
			
			cout << "Please select what to do " << temp->getPlayerName() << endl;
			//cout << "has armies " << tempon"
			
			exit2 =0;
			battle = 0;
			
			while (battle != -1)
			{
				if(reinforce == 0)
				{
					cout << "1) to begin Reinforcement phase" << endl;
				}
				
				if(attack == 0)
				{
					cout <<"2) to begin Attack phase" << endl;
				}
				
				if(fortify == 0)
				{
					cout << "3) to begin Fortification phase" << endl;
				}
				
				cout << "4) to skip the rest of your turn" << endl;
			
				while(exit2 != -2)
				{
					cin >> number;
					
					if (number <= 4 && number >= 1)
					{
						if (number == 1 && reinforce == 0)
						{
							exit2 = -2;
						}
						else if (number ==1)
						{
							cout << "Please enter a valid option" << endl;
						}
						
						if (number == 2 && attack == 0)
						{
							exit2 = -2;
						}
						else if (number == 2)
						{
							cout << "Please enter a valid option" << endl;
						}
						
						if (number == 3 && fortify == 0)
						{
							exit2 = -2;
						}
						else if (number == 3)
						{
							cout << "Please enter a valid option" << endl;
						}
						if (number == 4)
						{
							exit2 = -2;
						
						}
					}	
					else
					{
						cout << "Please enter a valid option" << endl;
					}
				
				}
				
				exit2 = 0;
				
				
				//playerClass temp2(temp);
				
				switch(number)
				{
					case 1:
						temp->reinforce();
						cout << this->getPlayer(i).getCountries()[0].getNumUnits() <<endl;
						round += 1;
						reinforce += 1;
						break;
					
					case 2:
						cout<<"about to attack" << endl;
						this->attack(temp);
						//temp = &temp2;
						//cout << "temp2 " << temp2.getCountries()[temp2.getPlayerCountriesSize()-1].getname() << endl;
						//cout << "temp " << temp->getCountries()[temp->getPlayerCountriesSize()-1].getname() << endl;
						attack += 1;
						break;
					
					case 3:
						cout << "temp " << temp->getCountries()[temp->getPlayerCountriesSize()-1].getname() << endl;
						//temp->fortify();
						fortify += 1;
						break;
					case 4:
						battle = -1;
						break;
				
				}
				
			}
			
			reinforce = 0;
			attack = 0;
			fortify = 0;
		
			
			
			if (!(i == getCastSize()-1))
			{
				cout << "Next Players Turn!" << endl;
			}
			
			//checks if the player has the full map worth of countires
			if (temp->getPlayerCountriesSize() == board.getAmountCountries())
			{
				//winner = temp;
				exit1 = -1;
			}
			
			
		}
	}
	//declares winner
	cout << winner.getPlayerName() << " has won the game!" << endl;

	delete temp;
	temp = NULL;

}