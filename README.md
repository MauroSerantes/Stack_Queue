These are templates of two dynamic data structures very well known.The stack and queue implementations
where thought with the finality of use any kind of data (the argument or value that they receive is a 
void pointer). The user does not need to worry about the memory management of the structures itselfs, 
only needs to use the constructor and the function that deletes the structure.

These are the procedures and functio that this template provides:

QUEUE:

(Queue)         queue_new_dynamic(void);

(Queue)         queue_new(unsigned int maxsize);

(void)          queue_free(Queue queue);

(unsigned int)  queue_getsize(Queue queue);

(bool)          queue_is_empty(Queue queue);

(bool)          queue_enqueue(Queue queue, void* element);

(void*)         queue_dequeue(Queue queue);

(void*)         queue_peek(Queue queue);

(void)          queue_traverse(Queue queue,bool queue_do(void*,void*),void* context);



STACK:

(Stack)           stack_new_dynamic(void);

(Stack)           stack_new(unsigned int maxsize);

(void)            stack_destroy(Stack stack);

(unsigned int)    stack_getsize(Stack stack);

(bool)            stack_is_empty(Stack stack);

(bool)            stack_push(Stack stack, void* element);

(void*)           stack_pop(Stack stack);

(void*)           stack_top(Stack stack);

(void)            stack_traverse(Stack stack,bool stack_do(void*,void*),void* context);
