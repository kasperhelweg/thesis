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
    #self.three = None
    self.hi = []
    self.lo = []
  
  def push_hi( self, node ):
    self.hi.append( node )
    #print(node)
    #if node.size == 3:
    #  self.three = node

  def push_lo( self, node ):
    self.lo.append( node )

  def pop_hi( self ):
    if len(self.hi) != 0:
      return self.hi.pop( )

  def pop_lo( self ):
    if len(self.lo) != 0:
      return self.lo.pop( )

  def find_three( self ):
    h = next((n for n in self.hi if n.size == 3), False)
    if h:
      return h

  def find_first_lo( self ):
    h = next((n for n in self.lo if n.size == 0 or n.size == 1), False)
    if h:
      return h


  def empty_hi( self ):
    return len( self.hi ) == 0

  def empty_lo( self ):
    return len( self.lo ) == 0

  def no_his( self ):
    return len(self.hi) == 0
