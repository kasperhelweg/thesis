/* 
  A root registry keeps track of the roots of the perfect binary heaps
  in a binary queue. The implicit numeral system used depends on store type and consolidation policy type.
  
  Author : KHJ 2014
*/

#ifndef THESIS_A_ROOT_REGISTRY
#define THESIS_A_ROOT_REGISTRY
#include <memory>
#include "heap_utils.h++"

namespace KHJ  {
  namespace thesis  {
    namespace registry  {
      template<typename N, typename M, typename S, typename J>
      class root_registry {
      public:
        typedef N node_type;
        typedef M modifier_type;
        typedef S store_type;
        typedef J consolidation_policy;
        
        typedef typename store_type::iterator_type iterator_type;
        
        explicit root_registry( );
        ~root_registry( ); 
        
        N*     top( ) const;
        bool empty( ) const;
        int   size( ) const;
        
        inline iterator_type begin( ) { return store_.begin( ); }
        inline iterator_type end( )   { return store_.end( ); }
        
        void insert( N* );
        N*  extract(    );
        
        void consolidate( );
        void  update_top( );
        
        void print( ) const;
        
        // Debug utils
        KHJ::thesis::utils::pfb<N, M> utils;
      private:
        store_type store_;
        consolidation_policy policy_;
      };
    }
  }
}
#include "root_registry.i++"
#endif
