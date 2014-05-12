/* 
  A root registry keeps track of the roots of the perfect binary heaps
  in a binary queue. The implicit numeral system used depends on store type and consolidation policy type.
  
  Author : KHJ 2014
*/

#ifndef THESIS_REGULAR_ROOT_REGISTRY
#define THESIS_REGULAR_ROOT_REGISTRY
#include <forward_list>
#include "heap_utils.h++"

namespace KHJ  {
  namespace thesis  {
    namespace root_registry  {
      template<typename N, typename M, typename S>
      class regular_root_registry {
      public:
        typedef N node_type;
        typedef M modifier_type;
        typedef S root_table_type;
                
        typedef typename root_table_type::iterator_type iterator_type;
        
        explicit regular_root_registry( );
        ~regular_root_registry( ); 
        
        N*     top( ) const;
        bool empty( ) const;
        int   size( ) const;
        void print( ) const;
        
        void insert( N* );
        N*   extract( );        
        void update_top( );        
        void consolidate( );
        
        inline iterator_type begin( ) { return root_table_.begin( ); }
        inline iterator_type end( )   { return root_table_.end( ); }
        
        // Debug utils
        KHJ::thesis::utils::pfb<N, M> utils;
      private:
        root_table_type root_table_;
        std::forward_list<iterator_type> hi_;
        std::forward_list<iterator_type> walls_;
                
        void swap_nodes_( N* [], int, int );
      };
    }
  }
}
#include "regular_root_registry.i++"
#endif
