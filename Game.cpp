#include "Game.h"
// Name: Game(string filename) - Overloaded Constructor
// Description: Creates a new Game
// Preconditions: None
// Postconditions: Initializes all game variables to defaults (constants)
// including m_myHero (null), mapFile (passed value), craftFile (passed)
// and starting area (START_AREA)
Game::Game(string mFile, string cFile) {
    m_myHero = nullptr;
    m_areaFile = mFile;
    m_craftFile = cFile;
    m_curArea = START_AREA;
}
  // Name: ~Game
  // Description: Destructor
  // Preconditions: None
  // Postconditions: Deallocates anything dynamically allocated
  //                 in Game
Game::~Game() {
    //Delete hero
    delete m_myHero;
    //Set hero pointer to null
    m_myHero = nullptr;

    for (unsigned long i = 0; i < m_areas.size(); i++) {
        //Delete all dynamically allocated areas
        delete m_areas[i];
    }
    //Clear areas vector
    m_areas.clear();

    for (unsigned long i = 0; i < m_items.size(); i++) {
        //delete all dynamically allocated items
        delete m_items[i];
    }
    //Clear items vector
    m_items.clear();
}
  // Name: LoadMap()
  // Description: Reads area data from the map file and dynamically
  //             creates Area objects. Inserts each new Area into
  //             m_myMap in the order encountered.
  // Preconditions: m_mapFile is set to a valid filename;
  //             the file exists and is formatted correctly.
  // Postconditions: m_myMap contains all loaded Area pointers;
  //             file stream is closed.
void Game::LoadMap() {
    ifstream inputstream;
    //Open area file
    inputstream.open(m_areaFile);
    //Dedicate space to hold information
    string areaID, name, desc, northID, eastID, southID, westID;
    //Loop line-by-line using delimiter (|) to extract information
    while (getline(inputstream, areaID, DELIMITER) && getline(inputstream, name, DELIMITER) 
            && getline(inputstream, desc, DELIMITER) && getline(inputstream, northID, DELIMITER)
            && getline(inputstream, eastID, DELIMITER) && getline(inputstream, southID, DELIMITER) 
            && getline(inputstream, westID, DELIMITER)) {
                //Create a new Area object dynamically and push it to the back of the areas vector
                Area *newArea = new Area(stoi(areaID), name, desc, stoi(northID), stoi(eastID), stoi(southID), stoi(westID));
                m_areas.push_back(newArea);
    }
    //Close area file
    inputstream.close();
}
  // Name: LoadCraft()
  // Description: Reads crafting definitions from the craft file and
  //              creates Item objects. Parses each line into an
  //              item name and its requirement list.
  // Preconditions: m_craftFile is set to a valid filename;
  //              the file exists and uses DELIMITER.
  // Postconditions: m_items contains new Item pointers for
  //              every recipe; file stream is closed.
void Game::LoadCraft() {
    ifstream inputstream;
    //Open craft file
    inputstream.open(m_craftFile);
    //Dedicate space to hold information from file
    string finishedProd, req1, req2, req3, req4;
    string endSpace;
    //Read file line-by-line using delimiter (|) to extract information
    while(getline(inputstream, finishedProd, DELIMITER) && getline(inputstream, req1, DELIMITER)
       && getline(inputstream, req2, DELIMITER) && getline(inputstream, req3, DELIMITER)) {
        if (getline(inputstream, req4, DELIMITER) && getline(inputstream, endSpace, '\n')) {}
        //Create vector to hold all requirements
        vector<string> reqs = {req1, req2, req3, req4};
        //Create a new Item dynamically
        Item *newItem = new Item(finishedProd, reqs);
        //Add item to items vector
        m_items.push_back(newItem);
       }
       //Close file
       inputstream.close();
}
  // Name: HeroCreation()
  // Description: Prompts the player to enter a hero name and
  //              constructs a new Hero.
  // Preconditions: Standard input (cin) is available.
  // Postconditions: m_myHero points to a newly allocated Hero
  //              with the entered name.
void Game::HeroCreation() {
    string heroName;
    cout << "Hero Name: ";
    //Get hero name from user
    getline(cin, heroName);
    //Dynamically allocate new hero with such name
    m_myHero = new Hero(heroName);
}
  // Name: Look()
  // Description: Displays the current Area’s name, description,
  //              and possible exits.
  // Preconditions: m_curArea is a valid index into m_myMap.
  // Postconditions: Current area details are printed to stdout.
void Game::Look() {
    //Print info about current area
    m_areas[m_curArea]->PrintArea();
}
  // Name: StartGame()
  // Description: Initializes game flow by loading map and crafting
  //              data, creating the hero, then showing the
  //              starting area and entering the main loop.
  // Preconditions: m_mapFile and m_craftFile are set; files exist.
  // Postconditions: Game state is initialized and Action() is called.
