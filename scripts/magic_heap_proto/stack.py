class stack_node( object ):
  def __init__( self, node ):
    self.node = node
    self.next = None
  

class stack( object ):
  def __init__( self ):
    self.head = None
    self.next = None

  def push( self, node ):
    n = stack_node( node )
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

class fix_stack( object ):
  def __init__( self ):
    self.hi = stack( )
    self.lo = stack( )
  
  def push_hi( self, node ):
    self.hi.push( node )

  def push_lo( self, node ):
    self.lo.push( node )

  def pop_hi( self ):
    return self.hi.pop( )

  def pop_lo( self ):
    return self.lo.pop( )


class fix_stack_vector( object ):
  def __init__( self ):
    self.hi = []
    self.lo = []
  
  def push_hi( self, node ):
    self.hi.append( node )

  def push_lo( self, node ):
    self.lo.append( node )

  def pop_hi( self ):
    if len(self.hi) != 0:
      return self.hi.pop( )

  def pop_lo( self ):
    if len(self.lo) != 0:
      return self.lo.pop( )


