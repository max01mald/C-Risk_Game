/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 1 due 28 September 2017
*/


#ifndef FILLER_H
#define FILLER_H

#include "Continent.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::cin;
using std::cout;


class filler
{
	public:
		//Constructor
		filler();
		filler(std::string stream_op);
		
		//variables
		std::string map_name;
		std::ifstream inStream;
		std::string name;
		std::string store;
		int number, counter, amount;
		char line;
		int cord_store[2];
		
		
		//Getters
		std:: string getname();
		
		//file functions
		std::string request_map();
		void open_map(std::string);
		void close_map();
		void is_file();
		
		//Mehtods
		vector<Continent> Cont_fill(vector<Country> cntry, std::string S_name);
		vector<Country> Countr_fill(std::string S_name);
		int count_countries(std::string, vector<Country> cntry);
		
		//void link_check(vector<Continent> conti, vector<Country> cntry);
		
		void disp_cord(int cord_store[]);
		void disp_neigh(std::vector<string> neigh_s);
		
	private:
		//filler object instaces
		std::string stream_name;
		std::vector<std::string> neigh_s;
};
#endif