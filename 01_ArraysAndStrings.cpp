#include "01_ArraysAndStrings.h"

/***********************************************
1.1
************************************************/
bool isStrHasAllUniqueChar_Method1(string str){
  bool char_set[256] = {false};

  for(int i =0; i < str.length(); i++){
    int val = str.at(i);
    if(char_set[val]) return false;
    char_set[val] = true;
  }

  return true;
}

bool isStrHasAllUniqueChar_Method2(string str){
  int checker = 0;

  for(int i =0; i < str.length(); i++){
    int val = str.at(i) - 'a';
    if((checker & (1 << val)) > 0) return false;
    checker |= (1 << val);
  }

  return true;
}

/*
Check every char of the string with every other char of the string for duplicate occurrences.
This will take O(n^2) time and no space.
*/

/*
If we are allowed to destroy the input string, we could sort the string in O(n log n) time
and then linearly check the string for neighboring characters that are identical. Careful,
though - many sorting algorithms take up extra space.
*/



/***********************************************
1.2
************************************************/

void reverseStr(char* str){
  char* end = str;
  char tmp;

  if(str){
    while(*end){
      ++end;

    }
    --end;
    while(str < end){
      tmp = *str;
      *str++ = *end;
      *end-- = tmp;
    }
  }
}