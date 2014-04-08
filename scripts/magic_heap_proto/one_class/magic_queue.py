from binary_queue import binary_queue
from heap_node import heap_node
from stack import *
import heap_utils


class magic_queue( binary_queue ):
  def __init__( self ):
    super( ).__init__( )
    self.fix_stack = fix_stack_vector( ) # Hi and Lo digits

  # overrides insert
  def insert( self, n ): # increment
    # insert new node at front.
    f = self._front( )
    f.push( n )

    # update min pointer
    if not self.min_pointer or n < self.min_pointer:
      self.min_pointer = n
    
    # fix
    if f.is_high( ) and not f.marked_for_fix:
      self.__fix( f )
    else :
      node_to_fix = self.fix_stack.pop_hi( )    
      if node_to_fix:
        node_to_fix.marked_for_fix = False
        self.__fix( node_to_fix )

  def delete_min( self ):
    m = self.min_pointer
    self.delete( m  )
    self.min_pointer = self.__scan_new_min( )

    return m
        
  def delete( self, node ):
    bn = self.__borrow( )
    self.heap_modifier.replace( node, bn  )

    r = bn.find_root( )
    if not r == node:
      miterator = self._front( )
      while miterator != None:
        riterator = miterator.south
        while riterator != None:
          if riterator.element == node:
            riterator.element = r
          riterator = riterator.next
        miterator = miterator.east   

  def __fix( self, node ):
    
    if not node.is_high( ):
      return

    # grow heap if necesary
    if node.east == None:
      self._grow( node )

    # Decrease sigma_j by 3
    p = node.pop( )
    q = node.pop( )
    r = node.pop( )
    if node.is_low( ) and not node.marked_for_unfix:
      node.marked_for_unfix = True
      self.fix_stack.push_lo( node )
    
    # increase sigma_j+1 by 1
    s = node.east

    if p < q:
      if p < r:
        if not node.is_front( ):
          sts = self.heap_modifier.cut_at_root( p )
        self.heap_modifier.join( p, q, r )
        s.push( p )
      else:
        if not node.is_front( ):
          sts = self.heap_modifier.cut_at_root( r )
        self.heap_modifier.join( r, p, q )
        s.push( r )
    elif q < r:
        if not node.is_front( ):
          sts = self.heap_modifier.cut_at_root( q )
        self.heap_modifier.join( q, r, p )
        s.push( q )
    else:
        if not node.is_front( ):
          sts = self.heap_modifier.cut_at_root( r )
        self.heap_modifier.join( r, p, q )
        s.push( r )

    if s.is_high( ) and not s.marked_for_fix:
      s.marked_for_fix = True
      self.fix_stack.push_hi( s )
    elif s.is_low( ) and not s.marked_for_unfix:
      s.marked_for_unfix = True
      self.fix_stack.push_lo( s )

    # increase sigma_j-1 by 2
    if not node.is_front( ):
      s = node.west
      s.push( sts[0] )
      s.push( sts[1] )
      if s.is_high( ) and not s.marked_for_fix:
        s.marked_for_fix = True
        self.fix_stack.push_hi( s  )

  def __unfix( self, node ):
    if not node.is_low( ):
      return
            
    if not node.is_front( ):
      p = node.east.pop( )
      q = node.west.pop( )
      r = node.west.pop( )
            
      sts = self.heap_modifier.cut_at_root( p )
      self.heap_modifier.join( p, q, r )
      self.heap_modifier.siftdown( p )

      root = p.find_root( )
      node.push( root )
      
      node.push( sts[0] )
      node.push( sts[1] )

      if node.east.is_low( ) and not node.east.marked_for_unfix:
        node.east.marked_for_unfix = True
        self.fix_stack.push_lo( node.east )

      if node.west.is_low( ) and not node.west.marked_for_unfix:
        node.west.marked_for_unfix = True
        self.fix_stack.push_lo( node.west )
    else:
      p   = node.east.pop( )
      sts = self.heap_modifier.cut_at_root( p )

      node.push( p )
      node.push( sts[0] )
      node.push( sts[1] )

      if node.east.is_low( ) and not node.east.marked_for_unfix:
        node.east.marked_for_unfix = True
        self.fix_stack.push_lo( node.east )

    # shrink
    if node.east.empty( ) and node.east.is_tail( ):
      self._shrink( node )
   
  def __borrow( self ):
    print(self.fix_stack.lo)
    node_to_unfix = None    
    if not self.__is_in_idle_state( ):   # if not 12t / 21t
      if self.__get_state( ) == 22: # if 22b
        three = self.__find_three( )
        if three:
          node_to_unfix = self.fix_stack.pop_lo( )
          node_to_unfix.marked_for_unfix = False
      else:
        if not len(self.fix_stack.lo) == 0:
          node_to_unfix = self.fix_stack.lo.pop( )
          node_to_unfix.marked_for_unfix = False
        else:
          node_to_unfix =  self.__find_first_lo( )
          node_to_unfix.marked_for_unfix = False

      if node_to_unfix:
        self.__unfix( node_to_unfix )

    bn = self._front( ).pop( )
    if self._front( ).is_low( ) and not self._front().marked_for_unfix:
      self._front().marked_for_unfix = True
      self.fix_stack.push_lo( self._front() )
    
    return bn

  def __is_in_idle_state( self ):
    if self.__get_state( ) == 21:
      return True
    elif self.__get_state( ) == 12:
      if len(self.fix_stack.lo) == 1 or self.fix_stack.lo[1].is_tail( ):
        print(self.fix_stack.lo)
        return True
      if self.__find_hi( ):
        return False
    else :
      return False
 
  def __get_state( self ):
    f = self._front( )
    return int(str(f.size) + str(f.east.size))

  def __find_tail( self ):
    miterator = self._front( )
    while miterator.east != None:
      miterator = miterator.east
    return miterator

  def __find_first_lo( self ):
    miterator = self._front( )
    while miterator.east != None:
      if miterator.size == 0 or miterator.size == 1:
        return miterator
      miterator = miterator.east
    return None


  def __find_three( self ):
    miterator = self._front( )
    while miterator.east != None:
      if miterator.size == 3:
        return miterator
      miterator = miterator.east
    return None

  def __find_hi( self ):
    miterator = self._front( )
    while miterator.east != None:
      if miterator.size >= 3:
        return miterator
      miterator = miterator.east
    return None

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

  def assert_magic_heap( ):
    miterator = mq.head
    s = 0
    while miterator != None:
      riterator = miterator.south
      while riterator != None:
        heap_utils.assert_heap( riterator.element )
        assert riterator.element.size( ) == 2**(s+1) - 1
        riterator = riterator.next
      miterator = miterator.east
      s += 1

  mq = magic_queue( )
  print( "size: " + str( mq.size( ) ) )
  
  t = process_time()
  for i in range( 0, 1000000 ):
    n         = heap_node( )
    n.element = get_random( )
    
    mq.insert( n  )
    #print( "structure: " + str( mq.structure( ) ) )
    #print( "size: " + str( mq.size( ) ) )
    #print(mq.fix_stack.lo)
    #print( "statebit: " + str( mq.state_bit ) )
    #print(mq.fix_stack.hi)

  print( "time: " + str( process_time() - t ) )
  print( "size: " + str( mq.size( ) ) )
  print( "structure: " + str( mq.structure( ) ) )
  print( "min element: " + str( mq.find_min( ).element ))
  #print(mq.fix_stack.hi)
  assert_magic_heap( )
  print("---------------------------------------------------")
  
  '''
  for i in range( 0, 10 ):
    min = mq.find_min( )
    e   = mq.delete_min( )
    print( "structure: " + str( mq.structure( ) ) )
    #print( "size: " + str( mq.size( ) ) )
    assert_magic_heap( )
  '''
    #print( "structure: " + str( mq.structure( ) ) )
    #print(mq.fix_stack.lo)
    #for n in mq.fix_stack.lo:
    #  print(n.size)
    
    #assert e is min
    
  #min = mq.find_min( )
  
  #assert e is min
  #print( "structure: " + str( mq.structure( ) ) )
  #print(e.element)

  #min = mq.find_min( )
  #e   = mq.delete_min( )
  #print(e.element)

  #assert e is min
  #print( "structure: " + str( mq.structure( ) ) )
    
  #assert_magic_heap( )
