#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// Inventory system
vector<string> inventory;

// Function to add an item to the inventory
void addItem(string item) {
    inventory.push_back(item);
    cout << "[Inventory] You picked up a " << item << "!\n";
}

// Function to check if an item exists in the inventory
bool hasItem(string item) {
    for (string i : inventory) {
        if (i == item) return true;
    }
    return false;
}

// Save game to a file
void saveGame() {
    ofstream file("savegame.txt");

    if (!file) { // Check if file opened successfully
        cout << "[Error] Could not save the game!\n";
        return;
    }

    for (string item : inventory) {
        file << item << "\n";  // Ensure each item is on a new line
    }

    file.close();
    cout << "[Game Saved!]\n";
}

// Load game from file
void loadGame() {
    inventory.clear();
    ifstream file("savegame.txt"); // Open file for reading

    if (!file) {  // Check if the file opened successfully
        cout << "[Error] No saved game found!\n";
        return;
    }

    string item;
    while (getline(file, item)) {  // Read each line and add to inventory
        if (!item.empty()) {  
            inventory.push_back(item);
        }
    }

    file.close();
    cout << "[Game Loaded!]\n";
}

// Random event generator
void randomEvent() {
    srand(time(0));
    int event = rand() % 3; // 3 possible events
    if (event == 0) {
        cout << "[Event] A shadow monster attacks! You barely escape!\n";
    } else if (event == 1) {
        cout << "[Event] You find a health potion!\n";
        addItem("Health Potion");
    } else {
        cout << "[Event] You hear distant whispers... creepy!\n";
    }
}

// Randomized Puzzle: Solve a math equation
bool solvePuzzle() {
    srand(time(0)); // Seed random number generator
    int num1 = rand() % 10 + 1;  // Random number between 1 and 10
    int num2 = rand() % 10 + 1;  // Random number between 1 and 10
    int correctAnswer = num1 + num2;

    cout << "[Puzzle] A door blocks your path. Solve the riddle to pass.\n";
    cout << "What is " << num1 << " + " << num2 << "? ";
    
    int playerAnswer;
    cin >> playerAnswer;

    if (playerAnswer == correctAnswer) {
        cout << "The puzzle is solved! You may proceed.\n";
        return true;  // Puzzle solved
    } else {
        cout << "Wrong answer! The cavern shakes. Try again later.\n";
        return false; // Puzzle failed
    }
}

// Game exploration function
void exploreCavern() {
    cout << "[Exploring...]\n";
    randomEvent();

    cout << "You find an old key on the ground. Pick it up? (yes/no): ";
    string pick;
    cin >> pick;
    if (pick == "yes") {
        addItem("Old Key");
    }

    cout << "You reach a locked door. Try to unlock it? (yes/no): ";
    string unlock;
    cin >> unlock;

    if (unlock == "yes" && hasItem("Old Key")) {
        cout << "You unlock the door with the key and move forward!\n";
        if (solvePuzzle()) {
            cout << "The puzzle is solved! You escape the cavern. YOU WIN!\n";
        } else {
            cout << "Wrong answer! You remain trapped.\n";
        }
    } else {
        cout << "You need a key to unlock this door.\n";
    }
}

// Main game logic
void playGame() {
    cout << "Welcome to Cavern of Shadows!\n";
    cout << "You wake up in a dark cavern. You must find a way out.\n";

    while (true) {
        cout << "\n[Actions] (1) Explore, (2) Check Inventory, (3) Save Game, (4) Load Game, (5) Quit\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {  // Explore
            exploreCavern();
        }
        else if (choice == 2) {  // Check Inventory
            cout << "[Inventory]: ";
            if (inventory.empty()) {
                cout << "Your inventory is empty.\n";
            } else {
                for (string item : inventory) {
                    cout << item << " ";
                }
                cout << "\n";
            }
        }
        else if (choice == 3) {  // Save game
            saveGame();
        }
        else if (choice == 4) {  // Load game
            loadGame();
        }
        else if (choice == 5) {  // Quit
            cout << "Exiting game...\n";
            break;
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }
}

// Main function
int main() {
    playGame();
    return 0;
}
