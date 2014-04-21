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
        
        lo_digits     lo_;
        hi_digits     hi_;
     
      public:
        typedef std::vector<iterator_type> cons_list;

        void   push_hi( iterator_type position );  
        void   push_lo( iterator_type );  
        void    pop_hi( );  
        void    pop_lo( );  
        inline bool  lo_empty( ) { return lo_.empty( ); }
        inline bool  hi_empty( ) { return hi_.empty( ); }

        void print( ) const;  

        cons_list join_list( );  
      };
    }
  }
}
#include "paper_join_policy.i++"
#endif
