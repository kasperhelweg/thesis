import math

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

hi = linked_list( )
lo = linked_list( )

def increment( D ): 
  # maintain lo list -----------------------------------
  if D[0] == 1:
    lo.pop()
  elif D[0] == 0:
    if not lo.head or lo.head.element != 0: lo.append( 0 )
  
  # maintain hi list and increment -----------------------------------
  D[0] += 1  
  if D[0] >= 3:
    if not hi.head or hi.head.element != 0:
      hi.append( 0 )
      #print("append front: " + str(0))

  # Fix -----------------------------------
  j = hi.pop( )
  if not j == None:
    D = fix( D, j  )
    
  return D

def fix( D, j ):

  # decrement and grow -----------------------------------
  D[j] -= 3
  if len( D ) - 1 <= j: D.append( 0 )
  
  # maintain lo list -----------------------------------
  # sigma(+1) + 1
  if j != 0:
    if D[j-1] <= 1:
      lo.pop()

  if D[j+1] == 1:
    lo.pop()
  elif D[j+1] == 0:
    if not lo.head or not lo.head.element == j+1:
      lo.append(j+1)

  if not lo.head or not lo.head.element == j:
    lo.append( j )


  # maintain hi list and increment -----------------------------------
  D[j+1] += 1  
  if D[j+1] >= 3:
    if not hi.head or not hi.head.element == j + 1:
      hi.append( j + 1  )
      #print("append: " + str(j+1))
 
  # sigma(-1) + 2
  if j != 0: 
    D[j-1] += 2  
    if D[j-1] >= 3: 
      hi.append( j-1 )
  return D


def decrement( D ):
  if not is_idle( D ):
    if get_state( D ) == '22':
      if not hi.empty and hi.peak( 1 ) == 3:
        j = lo.pop( )
        D = unfix( D, j )
    else:
      j = lo.pop( )
      if not j == None:
        D = unfix( D, j  )
  
  if D[0] == 3:
    hi.pop( )

  D[0] -= 1
  return D

def unfix( D, j ):

  
  D[j] += 3
  # always True - Thus, the check is obsolete
  if D[j] >= 3: hi.append( j )

  D[j+1] -= 1

  if j != 0: D[j+1] -= 2
  

  

  #if len( D ) - 1 <= j: D.append( 0 )
  
  return D

def get_state( D ):
  if len( D ) < 2:
    return str(D[0])
  else:
    return str(D[0]) + str(D[1])

def is_idle( D ):
  # idle state 21t
  if get_state( D ) == '21':
    return True
  elif get_state( D ) == '12': 
    # 12a
    if not hi.empty( ):
      return False
    else:
      if lo.size( ) == 1 or lo.peak( 2 ) == len(D) - 1:
        return True
      else:
        return False
  else:
    return False

def value_of( S ):
  n = 0
  for i ,s in enumerate( S ):
    n += s * ((2**(i+1)) - 1)
  return n

def high( D ):
  h = next((x for x in D if x == 3 or x == 4), False)
  return h

def to_binary( D ):
  B = []
  for i ,d in enumerate( D ):
    B.append(int(bin(d)[2:]))
  return B

D = [0]
print("------------------------------------ INC")
for i in range( 0, 100 ):
  D = increment( D )
  print( str( value_of(D) ) + ": " + str(D) )
  print("is idle: " + str( is_idle( D ) ))
  '''
  print("------------------------------------")
  print( str( value_of(D) ) + ": " + str(D) )
  print(hi.p())
  print(lo.p())
  print("------------------------------------INC")
  D = increment( D )
  print( str( value_of(D) ) + ": " + str(D) )
  print(hi.p())
  print(lo.p())
  print("------------------------------------")
  '''

print("------------------------------------")
print( str( value_of(D) ) + ": " + str(D) )
print(hi.p())
print(lo.p())

print("------------------------------------ DEC")
D = decrement( D )
print("------------------------------------")
print( str( value_of(D) ) + ": " + str(D) )
print(hi.p())
print(lo.p())


  #print( str( value_of(D) ) + ": " + str(D) )
  
  #for index,value in enumerate(D):
  #  if d >= 3:
  #   hi.append(index)
  #  elif d <= 1:
  #    lo.append(index)
  #print( "hi:" + str(hi) )
  #print( "lo:" + str(lo) )
print( "--Program magic_skew--" )



