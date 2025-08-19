# Cavern Quest RPG

A text-based role-playing adventure where players explore caves, craft tools, and manage resources. Built with modular C++ design, this project highlights object-oriented programming, polymorphism, and file-driven mechanics.

---

## 🚀 Features
- **Dynamic Map Exploration**: Traverse a cave system defined in external map files.
- **Hero System**: Manage health, inventory, and progression.
- **Crafting**: Combine resources using recipes to survive and thrive.
- **Item Interactions**: Pick up, use, and manage items with distinct behaviors.
- **Modular Architecture**: Clean separation of logic using C++ classes (`Hero`, `Game`, `Item`, `Area`, etc.).
- **File Integration**: Gameplay extended with map, recipe, and sample input files.

---

## 📂 Project Structure
```
.
├── Area.cpp / Area.h
├── Game.cpp / Game.h
├── Hero.cpp / Hero.h
├── Item.cpp / Item.h
├── Map.cpp
├── Node.cpp
├── proj5.cpp               # Main entry point
├── proj5_craft.txt         # Crafting recipes
├── proj5_map1.txt          # Map configuration 1
├── proj5_map2.txt          # Map configuration 2
├── proj5_sample.txt        # Sample game run
```

---

## 🛠️ Getting Started

### Prerequisites
- A C++ compiler supporting C++11 or higher (e.g., `g++`).
- A terminal or command line interface.

### Build Instructions
```bash
g++ -std=c++11 -o cavern_quest proj5.cpp Area.cpp Game.cpp Hero.cpp Item.cpp Map.cpp Node.cpp
```

### Run the Game
```bash
./cavern_quest
```

---

## 📖 How to Play
- Use the commands prompted in-game to move between areas.
- Explore the cave system to uncover secrets and resources.
- Collect and craft items to progress deeper into the caverns.
- Survive by managing health and resources strategically.

---

## 📜 License
This project is licensed under the MIT License.

---

## ✉️ Contact
Created by **Ali Amir**  
- GitHub: [TheAliAmir28](https://github.com/TheAliAmir28)  
- Email: codepirate2028@gmail.com
