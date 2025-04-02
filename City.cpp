//
// Created by El Wisman, w0497862, on 3/26/2025.
//
#include "City.h"

#include <memory>
#include <random>

#include "Human.h"
#include "Organism.h"
#include "Zombie.h"

using namespace std;
random_device rd;
mt19937 gen(rd());

//City constructor
City::City() {

    //clear garbage data
    for (auto& row : grid) {
        for (auto& cell : row) {
            cell = nullptr;
        }
    }

    //populate the humans on the board
    for (int human = 0; human < HUMAN_STARTCOUNT;) {
        int row = rd() % GRIDSIZE;
        int col = rd() % GRIDSIZE;
        cout << human << " Humans on the board, looking to place one at " << row << "," << col << endl;
        if (grid[row][col] == nullptr ) {
            cout << "there was space" << endl;
            grid[row][col] = new Human(this, GRIDSIZE, row, col);
            human++;
            cout << "Human has been placed" << endl;
        }
    }

    //populate Zombies on the board
    for (int human = 0; human < ZOMBIE_STARTCOUNT;) {
        int row = rd() % GRIDSIZE;
        int col = rd() % GRIDSIZE;
        cout << human << " Zombies on the board, looking to place one at " << row << "," << col << endl;
        if (grid[row][col] == nullptr ) {
            cout << "there was space" << endl;
            grid[row][col] = new Zombie(this, GRIDSIZE, row, col);
            human++;
            cout << "Zombie has been placed" << endl;
        }
    }

}

//Destructor
City::~City() {
    if (grid != nullptr) {
        delete[] grid;
    }
}

//get Organism from the grid
Organism *City::getOrganism( int x, int y ) {
    return grid[x][y];
}

//set Organism into the grid
void City::setOrganism( Organism *organism, int x, int y ) {
    grid[x][y] = organism;
}

//step/turn/dothing function
void City::step() {
    for (int row=0; row < GRIDSIZE; row++) {
        for (int col=0; col < GRIDSIZE; col++) {
            if (grid[row][col] != nullptr) { // check if something exists BEFORE pulling an organism
                Organism *organism = getOrganism(row, col);
                //cout << organism->getType() << " is checking...."<< endl;
                organism->turn();
            }
        }

    }
}

//reset the turn bool function
void City::reset() {
    for (int row=0; row < GRIDSIZE; row++) {
        for (int col=0; col < GRIDSIZE; col++) {
            if (grid[row][col] != nullptr) { // check if something exists BEFORE pulling an organism
                Organism *organism = getOrganism(row, col);
                organism->changeMoveState();
                //cout << "a creature got its flag changed" << endl;
            }
        }

    }
}

//count the given char on the grid
int City::countType(char type) {
    int count = 0;
    for (int row=0; row < GRIDSIZE; row++) {
        for (int col=0; col < GRIDSIZE; col++) {
            if (grid[row][col] != nullptr) {
                Organism *organism = getOrganism(row, col);
                if (char orgType = organism->getType(); orgType == type) {count++;}
            }
        }
    }
    return count;
}


//Simple print for debugging
void City::debugPrint() {
    for (int row = 0; row < GRIDSIZE; row++) {
        for (int col = 0; col < GRIDSIZE; col++) {
            if (grid[row][col] != nullptr) {
                Organism *currentOrg = this->getOrganism(row, col);
                if (currentOrg != nullptr) {
                    char currentType = currentOrg->getType();
                    cout << currentType;
                } else {
                    cout << "?";
                }
            } else { cout << "-";}
        }
        cout << endl;
    }
}

//friend function for <<
ostream& operator<<( ostream &output, City &city ) {
    for (int row=0; row < GRIDSIZE; row++) {
        for (int col=0; col < GRIDSIZE; col++) {
            if (city.grid[row][col] != nullptr) {
                Organism *currentOrg = city.getOrganism(row, col);
                char currentType = currentOrg->getType();
                output << currentType;
            } else {output << '-';}
        }
        output << endl;
    }
    return output;
}