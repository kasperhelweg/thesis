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

  def is_leaf( self ):
    return self.left == None


  # H e a p N o d e \ P r i v a t e #
  # ------------------------------- #


  def __eq__( self, other ):
    if not other == None:
      return self.element == other.element
    else:
      return self.element == other

  def __lt__( self, other ):
    if not other == None:
      return self.element < other.element
    else:
      return self.element < other

  def __gt__( self, other ):
    if not other == None:
      return self.element > other.element
    else:
      return self.element > other



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

  def replace( self, node, other ):
    other.left  = node.left
    other.right = node.right
    other.color = node.color

    if not other.is_root( ):
      if node.color == 1:
        node.parent( ).left = other
      else:
        node.parent( ).left.right = other

    node.left  = None
    node.right = None

    return node

  def splice( self, heaps ):
    print("wrapper for splice left and right")
    pass

  def size( self ):
    lvls = 0
    n = self.root
    
    while n.left != None:
      n = n.left
      lvls += 1

    return 2**lvls - 1
  
  # B i n a r y H e a p \ P r i v a t e #
  # ----------------------------------- #


  def siftup( self, node ):
    '''procedure __siftup. complexity is O(lg n)
      each case does: 
    3 temporary pointer variables + 2 cuts + at most 6 sews + at most 1 color-bit flip
    = at most 12 operations 
    = O(1) operations'''
  
    s = node
    p = node.parent( )
    while not s.is_root( ) and s < p:
      self.__swap( s, p)
      p = s.parent( )

    if s.is_root( ):
      self.root = s

  def siftdown( self, node ):
    '''siftup procedure. complexity is 2 O(lg n)'''
    
    s  = node
    lc = node.left_subtree( )
    rc = node.right_subtree( )

    while not s.is_leaf( ):
      if   s > lc:
        self.__swap( lc, s)
      elif s > rc:
        self.__swap( rc, s)
      else:
        break
      lc = s.left_subtree( )
      rc = s.right_subtree( )

  def __swap( self, node, other ):
    #             
    #    R           S
    #   / \   <=>   / \
    #  S - O       R - O

    if other.is_root( ) and node.color == 1:
      '''case 0 - left node, parent is root'''
      s = node
      o = node.right
      r = other
      
      # Cut out
      s.right = None
      o.right = None
      r.left  = s.left

      # Sew up
      s.left  = r
      o.right = s
      r.right = o
      self.__swap_colors( s, r ) 

    #               
    #    R           S
    #   / \   <=>   / \
    #  O - S       O - R

    elif other.is_root( ) and node.color == 0:
      '''case 0-1 - right node, parent is root'''
      s = node
      o = other.left
      r = other
      
      # Cut out 
      s.right = None
      o.right = None
      r.left  = s.left

      # Sew up
      s.left  = o
      o.right = r
      r.right = s

    #     /           /
    #    R-          S-
    #   / \   <=>   / \
    #  S - O       R - O

    elif node.color == 1 and other.color == 1:
      '''case 1 - left node in left subtree'''
      s = node
      o = node.right
      r = other
      
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

    #     /           /
    #    R-          S-
    #   / \   <=>   / \
    #  O - S       O - R

    elif node.color == 0 and other.color == 1:
      '''case 2 - right node in left subtree'''
      s = node
      o = other.left
      r = other
      
      # Cut out
      s.right = None
      o.right = None
      r.left  = s.left

      # Sew up
      s.left  = o
      s.right = r.right
      o.right = r
      r.right = s
      self.__swap_colors( s, r ) 
      if not s.is_root( ):
        s.parent( ).left = s
        
    #   \           \
    #   -R          -S
    #   / \   <=>   / \
    #  S - O       R - O

    elif node.color == 1 and other.color == 0:
      '''case 3 - left node in right subtree'''
      s = node
      o = s.right
      r = other
      
      # Cut out
      s.right = None
      o.right = None
      r.left  = s.left

      # Sew up
      s.left  = r
      s.right = r.right
      o.right = s
      r.right = o
      self.__swap_colors( s, r ) 
      if not s.is_root( ):
        s.parent( ).left.right = s
        

    #   \           \
    #   -R          -S
    #   / \   <=>   / \
    #  O - S       O - R

    elif node.color == 0 and other.color == 0:
      '''case 4 - right node in right subtree'''
      s = node
      o = other.left
      r = other
        
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
    
  def __splice_left( self, heap ):
    ''' Splice left subtree into heap'''
  
  def __splice_right( self, heap ):
    ''' Splice right subtree into heap'''

  def __swap_colors( self, node, other ):
    tmp = node.color
    node.color  = other.color
    other.color = tmp


