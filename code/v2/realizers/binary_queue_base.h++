#ifndef THESIS_BINARY_QUEUE_BASE
#define THESIS_BINARY_QUEUE_BASE
namespace KHJ  {
  namespace thesis  {
    namespace queue  {
      template<typename E, typename N, typename R>
      class binary_queue_base {
      public:
        typedef E element_type;
        typedef N node_type;
        typedef R registry_type;
                
        explicit binary_queue_base( ) : registry_( R( )) { } 
        
        value_type   top( );               //find-min
        N*          push( E const& );      //insert //should return iterator instead
        value_type   pop( );               //delete_min
        void       erase( N* );            //delete //should take iterator instead
        void        meld( binary_queue& );       
        void       clear( );
        
      private:
        registry_type registry_;
      };
    }
  }
}
#include "binary_queue_base.i++"
#endif
