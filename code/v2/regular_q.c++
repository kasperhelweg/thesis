#include "heap_awh_node.h++"
#include "node_awh_modifier.h++"
#include "regular_root_table.h++"
#include "regular_root_registry.h++"
#include "regular_binary_queue.h++"
#include "meldable_priority_queue.h++"

#include "benchmarks.h++"

#include <bitset>


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

typedef long long E;
typedef std::less<E> C;
typedef counting_comparator<E> C1;
typedef KHJ::thesis::heap_node::heap_awh_node<E> N;
// Node modifier
typedef KHJ::thesis::modifier::node_awh_modifier<E, N, C1> M;
// Allocator
typedef std::allocator<N> A;
// Storage
typedef KHJ::thesis::root_table::regular_root_table<N> S;
/* LAZY BINARY QUEUE */
typedef KHJ::thesis::root_registry::regular_root_registry<N, M, S> F;
// eager binary queue
typedef KHJ::thesis::queue::regular_binary_queue<E, C1, N, M, F> R;
typedef KHJ::thesis::priority_queue::meldable_priority_queue<E, C1, A, N, R> Q;

typedef KHJ::thesis::benchmark::bench<N, E, Q> B;

int main( )
{

  B benchmarker( comps, "regular" );
  Q regular_Q;

  std::cout << "---REGULAR---" << std::endl;
  benchmarker.push( regular_Q );
  regular_Q.clear( );
  benchmarker.pop( regular_Q );
  regular_Q.clear( );
  benchmarker.emplace( regular_Q );
  regular_Q.clear( );
  benchmarker.erase( regular_Q );
  regular_Q.clear( );
  benchmarker.decrease_key( regular_Q );
  regular_Q.clear( );
  benchmarker.seq_a( regular_Q ); 
  regular_Q.clear( );

  return 0;
}
