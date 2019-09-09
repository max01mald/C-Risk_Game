#include "Random.h"


Random::Random(): type("Random")
{
}

void Random::reinforce(playerClass *p)
{

	int break1 = 0;

	cout << "\nStarting Reinforcement phase.\n" << endl;
	p->setPlayerUnits(getArmies(p));
	cout << "\nThe player has received " << p->getPlayerUnits() << " armies.\n" << endl;
	this->placeArmies(p->getPlayerUnits(), p);


}

//This method calculates and returns the exact number of armies a player will get
//at the beginning of the reinforment phase.

int Random::getArmies(playerClass *p)
{
	int countryUnits = p->getCountries().size() / 3; //the number of countries divided by 3 rounded down
	if (countryUnits < 3) { countryUnits = 3; }  //with a minimum of 3.

	int contUnits = 0;
	for (int i = 0; i < p->getContinents().size(); i++)  //the continent-control value of all continents
	{
		contUnits += p->getContinents()[i].getnumber();  //controlled by the player.
	}

	int exchangeUnits = p->getPlayerHand().exchange();  //the armies resulting of card exchange, if possible.

	cout << "Units from controled countries: " << countryUnits << endl;
	cout << "Units from controled continents: " << contUnits << endl;
	cout << "Units from exchange method: " << exchangeUnits << endl;

	int total = countryUnits + contUnits + exchangeUnits; //the sum of all the previous values.

	return total;
}

//This method places a number of armies on the first continent of the player's continent list
void Random::placeArmies(int armies, playerClass* p)
{
	int counter = 1;
	int choice = 0;

	int break1 = 0;
	int break2 = 0;

	if (p->getCountries().size() > 0)
	{


		while (break1 != -1)
		{
			counter = 1;
			while (break2 != -1)
			{
				cout << "Select your Country to reinforce " << endl;

				for (int i = 0; i<p->getCountries().size(); i++)
				{
					cout << counter << " " << p->getCountries()[i].getname() << endl;
					counter++;

				}

				srand ( time(NULL) );
				
				choice = (rand() % counter) + 1;
				
				cout << "Random player has selected " << choice << endl;

				if (choice > counter)
				{
					cout << "Please pick another" << endl;
				}
				else
				{
					break2 = -1;
				}
			}

			break2 = 0;

			int initialUnits = p->getCountries()[choice - 1].getNumUnits();
			cout << "initial num units " << initialUnits << endl;

			cout << "Please choose the amount of units you want to allocate.\nMaximum amount is " << armies << endl;

			int choice2 = 0;

			while (break2 != -1)
			{
				srand ( time(NULL) );
				
				choice2 = (rand() % armies) + 1;
				
				cout << "Random player has chosen " << choice2 <<endl;

				if (choice2 > armies)
				{
					cout << "Please chose again" << endl;
				}
				else
				{
					break2 = -1;
				}

			}

			break2 = 0;
			armies = armies - choice2;

			p->getCountries()[choice - 1].setNumUnits(initialUnits + choice2); //adds the armies to the previous number of armies on that country
			cout << "final num units " << p->getCountries()[choice - 1].getNumUnits() << endl;
			p->setPlayerUnits(armies);


			cout << "\n" << choice2 << " armies have been placed on " << p->getCountries()[choice - 1].getname() << endl;
			cout << "Now there are " << p->getCountries()[choice - 1].getNumUnits() << " armies on " << p->getCountries()[choice - 1].getname() << " .\n" << endl;




			if (p->getPlayerUnits() == 0)
			{
				break1 = -1;
			}

		}
	}
}


