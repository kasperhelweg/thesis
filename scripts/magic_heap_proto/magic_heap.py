#!/usr/bin/env python
from binary_heap import *

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
    e          = self.head
    self.head  = self.head.right 
    e.right    = None
    self.size -= 1
    
    if self.size == 0:
      self.tail = self.head

    return e

  def meld( self, other ):
    pass
    
  def is_front( self  ):
    return self.previous == None


class magic_heap( object ):
  def __init__( self ):
    self.first = magical_heap_node( )
    
    self.high_digits = None # high and low digits might go in the magical_skew_list.
    self.low_digits  = None
    self.state_orbit = None # maybe convenient, maybe not.
        
    self.min_pointer = None


  # M a g i c H e a p \ P u b l i c #


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

    # Update list's of digits
    if node.size >= 3:
      self.__fix( node ) # add to high digit list
    # if in particular state, do a fix

  def delete( self, node ): # decrement
    pass

  def delete_min( self, node ):
    pass

  def meld( self, p_queue ):
    pass

  def size( self ):
    s = []
    i = self.__front( )
    while i:
      s.append( i.size )
      i = i.next
    return self.__value_of( s )


  # M a g i c H e a p \ P r i v a t e #

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
    
    # Increase sigma_j-1 by 2
    # node.previous.meld( )
    pass

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
  m_heap = magic_heap( )
  
  print( m_heap.size( ) )
  m_heap.insert( 21 )
  m_heap.insert( 11 )
  m_heap.insert( 10 )
  print( m_heap.size( ) )
  m_heap.insert( 2 )
  m_heap.insert( 8 )
  m_heap.insert( 7 )
  print( m_heap.size( ) )

  #print( m_heap.min_pointer.find_min( ).element )
  #m_heap.scan( )

#node         = heap_node( "root" )
#heap         = linked_list( )

#print( heap.size( ) )
#print( node.parent( ).element )
