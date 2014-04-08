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

  def left_child( self ):
    if self.left:
      return self.left

  def right_child( self ):
    if self.left:
      return self.left.right

  def is_root( self ):
    return self.right == None

  def is_leaf( self ):
    return self.left == None

  def size( self ):
    lvls = 0
    n = self
    while n.left  != None:
      n = n.left
      lvls += 1
    return 2**(lvls+1) - 1

  def find_root( self ):
    n = self
    while n.right != None:
      n = n.right
    return n


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

  def __le__( self, other ):
    if not other == None:
      return self.element < other.element or self.element == other.element 
    else:
      return self.element < other or self.element == other

  def __gt__( self, other ):
    if not other == None:
      return self.element > other.element
    else:
      return self.element > other

  def __ge__( self, other ):
    if not other == None:
      return self.element > other.element or self.element == other.element 
    else:
      return self.element > other or self.element == other
