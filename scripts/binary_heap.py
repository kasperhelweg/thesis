#!/usr/bin/env python
class heap_node( object ):
  def __init__( self, element, color ):
    self.color   = None # 0 is Black, 1 is White. Just a boolean bit value.
    self.right   = None # Right pointer
    self.left    = None # Left pointer
    self.element = element # Pointer to element

  def __eq__( self, other ):
    return self.element == other.element
    
  def __lt__( self, other ):
    return self.element < other.element

  def __gt__( self, other ):
    return self.element > other.element

  def parent( self ):
    if self.root( ): 
      return self
    elif self.color == 0: 
      return self.right.right
    elif self.color == 1: 
      return self.right

  def left_child( self ):
    if self.left:
      return self.left

  def right_child( self ):
    if self.left:
      return self.left.right

  def right( self ):
    return self.right

  def left( self ):
    return self.left

  def root( self ):
    return self.right == None or self.right.color == 0


class binary_heap( object ):
  def __init__( self, element ):
    # new black root node
    self.root = heap_node( element, 0 )
    
  def find_min( self ):
    return self.root

  def siftup( self ):
    pass

  def siftdown( self ):
    pass

  # To figure out sift cases we examine self and parent
  # ex. self = black, parent = black then case LS 1
  #     self = white, parent = black then case LS 2
  # etc...

if __name__ == "__main__":
  node_root          = heap_node( )
  node_root.element  = "root node"
  assert "root node" == node_root.parent( ).element

  node_l         = heap_node( )
  node_l.element = "left node"
  node_l.color   = 0
  
  node_r         = heap_node( )
  node_r.element = "right node"
  node_r.color   = 1

  node_root.left = node_l
  node_l.right   = node_r
  node_r.right   = node_root

  assert "left node"  == node_root.left_child( ).element
  assert "right node" == node_root.right_child( ).element

  assert "root node"  == node_root.left_child( ).parent( ).element
  assert "root node"  == node_root.right_child( ).parent( ).element
