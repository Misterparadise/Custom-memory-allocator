<h1>Custom Heap Memory Allocator</h1>
<h2>How my implementation works:</h2>
<h3>Data Structure</h3>
<p>I've created data structure that holds metadata about each chunk of allocated memory. Through the linked list of this data structure, it is possible to access the address of any memory block in the list, its size, availability, the next and previous chunks of adjacent memory and the end of the block.</p>
<h3>Algorithm</h3>
<p>My implementation uses "first fit" strategy". The algorithm searches list from biginning to the end, until it finds big enough block and returns it adress to user. To free memory, the algorithm changes the “available” state of the chunk’s metadata (struct), releasing it to further allocation. After that, the freed chunk is merged with the previous block (if this one is also freed), this is useful to avoid memory fragmentation in small sized blocks (it can happens after some splittings). </p>
