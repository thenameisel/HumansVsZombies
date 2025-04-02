//
// Created by El Wisman, w0497862, on 3/26/2025.
//

#include "City.h"
#include "Zombie.h"
#include "Organism.h"

#include <vector>
#include <random>
#include <algorithm>

using namespace std;
//default constructor
Zombie::Zombie() : Organism() {

}
//parm constructor
Zombie::Zombie(City *city, int size, int row, int col) : Organism(city, size, row, col) {
    type = ZOMBIE_CH;
}

// Zombie::~Zombie() {
//     if (this != nullptr) {delete this;}
// }

void Zombie::turn() {
    if (!moved) {
        //Move
        this->move();
        //Recruit

        //Starve
    }
}

vector<pair<int, int>> Zombie::findSpaces() {
    vector<pair<int, int>> emptySpaces;
    //for every way zombies can go, look to see if its open
    for (int direct = 0; direct < 8; direct++) {
        int nextX = directionOffsets[direct].first + x;
        int nextY = directionOffsets[direct].second + y;

        if (nextX < 0 || nextX >= size || nextY < 0 || nextY >= size) {
            //cout << "Zombie::move() was out of bounds" << endl;
            //cout << "x: " << x << ", y: " << y << " Size: "<< size << endl;
            continue;
        }
        //if passed gate if continue:
        Organism *adjacentCell = city->getOrganism(nextX, nextY);
        //cout << "Cell contents fetched" << endl;
        if (adjacentCell == nullptr) {
            emptySpaces.push_back( pair(nextX, nextY) );
        }
    }
    return emptySpaces;
}

void Zombie::move() {
    random_device rd;
    mt19937 gen(rd());
    vector<pair<int, int>> emptySpaces = findSpaces();

    if (!emptySpaces.empty()) {
        shuffle(emptySpaces.begin(), emptySpaces.end(), gen);
        //cout << "Zombie is moving from " << x << ", " << y << " to " << emptySpaces[0].first << ", " << emptySpaces[0].second << endl;
        city->setOrganism(this, emptySpaces[0].first, emptySpaces[0].second);
        city->setOrganism(nullptr, x, y);
        x = emptySpaces[0].first;
        y = emptySpaces[0].second;

    }
    //cout << "Zombie move complete, turning state to off" << endl;
    this->moved = true;
}