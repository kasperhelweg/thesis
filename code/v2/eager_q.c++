#include "heap_a_node.h++"
#include "node_a_modifier.h++"
#include "paper_root_table.h++"
#include "eager_root_registry.h++"
#include "eager_binary_queue.h++"
#include "meldable_priority_queue.h++"

#include "benchmarks.h++"

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
typedef KHJ::thesis::root_table::paper_root_table<N> S;
/* LAZY BINARY QUEUE */
typedef KHJ::thesis::root_registry::eager_root_registry<N, M, S> F;
// eager binary queue
typedef KHJ::thesis::queue::eager_binary_queue<E, C1, N, M, F> R;
typedef KHJ::thesis::priority_queue::meldable_priority_queue<E, C1, A, N, R> Q;

typedef KHJ::thesis::benchmark::bench<N, E, Q> B;

int main( )
{

  B benchmarker( comps, "eager" );
  Q eager_Q;

  benchmarker.push( eager_Q );
  //assert( eager_Q.size( ) == 0 );
  benchmarker.pop( eager_Q );
  benchmarker.emplace( eager_Q );
  benchmarker.erase( eager_Q );
 
  return 0;
}
