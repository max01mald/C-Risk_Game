//#include "stdafx.h"
//#include <stdio>
#include "Hand.h"
#include <iostream>
using namespace std;

Hand::Hand()
{

	size = 0;

	numOfInf = 0;
	numOfCav = 0;
	numOfArt = 0;
}

Hand::Hand(int inf, int cav, int art)
{
	numOfInf = inf;
	numOfCav = cav;
	numOfArt = art;
	size = inf + cav + art;
}

int counter = 0;
int Hand::exchange() {


	if (size < 3) {
		cout << "Not enough cards, you need at least 3." << endl;
		return 0;
	}

	if (numOfInf >= 3) {
		numOfInf -= 3;
		counter++;
		return 5 * counter;
	}
	if (numOfCav >= 3) {
		numOfCav -= 3;
		counter++;
		return 5 * counter;
	}
	if (numOfArt >= 3) {
		numOfArt -= 3;
		counter++;
		return 5 * counter;
	}
	if (numOfInf > 0 && numOfCav > 0 && numOfArt > 0) {
		numOfInf -= 1;
		numOfCav -= 1;
		numOfArt -= 1;
		counter++;
		return 5 * counter;
	}

	cout << "There is no combination of cards, you need 3 of the same type or one of each." << endl;
	return 0;

}
