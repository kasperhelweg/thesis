#include <vector>
#include <list>

#include "heap_a_node.h++"
#include "heap_b_node.h++"

/**
 * Desc : A two-pointer basic heap node used in a perfect binary heap.
 * Auth : KHJ
 * Ref  :
 * 
 *     R >|
 *   >/ \<
 *   S > O
 *  /   /
 *
 * @author KHJ
 *
 */

#ifndef THESIS_MAGICAL_HEAP
#define THESIS_MAGICAL_HEAP
namespace KHJ {
  namespace thesis {
    namespace heaps {
      template < typename N,
                 typename S, 
                 typename V = int, 
                 typename C = std::less<N>,
                 typename A = std::allocator<N>>
        
        class magical_heap {
          typedef S heap_store_type;
          typedef A allocator_type;

        public:
          explicit magical_heap( ); 
          ~magical_heap( ); 
          
          V   pop( );
          N*  push( const V& );
          N*  top( ); // return heap_store_.top( ) or similar
          N*  erase( );
          int size( );

          void print( );
          
          
        private:
          allocator_type       alloc_;
          heap_store_type heap_store_;
          
          N*   buy_node_ ( const V&  );
          void sell_node_( N* ); 
          void clear     ( );
        };
    }
  }
}
#include "magical_heap.i++"
#endif
