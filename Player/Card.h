/* Card.h
* Header file for the class Card.
* Created on: Sept. 2017 for COMP345-Assignment1.
* Author: Team 11, Javier Fernandez-Rial, Portela ID 40044982
*/


#pragma once


using namespace std;

enum Type { INFANTRY, CAVALRY, ARTILLERY }; //a card object can only have one of these three types

class Card {

private:

	Type type;

public:

	Card(Type t);

	Card();

	Type getType() const {
		return type;
	}

	void setType(Type t) {
		type = t;
	}

};


