#ifndef THESIS_NUMERAL_BINARY_QUEUE
#define THESIS_NUMERAL_BINARY_QUEUE
namespace KHJ  {
  namespace thesis  {
    namespace queue  {
      template<typename E, typename C, typename N, typename M, typename R>
      class numeral_binary_queue {
      public:
        typedef E element_type;
        typedef C comparator_type;
        typedef N node_type;
        typedef M modifier_type;
        typedef R registry_type;
        
        typedef typename registry_type::iterator_type iterator_type;
                
        explicit numeral_binary_queue( ) : registry_( R( )) { } 

        int size( ) const;
        
        N*   find_min( );       //find-min
        void   insert( N* ); //insert //should return iterator instead
        N*  erase_min( );       //delete_min
        void    erase( N* );  //delete //should take iterator instead
        
        void  meld( numeral_binary_queue& );       
        void clear( );
        
      private:
        registry_type registry_;
      };
    }
  }
}
#include "numeral_binary_queue.i++"
#endif
