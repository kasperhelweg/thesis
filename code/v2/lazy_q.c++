#include "heap_awh_node.h++"
#include "node_awh_modifier.h++"
#include "lazy_root_list.h++"
#include "lazy_root_registry.h++"
#include "lazy_binary_queue.h++"
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
typedef KHJ::thesis::heap_node::heap_awh_node<E> N;
// Node modifier
typedef KHJ::thesis::modifier::node_awh_modifier<N, C1> M;
// Allocator
typedef std::allocator<N> A;
// Storage
typedef KHJ::thesis::root_list::lazy_root_list<N> S;
typedef KHJ::thesis::root_registry::lazy_root_registry<N, M, S> F;
/* LAZY BINARY QUEUE */
typedef KHJ::thesis::queue::lazy_binary_queue<E, C1, N, M, F> R;
typedef KHJ::thesis::priority_queue::meldable_priority_queue<E, C1, A, N, R> Q;

typedef KHJ::thesis::benchmark::bench<N, E, Q> B;

int main( )
{
  B benchmarker( comps, "lazy" );
  Q lazy_Q;

 benchmarker.push( lazy_Q );
 //assert( lazy_Q.size( ) == 0 );
 benchmarker.pop( lazy_Q );
 benchmarker.emplace( lazy_Q );
 benchmarker.erase( lazy_Q );
  
 return 0;
}
