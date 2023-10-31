#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"
#include "stack.h"


//test both implementations
Stack creation_of_random_integer_stack(unsigned int mvalue);
void stack_printf(Stack stck);
void stack_invert_elements(Stack stack);

int main(void){
  srand(time(NULL));
  
  Stack val = creation_of_random_integer_stack(10);
  stack_printf(val);
  stack_invert_elements(val);
  printf("\n");
  stack_printf(val);
  stack_free(val); 

  return 0;    
}
  
Stack creation_of_random_integer_stack(unsigned int mvalue){
   Stack newStack = stack_new(mvalue);

   for(unsigned int i=0;i<mvalue;i++){
     int* pointer = (int*) malloc(sizeof(int));
     *pointer = (int)(rand()%30); 
     stack_push(newStack,pointer);
   }
   
   return newStack;
}

void stack_printf(Stack stck){
   if(!stack_is_empty(stck)){
      int* val = stack_pop(stck);
      printf("%d ",*val);
      stack_printf(stck);
      stack_push(stck,val);
   }
}

void stack_invert_elements(Stack stack){
   Queue queue = queue_new(stack_getsize(stack));

   while(!stack_is_empty(stack)){
      queue_enqueue(queue,stack_pop(stack));
   }

   while(!queue_is_empty(queue)){
      stack_push(stack,queue_dequeue(queue));
   }
    
   queue_free(queue); 
}

