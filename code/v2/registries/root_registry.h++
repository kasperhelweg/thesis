#ifndef THESIS_A_ROOT_REGISTRY
#define THESIS_A_ROOT_REGISTRY
namespace KHJ  {
  namespace thesis  {
    namespace registry  {
      template<typename N, typename M, typename S>
      class root_registry {
      public:
        typedef N node_type;
        typedef M modifier_type;
        typedef S store_type;
      
        typedef typename store_type::join_schedule join_schedule;
        typedef typename store_type::accessor_type accessor_type;
        
        explicit root_registry( );
                ~root_registry( ); 
        
        void    top( ) const;
        void insert( N* );
        N*  extract( );

        void print( ) const;
        
      private:
        store_type store_;
       
        void        fix_( accessor_type );
        void      unfix_( );
        void swap_nodes_( N* [], int, int );
        void  update_lo_( accessor_type );
      };
    }
  }
}
#include "root_registry.i++"
#endif
