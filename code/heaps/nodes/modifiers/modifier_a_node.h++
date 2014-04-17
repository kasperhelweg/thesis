#ifndef THESIS_MODIFIER_A_NODE
#define THESIS_MODIFIER_A_NODE
namespace KHJ {
  namespace thesis {
    namespace modifier {      

      template <typename N, typename C = std::less<N>>
        class modifier_a_node {
          
          void       join( N*, N* );
          void join_heaps( N*, N* );
           N**      split( );
            N*    replace( N* );
          
        private:
          N*  cut_left( );
          N* cut_right( );
          
          void swap_colors( N* );
          
          void   siftup( );
          void siftdown( );          
          void     swap( N* o );
        };
    }
  }
}
//#include "heap_a_node.i++"
#endif
