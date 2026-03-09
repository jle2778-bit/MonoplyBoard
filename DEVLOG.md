### Entry 1
Date : 3/8/26
Entry Type: Engineering Decision on CountSpaces
Had troubling implementing count spaces using a while loop because it would cause an off-by-one problem, I tried to initialize the count at 1 but then I'd be off in specfic cases.
By implementing a do loop I can always count the head node and then stop once I'm back at it.

### Entry 2
Date : 3/8/26
Entry Type: Engineering Decision on CountSpaces
After testing my clear method  I had exit code 0xC0000005, highlighting that I had dereferenced memory or null memory. 
I realized that the clear() deletes all the nodes but never resets node characteristics back in place like
headNode, tailNode, playNode, and nodeCount.