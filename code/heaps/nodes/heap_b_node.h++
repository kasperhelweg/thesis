/**
 * Desc : A two-pointer basic heap node used in a perfect binary heap.
 * Auth : KHJ
 * Ref  :
 * 
 *     R >|
 *   >/ \<
 *   S > O
 *  /   /
 *
 * @author KHJ
 *
 */

#ifndef THESIS_HEAP_B_NODE
#define THESIS_HEAP_B_NODE


namespace KHJ {
  namespace thesis {
    namespace heap_node {

      template <typename V = int, 
                typename C = std::less<V>, 
                typename A = std::allocator<V>>        
        class heap_b_node {
          typedef heap_b_node N;
           
          V  element_;
          bool color_;
          N*    left_;
          N*   right_;

        public:
          explicit heap_b_node( const V& e ) : element_( e ), color_( 0 ), left_( nullptr ) , right_( nullptr ) 
          { }; 
       
        public:
          bool is_root( ) const;
          bool is_leaf( ) const;
          N*    parent( ) const;
          N* find_root( ) const;

          /* join should assert that this is a root node. 
             Then, splice left and right subtrees */
          N* join( N* l, N* r );
          /* split should assert the this is a root node. 
             Then, split left and right subtrees */
          void split( N*);
          /* replaces this node with q and returns a handle to it. 
             promote / demote is used in the process */
          void replace( N* q );
          
        private:
          N*  cut_left( );
          N* cut_right( );

          void swap_colors( N* q );
          
          void promote( );
          void  demote( );
        };
    }
  }
}
#include "heap_b_node.i++"
#endif
