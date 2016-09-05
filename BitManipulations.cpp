#include "BitManipulations.h"

void setBit(int index, int* destVar){
  *destVar |= 1 << index; 
}

void  clearBit(int index, int* destVar){
  *destVar &= ~(1 << index);
}

void toggleBit(int index, int* destVar){
  *destVar ^= 1 << index;
}

int checkBit(int index, int destVar){
  return (destVar >> index) & 1;
}

void changeBit(int index, int* destVar, int val){
  *destVar ^= (-val ^ *destVar) & (1 << index);
}