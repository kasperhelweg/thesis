#!/usr/bin/env python
class heap_node( object ):
  def __init__( self, element = None, color = 0 ):
    self.right   = None    # Right pointer
    self.left    = None    # Left pointer
    self.color   = color   # 0 is Black, 1 is White. White is left. Black is right.
    self.element = element # Pointer to element


  # H e a p N o d e \ P u b l i c #
  # ----------------------------- #

  def parent( self ):
    if not self.is_root( ):
      if self.color == 0: 
        return self.right
      else:
        return self.right.right

    return None
  
  def left_subtree( self ):
    if self.left:
      return self.left

  def right_subtree( self ):
    if self.left:
      return self.left.right

  def is_root( self ):
    return self.right == None


  # H e a p N o d e \ P r i v a t e #
  # ------------------------------- #

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

  # B i n a r y H e a p \ P u b l i c #
  # --------------------------------- #


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

  # B i n a r y H e a p \ P r i v a t e #
  # ----------------------------------- #


  def siftup( self, node ):
    while not node.is_root( ) and node < node.parent( ):
      
    #     /         /
    #    R-        S-
    #   / \   =>  / \
    #  S - O     R - O

      if node.color == 1 and node.parent( ).color == 1:
        '''case 1 - left node in left subtree'''
        s = node
        o = node.right
        r = node.parent( )
      
        # Cut out
        s.right = None
        o.right = None
        r.left  = s.left
      
        # Sew up
        s.left  = r
        s.right = r.right
        o.right = s
        r.right = o
        if not s.is_root( ):
          s.parent( ).left = s


    #     /         /
    #    R-        S-
    #   / \   =>  / \
    #  O - S     O - R

      if node.color == 0 and node.parent( ).color == 1:
        '''case 2 - right node in left subtree'''
        pass

    #   \         \
    #   -R        -S
    #   / \   =>  / \
    #  S - O     R - O

      if node.color == 1 and node.parent( ).color == 0:
        '''case 3 - left node in right subtree'''
        pass

    #   \         \
    #   -R        -S
    #   / \   =>  / \
    #  O - S     O - R

      if node.color == 0 and node.parent( ).color == 0:
        '''case 4 - right node in right subtree'''
        pass



    if s.is_root( ):
      self.root = s


  def __siftdown( self, node ):
    pass

  def __swap( self ):
    pass

  def __splice_left( self, heap ):
    ''' Splice left subtree into heap'''
  
  def __splice_right( self, heap ):
    ''' Splice right subtree into heap'''

if __name__ == "__main__":

  # H e a p N o d e \ T e s t #
  # ------------------------- #

  node_root    = heap_node( 4 , 0 )
  assert None == node_root.parent( )

  node_l = heap_node( 3, 1 )
  node_r = heap_node( 6, 0 )

  node_root.left = node_l
  node_l.right   = node_r
  node_r.right   = node_root

  assert 3 == node_root.left_subtree( ).element
  assert 6 == node_root.right_subtree( ).element

  assert 4 == node_root.left_subtree( ).parent( ).element
  assert 4 == node_root.right_subtree( ).parent( ).element

    
  # B i n a r y H e a p \ T e s t #
  # ----------------------------- #

  bh = binary_heap( node_root )
  
  assert 3 != bh.root.element
  bh.siftup( node_l )
  assert 3 == bh.root.element
