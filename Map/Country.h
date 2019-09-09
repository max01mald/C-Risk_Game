/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 1 due 28 September 2017
*/

#ifndef COUNTRY_H
#define COUNTRY_H
#include <iostream>
#include <vector>
using namespace std;

//class Country
class Country
{
	public:
		//Constructors
		Country(std::vector<std::string> neigh_vec, int cord[]);
		Country(std::string str);
		Country(int cord[]);
		
		//declared variables
		std::vector<Country> store_vec;
		vector<Country> Country_linker(vector<Country> cntry);
	
		//getters
		std::string getname();
		std::string getowner();
		std::string getcontinent();
		std::string getneigh(int pos);
		int getcord1();
		int getcord2();
		
		Country* getN_Ptr(int pos);
		Country getN_Cntry(int pos);
		vector<std::string> getN_vec();
	
		//setters
		void setname(std::string new_name);
		void setowner(std::string new_owner);
		void setcord1(int new_cord1);
		void setcord2(int new_cord2);
		void setN_ptr(int pos, Country *point);
		
		//methods
		void Country_store(Country contr);

		void disp_count(Country count);
		void disp_N(Country cntry);
		void disp_neigh_ptr(Country cntry);
		
		

	private:
		
		//private instance variables 
		std::string name;
		std::string owner;
		std::string continent;
		int cord1, cord2;
		std::vector<std::string> neigh_vec;
		int num_of_neigh;
		std::vector<Country*> count_ptr_vec;
		
	
};

#endif