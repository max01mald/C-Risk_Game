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
		Map(std::string new_name);
		
		//mehtod
		void Runner(vector<Continent> conti, vector<Country> cntry);
		
		
	private:
		//object instance variables
		std::string name;
};

#endif