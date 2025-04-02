#ifndef _Organism_H
#define _Organism_H

#include <iostream>

using namespace std;

class City;

class Organism
{
protected:
	int x;
	int y;
	int size;
	bool moved;
	City *city;
	char type;

public:
	Organism();
	Organism( City *city, int size);
	virtual ~Organism();
	virtual void turn() = 0;
	void changeMoveState(); //moved is protected, need a way to access it
	char getType(); //type is protected, need a way to access it

	friend ostream& operator<<( ostream &output, Organism *organism );
};

#endif