if __name__ == "__main__":
  import random
  import heap_utils

    

  # H e a p N o d e \ T e s t #
  # ------------------------- #


  # B i n a r y H e a p \ T e s t #
  # ----------------------------- #

  #             
  #    R
  #   / \
  #  S - O
  '''siftup - case 0'''
  
  rv = random.randint( 100, 1000 )
  bh = heap_utils.build_heap( 1, rv  )  
  assert rv == bh.root.element
    
  s  = heap_utils.request_node( bh, 1, 1 )
  sp = heap_node( rv - 1, 0 ) 
  n  = bh.replace( s, sp )

  assert n.element == s.element
  bh.siftup( sp )
  
  assert sp.element == bh.root.element

  #             
  #    R
  #   / \
  #  O - S
  '''siftup - case 0-1'''
  
  rv = random.randint( 100, 1000 )
  bh = heap_utils.build_heap( 1, rv  )  
  assert rv == bh.root.element
    
  s  = heap_utils.request_node( bh, 2, 1 )
  sp = heap_node( rv - 1, 0 ) 
  n  = bh.replace( s, sp )

  assert n.element == s.element
  bh.siftup( sp )
  
  assert sp.element == bh.root.element

  #     /       
  #    R-
  #   / \
  #  S - O
  '''siftup - case 1 '''
 
  rv = random.randint( 100, 1000 )
  bh = heap_utils.build_heap( 2, rv  )  
  assert rv == bh.root.element
    
  s  = heap_utils.request_node( bh, 1, 2 )
  sp = heap_node( rv - 1, 0 ) 
  n  = bh.replace( s, sp )

  assert n.element == s.element
  bh.siftup( sp )
  
  assert sp.element == bh.root.element

  
  #     /       
  #    R-
  #   / \
  #  O - S
  '''siftup - case 2 '''
 
  rv = random.randint( 100, 1000 )
  bh = heap_utils.build_heap( 2, rv  )  
  assert rv == bh.root.element
    
  s  = heap_utils.request_node( bh, 2, 2 )
  sp = heap_node( rv - 1, 0 ) 
  n  = bh.replace( s, sp )

  assert n.element == s.element
  bh.siftup( sp )
  
  assert sp.element == bh.root.element
 

  '''siftup - random''' 
  for i in range(0, 1000 ):
    rv    = random.randint( 10, 1000 )
    lvels = random.randint( 1, 12 )

    bh         = heap_utils.build_heap( lvels, rv  )  
    assert rv == bh.root.element
    
    s  = heap_utils.request_random_node( bh, lvels )
    sp = heap_node( rv - 1, 0 ) 
    n  = bh.replace( s, sp )

    assert n.element == s.element
    bh.siftup( sp )
  
    assert sp.element == bh.root.element
    
  '''siftdown'''
  lvls = 12
  rv   = 0
  bh   = heap_utils.build_heap( lvls, rv, False  )  
  assert rv == bh.root.element
    
  s  = heap_utils.request_node( bh, 1, 0 )
  sp = heap_node( lvls + 1, 0 ) 
  n  = bh.replace( s, sp )

  assert n.element == s.element
  assert True == sp.is_root( )
  
  bh.siftdown( sp )
  
  assert True == sp.is_leaf( )


  '''siftdown - random'''
  for i in range(0, 1000 ):
    rv    = 0
    lvels = random.randint( 1, 12 )

    bh         = heap_utils.build_heap( lvels, rv, False  )  
    assert rv == bh.root.element
    
    s  = heap_utils.request_random_node( bh, lvels )
    sp = heap_node( lvels + 1, 0 ) 
    n  = bh.replace( s, sp )

    assert n.element == s.element
    #assert True == sp.is_root( )
  
    bh.siftdown( sp )
  
    assert True == sp.is_leaf( )
