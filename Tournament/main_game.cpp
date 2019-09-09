/*
	Author: Maximilien Malderle
	ID: 26562906
	Assignment 2 due 26 October 2017
*/

#include "game.h"


int main()
{
	Map board;
	
	start match;
	
	board = match.MapStartUp();
	
	match = match.PlayerStartUp();
	
	game risk("Ass2", match);
	
	risk.RandomCountries(board);
	
	risk.OrderCountries(board);
	
	risk.AllocateCountries(board);
	
	risk.MainGame(board);

	return 0;
}


