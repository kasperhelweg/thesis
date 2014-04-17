// g++ -Wall -O3 -I ../utils/ -I ./ -I ./nodes -I ./nodes/modifiers -I ./stores -std=c++11 -o heap.out heap.c++/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <assert.h>
#include <time.h>

#include "magical_heap.h++"
#include "magical_heap_store.h++"
#include "heap_a_node.h++"
#include "modifier_a_node.h++"
#include "heap_b_node.h++"
//#include "heap_utils.h++"

/*

  // element type
  typedef int V; 
  
  // node type
  typedef heap_a_node<V> N1;
  
  // comparator type
  typedef std::less<N1> C;
  
  // allocator type
  typedef std::allocator<N1> A;
  
  // node modifier - 
  // C allows to compare using compare( N1 a, N1 b)
  typedef heap_a_node_modifier<N1, C> M;
  
  // heap_store - 
  // C allows to compare using compare( N1 a, N1 b)
  // M allows operations on heaps
  typedef heap_store<N1, C, M> S;
  

  // heap and priority_queue
  // the heap is the realization of the priority queue
  typedef heap<V, C, N1, S> H;
  typedef meldable_priority_queue<V, C, A, N1, H> Q;
  
 */

/*
template <typename T>
class counting_comparator {
public:

  bool operator()(T const& a, T const& b) const {
    ++comps;
    return a < b;
  }
};
*/


typedef int V;
typedef std::less<V> C;
typedef std::allocator<V> A;
typedef KHJ::thesis::heap_node::heap_a_node<V, C, A> N1;

/*
  WORKS:
  ------
  typedef std::less<N1> C2;
  typedef KHJ::thesis::modifier::modifier_a_node<N1, C2> M1;
  ------
  THEN WE SHOULD DO:
  typedef KHJ::thesis::stores::magical_heap_store<N1, M1> S1;
*/

// this will be avoided in a modifier design like above
typedef std::less<N1> NC;
typedef KHJ::thesis::stores::magical_heap_store<N1, NC> S1;


typedef KHJ::thesis::heaps::magical_heap<N1, S1> H1;


//typedef KHJ::thesis::stores::join_schedule<std::vector> J1;
//typedef KHJ::thesis::stores::heap_a_store<N1, J1, std::list, std::vec> S;

// Utils
//typedef KHJ::thesis::utils::pfb<N1, V> pfb_N1;
//template<> std::deque<N1*> pfb_N1::heap = { };

int main( )
{
  std::vector<int> data;
  for (int i = 1000; i <= 100000000; ++i) data.push_back( i );
  std::random_shuffle ( data.begin( ), data.end( ) );

  H1 heap; 
  for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
    //std::cout << *it << std::endl;
    heap.push( *it );
  }
  heap.print( );
  return 0;
}
