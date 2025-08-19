#include "Area.h"
#include <vector>


  //Name: Area (Overloaded Constructor)
  //Precondition: Must have valid input for each part of a area
  // First int is the unique identifier for this particular area.
  // The first string is the name of the area
  // The second string is the description of the area
  // The last four ints are the unique identifier for adjacent areas
  //     (-1 = no path)
  // North, East, South, and West
  //Postcondition: Creates a new area
Area::Area(int id, string name, string desc, int north, int east, int south, int west) {
    m_ID = id;
    m_name = name;
    m_desc = desc;
    m_direction[0] = north;
    m_direction[1] = east;
    m_direction[2] = south;
    m_direction[3] = west;
}
  //Name: GetName
  //Precondition: Must have valid area
  //Postcondition: Returns area name as string
string Area::GetName() {
    return m_name;
}
  //Name: GetID
  //Precondition: Must have valid area
  //Postcondition: Returns area id as int
int Area::GetID() {
    return m_ID;
}
  //Name: GetDesc
  //Precondition: Must have valid area
  //Postcondition: Returns area desc as string
string Area::GetDesc() {
    return m_desc;
}
//Name: CheckDirection
//Precondition: Must have valid area
//You pass it a char (N/n, E/e, S/s, or W/w) and if that is a valid exit it
//returns the ID of the area in that direction
//Postcondition: Returns id of area in that direction if the exit exists
//If there is no exit in that direction, returns -1
int Area::CheckDirection(char myDirection) {
    int index = 0;
    //Map char to its corresponding int value
    if (myDirection == 'n' || myDirection == 'N') {
        index = 0;
    } else if (myDirection == 'e' || myDirection == 'E') {
        index = 1;
    } else if (myDirection == 's' || myDirection == 'S') {
        index = 2;
    } else if (myDirection == 'w' || myDirection == 'W') {
        index = 3;
    } else {
        return -1;
    }
    //Return the status (int) of the direction
    return m_direction[index];
}
  //Name: PrintArea
  //Precondition: Area must be complete
  //Postcondition: Outputs the area name, area desc, then possible exits
void Area::PrintArea() {
    //Print area name
    cout << '\n' << m_name << '\n' << m_desc << endl;
    cout << "Possible Exits: ";
    
    //Create a vector to hold all available paths
    vector<string> availablePaths;
    for (unsigned long i = 0; i < sizeof(m_direction)/sizeof(m_direction[0]); i++){
        //If path exists in that direction...
        if (m_direction[i] != -1) {
            //Match the index with proper direction
           if (i == 0) {
                availablePaths.push_back("North");
            } else if (i == 1) {
                availablePaths.push_back("East");
            } else if (i == 2) {
                availablePaths.push_back("South");
            } else if (i == 3) {
                availablePaths.push_back("West");
            }
        }   
    }
    //Display all available paths in a clean manner.
    for (unsigned long i = 0; i < availablePaths.size(); i++) {
        cout << availablePaths[i];
        if (availablePaths.size() > 1 && i != availablePaths.size() - 1) {
            //Seperate available paths with comma
            cout << ", ";
        }
    }
    cout << endl;
}