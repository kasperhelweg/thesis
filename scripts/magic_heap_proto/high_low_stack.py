class h_stack_node( object ):
  def __init__( self, node ):
    self.node = node
    self.next = None
  

class high_stack( object ):
  def __init__( self ):
    self.head = None
    self.next = None

  def push( self, node ):
    n = h_stack_node( node )
    if not self.head:
      self.head = n
    else:
      n.next    = self.head
      self.head = n
    
  def pop( self ):
    if self.head:
      t          = self.head.next
      e          = self.head
      e.right    = None
      self.head  = t
      return e.node
