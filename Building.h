

#ifndef BUILDING_H
#define BUILDING_H

#include "Organism.h"
#include <vector>

#include "Organism.h"

using namespace std;

class Building : public Organism {
protected:
    bool occupied = false;
    int buildingDecay = 5;
    Organism *humanOccupant;
public:
    Building();
    Building( City *city, int size, int row, int col);

    bool getOccupied();

    void leaveBuilding(int x, int y);

    void enterBuilding(Organism *organism, int x, int y);

    ~Building() override = default;

    void turn();

    void state();

    void humanMovement();

    void grow();

    vector<pair<int, int>> findSpaces();

};



#endif //BUILDING_H
