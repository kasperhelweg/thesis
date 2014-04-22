/*
g++ -O3 -I ./utils/ -I ./nodes/ -I ./registries -I ./registries/stores/ -I ./registries/policies -I ./realizers -I ./ -std=c++11 -o priority_queues.out priority_queues.c++
*/

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
typedef KHJ::thesis::priority_queue::magic_queue<E1, N1, R1, A1> Q1;

/* Magic Queue - Meldable */
/* Magic Queue - Lazy */


//typedef KHJ::thesis::priority_queue::meldable_priority_queue<N1, M1, R1, B1> Q


int main( ) 
{
  Q1 magic_Q;

  E1 elements = 1000000;
  std::vector<E1> data;
  for (E1 i = elements; i >= 1; --i) data.push_back( i );
  std::random_shuffle ( data.begin( ), data.end( ) );
  
  std::vector<N1*> nodes;
  clock_t cpu0  = clock( );
  for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
    nodes.push_back( magic_Q.push( *it ) );
  }
  clock_t cpu1  = clock();
  double cpu_time = static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC;

  std::cout << "-----------------" << std::endl ; 
  std::cout << "CPU Push( ): " << cpu_time * 1000 << std::endl;
  std::cout << "-----------------" << std::endl ; 
  std::cout << std::endl ; 

  
  std::random_shuffle ( nodes.begin( ), nodes.end( ) );
  cpu0  = clock( );
  for( int i = 1; i <= elements-5  ; ++i ) {
    magic_Q.erase( nodes.back( ) );
    nodes.pop_back( );
  }
  cpu1  = clock();
  cpu_time = static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC;
  assert( nodes.size() == 5 );
  
  std::cout << "-----------------" << std::endl ; 
  std::cout << "CPU Delete( ): " << cpu_time * 1000 << std::endl;
  std::cout << "-----------------" << std::endl ; 
  std::cout << std::endl ; 

  /*
  std::vector<E1> sort_vec;
  cpu0  = clock( );
  for( int i = 1; i <= elements-5  ; ++i ) {
    sort_vec.push_back( magic_Q.pop( ) );
  }
  cpu1  = clock();
  cpu_time = static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC;
  assert( sort_vec.size() == elements - 5 );
  assert( std::is_sorted( sort_vec.begin(),sort_vec.end() ));

  std::cout << "-----------------" << std::endl ; 
  std::cout << "CPU Pop( ): " << cpu_time * 1000 << std::endl;
  std::cout << "-----------------" << std::endl ; 
  std::cout << std::endl ; 
  */
  return 0;
}
