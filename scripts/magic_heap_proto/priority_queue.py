from magic_heap import *

class priority_queue( object ):
  def __init__( self, R ):
    self.realization = R
      
  def find_min( self ):
    self.realization.find_min( )

  def insert( self, element ):
    self.realization.insert( element )

  def delete( self, node ):
    pass

  def delete_min( self, node ):
    pass

  def meld( self, p_queue ):
    pass


if __name__ == "__main__":
  R     = magic_heap( )
  queue = priority_queue( R )