void Random::attack(playerClass* actor, game* g)
{
	
	
	int p1count = 0;
	int temp =0;
	string answer = "";

	Country* player1 = NULL;
	Country* player2 = NULL;
	playerClass* villan = NULL;
	
	vector<int> again;
	int repeat;
	int check;
	
		cout << "Do you wish to attack? yes/no" << endl;
		answer = "yes";

		if(answer != "no")
		{
			cout << endl;
			while(answer != "no")
			{
				
				
				player1 = &this->playerCountrySelection(actor, g);

				player2 = &this->chooseDefendingCountry(actor, g, player1);
		
			
				cout << "\n \t\t ATTACKING PLAYER DICE ROLL \n" << endl;
				
				actor->getPlayerDiceFactory().getV().clear();
				
				
				cout << "From 1-" << 3 << " , enter amount of dice rolls to put: " << endl;
				cout << player1->getname() << " has " << player1->getNumUnits()-1 << " available units"<<endl; 
				
				if(player1->getNumUnits()-1 >= 3)
				{
					temp = 3;
				}
				else
				{
					temp = player1->getNumUnits()-1;
				}
				
				actor->getPlayerDiceFactory().setNumDiceRolls(temp);
					
				

				//temporary variable that holds count of available dice rolls
				p1count = actor->getPlayerDiceFactory().getNumDiceRolls();

				int size = 0;
			
				//set size to numDiceRolls, represents the array size
				size = actor->getPlayerDiceFactory().getNumDiceRolls();

				//set numDiceRolls to validated dice roll
				actor->getPlayerDiceFactory().setNumDiceRolls(p1count);

				actor->getPlayerDiceFactory().dicePercentage(actor->getPlayerDiceFactory().getNumDiceRolls());

				//this method keeps track of the percentage of all individual values rolled up to now
				actor->getPlayerDiceFactory().displayAllIndividualPercentages();

				//display all values rolled during this sequence
				cout << endl;

				temp = 0;
				
				//sort array from largest to smallest
				for(int i = 0; i < actor->getPlayerDiceFactory().getNumDiceRolls(); i++)
				{
					for(int j = i+1; j < actor->getPlayerDiceFactory().getNumDiceRolls(); j++)
					{
						if(actor->getPlayerDiceFactory().getV()[i] < actor->getPlayerDiceFactory().getV()[j])
						{
							temp = actor->getPlayerDiceFactory().getV()[j];
							actor->getPlayerDiceFactory().getV()[j] = actor->getPlayerDiceFactory().getV()[i];
							actor->getPlayerDiceFactory().getV()[i] = temp;
						}
					}
				}
			
				
			
				for (int i=0; i< g->getCastSize(); i++)
				{
					if(player2->getowner() == g->getPlayer(i).getPlayerName())
					{
						*villan = g->getPlayer(i);
			
					}
				
				}
			
			

				cout << "Values stored in the container" << endl;
				for(int i=0; i < p1count; i++)
					cout << actor->getPlayerDiceFactory().getV()[i] << endl;

				//rol dice for defending player
				this->rollDicesDefendingPlayer(villan, player2);
			
				playerClass villan2(villan);
			
				//compare values of dices to determine winner
				this->compareDiceRolls(actor,g, villan2, player1, player2);
			
				//reset to 0
				actor->getPlayerDiceFactory().setNumDiceRolls(0);

				cout << endl;
				cout << "Do you want to roll again: ";
				
				
				
				srand(time(NULL));
				repeat = (rand() % 1);
				again.push_back(repeat);
				
				for (int i=0; i< again.size(); i++)
				{
					if(again[i] == 0)
					{
						check += 1; 
					}
				}
				
				if(check == 3)
				{
					answer = "no";
				}
				else 
				{
					answer = "yes";
				}
				
			
			}// end of while loop
		}
	
}

