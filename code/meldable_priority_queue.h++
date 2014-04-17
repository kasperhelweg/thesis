/**
 *
 * Desc : A meldable priority queue. The class is a bridge to a concrete implementation.
 * Auth : KHJ
 * Ref  :
 *
 */
#ifndef THESIS_HEAP_A_NODE
#define THESIS_HEAP_A_NODE
namespace KHJ {
  namespace thesis {
    template< typename V, 
              typename N, 
              typename R >
    class meldable_priority_queue {
      
      
    public:
      N* 
      find_min( );
      void 
      insert(  );
      void      
      borrow( );
      void 
      extract_min( );
      void      
      remove( );
      void        
      meld( );
    
    private:
      

    };
  }
}
#include "heap_store_base.i++"
#endif


