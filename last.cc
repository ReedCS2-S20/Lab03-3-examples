#include <iostream>

struct node {
  int data;
  struct node* next;
};

void outputSequence(node* first) { 
  if (first == nullptr) {
    std::cout << "[]" << std::endl;
  } else {
    node* current = first;
    while (current->next != nullptr) {
      std::cout << current->data << ", ";
      current = current->next;
    }
    std::cout << current->data << "]" << std::endl;
  }
}

void outputLast(node* first) { 
  if (first == nullptr) {
    std::cout << "An empty list has no last element." << std::endl;
  } else {
    node* current = first;
    while (current->next != nullptr) {
      current = current->next;
    }
    std::cout << "The last element of the list is " << current->data << "." << std::endl;
  }
}

node* insertAtFront(int value, node* first) {
  node* newNode = new node;
  newNode->data = value;
  newNode->next = first;
  return newNode;
}

node* insertAtEnd(int value, node* first) {
  node* newNode = new node;
  newNode->data = value;
  newNode->next = nullptr;
  if (first == nullptr) {
    return newNode;
  } else {
    node* current = first;
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = newNode;
    return first;
  }
}

node* requestSequence(int sz) { 
  node* first = nullptr;
  std::cout << "Enter your sequence, one item per line:" << std::endl;
  for (int i=0; i<sz; i++) {

    // Get a sequence value.
    int entry;
    std::cin >> entry;

    // Add a node for it to the linked list.
    first = insertAtFront(entry, first);
  }

  return first;
}

int main(void) {
  int length;
  std::cout << "Enter the length of your sequence: ";
  std::cin >> length;
  node* first = requestSequence(length);
  std::cout << "The sequence you entered was: " << std::endl;
  outputSequence(first);
}
