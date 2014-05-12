#include <iostream>
#include <fstream>
#include <assert.h>
#include <time.h>
#include <ctime>
#include <sys/time.h>
#include <algorithm>

#include "binomial_heap.hpp"
#include "fibonacci_heap.hpp"

typedef long E;

int main( ) 
{

  std::ofstream push_bench_binomial;
  std::ofstream pop_bench_binomial;
  std::ofstream emplace_bench_binomial;
  std::ofstream erase_bench_binomial;

  std::ofstream push_bench_fib;
  std::ofstream pop_bench_fib;
  std::ofstream emplace_bench_fib;
  std::ofstream erase_bench_fib;

  push_bench_binomial.open("./bench/data/binomial_push.dat");
  pop_bench_binomial.open("./bench/data/binomial_pop.dat");
  emplace_bench_binomial.open("./bench/data/binomial_emplace.dat");
  erase_bench_binomial.open("./bench/data/binomial_erase.dat");

  push_bench_fib.open("./bench/data/fibonacci_push.dat");
  pop_bench_fib.open("./bench/data/fibonacci_pop.dat");
  emplace_bench_fib.open("./bench/data/fibonacci_emplace.dat");
  erase_bench_fib.open("./bench/data/fibonacci_erase.dat");

  boost::heap::binomial_heap<E>  pq_b;
  boost::heap::fibonacci_heap<E> pq_f;
  
  double reps = 3;
  E max_elements = pow(10, 7);
  double sum;
  double mean;
  double sd;
  
  std::vector<E>   data;
  std::vector<double> push_vec;
  std::vector<double> emplace_vec;
  std::vector<double> pop_vec;
  std::vector<double> erase_vec;
  
  clock_t cpu0;
  clock_t cpu1;
  double cpu_timer;

  E j = 1000;
  while(j <= max_elements ) {   
    //std::cout << "Elements: " << j << std::endl;

    E elements = j;
  
    std::vector<E> data;
    for (E i = elements; i >= 1; --i) data.push_back( i );
    std::random_shuffle ( data.begin( ), data.end( ) );

    for( int k = 0; k < reps; k++ ) {
      cpu0  = clock( );
      for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
        pq_b.push( *it );
      }
      cpu1  = clock();
      cpu_timer = static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);
      emplace_vec.push_back( (cpu_timer * 1000000.0) );
       
      cpu0  = clock( );
      for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
        pq_b.pop( );
      }
      cpu1  = clock();
      cpu_timer = static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);
      pop_vec.push_back( (cpu_timer * 1000000.0) );
    }

    // stats
    sum = std::accumulate( std::begin(emplace_vec), std::end(emplace_vec), 0.0);
    mean = sum / static_cast<double>(emplace_vec.size( ));
    emplace_bench_binomial << elements << "          " << mean << std::endl;
    emplace_vec.clear( );
 
    sum = std::accumulate( std::begin(pop_vec), std::end(pop_vec), 0.0);
    mean = sum / static_cast<double>(pop_vec.size( ));
    pop_bench_binomial << elements << "          " << mean << std::endl;
    pop_vec.clear( );
 
    for( int k = 0; k < reps; k++ ) {
      cpu0  = clock( );
      for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
        pq_f.push( *it );
      }
      cpu1  = clock();
      cpu_timer = (static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC);
      emplace_vec.push_back( cpu_timer * 1000000.0 );

      cpu0  = clock( );
      for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
        pq_f.pop( );
      }
      cpu1  = clock();
      cpu_timer = (static_cast<double>( cpu1 - cpu0 )  / CLOCKS_PER_SEC);
      pop_vec.push_back( cpu_timer * 1000000.0 );
    }

    // stats
    sum = std::accumulate( std::begin(emplace_vec), std::end(emplace_vec), 0.0);
    mean = sum / static_cast<double>(emplace_vec.size( ));
    emplace_bench_fib << elements << "          " << mean << std::endl;
    emplace_vec.clear( );
 
    sum = std::accumulate( std::begin(pop_vec), std::end(pop_vec), 0.0);
    mean = sum / static_cast<double>(pop_vec.size( ));
    pop_bench_fib << elements << "          " << mean << std::endl;
    pop_vec.clear( );


    data.clear();
    j += j / 20;
  }
  push_bench_binomial.close();
  pop_bench_binomial.close();
  emplace_bench_binomial.close();
  erase_bench_binomial.close();

  push_bench_fib.close();
  pop_bench_fib.close();
  emplace_bench_fib.close();
  erase_bench_fib.close();

  return 0;
}