void Game::StartGame() {
    //Print welcome message
    cout << "Welcome to UMBC Runescape!" << endl;
    //Load passed-in map file
    LoadMap();
    //Load passed-in craft file
    LoadCraft();
    //Create Hero
    HeroCreation();
    //Set current area to 0 at the beginning
    m_curArea = 0;
    //Present info about the beginning area
    Look();
    //Let user choose their action
    Action();
}
  // Name: Action()
  // Description: Presents the player with the main menu
  //              (Look, Move, Use Area, Craft, Inventory, Quit)
  //              and drives game interactions until the player quits.
  // Preconditions: Hero and map are initialized.
  // Postconditions: Continues looping until user selects Quit.
void Game::Action() {
    int option = 0;
    while (option < 1 || option > 6 || option != 6) {
        //Present choices
        cout << "What would you like to do?" << endl;
        cout << "1. Look" << endl;
        cout << "2. Move" << endl;
        cout << "3. Use Area" << endl;
        cout << "4. Craft Item" << endl;
        cout << "5. Display Inventory" << endl;
        cout << "6. Quit" << endl;
        //Capture choice
        cin >> option;
        //Execute proper function based on choice
        if (option == 1) {
            Look();
        } else if (option == 2) {
            Move();
        } else if (option == 3) {
            UseArea();
        } else if (option == 4) {
            CraftItem();
        } else if (option == 5) {
            //Display inventory
            cout << "******* INVENTORY *******" << endl;
            m_myHero->DisplayInventory();
        } else if (option == 6) {
            //Final goodbye message
            cout << "Good bye!" << endl;
        } else {
            //If choice is out of range
            cout << "Invalid choice. Try again" << endl;
        }
    }
}

  // Name: Move()
  // Description: Prompts the player for a direction (N/E/S/W),
  //              validates the move, updates m_curArea, and
  //              calls Look() to show the new area.
  // Preconditions: m_curArea is valid; m_myMap contains
  //              adjacent Area pointers.
  // Postconditions: m_curArea is updated to the new area index.
void Game::Move() {
    char desiredDirection;
    int newAreaID = 0;
    
    do {
        cout << "Which direction? (N E S W)" << endl;
        //Get desired direction
        cin >> desiredDirection;
        //Check if the new direction is valid and continue to ask for direction until it is valid
        newAreaID = m_areas[m_curArea]->CheckDirection(desiredDirection);
    } while (newAreaID == -1);
    //Set current area to the new area.
    m_curArea = newAreaID;
    //Present info about the new area
    Look();
}
  // Name: CraftItem()
  // Description: Displays all craftable items, prompts for a selection,
  //              and attempts crafting via Hero’s CanCraft/Craft methods.
  // Preconditions: m_items is populated with Item pointers.
  // Postconditions: If crafting succeeds, inventory is
  //              updated; otherwise prints error.
void Game::CraftItem() {
    unsigned long craftChoice = 0;
    //Validate craft choice
    while (craftChoice <= 0 || craftChoice > m_items.size()) {
        cout << "Which item would you like to craft?" << endl;
        //Present a list of craftable items
        for (unsigned long i = 0; i < m_items.size(); i++) {
            cout << i+1 << ". " << m_items[i]->GetName() << endl;
        }
        //Get craft choice
        cin >> craftChoice;
    }
    //Allocate a vector that holds the requirements of that chosen item
    vector<string> requiredMaterials = m_items[craftChoice-1]->GetReq();
    //Check if user has all required materials to craft that item
    bool ableToCraft = m_myHero->CanCraft(requiredMaterials);
    //If requirements are met...
    if (ableToCraft) {
        //Craft item
        m_myHero->Craft(m_items[craftChoice-1]->GetName(), requiredMaterials);
    } else {
        //Let user know that they are lacking on requirements
        cout << "Cannot craft " << m_items[craftChoice-1]->GetName() << ". Missing Requirements." << endl;
    }
}
  // Name: UseArea()
  // Description: Prompts the player to choose a search action
  //              (Raw, Natural, Food, Hunt)
  //              and forwards that request to the Hero.
  // Preconditions: Hero exists and has methods Raw/Natural/Food/Hunt.
  // Postconditions: One gather action is performed and the result printed.
void Game::UseArea() {
    int lookOption = 0;
    //Display all choices
    do {
        cout << "What would you like to look for?" << endl;
        cout << "1. Raw Materials (Mining)" << endl;
        cout << "2. Natural Resources (Woodcutting/Foraging)" << endl;
        cout << "3. Food (Fishing/Farming)" << endl;
        cout << "4. Hunt" << endl;
        //Get choice
        cin >> lookOption;
    } while (lookOption <= 0 || lookOption > 4);
    //Execute proper function based on the choice
    if (lookOption == 1) {
        m_myHero->Raw();
    } else if (lookOption == 2) {
        m_myHero->Natural();
    } else if (lookOption == 3) {
        m_myHero->Food();
    } else {
        m_myHero->Hunt();
    }
}