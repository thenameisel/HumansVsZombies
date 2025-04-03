

#ifndef BUILDING_H
#define BUILDING_H

#include "Organism.h"
#include <vector>

using namespace std;

class Building : public Organism {
protected:
    bool occupied = false;
    int buildingDecay = 0;
public:
    Building();
    Building( City *city, int size, int row, int col);
    ~Building() override = default;

    void turn();

    void state();

    void grow();

    vector<pair<int, int>> findSpaces();

};



#endif //BUILDING_H
