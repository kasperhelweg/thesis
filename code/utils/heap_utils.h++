#include "heap_a_node.h++"
#include "heap_b_node.h++"
#include <stdlib.h>
#include <math.h>
#include <deque>
#include <string>
#include <sstream>
#include <algorithm>

#ifndef THESIS_HEAP_UTILS
#define THESIS_HEAP_UTILS
namespace KHJ {
  namespace thesis {
    namespace utils {
      
      template<typename N, typename V>
      class pfb {
        typedef N node_type; 
        
      public:
        static std::deque<N*> heap;
        
        static void breadth_first_draw( )
        {
          static std::string def_color  = "\033[0m";
          static std::string color      = "\033[36m";
          static std::string null_color = "\033[34m";
          
          std::deque<N*> heap = breadth_traverse( );

          int h = 0;
          int l = floor( log2( heap.size( ) - 1 ) );
          int off = l * 10;

          for (auto n = heap.begin( ); n != heap.end( );) {
            for( int i = 0; i != pow( 2, h ); i++ ) {
              
              //std::stringstream ss; ss << (*n);
              //std::string adr = ss.str( );
              
              std::cout << (*n)->element_ << " "; 
              
              //if( (*n)->is_root( ) ) { 
              //  for( int j = 0; j != off; j++ ) { std::cout << " "; }
              //  std::cout << (*n)->element_ << " @ " << adr.substr( 5,9 ) << std::endl; 
              //}
              
              //for( int j = 0; j != l*off/2; j++ ) { std::cout << " "; }
              //for( int j = 0; j != i; j++ ) { std::cout << " "; }
              
              
              /*
                std::stringstream ssl; ssl << (*n)->left_;
                std::stringstream ssr; ssr << (*n)->right_;
                std::stringstream sp; 
              
              std::string le = ssl.str( );
              std::string ri = ssr.str( );
              
              for( int j = 0; j != pow(4,l); j++ ) { sp << " "; }
              sp << "+";
              for( int j = 0; j != pow(4,l); j++ ) { sp << " "; }
              std::string sps = sp.str( );



              if( (*n)->left_ != nullptr ) {
                std::cout << (*n)->element_ << " @ " << le.substr( 5,9 ) << sps;
              } else {
                std::cout << null_color + le + def_color << sps;
              }
              
              if( (*n)->right_ != nullptr ) {
                std::cout << color << (*n)->element_ << " @ " << ri.substr( 5,9 ) << def_color ;
              } else {
                std::cout << null_color + ri + def_color;
              }

              */
              n++;
            }
            std::cout << std::endl;
            h++;
            l--;
          }
        }
        
        static void assert_heap( bool assert_heap_prop = true )
        {
          N* R = heap.front( );
          std::deque<N*> bf = breadth_traverse( R );
          int l = floor( log2( bf.size( ) - 1 ) );
          int h = 0;

          for (auto n = bf.begin(); n != bf.end();) {
            for( int i = 0; i != pow(2,h); i++ ) {
              if( h != l) {
                if( h == 0 ){
                  assert((*n)->is_root());
                  assert((*n)->color_ == 0);
                }
                // assert heap prop here.
                if( assert_heap_prop ) {
                  assert((*n)->left_->element_ >= (*n)->element_ );
                  assert((*n)->left_->right_->element_ >= (*n)->element_ );
                }

                assert((*n)->left_->color_ == 0 );
                assert((*n)->left_->right_->color_ == 1 );

                
              } else {
                assert((*n)->is_leaf());
              }
              n++;
            }
            h++;
          }
        }


        static void assert_heap( N* R  )
        {
          std::deque<N*> bf = breadth_traverse( R );
          assert( bf.size( ) == (pow( 2, (*R).height( ) + 1 ) - 1) );
          //std::cout << bf.size( ) << std::endl;
          int l = floor( log2( bf.size( ) - 1 ) );
          int h = 0;
          
          for (auto n = bf.begin( ); n != bf.end( );) {
            for( int i = 0; i != pow(2,h); i++ ) {
              if( h != l) {
                if( h == 0 ){
                  assert((*n)->is_root());
                  assert((*n)->color_ == 0);
                } else {
                  // assert heap prop here.
                  assert((*n)->left_->element_ >= (*n)->element_ );
                  assert((*n)->left_->right_->element_ >= (*n)->element_ );
                  
                  assert((*n)->left_->color_ == 0 );
                  assert((*n)->left_->right_->color_ == 1 );
                }
              } else {
                assert((*n)->is_leaf());
              }
              n++;
            }
            h++;
          }
        }
   
        static N* build_and_inject( int h )
        {
          std::deque<N*> aux;
          
          // Construct root
          int nn = pow( 2, h + 1 ) - 1;
          int rv = rand( ) % (nn * 3) + 0;
          
          node_type* R = new node_type( rv );
          aux.push_front( R );
          
          for( int i = 0; i != h; i++ ) {
            for( int j = 0; j != pow(2,i); j++ ) {
              node_type* R = aux.front( );
              aux.pop_front( );
              
              // cons
              node_type* P = new node_type( (rand( ) % nn * pow(2,i) + 0) + 
                                            (rand( ) % nn + 0), 0 );
              node_type* Q = new node_type( (rand( ) % nn * pow(2,i) + 0) + 
                                            (rand( ) % nn + 0), 1 );
              
              (R)->join( P, Q );
       
              aux.push_back( P );
              aux.push_back( Q );
            }
          }
          aux.clear( );
          heap.push_front( R );
          
          // Restore heap property
          std::deque<N*> bh = breadth_traverse( heap.front() );
          for (auto n = bh.begin(); n != bh.end(); n++) {
            (*n)->siftup( );
          }
          heap.push_front( R->find_root() );
          return R;
        }

        static std::deque<N*> breadth_traverse( N* R )
        {
          std::deque<N*> aux;
          std::deque<N*> b;
          //N* R  = heap.front( );
          aux.push_back( R ); b.push_back( R );
            
          int l = (*R).height( );
          for( int i = 0; i != l; i++ ) {
            for( int j = 0; j != pow( 2, i ); j++ ) {
              N* T = aux.front( );
              N* P = (*T).left_;
              N* Q = (*(*T).left_).right_;
          
              aux.push_back( P ); b.push_back( P );
              aux.push_back( Q ); b.push_back( Q );
                
              aux.pop_front( );
            }
          }
          aux.clear( );
          return b;
        }

        // this should maybe return something usefull
        static N* replace_rand( )
        {
          std::deque<N*> bf = breadth_traverse( heap.front( ) );
        
          int r = rand( ) % bf.size( ) + 0;
          node_type* O = new node_type( r );
          N* P         = bf[r];          
                    
          node_type* node = (*P).replace( O );  
          heap.pop_front(); heap.push_front( O->find_root() );

          // if the replacement changes the root; switch out
          // if((*node).is_root( )) {  }
          delete P; P = nullptr;
          return O;
        }
    
        static void siftup( N* S )
        {          
          (*S).siftup( );
          if((*S).is_root( )) { heap.pop_front(); heap.push_front( S ); }
        }

        static void siftdown( N* S )
        {
          bool is_root = (*S).is_root( );
          (*S).siftdown( );
          if( is_root && !(*S).is_root( )) { 
            heap.pop_front(); heap.push_front( (*S).find_root( ) ); 
          }
        }
        
          
        static void clear_heap( )
        {
          std::deque<N*> bh = breadth_traverse( heap.front( ) );
          for (auto n = bh.begin(); n != bh.end();) {
            delete *n; *n = nullptr;
            n = bh.erase( ( n ) );            
          }
        }
      };
    }
  }
}
#endif
