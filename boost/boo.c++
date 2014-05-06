#include <iostream>
#include <assert.h>
#include <time.h>
#include <ctime>
#include <sys/time.h>
#include <algorithm>
#include <queue>

#include "binomial_heap.hpp"
#include "fibonacci_heap.hpp"

typedef long long E;

int main( )
{
  boost::heap::fibonacci_heap<E> pq; 
  
  E elements = 1000000;
  std::vector<E> data;
  for (E i = elements; i >= 1; --i) data.push_back( i );
  std::random_shuffle ( data.begin( ), data.end( ) );
  
  std::cout << std::endl ; 
  std::cout << "----------------------PAPER REGISTRY----------------------" << std::endl;
  clock_t cpu0  = clock( );
  
  for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
    pq.push( *it );
  }
  
  clock_t cpu1  = clock();
  double cpu_time = static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC;
  
  std::cout << "-----------------" << std::endl ; 
  std::cout << "CPU Push( ): " << cpu_time * 1000 << std::endl;
  std::cout << "-----------------" << std::endl ; 
  std::cout << std::endl ;   
  std::cout << std::endl ; 

  cpu0  = clock( );
  
  for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
    pq.pop( );
  }
  
  cpu1  = clock();
  cpu_time = static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC;
  
  std::cout << "-----------------" << std::endl ; 
  std::cout << "CPU Push( ): " << cpu_time * 1000 << std::endl;
  std::cout << "-----------------" << std::endl ; 
  std::cout << std::endl ;   
  std::cout << std::endl ;
  
  return 0;
  
}
