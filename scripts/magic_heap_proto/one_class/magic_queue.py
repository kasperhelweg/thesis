from binary_queue import binary_queue
from heap_node import heap_node
from stack import *
import heap_utils
from linked_list import *

class magic_queue( binary_queue ):
  def __init__( self ):
    super( ).__init__( )
    self.hi = linked_list( )
    self.lo = linked_list( )

    self.fix_stack = fix_stack_vector( ) # Hi and Lo digits

  # overrides insert
  def insert( self, n ): # increment
    # insert new node at front.
    f = self._front( )
    assert True == n.is_root( )
    f.push( n )

    # update min pointer
    if not self.min_pointer or n < self.min_pointer:
      self.min_pointer = n
    
    if f.size == 1 and self.lo.peak( 1 ) != f: 
      self.lo.append( f ) 
    elif f.size == 2: 
      self.lo.pop( )
  
    if f.size == 3: self.__fix( f )
    else:
      j = self.hi.pop( )
      if not j == None:
        self.__fix( j )

  def delete_min( self ):
    m = self.min_pointer
    assert True == m.is_root()
    self.delete( m  )
    self.min_pointer = self.__scan_new_min( )
    assert(self.min_pointer.is_root())
    
    return m
        
  def delete( self, node ):
    node_is_root = node.is_root( )
    assert True == node_is_root
    bn = self.__borrow( )
    #bn = heap_node( 2 )
    self.heap_modifier.replace( node, bn  )
  
    r = bn.find_root( )
   
    miterator = self._front( )
    while miterator != None:
      riterator = miterator.south
      while riterator != None:
        if riterator.element == node:
          riterator.element = bn.find_root()
        riterator = riterator.next
      miterator = miterator.east   
      
  def __fix( self, node ):
    assert node.is_high( )
    # grow heap if necesary
    if node.east == None:
      self._grow( node )

    # Decrease sigma_j by 3
    p = node.pop( )
    q = node.pop( )
    r = node.pop( )
    o = [p, q, r]

    assert True == p.is_root()
    assert True == q.is_root()
    assert True == r.is_root()

    if o[2] < o[1]: o[2], o[1] = o[1], o[2]
    if o[1] < o[0]: o[1], o[0] = o[0], o[1]

    e = node.east
    w = None
    if not node.is_front( ):
      w = node.west
      if w.size <= 1: self.lo.pop( )
      sts = self.heap_modifier.cut_at_root( o[0] )
      assert True == o[0].is_root( )
      assert True == sts[0].is_root( )
      assert True == sts[1].is_root( )
      w.push( sts[0] )  # D[j-1] += 2  
      w.push( sts[1] )

    
    self.heap_modifier.join( o[0], o[1], o[2] )
    assert True == o[0].is_root()
    assert False ==  o[1].is_root( )
    assert False ==  o[2].is_root( )
    assert o[1].parent() is o[0]
    assert o[2].parent() is o[0]
    e.push( o[0] ) # D[j+1] += 1  
    
    if e.size == 1 and not self.lo.peak( 1 ) == e: 
      self.lo.append( e )
    elif e.size == 2: self.lo.pop( )
    elif e.size == 3: self.hi.append( e  )

    if w and w.size >= 3: self.hi.append( w )
    self.lo.append( node )
 
  def __unfix( self, node ):
    assert node.is_low( )
    e = node.east
    w = None
    
    print( "structure: " + str( self.structure( ) ) )
    p = e.pop( ) # D[j+1] -= 1
    print( "structure: " + str( self.structure( ) ) )
    print(node.size)
    heap_utils.draw_heap(p)

    sts = self.heap_modifier.cut_at_root( p )


    # shrink list
    if e.size == 0 and e.is_tail( ):
      self.lo.pop( )
      self._shrink( node )
    else:
      if e.size   == 1: self.lo.append( e )
      elif e.size == 2: self.hi.pop( )
    if not node.is_front( ):
      w = node.west
      if w.size >= 3: self.hi.pop( )
      q = node.west.pop( ) # D[j-1] -= 2
      r = node.west.pop( )
      assert True == q.is_root()
      assert True == r.is_root()
      
    


      if w.size <= 1 and not w is self._front( ):
        self.lo.append( w )
        
      self.heap_modifier.join( p, q, r )
      assert True == p.is_root()
      #self.heap_modifier.siftdown( p )
      root = p.find_root( )
    else:
      root = p
      root = p.find_root( )

    assert True == root.is_root()
    assert True == sts[0].is_root()
    assert True == sts[1].is_root()
    
    node.push( root )      # D[j] += 3
    node.push( sts[0] )
    node.push( sts[1] )

    if node.size >= 3: self.hi.append( node )
    
  def __borrow( self ):
    f = self._front( )
    if not self.__is_idle( ):
      if self.__get_state( ) == '22':
        if not self.hi.empty( ) and self.hi.peak( 1 ).size == 3:
          j = self.lo.pop( )
          if not j == None:
            self.__unfix( j )
      else:
        j = self.lo.pop( )
        if not j == None:
          self.__unfix( j  )

    bn = f.pop( )
    assert True == bn.is_root()
    if f.size == 2: self.hi.pop( )
    elif f.size <= 1 and self.lo.peak( 1 ) != f: self.lo.append( f )
    
    return bn

  def get_state( self ):
    return self.__get_state( )
    
  def is_idle( self ):
    return self.__is_idle( )

  def __get_state( self ):
    f = self._front( )
    if self.length == 1:
      return str(f.size)
    else:
      return str(f.size) + str(f.east.size)

  def __is_idle( self ):
    # idle state 21t
    if self.__get_state( ) == '21':
      return True
    elif self.__get_state( ) == '12': 
      # 12a
      if not self.hi.empty( ):
        return False
      else:
        if self.lo.size( ) == 1 or self.lo.peak( 2 ).is_tail( ):
          return True
        else:
          return False
    else:
      return False

  def __scan_new_min( self ):
    miterator = self._front( )
    min = None
    while miterator != None:
      riterator = miterator.south
      while riterator != None:
        if min == None or riterator.element < min:
          min = riterator.element
        riterator = riterator.next
      miterator = miterator.east    
    return min

