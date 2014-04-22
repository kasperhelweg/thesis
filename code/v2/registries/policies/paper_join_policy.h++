#include<vector>

#ifndef THESIS_PAPER_JOIN_POLICY
#define THESIS_PAPER_JOIN_POLICY
namespace KHJ {
  namespace thesis {
    namespace policy {
            
      template <typename I>        
      class paper_join_policy {
        typedef I iterator_type;
        typedef std::vector<iterator_type> lo_digits;
        typedef std::vector<iterator_type> hi_digits;
        
        lo_digits lo_;
        hi_digits hi_;
     
      public:
        typedef std::vector<iterator_type> cons_list;

        void   push_hi( iterator_type position );  
        void   push_lo( iterator_type );  
        void    pop_hi( );  
        void    pop_lo( );  
        inline bool  lo_empty( ) const { return lo_.empty( ); } 
        inline bool  hi_empty( ) const { return hi_.empty( ); } 
        
        inline int lo_size( ) const { return lo_.size( ); } 
        inline iterator_type get_lo( int index ) const { if(!lo_.empty() ) {return lo_[index];} } 
        
        inline int hi_size( ) const { return hi_.size( ); }
        inline iterator_type get_hi( int index ) const { if(!hi_.empty( )) {return hi_[index];} }
        
        void print( ) const;  
        
        cons_list join_list_hi( );  
        cons_list join_list_lo( );  
      };
    }
  }
}
#include "paper_join_policy.i++"
#endif
