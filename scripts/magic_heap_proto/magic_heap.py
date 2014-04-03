#!/usr/bin/env python
import random
from binary_heap import *
from high_low_stack import *

class magical_heap_node( object ):
  def __init__( self ):
    self.next     = None
    self.previous = None
    
    self.head = None
    self.tail = None
    
    self.size = 0

  def insert( self, node ):
    if not self.head or self.head.find_min( ) < node.find_min( ):
      #insert at tail
      if not self.tail:
        self.head = node
        self.tail = node
      else:
        self.tail.right = node
        self.tail       = node
    else:
      #insert at front
      node.right = self.head 
      self.head  = node
      
    self.size += 1

  def pop( self ):
    t       = self.head.right
    e       = self.head
    e.right = None
    
    self.size -= 1
    self.head  = t

    if self.size == 0:
      self.tail = self.head
    return e

  def meld( self, other ):
    pass
    
  def is_front( self  ):
    return self.previous == None
    
  def is_high( self ):
    return self.size == 3

class magic_heap( object ):
  def __init__( self ):
    self.first = magical_heap_node( )

    self.min_pointer = None
    self.high_stack  = high_stack( ) # Hi and Lo digits
    self.statebit    = 0

  ## M a g i c H e a p \ P u b l i c ##


  def find_min( self ):
    return self.min_pointer.find_min( )

  def buy_node( self ):
    return heap_node( )

  def insert( self, node ): # increment
    #print( self.__get_state( ) )
    # new, single node b heap
    #hn = heap_node( element )
    nh = binary_heap( node )

    # insert new node at front.
    node = self.__front( )
    node.insert( nh )

    # update min pointer
    if not self.min_pointer or nh.find_min( ) < self.min_pointer.find_min( ):
      self.min_pointer = nh

    # fix
    if node.is_high( ):
      self.__fix( node )
    else:
      node_to_fix = self.high_stack.pop( )    
      if node_to_fix:
        self.__fix( node_to_fix ) 

  def delete( self, node ): # decrement
    
    pass

  def delete_min( self, node ):
    pass

  def meld( self, mheap ):
    pass

  def size( self ):
    s = self.__numerical( )
    return self.__value_of( s )

  def list( self ):
    return self.__numerical( )


  ## M a g i c H e a p \ P r i v a t e ##
  
  def __get_state( self ):
    #f = self.__front( ).head.size( )
    #s = self.__front( ).next.head.size( )
    #return str( f ) + str( s )
    pass

  def __front( self ):
    '''Return front node of the magic-heap'''
    return self.first

  def __grow( self, node ):
    '''Given a pointer to a node, this function grows the magic-heap by one'''
    mhn          = magical_heap_node( )
    node.next    = mhn
    mhn.previous = node

  def __shrink( self, node ):
    '''Given a pointer to a node, this function shrinks the magic-heap by one'''
    node.previous.next = None
    node.previous      = None

  def __meld( self, mheap ):
    '''Given a second magic-heap, this function melds the two'''
    pass
    
  def __fix( self, node ):
    # Decrease sigma_j by 3
    mh = node.pop( )
    lh = node.pop( )
    rh = node.pop( )

    # Rearrange
    if not node.is_front( ):
      lrh = mh.cut_at_root( )
    mh.root.left  = lh.root
    lh.root.right = rh.root
    
    # grow heap if necesary
    if node.next == None:
      self.__grow( node )
    
    # increase sigma_j+1 by 1
    node.next.insert( mh )
    if node.next.is_high( ):
      self.high_stack.push( node.next )
  
    # increase sigma_j-1 by 2
    if not node.is_front( ):
      node.previous.insert( lrh[0] )
      node.previous.insert( lrh[1] )
      if node.previous.is_high( ):
        self.high_stack.push( node.previous  )
  
  def __unfix( self, node ):
    if not node.is_front( ):
      
      pass
    pass

  def __scan( self ):
    head = self.__front( ).head
    while head:
      print( head.find_min( ).element  )
      head = head.right

  def __empty( self, node ):
    return node.size == 0

  def __value_of( self, S ):
    n = 0
    for i ,s in enumerate( S ):
      n += s * ((2**(i+1)) - 1)
    return n

  def __numerical( self ):
    s = []
    i = self.__front( )
    while i:
      s.append( i.size )
      i = i.next
    return s


if __name__ == "__main__":
  def get_random( ):
    return random.randint( 1, 100000 )

  m_heap = magic_heap( )
  print( "size: " + str( m_heap.size( ) ) )

  for i in range( 0, 100000 ):
    node         = m_heap.buy_node( )
    node.element = get_random( )
    m_heap.insert( node  )
    #print(str(m_heap.size()) + " : " + str( m_heap.numerical())) 
  
  print( "size: " + str( m_heap.size( ) ) )
  print( "structure: " + str( m_heap.list( ) ) )
  print( "min element: " + str( m_heap.find_min( ).element ) )
