/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 1 due 28 September 2017
*/

#include "Map.h"

int main()
{
	//creates dumby variables
	std::string map;
	
	Map Playing("1");
	
	Continent world("world", 0, 0);
	
	Country geo("world");
	
	filler fill("wker");
	
	//requests the name of the file and checks for 1st level is map verification
	fill.request_map();
	
	fill.open_map(map);
	
	fill.is_file();
	
	//fills the appropriate country and continent vectors
	vector<Country> country_vec = fill.Countr_fill();
	
	fill.close_map();
	
	fill.open_map(map);
	
	vector<Continent> cont_vec = fill.Cont_fill(country_vec);
	
	fill.close_map();
	
	//links the objects in the vectors
	cont_vec = world.Continent_linker(cont_vec, country_vec);
	
	country_vec = geo.Country_linker(country_vec);
	
	//runs the map runner algorithm which allows the user to travel the 
	//created map
	Playing.Runner(cont_vec, country_vec);

	return 0;
}