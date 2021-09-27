#ifndef Token
#define Token

#include <cstdio>
#include <cstring>
#include <cctype>
#include <stdbool.h>
#include <string.h>
#include "linkedList.h"


void pop(NumStack*** Array){

  (**Array)->inUse--;


}

void pop(OpStack*** Array){
  
  (**Array)->inUse--;

}


void push(NumStack** Nums, int value){

  NumStack* Array = *Nums;
  if(Array->inUse == (Array->allocated - 1)){
    
    int* temp = new int[Array->allocated + 2];
      
      for(int i = 0; i < Array->allocated; i++){
      temp[i] = Array->arr[i];
    }

    Array->arr = temp;
    Array->allocated += 2;

  }

  Array->arr[Array->inUse] = value;
  Array->inUse++;
}

void push(OpStack** Ops, char symbol){
  
  OpStack* Array = *Ops;

  int lastInUse = Array->inUse;

  if(lastInUse == (Array->allocated - 1)){
    
    char* temp = new char[Array->allocated + 2];
      
      for(int i = 0; i < Array->allocated; i++){
      temp[i] = Array->arr[i];
    }

    Array->arr = temp;
    Array->allocated += 2;

  }

  Array->arr[lastInUse] = symbol;
  Array->inUse++;

}

bool isEmpty(OpStack* Ops){
  if(Ops->inUse == 0){
    return true;
  }
  return false;
}

bool isEmpty(NumStack* Nums){
  if(Nums->inUse == 0){
    return true;
  }
  return false;
}

char top(OpStack* Ops){
  return Ops->arr[Ops->inUse - 1];
}

int top(NumStack* Nums){
  return Nums->arr[Nums->inUse - 1];
}

void popLastOperator(OpStack** Ops){
  OpStack* Array = *Ops;
  int lastposition = Array->inUse;
  char* temp = new char[Array->allocated];
  for(int i = 0; i < lastposition; i++){
    temp[i] = Array->arr[i];
  }

  Array->arr = temp;
  Array->inUse--;
  delete[] temp;
}

void clear(OpStack** Ops){

    delete ((*Ops)->arr);
    (*Ops)->arr = new char[2];
}

void clear(NumStack** Nums){

    delete ((*Nums)->arr);
    (*Nums)->arr = new int[2];
}

#endif

