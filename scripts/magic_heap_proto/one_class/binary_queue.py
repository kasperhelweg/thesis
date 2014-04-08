from heap_node import heap_node
from heap_modifier import heap_modifier
from binary_queue_node import binary_queue_node

class binary_queue( object ):

  def __init__( self ):
    self.head          = binary_queue_node( )
    self.min_pointer   = None    
    self.heap_modifier = heap_modifier( ) 
    #self.size       = 0    #useful for constant time size()

    self.digits = 0

  # \\ capacity 

  # bool
  def size( self ):
    s = self._numerical( )
    return self._value_of( s )
  
  def empty( self ):
    return self.size( ) == 0

  # list
  def structure( self ):
    return self._numerical( )


  # \\ access

  # heap_node
  def find_min( self ):
    return self.min_pointer

  def top( self ):
    return self.find_min( )
    
  # \\ modifiers
  def insert( self, n ):
    pass

  def push( self, node ):
    self.insert( node )

  def delete( self, node ):
    pass

  def pop( self ):
    pass
  
  def erase( self, node ):
    pass

  def swap( self, node, other ):
    pass

  def clear( self ):
    pass

  def meld( self ):
    pass



  # B i n a r y Q u e u e \ P r i v a t e #
  # ------------------------------------- #

  def _front( self ):
    '''Return front node of the binary queue'''
    return self.head
    
  def _grow( self, n ):
    '''Given a pointer to a (binary_queue_)node, this function grows the queue by one'''
    bqn      = binary_queue_node( )
    n.east   = bqn
    bqn.west = n

    self.digits += 1

  def _shrink( self, node ):
    node.east.west = None
    node.east      = None

    self.digits -= 1

  def _empty( self, node ):
    return self.size == 0

  def _value_of( self, S ):
    v = 0
    for i ,s in enumerate( S ):
      v += s * ((2**(i+1)) - 1)
    return v

  def _numerical( self ):
    s = []
    i = self._front( )
    while i:
      s.append( i.size )
      i = i.east
    return s

  def _borrow( self ):
    pass
