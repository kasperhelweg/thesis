#ifndef THESIS_A_ROOT_REGISTRY
#define THESIS_A_ROOT_REGISTRY
namespace KHJ  {
  namespace thesis  {
    namespace registry  {
      template<typename N, typename M, typename S, typename J>
      class root_registry {
      public:
        typedef N     node_type;
        typedef M modifier_type;
        typedef S    store_type;
        typedef J   join_policy;
      
        typedef typename join_policy::cons_list cons_list;
        typedef typename store_type::iterator_type iterator_type;
        
        explicit root_registry( );
                ~root_registry( ); 
        
        void    top( ) const;
        void insert( N* );
        N*  extract( );

        void print( ) const;
        
      private:
        store_type        store_;
        join_policy join_policy_;
       
        void        fix_( iterator_type );
        void      unfix_( );
        void swap_nodes_( N* [], int, int );
        void  update_lo_( iterator_type );
      };
    }
  }
}
#include "root_registry.i++"
#endif
