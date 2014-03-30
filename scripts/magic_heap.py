class heap_node( object ):
  def __init__( self ):
    self.color   = None # 0 is Black, 1 is White
    self.right   = None # Right pointer
    self.left    = None # Left pointer
    self.element = None # Pointer to element

  def parent( self ):
    if self.right == None:
      return self
    elif self.color == 0:#Black
      return self.right.right
    elif self.color == 1:#White
      return self.right

  def left_child( self ):
    if self.left != None:
      return self.left

  def right_child( self ):
    if self.left != None:
      return self.left.right

  def right( self ):
    return self.right

  def left( self ):
    return self.left

  def root( self ):
    return self.right == None


    # To figure out sift cases we examine self and parent
    # ex. self = black, parent = black then case LS 1
    #     self = white, parent = black then case LS 2
    # etc...

node_root         = heap_node( )
node_root.element = "root node"

node_l         = heap_node( )
node_l.element = "left node"
node_l.color   = 0

node_r         = heap_node( )
node_r.element = "right node"
node_r.color   = 1

node_root.left = node_l
node_l.right   = node_r
node_r.right   = node_root

print( "--Program heap_node--" )
