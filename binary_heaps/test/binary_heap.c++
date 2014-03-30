#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include "heap_node.h++"
#include "binary_heap.h++"

int main() 
{
  typedef double E;                     // Element Type
  typedef KHJ::thesis::heap::node<E> N;       // Node type    
  typedef KHJ::thesis::heap::binary_heap<E, N> H;  // The heap
  
  double el = 3.0;
  H heap; 
  
  // Check that heap is empty
  if( heap.empty( ) ) {
    std::cout << "empty\n" << std::endl;
  }
  heap.insert( el );
}
