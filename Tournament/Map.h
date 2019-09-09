/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 1 due 28 September 2017
*/

#ifndef MAP_H
#define MAP_H
#include "filler.h"


#include <iostream>


//class map
class Map
{
	
	public:
		//map constructor
		Map();
		Map(std::string new_name);
		Map(std::string new_name, vector<Continent> Cont, vector<Country> Count);
		
		//getters
		std::string getName(){return name;};
		vector<Continent>& getContinents(){return Continent_vector;};
		vector<Country>& getCountries(){return Country_vector;};
		Country& getCountry(int pos) {return Country_vector[pos];};
		int getAmountCountries(){return Country_vector.size();};
		
		//setters
		void setCountryName(int pos, string str) {getCountry(pos).setname(str);};
		
		//mehtod
		bool MapCheck(vector<Continent> MCCo_vec, vector<Country> MCCy_vec);
		bool CountryCheck(vector<Country> CyC_vec);
		bool ContCheck(vector<Continent> CC_vec);
		
		void RandomCountries();
		
		void Runner(vector<Continent> conti, vector<Country> cntry);
		
		vector<Continent> MapLoaderContinent(std::string name, vector<Country> MLC_vec);
		vector<Country> MapLoaderCountry(std::string name);
		Map MapLinker(std::string name);
		
		
		
	private:
		//object instance variables
		std::string name;
		vector<Continent> Continent_vector;
		vector<Country> Country_vector;
};

#endif