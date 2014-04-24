#ifndef THESIS_PAPER_STORE
#define THESIS_PAPER_STORE
#include <list>
#include <forward_list>
#include <vector>
#include <math.h>

namespace KHJ {
  namespace thesis {
    namespace store {
            
      template <typename N>        
      class paper_store {        

        struct store_node {
          typedef std::vector<N*> root_list_type;
          typedef typename root_list_type::iterator       iterator_type;
          typedef typename root_list_type::const_iterator const_iterator_type;
          
          store_node( ) : size_( 0 ), root_list_( root_list_type( ) ) {}
          
          int size_;
          root_list_type root_list_;       
          
          int size( ) const 
          { return size_; }
          bool empty( ) const 
          { return size_ == 0; }
          
          iterator_type begin( ) 
          { return root_list_.begin( ); }     
          iterator_type   end( ) 
          { return root_list_.end( ); }     
        };

      public:        
        typedef std::list<store_node> store_type;

        typedef typename store_type::iterator iterator_type;
        typedef typename store_type::const_iterator const_iterator_type;
        
        typedef typename store_node::iterator_type node_iterator_type;
        typedef typename store_node::const_iterator_type const_node_iterator_type;
        

        paper_store( );
        ~paper_store( );

        N*   top; 
        int  size( )  const; 
        bool empty( ) const; 

        void push_front( N* S );
        N*    pop_front( );
        void     insert( iterator_type, N* );     
        N*      extract( iterator_type );
        N*      extract( iterator_type, node_iterator_type );
          
        /* should return custom iterator if need be */
        inline iterator_type begin( ) 
        { return store_.begin( ); }
        inline iterator_type end( ) 
        { return store_.end( );   }

        inline const_iterator_type begin( ) const 
        { return store_.begin( ); }
        inline const_iterator_type   end( ) const 
        { return store_.end( );   }

        inline const_iterator_type last( )  const 
        { return std::prev( store_.end( ) );   }
        
        void   grow( );  
        void shrink( );  
        
        void print( ) const;  
        
      private:   
        store_type store_;
      };
    }
  }
}
#include "paper_store.i++"
#endif
