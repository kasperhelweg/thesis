/**
 * 
 *
 * 
 * 
 * 
 *
 * @author KHJ
 *
 */
#ifndef THESIS_BINARY_HEAP
#define THESIS_BINARY_HEAP
namespace KHJ {
  namespace thesis {
    namespace heap {
      template <typename E, 
                typename N, 
                typename A = std::allocator<N>>
        class binary_heap
        {
          // Private Data Members
          //
        
        public:
          // Structors    
          //
           binary_heap( );
          ~binary_heap( );
        
          // Typedefs
          //
          typedef E  element_type;
          typedef N  node_type;
          typedef A  allocator_type;
        
          typedef E& reference;
          typedef const E& const_reference;
        
          typedef E* pointer;
          typedef const E* const_pointer;
        
          typedef N& node_reference;
          typedef const N& const_node_reference;
        
          typedef N* node_pointer;
          typedef const N* const_node_pointer;
        
          // Allocators
          //
          //typedef typename allocator_type::template rebind<N>::other node_allocator;
          typedef allocator_type node_allocator;
        
          // Iterators
          //
        
          // Modifiers
          //
          bool 
          empty   ( ) const;
          void 
          clear   ( );
          reference 
          top     ( ) const;                         // find min/max
          reference 
          pop_top ( );                           // extract min/max
          const_node_reference 
          insert  ( const_reference );
          void 
          decrease( );
          void 
          increase( );
          
        private:
          // Variable Members
          //
          node_pointer   t_;          
          node_allocator alloc_;
          
          // Function Members
          //
          void 
          swap_    ( );
          void 
          siftup_  ( );
          void 
          siftdown_( );
          node_pointer 
          buy_node_( const_reference );
        };
    }
  }
}
#include "binary_heap.i++"
#endif
