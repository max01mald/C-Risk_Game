#include "game.h"
#include "Human.h"
#include "Aggressive.h"
#include "Benevolent.h"
#include "Cheater.h"
#include "Random.h"

#include "playerClass.h"




int main()
{
	//creates the map and game objects
	Map board;
	
	start match;
	
	//loads map
	
	int N_MAP;
	int N_PL;
	int N_G;
	int N_D;
	
	int break1 = 0;
	
	
	while(break1 != -1)
	{
		cout<<"Please Select the number of Maps (1-5)" << endl;
		
		cin >> N_MAP;
		
		if(N_MAP>0 && N_MAP < 6)
		{
			break1 = -1;
		}
	}
	
	break1 = 0;
	
	
	while(break1 != -1)
	{
		cout<<"Please Select the number of Players (2-4)" << endl;
		
		cin >> N_PL;
		
		if(N_PL>1 && N_PL < 5)
		{
			break1 = -1;
		}
	}
	
	match = match.PlayerStartUp(N_PL);
	
	break1 = 0;
	
	
	while(break1 != -1)
	{
		cout<<"Please Select the number of Games (1-5)" << endl;
		
		cin >> N_G;
		
		if(N_G>0 && N_G < 6)
		{
			break1 = -1;
		}
	}
	
	break1 = 0;
	
	
	while(break1 != -1)
	{
		cout<<"Please Select the max number of rounds in a Game (10-50)" << endl;
		
		cin >> N_D;
		
		if(N_D>9 && N_D < 51)
		{
			break1 = -1;
		}
	}
	
	break1 = 0;
	
	
	int cMap = 1;
	int cG = 1;
	int cP = 1;
	int cPlayed = 0;
	string result;
	vector<string> map_store;
	vector<string> game_store;
	vector<string> result_store;
	
	while(break1 != -1)
	{
		
		if(cMap <= N_MAP)
		{
			
			board = match.MapStartUp(cMap);
			
			map_store.push_back(board.getName());
			
			while{
			
			if(cG <= N_G)
			{
			string temp = to_string(cG);
			string gName = "Game ";
			gName = gName + temp;
			game risk(gName, match);
			cG += 1;
		
			game_store.push_back(risk.getName());
			
			
			
			
			
			risk.RandomCountries(board);
	
			risk.OrderCountries(board);
	
			//allocates the countries and randomly distributes the units
			risk.AllocateCountries(board);
	
			//runs the game
			while(break1 != -1)
			{
				if(cPlayed <= N_G)
				{
					//result = risk.MainGame(board, N_D);
					result = "DRAW";
					result_store.push_back(result);
					
					cPlayed += 1;
				}
				else
				{
					break1 = -1;
				}
			}
			break1 = 0;
			cPlayed = 0;
			
			
		}
		else
		{
			break1 = -1;
		}
		cMap += 1;
		
		
	
	}
	
	
	cout << "Tournament Parameters" <<endl;
	cout << "M: ";
	
	for(int i=0; i<map_store.size(); i++)
	{
		if(i != map_store.size()-1)
		{
			cout << map_store[i] << ", ";
		}
		else
		{
			cout << map_store[i] << endl;
		}
	}
	
	cout << "P: ";
	
	for(int i=0; i<match.getVecSize(); i++)
	{
		if(i != match.getVecSize()-1)
		{
			cout << match.getPlayer(i).getPlayerName() << ", ";
		}
		else
		{
			cout << match.getPlayer(i).getPlayerName() << endl;
		}
	}
	
	cout << "G: " << N_G << endl;
	cout << "D: " << N_D << endl;
	cout << endl;
	
	cout << "Tournament Table" << endl;
	
	for(int i=0; i<N_MAP; i++)
	{
		if(i == 0)
		{
			cout << "\t\t\t";
			for(int j=0; j<N_G; j++)
			{
				cout << game_store[j] << "\t\t";
			}
			cout << endl;
		}
		
		for(int k=0; k<N_G; k++)
		{
			int jump = k * N_MAP;
			
			
			if(k==0)
			{	
				if(i ==0)
				{
					cout << map_store[i] << "\t\t\t";
				}
				else
				{
					cout << map_store[i] << "\t\t";
				}
				cout << result_store[i] << "\t\t"; 
			}
			else
			{
				cout << result_store[i + jump] << "\t\t";
			}
		}
		cout << endl;
		
	}
	
	
	

	return 0;
}
