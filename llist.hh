#ifndef _LLIST_HH
#define _LLIST_HH

#include <string>

namespace llist {

  struct node {
    int data;
    struct node* next;
  };

  struct llist {
    node* first;
  };

  llist* build(void);
  llist* buildWith(int* values, int length);
  void insertAtFront(llist* list, int value);
  void insertAtEnd(llist* list, int value);
  bool isEmpty(llist* list);
  bool contains(llist* list, int value);
  void deleteFront(llist* list);
  void deleteEnd(llist* list);
  std::string toString(llist* list);
  void destroy(llist* list);
  int length(llist* list); 
  void remove(llist* list, int value);
}

#endif
