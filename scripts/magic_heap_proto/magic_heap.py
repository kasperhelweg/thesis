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
    self.high_stack = high_stack( )
    self.low_stack  = None

  ## M a g i c H e a p \ P u b l i c ##

  def find_min( self ):
    return self.min_pointer.find_min( )

  def insert( self, element ): # increment
    # create empty, one element binary heap
    # insert element into heap
    hn = heap_node( element )
    nh = binary_heap( hn )

    node = self.__front( )
    node.insert( nh )

    # update min pointer
    if not self.min_pointer or nh.find_min( ) < self.min_pointer.find_min( ):
      self.min_pointer = nh

    if node.is_high( ):
      self.high_stack.push( node )

    node_to_fix = self.high_stack.pop( )
    
    if node_to_fix:
      self.__fix( node_to_fix ) # add to high digit list

  def delete( self, node ): # decrement
    pass

  def delete_min( self, node ):
    pass

  def meld( self, p_queue ):
    pass

  def size( self ):
    s = self.numerical( )
    return self.__value_of( s )

  def numerical( self ):
    s = []
    i = self.__front( )
    while i:
      s.append( i.size )
      i = i.next
    return s


  ## M a g i c H e a p \ P r i v a t e ##

  def __front( self ):
    return self.first

  def __grow( self, node ):
    mhn          = magical_heap_node( )
    node.next    = mhn
    mhn.previous = node

  def __shrink( self, node ):
    node.previous.next = None
    node.previous      = None

  def __meld( self, node, heap ):
   pass
    
  def __slice( self ):
    ''' Slice of say two nodes instead of popping one. Usefull for fixes.'''
    pass

  def __splice( self ):
    ''' Instead of insert, splices a slice of nodes into heap list
    '''
    pass

  def __fix( self, node ):
    # get first high node
    # do insert
    # Decrease sigma_j by 3
    mh = node.pop( )
    lh = node.pop( )
    rh = node.pop( )

    if not node.is_front( ):
      lrh = mh.cut_at_root( )
    
    mh.root.left  = lh.root
    lh.root.right = rh.root
    
    # Increase sigma_j+1 by 1
    if node.next == None:
      self.__grow( node )
    node.next.insert( mh )

    if node.next.is_high( ):
      self.high_stack.push( node.next )
  
    # Increase sigma_j-1 by 2
    # node.previous.meld( )
    if not node.is_front( ):
      node.previous.insert(lrh[0] )
      node.previous.insert(lrh[1] )
      if node.previous.is_high( ):
        self.high_stack.push( node.previous )
  
  def __unfix( self ):
    pass

  def __empty( self, node ):
    return node.size == 0
   
  def __scan( self ):
    head = self.__front( ).head
    while head:
      print( head.find_min().element  )
      head = head.right

  def __value_of( self, S ):
    n = 0
    for i ,s in enumerate( S ):
      n += s * ((2**(i+1)) - 1)
    return n

if __name__ == "__main__":
  def get_random( ):
    return random.randint( 1, 100000 )

  m_heap = magic_heap( )
  print( "size: " + str( m_heap.size( ) ) )

  for i in range( 0, 50000000 ):
    m_heap.insert( get_random( ) )
    #print(str(m_heap.size()) + " : " + str( m_heap.numerical())) 
  
  print( "size: " + str( m_heap.size( ) ) )
  print( "structure: " + str( m_heap.numerical( ) ) )
  print( "min element: " + str( m_heap.find_min( ).element ) )
