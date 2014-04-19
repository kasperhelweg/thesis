// g++ -Wall -O3 -I ../utils/ -I ./ -I ./nodes -I ./nodes/modifiers -I ./stores -std=c++11 -o heap.out heap.c++/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <assert.h>
#include <time.h>
#include <ctime>
#include <sys/time.h>
#include "magical_heap.h++"
#include "magical_heap_store.h++"
#include "heap_a_node.h++"
#include "modifier_a_node.h++"
#include "heap_b_node.h++"

#include <queue>
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




typedef long long V;
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

// Utils
typedef KHJ::thesis::utils::pfb<N1, V> pfb_N1;
template<> std::deque<N1*> pfb_N1::heap = { };

//typedef KHJ::thesis::stores::join_schedule<std::vector> J1;
//typedef KHJ::thesis::stores::heap_a_store<N1, J1, std::list, std::vec> S;

// Utils
//typedef KHJ::thesis::utils::pfb<N1, V> pfb_N1;
//template<> std::deque<N1*> pfb_N1::heap = { };


int main( ) 
{
  V elements = 10000000;
  std::vector<V> data;
  for (V i = elements; i >= 1; --i) data.push_back( i );
  //std::random_shuffle ( data.begin( ), data.end( ) );
  //std::random_shuffle ( data.begin( ), data.end( ) );

  // min heap

  H1 heap; 
  std::priority_queue<V, std::vector<V>, std::greater<V> > mypq;
  std::vector<V> heap_vec;
  std::vector<V> pq_vec;


  clock_t cpu0  = clock( );
  for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
    heap.push( *it );
  }

  /*
  V m;
  for (int i = 1; i <= elements - 5 ; ++i) {
    heap_vec.push_back( heap.pop( ) );
  }
  */
  clock_t cpu1  = clock();
  double cpu_time = static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC;
  
  heap.print( );
  std::cout << "-----------------" << std::endl ; 
  std::cout << "CPU: " << cpu_time * 1000 << std::endl;
  
  /*
  for( auto it = heap_vec.begin( ) ; it != heap_vec.end( ) ; it++ ) {
    std::cout << ( *it ) << " ";
  }
  std::cout << std::endl;
  */

  cpu0  = clock();
  for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
    mypq.push( *it );
  }

  /*
  for (int i = 1; i <= elements - 5; ++i) {
    pq_vec.push_back( mypq.top( ) );
    mypq.pop( );
  }
  */
  cpu1  = clock();  
  cpu_time = static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC;
  
  std::cout << "CPU: " << cpu_time * 1000 << std::endl;
  std::cout << std::endl;
  

/*
  for( auto it = heap.begin( ) ; it != heap.end( ) ; it++ ) {
    for( auto vit = (*it).begin( ) ; vit != (*it).end( ) ; vit++ ) {
      //std::cout << (*vit)->element_ << std::endl;
      //std::cout << "h" << std::endl;
      pfb_N1::assert_heap( (true, *vit) );
    }
  }

  V m;
  for (int i = 1; i <= 90000; ++i) {
   m = heap.pop( );
   std::cout << "pop: " << m << std::endl;
   //heap.print( );
 for( auto it = heap.begin( ) ; it != heap.end( ) ; it++ ) {
    for( auto vit = (*it).begin( ) ; vit != (*it).end( ) ; vit++ ) {
      //std::cout << (*vit)->element_ << std::endl;
      pfb_N1::assert_heap( (true, *vit) );
    }
  }
  }

 
*/

  return 0;
}
