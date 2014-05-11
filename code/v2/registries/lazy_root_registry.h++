/* 
  A root registry keeps track of the roots of the perfect binary heaps
  in a binary queue. The implicit numeral system used depends on store type and consolidation policy type.
  
  Author : KHJ 2014
*/

#ifndef THESIS_LAZY_ROOT_REGISTRY
#define THESIS_LAZY_ROOT_REGISTRY
#include <memory>
#include "heap_utils.h++"

namespace KHJ  {
  namespace thesis  {
    namespace root_registry  {
      template<typename N, typename M, typename S>
      class lazy_root_registry {
      public:
        typedef N node_type;
        typedef M modifier_type;
        typedef S store_type;
                
        typedef typename store_type::iterator_type iterator_type;
        
        explicit lazy_root_registry( );
        ~lazy_root_registry( ); 
        
        N*     top( ) const;
        bool empty( ) const;
        int   size( ) const;
        void print( ) const;
        
        void insert( N* );
        N*   extract( );        
        void update_top( );        
        void consolidate( );
        
        inline iterator_type begin( ) { return store_.begin( ); }
        inline iterator_type end( )   { return store_.end( ); }
        
        // Debug utils
        KHJ::thesis::utils::pfb<N, M> utils;
      private:
        store_type store_;
              
        void fix_( iterator_type );
        void swap_nodes_( N* [], int, int );
      };
    }
  }
}
#include "lazy_root_registry.i++"
#endif
