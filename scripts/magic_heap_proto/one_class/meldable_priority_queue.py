class meldable_priority_queue( object ):
  def __init__( self ):
    
    # types
    self.realization = None

    # iterators
    self.begin = None
    self.end   = None
    
  # capacity 
  # bool
  def empty( self ):
    self.realization.empty( )

  # bool
  def size( self ):
    self.realization.size( )

  # access

  def top( self ):
    self.realization.top( )
    
  # modifiers

  def push( self, node ):
    self.realization.push( )

  def pop( self ):
    self.realization.pop( )
  
  def erase( self, node ):
    self.realization.erase( )

  def swap( self, node, other ):
    self.realization.swap( )

  def clear( self ):
    self.realization.clear( )

  def meld( self ):
    self.realization.meld( )





