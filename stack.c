#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#define INIT_SIZE 10

typedef struct{
  void** s;
  unsigned int top;
  unsigned int maxsize;
  bool is_dynamic;
}stack_t;


Stack stack_new_dynamic(void){
  stack_t* newStack = (stack_t*) malloc(sizeof(stack_t));
  
  if(newStack!=NULL){
    newStack->s = (void**) malloc(INIT_SIZE*sizeof(void*));
    newStack->top = 0;
    newStack->maxsize = 0;
    newStack->is_dynamic = true;
  }

  return (Stack) newStack;
}

Stack stack_new(unsigned int maxsize){
  stack_t* newStack = (stack_t*) malloc(sizeof(stack_t));
  
  if(newStack!=NULL){
    newStack->s = (void**) malloc(maxsize*sizeof(void*));
    newStack->top = 0;
    newStack->maxsize = maxsize;
    newStack->is_dynamic = false;
  }

  return (Stack) newStack; 
}

void stack_destroy(Stack stack){
  if((stack_t*)stack != NULL){

    free(((stack_t*)stack)->s);
    free((stack_t*)stack);

  }
}

unsigned int stack_getsize(Stack stack){
  return ((stack_t*)stack != NULL)? ((stack_t*)stack)->top:0;
}

bool stack_is_empty(Stack stack){
  if((stack_t*)stack == NULL) return false;

  return ((stack_t*)stack)->top == 0;
}

bool stack_push(Stack stack, void* element){
  if((stack_t*)stack == NULL) return false;
  
  if(((stack_t*)stack)->is_dynamic){
    ((stack_t*)stack)->s[((stack_t*)stack)->top] = element;
    ((stack_t*)stack)->top += 1;
    
    if(((stack_t*)stack)->top % INIT_SIZE == 0){
       ((stack_t*)stack)->s  = (void**) realloc (((stack_t*)stack)->s,(((stack_t*)stack)->top + INIT_SIZE)*sizeof(void*));
    }
    
    return true;
  }
  else{
     
    if(((stack_t*)stack)->top == ((stack_t*)stack)->maxsize) return false;
     
    ((stack_t*)stack)->s[((stack_t*)stack)->top] = element;
    ((stack_t*)stack)->top += 1;

  }
  
  return true;
}

void* stack_pop(Stack stack){
  if((stack_t*)stack == NULL) return NULL;

  if(stack_is_empty(stack)) return NULL;
   
  ((stack_t*)stack)->top -= 1;  
  void* returned = ((stack_t*)stack)->s[((stack_t*)stack)->top];

  if(((stack_t*)stack)->is_dynamic && !stack_is_empty(stack) &&
  (((stack_t*)stack)->top + 1) % INIT_SIZE == 0){

    ((stack_t*)stack)->s = (void**) realloc (((stack_t*)stack)->s,(((stack_t*)stack)->top + 1)*sizeof(void*));
  }

  return returned;
}

void* stack_top(Stack stack){
  if((stack_t*)stack == NULL) return NULL;

  if(stack_is_empty(stack)) return NULL;

  return ((stack_t*)stack)->s[((stack_t*)stack)->top-1];
}

void stack_traverse(Stack stack,bool stack_do(void*,void*),void* context){
   Stack newStack = stack_new_dynamic();

   while(!stack_is_empty(stack) && stack_do(stack_top(stack),context)){
      stack_push(newStack,stack_pop(stack));
   }

   while(!stack_is_empty(newStack)){
      stack_push(stack,stack_pop(newStack));
   }
}





