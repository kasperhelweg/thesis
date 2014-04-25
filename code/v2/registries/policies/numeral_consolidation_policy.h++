#ifndef THESIS_NUMERAL_CONSOLIDATION_POLICY
#define THESIS_NUMERAL_CONSOLIDATION_POLICY
#include<vector>

namespace KHJ {
  namespace thesis {
    namespace policy {      
      template <typename N, typename M, typename S>        
      class numeral_consolidation_policy {
      public:
        typedef N node_type;
        typedef M modifier_type;
        typedef S store_type;
        
        typedef store_type& store_reference_type;
        typedef typename store_type::iterator_type store_iterator_type;
        
        numeral_consolidation_policy( store_reference_type );
        ~numeral_consolidation_policy( );
        
        N* extract( );
        void consolidate( );
        
      private:
        store_reference_type store_;
        std::vector<store_iterator_type> hi_;
        std::vector<store_iterator_type> lo_;

        std::vector<store_iterator_type> state_;
        
        void fix_( store_iterator_type );
        void unfix_( store_iterator_type );

        bool in_idle_state_( ) const;
        void update_lo_( store_iterator_type );
        void swap_nodes_( N* [], int, int );
      };
    }
  }
}
#include "numeral_consolidation_policy.i++"
#endif


