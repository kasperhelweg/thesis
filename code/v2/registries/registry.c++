//g++ -O3 -I ../utils/ -I ../nodes/ -I ./stores/ -I ./policies -I ./ -std=c++11 -o registry.out registry.c++
#include <iostream>
#include <assert.h>
#include <time.h>
#include <ctime>
#include <sys/time.h>
#include <algorithm>
#include <queue>

#include "heap_a_node.h++"
#include "node_a_modifier.h++"
#include "paper_store.h++"
#include "root_registry.h++"

#include "eager_consolidation_policy.h++"
#include "numeral_consolidation_policy.h++"

// Node
typedef long E1;
typedef KHJ::thesis::heap_node::heap_a_node<E1> N1;
// Node modifier
typedef std::less<N1> C1;
typedef KHJ::thesis::modifier::node_a_modifier<N1, C1> M1;
// Storage
typedef KHJ::thesis::store::paper_store<N1> S1;
// Registries
typedef KHJ::thesis::policy::numeral_consolidation_policy<N1, M1, S1> J1;
typedef KHJ::thesis::registry::root_registry<N1, M1, S1, J1> R1;

typedef KHJ::thesis::policy::eager_consolidation_policy<N1, M1, S1> J2;
typedef KHJ::thesis::registry::root_registry<N1, M1, S1, J2> R2;

int main( )
{
  R1 registry;
  R2 eager_registry;
  std::priority_queue<E1, std::vector<E1>, std::greater<E1> > mypq;

  E1 elements = 1000000;
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
  

  //----------------------PAPER REGISTRY----------------------
  std::cout << std::endl ; 
  std::cout << "----------------------PAPER REGISTRY----------------------" << std::endl;

  clock_t cpu0  = clock( );

  for( auto it = nodes.begin( ) ; it != nodes.end( ) ; it++ ) {
    registry.insert( *it );
    registry.consolidate( );
  }
  
  clock_t cpu1  = clock();
  double cpu_time = static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC;

  std::cout << "-----------------" << std::endl ; 
  std::cout << "CPU Push( ): " << cpu_time * 1000 << std::endl;
  std::cout << "-----------------" << std::endl ; 
  std::cout << std::endl ; 
  
  registry.print( );
  std::cout << std::endl ; 

  

  //----------------------PAPER REGISTRY EXTRACT----------------------
  
  cpu0  = clock( );
  for( int i = 1; i <= elements - 5  ; ++i ) {
    N1* S = registry.extract( );
    //delete S; S = nullptr;
  }
  cpu1  = clock();
  cpu_time = static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC;
    
  std::cout << "-----------------" << std::endl ; 
  std::cout << "CPU Pop( ): " << cpu_time * 1000 << std::endl;
  std::cout << "-----------------" << std::endl ; 
  std::cout << std::endl ; 
  registry.print( );
  std::cout << std::endl ; 

  for( auto it = nodes.begin( ) ; it != nodes.end( ) ; it++ ) {
    delete *it;
  }

 
  //----------------------EAGER REGISTRY----------------------

  std::cout << "----------------------EAGER REGISTRY----------------------" << std::endl;

  std::vector<N1*> nodes_eager;
  for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
    N1* S = new N1( *it );
    nodes_eager.push_back( S );
  }

  cpu0  = clock( );
  for( auto it = nodes_eager.begin( ) ; it != nodes_eager.end( ) ; it++ ) {
    eager_registry.insert( *it );
    eager_registry.consolidate( );
  }
  cpu1  = clock( );

  cpu_time = static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC;
  
  std::cout << "-----------------" << std::endl ; 
  std::cout << "CPU Push( ) - Eager: " << cpu_time * 1000 << std::endl;
  std::cout << "-----------------" << std::endl ; 
  std::cout << std::endl ; 

  eager_registry.print( );
  std::cout << std::endl ; 

  //----------------------EAGER REGISTRY EXTRACT----------------------

  cpu0  = clock( );
  std::random_shuffle ( nodes_eager.begin( ), nodes_eager.end( ) );
  for( int i = 1; i <= elements-5  ; ++i ) {
    N1* S = eager_registry.extract( );
    //std::cout << S->element( ) << std::endl ; 
    //delete S; S = nullptr;
  }
  cpu1  = clock( );

  cpu_time = static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC;
  
  std::cout << "-----------------" << std::endl ; 
  std::cout << "CPU Pop( ) - Eager: " << cpu_time * 1000 << std::endl;
  std::cout << "-----------------" << std::endl ; 
  std::cout << std::endl ; 

  eager_registry.print( );
  std::cout << std::endl ; 

  for( auto it = nodes_eager.begin( ) ; it != nodes_eager.end( ) ; it++ ) {
    delete *it;
  }

  //----------------------STD PQ----------------------

  std::cout << "----------------------STD PQueue----------------------" << std::endl; 
  cpu0  = clock( );
  for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
    mypq.push( *it );
  }
  cpu1  = clock( );

  cpu_time = static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC;
  
  std::cout << "-----------------" << std::endl ; 
  std::cout << "CPU Push( ) - STD: " << cpu_time * 1000 << std::endl;
  std::cout << "-----------------" << std::endl ; 
  std::cout << std::endl ; 


  cpu0  = clock( );
  for( int i = 1; i <= elements-5  ; ++i ) {
    mypq.pop( );
  }
  cpu1  = clock( );

  cpu_time = static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC;
  
  std::cout << "-----------------" << std::endl ; 
  std::cout << "CPU Pop( ) - STD: " << cpu_time * 1000 << std::endl;
  std::cout << "-----------------" << std::endl ; 
  std::cout << std::endl ; 

  return 0;
}
