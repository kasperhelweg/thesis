/**
 * 
 *
 * 
 * 
 * 
 *
 * @author KHJ
 *
 */
#ifndef THESIS_HEAP_NODE
#define THESIS_HEAP_NODE
namespace KHJ {
  namespace thesis {
    namespace heap {
      template <typename E>
      class node
      {
      public:
        typedef E element_type;
        typedef node<E> node_type;
        
        E     element_;
        node*  parent_;
        node* l_child_;
        node* r_child_;
        
        // Structors    
        //
        node() : parent_( nullptr ), l_child_( nullptr ), r_child_( nullptr ) { 
        }
        
        explicit node( const E& element ) : element_( element ), parent_ ( nullptr ), 
                                            l_child_( nullptr ), r_child_( nullptr ) { 
        }
      };
    }
  }
}
#include "heap_node.i++"
#endif
