#include <iostream>
#include <time.h>
#include <ctime>
#include <sys/time.h>
#include <algorithm>
#include "heap_a_node.h++"
#include "node_a_modifier.h++"
#include "paper_store.h++"
#include "root_registry.h++"

typedef long E1;
typedef KHJ::thesis::heap_node::heap_a_node<E1> N1;

typedef std::less<N1> C1;
typedef KHJ::thesis::modifier::node_a_modifier<N1, C1> M1;

typedef KHJ::thesis::store::paper_store<N1> S1;
typedef KHJ::thesis::registry::root_registry<N1, M1, S1> R1;

int main( )
{
  R1 registry;

  E1 elements = 1000000;
  std::vector<E1> data;
  for (E1 i = elements; i >= 1; --i) data.push_back( i );
  std::random_shuffle ( data.begin( ), data.end( ) );
  
  std::vector<N1*> nodes;
  for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
    //std::cout << *it << std::endl;
    N1* S = new N1( *it );
    nodes.push_back( S );
  }

  clock_t cpu0  = clock( );
  for( auto it = nodes.begin( ) ; it != nodes.end( ) ; it++ ) {
    registry.insert( *it );
  }
  clock_t cpu1  = clock();
  double cpu_time = static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC;
  
  //heap.print( );
  std::cout << "-----------------" << std::endl ; 
  std::cout << "CPU: " << cpu_time * 1000 << std::endl;
  std::cout << "-----------------" << std::endl ; 

  registry.print( );

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
