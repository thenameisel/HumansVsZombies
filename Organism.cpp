//
// Created by El Wisman, w0497862, on 3/26/2025.
//

#include "Organism.h"
using namespace std;

Organism::Organism() {

}

Organism::Organism(City *city, int size) {
    moved = true; //everything starts existence having moved.
}

void Organism::changeMoveState() {
    moved = !moved;
}
char Organism::getType() {
    return type;
}

