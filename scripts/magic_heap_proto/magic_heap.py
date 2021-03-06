#!/usr/bin/env python
import random
from binary_heap import *
from stack import *

import heap_utils

class magical_heap_node( object ):
  def __init__( self ):
    self.next     = None
    self.previous = None
    
    self.head = None
        
    self.size = 0

  def push_front( self, node ):
    node.right = self.head 
    self.head  = node
    self.size += 1

  def pop_front( self ):
    e          = self.head
    self.head  = e.right
    e.right    = None
    
    self.size -= 1
    return e

  def meld( self, other ):
    pass
    
  def is_front( self  ):
    return self.previous == None
    
  def is_high( self ):
    return self.size == 3

  def empty( self ):
    return self.size == 0

class magic_heap( object ):
  def __init__( self ):
    self.first = magical_heap_node( )

    self.min_pointer = None
    #self.fix_stack   = fix_stack( ) # Hi and Lo digits
    self.fix_stack   = fix_stack_vector( ) # Hi and Lo digits
    self.statebit    = 0

  ## M a g i c H e a p \ P u b l i c ##


  def find_min( self ):
    return self.min_pointer.find_min( )

  def buy_node( self ):
    return heap_node( )

  def insert( self, node ): # increment
    nh = binary_heap( node )

    # insert new node at front.
    node = self.__front( )
    node.push_front( nh )
    
    # update min pointer
    if not self.min_pointer or nh.find_min( ) < self.min_pointer.find_min( ):
      self.min_pointer = nh

    # fix
    if node.is_high( ):
      self.__fix( node )
    else:
      node_to_fix = self.fix_stack.pop_hi( )    
      if node_to_fix:
        self.__fix( node_to_fix ) 

  def delete( self, node ): # decrement    
    bn = self.__borrow( )
    node.head.replace( node, bn  )

  def delete_min( self ):
    self.delete( self.min_pointer )
    #scan roots to find new minimum


  def meld( self, mheap ):
    pass

  def size( self ):
    s = self.__numerical( )
    return self.__value_of( s )

  def list( self ):
    return self.__numerical( )


  ## M a g i c H e a p \ P r i v a t e ##
  
  def __get_state( self ):
    #f = self.__front( ).head.size( )
    #s = self.__front( ).next.head.size( )
    #return str( f ) + str( s )
    pass

  def __front( self ):
    '''Return front node of the magic-heap'''
    return self.first

  def __grow( self, node ):
    '''Given a pointer to a node, this function grows the magic-heap by one'''
    mhn          = magical_heap_node( )
    node.next    = mhn
    mhn.previous = node

  def __shrink( self, node ):
    '''Given a pointer to a node, this function shrinks the magic-heap by one'''
    node.previous.next = None
    node.previous      = None

  def __meld( self, mheap ):
    '''Given a second magic-heap, this function melds the two'''
    pass
    
  def __fix( self, node ):
    # grow heap if necesary
    if node.next == None:
      self.__grow( node )

    # Decrease sigma_j by 3
    p = node.pop_front( )
    q = node.pop_front( )
    r = node.pop_front( )

    # increase sigma_j-1 by 2
    if p.root < q.root:
      if p.root < r.root:
        if not node.is_front( ):
          sts = p.cut_at_root( )
        p.root.left  = q.root
        q.root.color = 1
        q.root.right = r.root
        r.root.right = p.root
        node.next.push_front( p )
      else:
        if not node.is_front( ):
          sts = r.cut_at_root( )
        r.root.left  = p.root
        p.root.color = 1
        p.root.right = q.root
        q.root.right = r.root
        node.next.push_front( r )        
    else:
      if q.root < r.root:
        if not node.is_front( ):
          sts = q.cut_at_root( )
        q.root.left  = r.root
        r.root.color = 1
        r.root.right = p.root
        p.root.right = q.root
        node.next.push_front( q )
      else:
        if not node.is_front( ):
          sts = r.cut_at_root( )
        r.root.left  = p.root
        p.root.color = 1
        p.root.right = q.root
        q.root.right = r.root
        node.next.push_front( r )

    if node.next.is_high( ):
      self.fix_stack.push_hi( node.next )
  
    # increase sigma_j-1 by 2
    if not node.is_front( ):
      node.previous.push_front( sts[0] )
      node.previous.push_front( sts[1] )
      if node.previous.is_high( ):
        self.fix_stack.push_hi( node.previous  )
        
  def __unfix( self, node ):
    if not node.is_front( ):
      p = node.next.pop_front( )
      q = node.previous.pop_front( )
      r = node.previous.pop_front( )
      
      sts          = p.cut_at_root( )
      p.root.left  = q.root
      q.root.color = 1
      q.root.right = r
      r.root.right = p
      
      p.siftdown( p.root  )
      node.push_front( p )
      node.push_front( sts[0] )
      node.push_front( sts[1] )
    else:
      p   = node.next.pop_front( )
      sts = p.cut_at_root( )
      
      node.push_front( p )
      node.push_front( sts[0] )
      node.push_front( sts[1] )
   
  def __borrow( self ):
    #node_to_unfix = self.low_stack.pop( )    
    #if node_to_unfix:
    #  self.__unfix( node_to_unfix )
    
    # bn = self.__front().pop()
    # return bn
    pass

  def __scan( self ):
    miterator = self.__front( )
    while miterator != None:
      riterator = miterator.head
      while riterator != None:
        print( riterator.find_min( ).element  )
        riterator = riterator.right
      miterator = miterator.next

  def __empty( self, node ):
    return node.size == 0

  def __value_of( self, S ):
    n = 0
    for i ,s in enumerate( S ):
      n += s * ((2**(i+1)) - 1)
    return n

  def __numerical( self ):
    s = []
    i = self.__front( )
    while i:
      s.append( i.size )
      i = i.next
    return s

  def assert_magic_heap( self ):
    miterator = self.__front( )
    while miterator != None:
      riterator = miterator.head
      while riterator != None:
        heap_utils.assert_heap( riterator )
        riterator = riterator.right
      miterator = miterator.next
    

if __name__ == "__main__":
  from time import process_time

  def get_random( ):
    return random.randint( 1, 1000000 )

  m_heap = magic_heap( )
  print( "size: " + str( m_heap.size( ) ) )
  
  t = process_time()
  for i in range( 0, 2**21 ):
    node         = m_heap.buy_node( )
    node.element = get_random( )
    m_heap.insert( node  )
  
  print( "time: " + str( process_time() - t ) )
  print( "size: " + str( m_heap.size( ) ) )
  print( "structure: " + str( m_heap.list( ) ) )
  print( "min element: " + str( m_heap.find_min( ).element ) )
  m_heap.assert_magic_heap( )
