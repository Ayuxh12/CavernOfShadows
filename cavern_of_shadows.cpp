#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// Player inventory
vector<string> inventory;

// Adds an item to the player's inventory
void addItem(const string& item) {
    inventory.push_back(item);
    cout << "🔹 You picked up a " << item << "!\n";
}

// Checks if an item is in the inventory
bool hasItem(const string& item) {
    for (const auto& i : inventory) {
        if (i == item) return true;
    }
    return false;
}

// Save inventory to a file
void saveGame() {
    ofstream file("savegame.txt");

    if (!file) {
        cout << "⚠️ Error: Could not save the game.\n";
        return;
    }

    for (const auto& item : inventory) {
        file << item << "\n";
    }

    file.close();
    cout << "💾 Game saved!\n";
}

// Load inventory from a save file
void loadGame() {
    inventory.clear();
    ifstream file("savegame.txt");

    if (!file) {
        cout << "⚠️ No saved game found.\n";
        return;
    }

    string item;
    while (getline(file, item)) {
        if (!item.empty()) {
            inventory.push_back(item);
        }
    }

    file.close();
    cout << "✅ Game loaded!\n";
}

// Random events during exploration
void randomEvent() {
    srand(time(0));
    int event = rand() % 3;

    switch (event) {
        case 0:
            cout << "👻 A shadowy figure appears... You barely escape!\n";
            break;
        case 1:
            cout << "🧪 You find a health potion on the ground.\n";
            addItem("Health Potion");
            break;
        case 2:
            cout << "👂 You hear eerie whispers echoing through the cavern...\n";
            break;
    }
}

// Generates a random math puzzle
bool solvePuzzle() {
    srand(time(0));
    int num1 = rand() % 10 + 1;
    int num2 = rand() % 10 + 1;
    int correctAnswer = num1 + num2;

    cout << "\n🧩 A door with a magical lock blocks your path.\n";
    cout << "Solve this: " << num1 << " + " << num2 << " = ?\n";
    
    int playerAnswer;
    cin >> playerAnswer;

    if (playerAnswer == correctAnswer) {
        cout << "🔓 The door unlocks! You can proceed.\n";
        return true;
    } else {
        cout << "❌ Wrong answer! The cavern shakes... Try again later.\n";
        return false;
    }
}

// Exploration function
void exploreCavern() {
    cout << "\n🔍 You venture deeper into the cavern...\n";
    randomEvent();

    cout << "🗝 You spot an old key on the ground. Pick it up? (yes/no): ";
    string pick;
    cin >> pick;
    if (pick == "yes") {
        addItem("Old Key");
    }

    cout << "🚪 You reach a locked door. Try to unlock it? (yes/no): ";
    string unlock;
    cin >> unlock;

    if (unlock == "yes") {
        if (hasItem("Old Key")) {
            cout << "✅ You unlock the door with the key and step forward...\n";
            if (solvePuzzle()) {
                cout << "🎉 You solved the puzzle and escaped the cavern! YOU WIN!\n";
                exit(0);
            } else {
                cout << "❌ The puzzle remains unsolved. You are stuck.\n";
            }
        } else {
            cout << "❌ The door is locked. You need a key to proceed.\n";
        }
    }
}

// Main game loop
void playGame() {
    cout << "🏰 Welcome to **Cavern of Shadows**!\n";
    cout << "🌑 You wake up in a dark cavern with no memory of how you got here...\n";
    cout << "Can you find a way out?\n";

    while (true) {
        cout << "\n📜 What will you do?\n";
        cout << "[1] Explore the cavern\n";
        cout << "[2] Check inventory\n";
        cout << "[3] Save game\n";
        cout << "[4] Load game\n";
        cout << "[5] Quit\n";
        cout << "Enter choice: ";
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                exploreCavern();
                break;
            case 2:
                if (inventory.empty()) {
                    cout << "👜 Your inventory is empty.\n";
                } else {
                    cout << "🎒 Inventory: ";
                    for (const auto& item : inventory) {
                        cout << item << " ";
                    }
                    cout << "\n";
                }
                break;
            case 3:
                saveGame();
                break;
            case 4:
                loadGame();
                break;
            case 5:
                cout << "👋 Exiting game... Goodbye!\n";
                return;
            default:
                cout << "⚠️ Invalid choice. Try again.\n";
        }
    }
}

// Main function
int main() {
    playGame();
    return 0;
}
