//
// Created by El Wisman, w0497862, on 3/26/2025.
//
#include "City.h"

#include <memory>
#include <random>
#include <iostream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
#include <conio.h>

#include "Building.h"
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
        if (grid[row][col] == nullptr ) {
            grid[row][col] = new Human(this, GRIDSIZE, row, col);
            human++;
        }
    }

    //populate Zombies on the board
    for (int zombie = 0; zombie < ZOMBIE_STARTCOUNT;) {
        int row = rd() % GRIDSIZE;
        int col = rd() % GRIDSIZE;
        if (grid[row][col] == nullptr ) {
            grid[row][col] = new Zombie(this, GRIDSIZE, row, col);
            zombie++;
        }
    }

    //populate Buildings on the board
    for (int building = 0; building < BUILDING_STARTCOUNT;) {
        int row = rd() % GRIDSIZE;
        int col = rd() % GRIDSIZE;
        if (grid[row][col] == nullptr ) {
            grid[row][col] = new Building(this, GRIDSIZE, row, col);
            building++;
        }
    }

}

//Destructor
City::~City() {
    if (grid != nullptr) {
        delete[] grid;
    }
}

int City::getGeneration() {
    return generation;
}

bool City::hasDiversity() {
    bool hasHumans = false;
    bool hasZombies = false;

    for (int row = 0; row < GRIDSIZE; row++) {
        for (int col = 0; col < GRIDSIZE; col++) {
            if (grid[row][col] != nullptr) {
                Organism *organism = getOrganism(row, col);
                char orgType = organism->getType();
                if (orgType == HUMAN_CH) {hasHumans = true;}
                else if (orgType == ZOMBIE_CH) {hasZombies = true;}
            }

        }
    }

    return hasHumans && hasZombies;
}

//get Organism from the grid
Organism *City::getOrganism( int x, int y ) {
    return grid[x][y];
}

//set Organism into the grid
void City::setOrganism( Organism *organism, int x, int y ) {
    grid[x][y] = organism;
}

//delete Organism from the grid
void City::removeOrganism( int x, int y ) {
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            if ((i != x || j != y) && grid[i][j] == grid[x][y]) {
                cout << "ERROR: Duplicate pointer at (" << i << "," << j << ")" << endl;
                cout << "ERROR: Original pointer at (" << x << "," << y << ")" << endl;
                return; // Don't delete - object exists elsewhere
            }
        }
    }
    if (grid[x][y] != nullptr) {
        delete grid[x][y];
        grid[x][y] = nullptr;
    }
}

//step/turn/dothing function
void City::step() {
    generation++;
    for (int row=0; row < GRIDSIZE; row++) {
        for (int col=0; col < GRIDSIZE; col++) {
            if (grid[row][col] != nullptr) { // check if something exists BEFORE pulling an organism
                Organism *organism = getOrganism(row, col);
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

void setColor(int colorId);
void resetColor();

//friend function for <<
ostream& operator<<( ostream &output, City &city ) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO originalInfo;
    GetConsoleScreenBufferInfo(hConsole, &originalInfo);

    for (int row=0; row < GRIDSIZE; row++) {
        for (int col=0; col < GRIDSIZE; col++) {
            if (city.grid[row][col] != nullptr) {
                Organism *currentOrg = city.getOrganism(row, col);
                char currentType = currentOrg->getType();
                if (currentType == ZOMBIE_CH) {
                    SetConsoleTextAttribute(hConsole, ZOMBIE_COLOR);
                } else if (currentType == HUMAN_CH) {
                    SetConsoleTextAttribute(hConsole, HUMAN_COLOR);
                } else if (currentType == BUILDING_CH) {
                    SetConsoleTextAttribute(hConsole, BUILDING_COLOR);
                }
                output << currentType;
                SetConsoleTextAttribute(hConsole, originalInfo.wAttributes);
            } else {
                SetConsoleTextAttribute(hConsole, DASH_COLOR);
                output << '-';
                SetConsoleTextAttribute(hConsole, originalInfo.wAttributes);
            }
        }
        output << endl;
    }
    SetConsoleTextAttribute(hConsole, originalInfo.wAttributes);
    return output;
}