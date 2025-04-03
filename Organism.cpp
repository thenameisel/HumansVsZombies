//
// Created by El Wisman, w0497862, on 3/26/2025.
//

#include "Organism.h"

#include "City.h"
using namespace std;

Organism::Organism() {

}

Organism::Organism(City *city, int inSize, int row, int col) {
    moved = true; //everything starts existence having moved.
    this->city = city;
    size = inSize;
    x = row;
    y = col;
}

void Organism::changeMoveState() {
    moved = false;
}

char Organism::getType() {
    return type;
}

