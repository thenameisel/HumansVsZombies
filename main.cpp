#include <iostream>
#include <chrono>
#include <thread>
#include "Organism.h"
#include "City.h"
//#include "


//this is a test for git
using namespace std;

void ClearScreen()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int main() {
    City *city = new City();
    chrono:: milliseconds interval(INTERVAL);

    while (city->hasDiversity()) { //while both humans and zombies exist
        this_thread::sleep_for(interval);
        ClearScreen();
        city->step();
        city->reset(); //resets moved flags
        city->countOrganisms(Z or H goes here);// run once for each type
        cout << *city; //prints city
        cout << "GENERATION " << city->getGeneration() << endl;
        cout << "HUMANS: " << city->countType(HUMAN_CH) << endl;
        cout << "ZOMBIES: " << city->countType(ZOMBIE_CH) << endl;
    }
}

