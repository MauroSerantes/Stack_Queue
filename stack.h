#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <stdbool.h>

typedef void (*Stack);

Stack           stack_new_dynamic(void);
Stack           stack_new(unsigned int maxsize);
void            stack_destroy(Stack stack);
unsigned int    stack_getsize(Stack stack);
bool            stack_is_empty(Stack stack);
bool            stack_push(Stack stack, void* element);
void*           stack_pop(Stack stack);
void*           stack_top(Stack stack);
void            stack_traverse(Stack stack,bool stack_do(void*,void*),void* context);

#include "stack.c"
#endif // STACK_H_INCLUDED