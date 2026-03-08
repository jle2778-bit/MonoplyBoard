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
            int stepCount = stepCount + 1;
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

        cout << "Displated Spaces: " << count << endl;
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
        cout << "findByColor unwritten" << endl;
        vector<string> matches;
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
        cout << "countSpaces unwritten" << endl;
        return 0;
    }

    // -------------------------------
    // Cleanup
    // -------------------------------
    void clear() {
        // TODO:
        // - Safely delete all nodes
        // - Tip: if tailNode exists, break the cycle first: tailNode->nextNode = nullptr
        // - Then delete like a normal singly linked list
        cout << "clear unwritten" << endl;
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
    // vector<MonopolySpace> spaces;
    // spaces.push_back(MonopolySpace("GO","None",0,0));
    // ...
    // board.addMany(spaces);
    //
    // NOTE: This starter calls addSpace once to show the intended API,
    // but your final submission should build a meaningful board.
    board.addSpace(MonopolySpace("GO", "None", 0, 0));

    // -------------------------------
    // Playable Traversal Loop
    // -------------------------------
 /*   for (int turn = 1; turn <= 10; turn++) {
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
    // board.removeByName("Baltic Avenue");
    // vector<string> brownProps = board.findByColor("Brown");
    //
    // Option B example:
    // board.mirrorBoard();
*/
    //ADD SPACE TEST
    /* cout << "----- ADD SPACE TEST -----" << endl;

    int spaceAdd = 41; // Change how much times you add space one times
        for (int i = 0; i < spaceAdd; i++) {
            bool print = board.addSpace(MonopolySpace("Test" + to_string(i), "None", 31, 67));
            cout << print << endl;
        }
    cout << endl;
    */

    // ADD MANY TEST
    /*cout << "----- ADD MANY TEST -----" << endl;


   vector<MonopolySpace> players;
    int numAdd = 40; // Change how many spaces you want to add.
    for (int i = 0; i < numAdd; i++) {
        players.push_back(MonopolySpace("Test1" + to_string(i), "None", 0, 0));
    }
    int addedPlayers = board.addMany(players);
    cout << "Test 1" << endl;
    cout << addedPlayers << endl;
    cout << endl;
    */

    // MOVE PLAYER TEST
    cout << "----- MOVE PLAYER TEST -----" << endl;
    vector<MonopolySpace> players;
    int numAdd = 40; // Change how many spaces you want to add.
    for (int i = 0; i < numAdd; i++) {
        players.push_back(MonopolySpace("Test1" + to_string(i), "None", 0, 0));
    }
    int addedPlayers = board.addMany(players);
    board.movePlayer(40);
    cout << "Pass Go Count: " << board.getPassGoCount() << endl;
    cout << endl;

    // PRINT FROM PLAYER TEST
    cout << "----- PRINT FROM PLAYER TEST -----" << endl;

    board.printFromPlayer(5);
    cout << endl;

    return 0;
}
