/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 1 due 28 September 2017
*/

#include "Country.h"

//Constructor which accepts the vector of Country info and the int array of coordinates
Country::Country(std::vector<std::string> pass, int cord[])
{
	name = pass[0];
	owner = "";
	continent = pass[2];
	cord1 = cord[0];
	cord2 = cord[1];
	
	//initializes a vector of string relating to neighbouring countries
	for (int i=3; i<pass.size(); i++)
	{
		neigh_vec.push_back(pass[i]);
	}
	
	//stores the number of neighbours
	num_of_neigh = neigh_vec.size();
	
	//sets the pointers to an empty object but initializes the necessary size
	for (int i=0; i<num_of_neigh; i++)
	{
		Country* cntry = new Country("empty");
		count_ptr_vec.push_back(cntry);
	}
	
}

//Constructor which accepts just the cord array
//used to develop
Country::Country(int cord[])
{
	name = "";
	owner = "";
	continent = "";
	cord1 = cord[0];
	cord2 = cord[1];
}

//Constructor which accepts a string used to create dumby variables
Country::Country(std::string str)
{
	name = str;
	owner = "";
	continent = "";
	cord1 = 0;
	cord2 = 0;
	
	//Country **count_ptr_arr = new Country*[num_of_neigh];
}

//getters
std::string Country::getname()
{
	return name;
}

std::string Country::getowner()
{
	return owner;
}

std::string Country::getcontinent()
{
	return continent;
}

std::string Country:: getneigh(int pos)
{
	return neigh_vec[pos];
}

int Country::getcord1()
{
	return cord1;
}

int Country::getcord2()
{
	return cord2;
}

vector<std::string> Country::getN_vec()
{
	return neigh_vec;
}

//returns from the pointer vector
//returns as a object 
Country Country::getN_Cntry(int pos)
{
	return *count_ptr_vec[pos];
}

//returns the address
Country* Country::getN_Ptr(int pos)
{
	return count_ptr_vec[pos];
}

//setters
void Country::setname(std::string new_name)
{
	name = new_name;
}

void Country::setowner(std::string new_owner)
{
	owner = new_owner;
}

void Country::setcord1(int new_cord1)
{
	cord1 = new_cord1;
}

void Country::setcord2(int new_cord2)
{
	cord2 = new_cord2;
}

//method which displays the countries and their neighbors
void Country::disp_count(Country country)
{
	if(country.getname() != "")
	{
		std::cout << country.getname() << " " << country.getcord1() << " " << country.getcord2()
		<< " "  << country.getcontinent() << " ";
	
		country.disp_N(country);
	
		std::cout<<std::endl;
	}
	else
	{
		std::cout<<std::endl;
	}
}

//mehtod that prints the neighbouring countries
void Country::disp_N(Country cntry)
{
	vector<std::string> temp = cntry.getN_vec();
	
	for (int i=0; i<temp.size(); i++)
	{
		std::cout<< temp[i] << " ";
	}
	
}

//Method that stores the country in the store vector temp in filler
void Country::Country_store(Country countr)
{
	store_vec.push_back(countr);
}

//sets the neighbour pointer in the object vector
void Country::setN_ptr(int pos, Country *point)
{
	count_ptr_vec[pos] = point;
}

//displays the neighbours through the pointed value
void Country::disp_neigh_ptr(Country cntry)
{
	vector<string> temp = cntry.getN_vec();
	
	for (int i=0; i<temp.size(); i++)
	{	
		std::cout << cntry.getN_Cntry(i).getname() << std::endl;
	}
}

//this method creates all the pointer links to the neighbors
vector<Country> Country::Country_linker(vector<Country> cntry)
{
	Country *c;
	
	vector<std::string> temp;
	
	//this 3 loops start by going through the countries then their neighbours in the second
	//to compare them with the countries in the vector in the third
	for(int i=0; i<cntry.size(); i++)
	{
		temp = cntry[i].getN_vec();
		
		for(int j=0; j<temp.size(); j++)
		{
			for(int k=0; k<cntry.size(); k++)
			{
				
				if(cntry[k].getname().find(temp[j]) != std::string::npos)
				{
					if(temp[j] != "")
					{	
						//stores the found country in a pointer variable
						c = &cntry[k];
						cntry[i].setN_ptr(j, c);
						//then sets the appropriate position to the neighbour country
					}
				}	
			}
		}
	}
	//returns the new linked vector
	return cntry;
	
}














