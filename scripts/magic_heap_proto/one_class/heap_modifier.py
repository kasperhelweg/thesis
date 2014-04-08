import heap_utils

class heap_modifier( object ):  
  # stats
  siftup_comps   = 0
  siftdown_comps = 0

  @staticmethod
  def replace( node, other ):
    other.left  = node.left
    other.right = node.right
    other.color = node.color

    if not node.is_root( ):
      if node.color == 1:
        node.parent( ).left = other
      else:
        node.parent( ).left.right = other
    else:
      pass

    if not node.is_leaf( ):
      node.right_child( ).right = other

    node.left  = None
    node.right = None
    
    if not other.is_root():
      heap_modifier.siftup( other )
    if not other.is_leaf( ):
      heap_modifier.siftdown( other )
    
  @staticmethod
  def cut_at_root( r ):
    lst = r.left_child( )
    rst = r.right_child( )
      
    r.left    = None
    lst.right = None
    rst.right = None
    lst.color = 0
    
    return [lst, rst]
    
  @staticmethod
  def __swap_colors( node, other ):
    tmp = node.color
    node.color  = other.color
    other.color = tmp

  @staticmethod
  def join( r, lst, rst ):
    r.left    = lst
    lst.color = 1
    lst.right = rst
    rst.right = r
    
  @staticmethod
  def siftup( node ):
    '''procedure __siftup. complexity is O(lg n)
      each case does: 
    3 temporary pointer variables + 2 cuts + at most 6 sews + at most 1 color-bit flip
    = at most 12 operations 
    = O(1) operations'''
    
    s = node
    p = node.parent( )

    heap_modifier.siftup_comps += 1
    while not s.is_root( ) and s < p:
      heap_modifier._swap( s, p )
      p = s.parent( )
      
  @staticmethod
  def siftdown( node ):
    '''siftup procedure. complexity is 2 O(lg n)'''
        
    s  = node
    lc = node.left_child( )
    rc = node.right_child( )
    while not s.is_leaf( ):
      heap_modifier.siftdown_comps += 2
      e = lc if lc < rc else rc
      if s > e:
        heap_modifier._swap( e, s )
      else:
        break
      lc = s.left_child( )
      rc = s.right_child( )

  @staticmethod
  def _swap( node, other ):
    #             
    #     R           S
    #    / \   <=>   / \
    #   S - O       R - O
    #  /   /       /   /

    if other.is_root( ) and node.color == 1:
      '''case 0 - left node, parent is root'''

      s = node
      o = node.right
      r = other

      # Cut out
      s.right = None
      o.right = None
      r.left  = s.left

      # Sew up
      s.left  = r
      o.right = s
      r.right = o
      if not r.is_leaf( ):
        r.left.right.right = r

      heap_modifier.__swap_colors( s, r ) 
      
    #               
    #     R           S
    #    / \   <=>   / \
    #   O - S       O - R
    #  /   /       /   /

    elif other.is_root( ) and node.color == 0:
      '''case 0-1 - right node, parent is root'''
      
      s = node
      o = other.left
      r = other
      
      # Cut out 
      s.right = None
      o.right = None
      r.left  = s.left

      # Sew up
      s.left  = o
      o.right = r
      r.right = s
      if not r.is_leaf( ):
        r.left.right.right = r


    #      /           /
    #     R-          S-
    #    / \   <=>   / \
    #   S - O       R - O
    #  /   /       /   /

    elif node.color == 1 and other.color == 1:
      '''case 1 - left node in left subtree'''
      
      s = node
      o = node.right
      r = other
      
      # Cut out
      s.right = None
      o.right = None
      r.left  = s.left

      # Sew up
      s.left  = r
      s.right = r.right
      o.right = s
      r.right = o
      if not r.is_leaf( ):
        r.left.right.right = r
      if not s.is_root( ):
        s.right.right.left = s

    #      /           /
    #     R-          S-
    #    / \   <=>   / \
    #   O - S       O - R
    #  /   /       /   /

    elif node.color == 0 and other.color == 1:
      '''case 2 - right node in left subtree'''
      
      s = node
      o = other.left
      r = other
      
      # Cut out
      s.right = None
      o.right = None
      r.left  = s.left

      # Sew up
      s.left  = o
      s.right = r.right
      o.right = r
      r.right = s
      if not r.is_leaf( ):
        r.left.right.right = r
      if not s.is_root( ):
        s.right.right.left = s

      heap_modifier.__swap_colors( s, r ) 
        
    #    \           \
    #    -R          -S
    #    / \   <=>   / \
    #   S - O       R - O
    #  /   /       /   /

    elif node.color == 1 and other.color == 0:
      '''case 3 - left node in right subtree'''
      
      s = node
      o = s.right
      r = other
      
      # Cut out
      s.right = None
      o.right = None
      r.left  = s.left

      # Sew up
      s.left  = r
      s.right = r.right
      o.right = s
      r.right = o
      if not r.is_leaf( ):
        r.left.right.right = r
      if not s.is_root( ):
        s.right.left.right = s
      
      heap_modifier.__swap_colors( s, r )

    #    \           \
    #    -R          -S
    #    / \   <=>   / \
    #   O - S       O - R
    #  /   /       /   /

    elif node.color == 0 and other.color == 0:
      '''case 4 - right node in right subtree'''
      
      s = node
      o = other.left
      r = other
        
      # Cut out
      s.right = None
      o.right = None
      r.left  = s.left
      
      # Sew up
      s.left  = o
      s.right = r.right
      o.right = r
      r.right = s
      if not r.is_leaf( ):
        r.left.right.right = r
      if not s.is_root( ):
        s.right.left.right = s 

if __name__ == "__main__":
  import random
  from time import process_time
  from statistics import mean
  from heap_node import *
  import heap_utils

  comps_up   = []
  comps_down = []

  tv = []
  rv    = random.randint( 1, 100000000 )
  lvels = random.randint( 19, 19 )

  t  = process_time()
  bh = heap_utils.build_heap( lvels, rv, False )
  heap_utils.assert_heap( bh, False )
  assert 2**(lvels+1) - 1 == bh.size()

  hm = heap_modifier( )
  print("build: " + str(process_time() - t))
  
  for i in range(0, 1 ):
    
    s  = heap_utils.request_random_node( bh, lvels )
    sp = heap_node( int(heap_utils.heap_mean(bh) - 5000000 ), s.color ) 
    t  = process_time( )
    n  = hm.replace( s, sp )
    tv.append((process_time() - t))
    
    bh = sp.find_root()
    heap_utils.assert_heap( bh )
    assert 2**(lvels+1) - 1 == bh.size()
    

    if not sp.is_root():
      assert sp.parent() <= sp

    if not sp.is_leaf():
      assert sp.left_child( ) >= sp
      assert sp.right_child( ) >= sp

    comps_up.append(hm.siftup_comps)
    comps_down.append(hm.siftdown_comps)

  #heap_utils.assert_heap( bh )
        
  print("time: " + str(mean(tv)))
  print("siftup compares: " + str(mean(comps_up)))
  print("siftdown compares: " + str(mean(comps_down)))


