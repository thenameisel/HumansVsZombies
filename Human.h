#ifndef _Human_H
#define _Human_H

#include "Organism.h"
#include <vector>

class Human : public Organism
{
protected:
	int recruitTimer = 0;
public:
	Human(); 
	Human( City *city, int size, int row, int col);
	~Human() override = default;

	void turn(); //all things a human may do on their turn. i.e. a move, and if allowed a recruitment

	vector<pair<int, int>> findSpaces();

	vector<pair<int, int>> findEmptySpaces();

	void move();
	void recruit();

	void setPosition(int x, int y);
};

#endif
