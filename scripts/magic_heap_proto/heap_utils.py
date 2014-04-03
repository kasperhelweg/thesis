from binary_heap import *
import random

# H e a p U t i l s \ B u i l d H e a p #
# ------------------------------------- #

def attach_children( r ):
  s = heap_node( random.randint( r.element + 1, r.element + 2 + 100000 ), 1 )
  o = heap_node( random.randint( r.element + 1, r.element + 2 + 100000 ), 0 )
    
  r.left  = s
  s.right = o
  o.right = r

  return [s, o]

def build_heap( h, rv ):
  b = 0
  bh = binary_heap( heap_node( rv, 0 ) ) 
  def rec( n, h, b ):
    if h == b:
      return 
    else:
      children = attach_children( n )
      for c in children:
        rec( c, h, b + 1 )

  rec( bh.root, h, b )
  return bh

# H e a p U t i l s \ D r a w H e a p #
# ----------------------------------- #

def draw_heap( bh ):
  pass


# H e a p U t i l s \ M i s c #
# --------------------------- #

def request_node( bh, node, level ):
  n = bh.root
  t = 2**level
  if node > t:
    return None
  elif t == 1:
    return n
  else:
    for i in range(0, level ):
      t = t // 2
      if( node <= t ):
        n = n.left
      else:
        n = n.left.right
  return n

def request_random_node( bh, levels ):
  lvel = random.randint(0, levels )
  nde  = random.randint(1, 2**lvel )
  n    = request_node( bh, nde, lvel )
  return n



if __name__ == "__main__":

  rv = random.randint( 100, 1000 )
  bh = build_heap( 3, rv  )

  node = request_node( bh, 2, 2  )
  assert not None == node.left

  node = request_node( bh, 1, 3  )
  assert None == node.left
