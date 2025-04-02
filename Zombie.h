#ifndef _Zombie_H
#define _Zombie_H

#include <bits/stl_vector.h>

#include "Organism.h"

class Zombie : public Organism
{
public:
	Zombie();
	Zombie( City *city, int size, int row, int col );
	//virtual ~Zombie();

	void turn(); //all things a zombie may do on their turn. i.e. an eat/move or a regular move, and if allowed a bite or convert back to human
	vector<pair<int, int>> findSpaces();

	void move();
};

#endif
