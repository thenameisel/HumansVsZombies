//
// Created by El Wisman, w0497862, on 3/26/2025.
//

#include "City.h"
#include "Human.h"
#include "Organism.h"

using namespace std;
//default constructor
Human::Human() : Organism() {

}
//Parm constructor
Human::Human(City *city, int size) : Organism(city, size) {
    type = HUMAN_CH;
}

Human::~Human() {
    if (this != nullptr) delete this; {}
}

void Human::turn() {
    //Move
    this->move();
    //Recruit
}

void Human::move() {
    int directions =
}
