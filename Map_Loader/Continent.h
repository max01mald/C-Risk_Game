/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 1 due 28 September 2017
*/

#ifndef CONTINENT_H
#define CONTINENT_H
#include <iostream>
#include <vector>
#include "Country.h"

//class Continent
class Continent
{

public:
	
	//constructors
	Continent(std::string new_name, std::string new_owner, int new_number, int new_amount);
	
	Continent(std::string new_name, int new_number, int new_amount);
	
	//declared variables
	std::vector<Continent> store_vec;
	
	//getters
	std::string getname();
	std::string getowner();
	int getnumber();
	int getamount();
	Country getN_Cntry(int pos);
	Country* getN_Ptr(int pos);
	
	//setters
	void setname(std::string new_name);
	void setowner(std::string new_owner);
	void setnumber(int new_number);
	void setN_ptr(int pos, Country *point);
	
	//methods
	void Cont_store(Continent cont);
	void Disp_Continent(vector<Continent> conti);
	vector<Continent> Continent_linker(vector<Continent> cnti, vector<Country> cntry);
	void disp_neigh_ptr(Continent cnti);
	
	
private:
	//private instance variables
	std::string name;
	int number, amount;
	std::string owner;
	std::vector<Country*> count_ptr_vec;
	//Country **count_ptr_arr;
	
};

#endif