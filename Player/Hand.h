#pragma once

using namespace std;


class Hand {

private:

	int size;

	int numOfInf;
	int numOfCav;
	int numOfArt;

public:

	Hand(); //default and only constructor, that initializes all values to 0.
	Hand(int inf, int cav, int art);
	int exchange();

	int getSize() const {
		return size;
	}

	void setSize(int i) {
		size = i;
	}

	int getNumOfInf() const {
		return numOfInf;
	}

	void setNumOfInf(int i) {
		numOfInf = i;
	}

	int getNumOfCav() const {
		return numOfCav;
	}

	void setNumOfCav(int i) {
		numOfCav = i;
	}

	int getNumOfArt() const {
		return numOfArt;
	}

	void setNumOfArt(int i) {
		numOfArt = i;
	}
};
