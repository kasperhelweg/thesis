#ifndef THESIS_BINARY_QUEUE
#define THESIS_BINARY_QUEUE
namespace KHJ  {
  namespace thesis  {
    namespace queue  {
      template<typename E, typename N, typename R, typename A>
      class binary_queue {
      public:
        typedef E value_type;
        typedef N node_type;
        typedef R registry_type;
        typedef A allocator_type;
        
        explicit binary_queue( ) : registry_( R( )), allocator_( A( ) ) { } 
        
        value_type   top( );               //find-min
        N*          push( E const& );      //insert //should return iterator instead
        value_type   pop( );               //delete_min
        void       erase( N* );            //delete //should take iterator instead
        void        meld( binary_queue& );       
        void       clear( );
        
      private:
        registry_type   registry_;
        allocator_type allocator_;
        
        N*    buy_node_( const E& val );
        void sell_node_( N* );
        
      };
    }
  }
}
#include "binary_queue.i++"
#endif
