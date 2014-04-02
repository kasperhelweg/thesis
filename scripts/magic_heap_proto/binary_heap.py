#!/usr/bin/env python
class heap_node( object ):
  def __init__( self, element = None, color = 0 ):
    self.right   = None    # Right pointer
    self.left    = None    # Left pointer
    self.color   = color   # 0 is Black, 1 is White. Just a boolean bit value. Black is left. White is right.
    self.element = element # Pointer to element


  # H e a p N o d e \ P u b l i c #


  def parent( self ):
    if self.color == 0:       
      return self.right.right
    else:
      return self.right

  def left_subtree( self ):
    if self.left:
      return self.left

  def right_subtree( self ):
    if self.left:
      return self.left.right

  def is_root( self ):
    return self.parent == None


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
    lst = binary_heap( self.root.left )
    rst = binary_heap( self.root.left.right )

    self.left      = None
    lst.root.right = None
    rst.root.right = None
    lst.root.color = 0
    
    return [lst, rst]

  def replace( self ):
    pass

  def splice( self, heaps ):
    print("wrapper for splice left and right")
    pass

  def __siftup( self, node ):

    while node < node.parent:
      
    #     /         /
    #    R-        S-
    #   / \   =>  / \
    #  S - O     R - O

      if node.color == 0 and node.parent.color == 0:
        '''case 1 - left node in left subtree'''
        s = node
        o = node.right
        r = node.parent
      
        # Cut loose
        s.right = None
        o.right = None
        r.left  = s.left
      
        # Sew up
        s.left   = r
        s.right  = r.right
        o.right  = s
        s.parent = s

    #     /         /
    #    R-        S-
    #   / \   =>  / \
    #  O - S     O - R

      if node.color == 1 and node.parent.color == 0:
        '''case 2 - left node in left subtree'''
        pass



  def __siftdown( self, node ):
    pass

  def __swap( self ):
    pass

  def __splice_left( self, heap ):
    ''' Splice left subtree into heap'''
  
  def __splice_right( self, heap ):
    ''' Splice right subtree into heap'''

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
