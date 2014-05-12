#ifndef THESIS_REGULAR_ROOT_TABLE
#define THESIS_REGULAR_ROOT_TABLE
#include <iostream>
#include <list>
#include <forward_list>
#include <bitset>

#include <vector>
#include <math.h>

namespace KHJ {
  namespace thesis {
    namespace root_table {
      template <typename N>        
      class regular_root_table {        
        
        struct root_list_node {
          N* hp_;
          N* sp_;
          unsigned long bittrace_;
          
          void print_bittrace( ) const
          {
            std::cout << "bittrace: " << (std::bitset<64>) bittrace_ << std::endl;
          }
        };

        // Template of two types: Container and Adapter
        struct root_table_node {
          typedef std::forward_list<root_list_node> root_list_type;
          
          typedef typename root_list_type::iterator       
          iterator_type;
          typedef typename root_list_type::const_iterator 
          const_iterator_type;
          
          root_table_node( ) : size_( 0 ), root_list_( root_list_type( ) ) { }
          
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
        typedef std::list<root_table_node> root_table_type;
        
        typedef typename root_table_type::iterator       
        iterator_type;
        typedef typename root_table_type::const_iterator 
        const_iterator_type;
        
        typedef typename root_table_node::iterator_type       
        root_list_iterator_type;
        typedef typename root_table_node::const_iterator_type 
        const_root_list_iterator_type;
        
         regular_root_table( );
        ~regular_root_table( );

        N*   top; 
        int  size( )  const; 
        bool empty( ) const; 

        void push_front( N* S );
        N*    pop_front( );
        void     insert( iterator_type, N* );     
        N*      extract( iterator_type );
        N*      extract( iterator_type, root_list_iterator_type );
          
        /* should return custom iterator if need be */
        inline iterator_type begin( ) 
        { return root_table_.begin( ); }
        inline iterator_type end( ) 
        { return root_table_.end( );   }
        
        inline const_iterator_type begin( ) const 
        { return root_table_.begin( ); }
        inline const_iterator_type   end( ) const 
        { return root_table_.end( );   }
        
        inline const_iterator_type last( )  const 
        { return std::prev( root_table_.end( ) );   }
        
        void   grow( );  
        void shrink( );  
        
        void print( ) const;  
        
      private:   
        root_table_type root_table_;
      };
    }
  }
}
#include "regular_root_table.i++"
#endif
