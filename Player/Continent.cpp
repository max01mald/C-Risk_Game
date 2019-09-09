/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 1 due 28 September 2017
*/

#include "Continent.h"

//Constructor which accepts a name and owner strings as well as the number and amount ints
Continent::Continent(): name(""), owner(""), number(0), amount(0)
{
}

Continent::Continent( int new_number)
{
	number = new_number;
}
Continent::Continent(string new_name, int new_number)
{
	name = new_name;
	number = new_number;
}

Continent::Continent(std::string new_name, std::string new_owner, int new_number, int new_amount)
{
	//sets the passed values
	name = new_name;
	owner = new_owner;
	number = new_number;
	amount = new_amount;

	//sets all the pointers to countries to dumby objects before linking
	for (int i=0; i<amount; i++)
	{
		Country* cntry = new Country("empty");
		count_ptr_vec.push_back(cntry);
	}

}
//accepts the input without an owner
Continent::Continent(std::string new_name, int new_number, int new_amount)
{
	name = new_name;
	owner = "none";
	number = new_number;
	amount = new_amount;
	//Country **count_ptr_arr = new Country*[new_number];

	for (int i=0; i<amount; i++)
	{
		Country* cntry = new Country("empty");
		count_ptr_vec.push_back(cntry);
	}
}

//getters
//returns the Country from a pointer
Country Continent::getN_Cntry(int pos)
{
	return *count_ptr_vec[pos];
}

//returns the address pointer from a country
Country* Continent::getN_Ptr(int pos)
{
	return count_ptr_vec[pos];
}

std::string Continent::getname()
{
	return name;
}

std::string Continent::getowner()
{
	return owner;
}

int Continent::getnumber()
{
	return number;
}

int Continent::getamount()
{
	return amount;
}

//setters
void Continent::setname(std::string new_name)
{
	name = new_name;
}

void Continent::setowner(std::string new_owner)
{
	owner = new_owner;
}

void Continent::setnumber(int new_number)
{
	number = new_number;
}

//sets the position in the object pointer array to the chosen country object pointer
void Continent::setN_ptr(int pos, Country *point)
{
	count_ptr_vec[pos] = point;
}

void Continent::Cont_store(Continent cont)
{
	store_vec.push_back(cont);
}

//this method displays the contents of a Continent vector
void Continent::Disp_Continent(vector<Continent> conti)
{
	for (int i=0; i<conti.size(); i++)
	{
		std::cout << conti[i].getname() << " = " << conti[i].getamount() << std::endl;
	}

}

//this method prints the associated Countries from the Continent through pointers
void Continent::disp_neigh_ptr(Continent cnti)
{
	for (int i=0; i<cnti.getamount(); i++)
	{
		std::cout << cnti.getN_Cntry(i).getname();
	}
}

//this method links the continents in the vector to their associated countries and
//returns the new vector
vector<Continent> Continent::Continent_linker(vector<Continent> cnti, vector<Country> cntry)
{

	int counter =0;

	Country *c;

	//this loops through the continent vector first then loops through the entire
	//country vector comparing for associations
	for (int i=0; i<cnti.size(); i++)
	{
		counter = 0;

		for (int j=i; j<cntry.size(); j++)
		{


			if(cnti[i].getname().find(cntry[j].getcontinent()) != std::string::npos)
			{
				if(cntry[j].getcontinent() != "")
				{
					//once the country is found it is pointed to by a temp pointer
					c = &cntry[j];

					cnti[i].setN_ptr(counter, c);
					//which is then passed through the function to make the link

					counter +=1;

				}
				//this makes sure that only the appropriate amount of links are made
				if (counter == cnti[i].getamount())
				{
					break;
				}
			}

		}

	}
	return cnti;
}
