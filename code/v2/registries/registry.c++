//g++ -O3 -I ../utils/ -I ../nodes/ -I ./stores/ -I ./policies -I ./ -std=c++11 -o registry.out registry.c++
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

// Node
typedef long E1;
typedef KHJ::thesis::heap_node::heap_a_node<E1> N1;
// Node modifier
typedef std::less<N1> C1;
typedef KHJ::thesis::modifier::node_a_modifier<N1, C1> M1;
// Storage
typedef KHJ::thesis::store::paper_store<N1, C1> S1;
typedef S1::iterator_type F1;
// Join policy
typedef KHJ::thesis::policy::paper_join_policy<F1> J1;
// Registry
typedef KHJ::thesis::registry::root_registry<N1, M1, S1, J1> R1;

int main( )
{
  R1 registry;
  
  E1 elements = 10000;
  std::vector<E1> data;
  for (E1 i = elements; i >= 1; --i) data.push_back( i );
  std::random_shuffle ( data.begin( ), data.end( ) );
  
  std::vector<N1*> nodes;
  for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
    //std::cout << *it << std::endl;
    N1* S = new N1( *it );
    nodes.push_back( S );
    //registry.print( );
  }

  clock_t cpu0  = clock( );
  for( auto it = nodes.begin( ) ; it != nodes.end( ) ; it++ ) {
    registry.insert( *it );
  }
  clock_t cpu1  = clock();
  double cpu_time = static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC;

  std::cout << "-----------------" << std::endl ; 
  std::cout << "CPU: " << cpu_time * 1000 << std::endl;
  std::cout << "-----------------" << std::endl ; 
  std::cout << std::endl ; 

  registry.print( );
  std::cout << std::endl ; 
  
  std::vector<E1> sort_vec;
  for( int i = 1; i != 9000 ; ++i ) {
    N1* S = registry.extract_min( );
    sort_vec.push_back( S->element( ) );
    //std::cout << "extract: " << (*S).element( ) << std::endl;
    //delete S; S = nullptr;
    //registry.print( );
  }
  //registry.print( );
  
  assert( std::is_sorted( sort_vec.begin(),sort_vec.end() ));
  
  

  for( auto it = nodes.begin( ) ; it != nodes.end( ) ; it++ ) {
    delete *it;
   }

  //for( int i = 0; i != n; i++ ) {
  //  N1* S = registry.extract( );
  //  delete S;
  //}
  
  //registry.insert( );
  //registry.extract( );
  
  return 0;
}
