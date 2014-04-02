#!/usr/bin/env python
from binary_heap import *

class magical_heap_node( object ):
  def __init__( self ):
    self.east  = None
    self.west  = None
    
    self.head = None
    self.tail = None
    
    self.size = 0

class magic_heap( object ):
  def __init__( self ):
    self.first = magical_heap_node( )
    
    self.high_digits = None # high and low digits might go in the magical_skew_list.
    self.low_digits  = None
    self.state_orbit = None # maybe convenient, maybe not.
        
    self.min_pointer = None

  #********************************************************************#
  #                                                                    #
  #                  M a g i c H e a p \ P u b l i c                   #
  #                                                                    #
  #********************************************************************#

  def find_min( self ):
    return self.min_pointer

  def insert( self, element ): # increment
    # create empty, one element binary heap
    # insert element into heap
    new_heap = binary_heap( )
    new_heap.insert( element )
    
    node = self.__front( )
    self.__meld( node, new_heap )
    
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
      i = i.east
    return self.__value_of( s )

  #********************************************************************#
  #                                                                    #
  #                 M a g i c H e a p \ P r i v a t e                  #
  #                                                                    #
  #********************************************************************#

  def __front( self ):
    return self.first

  def __grow( self ):
    pass

  def __shrink( self ):
    pass

  def __meld( self, node, heap ):
    ''' 
    '''
    if not node.head or node.head.find_min( ) < heap.find_min( ):
      #insert at tail
      if not node.tail:
        node.head = heap
        node.tail = heap
      else:
        node.tail.right = heap
        node.tail       = heap
    else:
      #insert at front
      heap.right = node.head 
      node.head  = heap
    
    node.size += 1

    # update min pointer
    if not self.min_pointer or heap.find_min( ) < self.min_pointer.find_min( ):
      self.min_pointer = heap

  def __pop ( self, node ):
    e         = node.head
    node.head = node.head.right 
    e.right   = None
    
    return e
    
  def __slice:
    ''' Slice of say two nodes instead of popping one. Usefull for fixes.
    '''
    pass

  def __splice:
    ''' Instead of insert, splices a slice of nodes into heap list
    '''
    pass

  def __fix( self, node ):
    # get first high node
    # do insert
    
    #min    = self.__pop( node )
    #lchild = self.__pop( node )
    #rchild = self.__pop( node )
    
    #new_heap_l = binary_heap( )
    #new_heap_r = binary_heap( )

    #new_heap_r.add_root( min.split_left( ) )
    #new_heap_l.add_root( min.split_right( ) )
  
    #min.add_left( lchild )
    #min.add_right( rchild )

    #self.__add( node.east, min  )
    #self.__add( node,west, new_heap_l  )
    #self.__add( node,west, new_heap_r  )
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
  m_heap.insert( 21 )
  m_heap.insert( 11 )
  m_heap.insert( 10 )
  
  #print( m_heap.size( ) )
  #print( m_heap.min_pointer.find_min( ).element )
  #m_heap.scan( )

#node         = heap_node( "root" )
#heap         = linked_list( )

#print( heap.size( ) )
#print( node.parent( ).element )
