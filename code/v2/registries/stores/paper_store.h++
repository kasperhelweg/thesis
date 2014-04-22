#include<list>
#include<vector>

#ifndef THESIS_PAPER_STORE
#define THESIS_PAPER_STORE
namespace KHJ {
  namespace thesis {
    namespace store {
            
      template <typename N, typename C>        
      class paper_store {        
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
        
        typedef typename store_type::iterator iterator_type;
        typedef C comparator_type;
        
        paper_store( );
        ~paper_store( );
     
        N*          top( ) const;  
        void push_front( N* S );
        N*    pop_front( );
        void     insert( iterator_type*, N* );     
        N*      extract( iterator_type );
        
           
        /* should return custom iterator if need be */
        inline iterator_type  begin( ) { return store_.begin( ); }
        inline iterator_type    end( ) { return store_.end( );   }
        inline root_store&     back( ) { return store_.back( );   }
        
        void print( ) const;  

        N*           top_;
        void         shrink_( );  
      private:   

        store_type store_;

        comparator_type compare_;
      
        void           grow_( iterator_type );  


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
