//
// Created by El Wisman, w0497862, on 3/26/2025.
//

#include "City.h"
#include "Zombie.h"
#include "Organism.h"

using namespace std;
//default constructor
Zombie::Zombie() : Organism() {

}
//parm constructor
Zombie::Zombie(City *city, int size) : Organism(city, size) {
    type = ZOMBIE_CH;
}

Zombie::~Zombie() {
    if (this != nullptr) {delete this;}
}

void Zombie::turn() {
    //Move

    //Recruit

    //Starve
}