//
// Created by El Wisman, w0497862, on 3/26/2025.
//

#include "City.h"
#include "Zombie.h"
#include "Organism.h"

#include <vector>
#include <random>
#include <algorithm>

#include "Human.h"

using namespace std;
//default constructor
Zombie::Zombie() : Organism() {

}
//parm constructor
Zombie::Zombie(City *city, int size, int row, int col) : Organism(city, size, row, col) {
    type = ZOMBIE_CH;
    cout << "Zombie created!" << endl;
}

void Zombie::turn() {
    if (!moved) {
        //Move
        this->move();
        //Bite
        this->bite();
        //Starve
        this->starve();
    }
}

vector<pair<int, int>> Zombie::findSpaces() {
    vector<pair<int, int>> emptySpaces;
    //for every way zombies can go, look to see if its open
    for (int direct = 0; direct < 8; direct++) {
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

vector<pair<int, int>> Zombie::findFood() {
    vector<pair<int, int>> foodSpaces;
    for (int direct = 0; direct < 8; direct++) {
        int nextX = directionOffsets[direct].first + x;
        int nextY = directionOffsets[direct].second + y;

        if (nextX < 0 || nextX >= size || nextY < 0 || nextY >= size) {
            continue;
        }

        //if passed gate if continue:
        Organism *adjacentCell = city->getOrganism(nextX, nextY);
        if (adjacentCell != nullptr && adjacentCell->getType() != ZOMBIE_CH && adjacentCell->getType() != BUILDING_CH) {
            foodSpaces.push_back( pair(nextX, nextY) );
        }
    }
    return foodSpaces;
}

void Zombie::move() {
    random_device rd;
    mt19937 gen(rd());
    vector<pair<int, int>> emptySpaces = findSpaces();
    vector<pair<int, int>> foodSpaces = findFood();

    if (!foodSpaces.empty()) {
        shuffle(foodSpaces.begin(), foodSpaces.end(), gen);
        city->removeOrganism(foodSpaces[0].first, foodSpaces[0].second);
        city->setOrganism(this, foodSpaces[0].first, foodSpaces[0].second);
        city->setOrganism(nullptr, x ,y);
        x = foodSpaces[0].first;
        y = foodSpaces[0].second;
        hasEaten = true;
        starveTimer = 0;
    } else if (!emptySpaces.empty()) {
        shuffle(emptySpaces.begin(), emptySpaces.end(), gen);
        city->setOrganism(this, emptySpaces[0].first, emptySpaces[0].second);
        city->setOrganism(nullptr, x, y);
        x = emptySpaces[0].first;
        y = emptySpaces[0].second;
        starveTimer++;
    }  else {
        starveTimer++;
    }
    this->moved = true;
}

void Zombie::bite() {
    random_device rd;
    mt19937 gen(rd());
    biteTimer++;

    if (biteTimer >= ZOMBIE_BREED && hasEaten) {
        vector<pair<int, int>> foodSpaces = findFood();

        if (!foodSpaces.empty()) {
            shuffle(foodSpaces.begin(), foodSpaces.end(), gen);
            city->removeOrganism(foodSpaces[0].first, foodSpaces[0].second);
            Organism *newZombie = new Zombie(city, size,foodSpaces[0].first, foodSpaces[0].second);
            city->setOrganism(newZombie, foodSpaces[0].first, foodSpaces[0].second);

            biteTimer = 0;
            hasEaten = false;
        }
    }
}
void Zombie::starve() {
    if (starveTimer >= ZOMBIE_STARVE) {
        Organism *newHuman = new Human(city, size, x, y);
        city->setOrganism(newHuman, x, y);
        delete this;
    }
}