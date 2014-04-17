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
#ifndef THESIS_HEAP_A_NODE
#define THESIS_HEAP_A_NODE
namespace KHJ {
  namespace thesis {
    namespace heap_node {      
      template <typename V = int, 
                typename C = std::less<V>, 
                typename A = std::allocator<V>>
        
        class heap_a_node {           
        public:  
          typedef V      value_type;
          typedef C comparator_type;
          typedef A  allocator_type;
          typedef    heap_a_node<V, C, A> N;
          
             V element_;
          bool   color_;
            N*    left_;
            N*   right_;

          constexpr static C compare_ = C( );
          
          //friend class heap_a_node;
          
        public:
          explicit heap_a_node( const V& ); 
          explicit heap_a_node( const V&, bool ); 
          ~heap_a_node( ); 

          // Operators
          inline bool operator<( const N& )  const;
          inline bool operator>( const N& )  const;
          inline bool operator==( const N& ) const;
          inline bool operator!=( const N& ) const;
          inline bool operator<=( const N& ) const;
          inline bool operator>=( const N& ) const;


          // Accessors
          bool     is_root( ) const;
          bool     is_leaf( ) const;
           int      height( ) const;
            N*      parent( ) const;
            N*  left_child( ) const;
            N* right_child( ) const;
            N*   find_root( ) const;
          
          // Modifiers
          void       join( N*, N* );
          void join_heaps( N*, N* );
           N**      split( );
            N*    replace( N* );
          void       swap( N* o );

          //should be private
        public:
          N*  cut_left( );
          N* cut_right( );
          
          void swap_colors( N* );
          
          void   siftup( );
          void siftdown( );          
        };
    }
  }
}
#include "heap_a_node.i++"
#endif
