//
// Created by El Wisman, w0497862, on 3/26/2025.
//

#include "City.h"
#include "Human.h"

#include <vector>
#include <random>
#include <algorithm>

#include "Organism.h"

using namespace std;
//default constructor
Human::Human() : Organism() {

}
//Parm constructor
Human::Human(City *city, int size, int row, int col) : Organism(city, size, row, col) {
    type = HUMAN_CH;
    cout << "Human created!" << endl;
}

void Human::turn() {
    //if it hasn't moved, then do the actions
    if (!moved) {
        //Move
        this->move();
        //Recruit
        this->recruit();
    }
}

//helper function to find empty spaces
vector<pair<int, int>> Human::findSpaces() {
    vector<pair<int, int>> emptySpaces;

    //for every way humans can go, look to see if its open
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

void Human::move() {
    random_device rd;
    mt19937 gen(rd());
    vector<pair<int, int>> emptySpaces = findSpaces();

    if (!emptySpaces.empty()) {
        shuffle(emptySpaces.begin(), emptySpaces.end(), gen);
        city->setOrganism(this, emptySpaces[0].first, emptySpaces[0].second);
        city->setOrganism(nullptr, x, y);
        x = emptySpaces[0].first;
        y = emptySpaces[0].second;
    }
    this->moved = true;
}

void Human::recruit() {
    recruitTimer++;
    random_device rd;
    mt19937 gen(rd());

    if (recruitTimer >= HUMAN_BREED) {
        vector<pair<int, int>> emptySpaces = findSpaces();
        if (!emptySpaces.empty()) {
            shuffle(emptySpaces.begin(), emptySpaces.end(), gen);
            Organism *newHuman = new Human(city, size,emptySpaces[0].first, emptySpaces[0].second);
            city->setOrganism(newHuman, emptySpaces[0].first, emptySpaces[0].second);

        }
        //reset the timer
        recruitTimer = 0;
    }
}
