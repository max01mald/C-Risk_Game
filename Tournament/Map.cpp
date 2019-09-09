/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 1 due 28 September 2017
*/


#include "Map.h"

//map constructor which accepts and sets the name

Map::Map(): name("Noone")
{
}

Map::Map(std::string new_name)
{
	name = new_name;
}

Map::Map(std::string new_name, vector<Continent> Cont, vector<Country> Coun)
{
	name = new_name;
	Continent_vector = Cont;
	Country_vector = Coun;
}

vector<Continent> Map::MapLoaderContinent(std::string name, vector<Country> MLC_vec)
{
	vector<Continent> MLCont_vec;
	
	filler* fill = new filler;
	
	cout << "The Continent is being loaded" << endl;
	
	MLCont_vec = fill->Cont_fill(MLC_vec, name);
		
	cout << "The Continent has been loaded" << endl;
	
	delete fill;
	fill = NULL;
	
	return MLCont_vec;
	
	MLCont_vec.clear();
	MLC_vec.clear();
	
}	
	
vector<Country> Map::MapLoaderCountry(std::string name)
{	

	vector<Country> MLCy_vec;
	
	filler* fill = new filler;
	
	cout << "The Country is being loaded" << endl;
	
	MLCy_vec = fill->Countr_fill(name);
	
	cout << "The Country has been loaded" << endl;
	
	delete fill;
	fill = NULL;
	
	return MLCy_vec;
	
	
}

Map Map::MapLinker(std::string name)
{

	Country cntry;
	Continent conti;

	vector<Country> MLiCy_vec = MapLoaderCountry(name);
	vector<Continent> MLiC_vec = MapLoaderContinent(name, MLiCy_vec);
	
	MLiCy_vec = cntry.Country_linker(MLiCy_vec);
	MLiC_vec = conti.Continent_linker(MLiC_vec, MLiCy_vec);
	
	
	bool t = true;
	
	t = MapCheck(MLiC_vec, MLiCy_vec);

	
	Map map;
	
	if(!t)
	{
		cout<< "This file is not properly configured for this game" << endl;
		Map map;
	}
	else
	{
		cout <<"This file has been loaded and is ready to be used!" << endl;
		map = Map("Ass2", MLiC_vec, MLiCy_vec);
	}

	MLiC_vec.clear();
	MLiCy_vec.clear();
	
	return map;
}


bool Map::MapCheck(vector<Continent> MCC_vec, vector<Country> MCy_vec)
{
	bool t = true;
	bool b = true;
	
	t = ContCheck(MCC_vec);
	b = CountryCheck(MCy_vec);
	
	if (!(b && t))
	{
		t = false;
	}
	
	return t;
}

bool Map::CountryCheck(vector<Country> CyC_vec)
{
	bool t = true;
	
	std::cout<<"CountryCheck running" << std::endl;
	
	std::vector<std::string> vec;
	std::vector<std::string> vec2;
	
	for (int i = 0; i<CyC_vec.size(); i++)
	{
		if (CyC_vec[i].getname() != "")
		{
			vec2.push_back(CyC_vec[i].getname());
		}
	}
	
	
	for (int i = 0; i< CyC_vec.size(); i++)
	{
		
		for (int j = 0; j<CyC_vec[i].getN_of_neigh(); j++)
		{
			if (std::find(vec.begin(), vec.end(),CyC_vec[i].getN_Ptr(j)->getname()) == vec.end())
			{
				vec.push_back(CyC_vec[i].getN_Ptr(j)->getname());
			}
		
		}
	}
	
	if(vec.size() != vec2.size())
	{
		t = false;
		std::cout<<" Comparision Something went wrong" << std::endl;
		std::cout<< "country vec size: " << vec2.size() << " filled vec size: " << vec.size() << std::endl;
	}
	else
	{
		std::cout << "CountryCheck is clear of error" << std::endl;
		t = true;
	}
	
	CyC_vec.clear();
	vec.clear();
	vec2.clear();
	
	return t;
}


