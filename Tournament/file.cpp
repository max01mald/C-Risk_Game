/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 2 due 26 October 2017
*/

#include "file.h"

//Constructors
file::file(): name("noname"), tag(".map")
{
}

file::file(std::string New_name): name(New_name), tag(".map")
{
}
