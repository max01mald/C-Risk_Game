//============================================================================
// Name        : DiceFactory.cpp
// Author      : Mair
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "DiceFactory.h"

DiceFactory::DiceFactory()
{
	numDiceRolls = 0;
	count = 0;
	size = 0;
	for(int i = 0 ; i < 6; i++)
		countArray[i] = 0;
	vector<int> v;
}


//return an element of the dice percentage array
double DiceFactory::getDicePercentageArray(int i)
{
	return diceValuePercentage[i];
}

int DiceFactory::getCountArrayElement(int i)
{
	return countArray[i];
}

//return the current count of dice rolls
int DiceFactory::getCount()
{
	return count;
}

int DiceFactory::getNumDiceRolls()
{
	return numDiceRolls;
}

void DiceFactory::setNumDiceRolls(int numOfRolls)
{
	numDiceRolls = numOfRolls;
}

int DiceFactory::random(int a, int b) {
	thread_local std::mt19937 eng{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(a, b);
	return dist(eng);
}

void DiceFactory::dicePercentage(int dicesRolled)
{
	//set the double out put to 2 digits after the decimal point
	cout.setf(ios:: fixed);
	cout.setf(ios:: showpoint);
	cout.precision(2);

	//the following values are used to ensure that dice rolls will be between 1-6
	int rand1 = 0;

	//this statement will make it so the random numbers won't repeat everytime
	srand(time(NULL));
	

	//count is used to keep track of how many dice rolls we did

	//these array will keep track to the percentage of each respective dice roll
	/*
	 * The element of the following array corresponds to the count of each dice roll
	 * 0 reprensents 1 value
	 * 1 represent 2 value rolled
	 * 2 is 3 value rolled and so on
	 */


	int length = sizeof(diceValuePercentage) / sizeof(*diceValuePercentage);

	for(int i = 0; i < dicesRolled; i++)
	{
		//randomly select a value from 1 - 6
		
		rand1 = random(1, 6);
		cout << "value rolled is: " << rand1 << endl;
		//store value in the container
		v.push_back(rand1);
		//increment dice count
		count++;

		switch(rand1)
		{
			case 1:
				countArray[0]++;
				diceValuePercentage[0] = (countArray[0] / (double) count) * 100;
				for(int i = 0; i < length; i++)
					diceValuePercentage[i] = (countArray[i] / (double) count) * 100;
				break;
			case 2:
				countArray[1]++;
				diceValuePercentage[1] = (countArray[1]/ (double) count) * 100;
				for(int i = 0; i < length; i++)
					diceValuePercentage[i] = (countArray[i] / (double) count) * 100;
				break;
			case 3:
				countArray[2]++;
				diceValuePercentage[2] = (countArray[2]/ (double) count) * 100;
				for(int i = 0; i < length; i++)
					diceValuePercentage[i] = (countArray[i] / (double) count) * 100;
				break;
			case 4:
				countArray[3]++;
				diceValuePercentage[3] = (countArray[3]/ (double) count) * 100;
				for(int i = 0; i < length; i++)
					diceValuePercentage[i] = (countArray[i] / (double) count) * 100;
				break;
			case 5:
				countArray[4]++;
				diceValuePercentage[4] = (countArray[4] / (double) count) * 100;
				for(int i = 0; i < length; i++)
					diceValuePercentage[i] = (countArray[i] / (double) count) * 100;
				break;
			case 6:
				countArray[5]++;
				diceValuePercentage[5] = (countArray[5]/ (double) count) * 100;
				for(int i = 0; i < length; i++)
					diceValuePercentage[i] = (countArray[i] / (double) count) * 100;
				break;
			default:
				cout << "Nothing for now" << endl;
		}//end of switch
	}//end of for loop
}// end of method

/*
 * Display the percentage of all individual dice values rolled
 */
void DiceFactory::displayAllIndividualPercentages()
{
	int length = sizeof(diceValuePercentage) / sizeof(*diceValuePercentage);

	for(int i = 0; i < length; i++)
	{
		cout << "Dice roll " << (i+1) << " Percentage: " << diceValuePercentage[i] << "%" << endl;
	}
}