bool Map::ContCheck(vector<Continent> CC_vec)
{
	std::cout << "ContCheck running" << std::endl;
	
	int amount =0;
	
	bool t = true;
	
	std::vector<std::string> vec;
	
	for (int i=0; i<CC_vec.size(); i++)
	{
		amount += CC_vec[i].getamount();
	
		for (int j=0; j<CC_vec[i].getamount(); j++)
		{
			if (std::find(vec.begin(), vec.end(), CC_vec[i].getN_Ptr(j)->getname()) == vec.end())
			{
				vec.push_back(CC_vec[i].getN_Ptr(j)->getname());
			}
			else
			{
				t = false;
			}
		}
	}
	
	if (t)
	{
		std::cout << "ContCheck is clear of error" << std::endl;
	}
	else
	{
		std::cout << "Something went wrong" << std::endl;
	}
	
	std::cout << "the number of countries: " << amount << std::endl;
	
	CC_vec.clear();
	
	
	return t;

}


/*void Map::RandomCountries()
{
	vector<Country> new_vec;
	
	for (int i=0; i< this->getAmountCountries(); i++)
	{
		if(this->getCountries()[i].getname() != "")
		{ 
			//cout << "Setting name" << endl;
			this->getCountries()[i].setname("hello");
		}	
	}
	for (int i=0; i< new_vec.size(); i++)
	{
		cout << this->getCountries()[i].getname() << endl;
	
	}
	
}
*/

//this is the method which allows the user to travel the map
void Map::Runner(vector<Continent> conti, vector<Country> cntry)
{
	int end = 1;
	int choice = 0;
	int choice2 =0;
	int count =0;
	
	//keeps the menu running until indicated otherwise
	while(end != 0)
	{
		//prompts the user for an action
		std::cout << std::endl;
		std::cout << "What would you like to do?" << std::endl;
		std::cout << "(1) Access the Map" << std::endl;
		std::cout << "(2) Exit" << std::endl;
		
		std::cin >> end;	
		
		switch (end)
		{
			case 1:
				//starts by presenting the continents to 
				//then point to their associated countries
				
				std::cout << "Pick a Continent" << std::endl;
				for(int i=0; i<conti.size(); i++)
				{
					//displays the countries in the vector
					std::cout << "(" << i+1 << ")" << " ";
					std::cout << conti[i].getname() << std::endl << std::endl;
					
				}	
				
				std::cin >> choice;
				std::cout << std::endl;
				
				
	
				std::cout << "Please pick a country you would like to visit" << std::endl;
				
				//loops through the countries associated to the Continent
				for(int j=0; j<conti[choice-1].getamount(); j++)
				{
					std::cout << "(" << j+1 << ")" << " ";
					std::cout << conti[choice-1].getN_Cntry(j).getname() << std::endl;
				}	
				//accepts selection
				std::cout << std::endl;
				std::cin >> choice2;
				std::cout << std::endl;
				
				Country *c;
				
				//stores the pointer to a country in a variable to then be able to move
				//from one to another independant of the continent
				c = conti[choice-1].getN_Ptr(choice2-1);
				
				//std::cout << c->getname() << std::endl;
				
				//this while allows the travelling to continue until the user indicates otherwise
				while (end != (-1))
				{
					count = 0;
					
					//checks to see if the neighbour pointers are loaded
					//returns error to indicate invalid map
					if (c->getN_vec().size() == 0)
					{
						std::cerr << "Error this is not a valid map" << std::endl;
						exit(1);
					}
					
					//loops through the neighbours of the selected country and displays them
					//through pointers
					for(int k=0; k<c->getN_vec().size(); k++)
					{
						std::cout << "(" << k+1 << ")" << " ";
						
						std::cout << c->getN_Cntry(k).getname() << std::endl;
						count+=1;
					}
					
					count += 1;
					
					//prompts options
					std::cout << "(" << count << ")" << " Exit to Main"<<std::endl;
					std::cout << std::endl;
					std::cin >> choice2;
					std::cout << std::endl;
					
					//sets county to new choice
					c = c->getN_Ptr(choice2-1);
					
					//terminating input
					if (choice2 == count)
					{
						end = -1;
					}
					
				}
			break;
			
			//exit the final loop
			case 2:	
				end = 0;	
				break;				
			
			
		}	
	}
}







