#include<list>
#include<vector>

#ifndef THESIS_PAPER_STORE
#define THESIS_PAPER_STORE
namespace KHJ {
  namespace thesis {
    namespace store {
            
      template <typename N>        
      class paper_store {        
      public:        
        typedef std::vector<N*>       root_store;
        typedef std::list<root_store> store_type;
        
        struct accessor_proxy {  
          typedef typename store_type::accessor_type accessor_type;

           accessor_proxy( accessor_type a, bool v ) : accessor( a ), is_valid( v ) { }
          ~accessor_proxy( );

          store_type s;
          accessor_type accessor;
          accessor_type is_valid;
                  
          inline bool valid( ) const;  
          inline int   size( ) const;  
        };

        typedef typename store_type::iterator accessor_type;       
        typedef std::vector<accessor_type> join_schedule;
        
         paper_store( );
        ~paper_store( );
     
        N*                   top( ) const;  
        join_schedule push_front( N* S );
        N*             pop_front( );
        void              insert( accessor_type, N* );     
        N*               extract( accessor_type );
        
        bool            is_valid( accessor_type ) const;  
        int              size_of( accessor_type ) const;  

        void   push_hi( accessor_type );  
        void   push_lo( accessor_type );  
        void    pop_hi( );  
        void    pop_lo( );  
        inline bool  lo_empty( ) { return lo_.empty( ); }
        inline bool  hi_empty( ) { return hi_.empty( ); }
        
        void print( ) const;  
        
      private:
        //friend class cons_proxy<N, I, S>;
        
        typedef std::vector<accessor_type> lo_digits;
        typedef std::vector<accessor_type> hi_digits;
        
        N*           top_;
        store_type store_;
        
        lo_digits     lo_;
        hi_digits     hi_;
        
        join_schedule join_schedule_( );  
        
        void     grow_( accessor_type );  
        void   shrink_( accessor_type );  
        
        /* Paper store
           for arrays, store_accessor_type is just an int
           typedef std::forward_list<N*>  root_store;
           typedef std::list<root_store>  store_type;
        */
      };
    }
  }
}
#include "paper_store.i++"
#endif
