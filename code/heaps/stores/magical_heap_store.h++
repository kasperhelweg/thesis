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
        
        constexpr static C compare_ = C( );
        
      public:
        explicit magical_heap_store( ); 
        ~magical_heap_store( ); 

        // maybe not public?
        typedef typename store_type::iterator store_iterator_type;
         // join policy
        typedef std::vector<store_iterator_type> lo_digits;
        typedef std::vector<store_iterator_type> hi_digits;

        N*           top( );
        void      inject( N* );
        N*         eject(  );
        N*        remove( N* ); // should be node iterator at some point
        N*    remove_min( );
        void       print( );

        void       swap_nodes_( N* nodes[], int, int );
        void       update_lo_( store_iterator_type );



        // maybe temporary
        store_iterator_type begin( );
        store_iterator_type   end( );
          
      private:
        store_type store_;
        lo_digits lo_;
        hi_digits hi_;
        
        N* top_;
        std::vector<store_iterator_type> state_;

        void fix_( store_iterator_type );
        void unfix_( store_iterator_type );
        N* borrow_( );
        
        void   grow_( store_iterator_type );
        void shrink_( store_iterator_type );

        N* scan_top_( );
        bool in_idle_state_( );
      };
    }
  }
}
#include "magical_heap_store.i++"
#endif
