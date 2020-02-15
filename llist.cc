#include <string>
#include <iostream>
#include "llist.hh"

namespace llist {

  llist* build(void) {
    llist* newList = new llist;
    newList->first = nullptr;
    return newList;
  }

  llist* buildWith(int* values, int length) {
    llist* newList = build();
    for (int i=0; i<length; i++) {
      insertAtFront(newList,values[length-i-1]);
    }
    return newList;
  }

  void insertAtFront(llist* list, int value) {
    node* newNode = new node;
    newNode->data = value;
    newNode->next = list->first;
    list->first = newNode;
  }

  void insertAtEnd(llist* list, int value) {
    node* newNode = new node;
    newNode->data = value;
    newNode->next = nullptr;

    if (list->first == nullptr) {

      list->first = newNode;

    } else {

      node* current = list->first;
      while (current->next != nullptr) {
	current = current->next;
      }
      current->next = newNode;

    }
  }

  bool isEmpty(llist* list) {
    return (list->first == nullptr);
  }

  bool contains(llist* list, int value) {
    node* current = list->first;
    while (current != nullptr) {
      if (current->data == value) {
	return true;
      }
      current = current->next;
    }
    return false;
  }

  void deleteFront(llist* list) {
    if (list->first != nullptr) {
      node* toDelete = list->first;
      list->first = list->first->next;
      delete toDelete;
    }
  }

  void deleteEnd(llist* list) {
    if (list->first != nullptr) {
      if (list->first->next == nullptr) {
	delete list->first;
	list->first = nullptr;
      } else {
	node* follower = list->first;
	node* leader = list->first->next;
	while (leader->next != nullptr) {
	  follower = leader;
	  leader = leader->next;
	}
	delete follower->next;
	follower->next = nullptr;
      }
    }
  }

  std::string toString(llist* list) {
    if (list->first == nullptr) {
      return "[]";
    } else {
      std::string s = "[";
      node* current = list->first;
      while (current->next != nullptr) {
	s += std::to_string(current->data) + ", ";
	current = current->next;
      } 
      s += std::to_string(current->data) + "]";
      return s;
    }
  }

  void destroy(llist* list) {
    node* current = list->first;
    while (current != nullptr) {
      node* toDelete = current;
      current = current->next;
      delete toDelete;
    }
    delete list;
  }

  int length(llist* list) {
    // UNIMPLEMENTED
    // Write for Homework 03, Part 1.
    return 0;
  }

  void remove(llist* list, int value) {
    // UNIMPLEMENTED
    // Write for Homework 03, Part 1.
    return;
  }

} // end namespace llist
