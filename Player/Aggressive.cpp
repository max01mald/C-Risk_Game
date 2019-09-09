#include "Aggressive.h"


void Aggressive::reinforce(playerClass *p)
{
	cout << "\nStarting Reinforcement phase.\n" << endl;
	p->setPlayerUnits(getArmies(p));
	cout << "\n" << p->getPlayerName() << " has received " << p->getPlayerUnits() << " armies.\n" << endl;
	this->placeArmies(p->getPlayerUnits(), p);
}

//This method calculates and returns the exact number of armies a player will get
//at the beginning of the reinforment phase.
int Aggressive::getArmies(playerClass *p)
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

//This method places the number of armies on the strongest country
void Aggressive::placeArmies(int armies, playerClass* p)
{
	int index = 0;
	int max = 0;

	if (p->getCountries().size() > 0)
	{
		for (int i = 0; i<p->getCountries().size(); i++)
		{
			if (p->getCountries()[i].getNumUnits() > max)
			{
				max = p->getCountries()[i].getNumUnits();
				index = i;
			}
		}

		cout << "Initial num units on " << p->getCountries()[index].getname() << " " << max << endl;


		p->getCountries()[index].setNumUnits(max + armies); //adds the armies to the previous number of armies on that country

		p->setPlayerUnits(0);

		cout << "\n" << armies << " armies have been placed on " << p->getCountries()[index].getname() << endl;
		cout << "Now there are " << p->getCountries()[index].getNumUnits() << " armies on " << p->getCountries()[index].getname() << " .\n" << endl;

	}
}

/*
 * This method involves the attack phase of a player
 * it will ask the attacking player how many dice rolls he want to roll
 *
 * Checks, if the amount entered is between 1 to 3 inclusive and also if the number does
 * not exceed the number of armies in the current country - 1.
 *
 *  @ param defPlayer	DiceFactory object of the defending player. Responsible for the dice rolls of the
 *  defending player
 */

void Aggressive::attack(playerClass* actor, game* g)
{


	int p1count = 0;
	int temp =0;
	int break1 =0;
	string answer = "";

	Country* player1 = new Country("");
	Country* player2 = new Country("");
	playerClass* villan = new playerClass("",0,0);


	if(actor->getCountries().size() > 0)
	{

		cout << endl;
		while(break1 != -1)
		{
			player1 = &this->playerCountrySelection(actor, g);
			
			player2 = &this->chooseDefendingCountry(actor, g, player1);
			
			if((player1->getNumUnits() < 2)|| player2->getNumUnits()==0 || (player2->getname() == ""))
			{
				break1 = -1;
				cout<<"hello"<<endl;
				break;
			}

			cout << player1->getname() <<endl;
			cout << player2->getname() <<endl;

			cout << "\n \t\t ATTACKING PLAYER DICE ROLL \n" << endl;

			actor->getPlayerDiceFactory().getV().clear();


			cout << "From 1-" << 3 << " , enter amount of dice rolls to put: " << endl;
			cout << player1->getname() << " has " << player1->getNumUnits()-1 << " available units"<<endl;

			if((player1->getNumUnits()-1) > 3)
			{
				temp = 3;
			}
			else if((player1->getNumUnits()-1) <= 3)
			{
				temp = player1->getNumUnits()-1 ;
			}

			cout<<"Attacker has selected to roll " << temp << " Dice" <<endl;

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

			villan->getPlayerDiceFactory().getV().clear();
			this->rollDicesDefendingPlayer(villan, player2);

			playerClass villan2(villan);

			//compare values of dices to determine winner
			this->compareDiceRolls(actor,g, villan2, player1, player2);

			//reset to 0
			actor->getPlayerDiceFactory().setNumDiceRolls(0);


		}		// end of while loop
	}
	else
	{
		cout<<"This country has no more Units"<<endl;
	}
	
	delete player1;
	player1 = NULL;
	
	delete player2;
	player2 = NULL;
	
	delete villan;
	villan = NULL;
	
}

 /*
 * Attacking player selects the country he wants to attack with from his list.
 * If user enters number that exceeds the list, it will output an error message and ask
 * the user to enter again
 */

