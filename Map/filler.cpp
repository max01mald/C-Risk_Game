/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 1 due 28 September 2017
*/

#include "filler.h"

//Constructor accepting a string
filler::filler(std::string stream_op)
{
	stream_name = stream_op;
}

//initializing dumby Objects to use in code
filler fillez("worker");

Continent world("World", 0, 0 );

Country grouped("hello");


//getter
std::string filler::getname()
{
	return stream_name;
}

//checks if the file is a [map]
void filler::is_file()
{
	while(!inStream.eof())
	{
		inStream >> name;
		
		if (name == "[Map]")
		{
			std::cout << "Yes this is a valid map" << std::endl;
			break;
		}
		else
		{
			std::cerr << "Error this is not a valid map" << std::endl;
			exit(1);
		}	
	}
}

//inputs the file territory as Continent objects in a vector and returns it
vector<Continent> filler::Cont_fill(vector<Country> cntry)
{
	store = "";
	line = 'a';

	//runs through the whole file
	while(!inStream.eof())
	{
		inStream >> name;
		
		//when it reaches the continent part to input the information into the objects
		if (name == "[Continents]")
		{	
			do
			{	
				inStream.get(line);
				
				//goes character by character
				if (line == '=')
				{
					inStream >> number;
					
					//stores the amount of countries in a variable
					amount = fillez.count_countries(store, cntry);
					
					//creates the object
					Continent cont(store, number, amount);
					
					//stores the object
					world.Cont_store(cont);
					
					store = "";
				}
				//gathers the strings for the name
				else
				{
					store = store + line;
				}			
			//indicates the end of the section
			} while(!(line == '['));
		}	
	}
	//if not filled then through error and terminate
	if (world.store_vec.size() == 0)
	{
		std::cerr << "Error this is not a valid map" << std::endl;
			exit(1);
	}
	//returns and clears the vector
	return world.store_vec;
	world.store_vec.clear();
}

//Method that stores the country info in an object and stores them in a vector which is then returned
vector<Country> filler::Countr_fill()
{
	store = "";
	counter = 0;
	//goes through the whole file
	while (!inStream.eof())
	{
		inStream >> name;
		//finds the section where Countries begin
		if (name == "[Territories]")
		{
			do
			{
				//reads line by line
				inStream.get(line);
				
				if (line == '\n')
				{
					//at the end of line the method has stored all the necessairy
					//information to create the country object
					
					//this removes any unwated break characters
					store.erase(std::remove(store.begin(), store.end(), '\n'), store.end());
					store.erase(std::remove(store.begin(), store.end(), '\r'), store.end());
					
					//stores the country info in a temp vector which will be passed to the
					//country object
					
					neigh_s.push_back(store);
					store = "";
					
					//creates the country object by passing the info as a vector
					//and the coordinates as an array int 
					Country geo(neigh_s, fillez.cord_store);
						
					//stores the object in the vector
					grouped.Country_store(geo);
						
					//clears the temp array to restart gathering for the next object
					neigh_s.clear();
						
					counter = 0;
				}
				
				if (line == ',')
				{
					if (counter == 0)
					{
						//trims and stores the info after every ,
						store.erase(std::remove(store.begin(), store.end(), '\n'), store.end());
						store.erase(std::remove(store.begin(), store.end(), '\r'), store.end());
						neigh_s.push_back(store);
						store = "";
					}
				
					counter += 1;
					
					if (counter > 0 && counter < 3)
					{
						//makes sure that when it reaches the coordinate positions it 
						//stores them into the int array
						store = "";
					
						inStream >> number;
						
						fillez.cord_store[counter - 1] = number;
					}
					
					else
					{
						//stores the country info in the temp array
						store.erase(std::remove(store.begin(), store.end(), '\n'), store.end());
						store.erase(std::remove(store.begin(), store.end(), '\r'), store.end());
						
						neigh_s.push_back(store);
						
						store = "";
					}
					
				}
	
				else
				{
					//stores the chars into a string
					store = store + line;
				}	
			//end of file has been reached	
			}while(!inStream.eof());
		}
	}
	
	
	//if not filled then through error and terminate
	
	
	for (int i=0; i<grouped.store_vec.size(); i++)
	{
		if (grouped.store_vec[i].getname() != "")
		{
			counter += 1;
		}
	}
	
	std::cout<< counter << std::endl;
	
	if (counter == 0)
	{
		std::cerr << "Error this is not a valid map" << std::endl;
		exit(1);
	}

	//returns and clears the array of Countries
	return grouped.store_vec;
	grouped.store_vec.clear();
}

//this method counts the countries by comparing the name of the continent
//with the continent name of Countries
int filler::count_countries(std::string str, vector<Country> cntry)
{
	int counter = 0;
	
	for (int i=0; i<cntry.size(); i++)
	{
		if (str.find(cntry[i].getcontinent()) != std::string::npos)
		{
			if(cntry[i].getcontinent() != "")
			{
			counter +=1;
			}		
		}
	}
	return counter;
}

//this mehtod is used to display the contents of the temp array
void filler::disp_neigh(std::vector<string> neigh_s)
{
	for (int i=0; i<neigh_s.size(); i++)
	{
		std::cout << neigh_s[i] << " ";
	}
}

//this mehtod is used to display the coordinate int array
void filler::disp_cord(int cord_store[])
{
	for(int i=0; i<2; i++)
	{
		std::cout << cord_store[i] << " ";
	}
	std::cout << std::endl;
}

//this method prompts the user for the name of the file which will be accessed
std::string filler::request_map()
{
	std::cout << "Please enter a file name, which is associated to your map" << std::endl;
	std::cin >> map_name;
	
	return map_name;
}

//this mehtod creates the stream to the map
void filler::open_map(std::string m_name)
{
	inStream.open(map_name);
}

//this method closes the stream to the map
void filler::close_map()
{
	inStream.close();
	
	std::cout << "The map file has been closed" << std::endl;	
	
}




