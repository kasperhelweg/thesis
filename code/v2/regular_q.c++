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

typedef long E;
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
  /*
  unsigned long x = 1;
  unsigned short b = 65535;
  
  std::cout << "x size = " << sizeof( x ) << std::endl;
  std::cout << "b size = " << sizeof( b ) << std::endl;
  std::cout << "x = " << (std::bitset<sizeof( x ) * 8>) x << std::endl;
  std::cout << "b = " << (std::bitset<sizeof( b ) * 8>) b << std::endl;
  
  x |= 1 << 5;
  x |= 1 << 10;
  std::cout << "x = " << (std::bitset<sizeof( x ) * 8>) x << std::endl;
  
  // updating the bittrace
  char s  = x & (1 << 0);
  x = x >> 1;
  std::cout << "x = " << (std::bitset<sizeof( x ) * 8>) x << std::endl;
  std::cout << "s = " <<  (int)s << std::endl;
  
  */
  
  /*
  std::vector<E>  data;
  std::vector<N*> nodes;
  */
  /*
  for (E i = 1000; i >= 1; --i) data.push_back( i );
  std::random_shuffle ( data.begin( ), data.end( ) );
  */
  /*
  for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
    N* n = new N( *it );
    nodes.push_back( n );
  }

  for( auto it = nodes.begin( ) ; it != nodes.end( ) ; it++ ) {
    regular_Q.push( *it );
  }
  */

  /*
  for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
    regular_Q.emplace( *it );
  }

   for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
     //std::cout << regular_Q.pop( ) << std::endl;
     regular_Q.pop( );
   }

   */
  /*
  for( auto it = nodes.begin( ) ; it != nodes.end( ) ; it++ ) {
    regular_Q.erase( *it );
  }
 
  */
  /*

  for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
    regular_Q.emplace( *it );
  }

  regular_Q.print( );

  for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
    regular_Q.pop( );
  }
  regular_Q.print( );
  
  */
  
  benchmarker.push( regular_Q );
  benchmarker.pop( regular_Q );
  benchmarker.emplace( regular_Q );
  benchmarker.erase( regular_Q );
  
  return 0;

}