Country& Aggressive::playerCountrySelection(playerClass* actor, game* g)
{

	int choice;
	int counter;
	int max =0;

	cout << endl;


	for(int i=0; i<actor->getCountries().size(); i++)
	{
		if(actor->getCountries()[i].getNumUnits() > max)
		{
			max = actor->getCountries()[i].getNumUnits();
			choice = i;
		}

	}


	
	return actor->getCountries()[choice];

	
}

/*
 * Attacking player selects the country he wants to attack from enemy list.
 * If user enters number that exceeds the list or the country selected does
 * not have at least 2 armies on it, it will output an error message and ask
 * the user to enter again
 */


Country& Aggressive::chooseDefendingCountry(playerClass* actor, game* g, Country* player)
{
	int choice =0;
	int choice2 =0;


	int counter = 0;
	int temp =0;
	int break1 =0;
	int min = 100000000;
	

	cout << "choosing defending country" <<endl;
	for(int i=0; i < g->getCastSize(); i++)
	{
		for(int j=0; j< g->getPlayer(i).getPlayerCountriesSize(); j++)
		{
			for(int k=0; k< player->getN_vec().size(); k++)
			{
				if(player->getN_vec()[k] == g->getPlayer(i).getCountries()[j].getname())
				{
					if(actor->getPlayerName() != g->getPlayer(i).getCountries()[j].getowner())
					{
						if(g->getPlayer(i).getCountries()[j].getNumUnits() !=0)
						{
							min = g->getPlayer(i).getCountries()[j].getNumUnits();
							choice = i;
							choice2 = j;
							counter += 1;

						}
					}
				}
			}
		}	
		
	}

	if(counter ==0)
	{	
		cout<<"No Country Selected"<<endl;
		cout <<counter<<endl;
		Country temp("");
		return temp;
	} 

	

	return g->getPlayer(choice).getCountries()[choice2];

	

}


/*
 * @param	player1		The diceFactory object representing attacking player
 * @param   player2		DiceFactory object representing defending player
 *
 * 	this method compares the sorted dice values rolled by each player and determines who won
 * 	or lost the round
 *
 * 	if attacker wins, defending players army of that country is reduced by 1
 * 	If defending player wins, attacker's army is reduced by 1
 *
 * 	If defender's army is reduced to zero than attacker gains control of the territory and it
 * 	is added to his list of countries while removing it from the defending player
 *
 * 	the attacker must then, if possible, move at least 1 army to the newly acquired country and must leave behind at least
 * 	1 army to defend his country that he attacked with
 */

