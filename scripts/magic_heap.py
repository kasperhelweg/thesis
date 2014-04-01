#!/usr/bin/env python
from magical_skew_list import *
from binary_heap import *

class magic_heap( object ):
  def __init__( self ):
    self.magical_skew = magical_skew_list( )
    self.high_digits  = None # high and low digits might go in the magical_skew_list.
    self.low_digits   = None
    self.state_orbit  = None # maybe convenient, maybe not.
        
    self.min_pointer  = None
        
  def find_min( self ):
    return self.min_pointer

  def insert( self, element ):
    # create empty, one element binary heap
    # insert element into heap
    new_heap = binary_heap( element )

    # insert new_heap
    front = self.magical_skew.front( )
    if not front.head or front.head.find_min( ) < new_heap.find_min( ):
      #insert at tail
      front.append( new_heap )
    else:
      #insert at front
      front.prepend( new_heap )

    # update min pointer
    if not self.min_pointer or new_heap.find_min( ) < self.min_pointer.find_min( ):
      self.min_pointer = new_heap
    
    # Update list's of digits
    # if front.size >= 3 # add to high digit list
    # if in particular state, do a fix


  def delete( self, node ):
    pass

  def delete_min( self, node ):
    pass

  def meld( self, p_queue ):
    pass

  def size( self ):
    #s = []
    #while numerical.next( ) != None:
    #  s.append += numerical.size( )
    #  numerical.next( )
      
    #return s.to_decimal
    pass
    
  def fix( self ):
    # get first high node
    # do insert
    pass

  def unfix( self ):
    pass

  def size( ):
    pass


if __name__ == "__main__":
  m_heap = magic_heap( )
  m_heap.insert( 21 )
  m_heap.insert( 11 )
  m_heap.insert( 10 )
  
  print( m_heap.min_pointer.find_min( ).element )
  
#node         = heap_node( "root" )
#heap         = linked_list( )

#print( heap.size( ) )
#print( node.parent( ).element )
