#include "LinkedList.h"


LinkedList::LinkedList(){
  head = new Item;
  head->next = NULL;
  length = 0;
}

void LinkedList::insertItem(Item *newItem){
  //First Item
  if(!head->next){
    head->next = newItem;
    length++;
    return;
  }

  //Iterate until the last item and then insert the new item
  Item *p = head;
  Item *q = head;
  while(q){
    p = q;
    q = p->next;
  }
  p->next = newItem;
  newItem->next = NULL;
  length++;
}

bool LinkedList::removeItem(string itemKey){
  if(!head->next) return false;

  Item *p = head;
  Item *q = head;

  while(q){
    if(q->key == itemKey)
    {
      p->next = q->next;
      delete q;
      length--;
      return true;
    }
    p = q;
    q = p->next;
  }
  return false;
}

Item* LinkedList::getItem(string itemKey){
  Item *p = head;
  Item *q = head;

  while(q){
    p = q;
    if((p != head) && (p->key == itemKey)) return p;
    q = p->next;
  }
  return NULL;
}

void LinkedList::printList(){
  if(length == 0){
    cout << "\n{}\n";
    return;
  }

  Item *p = head;
  Item *q = head;
  cout << "\n{ ";
  while(q){
    p = q;
    if(p != head){
      cout << p->key;
      if(p->next) cout << ", ";
      else cout << " ";
    }
    q = p->next;
  }
  cout << "}\n";
}

int LinkedList::getLength(){
  return length;
}

LinkedList::~LinkedList(){
  Item *p = head;
  Item *q = head;

  while(q){
    p =q;
    q = p->next;
    if(q) delete p;
  }
}

