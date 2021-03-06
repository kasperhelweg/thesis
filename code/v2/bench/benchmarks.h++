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
        std::ofstream bench_plots_med;
        std::vector<long long> bench_vec;
        std::vector<long long> comp_vec;

        clock_t cpu0;
        clock_t cpu1;
        double  cpu_timer;
  
        std::vector<E>  data;
        std::vector<N*> nodes;
        std::vector<N> nodes_boost;
        
        E max_elements = pow(10, 6);
        E     elements_ = 1000;
        
        double reps    = 5;
        double splits  = 10;
        double sum     = 0;
        double mean    = 0;
        double sd      = 0;
        
        void push( queue_type& q )
        { 
          std::string post_ = "_push.dat";
          std::cout << "PUSH" << std::endl;
          bench_plots.open(path + filename + post_);
          bench_plots_med.open(path + filename + "_med" + post_ );
          bench_plots << "#n        " << "#time_in_micro        " << "#compares" << std::endl;
          bench_plots << std::endl;
          bench_plots_med << "#n        " << "#time_in_micro        "<< std::endl;
          bench_plots_med << std::endl;

          
          E elements = elements_;
          while( elements <= max_elements ) {
            for (E i = elements; i >= 1; --i) data.push_back( i );
            //std::random_shuffle ( data.begin( ), data.end( ) );
     
            for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
              N* n = new N( *it );
              nodes.push_back( n );
            }
            
            for( int k = 0; k < reps; k++ ) {
              std::random_shuffle ( nodes.begin( ), nodes.end( ) );
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
            for( auto it = nodes.begin( ) ; it != nodes.end( ) ; it++ ) {
              delete *it;
            } 
            nodes.clear( );

            std::sort( bench_vec.begin(), bench_vec.end() );
            sum  = std::accumulate( std::begin(bench_vec), std::end(bench_vec), 0.0);
            mean = sum / static_cast<double>(bench_vec.size( ));
            bench_plots << elements << "        " << mean << "        ";
            bench_plots_med << elements << "        " << bench_vec[floor(reps/2)] << std::endl;
            bench_vec.clear( );
    
            sum  = std::accumulate( std::begin(comp_vec), std::end(comp_vec), 0.0);
            mean = sum / static_cast<double>(comp_vec.size( ));
            bench_plots << mean << std::endl;
            comp_vec.clear( );
    
            data.clear( );
            elements += elements / splits;
          }
          bench_plots.close( );
          bench_plots_med.close( );
        }

        void pop( queue_type& q )
        { 
          std::string post_ = "_pop.dat";
          std::cout << "POP" << std::endl;
          bench_plots.open(path + filename + post_);
          bench_plots_med.open(path + filename + "_med" + post_ );
          bench_plots << "#n        " << "#time_in_micro        " << "#compares" << std::endl;
          bench_plots << std::endl;
          bench_plots_med << "#n        " << "#time_in_micro        "<< std::endl;
          bench_plots_med << std::endl;
       
          E elements = elements_;
          while( elements <= max_elements ) {
            for (E i = elements; i >= 1; --i) data.push_back( i );
            
            for( int k = 0; k < reps; k++ ) {      
              std::random_shuffle ( data.begin( ), data.end( ) );
              for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
                q.push( *it );
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

            std::sort( bench_vec.begin(), bench_vec.end() );
            sum  = std::accumulate( std::begin(bench_vec), std::end(bench_vec), 0.0);
            mean = sum / static_cast<double>(bench_vec.size( ));
            bench_plots << elements << "        " << mean << "        ";
            bench_plots_med << elements << "        " << bench_vec[floor(reps/2)] << std::endl;
            bench_vec.clear( );
    
            sum  = std::accumulate( std::begin(comp_vec), std::end(comp_vec), 0.0);
            mean = sum / static_cast<double>(comp_vec.size( ));
            bench_plots << mean << std::endl;
            comp_vec.clear( );
    
            data.clear( );
            elements += elements / splits;
          }
          bench_plots.close();
          bench_plots_med.close();
        }

        void emplace( queue_type& q )
        {        
          std::string post_ = "_emplace.dat";
          std::cout << "EMPLACE" << std::endl;

          bench_plots.open(path + filename + post_);
          bench_plots_med.open(path + filename + "_med" + post_ );
          bench_plots << "#n        " << "#time_in_micro        " << "#compares" << std::endl;
          bench_plots << std::endl;
          bench_plots_med << "#n        " << "#time_in_micro        "<< std::endl;
          bench_plots_med << std::endl;
          
          E elements = elements_;
          while( elements <= max_elements ) {
            for (E i = elements; i >= 1; --i) data.push_back( i );
            for( int k = 0; k < reps; k++ ) {      
              std::random_shuffle ( data.begin( ), data.end( ) );
              compares = 0;
              cpu0  = clock( );
              for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
                q.push( *it );
              }
              cpu1  = clock( );
              cpu_timer = static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);
              bench_vec.push_back( cpu_timer * 1000000.0 );
              comp_vec.push_back( compares / elements );

              q.clear();
          
            }

            std::sort( bench_vec.begin(), bench_vec.end() );
            sum  = std::accumulate( std::begin(bench_vec), std::end(bench_vec), 0.0);
            mean = sum / static_cast<double>(bench_vec.size( ));
            bench_plots << elements << "        " << mean << "        ";
            bench_plots_med << elements << "        " << bench_vec[floor(reps/2)] << std::endl;
            bench_vec.clear( );
    
            sum  = std::accumulate( std::begin(comp_vec), std::end(comp_vec), 0.0);
            mean = sum / static_cast<double>(comp_vec.size( ));
            bench_plots << mean << std::endl;
            comp_vec.clear( );
    
            data.clear( );
            elements += elements / splits;
          }
          bench_plots.close();
          bench_plots_med.close();
        }

        void erase( queue_type& q )
        { 
          std::string post_ = "_erase.dat";
          
          std::cout << "ERASE" << std::endl;         
          bench_plots.open(path + filename + post_);
          bench_plots_med.open(path + filename + "_med" + post_ );
          bench_plots << "#n        " << "#time_in_micro        " << "#compares" << std::endl;
          bench_plots << std::endl;
          bench_plots_med << "#n        " << "#time_in_micro        "<< std::endl;
          bench_plots_med << std::endl;

          E elements = elements_;
          while( elements <= max_elements ) {
            for (E i = elements; i >= 1; --i) data.push_back( i );
            for( int k = 0; k < reps; k++ ) {      
              std::random_shuffle ( data.begin( ), data.end( ) );
              for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
                nodes.push_back( q.push( *it ) );
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

            std::sort( bench_vec.begin(), bench_vec.end() );
            sum  = std::accumulate( std::begin(bench_vec), std::end(bench_vec), 0.0);
            mean = sum / static_cast<double>(bench_vec.size( ));
            bench_plots << elements << "        " << mean << "        ";
            bench_plots_med << elements << "        " << bench_vec[floor(reps/2)] << std::endl;
            bench_vec.clear( );
    
            sum  = std::accumulate( std::begin(comp_vec), std::end(comp_vec), 0.0);
            mean = sum / static_cast<double>(comp_vec.size( ));
            bench_plots << mean << std::endl;
            comp_vec.clear( );
    
            data.clear( );
            elements += elements / splits;
          }
          bench_plots.close();
          bench_plots_med.close();
        }

        void erase_boost( queue_type& q )
        { 
          std::string post_ = "_erase.dat";
          
          std::cout << "ERASE" << std::endl;         
          bench_plots.open(path + filename + post_);
          bench_plots_med.open(path + filename + "_med" + post_ );
          bench_plots << "#n        " << "#time_in_micro        " << "#compares" << std::endl;
          bench_plots << std::endl;
          bench_plots_med << "#n        " << "#time_in_micro        "<< std::endl;
          bench_plots_med << std::endl;

          E elements = elements_;
          while( elements <= max_elements ) {
            for (E i = elements; i >= 1; --i) data.push_back( i );
            for( int k = 0; k < reps; k++ ) {      
              std::random_shuffle ( data.begin( ), data.end( ) );
              for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
                nodes_boost.push_back( q.push( *it ) );
              } std::random_shuffle ( nodes_boost.begin( ), nodes_boost.end( ) );
            
              compares = 0;
              cpu0  = clock( );
              for( auto it = nodes_boost.begin( ) ; it != nodes_boost.end( ) ; it++ ) {
                q.erase( *it );
              }
              cpu1  = clock( );
              cpu_timer = static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);
              bench_vec.push_back( cpu_timer * 1000000.0 );
              comp_vec.push_back( compares / elements );
              
              nodes_boost.clear();
            }

            std::sort( bench_vec.begin(), bench_vec.end() );
            sum  = std::accumulate( std::begin(bench_vec), std::end(bench_vec), 0.0);
            mean = sum / static_cast<double>(bench_vec.size( ));
            bench_plots << elements << "        " << mean << "        ";
            bench_plots_med << elements << "        " << bench_vec[floor(reps/2)] << std::endl;
            bench_vec.clear( );
    
            sum  = std::accumulate( std::begin(comp_vec), std::end(comp_vec), 0.0);
            mean = sum / static_cast<double>(comp_vec.size( ));
            bench_plots << mean << std::endl;
            comp_vec.clear( );
    
            data.clear( );
            elements += elements / splits;
          }
          bench_plots.close();
          bench_plots_med.close();
        }

        void decrease_key( queue_type& q  )
        { 
          std::string post_ = "_decrease.dat";
          
          std::cout << "DECREASE" << std::endl;         
          bench_plots.open(path + filename + post_);
          bench_plots_med.open(path + filename + "_med" + post_ );
          bench_plots << "#n        " << "#time_in_micro        " << "#compares" << std::endl;
          bench_plots << std::endl;
          bench_plots_med << "#n        " << "#time_in_micro        "<< std::endl;
          bench_plots_med << std::endl;

          E elements = elements_;
          std::vector<E> keys;
          while( elements <= max_elements ) {         
            for (E i = elements; i <= 2 * elements; i++) { 
              data.push_back( i );
              keys.push_back( i - elements );
            }
            std::reverse(keys.begin(),keys.end());
            
            
            for( int k = 0; k < reps; k++ ) {      
               std::random_shuffle ( data.begin( ), data.end( ) );
              for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
                nodes.push_back( q.push( *it ) );
              } std::random_shuffle ( nodes.begin( ), nodes.end( ) );
       
              compares = 0;
              cpu0  = clock( );
              for( auto it = keys.begin( ) ; it != keys.end( ) ; it++ ) {   
                q.decrease( nodes[*it], *it );       
              }

              cpu1  = clock( );
              cpu_timer = static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);
              bench_vec.push_back( cpu_timer * 1000000.0 );
              comp_vec.push_back( compares / elements );
                      
              q.clear( );     
              nodes.clear();
            }
          
            std::sort( bench_vec.begin(), bench_vec.end() );
            sum  = std::accumulate( std::begin(bench_vec), std::end(bench_vec), 0.0);
            mean = sum / static_cast<double>(bench_vec.size( ));
            bench_plots << elements << "        " << mean << "        ";
            bench_plots_med << elements << "        " << bench_vec[floor(reps/2)] << std::endl;
            bench_vec.clear( );
    
            sum  = std::accumulate( std::begin(comp_vec), std::end(comp_vec), 0.0);
            mean = sum / static_cast<double>(comp_vec.size( ));
            bench_plots << mean << std::endl;
            comp_vec.clear( );
    
            data.clear( );
            keys.clear( );
            q.clear( );
            nodes.clear( );
            elements += elements / splits;
           
          }
          bench_plots.close();
          bench_plots_med.close();
          
        }

        void decrease_key_boost( queue_type& q  )
        { 
          std::string post_ = "_decrease.dat";
          
          std::cout << "DECREASE" << std::endl;         
          bench_plots.open(path + filename + post_);
          bench_plots_med.open(path + filename + "_med" + post_ );
          bench_plots << "#n        " << "#time_in_micro        " << "#compares" << std::endl;
          bench_plots << std::endl;
          bench_plots_med << "#n        " << "#time_in_micro        "<< std::endl;
          bench_plots_med << std::endl;

          E elements = elements_;
          std::vector<E> keys;
          while( elements <= max_elements ) {         
            for (E i = elements; i <= 2 * elements; i++) { 
              data.push_back( i );
              keys.push_back( i - elements );
            }
            std::reverse(keys.begin(),keys.end());
            
            
            for( int k = 0; k < reps; k++ ) {      
              std::random_shuffle ( data.begin( ), data.end( ) );
              for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
                nodes_boost.push_back( q.push( *it ) );
              } std::random_shuffle ( nodes_boost.begin( ), nodes_boost.end( ) );
       
              compares = 0;
              cpu0  = clock( );
              for( auto it = keys.begin( ) ; it != keys.end( ) ; it++ ) {   
                q.decrease( nodes_boost[*it], *it );       
              }

              cpu1  = clock( );
              cpu_timer = static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);
              bench_vec.push_back( cpu_timer * 1000000.0 );
              comp_vec.push_back( compares / elements );
                      
              q.clear( );     
              nodes_boost.clear();
            }

            std::sort( bench_vec.begin(), bench_vec.end() );
            sum  = std::accumulate( std::begin(bench_vec), std::end(bench_vec), 0.0);
            mean = sum / static_cast<double>(bench_vec.size( ));
            bench_plots << elements << "        " << mean << "        ";
            bench_plots_med << elements << "        " << bench_vec[floor(reps/2)] << std::endl;
            bench_vec.clear( );
    
            sum  = std::accumulate( std::begin(comp_vec), std::end(comp_vec), 0.0);
            mean = sum / static_cast<double>(comp_vec.size( ));
            bench_plots << mean << std::endl;
            comp_vec.clear( );
    
            data.clear( );
            keys.clear( );
            q.clear( );
            nodes_boost.clear( );
            elements += elements / splits;
           
          }
          bench_plots.close();
          bench_plots_med.close();
          
        }

        void seq_a( queue_type& q )
        { 
          std::string post_ = "_seq_a.dat";
          std::cout << "SEQUENCE A" << std::endl;
          bench_plots.open(path + filename + post_);
          bench_plots_med.open(path + filename + "_med" + post_ );
          bench_plots << "#n        " << "#time_in_micro        " << "#compares" << std::endl;
          bench_plots << std::endl;
          bench_plots_med << "#n        " << "#time_in_micro        "<< std::endl;
          bench_plots_med << std::endl;
         
          E elements = elements_;
          std::vector<E> keys;
          while( elements <= max_elements ) {         
            for (E i = elements; i <= 2 * elements; i++) { 
              data.push_back( i );
              keys.push_back( i - elements );
            }
            std::random_shuffle( keys.begin( ), keys.end( ) );

            for( int k = 0; k < reps; k++ ) {      
              std::random_shuffle ( data.begin( ), data.end( ) );
              cpu_timer = 0;
              compares = 0;

              // maybe change to node type push?
              cpu0  = clock( );
              for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
                nodes.push_back( q.push( *it ) );
              } 
              cpu1  = clock( );
              cpu_timer += static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);

              std::random_shuffle ( nodes.begin( ), nodes.end( ) );

              cpu0  = clock( );
              for( auto it = keys.begin( ) ; it != keys.end( ) ; it++ ) {   
                q.decrease( nodes[*it], *it );       
              }
              cpu1  = clock( );
              cpu_timer += static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);

              
              auto middle = nodes.begin( ) + (int)(nodes.size( ) / 2);
              
              cpu0  = clock( );
              for( auto it = nodes.begin( ) ; it != middle ; it++ ) {
                q.erase( *it );
              }
              while( !q.empty( ) ) {
                q.pop( );
              }
              cpu1  = clock( );
              cpu_timer += static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);
            
              bench_vec.push_back( cpu_timer * 1000000.0 );
              comp_vec.push_back( compares / elements );

              q.clear( );
              nodes.clear( );
            }
            
            std::sort( bench_vec.begin(), bench_vec.end() );
            sum  = std::accumulate( std::begin(bench_vec), std::end(bench_vec), 0.0);
            mean = sum / static_cast<double>(bench_vec.size( ));
            bench_plots << elements << "        " << mean << "        ";
            bench_plots_med << elements << "        " << bench_vec[floor(reps/2)] << std::endl;
            bench_vec.clear( );
    
            sum  = std::accumulate( std::begin(comp_vec), std::end(comp_vec), 0.0);
            mean = sum / static_cast<double>(comp_vec.size( ));
            bench_plots << mean << std::endl;
            comp_vec.clear( );
            
            data.clear( );
            keys.clear( );
            q.clear( );
            nodes.clear( );
            elements += elements / splits;
          
          }
          bench_plots.close();
          bench_plots_med.close();
        }

        void seq_a_boost( queue_type& q )
        { 
          std::string post_ = "_seq_a.dat";
          std::cout << "SEQUENCE A" << std::endl;
          bench_plots.open(path + filename + post_);
          bench_plots_med.open(path + filename + "_med" + post_ );
          bench_plots << "#n        " << "#time_in_micro        " << "#compares" << std::endl;
          bench_plots << std::endl;
          bench_plots_med << "#n        " << "#time_in_micro        "<< std::endl;
          bench_plots_med << std::endl;
         
          E elements = elements_;
          std::vector<E> keys;
          while( elements <= max_elements ) {         
            for (E i = elements; i <= 2 * elements; i++) { 
              data.push_back( i );
              keys.push_back( i - elements );
            }
            std::random_shuffle( keys.begin( ), keys.end( ) );

            for( int k = 0; k < reps; k++ ) {      
              std::random_shuffle ( data.begin( ), data.end( ) );
              cpu_timer = 0;
              compares = 0;

              // maybe change to node type push?
              cpu0  = clock( );
              for( auto it = data.begin( ) ; it != data.end( ) ; it++ ) {
                nodes_boost.push_back( q.push( *it ) );
              } 
              cpu1  = clock( );
              cpu_timer += static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);

              std::random_shuffle ( nodes_boost.begin( ), nodes_boost.end( ) );

              cpu0  = clock( );
              for( auto it = keys.begin( ) ; it != keys.end( ) ; it++ ) {   
                q.decrease( nodes_boost[*it], *it );       
              }
              cpu1  = clock( );
              cpu_timer += static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);

              
              auto middle = nodes_boost.begin( ) + (int)(nodes_boost.size( ) / 2);
              
              cpu0  = clock( );
              for( auto it = nodes_boost.begin( ) ; it != middle ; it++ ) {
                q.erase( *it );
              }
              while( !q.empty( ) ) {
                q.pop( );
              }
              cpu1  = clock( );
              cpu_timer += static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);
            
              bench_vec.push_back( cpu_timer * 1000000.0 );
              comp_vec.push_back( compares / elements );

              q.clear( );
              nodes_boost.clear( );
            }
            
            std::sort( bench_vec.begin(), bench_vec.end() );
            sum  = std::accumulate( std::begin(bench_vec), std::end(bench_vec), 0.0);
            mean = sum / static_cast<double>(bench_vec.size( ));
            bench_plots << elements << "        " << mean << "        ";
            bench_plots_med << elements << "        " << bench_vec[floor(reps/2)] << std::endl;
            bench_vec.clear( );
    
            sum  = std::accumulate( std::begin(comp_vec), std::end(comp_vec), 0.0);
            mean = sum / static_cast<double>(comp_vec.size( ));
            bench_plots << mean << std::endl;
            comp_vec.clear( );
            
            data.clear( );
            keys.clear( );
            q.clear( );
            nodes_boost.clear( );
            elements += elements / splits;
          
          }
          bench_plots.close();
          bench_plots_med.close();
        }

        void seq_b( queue_type& q, queue_type& q1 )
        { 
          std::string post_ = "_seq_b.dat";
          std::cout << "SEQUENCE B" << std::endl;
          bench_plots.open(path + filename + post_);
          bench_plots_med.open(path + filename + "_med" + post_ );
          bench_plots << "#n        " << "#time_in_micro        " << "#compares" << std::endl;
          bench_plots << std::endl;
          bench_plots_med << "#n        " << "#time_in_micro        "<< std::endl;
          bench_plots_med << std::endl;
         
          E elements = elements_;
          std::vector<E>  keys;
          std::vector<E>  data;
          std::vector<N*> nodes;

          while( elements <= max_elements ) {
            E m    = floor( (elements/2));
            for (E i = (elements+m); i <= 2 * (elements+m); i++) { 
              data.push_back( i );
            }
            
            auto n = data.begin( ) + (int)elements;
            for( int k = 0; k < reps; k++ ) {      
              std::random_shuffle ( data.begin( ), data.end( ) );          
              for( auto it = data.begin( ) ; it != n; it++ ) {
                nodes.push_back( q.push( *it ) );
              } 
              for( auto it = n ; it != data.end( ); it++ ) {
                nodes.push_back( q1.push( *it ) );
              }
              
              E j = 0;
              for( auto it = nodes.begin() ; it != nodes.end( )-1; it++ ) {
                keys.push_back( j ); j++;
              }
              std::reverse(keys.begin(),keys.end());
              std::random_shuffle ( nodes.begin( ), nodes.end( ) );
              
              cpu_timer = 0;
              compares = 0;
              cpu0  = clock( );
              q.meld( q1 );
              q.erase(nodes.back()); nodes.pop_back(); 
           
              auto p = nodes.begin( ) + (int)m;
              for( auto it = keys.begin( ) ; it != keys.end( ) ; it++ )
                q.decrease( nodes[(*it)], *it );       
              for( auto it = nodes.begin() ; it != p; it++ )
                q.erase( *it  );
           
              while( !q.empty() ) 
                q.extract( );
             
              cpu1  = clock( );
              cpu_timer += static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);
              bench_vec.push_back( cpu_timer * 1000000.0 );
              comp_vec.push_back( compares / elements );
                      
              q.clear( );
              q1.clear( );
              nodes.clear( );
              keys.clear( );
            }

            std::sort( bench_vec.begin(), bench_vec.end() );
            sum  = std::accumulate( std::begin(bench_vec), std::end(bench_vec), 0.0);
            mean = sum / static_cast<double>(bench_vec.size( ));
            bench_plots << elements << "        " << mean << "        ";
            bench_plots_med << elements << "        " << bench_vec[floor(reps/2)] << std::endl;
            bench_vec.clear( );
    
            sum  = std::accumulate( std::begin(comp_vec), std::end(comp_vec), 0.0);
            mean = sum / static_cast<double>(comp_vec.size( ));
            bench_plots << mean << std::endl;
            comp_vec.clear( );
          
            q.clear( );
            q1.clear( );
            data.clear( );
            keys.clear( );
            nodes.clear( );
            elements += elements / splits;
          }
          bench_plots.close();
          bench_plots_med.close();
        }

        void seq_b_boost( queue_type& q, queue_type& q1 )
        { 
          std::string post_ = "_seq_b.dat";
          std::cout << "SEQUENCE B" << std::endl;
          bench_plots.open(path + filename + post_);
          bench_plots_med.open(path + filename + "_med" + post_ );
          bench_plots << "#n        " << "#time_in_micro        " << "#compares" << std::endl;
          bench_plots << std::endl;
          bench_plots_med << "#n        " << "#time_in_micro        "<< std::endl;
          bench_plots_med << std::endl;
         
          E elements = elements_;
          std::vector<E>  keys;
          std::vector<E>  data;
          std::vector<N> nodes;

          while( elements <= max_elements ) {
            E m    = floor( (elements/2));
            for (E i = (elements+m); i <= 2 * (elements+m); i++) { 
              data.push_back( i );
            }
            
            auto n = data.begin( ) + (int)elements;
            for( int k = 0; k < reps; k++ ) {      
              std::random_shuffle ( data.begin( ), data.end( ) );          
              for( auto it = data.begin( ) ; it != n; it++ ) {
                nodes.push_back( q.push( *it ) );
              } 
              for( auto it = n ; it != data.end( ); it++ ) {
                nodes.push_back( q1.push( *it ) );
              }
              
              E j = 0;
              for( auto it = nodes.begin() ; it != nodes.end( )-1; it++ ) {
                keys.push_back( j ); j++;
              }
              std::reverse(keys.begin(),keys.end());
              std::random_shuffle ( nodes.begin( ), nodes.end( ) );
          
              cpu_timer = 0;
              compares = 0;
              cpu0  = clock( );
              q.merge( q1 );
              q.erase(nodes.back()); nodes.pop_back(); //keys.pop_back();
              auto p = nodes.begin( ) + (int)m;
              for( auto it = keys.begin( ) ; it != keys.end( ) ; it++ )
                q.decrease( nodes[(*it)], *it );       
              for( auto it = nodes.begin() ; it != p; it++ )
                q.erase( *it  );
              while( !q.empty() ) 
                q.pop( );
              cpu1  = clock( );
              cpu_timer += static_cast<double>( cpu1 - cpu0 )  / double(CLOCKS_PER_SEC);
              bench_vec.push_back( cpu_timer * 1000000.0 );
              comp_vec.push_back( compares / elements );

              q.clear();
              q1.clear();
              nodes.clear( );
              keys.clear( );
            }

            std::sort( bench_vec.begin(), bench_vec.end() );
            sum  = std::accumulate( std::begin(bench_vec), std::end(bench_vec), 0.0);
            mean = sum / static_cast<double>(bench_vec.size( ));
            bench_plots << elements << "        " << mean << "        ";
            bench_plots_med << elements << "        " << bench_vec[floor(reps/2)] << std::endl;
            bench_vec.clear( );
    
            sum  = std::accumulate( std::begin(comp_vec), std::end(comp_vec), 0.0);
            mean = sum / static_cast<double>(comp_vec.size( ));
            bench_plots << mean << std::endl;
            comp_vec.clear( );
            
            q.clear( );
            q1.clear( );
            data.clear( );
            keys.clear( );
            nodes.clear( );
            elements += elements / splits;
          }
          bench_plots.close();
          bench_plots_med.close();
        }


      };
    }
  }
}
#endif