if __name__ == "__main__":
  import random
  import heap_utils
  from time import process_time
  
  def get_random( ):
    return random.randint( 1, 1000000 )


  def hi_lo( list ):
    l = []
    for e in list:
      l.append( e.size )
    return l
  
  def assert_magic_heap( param = True ):
    miterator = mq.head
    s = 0
    while miterator != None:
      riterator = miterator.south
      while riterator != None:
        heap_utils.assert_heap( riterator.element, param )
        assert riterator.element.size( ) == 2**(s+1) - 1
        riterator = riterator.next
      miterator = miterator.east
      s += 1


  for k in range(0,500):
    mq = magic_queue( )
    #print( "size: " + str( mq.size( ) ) )
  
    t = process_time()
    print("---------------------------------------------------INC")
    for i in range( 0, 5000 ):
      n         = heap_node( )
      n.element = get_random( )
      mq.insert( n  )
      #assert_magic_heap( )
      #print( "size: " + str( mq.size( ) ) + " | structure: " + str( mq.structure( ) ) )
      #assert_magic_heap( )
    print( "time: " + str( process_time() - t ) )
    print( "size: " + str( mq.size( ) ) )
    print( "structure: " + str( mq.structure( ) ) )
    print( "min element: " + str( mq.find_min( ).element ))
      #print(hi_lo(mq.hi.p()))
      #print(hi_lo(mq.lo.p()))
  
    assert_magic_heap( )

    print("---------------------------------------------------DONE INC")
    print("---------------------------------------------------DEC")
    for i in range( 0, 2000 ):
      min = mq.find_min( )
      assert True == min.is_root()
      #print( "size: " + str( mq.size( ) ) + " | structure: " + str( mq.structure( ) ) )
      e = mq.delete_min( )
      #print( "size: " + str( mq.size( ) ) + " | structure: " + str( mq.structure( ) ) )
      #print(e.element)
    
    print( "size: " + str( mq.size( ) ) )
    print( "structure: " + str( mq.structure( ) ) )
    print( "min element: " + str( mq.find_min( ).element ))
    #print(hi_lo(mq.hi.p()))
    #print(hi_lo(mq.lo.p()))
  
    assert_magic_heap( False )
    print("---------------------------------------------------DONE DEC")
