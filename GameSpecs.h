#ifndef _GAMESPECS_H
#define _GAMESPECS_H


const int GRIDSIZE = 20; // size of the square grid
const int BUILDING_COLLAPSE = 8; //how long till a building falls down. buildings start at 5. grow if they are 'repaired' down to 0
const int BUILDING_STARTCOUNT = 15;
const int HUMAN_STARTCOUNT = 100; // initial Humans (default 100)
const int ZOMBIE_STARTCOUNT = 5; //initial Zombie count
const int HUMAN_BREED = 6; // steps until an Human breeds
const int ZOMBIE_BREED = 8; // steps until an Zombie breeds
const int ZOMBIE_STARVE = 5; // steps until a Zombie starves and converts back
const char HUMAN_CH = 72;//72 "H"// ascii for Human
const char SPACE_CH = 45; // "-" ascii dash for empty elements
const char ZOMBIE_CH = 90;//90 "Z"// ascii for zombie
const char BUILDING_CH = 66; //"B" character for buildings
const int HUMAN_LEAVE_CHANCE = 2; //for chance they will leave a building. higher = lower chance
const int INTERVAL = 300; // millisecond pause between city steps
const int ITERATIONS = 1000; // max number of steps

//Colors
//0  = black				//9  = bright blue
//1  = blue					//10 = bright green
//2  = green				//11 = bright turquoise
//3  = turquoise				//12 = bright red
//4  = red					//13 = bright pink
//5  = pink					//14 = bright yellow
//6  = yellow				//15 = bright white
//7  = white regular		//16+ = solid blocks
//8  = white pale

const int HUMAN_COLOR = 3; // turquoise
const int ZOMBIE_COLOR = 14; // bright yellow
const int DASH_COLOR = 8; // pale white
const int BUILDING_COLOR = 12;

constexpr std::pair<int, int> directionOffsets[] = {
    {-1, 0}, // NORTH
    {0, 1},  // EAST
    {1, 0},  // SOUTH
    {0, -1},  // WEST
    {-1, 1}, // NORTHEAST
    {1, 1}, // SOUTHEAST
    {1, -1}, // SOUTHWEST
    {-1, -1} // NORTHWEST
};

#endif