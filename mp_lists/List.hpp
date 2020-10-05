/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_ -> next);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  while (head_ != NULL) {
    ListNode * newHead = head_ -> next;
    delete head_;
    head_ = newHead;
  }

  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  ListNode * tempNode;

  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  
  tempNode = head_;
  head_ = newNode;
  newNode = tempNode;

  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  ListNode * tempNode;

  if (head_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
  }

  tail_ -> next = newNode;

  tempNode = tail_;
  tail_ = newNode;
  newNode = tempNode;

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  if (start == NULL || splitPoint >= length_) {
    return NULL;
  }

  if (splitPoint == 0) {
    curr = start -> prev;
    if (curr != NULL) {
      curr -> next = NULL;
    }
    start -> prev = NULL;
    return start;
  }

  for (int i = 0; i < splitPoint - 1 && curr -> next != NULL; i++) {
    curr = curr -> next;
  }

  ListNode * toReturn = curr -> next;
  curr -> next = NULL;
  toReturn -> prev = NULL;
  tail_ = curr;

  return toReturn;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode * curr = head_;
  ListNode * swapOne = NULL;
  ListNode * swapTwo = NULL;
  ListNode * before = NULL;
  ListNode * after = NULL;

  for (int i = 1; i <= length_; i++) {
    if (swapOne == NULL) {
      swapOne = curr;
      before = curr -> prev;
      swapTwo = curr -> next;
    }
    
    if (i % 3 == 0 && swapOne != NULL) {
      after = curr -> next;

      //alter the third node
      swapOne -> prev = curr;
      if (after == NULL) {
        swapOne -> next = NULL;
        tail_ = swapOne;
      } else {
        swapOne -> next = after;
        after -> prev = swapOne;
      }

      //alter the second node
      curr -> prev = swapTwo;
      curr -> next = swapOne;

      //alter the first node
      if (before == NULL) {
        swapTwo -> prev = NULL;
        head_ = swapTwo;
      } else {
        swapTwo -> prev = before;
        before -> next = swapTwo;
      }
      swapTwo -> next = curr;

      curr = swapOne -> next;
      swapOne = NULL;
      before = NULL;
      swapTwo = NULL;
      after = NULL;
    } else {
      curr = curr -> next;
    }
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2

  ListNode * start = startPoint;
  ListNode * end = endPoint;
  ListNode * before = startPoint -> prev;
  ListNode * after = endPoint -> next;
  ListNode * curr = startPoint -> next;

  ListNode * toBeNext = startPoint;
  ListNode * toBePrev = curr -> next;
  
  startPoint -> prev = curr;
  
  while(curr != endPoint) {
    toBePrev = curr -> next;
    curr -> next = toBeNext;
    curr -> prev = toBePrev;
    toBeNext = curr;
    curr = curr -> prev;
  }
  
  
  endPoint -> next = toBeNext;

  if (after == NULL) {
    tail_ = start;
    start -> next = NULL;
  } else {
    start -> next = after;
    after -> prev = start;
  }

  if (before == NULL) {
    head_ = end;
    end -> prev = NULL;
  } else {
    end -> prev = before;
    before -> next = end;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  ListNode * curr = head_;
  ListNode * start = NULL;
  ListNode * end = NULL;
  int i = 1;

  while (curr != tail_) {
    if (start == NULL) {
      start = curr;
    }
    if (i % n == 0) {
      end = curr;
      curr = curr -> next;
      reverse(start, end);
      start = NULL;
    } else {
      curr = curr -> next;
    }
    i++;
  }
  if (start != NULL) {
    reverse (start, curr);
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode * start;
  ListNode * currOne = first;
  ListNode * currTwo = second;
  ListNode * tempOne = currOne;
  ListNode * tempTwo = NULL;

  if (first == NULL) {
    return second;
  } else if (second == NULL) {
    return first;
  }

  if (second -> data < first -> data) {
    start = second;
  } else {
    start = first;
  }

  if (currOne -> next == NULL) {
    while (currTwo != NULL && currTwo -> data < currOne -> data) {
      tempTwo = currTwo -> next;
      currTwo -> prev= tempOne;
      currTwo -> next = currOne;
      currOne -> prev = currTwo;
      tempOne = currTwo;

      currTwo = tempTwo;
    }
  }

  // goes to the end of list one
  while (currOne -> next != NULL) {
    if (!(currTwo -> data < currOne -> next -> data) || currTwo == NULL) {
      tempOne = currOne;
      currOne = currOne -> next;
    } else {
      tempTwo = currTwo -> next;


      tempOne = currOne -> next;
      currTwo -> prev = currOne;
      currTwo -> next = tempOne;
      currOne -> next = currTwo;
      tempOne -> prev = currTwo;

      currOne = currTwo;
      currTwo = tempTwo;

      if (currTwo != NULL) {
        currTwo -> prev = NULL;
      }
      

      tempOne = currOne;
    }
  }

  //what's leftover at the end of list1
  while (currTwo != NULL) {
    currTwo -> prev = NULL;
    tempTwo = currTwo -> next;

    currOne -> next = currTwo;
    currTwo -> prev = currOne;
    currTwo -> next = NULL;

    currOne = currTwo;
    currTwo = tempTwo;
  }
  
  return start;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  ListNode * beginning = start;
  ListNode * half;
  ListNode * temp;
  int size = chainLength / 2;

  /*
  temp = start -> prev;
  if (temp != NULL) {
    std::cout << "Reached splitter" << std::endl;
    temp -> next = NULL;
  }
  start -> prev = NULL;
  */

  if (chainLength == 1) {
    std::cout << "Reached base case of " << start -> data << std::endl;
    if (start -> prev != NULL) {
      std::cout << "GOD HAS FAILED US " << start -> prev -> data << std::endl;
    }

    return beginning;
  }
  
  half = split(beginning, size);
  std::cout << "size " << size << std::endl;
  std::cout << "chainLength - size " << chainLength - size << std::endl;

  std::cout << "half " << half -> data << std::endl;

  temp = half -> prev;
  std::cout << "temp " << temp -> data << std::endl;

  if (temp != NULL) {
    std::cout << "Reached splitter" << std::endl;
    temp -> next = NULL;
  }
  half -> prev = NULL;

  ListNode * lhs = mergesort(beginning, size);
  ListNode * rhs = mergesort(half, chainLength - size);
  ListNode * final = merge(lhs, rhs);

  std::cout << "lhs " << lhs -> data << std::endl;
  if (lhs -> prev != NULL) {
    std::cout << "lhs prev " << lhs -> prev -> data << std::endl;
  }
  std::cout << "rhs " << rhs -> data << std::endl;
  if (rhs -> next != NULL) {
    std::cout << "rhs two " << rhs -> next -> data << std::endl;
  }
  std::cout << "final " << final -> data << std::endl;
  std::cout << "final two " << final -> next -> data << std::endl;

  return final;


  /*
  ListNode * recursive = beginning -> next;
  beginning -> next = NULL;
  recursive -> prev = NULL;
  */

  //ListNode * toSort = mergesort(recursive, chainLength - 1);

  //std::cout << "toSort " << toSort -> data << std::endl;
  //std::cout << "recursive " << recursive -> data << std::endl;
  //std::cout << "start " << start -> data << std::endl;

  //ListNode * toReturn = merge(beginning, toSort);

  //return toReturn;
}
