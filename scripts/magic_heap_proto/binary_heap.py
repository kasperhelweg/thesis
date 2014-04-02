#!/usr/bin/env python
class heap_node( object ):
  def __init__( self, element, color = 0 ):
    self.right   = None    # Right pointer
    self.left    = None    # Left pointer
    self.color   = color    # 0 is Black, 1 is White. Just a boolean bit value.
    self.element = element # Pointer to element


  # H e a p N o d e \ P u b l i c #


  def parent( self ):
    if self.right == None: 
      return self
    elif self.color == 0:       
      return self.right.right
    else:
      return self.right

  def left_subtree( self ):
    if self.left:
      return self.left

  def right_subtree( self ):
    if self.left:
      return self.left.right

  def left( self ):
    return self.left

  def right( self ):
    return self.right


  # H e a p N o d e \ P r i v a t e #


  #def __eq__( self, other ):
  #  return self.element == other.element
    
  def __lt__( self, other ):
    return self.element < other.element

  def __gt__( self, other ):
    return self.element > other.element

class binary_heap( object ):
  def __init__( self, root = None ):
    self.root  = root
    self.right = None

  def add_root( self, root ):
    self.root = root

  def insert( self, element ):
    self.root = heap_node( element, 0 )

  def find_min( self ):
    return self.root

  def cut_at_root( self ):
    lst = binary_heap( self.left_subtree( ) )
    rst = binary_heap( self.right_subtree( ) )
    
    self.left      = None
    lst.root.right = None
    rst.root.right = None
    
    return [lst, rst]
    
  def splice( self, heaps ):
    print("wrapper for splice left and right")
    pass

  def __siftup( self ):
    pass

  def __siftdown( self ):
    pass

  def __splice_left( self, heap ):
    ''' Splice left subtree into heap'''
  
  def __splice_right( self, heap ):
    ''' Splice right subtree into heap'''

  # To figure out sift cases we examine self and parent
  # ex. self = black, parent = black then case LS 1
  #     self = white, parent = black then case LS 2
  # etc...

if __name__ == "__main__":
  node_root           = heap_node( "root_node", 0 )
  assert "root_node" == node_root.parent( ).element

  node_l = heap_node( "left_node", 0 )
  node_r = heap_node( "right_node", 1 )

  node_root.left = node_l
  node_l.right   = node_r
  node_r.right   = node_root

  assert "left_node"  == node_root.left_subtree( ).element
  assert "right_node" == node_root.right_subtree( ).element

  assert "root_node"  == node_root.left_subtree( ).parent( ).element
  assert "root_node"  == node_root.right_subtree( ).parent( ).element
