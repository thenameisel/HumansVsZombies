//
// Created by El Wisman, w0497862, on 3/26/2025.
//

#include <iostream>
#include <chrono>
#include <thread>
#include "Organism.h"
#include "City.h"
#include "Human.h"
//#include "


using namespace std;

void ClearScreen()
{
    cout << "\n\n==================================\n\n\n\n";
}

int main() {
    City *city = new City();
    chrono:: milliseconds interval(INTERVAL);

    //city->debugPrint(); // single run

    //testing loop, runs set number of times

    for (int i=0; i < 1; i++) {
        ClearScreen();
        cout << *city << endl;
        cout << "HUMANS: " << city->countType(HUMAN_CH) << endl;
        cout << "ZOMBIES: " << city->countType(ZOMBIE_CH) << endl;
    }

    //This is the hasDiversity loop, provided by instructor
    //NOTES
    //As of now, everything starts round one with move complete, then next round goes to step then reset moved flags for further rounds.
    // while (city->hasDiversity()) { //while both humans and zombies exist
    //     this_thread::sleep_for(interval);
    //     ClearScreen();
    //     city->step();
    //     city->reset(); //resets moved flags
    //     city->countOrganisms(Z or H goes here);// run once for each type
    //     cout << *city; //prints city
    //     cout << "GENERATION " << city->getGeneration() << endl;
    //     cout << "HUMANS: " << city->countType(HUMAN_CH) << endl;
    //     cout << "ZOMBIES: " << city->countType(ZOMBIE_CH) << endl;
    // }
}

