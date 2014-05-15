#ifndef THESIS_LAZY_ROOT_LIST
#define THESIS_LAZY_ROOT_LIST
#include <list>
#include <forward_list>
#include <vector>
#include <math.h>

namespace KHJ {
  namespace thesis {
    namespace root_list {
      template <typename N>        
      class lazy_root_list {        
        
      public:     
        typedef std::vector<N*> root_list_type;
       
        typedef typename root_list_type::iterator 
        iterator_type;
        typedef typename root_list_type::const_iterator 
        const_iterator_type;
          
         lazy_root_list( );
        ~lazy_root_list( );

        N*  top;
        int size_;

        int      
        size( )  const; 
        bool    
        empty( ) const; 
        bool 
        one_heap( ) const; 
    
        void 
        inject( N* S );
        N*    
        eject( );    

        void 
        insert_root( iterator_type, N* );
        N* 
        remove_root( iterator_type );
          
        /* maybe only support const iterators since "head_" is not supposed to be modified? */
        inline iterator_type 
        begin( ) { return root_list_.begin( ); }
        inline iterator_type 
        end( ) { return root_list_.end( ); }
        
        inline const_iterator_type 
        begin( ) const { return root_list_.begin( ); }
        inline const_iterator_type   
        end( ) const { return root_list_.end( );   }
        
        void 
        print( ) const;  
        
      private:  
        root_list_type root_list_;
      };
    }
  }
}
#include "lazy_root_list.i++"
#endif
