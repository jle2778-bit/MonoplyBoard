#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

static const int MAX_SPACES = 40;

// -------------------------------
// Data class (NOT a struct)
// -------------------------------
class MonopolySpace {
public:
    string propertyName;
    string propertyColor;
    int value;
    int rent;

    MonopolySpace() {
        // TODO: define default constructor (recommended) [ALREADY DONE]
        propertyName = "";
        propertyColor = "";
        value = 0;
        rent = 0;
    }

    MonopolySpace(string propertyName, string propertyColor, int value, int rent) {
        /* TODO: Define overloaded constructor here */
        this->propertyName = propertyName;
        this->propertyColor = propertyColor;
        this->value = value;
        this->rent = rent;
    }

    bool isEqual(MonopolySpace other) {
        /* TODO: Define isEqual here (compare by name is fine if you enforce uniqueness) */
        return this->propertyName == other.propertyName && this->propertyColor == other.propertyColor && this->value == other.value;
    }

    void print() {
        /* TODO: Define print here */
        // Example style:
         cout << propertyName << " | " << propertyColor << " | $" << value << " | Rent " << rent;
    }
};

// -------------------------------
// Template Node class (NOT a struct)
// -------------------------------
template <typename T>
class Node {
public:
    T data;
    Node<T>* nextNode;

    Node(T value) {
        data = value;
        nextNode = nullptr;
    }
};

// -------------------------------
// Template Circular Linked List class
// Spring 2026 version: traversable board
// -------------------------------
template <typename T>
class CircularLinkedList {
private:
    Node<T>* headNode;
    Node<T>* tailNode;

    // player cursor for traversal-based gameplay
    Node<T>* playerNode;

    int nodeCount;
    int passGoCount;

public:
    CircularLinkedList() {
        headNode = nullptr;
        tailNode = nullptr;
        playerNode = nullptr;

        nodeCount = 0;
        passGoCount = 0;
    }

    // -------------------------------
    // Board Construction Policy (Reminder)
    // -------------------------------
    // Spaces are added during board construction BEFORE gameplay.
    // You choose how to construct the board:
    // - hardcode spaces, read from file, or generate programmatically
    // The only non-negotiable requirement:
    // - enforce MAX_SPACES
    // - maintain circular integrity
    // -------------------------------

    // -------------------------------
    // Core A: Add a Space with Capacity Enforcement
    // -------------------------------
    bool addSpace(T value) {
        // TODO:
        // - If nodeCount == MAX_SPACES return false (do not corrupt list)
        // - Create new node
        // - If empty list: head=tail=player=new, new->next=head
        // - Else: tail->next=new, tail=new, tail->next=head
        // - nodeCount++
        if (nodeCount == MAX_SPACES) {
            return false;
        }
        Node<T>* newNode = new Node<T>(value);
        if (nodeCount == 0) {
            headNode = tailNode = playerNode = newNode;
            newNode->nextNode = headNode;
        }
        else {
            tailNode->nextNode = newNode;
            tailNode = newNode;
            tailNode->nextNode = headNode;
        }
        nodeCount++;
        return true;
    }


    // -------------------------------
    // Core B: Add Multiple Spaces at Once
    // -------------------------------
    int addMany(vector<T> values) {
        // TODO:
        // - Add sequentially until full
        // - Stop exactly when you reach MAX_SPACES
        // - Return number successfully added
        // - Do not corrupt pointers if capacity is exceeded
        int count = 0;
        for (int i = 0; i < values.size(); i++) {
            bool result = addSpace(values[i]);
            if (result == false) {
                break;
            }
            count++;
        }
        return count;
    }

    // -------------------------------
    // Core C: Traversal-Based Player Movement
    // -------------------------------
    void movePlayer(int steps) {
        // TODO:
        // - Move playerNode forward 'steps' times, node-by-node
        // - Wrap naturally because list is circular
        // - Detect and track passing GO:
        //   increment passGoCount when a move crosses from tail back to head
        // - Must handle empty list safely
        if (playerNode == nullptr) {
            return;
        }
        for (int i = 0; i < steps; i++) {
            if (playerNode->nextNode == headNode) {
                passGoCount++;
            }
            playerNode = playerNode->nextNode;
        }

    }

    int getPassGoCount() {
        return passGoCount;
    }

    // -------------------------------
    // Core D: Controlled Board Display
    // -------------------------------
    void printFromPlayer(int count) {
        // TODO:
        // - Print exactly 'count' nodes starting from playerNode
        // - Must not infinite loop
        // - Must handle empty list
        // - Output must be deterministic and readable
        if (playerNode == nullptr || count <= 0) {
            return;
        }
        int i = 0;
        Node<T>* current = playerNode;
        while (i < count) {
            current->data.print();
            cout << endl;
            i++;
            current = current->nextNode;
        }

        cout << "Displayed Spaces: " << count << endl;
    }

