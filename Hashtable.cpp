#include "Hashtable.h"

HashTable::HashTable(int tableLength){
  if (tableLength <= 0) tableLength = 13;
  arrayHT = new LinkedList[tableLength];
  length = tableLength;
}

int HashTable::hash(string itemKey){
  int value = 0;
  for(unsigned int i = 0; i < itemKey.length(); i++){
    value += itemKey[i];
  }
  return (value * itemKey.length() ) % length;;    //Check with also [return (value * itemKey.length() ) % length;]
}

void HashTable::insertItem(Item *newItem){
  int index = hash(newItem->key);
  arrayHT[index].insertItem(newItem);
}

bool HashTable::removeItem(string itemKey){
  int index = hash(itemKey);
  return arrayHT[index].removeItem(itemKey);
}

Item* HashTable::getItemByKey(string itemKey){
  int index = hash(itemKey);
  return arrayHT[index].getItem(itemKey);
}

void HashTable::printTable(){
  cout << "\nHash Table:\n";
  for(int i = 0; i < length; i++){
    cout << "Bucket " << i + 1 << ": ";
    arrayHT[i].printList();
  }
}

void HashTable::printHistogram(){
    cout << "\n\nHash Table Contains ";
    cout << getNumberOfItems() << " Items total\n";
    for ( int i = 0; i < length; i++ ){
        cout << i + 1 << ":\t";
        for ( int j = 0; j < arrayHT[i].getLength(); j++ )
            cout << " X";
        cout << "\n";
    }
}

int HashTable::getLength()
{
    return length;
}

int HashTable::getNumberOfItems(){
    int itemCount = 0;
    for ( int i = 0; i < length; i++ ){
        itemCount += arrayHT[i].getLength();
    }
    return itemCount;
}

HashTable::~HashTable()
{
    delete [] arrayHT;
}

int HashTableTest(){
    // Create 26 Items to store in the Hash Table.
    Item * A = new Item ("Apple", NULL);
    Item * B = new Item ("Banana", NULL);
    Item * C = new Item ("Caterpillar", NULL);
    Item * D = new Item ("Dog", NULL);
    Item * E = new Item ("Elephant", NULL);
    Item * F = new Item ("Fedora", NULL);
    Item * G = new Item ("Goosebumps", NULL);
    Item * H = new Item ("House", NULL);
    Item * I = new Item ("Insects", NULL);
    Item * J = new Item ("Jam", NULL);
    Item * K = new Item ("Kite", NULL);
    Item * L = new Item ("Limestone", NULL);
    Item * M = new Item ("Mountaineering", NULL);
    Item * N = new Item ("Night", NULL);
    Item * O = new Item ("Open Sesame", NULL);
    Item * P = new Item ("Potatoes", NULL);
    Item * Q = new Item ("Quantum Mechanics", NULL);
    Item * R = new Item ("Rrrrrrrrrrawr", NULL);
    Item * S = new Item ("Snakes", NULL);
    Item * T = new Item ("Tizzy Tube", NULL);
    Item * U = new Item ("Underworld", NULL);
    Item * V = new Item ("Volcanic Ash", NULL);
    Item * W = new Item ("Who When What Why", NULL);
    Item * X = new Item ("XXX", NULL);
    Item * Y = new Item ("Yellow", NULL);
    Item * Z = new Item ("Zest of Lemon", NULL);

    // Create a Hash Table of 13 Linked List elements.
    HashTable table;
    
    // Add 3 Items to Hash Table.
    table.insertItem(A);
    table.insertItem(B);
    table.insertItem(C);
    table.printTable();
    table.printHistogram();
    
    // Remove one item from Hash Table.
    table.removeItem("Apple");
    table.printTable();
    table.printHistogram();
    
    
    // Add 23 items to Hash Table.
    table.insertItem(D);
    table.insertItem(E);
    table.insertItem(F);
    table.insertItem(G);
    table.insertItem(H);
    table.insertItem(I);
    table.insertItem(J);
    table.insertItem(K);
    table.insertItem(L);
    table.insertItem(M);
    table.insertItem(N);
    table.insertItem(O);
    table.insertItem(P);
    table.insertItem(Q);
    table.insertItem(R);
    table.insertItem(S);
    table.insertItem(T);
    table.insertItem(U);
    table.insertItem(V);
    table.insertItem(W);
    table.insertItem(X);
    table.insertItem(Y);
    table.insertItem(Z);
    table.printTable();
    table.printHistogram();
    
    // Look up an item in the hash table
    Item * result = table.getItemByKey("Snakes");
    cout << result -> key << endl;
    return 0;
}



