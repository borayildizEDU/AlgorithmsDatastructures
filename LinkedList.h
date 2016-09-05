#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <string>
using namespace std;

//*****************************************************************
// List items are keys with pointers to the next item.
//*****************************************************************
struct Item{
  string key;
  Item *next;
  Item(){                         //Struct Default Constructor
    key = "Default Key";
    next = NULL;
  }
  Item(string k, Item* n){        //Struct Constructor
    key = k;
    next = n;
  }
};

//*****************************************************************
// Linked lists store a variable number of items.
//*****************************************************************
class LinkedList{
private:
  Item *head;
  int length;

public:
  LinkedList();
  void insertItem(Item *newItem);
  bool removeItem(string itemKey);
  Item *getItem(string itemKey);
  void printList();
  int getLength();
  ~LinkedList();
};


#endif //LINKED_LIST_H