void Aggressive::compareDiceRolls(playerClass* actor, game* g, playerClass& villan, Country* player1, Country* player2)
{

	playerClass* opponent = new playerClass("");
	
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


				int position=0;

				for(int i=0; i< g->getCastSize(); i++)
				{
					for(int j=0; j<g->getPlayer(i).getPlayerCountriesSize(); j++)
					{
						if(player2->getname() == g->getPlayer(i).getCountries()[j].getname())
						{
							opponent = &g->getPlayer(i);
							position = j;
						}

					}
				}


				opponent->getCountries()[position].setowner(player1->getowner());
				actor->getCountries().push_back(opponent->getCountries()[position]);

				opponent->getCountries().erase(opponent->getCountries().begin() + position);

				//check if player is able to move his armies
				if(player1->getNumUnits() > 1)
				{
					int max = player1->getNumUnits() - 1;
					int army;
					cout << "There are " << player1->getNumUnits() - 1 << " units that can be moved" << endl;


					army =player1->getNumUnits() - 1;

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
	
	delete opponent;
	opponent = NULL;
}

/*
 * this method accepts a dice factory object by reference representing the defending player
 *
 * will ask the defending player how many dices he want to roll.
 * Must be equal or less to the number of armies in his country
 *
 * displays error message, if not inputted correctly, and asks the user to input again
 *
 * the method will then sort the dice values in the container and display the dice percentage rolled
 * throughout the game
 *
 */

void Aggressive::rollDicesDefendingPlayer(playerClass* villan, Country* cntry)
{

	int p2count = 0;
	int temp = 0;

	cout << "\n \t \t DEFENDING PLAYER DICE ROLL \n" << endl;

	villan->getPlayerDiceFactory().getV().clear();

	cout << cntry->getname() <<" " << cntry->getNumUnits() <<endl;

	if(cntry->getNumUnits() > 3)
	{
		temp = 3;
	}
	else if(cntry->getNumUnits() <= 3)
	{
		temp = cntry->getNumUnits() ;
	}
	cout <<"Defending Player picked " << temp << "Dices to roll"<< endl;
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


void Aggressive::fortify(playerClass* p, game* g)
{
	string name = "noway";
	int choice = 0;
	int choice2 =0;
	int counter = 0;
	int max =0;
	int min =0;
	int move =0;
	
	if(p->getCountries().size() > 0)
	{
		cout << "\nFortification Phase started\n"<<endl;
		cout << "Selecting strongest Country" <<endl;

		for(int i=0; i<p->getCountries().size(); i++)
		{
			if(p->getCountries()[i].getNumUnits() > max)
			{

				max = p->getCountries()[i].getNumUnits();

				choice = i;

			}

		}

		cout <<  p->getCountries()[choice].getname() << endl;


		
		for(int i=0; i < p->getCountries()[choice].getN_vec().size(); i++)
		{
			for(int m=0; m<p->getCountries().size(); m++)
			{
				if(p->getCountries()[choice].getN_vec()[i] == p->getCountries()[m].getname())
				{
					choice2 = m;
					counter++;
				}
			}
		}
		
		
		cout << p->getCountries()[choice2].getname() << endl;

		
		if(counter != 0)
		{

			for(int j=0; j<p->getCountries()[choice2].getN_vec().size(); j++)
			{
				for(int k=0; k< g->getCastSize(); k++)
				{
					for(int l=0; l< g->getPlayer(k).getCountries().size(); l++)
					{

						if(p->getCountries()[choice2].getN_vec()[j] == g->getPlayer(k).getCountries()[l].getname())
						{

							name = p->getCountries()[choice2].getN_vec()[j];
						}
					}
				}
			}


			for(int i=0; i<p->getCountries().size(); i++)
			{
				if(name == p->getCountries()[i].getname())
				{
					choice2 = i;
				}

			}
		}
		
		if(p->getCountries()[choice].getname() == p->getCountries()[choice2].getname())
		{	
			
			for(int i=0; i< g->getCastSize(); i++)
			{
				for(int j=0; j<g->getPlayer(i).getCountries().size(); j++)
				{
					if(p->getCountries()[choice2].getowner() != g->getPlayer(i).getCountries()[j].getowner())
					{
						name = g->getPlayer(i).getCountries()[j].getname();
					}
				}
			}
			
			for(int i=0; i<p->getCountries().size(); i++)
			{
				for(int j=0; j<p->getCountries()[i].getN_vec().size(); j++)
				{
					if(name == p->getCountries()[i].getN_vec()[j])
					{
						choice2 = i;
					}
				}
			}	
		
		}
		
		move = (max - 1);



		//Transfers units from one country to the next and displays the new distribution of units. WORKS
		cout<< p->getCountries()[choice].getname() << " will transfer " << move << " units to " << p->getCountries()[choice2].getname() << endl;
		p->getCountries()[choice2].setNumUnits(p->getCountries()[choice2].getNumUnits() + move);
		p->getCountries()[choice].setNumUnits(p->getCountries()[choice].getNumUnits() - move);

		cout << "The new distribution of units is: " << endl;
		cout << p->getCountries()[choice].getname() << " " << p->getCountries()[choice].getNumUnits() << " units" << endl;
		cout << p->getCountries()[choice2].getname() << " " << p->getCountries()[choice2].getNumUnits() << " units" << endl;



		cout << "Fortification phase ended Aggressive. \n" << endl;

	}
	else
	{
		cout<<"This player has no countries" << endl;
	}
}
