/* card.cpp
* Source file for the class Card.
* Created on: Sept. 2017 for COMP345-Assignment1.
* Author: Team 11, Javier Fernandez-Rial, Portela ID 40044982
*/


#include "Card.h"
using namespace std;

Card::Card(Type t) {

	type = t;
}

Card::Card() { //default constructor that sets the type to INFANTRY

	type = INFANTRY;
}


