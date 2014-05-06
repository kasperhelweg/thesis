#ifndef THESIS_LAZY_STORE
#define THESIS_LAZY_STORE
#include <list>
#include <forward_list>
#include <vector>
#include <math.h>

namespace KHJ {
  namespace thesis {
    namespace store {
            
      template <typename N>        
      class lazy_store {        
        
      public:     
        typedef std::vector<N*> store_type;
        typedef std::forward_list<store_type> head_type;
        
        typedef typename head_type::iterator iterator_type;
        typedef typename head_type::const_iterator const_iterator_type;
        
        typedef typename store_type::iterator node_iterator_type;
        typedef typename store_type::const_iterator const_node_iterator_type;
        
         lazy_store( );
        ~lazy_store( );

        N*     top;

        int      size( ) const; 
        bool one_heap( ) const; 
        bool    empty( ) const; 

        void push_front( N* S );
        N*    pop_front( );    
          
        /* maybe only support const iterators since "head_" is not supposed to be modified? */
        inline iterator_type begin( ) 
        { return head_.begin( ); }
        inline iterator_type end( ) 
        { return head_.end( ); }
        
        inline const_iterator_type begin( ) const 
        { return head_.begin( ); }
        inline const_iterator_type   end( ) const 
        { return head_.end( );   }
        
        void print( ) const;  
        
      private:  
        int         size_;
        head_type   head_;
        store_type store_;
      };
    }
  }
}
#include "lazy_store.i++"
#endif
