from root_list_node import root_list_node

class binary_queue_node( object ):
  def __init__( self ):
    self.east  = None # pointer to next compartment
    self.west  = None # pointer to previous compartment    
    self.south = None # pointer to root list for this compartment
        
    self.size  = 0 # size of list
    
  def push( self, n ):
    ''' pushes a heap node onto root_node_list '''
    rln        = root_list_node( n ) # create new root list node pointing to n
    rln.next   = self.south 
    self.south = rln
    
    self.size += 1

  def pop( self ):
    ''' pops a root node and returns a pointer to the heap root stored '''
    rln        = self.south
    self.south = rln.next
    rln.next   = None
    
    self.size -= 1
    return rln.element # return pointer / deallocate node
    
  def is_front( self  ):
    return self.west == None

  def is_tail( self ):
    return self.east == None
 
  def is_high( self ):
    return self.size >= 3

  def is_low( self ):
    return self.size <= 1

  def empty( self ):
    return self.size == 0
