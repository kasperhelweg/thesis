#ifndef THESIS_BENCH
#define THESIS_BENCH
#include <math.h>
#include <string>

#include <iostream>
#include <fstream>
#include <assert.h>
#include <time.h>
#include <ctime>
#include <sys/time.h>
#include <algorithm>

namespace KHJ  {
  namespace thesis  {
    namespace benchmark  {
      template <typename N, typename E, typename Q>
      class bench {     
      public:
        typedef N node_type;
        typedef E element_type;
        typedef Q queue_type;
        
        //constexpr static comparator_type compare_ = C( );
        
        bench( long long & c, std::string f  ) : compares(c), filename(f) {} 
        

        long long & compares;
        std::string filename;
        std::string path = "./bench/data/";
        std::ofstream bench_plots;
        std::vector<long long> bench_vec;
        std::vector<long long> comp_vec;

        clock_t cpu0;
        clock_t cpu1;
        double  cpu_timer;
  
        std::vector<E>  data;
        std::vector<N*> nodes;
        
        E max_elements = pow(10, 5);
        E     elements_ = 1000;
        
        double reps    = 3;
        double sum     = 0;
        double mean    = 0;
        double sd      = 0;

        void push( queue_type& q )
        { 
          std::string post_ = "_push.dat";
          
          bench_plots.open(path + filename + post_);
          bench_plots << "#n        " << "#time_in_micro        " << "#compares" << std::endl;
          bench_plots << std::endl;

          E elements = elements_;
          while( elements <= max_elements ) {
            for (E i = elements; i >= 1; --i) data.push_back( i );
            std::random_shuffle ( data.begin( ), data.end( ) );
     
            for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
              N* n = new N( *it );
              nodes.push_back( n );
            }
            
            for( int k = 0; k < reps; k++ ) {
              compares = 0;
              cpu0  = clock( );
              for( auto it = nodes.begin( ) ; it != nodes.end( ) ; it++ ) {
                q.push( *it );
              }
              cpu1  = clock( );
              cpu_timer = static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);
              bench_vec.push_back( cpu_timer * 1000000.0 );
              comp_vec.push_back( compares / elements );
              
              for( auto it = nodes.begin( ) ; it != nodes.end( ) ; it++ ) {
                q.extract( );
              }
            }
            nodes.clear( );

            sum  = std::accumulate( std::begin(bench_vec), std::end(bench_vec), 0.0);
            mean = sum / static_cast<double>(bench_vec.size( ));
            bench_plots << elements << "        " << mean << "        ";
            bench_vec.clear( );
    
            sum  = std::accumulate( std::begin(comp_vec), std::end(comp_vec), 0.0);
            mean = sum / static_cast<double>(comp_vec.size( ));
            bench_plots << mean << std::endl;
            comp_vec.clear( );
    
            data.clear( );
            elements += elements / 20;
          }
          bench_plots.close();
        }

        void pop( queue_type& q )
        { 
          std::string post_ = "_pop.dat";
          
          bench_plots.open(path + filename + post_);
          bench_plots << "#n        " << "#time_in_micro        " << "#compares" << std::endl;
          bench_plots << std::endl;

          E elements = elements_;
          while( elements <= max_elements ) {
            for (E i = elements; i >= 1; --i) data.push_back( i );
            std::random_shuffle ( data.begin( ), data.end( ) );
            for( int k = 0; k < reps; k++ ) {      
              for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
                q.emplace( *it );
              }
              compares = 0;
              cpu0  = clock( );
              for( int i = 1; i <= elements; ++i ) {
                q.pop( );
              }
              cpu1  = clock( );
              cpu_timer = static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);
              bench_vec.push_back( cpu_timer * 1000000.0 );
              comp_vec.push_back( compares / elements );

            }

            sum  = std::accumulate( std::begin(bench_vec), std::end(bench_vec), 0.0);
            mean = sum / static_cast<double>(bench_vec.size( ));
            bench_plots << elements << "        " << mean << "        ";
            bench_vec.clear( );
    
            sum  = std::accumulate( std::begin(comp_vec), std::end(comp_vec), 0.0);
            mean = sum / static_cast<double>(comp_vec.size( ));
            bench_plots << mean << std::endl;
            comp_vec.clear( );
    
            data.clear( );
            elements += elements / 20;
          }
          bench_plots.close();
        }

        void emplace( queue_type& q )
        {        
          std::string post_ = "_emplace.dat";
          
          bench_plots.open(path + filename + post_);
          bench_plots << "#n        " << "#time_in_micro        " << "#compares" << std::endl;
          bench_plots << std::endl;
          
          E elements = elements_;
          while( elements <= max_elements ) {
            for (E i = elements; i >= 1; --i) data.push_back( i );
            std::random_shuffle ( data.begin( ), data.end( ) );
            for( int k = 0; k < reps; k++ ) {      
              compares = 0;
              cpu0  = clock( );
              for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
                q.emplace( *it );
              }
              cpu1  = clock( );
              cpu_timer = static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);
              bench_vec.push_back( cpu_timer * 1000000.0 );
              comp_vec.push_back( compares / elements );

              for( int i = 1; i <= elements; ++i ) {
                q.pop( );
              }
            }

            sum  = std::accumulate( std::begin(bench_vec), std::end(bench_vec), 0.0);
            mean = sum / static_cast<double>(bench_vec.size( ));
            bench_plots << elements << "        " << mean << "        ";
            bench_vec.clear( );
    
            sum  = std::accumulate( std::begin(comp_vec), std::end(comp_vec), 0.0);
            mean = sum / static_cast<double>(comp_vec.size( ));
            bench_plots << mean << std::endl;
            comp_vec.clear( );
    
            data.clear( );
            elements += elements / 20;
          }
          bench_plots.close();
        }

        void erase( queue_type& q )
        { 
          std::string post_ = "_erase.dat";
          
          bench_plots.open(path + filename + post_);
          bench_plots << "#n        " << "#time_in_micro        " << "#compares" << std::endl;
          bench_plots << std::endl;

          E elements = elements_;
          while( elements <= max_elements ) {
            for (E i = elements; i >= 1; --i) data.push_back( i );
            std::random_shuffle ( data.begin( ), data.end( ) );
            
            for( int k = 0; k < reps; k++ ) {      
              for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
                nodes.push_back( q.emplace( *it ) );
              } std::random_shuffle ( nodes.begin( ), nodes.end( ) );
            
              compares = 0;
              cpu0  = clock( );
              for( auto it = nodes.begin( ) ; it != nodes.end( ) ; it++ ) {
                q.erase( *it );
              }
              cpu1  = clock( );
              cpu_timer = static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);
              bench_vec.push_back( cpu_timer * 1000000.0 );
              comp_vec.push_back( compares / elements );
              
              nodes.clear();
            }

            sum  = std::accumulate( std::begin(bench_vec), std::end(bench_vec), 0.0);
            mean = sum / static_cast<double>(bench_vec.size( ));
            bench_plots << elements << "        " << mean << "        ";
            bench_vec.clear( );
    
            sum  = std::accumulate( std::begin(comp_vec), std::end(comp_vec), 0.0);
            mean = sum / static_cast<double>(comp_vec.size( ));
            bench_plots << mean << std::endl;
            comp_vec.clear( );
    
            data.clear( );
            elements += elements / 20;
          }
          bench_plots.close();
        }
      };
    }
  }
}
#endif
