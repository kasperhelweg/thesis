#include <iostream>
#include <assert.h>
#include <time.h>
#include <ctime>
#include <sys/time.h>
#include <algorithm>

#include "heap_a_node.h++"
#include "node_a_modifier.h++"

#include "paper_store.h++"
#include "paper_join_policy.h++"

#include "root_registry.h++"
#include "magic_queue.h++"

// Node
typedef long E1;
typedef KHJ::thesis::heap_node::heap_a_node<E1> N1;
// Node modifier
typedef std::less<N1> C1;
typedef KHJ::thesis::modifier::node_a_modifier<N1, C1> M1;
// Allocator
typedef std::allocator<N1> A1;


/* Magic Queue - Not Meldable */
// Storage
typedef KHJ::thesis::store::paper_store<N1> S1;
typedef S1::iterator_type F1;
// Join policy
typedef KHJ::thesis::policy::paper_join_policy<F1> J1;
// Registry
typedef KHJ::thesis::registry::root_registry<N1, M1, S1, J1> R1;
// magic queue( not meldable )
typedef KHJ::thesis::queue::magic_queue<N1, M1, R1, A1> B1;

/* Magic Queue - Meldable */
/* Magic Queue - Lazy */


//typedef KHJ::thesis::priority_queue::meldable_priority_queue<N1, M1, R1, B1> Q


int main( ) 
{
  
}
