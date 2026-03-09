### Entry 1
Date : 3/8/26
Entry Type: Engineering Decision on CountSpaces
Had troubling implementing count spaces using a while loop because it would cause an off-by-one problem, I tried to initialize the count at 1 but then I'd be off in specific cases such as an empty list having a count of 1.
By implementing a do loop I can always count the head node and then stop once I'm back at it.

### Entry 2
Date : 3/8/26
Entry Type: BugFix on implementation of clear()
After testing my clear method  I had exit code 0xC0000005, highlighting that I had dereferenced memory or null memory. 
I realized that the clear() deletes all the nodes but never resets node characteristics back in place like
headNode, tailNode, playNode, and nodeCount.

## Entry 3
Date : 3/8/26
Entry Type: BugFix on implementation of printFromPlayer()
Error/Symptoms: Printing method unintentionally modifying player position.
Attempts Made: Initially used playerNode for traversal.
Fix: Introduce another variable to simulate player behavior while preserving playNode.

## Entry 4 
Date : 3/8/26
Entry Type: Testing RemoveByName
Attempts: Before removal and after removal I would call to countSpaces to see if there was a difference in space count.
Solution: I was able to confirm that the delete my name method properly removed a space and that the circular structure was still intact.

## Entry 5
Date : 3/8/26 
Entry Type: Bug
Attempts: While running all my separate tests I was wondering why my tests have all start at "Test10" instead of "Test1".
Solution: What I thought was a traversal error was a concatenation error.

## Entry 6
Date : 3/8/26
Entry Type: Testing / Edge Case
Attempts: During my tests I wanted to verify if my board correctly enforced the 40 Space limit during both bulk insertion and single insertion.
Solution: Inserted spaces one at a time with addSpace and in bulk with addMany. Tests were successful as output results showed limit enforcement. 
Method addSpace would return 0 on unsuccessful operations and addMany would always return an output and integer >= 40 verifying that the max bulk insertion is 40.  
