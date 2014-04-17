#include <iterator> 
#include <vector>
#include <list>
#include <assert.h>

#include "heap_utils.h++"
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

#ifndef THESIS_MAGICAL_HEAP_STORE
#define THESIS_MAGICAL_HEAP_STORE
namespace KHJ {
  namespace thesis {
    namespace stores {
      template <typename N, typename C>        
      class magical_heap_store {
        typedef std::vector<N*>        root_store;
        typedef std::list<root_store>  store_type;

        typedef typename store_type::iterator store_iterator_type;
       
        
        // join policy
        typedef std::vector<store_iterator_type> lo_digits;
        typedef std::vector<store_iterator_type> hi_digits;

        constexpr static C compare_ = C( );


      public:
        explicit magical_heap_store( ); 
        ~magical_heap_store( ); 

        void push( N* );
        void print( );
          
      private:
        store_type store_;
        lo_digits lo_;
        hi_digits hi_;
        
        N* top_;
        std::vector<store_iterator_type> state_;

        void fix_( store_iterator_type );
        void unfix_( );
        
        void grow_( store_iterator_type );
        

      };
    }
  }
}
#include "magical_heap_store.i++"
#endif
