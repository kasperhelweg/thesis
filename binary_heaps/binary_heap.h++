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
    template <typename T, typename A = std::allocator<T>>
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
              typedef T  value_type;
              typedef A  allocator_type;
              typedef T& reference;
        typedef const T& const_reference;
              typedef T* pointer;
        typedef const T* const_pointer;
      
        // Allocators
        //
        //typedef typename allocator_type::template rebind<node_>::other node_allocator;
        
        // Iterators
        //
     
        // Modifiers
        //
             bool empty   ( ) const;
        reference top     ( ) const;           // find min/max
        reference pop_top ( );                 // extract min/max
             void insert  ( const_reference );
             void decrease( );
             void increase( T );
             void erase   ( );
             void replace ( );
             void clear   ( );
      private:
        // Variable Members
        //
        //node_allocator  alloc_;
        //         node_ *top_;
      
        // Function Members
        //
        //node_ *buy_node_( const T & ); 
        //void  sell_node_( node_ * ); 
        //void       clear( );
        void siftup  ( );
        void siftdown( );
      
      };
  }
}
#include "binary_heap.i++"
#endif
