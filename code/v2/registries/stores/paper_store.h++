#include<list>
#include <forward_list>
#include<vector>

#ifndef THESIS_PAPER_STORE
#define THESIS_PAPER_STORE
namespace KHJ {
  namespace thesis {
    namespace store {
            
      template <typename N>        
      class paper_store {        
        struct node {
          int size_;
          std::vector<N*> root_list;           
        };

      
      public:        

        /* this should be the store iterator !

           struct accessor_proxy {  
           typedef typename store_type::iterator_type iterator_type;
           
           accessor_proxy( iterator_type a, bool v ) : accessor( a ), is_valid( v ) { }
           ~accessor_proxy( );
           
           store_type s;
           iterator_type accessor;
           iterator_type is_valid;
           
           inline int   size( ) const;  
           
           inline bool operator==(const accessor_proxy& O) const
           {
           return element_ == O.element_;
           }
           
           };
        */

        /* here should be a custom iterator if need be 
           for example, there could be a root iterator, a store iterator and a heap iterator
         */
        typedef std::vector<N*>       root_store;
        typedef std::list<root_store> store_type;
        
        //typedef std::list<node> store_type;

        typedef typename store_type::iterator iterator_type;
        typedef typename store_type::const_iterator const_iterator_type;
        
        paper_store( );
        ~paper_store( );

        void push_front( N* S );
        N*    pop_front( );
        void     insert( iterator_type, N* );     
        N*      extract( iterator_type );
        int        size( iterator_type );  
           
        /* should return custom iterator if need be */
        inline iterator_type      begin( ) { return store_.begin( ); }
        inline iterator_type        end( ) { return store_.end( );   }
        inline root_store&        front( ) { return store_.front( ); }
        inline root_store&         back( ) { return store_.back( );  }

        inline const_iterator_type last( ) const { return std::prev( store_.end( ) );   }
        
        void   grow( );  
        void shrink( );  
        
        void print( ) const;  
        
      private:   
        store_type store_;



        /* Paper store
           for arrays, store_iterator_type is just an int
           typedef std::forward_list<N*>  root_store;
           typedef std::list<root_store>  store_type;
        */
      };
    }
  }
}
#include "paper_store.i++"
#endif
