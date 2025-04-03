
#include "City.h"
#include "Building.h"

#include <random>
#include <vector>
#include <algorithm>

#include "Organism.h"

using namespace std;

Building::Building() : Organism() {

}

Building::Building(City *city, int size, int row, int col) : Organism(city, size, row, col) {
    type = BUILDING_CH;
    cout << "Building created!" << endl;
}

vector<pair<int, int>> Building::findSpaces() {
    vector<pair<int, int>> emptySpaces;

    //for every way buildings can go, look to see if its open
    for (int direct = 0; direct < 4; direct++) {
        int nextX = directionOffsets[direct].first + x;
        int nextY = directionOffsets[direct].second + y;

        if (nextX < 0 || nextX >= size || nextY < 0 || nextY >= size) {
            continue;
        }
        //if passed gate if continue:
        Organism *adjacentCell = city->getOrganism(nextX, nextY);
        if (adjacentCell == nullptr) {
            emptySpaces.push_back( pair(nextX, nextY) );
        }
    }
    return emptySpaces;
}

void Building::turn() {
    //if unoccupied, buildingDecay goes up. if occupied it goes down.
    //if it gets to BUILDING_COLLAPSE, it is deleted.
    this->state();
}

void Building::state() {
    if (occupied) {buildingDecay--;} else {buildingDecay++;}

    if (buildingDecay >= BUILDING_COLLAPSE) {
        city->removeOrganism(x,y);
    } else if (buildingDecay <= 0) {
        this->grow();
    }
}

void Building::grow() {
    random_device rd;
    mt19937 gen(rd());
    vector<pair<int, int>> emptySpaces = findSpaces();

    if (!emptySpaces.empty()) {
        shuffle(emptySpaces.begin(), emptySpaces.end(), gen);
        Organism *newHuman = new Building(city, size,emptySpaces[0].first, emptySpaces[0].second);
        city->setOrganism(newHuman, emptySpaces[0].first, emptySpaces[0].second);
    }
}
