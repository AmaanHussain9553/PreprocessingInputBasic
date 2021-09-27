#ifndef TOKEN1
#define TOKEN1

#include <cstdio>
#include <cstring>
#include <cctype>
#include <stdbool.h>
#include <string.h>


typedef struct ArrayNumbers{
  int* arr;
  int allocated;
  int inUse;

ArrayNumbers(){ // default constructor
  arr = new int[2];
  allocated = 2;
  inUse = 0;
}

~ArrayNumbers(){ // destructor
  delete (arr);
    arr = new int[2];
}

void printArr(){
  if(inUse == 0){
    printf("Empty \n");
  }
  else{
  for(int i = 0; i <inUse; i++){
    printf(" %d ", arr[i]);
  }
    printf("\n");
  }
}

}NumStack;

typedef struct ArrayOperators{
  char* arr;
  int allocated;
  int inUse;

ArrayOperators(){
  arr = new char[2];
  allocated = 2;
  inUse = 0;
}

~ArrayOperators(){
  delete (arr);
    arr = new char[2];
}

void printArr(){
  if(inUse == 0){
    printf(" Empty \n");
  }
  else{
  for(int i = 0; i < inUse; i++){
    printf(" %c ", arr[i]);
  }
  printf("\n");
  }
}

}OpStack;

void pop(NumStack*** Array);
void pop(OpStack*** Array);
void push(NumStack** Nums, int value);
void push(OpStack** Ops, char symbol);
bool isEmpty(OpStack* Ops);
bool isEmpty(NumStack* Nums);
char top(OpStack* Ops);
int top(NumStack* Nums);
void popLastOperator(OpStack** Ops);
void clear(OpStack** Ops);
void clear(NumStack** Nums);

#endif

