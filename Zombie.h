#ifndef _Zombie_H
#define _Zombie_H

#include <vector>

#include "Organism.h"

class Zombie : public Organism
{
	protected:
	int biteTimer = 0;
	int starveTimer = 0;
	bool hasEaten = false;

public:
	Zombie();
	Zombie( City *city, int size, int row, int col );
	~Zombie() override = default;

	void turn(); //all things a zombie may do on their turn. i.e. an eat/move or a regular move, and if allowed a bite or convert back to human
	vector<pair<int, int>> findSpaces();
	vector<pair<int, int>> findFood();
	void move();

	void bite();

	void starve();
};

#endif
