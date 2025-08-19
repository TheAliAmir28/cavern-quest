#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <stdexcept>
#include "Node.cpp"
using namespace std;

template <typename K, typename V>
class Map {
public:
  // Name: Map()
  // Description: Default constructs an empty map.
  // Preconditions: None.
  // Postconditions: m_head is set to nullptr; m_size is initialized to 0.
  Map();
  // Name: ~Map()
  // Description: Destroys the map, freeing all nodes.
  // Preconditions: None.
  // Postconditions: All nodes are deleted; m_head is nullptr; m_size is 0.
  ~Map();
  // Name: Map(const Map& other)
  // Description: Copy constructor; deep copies another map’s contents.
  // Preconditions: other must be a valid Map<K,V>.
  // Postconditions: This map contains the same key/value pairs, in order.
  Map(const Map& other);
  // Name: operator=(const Map& other)
  // Description: Assignment operator; clears this map and deep copies other.
  // Preconditions: other is a valid Map<K,V>; self-assignment is handled.
  // Postconditions: This map contains a copy of other’s elements.
  Map<K,V>& operator=(const Map& other);
  // Name: Insert(const K& key, const V& value)
  // Description: Inserts or updates a key → value pair, keeping
  //              nodes ordered by key.
  // Preconditions: key and value are valid; map may be empty.
  // Postconditions: New node inserted at sorted position, or
  //                 existing node’s value updated; m_size adjusted.
  void Insert(const K& key, const V& value);
  // Name: Update(const K& key, const V& value)
  // Description: Changes the value for an existing key.
  // Preconditions: key must exist in the map.
  // Postconditions: Corresponding node’s value is set to
  //                 value; throws out_of_range if key not found.
  void Update(const K& key, const V& value);
  // Name: ValueAt(const K& key) const
  // Description: Retrieves a const reference to the value for key.
  // Preconditions: key must exist in the map.
  // Postconditions: Returns reference to the value;
  //                 throws out_of_range if not found.
  const V& ValueAt(const K& key) const;
  // Name: At(const K& key) const
  // Description: Returns a pointer to the node for key.
  // Preconditions: key must exist in the map.
  // Postconditions: Returns pointer to the Node<K,V>;
  //                 throws out_of_range if not found.
  Node<K,V>* At(const K& key) const;
  // Name: GetSize() const
  // Description: Reports the number of key‑value pairs in the map.
  // Preconditions: None.
  // Postconditions: Returns the value of m_size.
  int GetSize() const;
  // Name: IsEmpty() const
  // Description: Checks whether the map contains no elements.
  // Preconditions: None.
  // Postconditions: Returns true if m_size == 0
  //                 (m_head == nullptr); false otherwise.
  bool IsEmpty() const;
  // Name: Display() const
  // Description: Prints each key:value pair to cout, one per line.
  // Preconditions: ostream cout is available.
  // Postconditions: Map contents are written to standard output.
  void Display() const;
  // Name: operator<<
  // Description: Streams all key:value pairs into os, one per line.
  // Preconditions: os is a valid ostream; map is a valid Map<K,V>.
  // Postconditions: os contains serialized map contents;
  //                returns os by reference.
  // PROVIDED
  friend ostream& operator<<(ostream& os, const Map<K, V>& map){
    Node<K,V>* current = map.m_head;
    while (current != nullptr) {
      os << current->GetKey() << ":" << current->GetValue() << endl;
      current = current->GetNext();
    }
    return os;
  }
private:
  // Name: Clear()
  // Description: Deletes all nodes in the linked list,
  //              freeing their memory and resetting the map.
  // Preconditions: None.
  // Postconditions: All dynamically allocated nodes are deleted;
  //                 m_head is set to nullptr; m_size is reset to 0.
  void Clear();
  Node<K,V>* m_head; //Pointer to the first node in the Map
  int m_size; //Tracks the size of the Map (number of nodes)
};
#endif
//********IMPLEMENT MAP.CPP HERE DUE TO TEMPLATED CLASS*********

  // Name: Map()
  // Description: Default constructs an empty map.
  // Preconditions: None.
  // Postconditions: m_head is set to nullptr; m_size is initialized to 0.