Country& Random::playerCountrySelection(playerClass* actor, game* g)
{

	int choice;
	int counter; 
	int break1;
	int break2;
	cout << endl;
	
	break1 = 0;
	
	
	Country* arr = new Country[actor->getCountries().size()];
	string* arr2 = new string[actor->getCountries().size()];
	Country* arr3 = new Country[actor->getCountries().size()];
	
	while(break1 != -1)
	{	
		break2 = 0;
		
		while(break2 != -1)
		{
			counter = 1;
		
			cout << "Please select your country to attack with from your Countries: " << endl;
			
			
			for(int l=0; l < actor->getCountries().size(); l++)
			{
				for(int k=0; k< actor->getCountries()[l].getN_vec().size(); k++)
				{
					for(int i=0; i < g->getCastSize(); i++)
					{	
						if(actor->getPlayerName() != g->getPlayer(i).getPlayerName())
						{
							for(int j=0; j< g->getPlayer(i).getPlayerCountriesSize(); j++)
							{
							
								if(actor->getCountries()[l].getN_vec()[k] == g->getPlayer(i).getCountries()[j].getname())
								{
									if(actor->getCountries()[l].getNumUnits() > 1)
									{
										if(actor->getPlayerName() != g->getPlayer(i).getCountries()[j].getowner())
										{	
											if(l == 0)
											{
												arr2[l] = actor->getCountries()[l].getname();
												arr[l] = actor->getCountries()[l];
												counter++;
									
											}
											else if(arr2[l-1] != actor->getCountries()[l].getname())
											{													
												arr2[l] = actor->getCountries()[l].getname();
												arr[l] = actor->getCountries()[l];
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
			for(int i=0; i<actor->getCountries().size(); i++)
			{
				
				if(arr[i].getname() != "")
				{
					arr3[temp] = arr[i];
					temp += 1;
				
				}
			}
			
			for(int i=0; i<	actor->getCountries().size(); i++)
			{
				if(arr3[i].getname() != "")
				{
					cout << counter << " " << arr3[i].getname() << endl;
							
					counter++;
				}
			}
			
			
			cout << "Whats your choice: ";
			srand(time(NULL));
			choice = (rand() % counter) +1;
			cout << "Random player has selected " << choice << endl;
			cout << endl;
		
			
			if(choice <= counter)
			{	
			
				break2 = -1;
			}
		}
		
		counter = 0;
		break2 = 0;
		
		break1 = -1;
		
	}
	
	int temp2 = 0;
	
	for(int i=0; i<actor->getCountries().size(); i++)
	{
		if(arr3[choice-1].getname() == actor->getCountries()[i].getname())
		{
			temp2 = i;
		}
	
	}
	
	delete []arr;
	arr = NULL;
	
	delete []arr2;
	arr2 = NULL;
	
	delete []arr3;
	arr3 = NULL;
	
	
	return  actor->getCountries()[temp2];
	
	
}

Country& Random::chooseDefendingCountry(playerClass* actor, game* g, Country* player)
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
	
	
	for(int i=0; i < g->getCastSize(); i++)
	{	
		if(actor->getPlayerName() != g->getPlayer(i).getPlayerName())
		{
			for(int j=0; j< g->getPlayer(i).getPlayerCountriesSize(); j++)
			{
				for(int k=0; k< player->getN_vec().size(); k++)
				{
					if(player->getN_vec()[k] == g->getPlayer(i).getCountries()[j].getname())
					{
						if(actor->getPlayerName() != g->getPlayer(i).getCountries()[j].getowner())
						{
							arr[counter-1][0] =counter;
							arr[counter-1][1] = i;
							arr[counter-1][2] = j;
						
							cout << counter << " " << g->getPlayer(i).getCountries()[j].getname() << endl;
							counter += 1;
						
						
						}
					}
				}
			}
		}
	}		
	
	 
	
	cout << "What's your choice: ";
	srand(time(NULL));
	choice = (rand() % counter) +1;
	cout << "Random player has selected " << choice << endl;
	cout <<  endl;
	
	
	int i =arr[choice-1][1];
	int j = arr[choice-1][2];
	
	for(int i=0; i<50; i++)
	{
		delete arr[i];
	}
	
	delete []arr;
	
	arr = NULL;
	
	
	
	
	return g->getPlayer(i).getCountries()[j];
	
	
	
}




void Random::compareDiceRolls(playerClass* actor, game* g, playerClass& villan, Country* player1, Country* player2)
{
	
	vector<int> v1 = actor->getPlayerDiceFactory().getV();
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
				
				
				int position1=0;
				int position2=0;
				
				for(int i=0; i< g->getCastSize(); i++)
				{
					for(int j=0; j<g->getPlayer(i).getPlayerCountriesSize(); j++)
					{	
						if(player2->getname() == g->getPlayer(i).getCountries()[j].getname())
						{
							position1 = i;
							position2 = j;
						}
						
					}
				}
				
				
				g->getPlayer(position1).getCountries()[position2].setowner(player1->getowner());
				cout << "owner " << g->getPlayer(position1).getCountries()[position2].getowner()<<endl;
				actor->getCountries().push_back(g->getPlayer(position1).getCountries()[position2]);
				
				g->getPlayer(position1).getCountries().erase(g->getPlayer(position1).getCountries().begin() + position2);

				//check if player is able to move his armies
				if(player1->getNumUnits() > 1)
				{
					int army = player1->getNumUnits() - 1;
					
					cout << "\nHow many armies do you wish to move to your newly acquired country: " << endl;
					cout << "There are " << player1->getNumUnits() - 1 << " units that can be moved" << endl;
					cout << endl;
					
					//move armies to the country
					actor->getCountries()[actor->getPlayerCountriesSize()-1].setNumUnits(army);

					player1->setNumUnits(player1->getNumUnits() - army);

					cout << "You have moved " << army << " armies from " << player1->getname()<< " to " << actor->getCountries()[actor->getPlayerCountriesSize()-1].getname() << endl;
					cout << "\n" << player1->getname() << " now has " << player1->getNumUnits() << endl;
					cout << actor->getCountries()[actor->getPlayerCountriesSize()-1].getname() << " has " << actor->getCountries()[actor->getPlayerCountriesSize()-1].getNumUnits()<< endl;
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
	actor->getPlayerDiceFactory().getV().clear();
	villan.getPlayerDiceFactory().getV().clear();
}

void Random::rollDicesDefendingPlayer(playerClass* villan, Country* cntry)
{

	int p2count = 0;
	int temp = 0;
	
	cout << "\n \t \t DEFENDING PLAYER DICE ROLL \n" << endl;

	villan->getPlayerDiceFactory().getV().clear();
	
	cout << "From 1-3 , enter amount of dice rolls to put: " << endl;
	cout << cntry->getname() << " has " << cntry->getNumUnits() << " available units"<<endl;
	
	if(cntry->getNumUnits() > 1)
	{
			temp = 2;
	}
	else 
	{
		temp = 1;
	}
		
	villan->getPlayerDiceFactory().setNumDiceRolls(temp);
		
	
	p2count = villan->getPlayerDiceFactory().getNumDiceRolls();

	//keep track of dice rolled percentages
	villan->getPlayerDiceFactory().dicePercentage(p2count);

	//after number of rolls is validated, set p1count to numDiceRolls
	villan->getPlayerDiceFactory().setNumDiceRolls(p2count);

	//this method keeps track of the percentage of all individual values rolled up to now
	villan->getPlayerDiceFactory().displayAllIndividualPercentages();

	//display all values rolled during this sequence
	cout << endl;

	temp = 0;
	//sort array from largest to smallest
	for(int i = 0; i < villan->getPlayerDiceFactory().getNumDiceRolls(); i++)
	{
		for(int j = i+1; j < villan->getPlayerDiceFactory().getNumDiceRolls(); j++)
		{
			if(villan->getPlayerDiceFactory().getV()[i] < villan->getPlayerDiceFactory().getV()[j])
			{
				temp = villan->getPlayerDiceFactory().getV()[j];
				villan->getPlayerDiceFactory().getV()[j] = villan->getPlayerDiceFactory().getV()[i];
				villan->getPlayerDiceFactory().getV()[i] = temp;
			}
		}
	}

	cout << "Values stored in the container" << endl;
	for(int i=0; i < p2count; i++)
		cout << villan->getPlayerDiceFactory().getV()[i] << endl;

	villan->getPlayerDiceFactory().setNumDiceRolls(0);

}



void Random::fortify(playerClass* p, game* g) 
{
	
	string name = "noway";
	int break1 = 0;
	int done =0;
	int hold = 0;
	int counter = 1;
	int choice = 0;
	int temp =0;
	int temp2 =0;
	
	cout << "Fortification Phase has started" << endl;
	cout << "Please select one of your Countries to transfer countries from" <<endl;
	
	cout << p->getCountries().size();
	int** arr = new int*[p->getCountries().size()];
	for(int l=0; l<p->getCountries().size(); l++)
	{
		arr[l] = new int[2];	
	}
	
	int** arr2 = new int*[p->getCountries().size()];
	for(int l=0; l<p->getCountries().size(); l++)
	{
		arr2[l] = new int[2];	
	}

	
	counter = 1;

	for(int i=0; i<p->getCountries().size(); i++)
	{	
		if(p->getCountries()[i].getNumUnits() > 1)
		{	
			
			arr[counter-1][0] = counter;
			arr[counter-1][1] = i;
			
			cout << counter << " " << p->getCountries()[i].getname() << endl;
			counter++;
		}
				
	}
	
	srand(time(NULL));
	choice = (rand() % counter) +1;
	cout << "Random player has selected " << choice << endl;


	temp2 = arr[choice-1][1];
	
	name = p->getCountries()[temp2].getname();
	
	cout <<  p->getCountries()[temp2].getname() << endl;

	break1 = 0;
	
	//Displays the neighbours of the country that was chosen and allows to chose number of units to be transfered.WORKS
	for (int i = 0; i< p->getPlayerCountriesSize(); i++)
	{
		if (p->getCountries()[i].getname() == name)
		{
		
			cout << "\nHere are the possible neighbouring Countries" <<endl;

			
			counter = 1;
			
			for (int j=0; j< p->getCountries()[i].getN_vec().size(); j++)
			{
				for (int k=0; k< p->getCountries().size(); k++)
				{
					if(p->getCountries()[i].getN_Cntry(j).getname() == p->getCountries()[k].getname())
					{			

						arr2[counter-1][0] = counter;
						arr2[counter-1][1] = k;
						
						cout << counter << " " << p->getCountries()[k].getname() << endl;
						counter ++;
					}
				}
			}
			
			if (counter == 1)
			{
				cout << "Country has no friendly neighbours. Choose another country: " << endl;
				fortify(p, g);
				break;
			}
			
			cout << "\nChose a neighbour of " << name << " to which you want to pass units " << name << " has " << p->getCountries()[i].getNumUnits() << " units." << endl;
			
			srand(time(NULL));
			choice = (rand() % counter) +1;
			cout << "Random player has selected " << choice << endl;
			
			if(choice <= counter)
			{
				break1 = -1;
			}
		

			temp = arr2[choice-1][1];
			
			
			cout << p->getCountries()[temp2].getname() << " has " << p->getCountries()[temp2].getNumUnits()-1 << " units to move." << endl;

			cout << "Chose the number of units you wish to transfer: " << endl;

	
			int h;

			srand(time(NULL));
			h = (rand() % p->getCountries()[temp2].getNumUnits()-1) +1;
			cout << "Random player has selected " << h << endl;

			//Transfers units from one country to the next and displays the new distribution of units. WORKS
	
			p->getCountries()[temp].setNumUnits(p->getCountries()[temp].getNumUnits() + h);
			p->getCountries()[temp2].setNumUnits(p->getCountries()[temp2].getNumUnits() - h);
			cout << "The new distribution of units is: " << endl;
			cout << p->getCountries()[temp2].getname() << " " << p->getCountries()[temp2].getNumUnits() << " units" << endl;
			cout << p->getCountries()[temp].getname() << " " << p->getCountries()[temp].getNumUnits() << " units" << endl;

			done = -1;
			break1 = -1;

			cout << "Fortification phase ended.\n" << endl;
			break;

		}
	}
	
	for(int l=0; l<p->getCountries().size(); l++)
	{
		delete arr[l];
	}
	
	delete []arr;
	
	
	for(int l=0; l<p->getCountries().size(); l++)
	{
		delete arr2[l];
	}
	
	delete []arr2;
	
	
}