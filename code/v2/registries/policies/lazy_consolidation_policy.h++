#ifndef THESIS_LAZY_CONSOLIDATION_POLICY
#define THESIS_LAZY_CONSOLIDATION_POLICY
#include<vector>
#include <math.h>
namespace KHJ {
  namespace thesis {
    namespace policy {      
      template <typename N, typename M, typename S>        
      class lazy_consolidation_policy {
      public:
        typedef N node_type;
        typedef M modifier_type;
        typedef S store_type;
        
        typedef store_type& store_reference_type;
        typedef typename store_type::iterator_type store_iterator_type;
        
         lazy_consolidation_policy( store_reference_type );
        ~lazy_consolidation_policy( );
        
        N* extract( );
        void consolidate( );
        
      private:
        store_reference_type store_;
        std::vector<store_iterator_type> hi_;
        
        void fix_( store_iterator_type );
        void swap_nodes_( N* [], int, int );
      };
    }
  }
}
#include "lazy_consolidation_policy.i++"
#endif
