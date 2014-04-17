The basic components of this micro framework are:

-Heaps / Nodes
-HeapStores 

Thus, a meldable priority queue might be build combinatorially

Node<V, C, A> N
HeapStore<V, C, A, N> H
Heap<V, C, A, H> R
PriorityQueue<V, C, A, R> Q

and so on. The combinatorial obejcts can be split/refactored into more or less atomic and selfcontained pieces of code.
For example a HeapStore might have additional type parameters such as F( root list type).
Also, a Node might have a type parameter M for Modifier .

In the end it is challenging at best to find a solid design with the right balance. One problem is the growth of type parameters. However, 5-6 
paramters should be acceptable. Also, many of the structures can have sensible defaults so that basically no parameters have to be given by the user.  

--------------
The heaps are just linked collections of nodes. Thus, a heap is just a pointer.

HeapStores are used to keep track of the collection of heaps. They can be composed of several components themself, ex.:
- different join/split schedules
- different root list types

A heapstore is usually an implicit numeral representation of the collection.

It is of course necesary that all components have predictable signatures. 

For example, a heapstore has to support Inject() and Eject()
A node( or a supplied modifier ) will have to support sift's, joins and splits.
