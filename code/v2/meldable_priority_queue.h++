#ifndef THESIS_MELDABLE_PRIORITY_QUEUE
#define THESIS_MELDABLE_PRIORITY_QUEUE
namespace KHJ  {
  namespace thesis  {
    namespace priority_queue  {
      template<typename V, typename C, typename A, typename E, typename R>
      class meldable_priority_queue {
      public:
        typedef V value_type;
        typedef C comparator_type;
        typedef A allocator_type;
        typedef E element_type;
        typedef R realizer_type;
        
        
        explicit meldable_priority_queue( ) : realizer_( realizer_type( )), allocator_( allocator_type( ) ) { } 
        
        // accessors     
        value_type top( );               //find-min
        bool     empty( );
        int       size( );
        
        // modifiers     
        E*          push( V const& );      //insert //should return iterator instead
        value_type   pop( );               //delete_min
        void       erase( E* );            //delete //should take iterator instead
        void    increase( E* );            //delete //should take iterator instead
        //void        meld( binary_queue& );       
        void       clear( );
        
      private:
        realizer_type   realizer_;
        allocator_type allocator_;
        
        E*    buy_( const V& val );
        void sell_( E* );
        
      };
    }
  }
}
#include "meldable_priority_queue.i++"
#endif
