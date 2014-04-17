class list_node( object ):
  def __init__( self ):
    self.next    = None
    self.element = None

class linked_list( object ):
  def __init__( self ):
    self.head = None

  def append( self, element ):
    n          = list_node( )
    n. element = element
    n.next     = self.head
    self.head  = n

  def pop( self ):
    n = self.head
    if n:
      self.head = n.next
      n.next = None
    
      return n.element

  def peak( self, index ):
    if self.head:
      h = self.head
      while index != 1 and h != None:
        h = h.next
        index -= 1
      return h.element

  def empty( self ):
    return self.head == None

  def size( self ):
    s = 0
    n = self.head
    while n != None:
      s += 1
      n = n.next
    return s

  def p( self ):
    l = []
    n = self.head
    while not n == None:
      l.append(n.element)
      n = n.next
    return l
