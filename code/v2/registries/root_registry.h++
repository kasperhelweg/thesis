/* 
  A root registry keeps track of the roots of the perfect binary heaps
  in a binary queue. In this registry the magical skew system is used such that 
  the registry structure is of the form :REGWXPS HERE
  Also note that the registry is composed of two parts: Storage and Join "policy".
  
  Author : KHJ 2014
*/


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
        
        
        N*          top( ) const;
        bool      empty( ) const;
        void     insert( N* );
        N*      extract( N* );
        N*  extract_min( ); // only extract

        void print( ) const;
        
      private:
        typedef std::vector<iterator_type> state_type;
        
        N* top_;

        store_type        store_;
        join_policy join_policy_;
        state_type        state_;

        void           fix_( iterator_type );
        void         unfix_( iterator_type );
        N*          borrow_( );

        bool in_idle_state_(  ) const;  
        void    swap_nodes_( N* [], int, int );
        void     update_lo_( iterator_type );
      };
    }
  }
}
#include "root_registry.i++"
#endif