    // Optional helper: print full board once (one full cycle)
    void printBoardOnce() {
        // TODO:
        // - Traverse exactly one full cycle and print each node
        cout << "printBoardOnce unwritten" << endl;
    }

    // -------------------------------
    // Advanced Option A (Level 1): removeByName
    // -------------------------------
    bool removeByName(string name) {
        // TODO:
        // - Delete FIRST matching node
        // - Must handle:
        //   - deleting head
        //   - deleting tail
        //   - deleting the only-node list
        // - Maintain circular link tail->next=head
        // - If playerNode points to deleted node, move playerNode to a safe node
        // - nodeCount--
        Node<T>* current = headNode;
        Node<T>* previous = tailNode;
        if (headNode == nullptr) {
            return false;
        }
        int stepCount = 0;
        while (stepCount < nodeCount) {
            if (current->data.propertyName == name) {

                previous->nextNode = current->nextNode; //disconnects our node

                if (current == tailNode) {
                    tailNode = previous;
                }

                if (current == headNode) {
                    headNode = current->nextNode;
                }

                if (current == playerNode) {
                    playerNode = current->nextNode;
                }

                delete current;
                nodeCount--;
                return true;

            }
            previous = current;
            current = current->nextNode;
            stepCount++;
        }
        cout << "removeByName unwritten" << endl;
        return false;
    }

    // -------------------------------
    // Advanced Option A (Level 1): findByColor
    // -------------------------------
    vector<string> findByColor(string color) {
        // TODO:
        // - Traverse ring exactly once
        // - Collect matching names in vector<string>
        // - Return matches
        Node<T>* current = headNode;
        vector<string> matches;
        if (headNode == nullptr) {
            return matches;
        }
        int stepCount = 0;
        while (stepCount < nodeCount) {
            if (current->data.propertyColor == color) {
                matches.push_back(current->data.propertyName);

            }
            current = current->nextNode;
            stepCount++;
        }
        cout << "Colors Matched: " << endl;
        return matches;
    }

    // -------------------------------
    // Advanced Option B (Level 2): Mirror the Board (Circular Reversal)
    // -------------------------------
    void mirrorBoard() {
        // TODO:
        // - Reverse the direction of the circular list by reversing next pointers
        // - Preserve circular structure
        // - Correctly handle empty list and single-node list
        // - Player cursor must remain on the same logical space after reversal
        cout << "mirrorBoard unwritten" << endl;
    }

    // -------------------------------
    // Edge-case helper: countSpaces O(n)
    // -------------------------------
    int countSpaces() {
        // TODO:
        // - Must be O(n), traverse exactly once with correct stop condition
        // - Do NOT rely on nodeCount for this method
        Node<T>* current = headNode;
        Node<T>* startNode = headNode;
        int countSpaces = 0;
        if (headNode == nullptr) {
            return countSpaces;
        }
        do {
            countSpaces++;
            current = current->nextNode;
        }while (current != startNode);

        return countSpaces;
    }

    // -------------------------------
    // Cleanup
    // -------------------------------
    void clear() {
        // TODO:
        // - Safely delete all nodes
        // - Tip: if tailNode exists, break the cycle first: tailNode->nextNode = nullptr
        // - Then delete like a normal singly linked list
        Node<T>* current = headNode;
        if (tailNode != nullptr) {
            tailNode->nextNode = nullptr;
        }
        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->nextNode;
            delete temp;
        }
        headNode = nullptr;
        tailNode = nullptr;
        playerNode = nullptr;
        nodeCount = 0;
        passGoCount = 0;
    }
};

