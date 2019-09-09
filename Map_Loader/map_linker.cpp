/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 1 due 28 September 2017
*/

#include "filler.h"

int main()
{
	//creates dumby variables
	std::string map;
	
	filler fill("wker");
	
	Continent world("empty", 0, 0);
	
	Country geo("empty");
	
	//requests the name of the file and checks for 1st level is map verification
	fill.request_map();
	
	fill.open_map(map);
	
	fill.is_file();
	
	//fills the vectors (no linking)
	vector<Country> country_vec = fill.Countr_fill();
	
	fill.close_map();
	
	fill.open_map(map);
	
	vector<Continent> cont_vec = fill.Cont_fill(country_vec);
	
	fill.close_map();
	
	//links the contents of the vectors
	cont_vec = world.Continent_linker(cont_vec, country_vec);
	
	country_vec = geo.Country_linker(country_vec);
	
	//displays the contents of both vectors
	//Countries and Continents
	std::cout<< std::endl <<"Here are the Contients with their associated number of Countries" << std::endl;
	
	cont_vec[0].Disp_Continent(cont_vec);
	
	std::cout<<std::endl;
	
	std::cout<<"Here are the countries on the map" << std::endl << std::endl;
	for (int i=1; i<country_vec.size(); i++)
	{
		country_vec[0].disp_count(country_vec[i]);
		std::cout<<std::endl;
	}
	
	
	
	//world.Disp_store();
}