template<typename K, typename V>
Map<K, V>::Map() : m_head(nullptr), m_size(0) {}
  // Name: Insert(const K& key, const V& value)
  // Description: Inserts or updates a key → value pair, keeping
  //              nodes ordered by key.
  // Preconditions: key and value are valid; map may be empty.
  // Postconditions: New node inserted at sorted position, or
  //                 existing node’s value updated; m_size adjusted.
template<typename K, typename V>
void Map<K, V>::Insert(const K& key, const V& value) {
    // If map is empty, create a new node as the first element.
    if (m_size == 0) {
        Node<K, V> *newNode = new Node<K, V>(key, value);
        m_head = newNode; 
    } else if (m_size == 1) {  // If there's only one node, we need to decide where to insert.
        Node<K, V> *curr = m_head;
        if (curr->GetKey() < key) { // Insert after the current node if key is larger.
            Node<K, V> *newNode = new Node<K, V>(key, value);
            curr->SetNext(newNode);
        } else {  // Insert before the current node if key is smaller.
            Node<K, V> *newNode = new Node<K, V>(key, value);
            newNode->SetNext(m_head);
            m_head = newNode;
        }
        // For more than one node, search for key and insert at the correct position.
    } else {
        //Match check
        bool matchFound = false;
        
        Node<K, V>* curr = m_head;
        while (curr != nullptr) {
              // If key is found, update its value.
            if (curr->GetKey() == key) {
                curr->SetValue(value);
                matchFound = true;
            }
             // Move to the next node.
            curr = curr->GetNext();
        }
         // If no match was found, insert at the correct position.
        if (!matchFound) {
            Node<K, V>* curr = m_head;
            Node<K, V>* prev = m_head;
            curr = curr->GetNext();

            // Insert before the first node if key is smaller.
            if (key < prev->GetKey()) {
                Node<K, V> *newNode = new Node<K, V>(key, value);
                newNode->SetNext(m_head);
                m_head = newNode;
            // Find the right spot in the sorted list.
            } else {
                while (curr != nullptr && key > curr->GetKey()) {
                    curr = curr->GetNext();
                    prev = prev->GetNext();
                }
                Node<K, V> *newNode = new Node<K, V>(key, value);
                newNode->SetNext(prev->GetNext());
                prev->SetNext(newNode);
            }
        }
    }
    m_size++; 
}
  // Name: Display() const
  // Description: Prints each key:value pair to cout, one per line.
  // Preconditions: ostream cout is available.
  // Postconditions: Map contents are written to standard output.
template<typename K, typename V>
void Map<K, V>::Display() const {
    Node<K, V> *curr = m_head;
    while (curr != nullptr) {
        // Display each key-value pair
        cout << *curr << " ";
        // Move to the next node
        curr = curr->GetNext();
    }
    cout << endl;
}
  // Name: GetSize() const
  // Description: Reports the number of key‑value pairs in the map.
  // Preconditions: None.
  // Postconditions: Returns the value of m_size.
template<typename K, typename V>
int Map<K, V>::GetSize() const {
    return m_size;
}
  // Name: Map(const Map& other)
  // Description: Copy constructor; deep copies another map’s contents.
  // Preconditions: other must be a valid Map<K,V>.
  // Postconditions: This map contains the same key/value pairs, in order.
template<typename K, typename V>
Map<K, V>::Map(const Map& other) {
    //Reset 'this' map to prepare it for copy
    this->m_head = nullptr;
    this->m_size = 0;
    
    Node<K, V> *curr = other.m_head;
    // Traverse the other map and insert each element
    while (curr != nullptr) {
        //Obtain key and value
        K key = curr->GetKey();
        V value = curr->GetValue();
        this->Insert(key, value);
        curr = curr->GetNext();
    }
}
  // Name: IsEmpty() const
  // Description: Checks whether the map contains no elements.
  // Preconditions: None.
  // Postconditions: Returns true if m_size == 0
  //                 (m_head == nullptr); false otherwise.
