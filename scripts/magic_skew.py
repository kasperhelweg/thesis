import math

def increment( D ):  
  D[0] += 1
  h = next((x for x in D if x == 3 or x == 4), False)
  if h:
    j = D.index( h )
    D = fix( D, j )  
  return D

def fix( D, j ):
  D[j] -= 3
  if len( D ) - 1 <= j: D.append( 0 )
  
  D[j+1] += 1
  if j != 0: D[j-1] += 2  

  return D

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


D = [2,1]
for i in range( 0, 100):
  D = increment( D )
  print( str( value_of(D) ) + ": " + str(D) )

print( "--Program magic_skew--" )

