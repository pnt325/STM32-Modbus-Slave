/* 
 * File:   queue_circle_array.h
 * Author: PhuongXV
 *
 * Created on September 14, 2018, 10:33 AM
 * 2018-Otc-13: Mofified function names, and fixed datatype to uint8_t
 *              Return Value 0 is TRUE and others are FALSE
 */

#ifndef QUEUE_CIRCLE_ARRAY_H
#define	QUEUE_CIRCLE_ARRAY_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>


#define RET_TRUE    0
#define RET_FALSE   1
    
#define Queue_Put Queue_EnQueue
    
typedef uint8_t queue_data_type;
typedef struct
{
queue_data_type *data;
uint16_t         front;
uint16_t         rear;
uint16_t         queueSize;
}struct_queue_array;

/*Function Proctotype*/
uint8_t Queue_Initialize (struct_queue_array *queue, queue_data_type *array, uint16_t queueSize);
void Queue_MakeNull (struct_queue_array *queue);

uint8_t Queue_IsEmpty(struct_queue_array *queue);
uint8_t Queue_IsFull(struct_queue_array *queue);

/**
 * Enter @rear Out from front
 */

/*Insert an element at rear position*/
uint8_t Queue_EnQueue(struct_queue_array *queue, queue_data_type element);

/*Get & Delete front element*/
queue_data_type Queue_DeQueue(struct_queue_array *queue);

/*Get without delete front element*/
queue_data_type Queue_Peek (struct_queue_array *queue);

/*Get & Erase one Element of Queue;*Return 0 of success (queue is not empty*/
uint8_t Queue_Get(struct_queue_array *queue, queue_data_type *element);

/*Pick & Not Erase one Element of queue;*/
uint8_t Queue_Check(struct_queue_array *queue, queue_data_type *element);

/*Get elements number in the Queue*/
uint16_t Queue_GetFill(struct_queue_array *queue);

uint8_t Queue_PeekIndex(struct_queue_array *queue, queue_data_type *element, uint16_t index);
uint8_t Queue_EnQueueNew(struct_queue_array *queue, queue_data_type element);

/*Queue_GetToString: return len & string with NULL end*/
uint16_t Queue_GetToString (struct_queue_array *q, uint8_t *s);

uint16_t Queue_GetRemainSize(struct_queue_array *q);  

#ifdef	__cplusplus
}
#endif

#endif	/* QUEUE_CIRCLE_ARRAY_H */