// -------------------------------
// Main: playable loop demo
// -------------------------------
int rollDice2to12() {
    return (rand() % 6 + 1) + (rand() % 6 + 1);
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    CircularLinkedList<MonopolySpace> board;

    // -------------------------------
    // Board Construction Phase
    // -------------------------------
    // You decide how to build the board:
    // - hardcode spaces, load from file, or generate spaces programmatically
    // The only requirement: never exceed MAX_SPACES and keep the list circular.
    //
    // Example (hardcoded) usage:
    vector<MonopolySpace> spaces = {
        {"GO","None",0,0},
        {"Mediterranean Avenue","Brown",60,2},
        {"Community Chest","None",0,0},
        {"Baltic Avenue","Brown",60,4},
        {"Income Tax","None",0,0},
        {"Reading Railroad","Railroad",200,25},
        {"Oriental Avenue","Light Blue",100,6},
        {"Chance","None",0,0},
        {"Vermont Avenue","Light Blue",100,6},
        {"Connecticut Avenue","Light Blue",120,8},
        {"Jail","None",0,0},
        {"St. Charles Place","Pink",140,10},
        {"Electric Company","Utility",150,10},
        {"States Avenue","Pink",140,10},
        {"Virginia Avenue","Pink",160,12},
        {"Pennsylvania Railroad","Railroad",200,25},
        {"St. James Place","Orange",180,14},
        {"Community Chest","None",0,0},
        {"Tennessee Avenue","Orange",180,14},
        {"New York Avenue","Orange",200,16},
        {"Free Parking","None",0,0},
        {"Kentucky Avenue","Red",220,18},
        {"Chance","None",0,0},
        {"Indiana Avenue","Red",220,18},
        {"Illinois Avenue","Red",240,20},
        {"B&O Railroad","Railroad",200,25},
        {"Atlantic Avenue","Yellow",260,22},
        {"Ventnor Avenue","Yellow",260,22},
        {"Water Works","Utility",150,10},
        {"Marvin Gardens","Yellow",280,24},
        {"Go To Jail","None",0,0},
        {"Pacific Avenue","Green",300,26},
        {"North Carolina Avenue","Green",300,26},
        {"Community Chest","None",0,0},
        {"Pennsylvania Avenue","Green",320,28},
        {"Short Line Railroad","Railroad",200,25},
        {"Chance","None",0,0},
        {"Park Place","Dark Blue",350,35},
        {"Luxury Tax","None",0,0},
        {"Boardwalk","Dark Blue",400,50}
    };

    // ...
     board.addMany(spaces);
    //
    // NOTE: This starter calls addSpace once to show the intended API,
    // but your final submission should build a meaningful board.
    // -------------------------------
    // Playable Traversal Loop
    // -------------------------------
    for (int turn = 1; turn <= 10; turn++) {
        int roll = rollDice2to12();
        cout << "\nTurn " << turn << " | Rolled: " << roll << endl;

        board.movePlayer(roll);

        cout << "Board view from player (next 5 spaces):" << endl;
        board.printFromPlayer(5);

        cout << "Times passed GO so far: " << board.getPassGoCount() << endl;
    }

    // -------------------------------
    // Advanced Feature Demos (students choose path)
    // -------------------------------
    // Option A examples:
    cout << endl;
    cout << "----- Remove by Name -----" << endl;
    cout << "Before Removal: " << board.countSpaces() << endl;
    board.removeByName("Baltic Avenue");
    cout << "After Removal: " << board.countSpaces() << endl;

    cout << endl;

    cout << "----- Find by Color -----" << endl;
     vector<string> GreenProps = board.findByColor("Green");
    for (int i = 0; i < GreenProps.size(); i++) {
        cout << "| " << GreenProps[i] << " |" << endl;
    }
    //
    // Option B example:
    // board.mirrorBoard();





    //ADD SPACE TEST
/*
    cout << "----- ADD SPACE TEST -----" << endl;
board.clear();
    int spaceAdd = 45; // Change how much times you add space one times
        for (int i = 0; i < spaceAdd; i++) {
            bool print = board.addSpace(MonopolySpace("Test" + to_string(i), "None", 31, 67));
            cout << print << endl;
        }
    cout << endl;
*/

    // ADD MANY TEST
  /*  cout << "----- ADD MANY TEST -----" << endl;
    board.clear();
   vector<MonopolySpace> players1;
    int numAdd = 40; // Change how many spaces you want to add.
    for (int i = 0; i < numAdd; i++) {
        players1.push_back(MonopolySpace("Test1" + to_string(i), "None", 0, 0));
    }
    int addedPlayers = board.addMany(players1);
    cout << "Test 1" << endl;
    cout << addedPlayers << endl;
    cout << endl;
*/

    // MOVE PLAYER TEST
   /* cout << "----- MOVE PLAYER TEST -----" << endl;
    vector<MonopolySpace> players;
    int numAdd = 39; // Change how many spaces you want to add.
    for (int i = 0; i < numAdd; i++) {
        players.push_back(MonopolySpace("Test" + to_string(i), "Red", 0, 0));
    }
    int addedPlayers = board.addMany(players);
    board.movePlayer(40);
    cout << "Pass Go Count: " << board.getPassGoCount() << endl;
    cout << endl; */

    // PRINT FROM PLAYER TEST
   /* cout << "----- PRINT FROM PLAYER TEST -----" << endl;

    board.printFromPlayer(5);
    cout << endl; */

    // REMOVE BY NAME TEST
  /*  cout << "----- REMOVE BY NAME TEST -----" << endl;
    board.removeByName("GO");
    board.removeByName("Test1");
    board.removeByName("Test2");
    board.printFromPlayer(5);
    cout << endl; */

    // MATCH BY COLOR TEST
   /* cout << "----- FIND BY COLOR TEST -----" << endl;
    vector<string> matches = board.findByColor("Red");
    for (int i = 0; i < matches.size(); i++) {
        cout << matches[i] << " ";
    }
    cout << endl; */

    // COUNT SPACES TEST
  /*  cout << "----- COUNT SPACES TEST -----" << endl;
    cout << "Spaces Counted: " << board.countSpaces() << endl;
    cout << endl;

    // ClEAR METHOD TEST
    cout << "----- CLEAR METHOD TEST -----" << endl;
    board.clear();
    cout << "Spaces Counted: " << board.countSpaces() << endl; */

    return 0;



}
