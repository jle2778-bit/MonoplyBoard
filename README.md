## Build Instructions 
Open project folder in CLion, click the run button in CLion.

## Data Structures Used
MonopolySpace (Class) - Represents single space on Monopoly Board

Fields:
propertyName - Name of space
propertyColor - Color group or category
value - purchase value of property
rent - Cost of rent

Node<T> (Template Class) - Represents nodes in circular linked list
Fields:
data - holds MonopolySpace data
nextNode - Points to next node in the list

CircularLinkedList<T> (Template Class) - Implement Monopoly board through circular linked list.

Private Members:
headNode - pointer to first node
tailNode - pointer to last node
playerNode - pointer to players current node
nodeCount - current number of spaces
passGoCount - Number of times player passed "GO" space.

## List of Functions
MonopolySpace() - initializes an empty Monopoly space.
MonopolySpace(string name, string color, int value, int rent) -  initializes a Monopoly space with provided values.
bool isEqual(MonopolySpace other) - compares two MonopolySpace objects.
void print() - print formatted information about a board space.
CircularLinkedList() - initializes an empty circular linked list.
bool addSpace(T value) - add a node to the tail while enforcing the 40 space limit and preserving circular structure.
int addMany(vector<T> values) - adds multiple spaces sequentially until capacity is reached and returns the number successfully added.
void movePlayer(int steps) - moves the player forward step by step and increments passGoCount when passing GO.
int getPassGoCount() - returns the number of times the player has passed GO.
void printFromPlayer(int count) - preview a fixed number of spaces starting from the player position without modifying it.
bool removeByName(string name) - deletes the first matching space and correctly handles head, tail, and single node cases.
vector<string> findByColor(string color) - traverses the board once and returns the names of matching colored spaces.
int countSpaces() - traverses the circular list once and returns the total number of spaces.
void clear() - deletes all nodes safely and resets the board to an empty state.



## Transversal and Movement Logic
Monopoly board is implemented as a circular linked list, meaning that tail node points back to the head node.
tailNode -> nextNode = headNode

All movement is done through pointer transversal.
Using "nextNode" we can traverse our player's position.

playerNode = playNode -> nextNode

Circular Structure ensures that movement wraps from the last node to the front node.
Each "wrap" or passing of the "GO" space is marked by the traversal of the tailNode to the headNode, also tracked by "passGoCount"

Single "Full-Board" Loop Traversal Strategy 
1. Start at headNode 
2. Traverse with nextNode
3. Stop traversal once we return to starting node.

## 40 Space Board Limit
The board enforces a maximum of 40 spaces. The addSpace function prevents insertion once max is reach, ensuring circular structure is kept.