template<typename K, typename V>
bool Map<K, V>::IsEmpty() const {
    //If m_head points to null, that means the map is empty
    if (m_head == nullptr) {
        return true;
    }
    return false;
}
  // Name: Clear()
  // Description: Deletes all nodes in the linked list,
  //              freeing their memory and resetting the map.
  // Preconditions: None.
  // Postconditions: All dynamically allocated nodes are deleted;
  //                 m_head is set to nullptr; m_size is reset to 0.
template<typename K, typename V>
void Map<K, V>::Clear() {
    Node<K, V> *curr = m_head;
     // Traverse each node and delete it
    while (curr != nullptr) {
        m_head = curr;
        curr = curr->GetNext();
        // Delete current node
        delete m_head;
    }
    // Reset head pointer
    m_head = nullptr;
    // Reset size
    m_size = 0;
}
  // Name: operator=(const Map& other)
  // Description: Assignment operator; clears this map and deep copies other.
  // Preconditions: other is a valid Map<K,V>; self-assignment is handled.
  // Postconditions: This map contains a copy of other’s elements.
template<typename K, typename V>
Map<K, V>& Map<K, V>::operator=(const Map<K, V>& other) {
    // If assigning to itself, just return the map
    if (this == &other) {
        return *this;
    }
    // Clear this map before copying
    if (this->IsEmpty() == false) {
        this->Clear();
    }
    Node<K, V> *curr = other.m_head;
    // Copy each element from the other map
    while (curr != nullptr) {
        K key = curr->GetKey();
        V value = curr->GetValue();
        this->Insert(key, value);
        curr = curr->GetNext();
    }
    return *this;
}
  // Name: Update(const K& key, const V& value)
  // Description: Changes the value for an existing key.
  // Preconditions: key must exist in the map.
  // Postconditions: Corresponding node’s value is set to
  //                 value; throws out_of_range if key not found.
template<typename K, typename V>
void Map<K, V>::Update(const K& key, const V& value) {
    Node<K, V> *curr = m_head;
    // Traverse the list and find the key
    while (curr != nullptr) {
        if (curr->GetKey() == key) {
            // Update the value
            curr->SetValue(value);
            return;
        }
        // Move to the next node
        curr = curr->GetNext();
    }
    // Key wasn't found, throw exception
    throw out_of_range("Key not found");
}
  // Name: ValueAt(const K& key) const
  // Description: Retrieves a const reference to the value for key.
  // Preconditions: key must exist in the map.
  // Postconditions: Returns reference to the value;
  //                 throws out_of_range if not found.
template<typename K, typename V>
const V& Map<K, V>::ValueAt(const K& key) const {
    Node<K, V> *curr = m_head;
    // Traverse to find the key
    while (curr != nullptr) {
        if (curr->GetKey() == key) {
            // Return the value if key found
            return curr->GetValue();
        }
        curr = curr->GetNext();
    }
    // Key wasn't found, throw exception
    throw out_of_range("Key not found");
}
  // Name: At(const K& key) const
  // Description: Returns a pointer to the node for key.
  // Preconditions: key must exist in the map.
  // Postconditions: Returns pointer to the Node<K,V>;
  //                 throws out_of_range if not found.
template<typename K, typename V>
Node<K,V>* Map<K, V>::At(const K& key) const {
    Node<K, V> *curr = m_head;
    // Traverse the list to find the key
    while (curr != nullptr) {
        if (curr->GetKey() == key) {
            // Return the pointer to the node
            return curr;
        }
        curr = curr->GetNext();
    }
    // Key not found, throw exception
    throw out_of_range("Key not found");
}
  // Name: ~Map()
  // Description: Destroys the map, freeing all nodes.
  // Preconditions: None.
  // Postconditions: All nodes are deleted; m_head is nullptr; m_size is 0.
template<typename K, typename V>
Map<K, V>::~Map() {
    // Call Clear to free memory
    Clear();

}
