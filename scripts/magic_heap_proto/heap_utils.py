import random
from statistics import mean
from binary_heap import *

# H e a p U t i l s \ B u i l d H e a p #
# ------------------------------------- #

def attach_children( r, rand ):
  if rand:
    s = heap_node( random.randint( 0, 100000000 ), 1 )
    if s < r:
      s.element = s.element + r.element + random.randint(0, 1000 )
    o = heap_node( random.randint( 0, 100000000 ), 0 )
    if o < r:
      o.element = o.element + r.element + random.randint(0, 1000 )
    #s = heap_node( random.randint( r.element + 100, r.element + 1000 ), 1 )
    #o = heap_node( random.randint( r.element + 500, r.element + 100000 ), 0 )
  else:
    s = heap_node( r.element + 1, 1 )
    o = heap_node( r.element + 1, 0 )

  r.left  = s
  s.right = o
  o.right = r

  return [s, o]

def build_heap( h, rv, rand = True ):
  def rec( n, h, b ):
    if h == b:
      return 
    else:
      children = attach_children( n, rand )
      for c in children:
        rec( c, h, b + 1 )
  b = 0
  bh = binary_heap( heap_node( rv, 0 ) ) 
  rec( bh.root, h, b )
  return bh

# H e a p U t i l s \ D r a w H e a p #
# ----------------------------------- #

def draw_heap( bh, node = None, f = None ):
  def rec( n ):
    if n == None or n.left == None:
      return
    else:
      lc = n.left
      rc = n.left.right
      print("root: " + str(n.element) + " " + "lc: " + str(lc.element) + " " + "rc: " + str(rc.element) )
      print("root: " + str(n) )
      print("lc: " + str(lc) + " " + "rc: " + str(rc) )
      print("lc right: " + str(lc.right) )
      print("lc parent: " + str(lc.parent()) + " " + "rc parent: " + str(rc.parent()) )
      rec( lc )
      rec( rc )
  if not node:
    rec( bh.root )
  else:
    rec( node )


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
  lvel = random.randint( 0, levels )
  nde  = random.randint( 1, 2**lvel )
  return request_node( bh, nde, lvel )

def assert_heap( bh, heap_property = True, node = None ):
  ''' Sould take a heap, and assert that it is indeed a heap ''' 
  def rec( n ):
    if n == None or n.left == None:
      return
    else:
      lc = n.left_child( )
      rc = n.right_child( )    
      assert lc != None and rc != None
      if heap_property:
        assert n <= lc and n <= rc      
      assert rc.parent() is n
      assert lc.parent() is n
      rec( lc )
      rec( rc )
  if not node:
    rec( bh.root )
  else:
    rec( node )

def heap_mean( bh ):
  def rec( n ):
    if n.left == None:
      return
    else:
      lc = n.left
      rc = n.left.right
      vals.append(n.element)
      vals.append(lc.element)
      vals.append(rc.element)
      rec( lc )
      rec( rc )
  vals = []
  rec( bh.root )
  return mean(vals)

  

if __name__ == "__main__":
  
  rv = random.randint( 100, 1000 )
  bh = build_heap( 3, rv  )

  node = request_node( bh, 2, 2  )
  assert not None == node.left

  node = request_node( bh, 1, 3  )
  assert None == node.left

  bh = build_heap( 4, rv  )
  assert 15 == bh.size()

  lvls = 12
  bh   = build_heap( lvls, random.randint( 0, 100 )  )
  assert None == assert_heap( bh )  
  
