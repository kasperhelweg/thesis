#ifndef THESIS_MAGIC_QUEUE
#define THESIS_MAGIC_QUEUE
namespace KHJ  {
  namespace thesis  {
    namespace priority_queue  {
      template<typename E, typename N, typename R, typename A>
      class magic_queue {
      public:
        typedef E value_type;
        typedef N node_type;
        typedef R registry_type;
        typedef A allocator_type;

        explicit magic_queue( ) : registry_( R( )), allocator_( A( ) ) { } 
        
        value_type   top( );          //find-min
        N*          push( E const& ); //insert //should return iterator instead
        value_type   pop( );          //delete_min
        void       erase( N* );       //delete //should take iterator instead
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
#include "magic_queue.i++"
#endif
