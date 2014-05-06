#include <iostream>
#include <fstream>
#include <assert.h>
#include <time.h>
#include <ctime>
#include <sys/time.h>
#include <algorithm>

#include "heap_a_node.h++"
#include "node_a_modifier.h++"

#include "paper_store.h++"

#include "numeral_consolidation_policy.h++"

#include "root_registry.h++"

#include "numeral_binary_queue.h++"
#include "meldable_priority_queue.h++"

#include "benchmarks.h++"
//long long comps = 0;

static long long comps;
template <typename T>
class counting_comparator {
public:  
  long long& c = comps;
  bool operator()(T const& a, T const& b) const {
    ++comps;
    return a < b;
  }
};

typedef long E;
typedef std::less<E> C;
typedef counting_comparator<E> C1;
typedef KHJ::thesis::heap_node::heap_a_node<E> N;
// Node modifier
typedef KHJ::thesis::modifier::node_a_modifier<N, C1> M;
// Allocator
typedef std::allocator<N> A;
// Storage
typedef KHJ::thesis::store::paper_store<N> S;
/* LAZY BINARY QUEUE */
// Policy policy
typedef KHJ::thesis::policy::numeral_consolidation_policy<N, M, S> J;
// Registry
typedef KHJ::thesis::registry::root_registry<N, M, S, J> F;
// eager binary queue
typedef KHJ::thesis::queue::numeral_binary_queue<E, C1, N, M, F> R;
typedef KHJ::thesis::priority_queue::meldable_priority_queue<E, C1, A, N, R> Q;

// Benchmarking
typedef KHJ::thesis::benchmark::bench<N, E, Q> B;

int main( )
{  
  B benchmarker( comps, "magic" );
  Q magic_Q;

  benchmarker.push( magic_Q );
//assert( magic_Q.size( ) == 0 );
  benchmarker.pop( magic_Q );
  benchmarker.emplace( magic_Q );
  benchmarker.erase( magic_Q );
  
  return 0;
}
