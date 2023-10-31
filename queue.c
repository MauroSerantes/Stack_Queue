#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#define INIT_SIZE 10

typedef struct{
    void** a;
    unsigned int head;   
    unsigned int tail;   
    unsigned int maxsize;
    unsigned int count;
    bool is_dynamic;
}queue_t;


Queue queue_new(unsigned int maxsize){
  queue_t* newQueue = (queue_t*) malloc(sizeof(queue_t));
  
  if(newQueue!=NULL){
    newQueue->a = (void**) malloc(maxsize*sizeof(void*));
    newQueue->head = 0;
    newQueue->tail = 0;
    newQueue->count = 0;
    newQueue->maxsize = maxsize;
    newQueue->is_dynamic = false;  
  }

  return (Queue) newQueue;
}

Queue queue_new_dynamic(void){
 queue_t* newQueue = (queue_t*) malloc(sizeof(queue_t));
  
  if(newQueue!=NULL){
    newQueue->a = (void**) malloc(INIT_SIZE*sizeof(void*));
    newQueue->head = 0;
    newQueue->tail = 0;
    newQueue->count = 0;
    newQueue->maxsize = 0;
    newQueue->is_dynamic  = true;  
  }

  return (Queue) newQueue;
}

void queue_free(Queue queue){
  if((queue_t*)queue != NULL){
    free(((queue_t*)queue)->a);
    free((queue_t*)queue);
  }
}

unsigned int  queue_getsize(Queue queue){
  return ((queue_t*)queue!=NULL)?((queue_t*)queue)->count:0; 
}

bool queue_is_empty(Queue queue){
  if((queue_t*) queue == NULL) return false;

  return ((queue_t*)queue)->count == 0;
}

bool queue_enqueue(Queue queue, void* element){
  if((queue_t*)queue == NULL) return false;

  if(((queue_t*)queue)->is_dynamic){
     ((queue_t*)queue)->a[((queue_t*)queue)->tail] = element;
     ((queue_t*)queue)->tail += 1;
     ((queue_t*)queue)->count += 1;

     if(((queue_t*)queue)->tail % INIT_SIZE == 0){
        ((queue_t*)queue)->a = (void**) realloc(((queue_t*)queue)->a,(((queue_t*)queue)->count + INIT_SIZE)*sizeof(void*));
     }

  }
  else{
    
    if(((queue_t*)queue)->count == ((queue_t*)queue)->maxsize) return false;
     
    ((queue_t*)queue)->a[((queue_t*)queue)->tail] = element;
    ((queue_t*)queue)->tail += 1;
    
    if(((queue_t*)queue)->tail == ((queue_t*)queue)->maxsize){
      ((queue_t*)queue)->tail = 0;  
    }
    
    ((queue_t*)queue)->count += 1;
  }  
  return true;
}


void* queue_dequeue(Queue queue){
  if((queue_t*)queue == NULL) return NULL;

  if(queue_is_empty(queue)) return NULL;
  
  void* returned = ((queue_t*)queue)->a[((queue_t*)queue)->head];
  
  if(((queue_t*)queue)->is_dynamic){
    ((queue_t*)queue)->head++;
    ((queue_t*)queue)->count--;
    
    if(((queue_t*)queue)->head % INIT_SIZE == 0){

        for(unsigned int i=0; i<((queue_t*)queue)->tail;i++){
           ((queue_t*)queue)->a[i-INIT_SIZE] = ((queue_t*)queue)->a[i]; 
        }
        
        ((queue_t*)queue)->head -= INIT_SIZE; 
        ((queue_t*)queue)->tail -= INIT_SIZE;

        ((queue_t*)queue)->a = (void**) realloc(((queue_t*)queue)->a,(((queue_t*)queue)->count-INIT_SIZE)*sizeof(void*));
    }

  }
  else{
    ((queue_t*)queue)->head++;

    if(((queue_t*)queue)->head == ((queue_t*)queue)->maxsize){
      ((queue_t*)queue)->head = 0;  
    }
  
    ((queue_t*)queue)->count--;
  }    
  return returned;
}

void* queue_peek(Queue queue){
   if((queue_t*)queue == NULL) return NULL;

   if(queue_is_empty(queue)) return NULL;

   return ((queue_t*)queue)->a[((queue_t*)queue)->head];
}


void queue_traverse(Queue queue,bool queue_do(void*,void*),void* context){
  if((queue_t*)queue == NULL) return;
  
  unsigned int counter = 0;

  while(counter<queue_getsize(queue) && queue_do(queue_peek(queue),context)){
    void* auxiliar = queue_dequeue(queue);
    queue_enqueue(queue,auxiliar);
    counter++;  
  }
  while(counter<queue_getsize(queue)){
    queue_enqueue(queue,queue_dequeue(queue));  
  }
}


