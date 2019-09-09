#include "Cheater.h"


Cheater::Cheater(): type("Cheater")
{
}

void Cheater::reinforce(playerClass *p)
{

	
	
	for(int i=0; i<p->getCountries().size(); i++)
	{
		cout << endl;
		cout << p->getCountries()[i].getname() << " has " << p->getCountries()[i].getNumUnits() <<endl;
		p->getCountries()[i].setNumUnits(p->getCountries()[i].getNumUnits()*2);
		cout << p->getCountries()[i].getname() << " now has " << p->getCountries()[i].getNumUnits() <<endl;
		cout << endl;
	}

	cout <<endl;
}



void Cheater::attack(playerClass* actor, game* g)
{
	
	
	int p1count = 0;
	int temp =0;
	string answer = "";

	Country stop("");
	Country* player1;
	Country* player2;
	playerClass* villan;
	
	int position1 = 0;
	int position2 = 0;
	
	answer = "yes";

	if(answer != "no")
	{
		cout << endl;
		while(answer != "no")
		{
			
			
			player1 = &this->playerCountrySelection(actor, g, stop);
			
			if(player1->getname() != "")
			{
				player2 = &this->chooseDefendingCountry(actor, g, player1, stop);

				if (player2->getname() != "") {

					for (int i = 0; i < g->getCastSize(); i++)
					{
						if (player2->getowner() == g->getPlayer(i).getPlayerName())
						{
							position1 = i;

							for (int j = 0; j < g->getPlayer(i).getCountries().size(); j++)
							{
								if (player2->getname() == g->getPlayer(i).getCountries()[j].getname())
								{
									position2 = j;
								}

							}

						}
					}

					g->getPlayer(position1).getCountries()[position2].setowner(player1->getowner());


					string s = player1->getname();

					actor->getCountries().push_back(g->getPlayer(position1).getCountries()[position2]);

					for (int i = 0; i < actor->getPlayerCountriesSize(); i++) {
						if (s == actor->getCountries()[i].getname()) {
							player1 = &actor->getCountries()[i];
						}
					}

					g->getPlayer(position1).getCountries().erase(g->getPlayer(position1).getCountries().begin() + position2);


					cout << endl;
					//move armies to the country

					actor->getCountries()[actor->getPlayerCountriesSize() - 1].setNumUnits(1);

					player1->setNumUnits(player1->getNumUnits() - 1);

					cout << player1->getname() << endl;

					cout << "You have moved " << 1 << " armies from " << player1->getname() << " to " << actor->getCountries()[actor->getPlayerCountriesSize() - 1].getname() << endl;
					cout << "\n" << player1->getname() << " now has " << player1->getNumUnits() << endl;
					cout << actor->getCountries()[actor->getPlayerCountriesSize() - 1].getname() << " has " << actor->getCountries()[actor->getPlayerCountriesSize() - 1].getNumUnits() << endl;
					cout << "End of the fight" << endl;
				}
				else {
					answer = "no";
					cout << "No countries to attack. End of Attack phase Cheater.\n" << endl;
				}
			}
			else
			{
				answer = "no";
				cout << "No countries to attack from. End of Attack phase Cheater.\n" << endl;
			}

				
		}// end of while loop
	}		
}

Country& Cheater::playerCountrySelection(playerClass* actor, game* g, Country &stop)
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
			
			if (counter == 1) {
				return stop;
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
			
			
			choice = 1;
			
			break2 = -1;
			
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
	
	cout << "Whats your choice: " << actor->getCountries()[temp2].getname() << endl;
	return  actor->getCountries()[temp2];	
	
}

Country& Cheater::chooseDefendingCountry(playerClass* actor, game* g, Country* player, Country &stop)
{
	int choice;
	int counter = 1;
	int temp =0;

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
	if (counter == 1) {

		for (int i = 0; i < 50; i++)
		{
			delete arr[i];
		}

		delete[]arr;

		arr = NULL;

		return stop;
	}
	else {

		choice = 1;
		
		int i = arr[choice - 1][1];
		int j = arr[choice - 1][2];

		cout << "Choice is: " << g->getPlayer(i).getCountries()[j].getname() << endl;
		
		for (int i = 0; i < 50; i++)
		{
			delete arr[i];
		}

		delete[]arr;

		arr = NULL;

		return g->getPlayer(i).getCountries()[j];
	}
	
}



void Cheater::fortify(playerClass* actor, game* g) 
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
	
	
	counter = 1;

	cout << "Please select your country to Fortify from your Countries: " << endl;
	
	
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
							if(actor->getCountries()[l].getNumUnits() == 1)
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
			
	
	
	for(int i=0; i<temp; i++)
	{
		for(int j=0; j<actor->getCountries().size(); j++)
		{
			if(arr3[i].getname() == actor->getCountries()[j].getname())
			{
				cout << endl;
				cout << actor->getCountries()[j].getname() << " had " << actor->getCountries()[j].getNumUnits() << " Units" << endl;
				actor->getCountries()[j].setNumUnits(actor->getCountries()[j].getNumUnits()*2);
				cout << actor->getCountries()[j].getname() << " now has " << actor->getCountries()[j].getNumUnits() << " Units" << endl;
				cout << endl;
			}
		}
	}		
	
	
	counter = 0;
	break2 = 0;
	
	break1 = -1;
	
	cout << "End of Fortification Phase Cheater Player" << endl;
	

	
	delete []arr;
	arr = NULL;
	
	delete []arr2;
	arr2 = NULL;
	
	delete []arr3;
	arr3 = NULL;	
	
}