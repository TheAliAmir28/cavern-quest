#include "Hero.h"
  // Name: Hero(const string& name)
  // Description: Constructs a new Hero with the specified name.
  // Preconditions: name must be a valid, non‐empty string.
  // Postconditions: m_name is initialized; inventory map is empty.
Hero::Hero(const string& name) : m_name(name) {}
  // Name: ~Hero()
  // Description: Destructor for Hero.
  // Preconditions: None.
  // Postconditions: Releases any dynamically allocated items in Hero.
  //                 None in this case.
Hero::~Hero() {}
  // Name: GetName()
  // Description: Retrieves the hero’s name.
  // Preconditions: None.
  // Postconditions: Returns the value of m_name.
string Hero::GetName() const {
    return m_name;
}
  // Name: SetName(const string& name)
  // Description: Updates the hero’s name.
  // Preconditions: name must be a valid string.
  // Postconditions: m_name is set to the new value.
void Hero::SetName(const string& name) {
    m_name = name;
}
  // Name: DisplayInventory()
  // Description: Prints the hero’s current inventory using overloaded << operator
  // Preconditions: Inventory map has been initialized.
  // Postconditions: Inventory contents are displayed.
void Hero::DisplayInventory() const {
    cout << m_inventory << endl;
}
  // Name: CollectItem(const string& item)
  // Description: If the item exists, in m_inventory, uses Update to increment quantity
  //              If the item does not exist in m_inventory, inserts it.
  // Preconditions: item must be a valid item name.
  // Postconditions: Inventory count for item is incremented by 1.
  // Note: Uses try and catch (const out_of_range&) and inserts if caught.
void Hero::CollectItem(const string& item) {
    try {
        //Assuming item exists
        int val = m_inventory.ValueAt(item);
        //Update item's count
        m_inventory.Update(item, val+1);
    } catch (const out_of_range& e) {
        //If item does not exist, simply insert it and set count to 1
        m_inventory.Insert(item, 1);
    }
}
  // Name: CanCraft(const vector<string>& requirements)
  // Description: Iterators through the requirements to see if they have quantity in m_inventory
  // Preconditions: Requirements vector populated with item names.
  // Postconditions: Returns true if every required item has count ≥1.
  // Note: Uses try and catch (const out_of_range&) and returns false if caught.
bool Hero::CanCraft(const vector<string>& requirements) const {
    try {
        for (unsigned long i = 0; i < requirements.size(); i++) {
            //Check count of requirements
            int val = m_inventory.ValueAt(requirements[i]);
            //If any requirement is short, the item cannot be crafted
            if (val < 1) {
                return false;
            }
        }
    } catch (const out_of_range& e) {
        return false;
    }
    //Return true if all false-check tests fail
    return true;
}
  // Name: Craft(const string& result, const vector<string>& requirements)
  // Description: Consumes the listed requirements and adds the
  //              crafted "result" (iterates through requirements and Updates)
  // Preconditions: Call to CanCraft(requirements) must return true.
  // Postconditions: Each requirement’s count is decremented by 1;
  //                 Result of crafting is added.
void Hero::Craft(const string& result, const vector<string>& requirements) {
    //Loop through requirements
    for (unsigned long i = 0; i < requirements.size(); i++) {
        //Obtain count
        int val = m_inventory.ValueAt(requirements[i]);
        //Decrement count as resource is being used
        m_inventory.Update(requirements[i], val-1);
    }
    //Print message of successful craft
    cout << "Crafted: " << result << "!" << endl;
    //Send result to user's collection
    CollectItem(result);
}
  // Name: Raw()
  // Description: Simulates mining for raw materials. Passes values
  //              and calls Gather function.
  // Preconditions: Random number generator seeded.
  // Postconditions: Possibly adds a random raw material
  //                 to inventory or reports none found.
void Hero::Raw() {
    Gather(RawProducts, "You searched and found nothing.", "You mined and found some");
}
  // Name: Natural()
  // Description: Simulates foraging for natural resources. Passes values
  //              and calls Gather function.
  // Preconditions: Random number generator seeded.
  // Postconditions: Possibly adds a random natural resource
  //                 or reports none found.
void Hero::Natural() {
    Gather(NaturalProducts, "You searched and found nothing.", "You searched and harvested some");
}
  // Name: Food()
  // Description: Simulates gathering food items. Passes values
  //              and calls Gather function.
  // Preconditions: Random number generator seeded.
  // Postconditions: Possibly adds a random food item or reports none found.
void Hero::Food() {
    Gather(FoodProducts, "You searched and found nothing.", "You searched and harvested some");
}
  // Name: Hunt()
  // Description: Simulates hunting for creature drops. Passes values
  //              and calls Gather function.
  // Preconditions: Random number generator seeded.
  // Postconditions: Possibly adds a random creature drop
  //                 or reports none found.
void Hero::Hunt() {
    Gather(HuntProducts, "You searched and found nothing.", "You searched and harvested some");
}
  // Name: Gather
  // Description: Randomly selects an item from vector products passed.
  //              If selection equals list size, prints 'noItemMsg';
  //              otherwise prints foundMsg + item and adds it
  //              to the hero's inventory.
  // Preconditions: 'products' must contain valid item names.
  // Postconditions: Inventory is incremented for the selected
  //               item if found; message printed.
void Hero::Gather(const vector<string>& products, const string& noItemMsg,
    const string& foundMsg) {
        //Generate a random number between 0 and 3 inclusive
    unsigned long num = rand() % (products.size() + 1);
    //If num is 3, that means that no item was found
    if (num == products.size()) {
        cout << noItemMsg << endl;
    } else {
        //If num is not 3, print item found.
        string itemFound = products[num];
        cout << foundMsg << " " << itemFound << "." << endl;
        //Update user's collection after find
        CollectItem(itemFound);
    }

}