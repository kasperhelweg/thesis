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
    '''procedure __siftup. complexity is O(lg n)
    
    each case does: 
    3 temporary pointer variables + 2 cuts + at most 6 sews + at most 1 color-bit flip
    = at most 12 operations 
    = O(1) operations'''
    while not node.is_root( ) and node < node.parent( ):

    #             
    #    R         S
    #   / \   =>  / \
    #  S - O     R - O

      if node.parent( ).is_root( ) and node.color == 1:
        '''case 0 - left node, parent is root'''
        s = node
        o = node.right
        r = node.parent( )
      
        # Cut out
        s.right = None
        o.right = None
        r.left  = s.left

        # Sew up
        s.left  = r
        o.right = s
        r.right = o

        s.color = 0

    #               
    #    R         S
    #   / \   =>  / \
    #  O - S     O - R

      elif node.parent( ).is_root( ) and node.color == 0:
        '''case 0-1 - right node, parent is root'''
        s = node
        o = node.parent( ).left
        r = node.parent( )
      
        # Cut out 
        s.right = None
        o.right = None
        r.left  = s.left

        # Sew up
        s.left  = o
        o.right = r
        r.right = s

    #     /         /
    #    R-        S-
    #   / \   =>  / \
    #  S - O     R - O

      elif node.color == 1 and node.parent( ).color == 1:
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

      elif node.color == 0 and node.parent( ).color == 1:
        '''case 2 - right node in left subtree'''
        s = node
        o = node.parent( ).left
        r = node.parent( )
      
        # Cut out
        s.right = None
        o.right = None
        r.left  = s.left

        # Sew up
        s.left  = o
        s.right = r.right
        o.right = r
        r.right = s
        if not s.is_root( ):
          s.parent( ).left = s
          s.color = 1

    #   \         \
    #   -R        -S
    #   / \   =>  / \
    #  S - O     R - O

      elif node.color == 1 and node.parent( ).color == 0:
        '''case 3 - left node in right subtree'''
        s = node
        o = s.right
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
          s.parent( ).left.right = s
          s.color = 0

    #   \         \
    #   -R        -S
    #   / \   =>  / \
    #  O - S     O - R

      elif node.color == 0 and node.parent( ).color == 0:
        '''case 4 - right node in right subtree'''
        s = node
        o = node.parent( ).left
        r = node.parent( )
        
        # Cut out
        s.right = None
        o.right = None
        r.left  = s.left

        # Sew up
        s.left  = o
        s.right = r.right
        o.right = r
        r.right = s
        if not s.is_root( ):
          s.parent( ).left.right = s
          
    if s.is_root( ):
      self.root = s

  def __siftdown( self, node ):
    '''siftup procedure. complexity is 2 O(lg n)'''
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


  # B i n a r y H e a p \ T e s t #
  # ----------------------------- #

  #             
  #    R
  #   / \
  #  S - O
  '''siftup - case 0'''

  r = heap_node( 4 , 0 )
  assert True == r.is_root( )

  s = heap_node( 3, 1 )
  o = heap_node( 6, 0 )

  r.left  = s
  s.right = o
  o.right = r
  
  assert 3 == r.left_subtree( ).element
  assert 6 == r.right_subtree( ).element
  assert 4 == r.left_subtree( ).parent( ).element
  assert 4 == r.right_subtree( ).parent( ).element

  bh = binary_heap( r )

  assert 3 != bh.root.element
  bh.siftup( s )
  assert 3 == bh.root.element

  #             
  #    R
  #   / \
  #  O - S
  '''siftup - case 0-1'''

  r = heap_node( 4 , 0 )
  assert True == r.is_root( )

  s = heap_node( 3, 0 )
  o = heap_node( 6, 1 )

  r.left  = o
  s.right = r
  o.right = s

  bh = binary_heap( r )
  
  assert 3 != bh.root.element
  bh.siftup( s )
  assert 3 == bh.root.element


  #     /       
  #    R-
  #   / \
  #  O - S
  '''siftup - case 2 '''

  r = heap_node( 5 , 1 )
  assert True == r.is_root( )

  s = heap_node( 1, 0 )
  o = heap_node( 6, 1 )

  r.left  = o
  s.right = r
  o.right = s

  r.right            = heap_node( 5, 0 )
  r.right.right      = heap_node( 4, 0 )
  r.right.right.left = r
  
  bh = binary_heap( r.right.right )
  
  assert 1 != bh.root.element
  bh.siftup( s )
  assert 1 == bh.root.element
