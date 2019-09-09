#include "game.h"
#include "Human.h"
#include "Aggressive.h"
#include "Benevolent.h"
#include "Cheater.h"
#include "Random.h"

#include "playerClass.h"




int main()
{
	//Creates the strategic objects
	Human* h = new Human();
	
	Aggressive* a = new Aggressive();
	
	Benevolent* b = new Benevolent();

	Random* r = new Random();
	
	Cheater* ch = new Cheater();
	
	//creates the map and game objects
	Map board;
	
	start match;
	
	//loads map
	board = match.MapStartUp();
	
	//loads players
	match = match.PlayerStartUp();
	
	//creates game
	game risk("Ass2", match);
	
	//assigns human aggressive and benevolent players
	for(int i=0; i<risk.getCastSize(); i++)
	{
		if(i ==0)
		{
			risk.getPlayer(i).setStrategy(h);
		}
		
		if(i == 1)
		{
			risk.getPlayer(i).setStrategy(ch);
		}
		
		if(i == 2)
		{
			risk.getPlayer(i).setStrategy(h);
		}
	}
	
	//randomizes the mao
	risk.RandomCountries(board);
	
	risk.OrderCountries(board);
	
	//allocates the countries and randomly distributes the units
	risk.AllocateCountries(board);
	
	//runs the game
	risk.MainGame(board);

	system("PAUSE");

	return 0;
}
