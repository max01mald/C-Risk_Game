/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 2 due 26 October 2017
*/

#ifndef FILE_H
#define FILE_H

#include <iostream>


using namespace std;




class file{



	public:
		//Constructors
		file();
		file(std::string New_name);
		
		//Getters
		std::string getInfo(){return name+tag;};
		std::string getTag(){return tag;};
	
	private:	
		std::string name;
		std::string tag;


};







#endif