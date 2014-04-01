class magical_skew_node( object ):
    def __init__( self ):
        self.next     = None
        self.previous = None

        # Actual node
        self.head = None
        self.tail = None
        self.size = 0

    def append( self, element ):
        if self.empty:
            self.head = element
            self.tail = element
        else:
            self.tail.right = element
            self.tail       = element
            
        self.size += 1

    def prepend( self, element ):
        element.right = self.head
        self.head     = element
            

        self.size += 1

    def pop ( self ):
        pass

    def empty( ):
        return self.size == 0

class magical_skew_list( object ):
    def __init__( self ):
        self.first = magical_skew_node( )

    def front( self ):
        return self.first

    def append( self ):
        pass
