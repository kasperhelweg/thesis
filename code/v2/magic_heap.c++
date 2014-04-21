int main( )
{
  typedef int E1;
  typedef KHJ::thesis::heap_node::heap_a_node<E1> N1;

  typedef std::less<N1> C1;
  typedef KHJ::thesis::modifier::node_a_modifier<N1, C1> M1;
  
  /*
  typedef KHJ::thesis::registry::root_registry<N1, C1, M1> H1;
  typedef KHJ::thesis::heap::magic_heap<N1, C1, M1> H1;
  */

  return 0;
}
