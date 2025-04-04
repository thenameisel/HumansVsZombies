
#include "City.h"
#include "Building.h"

#include <random>
#include <vector>
#include <algorithm>

#include "Human.h"
#include "Organism.h"

using namespace std;

Building::Building() : Organism() {

}

Building::Building(City *city, int size, int row, int col) : Organism(city, size, row, col) {
    type = BUILDING_CH;
    cout << "Building created!" << endl;
}

bool Building::getOccupied() {
    return occupied;
}

//Human leaves building
void Building::leaveBuilding( int x, int y ) {
    city->setOrganism(humanOccupant, x, y);
    if (Human* human = dynamic_cast<Human*>(humanOccupant)) {
        human->setPosition(x, y);
    }
    humanOccupant = nullptr;
    occupied = false;
    buildingDecay = 5;
    cout << "Human left building!" << endl;
}

//set Organism into the building
void Building::enterBuilding( Organism *organism, int x, int y ) {
    humanOccupant = organism;
    occupied = true;
    cout << "Human entered building!" << endl;
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
    //if occupied there's a chance the human will leave
    if (occupied){this->humanMovement();}
}

void Building::state() {
    if (occupied) {buildingDecay--;} else {buildingDecay++;}

    if (buildingDecay >= BUILDING_COLLAPSE) {
        cout << "Building collapsed!" << endl;
        city->removeOrganism(x,y);
    } else if (buildingDecay <= 0) {
        this->grow();
    }
}

void Building::humanMovement() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, HUMAN_LEAVE_CHANCE);
    int randomValue = dist(gen);

    if (randomValue == 0) {
        vector<pair<int, int>> emptySpaces = findSpaces();
        shuffle(emptySpaces.begin(), emptySpaces.end(), gen);
        if (!emptySpaces.empty()) {
            leaveBuilding(emptySpaces[0].first,emptySpaces[0].second);
        }
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
