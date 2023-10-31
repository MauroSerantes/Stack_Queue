#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include <stdbool.h>


typedef void (*Queue);

Queue         queue_new_dynamic(void);
Queue         queue_new(unsigned int maxsize);
void          queue_free(Queue queue);
unsigned int  queue_getsize(Queue queue);
bool          queue_is_empty(Queue queue);
bool          queue_enqueue(Queue queue, void* element);
void*         queue_dequeue(Queue queue);
void*         queue_peek(Queue queue);
void          queue_traverse(Queue queue,bool queue_do(void*,void*),void* context);

#include "queue.c"
#endif //QUEUE_H_INCLUDED