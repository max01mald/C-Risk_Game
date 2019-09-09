#include "Benevolent.h"

void Benevolent::reinforce(playerClass *p)
{
	cout << "\nStarting Reinforcement phase.\n" << endl;
	p->setPlayerUnits(getArmies(p));
	cout << "\n" << p->getPlayerName() << " has received " << p->getPlayerUnits() << " armies.\n" << endl;
	this->placeArmies(p->getPlayerUnits(), p);
}

//This method calculates and returns the exact number of armies a player will get
//at the beginning of the reinforment phase.
int Benevolent::getArmies(playerClass *p)
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
void Benevolent::placeArmies(int armies, playerClass* p)
{
	int index = 0;
	int min = p->getCountries()[0].getNumUnits();

	if (p->getCountries().size() > 0)
	{
		for (int i = 1; i<p->getCountries().size(); i++)
		{
			if (p->getCountries()[i].getNumUnits() < min)
			{
				min = p->getCountries()[i].getNumUnits();
				index = i;
			}
		}

		cout << "Initial num units on " << p->getCountries()[index].getname() << " " << min << endl;


		p->getCountries()[index].setNumUnits(min + armies); //adds the armies to the previous number of armies on that country

		p->setPlayerUnits(0);

		cout << "\n" << armies << " armies have been placed on " << p->getCountries()[index].getname() << endl;
		cout << "Now there are " << p->getCountries()[index].getNumUnits() << " armies on " << p->getCountries()[index].getname() << " .\n" << endl;

	}
}

void Benevolent::attack(playerClass* p, game* g) 
{
	cout<<"I am a Benevolent player and I wont attack anyone\n" << endl;

}

void Benevolent::fortify(playerClass* p, game* g) 
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
		
		min = p->getCountries()[choice].getNumUnits();
		
		for (int j=0; j< p->getCountries()[choice].getN_vec().size(); j++)
		{
			for (int k=0; k< p->getCountries().size(); k++)
			{
				if(p->getCountries()[choice].getN_Cntry(j).getname() == p->getCountries()[k].getname())
				{			
					if(p->getCountries()[k].getNumUnits() < min)
					{
						min = p->getCountries()[k].getNumUnits();
						choice2 = k;
						counter++;
					}
				}
			}
		}
				
		move = (max -min) / 2;
			
		//Transfers units from one country to the next and displays the new distribution of units. WORKS
		cout<< p->getCountries()[choice].getname() << " will transfer " << move << " units to " << p->getCountries()[choice2].getname() << endl;
		p->getCountries()[choice2].setNumUnits(p->getCountries()[choice2].getNumUnits() + move);
		p->getCountries()[choice].setNumUnits(p->getCountries()[choice].getNumUnits() - move);
		
		cout << "The new distribution of units is: " << endl;
		cout << p->getCountries()[choice].getname() << " " << p->getCountries()[choice].getNumUnits() << " units" << endl;
		cout << p->getCountries()[choice2].getname() << " " << p->getCountries()[choice2].getNumUnits() << " units" << endl;

		
		
		cout << "Fortification phase ended Benevolent. \n" << endl;

	}
	else
	{
		cout<<"This player has no countries" << endl;
	}
}