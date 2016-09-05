#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "LinkedList.h"

class HashTable{
private:
  LinkedList *arrayHT;
  int length;
  int hash(string itemKey);

public:
  HashTable(int tableLength = 13);
  void insertItem(Item *newItem);
  bool removeItem(string itemKey);
  Item *getItemByKey(string itemKey);
  void printTable();
  void printHistogram();
  int getLength();
  int getNumberOfItems();
  ~HashTable();
};

int HashTableTest();

#endif //HASH_TABLE_H