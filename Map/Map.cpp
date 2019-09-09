/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 1 due 28 September 2017
*/

#include "Map.h"

//map constructor which accepts and sets the name
Map::Map(std::string new_name)
{
	name = new_name;
}

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







