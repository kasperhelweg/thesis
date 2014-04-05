if __name__ == "__main__":
  import sys
  sys.path.insert(0, '/home/kasper/Development/workspace/thesis/scripts/magic_heap_proto/')

  import thesis_test

  from binary_heap import *
  import heap_utils

  import random
  from statistics import mean
  
  # H e a p N o d e \ T e s t #
  # ------------------------- #


  # B i n a r y H e a p \ T e s t #
  # ----------------------------- #

  #             
  #    R
  #   / \
  #  S - O
  '''siftup - case 0'''
  '''
  rv = random.randint( 100, 1000 )
  bh = heap_utils.build_heap( 1, rv  )  
  assert rv == bh.root.element
    
  s  = heap_utils.request_node( bh, 1, 1 )
  sp = heap_node( rv - 1, 0 ) 
  n  = bh.replace( s, sp )

  assert n.element == s.element
  bh.siftup( sp )
  
  assert sp.element == bh.root.element
  '''
  #             
  #    R
  #   / \
  #  O - S
  '''siftup - case 0-1'''
  '''
  rv = random.randint( 100, 1000 )
  bh = heap_utils.build_heap( 1, rv  )  
  assert rv == bh.root.element
    
  s  = heap_utils.request_node( bh, 2, 1 )
  sp = heap_node( rv - 1, 0 ) 
  n  = bh.replace( s, sp )

  assert n.element == s.element
  bh.siftup( sp )
  
  assert sp.element == bh.root.element
  '''
  #     /       
  #    R-
  #   / \
  #  S - O
  '''siftup - case 1 '''
  '''
  rv = random.randint( 100, 1000 )
  bh = heap_utils.build_heap( 2, rv  )  
  assert rv == bh.root.element
    
  s  = heap_utils.request_node( bh, 1, 2 )
  sp = heap_node( rv - 1, 0 ) 
  n  = bh.replace( s, sp )

  assert n.element == s.element
  bh.siftup( sp )
  
  assert sp.element == bh.root.element
  '''
  
  #     /       
  #    R-
  #   / \
  #  O - S
  '''siftup - case 2 '''
  '''
  rv = random.randint( 100, 1000 )
  bh = heap_utils.build_heap( 2, rv  )  
  assert rv == bh.root.element
    
  s  = heap_utils.request_node( bh, 2, 2 )
  sp = heap_node( rv - 1, s.color ) 
  n  = bh.replace( s, sp )

  assert n.element == s.element
  bh.siftup( sp )
  
  assert sp.element == bh.root.element
  '''

  '''
  siftup - random - sift to root
  ''' 
  comps = []
  for i in range(0, 100 ):
    rv    = random.randint( 10, 1000 )
    lvels = random.randint( 1, 13 )

    bh         = heap_utils.build_heap( lvels, rv  )  
    assert rv == bh.root.element    
    heap_utils.assert_heap( bh )
    
    s  = heap_utils.request_random_node( bh, lvels )
    sp = heap_node( rv - 1, s.color ) 
    n  = bh.replace( s, sp )
    assert n.element == s.element

    heap_utils.assert_heap( bh, False )
    bh.siftup( sp )
    heap_utils.assert_heap( bh )
    assert sp.element == bh.root.element
    
    comps.append(bh.siftup_comps)
  
  print(mean(comps))


  '''siftdown - random - sift to bottom
  '''
  comps = []
  for i in range(0, 100 ):
    lvls = 12
    rv   = 0
    bh   = heap_utils.build_heap( lvls, rv, False  )  
    assert rv == bh.root.element
    heap_utils.assert_heap( bh )

    s  = heap_utils.request_node( bh, 1, 0 )
    sp = heap_node( lvls + 1, 0 ) 
    n  = bh.replace( s, sp )

    assert n.element == s.element
    assert True == sp.is_root( )
    heap_utils.assert_heap( bh, False )

    bh.siftdown( sp )  
    assert True == sp.is_leaf( )
    assert False == sp.is_root( )
    assert bh.root != sp
    assert bh.root != None
    heap_utils.assert_heap( bh )

    comps.append(bh.siftdown_comps)
  
  print(mean(comps))


  '''siftdown - more random
  '''      
  '''
  comps = []
  for i in range(0, 100 ):
    rv    = 0
    lvels = random.randint( 1, 13 )

    bh         = heap_utils.build_heap( lvels, rv, False  )  
    assert rv == bh.root.element
    
    s  = heap_utils.request_random_node( bh, lvels )
    sp = heap_node( lvels + 1, 0 ) 
    n  = bh.replace( s, sp )

    assert n.element == s.element
    #assert True == sp.is_root( )
  
    bh.siftdown( sp )
  
    assert True == sp.is_leaf( )
    heap_utils.assert_heap( bh )

    comps.append(bh.siftdown_comps)
  print(mean(comps))
  '''
  
  '''siftup / down
  '''
  comps_up   = []
  comps_down = []
  for i in range(0, 100 ):
    rv    = random.randint( 1000, 10000 )
    lvels = random.randint( 1, 15 )

    bh         = heap_utils.build_heap( lvels, rv  )  
    assert rv == bh.root.element
    heap_utils.assert_heap( bh )
    
    s  = heap_utils.request_random_node( bh, lvels )
    sp = heap_node( int(heap_utils.heap_mean(bh) - random.randint(1000,5000)), s.color ) 
    n  = bh.replace( s, sp )
    assert n.element == s.element
    heap_utils.assert_heap( bh, False )

    # try siftup
    bh.siftup( sp )
    # try siftdown
    bh.siftdown( sp )
    
    if not sp.is_root():
      assert sp.parent() <= sp

    if not sp.is_leaf():
      assert sp.left_child( ) >= sp
      assert sp.right_child( ) >= sp

    heap_utils.assert_heap( bh )
    
    comps_up.append(bh.siftup_comps)
    comps_down.append(bh.siftdown_comps)
    
  print(mean(comps_up))
  print(mean(comps_down))
