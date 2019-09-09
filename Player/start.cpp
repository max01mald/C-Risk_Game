/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 2 due 26 October 2017
*/

#include "start.h"
#include "vector"



//Constuctors
start::start(): name("Noone")
{
	vector<file> folder;
	vector<playerClass> cast;	
				
}
		
start::start(std::string New_name): name(New_name) 
{
	vector<file> folder;
	vector<playerClass> cast;
		
}
		
//getters
std::string start::getFile(std::string name)
{
	//this returns the file by searching for the matching name
	std::string temp;
			
	for (int i=0; i<folder.size(); i++)
	{
		if(name == folder[i].getInfo())
		{
			temp = folder[i].getInfo();
		}
	}
	return temp;
}

std::string start::getFile(int number)
{
	//this returns the file by placement in the vector
	std::string temp;
	
	temp = folder[number-1].getInfo();
	
	return temp;
}
		
		
playerClass& start::getPlayer(std::string name)
{
	//this return the player by searching by name
	int store = 0;
			
	for (int i=0; i<cast.size(); i++)
	{
		
		
		if(name == cast[i].getPlayerName())
		{
			store = i;
		}
	}
	
	return cast[store];
}
	
	
void start::setFile(std::string name)
{
	//this creates a file and stores it in the vector
	file f(name);
	
	folder.push_back(f);
}	

void start::setCast(int unit, int order, std::string name)
{	
	playerClass temp(name, unit, order);
	
	cast.push_back(temp);
	
}

void start::OrderCast()
{
	playerClass temp;
	
	for (int i=0; i< cast.size()-1; i++)
	{
		for (int j= 1; j < cast.size(); j++)
		{
			if(cast[i].getPlayerOrder() > cast[j].getPlayerOrder())
			{
				temp = cast[i];
				cast[i] = cast[j];
				cast[j] = temp;
			}

		}
	}

}

void start::PlayerSelection()
{
	//this creates the cast of players who be playing in the game 
	// the user gets to chose a number of players between a set parameter
	int number = 0;
	int exit = 0;
	string name = "Player ";
	string temp = "";
	char num = '0';
	cout << "Select the number of players you want to play with (2-6)" << endl;
		
	while(exit != -1)
	{
		cin >> number;  
		
		if (number >= 2 && number <= 6)
		{
			exit = -1;
		}
		else 
		{
			cout << "Please select a valid number" << endl; 
		}
	}
	
	for(int i=0; i<number; i++)
	{
		num += i+1;
		temp = name + num;
		
		setCast((40 - ((number - 2) * 5)),rand() % 100,temp);
		
		temp = "";
		num = '0';
	}
	
	cout << "Successfully generated player cast" << endl;
	
}


void start::setCast(int unit, int order, string name, string type)
{	
	name = "";
	
	Human* h = new Human;
	
	Aggressive* a = new Aggressive;
	
	Benevolent* b = new Benevolent;
	
	Random* r = new Random;
	
	Cheater* c = new Cheater;
	
	if(type == "b")
	{
		name = "Benevolent";
	}
	
	if(type == "c")
	{
		name = "Cheater";
	}
	
	if(type == "r")
	{
		name = "Random";
	}
	if(type == "a")
	{
		name = "Aggressive";
	}
	
	playerClass temp(name, unit, order);
	
	if(type == "b")
	{
		temp.setStrategy(b);
	}
	
	if(type == "c")
	{
		temp.setStrategy(c);
	}
	
	if(type == "r")
	{
		temp.setStrategy(r);
	}
	if(type == "a")
	{
		temp.setStrategy(a);
	}
	
	cast.push_back(temp);
	
}

void start::PlayerSelection(int pos)
{
	//this creates the cast of players who be playing in the game 
	// the user gets to chose a number of players between a set parameter
	int number = 0;
	int break1 = 0;
	string name = "Player ";
	string temp = "";
	char num = '0';
	string type = "x";
	number = pos;  
		
	for(int i=0; i<number; i++)
	{
		num += i+1;
		temp = name + num;
		
		
		
		while(break1 != -1)
		{
			cout << "What kind of Player do you want to assign to this player\nc = Cheater\nr = Random\nb = Benevolent\na = Aggressive\n" << endl;
			
			cin >> type;
			
			if(type == "c" || type == "h" || type == "r" || type == "b" || type == "a")
			{
				cout << "Player has been created" << endl;
				break1 = -1;	
			}
		
		}
		break1 = 0;
		
		
		setCast((40 - ((number - 2) * 5)),rand() % 100, temp, type);
		
		temp = "";
		num = '0';
	}
	
	
}

start start::PlayerStartUp(int pos)
{

	//this creates the cast by calling playerselection()
	start game("Ass2");
	
	game.PlayerSelection(pos);
	
	game.OrderCast();

	return game;
}

void start::displayFolder()
{
	//this prints out the folder vector
	for (int i=0; i<folder.size(); i++)
	{
		cout<< i+1 << " " << folder[i].getInfo() << endl;
	}

} 



Map start::MapStartUp()
{
	//this runs the get map, check map, and link map, finally storing the
	//continent and country vectors in a map object and returns it
	start game("Ass2");
	Map board;
	
	//these are the loaded maps for the game
	game.setFile("3D");
	game.setFile("World");
	game.setFile("Andorra");
	game.setFile("Atlantis");
	game.setFile("Labyrinth");
	
	int exit = 0;
	int number = 0;
	std::string temp;
	
	//this loop selects a map and builds it, only a valid map is returned
	while(exit != -1)
	{
		cout << "Select a file to run " << endl;
	
		game.displayFolder();
		
		cin >> number;
		
		
		temp = game.getFile(number);
		
		board = board.MapLinker(temp);
		
		if(board.getName() != "Noone")
		{
			exit = -1;
		}
			
	}
	
	return board;


}

Map start::MapStartUp(int pos)
{
	//this runs the get map, check map, and link map, finally storing the
	//continent and country vectors in a map object and returns it
	start game("Ass2");
	Map board;
	
	//these are the loaded maps for the game
	game.setFile("3D");
	game.setFile("World");
	game.setFile("Andorra");
	game.setFile("Atlantis");
	game.setFile("Labyrinth");
	
	int exit = 0;
	int number = 0;
	std::string temp;
	
	//this loop selects a map and builds it, only a valid map is returned
	while(exit != -1)
	{
		
		game.displayFolder();
		
		number = pos;
		
		
		temp = game.getFile(number);
		
		board = board.MapLinker(temp);
		
		if(board.getName() != "Noone")
		{
			exit = -1;
		}
			
	}
	
	return board;


}


start start::PlayerStartUp()
{

	//this creates the cast by calling playerselection()
	start game("Ass2");
	
	game.PlayerSelection();
	
	game.OrderCast();

	return game;
}

