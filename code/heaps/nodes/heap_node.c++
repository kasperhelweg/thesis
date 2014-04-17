// g++ -Wall -O3 -I ../../utils/ -I ./ -std=c++11 -o heap_node.out heap_node.c++

#include <iostream>
#include <assert.h>
#include <time.h>

#include "heap_a_node.h++"
#include "heap_b_node.h++"
#include "heap_utils.h++"
//namespace heap_utils = KHJ::thesis::heap_utils;

typedef int V;
typedef std::less<V> C;
typedef std::allocator<V> A;

typedef KHJ::thesis::heap_node::heap_a_node<V, C, A> N1;
typedef KHJ::thesis::heap_node::heap_b_node<V, C, A> N2;

// Utils
typedef KHJ::thesis::utils::pfb<N1, V> pfb_N1;
template<> std::deque<N1*> pfb_N1::heap = { };

void external( const N1& n )
{
  assert( n.is_root( ) );
  assert( n.left_->find_root( ) == &n );
  assert( n.left_->right_->find_root( ) == &n );
}

int main( )
{
  /*
  C comp = C( );

  if( comp(3,1) ) {
    std::cout << "less" << std::endl;
  } else {
    std::cout << "not less" << std::endl;
  }
  */

  N1 node_a( 4 );
  N1 node_b( 5 );

  assert( node_a < node_b );
  assert( node_a == node_a );
  
  assert( node_b > node_a );
  assert( !(node_a > node_b) );
  
  assert( node_a <= node_b );
  assert( !(node_a >= node_b) );
  
  assert( node_b >= node_a );
  assert( !(node_b <= node_a) );
  
  // Utils for perfect binary heaps
  std::srand( (unsigned) time(NULL) );
  
  for( int i = 0; i != 1000; i++ ) {
    N1* root = pfb_N1::build_and_inject( 10 );        
    pfb_N1::assert_heap( );
    pfb_N1::clear_heap( );
  }
  
  //pfb_N1::breadth_first_draw( );
  std::cout << "DONE BUILDING" << std::endl;
  
  N1* root = pfb_N1::build_and_inject( 10 );
  pfb_N1::assert_heap(  );
  for( int i = 0; i != 1000; i++ ) {
    N1* rep = pfb_N1::replace_rand( );
    pfb_N1::siftup( rep );
    pfb_N1::siftdown( rep );
    pfb_N1::assert_heap(  );
  }
  
  std::cout << "DONE REPLACING" << std::endl;
  pfb_N1::clear_heap( );
  std::cout << "DONE CLEARING" << std::endl;
 
  return 0;
}

/*
  ==25493== 
  ==25493== I   refs:      9,566,167,843
  ==25493== I1  misses:            4,769
  ==25493== LLi misses:            1,628
  ==25493== I1  miss rate:          0.00%
  ==25493== LLi miss rate:          0.00%
  ==25493== 
  ==25493== D   refs:      4,716,207,665  (3,001,698,050 rd   + 1,714,509,615 wr)
  ==25493== D1  misses:       26,021,391  (   22,401,844 rd   +     3,619,547 wr)
  ==25493== LLd misses:            9,096  (        6,115 rd   +         2,981 wr)
  ==25493== D1  miss rate:           0.5% (          0.7%     +           0.2%  )
  ==25493== LLd miss rate:           0.0% (          0.0%     +           0.0%  )
  ==25493== 
  ==25493== LL refs:          26,026,160  (   22,406,613 rd   +     3,619,547 wr)
  ==25493== LL misses:            10,724  (        7,743 rd   +         2,981 wr)
  ==25493== LL miss rate:            0.0% (          0.0%     +           0.0%  )
*/
