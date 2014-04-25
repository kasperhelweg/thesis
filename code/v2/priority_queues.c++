/*
  g++ -O3 -I ./utils/ -I ./nodes/ -I ./registries -I ./registries/stores/ -I ./registries/policies -I ./realizers -I ./containers -I ./ -std=c++11 -o priority_queues.out priority_queues.c++
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

#include "numeral_consolidation_policy.h++"
#include "eager_consolidation_policy.h++"
#include "root_registry.h++"

#include "numeral_binary_queue.h++"
#include "eager_binary_queue.h++"

#include "meldable_priority_queue.h++"

typedef long E1;
typedef KHJ::thesis::heap_node::heap_a_node<E1> N1;
// Node modifier
typedef std::less<N1> C1;
typedef KHJ::thesis::modifier::node_a_modifier<N1, C1> M1;
// Allocator
typedef std::allocator<N1> A1;
// Storage
typedef KHJ::thesis::store::paper_store<N1> S1;

/* NUMERAL BINARY QUEUE */
// Policy policy
typedef KHJ::thesis::policy::numeral_consolidation_policy<N1, M1, S1> J1;
// Registry
typedef KHJ::thesis::registry::root_registry<N1, M1, S1, J1> F1;
// eager binary queue
typedef KHJ::thesis::queue::numeral_binary_queue<E1, C1, N1, M1, F1> R1;
typedef KHJ::thesis::priority_queue::meldable_priority_queue<E1, C1, A1, N1, R1> Q1;

/* EAGER BINARY QUEUE */
// Policy policy
typedef KHJ::thesis::policy::eager_consolidation_policy<N1, M1, S1> J2;
// Registry
typedef KHJ::thesis::registry::root_registry<N1, M1, S1, J2> F2;
// eager binary queue
typedef KHJ::thesis::queue::eager_binary_queue<E1, C1, N1, M1, F2> R2;
typedef KHJ::thesis::priority_queue::meldable_priority_queue<E1, C1, A1, N1, R2> Q2;


int main( ) 
{
  Q1 magic_Q;

  E1 elements = 10000000;
  std::vector<E1> data;
  for (E1 i = elements; i >= 1; --i) data.push_back( i );
  std::random_shuffle ( data.begin( ), data.end( ) );
  
  std::vector<N1*> nodes;
  clock_t cpu0  = clock( );
  for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
    nodes.push_back( magic_Q.emplace( *it ) );
  }
  clock_t cpu1  = clock();
  double cpu_time = static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC;

  std::cout << "-----------------" << std::endl ; 
  std::cout << "CPU Push( ): " << cpu_time * 1000 << std::endl;
  std::cout << "-----------------" << std::endl ; 
  std::cout << std::endl ; 
  
  std::random_shuffle ( nodes.begin( ), nodes.end( ) );
  cpu0  = clock( );
  for( int i = 1; i < elements - 5  ; ++i ) {
    //magic_Q.pop( );
    magic_Q.erase( nodes.back( ) );
    nodes.pop_back( );
  }
  cpu1  = clock();
  cpu_time = static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC;
  //assert( nodes.size() == 1 );
  
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
