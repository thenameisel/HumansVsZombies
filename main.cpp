//
// Created by El Wisman, w0497862, on 3/26/2025.
//

#include <iostream>
#include <chrono>
#include <thread>
#include "City.h"



using namespace std;

void ClearScreen()
{
    cout << "\n\n==================================\n\n\n\n";
}

int main() {

    City *city = new City();
    chrono:: milliseconds interval(INTERVAL);

    //This is the hasDiversity loop, provided by instructor
    //NOTES
    while (city->hasDiversity()) { //while both humans and zombies exist
        this_thread::sleep_for(interval);
        ClearScreen();
        city->step();
        city->reset(); //resets moved flags
        cout << *city; //prints city
        cout << "GENERATION " << city->getGeneration() << endl;
        cout << "HUMANS: " << city->countType(HUMAN_CH) << endl;
        cout << "ZOMBIES: " << city->countType(ZOMBIE_CH) << endl;
        cout << "BUILDINGS: " << city->countType(BUILDING_CH) << endl;
    }

    cout << "There has been an ELE!" << endl;
}

