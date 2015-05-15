#include "delist.h"
#include <iostream>

using namespace std;

DEList::DEList()
{
  head = NULL;
  tail = NULL;
}

DEList::~DEList()
{
  DEItem* deleter = tail;
  
  // Deletes list nodes moving from tail to head
  while(tail != head)
  {
    tail = tail->prev;
    delete deleter;
    deleter = tail;
  }
  // Deletes the head itself
  delete tail;
}

bool DEList::empty()
{
  // List is empty when both head and tail don't point to anything
  if(head == NULL && tail == NULL)
    return true;
  else
    return false;
}

int DEList::size()
{
  // There are 0 items if the list is empty
  if(empty())
    return 0;

  int items = 0;
  DEItem* locMarker = tail;
  // Counts items moving from tail to head
  do
  {
    items++;
    locMarker = locMarker->prev;
  // Ends when the item before the last item counted is NULL
  }while(locMarker != NULL);
  return items;
}

int DEList::front()
{
  if(empty())
    return -1;
  else
    return head->val;    
}

int DEList::back()
{
  if(empty())
    return -1;
  else
    return tail->val;
}

void DEList::push_front(int new_val)
{
  // Creates a new list node
  DEItem* newItem = new DEItem;
  // Gives that node the desired value
  newItem->val = new_val;
  // Node points to NULL in the front and old front in the back
  newItem->prev = NULL;
  newItem->next = head;

  // If the list is empty, head and tail go straight to the new item
  if(empty())
  {
    head = newItem;
    tail = newItem;
  }
  // If there is already a list item, only head updates
  else
  {
    // Old front points to new front in the front
    head->prev = newItem;
    // Head points to new front node
    head = newItem;
  }
}

void DEList::push_back(int new_val)
{
  // Creates a new list node
  DEItem* newItem = new DEItem;
  // Gives that node the desired value
  newItem->val = new_val;
  // Node points to old back in the front and NULL in the back
  newItem->prev = tail;
  newItem->next = NULL;

  // If the list is empty, head and tail go straight to the new item
  if(empty())
  {
    head = newItem;
    tail = newItem;
  }
  // If there is already a list item, only tail updates
  else
  {
    // Old back points to new back in the back
    tail->next = newItem;
    // Tail points to new back node
    tail = newItem;
  }
}

void DEList::pop_front()
{
  if(!empty())
  {
    // When there is only one element both head and tail need to be set to NULL
    if(size() == 1)
    {
      delete head;
      tail = NULL;
      head = NULL;
    }
    else
    {
      // Temp pointer knows where the new front node is
      DEItem* tempPtr = head->next;
      // New front node points to NULL at the front
      tempPtr->prev = NULL;
      // Delete the old head
      delete head;
      // Update the new head
      head = tempPtr;
    }
  }
  else
    cerr << "This list is already empty" << endl;
}

void DEList::pop_back()
{
  if(!empty())
  {
    // When there is only one element both head and tail need to be set to NULL
    if(size() == 1)
    {
      delete head;
      tail = NULL;
      head = NULL;
    }
    else
    {
      // Temp pointer knows where the new back node is
      DEItem* tempPtr = tail->prev;
      // New back node points to NULL at the back
      tempPtr->next = NULL;
      // Delete the old tail
      delete tail;
      // Update the new tail
      tail = tempPtr;
    }
  }
  else
    cerr << "This list is already empty" << endl;  
}
