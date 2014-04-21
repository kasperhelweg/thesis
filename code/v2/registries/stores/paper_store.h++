#include<list>
#include<vector>

#ifndef THESIS_PAPER_STORE
#define THESIS_PAPER_STORE
namespace KHJ {
  namespace thesis {
    namespace store {
      
      template<typename N, typename A, typename S>
      class cons_proxy {
      public:  
        typedef N node_type;
        typedef A accessor_type;
        typedef S store_type;
        
        explicit cons_proxy( accessor_type a, store_type& s  ) : accessor_( a ), paper_store_( s ) 
        { }
                
        accessor_type accessor( ) { return accessor_; }
        accessor_type     next( ) { return std::next( accessor_ ); }
        accessor_type     prev( ) { return std::prev( accessor_ ); }
        
        void push( accessor_type a, N* s ) {
          paper_store_.insert( a, s );
        }
        
        N* pop( accessor_type a  ) {
          return paper_store_.extract( a );
        }

        void pop_hi( ) {
          paper_store_.hi_.pop_back( );
        }

        void pop_lo( ) {
          paper_store_.lo_.pop_back( );
        }
        
        void push_hi( accessor_type a ) {
          paper_store_.push_hi_( a );
        }

        void push_lo( accessor_type a ) {
          paper_store_.push_lo_( a );
        }

        bool is_valid( accessor_type a ) {
          return paper_store_.is_valid_( a );
        }
     
        int size( accessor_type a ) {
          return paper_store_.size_of_( a );
        }

        bool lo_empty( ) {
          return paper_store_.lo_.empty( );
        }
        
        bool hi_empty( ) {
          return paper_store_.hi_.empty( );
        }
        
        
      private:
        store_type&  paper_store_;
        accessor_type   accessor_;
      };
      
      template <typename N>        
      class paper_store {        
      public:        
        typedef std::vector<N*>       root_store;
        typedef std::list<root_store> store_type;
        typedef typename store_type::iterator  I;

        typedef paper_store S;
        typedef cons_proxy<N, I, S> C;

        typedef std::vector<C> cons_list;
        
         paper_store( );
        ~paper_store( );
        
        cons_list push_front( N* S );
        N*         pop_front( );
        N*               top( );  

        void print( );  
      
      private:
        friend class cons_proxy<N, I, S>;
        
        typedef std::vector<C> lo_digits;
        typedef std::vector<C> hi_digits;

        N*           top_;
        store_type store_;
        lo_digits     lo_;
        hi_digits     hi_;
        
        void      insert( I, N* );     
        N*       extract( I );
        cons_list  cons_(   );  
                
        bool is_valid_( I );  
        int   size_of_( I );  

        void   push_hi_( I );  
        void   push_lo_( I );  

        void     grow_( I );  
        void   shrink_( I );  
        
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
